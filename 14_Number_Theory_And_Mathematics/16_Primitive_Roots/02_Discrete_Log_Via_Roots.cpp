/*
 * ============================================================================
 *  📘 02 — Discrete Log via Primitive Root (Index Table)
 * ============================================================================
 *
 *  IDEA: If g is a primitive root mod p, then every a coprime to p can
 *        be written as a = g^k for some k (the discrete log / index).
 *
 *  BUILD: Compute g^0, g^1, ..., g^(p-2) mod p. Store index[value] = k.
 *
 *  USE: To solve a^x ≡ b (mod p):
 *    Let a = g^α, b = g^β (look up in index table).
 *    Then g^(αx) ≡ g^β → αx ≡ β (mod p-1)
 *    Solve linear congruence: x = β × α^(-1) mod (p-1)
 *    (if gcd(α, p-1) | β)
 *
 *  TIME: O(p) precompute, O(log p) per query.
 *  SPACE: O(p)
 *
 *  LIMITATION: Only works for prime p (where primitive root exists).
 *  For general m, use BSGS (see 15_Discrete_Logarithm).
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
#include <algorithm>
#include <map>
#include <cmath>
#include <numeric>
#include <cassert>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
#define nl '\n'
#define sz(x) ((int)(x).size())
#define pb push_back

i64 powmod(i64 b, i64 e, i64 m) {
    i64 r = 1; b %= m;
    while (e > 0) { if (e & 1) r = r * b % m; b = b * b % m; e >>= 1; }
    return r;
}

i64 euler_phi(i64 n) {
    i64 result = n;
    for (i64 p = 2; p * p <= n; p++) {
        if (n % p == 0) { while (n % p == 0) n /= p; result -= result / p; }
    }
    if (n > 1) result -= result / n;
    return result;
}

// Find smallest primitive root mod p (p prime)
i64 find_primitive_root(i64 p) {
    i64 phi = p - 1;
    vec<i64> factors;
    i64 n = phi;
    for (i64 f = 2; f * f <= n; f++) {
        if (n % f == 0) { factors.pb(f); while (n % f == 0) n /= f; }
    }
    if (n > 1) factors.pb(n);

    for (i64 g = 2; g < p; g++) {
        bool ok = true;
        for (i64 f : factors) {
            if (powmod(g, phi / f, p) == 1) { ok = false; break; }
        }
        if (ok) return g;
    }
    return -1;
}

// ============================================================================
//  📌 INDEX TABLE (Discrete Log Table)
// ============================================================================

struct IndexTable {
    i64 p, g;
    vec<i64> idx;  // idx[a] = k such that g^k ≡ a (mod p)

    IndexTable(i64 p) : p(p), idx(p, -1) {
        g = find_primitive_root(p);
        i64 pw = 1;
        for (i64 k = 0; k < p - 1; k++) {
            idx[pw] = k;
            pw = pw * g % p;
        }
    }

    // Get discrete log: find k such that g^k ≡ a (mod p)
    i64 dlog(i64 a) {
        a %= p;
        if (a < 0) a += p;
        return idx[a];
    }

    // Solve a^x ≡ b (mod p)
    i64 solve_power(i64 a, i64 b) {
        a %= p; b %= p;
        if (a == 0) return (b == 0) ? 1 : -1;
        if (b == 0) return -1;  // a^x ≡ 0 impossible if p prime, a != 0

        i64 alpha = dlog(a), beta = dlog(b);
        // Solve alpha * x ≡ beta (mod p-1)
        i64 m = p - 1;
        i64 g_ab = gcd(alpha, m);
        if (beta % g_ab != 0) return -1;

        alpha /= g_ab; beta /= g_ab; m /= g_ab;
        // alpha * x ≡ beta (mod m), gcd(alpha, m) = 1
        return beta % m * powmod(alpha, euler_phi(m) - 1, m) % m;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Discrete Log via Primitive Root ===" << nl << nl;

    i64 p = 17;
    IndexTable table(p);
    cout << "p = " << p << ", primitive root g = " << table.g << nl << nl;

    // Print full index table
    cout << "--- Index Table mod " << p << " ---" << nl;
    for (i64 a = 1; a < p; a++) {
        cout << table.g << "^" << table.dlog(a) << " ≡ " << a << " (mod " << p << ")" << nl;
    }

    // Solve some discrete log problems
    cout << nl << "--- Solve a^x ≡ b (mod " << p << ") ---" << nl;
    vec<pair<i64,i64>> queries = {{3, 13}, {2, 8}, {5, 1}, {7, 3}};
    for (auto [a, b] : queries) {
        i64 x = table.solve_power(a, b);
        if (x >= 0) {
            cout << a << "^" << x << " ≡ " << b << " (mod " << p << ")";
            cout << " [check: " << powmod(a, x, p) << "]" << nl;
        } else {
            cout << a << "^x ≡ " << b << " (mod " << p << "): NO SOLUTION" << nl;
        }
    }

    return 0;
}

