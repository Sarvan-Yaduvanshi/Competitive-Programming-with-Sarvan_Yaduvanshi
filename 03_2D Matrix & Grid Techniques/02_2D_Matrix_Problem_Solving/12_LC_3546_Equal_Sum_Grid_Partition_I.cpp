/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-26 09:27:37
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

/* Problem: LeetCode 3546. Equal Sum Grid Partition I
 * Difficulty: Medium
 * You are given an m x n matrix grid of positive integers.
 * Your task is to determine if it is possible to make either one horizontal or one vertical cut on the grid such that:
 *           1. Each of the two resulting sections formed by the cut is non-empty.
 *           2. The sum of the elements in both sections is equal.
 *           3. Return true if such a partition exists; otherwise return false.
 *
 * Example 1:
 * Input: grid = [[1, 4], [2, 3]]
 * Output: true
 * Explanation: A horizontal cut between row 0 and row 1 results in two non-empty sections, each with a sum of 5. Thus, the answer is true.
 *
 * Example 2:
 * Input: grid = [[1, 3], [2, 4]]
 * Output: false
 * Explanation: There is no way to cut the grid into two non-empty sections with equal sums. Thus, the answer is false.
 *
 * Constraints:
 * - m == grid.length
 * - n == grid[i].length
 * - 1 <= m, n <= 10^5
 * - 2 <= m * n <= 10^5
 * - 1 <= grid[i][j] <= 10^4
 */

// Approach 1: Brute Force
// The Brute Force Algorithm:
//  1. Enumerate Horizontal Cuts: Try to cutting after row 0, after row 1, ..., after row m-2. For each cut, calculate the sum of the upper and lower sections and check if they are equal.
//  2. Enumerate Vertical Cuts: Try cutting after column 0, after column 1, ..., after column n-2. For each cut, calculate the sum of the left and right sections and check if they are equal.
//  3. If any cut results in equal sums, return true. If after checking all cuts no equal sum is found, return false.
// Time Complexity: O(m * (m * n) + n * (m * n)) = O(m^2 * n + m * n^2) which is not efficient for large matrices.
// if m = 10^5 and n = 1, becomes (10^5)^2 * 1 + 10^5 * 1^2 = 10^10 Gives TLE for large inputs.
bool canPartitionGridBruteForce(const vvec<int>& grid){
    int m = sz(grid);
    int n = sz(grid[0]);

    // 1. Try all possible HORIZONTAL cuts
    // We can cut after row 0 up to row m-2
    for (int cutRow = 0; cutRow < m - 1; cutRow++){
        i64 topSum = 0;
        i64 bottomSum = 0;

        // Calculate sum of the TOP section (rows 0 to cutRow)
        for (int i = 0; i <= cutRow; i++){
            for (int j = 0; j < n; j++){
                topSum += grid[i][j];
            }
        }

        // Calculate sum of the BOTTOM section (rows cutRow + 1 to m - 1)
        for (int i = cutRow + 1; i < m; i++){
            for (int j = 0; j < n; j++){
                bottomSum += grid[i][j];
            }
        }

        // Check if this cut splits the grid equally
        if (topSum == bottomSum) return true;
    }

    // 2. Try all possible VERTICAL cuts
    // We can cut after col 0 up to col n-2
    for (int cutCol = 0; cutCol < n - 1; cutCol++){
        i64 leftSum = 0;
        i64 rightSum = 0;

        // Calculate sum of the LEFT section (cols 0 to cutCol)
        for (int i = 0; i < m; i++){
            for (int j = 0; j <= cutCol; j++){
                leftSum += grid[i][j];
            }
        }

        // Calculate sum of the RIGHT section (cols cutCol + 1 to n - 1)
        for (int i = 0; i < m; i++){
            for (int j = cutCol + 1; j < n; j++){
                rightSum += grid[i][j];
            }
        }

        // Check if this cut splits the grid equally
        if (leftSum == rightSum) return true;
    }

    return false; // If no cut worked, return false
}

