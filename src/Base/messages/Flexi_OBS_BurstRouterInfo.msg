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

//
// TODO generated message class
//
class Flexi_OBS_BurstRouterInfo {
      int burstId = -1; // Internal burst Id used only by router module. This is independent for any other Id.
      int burstifierId = -1; // Burstifier Id. Part of burst identifier.
      int numSeq = -1; // Sequence number. The other part of burst identifier.
      double assignedSpectrumCenter = -1;
      double aSsignedSpectrumLowerBound = -1;
      double assignedSpectrumUpperBund = -1;
      int label = -1; // Destination label.
      int ACO_RouteId = -1;
      //simtime_t time; // Message creation timestamp. Used to insert into BCP's sender queue.
      //int senderId;
      //string route;
}
