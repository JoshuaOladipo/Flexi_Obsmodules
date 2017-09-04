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

package obsmodules.src.Base.Fibre;

//
// Handles creating lightpaths and sending data on lightpaths
//
moduleinterface IMux
{
    parameters:
        double transmitterPower @unit(dbm);
        double recieverSensitivity @unit(dbm);
        double attenuationConst @unit(db);
        double length @unit(km);
        bool hasOwnControlChannel;
   gates:
        inout toNode;//to input node
        inout muxInOut[];//to next mux
}
