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

#ifndef __OBSMODULES_FLEXI_OBS_CORECONTROLLOGIC_H_
#define __OBSMODULES_FLEXI_OBS_CORECONTROLLOGIC_H_

#include <omnetpp.h>
#include "Flexi_OBS_OpticalCrossConnect.h"
#include "K_ShortestPathTableEntry_m.h"
#include "K_ShortestPathTable.h"
#include "Flexi_OBS_BurstControlPacket_m.h"
#include "EndToEndAck_m.h"
#include "Flexi_OBS_CoreRoutingTable.h"

using namespace omnetpp;
/**
 * TODO - Generated class
 */
class Flexi_OBS_CoreControlLogic : public cSimpleModule
{
protected:
    Flexi_OBS_OpticalCrossConnect* oxc;
    simsignal_t lostBCPId;
    int gridType;
    bool inSuperNode;
    double spectrumLowerBound, spectrumUpperBound, assignedSpectrumWidth;
    simtime_t processingDelay, conversionDelay, coreNodeProcessingTime, switchingDelay;
    virtual void initialize(int stage);
    virtual int numInitStages() const  {return 4;}
    virtual void handleMessage(cMessage *msg);
    Flexi_OBS_OpticalCrossConnect* getOXC();
    int getOutputGate(int gate);

    Flexi_OBS_CoreRoutingTable* getTable();
    virtual K_ShortestPathTable* getShortestPathTable();
    simtime_t calculateMinimumOffset(K_ShortestPathTableEntry* path);
};

#endif
