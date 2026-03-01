/*
╔══════════════════════════════════════════════════════════════╗
║  09. RECURSION + MEMOIZATION → DP (Top-Down DP)             ║
║  Level 5 — Advanced Recursion (GM Level)                     ║
╚══════════════════════════════════════════════════════════════╝

════════════════════════════════════════════════════════════════
📖 MEMOIZATION: THE BRIDGE FROM RECURSION TO DP
════════════════════════════════════════════════════════════════

If a recursive function:
  1. Has OVERLAPPING SUBPROBLEMS (same inputs computed multiple times)
  2. Has OPTIMAL SUBSTRUCTURE (optimal solution uses optimal sub-solutions)

→ We can CACHE results! This is TOP-DOWN DP (Memoization).

HOW:
  - Create a dp table (map or array)
  - Before computing: check if answer already cached
  - After computing: store the result

  This converts exponential → polynomial time!

════════════════════════════════════════════════════════════════
🏗️ MEMOIZATION TEMPLATE
════════════════════════════════════════════════════════════════

    map<state, result> memo;  // or dp array

    result solve(state) {
        if (base_case) return base_value;
        if (memo.count(state)) return memo[state];  // CACHED!

        result ans = compute(solve(sub_state1), solve(sub_state2), ...);
        return memo[state] = ans;  // CACHE and return
    }

════════════════════════════════════════════════════════════════

🎯 Problems:
   1. Fibonacci (memoized) — the classic example
   2. 0/1 Knapsack — the KING of DP
   3. Longest Common Subsequence (LCS) — LC 1143
   4. Coin Change — LC 322
   5. Edit Distance — LC 72
   6. Partition Equal Subset Sum — LC 416
   7. Target Sum — LC 494
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>
#include <functional>

using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;

constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD = 1'000'000'007LL;

#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

template<class T>
void read(vec<T> &v) {
    for (auto &x : v) cin >> x;
}


// ═══════════════════════════════════════════════════════════
// 1️⃣ 0/1 KNAPSACK — The King of DP
// ═══════════════════════════════════════════════════════════
/*
   Given N items with weights and values, and capacity W.
   Maximize total value without exceeding weight W.
   Each item can be taken or not (0/1).

   This is Take/Not-Take pattern + Memoization!

   State: dp[i][w] = max value using items[i..n-1] with capacity w

   Transition:
   - NOT TAKE: dp[i][w] = dp[i+1][w]
   - TAKE (if wt[i] <= w): dp[i][w] = val[i] + dp[i+1][w - wt[i]]

   Time: O(N * W), Space: O(N * W)
*/
i64 knapsack01(vec<int>& wt, vec<int>& val, int n, int W) {
    vvec<i64> dp(n + 1, vec<i64>(W + 1, -1));

    function<i64(int, int)> solve = [&](int i, int w) -> i64 {
        if (i == n || w == 0) return 0;
        if (dp[i][w] != -1) return dp[i][w];

        // NOT TAKE
        i64 notTake = solve(i + 1, w);

        // TAKE
        i64 take = 0;
        if (wt[i] <= w) take = val[i] + solve(i + 1, w - wt[i]);

        return dp[i][w] = max(take, notTake);
    };

    return solve(0, W);
}


// ═══════════════════════════════════════════════════════════
// 2️⃣ LONGEST COMMON SUBSEQUENCE (LCS) — LC 1143
// ═══════════════════════════════════════════════════════════
/*
   Given two strings s1 and s2, find length of longest
   common subsequence.

   s1 = "abcde", s2 = "ace" → LCS = "ace" → length 3

   State: dp[i][j] = LCS of s1[i..] and s2[j..]

   Transition:
   - If s1[i] == s2[j]: dp[i][j] = 1 + dp[i+1][j+1]
   - Else: dp[i][j] = max(dp[i+1][j], dp[i][j+1])

   Time: O(n * m), Space: O(n * m)
*/
int lcs(const string& s1, const string& s2) {
    int n = sz(s1), m = sz(s2);
    vvec<int> dp(n + 1, vec<int>(m + 1, -1));

    function<int(int, int)> solve = [&](int i, int j) -> int {
        if (i == n || j == m) return 0;
        if (dp[i][j] != -1) return dp[i][j];

        if (s1[i] == s2[j]) return dp[i][j] = 1 + solve(i + 1, j + 1);
        return dp[i][j] = max(solve(i + 1, j), solve(i, j + 1));
    };

    return solve(0, 0);
}


