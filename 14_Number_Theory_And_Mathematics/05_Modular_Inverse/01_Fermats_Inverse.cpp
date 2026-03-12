/*
 * ============================================================================
 *  📘 01 — Modular Inverse via Fermat's Little Theorem
 * ============================================================================
 *
 *  THEOREM: If p is prime and gcd(a, p) = 1:
 *    a^(-1) ≡ a^(p-2) (mod p)
 *
 *  PROOF:
 *    By Fermat: a^(p-1) ≡ 1 (mod p)
 *    → a × a^(p-2) ≡ 1 (mod p)
 *    → a^(-1) = a^(p-2) mod p
 *
 *  TIME: O(log p) — via binary exponentiation
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
#include <map>
#include <set>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
constexpr i64 MOD = 1'000'000'007LL;
#define nl '\n'

i64 binpow(i64 base, i64 exp, i64 mod) {
    i64 res = 1; base %= mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

// a^(-1) mod p = a^(p-2) mod p
i64 mod_inv_fermat(i64 a, i64 p) {
    return binpow(a % p, p - 2, p);
}

// nCr mod p using factorial + inverse
struct Combo {
    vec<i64> fact, inv_fact;
    i64 mod;

    Combo(int n, i64 m) : fact(n + 1), inv_fact(n + 1), mod(m) {
        fact[0] = 1;
        for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i % mod;
        inv_fact[n] = binpow(fact[n], mod - 2, mod);
        for (int i = n - 1; i >= 0; i--) inv_fact[i] = inv_fact[i+1] * (i+1) % mod;
    }

    i64 C(int n, int r) {
        if (r < 0 || r > n) return 0;
        return fact[n] % mod * inv_fact[r] % mod * inv_fact[n-r] % mod;
    }

    i64 P(int n, int r) {
        if (r < 0 || r > n) return 0;
        return fact[n] % mod * inv_fact[n-r] % mod;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Modular Inverse (Fermat) ===" << nl << nl;

    // Basic inverse tests
    cout << "--- Inverses mod 10^9+7 ---" << nl;
    for (i64 a : {2, 3, 5, 7, 11, 13, 100, 1000000006LL}) {
        i64 inv = mod_inv_fermat(a, MOD);
        cout << a << "^(-1) = " << inv << "  [check: " << a % MOD * inv % MOD << "]" << nl;
    }

    // Inverses mod 7
    cout << nl << "--- All Inverses mod 7 ---" << nl;
    for (int a = 1; a <= 6; a++) {
        i64 inv = mod_inv_fermat(a, 7);
        cout << a << "^(-1) mod 7 = " << inv << "  [" << a << "×" << inv << "=" << a*inv << "≡" << a*inv%7 << "]" << nl;
    }

    // nCr examples
    cout << nl << "--- nCr mod 10^9+7 ---" << nl;
    Combo combo(1000000, MOD);
    cout << "C(10, 3) = " << combo.C(10, 3) << nl;
    cout << "C(20, 10) = " << combo.C(20, 10) << nl;
    cout << "C(100, 50) = " << combo.C(100, 50) << nl;
    cout << "C(1000000, 500000) = " << combo.C(1000000, 500000) << nl;

    return 0;
}

