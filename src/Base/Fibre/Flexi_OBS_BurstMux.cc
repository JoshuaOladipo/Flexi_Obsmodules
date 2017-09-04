#include "Flexi_OBS_BurstMux.h"

Define_Module(Flexi_OBS_BurstMux);

Flexi_OBS_BurstMux::~Flexi_OBS_BurstMux(){
}

void Flexi_OBS_BurstMux::initialize(){
    lostBurstId = registerSignal("lostBurst");
    lostBCPId = registerSignal("lostBCP");

    //Pick up parameters from ned file
    gridType = par("gridType");
    spectrumLowerBound = par("spectrumLowerBound");
    spectrumUpperBound = par("spectrumUpperBound");
    transmitterPower = par("transmitterPower");
    recieverSensitivity = par("recieverSensitivity");
    k = par("k");
    attenuationConst = par("attenuationConst");
    fibreLength = par("length");
    reservationTimerEnabled = par("reservationTimerEnabled");
    maxControlQueueLength = par("maxControlQueueLength");
    useExplicitRelease = par("useExplicitRelease");
    hasOwnControlChannel = par("hasOwnControlChannel");
    wavelengthAssignmentType = par("wavelengthAssignmentType");
    enableImpairments = par("enableImpairments");
    enablePriorityQueuing = par("enablePriorityQueuing");

    infiniteControlQueueLength = maxControlQueueLength <=0;
    c = 0;
    totalBandwidth = spectrumUpperBound - spectrumLowerBound;
    ASSERT(totalBandwidth>0);
    controlChannelQueue.setName("waiting Control Messages");

    if(enablePriorityQueuing)
        controlChannelQueue.setup(controlComparator);

    propagationDelay = fibreLength * propagationDelayPerKm;
    guardTime = propagationDelay/2;

    burstLoss = 0;
    burstCounter = 0;
    controlMessageLost = 0;
    burstDroppedAtSource = 0;
    bcpLost = 0;
    controlMessageDroppedByQueue = 0;
    burstLost = 0;
    controlMessageLostByImpairments = 0;
    burstLostByFailedReservation = 0;
    recvedBcpsFromNode = 0;
    burstRecvFromNode = 0;
    controlMessageFromNode = 0;
    lostBcpSources.setName("lost BCP Senders");
    lostBcpDestination.setName("lost BCP Destination");
    offsetTimes.setName("offsetTimes");
    transmissionCenters.setName("transmission wavelength");
    WATCH(bcpLost);
    WATCH(burstLost);
    WATCH(controlMessageLost);
    WATCH(controlMessageDroppedByQueue);
    WATCH(controlMessageLostByImpairments);
    WATCH(burstLostByFailedReservation);
    WATCH(recvedBcpsFromNode);
    WATCH(controlMessageFromNode);
    WATCH(burstDroppedAtSource);
    WATCH(burstLoss);
    WATCH(burstCounter);
    WATCH_PTRMAP(reservationTimers);
    //WATCH_VECTOR(reservations);
    WATCH_OBJ(controlChannelQueue);

    strcmp(this->getName(), "leftMux")==0 ? position = Mux::Left : position = Mux::Right;
    inUsePos = position == Mux::Left ? "inUseLeft" : "inUseRight";
    processControlQueue = new cMessage("controlQueue");
    controlChannelOutGate = gate("muxInOut$o", getControlGateIndex());
    controlChannelOut =  check_and_cast<cDatarateChannel*>(controlChannelOutGate->findTransmissionChannel());
    controlChannelIn = check_and_cast<cDatarateChannel*>(gate("muxInOut$i", getControlGateIndex())->findIncomingTransmissionChannel());
    controlChannelOut->setDelay(propagationDelay.dbl());
    controlChannelIn->setDelay(propagationDelay.dbl());
    table = check_and_cast<FibreTable*>(getParentModule()->getSubmodule("fibreTable"));

    switch(gridType)
    {
    case 0: assignedSpectrumWidth = 12.5;
    break;
    case 1: assignedSpectrumWidth = 50;
    break;
    case 2: assignedSpectrumWidth = 100;
    break;
    }

    numOfWavelengths = (spectrumUpperBound - spectrumLowerBound)/assignedSpectrumWidth;
    initialiseWavelengthReservationTables();
}

/*initially sets transmission power, and applies impairments afterwards. can implement amplifer logic and other transmission optical component logic here
 * should be called on a message before sending it over the fiber and after recieving a message from the fibre.
 */
