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

#include "Greedy_OBS_Routing.h"

Define_Module(Greedy_OBS_Routing);

void Greedy_OBS_Routing::initialize(int stage)
{
    Flexi_OBS_Routing::initialize(stage);
}

void Greedy_OBS_Routing::handleMessage(cMessage *msg)
{
    Flexi_OBS_Routing::handleMessage(msg);

    if(strcmp(msg->getName(), "burst") == 0)
    {
        OBS_Burst *burst = check_and_cast<OBS_Burst*>(msg);
        doGreedy(burst);
    }
}

void Greedy_OBS_Routing::doGreedy(OBS_Burst *burst)
{
    Flexi_OBS_BurstControlPacket *bcp = new Flexi_OBS_BurstControlPacket("BCP");
    bcp->setIsControl(true);
    K_ShortestPathTable* pathTable = getShortestPathTable();

    OBS_BurstifierInfo *info = check_and_cast< OBS_BurstifierInfo *>(burst->getControlInfo());
    int destAddr = info->getLabel();

    Flexi_OBS_BurstRouterInfo *rInfo = new Flexi_OBS_BurstRouterInfo();
    rInfo->setLabel(destAddr);
    burst->removeControlInfo();
    burst->setControlInfo(rInfo);

    K_ShortestPathTableEntry *path = pathTable->getTop(destAddr);

    if(path == NULL)
    {
        EV << to_string(destAddr) << " does not have shortest path table entries (id=" << to_string(this->getId()) << ").";
        return;
    }

    simtime_t offset = calculateMinimumOffset(path);
    int gate = getLocalOutGate(path->getPath(0));

    bcp->setDestAddr(destAddr);
    bcp->setSrcAddr(path->getSrcAddress());
    bcp->setBurstifierId(burst->getBurstifierId());
    bcp->setNumSeq(burst->getNumSeq());
    bcp->setBurstSize(burst->getByteLength());
    bcp->setDatarate(getDatarate());
    bcp->setRoute(path);
    bcp->setBurstOffset(offset);

    bcp->setSchedulingPriority(3);
    bcp->setRoutePos(2);

    bcp->setSourceSendTIme(simTime());
    burst->setSourceSendTIme(simTime());

    send(bcp, gate);
    controlSent++;

    sendDelayed(burst, offset, gate);

    sentBurst++;
    destVector.record(destAddr);
    emit(sentBurstId, true);
}
