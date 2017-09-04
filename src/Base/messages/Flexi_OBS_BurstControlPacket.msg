//
// Copyright (C) 2010-2012 Javier Armendariz Silva, Naiara Garcia Royo
// Copyright (C) 2010-2012 Universidad Publica de Navarra
//
// This file is part of OBSModules.
//
// OBSModules is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// OBSModules is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with OBSModules.  If not, see <http://www.gnu.org/licenses/>.
//

//Also known as BCP. Control Message for OBS transmissions.
//
//

cplusplus {{ 
    #include "TransmittedMessage_m.h"
    #include "K_ShortestPathTableEntry_m.h"
    typedef K_ShortestPathTableEntry *pathPtr;
     }} // C++ typedef
class noncobject pathPtr; // announcement

packet TransmittedMessage_Base; 

packet Flexi_OBS_BurstControlPacket extends TransmittedMessage_Base
{
    int srcAddr = -1;
    int destAddr = -1;   
    double assignedSpectrumCenter = -1; //Burst's assigned center
    double assignedSpectrumLowerBound = -1; //Burst assigned spectrum Lower Bound
    double assignedSpectrumUpperBound = -1; //Burst assigned spectrum upper bound
    int burstifierId = -1; //Burstifier id
    int numSeq = -1; //Sequence number into packet burstifier
    simtime_t burstOffset = -1; //Difference between BCP send time and burst send time
    int burstSize = -1; // Associated burst size  in bytes
    double datarate; //Gbps
    bool hasSetupTransmitter = false;
    
    int distTravelled = 0; //distance travelled by bcp//needs tobe modified in mux
    int shortestPathCost;
    int nodeCounter = 0;
    
    pathPtr route;     
    int routePos = 0;
    
    int entryId = -1;//if only routing entry at source used
    int entryIds[];//entryids of routing entries used to route bcp
    bool recordPath = false;
    int pathPos = 0;
    
    int componentIds[];
    int compPos = 0;    
        
    int reservedChannelIndex;
    
    double percentFreeWavelengths = 1;
    simtime_t killTime;
    
    byteLength = 150;
    isControl = true;
    
}
