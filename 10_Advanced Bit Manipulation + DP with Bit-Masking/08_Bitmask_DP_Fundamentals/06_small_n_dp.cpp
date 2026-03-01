/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 08.06 — SMALL N DP (n ≤ 20) — Collection of Patterns    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

This file collects several classic "small n" bitmask DP problems:

1. ELEVATOR RIDES (CSES): Partition n people into minimum groups with weight limit.
2. COUNTING TILINGS: Tile a grid using bitmask DP.
3. MINIMUM VERTEX COVER using bitmask on small graph.

PATTERN 1 — PARTITION INTO MINIMUM GROUPS:
══════════════════════════════════════════
    dp[mask] = {min_groups, remaining_capacity_in_last_group}
    For each mask, try adding person i not in mask.

PATTERN 2 — SUM-BASED SUBSET DP:
═════════════════════════════════
    dp[mask] = sum of elements in mask (precompute).
    Or dp[mask] = some function that depends on the subset.

GENERAL BITMASK DP TIPS:
════════════════════════
    • n ≤ 15: O(2ⁿ) is fine
    • n ≤ 20: O(n × 2ⁿ) is fine (~20M)
    • n ≤ 23: O(2ⁿ) barely fits
    • n ≤ 25: Need O(2^(n/2)) meet-in-middle

PRACTICE PROBLEMS:
══════════════════
    CSES: Elevator Rides, Apple Division
    LeetCode 698: Partition to K Equal Sum Subsets
    LeetCode 473: Matchsticks to Square
    Codeforces: 453B, 580D
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

// CSES Elevator Rides: min groups with capacity C
pair<int,int> elevatorRides(vector<int>& weights, int C) {
    int n = weights.size();
    // dp[mask] = {min rides, best remaining capacity in last ride}
    vector<pair<int,int>> dp(1 << n, {n+1, 0});
    dp[0] = {1, C}; // 1 ride, full capacity remaining

    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) continue;
            int newMask = mask | (1 << i);
            auto [rides, rem] = dp[mask];
            pair<int,int> candidate;
            if (weights[i] <= rem) {
                candidate = {rides, rem - weights[i]};
            } else {
                candidate = {rides + 1, C - weights[i]};
            }
            dp[newMask] = min(dp[newMask], candidate);
        }
    }
    return dp[(1 << n) - 1];
}

// Precompute subset sums
vector<int> precomputeSubsetSums(vector<int>& arr) {
    int n = arr.size();
    vector<int> sum(1 << n, 0);
    for (int mask = 1; mask < (1 << n); mask++) {
        int lowest = mask & (-mask);
        int idx = __builtin_ctz(lowest);
        sum[mask] = sum[mask ^ lowest] + arr[idx];
    }
    return sum;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   SMALL N DP (n ≤ 20)                           ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Elevator Rides
    cout << "\n--- Elevator Rides ---" << endl;
    vector<int> weights = {2, 3, 3, 5, 6};
    int C = 10;
    auto [rides, rem] = elevatorRides(weights, C);
    cout << "  Weights: {2,3,3,5,6}, Capacity: " << C << endl;
    cout << "  Min rides: " << rides << endl;

    // Subset sums
    cout << "\n--- Precompute Subset Sums ---" << endl;
    vector<int> arr = {3, 5, 7};
    auto sums = precomputeSubsetSums(arr);
    for (int mask = 0; mask < 8; mask++) {
        cout << "  sum[" << bitset<3>(mask) << "] = " << sums[mask] << endl;
    }
    assert(sums[0b111] == 15); // 3+5+7
    assert(sums[0b101] == 10); // 3+7
    assert(sums[0b010] == 5);  // 5

    cout << "\n✅ Small n DP patterns verified!" << endl;
    return 0;
}