// ═══════════════════════════════════════════════════════════
// 3️⃣ COIN CHANGE — LC 322
// ═══════════════════════════════════════════════════════════
/*
   Given coins and amount, find minimum coins to make that amount.
   Unlimited supply of each coin.

   coins = [1, 5, 11], amount = 15 → answer = 3 (5+5+5)

   State: dp[i][amt] = min coins using coins[i..n-1] for amount amt

   This is like Combination Sum I but with minimization!
*/
int coinChange(vec<int>& coins, int amount) {
    int n = sz(coins);
    vvec<int> dp(n + 1, vec<int>(amount + 1, -2));

    function<int(int, int)> solve = [&](int i, int amt) -> int {
        if (amt == 0) return 0;
        if (i == n || amt < 0) return INF32;
        if (dp[i][amt] != -2) return dp[i][amt];

        // NOT TAKE: move to next coin
        int notTake = solve(i + 1, amt);

        // TAKE: use coin[i], stay at same index (unlimited)
        int take = INF32;
        if (coins[i] <= amt) take = 1 + solve(i, amt - coins[i]);

        return dp[i][amt] = min(take, notTake);
    };

    int res = solve(0, amount);
    return res >= INF32 ? -1 : res;
}


// ═══════════════════════════════════════════════════════════
// 4️⃣ EDIT DISTANCE — LC 72
// ═══════════════════════════════════════════════════════════
/*
   Minimum operations (insert, delete, replace) to convert s1 → s2.

   "horse" → "ros" → 3 operations

   State: dp[i][j] = min ops to convert s1[i..] to s2[j..]

   Transition:
   - If s1[i] == s2[j]: dp[i][j] = dp[i+1][j+1] (no op needed)
   - Else: dp[i][j] = 1 + min(
       dp[i+1][j+1],  // REPLACE s1[i] with s2[j]
       dp[i+1][j],     // DELETE s1[i]
       dp[i][j+1]      // INSERT s2[j] before s1[i]
     )
*/
int editDistance(const string& s1, const string& s2) {
    int n = sz(s1), m = sz(s2);
    vvec<int> dp(n + 1, vec<int>(m + 1, -1));

    function<int(int, int)> solve = [&](int i, int j) -> int {
        if (i == n) return m - j;  // Insert remaining of s2
        if (j == m) return n - i;  // Delete remaining of s1
        if (dp[i][j] != -1) return dp[i][j];

        if (s1[i] == s2[j]) return dp[i][j] = solve(i + 1, j + 1);

        return dp[i][j] = 1 + min({
            solve(i + 1, j + 1),  // Replace
            solve(i + 1, j),       // Delete
            solve(i, j + 1)        // Insert
        });
    };

    return solve(0, 0);
}


// ═══════════════════════════════════════════════════════════
// 5️⃣ PARTITION EQUAL SUBSET SUM — LC 416
// ═══════════════════════════════════════════════════════════
/*
   Can we partition array into two subsets with equal sum?
   Equivalent to: does a subset with sum = totalSum/2 exist?

   This is subset sum = Take/Not-Take + Memoization!
*/
bool canPartition(vec<int>& nums) {
    int totalSum = accumulate(all(nums), 0);
    if (totalSum & 1) return false;  // Odd sum → impossible

    int target = totalSum / 2;
    int n = sz(nums);
    vvec<int> dp(n + 1, vec<int>(target + 1, -1));

    function<bool(int, int)> solve = [&](int i, int sum) -> bool {
        if (sum == 0) return true;
        if (i == n || sum < 0) return false;
        if (dp[i][sum] != -1) return dp[i][sum];

        bool take = solve(i + 1, sum - nums[i]);
        bool notTake = solve(i + 1, sum);

        return dp[i][sum] = take || notTake;
    };

    return solve(0, target);
}


