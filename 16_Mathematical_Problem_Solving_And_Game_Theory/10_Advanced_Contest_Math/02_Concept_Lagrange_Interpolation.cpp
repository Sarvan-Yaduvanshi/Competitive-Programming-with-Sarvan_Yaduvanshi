/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-13 19:41:21
*/
/*
 * ============================================================
 *  Topic   : Lagrange Interpolation
 *  Pattern : Given k+1 points, evaluate degree-k polynomial at any x
 *
 *  Problems:
 *    - Codeforces 622F — Sum of k-th Powers
 *    - Evaluate polynomial sum at large n
 *
 *  Complexity: O(k²) general, O(k) for consecutive x-values
 * ============================================================
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
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

template<class T>
void read(vec<T> &v) { for (auto &x : v) cin >> x; }
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD) {
    i64 res = 1; base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

inline i64 modinv(i64 a, i64 mod = MOD) {
    return modpow(a, mod - 2, mod);
}

/*
 * ============================================================
 *  LAGRANGE INTERPOLATION — General Version
 * ============================================================
 *
 *  Given n points (x₀,y₀), ..., (xₙ₋₁,yₙ₋₁), evaluate the
 *  unique polynomial of degree < n at point t.
 *
 *  FORMULA:
 *  P(t) = Σᵢ yᵢ × ∏_{j≠i} (t - xⱼ) / (xᵢ - xⱼ)
 *
 *  TIME: O(n²) with modular arithmetic
 * ============================================================
 */

i64 lagrangeInterpolation(vec<i64>& x, vec<i64>& y, i64 t) {
    int n = sz(x);
    i64 result = 0;

    for (int i = 0; i < n; i++) {
        // Compute Lagrange basis polynomial Lᵢ(t)
        i64 num = 1, den = 1;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            num = num % MOD * ((t - x[j]) % MOD + MOD) % MOD;
            den = den % MOD * ((x[i] - x[j]) % MOD + MOD) % MOD;
        }
        result = (result + y[i] % MOD * num % MOD * modinv(den)) % MOD;
    }

    return (result + MOD) % MOD;
}

/*
 * ============================================================
 *  LAGRANGE INTERPOLATION — Consecutive Points
 * ============================================================
 *
 *  If points are at x = 0, 1, 2, ..., n-1 then:
 *  - Precompute prefix/suffix products of (t - i)
 *  - Precompute factorial inverse for denominators
 *
 *  TIME: O(n) — much faster!
 *
 *  APPLICATION: Compute Σ i^k for i=1..n
 *  - S(n) = 1^k + 2^k + ... + n^k is a polynomial of degree k+1 in n
 *  - Compute S(0), S(1), ..., S(k+1) directly
 *  - Interpolate to find S(n) for large n
 * ============================================================
 */

i64 lagrangeConsecutive(vec<i64>& y, i64 t) {
    // Points at x = 0, 1, 2, ..., n-1
    int n = sz(y);

    // If t is one of the sample points
    if (t >= 0 && t < n) return y[t] % MOD;

    // Precompute factorials and inverse factorials
    vec<i64> fact(n), ifact(n);
    fact[0] = 1;
    for (int i = 1; i < n; i++) fact[i] = fact[i-1] * i % MOD;
    ifact[n-1] = modinv(fact[n-1]);
    for (int i = n-2; i >= 0; i--) ifact[i] = ifact[i+1] * (i+1) % MOD;

    // Precompute prefix products: pref[i] = ∏_{j=0}^{i-1} (t - j)
    vec<i64> pref(n + 1, 1);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] % MOD * ((t - i) % MOD + MOD) % MOD;
    }

    // Precompute suffix products: suf[i] = ∏_{j=i}^{n-1} (t - j)
    vec<i64> suf(n + 1, 1);
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = suf[i + 1] % MOD * ((t - i) % MOD + MOD) % MOD;
    }

    i64 result = 0;
    for (int i = 0; i < n; i++) {
        // Numerator: ∏_{j≠i} (t - j) = pref[i] * suf[i+1]
        i64 num = pref[i] % MOD * suf[i + 1] % MOD;

        // Denominator: ∏_{j≠i} (i - j) = (-1)^(n-1-i) * i! * (n-1-i)!
        i64 den = ifact[i] % MOD * ifact[n - 1 - i] % MOD;
        if ((n - 1 - i) % 2 == 1) den = MOD - den;

        result = (result + y[i] % MOD * num % MOD * den) % MOD;
    }

    return (result + MOD) % MOD;
}

/*
 * ============================================================
 *  APPLICATION: Sum of k-th Powers
 * ============================================================
 *
 *  Compute S(n) = 1^k + 2^k + ... + n^k  (mod MOD)
 *
 *  S(n) is a polynomial of degree k+1 in n.
 *  So we need k+2 sample points.
 *
 *  Compute S(0), S(1), ..., S(k+1) directly, then interpolate.
 *
 *  Direct computation of each S(i): O(k log k) (or O(k) if cumulative)
 *  Interpolation: O(k)
 *  Total: O(k log k) or O(k²) depending on modpow usage
 * ============================================================
 */

i64 sumOfKthPowers(i64 n, int k) {
    // Compute S(0), S(1), ..., S(k+1)
    int pts = k + 2;
    vec<i64> y(pts, 0);
    y[0] = 0;  // S(0) = 0
    for (int i = 1; i < pts; i++) {
        y[i] = (y[i-1] + modpow(i, k)) % MOD;
    }

    // Interpolate at n
    return lagrangeConsecutive(y, n % MOD);
}

void solve() {
    i64 n;
    int k;
    cin >> n >> k;

    cout << sumOfKthPowers(n, k) << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    int TC = 1;
    // cin >> TC;
    while (TC--) solve();

    return 0;
}