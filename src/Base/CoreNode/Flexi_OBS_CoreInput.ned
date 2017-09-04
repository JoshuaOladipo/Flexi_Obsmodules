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

package obsmodules.src.Base.CoreNode;

//
// Input module for OBS_CoreNode. Splits optical fibers in two parts: control channels connected to the Control Unit and data channels connected to the OXC.
//
simple Flexi_OBS_CoreInput
{
    parameters:
      double OEConversionDelay @unit(s) = default(0); //Processing time required to do the OE conversion
    gates:
     input in[];
     output outControl;
     output outOXC;
}
