/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-05 14:44:01
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

/* Problem: LeetCode 3453 - Separate Squares I
 * Difficulty: Medium
* You are given a 2D integer array squares. Each squares[i] = [xi, yi, li]
* represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.
* Find the minimum y-coordinate value of a horizontal line such that
* the total area of the squares above the line equals the total area of the squares below the line.
*
* Answers within 10^-5 of the actual answer will be accepted.
* Note: Squares may overlap. Overlapping areas should be counted multiple times.
*
* Example 1:
* Input: squares = [[0, 0, 1], [2, 2, 1]]
* Output: 1.00000
* Explanation: The line y = 1 divides the area of the two squares into two equal parts.
* The area above the line is 1 and the area below the line is also 1
*
* Example 2:
* Input: squares = [[0, 0, 2], [1, 1, 1]]
* Output: 1.16667
* The areas are:
* Below the line: 7/6 * 2 (Red) + 1/6 (Blue) = 15/6 = 2.5.
* Above the line: 5/6 * 2 (Red) + 5/6 (Blue) = 15/6 = 2.5.
* Since the areas above and below the line are equal, the output is 7/6 = 1.16667.
*/

double separateSquares(const vec<vec<int>>& squares){
    double totalArea = 0;
    double minY = 2e9, maxY = 0;

    // 1. Calculate Total Area and Search Bounds
    for (const auto& sq : squares) {
        double y = sq[1];
        double l = sq[2];
        totalArea += l * l;
        minY = min(minY, y);
        maxY = max(maxY, y + l);
    }

    double target = totalArea / 2.0;
    double low = minY, high = maxY;

    for (int i = 0; i < 100; i++) {
        double mid = low + (high - low) / 2.0;

        double currentArea = 0;
        for (const auto& sq : squares) {
            double y = sq[1];
            double l = sq[2];
            double top = y + l;

            if (top <= mid) {
                // Fully below
                currentArea += l * l;
            } else if (y >= mid) {
                // Fully above
                currentArea += 0;
            } else {
                // Partial overlap
                currentArea += l * (mid - y);
            }
        }

        // 3. Decision Logic
        // If we have enough area (or more), we try to find a smaller Y (move high down)
        if (currentArea >= target) {
            high = mid;
        } else {
            low = mid;
        }
    }

    return high;
}

void solve() {
    int n; cin >> n;
    vec<vec<int>> squares(n, vec<int>(3));
    for (int i = 0; i < n; i++) {
        cin >> squares[i][0] >> squares[i][1] >> squares[i][2];
    }

    double result = separateSquares(squares);
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

