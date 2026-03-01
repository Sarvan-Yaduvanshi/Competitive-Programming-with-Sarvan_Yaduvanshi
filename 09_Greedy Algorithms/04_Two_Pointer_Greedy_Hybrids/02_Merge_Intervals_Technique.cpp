/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Merge Intervals Technique
 *  Level   : Intermediate
 * ============================================================================
 *
 *  PROBLEM: Given a collection of intervals, merge all overlapping intervals.
 *  GREEDY: Sort by start time, merge greedily when overlap detected.
 *
 *  VARIATIONS:
 *  1. Merge Intervals (LC 56) — merge overlapping
 *  2. Insert Interval (LC 57) — insert and merge
 *  3. Interval List Intersections (LC 986) — find intersections
 *
 *  TIME: O(N log N) for sorting
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// LC 56: Merge Intervals
vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> merged;

    for (auto& iv : intervals) {
        if (merged.empty() || merged.back()[1] < iv[0]) {
            merged.push_back(iv);  // No overlap → add new interval
        } else {
            merged.back()[1] = max(merged.back()[1], iv[1]);  // Merge
        }
    }
    return merged;
}

// LC 57: Insert Interval
vector<vector<int>> insertInterval(vector<vector<int>>& intervals, vector<int>& newIv) {
    vector<vector<int>> result;
    int i = 0, n = intervals.size();

    // Add all intervals ending before newInterval starts
    while (i < n && intervals[i][1] < newIv[0])
        result.push_back(intervals[i++]);

    // Merge overlapping intervals with newInterval
    while (i < n && intervals[i][0] <= newIv[1]) {
        newIv[0] = min(newIv[0], intervals[i][0]);
        newIv[1] = max(newIv[1], intervals[i][1]);
        i++;
    }
    result.push_back(newIv);

    // Add remaining intervals
    while (i < n)
        result.push_back(intervals[i++]);

    return result;
}

// LC 986: Interval List Intersections
vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
    vector<vector<int>> result;
    int i = 0, j = 0;

    while (i < (int)A.size() && j < (int)B.size()) {
        int lo = max(A[i][0], B[j][0]);
        int hi = min(A[i][1], B[j][1]);
        if (lo <= hi) result.push_back({lo, hi});

        // Advance the pointer with the smaller end time
        if (A[i][1] < B[j][1]) i++;
        else j++;
    }
    return result;
}

int main() {
    vector<vector<int>> intervals = {{1,3}, {2,6}, {8,10}, {15,18}};
    auto merged = mergeIntervals(intervals);
    cout << "Merged: ";
    for (auto& iv : merged) cout << "[" << iv[0] << "," << iv[1] << "] ";
    cout << endl; // [1,6] [8,10] [15,18]

    return 0;
}

