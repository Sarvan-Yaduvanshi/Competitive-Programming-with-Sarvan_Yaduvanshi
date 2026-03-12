/*
 * ============================================================================
 *  📘 01 — Polynomial Basics (Representation, Evaluation, Multiplication)
 * ============================================================================
 *
 *  REPRESENTATION: P(x) = a₀ + a₁x + a₂x² + ... + aₙxⁿ
 *    Stored as vector<i64> {a₀, a₁, a₂, ..., aₙ}
 *
 *  EVALUATION (Horner's Method): O(n)
 *    P(x) = a₀ + x(a₁ + x(a₂ + ... + x·aₙ))
 *    Avoids computing x^k separately.
 *
 *  NAIVE MULTIPLICATION: O(n²)
 *    C[k] = Σ A[i]×B[k-i]  (convolution)
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

constexpr i64 MOD = 1'000'000'007LL;

// ============================================================================
//  📌 POLYNOMIAL EVALUATION — Horner's Method O(n)
// ============================================================================
//  DRY RUN: P(x) = 1 + 2x + 3x², evaluate at x = 5
//    Start from right: 3
//    3 × 5 + 2 = 17
//    17 × 5 + 1 = 86
//    P(5) = 86 ✓  (check: 1 + 10 + 75 = 86)
// ============================================================================

i64 evaluate(const vec<i64>& poly, i64 x, i64 mod) {
    i64 result = 0;
    for (int i = sz(poly) - 1; i >= 0; i--) {
        result = (result * (x % mod) + poly[i] % mod) % mod;
    }
    return (result + mod) % mod;
}

// ============================================================================
//  📌 NAIVE MULTIPLICATION — O(n²)
// ============================================================================

vec<i64> multiply_naive(const vec<i64>& a, const vec<i64>& b, i64 mod) {
    int n = sz(a) + sz(b) - 1;
    vec<i64> c(n, 0);
    for (int i = 0; i < sz(a); i++) {
        for (int j = 0; j < sz(b); j++) {
            c[i + j] = (c[i + j] + a[i] % mod * (b[j] % mod)) % mod;
        }
    }
    return c;
}

// ============================================================================
//  📌 POLYNOMIAL ADDITION / SUBTRACTION
// ============================================================================

vec<i64> poly_add(const vec<i64>& a, const vec<i64>& b, i64 mod) {
    vec<i64> c(max(sz(a), sz(b)), 0);
    for (int i = 0; i < sz(a); i++) c[i] = (c[i] + a[i]) % mod;
    for (int i = 0; i < sz(b); i++) c[i] = (c[i] + b[i]) % mod;
    return c;
}

// ============================================================================
//  📌 POLYNOMIAL DERIVATIVE
// ============================================================================

vec<i64> poly_derivative(const vec<i64>& a, i64 mod) {
    if (sz(a) <= 1) return {0};
    vec<i64> d(sz(a) - 1);
    for (int i = 1; i < sz(a); i++) {
        d[i-1] = a[i] % mod * (i % mod) % mod;
    }
    return d;
}

void print_poly(const vec<i64>& p) {
    for (int i = 0; i < sz(p); i++) {
        if (i > 0 && p[i] >= 0) cout << " + ";
        else if (i > 0) cout << " ";
        cout << p[i];
        if (i == 1) cout << "x";
        else if (i > 1) cout << "x^" << i;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Polynomial Basics ===" << nl << nl;

    // Evaluation via Horner
    cout << "--- Horner's Evaluation ---" << nl;
    vec<i64> P = {1, 2, 3};  // 1 + 2x + 3x²
    cout << "P(x) = "; print_poly(P); cout << nl;
    for (int x = 0; x <= 5; x++) {
        cout << "P(" << x << ") = " << evaluate(P, x, MOD) << nl;
    }

    // Naive multiplication
    cout << nl << "--- Naive Multiplication ---" << nl;
    vec<i64> A = {1, 2, 3}, B = {4, 5};
    auto C = multiply_naive(A, B, MOD);
    cout << "A = "; print_poly(A); cout << nl;
    cout << "B = "; print_poly(B); cout << nl;
    cout << "A×B = "; print_poly(C); cout << nl;
    assert((C == vec<i64>{4, 13, 22, 15}));
    cout << "Expected: 4 + 13x + 22x² + 15x³ ✓" << nl;

    // Derivative
    cout << nl << "--- Derivative ---" << nl;
    vec<i64> Q = {5, 3, 6, 2};  // 5 + 3x + 6x² + 2x³
    auto dQ = poly_derivative(Q, MOD);
    cout << "Q(x) = "; print_poly(Q); cout << nl;
    cout << "Q'(x) = "; print_poly(dQ); cout << nl;
    // Expected: 3 + 12x + 6x²

    return 0;
}

