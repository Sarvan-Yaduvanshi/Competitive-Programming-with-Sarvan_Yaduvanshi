/*
 * ============================================================================
 *                  RECURSION TO MEMOIZATION (Top-Down DP)
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : DP Foundations — Converting Recursion to Memoization
 * Level   : ⭐ Beginner
 * ============================================================================
 *
 * THE DP CONVERSION PIPELINE:
 * ============================
 *
 *  Step 1: Write brute-force RECURSION
 *           ↓
 *  Step 2: Identify OVERLAPPING SUBPROBLEMS (same calls repeated)
 *           ↓
 *  Step 3: Add MEMOIZATION (cache/store results)
 *           ↓
 *  Step 4: Convert to TABULATION (bottom-up) [optional]
 *           ↓
 *  Step 5: SPACE OPTIMIZE [optional]
 *
 * MEMOIZATION TECHNIQUE:
 * =======================
 * - Use a hashmap or array to store computed results
 * - Before computing, CHECK if already stored
 * - After computing, STORE the result
 * - This turns exponential → polynomial
 *
 * TEMPLATE:
 *   int solve(state) {
 *       if (base_case) return base_value;
 *       if (memo[state] != -1) return memo[state];  // CHECK
 *       int result = /* recursive formula */;
 *       return memo[state] = result;                  // STORE
 *   }
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * EXAMPLE 1: Minimum Cost Climbing Stairs (LeetCode 746)
 * --------------------------------------------------------
 * Given: cost[] array, you can start from step 0 or 1
 * Each step, pay cost[i] and climb 1 or 2 steps
 * Find: minimum cost to reach the top
 *
 * State:    dp[i] = minimum cost to reach step i
 * Transition: dp[i] = cost[i] + min(dp[i-1], dp[i-2])
 * Base:     dp[0] = cost[0], dp[1] = cost[1]
 * Answer:   min(dp[n-1], dp[n-2])  — can reach top from last or second-last
 */

// STEP 1: Pure Recursion — O(2^n)
int minCost_recursive(vector<int>& cost, int i) {
    if (i < 0) return 0;
    if (i == 0 || i == 1) return cost[i];
    return cost[i] + min(minCost_recursive(cost, i - 1),
                         minCost_recursive(cost, i - 2));
}

// STEP 2: Add Memoization — O(n)
int minCost_memo(vector<int>& cost, int i, vector<int>& dp) {
    if (i < 0) return 0;
    if (i == 0 || i == 1) return cost[i];
    if (dp[i] != -1) return dp[i];  // Already computed

    dp[i] = cost[i] + min(minCost_memo(cost, i - 1, dp),
                          minCost_memo(cost, i - 2, dp));
    return dp[i];
}

// STEP 3: Tabulation — O(n)
int minCost_tabulation(vector<int>& cost) {
    int n = cost.size();
    vector<int> dp(n);
    dp[0] = cost[0];
    dp[1] = cost[1];

    for (int i = 2; i < n; i++) {
        dp[i] = cost[i] + min(dp[i - 1], dp[i - 2]);
    }
    return min(dp[n - 1], dp[n - 2]);
}

// STEP 4: Space Optimized — O(1) space
int minCost_optimized(vector<int>& cost) {
    int n = cost.size();
    int prev2 = cost[0], prev1 = cost[1];

    for (int i = 2; i < n; i++) {
        int curr = cost[i] + min(prev1, prev2);
        prev2 = prev1;
        prev1 = curr;
    }
    return min(prev1, prev2);
}

/*
 * EXAMPLE 2: Count ways to reach nth stair (Climbing Stairs)
 * -----------------------------------------------------------
 * State:     dp[i] = number of ways to reach step i
 * Transition: dp[i] = dp[i-1] + dp[i-2]
 * Base:      dp[0] = 1, dp[1] = 1
 */

// STEP 1: Recursion — O(2^n)
int climbStairs_rec(int n) {
    if (n <= 1) return 1;
    return climbStairs_rec(n - 1) + climbStairs_rec(n - 2);
}

// STEP 2: Memoization — O(n)
int climbStairs_memo(int n, vector<int>& dp) {
    if (n <= 1) return 1;
    if (dp[n] != -1) return dp[n];
    return dp[n] = climbStairs_memo(n - 1, dp) + climbStairs_memo(n - 2, dp);
}

/*
 * EXAMPLE 3: Partition problem (more complex memoization)
 * --------------------------------------------------------
 * Given array, can you partition into two subsets with equal sum?
 * This demonstrates 2D memoization.
 *
 * State:     dp[i][sum] = can we make 'sum' using first i elements?
 * Transition: dp[i][sum] = dp[i-1][sum] || dp[i-1][sum - arr[i]]
 */

// 2D Memoization example
int dp_2d[105][10005];  // -1: not visited, 0: false, 1: true

bool canPartition_memo(vector<int>& arr, int i, int target) {
    if (target == 0) return true;
    if (i < 0 || target < 0) return false;
    if (dp_2d[i][target] != -1) return dp_2d[i][target];

    // Choice: include arr[i] or exclude it
    bool include = canPartition_memo(arr, i - 1, target - arr[i]);
    bool exclude = canPartition_memo(arr, i - 1, target);

    return dp_2d[i][target] = (include || exclude);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "============================================" << endl;
    cout << "   RECURSION TO MEMOIZATION — DEMO" << endl;
    cout << "============================================" << endl;

    // Example 1: Min Cost Climbing Stairs
    vector<int> cost = {10, 15, 20, 25, 30};
    int n = cost.size();

    cout << "\n--- Min Cost Climbing Stairs ---" << endl;
    cout << "Cost array: ";
    for (int c : cost) cout << c << " ";
    cout << endl;

    // Pure recursion
    int ans1 = min(minCost_recursive(cost, n - 1),
                   minCost_recursive(cost, n - 2));
    cout << "Recursion:     " << ans1 << endl;

    // Memoization
    vector<int> dp(n, -1);
    int ans2 = min(minCost_memo(cost, n - 1, dp),
                   minCost_memo(cost, n - 2, dp));
    cout << "Memoization:   " << ans2 << endl;

    // Tabulation
    cout << "Tabulation:    " << minCost_tabulation(cost) << endl;

    // Space optimized
    cout << "Optimized:     " << minCost_optimized(cost) << endl;

    // Example 2: Climbing Stairs
    cout << "\n--- Climbing Stairs ---" << endl;
    for (int i = 1; i <= 10; i++) {
        vector<int> dp2(i + 1, -1);
        cout << "n=" << i << " → ways = " << climbStairs_memo(i, dp2) << endl;
    }

    // Example 3: Partition Problem
    cout << "\n--- Partition Problem ---" << endl;
    vector<int> arr = {1, 5, 11, 5};
    int total = 0;
    for (int x : arr) total += x;

    if (total % 2 != 0) {
        cout << "Cannot partition (odd sum)" << endl;
    } else {
        memset(dp_2d, -1, sizeof(dp_2d));
        bool result = canPartition_memo(arr, arr.size() - 1, total / 2);
        cout << "Array: ";
        for (int x : arr) cout << x << " ";
        cout << "\nCan partition into equal subsets? "
             << (result ? "YES" : "NO") << endl;
    }

    /*
     * MEMOIZATION TIPS:
     * =================
     * 1. Initialize dp array with -1 (or use unordered_map for sparse states)
     * 2. For boolean DP, use 0/1/-1 instead of true/false
     * 3. State should capture ALL info needed to solve from that point
     * 4. memo key = function parameters that change
     * 5. Use memset(dp, -1, sizeof(dp)) for quick initialization
     */

    return 0;
}

