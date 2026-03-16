/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-11 23:48:18
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

/* Problem: LeetCode 885 - Spiral Matrix III
 * Given the dimensions of a grid (R rows and C columns) and a starting point (r0, c0),
 * return the coordinates of all cells in the grid in the order they are visited in a spiral pattern starting from (r0, c0).
 *
 * Example:
 * Input: R = 5, C = 6, r0 = 1, c0 = 4
 * Output: [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[3,1],[3,0],[2,0],[1,0],[0,0],[0,1],[0,2],[1,2],[2,2],[4,5],[4,4],[4,3],[4,2],[4,1],[4,0]]
 *
 * Example: R = 1, C = 4, r0 = 0, c0 = 0
 * Output: [[0,0],[0,1],[0,2],[0,3]]
 *
 * Note:
 * 1 <= R, C <= 100
 * 0 <= r0 < R
 * 0 <= c0 < C
 * The total number of cells in the grid is R * C.
 *
 *  Start from position (rStart, cStart) and walk in clockwise spiral.
 *  Return all cells of the R×C grid in the order visited.
 *  (Cells outside the grid are skipped but the spiral continues.)
 *
 *  Pattern: Go 1 step right, 1 step down, 2 steps left, 2 steps up,
 *           3 steps right, 3 steps down, 4 steps left, 4 steps up, ...
 *  Steps increase by 1 after every 2 direction changes.
 *
 *  Time: O(max(R,C)²), Space: O(R×C)
*/

vvec<int> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
    vvec<int> ans;
    int totalCells = rows * cols;

    int dr[] = {0, 1, 0, -1}; // Right, Down, Left, Up
    int dc[] = {1, 0, -1, 0};

    int r = rStart;
    int c = cStart;
    int d = 0; // Direction index
    int steps = 1; // Number of steps to take in the current direction

    ans.pb({r, c}); // start ceil is always included

    while (sz(ans) < totalCells){
        for (int rep = 0; rep < 2; rep++){ // Two directions per step-size than repeat as cycle
            for (int s = 0; s < steps; s++){
                r += dr[d]; // Move in the current direction
                c += dc[d];

                if (r >= 0 && r < rows && c >= 0 && c < cols) // Check if the new position is within bounds
                    ans.pb({r, c});
            }

            d = (d + 1) % 4; // Change direction (Right → Down → Left → Up → Right ...)
        }

        steps++; // Increase the number of steps after every 2 direction changes
    }
    return ans;
}

void solve() {
    int rows, cols, rStart, cStart;
    cin >> rows >> cols >> rStart >> cStart;

    auto ans = spiralMatrixIII(rows, cols, rStart, cStart);

    cout << "[" << nl;
    for (int i = 0; i < sz(ans); i++) {
        cout << "  [" << ans[i][0] << "," << ans[i][1] << "]";
        if (i + 1 < sz(ans)) cout << ",";
        cout << nl;
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

