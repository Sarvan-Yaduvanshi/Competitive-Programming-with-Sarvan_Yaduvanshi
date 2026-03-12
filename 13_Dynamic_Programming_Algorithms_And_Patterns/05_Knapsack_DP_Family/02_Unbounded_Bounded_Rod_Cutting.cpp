/*
 * ============================================================================
 *         UNBOUNDED KNAPSACK, BOUNDED KNAPSACK & ROD CUTTING
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Knapsack DP — Unbounded, Bounded, Rod Cutting, Coin Change
 * Level   : ⭐⭐ Intermediate
 * ============================================================================
 *
 * UNBOUNDED KNAPSACK:
 *   Same as 0/1 but each item can be used UNLIMITED times.
 *   TRICK: Iterate capacity FORWARDS (not backwards).
 *
 * BOUNDED KNAPSACK:
 *   Item i can be used at most count[i] times.
 *   Binary decomposition trick for efficiency.
 *
 * ROD CUTTING:
 *   Given rod of length n and price table, maximize profit.
 *   This is unbounded knapsack variant.
 *
 * COIN CHANGE COMBINATIONS vs PERMUTATIONS:
 *   Combinations: outer loop coins, inner loop amount
 *   Permutations: outer loop amount, inner loop coins
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// Unbounded Knapsack — Items can be reused
int unboundedKnapsack(vector<int>& wt, vector<int>& val, int W) {
    vector<int> dp(W + 1, 0);

    for (int i = 0; i < (int)wt.size(); i++) {
        for (int w = wt[i]; w <= W; w++) {  // FORWARD for unbounded
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
        }
    }
    return dp[W];
}

// Rod Cutting Problem
int rodCutting(vector<int>& price, int n) {
    // price[i] = price of rod of length (i+1)
    vector<int> dp(n + 1, 0);

    for (int len = 1; len <= n; len++) {
        for (int cut = 1; cut <= len; cut++) {
            dp[len] = max(dp[len], price[cut - 1] + dp[len - cut]);
        }
    }
    return dp[n];
}

// Bounded Knapsack — Binary Decomposition
// Item i available count[i] times
int boundedKnapsack(vector<int>& wt, vector<int>& val, vector<int>& cnt, int W) {
    int n = wt.size();
    vector<int> dp(W + 1, 0);

    for (int i = 0; i < n; i++) {
        // Binary decomposition: split count[i] into 1, 2, 4, 8, ..., remainder
        int remaining = cnt[i];
        for (int k = 1; remaining > 0; k *= 2) {
            int take = min(k, remaining);
            remaining -= take;
            int w_item = wt[i] * take;
            int v_item = val[i] * take;

            // 0/1 knapsack for this "virtual" item
            for (int w = W; w >= w_item; w--) {
                dp[w] = max(dp[w], dp[w - w_item] + v_item);
            }
        }
    }
    return dp[W];
}

// Coin Change — Combinations (order doesn't matter)
int coinCombinations(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;

    for (int coin : coins) {                    // Outer: coins
        for (int i = coin; i <= amount; i++) {  // Inner: amount
            dp[i] += dp[i - coin];
        }
    }
    return dp[amount];
}

// Coin Change — Permutations (order matters)
int coinPermutations(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= amount; i++) {          // Outer: amount
        for (int coin : coins) {                  // Inner: coins
            if (i >= coin) dp[i] += dp[i - coin];
        }
    }
    return dp[amount];
}

// Coin Change — Minimum coins
int coinChangeMin(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (i >= coin && dp[i - coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== UNBOUNDED & BOUNDED KNAPSACK ===" << endl;

    // Unbounded Knapsack
    vector<int> wt = {1, 3, 4, 5}, val = {1, 4, 5, 7};
    cout << "\n--- Unbounded Knapsack ---" << endl;
    cout << "Capacity 7: " << unboundedKnapsack(wt, val, 7) << endl;

    // Rod Cutting
    vector<int> price = {1, 5, 8, 9, 10, 17, 17, 20};
    cout << "\n--- Rod Cutting ---" << endl;
    cout << "Rod length 8: " << rodCutting(price, 8) << endl;

    // Bounded Knapsack
    vector<int> bwt = {2, 3, 4}, bval = {3, 4, 5}, bcnt = {3, 2, 1};
    cout << "\n--- Bounded Knapsack ---" << endl;
    cout << "Capacity 10: " << boundedKnapsack(bwt, bval, bcnt, 10) << endl;

    // Coin Change
    vector<int> coins = {1, 2, 5};
    cout << "\n--- Coin Change ---" << endl;
    cout << "Amount 5 (combinations): " << coinCombinations(coins, 5) << endl;
    cout << "Amount 5 (permutations): " << coinPermutations(coins, 5) << endl;
    cout << "Amount 11 (min coins): " << coinChangeMin(coins, 11) << endl;

    /*
     * KEY DIFFERENCE:
     * Combinations of amount=5, coins={1,2,5}:
     *   {5}, {2+2+1}, {2+1+1+1}, {1+1+1+1+1} → 4 ways
     *
     * Permutations of amount=5:
     *   {5}, {1+2+2}, {2+1+2}, {2+2+1}, ... → 9 ways
     */

    return 0;
}