void Flexi_OBS_BurstMux::opticalLogic(TransmittedMessage_Base* msg, bool justPassedThroughFiber)
{
    if(!msg->getHasPassedFirstStation())
    {
        msg->setSourcePower(transmitterPower);
        msg->setHasPassedFirstStation(true);
    }

    if(justPassedThroughFiber && enableImpairments){
        //calculate impairments
        FibreTable* table = check_and_cast<FibreTable*>(getParentModule()->getSubmodule("fibreTable"));

        double attenuation = fibreLength * attenuationConst;

        if(table)
        {
            TransmissionEntry* entry = msg->getTransmissionEntry();
            set<TransmissionEntry*>* entriesFromSource = table->getEntriesBetweenTimes(position == Mux::Right ? Mux::Left : Mux::Right,
                    msg->getSendingTime(), msg->getArrivalTime());
            set<TransmissionEntry*>* entriesFromDestination = table->getEntriesBetweenTimes(position, msg->getSendingTime(), msg->getArrivalTime());

            entriesFromSource->erase(entry);

            double C = 0;
            if(entriesFromDestination->size() != 0)
            {
                double intermediate = 0;
                for(set<TransmissionEntry*>::iterator it = entriesFromDestination->begin(); it!=entriesFromDestination->end(); it++)
                {
                    intermediate += (entry->getBitrate()/(*it)->getBitrate()) *(pow(10, (*it)->getPower()/10)/ pow(10, entry->getPower()/10))
                                                                                                                                                                                                                                                                                                                                                     * (1/((*it)->getSpectrumCenter()-entry->getSpectrumCenter()));
                }
                C = C + (k*intermediate*fibreLength);
            }

            if(entriesFromSource->size() != 0)
            {
                double intermediate = 0;
                for(set<TransmissionEntry*>::iterator it = entriesFromSource->begin(); it!=entriesFromSource->end(); it++)
                {
                    if(!((entry->getStartTime() > (*it)->getStartTime() && entry->getEndTime() > (*it)->getEndTime()) ||
                            ((*it)->getStartTime() > entry->getStartTime() && (*it)->getEndTime() > entry->getEndTime()))){
                        intermediate += (entry->getBitrate()/(*it)->getBitrate())*(pow(10, (*it)->getPower()/10)/ pow(10, entry->getPower()/10))
                                                                                                                                                                                                                                                                                                                                                       * (1/((*it)->getSpectrumCenter()-entry->getSpectrumCenter()));
                    }
                }
                C = C + (k*intermediate*fibreLength);
            }

            msg->setSourcePower(msg->getSourcePower()-attenuation-C);

            entry->setReadyForDeletion(true);
        }
    }
}

//compares message power to transmitter sensitivity
bool Flexi_OBS_BurstMux::isMessageReadable(TransmittedMessage_Base* msg)
{
    if(msg->getSourcePower() >= recieverSensitivity && !msg->hasBitError()){
        msg->setIsReadable(true);
        return true;
    }

    msg->setIsReadable(false);
    return false;
}

