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

#include "Flexi_OBS_JIT_Mux.h"

Define_Module(Flexi_OBS_JIT_Mux);

void Flexi_OBS_JIT_Mux::initialize()
{
    Flexi_OBS_BurstMux::initialize();

    nackSentId = registerSignal("nackSentMuxAT");
    sendBackReservationResult = par("sendBackReservationResult");
    endToEndAckEnabled = par("endToEndAckEnabled");
    bcpTraversalAckEnabled = par("bcpTraversalAckEnabled");
    bcpTraversalAckMultiplier = par("bcpTraversalAckTimerMultiplier");

    WATCH_VECTOR(wavelengthInUseArray);
}

void Flexi_OBS_JIT_Mux::handleMessage(cMessage *msg)
{
    Flexi_OBS_BurstMux::handleMessage(msg);
}

void Flexi_OBS_JIT_Mux::initialiseWavelengthReservationTables()
{
    wavelengthInUseArray.resize(numOfWavelengths);
}

bool Flexi_OBS_JIT_Mux::doReservationAndSignalling(Flexi_OBS_BurstControlPacket* bcp)
{
    bool ret = true;
    if(!bcp->getHasSetupTransmitter())
        ret=assignWavelength(bcp);
    else{
        double center = bcp->getAssignedSpectrumCenter();
        double lower = bcp->getAssignedSpectrumLowerBound();
        double upper = bcp->getAssignedSpectrumUpperBound();

        int numberOfChannels = (upper-lower)/assignedSpectrumWidth;
        int startIndex = (lower-spectrumLowerBound)/assignedSpectrumWidth;

        for(int i = startIndex; i < startIndex + numberOfChannels; i++)
        {
            if(wavelengthInUseArray[i]){
                ret = false;
                break;
            }
        }

        if(ret)//reserve channel
        {
            int count = 0;
            while(count < numberOfChannels)
            {
                wavelengthInUseArray[startIndex] = true;
                startIndex++;
                count++;
            }
        }
    }

    if(!ret)
    {
        lostBcpSources.record(bcp->getSrcAddr());
        lostBcpDestination.record(bcp->getDestAddr());
        bcpLost++;
        controlMessageLost++;
        emit(lostBCPId,1);

        EV_INFO <<"FAILED RESERVATION ATTEMPT"<< bcp->getAssignedSpectrumCenter()<<endl;

        if(endToEndAckEnabled){
            EndToEndAck* failedMessage = new EndToEndAck("failedBcpAck");
            failedMessage->setIsControl(true);
            failedMessage->setSenderId(bcp->getSrcAddr());
            failedMessage->setSchedulingPriority(2);

            if(bcp->getRecordPath()){
                failedMessage->setEntryIdPos(bcp->getPathPos());
                failedMessage->setEntryIdsArraySize(bcp->getEntryIdsArraySize());
                for(int i =0; i < bcp->getEntryIdsArraySize(); i++){
                    failedMessage->setEntryIds(i, bcp->getEntryIds(i));
                }
            }else failedMessage->setEntry_Id(bcp->getEntryId());

            failedMessage->setNumSeq(bcp->getNumSeq());
            failedMessage->setBurstifierId(bcp->getBurstifierId());
            failedMessage->setRoutePos(bcp->getRoutePos()-3);
            failedMessage->setRoute(bcp->getRoute());
            failedMessage->setShortestPathCost(bcp->getShortestPathCost());
            failedMessage->setDistTravelled(bcp->getDistTravelled());
            send(failedMessage, "toNode$o");
            emit(nackSentId, false);
        }

        return ret;
    }

    opticalLogic(bcp, false);

    ret =  doJIT(bcp);

    if(ret){
        if(enableImpairments){
            TransmissionEntry* entry = new TransmissionEntry("transmissionEntry");

            double specCenter, specLower, specUpper, datarate;
            specCenter = controlChannelOut->par("assignedSpectrumCenter");
            specLower = controlChannelOut->par("assignedSpectrumLowerBound");
            specUpper = controlChannelOut->par("assignedSpectrumUpperBound");
            datarate = controlChannelOut->par("datarate");

            entry->setBitrate(datarate/1000000);
            entry->setPower(bcp->getSourcePower());
            entry->setSpectrumCenter(specCenter);
            entry->setSpectrumLowerBound(specLower);
            entry->setSpectrumUpperBound(specUpper);
            entry->setSender(position);
            entry->setStartTime(simTime());
            entry->setEndTime(simTime() +controlChannelOut->calculateDuration(bcp) + controlChannelOut->getDelay());
            bcp->setTransmissionEntry(entry);
            sendDirect(entry, table, "entryIn");
        }

        if(bcpTraversalAckEnabled)
            startAckTimer(bcp,controlChannelOut->calculateDuration(bcp)+ controlChannelOut->getDelay());

        if(reservationTimerEnabled)
            startReservationTimer(bcp, true);

        if(sendBackReservationResult)
        {
            TraversalAck* ack = new TraversalAck("traversalAck");
            ack->setIsControl(true);
            ack->setBurstifierId(bcp->getBurstifierId());
            ack->setSenderId(bcp->getSrcAddr());
            ack->setNumSeq(bcp->getNumSeq());

            ack->setDistanceDifference(bcp->getDistTravelled() - bcp->getShortestPathCost());
            ack->setLastEntryId(bcp->getRecordPath() ? bcp->getEntryIds(bcp->getPathPos()-1) : bcp->getEntryId());
            send(ack, "toNode$o");
        }

        if(!bcp->getHasSetupTransmitter()) bcp->setHasSetupTransmitter(true);

        send(bcp, controlChannelOutGate);
    }else{
        bcpLost++;
        controlMessageLost++;
        lostBcpSources.record(bcp->getSrcAddr());
        lostBcpDestination.record(bcp->getDestAddr());

        double center = bcp->getAssignedSpectrumCenter();
        double lower = bcp->getAssignedSpectrumLowerBound();
        double upper = bcp->getAssignedSpectrumUpperBound();

        int numberOfChannels = (upper-lower)/assignedSpectrumWidth;
        int startIndex = (lower-spectrumLowerBound)/assignedSpectrumWidth;

        int count = 0;
        while(count < numberOfChannels)
        {
            wavelengthInUseArray[startIndex] = false;
            startIndex++;
            count++;
        }

        EV_INFO <<"FAILED RESERVATION ATTEMPT"<< bcp->getAssignedSpectrumCenter()<<endl;

        if(endToEndAckEnabled){
            EndToEndAck* failedMessage = new EndToEndAck("failedBcpAck");
            failedMessage->setIsControl(true);
            failedMessage->setSenderId(bcp->getSrcAddr());
            failedMessage->setSchedulingPriority(2);

            if(bcp->getRecordPath()){
                failedMessage->setEntryIdPos(bcp->getPathPos());
                failedMessage->setEntryIdsArraySize(bcp->getEntryIdsArraySize());
                for(int i =0; i < bcp->getEntryIdsArraySize(); i++){
                    failedMessage->setEntryIds(i, bcp->getEntryIds(i));
                }
            }else failedMessage->setEntry_Id(bcp->getEntryId());

            failedMessage->setNumSeq(bcp->getNumSeq());
            failedMessage->setBurstifierId(bcp->getBurstifierId());
            failedMessage->setRoutePos(bcp->getRoutePos()-3);
            failedMessage->setRoute(bcp->getRoute());
            failedMessage->setShortestPathCost(bcp->getShortestPathCost());
            failedMessage->setDistTravelled(bcp->getDistTravelled());
            send(failedMessage, "toNode$o");
            emit(nackSentId, false);
        }

        emit(lostBCPId,1);
    }

    return ret;
}

