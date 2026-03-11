/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-11 18:51:28
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

/* Problem: LeetCode 867 - Transpose Matrix
   Given a 2D integer array matrix, return the transpose of matrix.
   The transpose of a matrix is the matrix flipped over its main diagonal, switching the matrix's row and column indices.

   Example 1:
   Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
   Output: [[1,4,7],[2,5,8],[3,6,9]]

   Example 2:
   Input: matrix = [[1,2,3],[4,5,6]]
   Output: [[1,4],[2,5],[3,6]]

   Transpose matrix two types 1. Square matrix 2. Rectangular matrix
   1. Square matrix: The number of rows and columns are the same (m == n). In this case,
   the transpose can be achieved by swapping elements across the main diagonal.
   2. Rectangular matrix: The number of rows and columns are different (m != n). In this case,
   the transpose will have dimensions n x m, and we need to create a new matrix to store the transposed values.
   so space complexity is O(1) for square matrix and O(m*n) for rectangular matrix

   Constraints:
   m == matrix.length
   n == matrix[i].length
   1 <= m, n <= 1000
   1 <= m * n <= 10^5
   -10^9 <= matrix[i][j] <= 10^9
*/

// Time Complexity: O(m*n) | Space Complexity: O(1)
// Approach: In-place Transposition for Square Matrices
// why j = i + 1 is used -> Because we only need to traverse the upper triangular
// part of the matrix to avoid swapping elements twice during transpose.
// For example, in a 3x3 matrix, when i = 0, we swap elements at (0,1) and (1,0), and (0,2) and (2,0).
vec<vec<int>> transpose(vec<vec<int>>& matrix){
    int m = sz(matrix);
    int n = sz(matrix[0]);

    for (int i = 0; i < m; i++){
        for (int j = i + 1; j < n; j++){
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    return matrix;
}

// 2. Rectangular matrix: O(m*n) time and O(m*n) space
// Logic: Loop 0 to n and 0 to m and assign result[j][i] = matrix[i][j]
vec<vec<int>> transposeRectangular(const vec<vec<int>>& matrix){
    int m = sz(matrix);
    int n = sz(matrix[0]);

    vec<vec<int>> result(n, vec<int>(m));
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}

void solve() {
    int m, n;
    cin >> m >> n;

    vec<vec<int>> matrix(m, vec<int>(n));
    for (auto& row : matrix){
        for (auto& val : row){
            cin >> val;
        }
    }

    // vec<vec<int>> result = transpose(matrix); // For square matrix
    vec<vec<int>> result = transposeRectangular(matrix); // For rectangular matrix
    cout << "[";
    for (int i = 0; i < sz(result); i++){
        cout << "[";
        for (int j = 0; j < sz(result[i]); j++){
            cout << result[i][j];
            if (j < sz(result[i]) - 1) cout << ",";
        }
        cout << "]";
        if (i < sz(result) - 1) cout << ",";
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