void Flexi_OBS_BurstMux::handleMessage(cMessage *msg){
    if(msg->isSelfMessage())
    {
        //process control queue
        if(strcmp(msg->getName(), "controlQueue") == 0 && !controlChannelQueue.isEmpty())
        {
            sendCtlMsg();
        }else if(strcmp(msg->getName(), "resTimer") == 0){
            handleReservationTimer(msg);
        }else doSelfMessageProcessing(msg);
    }else{
        cGate *inGate = msg->getArrivalGate();

        //if message was transmitted over fiber
        if(strcmp(inGate->getBaseName(), "muxInOut") == 0)
        {
            int index = inGate->getIndex();

            //if burst channel, check if channel was properly reserved. if not delete msg. channel is torn down by reservation timer or release message
            if((hasOwnControlChannel && index > 1) || (!hasOwnControlChannel && index > 0)){
                burstCounter++;

                cChannel *inChannel = inGate->getPreviousGate()->getChannel();

                if(inChannel)
                {
                    if(position == Mux::Left){
                        if(!inChannel->par("leftReservationSuccessful")){

                            burstLostByFailedReservation++;
                            burstLost++;
                            burstLoss = (double)burstLost/burstCounter;

                            EV_INFO << "BURST LOSS = " << burstLoss;
                            delete(msg);
                            emit(lostBurstId, 2);
                            return;
                        }
                    }else{
                        if(!inChannel->par("rightReservationSuccessful")){
                            burstLostByFailedReservation++;
                            burstLost++;
                            burstLoss = (double)burstLost/burstCounter;

                            EV_INFO << "BURST LOSS = " << burstLoss;
                            delete(msg);
                            emit(lostBurstId, 2);
                            return;
                        }
                    }
                }
            }

            opticalLogic(dynamic_cast<TransmittedMessage_Base*>(msg), true);

            if(isMessageReadable(dynamic_cast<TransmittedMessage_Base*>(msg))){

                if(!((hasOwnControlChannel && index > 1) || (!hasOwnControlChannel && index > 0))){
                    TransmittedMessage_Base* msg1 = check_and_cast<TransmittedMessage_Base*>(msg);
                    msg1->setHasPassedFirstStation(false);//control messages are always read and retransmitted
                }

                if(doProcessingIfMessageReadable(msg)) return;

                if(strcmp(msg->getName(), "BCP")==0){
                    Flexi_OBS_BurstControlPacket* bcp = dynamic_cast<Flexi_OBS_BurstControlPacket *>(msg);

                    int index = bcp->getReservedChannelIndex();
                    int size = gateSize("muxInOut$i");

                    if(index >= size || index < 0){
                        EV_ERROR << "Tried to reserve non-existent channel index = " << index<< endl;
                        return;
                    }

                    if(!doReservationReceiverSide(bcp))
                    {//reservation unsuccessful
                        int baseIdOut = gateBaseId("muxInOut$o");
                        cGate *gateOut = gate(baseIdOut+index);
                        int baseIdIn = gateBaseId("muxInOut$i");
                        cGate *gateIn = gate(baseIdIn+index);
                        cChannel *inChannel = gateIn->getPreviousGate()->getChannel();
                        cChannel *outChannel = gateOut->getChannel();

                        if(inChannel && outChannel)
                        {
                            if(position == Mux::Left){
                                inChannel->par("leftReservationSuccessful").setBoolValue(false);
                                outChannel->par("leftReservationSuccessful").setBoolValue(false);
                            }else{
                                inChannel->par("rightReservationSuccessful").setBoolValue(false);
                                outChannel->par("rightReservationSuccessful").setBoolValue(false);
                            }
                        }
                        lostBcpSources.record(bcp->getSrcAddr());
                        lostBcpDestination.record(bcp->getDestAddr());
                        bcpLost++;

                        emit(lostBCPId, 1);
                        delete(msg);
                        return;
                    }
                }

                send(msg, "toNode$o");
            }else{//if message unreadable

                if(!((hasOwnControlChannel && index > 1) || (!hasOwnControlChannel && index > 0))){
                    controlMessageLost++;
                    controlMessageLostByImpairments++;

                    //if bcp not readable reservation is not made
                    if(strcmp(msg->getName(), "BCP")==0){
                        Flexi_OBS_BurstControlPacket* bcp = dynamic_cast<Flexi_OBS_BurstControlPacket *>(msg);

                        int index = bcp->getReservedChannelIndex();
                        int baseIdOut = gateBaseId("muxInOut$o");
                        int size = gateSize("muxInOut$i");

                        if(index >= size || index < 0){
                            EV_ERROR << "Tried to reserve non-existent channel index = " << index<< endl;
                            return;
                        }

                        cGate *gateOut = gate(baseIdOut+index);
                        int baseIdIn = gateBaseId("muxInOut$i");
                        cGate *gateIn = gate(baseIdIn+index);

                        cChannel *inChannel = gateIn->getPreviousGate()->getChannel();
                        cChannel *outChannel = gateOut->getChannel();

                        if(inChannel && outChannel)
                        {
                            if(position == Mux::Left){
                                inChannel->par("leftReservationSuccessful").setBoolValue(false);
                                outChannel->par("leftReservationSuccessful").setBoolValue(false);
                            }else{
                                inChannel->par("rightReservationSuccessful").setBoolValue(false);
                                outChannel->par("rightReservationSuccessful").setBoolValue(false);
                            }
                        }

                        lostBcpSources.record(bcp->getSrcAddr());
                        lostBcpDestination.record(bcp->getDestAddr());
                        bcpLost++;

                        emit(lostBCPId, 3);
                    }

                    delete(msg);
                }
                else{
                    send(msg, "toNode$o");//if message is not control, then even though message is unreadable, need to still send it along the path so its impairment effect can be taken into account
                }
            }

            return;
        }

        //if message comes from another component
        OBS_Burst *burst = dynamic_cast<OBS_Burst *> (msg);
        TransmittedMessage_Base* msg1 = check_and_cast<TransmittedMessage_Base*>(msg);

        if(burst != NULL){
            burstCounter++;
            burstRecvFromNode++;
            sendBurst(burst);
        }else if(msg1->getIsControl())
        {
            controlMessageFromNode++;

            if(strcmp(msg->getName(), "BCP")==0) recvedBcpsFromNode++;

            doProcessingBeforeSendingCtlMsg(msg);

            insertCtlMsgIntoQueue(msg);
            return;
        }
    }
}

