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

#ifndef __OBSMODULES_FIBRETABLE_H_
#define __OBSMODULES_FIBRETABLE_H_

#include <omnetpp.h>
#include "TransmissionEntry_m.h"

using namespace omnetpp;
using namespace std;

/**
 * TODO - Generated class
 */
class FibreTable : public cSimpleModule, public cListener
{
public:
    set<TransmissionEntry*>* getEntriesBetweenTimes(Mux sender, simtime_t startTime, simtime_t endTime);
    const vector<TransmissionEntry*> getEntriesWithStartTime(Mux sender, simtime_t startTime);
protected:
    simtime_t cleanUpInterval;
    int maxContainerSize;
    simtime_t longestDuration;
    bool infiniteContainerSize;
    cMessage* cleanUpTimer;
    cArray transmissions;
    map<simtime_t, vector<TransmissionEntry*>> leftStartTimeIndex;
    map<simtime_t, vector<TransmissionEntry*>> rightStartTimeIndex;
    map<simtime_t, vector<TransmissionEntry*>> leftEndTimeIndex;
    map<simtime_t, vector<TransmissionEntry*>> rightEndTimeIndex;
    virtual void handleMessage(cMessage *msg);
    virtual void initialize();
    void cleanUp();
};

#endif
