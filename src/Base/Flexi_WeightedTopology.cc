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


#include "Flexi_WeightedTopology.h"

void Flexi_WeightedTopology::calculateWeightedSingleShortestPathsTo(Node *_target)
{
    if (!_target)
        throw cRuntimeError(this,"..ShortestPathTo(): target node is NULL");
    target = _target;

    // clean path infos
    for (int i=0; i<nodes.size(); i++)
    {
        ((WNode *)nodes[i])->known = false;
        ((WNode *)nodes[i])->dist = INFINITY;
        ((WNode *)nodes[i])->outPath = nullptr;
    }

    ((WNode *)target)->dist = 0;

    std::list<Node*> q;

    q.push_back(target);

    while (!q.empty())
    {
        Node *dest = q.front();
        q.pop_front();

        ASSERT(dest->getWeight() >= 0.0);

        // for each w adjacent to v...
        for (int i=0; i < dest->getNumInLinks(); i++)
        {
            if (!(dest->getLinkIn(i)->isEnabled()) || ((WLink*)dest->getLinkIn(i))->removed) continue;

            Node *src = dest->getLinkIn(i)->getRemoteNode();
            if (!src->isEnabled() || ((WNode *)src)->removed) continue;

            double linkWeight = dest->getLinkIn(i)->getWeight();
            ASSERT(linkWeight > 0.0);

            double newdist = ((WNode *)dest)->dist + linkWeight;
            if (dest != target)
                newdist += dest->getWeight();  // dest is not the target, uses weight of dest node as price of routing (infinity means dest node doesn't route between interfaces)
            if (newdist != INFINITY && ((WNode *)src)->dist > newdist)  // it's a valid shorter path from src to target node
            {
                if (((WNode *)src)->dist != INFINITY)
                    q.remove(src);   // src is in the queue
                ((WNode *)src)->dist = newdist;
                ((WNode *)src)->outPath =((WNode *)dest)->inLinks[i];

                // insert src node to ordered list
                std::list<Node*>::iterator it;
                for (it = q.begin(); it != q.end(); ++it)
                    if (((WNode *)(*it))->dist > newdist)
                        break;
                q.insert(it, src);
            }
        }
    }
}