void Flexi_OBS_BurstMux::finish(){
    cancelAndDelete(processControlQueue);

    recordScalar("burst lost",burstLost);
    recordScalar("control message Lost", controlMessageLost);
    recordScalar("bcp Lost", bcpLost);
    recordScalar("control message dropped by queue",controlMessageDroppedByQueue);
    recordScalar("control message lost by impairments", controlMessageLostByImpairments);
    recordScalar("burst lost due to failed reservation", burstLostByFailedReservation);
    recordScalar("bcps recved from node", recvedBcpsFromNode);
    recordScalar("burst recved from node", burstRecvFromNode );
    recordScalar("control messages recved from node", controlMessageFromNode);
    recordScalar("simulation run time", simTime().dbl());
    recordScalar("Burst Dropped at source", burstDroppedAtSource);
    recordScalar("BCPs pending to be sent (because the control channel is busy)", controlChannelQueue.getLength());
    recordScalar("BurstLossProbabilityForMux", burstLoss);
}

int Flexi_OBS_BurstMux::createLightPath(double spectrumCenter, double spectrumLowerBound, double spectrumUpperBound, double datarate, bool createTransmitter)
{
    if(spectrumLowerBound < this->spectrumLowerBound || spectrumUpperBound > this->spectrumUpperBound)
        return -1;

    if(spectrumCenter <= spectrumLowerBound || spectrumCenter >= spectrumUpperBound)
        return -1;

    if(spectrumLowerBound >= spectrumUpperBound)
        return -1;

    int baseIdIn = gateBaseId("muxInOut$i");
    int baseIdOut = gateBaseId("muxInOut$o");
    int size = gateSize("muxInOut$i");
    int freeChannel;
    bool inUse, freeChannelSet = false, isDatarateChannel;

    int start = hasOwnControlChannel ? 2 : 1;
    //loop looks for free channels that can be reassigned
    for(int i = start; i < size; i++){
        cGate *gateIn = gate(baseIdIn+i)->getPreviousGate();
        cGate *gateOut = gate(baseIdOut+i);

        cChannel *inChannel = gateIn->getChannel();
        cChannel *outChannel = gateOut->getChannel();

        if(inChannel && outChannel)
        {
            inUse = inChannel->par("inUseLeft") || inChannel->par("inUseRight");
            isDatarateChannel = inChannel->par("isDatarateChannel");

            if(!inUse)
            {
                if(!freeChannelSet && ((isDatarateChannel && createTransmitter) || (!isDatarateChannel && !createTransmitter))){
                    freeChannel = i;
                    freeChannelSet = true;
                    break;
                }
                else {
                    inChannel->par("assignedSpectrumCenter").setDoubleValue(-1);
                    inChannel->par("assignedSpectrumLowerBound").setDoubleValue(-1);
                    inChannel->par("assignedSpectrumUpperBound").setDoubleValue(-1);

                    inChannel->par("leftReservationSuccessful").setBoolValue(true);
                    inChannel->par("rightReservationSuccessful").setBoolValue(true);
                    outChannel->par("leftReservationSuccessful").setBoolValue(true);
                    outChannel->par("rightReservationSuccessful").setBoolValue(true);

                    outChannel->par("assignedSpectrumCenter").setDoubleValue(-1);
                    outChannel->par("assignedSpectrumLowerBound").setDoubleValue(-1);
                    outChannel->par("assignedSpectrumUpperBound").setDoubleValue(-1);
                }
            }
        }
    }

    if(freeChannelSet)//reassign channel
    {
        cGate *gateIn = gate(baseIdIn+freeChannel)->getPreviousGate();
        cGate *gateOut = gate(baseIdOut+freeChannel);

        cChannel *inChannel = gateIn->getChannel();
        cChannel *outChannel = gateOut->getChannel();


        inChannel->par(inUsePos).setBoolValue(true);
        inChannel->par("assignedSpectrumCenter").setDoubleValue(spectrumCenter);
        inChannel->par("assignedSpectrumLowerBound").setDoubleValue(spectrumLowerBound);
        inChannel->par("assignedSpectrumUpperBound").setDoubleValue(spectrumUpperBound);
        inChannel->par("datarate").setDoubleValue(datarate);
        inChannel->par("leftReservationSuccessful").setBoolValue(true);
        inChannel->par("rightReservationSuccessful").setBoolValue(true);
        outChannel->par("leftReservationSuccessful").setBoolValue(true);
        outChannel->par("rightReservationSuccessful").setBoolValue(true);
        outChannel->par("assignedSpectrumCenter").setDoubleValue(spectrumCenter);
        outChannel->par("assignedSpectrumLowerBound").setDoubleValue(spectrumLowerBound);
        outChannel->par("assignedSpectrumUpperBound").setDoubleValue(spectrumUpperBound);
        outChannel->par(inUsePos).setBoolValue(true);
        outChannel->par("datarate").setDoubleValue(datarate);

        double d = inChannel->par("assignedSpectrumCenter");
        EV_INFO<<"CHANNEL reserved CENTER: " << d << endl;

        return freeChannel;
    }

    //create new channel
    setGateSize("muxInOut", size+1);

    cGate *gateIn = gate(baseIdIn+size);
    cGate *gateOut = gate(baseIdOut+size);
    cGate *controlGateOut = gate(baseIdOut);
    cGate *controlGateIn = gate(baseIdIn);

    cModule *nextMux = controlGateOut->getPathEndGate()->getOwnerModule();
    nextMux->setGateSize("muxInOut", size+1);

    cChannelType *channelFactory;
    if(!createTransmitter)
        channelFactory = cChannelType::get("obsmodules.src.Base.Fibre.SpectrumChannelDelay");
    else
        channelFactory = cChannelType::get("obsmodules.src.Base.Fibre.SpectrumChannelTransmitter");

    cChannel *inChannel = channelFactory->create("inChannel");
    cChannel *outChannel = channelFactory->create("outChannel");

    //    nextMux->gate(controlGateOut->getPathEndGate()->getBaseId()+size)->connectTo(gateIn, inChannel);
    //    gateOut->connectTo(nextMux->gate(controlGateIn->getPathStartGate()->getBaseId()+size), outChannel);

    nextMux->gate(controlGateIn->getPathStartGate()->getBaseId()+size)->connectTo(gateIn, inChannel);
    gateOut->connectTo(nextMux->gate(controlGateOut->getPathEndGate()->getBaseId()+size), outChannel);

    inChannel->par("assignedSpectrumCenter").setDoubleValue(spectrumCenter);
    inChannel->par("assignedSpectrumLowerBound").setDoubleValue(spectrumLowerBound);
    inChannel->par("assignedSpectrumUpperBound").setDoubleValue(spectrumUpperBound);
    inChannel->par("datarate").setDoubleValue(datarate);
    inChannel->par(inUsePos).setBoolValue(true);

    outChannel->par("assignedSpectrumCenter").setDoubleValue(spectrumCenter);
    outChannel->par("assignedSpectrumLowerBound").setDoubleValue(spectrumLowerBound);
    outChannel->par("assignedSpectrumUpperBound").setDoubleValue(spectrumUpperBound);
    outChannel->par("datarate").setDoubleValue(datarate);
    outChannel->par(inUsePos).setBoolValue(true);

    double d = inChannel->par("assignedSpectrumCenter");
    EV_INFO<<"CHANNEL reserved CENTER: " << d << endl;

    return size;
}


