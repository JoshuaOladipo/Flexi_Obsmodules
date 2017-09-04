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

#include "K_ShortestPathTable.h"

Define_Module(K_ShortestPathTable);

void K_ShortestPathTable::initialize()
{
    take(&(this->table));
    this->table.setName("ShortestPathEntry");
}

int K_ShortestPathTable::getDestCount(){return table.size();}

void K_ShortestPathTable::addEntry(K_ShortestPathTableEntry *entry)
{
    for(int i =0; i < table.size(); i++)
    {
        cQueue *q = dynamic_cast<cQueue*>(table[i]);
        K_ShortestPathTableEntry *temp = check_and_cast<K_ShortestPathTableEntry *>(q->front());
        if(temp->getDestAddress() == entry->getDestAddress())
        {
            q->insert(entry);
            return;
        }
    }

    cQueue *paths = new cQueue(NULL, comparator);//compare function
    paths->insert(entry);
    table.add(paths);
}

K_ShortestPathTableEntry* K_ShortestPathTable::getTop(int value, bool byDest)
{
    if(byDest){
        for(int i=0; i < table.size(); i++)
        {
            cQueue *q = dynamic_cast<cQueue*>(table[i]);
            K_ShortestPathTableEntry *temp = check_and_cast<K_ShortestPathTableEntry *>(q->front());
            if(temp->getDestAddress() == value)
                return temp;
        }
    }else {
        cQueue *q = dynamic_cast<cQueue*>(table[value]);
        K_ShortestPathTableEntry *temp = check_and_cast<K_ShortestPathTableEntry *>(q->front());
        return temp;
    }

    return NULL;
}

K_ShortestPathTableEntry* K_ShortestPathTable::getRandom(int value, bool byDest)
{
    if(byDest){
        for(int i=0; i < table.size(); i++)
        {
            cQueue *q = dynamic_cast<cQueue*>(table[i]);
            K_ShortestPathTableEntry *temp = check_and_cast<K_ShortestPathTableEntry *>(q->front());
            if(temp->getDestAddress() == value)
            {
                int size = q->getLength();
                int selected = intrand(size);
                return check_and_cast<K_ShortestPathTableEntry *>(q->get(selected));
            }
        }
    }else {
        cQueue *q = dynamic_cast<cQueue*>(table[value]);
        int size = q->getLength();
        int selected = intrand(size);
        return check_and_cast<K_ShortestPathTableEntry *>(q->get(selected));
    }

    return NULL;
}

map<int, double>* K_ShortestPathTable::getCandidateLinksShortestPaths(int index)
{
    cQueue *q = dynamic_cast<cQueue*>(table[index]);// get entries for a destination
    int size = q->getLength();
    map<int, double> *candidates = new map<int, double>();//create map to hold port and shortest path to destination using port

    K_ShortestPathTableEntry *temp;
    for(int i =0; i < size; i++)//for each entry
    {
        temp = check_and_cast<K_ShortestPathTableEntry *>(q->get(i));

        if(candidates->find(temp->getPath(0)) == candidates->end())//if port not in map
            candidates->insert({temp->getPath(0), temp->getCost()});//create entry for port
        else if(candidates->at(temp->getPath(0)) >= temp->getCost())//if cost of port using another entry is less than current cost in map
            candidates->at(temp->getPath(0)) = temp->getCost();//replace cost
    }

    return candidates;
}

K_ShortestPathTableEntry* K_ShortestPathTable::getLongestAvailable(int value, bool byDest)
{
    if(byDest){
        for(int i=0; i < table.size(); i++)
        {
            cQueue *q = dynamic_cast<cQueue*>(table[i]);
            K_ShortestPathTableEntry *temp = check_and_cast<K_ShortestPathTableEntry *>(q->get(q->getLength()-1));
            if(temp->getDestAddress() == value)
                 return temp;
        }
    }else {
        cQueue *q = dynamic_cast<cQueue*>(table[value]);
        return check_and_cast<K_ShortestPathTableEntry *>(q->get(q->getLength()-1));
    }

    return NULL;
}

int K_ShortestPathTable::comparator(cObject *obj1, cObject *obj2)
{
    K_ShortestPathTableEntry *o1 = check_and_cast<K_ShortestPathTableEntry *>(obj1);
    K_ShortestPathTableEntry *o2 = check_and_cast<K_ShortestPathTableEntry *>(obj2);

    return (o1->getCost() > o2->getCost()) ? 1 : (o1->getCost() == o2->getCost() ? 0 : -1);
    //todo make it also consider path node count, if path cost is the same
}
