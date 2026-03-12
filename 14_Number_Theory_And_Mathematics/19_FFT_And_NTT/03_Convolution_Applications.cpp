/*
 * ============================================================================
 *  📘 03 — Convolution Applications (via FFT/NTT)
 * ============================================================================
 *
 *  CONVOLUTION: C[k] = Σ A[i] × B[k-i]  (polynomial multiplication)
 *
 *  APPLICATIONS IN CP:
 *
 *  1. BIG INTEGER MULTIPLICATION
 *     Treat digits as polynomial coefficients → NTT → carry propagation.
 *
 *  2. COUNTING SUM COMBINATIONS
 *     A[i] = number of ways to get sum i from set 1.
 *     B[j] = number of ways to get sum j from set 2.
 *     C = A * B → C[k] = ways to get total sum k.
 *
 *  3. STRING MATCHING (wildcard)
 *     Count matches at each position via convolution.
 *
 *  4. OR CONVOLUTION / AND CONVOLUTION (subset sum transform)
 *     Not FFT-based; uses sum-over-subsets (SOS) DP.
 *
 *  5. GCD CONVOLUTION
 *     f(g) = Σ_{gcd(i,j)=g} a[i] × b[j]
 *     Use Möbius inversion + pointwise multiply.
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
//  📌 APPLICATION 1: Counting dice sum distributions
// ============================================================================
//  Two dice: die A has faces {1,2,3,4,5,6}, die B same.
//  count[k] = number of ways to get sum k with 2 dice.
//  This is the convolution of the two distributions.
// ============================================================================

void demo_dice() {
    cout << "--- Dice Sum Convolution ---" << nl;
    vec<i64> die(7, 0);
    for (int f = 1; f <= 6; f++) die[f] = 1;  // x + x² + ... + x⁶

    auto two_dice = poly_mul(die, die);
    cout << "Sum | Ways" << nl;
    for (int s = 2; s <= 12; s++) {
        cout << " " << s << "  |  " << two_dice[s] << nl;
    }
    // Expected: 2→1, 3→2, 4→3, 5→4, 6→5, 7→6, 8→5, 9→4, 10→3, 11→2, 12→1
}

// ============================================================================
//  📌 APPLICATION 2: Counting subset sum (knapsack via NTT)
// ============================================================================
//  Given items with values, count ways to achieve each total.
//  Each item can be used once: product of (1 + x^{val})
// ============================================================================

void demo_subset_sum() {
    cout << nl << "--- Subset Sum Counting ---" << nl;
    vec<int> items = {1, 2, 3, 5};

    vec<i64> result = {1};  // polynomial = 1
    for (int v : items) {
        // Multiply by (1 + x^v)
        vec<i64> term(v + 1, 0);
        term[0] = 1; term[v] = 1;
        result = poly_mul(result, term);
    }

    cout << "Items: {1, 2, 3, 5}" << nl;
    cout << "Sum | Ways" << nl;
    for (int s = 0; s < sz(result); s++) {
        if (result[s] > 0) cout << " " << s << "  |  " << result[s] << nl;
    }
}

// ============================================================================
//  📌 APPLICATION 3: Power of polynomial (k-fold convolution)
// ============================================================================
//  f(x)^k via repeated squaring of polynomials.
// ============================================================================

vec<i64> poly_pow(vec<i64> f, int k, int max_deg) {
    vec<i64> result = {1};
    while (k > 0) {
        if (k & 1) {
            result = poly_mul(result, f);
            if (sz(result) > max_deg + 1) result.resize(max_deg + 1);
        }
        f = poly_mul(f, f);
        if (sz(f) > max_deg + 1) f.resize(max_deg + 1);
        k >>= 1;
    }
    return result;
}

void demo_poly_pow() {
    cout << nl << "--- Sum of 5 dice ---" << nl;
    vec<i64> die(7, 0);
    for (int f = 1; f <= 6; f++) die[f] = 1;

    auto five_dice = poly_pow(die, 5, 30);
    cout << "Sum | Ways" << nl;
    for (int s = 5; s <= 30; s++) {
        if (s < sz(five_dice) && five_dice[s] > 0)
            cout << " " << s << "  |  " << five_dice[s] << nl;
    }
    // Total ways should be 6^5 = 7776
    i64 total = 0;
    for (auto x : five_dice) total += x;
    cout << "Total: " << total << " (should be 7776)" << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Convolution Applications ===" << nl << nl;

    demo_dice();
    demo_subset_sum();
    demo_poly_pow();

    return 0;
}

