/*
 * ============================================================================
 *  📘 03 — Precompute All Modular Inverses in O(n)
 * ============================================================================
 *
 *  FORMULA: inv[i] = -(m / i) × inv[m % i] mod m
 *
 *  PROOF:
 *    Let m = q×i + r, where q = ⌊m/i⌋, r = m % i.
 *    Then q×i + r ≡ 0 (mod m)
 *    → i ≡ -r/q (mod m)
 *    → i^(-1) ≡ -q × r^(-1) ≡ -⌊m/i⌋ × inv[m%i] (mod m)
 *
 *  This also lets us precompute factorial inverses in O(n):
 *    inv_fact[n] = binpow(fact[n], p-2, p)
 *    inv_fact[i] = inv_fact[i+1] × (i+1) mod p   (for i < n)
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
#include <string>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <cassert>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
constexpr i64 MOD = 1'000'000'007LL;
#define nl '\n'
#define sz(x) ((int)(x).size())

// ============================================================================
//  📌 O(n) Precomputation of Inverses
// ============================================================================

vec<i64> precompute_inv(int n, i64 m) {
    vec<i64> inv(n + 1, 0);
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = (m - (m / i) * inv[m % i] % m) % m;
    }
    return inv;
}

// ============================================================================
//  📌 O(n) Precomputation of Factorial + Inverse Factorials
// ============================================================================

struct FastCombo {
    vec<i64> fact, inv_fact, inv;
    i64 mod;

    FastCombo(int n, i64 m) : fact(n+1), inv_fact(n+1), inv(n+1), mod(m) {
        fact[0] = fact[1] = 1;
        inv[1] = 1;
        inv_fact[0] = inv_fact[1] = 1;

        for (int i = 2; i <= n; i++) {
            fact[i] = fact[i-1] * i % mod;
            inv[i] = (mod - (mod / i) * inv[mod % i] % mod) % mod;
            inv_fact[i] = inv_fact[i-1] * inv[i] % mod;
        }
    }

    i64 C(int n, int r) {
        if (r < 0 || r > n) return 0;
        return fact[n] % mod * inv_fact[r] % mod * inv_fact[n-r] % mod;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Precompute Inverses O(n) ===" << nl << nl;

    // Small modulus demo
    cout << "--- All Inverses mod 13 ---" << nl;
    auto inv13 = precompute_inv(12, 13);
    for (int i = 1; i <= 12; i++) {
        cout << "inv[" << i << "] = " << inv13[i]
             << "  [check: " << i << "×" << inv13[i] << "=" << i*inv13[i]
             << "≡" << i*inv13[i]%13 << " mod 13]" << nl;
    }

    // Dry run mod 7
    cout << nl << "--- Dry Run: Inverses mod 7 ---" << nl;
    cout << "inv[1] = 1" << nl;
    cout << "inv[2] = -(7/2)*inv[7%2] = -3*inv[1] = -3 ≡ 4 mod 7" << nl;
    cout << "inv[3] = -(7/3)*inv[7%3] = -2*inv[1] = -2 ≡ 5 mod 7" << nl;
    cout << "inv[4] = -(7/4)*inv[7%4] = -1*inv[3] = -5 ≡ 2 mod 7" << nl;
    cout << "inv[5] = -(7/5)*inv[7%5] = -1*inv[2] = -4 ≡ 3 mod 7" << nl;
    cout << "inv[6] = -(7/6)*inv[7%6] = -1*inv[1] = -1 ≡ 6 mod 7" << nl;

    auto inv7 = precompute_inv(6, 7);
    cout << "Computed: ";
    for (int i = 1; i <= 6; i++) cout << inv7[i] << " ";
    cout << nl;

    // FastCombo test
    cout << nl << "--- FastCombo nCr ---" << nl;
    FastCombo fc(1000000, MOD);
    cout << "C(5,2) = " << fc.C(5,2) << nl;
    cout << "C(10,5) = " << fc.C(10,5) << nl;
    cout << "C(100,50) = " << fc.C(100,50) << nl;
    cout << "C(1000000, 1) = " << fc.C(1000000, 1) << nl;

    return 0;
}

