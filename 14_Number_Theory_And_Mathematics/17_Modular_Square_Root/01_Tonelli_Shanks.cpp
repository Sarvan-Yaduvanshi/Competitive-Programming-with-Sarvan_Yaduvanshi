/*
 * ============================================================================
 *  📘 01 — Tonelli-Shanks Algorithm (Square Root mod Prime)
 * ============================================================================
 *
 *  PROBLEM: Find x such that x² ≡ a (mod p), p prime.
 *
 *  EULER'S CRITERION: a is QR mod p iff a^((p-1)/2) ≡ 1 (mod p)
 *
 *  ALGORITHM (Tonelli-Shanks):
 *    Write p-1 = 2^s × q (q odd)
 *    Find QNR z (test random values)
 *    Set M=s, c=z^q, t=a^q, R=a^((q+1)/2)
 *    Loop:
 *      if t ≡ 1: return R
 *      Find smallest i: t^(2^i) ≡ 1
 *      b = c^(2^(M-i-1))
 *      M = i, c = b², t = t×b², R = R×b
 *
 *  SPECIAL CASE: If p ≡ 3 (mod 4): x = a^((p+1)/4) mod p
 *    Proof: x² = a^((p+1)/2) = a^((p-1)/2) × a = 1 × a = a (by Euler). ∎
 *
 *  TIME: O(log² p)
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
#include <string>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;
using i64 = long long;
using u128 = __uint128_t;
template<class T> using vec = vector<T>;
#define nl '\n'

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

i64 mulmod(i64 a, i64 b, i64 m) { return (u128)a * b % m; }

i64 powmod(i64 base, i64 exp, i64 mod) {
    i64 res = 1; base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) res = mulmod(res, base, mod);
        base = mulmod(base, base, mod);
        exp >>= 1;
    }
    return res;
}

// Legendre symbol (a/p) = a^((p-1)/2) mod p
int legendre(i64 a, i64 p) {
    i64 val = powmod(a % p, (p - 1) / 2, p);
    if (val == 0) return 0;
    if (val == 1) return 1;
    return -1;  // val == p - 1
}

// ============================================================================
//  📌 TONELLI-SHANKS ALGORITHM
// ============================================================================

i64 tonelli_shanks(i64 a, i64 p) {
    a %= p;
    if (a < 0) a += p;
    if (a == 0) return 0;
    if (p == 2) return a;

    // Check if a is QR
    if (legendre(a, p) != 1) return -1;  // no solution

    // Special case: p ≡ 3 (mod 4)
    if (p % 4 == 3) {
        return powmod(a, (p + 1) / 4, p);
    }

    // Write p-1 = 2^s × q
    i64 q = p - 1;
    int s = 0;
    while (q % 2 == 0) { q /= 2; s++; }

    // Find QNR z
    i64 z = 2;
    while (legendre(z, p) != -1) z++;

    i64 M = s;
    i64 c = powmod(z, q, p);
    i64 t = powmod(a, q, p);
    i64 R = powmod(a, (q + 1) / 2, p);

    while (true) {
        if (t == 1) return R;

        // Find smallest i with t^(2^i) ≡ 1
        i64 i = 1, tmp = mulmod(t, t, p);
        while (tmp != 1) { tmp = mulmod(tmp, tmp, p); i++; }

        // b = c^(2^(M-i-1))
        i64 b = c;
        for (i64 j = 0; j < M - i - 1; j++) b = mulmod(b, b, p);

        M = i;
        c = mulmod(b, b, p);
        t = mulmod(t, c, p);
        R = mulmod(R, b, p);
    }
}

// Returns both roots (r and p-r), or {-1,-1} if no root
pair<i64,i64> sqrt_mod(i64 a, i64 p) {
    i64 r = tonelli_shanks(a, p);
    if (r == -1) return {-1, -1};
    return {min(r, p - r), max(r, p - r)};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Tonelli-Shanks (Modular Square Root) ===" << nl << nl;

    // Test: x² ≡ a (mod p)
    cout << "--- Basic Tests ---" << nl;
    vec<pair<i64,i64>> tests = {{4,7},{2,7},{3,11},{5,13},{10,13},{2,1000000007}};
    for (auto [a, p] : tests) {
        auto [r1, r2] = sqrt_mod(a, p);
        if (r1 == -1) {
            cout << "√" << a << " mod " << p << " = NO SOLUTION (QNR)" << nl;
        } else {
            cout << "√" << a << " mod " << p << " = {" << r1 << ", " << r2 << "}";
            cout << "  [check: " << r1 << "²=" << mulmod(r1,r1,p) << ", "
                 << r2 << "²=" << mulmod(r2,r2,p) << "]" << nl;
        }
    }

    // Quadratic residues mod 13
    cout << nl << "--- Quadratic Residues mod 13 ---" << nl;
    cout << "QR: ";
    for (int a = 1; a < 13; a++) {
        if (legendre(a, 13) == 1) cout << a << " ";
    }
    cout << nl << "QNR: ";
    for (int a = 1; a < 13; a++) {
        if (legendre(a, 13) == -1) cout << a << " ";
    }
    cout << nl << "Exactly (p-1)/2 = 6 of each ✓" << nl;

    return 0;
}