bool Flexi_OBS_JIT_Mux::assignFlexiWavelengthFirstFit(Flexi_OBS_BurstControlPacket* bcp)
{
    int start = 0, end;
    bool startSet = false;
    for(int i = 0; i < numOfWavelengths; i++)
    {
        if(!wavelengthInUseArray[i])
        {
            if(!startSet){
                startSet = true;
                start = i;
                end = i+1;
            }else end = i+1;

            if(((end-start)*(assignedSpectrumWidth*pow(10,9)))/bcp->getDatarate() >= 1)
            {
                double chosenCenter = spectrumLowerBound + assignedSpectrumWidth/2 + start*assignedSpectrumWidth;;

                bcp->setAssignedSpectrumCenter(chosenCenter);
                bcp->setAssignedSpectrumLowerBound(spectrumLowerBound + (start*assignedSpectrumWidth));
                bcp->setAssignedSpectrumUpperBound(spectrumLowerBound + (end*assignedSpectrumWidth));

                transmissionCenters.record(bcp->getAssignedSpectrumCenter());
                for(int j =start; j <end; j++)
                    wavelengthInUseArray[j] = true;
                return true;
            }
        }else startSet = false;
    }

    return false;
}

bool Flexi_OBS_JIT_Mux::assignRandomWavelength(Flexi_OBS_BurstControlPacket* bcp)
{
    int largestPos = -1;
    double largestRand = -1;
    for(int i = 0; i < numOfWavelengths; i++)
    {
        if(!wavelengthInUseArray[i])
        {
            double rand = dblrand();
            if(rand > largestRand)
            {
                largestPos = i;
                largestRand = rand;
            }
        }
    }

    if(largestPos >= 0)
    {
        double chosenCenter = spectrumLowerBound + assignedSpectrumWidth/2 + largestPos*assignedSpectrumWidth;
        wavelengthInUseArray[largestPos] = true;

        bcp->setAssignedSpectrumCenter(chosenCenter);
        bcp->setAssignedSpectrumLowerBound(chosenCenter - (assignedSpectrumWidth/2));
        bcp->setAssignedSpectrumUpperBound(chosenCenter + (assignedSpectrumWidth/2));

        transmissionCenters.record(bcp->getAssignedSpectrumCenter());

        return true;
    }

    return false;
}

