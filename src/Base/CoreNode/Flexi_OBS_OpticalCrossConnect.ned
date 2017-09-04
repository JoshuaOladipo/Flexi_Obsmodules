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
// Interconnection point where optical bursts pass through transparently. OBS_CoreControlLogic is the responsible of setting/unsetting lightpaths.
//
simple Flexi_OBS_OpticalCrossConnect
{
    parameters:
        double switchingDelay @unit(s) = default(0); // Time between switching request and the time where connection is available
        double spectrumLowerBound @unit(GHz);
        double spectrumUpperBound @unit(GHz);
        double BCPProcessingDelay @unit(s) = default(0);
        
         @signal[lostBurst](type=long);
    gates:
        input inInput;
        input inControl;
        output out[];
}
