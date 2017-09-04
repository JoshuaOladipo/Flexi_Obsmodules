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

package obsmodules.src.Base;

import inet.networklayer.configurator.ipv4.FlatNetworkConfigurator;
//
// TODO auto-generated module
//
simple Flexi_FlatNetworkConfigurator extends FlatNetworkConfigurator
{
    parameters:
    int k = default(5); //maximum number of shortest paths to hold for each src-dest pair
    bool fillCoreNodeTables = default(false);
    bool fillIpTrafGenAddresses = default(true);
    
    @class(Flexi_FlatNetworkConfigurator);
}