bool Flexi_OBS_JIT_Mux::assignFirstFitWavelength(Flexi_OBS_BurstControlPacket* bcp)
{
    for(int i = 0; i < numOfWavelengths; i++)
    {
        if(!wavelengthInUseArray[i])
        {
            double chosenCenter = spectrumLowerBound + assignedSpectrumWidth/2 + i*assignedSpectrumWidth;
            wavelengthInUseArray[i] = true;

            bcp->setAssignedSpectrumCenter(chosenCenter);
            bcp->setAssignedSpectrumLowerBound(chosenCenter - (assignedSpectrumWidth/2));
            bcp->setAssignedSpectrumUpperBound(chosenCenter + (assignedSpectrumWidth/2));

            transmissionCenters.record(bcp->getAssignedSpectrumCenter());
            return true;
        }
    }

    return false;
}

bool Flexi_OBS_JIT_Mux::assignFlexiWavelengthRandom(Flexi_OBS_BurstControlPacket* bcp)
{
    int start = intrand(numOfWavelengths),counter = start;

    while(wavelengthInUseArray[counter])
    {
        counter = (counter+1)%numOfWavelengths;

        if(counter == start)
            return false;
    }

    start = counter;
    int end = start+1;

    while(((end-start)*(assignedSpectrumWidth*pow(10,9)))/bcp->getDatarate() < 1)
        end++;

    if(end > numOfWavelengths)
        return false;

    double chosenCenter = spectrumLowerBound + assignedSpectrumWidth/2 + start*assignedSpectrumWidth;

    bcp->setAssignedSpectrumCenter(chosenCenter);
    bcp->setAssignedSpectrumUpperBound(spectrumLowerBound + (end*assignedSpectrumWidth));
    bcp->setAssignedSpectrumLowerBound(spectrumLowerBound + (start*assignedSpectrumWidth));
    transmissionCenters.record(bcp->getAssignedSpectrumCenter());

    return true;
}

