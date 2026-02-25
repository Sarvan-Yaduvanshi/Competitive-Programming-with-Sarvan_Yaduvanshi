/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-25 12:39:45
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

/* Problem: Median in a row-wise sorted Matrix
 * Given a row-wise sorted matrix, find the median of the matrix.
 * Example:
 * Input: mat = [[1, 3, 5], [2, 6, 9], [3, 6, 9]]
 * Output: 5
 * Explanation: The sorted order of the elements is [1, 2, 3, 3, 5, 6, 6, 9, 9]. The median is 5.
 * Approach:
 * 1. The median is the middle element in the sorted order. For a matrix of size n x m, the median is the (n*m + 1)/2-th smallest element.
 * 2. We can use binary search on the value range of the elements in the matrix. The minimum value is mat[0][0] and the maximum value is mat[n-1][m-1].
 * 3. For each mid value, count how many elements in the matrix are less than or equal to mid. This can be done efficiently since each row is sorted.
 * 4. If the count is less than (n*m + 1)/2, we need to search in the higher half (lo = mid + 1), otherwise we search in the lower half (hi = mid).
 * 5. The binary search will converge to the median value.
 * Time Complexity: O(n log(max - min)), where max and min are the maximum and minimum elements in the matrix.
 * Space Complexity: O(1)
 */

int medianInRowWiseSortedMat(const vvec<int>& mat){

}

void solve() {
    
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