bool Flexi_OBS_BurstMux::tearDownLightPath(int index)
{
    int baseIdIn = gateBaseId("muxInOut$i");
    int baseIdOut = gateBaseId("muxInOut$o");
    int size = gateSize("muxInOut$i");

    if(index >= size || index < 0)
        return false;

    cGate *gateIn = gate(baseIdIn+index)->getPreviousGate();
    cGate *gateOut = gate(baseIdOut+index);

    cChannel *inChannel = gateIn->getChannel();
    cChannel *outChannel = gateOut->getChannel();

    inChannel->par(inUsePos).setBoolValue(false);
    outChannel->par(inUsePos).setBoolValue(false);

    double center = inChannel->par("assignedSpectrumCenter");

    EV_INFO<<"CHANNEL TORN DOWN CENTER: " << center << endl;
    return true;
}

void Flexi_OBS_BurstMux::startReservationTimer(Flexi_OBS_BurstControlPacket* bcp, bool sender)
{
    if(reservationTimerEnabled){
        ReservationTimer* timer = new ReservationTimer("resTimer");
        timer->setBurstifierId(bcp->getBurstifierId());
        timer->setNumseq(bcp->getNumSeq());
        timer->setMsgSize(bcp->getBurstSize());
        timer->setMsgOffset(bcp->getBurstOffset());
        timer->setSpectrumCenter(bcp->getAssignedSpectrumCenter());
        timer->setSpectrumLowerBound(bcp->getAssignedSpectrumLowerBound());
        timer->setSpectrumUpperBound(bcp->getAssignedSpectrumUpperBound());
        timer->setTimerStart(simTime());
        timer->setChannelIndex(bcp->getReservedChannelIndex());
        timer->setSenderId(bcp->getSrcAddr());

        //transmission duration still has to be factored in, hence manually calculate transmission duration
        simtime_t transmissionDuration = (bcp->getBurstSize()*8)/bcp->getDatarate();

        timer->setMsgDuration(transmissionDuration);

        timer->setTimerEnd(simTime() + timer->getMsgDuration() + bcp->getBurstOffset());

        scheduleAt(timer->getTimerEnd(), timer);
        reservationTimers.insert({timer->getChannelIndex(), timer});
    }
}

