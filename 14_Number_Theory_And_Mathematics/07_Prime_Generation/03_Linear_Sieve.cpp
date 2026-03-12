/*
 * ============================================================================
 *  📘 03 — Linear Sieve (O(n) — Smallest Prime Factor)
 * ============================================================================
 *
 *  KEY IDEA: Each composite number is marked EXACTLY ONCE by its SPF.
 *
 *  ALGORITHM:
 *    for i = 2 to N:
 *      if spf[i] == 0: spf[i] = i, add i to primes
 *      for each prime p in primes:
 *        if p > spf[i] or p*i > N: break
 *        spf[p*i] = p
 *
 *  WHY "p > spf[i]" BREAK?
 *    Ensures p*i is marked by p = spf(p*i). If p > spf[i], then spf[i]
 *    would be the SPF of p*i, not p — so we'd mark it twice later.
 *
 *  DRY RUN (N=20):
 *    i=2:  spf[2]=2, primes={2}
 *          p=2: spf[4]=2
 *    i=3:  spf[3]=3, primes={2,3}
 *          p=2: spf[6]=2
 *          p=3: 3=spf[3], spf[9]=3, break (next p>spf[3])
 *    i=4:  spf[4]=2 (already set)
 *          p=2: 2=spf[4], spf[8]=2, break
 *    i=5:  spf[5]=5, primes={2,3,5}
 *          p=2: spf[10]=2
 *          p=3: spf[15]=3
 *          p=5: spf[25]→skip (>20)
 *    ...
 *
 *  BONUS: O(log n) factorization using SPF!
 *    factorize(n): while n>1, output spf[n], divide n by spf[n]
 *
 *  TIME: O(n)  SPACE: O(n)
 *
 *  Reference: https://cp-algorithms.com/algebra/prime-sieve-linear.html
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
#include <map>
#include <set>
#include <cmath>
#include <numeric>
#include <cassert>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
using pii = pair<int, int>;
#define nl '\n'
#define sz(x) ((int)(x).size())
#define pb push_back

// ============================================================================
//  📌 LINEAR SIEVE with SPF
// ============================================================================

struct LinearSieve {
    int n;
    vec<int> spf;     // smallest prime factor
    vec<int> primes;

    LinearSieve(int n) : n(n), spf(n + 1, 0) {
        for (int i = 2; i <= n; i++) {
            if (spf[i] == 0) {
                spf[i] = i;
                primes.pb(i);
            }
            for (int j = 0; j < sz(primes) && primes[j] <= spf[i] && (i64)primes[j] * i <= n; j++) {
                spf[primes[j] * i] = primes[j];
            }
        }
    }

    bool is_prime(int x) const { return x >= 2 && spf[x] == x; }

    // O(log n) factorization
    vec<pii> factorize(int x) const {
        vec<pii> factors;
        while (x > 1) {
            int p = spf[x], cnt = 0;
            while (x % p == 0) { x /= p; cnt++; }
            factors.pb({p, cnt});
        }
        return factors;
    }

    // Number of divisors
    int divisor_count(int x) const {
        int result = 1;
        while (x > 1) {
            int p = spf[x], cnt = 0;
            while (x % p == 0) { x /= p; cnt++; }
            result *= (cnt + 1);
        }
        return result;
    }

    // Sum of divisors
    i64 divisor_sum(int x) const {
        i64 result = 1;
        while (x > 1) {
            int p = spf[x];
            i64 pw = 1, geo = 1;
            while (x % p == 0) { x /= p; pw *= p; geo += pw; }
            result *= geo;
        }
        return result;
    }

    // Euler totient
    i64 phi(int x) const {
        i64 result = x;
        while (x > 1) {
            int p = spf[x];
            result = result / p * (p - 1);
            while (x % p == 0) x /= p;
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Linear Sieve (SPF) ===" << nl << nl;

    LinearSieve sieve(10000000); // 10^7

    // Print first 25 primes
    cout << "--- First 25 Primes ---" << nl;
    for (int i = 0; i < 25; i++) cout << sieve.primes[i] << " ";
    cout << nl << nl;

    // SPF table
    cout << "--- SPF Table (2 to 30) ---" << nl;
    for (int i = 2; i <= 30; i++) {
        cout << "spf[" << i << "] = " << sieve.spf[i];
        if (sieve.is_prime(i)) cout << " (prime)";
        cout << nl;
    }

    // Factorization demo
    cout << nl << "--- O(log n) Factorization ---" << nl;
    vec<int> test = {12, 36, 60, 100, 360, 720, 2310, 9999991};
    for (int n : test) {
        if (n > sieve.n) continue;
        auto factors = sieve.factorize(n);
        cout << n << " = ";
        for (int i = 0; i < sz(factors); i++) {
            if (i > 0) cout << " × ";
            cout << factors[i].first;
            if (factors[i].second > 1) cout << "^" << factors[i].second;
        }
        cout << "  [τ=" << sieve.divisor_count(n) << ", σ=" << sieve.divisor_sum(n)
             << ", φ=" << sieve.phi(n) << "]" << nl;
    }

    // Prime counting
    cout << nl << "--- Prime Count ---" << nl;
    cout << "Primes up to 10^7: " << sz(sieve.primes) << nl;

    return 0;
}

