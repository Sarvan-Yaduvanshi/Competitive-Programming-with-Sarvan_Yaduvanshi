/*
 * ============================================================================
 *  📘 03 — Garner's Algorithm (CRT with arbitrary output modulus)
 * ============================================================================
 *
 *  PROBLEM: Given x ≡ rᵢ (mod mᵢ) for pairwise coprime mᵢ,
 *  compute x mod M for some OTHER modulus M (e.g., 10^9+7).
 *
 *  STANDARD CRT computes x mod (m₁×m₂×...×mₖ) which may be huge.
 *  Garner computes in a mixed-radix representation to avoid big numbers.
 *
 *  MIXED RADIX: x = a₁ + m₁(a₂ + m₂(a₃ + ...))
 *  Coefficients aᵢ computed iteratively using modular inverse.
 *
 *  TIME: O(k²) where k = number of congruences
 *
 *  Reference: https://cp-algorithms.com/algebra/chinese-remainder-theorem.html
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

i64 binpow(i64 base, i64 exp, i64 mod) {
    i64 res = 1; base %= mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

// ============================================================================
//  📌 GARNER'S ALGORITHM
// ============================================================================
//  Input: r[i], m[i] (pairwise coprime moduli)
//  Output: x mod output_mod
// ============================================================================

i64 garner(vec<i64> r, vec<i64> m, i64 output_mod) {
    int k = sz(r);

    // Compute mixed radix coefficients
    vec<i64> coeffs(k);  // mixed radix representation
    vec<i64> prefix_mod(k, 1);  // m₁ × m₂ × ... × mᵢ₋₁ mod mᵢ

    for (int i = 0; i < k; i++) {
        // Find coeffs[i] = (r[i] - (a₁ + m₁(a₂ + m₂(...)))) / (m₁m₂...m_{i-1}) mod m[i]
        i64 val = r[i];
        i64 mult = 1;
        for (int j = 0; j < i; j++) {
            val = (val - coeffs[j] * mult % m[i] + m[i]) % m[i];
            mult = mult * m[j] % m[i];
        }
        coeffs[i] = val % m[i] * binpow(mult, m[i] - 2, m[i]) % m[i];
    }

    // Reconstruct answer mod output_mod
    // x = a₁ + m₁(a₂ + m₂(a₃ + ...))
    i64 result = 0, mult = 1;
    for (int i = 0; i < k; i++) {
        result = (result + coeffs[i] % output_mod * mult) % output_mod;
        mult = mult * (m[i] % output_mod) % output_mod;
    }
    return (result + output_mod) % output_mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Garner's Algorithm ===" << nl << nl;

    // Example: x ≡ 2 (mod 3), x ≡ 3 (mod 5), x ≡ 2 (mod 7)
    // Answer: x = 23 (mod 105)
    {
        vec<i64> r = {2, 3, 2}, m = {3, 5, 7};
        i64 x = garner(r, m, 1000000007LL);
        cout << "x ≡ 2 (mod 3), x ≡ 3 (mod 5), x ≡ 2 (mod 7)" << nl;
        cout << "x mod 10^9+7 = " << x << nl;
        cout << "Check: " << x%3 << ", " << x%5 << ", " << x%7 << nl << nl;
    }

    // Example with large output mod
    {
        vec<i64> r = {1, 2, 3}, m = {1000000007, 998244353, 999999937};
        i64 x = garner(r, m, 1000000007LL);
        cout << "Large CRT: x mod 10^9+7 = " << x << nl;
    }

    return 0;
}

