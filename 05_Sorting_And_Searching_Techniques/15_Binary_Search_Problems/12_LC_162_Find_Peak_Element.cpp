/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-04 18:37:48
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

/* Problem: LeetCode 162 - Find Peak Element or Peak Index in a Mountain Array(LC 852)
 * Difficulty: Medium
 * A peak element is an element that is strictly greater than its neighbors.
 * Given an integer array nums, find a peak element, and return its index. If the array contains multiple peaks,
 * return the index to any of the peaks.
 * You may imagine that nums[-1] = nums[n] = -∞.
 *
 * You must write an algorithm that runs in O(log n) time.
 *
 * Example 1:
 * Input: nums = [1,2,3,1]
 * Output: 2
 * Explanation: 3 is a peak element and your function should return the index number 2.
 *
 * Example 2:
 * Input: nums = [1,2,1,3,5,6,4]
 * Output: 1 or 5
 * Explanation: Your function can return either index number 1 where the peak element is 2, or index number 5 where the peak element is 6.
 *
 * Constraints:
 * 1 <= nums.length <= 1000
 * -231 <= nums[i] <= 231 - 1
 * nums[i] != nums[i + 1] for all valid i.
 *
 */

// Approach: Binary Search
// Logic: Compare mid with mid+1 → move toward the higher side, never drop mid if it can be the peak.
int findPeakElement(const vec<int>& A){
    int lo = 0;
    int hi = sz(A) - 1;

    while (lo < hi){
        int mid = lo + (hi - lo) / 2;

        // If A[mid] > A[mid+1], we are on a decreasing slope
        // Mid can be the peak, so keep it in the search space
        if (A[mid] > A[mid + 1]) hi = mid;
        // If A[mid] < A[mid+1], we are on an increasing slope
        // Peak must exist on the right side
        else lo = mid + 1;
    }

    // lo == hi points to a peak element
    return lo;
}



void solve() {
    int n;
    cin >> n;

    vec<int> nums(n);
    read(nums);

    int peakIndex = findPeakElement(nums);
    cout << "Peak Element Index: " << peakIndex << nl;
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

/* =================================================================================
   GM LEVEL INTERVIEW NOTES: PEAK vs. MOUNTAIN vs. BITONIC ARRAYS
   Context: Binary Search on Unsorted/Partially Sorted Arrays
   =================================================================================

   1. WHAT IS A "PEAK ELEMENT"? (LeetCode 162)
   ---------------------------------------------------------------------------------
   -> Definition: Any element that is STRICTLY GREATER than its immediate neighbors.
      (arr[i] > arr[i-1] AND arr[i] > arr[i+1]).
   -> The Array Structure: Completely unsorted. It can go up and down repeatedly.
   -> Number of Peaks: Can have 1, or MULTIPLE peaks.
   -> The Edge Rule: Edges are treated as -Infinity (arr[-1] = -∞, arr[n] = -∞).
   -> Interview Goal: Find and return ANY ONE valid peak.
   -> GM Insight: Binary search works here using "Gradient Ascent." If you step
      to the right and go uphill, a peak MUST exist in that direction because
      the array eventually drops to -∞ at the end.


   2. WHAT IS A "MOUNTAIN ARRAY"? (LeetCode 852)
   ---------------------------------------------------------------------------------
   -> Definition: An array that is STRICTLY increasing up to a point, and then
      STRICTLY decreasing. (No flat plateaus allowed; adjacent elements are never equal).
   -> The Array Structure: Two perfectly sorted halves (one ascending, one descending).
   -> Number of Peaks: EXACTLY ONE peak (the summit of the mountain).
   -> Length Rule: Must be at least 3 elements long to form a valid mountain.
   -> Interview Goal: Find the exact index of the summit.
   -> GM Insight: Binary search works by finding the exact boundary where the slope
      changes from positive (uphill) to negative (downhill).


   3. WHAT IS A "BITONIC ARRAY"?
   ---------------------------------------------------------------------------------
   -> Definition: A sequence that monotonically increases, then monotonically decreases.
   -> How it differs from a Mountain:
      In strict mathematical terms, a Bitonic sequence can be a cyclic shift of a
      mountain, or it can be entirely increasing / entirely decreasing.
   -> IN INTERVIEWS: Interviewers use "Bitonic" and "Mountain" interchangeably!
      If an interviewer asks "Find the peak in a Bitonic Array", they mean a
      Mountain Array.
   -> GM Insight: Don't overthink this one. Treat Bitonic exactly like a Mountain.


   =================================================================================
   THE "TL;DR" DIFFERENCES FOR QUICK REVISION
   =================================================================================
   | Feature         | Peak Element (LC 162)      | Mountain / Bitonic (LC 852) |
   |-----------------|----------------------------|-----------------------------|
   | Array State     | Completely Unsorted        | Ascending, then Descending  |
   | Number of Peaks | 1 or Multiple              | Exactly 1                   |
   | Flat Areas?     | No (adjacent elements !=)  | No (strictly inc/dec)       |
   | BS Strategy     | Gradient Ascent (go up!)   | Find the Up/Down boundary   |
   | Code Used       | EXACTLY THE SAME TEMPLATE  | EXACTLY THE SAME TEMPLATE   |

   NOTE: The exact same `left < right` Binary Search template works for all three
   because finding *any* peak relies on the same local slope check (arr[mid] < arr[mid+1])
   as finding the *only* peak.
   ================================================================================= */