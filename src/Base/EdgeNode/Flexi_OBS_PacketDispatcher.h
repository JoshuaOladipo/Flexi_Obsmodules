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

#ifndef __OBSMODULES_FLEXI_OBS_PACKETDISPATCHER_H_
#define __OBSMODULES_FLEXI_OBS_PACKETDISPATCHER_H_

#include <omnetpp.h>
#include <stdlib.h>
#include "QueueAssignment.h"
#include "inet/networklayer/contract/INetworkProtocolControlInfo.h"

using namespace std;
using namespace inet;
/**
 * TODO - Generated class
 */
class Flexi_OBS_PacketDispatcher : public cSimpleModule, public cListener
{
  protected:
    int numQueues;
    vector<QueueAssignment> monitorArray;
    simtime_t lastPacket_t;

    //Statistics
    cStdDev recvPackSize; //!< Received packets' length statistics.
    cStdDev interArrivalTimes;
    int droppedPacket; //!< Number of dropped packets.
    cOutVector recvPackSizeVec; //!< Length of the packets received (in bytes).

    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
    int searchMonitorArray(int dest, bool assign);
    void freeQueue(int dest);
};

#endif
