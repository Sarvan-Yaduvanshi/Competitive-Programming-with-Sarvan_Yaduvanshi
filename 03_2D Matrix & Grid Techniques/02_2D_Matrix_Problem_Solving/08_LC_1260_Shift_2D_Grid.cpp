/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-16 10:49:55
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

/* Problem: LeetCode 1260 - Shift 2D Grid
   Given a 2D grid of size m x n and an integer k, shift the grid to the right by k positions.
   The elements that fall off the right end will appear at the left end of the next row.
   The last element of the last row will wrap around to the first element of the first row.

   Example:
   Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 1
   Output: [[9,1,2],[3,4,5],[6,7,8]]

   Example:
   Input: grid = [[3,8,1,9],[19,7,2,5],[4,6,11,10],[12,0,21,13]], k = 4
   Output: [[12,0,21,13],[3,8,1,9],[19,7,2,5],[4,6,11,10]]

   Constraints:
   - m == grid.length
   - n == grid[i].length
   - 1 <= m <= 50
   - 1 <= n <= 50
   - -1000 <= grid[i][j] <= 1000
   - 0 <= k <= 100
*/

// Approach:
//           Step 1: Flatten the 2D grid into a 1D array,
//           Step 2: rotate the array by k positions,
//           Step 3: and then reshape it back into a 2D grid.
// * What One Shift Means :- grid[i][j] → grid[i][j+1] -> shift right by 1 position
//                           last column → next row first column
//                           last element → first element
// Time Complexity: O(m*n) for flattening and reshaping, O(m*n) for rotation, overall O(m*n).

vvec<int> shiftGrid(const vvec<int>& grid, int k){
    int m = sz(grid);
    int n = sz(grid[0]);

    // Step 1: Flatten the 2D grid into a 1D array
    vec<int> flat;
    for (const auto& row : grid){
        for (auto val : row)
            flat.pb(val);
    }

    // Step 2: Rotate the array by k positions
    k %= (m * n); // Handle cases where k is larger than the total number of elements

    // if k %= (n * m) == 0 than 0 moment means no moment
    // Output = original grid.
    if (k == 0) return grid;

    // if k != 0 than rotated
    rotate(flat.begin(), flat.end() - k, flat.end());

    // Step 3: Reshape it back into a 2D grid
    vvec<int> ans(m, vec<int>(n));
    for (int i = 0; i < m * n; i++){
        ans[i / n][i % n] = flat[i];
    }

    return ans;
}

// Approach 2: Instead of rotating array, compute new index directly
// Flatten index formula: i * n + j
// New index after shift: (i * n + j + k) % (m * n)
// Convert back to 2D: row = new_idx / n, col = new_idx % n
// Time Complexity: O(m*n) for reshaping, overall O(m*n).
vvec<int> shiftGrid2(const vvec<int>& grid, int k){
    int m = sz(grid);
    int n = sz(grid[0]);
    int total = m * n;

    vvec<int> ans(m, vec<int>(n));
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            // Original idx in 1D form store
            int idx = i * n + j;

            // cal new idx after shift
            int new_idx = (idx + k) % total;

            // Convert new_idx back to 2D form
            int r = new_idx / n; // row index
            int c = new_idx % n; // column index

            ans[r][c] = grid[i][j];
        }
    }

    return ans;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vvec<int> grid(n, vec<int>(m));
    for (auto& row : grid) {
        for (auto& val : row) {
            cin >> val;
        }
    }

    // vvec<int> ans = shiftGrid(grid, k);
    vvec<int> ans = shiftGrid2(grid, k);
    cout << "[" << nl;
    for (int i = 0; i < n; i++){
        cout << "  [";
        for (int j = 0; j < m; j++){
            cout << ans[i][j];
            if (j < m - 1) cout << ",";
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

