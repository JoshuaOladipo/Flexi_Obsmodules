#include <omnetpp.h>
#include <cmath>
#include <stdlib.h>
#include "inet/common/INETDefs.h"
#include "inet/common/NotifierConsts.h"
#include "OBS_Burst.h"
#include "Flexi_OBS_BurstControlPacket_m.h"
#include "TransmissionEntry_m.h"
#include "FibreTable.h"
#include "TransmittedMessage_m.h"
#include "ReservationTimer_m.h"
#include <ostream>
#include <string>
#include <iosfwd>

using namespace std;

class Flexi_OBS_BurstRouterInfo;

//! Responsible of burst sending through the OBS Network
class Flexi_OBS_BurstMux : public cSimpleModule{
protected:
    static constexpr double propagationDelayPerKm = 0.000005;//5 microseconds

    struct reservation{
        int index;
        int numseq;
        int burstifierId;
        int msgSize;
        bool isSender;
        simtime_t msgOffset;

        reservation(int index_, int numseq_, int burstifierId_, int msgSize_, simtime_t msgOffset_, bool isSender_ )
        {
            index = index_;
            numseq = numseq_;
            burstifierId = burstifierId_;
            msgSize = msgSize_;
            msgOffset = msgOffset_;
            isSender = isSender_;
        }

        //        ostream& operator <<(ostream& os, const reservation& rhs)
        //        {
        //        os << rhs.index<< rhs.numseq<< rhs.burstifierId;
        //        return os;
        //        }
    };

    //statistic signals
    simsignal_t lostBurstId;
    simsignal_t lostBCPId;

    // Statistic counters
    double burstLoss;
    int controlMessageLost, bcpLost, controlMessageDroppedByQueue, controlMessageLostByImpairments, burstLostByFailedReservation;
    int burstLost, burstDroppedAtSource, recvedBcpsFromNode, burstRecvFromNode, controlMessageFromNode, wavelengthAssignmentType, burstCounter;

    //Statistics vectors
    cOutVector lostBcpSources;
    cOutVector lostBcpDestination;
    cOutVector offsetTimes;
    cOutVector transmissionCenters;

    simtime_t propagationDelay;//!< propagation delay across current fibre, calculated by multiplying propagationDelayPerKm by length of fibre
    simtime_t guardTime; //!< Offset which could be placed between consecutive burst transmissions.
    cQueue controlChannelQueue; //!< Queue of BCPs pending to be sent (because they found BCP channel busy).

    double k, attenuationConst, fibreLength;
    bool reservationTimerEnabled, hasOwnControlChannel;
    bool controlChannelReady = false;
    bool enableImpairments, enablePriorityQueuing;

    //c = collision count
    int maxControlQueueLength, gridType, numOfWavelengths, c;
    double transmitterPower, recieverSensitivity;
    double spectrumLowerBound, spectrumUpperBound, totalBandwidth, assignedSpectrumWidth;
    bool useExplicitRelease, infiniteControlQueueLength;

    vector<reservation> reservations;
    map<int,ReservationTimer*> reservationTimers;
    Mux position;
    const char* inUsePos;
    FibreTable* table;

    cMessage* processControlQueue;
    cDatarateChannel* controlChannelOut;
    cDatarateChannel* controlChannelIn;
    cGate* controlChannelOutGate;

    static int controlComparator(cObject *obj1, cObject *obj2);

    //! Initialize the scheduled and BCP queues, set the control channel as free, create the horizon array which size is the value of the lambda parameter and initialize them to 0's.
    virtual void initialize();
    //! Write scalars and make all the cleanup.
    virtual void finish();
    //!Message handler of the module. It contains the protocol needed to send bursts to an assigned lightpath. See ned documentation for details.
    //! @param *msg Message received by the getModule(either messages from the outer-world or an auto-message).
    void handleMessage(cMessage *msg);
    virtual ~Flexi_OBS_BurstMux();

    virtual bool isMessageReadable(TransmittedMessage_Base* msg);
    virtual void opticalLogic(TransmittedMessage_Base* msg, bool justPassedThroughFiber);

    int getControlGateIndex();
    int createLightPath(double spectrumCenter, double spectrummLowerBound, double spectrumUpperBound, double datarate, bool isDelay);
    bool tearDownLightPath(int index);

    void insertCtlMsgIntoQueue(cMessage* msg);
    bool sendCtlMsg();
    bool sendBurst(OBS_Burst* burst);

    void startReservationTimer(Flexi_OBS_BurstControlPacket* bcp, bool sender);
    void cancelAndDeleteReservationTimer(int channelIndex, int burstifierId=-1, int numSeq=-1, int senderId=-1);
    void handleReservationTimer(cMessage* msg);
    virtual void cancelReservation(ReservationTimer* timer) {throw cRuntimeError("Flexi_OBS_BurstMux is a base type");}
    void scheduleReleaseMessage(simtime_t time, Flexi_OBS_BurstControlPacket* bcp);

    virtual void initialiseWavelengthReservationTables(){throw cRuntimeError("Flexi_OBS_BurstMux is a base type");}
    virtual void doSelfMessageProcessing(cMessage *msg){throw cRuntimeError("Flexi_OBS_BurstMux is a base type");}//return true if handleMessage should return, false otherwise
    virtual bool doProcessingIfMessageReadable(cMessage *msg){throw cRuntimeError("Flexi_OBS_BurstMux is a base type");}
    virtual void doProcessingBeforeSendingCtlMsg(cMessage *msg){throw cRuntimeError("Flexi_OBS_BurstMux is a base type");}
    virtual bool doReservationAndSignalling(Flexi_OBS_BurstControlPacket* bcp){throw cRuntimeError("Flexi_OBS_BurstMux is a base type");}
    virtual bool doReservationReceiverSide(Flexi_OBS_BurstControlPacket* bcp){throw cRuntimeError("Flexi_OBS_BurstMux is a base type");}
    virtual void cancelOtherTimers(ReservationTimer* timer){throw cRuntimeError("Flexi_OBS_BurstMux is a base type");}
    virtual bool assignWavelength(Flexi_OBS_BurstControlPacket* bcp){throw cRuntimeError("Flexi_OBS_BurstMux is a base type");}
    virtual double determinePercentageFreeWavelengths(){throw cRuntimeError("Flexi_OBS_BurstMux is a base type");}
};
