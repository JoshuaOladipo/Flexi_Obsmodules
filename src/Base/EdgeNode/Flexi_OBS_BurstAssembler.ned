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
module Flexi_OBS_BurstAssembler
{
    parameters:
        int numPacketBurstifiers = default(14); // Number of OBS_PacketBurstifier modules present in the module.
        string routerType = default("Flexi_OBS_Routing");
        bool inSuperNode;
        @display("bgb=522,413");
    gates:
        input in; // Electronic input
        output out[]; //Output to fibre
    submodules:
        dispatcher: Flexi_OBS_PacketDispatcher {
            parameters:
                numQueues = numPacketBurstifiers;
                @display("p=72,208;i=block/classifier");
            gates:
                out[numPacketBurstifiers];
        }
        packetBurstifier[numPacketBurstifiers]: Flexi_OBS_PacketBurstifier {
            parameters:
                @display("i=block/queue;q=burstifierQueue");
        }
        router: <routerType> like IRouting {
            parameters:
                @display("p=356,200;i=block/process;q=ScheduledBursts");
                InSuperNode = inSuperNode;
            gates:
                in[numPacketBurstifiers];
        }
    connections:
        // Connect the input with the dispatcher
        in --> dispatcher.in;

        // Connect OBS_PacketBurstifiers first
        for i=0..numPacketBurstifiers-1 {
            dispatcher.out[i] --> packetBurstifier[i].in;
            packetBurstifier[i].out --> router.in[i];
        }

        for i=0..sizeof(out)-1 {
            router.out++ --> out[i];
        }
}
