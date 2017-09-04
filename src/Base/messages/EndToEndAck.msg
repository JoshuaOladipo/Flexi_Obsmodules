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
    #include "TransmittedMessage_m.h"
     typedef K_ShortestPathTableEntry *pathPtr; }} // C++ typedef
class noncobject pathPtr; // announcement 

packet TransmittedMessage_Base; 

packet EndToEndAck extends TransmittedMessage_Base {
    pathPtr route;
    int routePos = 0;
    
    int burstifierId = -1; //Burstifier id
    int numSeq = -1; //Sequence number into packet burstifier
    int senderId = -1; //Burst sender identifier. Not used as a Id
    int entry_Id;
    
    int entryIds[];
    int entryIdPos;
    int shortestPathCost;
    int distTravelled;
    int nodeCounter = 0;
    
    byteLength = 60;
    isControl = true;
}
