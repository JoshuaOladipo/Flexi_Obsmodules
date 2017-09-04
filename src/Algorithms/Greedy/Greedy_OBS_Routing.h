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

#ifndef __OBSMODULES_OBS_ROUTING_H_
#define __OBSMODULES_OBS_ROUTING_H_

#include <omnetpp.h>
#include "Flexi_OBS_Routing.h"
#include "OBS_Burst.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Greedy_OBS_Routing : public Flexi_OBS_Routing
{
  protected:
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);
    virtual void doGreedy(OBS_Burst *burst);
};

#endif
