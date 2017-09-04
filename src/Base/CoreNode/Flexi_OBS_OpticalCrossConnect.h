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

#ifndef FLEXI_OPTICALCROSSCONNECT_H_
#define FLEXI_OPTICALCROSSCONNECT_H_

#include <omnetpp.h>
#include "OBS_Burst.h"
#include "Flexi_OBS_BurstRouterInfo_m.h"
#include "Flexi_OBS_BurstControlPacket_m.h"
#include "EndToEndAck_m.h"

using namespace std;
using namespace omnetpp;

class Flexi_OBS_OpticalCrossConnect : public cSimpleModule {
public:
    Flexi_OBS_OpticalCrossConnect();
    virtual ~Flexi_OBS_OpticalCrossConnect();

   // virtual void setOutLink(int destLabel, int link);
    virtual void setOutLink(int seq, int burstifierId, int link);
    virtual void setOutLink(int seq, int burstifierId, int link, simtime_t delay);
   // virtual void releaseOutLink(int destLabel);
    virtual void releaseOutLink(int seq, int burstfierId);
  protected:
    simsignal_t lostBurstId;
    int burstSent, bcpSent, controlSent;
    simtime_t switchingDelay, processingDelay;
    struct reservation{
            int link;
            int numseq;
            int burstifierId;
            int destLabel;
            bool ready;
            bool sendDelayed;
            simtime_t delay;
        };
    vector<reservation> reservations;
     virtual void initialize();
     virtual void handleMessage(cMessage *msg);
     void finish();
};

#endif /* FLEXI_OPTICALCROSSCONNECT_H_ */
