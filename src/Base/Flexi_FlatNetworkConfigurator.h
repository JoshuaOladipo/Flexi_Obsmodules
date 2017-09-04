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

#ifndef __OBSMODULES_FLEXI_FLATNETWORKCONFIGURATOR_H_
#define __OBSMODULES_FLEXI_FLATNETWORKCONFIGURATOR_H_

#include <algorithm>
#include <omnetpp.h>

#include "inet/common/INETDefs.h"
#include "inet/networklayer/contract/ipv4/IPv4Address.h"
#include "inet/networklayer/contract/IRoutingTable.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/common/InterfaceEntry.h"
#include "inet/networklayer/ipv4/IPv4InterfaceData.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/ipv4/IPv4Route.h"
#include "Flexi_WeightedTopology.h"
#include "K_ShortestPathTableEntry_m.h"
#include "K_ShortestPathTable.h"

using namespace std;
using namespace inet;

class Flexi_FlatNetworkConfigurator : public cSimpleModule
{
protected:
    struct NodeInfo {
        NodeInfo() {isIPNode = false; ift = NULL; rt = NULL; usesDefaultRoute = false; ipForwardEnabled = true;}
        bool isIPNode;
        IInterfaceTable *ift;
        IRoutingTable *rt;
        IPv4Address address;
        bool usesDefaultRoute;
        bool ipForwardEnabled;
    };
    typedef std::vector<NodeInfo> NodeInfoVector;

  protected:
    double startTime;
    int maxNumberOfShortestPaths;
    bool fillCoreNodeTables, fillIpTrafGenAddresses;
    virtual int numInitStages() const  {return 3;}
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);

    virtual void extractTopology(cTopology& topo, NodeInfoVector& nodeInfo);
    virtual void assignAddresses(cTopology& topo, NodeInfoVector& nodeInfo);
    virtual void addDefaultRoutes(cTopology& topo, NodeInfoVector& nodeInfo);
    virtual void fillShortestPathRoutingTables(cTopology& topo, NodeInfoVector& nodeInfo);
    virtual void fillRoutingTables(cTopology& _topo, NodeInfoVector& nodeInfo);

    virtual void setDisplayString(cTopology& topo, NodeInfoVector& nodeInfo);
    void printTimeSpentUsingDuration(const char *name, long duration);
    void printElapsedTime(const char *name, long startTime);
};

#endif
