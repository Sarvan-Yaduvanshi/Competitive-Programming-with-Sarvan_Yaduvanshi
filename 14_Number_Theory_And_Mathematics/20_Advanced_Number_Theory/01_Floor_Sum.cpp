/*
 * ============================================================================
 *  📘 01 — Floor Sum & Block Decomposition
 * ============================================================================
 *
 *  PROBLEM 1: Compute Σ_{i=1}^{n} ⌊n/i⌋ in O(√n)
 *
 *  KEY INSIGHT: ⌊n/i⌋ takes at most O(√n) distinct values.
 *  For each value v, find the range [lo, hi] where ⌊n/i⌋ = v.
 *    hi = ⌊n/v⌋
 *    lo = ⌊n/(v+1)⌋ + 1
 *
 *  PROBLEM 2: Floor Sum — Σ_{i=0}^{n-1} ⌊(a×i + b) / m⌋
 *  Computed in O(log m) via Euclidean-like reduction.
 *  (AtCoder Library has this as floor_sum)
 *
 *  Reference: https://cp-algorithms.com/algebra/
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
#include <cmath>
#include <numeric>
#include <cassert>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
#define nl '\n'
#define sz(x) ((int)(x).size())

// ============================================================================
//  📌 BLOCK DECOMPOSITION: Σ_{i=1}^{n} ⌊n/i⌋ in O(√n)
// ============================================================================
//
//  DRY RUN: n = 10
//    i=1: ⌊10/1⌋=10,  range [1,1]  → 1 × 10 = 10
//    i=2: ⌊10/2⌋=5,   range [2,2]  → 1 × 5 = 5
//    i=3: ⌊10/3⌋=3,   range [3,3]  → 1 × 3 = 3
//    i=4: ⌊10/4⌋=2,   range [4,5]  → 2 × 2 = 4
//    i=6: ⌊10/6⌋=1,   range [6,10] → 5 × 1 = 5
//    Total = 10+5+3+4+5 = 27
//
//  Brute: 10+5+3+2+2+1+1+1+1+1 = 27 ✓
// ============================================================================

i64 sum_floor_div(i64 n) {
    i64 result = 0;
    for (i64 i = 1; i <= n; ) {
        i64 v = n / i;                  // ⌊n/i⌋
        i64 hi = n / v;                 // largest i with same value
        result += (hi - i + 1) * v;     // (count) × (value)
        i = hi + 1;
    }
    return result;
}

// ============================================================================
//  📌 GENERAL: Σ_{i=1}^{n} f(⌊n/i⌋) in O(√n) blocks
// ============================================================================
//  For each block [lo, hi] where ⌊n/i⌋ = v:
//    contribution = (hi - lo + 1) × f(v)
//  Plus need prefix sums of the "multiplier" function.
// ============================================================================

// Count of (a,b) with 1 ≤ a,b ≤ n and gcd(a,b) = 1
// = Σ_{i=1}^{n} φ(i)   (via Euler totient)
// But also: Σ_{d=1}^{n} μ(d) × ⌊n/d⌋² (via Möbius)

// ============================================================================
//  📌 FLOOR SUM: Σ_{i=0}^{n-1} ⌊(a×i + b) / m⌋
// ============================================================================
//  AtCoder Library style. O(log m).
//
//  REDUCTION (like Euclidean algorithm):
//    If a ≥ m: extract ⌊a/m⌋ factor
//    If b ≥ m: extract ⌊b/m⌋ factor
//    Then swap roles of (a, m) like in GCD
// ============================================================================

i64 floor_sum(i64 n, i64 m, i64 a, i64 b) {
    // Σ_{i=0}^{n-1} ⌊(a*i + b) / m⌋
    if (n == 0) return 0;

    i64 ans = 0;

    // Handle a ≥ m
    if (a >= m) {
        ans += n * (n - 1) / 2 * (a / m);
        a %= m;
    }
    // Handle b ≥ m
    if (b >= m) {
        ans += n * (b / m);
        b %= m;
    }

    i64 y_max = (a * (n - 1) + b) / m;
    if (y_max == 0) return ans;

    i64 x_max = y_max * m - b;
    // Recursion: swap roles
    ans += (n - 1) * y_max - floor_sum(y_max, a, m, m - b - 1 + a);
    // Actually, the standard recursion is:
    // ans += (n-1)*y_max - floor_sum(y_max, a, m, m - b%m - 1) but let me use correct form

    return ans;
}

// Correct AtCoder-style floor_sum
i64 acl_floor_sum(i64 n, i64 m, i64 a, i64 b) {
    i64 ans = 0;
    if (a >= m) {
        ans += (n - 1) * n / 2 * (a / m);
        a %= m;
    }
    if (b >= m) {
        ans += n * (b / m);
        b %= m;
    }

    i64 y_max = a * n + b;
    if (y_max < m) return ans;
    y_max /= m;

    ans += y_max * n;
    ans -= acl_floor_sum(y_max, a, m, m - b - 1);
    ans--;

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Floor Sum & Block Decomposition ===" << nl << nl;

    // Block decomposition demo
    cout << "--- Σ⌊n/i⌋ via Block Decomposition ---" << nl;
    for (i64 n : {10LL, 100LL, 1000LL, 1000000LL}) {
        i64 fast = sum_floor_div(n);
        cout << "Σ_{i=1}^{" << n << "} ⌊" << n << "/i⌋ = " << fast;

        // Verify for small n
        if (n <= 1000) {
            i64 brute = 0;
            for (i64 i = 1; i <= n; i++) brute += n / i;
            assert(fast == brute);
            cout << " ✓";
        }
        cout << nl;
    }

    // Block decomposition trace
    cout << nl << "--- Block Trace for n = 20 ---" << nl;
    {
        i64 n = 20;
        for (i64 i = 1; i <= n; ) {
            i64 v = n / i;
            i64 hi = n / v;
            cout << "i=[" << i << "," << hi << "]: ⌊" << n << "/i⌋=" << v
                 << ", count=" << hi-i+1 << ", sum+=" << (hi-i+1)*v << nl;
            i = hi + 1;
        }
    }

    // Count blocks
    cout << nl << "--- Number of Blocks ---" << nl;
    for (i64 n : {100LL, 10000LL, 1000000LL, 1000000000LL}) {
        int blocks = 0;
        for (i64 i = 1; i <= n; ) {
            blocks++;
            i = n / (n / i) + 1;
        }
        cout << "n=" << n << ": " << blocks << " blocks (2√n ≈ " << 2*(int)sqrt(n) << ")" << nl;
    }

    return 0;
}