bool Flexi_OBS_JIT_Mux::assignWavelength(Flexi_OBS_BurstControlPacket* bcp)
{
    switch(wavelengthAssignmentType)
    {
    case 0:
    {
        double center = bcp->getAssignedSpectrumCenter();
        double lower = bcp->getAssignedSpectrumLowerBound();
        double upper = bcp->getAssignedSpectrumUpperBound();
        int numberOfChannels = (upper-lower)/assignedSpectrumWidth;
        int startIndex = (lower-spectrumLowerBound)/assignedSpectrumWidth;

        int count = 0;
        while(count < numberOfChannels)
        {
            wavelengthInUseArray[startIndex] = true;
            startIndex++;
            count++;
        }
        transmissionCenters.record(bcp->getAssignedSpectrumCenter());
        return true;
    }
    case 1: return assignFirstFitWavelength(bcp);
    case 2: return assignRandomWavelength(bcp);
    case 3: return assignFlexiWavelengthFirstFit(bcp);
    case 4: return assignFlexiWavelengthRandom(bcp);

    }

    return false;
}

void Flexi_OBS_JIT_Mux::startAckTimer(Flexi_OBS_BurstControlPacket *bcp, simtime_t transmissionDuration)
{
    AckTimer* timer = new AckTimer("ackTimer");

    //set variables
    timer->setCreationTime(simTime());
    timer->setBurstifierId(bcp->getBurstifierId());
    timer->setNumSeq(bcp->getNumSeq());
    timer->setSenderId(bcp->getSrcAddr());
    timer->setRoute(bcp->getRoute());
    timer->setRoutePos(bcp->getRoutePos());

    if(bcp->getRecordPath()){
        timer->setEntryIdsArraySize(bcp->getEntryIdsArraySize());
        for(int i =0; i < bcp->getEntryIdsArraySize(); i++){
            timer->setEntryIds(i, bcp->getEntryIds(i));
        }
    }else
        timer->setEntryId(bcp->getEntryId());

    //send self message for ack wait time
    scheduleAt(simTime() + (bcpTraversalAckMultiplier*(transmissionDuration+guardTime)), timer);

    //add timer to ackTimers
    ackTimers.push_back(timer);
}

void Flexi_OBS_JIT_Mux::sendAck(Flexi_OBS_BurstControlPacket* bcp)
{
    if(bcpTraversalAckEnabled){
        TraversalAck* ack = new TraversalAck("traversalAck");
        ack->setIsControl(true);
        ack->setSchedulingPriority(4);//scheduling priority can be set between 1 and 5
        ack->setBurstifierId(bcp->getBurstifierId());
        ack->setSenderId(bcp->getSrcAddr());
        ack->setNumSeq(bcp->getNumSeq());

        ack->setDistanceDifference(bcp->getDistTravelled() - bcp->getShortestPathCost());
        ack->setLastEntryId(bcp->getRecordPath() ? bcp->getEntryIds(bcp->getEntryIdsArraySize()-1) : bcp->getEntryId());
        insertCtlMsgIntoQueue(ack);
    }
}

void Flexi_OBS_JIT_Mux::cancelAckTimer(int burstifierId, int numSeq, int senderId)
{
    //search acktTimers and delete AckTimer if found
    for(int i = 0; i < ackTimers.size(); i++)
    {
        if(ackTimers[i]->getBurstifierId() == burstifierId && ackTimers[i]->getNumSeq() == numSeq && ackTimers[i]->getSenderId() == senderId)
        {
            cMessage *ev = cancelEvent(ackTimers[i]);
            ackTimers.erase(ackTimers.begin()+i);
            delete(ev);
            return;
        }
    }
}

