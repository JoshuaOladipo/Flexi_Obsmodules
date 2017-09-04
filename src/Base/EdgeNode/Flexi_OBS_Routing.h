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

#ifndef __OBSMODULES_FLEXI_OBS_ROUTING_H_
#define __OBSMODULES_FLEXI_OBS_ROUTING_H_

#include <omnetpp.h>
#include <cmath>

#include "inet/networklayer/common/InterfaceEntry.h"
#include "inet/networklayer/common/InterfaceToken.h"
#include "inet/networklayer/contract/IInterfaceTable.h"

#include "OBS_Burst.h"
#include "Flexi_OBS_BurstControlPacket_m.h"
#include "K_ShortestPathTable.h"
#include "OBS_BurstifierInfo_m.h"
#include "K_ShortestPathTableEntry_m.h"
#include "Flexi_OBS_EdgeRoutingTable.h"
#include "Flexi_OBS_BurstRouterInfo_m.h"
#include "NodeRoutingTableEntry_m.h"
#include "EndToEndAck_m.h"
#include "Flexi_OBS_DisassemblerInfo_m.h"

using namespace inet;
using namespace std;
/**
 * TODO - Generated class
 */
class Flexi_OBS_Routing : public cSimpleModule
{
public:
    //gets the local gate which leads to the external gate(input to the function) this message should go through. written to work irrespective of whether gate given is an input or output gate
    int getLocalOutGate(int externalGate);
protected:
    cStdDev recvBurstSize; //!< Received burst' length statistics.
    cStdDev interArrivalTimes;
    vector<double> datarates;
    vector<double> probabilities;

    simtime_t lastBurst_t;
    simsignal_t sentBurstId;
    int gridType, numOfWavelengths, droppedBurst, sentBurst, controlSent, ipAddr;
    cOutVector destVector, burstInterarrivalTimes, dataratesVector;
    double spectrumLowerBound, spectrumUpperBound, assignedSpectrumWidth;
    bool deferRouting, inSuperNode;
    simtime_t coreNodeProcessingTime;
    simtime_t switchingDelay;
    virtual void initialize(int stage);
    virtual int numInitStages() const  {return 4;}
    virtual void handleMessage(cMessage *msg);
    virtual InterfaceEntry* registerInterface ();
    //Flexi_OBS_BurstControlPacket* generateBCP(OBS_Burst *burst);
    Flexi_OBS_EdgeRoutingTable* getTable();
    virtual K_ShortestPathTable* getShortestPathTable();
    simtime_t calculateMinimumOffset(K_ShortestPathTableEntry* path);
    virtual double getDatarate();
    void finish();
};

#endif
