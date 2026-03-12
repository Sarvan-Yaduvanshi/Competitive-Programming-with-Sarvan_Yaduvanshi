/*
 * ============================================================================
 *  📘 02 — Coprime Count via Inclusion-Exclusion
 * ============================================================================
 *
 *  Count integers in [1, N] coprime to m (i.e., gcd(x, m) = 1).
 *
 *  ALGORITHM:
 *    1. Factorize m into distinct primes: p₁, p₂, ..., pₖ
 *    2. IE: Count = Σ_{S ⊆ primes} (-1)^|S| × ⌊N / product(S)⌋
 *    3. Iterate over 2^k subsets via bitmask
 *
 *  DRY RUN: N=30, m=30=2×3×5, count numbers coprime to 30
 *    Total = 30
 *    ÷2: 15, ÷3: 10, ÷5: 6
 *    ÷6: 5, ÷10: 3, ÷15: 2
 *    ÷30: 1
 *    IE = 30 - (15+10+6) + (5+3+2) - 1 = 30 - 31 + 10 - 1 = 8
 *    φ(30) = 30(1-1/2)(1-1/3)(1-1/5) = 8 ✓
 *
 *  CSES: Prime Multiples (https://cses.fi/problemset/task/2185)
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
//  📌 COUNT COPRIME TO m IN [1..N] via IE
// ============================================================================

i64 coprime_count(i64 N, i64 m) {
    // Get distinct prime factors of m
    vec<i64> primes;
    i64 temp = m;
    for (i64 p = 2; p * p <= temp; p++) {
        if (temp % p == 0) {
            primes.pb(p);
            while (temp % p == 0) temp /= p;
        }
    }
    if (temp > 1) primes.pb(temp);

    int k = sz(primes);
    i64 result = 0;

    // Iterate over all 2^k subsets
    for (int mask = 0; mask < (1 << k); mask++) {
        i64 product = 1;
        int bits = __builtin_popcount(mask);
        for (int i = 0; i < k; i++) {
            if (mask & (1 << i)) {
                product *= primes[i];
                if (product > N) break;  // overflow protection
            }
        }
        if (product > N && bits > 0) continue;
        i64 count = N / product;
        if (bits % 2 == 0) result += count;
        else result -= count;
    }

    return result;
}

// ============================================================================
//  📌 CSES: Prime Multiples — count [1..N] divisible by at least one of given primes
//  Answer = N - coprime_count, but here primes are directly given.
// ============================================================================

i64 prime_multiples(i64 N, vec<i64>& primes) {
    int k = sz(primes);
    i64 result = 0;

    for (int mask = 1; mask < (1 << k); mask++) {
        i64 product = 1;
        int bits = __builtin_popcount(mask);
        bool overflow = false;
        for (int i = 0; i < k; i++) {
            if (mask & (1 << i)) {
                if (product > N / primes[i]) { overflow = true; break; }
                product *= primes[i];
            }
        }
        if (overflow) continue;

        i64 count = N / product;
        if (bits % 2 == 1) result += count;
        else result -= count;
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Coprime Count via IE ===" << nl << nl;

    // Basic test
    cout << "--- Coprime to 30 in [1..30] ---" << nl;
    i64 cnt = coprime_count(30, 30);
    cout << "Count = " << cnt << " (expected 8 = φ(30))" << nl;

    // Verify with brute force
    int brute = 0;
    for (int i = 1; i <= 30; i++) if (gcd(i, 30) == 1) brute++;
    assert(cnt == brute);
    cout << "Verified ✓" << nl;

    // Prime Multiples style
    cout << nl << "--- Numbers ≤ 20 divisible by 2 or 3 or 5 ---" << nl;
    vec<i64> primes = {2, 3, 5};
    i64 pm = prime_multiples(20, primes);
    cout << "Count = " << pm << nl;
    brute = 0;
    for (int i = 1; i <= 20; i++) if (i%2==0 || i%3==0 || i%5==0) brute++;
    cout << "Brute = " << brute << (pm == brute ? " ✓" : " ✗") << nl;

    return 0;
}

