/*
 * ============================================================================
 *                  TOP-DOWN vs BOTTOM-UP DP (Tabulation)
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : DP Foundations — Top-Down vs Bottom-Up comparison
 * Level   : ⭐ Beginner
 * ============================================================================
 *
 * TOP-DOWN (Memoization):
 * ========================
 * - Start from the main problem, recurse into subproblems
 * - Lazy: Only solves subproblems that are actually needed
 * - Uses recursion + cache (hashmap/array)
 * - Easier to think about (natural recursive thinking)
 * - Risk: Stack overflow for deep recursion
 *
 * BOTTOM-UP (Tabulation):
 * ========================
 * - Start from base cases, build up to the main problem
 * - Eager: Solves all subproblems in order
 * - Uses iterative loops + table (array)
 * - No recursion overhead, no stack overflow risk
 * - Easier to optimize space
 *
 * COMPARISON TABLE:
 * ==================
 * Feature          | Top-Down (Memo)      | Bottom-Up (Tab)
 * -----------------|----------------------|-------------------
 * Approach         | Recursive            | Iterative
 * Order            | Depends on calls     | Predefined order
 * Space            | Stack + memo         | Just table
 * Subproblems      | Only needed ones     | All subproblems
 * Ease of coding   | Usually easier       | Sometimes harder
 * Speed            | Slight overhead      | Usually faster
 * Space optimize   | Harder               | Easier
 * Stack overflow   | Possible             | Not possible
 *
 * WHEN TO USE WHICH:
 * ===================
 * → Top-Down: When not all states are visited, or tree-like DP
 * → Bottom-Up: When all states visited, or space optimization needed
 * → In competitive programming: Start with Top-Down (faster to code),
 *   convert to Bottom-Up if TLE or MLE
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * EXAMPLE: Longest Common Subsequence (LCS)
 * ------------------------------------------
 * Given two strings s1 and s2, find the length of LCS.
 *
 * State:    dp[i][j] = LCS of s1[0..i-1] and s2[0..j-1]
 * Transition:
 *   if s1[i-1] == s2[j-1]: dp[i][j] = dp[i-1][j-1] + 1
 *   else:                   dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 * Base:    dp[0][j] = dp[i][0] = 0
 */

// ======================== TOP-DOWN (Memoization) ========================
class TopDownLCS {
    string s1, s2;
    vector<vector<int>> memo;

public:
    int solve(int i, int j) {
        if (i == 0 || j == 0) return 0;  // Base case
        if (memo[i][j] != -1) return memo[i][j];  // Check cache

        if (s1[i - 1] == s2[j - 1]) {
            memo[i][j] = 1 + solve(i - 1, j - 1);
        } else {
            memo[i][j] = max(solve(i - 1, j), solve(i, j - 1));
        }
        return memo[i][j];
    }

    int lcs(string& a, string& b) {
        s1 = a; s2 = b;
        int n = a.size(), m = b.size();
        memo.assign(n + 1, vector<int>(m + 1, -1));
        return solve(n, m);
    }
};

// ======================== BOTTOM-UP (Tabulation) ========================
class BottomUpLCS {
public:
    int lcs(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Fill table bottom-up
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[n][m];
    }
};

// ======================== SPACE OPTIMIZED BOTTOM-UP ======================
class SpaceOptimizedLCS {
public:
    int lcs(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();
        // Only need previous row!
        vector<int> prev(m + 1, 0), curr(m + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    curr[j] = prev[j - 1] + 1;
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            swap(prev, curr);
            fill(curr.begin(), curr.end(), 0);
        }
        return prev[m];
    }
};

/*
 * EXAMPLE 2: Coin Change — showing both approaches
 * Given coins[] and amount, find minimum coins needed.
 */

// TOP-DOWN
int coinChange_topDown(vector<int>& coins, int amount, vector<int>& dp) {
    if (amount == 0) return 0;
    if (amount < 0) return INT_MAX;
    if (dp[amount] != -1) return dp[amount];

    int res = INT_MAX;
    for (int coin : coins) {
        int sub = coinChange_topDown(coins, amount - coin, dp);
        if (sub != INT_MAX) {
            res = min(res, sub + 1);
        }
    }
    return dp[amount] = res;
}

// BOTTOM-UP
int coinChange_bottomUp(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;  // Base case: 0 coins for amount 0

    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (i - coin >= 0 && dp[i - coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "============================================" << endl;
    cout << "   TOP-DOWN vs BOTTOM-UP DP — DEMO" << endl;
    cout << "============================================" << endl;

    // LCS Example
    string s1 = "abcde", s2 = "ace";
    cout << "\n--- Longest Common Subsequence ---" << endl;
    cout << "s1 = \"" << s1 << "\", s2 = \"" << s2 << "\"" << endl;

    TopDownLCS td;
    cout << "Top-Down:        " << td.lcs(s1, s2) << endl;

    BottomUpLCS bu;
    cout << "Bottom-Up:       " << bu.lcs(s1, s2) << endl;

    SpaceOptimizedLCS so;
    cout << "Space Optimized: " << so.lcs(s1, s2) << endl;

    // Coin Change Example
    vector<int> coins = {1, 3, 4};
    int amount = 6;
    cout << "\n--- Coin Change ---" << endl;
    cout << "Coins: ";
    for (int c : coins) cout << c << " ";
    cout << ", Amount: " << amount << endl;

    vector<int> dp(amount + 1, -1);
    cout << "Top-Down:  " << coinChange_topDown(coins, amount, dp) << " coins" << endl;
    cout << "Bottom-Up: " << coinChange_bottomUp(coins, amount) << " coins" << endl;

    /*
     * DRY RUN for Coin Change (coins={1,3,4}, amount=6):
     *
     * Bottom-Up Table:
     * dp[0] = 0  (base)
     * dp[1] = 1  (coin 1)
     * dp[2] = 2  (1+1)
     * dp[3] = 1  (coin 3)
     * dp[4] = 1  (coin 4)
     * dp[5] = 2  (4+1)
     * dp[6] = 2  (3+3)  ← Answer!
     */

    return 0;
}

