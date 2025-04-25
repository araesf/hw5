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

// type for the ID of a worker
typedef unsigned int Worker_T;

// n-by-k Matrix of each of the k workers' availability over an n-day period

typedef std::vector<std::vector<bool>> AvailabilityMatrix;

// n-by-d matrix with the d worker IDs who are scheduled 
// to work on each of the n days
typedef std::vector<std::vector<Worker_T> > DailySchedule;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here
bool schedule_bt(const AvailabilityMatrix& avail, const size_t dailyNeed, 
const size_t maxShifts, DailySchedule& sched, vector<int>& workerFreq, int col, int row) {

	if (row == avail.size()) {
		return true;
	}

	if (col == dailyNeed) {
		return schedule_bt(avail, dailyNeed, maxShifts, sched, workerFreq, 0, row + 1);
	}

	// i is the given worker
	for (int i = 0; i < avail[0].size(); i++) {
		// if worker is available and hasnt achieved maxShifts yet
		if (avail[row][i] == true && workerFreq[i] < maxShifts) {
			workerFreq[i]++;
			sched[row][col] = i;

			// with the current selection, test if true. if row == avail.size(), return true, else undo
			if (schedule_bt(avail, dailyNeed, maxShifts, sched, workerFreq, col + 1, row)) {
				return true;
			}

			// undo
			workerFreq[i]--;
		}
	}

	return false;
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
		int row = 0;
		int col = 0;
		vector<int> workerFreq(avail[0].size(), 0);

		// populate schedule 2D
		for (int r = 0; r < avail.size(); r++) {
			vector<Worker_T> curr_day;
			for (int c = 0; c < dailyNeed; c++) {
				curr_day.push_back(INVALID_ID);
			}

			sched.push_back(curr_day);
		}

	return schedule_bt(avail, dailyNeed, maxShifts, sched, workerFreq, col, row);
}