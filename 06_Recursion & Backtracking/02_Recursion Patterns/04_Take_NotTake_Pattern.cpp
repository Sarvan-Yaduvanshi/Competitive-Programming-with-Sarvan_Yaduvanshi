/*
╔══════════════════════════════════════════════════════════════╗
║  04. THE "TAKE / NOT-TAKE" PATTERN — Most Important Pattern!║
║  Level 2 — Recursion Patterns                                ║
╚══════════════════════════════════════════════════════════════╝

🧠 THE TAKE / NOT-TAKE PATTERN (a.k.a. Include/Exclude)

This is THE most important recursion pattern in competitive programming.
Almost everything builds on this.

════════════════════════════════════════════════════════════════
📖 THE IDEA
════════════════════════════════════════════════════════════════

At each index i, you have exactly 2 CHOICES:
    ✅ TAKE arr[i]   — include it in current selection
    ❌ NOT TAKE arr[i] — skip it

This creates a BINARY TREE of decisions:

                      i=0
                    /      \
              TAKE a[0]   SKIP a[0]
               /    \       /    \
          TAKE a[1] SKIP  TAKE  SKIP    ... for each index

Total leaves = 2^n (every possible subset!)

════════════════════════════════════════════════════════════════
🏗️ TEMPLATE
════════════════════════════════════════════════════════════════

    void solve(int index, vec<int>& arr, <state>) {
        // BASE CASE: processed all elements
        if (index == arr.size()) {
            // Process current selection
            return;
        }

        // CHOICE 1: TAKE arr[index]
        <add arr[index] to state>
        solve(index + 1, arr, state);
        <remove arr[index] from state>  // BACKTRACK!

        // CHOICE 2: NOT TAKE arr[index]
        solve(index + 1, arr, state);
    }

════════════════════════════════════════════════════════════════

🎯 Problems in this file:
   1. Print ALL subsequences
   2. Print subsequences with sum = K
   3. Count subsequences with sum = K
   4. Check if ANY subsequence has sum = K
   5. Generate all subsets (Power Set) — LC 78
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

using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;

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
// 1️⃣ PRINT ALL SUBSEQUENCES
// ═══════════════════════════════════════════════════════════
/*
   arr = {3, 1, 2}

   Subsequences (maintain relative order):
   {} {3} {1} {2} {3,1} {3,2} {1,2} {3,1,2}

   Total = 2^n = 2^3 = 8

   Recursion tree:
                           []
                        /      \
                   [3]           []
                  /    \        /   \
             [3,1]    [3]    [1]     []
             / \      / \    / \    / \
         [3,1,2] [3,1] [3,2] [3] [1,2] [1] [2] []

   Time: O(2^n * n) — 2^n subsequences, each takes O(n) to print
   Space: O(n) — recursion depth + current subsequence
*/
void printAllSubsequences(vec<int>& arr, int index, vec<int>& current) {
    // BASE CASE: processed all elements
    if (index == sz(arr)) {
        cout << "{ ";
        for (int x : current) cout << x << " ";
        cout << "}" << nl;
        return;
    }

    // CHOICE 1: TAKE arr[index]
    current.pb(arr[index]);
    printAllSubsequences(arr, index + 1, current);
    current.pop_back();  // ← BACKTRACK! Undo the choice

    // CHOICE 2: NOT TAKE arr[index]
    printAllSubsequences(arr, index + 1, current);
}


// ═══════════════════════════════════════════════════════════
// 2️⃣ PRINT SUBSEQUENCES WITH SUM = K
// ═══════════════════════════════════════════════════════════
/*
   Same as above, but only print if sum equals target K.

   🧠 OPTIMIZATION: Pass running sum as parameter to avoid
      recalculating sum each time.

   PRUNING: If sum already exceeds K and all elements are positive,
            we can stop early!
*/
void printSubseqWithSumK(vec<int>& arr, int index, vec<int>& current,
                          int currentSum, int K) {
    // BASE CASE
    if (index == sz(arr)) {
        if (currentSum == K) {
            cout << "{ ";
            for (int x : current) cout << x << " ";
            cout << "}" << nl;
        }
        return;
    }

    // PRUNING: if all elements are non-negative and sum already > K, stop
    // (only valid when all arr[i] >= 0)
    // if (currentSum > K) return;

    // TAKE
    current.pb(arr[index]);
    printSubseqWithSumK(arr, index + 1, current, currentSum + arr[index], K);
    current.pop_back();

    // NOT TAKE
    printSubseqWithSumK(arr, index + 1, current, currentSum, K);
}


