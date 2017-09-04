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
channelinterface SpectrumChannelInterface
{
    bool isControl;
    bool isDatarateChannel;
    volatile double assignedSpectrumCenter @unit(GHz);
    volatile double assignedSpectrumLowerBound @unit(GHz);
    volatile double assignedSpectrumUpperBound @unit(GHz);
    double weight @unit(km); //used for initial setup when finding shortest paths, to set weight of links
    volatile string modulationScheme;
    volatile bool inUseLeft; //neccessary to prevent both sides from sending over same channel object at the same time, allowing reuse of object
    volatile bool inUseRight;
    volatile bool leftReservationSuccessful;
    volatile bool rightReservationSuccessful;
}
