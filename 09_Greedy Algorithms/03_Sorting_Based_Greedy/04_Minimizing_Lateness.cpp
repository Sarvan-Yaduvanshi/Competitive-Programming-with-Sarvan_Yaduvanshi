/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Minimizing Lateness — Earliest Deadline First
 *  Level   : Intermediate
 * ============================================================================
 *
 *  PROBLEM: N jobs, each with processing time p[i] and deadline d[i].
 *           Schedule on a single machine to minimize MAXIMUM lateness.
 *           Lateness of job i = max(0, finish_time[i] - d[i])
 *
 *  GREEDY: Sort by deadline (ascending) — Earliest Deadline First (EDF)
 *  PROOF: Exchange argument — any inversion can be fixed without increasing max lateness
 *  TIME: O(N log N)
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minimizeLateness(vector<pair<int,int>>& jobs) {
    // jobs[i] = {processing_time, deadline}
    sort(jobs.begin(), jobs.end(), [](auto& a, auto& b) {
        return a.second < b.second; // EDF: sort by deadline
    });

    int currentTime = 0, maxLateness = 0;
    for (auto& [p, d] : jobs) {
        currentTime += p;
        maxLateness = max(maxLateness, currentTime - d);
    }
    return maxLateness;
}

int main() {
    vector<pair<int,int>> jobs = {{3,6}, {2,8}, {1,9}, {4,9}, {3,14}, {2,15}};
    cout << "Min max lateness: " << minimizeLateness(jobs) << endl; // 1
    return 0;
}

