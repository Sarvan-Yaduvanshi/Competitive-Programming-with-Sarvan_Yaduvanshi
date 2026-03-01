/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Interval Scheduling — All Variants
 *  Level   : Expert
 * ============================================================================
 *
 *  ▶ VARIANT 1: Max Non-Overlapping Intervals
 *     Sort by end time, greedily pick earliest ending.  O(N log N)
 *
 *  ▶ VARIANT 2: Min Intervals to Remove (LC 435)
 *     = N - max_non_overlapping.   O(N log N)
 *
 *  ▶ VARIANT 3: Min Arrows to Burst Balloons (LC 452)
 *     Sort by end, shoot at end of first unpopped.  O(N log N)
 *
 *  ▶ VARIANT 4: Max Length of Pair Chain (LC 646)
 *     Same as activity selection — sort by second element.  O(N log N)
 *
 *  ▶ VARIANT 5: Remove Covered Intervals (LC 1288)
 *     Sort by start asc, end desc. Count non-covered. O(N log N)
 *
 *  ▶ VARIANT 6: Count Ways to Group Overlapping Ranges (LC 2580)
 *     Merge overlapping, answer = 2^(number_of_groups) mod 10^9+7
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// VARIANT 1: Max non-overlapping
int maxNonOverlapping(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
        return a[1] < b[1];
    });
    int count = 0, lastEnd = INT_MIN;
    for (auto& iv : intervals) {
        if (iv[0] >= lastEnd) {
            count++;
            lastEnd = iv[1];
        }
    }
    return count;
}

// VARIANT 3: Min arrows (LC 452)
int findMinArrowShots(vector<vector<int>>& points) {
    sort(points.begin(), points.end(), [](auto& a, auto& b) {
        return a[1] < b[1];
    });
    int arrows = 1;
    long long arrowPos = points[0][1];
    for (int i = 1; i < (int)points.size(); i++) {
        if (points[i][0] > arrowPos) {
            arrows++;
            arrowPos = points[i][1];
        }
    }
    return arrows;
}

// VARIANT 4: Max pair chain (LC 646)
int findLongestChain(vector<vector<int>>& pairs) {
    sort(pairs.begin(), pairs.end(), [](auto& a, auto& b) {
        return a[1] < b[1];
    });
    int count = 1, lastEnd = pairs[0][1];
    for (int i = 1; i < (int)pairs.size(); i++) {
        if (pairs[i][0] > lastEnd) { // Strict inequality for pairs
            count++;
            lastEnd = pairs[i][1];
        }
    }
    return count;
}

// VARIANT 5: Remove covered intervals (LC 1288)
int removeCoveredIntervals(vector<vector<int>>& intervals) {
    // Sort: start asc, end desc (so longer intervals come first for same start)
    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
        return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
    });
    int count = 0, maxEnd = 0;
    for (auto& iv : intervals) {
        if (iv[1] > maxEnd) {
            count++;
            maxEnd = iv[1];
        }
    }
    return count;
}

int main() {
    // Variant 1
    vector<vector<int>> iv1 = {{1,2},{2,3},{3,4},{1,3}};
    cout << "Max non-overlapping: " << maxNonOverlapping(iv1) << endl; // 3

    // Variant 3
    vector<vector<int>> iv3 = {{10,16},{2,8},{1,6},{7,12}};
    cout << "Min arrows: " << findMinArrowShots(iv3) << endl; // 2

    // Variant 4
    vector<vector<int>> iv4 = {{1,2},{2,3},{3,4}};
    cout << "Max chain: " << findLongestChain(iv4) << endl; // 2

    // Variant 5
    vector<vector<int>> iv5 = {{1,4},{3,6},{2,8}};
    cout << "After removing covered: " << removeCoveredIntervals(iv5) << endl; // 2

    return 0;
}