void Flexi_OBS_BurstMux::cancelAndDeleteReservationTimer(int channelIndex, int burstifierId, int numSeq, int senderId)
{
    bool matches = true;
    std::map<int, ReservationTimer*>::iterator it = reservationTimers.find(channelIndex);

    if(it != reservationTimers.end()){
        ReservationTimer* timer = (*it).second;

        EV_INFO<< "reservation timer for bId = " << timer->getBurstifierId() << " numseq = " << timer->getNumseq() << endl;

        if(burstifierId != -1 && numSeq != -1 && senderId != -1)
        {
            if(timer->getBurstifierId() != burstifierId && timer->getNumseq() != numSeq && timer->getSenderId() != senderId){
                matches = false;
                EV_ERROR << "Reservation timer not deleted";
            }
        }

        if(it != reservationTimers.end() && matches){
            cMessage *ev = cancelEvent(timer);
            reservationTimers.erase(it);
            delete(ev);
        }
    }
}

int Flexi_OBS_BurstMux::getControlGateIndex()
{
    if(!hasOwnControlChannel)
        return 0;
    else{
        if(position == Mux::Left)
            return 0;
        else return 1;
    }
}

bool Flexi_OBS_BurstMux::sendBurst(OBS_Burst* burst)
{
    for(int i = 0; i < reservations.size(); i++)
    {
        if(reservations[i].burstifierId == burst->getBurstifierId() && reservations[i].numseq == burst->getNumSeq() && reservations[i].isSender)
        {
            int baseIdOut = gateBaseId("muxInOut$o");
            cGate *outGate = gate(baseIdOut+reservations[i].index);
            cChannel* channel = outGate->getChannel();
            bool inUse = channel->par("inUseLeft") || channel->par("inUseRight");

            //if channel has been torn down
            if(!inUse)
            {
                burstLostByFailedReservation++;
                burstLost++;
                burstLoss = (double)burstLost/burstCounter;
                if(!burst->getHasBeenTransmitted())
                    burstDroppedAtSource++;

                EV_INFO << "BURST LOSS = " << burstLoss;

                EV_INFO << "Burst dropped due to late arrival bid =" << burst->getBurstifierId() <<" numseq = " << burst->getNumSeq() << " index =  " << reservations[i].index << endl;
                emit(lostBurstId, 2);

                delete(burst);

                return false;
            }

            channel->par("delay").setDoubleValue(propagationDelay.dbl());

            if(enableImpairments){
                TransmissionEntry* entry = new TransmissionEntry("transmissionEntry");
                double specCenter = channel->par("assignedSpectrumCenter");
                double specLower = channel->par("assignedSpectrumLowerBound");
                double specUpper = channel->par("assignedSpectrumUpperBound");
                double datarate = channel->par("datarate");

                entry->setBitrate(datarate/1000000);
                entry->setPower(burst->getSourcePower());
                entry->setSpectrumCenter(specCenter);
                entry->setSpectrumLowerBound(specLower);
                entry->setSpectrumUpperBound(specUpper);
                entry->setSender(position);
                entry->setStartTime(simTime());

                simtime_t transmissionDuration = SIMTIME_ZERO;
                if(channel->par("isDatarateChannel"))
                    transmissionDuration = check_and_cast<cDatarateChannel*>(channel)->calculateDuration(burst);

                entry->setEndTime(simTime()+ transmissionDuration + propagationDelay);
                burst->setTransmissionEntry(entry);
                sendDirect(entry, table, "entryIn");
            }

            burst->setHasBeenTransmitted(true);
            send(burst, outGate->getId());

            return true;
        }
    }

    burstLostByFailedReservation++;
    burstLost++;
    burstLoss = (double)burstLost/burstCounter;

    EV_INFO << "BURST LOSS = " << burstLoss;

    emit(lostBurstId, 2);
    delete(burst);
    return false;
}

