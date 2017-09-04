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

#ifndef __OBSMODULES_FLEXI_OBS_PACKETBURSTIFIER_H_
#define __OBSMODULES_FLEXI_OBS_PACKETBURSTIFIER_H_

#include <omnetpp.h>
#include "inet/networklayer/ipv4/IPv4Datagram.h"
#include "inet/networklayer/contract/INetworkProtocolControlInfo.h"
#include "OBS_Burst.h"
#include "OBS_BurstifierInfo_m.h"
#include "QueueAssignment.h"
#include "Flexi_OBS_PacketDispatcher.h"

using namespace inet;
/**
 * TODO - Generated class
 */
class Flexi_OBS_PacketBurstifier : public cSimpleModule
{
public:
    virtual ~Flexi_OBS_PacketBurstifier();
protected:
    //Main parameters:
    int assembly;
    cQueue burstContent; //!< Packet queue.
    simsignal_t assembledSignalId;
    simtime_t timeout; //!< Burstifier's timeout. If reached, burst will be assembled with the current content of the queue.
    int maxSize; //!< Burst maximum size.
    int numPackets; //!< Maximum number of packets.
    int minSizeWithPadding; //!<  Padding value. Fills burst size to this value if not reached during packet collecting. If 0 doesn't do padding.
    bool overflowLastPacket; //!< If true, allows the last packet to enter the burst even if size is exceeded by that. If false, burst will be assembled and the current message will be inserted as the first message of the next burst.
    int cteHeader; //!< Burst header size (in bytes).
    int varHeader; //!< 'Variable' header size (in bytes). Attached to total burst size when a packet is inserted into the burst.
    bool includeMsgsInBurst;

    //Current burst information
    int burstBits; //!< Current burst size (in bits).
    int numBurstPackets; //!< Number of packets of the current burst.

    int destLabel; //!< Burst destination label.

    cMessage *timeout_msg; //!< Timeout message.

    //Statistics
    int burstCounter; //!< Created burst counter.
    cStdDev recvPackSize; //!< Received packets' length statistics.
    cOutVector recvPackSizeVec; //!< Length of the packets received (in bytes).
    cStdDev queuedTime; //!< Time between the first packet is queued and each of the packets are queued.
    cOutVector avgPacketTime; //!< Average packet delay due the burst assembly.
    cOutVector burstSize; //!< This vector stores burst's sizes.

    simtime_t firstPacket_t; //!< Arrival time of the first packet for the current burst.
    Flexi_OBS_PacketDispatcher* dispatch;

    virtual void initialize();
    // virtual void finish();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
    //! Builds an OBS_Burst object with all elements inside burstContent.
    void assembleBurst();
    void doMixedAssembly(cMessage* msg);
};

#endif
