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
// TODO auto-generated type
//
module Fibre
{
    parameters:
        bool fullDuplex = default(false);
        double attenuationConstant @unit(db) = default(0.2db);
        double fibreLength @unit(km) = default(12km);
        double leftTransmitterPower @unit(dbm) = default(30dbm);
        double leftRecieverSensitivity @unit(dbm) = default(5dbm);
        double rightTransmitterPower @unit(dbm) = default(30dbm);
        double rightRecieverSensitivity @unit(dbm) = default(5dbm);
        double controlChannelCenter @unit(GHz);
        double controlChannelLowerBound @unit(GHz);
        double controlChannelUpperBound @unit(GHz);
        double controlChannelDatarate @unit(Gbps);
        
        double controlChannelCenter1 @unit(GHz) = default(0);
        double controlChannelLowerBound1 @unit(GHz) = default(0);
        double controlChannelUpperBound1 @unit(GHz) = default(0);
        double controlChannelDatarate1 @unit(Gbps) = default(0);
        string muxType;
        @link(length);
        @display("i=block/mac");
    gates:
        inout left;
        inout right;
        //inout control[numOfControlChannels];   
        //inout control; 

    submodules:
        leftMux: <muxType> like IMux {
            transmitterPower = leftTransmitterPower;
            recieverSensitivity = leftRecieverSensitivity;
            attenuationConst = attenuationConstant;
            length = fibreLength;
            hasOwnControlChannel = fullDuplex;
            @display("p=39,50");
        }
        rightMux: <muxType> like IMux {
            transmitterPower = rightTransmitterPower;
            recieverSensitivity = rightRecieverSensitivity;
            attenuationConst = attenuationConstant;
            length = fibreLength;
            hasOwnControlChannel = fullDuplex;
            @display("p=160,50");
        }

        fibreTable: FibreTable {
            @display("p=103,127");
        }
    connections:
        left <--> leftMux.toNode;
        rightMux.toNode <--> right;

        leftMux.muxInOut++ <--> SpectrumChannelTransmitter {  datarate = controlChannelDatarate; isControl = true; assignedSpectrumCenter = controlChannelCenter; assignedSpectrumLowerBound = controlChannelLowerBound; assignedSpectrumUpperBound = controlChannelUpperBound; weight = fibreLength; } <--> rightMux.muxInOut++;
        
        leftMux.muxInOut++ <--> SpectrumChannelTransmitter {  datarate = controlChannelDatarate; isControl = true; assignedSpectrumCenter = controlChannelCenter1; assignedSpectrumLowerBound = controlChannelLowerBound1; assignedSpectrumUpperBound = controlChannelUpperBound1; weight = fibreLength; } <--> rightMux.muxInOut++
        if fullDuplex;
        
}
