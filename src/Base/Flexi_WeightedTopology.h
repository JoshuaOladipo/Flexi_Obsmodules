//
// Copyright (C) 2011 OpenSim Ltd
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//
// @author: Zoltan Bojthe

//#include "INETDefs.h"

/**
 * expands cTopology with weighted shortest path finder algorithm
 *
 * The cTopology::calculateWeightedSingleShortestPathsTo() implements in OMNeT 4.3
 */
#include <omnetpp.h>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;
using namespace omnetpp;

class Flexi_WeightedTopology : public cTopology
{
private:
    class WLink : public cTopology::Link
    {
        friend class Flexi_WeightedTopology;

    private:
        bool removed = false;
    };

    /** copy from cTopology:Node */
    class WNode : public cTopology::Node
    {
        friend class Flexi_WeightedTopology;

    private:
        //            int module_id;
        //            double wgt;
        //            bool enabl;
//        int num_in_links;
//        Link **in_links;
//        int num_out_links;
//        Link *out_links;
        const char* name;

        // variables used by the shortest-path algorithms
        bool known;
        bool removed = false;

    public:
        WNode(int moduleId=-1) {this->moduleId=moduleId; weight=0; enabled=true; dist=INFINITY; outPath= nullptr;}
        WLink* getLinkTo(WNode* node){
            for(int i = 0; i < this->getNumOutLinks(); i++)
            {
                if(this->getLinkOut(i)->getRemoteNode() == node)
                    return  ((WLink*)this->outLinks[i]);
            }

            return nullptr;
        }

        void setOutPath(Link* link){outPath = link;};
    };

    public:
    /**
     * Constructor.
     */
    explicit Flexi_WeightedTopology(const char *name=NULL) : cTopology(name) {};

    /**
     * Apply the Dijkstra algorithm to find all shortest paths to the given
     * graph node. The paths found can be extracted via Node's methods.
     * Uses weights in nodes and links.
     */
    void calculateWeightedSingleShortestPathsTo(Node *target);

    vector< vector<double> > calculateWeightedMultipleShortestPathsBetween(
            Node *srcNode, Node *destNode, int maxRoutesPerNode, int srcAddr, int destAddr);

    vector< vector<double> > YensKShortestPathAlg(int srcNodePos, int destNodePos,
            int maxRoutesPerNode, int srcAddr, int destAddr);

    virtual void extractFromNetwork(bool (*selfunc)(cModule *,void *), void *userdata=nullptr);

    protected:
    virtual WNode *createNode(cModule *module) { return new WNode(module->getId()); }
    static bool pathCompareFunction(vector<double> vector1,vector<double> vector2);
    static bool linkCompareFunction(Link* link1, Link* link2);
    static bool hasEqualPath(vector<Node*> path1, vector<Node*> path2);
};
