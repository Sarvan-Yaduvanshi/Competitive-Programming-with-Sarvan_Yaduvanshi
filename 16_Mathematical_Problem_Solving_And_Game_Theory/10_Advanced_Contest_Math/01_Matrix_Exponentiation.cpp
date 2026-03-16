/*
 * ============================================================
 *  Topic   : Matrix Exponentiation for Linear Recurrences
 *  Pattern : Represent recurrence as matrix, use binary exp
 *
 *  Problems:
 *    - CSES Fibonacci Numbers (1722)
 *    - CSES Throwing Dice (1096)
 *    - CSES Graph Paths I (1723)
 *    - LeetCode 509 — Fibonacci Number (matrix method)
 *
 *  Complexity: O(k³ log n) where k = recurrence order
 * ============================================================
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

using i64 = long long;
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

template<class T>
void read(vec<T> &v) { for (auto &x : v) cin >> x; }
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

/*
 * ============================================================
 *  MATRIX OPERATIONS (modular)
 * ============================================================
 */

using Matrix = vvec<i64>;

Matrix identity(int n) {
    Matrix I(n, vec<i64>(n, 0));
    for (int i = 0; i < n; i++) I[i][i] = 1;
    return I;
}

Matrix matmul(const Matrix& A, const Matrix& B, i64 mod = MOD) {
    int n = sz(A), m = sz(B[0]), k = sz(B);
    Matrix C(n, vec<i64>(m, 0));
    for (int i = 0; i < n; i++)
        for (int p = 0; p < k; p++) if (A[i][p])
            for (int j = 0; j < m; j++)
                C[i][j] = (C[i][j] + A[i][p] * B[p][j]) % mod;
    return C;
}

Matrix matpow(Matrix M, i64 p, i64 mod = MOD) {
    int n = sz(M);
    Matrix res = identity(n);
    while (p > 0) {
        if (p & 1) res = matmul(res, M, mod);
        M = matmul(M, M, mod);
        p >>= 1;
    }
    return res;
}

/*
 * ============================================================
 *  FIBONACCI via Matrix Exponentiation
 * ============================================================
 *
 *  F(0) = 0, F(1) = 1
 *  F(n) = F(n-1) + F(n-2)
 *
 *  [F(n+1)]   [1 1]^n   [1]
 *  [F(n)  ] = [1 0]   × [0]
 *
 *  So F(n) = M^n[1][0] where M = {{1,1},{1,0}}
 * ============================================================
 */

i64 fibonacci(i64 n) {
    if (n <= 1) return n;
    Matrix M = {{1, 1}, {1, 0}};
    Matrix result = matpow(M, n);
    return result[0][1];  // F(n)
}

/*
 * ============================================================
 *  THROWING DICE (CSES 1096)
 * ============================================================
 *
 *  How many ways to get sum n by throwing a die (faces 1-6)?
 *  f(n) = f(n-1) + f(n-2) + f(n-3) + f(n-4) + f(n-5) + f(n-6)
 *  f(0) = 1, f(k) = 0 for k < 0
 *
 *  6th order recurrence → 6×6 matrix
 *
 *  M = [1 1 1 1 1 1]       V = [f(5)]   [f(n)  ]
 *      [1 0 0 0 0 0]           [f(4)]   [f(n-1)]
 *      [0 1 0 0 0 0]           [f(3)] → [f(n-2)]
 *      [0 0 1 0 0 0]           [f(2)]   [f(n-3)]
 *      [0 0 0 1 0 0]           [f(1)]   [f(n-4)]
 *      [0 0 0 0 1 0]           [f(0)]   [f(n-5)]
 *
 *  Result = (M^(n-5) × V)[0] for n >= 6
 * ============================================================
 */

i64 throwingDice(i64 n) {
    if (n == 0) return 1;

    // Compute f(0) through f(5) directly
    vec<i64> f(6, 0);
    f[0] = 1;
    for (int i = 1; i <= 5; i++) {
        for (int d = 1; d <= min(i, 6); d++) {
            f[i] = (f[i] + f[i - d]) % MOD;
        }
    }

    if (n <= 5) return f[n];

    // Build 6x6 transition matrix
    int k = 6;
    Matrix M(k, vec<i64>(k, 0));
    for (int j = 0; j < k; j++) M[0][j] = 1;  // first row all 1s
    for (int i = 1; i < k; i++) M[i][i - 1] = 1;  // shift

    Matrix result = matpow(M, n - 5);

    // Multiply result × initial vector [f(5), f(4), f(3), f(2), f(1), f(0)]
    i64 ans = 0;
    for (int j = 0; j < k; j++) {
        ans = (ans + result[0][j] * f[5 - j]) % MOD;
    }

    return ans;
}

/*
 * ============================================================
 *  GRAPH PATHS (CSES 1723)
 * ============================================================
 *
 *  Given directed graph with n nodes, count paths of exactly
 *  k edges from node 1 to node n.
 *
 *  Answer: (adj_matrix ^ k)[0][n-1]
 *
 *  The (i,j) entry of A^k = number of paths of length k from i to j.
 * ============================================================
 */

i64 graphPaths(int n, int k, Matrix& adj) {
    Matrix result = matpow(adj, k);
    return result[0][n - 1];
}

/*
 * ============================================================
 *  GENERAL LINEAR RECURRENCE via Matrix Exp
 * ============================================================
 *  f(n) = c1*f(n-1) + c2*f(n-2) + ... + ck*f(n-k)
 *
 *  Build k×k matrix M:
 *    Row 0: [c1, c2, ..., ck]
 *    Row i (i>=1): 1 at column i-1, 0 elsewhere
 *
 *  V(0) = [f(k-1), f(k-2), ..., f(0)]^T
 *  f(n) = (M^(n-k+1) × V(0))[0]
 * ============================================================
 */

i64 linearRecurrence(vec<i64>& coeffs, vec<i64>& initial, i64 n) {
    int k = sz(coeffs);
    if (n < k) return initial[n];

    Matrix M(k, vec<i64>(k, 0));
    for (int j = 0; j < k; j++) M[0][j] = coeffs[j] % MOD;
    for (int i = 1; i < k; i++) M[i][i - 1] = 1;

    Matrix result = matpow(M, n - k + 1);

    i64 ans = 0;
    for (int j = 0; j < k; j++) {
        ans = (ans + result[0][j] % MOD * initial[k - 1 - j]) % MOD;
    }
    return (ans + MOD) % MOD;
}

void solve() {
    i64 n;
    cin >> n;

    // CSES Fibonacci Numbers
    cout << fibonacci(n) << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    int TC = 1;
    // cin >> TC;
    while (TC--) solve();

    return 0;
}


