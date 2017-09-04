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

#ifndef SRC_BASE_EDGENODE_FLEXI_OBS_BURSTDISASSEMBLER_H_
#define SRC_BASE_EDGENODE_FLEXI_OBS_BURSTDISASSEMBLER_H_

#include <omnetpp.h>
#include "OBS_Burst.h"
#include "Flexi_OBS_Routing.h"
#include "EndToEndAck_m.h"
#include "Flexi_OBS_DisassemblerInfo_m.h"

using namespace std;
using namespace omnetpp;
class Flexi_OBS_BurstDisassembler: public omnetpp::cSimpleModule {
protected:
      bool endToEndAckEnabled, updateRoutingTable;

      /* Statistics */
      cOutVector bcpSources;
      int recvBursts, recvBcps, recvControls, burstLostByImpairments, burstLost, pendingAcksSize; //!< Counters.

      simsignal_t lostBurstId;
      simsignal_t successfulBurstId;
      vector<EndToEndAck*> pendingAcks;
      Flexi_OBS_EdgeRoutingTable* table;

      int ipAddr;
      cMessage* cleanPendingAckTimer;

      //! Initializer of data structures and statistics.
      virtual void initialize(int stage);
      virtual int numInitStages() const  {return 4;}
      //! Incoming message handler.
      virtual void handleMessage(cMessage *msg);
      //! Record scalars.
      virtual void finish();
      Flexi_OBS_Routing* getRouter();
      void addPendingAck(Flexi_OBS_BurstControlPacket* bcp, Flexi_OBS_DisassemblerInfo* info);
      void sendPendingAck(OBS_Burst* burst, bool isSuccessful);
      void doUpdateRoutingTable(cMessage* msg);
      virtual bool doOnBCPArrival(Flexi_OBS_BurstControlPacket* bcp, Flexi_OBS_DisassemblerInfo* info){return false;};
      virtual bool doOnBurstArrival(OBS_Burst* burst, Flexi_OBS_DisassemblerInfo* info){return false;};
      virtual void handleControlMessage(cMessage* msg, Flexi_OBS_DisassemblerInfo* info);
   public:
      //! Clean up recvBurst.
      virtual ~Flexi_OBS_BurstDisassembler();
};

#endif /* SRC_BASE_EDGENODE_FLEXI_OBS_BURSTDISASSEMBLER_H_ */
