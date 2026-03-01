/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Coin Change — When Greedy Works vs Fails
 *  Level   : Beginner
 * ============================================================================
 *
 *  WHEN GREEDY WORKS:
 *  - Standard denominations: {1, 5, 10, 25} (US coins)
 *  - Any "canonical" coin system where each coin ≥ 2× the next smaller
 *  - Powers of a number: {1, 2, 4, 8, ...} or {1, 3, 9, 27, ...}
 *
 *  WHEN GREEDY FAILS:
 *  - Arbitrary denominations: {1, 3, 4} with amount 6
 *    Greedy: 4+1+1 = 3 coins, Optimal: 3+3 = 2 coins
 *  - {1, 5, 6, 9} with amount 11
 *    Greedy: 9+1+1 = 3 coins, Optimal: 5+6 = 2 coins
 *
 *  RULE: If coins are "nice" (each is ≥ sum of all smaller), greedy works.
 *        Otherwise, use DP!
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// Greedy Coin Change — O(D) where D = number of denominations
int greedyCoinChange(vector<int>& coins, int amount) {
    sort(coins.rbegin(), coins.rend()); // Largest first
    int count = 0;
    for (int c : coins) {
        count += amount / c;
        amount %= c;
    }
    return amount == 0 ? count : -1; // -1 if impossible
}

// DP Coin Change — O(N*Amount), always correct
int dpCoinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= amount; i++)
        for (int c : coins)
            if (c <= i && dp[i-c] != INT_MAX)
                dp[i] = min(dp[i], dp[i-c] + 1);
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

int main() {
    // Case 1: Greedy WORKS (standard coins)
    vector<int> standard = {1, 5, 10, 25};
    cout << "Standard coins, amount=41:" << endl;
    cout << "  Greedy: " << greedyCoinChange(standard, 41) << endl; // 4 (25+10+5+1)
    cout << "  DP:     " << dpCoinChange(standard, 41) << endl;     // 4

    // Case 2: Greedy FAILS (arbitrary coins)
    vector<int> arbitrary = {1, 3, 4};
    cout << "Coins {1,3,4}, amount=6:" << endl;
    cout << "  Greedy: " << greedyCoinChange(arbitrary, 6) << endl; // 3 (4+1+1) WRONG!
    cout << "  DP:     " << dpCoinChange(arbitrary, 6) << endl;     // 2 (3+3) CORRECT!

    return 0;
}

