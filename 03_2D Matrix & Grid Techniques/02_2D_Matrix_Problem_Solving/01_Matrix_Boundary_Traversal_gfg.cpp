/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-08 15:33:22
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

/* Problem: Matrix Boundary Traversal
 * Platform: GeeksforGeeks | Difficulty: Easy
 * You are given a matrix mat[][] . Return the boundary traversal on the matrix
 * in a clockwise manner starting from the first row of the matrix.
 * Example 1:
 * Input:
 * N = 4, M = 4
 * mat[][] = {{1, 2, 3, 4},
 *            {5, 6, 7, 8},
 *            {9, 10, 11, 12},
 *            {13, 14, 15, 16}}
 * Output: 1 2 3 4 8 12 16 15 14 13 9 5
 * Explanation: The boundary traversal of the matrix is: 1 2 3 4 8 12 16 15 14 13 9 5.
 *
 * Example 2:
 * Input:
 * N = 2, M = 2
 * mat[][] = {{12, 11},
 *           {4, 3}}
 * Output: 12, 11, 3, 4
 * Explanation: The boundary traversal of the matrix is: 12, 11, 3, 4.
 */

// Time Complexity: O(N*M) | Space Complexity: O(N+M)
vec<int> boundaryTraversal(const vvec<int>& mat){
    vec<int> result;

    if (mat.empty() || mat[0].empty()) return result;

    int top = 0;
    int bottom = sz(mat) - 1;
    int left = 0;
    int right = sz(mat[0]) - 1;

    // Step 1: Top row → (left to right)
    for (int i = left; i <= right; i++)
        result.pb(mat[top][i]);
    top++;

    // Step 2: Right column ↓ (top to bottom)
    for (int i = top; i <= bottom; i++)
        result.pb(mat[i][right]);
    right--;

    // Handle single row
    if (top <= bottom){
        // Step 3: Bottom row ← (right to left)
        for (int i = right; i >= left; i--)
            result.pb(mat[bottom][i]);
        bottom--;
    }

    // Handle single column
    if (left <= right){
        // Step 4: Left column ↑ (bottom to top)
        for (int i = bottom; i >= top; i--)
            result.pb(mat[i][left]);
        left++;
    }

    return result;
}


void solve() {
    int n, m;
    cin >> n >> m;

    vvec<int> mat(n, vec<int>(m));
    for (auto& row : mat){
        for (auto& val : row){
            cin >> val;
        }
    }

    vec<int> boundary = boundaryTraversal(mat);
    cout << "[";
    for (int i = 0; i < sz(boundary); i++){
        cout << boundary[i] << (i == sz(boundary) - 1 ? "" : ", ");
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

