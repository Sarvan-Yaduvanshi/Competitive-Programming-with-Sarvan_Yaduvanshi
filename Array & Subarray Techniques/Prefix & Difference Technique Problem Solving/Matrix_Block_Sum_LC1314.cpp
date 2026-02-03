/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-03 14:43:46
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
using ld = long double;
template<class T>
using vec = vector<T>;
template<class T>
using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

// --- Constants ---
constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD = 1'000'000'007LL;
constexpr i64 MOD9 = 998'244'353LL;
constexpr ld PI = 3.14159265358979323846;

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
void read(vec<T>& v){
    for (auto& x : v) cin >> x;
}

#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

inline i64 gcd(i64 a, i64 b){ return std::gcd(a, b); }
inline i64 lcm(i64 a, i64 b){ return (a / std::gcd(a, b)) * b; }

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD){
    i64 res = 1;
    base %= mod;
    while (exp > 0){
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

/*
* ==========================================
* Problem: 1314. Matrix Block Sum
* Platform: LeetCode (Amazon Interview Question)
* ==========================================
*
* Description:
* Given an m x n matrix and an integer k, return a matrix 'ans' where
* each ans[i][j] is the sum of elements in the submatrix defined by:
* - Rows:    [i - k, i + k]
* - Columns: [j - k, j + k]
* Ensure the indices remain within valid matrix bounds (0 to m-1, 0 to n-1).
*
* Constraints:
* - m, n <= 100
* - mat[i][j] <= 100
* - 1 <= k <= 100
*
* Approach:
* - Use 2D Prefix Sum (Integral Image) technique.
* - Build a padded prefix sum array (size m+1 x n+1) to handle boundary checks easily.
* - For every cell (i, j), calculate the top-left (r1, c1) and bottom-right (r2, c2)
* corners of the block sum window using min/max to stay in bounds.
* - Use the O(1) inclusion-exclusion formula to compute the sum.
*
* Complexity:
* - Time: O(M * N) - We visit every cell constant times.
* - Space: O(M * N) - For the prefix sum array.
*/
vvec<int> matrixBlockSum(vvec<int>& mat, int k){
    int m = sz(mat);
    int n = sz(mat[0]);

    // 1. Build 2D Prefix Sum Array (0 based index)
    vvec<i64> pref(m, vec<i64>(n, 0));
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            pref[i][j] = mat[i][j];
            if (i > 0) pref[i][j] += pref[i - 1][j];
            if (j > 0) pref[i][j] += pref[i][j - 1];
            if (i > 0 && j > 0) pref[i][j] -= pref[i- 1][j - 1];
        }
    }

    // 2. Calculate the answer for each cell
    vvec<int> ans(m, vec<int>(n));
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            int r1 = max(0, i - k);
            int c1 = max(0, j - k);
            int r2 = min(m - 1, i + k);
            int c2 = min(n - 1, j + k);

            i64 sum = pref[r2][c2];
            if (r1 > 0) sum -= pref[r1 - 1][c2];
            if (c1 > 0) sum -= pref[r2][c1 - 1];
            if (r1 > 0 && c1 > 0) sum += pref[r1 - 1][c1 - 1];

            ans[i][j] = sum;
        }
    }

    return ans;
}

void solve(){
    int m, n; cin >> m >> n;

    vvec<int> mat(m, vec<int>(n));
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            cin >> mat[i][j];
        }
    }

    int k; cin >> k;

    vvec<int> ans = matrixBlockSum(mat, k);

    cout << "Output Matrix:" << endl;
    for (const auto& row : ans){
        cout << "[ ";
        for (int val : row){
            cout << val << " ";
        }
        cout << "]";
    }
}


int main(){
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

