/*
 * ============================================================================
 *  📘 03 — Large Modular Arithmetic (__int128, overflow-safe)
 * ============================================================================
 *
 *  PROBLEM: When mod m > 10^9, (a%m)*(b%m) can overflow i64.
 *    e.g., m = 10^18, a = m-1: (m-1)² ≈ 10^36 > 2^63 ≈ 9.2×10^18
 *
 *  SOLUTIONS:
 *    1. __int128 (GCC extension): most common in CP
 *    2. Binary multiplication (Russian peasant): portable
 *    3. __float128 or long double trick
 *
 *  Reference: https://cp-algorithms.com/algebra/module-inverse.html
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
using u64 = unsigned long long;
using u128 = __uint128_t;
template<class T> using vec = vector<T>;
#define nl '\n'

// ============================================================================
//  📌 METHOD 1: __int128 (best for competitive programming)
// ============================================================================

i64 mulmod_128(i64 a, i64 b, i64 m) {
    return (u128)a * b % m;
}

i64 powmod_128(i64 base, i64 exp, i64 mod) {
    i64 res = 1; base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) res = mulmod_128(res, base, mod);
        base = mulmod_128(base, base, mod);
        exp >>= 1;
    }
    return res;
}

// ============================================================================
//  📌 METHOD 2: Binary Multiplication (portable, no __int128)
// ============================================================================
//  Same idea as binary exponentiation but for multiplication.
//  a*b = a*(b₀ + 2b₁ + 4b₂ + ...) = a*b₀ + 2a*b₁ + ...
//  Keep doubling a, add to result when bit is set.
// ============================================================================

i64 mulmod_binary(i64 a, i64 b, i64 m) {
    a %= m; b %= m;
    if (a < 0) a += m;
    if (b < 0) b += m;
    i64 result = 0;
    while (b > 0) {
        if (b & 1) result = (result + a) % m;
        a = (a + a) % m;
        b >>= 1;
    }
    return result;
}

// ============================================================================
//  📌 METHOD 3: Long double trick
// ============================================================================
//  a*b mod m = a*b - floor(a*b/m)*m
//  Use long double for the division (only ~18-19 digits precision).
//  Works for m up to ~10^15 reliably.
// ============================================================================

i64 mulmod_ld(i64 a, i64 b, i64 m) {
    i64 q = (i64)((long double)a * b / m);
    i64 r = a * b - q * m;
    // Might be off by ±m
    r %= m;
    if (r < 0) r += m;
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Large Modular Arithmetic ===" << nl << nl;

    i64 m = 999999999999999989LL; // large prime near 10^18
    i64 a = m - 1, b = m - 2;

    cout << "m = " << m << nl;
    cout << "a = " << a << ", b = " << b << nl << nl;

    // Compare methods
    i64 r1 = mulmod_128(a, b, m);
    i64 r2 = mulmod_binary(a, b, m);
    cout << "__int128:    a*b mod m = " << r1 << nl;
    cout << "Binary mul:  a*b mod m = " << r2 << nl;
    assert(r1 == r2);
    cout << "Match ✓" << nl;

    // Large power
    cout << nl << "--- Large Modular Power ---" << nl;
    cout << "2^(10^18) mod m = " << powmod_128(2, (i64)1e18, m) << nl;
    cout << "3^(10^18) mod m = " << powmod_128(3, (i64)1e18, m) << nl;

    // Fermat test with large mod
    cout << nl << "--- Fermat Test with large prime ---" << nl;
    cout << "2^(m-1) mod m = " << powmod_128(2, m - 1, m) << " (should be 1)" << nl;
    cout << "3^(m-1) mod m = " << powmod_128(3, m - 1, m) << " (should be 1)" << nl;

    return 0;
}

