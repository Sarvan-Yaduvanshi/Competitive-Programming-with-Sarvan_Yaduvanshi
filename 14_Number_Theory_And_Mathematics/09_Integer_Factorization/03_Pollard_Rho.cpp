/*
 * ============================================================================
 *  📘 03 — Pollard's Rho Factorization Algorithm
 * ============================================================================
 *
 *  IDEA: Find a non-trivial factor of n using pseudo-random walk and
 *        Birthday Paradox. Expected O(n^{1/4}) per factor.
 *
 *  BIRTHDAY PARADOX CONNECTION:
 *    If p | n and we generate random x_i mod p, collision x_i ≡ x_j (mod p)
 *    happens after O(√p) values. Since p ≤ √n, we need O(n^{1/4}) steps.
 *
 *  ALGORITHM (Brent's variant with batch GCD):
 *    1. Pick random c, x = random
 *    2. f(x) = (x² + c) mod n
 *    3. Use Brent's cycle detection
 *    4. Accumulate product q = q * |x-y| mod n
 *    5. Periodically check gcd(q, n)
 *
 *  COMBINED WITH MILLER-RABIN for complete factorization of n ≤ 10^18.
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
#include <string>
#include <algorithm>
#include <map>
#include <cmath>
#include <numeric>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using u128 = __uint128_t;
template<class T> using vec = vector<T>;
using pll = pair<i64, i64>;
#define nl '\n'
#define sz(x) ((int)(x).size())
#define pb push_back

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// ============================================================================
//  📌 UTILITIES
// ============================================================================

i64 mulmod(i64 a, i64 b, i64 m) {
    return (u128)a * b % m;
}

i64 powmod(i64 base, i64 exp, i64 mod) {
    i64 result = 1; base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) result = mulmod(result, base, mod);
        base = mulmod(base, base, mod);
        exp >>= 1;
    }
    return result;
}

// ============================================================================
//  📌 MILLER-RABIN (Deterministic for n < 3.3 × 10^18)
// ============================================================================

bool is_prime(i64 n) {
    if (n < 2) return false;
    if (n < 4) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    i64 d = n - 1; int s = 0;
    while (d % 2 == 0) { d /= 2; s++; }

    for (i64 a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a) return true;
        if (n % a == 0) return false;
        i64 x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool found = false;
        for (int r = 0; r < s - 1; r++) {
            x = mulmod(x, x, n);
            if (x == n - 1) { found = true; break; }
        }
        if (!found) return false;
    }
    return true;
}

// ============================================================================
//  📌 POLLARD'S RHO (Brent's variant with batch GCD)
// ============================================================================

i64 pollard_rho(i64 n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;

    while (true) {
        i64 x = rng() % (n - 2) + 2;
        i64 y = x;
        i64 c = rng() % (n - 1) + 1;
        i64 d = 1;

        auto f = [&](i64 x) -> i64 {
            return (mulmod(x, x, n) + c) % n;
        };

        while (d == 1) {
            x = f(x);
            y = f(f(y));
            d = __gcd(abs(x - y), n);
        }

        if (d != n) return d;
        // else retry with different c
    }
}

// Brent's optimization with batch GCD
i64 pollard_brent(i64 n) {
    if (n % 2 == 0) return 2;

    while (true) {
        i64 x = rng() % (n - 2) + 2;
        i64 c = rng() % (n - 1) + 1;
        i64 y = x, d = 1;
        i64 q = 1;

        auto f = [&](i64 x) -> i64 {
            return (mulmod(x, x, n) + c) % n;
        };

        i64 ys = 0, r = 1;
        while (d == 1) {
            x = y;
            for (i64 i = 0; i < r; i++) y = f(y);

            for (i64 k = 0; k < r && d == 1; k += 128) {
                ys = y;
                i64 bound = min((i64)128, r - k);
                q = 1;
                for (i64 i = 0; i < bound; i++) {
                    y = f(y);
                    q = mulmod(q, abs(x - y), n);
                }
                d = __gcd(q, n);
            }
            r <<= 1;
        }

        if (d == n) {
            // Fallback: find exact point
            while (true) {
                ys = f(ys);
                d = __gcd(abs(x - ys), n);
                if (d > 1) break;
            }
        }

        if (d != n) return d;
    }
}

// ============================================================================
//  📌 COMPLETE FACTORIZATION
// ============================================================================

vec<i64> factorize(i64 n) {
    if (n <= 1) return {};
    if (is_prime(n)) return {n};

    i64 d = pollard_brent(n);
    auto left = factorize(d);
    auto right = factorize(n / d);
    left.insert(left.end(), right.begin(), right.end());
    return left;
}

// Returns sorted (prime, exponent) pairs
vec<pll> factorize_full(i64 n) {
    auto primes = factorize(n);
    sort(primes.begin(), primes.end());

    vec<pll> result;
    for (i64 p : primes) {
        if (!result.empty() && result.back().first == p)
            result.back().second++;
        else
            result.pb({p, 1});
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Pollard's Rho Factorization ===" << nl << nl;

    // Test cases
    vec<i64> tests = {
        12, 100, 360, 1000000007LL, 999999999999999989LL,
        1000000007LL * 998244353LL,  // product of two large primes
        2LL * 3 * 5 * 7 * 11 * 13 * 17 * 19 * 23,  // primorial
        (i64)1e18 + 9,
    };

    for (i64 n : tests) {
        auto factors = factorize_full(n);
        cout << n << " = ";
        for (int i = 0; i < sz(factors); i++) {
            if (i > 0) cout << " × ";
            cout << factors[i].first;
            if (factors[i].second > 1) cout << "^" << factors[i].second;
        }

        // Verify
        i64 product = 1;
        for (auto [p, e] : factors) {
            for (int j = 0; j < e; j++) product *= p;
        }
        cout << (product == n ? " ✓" : " ✗") << nl;
    }

    return 0;
}

