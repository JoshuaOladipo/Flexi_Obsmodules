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
    #include "TransmittedMessage_m.h" }} // C++ typedef

packet TransmittedMessage_Base; 

packet TraversalAck extends TransmittedMessage_Base {
    int burstifierId = -1; //Burstifier id
    int numSeq = -1; //Sequence number into packet burstifier
    int senderId = -1; //Burst sender identifier. Not used as a Id
    int distanceDifference;
    int lastEntryId;
    double queueTime;
    
    byteLength = 20;
    isControl = true;
}
