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

//
// TODO auto-generated type
//
module Flexi_OBS_EdgeInterface
{
    parameters:
        string disassemblerType = default("Flexi_OBS_BurstDisassembler");
        string routingTable = default("Flexi_OBS_EdgeRoutingTable");
        bool InSuperNode;
        @display("bgb=184,234");
    gates:
        inout physInOut[];
        input upperLayerIn;
        output upperLayerOut;
    submodules:
        assembler: Flexi_OBS_BurstAssembler {
            parameters:
                inSuperNode = InSuperNode;
                @display("p=82,79;i=block/fork");
        }
        disassembler: <disassemblerType> like IDisassembler {
            parameters:
                @display("p=99,150;i=block/join");
        }
       EdgeRoutingTable: <routingTable> like IEdgeRoutingTable {
            @display("p=41.986664,112.17333");
            inSuperNode = InSuperNode;
        }
    connections:
        upperLayerIn --> assembler.in;
        disassembler.out --> upperLayerOut;

        for i=0..sizeof(physInOut)-1 {
            physInOut$i[i] --> disassembler.in++;
            assembler.out++ --> physInOut$o[i];
        }
}