bool Flexi_OBS_JIT_Mux::doJIT(Flexi_OBS_BurstControlPacket* bcp)
{
    int index = -1;

    if(!bcp->getHasSetupTransmitter())
        index = createLightPath(bcp->getAssignedSpectrumCenter(), bcp->getAssignedSpectrumLowerBound(),bcp->getAssignedSpectrumUpperBound(), bcp->getDatarate(), true);
    else
        index = createLightPath(bcp->getAssignedSpectrumCenter(), bcp->getAssignedSpectrumLowerBound(),bcp->getAssignedSpectrumUpperBound(), bcp->getDatarate(), false);

    if(index == -1) return false;

    reservation reserve = reservation(index, bcp->getNumSeq(), bcp->getBurstifierId(), bcp->getBurstSize(), bcp->getBurstOffset(), true);
    bcp->setReservedChannelIndex(index);

    reservations.push_back(reserve);

    return true;
}

double Flexi_OBS_JIT_Mux::determinePercentageFreeWavelengths()
{
    double bandwidthNotInUse = totalBandwidth;

    for(int i = 0; i < wavelengthInUseArray.size(); i++){
        if(!wavelengthInUseArray[i])
            bandwidthNotInUse -= (spectrumLowerBound+(assignedSpectrumWidth*(i+1))) - (spectrumLowerBound + assignedSpectrumWidth*i);
    }

    return bandwidthNotInUse/totalBandwidth;
}

void  Flexi_OBS_JIT_Mux::handleAckTimer(cMessage* msg)
{
    //process ack timer by freeing reservation and sending EndToEndAck message
    AckTimer* timer = check_and_cast<AckTimer*>(msg);
    int channelIndex = -1;
    for(int i = 0; i < reservations.size(); i++)
    {
        if(reservations[i].burstifierId == timer->getBurstifierId() && reservations[i].numseq == timer->getNumSeq())
        {
            channelIndex = reservations[i].index;
            tearDownLightPath(reservations[i].index);
            reservations.erase(reservations.begin()+i);
            break;
        }
    }

    if(endToEndAckEnabled){
        EndToEndAck* failedMessage = new EndToEndAck("failedBcpAck");
        failedMessage->setIsControl(true);
        failedMessage->setSenderId(timer->getSenderId());
        failedMessage->setSchedulingPriority(2);

        if(timer->getEntryIdsArraySize() > 1){
            failedMessage->setEntryIdsArraySize(timer->getEntryIdsArraySize());
            failedMessage->setEntryIdPos(timer->getEntryIdsArraySize()-1);
            for(int i =0; i < timer->getEntryIdsArraySize(); i++){
                failedMessage->setEntryIds(i, timer->getEntryIds(i));
            }
        }else failedMessage->setEntry_Id(timer->getEntryId());

        failedMessage->setNumSeq(timer->getNumSeq());
        failedMessage->setBurstifierId(timer->getBurstifierId());
        failedMessage->setRoutePos(timer->getRoutePos()-3);
        failedMessage->setRoute(timer->getRoute());
        failedMessage->setShortestPathCost(timer->getShortestPathCost());
        failedMessage->setDistTravelled(timer->getDistTravelled());
        send(failedMessage, "toNode$o");
        emit(nackSentId, false);
    }

    //cancel reservation timer
    if(reservationTimerEnabled && channelIndex >= 0)
        cancelAndDeleteReservationTimer(channelIndex, timer->getBurstifierId(), timer->getNumSeq(), timer->getSenderId());

    cancelAckTimer(timer->getBurstifierId(), timer->getNumSeq(), timer->getSenderId());
}

