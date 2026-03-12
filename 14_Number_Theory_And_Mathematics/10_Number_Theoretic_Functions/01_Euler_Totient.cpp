/*
 * ============================================================================
 *  📘 01 — Euler's Totient Function φ(n)
 * ============================================================================
 *
 *  DEFINITION: φ(n) = count of k in [1,n] with gcd(k,n) = 1
 *
 *  FORMULA: φ(n) = n × Π(1 - 1/p) for all prime factors p of n
 *
 *  PROOF (by Inclusion-Exclusion):
 *    Count of numbers in [1,n] NOT divisible by any prime factor of n:
 *    |[1,n] \ (multiples of p1 ∪ p2 ∪ ... ∪ pk)|
 *    = n - Σ(n/pi) + Σ(n/pipj) - ...
 *    = n(1 - 1/p1)(1 - 1/p2)...(1 - 1/pk)
 *
 *  PROPERTIES:
 *    1. φ(p) = p-1 for prime p
 *    2. φ(p^k) = p^(k-1)(p-1)
 *    3. Multiplicative: gcd(a,b)=1 → φ(ab) = φ(a)φ(b)
 *    4. Σ_{d|n} φ(d) = n
 *    5. Euler's theorem: a^φ(n) ≡ 1 (mod n) when gcd(a,n)=1
 *
 *  Reference: https://cp-algorithms.com/algebra/phi-function.html
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
//  📌 SINGLE φ(n) — O(√n)
// ============================================================================
//  Process: for each prime factor p, multiply by (1 - 1/p)
//  Implementation: result = result / p * (p - 1) for each distinct p
//
//  DRY RUN: φ(36)
//    n = 36, result = 36
//    p=2: 36 divisible → result = 36/2*(2-1) = 18, divide out 2s: 36→9
//    p=3: 9 divisible → result = 18/3*(3-1) = 12, divide out 3s: 9→1
//    n=1, stop. φ(36) = 12 ✓
// ============================================================================

i64 euler_phi(i64 n) {
    i64 result = n;
    for (i64 p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;  // multiply by (1 - 1/p)
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

// ============================================================================
//  📌 SIEVE OF EULER TOTIENT — O(n log log n)
// ============================================================================
//  Similar to sieve of Eratosthenes: for each prime p,
//  multiply all multiples of p by (1 - 1/p).
// ============================================================================

vec<i64> phi_sieve(int n) {
    vec<i64> phi(n + 1);
    iota(phi.begin(), phi.end(), 0);  // phi[i] = i

    for (int p = 2; p <= n; p++) {
        if (phi[p] == p) {  // p is prime (unchanged)
            for (int j = p; j <= n; j += p) {
                phi[j] -= phi[j] / p;  // multiply by (1 - 1/p)
            }
        }
    }
    return phi;
}

// ============================================================================
//  📌 SIEVE using LINEAR SIEVE — O(n)
// ============================================================================

vec<i64> phi_linear_sieve(int n) {
    vec<i64> phi(n + 1, 0);
    vec<int> primes;
    phi[1] = 1;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == 0) {  // i is prime
            phi[i] = i - 1;
            primes.push_back(i);
        }
        for (int j = 0; j < sz(primes) && (i64)primes[j] * i <= n; j++) {
            int p = primes[j];
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;  // p already divides i
                break;
            } else {
                phi[i * p] = phi[i] * (p - 1);  // multiplicative
            }
        }
    }
    return phi;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Euler's Totient Function ===" << nl << nl;

    // Single values
    cout << "--- Single φ(n) ---" << nl;
    vec<i64> test = {1, 2, 6, 10, 12, 36, 100, 360, 1000000007LL};
    for (i64 n : test) {
        cout << "φ(" << n << ") = " << euler_phi(n) << nl;
    }

    // Dry run
    cout << nl << "--- Dry Run: φ(60) ---" << nl;
    cout << "60 = 2² × 3 × 5" << nl;
    cout << "φ(60) = 60 × (1-1/2) × (1-1/3) × (1-1/5)" << nl;
    cout << "      = 60 × 1/2 × 2/3 × 4/5" << nl;
    cout << "      = 60 × 8/30 = 16" << nl;
    cout << "Computed: " << euler_phi(60) << nl;

    // Verify property: Σ φ(d) for d|n = n
    cout << nl << "--- Verify: Σ_{d|n} φ(d) = n ---" << nl;
    auto phi = phi_sieve(100);
    for (int n = 1; n <= 20; n++) {
        i64 sum = 0;
        for (int d = 1; d <= n; d++) {
            if (n % d == 0) sum += phi[d];
        }
        cout << "n=" << n << ": Σφ(d) = " << sum << (sum == n ? " ✓" : " ✗") << nl;
    }

    // φ table
    cout << nl << "--- φ(n) for n = 1 to 30 ---" << nl;
    auto phi2 = phi_linear_sieve(30);
    for (int i = 1; i <= 30; i++) {
        cout << "φ(" << i << ")=" << phi2[i] << "  ";
        if (i % 10 == 0) cout << nl;
    }
    cout << nl;

    // Verify two sieve methods agree
    auto phi_a = phi_sieve(10000);
    auto phi_b = phi_linear_sieve(10000);
    assert(phi_a == phi_b);
    cout << "Both sieve methods agree up to 10000 ✓" << nl;

    return 0;
}

