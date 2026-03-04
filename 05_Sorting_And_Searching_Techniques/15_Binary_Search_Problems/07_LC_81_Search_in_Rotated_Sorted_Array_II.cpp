/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-04 13:44:00
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

/* Problem: 81. Search in Rotated Sorted Array II
 * URL: https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
 *
 * Given an integer array nums that is sorted in non-decreasing order and then rotated at an unknown pivot index,
 * and an integer target, return true if target is in nums, or false if it is not in nums.
 *
 * There may be duplicates in the array.
 *
 * Example 1:
 * Input: nums = [2,5,6,0,0,1,2], target = 0
 * Output: true
 *
 * Example 2:
 * Input: nums = [2,5,6,0,0,1,2], target = 3
 * Output: false
 *
 * Constraints:
 * 1 <= nums.length <= 5000
 * -104 <= nums[i] <= 104
 * nums is guaranteed to be rotated at some pivot.
 * -104 <= target <= 104
 */

/*
     * Complexity Analysis:
     * Time: O(log N) average, O(N) worst-case.
     * Space: O(1).
     * * Worst-Case Scenario (Degradation to Linear Time):
     * Consider searching for target k = 0 in: [1, 1, 1, 0, 1]
     * * Iteration 1:
     * lo = 0 (val 1), hi = 4 (val 1), mid = 2 (val 1)
     * Here, A[lo] == A[mid] == A[hi].
     * * Critically, the algorithm cannot distinguish this from the case [1, 0, 1, 1, 1].
     * Because the sorted property is indistinguishable on both sides,
     * we are forced to contract linearly (lo++, hi--) rather than logarithmically.
     * This effectively reduces the algorithm to a linear scan in the worst case.
*/
bool search(const vec<int>& A, int k) {
    int lo = 0, hi = (int)sz(A) - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (A[mid] == k) return true;

        // Ambiguity Resolution:
        // When ends and mid are identical, we cannot determine which half
        // preserves monotonicity. We conservatively shrink the window.
        if (A[lo] == A[mid] && A[mid] == A[hi]) {
            lo++;
            hi--;
            continue;
        }

        // Pivot Analysis:
        // Case 1: Left half [lo...mid] is monotonic (sorted).
        if (A[lo] <= A[mid]) {
            if (A[lo] <= k && k < A[mid]) hi = mid - 1;
            else lo = mid + 1;
        }
        // Case 2: Right half [mid...hi] is monotonic (sorted).
        else {
            if (A[mid] < k && k <= A[hi]) lo = mid + 1;
            else hi = mid - 1;
        }
    }

    return false;
}

void solve() {
    int n, k; cin >> n >> k;

    vec<int> a(n);
    read(a);

    bool ans = search(a, k);
    cout << (ans ? "true" : "false") << nl;
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

