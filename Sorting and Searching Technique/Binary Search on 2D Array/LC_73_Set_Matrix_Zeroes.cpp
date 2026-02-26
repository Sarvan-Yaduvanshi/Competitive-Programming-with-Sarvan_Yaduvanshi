/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-25 19:06:04
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

/* Problem: LC 73. Set Matrix Zeroes
 * Given an m x n integer matrix, if an element is 0, set its entire row and column to 0's.
 * You must do it in place.
 * Example 1:
 * Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
 * Output: [[1,0,1],[0,0,0],[1,0,1]]
 * Example 2:
 * Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
 * Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
 * Follow up:
 * A straightforward solution using O(mn) space is probably a bad idea.
 * A simple improvement uses O(m + n) space, but still not the best solution.
 * Could you devise a constant space solution?
 */

// Approach 1: Brute Force
// Time Complexity: O(m*n*(m+n)) in worst case (if all elements are zero)
// Space Complexity: O(m*n) for the copy of the matrix
void setZeroesBruteForce(vvec<int>& mat){
    int m = sz(mat);
    int n = sz(mat[0]);

    // 1. Create a "Safe Copy" (Ans)
    vvec<int> ans = mat;

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            // current element is zero, set the entire row and column to zero in the answer matrix
            if (mat[i][j] == 0){
                // set the entire row to zero
                for (int k = 0; k < n; k++){
                    ans[i][k] = 0;
                }
                // set the entire column to zero
                for (int k = 0; k < m; k++){
                    ans[k][j] = 0;
                }
            }
        }
    }

    // 3. Copy the modified 'ans' back to the original 'matrix'
    mat = ans;
}

// Approach 2: The "Checklist" (Optimization Level 1)
// Time Complexity: O(m*n)
// Space Complexity: O(m + n) for the two boolean variables to track the first row and column
void setZeroesChecklist(vvec<int>& mat){
    int m = sz(mat);
    int n = sz(mat[0]);

    // 1. Create two "Checklists" initialized to 0 (false)
    // Space Complexity: O(M + N) -> Much better than O(M * N)
    vec<int> rowChecklist(m, 0);
    vec<int> colChecklist(n, 0);

    // 2. Pass 1: Survey the Matrix
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (mat[i][j] == 0){
                // Mark the specific row and column as 1
                rowChecklist[i] = 1;
                colChecklist[j] = 1;
            }
        }
    }

    // 3. Pass 2: The Update
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            // If EITHER the row OR the column was marked...
            if (rowChecklist[i] == 1 || colChecklist[j] == 1)
                mat[i][j] = 0;
        }
    }
}

// Approach 3: The Logic: "In-Place Checklists"
// Time Complexity: O(m*n)
// Space Complexity: O(1) (constant space)
void setZeroesInPlace(vvec<int>& mat){
    int m = sz(mat);
    int n = sz(mat[0]);

    int cols0 = 1; // marks as true
    for (int i = 0; i < m; i++){
        if (mat[i][0] == 0) cols0 = 0;

        for (int j = 1; j < n; j++){
            if (mat[i][j] == 0){
                mat[i][0] = 0;
                mat[0][j] = 0;
            }
        }
    }

    for (int i = m - 1; i >= 0; i--){
        for (int j = n - 1; j >= 1; j--){
            if (mat[i][0] == 0 || mat[0][j] == 0){
                mat[i][j] = 0;
            }
        }

        if (cols0 == 0)
            mat[i][0] = 0;
    }
}

void solve() {
    int m, n;
    cin >> m >> n;
    vvec<int> mat(m, vec<int>(n));
    for (auto& row : mat){
        for (auto& val : row){
            cin >> val;
        }
    }

    // print the original matrix
    cout << "Original Matrix:" << nl;
    for (const auto& row : mat){
        cout << "[";
        for (int i = 0; i < sz(row); i++){
            cout << row[i];
            if (i != sz(row) - 1) cout << ",";
        }
        cout << "]" << nl;
    }
    cout << nl;

    setZeroesInPlace(mat);

    // Output the modified matrix
    cout << "Modified Matrix:" << nl;
    for (const auto& row : mat){
        cout << "[";
        for (int i = 0; i < sz(row); i++){
            cout << row[i];
            if (i != sz(row) - 1) cout << ",";
        }
        cout << "]" << nl;
    }
    cout << nl;
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