vector< vector<double> > Flexi_WeightedTopology::YensKShortestPathAlg(int srcNodePos, int destNodePos,
        int maxRoutesPerNode, int srcAddr, int destAddr)
{
    calculateWeightedSingleShortestPathsTo(this->getNode(destNodePos));

    std::vector<vector<Node*>> A;
    std::vector<vector<Node*>> B;
    vector<double> bSize;
    vector<double> aSize;
    std::vector<Node*> shortestPath;
    vector< vector<double> > shortestPaths;
    vector<WNode*> removedNodes;
    vector<WLink*> removedLinks;

    Node *curr = this->getNode(srcNodePos);
    shortestPath.push_back(curr);
    double cost = 0;
    while(curr->getNumPaths() != 0)
    {
        cost += curr->getPath(0)->getWeight();
        curr = curr->getPath(0)->getRemoteNode();
        shortestPath.push_back(curr);
    }

    if(shortestPath.size() == 0)
        return shortestPaths;

    aSize.push_back(cost);

    A.push_back(shortestPath);

    for(int k = 1; k < maxRoutesPerNode; k++)
    {
        for(int i = 1; i <= A[k-1].size()-1; i++)
        {
            Node* spurNode = A[k-1].at(i-1);
            std::vector<Node*> rootPath(A[k-1].begin(), A[k-1].begin()+i);
            std::vector<Node*> spurPath;
            std::vector<Node*> totalPath;

            for(int j = 0; j < A.size(); j++)
            {
                if(hasEqualPath(A[j], rootPath))
                {
                    WLink* link = ((WNode*)A[j].at(rootPath.size()-1))->getLinkTo((WNode*)A[j].at(rootPath.size()));
                    link->removed = true;
                    removedLinks.push_back(link);
                }
            }

            for(int j = 0; j < rootPath.size()-1; j++)
            {
                ((WNode*)rootPath[j])->removed = true;
                removedNodes.push_back((WNode*)rootPath[j]);
            }

            calculateWeightedSingleShortestPathsTo(this->getNode(destNodePos));

            curr = spurNode;
            spurPath.push_back(spurNode);
            while(curr->getNumPaths() != 0)
            {
                curr = curr->getPath(0)->getRemoteNode();
                spurPath.push_back(curr);
            }

            totalPath.insert(totalPath.begin(),rootPath.begin(), rootPath.end());
            totalPath.insert(totalPath.end(),spurPath.begin()+1, spurPath.end());

            for(int j = 0; j < removedNodes.size(); j++)
                removedNodes[j]->removed = false;

            for(int j = 0; j < removedLinks.size(); j++)
                removedLinks[j]->removed = false;

            removedNodes.clear();
            removedLinks.clear();

            if(totalPath[0] == getNode(srcNodePos) && totalPath[totalPath.size()-1] == getNode(destNodePos)){
                B.push_back(totalPath);

                //calculate length of newly inserted path
                cost = 0;
                for(int m = 0; m < B[B.size()-1].size()-1; m++)//for each node
                {
                    Node* currNode = B[B.size()-1].at(m);
                    Node* nextNode = B[B.size()-1].at(m+1);
                    for(int j = 0; j < currNode->getNumOutLinks(); j++)//for each outlink in node
                    {
                        if(currNode->getLinkOut(j)->getRemoteNode() == nextNode){
                            cost += currNode->getLinkOut(j)->getWeight();
                            break;
                        }
                    }
                }

                //sort B ascendingly, make sure newly inserted entry is in right position
                bSize.push_back(cost);
                int pos = bSize.size()-1;
                for(int l = bSize.size()-1; l >= 0; l--)
                {
                    if(bSize[l] > cost)
                        pos = l;
                    else break;
                }

                if(pos != bSize.size()-1){
                    bSize.pop_back();
                    bSize.insert(bSize.begin()+pos, cost);

                    vector<Node*>path = B[B.size()-1];
                    B.insert(B.begin()+pos, path);
                    B.pop_back();
                }
            }
        }

        if(B.empty())
            break;

        A.push_back(B[0]);
        aSize.push_back(bSize[0]);
        B.erase(B.begin());
        bSize.erase(bSize.begin());
    }

    //output A
    for(int i = 0; i < A.size(); i++)//for each path in A
    {
        vector<Node*> pathNodes = A[i];
        int pathSize = pathNodes.size()-1;
        int vectorSize = 2*pathSize + 3;
        vector<double> path(vectorSize); //special indexes 0:srcAddr, n-1:destAddr, n:cost
        path[0]= srcAddr;
        path[vectorSize-2] = destAddr;
        path[vectorSize-1] = aSize[i];
        int pathPos = 0;

        for(int j =0; j < pathNodes.size()-1; j++)//for each node in pathNodes
        {
            Node* node = pathNodes[j];
            for(int k = 0; k < node->getNumOutLinks(); k++)//for each outlink in node
            {
                if(node->getLinkOut(k)->getRemoteNode() == pathNodes[j+1])
                {
                    path[++pathPos] = node->getLinkOut(k)->getLocalGateId();
                    path[++pathPos] = node->getLinkOut(k)->getRemoteGateId();
                }
            }
        }

        shortestPaths.push_back(path);
    }
    return shortestPaths;
}

