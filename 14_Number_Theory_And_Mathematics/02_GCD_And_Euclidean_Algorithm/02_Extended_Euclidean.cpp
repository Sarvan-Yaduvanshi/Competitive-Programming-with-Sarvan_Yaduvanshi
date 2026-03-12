/*
 * ============================================================================
 *  📘 02 — Extended Euclidean Algorithm
 * ============================================================================
 *
 *  BÉZOUT'S IDENTITY:
 *    For any integers a, b (not both zero), there exist integers x, y such that:
 *      ax + by = gcd(a, b)
 *
 *  PROOF (Constructive — via the algorithm):
 *    Base case: gcd(a, 0) = a, so x=1, y=0 works: a(1) + 0(0) = a.
 *
 *    Recursive step: Suppose we know x1, y1 such that:
 *      b·x1 + (a mod b)·y1 = gcd(b, a mod b) = gcd(a, b) = g
 *
 *    Since a mod b = a - ⌊a/b⌋·b:
 *      b·x1 + (a - ⌊a/b⌋·b)·y1 = g
 *      a·y1 + b·(x1 - ⌊a/b⌋·y1) = g
 *
 *    So: x = y1,  y = x1 - ⌊a/b⌋·y1
 *
 *  COMPLEXITY: O(log(min(a, b)))  — same as Euclidean algorithm
 *
 *  APPLICATIONS:
 *    1. Finding modular inverse: ax ≡ 1 (mod m)
 *    2. Solving linear Diophantine equations: ax + by = c
 *    3. Chinese Remainder Theorem
 *
 *  Reference: https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
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
//  📌 RECURSIVE Extended Euclidean Algorithm
// ============================================================================
//  Returns gcd(a, b) and sets x, y such that a*x + b*y = gcd(a, b)
//
//  DRY RUN: extgcd(30, 12)
//
//  Call stack:
//    extgcd(30, 12):
//      extgcd(12, 6):
//        extgcd(6, 0):
//          return 6, x=1, y=0     → 6(1) + 0(0) = 6 ✓
//        g=6, x1=1, y1=0
//        x = 0, y = 1 - (12/6)*0 = 1 - 2*0 = 1
//        return 6, x=0, y=1       → 12(0) + 6(1) = 6 ✓
//      g=6, x1=0, y1=1
//      x = 1, y = 0 - (30/12)*1 = 0 - 2 = -2
//      return 6, x=1, y=-2        → 30(1) + 12(-2) = 30 - 24 = 6 ✓
// ============================================================================

i64 extgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i64 x1, y1;
    i64 g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// ============================================================================
//  📌 ITERATIVE Extended Euclidean Algorithm
// ============================================================================
//  More efficient: no recursion overhead, no stack overflow risk.
//
//  We maintain two equations:
//    a_old = a * x_old + b * y_old
//    a_cur = a * x_cur + b * y_cur
//
//  Initially:
//    a_old = a = a*1 + b*0  →  x_old=1, y_old=0
//    a_cur = b = a*0 + b*1  →  x_cur=0, y_cur=1
//
//  Each step: q = a_old / a_cur
//    new = old - q * cur  (for all three: value, x, y)
// ============================================================================

i64 extgcd_iter(i64 a, i64 b, i64 &x, i64 &y) {
    i64 x0 = 1, y0 = 0;  // coefficients for a_old
    i64 x1 = 0, y1 = 1;  // coefficients for a_cur

    while (b != 0) {
        i64 q = a / b;

        i64 temp_a = a - q * b;
        a = b; b = temp_a;

        i64 temp_x = x0 - q * x1;
        x0 = x1; x1 = temp_x;

        i64 temp_y = y0 - q * y1;
        y0 = y1; y1 = temp_y;
    }

    x = x0;
    y = y0;
    return a;
}

// ============================================================================
//  📌 Extended GCD with TRACE
// ============================================================================

i64 extgcd_trace(i64 a, i64 b, i64 &x, i64 &y, int depth = 0) {
    string indent(depth * 2, ' ');
    cout << indent << "extgcd(" << a << ", " << b << ")" << nl;

    if (b == 0) {
        x = 1; y = 0;
        cout << indent << "  Base: x=" << x << ", y=" << y
             << "  → " << a << "*" << x << " + " << b << "*" << y << " = " << a << nl;
        return a;
    }

    i64 x1, y1;
    i64 g = extgcd_trace(b, a % b, x1, y1, depth + 1);

    x = y1;
    y = x1 - (a / b) * y1;

    cout << indent << "  Back-sub: x=" << x << ", y=" << y
         << "  → " << a << "*(" << x << ") + " << b << "*(" << y << ") = "
         << a * x + b * y << nl;

    return g;
}

// ============================================================================
//  📌 APPLICATION: Modular Inverse via Extended GCD
// ============================================================================
//  Find x such that: a*x ≡ 1 (mod m)
//  This is: a*x + m*y = 1 (since gcd(a, m) must be 1)
//
//  EXAMPLE: Find 3^(-1) mod 7
//    extgcd(3, 7, x, y):  3*5 + 7*(-2) = 1
//    So 3^(-1) ≡ 5 (mod 7)
//    Check: 3 * 5 = 15 ≡ 1 (mod 7) ✓
// ============================================================================

i64 mod_inverse_extgcd(i64 a, i64 m) {
    i64 x, y;
    i64 g = extgcd(a, m, x, y);
    if (g != 1) return -1; // inverse doesn't exist
    return ((x % m) + m) % m; // ensure positive
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Extended Euclidean Algorithm ===" << nl << nl;

    // Detailed dry runs
    cout << "--- Dry Run: extgcd(30, 12) ---" << nl;
    {
        i64 x, y;
        i64 g = extgcd_trace(30, 12, x, y);
        cout << "Result: gcd=" << g << ", x=" << x << ", y=" << y << nl;
        cout << "Verify: 30*(" << x << ") + 12*(" << y << ") = " << 30*x + 12*y << nl << nl;
    }

    cout << "--- Dry Run: extgcd(35, 15) ---" << nl;
    {
        i64 x, y;
        i64 g = extgcd_trace(35, 15, x, y);
        cout << "Result: gcd=" << g << ", x=" << x << ", y=" << y << nl;
        cout << "Verify: 35*(" << x << ") + 15*(" << y << ") = " << 35*x + 15*y << nl << nl;
    }

    cout << "--- Dry Run: extgcd(99, 78) ---" << nl;
    {
        i64 x, y;
        i64 g = extgcd_trace(99, 78, x, y);
        cout << "Result: gcd=" << g << ", x=" << x << ", y=" << y << nl;
        cout << "Verify: 99*(" << x << ") + 78*(" << y << ") = " << 99*x + 78*y << nl << nl;
    }

    // Iterative vs Recursive comparison
    cout << "--- Iterative vs Recursive ---" << nl;
    vec<pll> tests = {{252, 105}, {1071, 462}, {48, 18}, {17, 13}};
    for (auto [a, b] : tests) {
        i64 x1, y1, x2, y2;
        i64 g1 = extgcd(a, b, x1, y1);
        i64 g2 = extgcd_iter(a, b, x2, y2);
        cout << "gcd(" << a << "," << b << ") = " << g1
             << "  recursive: " << a << "*" << x1 << "+" << b << "*" << y1 << "=" << a*x1+b*y1
             << "  iterative: " << a << "*" << x2 << "+" << b << "*" << y2 << "=" << a*x2+b*y2 << nl;
        assert(g1 == g2);
    }

    // Modular inverse examples
    cout << nl << "--- Modular Inverse ---" << nl;
    vec<pll> inv_tests = {{3, 7}, {5, 11}, {7, 26}, {3, MOD}};
    for (auto [a, m] : inv_tests) {
        i64 inv = mod_inverse_extgcd(a, m);
        cout << a << "^(-1) mod " << m << " = " << inv;
        if (inv != -1) cout << "  [check: " << a << "*" << inv << " mod " << m << " = " << ((__int128)a * inv % m) << "]";
        cout << nl;
    }

    return 0;
}

