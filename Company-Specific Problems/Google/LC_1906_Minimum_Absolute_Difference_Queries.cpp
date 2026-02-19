/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-19 12:14:48
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

// --- Type Definitions ---
using i64 = long long;
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

// --- Constants ---
constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;

// --- Random Number Generator ---
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// --- Macros ---
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

// Input helper
template<class T>
void read(vec<T> &v) {
    for (auto &x : v) cin >> x;
}
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

inline i64 gcd(i64 a, i64 b) { return std::gcd(a, b); }
inline i64 lcm(i64 a, i64 b) { return (a / std::gcd(a, b)) * b; }

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD) {
    i64 res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

/* Problem: 1906. Minimum Absolute Difference Queries
 You are given an integer array nums and an array queries where queries[i] = [li, ri].
 The answer to the ith query is the minimum absolute difference between any two distinct elements in the subarray nums[li...ri] (inclusive).
 If there is no minimum absolute difference, the answer to the query is -1.
Return an array answer where answer[i] is the answer to the ith query.
Example 1:
Input: nums = [1,3,4], queries = [[0,2],[0,0],[2,2]]
Output: [1,-1,-1]
Explanation: The minimum absolute difference of each query are:
- queries[0]: The subarray is [1,3,4]. The minimum absolute difference is min(|1-3|, |1-4|, |3-4|) = min(2, 3, 1) = 1.
- queries[1]: The subarray is [1]. There are no two distinct elements in this query, so the answer is -1.
- queries[2]: The subarray is [4]. There are no two distinct elements in this query, so the answer is -1.

Example 2:
Input: nums = [5,2,2], queries = [[0,2]]
Output: [0]
Explanation: The minimum absolute difference of the query is min(|5-2|, |5-2|, |2-2|) = min(3, 3, 0) = 0.

Constraints:
2 <= nums.length <= 10^5
1 <= nums[i] <= 100
1 <= queries.length <= 10^5
queries[i].length == 2
0 <= li < ri < nums.length
*/

// Approach1: Use Brute force to compute the minimum absolute difference for each query.
// Time Complexity: O(Q * (R - L + 1)^2) in the worst case, where Q is the number of queries and R-L+1 is the size of the subarray for each query.
// Space Complexity: O(1) for the brute force approach, but we can optimize it using a frequency array of size 101 (since nums[i] <= 100) to compute the minimum absolute difference in O(1) time after O(R-L+1) time to build the frequency array for each query.
vec<int> minAbsDifferenceBruteForce(const vec<int>& nums, const vvec<int>& queries) {
    vec<int> ans;

    for (const auto& querie : queries){
        int l = querie[0];
        int r = querie[1];

        vec<int> temp;
        // FIX 1: Push the actual values from nums, not the index 'i'
        for (int i = l; i <= r; i++) {
            temp.pb(nums[i]);
        }

        sort(all(temp));

        int minDiff = INT_MAX;
        // FIX 2: i < sz(temp) to avoid out-of-bounds access
        for (int i = 1; i < sz(temp); i++){
            if (temp[i] != temp[i - 1]){
                minDiff = min(minDiff, temp[i] - temp[i - 1]);
            }
        }

        // FIX 3: Check against INT_MAX instead of INT8_MAX
        ans.pb(minDiff == INT_MAX ? -1 : minDiff);
    }

    return ans;
}

// Approach 2: Use Prefix Sum and Frequency Array to compute the minimum absolute difference for each query in O(1) time
// after O(R-L+1) time to build the frequency array for each query.
// Time Complexity: O(Q * (R - L + 1)) in the worst case, where Q is the number of queries and R-L+1 is the size of the subarray for each query.
// Space Complexity: O(1) for the frequency array of size 101.
vec<int> minAbsDifferencePrefixSum(const vec<int>& nums, const vvec<int>& queries) {
    int n = sz(nums);

    // pref[i][c] stores the frequency of number 'c' up to index i-1
    // We use n + 1 rows, and 101 columns (since 1 <= nums[i] <= 100)
    vvec<int> pref(n + 1, vec<int>(101, 0));

    // Build the Prefix Sum of Frequencies
    for (int i = 0; i < n; i++){
        // Copy previous frequencies
        for (int c = 1; c <= 100; c++)
            pref[i + 1][c] = pref[i][c];

        // Increment the frequency of the current number
        pref[i + 1][nums[i]]++;
    }

    vec<int> ans;
    ans.reserve(sz(queries));

    // Process each query
    for (const auto& q : queries){
        int l = q[0];
        int r = q[1];

        int minDiff = 1000;
        int prev_found = -1; // To track the last number we saw

        // Check all possible numbers from 1 to 100
        for (int c = 1; c <= 100; c++){
            // If count is > 0, the number 'c' exists in the range [L, R]
            if (pref[r + 1][c] - pref[l][c] > 0){
                if (prev_found != -1)
                    minDiff = min(minDiff, c - prev_found);

                // Update previous to current
                prev_found = c;
            }
        }

        // If min_diff wasn't updated, all elements were the same (or range was size 1)
        minDiff == 1000 ? ans.pb(-1) : ans.pb(minDiff);
    }

    return ans;
}


void solve() {
    int n; cin >> n;

    vec<int> nums(n);
    read(nums);

    int q; cin >> q;
    // FIX 4: Initialize inner vectors to size 2 so you can access [0] and [1]
    vvec<int> queries(q, vec<int>(2));
    for (int i = 0; i < q; i++) {
        cin >> queries[i][0] >> queries[i][1];
    }

    vec<int> ans = minAbsDifferencePrefixSum(nums, queries);
    cout << "[";
    for (int i = 0; i < sz(ans); i++){
        // FIX 5: The ans array size is bounded by q (sz(ans)), not n
        cout << ans[i] << (i == sz(ans) - 1 ? "" : ", ");
    }
    cout << "]" << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);
    
    // Multi-test case support (commented out for this demo)
    // int TC = 1;
    // cin >> TC;
    // while (TC--) solve();
    
    solve();
    return 0;
}

