/*
 * ============================================================================
 *              0/1 KNAPSACK & VARIANTS
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Knapsack DP — 0/1 Knapsack, Subset Sum, Partition
 * Level   : ⭐⭐ Intermediate
 * ============================================================================
 *
 * 0/1 KNAPSACK:
 *   Given n items with weight[] and value[], capacity W.
 *   Maximize value without exceeding capacity. Each item used at most once.
 *   dp[i][w] = max value using first i items with capacity w
 *   dp[i][w] = max(dp[i-1][w], dp[i-1][w-wt[i]] + val[i])
 *
 * SUBSET SUM:
 *   Can we pick a subset with exact sum S?
 *   dp[i][s] = can first i elements make sum s?
 *
 * EQUAL PARTITION:
 *   Can we split array into two subsets with equal sum?
 *   → Reduce to subset sum with target = totalSum/2
 *
 * TARGET SUM:
 *   Assign +/- to each element to reach target.
 *   → Reduce to subset sum: find subset with sum = (totalSum + target) / 2
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// 0/1 Knapsack — Space Optimized O(W)
int knapsack01(vector<int>& wt, vector<int>& val, int W) {
    int n = wt.size();
    vector<int> dp(W + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int w = W; w >= wt[i]; w--) {  // BACKWARD for 0/1
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
        }
    }
    return dp[W];
}

// Subset Sum — Can we make exact sum?
bool subsetSum(vector<int>& nums, int target) {
    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int num : nums) {
        for (int s = target; s >= num; s--) {
            dp[s] = dp[s] || dp[s - num];
        }
    }
    return dp[target];
}

// Count Subsets with Sum (number of ways)
int countSubsetSum(vector<int>& nums, int target) {
    vector<int> dp(target + 1, 0);
    dp[0] = 1;

    for (int num : nums) {
        for (int s = target; s >= num; s--) {
            dp[s] += dp[s - num];
        }
    }
    return dp[target];
}

// Partition Equal Subset Sum (LeetCode 416)
bool canPartition(vector<int>& nums) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (total % 2 != 0) return false;
    return subsetSum(nums, total / 2);
}

// Minimum Subset Sum Difference
int minSubsetDiff(vector<int>& nums) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    int half = total / 2;

    vector<bool> dp(half + 1, false);
    dp[0] = true;

    for (int num : nums)
        for (int s = half; s >= num; s--)
            dp[s] = dp[s] || dp[s - num];

    // Find largest achievable sum <= half
    for (int s = half; s >= 0; s--) {
        if (dp[s]) return total - 2 * s;
    }
    return total;
}

// Target Sum (LeetCode 494)
// Assign + or - to each num to reach target
// Let P = sum of positive, N = sum of negative
// P - N = target, P + N = total → P = (total + target) / 2
int targetSum(vector<int>& nums, int target) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if ((total + target) % 2 != 0 || total + target < 0) return 0;

    int sum = (total + target) / 2;
    vector<int> dp(sum + 1, 0);
    dp[0] = 1;

    for (int num : nums) {
        for (int s = sum; s >= num; s--) {
            dp[s] += dp[s - num];
        }
    }
    return dp[sum];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== KNAPSACK DP FAMILY ===" << endl;

    // 0/1 Knapsack
    vector<int> wt = {1, 3, 4, 5}, val = {1, 4, 5, 7};
    int W = 7;
    cout << "\n--- 0/1 Knapsack ---" << endl;
    cout << "Max value: " << knapsack01(wt, val, W) << endl;

    // Subset Sum
    vector<int> arr = {3, 34, 4, 12, 5, 2};
    cout << "\n--- Subset Sum ---" << endl;
    cout << "Sum 9: " << (subsetSum(arr, 9) ? "YES" : "NO") << endl;
    cout << "Sum 30: " << (subsetSum(arr, 30) ? "YES" : "NO") << endl;

    // Count subsets
    vector<int> arr2 = {1, 2, 3, 3};
    cout << "\n--- Count Subsets with Sum ---" << endl;
    cout << "Sum 6: " << countSubsetSum(arr2, 6) << " ways" << endl;

    // Equal Partition
    vector<int> arr3 = {1, 5, 11, 5};
    cout << "\n--- Equal Partition ---" << endl;
    cout << "Can partition: " << (canPartition(arr3) ? "YES" : "NO") << endl;

    // Min Subset Diff
    vector<int> arr4 = {1, 6, 11, 5};
    cout << "\n--- Min Subset Difference ---" << endl;
    cout << "Min diff: " << minSubsetDiff(arr4) << endl;

    // Target Sum
    vector<int> arr5 = {1, 1, 1, 1, 1};
    cout << "\n--- Target Sum ---" << endl;
    cout << "Target 3: " << targetSum(arr5, 3) << " ways" << endl;

    return 0;
}