// Approach 2: Use prefix sum to optimize the sum calculations
// The Optimized Algorithm:
//  1. Precompute Row and Column Sums: Create two arrays, rowSum and colSum, where rowSum[i] is the sum of the i-th row and colSum[j] is the sum of the j-th column. This allows us to quickly calculate the sum of any section of the grid in O(1) time after an O(m * n) preprocessing step.
//  2. Check Horizontal Cuts: Iterate through possible horizontal cuts and use the precomputed row sums to calculate the sum of the top and bottom sections in O(1) time. If any cut results in equal sums, return true.
//  3. Check Vertical Cuts: Similarly, iterate through possible vertical cuts and use the precomputed column sums to calculate the sum of the left and right sections in O(1) time. If any cut results in equal sums, return true.
//  4. If no cut results in equal sums, return false.
// Time Complexity: O(m * n) for precomputing sums + O(m) for checking horizontal cuts + O(n)
// Space Complexity: O(m + n) for storing row and column sums, which is efficient for large matrices.
bool canPartitionGrid(vvec<int>& grid){
    int m = sz(grid);
    int n = sz(grid[0]);

    vec<i64> rowSum(m, 0);
    vec<i64> colSum(n, 0);
    i64 totalSum = 0;

    // 1. Precompute the sums in a single pass O(m * n)
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            int val = grid[i][j];
            rowSum[i] += val;
            colSum[j] += val;
            totalSum += val;
        }
    }

    // Optimized if all sum is odd than impossible to cut matrix
    // totalSum = topSum + bottomSum, equal value than totalSum = topSum + topSum
    // Because 2 * anything is always an even number, it is mathematically impossible to split the grid equally if the totalSum is odd.
    if (totalSum & 1) return false;

    // Since it's even, we know exactly what half the sum is
    i64 targetSum = totalSum / 2;

    // 2. Check Horizontal Cuts O(m)
    i64 runningTopSum = 0;
    // Iterate up to m - 1 because the bottom section cannot be empty
    for (int i = 0; i < m - 1; i++){
        runningTopSum += rowSum[i];
        // i64 bottomSum = totalSum - runningTopSum;
        if (runningTopSum == targetSum) return true;
    }

    // 3. Check Vertical Cuts O(n)
    i64 runningLeftSum = 0;
    // Iterate up to n - 1 because the right section cannot be empty
    for (int i = 0; i < n - 1; i++){
        runningLeftSum += colSum[i];
        // i64 rightSum = totalSum - runningLeftSum;
        if (runningLeftSum == targetSum) return true;
    }

    return false;
}

// Approach 3: Same logic use prefix sum but optimized space
// Time Complexity: O(m * n)
// Space Complexity: O(1)
bool canPartitionGridOptimized(vvec<int>& grid){
    int m = sz(grid);
    int n = sz(grid[0]);

    i64 totalSum = 0;
    // Step 1: total sum
    for (auto& row : grid){
        for (auto& val : row){
            totalSum += val;
        }
    }

    // Optimized if all sum is odd than impossible to cut matrix
    if (totalSum & 1) return false;

    i64 targetSum = totalSum / 2;

    // Step 2: horizontal cuts
    i64 runningTopSum = 0;
    for (int i = 0; i < m - 1; i++){
        i64 rowSum = 0;
        for (int j = 0; j < n; j++)
            rowSum += grid[i][j];

        runningTopSum += rowSum;
        if (runningTopSum == targetSum) return true;
    }

    // Step 3: vertical cuts
    i64 runningLeftSum = 0;
    for (int j = 0; j < n - 1; j++){
        i64 colSum = 0;
        for (int i = 0; i < m; i++)
            colSum += grid[i][j];

        runningLeftSum += colSum;
        if (runningLeftSum == targetSum) return true;
    }

    return false;
}

void solve() {
    int m, n;
    cin >> m >> n;

    vvec<int> grid(m, vec<int>(n));
    for (auto& row : grid)
        for (int& x : row) cin >> x;

    cout << (canPartitionGridOptimized(grid) ? "Yes" : "No") << nl;
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

