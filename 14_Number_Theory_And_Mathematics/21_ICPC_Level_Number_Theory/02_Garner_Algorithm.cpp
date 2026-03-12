/*
 * ============================================================================
 *  📘 02 — Garner's Algorithm (ICPC ready)
 * ============================================================================
 *
 *  See 11_Chinese_Remainder_Theorem/03_Garner_Algorithm.cpp for full version.
 *  This is an ICPC-optimized variant that computes CRT result mod any M.
 *
 *  USE CASE: Compute answer modulo M=10^9+7 when intermediate CRT moduli
 *  are different primes (e.g., computing via NTT with multiple primes).
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
#include <cassert>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
#define nl '\n'
#define sz(x) ((int)(x).size())

i64 powmod(i64 b, i64 e, i64 m) {
    i64 r = 1; b %= m;
    while (e > 0) { if (e & 1) r = r * b % m; b = b * b % m; e >>= 1; }
    return r;
}

// ============================================================================
//  📌 GARNER'S ALGORITHM (ICPC template)
// ============================================================================
//  r[i] = x mod m[i], m[i] pairwise coprime (all prime typically)
//  Computes x mod output_mod
// ============================================================================

i64 garner(vec<i64> r, vec<i64> m, i64 output_mod) {
    int k = sz(r);
    vec<i64> C(k);  // mixed radix coefficients

    for (int i = 0; i < k; i++) {
        C[i] = r[i];
        for (int j = 0; j < i; j++) {
            C[i] = (C[i] - C[j] + m[i]) % m[i];
            C[i] = C[i] * powmod(m[j], m[i] - 2, m[i]) % m[i];
        }
    }

    // Reconstruct mod output_mod
    i64 result = 0, mult = 1;
    for (int i = 0; i < k; i++) {
        result = (result + C[i] % output_mod * mult) % output_mod;
        mult = mult * (m[i] % output_mod) % output_mod;
    }
    return (result + output_mod) % output_mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Garner's Algorithm (ICPC) ===" << nl << nl;

    // Classic 3-prime NTT reconstruction
    // Compute x = 12345678901234567 using 3 NTT primes
    i64 x = 12345678901234567LL;
    vec<i64> primes = {998244353, 985661441, 754974721};
    vec<i64> r(3);
    for (int i = 0; i < 3; i++) r[i] = x % primes[i];

    i64 MOD = 1000000007;
    i64 reconstructed = garner(r, primes, MOD);
    cout << "Original: " << x << nl;
    cout << "Original mod 10^9+7: " << x % MOD << nl;
    cout << "Garner result: " << reconstructed << nl;
    assert(reconstructed == x % MOD);
    cout << "Match ✓" << nl;

    return 0;
}

