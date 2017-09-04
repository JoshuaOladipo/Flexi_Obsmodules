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

#include "FibreTable.h"

Define_Module(FibreTable);

void FibreTable::initialize()
{
    cleanUpInterval = par("cleanUpInterval");
    maxContainerSize = par("maxContainerSize");

    cleanUpTimer = new cMessage("cleanUp");
    scheduleAt(cleanUpInterval, cleanUpTimer);

    longestDuration = SIMTIME_ZERO;

    transmissions.setTakeOwnership(true);

    infiniteContainerSize = maxContainerSize == 0;

    WATCH(longestDuration);
}

void FibreTable::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
        cleanUp();
        scheduleAt(simTime()+cleanUpInterval, cleanUpTimer);
        return;
    }

    TransmissionEntry* entry = check_and_cast<TransmissionEntry*>(msg);
    transmissions.add(entry);
    simtime_t duration = entry->getEndTime() - entry->getStartTime();

    if(longestDuration < duration)
        longestDuration = duration;

    if(entry->getSender() == Mux::Left)
    {
        leftStartTimeIndex[entry->getStartTime()].push_back(entry);//map creates new entry with key, if key not found
        leftEndTimeIndex[entry->getEndTime()].push_back(entry);
    }else{
        rightStartTimeIndex[entry->getStartTime()].push_back(entry);
        rightEndTimeIndex[entry->getEndTime()].push_back(entry);
    }

    EV_INFO << "transmission entry starTime = " << entry->getStartTime() << "endTime= " << entry->getEndTime() << " spectrumCenter = " << entry->getSpectrumCenter() << endl;

    if(!infiniteContainerSize && transmissions.size() > maxContainerSize)
        cleanUp();
}

const vector<TransmissionEntry*> FibreTable::getEntriesWithStartTime(Mux sender, simtime_t startTime)
{
    if(sender == Mux::Left)
        return leftStartTimeIndex[startTime];
    else return leftStartTimeIndex[startTime];

}

set<TransmissionEntry*>* FibreTable::getEntriesBetweenTimes(Mux sender, simtime_t startTime, simtime_t endTime)
{
    set<TransmissionEntry*> *temp = new set<TransmissionEntry*>();

    map<simtime_t,vector<TransmissionEntry*>>::iterator itlowStart,itupStart, itlowEnd, itupEnd;

    if(sender == Mux::Left && leftStartTimeIndex.size() != 0)
    {
        itlowStart = leftStartTimeIndex.lower_bound(startTime);
        itupStart = leftStartTimeIndex.upper_bound(endTime);
        itlowEnd = leftEndTimeIndex.lower_bound(startTime);
        itupEnd = leftEndTimeIndex.upper_bound(endTime);
    }else if(sender == Mux::Right && rightStartTimeIndex.size() != 0){
        itlowStart = rightStartTimeIndex.lower_bound(startTime);
        itupStart = rightStartTimeIndex.upper_bound(endTime);
        itlowEnd = rightEndTimeIndex.lower_bound(startTime);
        itupEnd = rightEndTimeIndex.upper_bound(endTime);
    }else return temp;

    for(map<simtime_t,vector<TransmissionEntry*>>::iterator it=itlowStart; it!=itupStart; it++)
    {
        if(it->first == endTime)//do not consider entries starting exactly at endtime of transmission being considered
            continue;

        temp->insert(it->second.begin(),it->second.end());
    }

    for(map<simtime_t,vector<TransmissionEntry*>>::iterator it=itlowEnd; it!=itupEnd; it++)
    {
        if(it->first == startTime) //do not consider entries ending exactly at startTime of transmission being considered
            continue;

        temp->insert(it->second.begin(),it->second.end());
    }

    return temp;
}

void FibreTable::cleanUp()
{
    map<simtime_t,vector<TransmissionEntry*>>::iterator itl = leftEndTimeIndex.begin();
    map<simtime_t,vector<TransmissionEntry*>>::iterator itr = rightEndTimeIndex.begin();
    map<simtime_t,vector<TransmissionEntry*>>::iterator temp;
    set<simtime_t> startTimes;

    if(longestDuration < 0)
        return;

    simtime_t timePast = simTime() - longestDuration;

    if(timePast < SIMTIME_ZERO)
        return;

    while(itl != leftEndTimeIndex.end()){
        if(itl->first < timePast)
        {
            vector<TransmissionEntry*> vec = (*itl).second;
            int size = vec.size();
            for(int i = 0; i < size; i++){
                startTimes.insert(vec[i]->getStartTime());
                cObject *obj =  transmissions.remove(vec[i]);
                delete(obj);
            }

            temp = itl;
            ++itl;

            leftEndTimeIndex.erase(temp);
        }else break;
    }


    while(itr != rightEndTimeIndex.end()){
           if(itr->first < timePast)
           {
               vector<TransmissionEntry*> vec = (*itr).second;
               int size = vec.size();
               for(int i = 0; i < size; i++){
                   startTimes.insert(vec[i]->getStartTime());
                   cObject *obj =  transmissions.remove(vec[i]);
                   delete(obj);
               }

               temp = itr;
               ++itr;

               rightEndTimeIndex.erase(temp);
           }else break;
       }

    for(set<simtime_t>::iterator its = startTimes.begin(); its != startTimes.end(); its++)
    {
        leftStartTimeIndex.erase((*its));
        rightStartTimeIndex.erase((*its));
    }

}

/*interesting code for accessing maps from http://stackoverflow.com/questions/8960550/c-mapstring-vectorchar-access
 *
 * string key = "something";
char ch = 'a'; // the character you want to append

map<string, vector<char> >::iterator itr = myMap.find(key);
if(itr != myMap.end())
{
    vector<char> &v = itr->second;
    v.push_back(ch);
}
 */

//map<double,vector<TransmissionEntry*>>::iterator itl = leftEndTimeIndex.begin();
//   map<double,vector<TransmissionEntry*>>::iterator itr = rightEndTimeIndex.begin();
//   map<double,vector<TransmissionEntry*>>::iterator temp;
//   set<double> startTimes;
//
//   if(longestDuration < 0)
//       return;
//
//   int timePast = simTime().dbl() - longestDuration;
//
//   if(timePast < 0)
//       return;
//
//   while(itl != leftEndTimeIndex.end()){
//       if(itl->first < timePast)
//       {
//           vector<TransmissionEntry*> vec = (*itl).second;
//           int size = vec.size();
//           for(int i = 0; i < size; i++)
//               allReadyToBeDeleted = allReadyToBeDeleted && vec[i]->getReadyForDeletion();
//
//           if(allReadyToBeDeleted){
//               temp = itl;
//               ++itl;
//
//               for(int i =0; i < size; i++)
//                   transmissions.remove((*temp).second[i]);
//
//               leftEndTimeIndex.erase(temp);
//           }
//
//       }else break;
//   }
//
//   while(itr != rightEndTimeIndex.end()){
//       if(itr->first < simTime().dbl())
//       {
//           bool allReadyToBeDeleted = true;
//           vector<TransmissionEntry*> vec = (*itl).second;
//           int size = vec.size();
//           for(int i = 0; i < size; i++)
//               allReadyToBeDeleted = allReadyToBeDeleted && vec[i]->getReadyForDeletion();
//
//           if(allReadyToBeDeleted){
//               temp = itr;
//               ++itr;
//
//               for(int i =0; i < size; i++)
//                   transmissions.remove((*temp).second[i]);
//
//               rightEndTimeIndex.erase(temp);
//           }
//
//       }else break;
//   }