bool Flexi_OBS_BurstMux::sendCtlMsg()
{
    if(processControlQueue->isScheduled())
        return false;

    if(!hasOwnControlChannel)
    {
        if(controlChannelOut->isBusy() || controlChannelIn->isBusy()){
            if(c == 4)c=0;

            c++;
            scheduleAt(simTime()+c*propagationDelay,processControlQueue);
            return false;
        }

        c=0;
    }

    TransmittedMessage_Base* msg = check_and_cast<TransmittedMessage_Base*>(controlChannelQueue.pop());

    if(strcmp(msg->getName(), "BCP") == 0)
    {
        Flexi_OBS_BurstControlPacket* bcp = check_and_cast<Flexi_OBS_BurstControlPacket*>(msg);

        bool ret = doReservationAndSignalling(bcp);

        offsetTimes.record(bcp->getBurstOffset());

        if(!ret) delete(bcp);

        scheduleAt((controlChannelOut->getTransmissionFinishTime() <= simTime() ? simTime() : controlChannelOut->getTransmissionFinishTime()) + guardTime,processControlQueue);
        return ret;
    }


    opticalLogic(msg, false);

    if(enableImpairments){
        TransmissionEntry* entry = new TransmissionEntry("transmissionEntry");
        double specCenter = controlChannelOut->par("assignedSpectrumCenter");
        double specLower = controlChannelOut->par("assignedSpectrumLowerBound");
        double specUpper = controlChannelOut->par("assignedSpectrumUpperBound");
        double datarate = controlChannelOut->par("datarate");

        entry->setBitrate(datarate/1000000);
        entry->setPower(msg->getSourcePower());
        entry->setSpectrumCenter(specCenter);
        entry->setSpectrumLowerBound(specLower);
        entry->setSpectrumUpperBound(specUpper);
        entry->setSender(position);
        entry->setStartTime(simTime());
        entry->setEndTime(simTime() +controlChannelOut->calculateDuration(msg) + controlChannelOut->getDelay());
        msg->setTransmissionEntry(entry);
        sendDirect(entry, table, "entryIn");
    }

    send(msg, controlChannelOutGate);
    scheduleAt((controlChannelOut->getTransmissionFinishTime() <= simTime() ? simTime() : controlChannelOut->getTransmissionFinishTime()) + guardTime,processControlQueue);
    return true;
}

void  Flexi_OBS_BurstMux::handleReservationTimer(cMessage* msg)
{
    ReservationTimer* timer = check_and_cast<ReservationTimer*>(msg);

    cancelReservation(timer);

    cancelOtherTimers(timer);

    cancelAndDeleteReservationTimer(timer->getChannelIndex(), timer->getBurstifierId(), timer->getNumseq(), timer->getSenderId());
}

void Flexi_OBS_BurstMux::insertCtlMsgIntoQueue(cMessage* msg)
{
    if(infiniteControlQueueLength || (!infiniteControlQueueLength && controlChannelQueue.getLength() < maxControlQueueLength)){
        controlChannelQueue.insert(msg);
        sendCtlMsg();
    }else{
        controlMessageLost++;
        controlMessageDroppedByQueue++;

        if(strcmp(msg->getName(), "BCP") ==0){
            Flexi_OBS_BurstControlPacket* bcp = check_and_cast<Flexi_OBS_BurstControlPacket*>(msg);
            lostBcpSources.record(bcp->getSrcAddr());
            lostBcpDestination.record(bcp->getDestAddr());
            bcpLost++;

            emit(lostBCPId, 2);
        }
        delete(msg);
    }
}

void Flexi_OBS_BurstMux::scheduleReleaseMessage(simtime_t time, Flexi_OBS_BurstControlPacket* bcp)
{
    //todo
}

int Flexi_OBS_BurstMux::controlComparator(cObject *obj1, cObject *obj2)
{
    cMessage* msg = check_and_cast<cMessage*>(obj1);
    cMessage* msg1 = check_and_cast<cMessage*>(obj2);

    return msg->getSchedulingPriority() == msg1->getSchedulingPriority() ? 0 : (msg->getSchedulingPriority() > msg1->getSchedulingPriority() ? 1:-1);
}

//try{
//       OBS_Burst *burst = check_and_cast<OBS_Burst *> (msg);
//
//       if(burst == NULL)
//       burstSize.record(burst->getByteLength()); // Record burst length and update burst counter
//       burstRecv++;
//       }catch(cRuntimeError&)
//       {
//           try{
//               Flexi_OBS_BurstControlPacket *bcp = check_and_cast<Flexi_OBS_BurstControlPacket *>(msg);
//           }catch(cRuntimeError&){
//
//           }
//       }

//if(transmissionTimerEnabled){
//       TransmissionTimer* timer = new TransmissionTimer("transTimer");
//       timer->setMsgSize(bcp->getBurstSize());
//       timer->setMsgOffset(bcp->getBurstOffset());
//       timer->setSpectrumCenter(bcp->getAssignedSpectrumCenter());
//       timer->setSpectrumLowerBound(bcp->getAssignedSpectrumLowerBound());
//       timer->setSpectrumUpperBound(bcp->getAssignedSpectrumUpperBound());
//       timer->setTimerStart(simTime.dbl());
//       timer->setChannelIndex(bcp.getReservedChannelIndex());
//
//       int baseIdIn = gateBaseId("muxInOut$i");
//       cGate *inGate = gate(baseIdIn+bcp.getReservedChannelIndex());
//       cDatarateChannel*  channel = check_and_cast<cDatarateChannel*>(inGate->findIncomingTransmissionChannel());
//
//       cPacket* temp = new cPacket();
//       temp->setByteLength(bcp->getBurstSize());
//       timer->setMsgDuration(channel->calculateDuration(temp) + (propagationDelayPerKm*fibreLength));
//
//       timer->setTimerEnd(simTime.dbl() + timer->getMsgDuration() + bcp->getBurstOffset());
//       scheduleAt(timer->getTimerEnd(), timer);
//       transmissionTimers.insert({timer->getChannelIndex(), timer});
//   }
//}

