/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-24 09:46:06
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

/* Problem: LeetCode 2906 - Construct Product Matrix
 * Given a 2D matrix of integers, construct a new matrix where each element at position (i, j) is
 * the product of all elements in the original matrix except the one at (i, j).
 *
 * Example:
 * Input: [[1, 2], [3, 4]]
 * Output: [[24, 12], [8, 6]]
 * Explanation:
 * - For (0,0): product = 2 * 3 * 4 = 24
 * - For (0,1): product = 1 * 3 * 4 = 12
 * - For (1,0): product = 1 * 2 * 4 = 8
 * - For (1,1): product = 1 * 2 * 3 = 6
 *
 * Constraints:
 * - The dimensions of the matrix are m x n, where 1 <= m, n <= 1e5
 * - 2 <= m * n <= 1e5
 * - 1 <= matrix[i][j] <= 1e9
 *
 * Key Challenges:
 * 1. Handling large products without overflow (use logarithms or modular arithmetic).
 * 2. Handling with Zeros Case:
 *  - Case A: If there are more than one zero, all products will be zero.
 *  - Case B: exactly one zero: only that position gets product of others, rest are zero.
 *  - Case C: No zeros: use division or prefix/suffix products.
 */

// Approach 1: Brute Force
// Logic: loop run i = 0 to m-1 and j = 0 to n-1 than traverse the whole matrix and cal the product of all
// the elements except the current element and store it in the result matrix.
// Time Complexity: O(m*n*m*n) = O((m*n)^2) which is not efficient for large matrices.
// Given problem use modulo 12345
constexpr static int mod = 12345;
vvec<int> constructProductMatrixBruteForce(const vvec<int>& grid){
    int m = sz(grid);
    int n = sz(grid[0]);

    vvec<int> ans(m, vec<int>(n, 1));

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            i64 prod = 1;
            for (int x = 0; x < m; x++){
                for (int y = 0; y < n; y++){
                    if (x == i && y == j) continue; // Skip the current element
                    prod = (prod * grid[x][y]) % mod; // Use modulo to prevent overflow
                }
            }
            ans[i][j] = prod;
        }
    }
    return ans;
}

// Approach 2: Optimized with Prefix and Suffix Products
// Logic: 1. Flatten the 2D matrix into a 1D array for easier prefix/suffix calculations.
//        2. Calculate prefix products from the left and store them in an array.
//        3. Calculate suffix products from the right and multiply with prefix products to get the final result.
//        4. Convert the 1D result back to a 2D matrix.
// Time Complexity: O(m*n) for flattening + O(m*n) for prefix + O(m*n) for suffix + O(m*n) for conversion = O(m*n), which is efficient for large matrices.
// Space Complexity: O(m*n) for the flattened array and the result array, which is O(m*n) overall.
vvec<int> constructProductMatrix(const vvec<int>& grid){
    int n = sz(grid);
    int m = sz(grid[0]);

    // Step 1: Convert 2D -> 1D (Flat matrix)
    vec<int> flat;
    for (auto& row : grid){
        for (auto& val : row)
            flat.pb(val % mod);
    }

    int sz = sz(flat);
    vec<int> ans1d(sz, 1);

    // Step 2: Cal Prefix product
    i64 pref = 1;
    for (int i = 0; i < sz; i++){
        ans1d[i] = (ans1d[i] * pref) % mod;
        pref = (1LL * pref * flat[i]) % mod;
    }

    // Step 3: Cal suffix product
    i64 suff = 1;
    for (int i = sz - 1; i >= 0; i--){
        ans1d[i] = (ans1d[i] * suff) % mod;
        suff = (1LL * suff * flat[i]) % mod;
    }

    // Step 4: Convert 1d ans to 2d ans
    vvec<int> ans(n, vec<int>(m));
    for (int i = 0; i < sz(ans1d); i++){
        int r = i / m;
        int c = i % m;
        ans[r][c] = ans1d[i];
    }

    return ans;
}

void solve() {
    int m, n;
    cin >> m >> n;

    vvec<int> grid(m, vec<int>(n));
    for (auto& row : grid) {
        for (int& x : row) cin >> x;
    }

    vvec<int> result = constructProductMatrix(grid);
    cout << "[";
    for (int i = 0; i < m; i++) {
        cout << "[";
        for (int j = 0; j < n; j++) {
            cout << result[i][j];
            if (j < n - 1) cout << ", ";
        }
        cout << "]";
        if (i < m - 1) cout << ", ";
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

