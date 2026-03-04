/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-04 13:20:37
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

/* Problem: LeetCode 33. Search in Rotated Sorted Array
 * Difficulty: Medium
 * URL: https://leetcode.com/problems/search-in-rotated-sorted-array/
 *
 * Rotated Sorted Array: An array that was originally sorted in ascending order but then rotated at some pivot.
 * Pattern: increasing -> one drop -> increasing e.g. [4,5,6,7,0,1,2] only one drop from 7 to 0
 *
 * Given an integer array nums sorted in ascending order, and an integer target,
 * suppose that nums is rotated at some pivot unknown to you beforehand (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
 *
 * If target is found in the array return its index, otherwise return -1.
 *
 * You must write an algorithm with O(log n) runtime complexity.
 *
 * Example 1:
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 *
 * Example 2:
 * Input: nums = [4,5,6,7,0,1,2], target = 3
 * Output: -1
 *
 * Example 3:
 * Input: nums = [1], target = 0
 * Output: -1
 *
 * Constraints:
 * 1 <= nums.length <= 5000
 * -10^4 <= nums[i] <= 10^4
 * All values of nums are unique.
 * nums is guaranteed to be rotated at some pivot.
 * -10^4 <= target <= 10^4
 */

/*
 * Binary Search on Rotated Sorted Array (Recursive)
 *
 * At each step, one half of the array is sorted.
 * We recurse only into the half that can contain the target.
 *
 * Time Complexity: O(log N)
 * Space Complexity: O(log N)  // recursion stack
 */
int searchInRotatedArray(const vec<int>& a, int si, int en, int k) {
    // Base Case
    if (si > en)
        return -1;

    int mid = si + (en - si) / 2;

    // Case Found
    if (a[mid] == k) return mid;

    // mid-on Line1
    if (a[si] <= a[mid]) {
        // Case a : Left Part
        if (a[si] <= k && k <= a[mid]) {
            return searchInRotatedArray(a, si, mid - 1, k);
        } else {
            // Case b : Right Part
            return searchInRotatedArray(a, mid + 1, en, k);
        }
    }
    // mid-on Line2
    else {
        // Case c : Right Part
        if (a[mid] <= k && k <= a[en]) {
            return searchInRotatedArray(a, mid + 1, en, k);
        } else {
            // Case d : Left Part
            return searchInRotatedArray(a, si, mid - 1, k);
        }
    }
}

/*
 * Binary Search on Rotated Sorted Array (Iterative)
 * In every iteration, one sorted half is identified and the
 * other half is discarded based on target position.
 * Time Complexity: O(log N)
 * Space Complexity: O(1)
 *
 *  Logic: step 1: find the pivot (index of smallest element) -> means which part is sorted
 *         step 2: determine which half to search based on target and pivot
 *         step 3: perform binary search in the identified half
 */

int searchInRotatedArrayIterative(const vec<int>& a, int k) {
    int n = sz(a);
    int lo = 0, hi = n - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        // Case Found
        if (a[mid] == k) return mid;

        // mid-on Line1: Left half is sorted
        if (a[lo] <= a[mid]) {
            // Case a : Target in left half
            if (a[lo] <= k && k < a[mid])
                hi = mid - 1;
           // Case b : Target in right half
            else
                lo = mid + 1;
        }
        // mid-on Line2: Right half is sorted
        else {
            // Case c : Target in right half
            if (a[mid] < k && k <= a[hi])
                lo = mid + 1;
            // Case d : Target in left half
            else
                hi = mid - 1;
        }
    }

    return -1; // Not found
}


void solve() {
    int n, k; cin >> n >> k;

    vec<int> a(n);
    read(a);

    // Recursive version
    int ans = searchInRotatedArray(a, 0, n - 1, k);
    cout << "Recursive: " << ans << nl;

    // Iterative version
    int ansIter = searchInRotatedArrayIterative(a, k);
    cout << "Iterative: " << ansIter << nl;
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

