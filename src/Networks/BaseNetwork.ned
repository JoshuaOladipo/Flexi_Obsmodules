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

package obsmodules.src.Networks;

network BaseNetwork
{
    parameters:
        @statistic[BurstLost](source=lostBurst; record=last,vector,vector(count));//1-failed reservation oxc, 2-failed reservation mux, 3- impairments, 4 - arrived at wrong destination
        @statistic[BCPLost](source=lostBCP; record=vector);//1-bcp lost due to contention, 2-bcp dropped by queue, 3-bcp lost impairments, 4-offset finished
        @statistic[BurstSent](source=count(sentBurst); record=last,vector);
        @statistic[BurstSuccess](source=count(successfulBurst); record=last,vector);
        @statistic[BurstLossRatio](source=count(lostBurst)/count(sentBurst); record=last,vector);
        @statistic[EndToEndAcksFromMux](source=nackSentMuxAT; record=count);
}
