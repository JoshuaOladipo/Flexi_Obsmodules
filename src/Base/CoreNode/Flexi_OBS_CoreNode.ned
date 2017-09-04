package obsmodules.src.Base.CoreNode;
import obsmodules.src.Base.K_ShortestPathTable;


//
// Switching device in the OBS architecture.
//
module Flexi_OBS_CoreNode
{
    parameters:
        @node;
        double spectrumLowerBound @unit(GHz);
        double spectrumUpperBound @unit(GHz);
        bool forwarding = default(true);
        bool InSuperNode = default(false);
        string controlLogicType = default("Flexi_OBS_CoreControlLogic");
        string routingTableType = default("Flexi_OBS_CoreRoutingTable");
        @display("i=block/switch");
    gates:
        inout inOut[];
    submodules:
        Input: Flexi_OBS_CoreInput {
            parameters:
                @display("i=block/arrival;p=81,127");
            gates:
                in[sizeof(inOut)];
        }
        OXC: Flexi_OBS_OpticalCrossConnect {
            parameters:
                @display("i=block/switch;p=218,195");
            gates:
                out[sizeof(inOut)];
        }
        iCoreRoutingTable: <routingTableType> like ICoreRoutingTable {
            @display("p=108,39");
        }
        iCoreControlLogic: <controlLogicType> like ICoreControlLogic {
            @display("p=270,103");
            inSuperNode = InSuperNode;
        }
        k_ShortestPathTable: K_ShortestPathTable {
            @display("p=218,39");
        }
    connections:

        for i=0..sizeof(inOut)-1 {
            inOut$i[i] --> Input.in[i];
        }

        for i=0..sizeof(inOut)-1 {
            OXC.out[i] --> inOut$o[i];
        }

        Input.outControl --> iCoreControlLogic.inInput;

        Input.outOXC --> OXC.inInput;

        iCoreControlLogic.outOXC --> OXC.inControl;
}
