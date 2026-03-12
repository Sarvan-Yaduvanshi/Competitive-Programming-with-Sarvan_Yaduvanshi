/*
 * ============================================================================
 *               SPACE OPTIMIZATION & COMPLEXITY ANALYSIS
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : DP Foundations — Space Optimization Techniques + Complexity
 * Level   : ⭐⭐ Intermediate
 * ============================================================================
 *
 * SPACE OPTIMIZATION TECHNIQUES:
 * ===============================
 *
 * 1. ROLLING ARRAY (Previous Row Only)
 *    - When dp[i] depends only on dp[i-1]
 *    - Keep only 2 rows instead of n rows
 *    - O(n*m) → O(m) space
 *
 * 2. SINGLE ROW OPTIMIZATION
 *    - When dp[i][j] depends on dp[i-1][j] and dp[i-1][j-1]
 *    - Iterate backwards in inner loop for 0/1 knapsack
 *    - O(n*m) → O(m) space
 *
 * 3. TWO VARIABLES
 *    - When dp[i] depends only on dp[i-1] and dp[i-2]
 *    - Keep only 2 variables
 *    - O(n) → O(1) space
 *
 * DP COMPLEXITY ANALYSIS:
 * ========================
 * Time = (Number of states) × (Time per transition)
 * Space = (Number of states stored simultaneously)
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * TECHNIQUE 1: Rolling Array — 0/1 Knapsack Space Optimization
 * =============================================================
 *
 * Standard 0/1 Knapsack: O(n*W) time, O(n*W) space
 * With rolling array: O(n*W) time, O(W) space
 *
 * KEY INSIGHT: dp[i] only depends on dp[i-1]
 * TRICK: Iterate capacity BACKWARDS to avoid using updated values
 *
 * Why backwards?
 * If we go left→right: dp[w] might use dp[w-wt[i]] that was already
 * updated in this iteration (effectively using item i twice!)
 * Going right→left: dp[w-wt[i]] hasn't been updated yet → correct!
 */

// Standard 2D Knapsack
int knapsack_2D(vector<int>& wt, vector<int>& val, int W) {
    int n = wt.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i-1][w];  // Don't take item i
            if (w >= wt[i-1]) {
                dp[i][w] = max(dp[i][w], dp[i-1][w - wt[i-1]] + val[i-1]);
            }
        }
    }
    return dp[n][W];
}

// Space Optimized 1D Knapsack — O(W) space
int knapsack_1D(vector<int>& wt, vector<int>& val, int W) {
    int n = wt.size();
    vector<int> dp(W + 1, 0);

    for (int i = 0; i < n; i++) {
        // BACKWARDS to avoid reusing same item
        for (int w = W; w >= wt[i]; w--) {
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
        }
    }
    return dp[W];
}

/*
 * TECHNIQUE 2: Rolling Two Rows — LCS Space Optimization
 */
int lcs_space_optimized(string& s1, string& s2) {
    int n = s1.size(), m = s2.size();
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i-1] == s2[j-1])
                curr[j] = prev[j-1] + 1;
            else
                curr[j] = max(prev[j], curr[j-1]);
        }
        swap(prev, curr);
        fill(curr.begin(), curr.end(), 0);
    }
    return prev[m];
}

/*
 * TECHNIQUE 3: Two Variables — Fibonacci / Climbing Stairs
 */
long long fib_O1_space(int n) {
    if (n <= 1) return n;
    long long a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        long long c = a + b;
        a = b;
        b = c;
    }
    return b;
}

/*
 * TECHNIQUE 4: Unbounded Knapsack — Forward iteration
 * For UNBOUNDED knapsack, iterate FORWARDS (items can be reused)
 */
int unbounded_knapsack(vector<int>& wt, vector<int>& val, int W) {
    vector<int> dp(W + 1, 0);

    for (int i = 0; i < (int)wt.size(); i++) {
        // FORWARDS because we CAN reuse items
        for (int w = wt[i]; w <= W; w++) {
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
        }
    }
    return dp[W];
}

/*
 * COMPLEXITY ANALYSIS EXAMPLES:
 * ===============================
 *
 * Problem             | States        | Per State | Total Time | Space
 * --------------------|---------------|-----------|------------|-------
 * Fibonacci           | O(n)          | O(1)      | O(n)       | O(1)*
 * Climbing Stairs     | O(n)          | O(1)      | O(n)       | O(1)*
 * 0/1 Knapsack        | O(n*W)        | O(1)      | O(n*W)     | O(W)*
 * LCS                 | O(n*m)        | O(1)      | O(n*m)     | O(m)*
 * Edit Distance       | O(n*m)        | O(1)      | O(n*m)     | O(m)*
 * LIS (O(n²))         | O(n)          | O(n)      | O(n²)      | O(n)
 * LIS (Binary Search) | O(n)          | O(log n)  | O(n log n) | O(n)
 * Interval DP         | O(n²)         | O(n)      | O(n³)      | O(n²)
 * Bitmask DP          | O(2^n * n)    | O(n)      | O(2^n*n²)  | O(2^n*n)
 * Digit DP            | O(D*S*2)      | O(10)     | O(D*S*20)  | O(D*S*2)
 *
 * * = after space optimization
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "============================================" << endl;
    cout << "   SPACE OPTIMIZATION & COMPLEXITY — DEMO" << endl;
    cout << "============================================" << endl;

    // Knapsack comparison
    vector<int> wt = {1, 3, 4, 5};
    vector<int> val = {1, 4, 5, 7};
    int W = 7;

    cout << "\n--- 0/1 Knapsack ---" << endl;
    cout << "Weights: "; for(int w : wt) cout << w << " "; cout << endl;
    cout << "Values:  "; for(int v : val) cout << v << " "; cout << endl;
    cout << "Capacity: " << W << endl;
    cout << "2D DP result:  " << knapsack_2D(wt, val, W) << endl;
    cout << "1D DP result:  " << knapsack_1D(wt, val, W) << endl;

    // Unbounded knapsack
    cout << "\n--- Unbounded Knapsack ---" << endl;
    cout << "Result: " << unbounded_knapsack(wt, val, W) << endl;

    // LCS
    string s1 = "abcde", s2 = "ace";
    cout << "\n--- LCS (Space Optimized) ---" << endl;
    cout << "s1=\"" << s1 << "\", s2=\"" << s2 << "\"" << endl;
    cout << "LCS length: " << lcs_space_optimized(s1, s2) << endl;

    // Fibonacci O(1) space
    cout << "\n--- Fibonacci (O(1) space) ---" << endl;
    for (int i = 0; i <= 10; i++) {
        cout << "F(" << i << ")=" << fib_O1_space(i) << " ";
    }
    cout << endl;

    cout << "\n============================================" << endl;
    cout << "  SPACE OPTIMIZATION RULES:" << endl;
    cout << "  • 0/1 Knapsack → iterate BACKWARDS" << endl;
    cout << "  • Unbounded    → iterate FORWARDS" << endl;
    cout << "  • 2 row dep    → rolling array (prev/curr)" << endl;
    cout << "  • 2 var dep    → just 2 variables" << endl;
    cout << "============================================" << endl;

    return 0;
}