//else if(strcmp(msg->getName(), "transTimer") == 0){
//            TransmissionTimer* timer = check_and_cast<TransmissionTimer*>(msg);
//            tearDownLightPath(timer->getChannelIndex());
//            transmissionTimers.erase(transmissionTimers.find(timer->getChannelIndex()));
//            delete(timer);
//        }


//
//        //Ack gets preferred treatment
//        if(proccessControlQueue->isScheduled() || controlChannelOut->isBusy() || controlChannelIn->isBusy())
//            controlChannelQueue.isEmpty() ? controlChannelQueue.insert(ack) : controlChannelQueue.insertBefore(controlChannelQueue.front(), ack);
//        else
//        {
//            TransmissionEntry* entry = new TransmissionEntry("transmissionEntry");
//
//            double specCenter, specLower, specUpper, datarate;
//            specCenter = controlChannelOut->par("assignedSpectrumCenter");
//            specLower = controlChannelOut->par("assignedSpectrumLowerBound");
//            specUpper = controlChannelOut->par("assignedSpectrumUpperBound");
//            datarate = controlChannelOut->par("datarate");
//
//            entry->setBitrate(datarate/1000000);//bps to mbps
//            entry->setPower(ack->getSourcePower());
//            entry->setSpectrumCenter(specCenter);
//            entry->setSpectrumLowerBound(specLower);
//            entry->setSpectrumUpperBound(specUpper);
//            entry->setSender(position);
//            entry->setStartTime(simTime());
//            entry->setEndTime(simTime() + controlChannelOut->calculateDuration(ack) + controlChannelOut->getDelay());
//
//            ack->setTransmissionEntry(entry);
//
//            send(ack, controlChannelOutGate);
//            sendDirect(entry, table, "entryIn");
//        }

//        if(!bcp->getHasSetupTransmitter() && !ret)
//        {
//            if(!controlChannelQueue.isEmpty())
//            controlChannelQueue.insertBefore(controlChannelQueue.get(0),bcp);
//            else controlChannelQueue.insert(bcp);
//        }

//bool no;
//    if(bcp->getBurstifierId() == 32 && bcp->getNumSeq() == 7 && getFullPath().compare("Horn.fibre5.leftMux") == 0)
//        no = true;

//bool yeaboy;
//   //
//   //    if(center == 2350 && getFullPath().compare("Horn.fibre5.leftMux") == 0)
//   //        yeaboy = true;
//
//   //    if(center == 2350 && simTime().dbl() > 1.5 && getFullPath().compare("Horn.fibre5.leftMux") == 0)
//
//   if(simTime().dbl() > 1.3 && getFullPath().compare("Horn.fibre5.leftMux") == 0)
//       yeaboy = true;

//bool no;
//           if(reservations[i].burstifierId == 32 && reservations[i].numseq == 102 && getFullPath().compare("Horn.fibre5.leftMux") == 0)
//               no = true;

//timer->setTimerEnd(simTime() + timer->getMsgDuration() + bcp->getBurstOffset() - (sender?0:((bcp->getByteLength()*8)/controlChannelDatarate)));

//SimTime time;
//                   if(bcp->getBurstifierId() == 122 && bcp->getNumSeq() == 12008 && getFullPath().compare("Horn.fibre1.leftMux") == 0)
//                       time = simTime();

//SimTime time;
//    if((timer->getBurstifierId() == 470 || timer->getBurstifierId() == 508) && (timer->getNumseq() == 246 || timer->getNumseq() == 215) && getFullPath().compare("NSFNET.fibre18.leftMux") == 0)
//        time = simTime();

//SimTime time;
//    if(bcp->getBurstifierId() == 508 && bcp->getNumSeq() == 215 && getFullPath().compare("NSFNET.fibre18.rightMux") == 0)
//        time = simTime();
//
//    if(bcp->getBurstifierId() == 470 && bcp->getNumSeq() == 246 && getFullPath().compare("NSFNET.fibre18.leftMux") == 0)
//        time = simTime();

//if(time.dbl() > 7 && getFullPath().compare("Horn.fibre1.leftMux") == 0)
//                               time = simTime();
