/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Weighted Job Scheduling — The Greedy → DP Bridge
 *  Level   : Expert
 * ============================================================================
 *
 *  PROBLEM (LC 1235): N jobs with [start, end, profit].
 *  Select non-overlapping jobs to maximize total profit.
 *
 *  WHY GREEDY ALONE FAILS:
 *  With different profits, sorting by end time and picking greedily
 *  may skip a high-profit job. Need DP.
 *
 *  APPROACH: Sort by end time. DP + Binary Search.
 *  dp[i] = max profit considering first i jobs
 *  dp[i] = max(dp[i-1], profit[i] + dp[last_non_overlapping_job])
 *
 *  Use binary search to find last_non_overlapping_job efficiently.
 *
 *  TIME:  O(N log N)
 *  SPACE: O(N)
 *
 *  THIS IS THE BRIDGE: When weights/profits differ, pure greedy fails → DP.
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
    int n = startTime.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);

    // Sort by end time
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return endTime[a] < endTime[b];
    });

    // dp[i] = max profit using first i+1 jobs (sorted)
    vector<int> dp(n);
    vector<int> ends(n); // Sorted end times for binary search

    for (int i = 0; i < n; i++) ends[i] = endTime[idx[i]];

    dp[0] = profit[idx[0]];

    for (int i = 1; i < n; i++) {
        int curStart = startTime[idx[i]];
        int curProfit = profit[idx[i]];

        // Binary search for last job ending at or before curStart
        int lo = 0, hi = i - 1, best = -1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (ends[mid] <= curStart) {
                best = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        int incl = curProfit + (best >= 0 ? dp[best] : 0);
        dp[i] = max(dp[i - 1], incl);
    }

    return dp[n - 1];
}

int main() {
    vector<int> start = {1, 2, 3, 3};
    vector<int> end   = {3, 4, 5, 6};
    vector<int> profit = {50, 10, 40, 70};

    cout << "Max profit: " << jobScheduling(start, end, profit) << endl; // 120

    vector<int> start2 = {1, 2, 3, 4, 6};
    vector<int> end2   = {3, 5, 10, 6, 9};
    vector<int> profit2 = {20, 20, 100, 70, 60};

    cout << "Max profit: " << jobScheduling(start2, end2, profit2) << endl; // 150

    return 0;
}

