/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-11 23:29:15
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

/* Problem: LeetCode 59 - Spiral Matrix II
 * Given a positive integer n, generate an n x n matrix filled with elements from 1 to n^2 in spiral order.
 *
 * Example 1:
 * Input: n = 3
 * Output: [[1,2,3],[8,9,4],[7,6,5]]
 *
 * Example 2:
 * Input: n = 1
 * Output: [[1]]
*/

// Time Complexity: O(n^2)
// Space Complexity: O(n^2)
vvec<int> generateMatrix(int n) {
    vvec<int> matrix(n, vec<int>(n));
    int val = 1; // Start filling from 1
    int top = 0, bottom = n - 1, left = 0, right = n - 1;

    while (top <= bottom && left <= right) {
        // Traverse from left to right -> fill the top row
        for (int i = left; i <= right; ++i) {
            matrix[top][i] = val++;
        }
        top++; // Move down to the next row

        // Traverse from top to bottom -> fill the right column
        for (int i = top; i <= bottom; ++i) {
            matrix[i][right] = val++;
        }
        right--; // Move left to the next column

        // Traverse from right to left -> fill the bottom row
        if (top <= bottom) {
            for (int i = right; i >= left; --i) {
                matrix[bottom][i] = val++;
            }
            bottom--; // Move up to the next row
        }

        // Traverse from bottom to top -> fill the left column
        if (left <= right) {
            for (int i = bottom; i >= top; --i) {
                matrix[i][left] = val++;
            }
            left++; // Move right to the next column
        }
    }

    return matrix;
}

void solve() {
    int n; cin >> n;

    vvec<int> ans = generateMatrix(n);
    cout << "[" << nl;
    for (int i = 0; i < n; ++i){
        cout << "  [";
        for (int j = 0; j < n; ++j){
            cout << ans[i][j];
            if (j < n - 1) cout << ",";
        }
        cout << "]";
        if (i < n - 1) cout << ",";
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

