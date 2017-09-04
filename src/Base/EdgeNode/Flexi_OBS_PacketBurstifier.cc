//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Flexi_OBS_PacketBurstifier.h"

Define_Module(Flexi_OBS_PacketBurstifier);

void Flexi_OBS_PacketBurstifier::initialize()
{
    assembly = par("assembly");
    destLabel = -1;
    timeout = par("timeout");
    maxSize = par("maxSize");
    numPackets = par("numPackets");
    minSizeWithPadding = par("minSizeWithPadding");
    overflowLastPacket = par("overflowLastPacket");

    cteHeader = par("cteHeader");
    varHeader = par("varHeader");
    includeMsgsInBurst = par("includeMsgsInBurst");

    //Initialize queue
    burstContent.setName("burstifierQueue");

    //Initialize counters
    int cteHeaderInBits = cteHeader*8;
    burstBits = cteHeaderInBits;
    numBurstPackets = 0;

    //Create timeout message
    timeout_msg = new cMessage("timeout");

    //statistics
    recvPackSizeVec.setName("burstifierInPacketSize");
    avgPacketTime.setName("avgPacketTime");
    recvPackSize.setName("recvPackSize");
    queuedTime.setName("queuedTime");
    burstSize.setName("Burst sizes");
    burstCounter = 0;
    dispatch = check_and_cast<Flexi_OBS_PacketDispatcher*>(getParentModule()->getSubmodule("dispatcher"));

    WATCH(burstBits);
    recordScalar("my ID",getId());
    assembledSignalId = registerSignal("queueAssembled");
}

void Flexi_OBS_PacketBurstifier::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){ //If a self-message is received...
        //Assemble the burst and restart the variables
        assembleBurst();

        cMessage *msg = new cMessage("freeQueue");
        msg->addPar("dest").setLongValue(destLabel);
        sendDirect(msg, dispatch, "infoIn");
        return;
    }

    INetworkProtocolControlInfo *controlInfo = check_and_cast<INetworkProtocolControlInfo*>(msg->getControlInfo());
    if(numBurstPackets > 0 && controlInfo->getDestinationAddress().toIPv4().getInt() != destLabel){
        delete(msg);
        EV_ERROR<< "Packet sent to wrong burstifier";
        return;
    }else if(numBurstPackets == 0) destLabel = controlInfo->getDestinationAddress().toIPv4().getInt();

    switch(assembly)//Else.... is it a IP Datagram?
    {
    case 0: doMixedAssembly(msg);
    break;
    }
}

void Flexi_OBS_PacketBurstifier::doMixedAssembly(cMessage* msg)
{
    //      IPDatagram *arrivedMsg = check_and_cast < IPDatagram *> (msg);
    cPacket *arrivedMsg = check_and_cast <cPacket*> (msg);

    //record incoming packet
    recvPackSizeVec.record(arrivedMsg->getByteLength());
    recvPackSize.collect(arrivedMsg->getByteLength());

    bool overflowHappened = false;
    int maxSizeInBits = maxSize*8;
    int varHeaderInBits = varHeader*8;

    if(((burstBits + arrivedMsg->getBitLength() + varHeaderInBits) > maxSizeInBits)) overflowHappened = true;

    // Check if burstifier is empty
    if(numBurstPackets == 0){ // If so, start timeout and initialize queue
        scheduleAt(simTime()+timeout,timeout_msg); //Set the timeout
        //Register first packet arrival time
        firstPacket_t = simTime();
    }
    else if (overflowHappened && !overflowLastPacket){ // Enter if burst assembly is needed before the packet is inserted into the queue
        //If queue is empty at this moment, display an error message because something weird happened :S
        if(numBurstPackets == 0) EV_ERROR << "Attempted to assemble a burst using an empty queue";
        //Assemble burst and restart counters
        assembleBurst();

        if(timeout_msg->isScheduled()) cancelEvent(timeout_msg); //Cancel current timeout and schedule a new one
        scheduleAt(simTime()+timeout,timeout_msg);
        firstPacket_t = simTime();
        //Calculate if overflow happens with the first message
        overflowHappened = false;
        if(((burstBits + arrivedMsg->getBitLength() + varHeaderInBits) > maxSizeInBits)) overflowHappened = true;
    }

    //Anyway, insert the current message into the queue
    queuedTime.collect(simTime() - firstPacket_t);

    burstBits += arrivedMsg->getBitLength() + varHeaderInBits;
    numBurstPackets++;

    //If burst overflow is not allowed, but overflow happens when you insert the first message, show an error message
    if(overflowHappened && !overflowLastPacket) EV_ERROR<< "Queue overflow happened inserting the first message and you don't allow Queue overflow (overflowLastPacket is false) " << arrivedMsg->getBitLength();

    if(includeMsgsInBurst)
           burstContent.insert(msg);
       else delete(msg);

    //If either overflow happened or maximum size/packets reached appending this message, assemble it now!
    if((overflowHappened || numBurstPackets == numPackets) || burstBits == maxSizeInBits){
        assembleBurst();
        if(timeout_msg->isScheduled()) cancelEvent(timeout_msg);

        cMessage *msg = new cMessage("freeQueue");
        msg->addPar("dest").setLongValue(destLabel);

        sendDirect(msg, dispatch, "infoIn");
    }
}

void Flexi_OBS_PacketBurstifier::assembleBurst(){
    // Record into avgPacketTime the average waiting time for all messages from this burst
    avgPacketTime.record((simTime() - firstPacket_t) - queuedTime.getMean());

    // Check if burst reaches a minimum size. If not, fill with padding
    int minSizeWithPaddingInBits = minSizeWithPadding*8;
    if(burstBits < minSizeWithPaddingInBits) burstBits = minSizeWithPaddingInBits;

    //Create burst and insert queue contents
    OBS_Burst *assembledBurst = new OBS_Burst("burst");

    assembledBurst->setNumPackets(numBurstPackets);
    assembledBurst->setBitLength(burstBits);
    assembledBurst->setByteLength(burstBits/8);

    assembledBurst->setBurstifierId(getId());
    assembledBurst->setNumSeq(burstCounter++);

    OBS_BurstifierInfo *info = new OBS_BurstifierInfo();
    info->setLabel(destLabel);
    assembledBurst->setControlInfo(info);

    //SenderID will be set once the burst arrives at the sender
    cMessage *tempMsg;
    while(!(burstContent.isEmpty())){
        tempMsg = (cMessage*)burstContent.pop();
        assembledBurst->insertMessage(tempMsg);
    }

    //Cleanup
    burstContent.clear();
    numBurstPackets = 0;
    int cteHeaderInBits = cteHeader*8;
    burstBits = cteHeaderInBits;
    firstPacket_t = 0;

    burstSize.record(assembledBurst->getByteLength()); // Record burst length and update burst counter
    //Burst finally assembled. Send to output gate
    send(assembledBurst,"out");
}

void Flexi_OBS_PacketBurstifier::finish(){
    recordScalar("Packets received",recvPackSize.getCount());
    recordScalar("Average packet size",recvPackSize.getMean());
    recordScalar("Packet size variance",recvPackSize.getVariance());
}

Flexi_OBS_PacketBurstifier::~Flexi_OBS_PacketBurstifier()
{
    cancelAndDelete(timeout_msg);
}
