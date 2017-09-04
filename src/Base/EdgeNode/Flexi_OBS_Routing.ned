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
// TODO auto-generated module
//
simple Flexi_OBS_Routing like IRouting
{
    parameters:
        double spectrumLowerBound @unit(GHz);
        double spectrumUpperBound @unit(GHz);
        int gridType = default(1); //0 - flexi-grid, 1 - fixed 50GHz, 2 - fixed 100GHz
        bool deferRoutingWhenInSuperNode = default(false);
        bool InSuperNode;
        string datarates = default("10"); //Gbps
        string datarateProbabilities = default("1");//corressponding probabilities to datarates. all must add up to 1
                
        //corenode parameters, required for calculating offset
        double BCPProcessingDelay @unit(s) = default(0); //Processing time of BCP
        double EOConversionDelay @unit(s) = default(0); //Processing time required to do the EO conversion
        double switchingDelay @unit(s) = default(0);
        double OEConversionDelay @unit(s) = default(0);
        double coreNodeProcessingTime @unit(s) = BCPProcessingDelay + EOConversionDelay + OEConversionDelay;
        
        @signal[sentBurst]();
    gates:
        input internalComm @directIn;
        input in[];
        output out[];
}
