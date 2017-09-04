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

#include "Flexi_OBS_PacketDispatcher.h"

Define_Module(Flexi_OBS_PacketDispatcher);

void Flexi_OBS_PacketDispatcher::initialize()
{
    numQueues = par("numQueues");
    droppedPacket = 0;
    WATCH(droppedPacket);

    //initialize the statistic variables
    recvPackSizeVec.setName("recvPacketSize");
    recvPackSize.setName("recvPackSize");
    //end of initialization

    if (numQueues == 0)
        EV_ERROR << "Burst Assembler must have at least one packet burstifier";
}

//need to set inUse to false when notifications come in(inUse can be used to simulate hardware constraints)
void Flexi_OBS_PacketDispatcher::handleMessage(cMessage *msg)
{
    if(strcmp(msg->getName(), "freeQueue")==0){
        int dest = msg->par("dest");
        freeQueue(dest);
        delete(msg);
        return;
    }

    // Make sure the received message is an IPDatagram
    //   IPDatagram *recvIP = check_and_cast< IPDatagram* > (msg);
    cPacket *recvIP = dynamic_cast<cPacket*> (msg);

    if(recvIP == NULL)
    {
        delete(msg);
        return;
    }

    if(interArrivalTimes.getCount() == 0){
        lastPacket_t = simTime();
        interArrivalTimes.collect(0);
    }else
    {
        interArrivalTimes.collect(simTime() - lastPacket_t);
        lastPacket_t = simTime();
    }

    INetworkProtocolControlInfo *controlInfo = check_and_cast<INetworkProtocolControlInfo*>(recvIP->getControlInfo());
    //register incoming packet
    recvPackSizeVec.record(recvIP->getByteLength());
    recvPackSize.collect(recvIP->getByteLength());
    //end of register

    int destAddress = controlInfo->getDestinationAddress().toIPv4().getInt();

    int pos = searchMonitorArray(destAddress, true);

    if(pos > -1)
    {
        if(!monitorArray[pos].inUse)
            monitorArray[pos].inUse = true;

        cGate *outGate = gate("out", pos);
        send(msg, outGate);
        return;
    }

    //No burstifier matches, and all burstifiers are busy then discard packet
    delete msg;
    //count discarded packet
    droppedPacket++;
}

int Flexi_OBS_PacketDispatcher::searchMonitorArray(int dest, bool assign)
{
    int i, j = -1;
    for(i = 0; i < monitorArray.size(); i++)
    {
        if((monitorArray[i].dest) == dest)
            return i;

        if( j == -1 && !monitorArray[i].inUse)
            j = i;
    }

    if(assign){
        if(monitorArray.size() != numQueues){
            QueueAssignment temp;
            monitorArray.push_back(temp);
            monitorArray[monitorArray.size()-1].dest = dest;
            monitorArray[monitorArray.size()-1].outGate = monitorArray.size()-1;

            return monitorArray.size()-1;
        }else if(monitorArray.size() == numQueues && j != -1){
            monitorArray[j].dest = dest;
            return j;
        }
    }

    return -1;
}

void Flexi_OBS_PacketDispatcher::freeQueue(int dest)
{
    int pos = searchMonitorArray(dest, false);

    if(pos != -1)
    {
        monitorArray[pos].inUse = false;
    }
}

void Flexi_OBS_PacketDispatcher::finish(){
    recordScalar("Packets received",recvPackSize.getCount());
    recordScalar("Average packet size",recvPackSize.getMean());
    recordScalar("Packet size variance",recvPackSize.getVariance());
    recordScalar("Min Packet size",recvPackSize.getMin());
    recordScalar("Max Packet size",recvPackSize.getMax());

    recordScalar("Average packet interarrival time", interArrivalTimes.getMean());
    recordScalar("Interarrival time variance",interArrivalTimes.getVariance());
    recordScalar("Dropped Packets",droppedPacket);
}



