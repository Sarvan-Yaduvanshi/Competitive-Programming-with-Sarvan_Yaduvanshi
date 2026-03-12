/*
 * ============================================================================
 *  📘 01 — Euclidean Algorithm for GCD
 * ============================================================================
 *
 *  THEOREM: gcd(a, b) = gcd(b, a mod b)
 *
 *  PROOF:
 *    Let d = gcd(a, b). Write a = bq + r where r = a mod b.
 *    d | a and d | b  ⟹  d | (a - bq) = r  ⟹  d | gcd(b, r)
 *    Conversely, if d' | b and d' | r, then d' | (bq + r) = a.
 *    So gcd(a, b) = gcd(b, a mod b).
 *
 *  COMPLEXITY: O(log(min(a, b)))
 *    - After two iterations, the value is halved.
 *    - Worst case: Fibonacci numbers (gcd(F(n+1), F(n)) takes n steps).
 *
 *  Reference: https://cp-algorithms.com/algebra/euclid-algorithm.html
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
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

template<class T>
void read(vec<T> &v) { for (auto &x : v) cin >> x; }
#define nl '\n'

// ============================================================================
//  📌 RECURSIVE GCD
// ============================================================================
//  Base case: gcd(a, 0) = a
//  Recursive: gcd(a, b) = gcd(b, a % b)
// ============================================================================

i64 gcd_recursive(i64 a, i64 b) {
    if (b == 0) return a;
    return gcd_recursive(b, a % b);
}

// ============================================================================
//  📌 ITERATIVE GCD (preferred in CP — no stack overflow)
// ============================================================================

i64 gcd_iterative(i64 a, i64 b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// ============================================================================
//  📌 GCD WITH TRACE (for learning / dry run)
// ============================================================================
//  Shows each step of the algorithm.
//
//  DRY RUN: gcd_trace(252, 105)
//    Step 1: gcd(252, 105) → 252 = 105 × 2 + 42
//    Step 2: gcd(105, 42)  → 105 = 42 × 2 + 21
//    Step 3: gcd(42, 21)   → 42 = 21 × 2 + 0
//    Step 4: gcd(21, 0)    → return 21
// ============================================================================

i64 gcd_trace(i64 a, i64 b, int step = 1) {
    cout << "  Step " << step << ": gcd(" << a << ", " << b << ")";
    if (b == 0) {
        cout << " → return " << a << nl;
        return a;
    }
    cout << " → " << a << " = " << b << " × " << (a / b) << " + " << (a % b) << nl;
    return gcd_trace(b, a % b, step + 1);
}

// ============================================================================
//  📌 LCM using GCD
// ============================================================================
//  lcm(a, b) = |a * b| / gcd(a, b)
//  IMPORTANT: Divide first to avoid overflow!
// ============================================================================

i64 lcm_safe(i64 a, i64 b) {
    return (a / gcd_iterative(a, b)) * b;
}

// ============================================================================
//  📌 GCD of an array
// ============================================================================
//  gcd(a1, a2, ..., an) = gcd(gcd(a1, a2), a3, ..., an)
// ============================================================================

i64 gcd_array(const vec<i64>& arr) {
    i64 g = 0;
    for (i64 x : arr) g = gcd_iterative(g, x);
    return g;
}

// ============================================================================
//  📌 LCM of an array
// ============================================================================

i64 lcm_array(const vec<i64>& arr) {
    i64 result = 1;
    for (i64 x : arr) {
        result = lcm_safe(result, x);
        // Overflow check
        if (result < 0) return -1; // overflow
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Euclidean Algorithm ===" << nl << nl;

    // Dry run examples
    cout << "--- Dry Run: gcd(48, 18) ---" << nl;
    i64 g1 = gcd_trace(48, 18);
    cout << "Result: " << g1 << nl << nl;

    cout << "--- Dry Run: gcd(252, 105) ---" << nl;
    i64 g2 = gcd_trace(252, 105);
    cout << "Result: " << g2 << nl << nl;

    cout << "--- Dry Run: gcd(1071, 462) ---" << nl;
    i64 g3 = gcd_trace(1071, 462);
    cout << "Result: " << g3 << nl << nl;

    // Worst case: Fibonacci numbers
    cout << "--- Worst Case: Fibonacci ---" << nl;
    cout << "gcd(F13, F12) = gcd(233, 144):" << nl;
    gcd_trace(233, 144);
    cout << nl;

    // LCM examples
    cout << "--- LCM Examples ---" << nl;
    vec<pll> lcm_tests = {{12, 18}, {7, 5}, {100, 75}, {6, 8}};
    for (auto [a, b] : lcm_tests) {
        cout << "lcm(" << a << ", " << b << ") = " << lcm_safe(a, b)
             << "  [gcd = " << gcd_iterative(a, b) << "]" << nl;
    }
    cout << nl;

    // Array GCD and LCM
    cout << "--- Array GCD & LCM ---" << nl;
    vec<i64> arr = {12, 18, 24, 36};
    cout << "Array: ";
    for (auto x : arr) cout << x << " ";
    cout << nl;
    cout << "GCD = " << gcd_array(arr) << nl;
    cout << "LCM = " << lcm_array(arr) << nl;

    return 0;
}

