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

#include "Flexi_OBS_Routing.h"

Define_Module(Flexi_OBS_Routing);

void Flexi_OBS_Routing::initialize(int stage)
{
    if(stage == 0){
        registerInterface();

        sentBurstId = registerSignal("sentBurst");

        droppedBurst = 0;
        sentBurst = 0;
        controlSent = 0;
        destVector.setName("Burst sent to dest");
        burstInterarrivalTimes.setName("burst interarrival time");
        dataratesVector.setName("datarates");

        spectrumLowerBound = par("spectrumLowerBound");
        spectrumUpperBound = par("spectrumUpperBound");
        gridType = par("gridType");
        coreNodeProcessingTime = par("coreNodeProcessingTime");
        switchingDelay = par("switchingDelay");
        deferRouting = par("deferRoutingWhenInSuperNode");
        inSuperNode = par("InSuperNode");

        switch(gridType)
        {
        case 0: assignedSpectrumWidth = 12.5;
        break;
        case 1: assignedSpectrumWidth = 50;
        break;
        case 2: assignedSpectrumWidth = 100;
        break;
        }

        numOfWavelengths = (spectrumUpperBound - spectrumLowerBound)/assignedSpectrumWidth;

        const char *d = par("datarates");
        const char *p = par("datarateProbabilities");
        cStringTokenizer tokenizer(d);
        cStringTokenizer tokenizer2(p);

        while (tokenizer.hasMoreTokens())
            datarates.push_back(strtod(tokenizer.nextToken(), NULL)*1000000000);

        probabilities = tokenizer2.asDoubleVector();

        double sum = 0;
        for(int i = 0; i < probabilities.size(); i++)
            sum += probabilities[i];


        if(sum != 1)
            EV_ERROR << "datarate percentages don't add up to 1" << endl;
    }

    if(stage == 3)
        ipAddr = getShortestPathTable()->getTop(0, false)->getSrcAddress();
}

void Flexi_OBS_Routing::finish()
{
    recordScalar("Burst received",recvBurstSize.getCount());
    recordScalar("Average burst size",recvBurstSize.getMean());
    recordScalar("Burst size variance",recvBurstSize.getVariance());
    recordScalar("Min Burst size", recvBurstSize.getMin());
    recordScalar("Max Burst size", recvBurstSize.getMax());

    recordScalar("Average Burst interarrival time", interArrivalTimes.getMean());
    recordScalar("Interarrival Burst variance",interArrivalTimes.getVariance());

    recordScalar("Burst dropped at source", droppedBurst);
    recordScalar("Burst sent by source", sentBurst);
    recordScalar("Control messages sent by node", controlSent);
    recordScalar("IP Address", ipAddr);
}

void Flexi_OBS_Routing::handleMessage(cMessage *msg)
{

    if(strcmp(msg->getName(), "burst")==0){
        OBS_Burst* burst = check_and_cast<OBS_Burst*>(msg);

        recvBurstSize.collect(burst->getByteLength());

        if(interArrivalTimes.getCount() == 0){
            lastBurst_t = simTime();
            interArrivalTimes.collect(0);
            burstInterarrivalTimes.record(0);
        }else
        {
            interArrivalTimes.collect(simTime() - lastBurst_t);
            burstInterarrivalTimes.record(simTime() - lastBurst_t);
            lastBurst_t = simTime();
        }

        if(inSuperNode && deferRouting)
        {
            Flexi_OBS_BurstControlPacket *bcp = new Flexi_OBS_BurstControlPacket("BCP");
            bcp->setIsControl(true);
            //send bcp and burst on only gate
            OBS_BurstifierInfo *info = check_and_cast< OBS_BurstifierInfo *>(burst->getControlInfo());
            int destAddr = info->getLabel();
            Flexi_OBS_BurstRouterInfo *rInfo = new Flexi_OBS_BurstRouterInfo();
            rInfo->setLabel(ipAddr);
            burst->removeControlInfo();
            burst->setControlInfo(rInfo);

            bcp->setDestAddr(destAddr);
            bcp->setSrcAddr(ipAddr);
            bcp->setBurstifierId(burst->getBurstifierId());
            bcp->setNumSeq(burst->getNumSeq());
            bcp->setBurstSize(burst->getByteLength());
            bcp->setDatarate(getDatarate());
            bcp->setSchedulingPriority(3);

            bcp->setSourceSendTIme(simTime());
            burst->setSourceSendTIme(simTime());

            send(bcp, gateBaseId("out"));
            controlSent++;
            sendDelayed(burst, coreNodeProcessingTime + switchingDelay, gateBaseId("out"));
            sentBurst++;
            destVector.record(destAddr);
            emit(sentBurstId, true);
            return;
        }
    }

    if(strcmp(msg->getName(), "successfulBcpAck") == 0 || strcmp(msg->getName(), "failedBcpAck") == 0)
    {
        EndToEndAck *ack = check_and_cast<EndToEndAck*>(msg);

        if(ack->getControlInfo()){
            Flexi_OBS_DisassemblerInfo *info = check_and_cast<Flexi_OBS_DisassemblerInfo*>(ack->getControlInfo());
            int gate = getLocalOutGate(info->getEntryPort());
            send(ack, gate);
        }else{
            int gate = getLocalOutGate(ack->getRoute()->getPath(ack->getRoutePos()));
            ack->setRoutePos(ack->getRoutePos()-2);
            send(ack, gate);
        }
        controlSent++;
    }
}

