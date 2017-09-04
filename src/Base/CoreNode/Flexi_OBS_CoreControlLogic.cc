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

#include "Flexi_OBS_CoreControlLogic.h"

Define_Module(Flexi_OBS_CoreControlLogic);

void Flexi_OBS_CoreControlLogic::initialize(int stage)
{
    if(stage == 0){
        oxc = this->getOXC();

        processingDelay = par("BCPProcessingDelay");
        conversionDelay = par("EOConversionDelay");
        coreNodeProcessingTime = par("coreNodeProcessingTime");
        switchingDelay = par("switchingDelay");

        spectrumLowerBound = par("spectrumLowerBound");
        spectrumUpperBound = par("spectrumUpperBound");
        gridType = par("gridType");
        inSuperNode = par("inSuperNode");
        lostBCPId = registerSignal("lostBCP");

        switch(gridType)
        {
        case 1: assignedSpectrumWidth = 50;
        break;
        case 2: assignedSpectrumWidth = 100;
        break;
        }
    }
}

void Flexi_OBS_CoreControlLogic::handleMessage(cMessage *msg)
{
    if(strstr(msg->getName(), "BcpAck") != NULL)
    {
        EndToEndAck *e = check_and_cast<EndToEndAck*>(msg);
        K_ShortestPathTableEntry *route = e->getRoute();

        //        int outGate = getOutputGate(route->getPath(route->getPathArraySize() + e->getRoutePos()));
        int outGate = getOutputGate(route->getPath(e->getRoutePos()));

        if(outGate > -1)
        {
            e->setRoutePos(e->getRoutePos()-2);
            oxc->releaseOutLink(e->getNumSeq(), e->getBurstifierId());
            oxc->setOutLink(e->getNumSeq(), e->getBurstifierId(), outGate);
            sendDelayed(msg, processingDelay+conversionDelay, "outOXC");
        }
    }
}

Flexi_OBS_OpticalCrossConnect* Flexi_OBS_CoreControlLogic::getOXC()
{
    return check_and_cast<Flexi_OBS_OpticalCrossConnect *>(this->getParentModule()->getSubmodule("OXC"));
}

int Flexi_OBS_CoreControlLogic::getOutputGate(int gate)
{
    cModule* coreNode = this->getParentModule();
    cGate *outGate = coreNode->gate(gate);

    std::string buf(outGate->getBaseName());
    buf.append("$o");

    outGate = coreNode->gate(buf.c_str(), outGate->getIndex());

    return outGate->getPreviousGate()->getId();
}

Flexi_OBS_CoreRoutingTable* Flexi_OBS_CoreControlLogic::getTable()
{
    return check_and_cast<Flexi_OBS_CoreRoutingTable *>(this->getParentModule()->getSubmodule("iCoreRoutingTable"));
}

K_ShortestPathTable* Flexi_OBS_CoreControlLogic::getShortestPathTable()
{
    return check_and_cast<K_ShortestPathTable *>(this->getParentModule()->getSubmodule("k_ShortestPathTable"));
}

simtime_t Flexi_OBS_CoreControlLogic::calculateMinimumOffset(K_ShortestPathTableEntry* path)
{
    int k = (path->getPathArraySize()/2) - 1;//number of intermediate nodes

    return (k*coreNodeProcessingTime) + switchingDelay;

}
