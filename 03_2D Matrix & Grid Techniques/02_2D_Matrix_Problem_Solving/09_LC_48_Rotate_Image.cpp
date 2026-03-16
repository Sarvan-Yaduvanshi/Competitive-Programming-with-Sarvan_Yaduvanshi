/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-16 15:24:50
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

/* Problem: Rotate Image (LeetCode 48)
   Given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).
   You have to rotate the image in-place, which means you have to modify the input 2D matrix directly.
   DO NOT allocate another 2D matrix and do the rotation.

   Example:
   Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
   Output: [[7,4,1],[8,5,2],[9,6,3]]

  Constraints:
   - n == matrix.length == matrix[i].length
   - 1 <= n <= 20
   - -1000 <= matrix[i][j] <= 1000
*/

// Approach 1: Use Extra Space (Not in-place)
// Time Complexity: O(n^2), Space Complexity: O(n^2)
void rotateExtraSpace(vvec<int>& mat){
    int n = sz(mat);

    vvec<int> ans(n, vec<int>(n));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            ans[i][n - i - 1] = mat[i][j];
        }
    }

    mat = ans;
}

void solve() {
    int n;
    cin >> n;

    vvec<int> grid(n, vec<int>(n));
    for (auto& row : grid) {
        for (auto& val : row) {
            cin >> val;
        }
    }

    rotateExtraSpace(grid);
    cout << "[" << nl;
    for (int i = 0; i < n; i++){
        cout << "  [";
        for (int j = 0; j < n; j++){
            cout << grid[i][j];
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