vector< vector<double> > Flexi_WeightedTopology::calculateWeightedMultipleShortestPathsBetween(Node *srcNode, Node *destNode, int maxRoutesPerNode, int srcAddr, int destAddr)
{
    stack<LinkOut *> unVisitedLinks;
    stack<LinkOut *> visitedLinks;

    if (!srcNode || !destNode)
        throw cRuntimeError(this,"..ShortestPathsBetweeen():at least one target node is NULL");

    vector< vector<double> > shortestPaths;
    if(srcNode->getNumOutLinks() == 0 || destNode->getNumInLinks() == 0 || !(destNode->isEnabled()))
        return shortestPaths;

    // clean path infos
    for (int i=0; i<nodes.size(); i++)
    {
        ((WNode *)nodes[i])->known = false;
        ((WNode *)nodes[i])->dist = INFINITY;
        ((WNode *)nodes[i])->outPath = NULL;
    }

    //sort links in descending order, ensuring longer ones are at the top of the stack
    std::sort(((WNode *)srcNode)->outLinks.begin(), ((WNode *)srcNode)->outLinks.end(), linkCompareFunction);
    for(int i=0; i < srcNode->getNumOutLinks(); i++)
    {
        if(srcNode->getLinkOut(i)->isEnabled())
            unVisitedLinks.push(srcNode->getLinkOut(i));
    }

    ((WNode *)srcNode)->known = true;
    Node* prevNode = srcNode;

    while(!unVisitedLinks.empty())
    {
        LinkOut *outLink = unVisitedLinks.top();
        unVisitedLinks.pop();
        visitedLinks.push(outLink);

        target = outLink->getRemoteNode();

        if(target == destNode)
        {
            stack<LinkOut *> temp;

            //record path, calculate cost
            double cost = 0;

            int pathSize = visitedLinks.size();
            int vectorSize = 2*pathSize + 3;
            vector<double> path(vectorSize); //special indexes 0:srcAddr, n-1:destAddr, n:cost
            path[0]= srcAddr;
            path[vectorSize-2] = destAddr;

            while(!visitedLinks.empty())
            {
                temp.push(visitedLinks.top());
                visitedLinks.pop();
            }

            int pos = 0;
            for(int i = 0; i < pathSize; i++)
            {
                outLink = temp.top();
                target = outLink->getRemoteNode();
                path[++pos] = outLink->getLocalGateId();
                path[++pos] = outLink->getRemoteGateId();

                if(i == pathSize-1 )
                    cost+= outLink->getWeight();
                else{
                    cost += outLink->getWeight() + target->getWeight();
                    visitedLinks.push(outLink);
                    temp.pop();
                }
            }

            path[vectorSize-1] = cost;
            shortestPaths.push_back(path);
            if(shortestPaths.size() == maxRoutesPerNode)
                break;

            LinkOut *visitedOutLink = outLink;

            if(!unVisitedLinks.empty()){
                LinkOut *outLink = unVisitedLinks.top();
                while(outLink->getLocalNode() != visitedOutLink->getLocalNode() && !visitedLinks.empty()){
                    visitedOutLink = visitedLinks.top();
                    visitedLinks.pop();
                }
            }
            continue;
        }

        if(!target->isEnabled() || target->getWeight() == INFINITY){
            LinkOut *visitedOutLink = visitedLinks.top();
            visitedLinks.pop();

            if(!unVisitedLinks.empty()){
                LinkOut *outLink = unVisitedLinks.top();
                while(outLink->getLocalNode() != visitedOutLink->getLocalNode() && !visitedLinks.empty()){
                    visitedOutLink = visitedLinks.top();
                    visitedLinks.pop();
                }
            }
            continue;
        }

        //if target is not destination node, add unvisited links of target to unvisited stack
        if(((WNode *)target)->known == false){
            std::sort(((WNode *)target)->outLinks.begin(), ((WNode *)target)->outLinks.end(), linkCompareFunction);
            for(int i=0; i < target->getNumOutLinks(); i++)
            {
                if(target->getLinkOut(i)->isEnabled() && target->getLinkOut(i)->getRemoteNode() != prevNode)
                    unVisitedLinks.push(target->getLinkOut(i));
            }
        }

        prevNode = target;
        ((WNode *)target)->known = true;
    }

    //reduce size of shortest paths if necessary, according to maxNumberOfShortestPaths
    //    if(shortestPaths.size() > maxRoutesPerNode)
    //    {
    //        std::sort(shortestPaths.begin(), shortestPaths.end(), pathCompareFunction);
    //        shortestPaths.resize(maxRoutesPerNode);
    //    }

    std::sort(shortestPaths.begin(), shortestPaths.end(), pathCompareFunction);
    return shortestPaths;
}

