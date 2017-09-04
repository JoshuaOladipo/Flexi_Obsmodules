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
    #include "TransmittedMessage_m.h"
     }} // C++ typedef

packet TransmittedMessage_Base; 

packet ReservationTimer extends TransmittedMessage_Base{
        int numseq;
        int burstifierId;
        double spectrumCenter;
        double spectrumLowerBound;
        double spectrumUpperBound;
        double msgSize;//in byte
        simtime_t msgOffset;
        simtime_t msgDuration;
        simtime_t timerStart;
        simtime_t timerEnd;
        int channelIndex;
        int senderId;
        
        byteLength = 150;
        isControl = true;
}
