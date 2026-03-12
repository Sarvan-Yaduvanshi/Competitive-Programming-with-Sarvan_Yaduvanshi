/*
 * ============================================================================
 *  📘 03 — Divisor Count τ(n) and Divisor Sum σ(n) Sieve
 * ============================================================================
 *
 *  FORMULAS (from prime factorization n = p₁^a₁ × p₂^a₂ × ...):
 *    τ(n) = Π(aᵢ + 1)
 *    σ(n) = Π(pᵢ^(aᵢ+1) - 1) / (pᵢ - 1)
 *
 *  SIEVE METHOD: O(n log n) — for each d, add contribution to all multiples.
 *
 *  DRY RUN: τ(12) = ?
 *    12 = 2² × 3¹
 *    τ(12) = (2+1)(1+1) = 6
 *    Divisors: {1, 2, 3, 4, 6, 12} → count = 6 ✓
 *
 *  DRY RUN: σ(12) = ?
 *    σ(12) = (2³-1)/(2-1) × (3²-1)/(3-1) = 7 × 4 = 28
 *    Sum: 1+2+3+4+6+12 = 28 ✓
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

// ============================================================================
//  📌 SIEVE OF DIVISOR COUNT — O(n log n)
// ============================================================================
//  For each d = 1..n, increment tau[d], tau[2d], tau[3d], ...
// ============================================================================

vec<int> sieve_tau(int n) {
    vec<int> tau(n + 1, 0);
    for (int d = 1; d <= n; d++) {
        for (int j = d; j <= n; j += d) {
            tau[j]++;
        }
    }
    return tau;
}

// ============================================================================
//  📌 SIEVE OF DIVISOR SUM — O(n log n)
// ============================================================================

vec<i64> sieve_sigma(int n) {
    vec<i64> sigma(n + 1, 0);
    for (int d = 1; d <= n; d++) {
        for (int j = d; j <= n; j += d) {
            sigma[j] += d;
        }
    }
    return sigma;
}

// ============================================================================
//  📌 SINGLE τ(n) and σ(n) via trial division — O(√n)
// ============================================================================

int tau_single(i64 n) {
    int result = 1;
    for (i64 p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            int a = 0;
            while (n % p == 0) { n /= p; a++; }
            result *= (a + 1);
        }
    }
    if (n > 1) result *= 2;
    return result;
}

i64 sigma_single(i64 n) {
    i64 result = 1;
    for (i64 p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            i64 pw = 1, geo = 1;
            while (n % p == 0) { n /= p; pw *= p; geo += pw; }
            result *= geo;
        }
    }
    if (n > 1) result *= (1 + n);
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Divisor Functions τ(n) and σ(n) ===" << nl << nl;

    int N = 30;
    auto tau = sieve_tau(N);
    auto sigma = sieve_sigma(N);

    cout << "--- Table for n = 1..30 ---" << nl;
    cout << "  n | τ(n) | σ(n)" << nl;
    cout << "----|------|------" << nl;
    for (int n = 1; n <= N; n++) {
        printf("%3d | %3d  | %4lld\n", n, tau[n], sigma[n]);
    }

    // Verify single-value functions
    cout << nl << "--- Verify single-value computation ---" << nl;
    for (int n = 1; n <= 30; n++) {
        assert(tau_single(n) == tau[n]);
        assert(sigma_single(n) == sigma[n]);
    }
    cout << "All match ✓" << nl;

    // Highly composite numbers (most divisors)
    cout << nl << "--- Most Divisors up to 10000 ---" << nl;
    auto tau_big = sieve_tau(10000);
    int best_n = 1;
    for (int n = 2; n <= 10000; n++) {
        if (tau_big[n] > tau_big[best_n]) {
            best_n = n;
            cout << "n=" << n << ": τ=" << tau_big[n] << nl;
        }
    }

    // Perfect numbers: σ(n) = 2n
    cout << nl << "--- Perfect Numbers up to 10000 ---" << nl;
    auto sigma_big = sieve_sigma(10000);
    for (int n = 2; n <= 10000; n++) {
        if (sigma_big[n] == 2 * n) cout << n << " ";
    }
    cout << nl;

    return 0;
}

