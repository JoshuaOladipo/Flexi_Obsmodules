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

package obsmodules.src.Base.EdgeNode;

import inet.applications.generic.IPvXTrafGen;
import inet.networklayer.common.InterfaceTable;
import obsmodules.src.Base.K_ShortestPathTable;

//
// //change ipforward of edge nodes, if want routing to only be done through edge nodes
//
module Flexi_OBS_EdgeNode
{
    parameters:
        @node;
        @networkNode;
        @display("i=block/classifier2");
        bool inSuperNode = default(false);
    gates:
        inout obsInOut[];  // OBS input and output. vector because can have multiple ports
    submodules:
        interfaceTable: InterfaceTable {
            @display("p=190,43");
        }
        obs: Flexi_OBS_EdgeInterface {
            parameters:
                InSuperNode = inSuperNode;
                @display("p=75,143;q=l2queue;i=block/ifcard");
        }
        k_ShortestPathTable: K_ShortestPathTable {
            @display("p=84,43");
        }
        iPvXTrafGen: IPvXTrafGen {
            @display("p=160,132");
        }
    connections allowunconnected:

        for i=0..sizeof(obsInOut)-1 {
            obsInOut[i] <--> obs.physInOut++;
        }

        obs.upperLayerIn <-- iPvXTrafGen.ipOut;
        obs.upperLayerOut --> iPvXTrafGen.ipIn;
}


