/*
 * ============================================================================
 *  📘 02 — Lagrange Interpolation
 * ============================================================================
 *
 *  PROBLEM: Given n+1 points (x₀,y₀),...,(xₙ,yₙ), find polynomial P of
 *           degree ≤ n passing through all points. Evaluate at any x.
 *
 *  FORMULA:
 *    P(x) = Σᵢ yᵢ × Πⱼ≠ᵢ (x - xⱼ) / (xᵢ - xⱼ)
 *
 *  GENERAL: O(n²) per evaluation
 *  CONSECUTIVE x = 0,1,...,n: O(n) per evaluation using prefix/suffix
 *
 *  PROOF OF UNIQUENESS:
 *    If P, Q both have degree ≤ n and agree on n+1 points,
 *    then P-Q has degree ≤ n but n+1 roots → P-Q = 0 → P = Q. ∎
 *
 *  Reference: https://cp-algorithms.com/algebra/polynomial.html
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

constexpr i64 MOD = 1'000'000'007LL;

i64 binpow(i64 base, i64 exp, i64 mod) {
    i64 res = 1; base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

i64 modinv(i64 a, i64 mod) { return binpow(a % mod, mod - 2, mod); }

// ============================================================================
//  📌 GENERAL LAGRANGE INTERPOLATION — O(n²)
// ============================================================================
//  Evaluate polynomial defined by points at a given x.
//  Works for arbitrary (distinct) x-coordinates.
// ============================================================================

i64 lagrange_general(const vec<i64>& xs, const vec<i64>& ys, i64 x, i64 mod) {
    int n = sz(xs);
    i64 result = 0;

    for (int i = 0; i < n; i++) {
        if ((x - xs[i]) % mod == 0) return ys[i];  // x equals a known point

        i64 num = ys[i], den = 1;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            num = num % mod * ((x - xs[j]) % mod + mod) % mod;
            den = den % mod * ((xs[i] - xs[j]) % mod + mod) % mod;
        }
        result = (result + num % mod * modinv(den, mod)) % mod;
    }
    return (result % mod + mod) % mod;
}

// ============================================================================
//  📌 CONSECUTIVE LAGRANGE INTERPOLATION — O(n)
// ============================================================================
//  Points at x = 0, 1, 2, ..., n with values y[0..n].
//  Evaluate at arbitrary x.
//
//  P(x) = Σᵢ yᵢ × Πⱼ≠ᵢ (x-j)/(i-j)
//
//  Numerator product Πⱼ≠ᵢ (x-j) = prefix[i] × suffix[i]
//  Denominator Πⱼ≠ᵢ (i-j) = (-1)^(n-i) × i! × (n-i)!
//
//  So: term_i = y[i] × prefix[i] × suffix[i] × inv((-1)^(n-i) × i! × (n-i)!)
// ============================================================================

i64 lagrange_consecutive(const vec<i64>& y, i64 x, i64 mod) {
    int n = sz(y) - 1;  // degree

    // Check if x is one of the points
    if (x >= 0 && x <= n) return y[(int)x] % mod;

    // Precompute factorials and inverse factorials
    vec<i64> fact(n + 1), inv_fact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i % mod;
    inv_fact[n] = modinv(fact[n], mod);
    for (int i = n - 1; i >= 0; i--) inv_fact[i] = inv_fact[i+1] * (i+1) % mod;

    // prefix[i] = (x-0)(x-1)...(x-(i-1))
    // suffix[i] = (x-(i+1))(x-(i+2))...(x-n)
    vec<i64> prefix(n + 2, 1), suffix(n + 2, 1);
    for (int i = 0; i <= n; i++) {
        prefix[i + 1] = prefix[i] % mod * ((x - i) % mod + mod) % mod;
    }
    for (int i = n; i >= 0; i--) {
        suffix[i] = suffix[i + 1] % mod * ((x - i) % mod + mod) % mod;
    }

    i64 result = 0;
    for (int i = 0; i <= n; i++) {
        i64 num = prefix[i] % mod * suffix[i + 1] % mod;
        i64 den = inv_fact[i] % mod * inv_fact[n - i] % mod;
        if ((n - i) % 2 == 1) den = (mod - den) % mod;

        result = (result + y[i] % mod * num % mod * den) % mod;
    }
    return (result + mod) % mod;
}

// ============================================================================
//  📌 APPLICATION: Sum of k-th powers S(n) = 1^k + 2^k + ... + n^k
// ============================================================================
//  S(n) is a polynomial of degree k+1 in n.
//  Compute S(0), S(1), ..., S(k+1) directly, then interpolate.
//  Total: O(k log k) to compute values + O(k) per query.
// ============================================================================

i64 sum_of_kth_powers(i64 n, int k, i64 mod) {
    // Compute y[i] = S(i) = 0^k + 1^k + ... + i^k for i = 0..k+1
    vec<i64> y(k + 2);
    y[0] = 0;
    for (int i = 1; i <= k + 1; i++) {
        y[i] = (y[i-1] + binpow(i, k, mod)) % mod;
    }
    return lagrange_consecutive(y, n, mod);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Lagrange Interpolation ===" << nl << nl;

    // Example 1: Interpolate (0,1), (1,3), (2,7) → P(x) = x²+x+1
    cout << "--- General Interpolation ---" << nl;
    {
        vec<i64> xs = {0, 1, 2}, ys = {1, 3, 7};
        for (i64 x = 0; x <= 5; x++) {
            cout << "P(" << x << ") = " << lagrange_general(xs, ys, x, MOD)
                 << " (expected " << x*x + x + 1 << ")" << nl;
        }
    }

    // Example 2: Consecutive interpolation
    cout << nl << "--- Consecutive Interpolation ---" << nl;
    {
        // y[i] = i² + i + 1 for i = 0,1,2
        vec<i64> y = {1, 3, 7};
        for (i64 x = 0; x <= 10; x++) {
            cout << "P(" << x << ") = " << lagrange_consecutive(y, x, MOD)
                 << " (expected " << x*x + x + 1 << ")" << nl;
        }
    }

    // Example 3: Sum of k-th powers
    cout << nl << "--- Sum of k-th Powers ---" << nl;
    for (int k = 1; k <= 5; k++) {
        i64 n = 100;
        i64 result = sum_of_kth_powers(n, k, MOD);
        // Brute force verify
        i64 brute = 0;
        for (int i = 1; i <= n; i++) brute = (brute + binpow(i, k, MOD)) % MOD;
        cout << "1^" << k << " + 2^" << k << " + ... + " << n << "^" << k
             << " = " << result << (result == brute ? " ✓" : " ✗") << nl;
    }

    // Large query
    cout << nl << "--- Large Query ---" << nl;
    cout << "1^3 + 2^3 + ... + (10^18)^3 mod 10^9+7 = "
         << sum_of_kth_powers((i64)1e18, 3, MOD) << nl;

    return 0;
}

