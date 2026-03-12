/*
 * ============================================================================
 *  📘 01 — Multiplicative Functions & Möbius Sieve
 * ============================================================================
 *
 *  A function f is multiplicative if:
 *    f(1) = 1 and f(ab) = f(a)f(b) when gcd(a,b) = 1
 *
 *  KEY FUNCTIONS:
 *    μ(n) = {1 if n=1, (-1)^k if n=p1p2...pk squarefree, 0 otherwise}
 *    φ(n) = n × Π(1-1/p)
 *    τ(n) = Π(aᵢ+1)  (divisor count)
 *    σ(n) = Π(p^(a+1)-1)/(p-1)  (divisor sum)
 *
 *  DIRICHLET IDENTITIES:
 *    Σ_{d|n} μ(d) = [n=1]
 *    Σ_{d|n} φ(d) = n
 *    μ * 1 = ε,  φ * 1 = id,  μ * id = φ
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
//  📌 LINEAR SIEVE computing μ, φ, τ, σ simultaneously
// ============================================================================

struct MultiSieve {
    int n;
    vec<int> spf, primes;
    vec<int> mu;     // Möbius function
    vec<i64> phi;    // Euler totient
    vec<int> tau;    // Divisor count
    vec<i64> sigma;  // Divisor sum

    MultiSieve(int n) : n(n), spf(n+1,0), mu(n+1,0), phi(n+1,0), tau(n+1,0), sigma(n+1,0) {
        mu[1] = 1; phi[1] = 1; tau[1] = 1; sigma[1] = 1;

        // We'll use a simpler sieve approach for clarity
        // First: linear sieve for SPF
        for (int i = 2; i <= n; i++) {
            if (spf[i] == 0) {
                spf[i] = i;
                primes.push_back(i);
            }
            for (int j = 0; j < sz(primes) && primes[j] <= spf[i] && (i64)primes[j]*i <= n; j++) {
                spf[primes[j] * i] = primes[j];
            }
        }

        // Compute all functions using factorization via SPF
        for (int i = 2; i <= n; i++) {
            int x = i, p = spf[i];
            int pk = 1, a = 0;  // p^a dividing i
            while (x % p == 0) { x /= p; pk *= p; a++; }

            // x = i / p^a, gcd(x, p^a) = 1 → use multiplicativity
            if (x == 1) {
                // i = p^a (prime power)
                mu[i] = (a == 1) ? -1 : 0;
                phi[i] = pk - pk / p;  // p^a - p^(a-1)
                tau[i] = a + 1;
                // σ(p^a) = 1 + p + p² + ... + p^a = (p^(a+1)-1)/(p-1)
                sigma[i] = 0;
                i64 pw = 1;
                for (int j = 0; j <= a; j++) { sigma[i] += pw; pw *= p; }
            } else {
                // i = p^a × x with gcd(p^a, x) = 1
                mu[i] = mu[pk] * mu[x];
                phi[i] = phi[pk] * phi[x];
                tau[i] = tau[pk] * tau[x];
                sigma[i] = sigma[pk] * sigma[x];
            }
        }
    }
};

// ============================================================================
//  📌 DIRICHLET CONVOLUTION: (f*g)(n) = Σ_{d|n} f(d)g(n/d)
// ============================================================================

vec<i64> dirichlet_conv(const vec<i64>& f, const vec<i64>& g, int n) {
    vec<i64> h(n + 1, 0);
    for (int d = 1; d <= n; d++) {
        for (int j = d; j <= n; j += d) {
            h[j] += f[d] * g[j / d];
        }
    }
    return h;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N = 100;
    MultiSieve sieve(N);

    cout << "=== Multiplicative Functions ===" << nl << nl;

    // Print table
    cout << "--- Function Table (n=1..20) ---" << nl;
    cout << " n  | μ(n) | φ(n) | τ(n) | σ(n)" << nl;
    cout << "----|------|------|------|-----" << nl;
    for (int n = 1; n <= 20; n++) {
        printf("%3d | %3d  | %3lld  | %3d  | %3lld\n",
               n, sieve.mu[n], sieve.phi[n], sieve.tau[n], sieve.sigma[n]);
    }

    // Verify identities
    cout << nl << "--- Verify: Σ_{d|n} μ(d) = [n=1] ---" << nl;
    for (int n = 1; n <= 20; n++) {
        int sum = 0;
        for (int d = 1; d <= n; d++) if (n % d == 0) sum += sieve.mu[d];
        cout << "n=" << n << ": " << sum << (sum == (n==1) ? " ✓" : " ✗") << "  ";
        if (n % 5 == 0) cout << nl;
    }

    cout << nl << "--- Verify: Σ_{d|n} φ(d) = n ---" << nl;
    for (int n = 1; n <= 20; n++) {
        i64 sum = 0;
        for (int d = 1; d <= n; d++) if (n % d == 0) sum += sieve.phi[d];
        assert(sum == n);
    }
    cout << "All verified ✓" << nl;

    // Möbius inversion: φ(n) = Σ_{d|n} μ(d) × (n/d)
    cout << nl << "--- Verify Möbius Inversion: φ = μ * id ---" << nl;
    for (int n = 1; n <= 20; n++) {
        i64 sum = 0;
        for (int d = 1; d <= n; d++) if (n % d == 0) sum += sieve.mu[d] * (n / d);
        assert(sum == sieve.phi[n]);
    }
    cout << "φ = μ * id verified ✓" << nl;

    return 0;
}

