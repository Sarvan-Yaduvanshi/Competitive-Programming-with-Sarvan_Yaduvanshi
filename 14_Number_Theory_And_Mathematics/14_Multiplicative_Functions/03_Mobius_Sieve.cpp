/*
 * ============================================================================
 *  📘 03 — Möbius Sieve & Applications
 * ============================================================================
 *
 *  DEFINITION:
 *    μ(1) = 1
 *    μ(n) = (-1)^k if n = p₁p₂...pₖ (squarefree, k distinct primes)
 *    μ(n) = 0      if p² | n for some prime p
 *
 *  SIEVE: Compute μ(1..N) in O(N) via linear sieve.
 *
 *  KEY IDENTITY: Σ_{d|n} μ(d) = [n = 1]
 *
 *  APPLICATION 1: Count pairs (a,b) ∈ [1,N]² with gcd(a,b) = 1
 *    = Σ_{d=1}^{N} μ(d) × ⌊N/d⌋²
 *
 *  APPLICATION 2: Sum Σ_{i=1}^{N} Σ_{j=1}^{N} gcd(i,j)
 *    = Σ_{d=1}^{N} φ(d) × ⌊N/d⌋²
 *    (via μ * id = φ relationship)
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
#include <algorithm>
#include <cmath>
#include <numeric>
#include <cassert>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
#define nl '\n'
#define sz(x) ((int)(x).size())
#define pb push_back

// ============================================================================
//  📌 LINEAR SIEVE for μ(n)
// ============================================================================

struct MuSieve {
    int n;
    vec<int> mu, spf;
    vec<int> primes;
    vec<i64> prefix_mu;  // prefix sum of μ

    MuSieve(int n) : n(n), mu(n+1, 0), spf(n+1, 0), prefix_mu(n+1, 0) {
        mu[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (spf[i] == 0) {
                spf[i] = i;
                primes.pb(i);
                mu[i] = -1;
            }
            for (int j = 0; j < sz(primes) && primes[j] <= spf[i] && (i64)primes[j]*i <= n; j++) {
                spf[primes[j] * i] = primes[j];
                if (i % primes[j] == 0) {
                    mu[primes[j] * i] = 0;  // p² divides
                    break;
                } else {
                    mu[primes[j] * i] = -mu[i];
                }
            }
        }
        for (int i = 1; i <= n; i++) prefix_mu[i] = prefix_mu[i-1] + mu[i];
    }
};

// ============================================================================
//  📌 COUNT COPRIME PAIRS in [1,N]² using Möbius + block decomposition
// ============================================================================
//  Answer = Σ_{d=1}^{N} μ(d) × ⌊N/d⌋²
//  Optimized: O(√N) using block decomposition on ⌊N/d⌋
// ============================================================================

i64 coprime_pairs(i64 N, const vec<i64>& prefix_mu) {
    i64 result = 0;
    for (i64 d = 1; d <= N; ) {
        i64 v = N / d;
        i64 hi = N / v;
        i64 mu_sum = prefix_mu[hi] - prefix_mu[d - 1];
        result += mu_sum * v * v;
        d = hi + 1;
    }
    return result;
}

// ============================================================================
//  📌 SUM OF GCD: Σ_{i=1}^{N} Σ_{j=1}^{N} gcd(i,j)
// ============================================================================
//  = Σ_{d=1}^{N} d × (number of pairs with gcd = d)
//  = Σ_{d=1}^{N} d × Σ_{k=1}^{N/d} μ(k) × ⌊N/(dk)⌋²
//  = Σ_{e=1}^{N} ⌊N/e⌋² × Σ_{d|e} d × μ(e/d)
//  = Σ_{e=1}^{N} ⌊N/e⌋² × φ(e)
// ============================================================================

i64 sum_of_gcd(i64 N, const vec<i64>& prefix_phi) {
    i64 result = 0;
    for (i64 e = 1; e <= N; ) {
        i64 v = N / e;
        i64 hi = N / v;
        i64 phi_sum = prefix_phi[hi] - prefix_phi[e - 1];
        result += phi_sum * v * v;
        e = hi + 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N = 1000000;
    MuSieve sieve(N);

    cout << "=== Möbius Sieve & Applications ===" << nl << nl;

    // Print μ for small values
    cout << "--- μ(n) for n = 1..30 ---" << nl;
    for (int n = 1; n <= 30; n++) {
        cout << "μ(" << n << ")=" << sieve.mu[n];
        if (n < 30) cout << ", ";
        if (n % 10 == 0) cout << nl;
    }
    cout << nl;

    // Verify Σ_{d|n} μ(d) = [n=1]
    cout << "--- Verify: Σ_{d|n} μ(d) = [n=1] ---" << nl;
    bool ok = true;
    for (int n = 1; n <= 100; n++) {
        int sum = 0;
        for (int d = 1; d <= n; d++) if (n % d == 0) sum += sieve.mu[d];
        if (sum != (n == 1 ? 1 : 0)) { ok = false; break; }
    }
    cout << (ok ? "✓ Verified for n=1..100" : "✗ Failed") << nl;

    // Coprime pairs
    cout << nl << "--- Coprime Pairs in [1,N]² ---" << nl;
    for (int n : {10, 100, 1000, 10000}) {
        i64 result = coprime_pairs(n, sieve.prefix_mu);
        cout << "N=" << n << ": " << result << " coprime pairs" << nl;
    }

    // Build prefix phi for sum_of_gcd
    cout << nl << "--- Sum of GCD ---" << nl;
    {
        vec<i64> phi(N + 1);
        iota(phi.begin(), phi.end(), 0LL);
        for (int i = 2; i <= N; i++) {
            if (phi[i] == i) {
                for (int j = i; j <= N; j += i) phi[j] -= phi[j] / i;
            }
        }
        vec<i64> prefix_phi(N + 1, 0);
        for (int i = 1; i <= N; i++) prefix_phi[i] = prefix_phi[i-1] + phi[i];

        for (int n : {10, 100, 1000}) {
            i64 fast = sum_of_gcd(n, prefix_phi);
            // Brute force for small n
            if (n <= 1000) {
                i64 brute = 0;
                for (int i = 1; i <= n; i++)
                    for (int j = 1; j <= n; j++)
                        brute += gcd(i, j);
                cout << "N=" << n << ": fast=" << fast << ", brute=" << brute
                     << (fast == brute ? " ✓" : " ✗") << nl;
            } else {
                cout << "N=" << n << ": " << fast << nl;
            }
        }
    }

    return 0;
}

