/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Interval Scheduling Maximization
 *  Level   : Intermediate
 * ============================================================================
 *
 *  PROBLEM: Given N intervals [start, end], find the maximum number of
 *           non-overlapping intervals.
 *
 *  GREEDY: Sort by end time. Pick earliest-ending that doesn't overlap.
 *  TIME: O(N log N)
 *
 *  VARIATIONS:
 *  - Max non-overlapping intervals → sort by end time, count compatible
 *  - Min intervals to remove (LC 435) → N - max_non_overlapping
 *  - Min arrows to burst balloons (LC 452) → same idea
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxNonOverlapping(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
        return a[1] < b[1];
    });

    int count = 1, lastEnd = intervals[0][1];
    for (int i = 1; i < (int)intervals.size(); i++) {
        if (intervals[i][0] >= lastEnd) {
            count++;
            lastEnd = intervals[i][1];
        }
    }
    return count;
}

// LC 435: Minimum removal = N - max non-overlapping
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;
    return (int)intervals.size() - maxNonOverlapping(intervals);
}

int main() {
    vector<vector<int>> intervals = {{1,2}, {2,3}, {3,4}, {1,3}};
    cout << "Max non-overlapping: " << maxNonOverlapping(intervals) << endl; // 3
    cout << "Min removals: " << eraseOverlapIntervals(intervals) << endl;    // 1
    return 0;
}

