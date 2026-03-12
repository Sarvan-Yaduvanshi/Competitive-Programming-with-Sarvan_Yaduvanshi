/*
 * ============================================================================
 *  📘 01 — FFT (Fast Fourier Transform)
 * ============================================================================
 *
 *  Polynomial multiplication in O(n log n) using complex roots of unity.
 *
 *  ALGORITHM (Cooley-Tukey):
 *    1. Split A(x) into even/odd: A(x) = A_even(x²) + x·A_odd(x²)
 *    2. Evaluate both at n/2 points recursively
 *    3. Combine using butterfly operation
 *
 *  ROOTS OF UNITY: ω_n = e^(2πi/n)
 *    ω_n^n = 1, ω_n^k for k=0..n-1 are distinct
 *
 *  INVERSE FFT: Same algorithm with ω_n^(-1), divide by n at the end
 *
 *  ⚠️ FLOATING POINT: FFT uses doubles → possible precision issues.
 *    For exact results mod prime, use NTT instead (see 02_NTT.cpp).
 *
 *  TIME: O(n log n)   SPACE: O(n)
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
#include <complex>
#include <cmath>
#include <cassert>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
#define nl '\n'
#define sz(x) ((int)(x).size())

const double PI = acos(-1);
using cd = complex<double>;

// ============================================================================
//  📌 FFT (iterative, in-place)
// ============================================================================

void fft(vec<cd>& a, bool inverse) {
    int n = sz(a);
    assert((n & (n-1)) == 0);

    // Bit-reversal permutation
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    // Butterfly
    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2 * PI / len * (inverse ? -1 : 1);
        cd wlen(cos(angle), sin(angle));

        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len/2] * w;
                a[i + j] = u + v;
                a[i + j + len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (inverse) {
        for (auto& x : a) x /= n;
    }
}

// ============================================================================
//  📌 POLYNOMIAL MULTIPLICATION via FFT
// ============================================================================

vec<i64> multiply_fft(vec<i64>& a, vec<i64>& b) {
    vec<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int result_size = sz(a) + sz(b) - 1;
    int n = 1;
    while (n < result_size) n <<= 1;
    fa.resize(n); fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vec<i64> result(result_size);
    for (int i = 0; i < result_size; i++)
        result[i] = llround(fa[i].real());
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Fast Fourier Transform ===" << nl << nl;

    // Multiply (1 + 2x + 3x²) × (4 + 5x)
    vec<i64> a = {1, 2, 3}, b = {4, 5};
    auto c = multiply_fft(a, b);
    cout << "(1+2x+3x²) × (4+5x) = ";
    for (int i = 0; i < sz(c); i++) {
        if (i > 0) cout << " + ";
        cout << c[i];
        if (i > 0) cout << "x^" << i;
    }
    cout << nl;
    assert((c == vec<i64>{4, 13, 22, 15}));
    cout << "Expected: 4 + 13x + 22x² + 15x³ ✓" << nl;

    // Square: (1+x+x²+x³)²
    cout << nl;
    vec<i64> d = {1,1,1,1};
    auto e = multiply_fft(d, d);
    cout << "(1+x+x²+x³)² = ";
    for (int i = 0; i < sz(e); i++) {
        if (i > 0) cout << " + ";
        cout << e[i] << "x^" << i;
    }
    cout << nl;

    return 0;
}

