/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-24 22:35:04
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

/* Problem: Row with Maximum 1s in Binary Matrix
 * Given a binary matrix where each row has 0s followed by 1s,
 * find the row with the maximum number of 1s.
 *
 * Approach: Start from top-right. Move left on 1, move down on 0.
 * Time: O(N + M), Space: O(1)
 *
 * Example:
 * 0 0 0 1 1
 * 0 0 1 1 1
 * 0 0 0 0 1
 * 0 1 1 1 1
 *
 * Answer: Row 3 (four 1s)
 *  interview version: In staircase search, we start from the top-right corner.
 *                     At each step, depending on the value, we eliminate either one full row or one full column.
 *                     This reduces the search space efficiently, giving O(n + m) time complexity.
 */

// Approach 1: Brute Force O(N × M)
int rowWithMaxOnesBrute(const vector<vector<int>>& mat) {
    int n = sz(mat), m = sz(mat[0]);
    int maxRow = 0, maxOnes = 0;

    for (int i = 0; i < n; i++) {
        int countOnes = 0;
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == 1) countOnes++;
        }
        if (countOnes > maxOnes) {
            maxOnes = countOnes;
            maxRow = i;
        }
    }
    return maxRow;
}


// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 4: ROW WITH MAXIMUM 1s IN BINARY MATRIX  O(N + M)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Given binary matrix where each row has 0s followed by 1s,
 *  find the row with the maximum number of 1s.
 *
 *  Approach: Start from top-right. Move left on 1, move down on 0.
 *  Time: O(N + M), Space: O(1)
 *
 *  Example:
 *  0 0 0 1 1
 *  0 0 1 1 1
 *  0 0 0 0 1
 *  0 1 1 1 1
 * Answer: Row 3 (four 1s)
 * Counting number of 1s using index j
 * (Staircase Algorithm Notes)
 * Example row:
 * index:  0 1 2 3 4
 * value:  0 0 0 1 1
 * After staircase movement:
 * index:  0 1 2 3 4
 * value:  0 0 0 1 1
               ↑
               j = 2   (j points to LAST 0)
 * ----------------------------------------
 * Step 1: Count number of zeros
 * Zeros exist from index 0 to j
 * Formula:
 * count = last_index - first_index + 1
 * count = j - 0 + 1
 * count = j + 1
 * Example:
 * j = 2
 * zeros = 2 + 1 = 3
 * Reason:
 * Index starts from 0, so count is always j+1
 * ----------------------------------------
 * Step 2: Count number of ones
 * Total columns = m
 * Formula:
 * ones = total_columns - zeros
 * ones = m - (j + 1)
 * ones = m - 1 - j
 * Example:
 * m = 5, j = 2
 * ones = 5 - 1 - 2 -> ans => 2
 * ----------------------------------------
 * Final formulas to remember:
 * zeros = j + 1
 * ones  = m - 1 - j
 * ----------------------------------------
 * Key intuition:
 * j points to last 0
 * j+1 is first 1 index
 * Example:
 * 0 0 0 1 1
        ↑
        j
 * ones exist from index (j+1) to (m-1)
 * count = (m-1) - (j+1) + 1 -> m - 1 - j
 * ----------------------------------------
 * Time complexity advantage:
 * No need to count manually → O(1)
 * Because staircase already found boundary
 *  interview version: In staircase search, we start from the top-right corner.
 *                     At each step, depending on the value, we eliminate either one full row or one full column.
 *                     This reduces the search space efficiently, giving O(n + m) time complexity.
 */
int rowWithMaxOnes(const vector<vector<int>>& mat){
    int m = sz(mat);
    int n = sz(mat[0]);

    int maxRow = 0;
    int j = n - 1; // Start from top-right

    for (int i = 0; i < n; i++){
        while (j >= 0 && mat[i][j] == 1){
            j--;
            maxRow = i; // This row has more 1s
        }
    }

    return maxRow;
}

void solve(){
    int n, m;
    cin >> n >> m;

    vvec<int> mat(n, vec<int>(m));
    for (auto& row : mat){
        for (auto& val : row){
            cin >> val;
        }
    }

    int ans = rowWithMaxOnes(mat);
    cout << "Row with maximum 1s: " << ans << endl;
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

