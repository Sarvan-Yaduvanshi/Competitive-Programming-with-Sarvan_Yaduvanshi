/*
 * ============================================================================
 *  📘 01 — nCr Modular (Factorial + Inverse Precomputation)
 * ============================================================================
 *
 *  FORMULA: C(n,r) = n! / (r! × (n-r)!)
 *  Modular: C(n,r) mod p = n! × (r!)⁻¹ × ((n-r)!)⁻¹ mod p
 *
 *  PRECOMPUTATION:
 *    fact[i] = i! mod p                      → O(n)
 *    inv_fact[n] = fact[n]^(p-2) mod p       → O(log p)
 *    inv_fact[i] = inv_fact[i+1] × (i+1)     → O(n) backwards
 *
 *  QUERY: C(n,r) = fact[n] × inv_fact[r] × inv_fact[n-r] mod p → O(1)
 *
 *  Reference: https://cp-algorithms.com/combinatorics/binomial-coefficients.html
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
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

// ============================================================================
//  📌 COMBINATORICS STRUCT
// ============================================================================

struct Combo {
    vec<i64> fact, inv_fact;
    i64 mod;
    int n;

    Combo(int n, i64 mod) : n(n), mod(mod), fact(n + 1), inv_fact(n + 1) {
        fact[0] = 1;
        for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i % mod;
        inv_fact[n] = binpow(fact[n], mod - 2, mod);
        for (int i = n - 1; i >= 0; i--) inv_fact[i] = inv_fact[i+1] * (i+1) % mod;
    }

    // C(n, r) = n! / (r! × (n-r)!) mod p
    i64 C(int n, int r) const {
        if (r < 0 || r > n) return 0;
        return fact[n] % mod * inv_fact[r] % mod * inv_fact[n-r] % mod;
    }

    // P(n, r) = n! / (n-r)! mod p
    i64 P(int n, int r) const {
        if (r < 0 || r > n) return 0;
        return fact[n] % mod * inv_fact[n-r] % mod;
    }

    // Catalan: C_n = C(2n, n) / (n+1)
    i64 catalan(int n) const {
        return C(2*n, n) % mod * binpow(n + 1, mod - 2, mod) % mod;
    }

    // Stars and Bars: n identical items into k boxes
    i64 stars_bars(int n, int k) const {
        return C(n + k - 1, k - 1);
    }

    // Derangement: D(n) = n! × Σ (-1)^i / i!
    i64 derangement(int n) const {
        i64 res = 0;
        for (int i = 0; i <= n; i++) {
            if (i % 2 == 0) res = (res + inv_fact[i]) % mod;
            else res = (res - inv_fact[i] + mod) % mod;
        }
        return res % mod * fact[n] % mod;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Combo combo(2000000, MOD);

    cout << "=== nCr Modular ===" << nl << nl;

    // Pascal's Triangle (small)
    cout << "--- Pascal's Triangle (n=0..8) ---" << nl;
    for (int n = 0; n <= 8; n++) {
        for (int r = 0; r <= n; r++) {
            cout << combo.C(n, r) << " ";
        }
        cout << nl;
    }

    // Verify Pascal's identity
    cout << nl << "--- Verify: C(n,r) = C(n-1,r-1) + C(n-1,r) ---" << nl;
    for (int n = 2; n <= 10; n++) {
        for (int r = 1; r < n; r++) {
            assert(combo.C(n, r) == (combo.C(n-1, r-1) + combo.C(n-1, r)) % MOD);
        }
    }
    cout << "Pascal's identity verified for n ≤ 10 ✓" << nl;

    // Large values
    cout << nl << "--- Large nCr ---" << nl;
    cout << "C(100, 50) = " << combo.C(100, 50) << nl;
    cout << "C(1000, 500) = " << combo.C(1000, 500) << nl;
    cout << "C(10^6, 5×10^5) = " << combo.C(1000000, 500000) << nl;

    // Catalan numbers
    cout << nl << "--- Catalan Numbers ---" << nl;
    for (int n = 0; n <= 15; n++) {
        cout << "C_" << n << " = " << combo.catalan(n) << nl;
    }

    // Stars and bars
    cout << nl << "--- Stars & Bars ---" << nl;
    cout << "5 balls into 3 boxes: " << combo.stars_bars(5, 3) << nl;
    cout << "10 balls into 4 boxes: " << combo.stars_bars(10, 4) << nl;

    // Derangements
    cout << nl << "--- Derangements D(n) ---" << nl;
    for (int n = 0; n <= 10; n++) {
        cout << "D(" << n << ") = " << combo.derangement(n) << nl;
    }

    return 0;
}

