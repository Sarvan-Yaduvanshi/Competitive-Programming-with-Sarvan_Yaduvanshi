/*
 * ============================================================================
 *  📘 02 — Dirichlet Convolution & Möbius Inversion
 * ============================================================================
 *
 *  DIRICHLET CONVOLUTION:
 *    (f * g)(n) = Σ_{d|n} f(d) × g(n/d)
 *
 *  COMPUTING (f * g) for all n ≤ N: O(N log N)
 *    For each d, for each multiple m of d: h[m] += f[d] * g[m/d]
 *
 *  KEY IDENTITIES:
 *    μ * 1 = ε        (Möbius is inverse of constant)
 *    φ * 1 = id        (sum of totients = n)
 *    μ * id = φ        (Möbius inversion of φ)
 *    τ = 1 * 1         (divisor count)
 *    σ = 1 * id        (divisor sum)
 *
 *  MÖBIUS INVERSION:
 *    If f = g * 1, then g = f * μ.
 *
 *  APPLICATION: Given f(n) = Σ_{d|n} g(d), recover g(n).
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

// ============================================================================
//  📌 DIRICHLET CONVOLUTION: h = f * g, O(N log N)
// ============================================================================

vec<i64> dirichlet_convolve(const vec<i64>& f, const vec<i64>& g, int N) {
    vec<i64> h(N + 1, 0);
    for (int d = 1; d <= N; d++) {
        for (int m = d; m <= N; m += d) {
            h[m] += f[d] * g[m / d];
        }
    }
    return h;
}

// ============================================================================
//  📌 MÖBIUS SIEVE
// ============================================================================

vec<int> mobius_sieve(int N) {
    vec<int> mu(N + 1, 0), spf(N + 1, 0);
    vec<int> primes;
    mu[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (spf[i] == 0) { spf[i] = i; primes.push_back(i); mu[i] = -1; }
        for (int j = 0; j < sz(primes) && primes[j] <= spf[i] && (i64)primes[j] * i <= N; j++) {
            spf[primes[j] * i] = primes[j];
            if (i % primes[j] == 0) { mu[primes[j] * i] = 0; break; }
            else mu[primes[j] * i] = -mu[i];
        }
    }
    return mu;
}

// ============================================================================
//  📌 EULER TOTIENT SIEVE
// ============================================================================

vec<i64> euler_sieve(int N) {
    vec<i64> phi(N + 1);
    iota(phi.begin(), phi.end(), 0LL);
    for (int i = 2; i <= N; i++) {
        if (phi[i] == i) { // i is prime
            for (int j = i; j <= N; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
    return phi;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N = 30;

    auto mu = mobius_sieve(N);
    auto phi = euler_sieve(N);

    // Build 1(n) = 1, id(n) = n, ε(n) = [n=1]
    vec<i64> one(N + 1, 1), id_func(N + 1), eps(N + 1, 0);
    for (int i = 0; i <= N; i++) id_func[i] = i;
    eps[1] = 1; one[0] = 0; id_func[0] = 0;

    vec<i64> mu_64(N + 1);
    for (int i = 0; i <= N; i++) mu_64[i] = mu[i];

    cout << "=== Dirichlet Convolution ===" << nl << nl;

    // Verify μ * 1 = ε
    cout << "--- μ * 1 = ε ---" << nl;
    auto h1 = dirichlet_convolve(mu_64, one, N);
    bool ok = true;
    for (int n = 1; n <= N; n++) {
        if (h1[n] != eps[n]) { ok = false; cout << "FAIL at n=" << n << nl; }
    }
    cout << (ok ? "✓ Verified" : "✗ Failed") << nl;

    // Verify φ * 1 = id
    cout << nl << "--- φ * 1 = id ---" << nl;
    auto h2 = dirichlet_convolve(phi, one, N);
    ok = true;
    for (int n = 1; n <= N; n++) {
        if (h2[n] != n) { ok = false; cout << "FAIL at n=" << n << ": " << h2[n] << "!=" << n << nl; }
    }
    cout << (ok ? "✓ Verified" : "✗ Failed") << nl;

    // Verify 1 * 1 = τ (divisor count)
    cout << nl << "--- 1 * 1 = τ ---" << nl;
    auto tau = dirichlet_convolve(one, one, N);
    for (int n = 1; n <= 20; n++) {
        cout << "τ(" << n << ")=" << tau[n] << "  ";
        if (n % 5 == 0) cout << nl;
    }
    cout << nl;

    // Möbius inversion demo
    cout << nl << "--- Möbius Inversion: recover φ from id ---" << nl;
    auto phi_recovered = dirichlet_convolve(id_func, mu_64, N);
    ok = true;
    for (int n = 1; n <= N; n++) {
        if (phi_recovered[n] != phi[n]) { ok = false; break; }
    }
    cout << (ok ? "✓ φ = id * μ verified" : "✗ Failed") << nl;

    return 0;
}

