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

cplusplus {{
    #include "TransmissionEntry_m.h"
     typedef TransmissionEntry *tEntryPtr; }} // C++ typedef
class noncobject tEntryPtr; // announcement 

packet TransmittedMessage{
        @customize(true);
        double sourcePower @unit(db);
        bool hasPassedFirstStation = false;
        bool isControl;
        bool isReadable;
        tEntryPtr transmissionEntry;
        simtime_t sourceSendTIme;
}
