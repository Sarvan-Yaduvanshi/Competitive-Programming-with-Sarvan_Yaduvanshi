/*
 * ============================================================================
 *              COIN CHANGE & DECODE WAYS
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : 1D DP — Coin Change (Min Coins), Decode Ways
 * Level   : ⭐⭐ Intermediate
 * ============================================================================
 *
 * COIN CHANGE (LeetCode 322):
 *   Given coins[], find minimum coins to make amount.
 *   dp[i] = min coins to make amount i
 *   dp[i] = min(dp[i - coin] + 1) for all coins
 *
 * DECODE WAYS (LeetCode 91):
 *   Given digit string, count ways to decode (A=1..Z=26)
 *   dp[i] = ways to decode s[i..n-1]
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// Coin Change — Minimum coins (LeetCode 322)
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

// Coin Change — Count combinations (LeetCode 518)
int coinChangeCombinations(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;

    // Outer loop on coins → combinations (order doesn't matter)
    for (int coin : coins) {
        for (int i = coin; i <= amount; i++) {
            dp[i] += dp[i - coin];
        }
    }
    return dp[amount];
}

// Coin Change — Count permutations (LeetCode 377 Combination Sum IV)
int coinChangePermutations(vector<int>& coins, int amount) {
    vector<unsigned long long> dp(amount + 1, 0);
    dp[0] = 1;

    // Outer loop on amount → permutations (order matters)
    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (i >= coin) {
                dp[i] += dp[i - coin];
            }
        }
    }
    return dp[amount];
}

// Decode Ways (LeetCode 91)
int decodeWays(string& s) {
    int n = s.size();
    if (n == 0 || s[0] == '0') return 0;

    vector<int> dp(n + 1, 0);
    dp[n] = 1;       // Empty string = 1 way
    dp[n-1] = (s[n-1] != '0') ? 1 : 0;

    for (int i = n - 2; i >= 0; i--) {
        if (s[i] == '0') { dp[i] = 0; continue; }

        dp[i] = dp[i + 1];  // Single digit decode

        int twoDigit = (s[i] - '0') * 10 + (s[i+1] - '0');
        if (twoDigit <= 26) {
            dp[i] += dp[i + 2];  // Two digit decode
        }
    }
    return dp[0];
}

// Decode Ways II (LeetCode 639) — with '*' wildcard
const int MOD = 1e9 + 7;
int decodeWaysII(string& s) {
    int n = s.size();
    vector<long long> dp(n + 1, 0);
    dp[n] = 1;
    dp[n-1] = (s[n-1] == '*') ? 9 : (s[n-1] != '0' ? 1 : 0);

    for (int i = n - 2; i >= 0; i--) {
        if (s[i] == '0') { dp[i] = 0; continue; }

        if (s[i] == '*') {
            dp[i] = 9 * dp[i + 1] % MOD;  // * as 1-9
            if (s[i+1] == '*') {
                dp[i] = (dp[i] + 15 * dp[i + 2]) % MOD;  // 11-19, 21-26
            } else if (s[i+1] <= '6') {
                dp[i] = (dp[i] + 2 * dp[i + 2]) % MOD;   // 1x or 2x
            } else {
                dp[i] = (dp[i] + dp[i + 2]) % MOD;        // only 1x
            }
        } else {
            dp[i] = dp[i + 1];
            if (s[i+1] == '*') {
                if (s[i] == '1') dp[i] = (dp[i] + 9 * dp[i+2]) % MOD;
                else if (s[i] == '2') dp[i] = (dp[i] + 6 * dp[i+2]) % MOD;
            } else {
                int two = (s[i]-'0')*10 + (s[i+1]-'0');
                if (two >= 10 && two <= 26) dp[i] = (dp[i] + dp[i+2]) % MOD;
            }
        }
    }
    return dp[0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== COIN CHANGE & DECODE WAYS ===" << endl;

    // Coin Change Min
    vector<int> coins = {1, 3, 4};
    cout << "\n--- Coin Change (Min Coins) ---" << endl;
    cout << "Coins: "; for (int c : coins) cout << c << " ";
    for (int amt : {6, 7, 11, 0}) {
        cout << "\nAmount " << amt << " → " << coinChangeMin(coins, amt) << " coins";
    }

    // Coin Change Combinations
    vector<int> coins2 = {1, 2, 5};
    int amt = 5;
    cout << "\n\n--- Coin Change (Combinations) ---" << endl;
    cout << "Coins: "; for (int c : coins2) cout << c << " ";
    cout << "\nAmount " << amt << " → " << coinChangeCombinations(coins2, amt) << " ways";

    // Coin Change Permutations
    cout << "\n\n--- Coin Change (Permutations) ---" << endl;
    cout << "Amount " << amt << " → " << coinChangePermutations(coins2, amt) << " ways";

    // Decode Ways
    string s = "226";
    cout << "\n\n--- Decode Ways ---" << endl;
    cout << "\"" << s << "\" → " << decodeWays(s) << " ways" << endl;
    // 2,2,6 | 22,6 | 2,26 → 3 ways

    string s2 = "12";
    cout << "\"" << s2 << "\" → " << decodeWays(s2) << " ways" << endl;
    // 1,2 | 12 → 2 ways

    return 0;
}

