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
simple Flexi_OBS_PacketBurstifier
{
      parameters:
        int assembly = default(0); //0 - for mixed, 1 for time based and 2 for size based
        double timeout @unit(s) = default(1s); // Burstifier's timeout. If reached, burst will be assembled with the current content of the queue.
        int maxSize @unit(B) = default(15000B); // Burst maximum size.
        int numPackets = default(0); // Maximum number of packets.
        int minSizeWithPadding @unit(B) = default(1500B); // Minimum size a burst should have. If not reached, will be filled until this value. If 0, no padding will be done.
        bool overflowLastPacket = default(false); // If true, allows the last packet to enter the burst even if size is exceeded by that. If false, burst will be assembled and the current message will be inserted as the first message of the next burst.
        int cteHeader @unit(B) = default(20B); // Burst header size.
        int varHeader @unit(B) = default(2B); // Header added for each message inside the burst.
        bool includeMsgsInBurst = default(true);
        @signal[queueAssembled](type=QueueAssignment);
    gates:
        input in;
        output out;
}
