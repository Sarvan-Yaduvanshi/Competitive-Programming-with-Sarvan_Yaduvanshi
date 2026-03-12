/*
 * ============================================================================
 *  📘 02 — Cipolla's Algorithm (Modular Square Root)
 * ============================================================================
 *
 *  PROBLEM: Find x such that x² ≡ a (mod p), p odd prime.
 *
 *  CIPOLLA'S APPROACH:
 *    1. Find t such that (t² - a) is a quadratic non-residue mod p.
 *    2. Work in F_{p²} = {α + β√ω : α, β ∈ F_p} where ω = t² - a.
 *    3. Compute (t + √ω)^((p+1)/2) in F_{p²}.
 *    4. The result is x + 0·√ω, so x is the answer.
 *
 *  WHY IT WORKS:
 *    In F_{p²}: (√ω)^p = ω^((p-1)/2) · √ω = -√ω (since ω is QNR).
 *    So (t + √ω)^p = t^p + (√ω)^p = t - √ω (Frobenius).
 *    (t + √ω)^(p+1) = (t + √ω)(t - √ω) = t² - ω = t² - (t² - a) = a.
 *    Taking square root: (t + √ω)^((p+1)/2) = ±√a. ∎
 *
 *  WHEN TO USE:
 *    - When p-1 has large power of 2 (Tonelli-Shanks can be slow)
 *    - Conceptually cleaner than Tonelli-Shanks
 *
 *  TIME: O(log p) — just one exponentiation in F_{p²}
 *
 *  Reference: https://cp-algorithms.com/algebra/quadratic_residue.html
 * ============================================================================
 */

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
#define nl '\n'

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

i64 powmod(i64 b, i64 e, i64 m) {
    i64 r = 1; b %= m;
    if (b < 0) b += m;
    while (e > 0) { if (e & 1) r = r * b % m; b = b * b % m; e >>= 1; }
    return r;
}

// Euler's criterion: a^((p-1)/2) mod p ∈ {0, 1, p-1}
i64 legendre(i64 a, i64 p) {
    i64 r = powmod(a % p + p, (p - 1) / 2, p);
    return r == p - 1 ? -1 : r;
}

// ============================================================================
//  📌 CIPOLLA'S ALGORITHM
// ============================================================================

struct Fp2 {
    i64 a, b;  // a + b√ω
};

i64 cipolla_omega;  // global ω for F_{p²} multiplication
i64 cipolla_p;

Fp2 fp2_mul(Fp2 x, Fp2 y) {
    return {
        (x.a * y.a % cipolla_p + x.b % cipolla_p * (y.b % cipolla_p) % cipolla_p * (cipolla_omega % cipolla_p) % cipolla_p) % cipolla_p,
        (x.a * y.b % cipolla_p + x.b * y.a % cipolla_p) % cipolla_p
    };
}

Fp2 fp2_pow(Fp2 base, i64 exp) {
    Fp2 res = {1, 0};
    while (exp > 0) {
        if (exp & 1) res = fp2_mul(res, base);
        base = fp2_mul(base, base);
        exp >>= 1;
    }
    return res;
}

// Returns x such that x² ≡ a (mod p), or -1 if no solution
i64 cipolla(i64 a, i64 p) {
    a %= p;
    if (a < 0) a += p;
    if (a == 0) return 0;
    if (p == 2) return a;
    if (legendre(a, p) != 1) return -1;  // not a QR

    cipolla_p = p;

    // Find t such that t²-a is QNR
    i64 t;
    do {
        t = rng() % p;
        cipolla_omega = ((t * t - a) % p + p) % p;
    } while (legendre(cipolla_omega, p) != -1);

    // Compute (t + √ω)^((p+1)/2) in F_{p²}
    Fp2 result = fp2_pow({t, 1}, (p + 1) / 2);

    // Result should have b = 0
    assert(result.b == 0);

    i64 x = result.a % p;
    if (x < 0) x += p;
    return min(x, p - x);  // return the smaller root
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Cipolla's Algorithm ===" << nl << nl;

    // Test cases
    vec<pair<i64,i64>> tests = {
        {4, 7}, {2, 7}, {3, 11}, {5, 11},
        {2, 17}, {4, 1000000007}, {2, 998244353}
    };

    for (auto [a, p] : tests) {
        i64 x = cipolla(a, p);
        if (x >= 0) {
            cout << "√" << a << " mod " << p << " = " << x;
            cout << " [check: " << x << "² mod " << p << " = " << (x * x % p) << "]";
            assert(x * x % p == a % p);
            cout << " ✓" << nl;
        } else {
            cout << "√" << a << " mod " << p << " = NO SOLUTION" << nl;
        }
    }

    // Test non-residues
    cout << nl << "--- Non-residues mod 7 ---" << nl;
    for (int a = 1; a < 7; a++) {
        i64 x = cipolla(a, 7);
        if (x >= 0) cout << "√" << a << " = " << x << nl;
        else cout << "√" << a << " = QNR" << nl;
    }

    return 0;
}