// ═══════════════════════════════════════════════════════════
// 3️⃣ COUNT SUBSEQUENCES WITH SUM = K
// ═══════════════════════════════════════════════════════════
/*
   Instead of printing, just COUNT how many subsequences sum to K.

   🧠 Pattern: Return count from both branches and ADD them.

   This is the foundation for DP problems like:
   - Count subsets with sum K
   - Coin change count
   - Target Sum (LC 494)
*/
int countSubseqWithSumK(vec<int>& arr, int index, int currentSum, int K) {
    // BASE CASE
    if (index == sz(arr)) {
        return (currentSum == K) ? 1 : 0;
    }

    // TAKE + NOT TAKE → sum their counts
    int take = countSubseqWithSumK(arr, index + 1, currentSum + arr[index], K);
    int notTake = countSubseqWithSumK(arr, index + 1, currentSum, K);

    return take + notTake;
}


// ═══════════════════════════════════════════════════════════
// 4️⃣ CHECK IF ANY SUBSEQUENCE HAS SUM = K
// ═══════════════════════════════════════════════════════════
/*
   Return true as SOON as we find one valid subsequence.

   🧠 EARLY TERMINATION: If TAKE branch returns true,
      don't even explore NOT TAKE branch!

   This is more efficient than counting ALL and checking > 0.
*/
bool anySubseqWithSumK(vec<int>& arr, int index, int currentSum, int K) {
    if (index == sz(arr)) {
        return currentSum == K;
    }

    // TAKE — if this returns true, we're done!
    if (anySubseqWithSumK(arr, index + 1, currentSum + arr[index], K))
        return true;

    // NOT TAKE
    if (anySubseqWithSumK(arr, index + 1, currentSum, K))
        return true;

    return false;
}


// ═══════════════════════════════════════════════════════════
// 5️⃣ GENERATE ALL SUBSETS (Power Set) — LeetCode 78
// ═══════════════════════════════════════════════════════════
/*
   Same as print all subsequences, but store results in a 2D vector.

   Input:  [1, 2, 3]
   Output: [[], [1], [2], [3], [1,2], [1,3], [2,3], [1,2,3]]
*/
void generateSubsets(vec<int>& nums, int index, vec<int>& current,
                     vec<vec<int>>& result) {
    if (index == sz(nums)) {
        result.pb(current);
        return;
    }

    // TAKE
    current.pb(nums[index]);
    generateSubsets(nums, index + 1, current, result);
    current.pop_back();

    // NOT TAKE
    generateSubsets(nums, index + 1, current, result);
}

// ═══════════════════════════════════════════════════════════
// 6️⃣ STRING SUBSEQUENCES
// ═══════════════════════════════════════════════════════════
/*
   Same pattern applied to strings!
   "abc" → "", "a", "b", "c", "ab", "ac", "bc", "abc"
*/
void stringSubsequences(const string& s, int index, string& current,
                        vec<string>& result) {
    if (index == sz(s)) {
        result.pb(current);
        return;
    }

    // TAKE s[index]
    current.pb(s[index]);
    stringSubsequences(s, index + 1, current, result);
    current.pop_back();

    // NOT TAKE
    stringSubsequences(s, index + 1, current, result);
}


// ═══════════════════════════════════════════════════════════
// 🧪 TEST ALL FUNCTIONS
// ═══════════════════════════════════════════════════════════

void solve() {
    vec<int> arr = {3, 1, 2};

    // 1. All subsequences
    cout << "=== ALL SUBSEQUENCES of {3, 1, 2} ===" << nl;
    vec<int> current;
    printAllSubsequences(arr, 0, current);

    // 2. Subsequences with sum = 3
    cout << nl << "=== SUBSEQUENCES with SUM = 3 ===" << nl;
    current.clear();
    printSubseqWithSumK(arr, 0, current, 0, 3);

    // 3. Count subsequences with sum = 3
    cout << nl << "Count of subsequences with sum=3: "
         << countSubseqWithSumK(arr, 0, 0, 3) << nl;

    // 4. Any subsequence with sum = 5?
    cout << "Any subsequence with sum=5? "
         << (anySubseqWithSumK(arr, 0, 0, 5) ? "YES" : "NO") << nl;
    cout << "Any subsequence with sum=10? "
         << (anySubseqWithSumK(arr, 0, 0, 10) ? "YES" : "NO") << nl;

    // 5. Power set
    vec<int> nums = {1, 2, 3};
    vec<vec<int>> subsets;
    current.clear();
    generateSubsets(nums, 0, current, subsets);
    cout << nl << "=== POWER SET of {1, 2, 3} ===" << nl;
    for (auto& s : subsets) {
        cout << "{ ";
        for (int x : s) cout << x << " ";
        cout << "}" << nl;
    }

    // 6. String subsequences
    string str = "abc";
    string curr = "";
    vec<string> strSubs;
    stringSubsequences(str, 0, curr, strSubs);
    cout << nl << "=== STRING SUBSEQUENCES of 'abc' ===" << nl;
    for (auto& s : strSubs) cout << "\"" << s << "\" ";
    cout << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    while (TC--) solve();

    return 0;
}

