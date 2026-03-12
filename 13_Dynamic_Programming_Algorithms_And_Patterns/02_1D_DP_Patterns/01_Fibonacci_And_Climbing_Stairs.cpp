/*
 * ============================================================================
 *                    FIBONACCI & CLIMBING STAIRS DP
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : 1D DP — Fibonacci Variants & Climbing Stairs
 * Level   : ⭐ Beginner
 * ============================================================================
 *
 * FIBONACCI VARIANTS:
 * ====================
 * F(n) = F(n-1) + F(n-2), F(0)=0, F(1)=1
 *
 * Applications: Climbing stairs, tiling, counting binary strings, etc.
 *
 * CLIMBING STAIRS:
 * =================
 * LeetCode 70: You can climb 1 or 2 steps. Count ways to reach top.
 * dp[i] = dp[i-1] + dp[i-2]  (same as Fibonacci!)
 *
 * EXTENDED: K-step climbing
 * dp[i] = dp[i-1] + dp[i-2] + ... + dp[i-k]
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// Climbing Stairs — O(n) time, O(1) space
int climbStairs(int n) {
    if (n <= 2) return n;
    int a = 1, b = 2;
    for (int i = 3; i <= n; i++) {
        int c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// K-step Climbing Stairs — O(n*k) time
int climbStairsK(int n, int k) {
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k && i - j >= 0; j++) {
            dp[i] += dp[i - j];
        }
    }
    return dp[n];
}

// Min Cost Climbing Stairs (LeetCode 746) — O(n) time, O(1) space
int minCostClimbing(vector<int>& cost) {
    int n = cost.size();
    int a = cost[0], b = cost[1];
    for (int i = 2; i < n; i++) {
        int c = cost[i] + min(a, b);
        a = b;
        b = c;
    }
    return min(a, b);
}

// Tiling Problem: Fill 2×n board with 2×1 tiles
// Same as Fibonacci: dp[n] = dp[n-1] + dp[n-2]
long long tilingWays(int n) {
    if (n <= 2) return n;
    long long a = 1, b = 2;
    for (int i = 3; i <= n; i++) {
        long long c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// Count binary strings of length n with no two consecutive 1s
// dp[i][0] = strings ending with 0, dp[i][1] = ending with 1
// dp[i][0] = dp[i-1][0] + dp[i-1][1]
// dp[i][1] = dp[i-1][0]
long long countBinaryStrings(int n) {
    long long end0 = 1, end1 = 1;  // length 1
    for (int i = 2; i <= n; i++) {
        long long new0 = end0 + end1;
        long long new1 = end0;
        end0 = new0;
        end1 = new1;
    }
    return end0 + end1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== FIBONACCI & CLIMBING STAIRS DP ===" << endl;

    // Climbing Stairs
    cout << "\n--- Climbing Stairs ---" << endl;
    for (int i = 1; i <= 10; i++)
        cout << "n=" << i << " → " << climbStairs(i) << " ways" << endl;

    // K-step climbing
    cout << "\n--- K-Step Climbing (k=3) ---" << endl;
    for (int i = 1; i <= 10; i++)
        cout << "n=" << i << " → " << climbStairsK(i, 3) << " ways" << endl;

    // Min cost climbing
    vector<int> cost = {10, 15, 20};
    cout << "\n--- Min Cost Climbing ---" << endl;
    cout << "Cost: "; for (int c : cost) cout << c << " ";
    cout << "\nMin cost: " << minCostClimbing(cost) << endl;

    // Tiling
    cout << "\n--- 2×n Tiling ---" << endl;
    for (int i = 1; i <= 10; i++)
        cout << "n=" << i << " → " << tilingWays(i) << " ways" << endl;

    // Binary strings
    cout << "\n--- Binary Strings (no consecutive 1s) ---" << endl;
    for (int i = 1; i <= 10; i++)
        cout << "n=" << i << " → " << countBinaryStrings(i) << " strings" << endl;

    return 0;
}