bool Flexi_OBS_JIT_Mux::doReservationReceiverSide(Flexi_OBS_BurstControlPacket* bcp)
{
    //reserve channel in wavelengthinusearray if not taken
    double center = bcp->getAssignedSpectrumCenter();
    double lower = bcp->getAssignedSpectrumLowerBound();
    double upper = bcp->getAssignedSpectrumUpperBound();
    int numberOfChannels = (upper-lower)/assignedSpectrumWidth;
    int startIndex = (lower-spectrumLowerBound)/assignedSpectrumWidth;
    bool allFree =  true;

    for(int i = startIndex; i < startIndex + numberOfChannels; i++)
    {
        if(wavelengthInUseArray[i]){
            allFree = false;
            break;
        }
    }

    if(allFree)//reserve channel
    {
        int count = 0;
        while(count < numberOfChannels)
        {
            wavelengthInUseArray[startIndex] = true;
            startIndex++;
            count++;
        }

        int index = bcp->getReservedChannelIndex();
        int baseIdIn = gateBaseId("muxInOut$i");
        int baseIdOut = gateBaseId("muxInOut$o");

        cGate *gateIn = gate(baseIdIn+index)->getPreviousGate();
        cGate *gateOut = gate(baseIdOut+index);

        cChannel *inChannel = gateIn->getChannel();
        cChannel *outChannel = gateOut->getChannel();

        inChannel->par(inUsePos).setBoolValue(true);
        outChannel->par(inUsePos).setBoolValue(true);

        reservation reserve = reservation(index, bcp->getNumSeq(), bcp->getBurstifierId(), bcp->getBurstSize(), bcp->getBurstOffset(), false);
        reservations.push_back(reserve);

        startReservationTimer(bcp, false);
    }

    return allFree;
}

void Flexi_OBS_JIT_Mux::cancelReservation(ReservationTimer* timer)
{
    for(int i = 0; i < reservations.size(); i++)
    {
        if(reservations[i].burstifierId == timer->getBurstifierId() && reservations[i].numseq == timer->getNumseq()){
            tearDownLightPath(reservations[i].index);

            double lower = timer->getSpectrumLowerBound();
            double upper = timer->getSpectrumUpperBound();


            int numberOfChannels = (upper-lower)/assignedSpectrumWidth;
            int startIndex = (lower-spectrumLowerBound)/assignedSpectrumWidth;

            int count = 0;
            while(count < numberOfChannels)
            {
                wavelengthInUseArray[startIndex] = false;
                startIndex++;
                count++;
            }


            reservations.erase(reservations.begin()+i);
            break;
        }
    }
}

void Flexi_OBS_JIT_Mux::cancelOtherTimers(ReservationTimer* timer)
{
    //cancel ack timer, if acktimer not received by the time burst should have been sent, transmisison can be considered failed
    if(bcpTraversalAckEnabled)
        cancelAckTimer(timer->getBurstifierId(), timer->getNumseq(), timer->getSenderId());
}

void Flexi_OBS_JIT_Mux::doSelfMessageProcessing(cMessage *msg)
{
    if(strcmp(msg->getName(), "ackTimer") == 0){
        handleAckTimer(msg);
    }
}

bool Flexi_OBS_JIT_Mux::doProcessingIfMessageReadable(cMessage *msg)
{
    if(strcmp(msg->getName(), "BCP")==0 || strcmp(msg->getName(), "ANT")==0){
        Flexi_OBS_BurstControlPacket* bcp = dynamic_cast<Flexi_OBS_BurstControlPacket *>(msg);
        bcp->setDistTravelled(bcp->getDistTravelled() + fibreLength);
        sendAck(bcp);
        return false;
    }

    if(strcmp(msg->getName(), "traversalAck")==0){
        TraversalAck* ack = dynamic_cast<TraversalAck*>(msg);
        cancelAckTimer(ack->getBurstifierId(), ack->getNumSeq(), ack->getSenderId());
        delete(msg);
        return true;
    }

    return false;
}

void Flexi_OBS_JIT_Mux::doProcessingBeforeSendingCtlMsg(cMessage *msg)
{
    if(strcmp(msg->getName(), "ANT")==0){
        Flexi_OBS_BurstControlPacket* bcp = dynamic_cast<Flexi_OBS_BurstControlPacket *>(msg);
        bcp->setPercentFreeWavelengths(determinePercentageFreeWavelengths());
    }
}
