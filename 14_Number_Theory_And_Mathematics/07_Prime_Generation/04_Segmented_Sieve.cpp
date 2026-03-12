/*
 * ============================================================================
 *  📘 04 — Segmented Sieve
 * ============================================================================
 *
 *  PROBLEM: Find all primes in range [L, R] where R can be up to 10^12
 *           but R - L ≤ 10^6.
 *
 *  ALGORITHM:
 *    1. Sieve all primes up to √R using standard sieve.
 *    2. Create boolean array for [L, R].
 *    3. For each prime p ≤ √R:
 *       - Find first multiple of p ≥ L: start = max(p*p, ceil(L/p)*p)
 *       - Mark all multiples of p in [L, R].
 *
 *  TIME:  O(√R + (R-L) log log R)
 *  SPACE: O(√R + (R-L))
 *
 *  DRY RUN: Primes in [10, 30]
 *    √30 ≈ 5, primes ≤ 5: {2, 3, 5}
 *
 *    Array: [10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30]
 *
 *    p=2: start=10, cross 10,12,14,16,18,20,22,24,26,28,30
 *    p=3: start=12, cross 12,15,18,21,24,27,30
 *    p=5: start=25, cross 25
 *
 *    Remaining: {11, 13, 17, 19, 23, 29} ✓
 *
 *  Reference: https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html
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
#define pb push_back

// ============================================================================
//  📌 SEGMENTED SIEVE
// ============================================================================

vec<i64> segmented_sieve(i64 L, i64 R) {
    // Step 1: Get small primes up to √R
    i64 limit = (i64)sqrt((double)R) + 1;
    vec<bool> small_prime(limit + 1, true);
    small_prime[0] = small_prime[1] = false;
    for (i64 p = 2; p * p <= limit; p++) {
        if (small_prime[p]) {
            for (i64 j = p * p; j <= limit; j += p)
                small_prime[j] = false;
        }
    }

    vec<i64> small_primes;
    for (i64 i = 2; i <= limit; i++) {
        if (small_prime[i]) small_primes.pb(i);
    }

    // Step 2: Sieve the range [L, R]
    i64 len = R - L + 1;
    vec<bool> is_prime(len, true);

    // Handle L = 0 or L = 1
    if (L == 0) is_prime[0] = false;
    if (L <= 1 && 1 <= R) is_prime[1 - L] = false;

    for (i64 p : small_primes) {
        // First multiple of p that is >= L and >= p*p
        i64 start = max(p * p, ((L + p - 1) / p) * p);
        for (i64 j = start; j <= R; j += p) {
            is_prime[j - L] = false;
        }
    }

    vec<i64> primes;
    for (i64 i = 0; i < len; i++) {
        if (is_prime[i] && L + i >= 2) {
            primes.pb(L + i);
        }
    }
    return primes;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Segmented Sieve ===" << nl << nl;

    // Example 1: Small range
    cout << "--- Primes in [10, 50] ---" << nl;
    auto p1 = segmented_sieve(10, 50);
    for (i64 p : p1) cout << p << " ";
    cout << nl << nl;

    // Example 2: Larger range
    cout << "--- Primes in [1000000, 1001000] ---" << nl;
    auto p2 = segmented_sieve(1000000, 1001000);
    cout << "Count: " << sz(p2) << nl;
    cout << "First 10: ";
    for (int i = 0; i < min(10, sz(p2)); i++) cout << p2[i] << " ";
    cout << nl << nl;

    // Example 3: Range around 10^9
    cout << "--- Primes near 10^9 ---" << nl;
    i64 base = 1000000000LL;
    auto p3 = segmented_sieve(base, base + 100);
    cout << "Primes in [10^9, 10^9+100]: ";
    for (i64 p : p3) cout << p << " ";
    cout << nl << "Count: " << sz(p3) << nl << nl;

    // Example 4: Range around 10^12
    cout << "--- Primes near 10^12 ---" << nl;
    i64 base2 = 1000000000000LL;
    auto p4 = segmented_sieve(base2, base2 + 1000);
    cout << "Primes in [10^12, 10^12+1000]: count = " << sz(p4) << nl;
    if (!p4.empty()) {
        cout << "First: " << p4[0] << ", Last: " << p4.back() << nl;
    }

    // Verification
    cout << nl << "--- Verification against standard sieve ---" << nl;
    auto p_seg = segmented_sieve(2, 100000);

    // Standard sieve for comparison
    vec<bool> is_p(100001, true);
    is_p[0] = is_p[1] = false;
    for (int i = 2; i * i <= 100000; i++)
        if (is_p[i]) for (int j = i*i; j <= 100000; j += i) is_p[j] = false;
    vec<i64> p_std;
    for (int i = 2; i <= 100000; i++) if (is_p[i]) p_std.pb(i);

    assert(p_seg == p_std);
    cout << "Segmented sieve matches standard sieve! (" << sz(p_seg) << " primes)" << nl;

    return 0;
}

