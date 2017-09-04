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

#include "Greedy_CoreControlLogic.h"

Define_Module(Greedy_CoreControlLogic);

void Greedy_CoreControlLogic::handleMessage(cMessage *msg)
{
    if(strcmp(msg->getName(), "BCP") ==0){
        Flexi_OBS_BurstControlPacket *bcp = check_and_cast<Flexi_OBS_BurstControlPacket *>(msg);

        if(bcp->getBurstOffset() >= 0){
            K_ShortestPathTableEntry *route = bcp->getRoute();

            int outGate = getOutputGate(route->getPath(bcp->getRoutePos()));

            if(outGate > -1)
            {
                bcp->setRoutePos(bcp->getRoutePos()+2);
                oxc->setOutLink(bcp->getNumSeq(), bcp->getBurstifierId(), outGate);

                bcp->setBurstOffset(bcp->getBurstOffset() - (processingDelay+conversionDelay));

                sendDelayed(msg, processingDelay+conversionDelay, "outOXC");
                return;
            }

            EV << "Could not route bcp numseq:" << to_string(bcp->getNumSeq()) << " burstifierId: " << to_string(bcp->getBurstifierId());
            delete(msg);
        }else
            {
               emit(lostBCPId, 4);
               delete(msg);
            }
    }
}