// ═══════════════════════════════════════════════════════════
// 6️⃣ TARGET SUM — LC 494
// ═══════════════════════════════════════════════════════════
/*
   Assign + or - to each number to reach target sum.

   nums = [1,1,1,1,1], target = 3 → 5 ways

   At each index: add or subtract the number.
   State: dp[i][currentSum]

   ⚠️ currentSum can be negative! Use map or offset.
*/
int targetSum(vec<int>& nums, int target) {
    int n = sz(nums);
    map<pair<int,int>, int> dp;

    function<int(int, int)> solve = [&](int i, int sum) -> int {
        if (i == n) return sum == target ? 1 : 0;

        auto key = make_pair(i, sum);
        if (dp.count(key)) return dp[key];

        return dp[key] = solve(i + 1, sum + nums[i]) + solve(i + 1, sum - nums[i]);
    };

    return solve(0, 0);
}


// ═══════════════════════════════════════════════════════════
// 7️⃣ LONGEST INCREASING SUBSEQUENCE (LIS) — LC 300
// ═══════════════════════════════════════════════════════════
/*
   dp[i] = length of LIS ending at index i

   For each i, check all j < i where nums[j] < nums[i]:
       dp[i] = max(dp[i], dp[j] + 1)

   Recursive with memo: dp[i] = 1 + max(dp[j]) for valid j

   Time: O(n^2) with memo, O(n log n) with binary search
*/
int lisRecursive(vec<int>& nums) {
    int n = sz(nums);
    vec<int> dp(n, -1);

    function<int(int)> solve = [&](int i) -> int {
        if (dp[i] != -1) return dp[i];
        dp[i] = 1;  // At minimum, the element itself
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                dp[i] = max(dp[i], 1 + solve(j));
            }
        }
        return dp[i];
    };

    int ans = 0;
    for (int i = 0; i < n; i++) ans = max(ans, solve(i));
    return ans;
}


// ═══════════════════════════════════════════════════════════
// 🧪 TEST
// ═══════════════════════════════════════════════════════════

void solve() {
    // 1. Knapsack
    {
        cout << "=== 0/1 KNAPSACK ===" << nl;
        vec<int> wt = {1, 3, 4, 5};
        vec<int> val = {1, 4, 5, 7};
        cout << "Max value (W=7): " << knapsack01(wt, val, 4, 7) << nl;
    }

    // 2. LCS
    {
        cout << nl << "=== LCS ===" << nl;
        cout << "LCS('abcde', 'ace') = " << lcs("abcde", "ace") << nl;
    }

    // 3. Coin Change
    {
        cout << nl << "=== COIN CHANGE ===" << nl;
        vec<int> coins = {1, 5, 11};
        cout << "Min coins for 15: " << coinChange(coins, 15) << nl;
    }

    // 4. Edit Distance
    {
        cout << nl << "=== EDIT DISTANCE ===" << nl;
        cout << "edit('horse','ros') = " << editDistance("horse", "ros") << nl;
    }

    // 5. Partition Equal Subset Sum
    {
        cout << nl << "=== PARTITION EQUAL SUBSET SUM ===" << nl;
        vec<int> nums = {1, 5, 11, 5};
        cout << "Can partition? " << (canPartition(nums) ? "YES" : "NO") << nl;
    }

    // 6. Target Sum
    {
        cout << nl << "=== TARGET SUM ===" << nl;
        vec<int> nums = {1, 1, 1, 1, 1};
        cout << "Ways to reach 3: " << targetSum(nums, 3) << nl;
    }

    // 7. LIS
    {
        cout << nl << "=== LONGEST INCREASING SUBSEQUENCE ===" << nl;
        vec<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
        cout << "LIS length: " << lisRecursive(nums) << nl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    while (TC--) solve();

    return 0;
}

