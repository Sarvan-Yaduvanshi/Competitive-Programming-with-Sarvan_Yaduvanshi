/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-04 00:32:02
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

/*
 * Problem: Maximum Sum of Subarray of Size K
 * Pattern: Fixed Size Sliding Window (Fixed Length
 * Problem Statement:
 * Given an integer array arr[] of size n and an integer k,
 * find the maximum sum of any contiguous subarray of size k.
 * Return only the maximum sum.
 * Example:
 *  arr = [2, 1, 5, 1, 3, 2] and k = 3
 *  Subarrays of size k:
 *  1) [2 1 5] -> sum = 8
 *  2) [1 5 1] -> sum = 7
 *  3) [5 1 3] -> sum = 9
 *  4) [1 3 2] -> sum = 6
 *
 *  Answer :- 8
 */

// Approach 1: Brute Force
// Time Complexity -> O(N * K) || Space Complexity -> O(1)
i64 maxSumOfSubarraySizeK(const vec<int>& arr, const int k){
    int n = sz(arr);

    i64 maxSum = INT_MIN;
    for (int i = 0; i <= n - k; i++){
        i64 currSum = 0;
        for (int j = i; j < i + k; j++){
            currSum += arr[j];
        }

        maxSum = max(maxSum, currSum);
    }
    return maxSum;
}

/* Algorithm: Max Subarray Sum of Size K (Prefix Sum Strategy)
 * APPLYING TO SIZE K WINDOW:
 * Indices: i, i+1, i+2, ...., i+(k-1)
 * start = i and end = i + k - 1
 * Logic: A window of size K starting at index 'i' looks like:
 *        Indices: [ i, i+1, ..., i+k-1 ]
 *
 * Formula derivation:
 * Sum(L, R) = PrefixSum[R + 1] - PrefixSum[L]
 * Here, Start (L) = i
 *       End   (R) = i + k - 1
 *
 * Therefore:
 * Sum = pref[(i + k - 1) + 1] - pref[i]
 * Sum = pref[i + k]           - pref[i]
 * Time Complexity -> O(N) | Space Complexity -> O(N) prefix array
 */
i64 maxSubarraySumSizeK(const vec<int>& arr, const int k){
    int n = sz(arr);

    // Step 1: Build Prefix Sum
    vec<i64> pref(n + 1, 0);
    for (int i = 0; i < n; i++)
        pref[i + 1] = pref[i] + arr[i];

    // STEP 2: Iterate Over All Valid Windows
    i64 maxSum = LLONG_MIN;
    for (int i = 0; i <= n - k; i++){
        i64 currSum = pref[i + k] - pref[i];
        maxSum = max(maxSum, currSum);
    }
    return maxSum;
}


void solve() {
    int n, k; cin >> n >> k;

    vec<int> a(n);
    read(a);
    
    cout << maxSubarraySumSizeK(a, k) << nl;
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

