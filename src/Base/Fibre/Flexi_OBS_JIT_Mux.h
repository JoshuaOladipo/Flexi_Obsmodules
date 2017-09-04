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

#ifndef __OBSMODULES_FLEXI_OBS_JIT_MUX_H_
#define __OBSMODULES_FLEXI_OBS_JIT_MUX_H_

#include <omnetpp.h>
#include "AckTimer_m.h"
#include "TraversalAck_m.h"
#include "EndToEndAck_m.h"
#include "Flexi_OBS_BurstMux.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Flexi_OBS_JIT_Mux : public Flexi_OBS_BurstMux
{
protected:
    simsignal_t nackSentId;

    vector<bool> wavelengthInUseArray;
    vector<AckTimer*> ackTimers;
    double bcpTraversalAckMultiplier;
    bool bcpTraversalAckEnabled, sendBackReservationResult, endToEndAckEnabled;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    bool doReservationAndSignalling(Flexi_OBS_BurstControlPacket* bcp);
    virtual bool assignWavelength(Flexi_OBS_BurstControlPacket* bcp) override;
    bool assignRandomWavelength(Flexi_OBS_BurstControlPacket* bcp);
    bool assignFirstFitWavelength(Flexi_OBS_BurstControlPacket* bcp);
    bool assignFlexiWavelengthFirstFit(Flexi_OBS_BurstControlPacket* bcp);
    bool assignFlexiWavelengthRandom(Flexi_OBS_BurstControlPacket* bcp);

    void startAckTimer(Flexi_OBS_BurstControlPacket *bcp, simtime_t transmissionDuration);
    void cancelAckTimer(int burstifierId, int numSeq, int senderId);
    void sendAck(Flexi_OBS_BurstControlPacket* bcp);
    double determinePercentageFreeWavelengths() override;
    void handleAckTimer(cMessage* msg);

    virtual void initialiseWavelengthReservationTables() override;
    virtual void doSelfMessageProcessing(cMessage *msg) override;//return true if handleMessage should return, false otherwise
    virtual bool doProcessingIfMessageReadable(cMessage *msg) override;
    virtual void doProcessingBeforeSendingCtlMsg(cMessage *msg) override;
    virtual bool doReservationReceiverSide(Flexi_OBS_BurstControlPacket* bcp) override;
    virtual void cancelOtherTimers(ReservationTimer* timer)override;
    void cancelReservation(ReservationTimer* timer) override;

    virtual bool doJIT(Flexi_OBS_BurstControlPacket* bcp);
};

#endif
