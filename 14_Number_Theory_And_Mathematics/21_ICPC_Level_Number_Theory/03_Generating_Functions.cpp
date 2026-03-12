/*
 * ============================================================================
 *  📘 03 — Generating Functions (via NTT)
 * ============================================================================
 *
 *  A generating function encodes a sequence {a₀, a₁, a₂, ...} as:
 *    f(x) = a₀ + a₁x + a₂x² + ...
 *
 *  OPERATIONS (all in O(n log n)):
 *    - Multiplication: (f × g)[n] = Σ f[k]g[n-k]  → NTT
 *    - Inverse: f⁻¹ such that f × f⁻¹ = 1  → Newton's method
 *    - Exp/Log: via Newton's method
 *
 *  CLASSIC EXAMPLES:
 *    Fibonacci: f(x) = x / (1 - x - x²)
 *    Catalan:   C(x) = (1 - √(1-4x)) / (2x)
 *    Partition:  P(x) = Π 1/(1-x^k)
 *
 *  This file demonstrates generating function operations used in ICPC.
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

constexpr i64 MOD = 998244353;
constexpr i64 G = 3;

i64 binpow(i64 b, i64 e, i64 m) {
    i64 r = 1; b %= m;
    while (e > 0) { if (e & 1) r = r * b % m; b = b * b % m; e >>= 1; }
    return r;
}

// NTT
void ntt(vec<i64>& a, bool inv) {
    int n = sz(a);
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        i64 w = inv ? binpow(G, MOD - 1 - (MOD - 1) / len, MOD) : binpow(G, (MOD - 1) / len, MOD);
        for (int i = 0; i < n; i += len) {
            i64 wn = 1;
            for (int j = 0; j < len / 2; j++) {
                i64 u = a[i+j], v = a[i+j+len/2] * wn % MOD;
                a[i+j] = (u+v) % MOD;
                a[i+j+len/2] = (u-v+MOD) % MOD;
                wn = wn * w % MOD;
            }
        }
    }
    if (inv) { i64 ni = binpow(n, MOD-2, MOD); for (auto& x : a) x = x * ni % MOD; }
}

vec<i64> poly_mul(vec<i64> a, vec<i64> b) {
    int rs = sz(a) + sz(b) - 1, n = 1;
    while (n < rs) n <<= 1;
    a.resize(n); b.resize(n);
    ntt(a, false); ntt(b, false);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % MOD;
    ntt(a, true); a.resize(rs);
    return a;
}

// ============================================================================
//  📌 POLYNOMIAL INVERSE — Newton's method O(n log n)
// ============================================================================
//  Given f, find g such that f × g ≡ 1 (mod x^n)
//
//  Newton iteration: g_{k+1} = g_k × (2 - f × g_k)
//  Start with g_0 = f[0]^(-1)
// ============================================================================

vec<i64> poly_inv(vec<i64> f, int n) {
    vec<i64> g = {binpow(f[0], MOD - 2, MOD)};

    for (int len = 2; len < 2 * n; len <<= 1) {
        // g = g * (2 - f * g) mod x^len
        vec<i64> tmp(f.begin(), f.begin() + min(sz(f), len));
        tmp = poly_mul(tmp, g);
        for (auto& x : tmp) x = (MOD - x) % MOD;
        tmp[0] = (tmp[0] + 2) % MOD;
        g = poly_mul(g, tmp);
        g.resize(len);
    }
    g.resize(n);
    return g;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Generating Functions ===" << nl << nl;

    // Example 1: Fibonacci via GF
    // F(x) = x / (1 - x - x²) = x × (1 - x - x²)⁻¹
    cout << "--- Fibonacci via GF ---" << nl;
    {
        int N = 20;
        vec<i64> denom = {1, MOD - 1, MOD - 1};  // 1 - x - x²
        auto inv = poly_inv(denom, N);
        // F(x) = x × inv(1-x-x²), so f[n] = inv[n-1]
        cout << "F(n): ";
        for (int n = 0; n < N; n++) {
            i64 fib = (n == 0) ? 0 : inv[n - 1];
            cout << fib << " ";
        }
        cout << nl;
        // Expected: 0 1 1 2 3 5 8 13 21 34 55 89 144 ...
    }

    // Example 2: Partition function via GF
    // P(x) = Π_{k=1}^{N} 1/(1-x^k)
    cout << nl << "--- Partition Numbers ---" << nl;
    {
        int N = 30;
        vec<i64> f(N + 1, 0);
        f[0] = 1;
        for (int k = 1; k <= N; k++) {
            for (int j = k; j <= N; j++) {
                f[j] = (f[j] + f[j - k]) % MOD;
            }
        }
        cout << "p(n): ";
        for (int n = 0; n <= 20; n++) cout << f[n] << " ";
        cout << nl;
        // Expected: 1 1 2 3 5 7 11 15 22 30 42 56 77 101 135 176 ...
    }

    // Example 3: Verify polynomial inverse
    cout << nl << "--- Verify Poly Inverse ---" << nl;
    {
        vec<i64> f = {1, 2, 3, 4, 5};  // 1 + 2x + 3x² + 4x³ + 5x⁴
        int N = 10;
        auto g = poly_inv(f, N);
        auto product = poly_mul(f, g);

        cout << "f × f⁻¹ mod x^" << N << " = ";
        for (int i = 0; i < N; i++) {
            i64 val = (i < sz(product)) ? product[i] : 0;
            cout << val << " ";
        }
        cout << nl;
        cout << "(Should be 1 0 0 0 0 ...)" << nl;
        assert(product[0] == 1);
        for (int i = 1; i < N; i++) assert(product[i] == 0);
        cout << "Verified ✓" << nl;
    }

    return 0;
}

