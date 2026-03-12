/*
 * ============================================================================
 *  📘 01 — Primitive Root Finding
 * ============================================================================
 *
 *  DEFINITION: g is a primitive root mod n if ord_n(g) = φ(n)
 *
 *  EXISTENCE: Primitive roots exist for n = 1, 2, 4, p^k, 2p^k
 *             (p odd prime, k ≥ 1)
 *
 *  ALGORITHM:
 *    1. Compute φ(n)
 *    2. Factor φ(n) into prime factors q₁, q₂, ...
 *    3. For g = 2, 3, ...:
 *       If g^(φ(n)/qᵢ) ≢ 1 (mod n) for ALL qᵢ → g is primitive root
 *
 *  SMALLEST PRIMITIVE ROOT is typically small (O(n^0.25) heuristic).
 *
 *  Reference: https://cp-algorithms.com/algebra/primitive-root.html
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
#include <cassert>

using namespace std;
using i64 = long long;
using u128 = __uint128_t;
template<class T> using vec = vector<T>;
using pll = pair<i64, i64>;
#define nl '\n'
#define sz(x) ((int)(x).size())
#define pb push_back

i64 mulmod(i64 a, i64 b, i64 m) { return (u128)a * b % m; }

i64 powmod(i64 base, i64 exp, i64 mod) {
    i64 res = 1; base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) res = mulmod(res, base, mod);
        base = mulmod(base, base, mod);
        exp >>= 1;
    }
    return res;
}

i64 euler_phi(i64 n) {
    i64 result = n;
    for (i64 p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

vec<i64> prime_factors(i64 n) {
    vec<i64> factors;
    for (i64 p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            factors.pb(p);
            while (n % p == 0) n /= p;
        }
    }
    if (n > 1) factors.pb(n);
    return factors;
}

// ============================================================================
//  📌 FIND PRIMITIVE ROOT mod n
// ============================================================================

i64 primitive_root(i64 n) {
    if (n <= 1) return -1;
    if (n == 2) return 1;
    if (n == 4) return 3;

    i64 phi_n = euler_phi(n);
    vec<i64> factors = prime_factors(phi_n);

    for (i64 g = 2; g < n; g++) {
        if (__gcd(g, n) != 1) continue;

        bool is_root = true;
        for (i64 q : factors) {
            if (powmod(g, phi_n / q, n) == 1) {
                is_root = false;
                break;
            }
        }
        if (is_root) return g;
    }
    return -1;  // no primitive root (shouldn't happen if n has one)
}

// ============================================================================
//  📌 FIND ALL PRIMITIVE ROOTS mod n
// ============================================================================
//  If g is a primitive root, then g^k is also primitive root iff gcd(k, φ(n)) = 1.
//  Total count of primitive roots = φ(φ(n)).
// ============================================================================

vec<i64> all_primitive_roots(i64 n) {
    i64 g = primitive_root(n);
    if (g == -1) return {};

    i64 phi_n = euler_phi(n);
    vec<i64> roots;

    i64 cur = 1;
    for (i64 k = 1; k <= phi_n; k++) {
        cur = mulmod(cur, g, n);
        if (__gcd(k, phi_n) == 1) {
            roots.pb(cur);
        }
    }
    sort(roots.begin(), roots.end());
    return roots;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Primitive Roots ===" << nl << nl;

    // Find smallest primitive root for small primes
    cout << "--- Smallest Primitive Root for Primes ---" << nl;
    for (i64 p : {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97}) {
        i64 g = primitive_root(p);
        cout << "g(" << p << ") = " << g << "  ";
    }
    cout << nl << nl;

    // Verify: powers of primitive root
    cout << "--- Powers of g=3 mod 7 ---" << nl;
    {
        i64 p = 7, g = 3;
        cout << "Powers: ";
        i64 cur = 1;
        for (int k = 1; k <= p - 1; k++) {
            cur = cur * g % p;
            cout << cur << " ";
        }
        cout << nl;
        cout << "These should be a permutation of {1,2,3,4,5,6}" << nl;
    }

    // All primitive roots mod 13
    cout << nl << "--- All Primitive Roots mod 13 ---" << nl;
    auto roots = all_primitive_roots(13);
    cout << "Count = " << sz(roots) << " (φ(φ(13)) = φ(12) = 4)" << nl;
    for (i64 r : roots) cout << r << " ";
    cout << nl;

    // Large prime
    cout << nl << "--- Primitive Root mod 10^9+7 ---" << nl;
    i64 g = primitive_root(1000000007LL);
    cout << "g(10^9+7) = " << g << nl;

    return 0;
}

