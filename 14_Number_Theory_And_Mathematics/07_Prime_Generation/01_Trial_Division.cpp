/*
 * ============================================================================
 *  📘 01 — Trial Division Primality & Factorization
 * ============================================================================
 *
 *  PRIMALITY: Check divisors from 2 to √n → O(√n)
 *  FACTORIZATION: Divide by each prime → O(√n)
 *
 *  WHY √n SUFFICES:
 *    If n = a × b with a ≤ b, then a ≤ √n.
 *    So the smallest factor (other than 1) is ≤ √n.
 *
 *  OPTIMIZATION: Check 2 and 3 first, then only 6k±1.
 *    All primes > 3 are of form 6k±1 (since 6k, 6k±2, 6k+3 are composite).
 *
 *  Reference: https://cp-algorithms.com/algebra/factorization.html
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
using pll = pair<i64, i64>;
#define nl '\n'
#define sz(x) ((int)(x).size())
#define pb push_back

// ============================================================================
//  📌 BASIC PRIMALITY TEST — O(√n)
// ============================================================================

bool is_prime_trial(i64 n) {
    if (n < 2) return false;
    if (n < 4) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (i64 i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// ============================================================================
//  📌 TRIAL DIVISION FACTORIZATION — O(√n)
// ============================================================================

vec<pll> trial_factorize(i64 n) {
    vec<pll> factors;
    for (i64 p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            int cnt = 0;
            while (n % p == 0) { n /= p; cnt++; }
            factors.pb({p, cnt});
        }
    }
    if (n > 1) factors.pb({n, 1});
    return factors;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Trial Division ===" << nl << nl;

    // Primality
    cout << "--- Primality ---" << nl;
    for (i64 n : {1LL,2LL,3LL,4LL,17LL,100LL,997LL,1000000007LL}) {
        cout << n << ": " << (is_prime_trial(n) ? "PRIME" : "COMPOSITE") << nl;
    }

    // Factorization
    cout << nl << "--- Factorization ---" << nl;
    for (i64 n : {12LL, 60LL, 360LL, 1000000007LL, 123456789LL}) {
        auto f = trial_factorize(n);
        cout << n << " = ";
        for (int i = 0; i < sz(f); i++) {
            if (i) cout << " × ";
            cout << f[i].first;
            if (f[i].second > 1) cout << "^" << f[i].second;
        }
        cout << nl;
    }

    return 0;
}

