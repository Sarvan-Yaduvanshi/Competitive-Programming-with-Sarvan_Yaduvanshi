/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-17 11:39:37
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
/* Problem: LeetCode 1878. Get Biggest Three Rhombus Sums in a Grid
 * Difficulty: Medium
 * You are given an m x n integer matrix grid.
 * A rhombus sum is the sum of the elements that form a regular rhombus shape in the grid.
 * The rhombus must have odd length sides and its center must be a cell of the grid.
 * The rhombus can be of different sizes, and it can be oriented in any direction.
 * Return the biggest three distinct rhombus sums in the grid in descending order.
 * If there are less than three distinct values, return all of them.
 *
 * Example 1:
 * Input: grid = [[3,4,5,1,3],[3,3,4,2,3],[20,30,200,40,10],[1,5,5,4,1],[4,3,2,2,5]]
 * Output: [228,216,211]
 * Explanation: The rhombus shapes with the biggest three distinct sums are shown above.
 * The rhombus sums are 228 (sum of the yellow cells), 216 (sum of the red cells) and 211 (sum of the blue cells).
 *
 * Example 2:
 * Input: grid = [[1,2,3],[4,5,6],[7,8,9]]
 * Output: [25,16]
 * Explanation: The rhombus shapes with the biggest two distinct sums are shown above.
 * The rhombus sums are 25 (sum of the yellow cells) and 16 (sum of the red cells).
 *
 * Example 3:
 * Input: grid = [[7,7,7]]
 * Output: [7]
 * Explanation: All rhombus shapes have the same sum of 7.
 *
 * Constraints:
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 50
 * 0 <= grid[i][j] <= 10^5
 *
 * VISUAL CONCEPTS & EXAMPLES (Saved as ASCII Diagrams):
 * =====================================================
 *
 * EXAMPLE 1: Multiple Rhombus Shapes in Grid (5x5)
 * Grid with values:
 *     0   1   2   3   4
 *  0 [3] [4] [5] [1] [3]
 *  1 [3] [3] [4] [2] [3]
 *  2 [20][30][200][40][10]
 *  3 [1] [5] [5] [4] [1]
 *  4 [4] [3] [2] [2] [5]
 *
 * Rhombus shapes (shown by coordinates):
 *
 *  BLUE RHOMBUS (size=1, center at 2,1):    RED RHOMBUS (size=1, center at 2,3):
 *       0   1   2   3                            0   1   2   3
 *    1 [ ] [*] [ ] [ ]                        1 [ ] [ ] [ ] [*]
 *    2 [*] [ ] [*] [ ]                        2 [ ] [ ] [*] [ ] [*]
 *    3 [ ] [*] [ ] [ ]                        3 [ ] [ ] [ ] [*]
 *
 *  GREEN RHOMBUS (size=1, center at 2,2):   PINK RHOMBUS (size=1, center at 2,3):
 *       1   2   3                                2   3   4
 *    1 [ ] [*] [ ]                            1 [ ] [*] [ ]
 *    2 [*] [ ] [*]                            2 [*] [ ] [*]
 *    3 [ ] [*] [ ]                            3 [ ] [*] [ ]
 *
 * Output: [228, 216, 211] - Three largest distinct rhombus sums
 *
 * EXAMPLE 2: Simple 3x3 Grid
 * Grid with values:
 *     0   1   2
 *  0 [1] [2] [3]
 *  1 [4] [5] [6]
 *  2 [7] [8] [9]
 *
 * Rhombus shapes (size=1):
 *
 *  Center at (0,1):  Center at (1,0):  Center at (1,1):   Center at (1,2):   Center at (2,1):
 *  [*]               [*]                    [*]               [*]                [*]
 *  [ ] [*] [ ]       [ ] [*]            [ ] [*] [ ]       [*] [ ]            [ ] [*] [ ]
 *  [ ] [ ]           [ ]                [ ] [ ] [ ]       [ ] [ ] [ ]        [ ] [ ] [ ]
 *  Sum=9             Sum=13             Sum=25             Sum=17             Sum=10
 *
 * Output: [25, 16] - Two largest distinct rhombus sums
 *
 * EXAMPLE 3: All Same Values
 * Grid: [[7, 7, 7]]
 * Output: [7] - Only one distinct rhombus sum
 *
 * HOW RHOMBUS WORKS:
 * ==================
 * A rhombus of "size" L has:
 *  - A center cell at (i, j)
 *  - Four directions from center: down-left, down-right, up-right, up-left
 *  - Each edge has L steps
 *  - Perimeter forms a diamond shape
 *
 * Visual representation for size L=1, center at (i,j):
 *         (i, j)           <- top vertex
 *        /       \
 *   (i+1,j-1)  (i+1,j+1)  <- left and right vertices
 *        \       /
 *      (i+2, j)           <- bottom vertex
 *
 * Walking the perimeter (L steps each direction):
 * Start at top -> go down-left -> down-right -> up-right -> up-left -> back to top
*/

vec<int> getBiggestThreeBruteForce(const vvec<int>& grid){
    int m = sz(grid);
    int n = sz(grid[0]);

    // use set or priority queue to maintain top 3 distinct sums
    // but used set here for simplicity, as it automatically handles duplicates and keeps sorted order
    // why not use priority queue? because only need top 3 distinct sums, not top k sums
    set<int> top3;

    // Lambda function to add a value to the top3 set and maintain only top 3 distinct values
    auto addToTop3 = [&](const int val){
        top3.insert(val);
        if (sz(top3) > 3)
            top3.erase(top3.begin()); // remove more than 3 smallest value, keep only top 3 largest values
    };

    // Iterate through every cell to treat it as the "Top Vertex"
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){

            // Base Case: Rhombus of size 0 (area 0) eg: single cell itself is a rhombus
            addToTop3(grid[i][j]);

            // Expand the rhombus size L from 1 to maximum possible based on grid boundaries
            for (int L = 1; ; L++){
                // Boundary check: Bottom, Left, Right
                // why i + 2 * L? because diamond shape like L upper and L lower, total 2L height, so i + 2L is the bottom vertex of the rhombus
                if (i + 2 * L >= m || j - L < 0 || j + L >= n)
                    break;

                int sum = 0;
                int r = i, c = j;

                // Walk the perimeter. L steps for each of the 4 edges.

                // 1. Move down-left (L steps)
                for (int k = 0; k < L; k++) sum += grid[r++][c--];
                // 2. Move down-right (L steps)
                for (int k = 0; k < L; k++) sum += grid[r++][c++];
                // 3. Move up-right (L steps)
                for (int k = 0; k < L; k++) sum += grid[r--][c++];
                // 4. Move up-left (this brings us exactly back to the top vertex)
                for (int k = 0; k < L; k++) sum += grid[r--][c--];

                addToTop3(sum);
            }
        }
    }

    // The set is ascending (e.g., [8, 9, 20]).
    // We need to return it descending ([20, 9, 8]).
    return vec<int>(rall(top3));
}
void solve() {
    int m, n;
    cin >> m >> n;

    vvec<int> grid(m, vec<int>(n));
    for (auto& row : grid){
        for (auto& val : row)
            cin >> val;
    }

    const vec<int> ans = getBiggestThreeBruteForce(grid);
    cout << "[";
    for (int i = 0; i < sz(ans); i++){
        cout << ans[i] << (i + 1 < sz(ans) ? "," : "");
    }
    cout << "]";
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



