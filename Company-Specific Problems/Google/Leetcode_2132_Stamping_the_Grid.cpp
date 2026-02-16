/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-10 15:23:13
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

/* Problem: LeetCode 2132 - Stamping the Grid
 * You are given a 0-indexed 2D binary matrix grid of size m x n, where 0 represents an empty cell and 1 represents a filled cell. You are also given a stamp of size stampHeight x stampWidth that you want to place on the grid.
 * The stamp can only be placed on empty cells, and it must be fully covered by the grid. The stamp can be placed multiple times on the grid, and it can overlap with itself. However, it cannot overlap with any filled cell (1) in the grid.
 * Return true if it is possible to place the stamp on the grid such that all empty cells (0) are covered at least once by the stamp. Otherwise, return false.
 * Example:
 * Input: grid = [[1,0,0],[0,0,0],[0,0,1]], stampHeight = 2, stampWidth = 2
 * Output: true
 * Explanation: We can place the stamp at position (0, 1) and (1, 1) to cover all empty cells.
 * Constraints:
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 1000
 * grid[i][j] is either 0 or 1.
 * 1 <= stampHeight <= m
 * 1 <= stampWidth <= n
*/

/* Logic:
 * 1. 2D Prefix Sum: Precompute grid sums to check if a stamp region is occupied in O(1).
 * 2. Greedy Strategy: Try to place a stamp at every possible top-left coordinate (i, j).
 * If the region is strictly empty (sum == 0), we stamp it.
 * 3. 2D Difference Array: Instead of updating the grid (O(H*W)), use a diff array to mark
 * the stamped rectangle in O(1).
 * 4. Sweep Line/Accumulation: Compute the prefix sum of the diff array to determine
 * actual coverage.
 * 5. Final Validation: If any cell is empty (0) but has 0 coverage, it's impossible.
 *
 * Time Complexity: O(N * M)
 * - dominated by three linear passes over the grid.
 * Space Complexity: O(N * M)
 * - for the prefix sum and difference arrays.
 */
bool possibleStamping(const vec<vec<int>>& grid, int stampHeight, int stampWidth){
    int rows = sz(grid);
    int cols = sz(grid[0]);

    // 1. Build 2D Prefix Sum (1-based indexing for boundary safety)
    vvec<int> pref(rows + 1, vec<int>(cols + 1));
    for (int i = 1; i <= rows; i++){
        for (int j = 1; j <= cols; j++){
            pref[i][j] = grid[i - 1][j - 1]
                       + pref[i - 1][j]
                       + pref[i][j - 1]
                       - pref[i - 1][j - 1];
        }
    }

    // 2. Diff Array to mark covered areas (Size +2 for easy boundary handling)
    vvec<int> stampDiff(rows + 2, vec<int>(cols + 2, 0));

    // Try placing stamp at every valid top-left (i, j)
    for (int i = 1; i + stampHeight - 1 <= rows; i++) {
        for (int j = 1; j + stampWidth - 1 <= cols; j++){
            // Check if region (i,j) to (i+h-1, j+w-1) is empty using Prefix Sum
            int bottomRow = i + stampHeight - 1;
            int rightCol = j + stampWidth - 1;

            // Calculate sum of the area covered by the stamp
            int areaSum = pref[bottomRow][rightCol]
                        - pref[bottomRow][j - 1]
                        - pref[i - 1][rightCol]
                        + pref[i - 1][j - 1];

            // If areaSum is 0, it means all cells in this area are empty (0)
            if (areaSum == 0){
                // Apply 2D Difference Update: Add +1 to the rectangle
                stampDiff[i][j]++;
                stampDiff[i][rightCol + 1]--;
                stampDiff[bottomRow + 1][j]--;
                stampDiff[bottomRow + 1][rightCol + 1]++;
            }
        }
    }

    // 3. Accumulate Diff Array & Validate
    // Note: We can reuse the diff array to store the running sum
    for (int i = 1; i <= rows; i++){
        for (int j = 1; j <= cols; j++){
            stampDiff[i][j] += stampDiff[i- 1][j]
                            +  stampDiff[i][j - 1]
                            -  stampDiff[i - 1][j - 1];

            if (grid[i - 1][j - 1] == 0 && stampDiff[i][j] == 0)
                return false;
        }
    }

    return true;
}

void solve() {
    int n, m;
    if (!(cin >> n >> m));

    vvec<int> grid(n, vec<int>(m));
    for (auto& row : grid)
        for (auto& cell : row)
            cin >> cell;

    int stampHeight, stampWidth;
    cin >> stampHeight >> stampWidth;

    bool ans = possibleStamping(grid, stampHeight, stampWidth);
    cout << (possibleStamping(grid, stampHeight, stampWidth) ? "True" : "False") << endl;
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

