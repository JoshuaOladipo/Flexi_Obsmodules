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

//
// TODO generated message class
//
cplusplus {{
    #include "K_ShortestPathTableEntry_m.h"
     typedef K_ShortestPathTableEntry *pathPtr; }} // C++ typedef
class noncobject pathPtr; // announcement 

class NodeRoutingTableEntry {
    double pheromoneConc;
    int entry_Id;
    bool responseReceived = true;
    
    int source;
    int destination;
    double assignedSpectrumCenter;
    double assignedSpectrumLowerBound;
    double assignedSpectrumUpperBound;
    int inputPort;
    int outputPort;
    
    pathPtr route;
    int usedCounter = 0;
    int failedCounter = 0;
    int successCounter = 0;
    int numberOfCoreNodes = 0;
}
