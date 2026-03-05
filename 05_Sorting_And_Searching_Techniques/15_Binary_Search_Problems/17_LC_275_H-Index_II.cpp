/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-05 14:21:35
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

/* Problem: LeetCode 275 - H-Index II
 * Difficulty: Medium
 * Given an array of integers citations where citations[i] is the number of citations a researcher received for their ith paper and citations is sorted in an ascending order, return compute the researcher's h-index.
 * According to the definition of h-index on Wikipedia: "A scientist has an index h if h of their n papers have at least h citations each, and the other n − h papers have no more than h citations each."
 *
 * Example 1:
 * Input: citations = [0,1,3,5,6]
 * Output: 3
 * Explanation: [0,1,3,5,6] means the researcher has 5 papers in total and each of them had received 0, 1, 3, 5, 6 citations respectively. Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, their h-index is 3.
 *
 * Example 2:
 * Input: citations = [1,2,100]
 * Output: 2
 *
 * Constraints:
 * - n == citations.length
 * - 1 <= n <= 10^5
 * - 0 <= citations[i] <= 1000
 * - citations is sorted in ascending order.
 */

// Approach: Binary Search
// Time Complexity: O(log(n))
// Space Complexity: O(1)
int hIndex(const vec<int>& citations){
    int n = sz(citations);

    int lo = 0, hi = n;

    while (lo < hi){
        int mid = lo + (hi - lo) / 2;
        int h = n - mid; // Number of papers with at least citations[mid] citations

        if (citations[mid] >= h){
            hi = mid; // Try to find a smaller h
        } else {
            lo = mid + 1; // Need a larger h
        }
    }

    return n - lo; // h-index is n - lo
}

void solve() {
    int n; cin >> n;

    vec<int> citations(n);
    read(citations);

    int result = hIndex(citations);
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

