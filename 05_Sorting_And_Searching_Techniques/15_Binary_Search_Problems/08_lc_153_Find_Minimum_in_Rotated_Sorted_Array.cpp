/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-04 17:02:21
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

/* Problem: LeetCode 153 - Find Minimum in Rotated Sorted Array
   Link: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

   Given a rotated sorted array of unique integers, find the minimum element.
   The array was originally sorted in ascending order and then rotated at some pivot.

   * [4 5 6 7 0 1 2] if it was rotated 4 times, the original sorted array would be 0 1 2 4 5 6 7
   * [0,1,2,4,5,6,7] if it was rotated 7 times, the original sorted array would be 0 1 2 4 5 6 7

   Example 1:
   Input: [3,4,5,1,2]
   Output: 1
   Explanation: The original array was [1,2,3,4,5] rotated 3 times.

    Example 2:
    Input: [4,5,6,7,0,1,2]
    Output: 0
    Explanation: The original array was [0,1,2,4,5,6

    Example 3:
    Input: [11,13,15,17]
    Output: 11
    Explanation: The original array was [11,13,15,17] and it was rotated 4 times.

    Constraints:
    1 <= nums.length <= 5000
    -5000 <= nums[i] <= 5000
    All the integers of nums are unique.
    nums is sorted and rotated between 1 and nums.length times.

    Note: You must write an algorithm that runs in O(log n) time.
*/

/*
 * Algorithm: Find Minimum in Rotated Sorted Array (Unique Elements)
 * -----------------------------------------------------------------
 * Logic: Compare mid with 'hi' (the rightmost boundary of current search).
 * - If arr[mid] < arr[hi]: The right side is sorted. The min must be at mid or left.
 * - If arr[mid] > arr[hi]: The left side is sorted. The min must be to the right.
 *
 * Time Complexity : O(log N)
 * Space Complexity: O(1)
 */
int findMin(const vec<int>& nums) {
    int n = sz(nums);
    int lo = 0, hi = n - 1;

    // GM Note: Loop runs while lo < hi.
    // We stop when lo == hi (converged to the single minimum element).
    while (lo < hi){
        int mid = lo + (hi - lo) / 2;

        if (nums[mid] < nums[hi]) {
            // Case 1: Right side is smooth (e.g., [4, 5, 1, 2, 3] check 1 vs 3)
            // 'mid' might be the minimum, or the min is to the left.
            // We cannot discard 'mid', so we pull hi to mid.
            hi = mid;
        } else {
            // Case 2: Left side is smooth but mid > hi (e.g., [3, 4, 5, 1, 2] check 5 vs 2)
            // The rotation pivot is definitely to the right of mid.
            // We can safely discard 'mid' and everything left of it.
            lo = mid + 1;
        }
    }

    return nums[lo]; // At the end of loop, lo == hi pointing to the minimum element
}

void solve() {
    int n; cin >> n;
    vec<int> a(n); read(a);

    cout << findMin(a) << nl;

    // Alternative implementation using mid vs first element comparison
    /*
    int lo = 0;
    int hi = n - 1;
    int ans = 0;

    while (lo <= hi){
        int mid = lo + (hi - lo) / 2;
        if (a[mid] < a[0]){
            ans = mid;
            hi = mid - 1;
        } else lo = mid + 1;
    }
    cout << ans << nl;
    */
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

