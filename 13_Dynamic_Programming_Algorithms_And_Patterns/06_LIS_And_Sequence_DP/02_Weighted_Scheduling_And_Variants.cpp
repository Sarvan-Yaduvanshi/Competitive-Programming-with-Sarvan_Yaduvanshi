/*
 * ============================================================================
 *       WEIGHTED INTERVAL SCHEDULING & SEQUENCE DP VARIANTS
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Sequence DP — Weighted Scheduling, LDS, Box Stacking
 * Level   : ⭐⭐⭐ Advanced
 * ============================================================================
 *
 * 1. WEIGHTED INTERVAL SCHEDULING
 *    Given intervals with weights, find max weight non-overlapping set.
 *    Sort by end time. dp[i] = max weight using first i intervals.
 *    Binary search for last non-overlapping interval.
 *
 * 2. LONGEST DECREASING SUBSEQUENCE
 *    Mirror of LIS: find LDS.
 *
 * 3. BOX STACKING
 *    Given 3D boxes. Stack them (can rotate). Maximize height.
 *    Reduce to LIS on sorted base dimensions.
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// Weighted Interval Scheduling — O(n log n)
int weightedScheduling(vector<tuple<int,int,int>>& jobs) {
    // jobs = {start, end, weight}
    int n = jobs.size();
    sort(jobs.begin(), jobs.end(), [](auto& a, auto& b) {
        return get<1>(a) < get<1>(b);
    });

    vector<int> dp(n + 1, 0);
    vector<int> ends(n);
    for (int i = 0; i < n; i++) ends[i] = get<1>(jobs[i]);

    for (int i = 1; i <= n; i++) {
        auto [s, e, w] = jobs[i - 1];

        // Binary search: last job that ends before s
        int lo = 0, hi = i - 1, best = 0;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (mid == 0 || ends[mid - 1] <= s) {
                best = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        dp[i] = max(dp[i - 1], dp[best] + w);
    }
    return dp[n];
}

// Longest Decreasing Subsequence — O(n log n) using LIS on negated
int longestDecreasingSubseq(vector<int>& arr) {
    vector<int> tails;
    for (int x : arr) {
        int neg = -x;
        auto it = lower_bound(tails.begin(), tails.end(), neg);
        if (it == tails.end()) tails.push_back(neg);
        else *it = neg;
    }
    return tails.size();
}

// Box Stacking — O(n² after generating rotations)
struct Box {
    int l, w, h;  // length, width, height
};

int boxStacking(vector<Box>& boxes) {
    // Generate all rotations
    vector<Box> all;
    for (auto& b : boxes) {
        int dims[3] = {b.l, b.w, b.h};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == j) continue;
                int k = 3 - i - j;
                int base1 = max(dims[i], dims[j]);
                int base2 = min(dims[i], dims[j]);
                all.push_back({base1, base2, dims[k]});
            }
        }
    }

    // Remove duplicates
    sort(all.begin(), all.end(), [](auto& a, auto& b) {
        return a.l * a.w > b.l * b.w;  // Sort by base area descending
    });

    int n = all.size();
    vector<int> dp(n);
    for (int i = 0; i < n; i++) dp[i] = all[i].h;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (all[j].l > all[i].l && all[j].w > all[i].w) {
                dp[i] = max(dp[i], dp[j] + all[i].h);
            }
        }
    }
    return *max_element(dp.begin(), dp.end());
}

// Longest Chain of Pairs
// Given pairs (a,b), chain if b[i] < a[j]. Find longest chain.
int longestPairChain(vector<pair<int,int>>& pairs) {
    sort(pairs.begin(), pairs.end(), [](auto& a, auto& b) {
        return a.second < b.second;
    });

    int count = 1, lastEnd = pairs[0].second;
    for (int i = 1; i < (int)pairs.size(); i++) {
        if (pairs[i].first > lastEnd) {
            count++;
            lastEnd = pairs[i].second;
        }
    }
    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== SEQUENCE DP VARIANTS ===" << endl;

    // Weighted Interval Scheduling
    vector<tuple<int,int,int>> jobs = {
        {1, 3, 5}, {2, 5, 6}, {4, 6, 5}, {6, 7, 4}, {5, 8, 11}, {7, 9, 2}
    };
    cout << "\n--- Weighted Interval Scheduling ---" << endl;
    cout << "Max weight: " << weightedScheduling(jobs) << endl;

    // LDS
    vector<int> arr = {10, 22, 9, 33, 21, 50, 41, 60};
    cout << "\n--- Longest Decreasing Subsequence ---" << endl;
    cout << "LDS length: " << longestDecreasingSubseq(arr) << endl;

    // Box Stacking
    vector<Box> boxes = {{4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32}};
    cout << "\n--- Box Stacking ---" << endl;
    cout << "Max height: " << boxStacking(boxes) << endl;

    // Longest Pair Chain
    vector<pair<int,int>> pairs = {{1,2},{2,3},{3,4}};
    cout << "\n--- Longest Pair Chain ---" << endl;
    cout << "Length: " << longestPairChain(pairs) << endl;

    return 0;
}

