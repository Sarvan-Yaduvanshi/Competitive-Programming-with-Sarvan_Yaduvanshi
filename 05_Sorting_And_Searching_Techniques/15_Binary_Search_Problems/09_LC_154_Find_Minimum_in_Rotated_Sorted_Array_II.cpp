/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-05 09:21:31
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

/* Problem: LeetCode 54 - Find Minimum in Rotated Sorted Array II
 * Difficulty: Hard
 * Suppose an array of length n sorted in ascending order is rotated between 1 and n times.
 * For example, the array nums = [0,1,4,4,5,6,7] might become:
 * After 1 rotation: [7,0,1,4,4,5,6]
 * After 2 rotations: [6,7,0,1,4,4,5]
 * After 3 rotations: [5,6,7,0,1,4,4]
 * After 4 rotations: [4,5,6,7,0,1,4]
 * After 7 rotations: [0,1,4,4,5,6,7]
 *
 * Given the sorted rotated array nums that may contain duplicates, return the minimum element of this array.
 * You must decrease the overall operation steps as much as possible.
 *
 * Example 1:
 * Input: nums = [1,3,5]
 * Output: 1
 *
 * Example 2:
 * Input: nums = [2,2,2,0,1]
 * Output: 0
 *
 * Constraints:
 * n == nums.length
 * 1 <= n <= 5000
 * -5000 <= nums[i] <= 5000
 * nums is sorted and rotated between 1 and n times.
 *
 * Follow up: This problem is similar to Find Minimum in Rotated Sorted Array,
 * but nums may contain duplicates. Would this affect the run-time complexity? How and why?
 *
* Answer: Duplicates can increase the worst-case time complexity from O(log n) to O(n).
          Because when nums[mid] == nums[hi], we can’t determine which half contains the minimum,
          so we shrink the search space by only hi-- (or lo++) instead of discarding half.
          In cases like [2,2,2,2,2], this becomes linear.
 */

// Time Complexity -> O(logN) in average case, O(N) in worst case (when all elements are duplicates)

int findMin(const vec<int>& nums) {
    int lo = 0;
    int hi = sz(nums) - 1;

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        if (nums[mid] > nums[hi]) {
            // Minimum must be in the right half
            lo = mid + 1;
        } else if (nums[mid] < nums[hi]) {
            // Minimum must be in the left half (including mid)
            hi = mid;
        } else {
            // nums[mid] == nums[hi], we can’t determine the side, shrink search space
            hi--;
        }
    }

    return nums[lo];
}

void solve() {
    int n;
    cin >> n;
    vec<int> nums(n);
    read(nums);

    int minElement = findMin(nums);
    cout << minElement << nl;
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

