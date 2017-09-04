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

package obsmodules.src.Networks.Horn;

import obsmodules.src.Base.Fibre.Fibre;
import obsmodules.src.Base.Flexi_FlatNetworkConfigurator;
import obsmodules.src.Base.SuperNode.Flexi_OBS_SuperNode;
import obsmodules.src.Networks.BaseNetwork;

//
// TODO Auto-generated network
//
network Horn extends BaseNetwork
{
    submodules:
        flexi_OBS_SuperNode: Flexi_OBS_SuperNode {
            @display("p=686,483");
        }
        flexi_OBS_SuperNode1: Flexi_OBS_SuperNode {
            @display("p=59,57");
        }
        flexi_OBS_SuperNode2: Flexi_OBS_SuperNode {
            @display("p=121,194");
        }
        flexi_OBS_SuperNode3: Flexi_OBS_SuperNode {
            @display("p=670,183");
        }
        flexi_OBS_SuperNode4: Flexi_OBS_SuperNode {
            @display("p=680,318");
        }
        flexi_OBS_SuperNode5: Flexi_OBS_SuperNode {
            @display("p=262,351");
        }
        flexi_OBS_SuperNode6: Flexi_OBS_SuperNode {
            @display("p=463,459");
        }
        fibre: Fibre {
            @display("p=73,124");
        }
        fibre1: Fibre {
            @display("p=401,180");
        }
        fibre2: Fibre {
            @display("p=175,279");
        }
        fibre3: Fibre {
            @display("p=348,427");
        }
        fibre4: Fibre {
            @display("p=571,482");
        }
        fibre5: Fibre {
            @display("p=680,403");
        }
        fibre6: Fibre {
            @display("p=680,254");
        }
        flexi_FlatNetworkConfigurator: Flexi_FlatNetworkConfigurator {
            @display("p=625,47");
        }
    connections:
        flexi_OBS_SuperNode1.links++ <--> fibre.left;
        fibre.right <--> flexi_OBS_SuperNode2.links++;
        flexi_OBS_SuperNode2.links++ <--> fibre2.left;
        fibre2.right <--> flexi_OBS_SuperNode5.links++;
        flexi_OBS_SuperNode5.links++ <--> fibre3.left;
        fibre3.right <--> flexi_OBS_SuperNode6.links++;
        flexi_OBS_SuperNode6.links++ <--> fibre4.left;
        fibre4.right <--> flexi_OBS_SuperNode.links++;
        flexi_OBS_SuperNode.links++ <--> fibre5.left;
        fibre5.right <--> flexi_OBS_SuperNode4.links++;
        flexi_OBS_SuperNode4.links++ <--> fibre6.left;
        flexi_OBS_SuperNode3.links++ <--> fibre6.right;
        fibre1.right <--> flexi_OBS_SuperNode3.links++;
        fibre1.left <--> flexi_OBS_SuperNode2.links++;
}
