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

#include "Flexi_OBS_CoreInput.h"

Define_Module(Flexi_OBS_CoreInput);

void Flexi_OBS_CoreInput::initialize()
{
    burstRecieved = 0;
    controlRecieved = 0;
    bcpRecieved = 0;
    conversionDelay = par("OEConversionDelay");
}

void Flexi_OBS_CoreInput::handleMessage(cMessage *msg){
    const char *name;
    name = msg->getName();

    if(strcmp(name, "burst") == 0){ send(msg, "outOXC"); burstRecieved++;}
    else
    {
        controlRecieved++;
        OBS_CoreNodeInfo* info = new OBS_CoreNodeInfo();
        info->setInputPort(msg->getArrivalGate()->getPreviousGate()->getId());
        msg->removeControlInfo();
        msg->setControlInfo(info);


        if(strcmp(msg->getName(), "BCP") == 0){
            bcpRecieved++;
            Flexi_OBS_BurstControlPacket* bcp = check_and_cast<Flexi_OBS_BurstControlPacket*>(msg);
            bcp->setBurstOffset(bcp->getBurstOffset() - conversionDelay);
        }

        sendDelayed(msg, conversionDelay, "outControl");
    }
}

void Flexi_OBS_CoreInput::finish()
{
    recordScalar("burst recieved", burstRecieved);
    recordScalar("control recieved", controlRecieved);
    recordScalar("bcp recieved", bcpRecieved);
}

Flexi_OBS_CoreInput::~Flexi_OBS_CoreInput() {
    // TODO Auto-generated destructor stub
}