int Flexi_OBS_Routing::getLocalOutGate(int gate)
{
    cModule* edgeNode = this->getParentModule()->getParentModule()->getParentModule();
    cGate *outGate = edgeNode->gate(gate);

    std::string buf(outGate->getBaseName());
    buf.append("$o");

    outGate = edgeNode->gate(buf.c_str(), outGate->getIndex());

    return outGate->getPreviousGate()->getPreviousGate()->getPreviousGate()->getId();
}

Flexi_OBS_EdgeRoutingTable* Flexi_OBS_Routing::getTable()
{
    return check_and_cast<Flexi_OBS_EdgeRoutingTable *>(this->getParentModule()->getParentModule()->getSubmodule("EdgeRoutingTable"));
}

K_ShortestPathTable* Flexi_OBS_Routing::getShortestPathTable()
{
    return check_and_cast<K_ShortestPathTable *>(this->getParentModule()->getParentModule()->getParentModule()->getSubmodule("k_ShortestPathTable"));
}

// Code taken from INET Router module. Register the OBS interface into the interface table among other things
InterfaceEntry* Flexi_OBS_Routing::registerInterface (){
    InterfaceEntry *e = new InterfaceEntry(this);

    const char * s = getParentModule()->getParentModule()->getFullName();
    std::string name;
    for (; *s; s++){
        if (isalnum(*s)){
            name += *s;
        }
    }
    e->setName(name.c_str());
    e->setLoopback(false);
    // data rate
    e->setDatarate(1);

    // generate a link-layer address to be used as interface token for IPv6
    InterfaceToken token(0, getSimulation()->getUniqueNumber(), 64);
    e->setInterfaceToken(token);

    // MTU: typical values are 576 (Internet de facto), 1500 (Ethernet-friendly),
    // 4000 (on some point-to-point links), 4470 (Cisco routers default, FDDI compatible)
    e->setMtu(4470);

    // capabilities
    e->setMulticast(false);
    e->setPointToPoint(true);

    // add
    IInterfaceTable *ift = check_and_cast<IInterfaceTable *>(this->getParentModule()->getParentModule()->getParentModule()->getSubmodule("interfaceTable"));
    if (ift)
        ift->addInterface(e);
    //Maybe this could be useful in the future...
    //  e->setNodeOutputGateId(e->getNodeOutputGateId()-lambda*idInterfaz);
    //e->setNodeOutputGateId(e->getNodeOutputGateId()-lambda+1);

    return e;
}


simtime_t Flexi_OBS_Routing::calculateMinimumOffset(K_ShortestPathTableEntry* path)
{
    int k = (path->getPathArraySize()/2) - 1;//number of intermediate nodes

    return (k*coreNodeProcessingTime) + switchingDelay;

}

double Flexi_OBS_Routing::getDatarate()
{
    double rand = dblrand();
    double sum = 0;

    for(int i = 0; i < probabilities.size(); i++)
    {
        sum += probabilities[i];

        if(rand < sum){
            dataratesVector.record(datarates[i]);
            return datarates[i];
        }
    }
}
