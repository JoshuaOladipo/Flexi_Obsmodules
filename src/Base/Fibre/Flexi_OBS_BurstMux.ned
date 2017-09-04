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
simple Flexi_OBS_BurstMux like IMux
{
    parameters:
        bool hasOwnControlChannel = default(false);
        int gridType = default(1); //0 - flexi-grid, 1 - fixed 50GHz, 2 - fixed 100GHz
        int wavelengthAssignmentType = default(0); //0 - preassigned, 1 - fixedfirstfit, 2 - fixed random, 3-flexi firstfit, 4-flexi random

        //spectrum upper and lowerbound should exclude control channel band
        double spectrumLowerBound @unit(GHz);
        double spectrumUpperBound @unit(GHz);
        double k = default(4.78); //constant for impairment model
        double transmitterPower @unit(dbm);
        double recieverSensitivity @unit(dbm);
        double attenuationConst @unit(db);
        double length @unit(km);
        bool reservationTimerEnabled = default(false);
        bool useExplicitRelease = default(false);
        bool enableImpairments = default(true);
        bool enablePriorityQueuing = default(true);
        int maxControlQueueLength = default(0);
        @display("i=block/rxtx");
            
        @signal[lostBurst](type=long);
        @signal[lostBCP](type=long);
        @signal[nackSentMuxAT]();
    gates:
        inout toNode;//to input node
        inout muxInOut[];//to next mux
}
