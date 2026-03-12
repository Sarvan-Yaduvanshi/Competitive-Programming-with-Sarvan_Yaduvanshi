/*
 * ============================================================================
 *  📘 03 — Matrix Exponentiation
 * ============================================================================
 *
 *  IDEA: If a linear recurrence can be written as a matrix multiplication:
 *    v(n) = M × v(n-1)
 *  Then: v(n) = M^n × v(0)
 *
 *  We compute M^n using binary exponentiation on matrices.
 *
 *  FIBONACCI EXAMPLE:
 *    F(n) = F(n-1) + F(n-2)
 *
 *    |F(n+1)| = |1 1| × |F(n)  |
 *    |F(n)  |   |1 0|   |F(n-1)|
 *
 *    |F(n+1)| = |1 1|^n × |1|
 *    |F(n)  |   |1 0|     |0|
 *
 *  COMPLEXITY: O(k³ log n) for k×k matrix
 *    - Fibonacci: k=2 → O(8 log n) = O(log n)
 *
 *  APPLICATIONS:
 *    - Fibonacci in O(log n)
 *    - Any linear recurrence in O(k³ log n)
 *    - Graph path counting (adjacency matrix power)
 *    - DP optimization
 *
 *  Reference: https://cp-algorithms.com/algebra/binary-exp.html
 * ============================================================================
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
#define sz(x) ((int)(x).size())
#define pb push_back
#define fi first
#define se second
#define nl '\n'

template<class T>
void read(vec<T> &v) { for (auto &x : v) cin >> x; }

// ============================================================================
//  📌 MATRIX STRUCT
// ============================================================================

using Matrix = vvec<i64>;

Matrix make_identity(int n) {
    Matrix I(n, vec<i64>(n, 0));
    for (int i = 0; i < n; i++) I[i][i] = 1;
    return I;
}

Matrix mat_mul(const Matrix &A, const Matrix &B, i64 mod) {
    int n = sz(A), m = sz(B[0]), k = sz(B);
    Matrix C(n, vec<i64>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int p = 0; p < k; p++)
                C[i][j] = (C[i][j] + A[i][p] * B[p][j]) % mod;
    return C;
}

void print_matrix(const Matrix &M, const string &name = "") {
    if (!name.empty()) cout << name << ":" << nl;
    for (auto &row : M) {
        cout << "  |";
        for (auto x : row) cout << " " << x;
        cout << " |" << nl;
    }
}

// ============================================================================
//  📌 MATRIX EXPONENTIATION
// ============================================================================
//  Same idea as scalar binary exponentiation:
//    result = Identity matrix
//    while exp > 0:
//      if exp is odd: result = result × base
//      base = base × base
//      exp >>= 1
// ============================================================================

Matrix mat_pow(Matrix base, i64 exp, i64 mod) {
    int n = sz(base);
    Matrix result = make_identity(n);

    while (exp > 0) {
        if (exp & 1) result = mat_mul(result, base, mod);
        base = mat_mul(base, base, mod);
        exp >>= 1;
    }
    return result;
}

// ============================================================================
//  📌 FIBONACCI via Matrix Exponentiation
// ============================================================================
//
//  |F(n+1)| = |1 1|^n  ×  |F(1)| = |1 1|^n × |1|
//  |F(n)  |   |1 0|       |F(0)|   |1 0|    |0|
//
//  DRY RUN: Fibonacci(6)
//
//  M = |1 1|
//      |1 0|
//
//  M^1 = |1 1|  → F(2)=1, F(1)=1
//        |1 0|
//
//  M^2 = |2 1|  → F(3)=2, F(2)=1
//        |1 1|
//
//  M^4 = |5 3|  → F(5)=5, F(4)=3
//        |3 2|
//
//  M^6 = M^4 × M^2 = |13  8| → F(7)=13, F(6)=8
//                      | 8  5|
//
//  Fibonacci: 0, 1, 1, 2, 3, 5, 8, 13, ...  → F(6) = 8 ✓
// ============================================================================

i64 fibonacci(i64 n, i64 mod = MOD) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    Matrix M = {{1, 1}, {1, 0}};
    Matrix result = mat_pow(M, n, mod);
    return result[0][1]; // F(n)
}

// ============================================================================
//  📌 GENERAL LINEAR RECURRENCE
// ============================================================================
//  Recurrence: f(n) = c1·f(n-1) + c2·f(n-2) + ... + ck·f(n-k)
//
//  Matrix form (k×k):
//  |f(n)  |   |c1 c2 c3 ... ck|   |f(n-1)|
//  |f(n-1)| = |1  0  0  ... 0 | × |f(n-2)|
//  |f(n-2)|   |0  1  0  ... 0 |   |f(n-3)|
//  |...   |   |...            |   |...   |
//  |f(n-k+1)| |0  0  ... 1  0|   |f(n-k)|
// ============================================================================

// Compute f(n) given coefficients c[] and initial values f[0..k-1]
i64 linear_recurrence(vec<i64> coeff, vec<i64> init, i64 n, i64 mod) {
    int k = sz(coeff);
    if (n < k) return init[n] % mod;

    // Build transition matrix
    Matrix M(k, vec<i64>(k, 0));
    for (int j = 0; j < k; j++) M[0][j] = coeff[j] % mod;
    for (int i = 1; i < k; i++) M[i][i-1] = 1;

    Matrix result = mat_pow(M, n - k + 1, mod);

    // Multiply by initial vector (reversed)
    i64 ans = 0;
    for (int j = 0; j < k; j++) {
        ans = (ans + result[0][j] * init[k - 1 - j]) % mod;
    }
    return ans;
}

// ============================================================================
//  📌 PATH COUNTING via Adjacency Matrix Power
// ============================================================================
//  Number of paths of length exactly L from u to v in a graph
//  = (A^L)[u][v] where A is the adjacency matrix
// ============================================================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Matrix Exponentiation ===" << nl << nl;

    // Fibonacci tests
    cout << "--- Fibonacci Numbers ---" << nl;
    for (i64 n = 0; n <= 15; n++) {
        cout << "F(" << n << ") = " << fibonacci(n) << nl;
    }

    // Large Fibonacci
    cout << nl << "--- Large Fibonacci ---" << nl;
    cout << "F(10^9) mod 10^9+7 = " << fibonacci(1000000000LL) << nl;
    cout << "F(10^18) mod 10^9+7 = " << fibonacci((i64)1e18) << nl;

    // Matrix power trace
    cout << nl << "--- Matrix Power Trace ---" << nl;
    Matrix M = {{1, 1}, {1, 0}};
    for (int n = 1; n <= 6; n++) {
        Matrix Mn = mat_pow(M, n, MOD);
        cout << "M^" << n << " = ";
        cout << "| " << Mn[0][0] << " " << Mn[0][1] << " | ";
        cout << "| " << Mn[1][0] << " " << Mn[1][1] << " |";
        cout << "  → F(" << n+1 << ")=" << Mn[0][0] << ", F(" << n << ")=" << Mn[0][1] << nl;
    }

    // General recurrence: Tribonacci T(n) = T(n-1) + T(n-2) + T(n-3)
    cout << nl << "--- Tribonacci: T(n) = T(n-1) + T(n-2) + T(n-3) ---" << nl;
    cout << "T(0)=0, T(1)=0, T(2)=1" << nl;
    // coeff: [1, 1, 1], init: [0, 0, 1]
    for (i64 n = 0; n <= 15; n++) {
        cout << "T(" << n << ") = " << linear_recurrence({1,1,1}, {0,0,1}, n, MOD) << nl;
    }

    return 0;
}

