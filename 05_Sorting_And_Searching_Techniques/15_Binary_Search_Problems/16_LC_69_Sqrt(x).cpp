/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-05 14:01:21
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

/* Problem: LeetCode 69 - Sqrt(x)
 * Difficulty: Easy
 * Given a non-negative integer x, compute and return the square root of x.
 * The returned integer should be the truncated integer part of the square root.
 *
 * For example, do not use a built-in exponent function or operator, such as pow(x, 0.5) or x ** 0.5.
 *
 * Example 1:
 * Input: x = 4
 * Output: 2
 *
 * Example 2:
 * Input: x = 8
 * Output: 2
 * Explanation: The square root of 8 is approximately 2.82842, and since the decimal part is truncated, 2 is returned.
 *
 * Constraints:
 * - 0 <= x <= 2^31 - 1
 */

// Approach: Binary Search
// Time Complexity: O(log(x))
// Space Complexity: O(1)
i64 mySqrt(i64 x) {
    if (x < 2) return x; // Handle 0 and 1 quickly

    i64 lo = 0;
    i64 hi = x;
    i64 ans = 0;

    while (lo <= hi) {
        i64 mid = lo + (hi - lo) / 2;
        i64 mid_squared = mid * mid;

        if (mid_squared == x) {
            return mid; // Found exact square root
        } else if (mid_squared < x) {
            ans = mid; // Update answer to the largest mid that is less than sqrt(x)
            lo = mid + 1; // Search in the right half
        } else {
            hi = mid - 1; // Search in the left half
        }
    }

    return ans; // Return the truncated integer part of the square root
}

void solve() {
    i64 x; cin >> x;

    i64 result = mySqrt(x);
    cout << result << nl;
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

