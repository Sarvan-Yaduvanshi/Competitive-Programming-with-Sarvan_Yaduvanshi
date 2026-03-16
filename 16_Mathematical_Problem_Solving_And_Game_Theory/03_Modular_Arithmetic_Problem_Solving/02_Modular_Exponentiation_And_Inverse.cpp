/*
 * ============================================================
 *  Topic   : Modular Exponentiation & Mod Inverse
 *  Pattern : Binary exponentiation, Fermat's inverse, Extended GCD
 *
 *  Problems:
 *    - CSES Exponentiation (1095)
 *    - CSES Exponentiation II (1712)
 *    - LeetCode 50 — Pow(x, n)
 *
 *  Complexity: O(log n) for modpow, O(n) for precomputing factorials
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

/*
 * ============================================================
 *  BINARY EXPONENTIATION — O(log exp)
 * ============================================================
 *
 *  Idea: a^b = (a^(b/2))^2  if b is even
 *             = a * (a^(b/2))^2  if b is odd
 *
 *  Works for: modular exponentiation, matrix exponentiation
 * ============================================================
 */
inline i64 modpow(i64 base, i64 exp, i64 mod = MOD) {
    i64 res = 1;
    base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

/*
 * ============================================================
 *  MODULAR INVERSE
 * ============================================================
 *
 *  METHOD 1: Fermat's Little Theorem (mod is PRIME)
 *  a^(-1) ≡ a^(p-2) (mod p)
 *
 *  METHOD 2: Extended GCD (mod can be non-prime)
 *  Solve: a*x + m*y = gcd(a, m)
 *  If gcd = 1, then x is the inverse
 *
 *  METHOD 3: Linear precomputation of inv[1..n]
 *  inv[i] = -(m/i) * inv[m % i] mod m
 * ============================================================
 */

// Method 1: Fermat's inverse (mod must be prime)
inline i64 modinv_fermat(i64 a, i64 p = MOD) {
    return modpow(a, p - 2, p);
}

// Method 2: Extended GCD
i64 extgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    i64 x1, y1;
    i64 g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

i64 modinv_extgcd(i64 a, i64 m) {
    i64 x, y;
    i64 g = extgcd(a, m, x, y);
    if (g != 1) return -1;  // No inverse exists
    return (x % m + m) % m;
}

/*
 * ============================================================
 *  MODULAR COMBINATORICS — nCr mod p
 * ============================================================
 *  Precompute fact[] and ifact[] for O(1) nCr queries.
 * ============================================================
 */
const int MAXN = 2'000'001;
i64 fact[MAXN], ifact[MAXN];

void precompute_factorials(i64 mod = MOD) {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++)
        fact[i] = fact[i - 1] * i % mod;
    ifact[MAXN - 1] = modpow(fact[MAXN - 1], mod - 2, mod);
    for (int i = MAXN - 2; i >= 0; i--)
        ifact[i] = ifact[i + 1] * (i + 1) % mod;
}

i64 C(int n, int r, i64 mod = MOD) {
    if (r < 0 || r > n) return 0;
    return fact[n] % mod * ifact[r] % mod * ifact[n - r] % mod;
}

i64 P(int n, int r, i64 mod = MOD) {
    if (r < 0 || r > n) return 0;
    return fact[n] % mod * ifact[n - r] % mod;
}

/*
 *  LUCAS' THEOREM — nCr mod p when n is very large, p is small prime
 *  C(n, r) mod p = product of C(n_i, r_i) mod p
 *  where n_i, r_i are digits of n, r in base p
 */
i64 lucas(i64 n, i64 r, i64 p) {
    if (r == 0) return 1;
    return C(n % p, r % p, p) * lucas(n / p, r / p, p) % p;
}

void solve() {
    i64 a, b, m;
    cin >> a >> b >> m;

    // a^b mod m
    cout << modpow(a, b, m) << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    precompute_factorials();

    int TC = 1;
    cin >> TC;
    while (TC--) solve();

    return 0;
}

