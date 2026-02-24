/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-24 20:42:25
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

/* Problem: Search in a 2D Matrix II
 * URL: https://leetcode.com/problems/search-a-2d-matrix-ii/
 * Level: Medium
 * Tags: Array, Binary Search, Divide and Conquer
 *
 * Given an m x n matrix and a target value, return true if the target value exists in the matrix or false otherwise.
 * The matrix has the following properties:
 * - Integers in each row are sorted in ascending from left to right.
 * - Integers in each column are sorted in ascending from top to bottom.
 *
 * Example 1:
 * Input: matrix = [[1,4,7,11,15],
 *                  [2,5,8,12,19],
 *                  [3,6,9,16,22],
 *                  [10,13,14,17,24],
 *                  [18,21,23,26,30]], target = 5
 * Output: true
 *
 * Example 2:
 * Input: matrix = [[1,4,7,11,15],
 *                  [2,5,8,12,19],
 *                  [3,6,9,16,22],
 *                  [10,13,14,17,24],
 *                  [18,21,23,26,30]], target = 20
 * Output: false
 *
 * Constraints:
 * - m == matrix.length
 * - n == matrix[i].length
 * - 1 <= m, n <= 300
 * - -10^9 <= matrix[i][j] <= 10^9
 * - All the integers in each row are sorted in ascending order.
 * - All the integers in each column are sorted in ascending order.
 * - -10^9 <= target <= 10^9
 */

// Approach 1: Brute Force Search(Linear Search)
// Time Complexity: O(m*n) | Space Complexity: O(1)
bool searchMatrixBruteForce(const vvec<int>& mat, int k){
    int m = sz(mat);
    int n = sz(mat[0]);

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (mat[i][j] == k) return true;
        }
    }

    return false;
}

/*
 *  - Approach 2: Staircase Search in Row+Col Sorted Matrix
 *  For matrix where:
 *  - Each row is sorted left to right
 *  - Each column is sorted top to bottom
 *  (But first element of next row is NOT necessarily > last of previous row)
 *
 *  Start from TOP-RIGHT corner (or BOTTOM-LEFT corner).
 *
 *  From top-right (0, M-1):
 *  - If current == target → Found!
 *  - If current > target → Move LEFT (smaller values)
 *  - If current < target → Move DOWN (larger values)
 *
 *  LC #240: Search a 2D Matrix II
 *  Time: O(N + M), Space: O(1)
 *
 *  Example:
 *   1   4   7  11  15
 *   2   5   8  12  19
 *   3   6   9  16  22
 *  10  13  14  17  24
 *  18  21  23  26  30
 *
 *  Target = 5:
 *  Start at (0,4)=15 > 5 → left
 *  (0,3)=11 > 5 → left
 *  (0,2)=7 > 5 → left
 *  (0,1)=4 < 5 → down
 *  (1,1)=5 = 5 → Found!
 */
bool searchMatrixOptimized(const vvec<int>& mat, int k){
    int m = sz(mat);
    int n = sz(mat[0]);

    int row = 0;
    int col = n - 1;

    while (row < m && col >= 0){
        if (mat[row][col] == k) return true;
        else if (mat[row][col] < k) row++;
        else col--;
    }

    return false;
}

void solve() {
    int m, n, target;
    cin >> m >> n >> target;

    vvec<int> mat(m, vec<int>(n));
    for (auto& row: mat){
        for (auto& val: row){
            cin >> val;
        }
    }

    // cout << (searchMatrixBruteForce(mat, target) ? "YES" : "NO") << nl;
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

