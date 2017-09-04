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

#ifndef __OBSMODULES_K_SHORTESTPATHTABLE_H_
#define __OBSMODULES_K_SHORTESTPATHTABLE_H_

#include <omnetpp.h>
#include "K_ShortestPathTableEntry_m.h"
using namespace std;
using namespace omnetpp;

/**
 * TODO - Generated class
 */
class K_ShortestPathTable : public cSimpleModule
{
  public:
    virtual void addEntry(K_ShortestPathTableEntry *entry);
    virtual K_ShortestPathTableEntry* getTop(int value, bool byDest=1);//by destination or by index
    virtual K_ShortestPathTableEntry* getRandom(int value, bool byDest=1);
    virtual int getDestCount();
    virtual map<int, double>* getCandidateLinksShortestPaths(int index);
    virtual K_ShortestPathTableEntry* getLongestAvailable(int value, bool byDest=1);
  protected:
    cArray table;
    virtual void initialize();
    static int comparator(cObject *obj1, cObject *obj2);
};

#endif
