/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-24 21:38:21
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

/* Problem: Leetcode 74 - Search a 2D Matrix
 * URL: https://leetcode.com/problems/search-a-2d-matrix/
 * Difficulty: Medium
 * Tags: Binary Search, Matrix
 * Company: Microsoft, Amazon, Apple, Google
 * You are given an m x n integer matrix matrix with the following two properties:
 * - Each row is sorted in non-decreasing order.
 * - The first integer of each row is greater than the last integer of the previous row.
 * Given an integer target, return true if target is in matrix or false otherwise.
 * You must write a solution in O(log(m * n)) time complexity.
 * Example 1:
 * Input: matrix = [[1,3,5,7],
 *                  [10,11,16,20],
 *                  [23,30,34,60]], target = 3
 * Output: true
 * Example 2:
 * Input: matrix = [[1,3,5,7],
 *                  [10,11,16,20],
 *                  [23,30,34,60]], target = 13
 * Output: false
 */

// Approach 1: Binary Search on 2D Matrix
// Time Complexity: O(log(m*n)) | Space Complexity: O(1)
bool searchInRow(const vvec<int>& mat, int k, int row){
    int n = sz(mat[0]);

    int stCol = 0;
    int endCol = n - 1;

    while (stCol <= endCol){
        int midCol = stCol + (endCol - stCol) / 2;

        if (mat[row][midCol] == k) return true;
        else if (mat[row][midCol] < k) stCol = midCol + 1;
        else endCol = midCol - 1;
    }

    return false;
}
bool searchMatrix(vvec<int>& mat, int k){
    int m = sz(mat);
    int n = sz(mat[0]);

    int stRow = 0;
    int endRow = m - 1;

    while (stRow <= endRow){
        int midRow = stRow + (endRow - stRow) / 2;

        if (k >= mat[midRow][0] && k <= mat[midRow][n - 1])
            return searchInRow(mat, k, midRow);
        else if (mat[midRow][n - 1] < k) stRow = midRow + 1;
        else endRow = midRow - 1;
    }

    return false;
}

/*
 *  - Approach 2: Treat 2D Matrix as 1D Array and Binary Search
 *  Matrix where:
 *  - Each row is sorted left to right
 *  - First element of each row > last element of previous row
 *
 *  This means the entire matrix is sorted in row-major order!
 *  Treat it as a 1D sorted array of size N×M.
 *
 *  Index mapping:
 *  1D index k → row = k / M, col = k % M
 *
 *  LC #74: Search a 2D Matrix
 *  Time: O(log(N×M)), Space: O(1)
 *
 *  Example:
 *   1   3   5   7
 *  10  11  16  20
 *  23  30  34  60
 *
 *  Target = 3 → Found at (0, 1)
 */
bool searchMatrixOptimized(vvec<int>& mat, int k){
    int m = sz(mat);
    int n = sz(mat[0]);

    int lo = 0;
    int hi = m * n - 1;

    while (lo <= hi){
        int mid = lo + (hi - lo) / 2;
        int r = mid / n;
        int c = mid % n;

        if (mat[r][c] == k) return true;
        else if (mat[r][c] < k) lo = mid + 1;
        else hi = mid - 1;
    }

    return false;
}

void solve() {
    int m, n, target;
    cin >> m >> n >> target;

    vvec<int> mat(m, vec<int>(n));
    for (auto& row : mat){
        for (auto& val : row){
            cin >> val;
        }
    }

    cout << (searchMatrixOptimized(mat, target) ? "YES" : "NO") << nl;
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

