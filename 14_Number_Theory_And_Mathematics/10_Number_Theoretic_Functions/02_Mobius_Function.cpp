/*
 * ============================================================================
 *  📘 02 — Möbius Function & Sieve
 * ============================================================================
 *
 *  DEFINITION:
 *    μ(1) = 1
 *    μ(n) = (-1)^k if n = p₁p₂...pₖ (squarefree, k distinct primes)
 *    μ(n) = 0 if p² | n for some prime p
 *
 *  KEY IDENTITY: Σ_{d|n} μ(d) = [n = 1]
 *
 *  MÖBIUS INVERSION:
 *    If f(n) = Σ_{d|n} g(d), then g(n) = Σ_{d|n} μ(d) × f(n/d)
 *
 *  APPLICATION: Count pairs (a,b) in [1,N]² with gcd(a,b) = 1
 *    = Σ_{d=1}^{N} μ(d) × ⌊N/d⌋²
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
//  📌 MÖBIUS SIEVE (linear sieve)
// ============================================================================

struct MobiusSieve {
    int n;
    vec<int> mu, spf;
    vec<int> primes;

    MobiusSieve(int n) : n(n), mu(n+1, 0), spf(n+1, 0) {
        mu[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (spf[i] == 0) {
                spf[i] = i;
                primes.pb(i);
                mu[i] = -1;  // prime: single factor, odd count
            }
            for (int j = 0; j < sz(primes) && primes[j] <= spf[i] && (i64)primes[j]*i <= n; j++) {
                spf[primes[j] * i] = primes[j];
                if (i % primes[j] == 0) {
                    mu[primes[j] * i] = 0;  // p² divides
                    break;
                } else {
                    mu[primes[j] * i] = -mu[i];  // one more prime factor
                }
            }
        }
    }
};

// ============================================================================
//  📌 COUNT COPRIME PAIRS using Möbius
// ============================================================================
//  Count of (a,b) in [1,N]² with gcd(a,b) = 1:
//    = Σ_{d=1}^{N} μ(d) × ⌊N/d⌋²
//  Optimized with block decomposition: O(√N)
// ============================================================================

i64 coprime_pairs(i64 N, const vec<int>& mu_prefix) {
    i64 result = 0;
    for (i64 d = 1; d <= N; ) {
        i64 v = N / d;
        i64 hi = N / v;
        i64 mu_sum = mu_prefix[hi] - mu_prefix[d - 1];
        result += mu_sum * v * v;
        d = hi + 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N = 1000000;
    MobiusSieve sieve(N);

    cout << "=== Möbius Function ===" << nl << nl;

    // Print μ for small values
    cout << "--- μ(n) for n = 1..30 ---" << nl;
    for (int n = 1; n <= 30; n++) {
        cout << "μ(" << n << ")=" << sieve.mu[n] << "  ";
        if (n % 10 == 0) cout << nl;
    }
    cout << nl;

    // Verify: Σ_{d|n} μ(d) = [n=1]
    cout << "--- Verify: Σ_{d|n} μ(d) = [n=1] ---" << nl;
    for (int n = 1; n <= 20; n++) {
        int sum = 0;
        for (int d = 1; d <= n; d++) if (n % d == 0) sum += sieve.mu[d];
        cout << "n=" << n << ": " << sum << (sum == (n == 1 ? 1 : 0) ? " ✓" : " ✗") << "  ";
        if (n % 5 == 0) cout << nl;
    }

    // Coprime pair counting
    cout << nl << "--- Coprime Pairs in [1,N]² ---" << nl;
    vec<int> mu_prefix(N + 1, 0);
    for (int i = 1; i <= N; i++) mu_prefix[i] = mu_prefix[i-1] + sieve.mu[i];

    for (int n : {10, 100, 1000, 10000, 100000, 1000000}) {
        i64 count = coprime_pairs(n, mu_prefix);
        cout << "N=" << n << ": " << count << " coprime pairs" << nl;
    }

    return 0;
}

