#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool assignment(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& shifts,
    size_t myDay,
    size_t mySlot);

// Add your implementation of schedule() and other helper functions here
bool assignment(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& shifts,
    size_t myDay,
    size_t mySlot) {
        // total workers and days initialize
        size_t workers = avail[0].size();
        size_t days = avail.size();
        
        //all days scheduled
        if (myDay==days) {
            return true;
        }
        // all slots fileld already
        if (mySlot==dailyNeed) {
            return assignment(avail,dailyNeed,maxShifts,sched,shifts,myDay+1,0);
        }
        // see each worker to assign to slot or day
        for (Worker_T i=0;i<workers;++i) {
            if (avail[myDay][i]&&shifts[i]<static_cast<int>(maxShifts)) {
                if (find(sched[myDay].begin(),sched[myDay].end(),i)!=sched[myDay].end()) {
                    continue; // skip worker if alr assigned
                }
                sched[myDay][mySlot]=i;
                shifts[i]++;// assign and increment
                //recursion
                if (assignment(avail,dailyNeed,maxShifts,sched,shifts,myDay,mySlot+1)) {
                    return true;
                }
                sched[myDay][mySlot]=INVALID_ID;
                shifts[i]--;// backtracking step

            }
        }
        return false;// no worker found
    }

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    size_t workers = avail[0].size();// workers total
    size_t days = avail.size();// days total

    // initialize schedule with empty
    sched=DailySchedule(days,std::vector<Worker_T>(dailyNeed,INVALID_ID));
    // shift count vector to track for each worker
    vector<int> shiftCount(workers,0);
    // recursion step
    return assignment(avail,dailyNeed,maxShifts,sched,shiftCount,0,0);


    




}

