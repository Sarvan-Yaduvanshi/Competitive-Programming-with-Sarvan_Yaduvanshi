/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Activity Selection Problem (Complete)
 *  Level   : Beginner
 * ============================================================================
 *
 *  PROBLEM: Given N activities with start[i] and end[i], select the maximum
 *           number of non-overlapping activities.
 *
 *  GREEDY STRATEGY: Sort by end time, pick earliest-finishing compatible activity
 *
 *  TIME:  O(N log N) for sorting
 *  SPACE: O(1) extra
 *
 *  VARIATIONS:
 *  1. Maximum activities (basic) — sort by end time
 *  2. Minimum removal for non-overlapping (LC 435) — same as N - maxActivities
 *  3. Weighted activity selection — needs DP (not pure greedy)
 *  4. Activity selection with K persons (CSES Movie Festival II)
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// VARIATION 1: Max non-overlapping activities
int maxActivities(vector<pair<int,int>>& acts) {
    sort(acts.begin(), acts.end(), [](auto& a, auto& b) {
        return a.second < b.second;  // Sort by end time
    });

    int count = 1, lastEnd = acts[0].second;
    for (int i = 1; i < (int)acts.size(); i++) {
        if (acts[i].first >= lastEnd) {
            count++;
            lastEnd = acts[i].second;
        }
    }
    return count;
}

// VARIATION 2: Minimum removals for non-overlapping (LC 435)
int minRemovals(vector<pair<int,int>>& intervals) {
    return (int)intervals.size() - maxActivities(intervals);
}

// VARIATION 3: Print the selected activities
vector<pair<int,int>> selectActivities(vector<pair<int,int>>& acts) {
    sort(acts.begin(), acts.end(), [](auto& a, auto& b) {
        return a.second < b.second;
    });

    vector<pair<int,int>> selected;
    selected.push_back(acts[0]);
    int lastEnd = acts[0].second;

    for (int i = 1; i < (int)acts.size(); i++) {
        if (acts[i].first >= lastEnd) {
            selected.push_back(acts[i]);
            lastEnd = acts[i].second;
        }
    }
    return selected;
}

int main() {
    vector<pair<int,int>> activities = {{1,4}, {3,5}, {0,6}, {5,7}, {3,9}, {5,9}, {6,10}, {8,11}, {8,12}, {2,14}, {12,16}};

    cout << "Max activities: " << maxActivities(activities) << endl;

    auto selected = selectActivities(activities);
    cout << "Selected: ";
    for (auto& [s, e] : selected) cout << "(" << s << "," << e << ") ";
    cout << endl;

    return 0;
}

