/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-06 18:07:58
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

// Approach 1: Brute Force solution for LeetCode 1074
// Time Complexity -> O(M * N)^3
// Space Complexity -> O(1)
int sumOfSubMatrix(const vvec<int>& mat, int i, int rowSize, int j, int colSize){
    int subMatrixSum = 0;
    for (int x = i; x < i + rowSize; x++){
        for (int k = j; k < j + colSize; k++)
            subMatrixSum += mat[x][k];
    }

    return subMatrixSum;
}
int numSubmatrixSumTarget(const vvec<int>& mat, int k){
    int n = sz(mat);
    int m = sz(mat[0]);
    int ans = 0;

    for (int i = 0; i < n; i++){ // start row
        for (int rowSize = 1; i + rowSize <= n; rowSize++){ // height
            for (int j = 0; j < m; j++){ // start column
                for (int colSize = 1; j + colSize <= m; colSize++){ // width
                   if (sumOfSubMatrix(mat, i, rowSize, j, colSize) == k)
                       ans++;
                }
            }
        }
    }
    return ans;
}

// Approach 2: Using Prefix Sum
// TC -> O(M * N)^2 | SC -> O(M * N)
int numSubmatrixSumTargetPrefix(const vvec<int>& mat, int k){
    int rows = sz(mat);
    int cols = sz(mat[0]);

    vvec<int> pref(rows + 1, vec<int>(cols + 1, 0));
    for (int i = 1; i <= rows; i++){
        for (int j = 1; j <= cols; j++){
            pref[i][j] = mat[i - 1][j - 1]
                       + pref[i - 1][j]
                       + pref[i][j - 1]
                       - pref[i - 1][j - 1];
        }
    }

    int cnt = 0;
    for (int r1 = 1; r1 <= rows; r1++){
        for (int c1 = 1; c1 <= cols; c1++){
            for (int r2 = r1; r2 <= rows; r2++){
                for (int c2 = c1; c2 <= cols; c2++){
                    const i64 currSum = pref[r2][c2]
                                - pref[r1 - 1][c2]
                                - pref[r2][c1 - 1]
                                + pref[r1 - 1][c1 - 1];

                    if (currSum == k) cnt++;
                }
            }
        }
    }

    return cnt;
}

// Approach 3: Using Prefix sum + Map + 1D Subarray sum equal k
// TC -> O(M * N)^2 | SC -> O(N)
int subarraySum(const vec<int>& nums, const int k){
    unordered_map<int, int> prefixMap;
    prefixMap[0] = 1;

    int cnt = 0;
    int currSum = 0;

    for (auto num : nums){
        currSum += num;

        if (prefixMap.contains(currSum - k))
            cnt += prefixMap[currSum - k];

        prefixMap[currSum]++;
    }
    return cnt;
}
int numSubmatrixSumTargetOptimal(const vvec<int>& mat, int k){
    int rows = sz(mat);
    int cols = sz(mat[0]);
    int cnt = 0;

    // Fixed Top row
    for (int top = 0; top < rows; top++){
        vec<int> colSum(cols, 0);
        // Fixed bottom row
        for (int bottom = top; bottom < cols; bottom++){
            for (int col = 0; col < cols; col++){
                colSum[col] = mat[bottom][col];
            }
            cnt += subarraySum(colSum, k);
        }
    }
    return cnt;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vvec<int>mat(n, vec<int>(m));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
            cin >> mat[i][j];
    }

    int k; cin >> k;
    int ans = numSubmatrixSumTargetOptimal(mat, k);

    cout << ans << nl;
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

