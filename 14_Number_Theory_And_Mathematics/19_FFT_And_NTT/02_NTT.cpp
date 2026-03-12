/*
 * ============================================================================
 *  📘 02 — Number Theoretic Transform (NTT)
 * ============================================================================
 *
 *  NTT is FFT over Z_p (integers mod prime p).
 *  No floating-point errors! Exact modular results.
 *
 *  REQUIREMENTS:
 *    p must be prime, p-1 divisible by large power of 2.
 *    Standard: p = 998244353 = 119 × 2²³ + 1, primitive root g = 3.
 *
 *  ALGORITHM:
 *    Same as Cooley-Tukey FFT, but using:
 *      ω_n = g^((p-1)/n) mod p    (n-th root of unity in Z_p)
 *    instead of complex roots.
 *
 *  INVERSE NTT: use ω_n^(-1) = g^(-(p-1)/n) and multiply by n^(-1).
 *
 *  TIME: O(n log n)
 *  SPACE: O(n)
 *
 *  Reference: https://cp-algorithms.com/algebra/fft.html
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

constexpr i64 NTT_MOD = 998244353;
constexpr i64 NTT_G = 3;  // primitive root of 998244353

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
//  📌 NTT (iterative, in-place)
// ============================================================================

void ntt(vec<i64>& a, bool inverse) {
    int n = sz(a);
    assert((n & (n - 1)) == 0);  // n must be power of 2

    // Bit-reversal permutation
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    // Butterfly operations
    for (int len = 2; len <= n; len <<= 1) {
        i64 w = inverse ? binpow(NTT_G, NTT_MOD - 1 - (NTT_MOD - 1) / len, NTT_MOD)
                        : binpow(NTT_G, (NTT_MOD - 1) / len, NTT_MOD);

        for (int i = 0; i < n; i += len) {
            i64 wn = 1;
            for (int j = 0; j < len / 2; j++) {
                i64 u = a[i + j];
                i64 v = a[i + j + len/2] * wn % NTT_MOD;
                a[i + j] = (u + v) % NTT_MOD;
                a[i + j + len/2] = (u - v + NTT_MOD) % NTT_MOD;
                wn = wn * w % NTT_MOD;
            }
        }
    }

    if (inverse) {
        i64 n_inv = binpow(n, NTT_MOD - 2, NTT_MOD);
        for (auto& x : a) x = x * n_inv % NTT_MOD;
    }
}

// ============================================================================
//  📌 POLYNOMIAL MULTIPLICATION via NTT
// ============================================================================
//  C = A × B  where C[k] = Σ A[i]×B[k-i]
//
//  DRY RUN: A = [1, 2, 3], B = [4, 5]
//    A(x) = 1 + 2x + 3x²
//    B(x) = 4 + 5x
//    C(x) = 4 + 13x + 22x² + 15x³
//    C = [4, 13, 22, 15]
// ============================================================================

vec<i64> multiply(vec<i64> a, vec<i64> b) {
    int result_size = sz(a) + sz(b) - 1;
    int n = 1;
    while (n < result_size) n <<= 1;

    a.resize(n); b.resize(n);

    ntt(a, false);
    ntt(b, false);

    vec<i64> c(n);
    for (int i = 0; i < n; i++) {
        c[i] = a[i] * b[i] % NTT_MOD;
    }

    ntt(c, true);
    c.resize(result_size);
    return c;
}

// ============================================================================
//  📌 BIG INTEGER MULTIPLICATION via NTT
// ============================================================================

string multiply_big(const string& num1, const string& num2) {
    int n1 = sz(num1), n2 = sz(num2);
    vec<i64> a(n1), b(n2);
    for (int i = 0; i < n1; i++) a[i] = num1[n1 - 1 - i] - '0';
    for (int i = 0; i < n2; i++) b[i] = num2[n2 - 1 - i] - '0';

    auto c = multiply(a, b);

    // Handle carries
    string result;
    i64 carry = 0;
    for (int i = 0; i < sz(c) || carry; i++) {
        i64 val = carry + (i < sz(c) ? c[i] : 0);
        result += ('0' + val % 10);
        carry = val / 10;
    }

    while (sz(result) > 1 && result.back() == '0') result.pop_back();
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Number Theoretic Transform (NTT) ===" << nl << nl;

    // Basic multiplication
    cout << "--- Polynomial Multiplication ---" << nl;
    {
        vec<i64> a = {1, 2, 3};  // 1 + 2x + 3x²
        vec<i64> b = {4, 5};     // 4 + 5x
        auto c = multiply(a, b);
        cout << "(1 + 2x + 3x²) × (4 + 5x) = ";
        for (int i = 0; i < sz(c); i++) {
            if (i > 0) cout << " + ";
            cout << c[i];
            if (i > 0) cout << "x";
            if (i > 1) cout << "^" << i;
        }
        cout << nl;
        // Expected: 4 + 13x + 22x² + 15x³
        assert(c == (vec<i64>{4, 13, 22, 15}));
        cout << "Verified ✓" << nl;
    }

    // Larger test
    cout << nl << "--- Larger Polynomial ---" << nl;
    {
        vec<i64> a = {1, 1, 1, 1};  // 1 + x + x² + x³
        vec<i64> b = {1, 1, 1, 1};
        auto c = multiply(a, b);
        cout << "(1+x+x²+x³)² = ";
        for (int i = 0; i < sz(c); i++) {
            if (i > 0) cout << " + ";
            cout << c[i] << "x^" << i;
        }
        cout << nl;
        // Expected: 1 + 2x + 3x² + 4x³ + 3x⁴ + 2x⁵ + x⁶
    }

    // Big integer multiplication
    cout << nl << "--- Big Integer Multiplication ---" << nl;
    cout << "123456789 × 987654321 = " << multiply_big("123456789", "987654321") << nl;
    cout << "Expected: 121932631112635269" << nl;

    // Performance note
    cout << nl << "--- NTT Performance ---" << nl;
    cout << "NTT mod = " << NTT_MOD << " (998244353)" << nl;
    cout << "Max length: 2^23 = " << (1 << 23) << " (~8.4M)" << nl;
    cout << "Primitive root: " << NTT_G << nl;

    return 0;
}

