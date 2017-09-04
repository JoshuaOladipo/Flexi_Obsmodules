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
#include <omnetpp.h>
#include <map>
#include "Flexi_OBS_BurstControlPacket_m.h"
#include "OBS_CoreNodeInfo_m.h"

using namespace std;
using namespace omnetpp;

class Flexi_OBS_CoreInput : public cSimpleModule{
public:
    virtual ~Flexi_OBS_CoreInput();

protected:
    int burstRecieved;
    int controlRecieved;
    int bcpRecieved;
    simtime_t conversionDelay;
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void finish();
};