bool Flexi_WeightedTopology::pathCompareFunction(vector<double> vector1,vector<double> vector2)
{
    double cost1 = vector1[vector1.size()-1];
    double cost2 = vector2[vector2.size()-1];

    return cost1 < cost2;
}

bool Flexi_WeightedTopology::linkCompareFunction(Link* link1, Link* link2)
{
    return link1->getWeight() > link2->getWeight();
}

bool Flexi_WeightedTopology::hasEqualPath(vector<Node*> path1, vector<Node*> path2)
{
    if(path1.size() != 0 && path2.size() != 0){
        for(int i =0; i < (path1.size() <= path2.size() ? path1.size() : path2.size()); i++)
        {
            if(path1[i] != path2[i])
                return false;
        }

        return true;
    }

    return false;
}

void Flexi_WeightedTopology::extractFromNetwork(bool (*predicate)(cModule *,void *), void *data)
{
    clear();

    // Loop through all modules and find those that satisfy the criteria
    for (int moduleId = 0; moduleId <= getSimulation()->getLastComponentId(); moduleId++) {
        cModule *module = getSimulation()->getModule(moduleId);
        if (module && predicate(module, data)) {
            WNode *node = createNode(module);
            node->name = module->getName();
            nodes.push_back(node);
        }
    }

    // Discover out neighbors too.
    for (int k = 0; k < (int)nodes.size(); k++) {
        // Loop through all its gates and find those which come
        // from or go to modules included in the topology.

        WNode *node = (WNode *)nodes[k];
        cModule *module = getSimulation()->getModule(node->moduleId);

        for (cModule::GateIterator it(module); !it.end(); ++it) {
            cGate *gate = *it;
            if (gate->getType() != cGate::OUTPUT)
                continue;

            // follow path
            cGate *srcGate = gate;
            int dirrection = 0; //-1 from left, 1 from right
            bool weightSet = false;
            double weight = 0;

            do {
                gate = gate->getNextGate();
                cModule* mod  = gate->getOwnerModule();

                if(strstr(mod->getName(), "leftMux"))
                {
                    if(dirrection == 0){
                        gate = mod->gate("muxInOut$o", 0);
                        cChannel *channel = gate->getTransmissionChannel();

                        if(channel){
                            double h = channel->par("weight");
                            weight += h;
                            weightSet = true;
                        }

                        dirrection = -1;
                    }else if (dirrection == 1){
                        gate = mod->gate("toNode$o");
                        dirrection = 0;
                    }
                }else if(strstr(mod->getName(), "rightMux"))
                {
                    if(dirrection == -1){
                        gate = mod->gate("toNode$o");
                        dirrection = 0;
                    }
                    else if(dirrection == 0){
                        gate = mod->gate("muxInOut$o", 0);
                        cChannel *channel = gate->getTransmissionChannel();

                        if(channel){
                            double h = channel->par("weight");
                            weight += h;
                            weightSet = true;
                        }

                        dirrection = 1;
                    }
                }
            } while (gate && !predicate(gate->getOwnerModule(), data));

            // if we arrived at a module in the topology, record it.
            if (gate) {
                WLink *link = new WLink();
                link->srcNode = node;
                link->srcGateId = srcGate->getId();
                link->destNode = getNodeFor(gate->getOwnerModule());
                link->destGateId = gate->getId();

                if(weightSet)
                    link->weight = weight;

                node->outLinks.push_back(link);
            }
        }
    }

    // fill inLinks vectors
    for (int k = 0; k < (int)nodes.size(); k++) {
        for (int l = 0; l < (int)((WNode*)nodes[k])->outLinks.size(); l++) {
            WLink *link = (WLink*)((WNode*)nodes[k])->outLinks[l];
            ((WNode*)link->destNode)->inLinks.push_back(link);
        }
    }
}
