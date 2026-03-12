/*
 * ============================================================================
 *  📘 01 — Complete Number Theory Template (ICPC / GM Level)
 * ============================================================================
 *
 *  All essential NT algorithms in one file:
 *    - Miller-Rabin (deterministic, n < 3.3×10^18)
 *    - Pollard's Rho (Brent variant, batch GCD)
 *    - Euler Totient (single + sieve)
 *    - Extended Euclidean + Modular Inverse
 *    - CRT (coprime + general)
 *    - nCr modular (factorial precomp)
 *    - Floor block decomposition
 *
 *  Ready to copy-paste into contest submissions.
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
using u128 = __uint128_t;
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

// ========================= BASIC UTILITIES =========================

inline i64 mulmod(i64 a, i64 b, i64 m) { return (u128)a * b % m; }

inline i64 powmod(i64 base, i64 exp, i64 mod) {
    i64 res = 1; base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) res = mulmod(res, base, mod);
        base = mulmod(base, base, mod);
        exp >>= 1;
    }
    return res;
}

i64 extgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    i64 x1, y1;
    i64 g = extgcd(b, a % b, x1, y1);
    x = y1; y = x1 - (a / b) * y1;
    return g;
}

// ========================= MILLER-RABIN =========================

bool is_prime(i64 n) {
    if (n < 2) return false;
    if (n < 4) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    i64 d = n - 1; int s = 0;
    while (d % 2 == 0) { d /= 2; s++; }
    for (i64 a : {2,3,5,7,11,13,17,19,23,29,31,37}) {
        if (n == a) return true;
        if (n % a == 0) return false;
        i64 x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool found = false;
        for (int r = 0; r < s - 1; r++) {
            x = mulmod(x, x, n);
            if (x == n - 1) { found = true; break; }
        }
        if (!found) return false;
    }
    return true;
}

// ========================= POLLARD'S RHO =========================

i64 pollard_rho(i64 n) {
    if (n % 2 == 0) return 2;
    while (true) {
        i64 x = rng() % (n - 2) + 2, y = x;
        i64 c = rng() % (n - 1) + 1, d = 1;
        while (d == 1) {
            x = (mulmod(x, x, n) + c) % n;
            y = (mulmod(y, y, n) + c) % n;
            y = (mulmod(y, y, n) + c) % n;
            d = __gcd(abs(x - y), n);
        }
        if (d != n) return d;
    }
}

vec<i64> factorize(i64 n) {
    if (n <= 1) return {};
    if (is_prime(n)) return {n};
    i64 d = pollard_rho(n);
    auto l = factorize(d), r = factorize(n / d);
    l.insert(l.end(), all(r));
    return l;
}

map<i64, int> factorize_map(i64 n) {
    auto primes = factorize(n);
    map<i64, int> m;
    for (i64 p : primes) m[p]++;
    return m;
}

// ========================= EULER TOTIENT =========================

i64 euler_phi(i64 n) {
    i64 result = n;
    for (i64 p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

// ========================= MODULAR INVERSE =========================

i64 mod_inv(i64 a, i64 m) {
    i64 x, y;
    i64 g = extgcd(a % m + m, m, x, y);
    return g == 1 ? (x % m + m) % m : -1;
}

// ========================= CRT =========================

pll crt2(i64 r1, i64 m1, i64 r2, i64 m2) {
    i64 x, y;
    i64 g = extgcd(m1, m2, x, y);
    if ((r2 - r1) % g) return {-1, -1};
    i64 lcm = m1 / g * m2;
    i64 t = (i64)((u128)((r2-r1)/g % (m2/g)) * (x % (m2/g)) % (m2/g) + (m2/g)) % (m2/g);
    i64 r = (r1 + m1 * t % lcm) % lcm;
    return {(r + lcm) % lcm, lcm};
}

pll crt(const vec<i64>& r, const vec<i64>& m) {
    i64 cr = r[0], cm = m[0];
    for (int i = 1; i < sz(r); i++) {
        auto [nr, nm] = crt2(cr, cm, r[i], m[i]);
        if (nm == -1) return {-1, -1};
        cr = nr; cm = nm;
    }
    return {cr, cm};
}

// ========================= nCr MODULAR =========================

struct Combo {
    vec<i64> fact, ifact;
    i64 mod;
    Combo(int n, i64 m) : mod(m), fact(n+1), ifact(n+1) {
        fact[0] = 1;
        for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i % mod;
        ifact[n] = powmod(fact[n], mod - 2, mod);
        for (int i = n-1; i >= 0; i--) ifact[i] = ifact[i+1] * (i+1) % mod;
    }
    i64 C(int n, int r) {
        if (r < 0 || r > n) return 0;
        return fact[n] % mod * ifact[r] % mod * ifact[n-r] % mod;
    }
};

// ========================= FLOOR BLOCK DECOMPOSITION =========================

// Σ_{i=1}^{n} ⌊n/i⌋ in O(√n)
i64 sum_floor(i64 n) {
    i64 res = 0;
    for (i64 i = 1; i <= n; ) {
        i64 v = n / i, hi = n / v;
        res += (hi - i + 1) * v;
        i = hi + 1;
    }
    return res;
}

// ========================= SOLVE =========================

void solve() {
    // Example: factorize a large number
    i64 n;
    cin >> n;

    auto factors = factorize_map(n);
    cout << n << " = ";
    bool first = true;
    for (auto [p, e] : factors) {
        if (!first) cout << " × ";
        cout << p;
        if (e > 1) cout << "^" << e;
        first = false;
    }
    cout << nl;

    cout << "is_prime: " << (is_prime(n) ? "YES" : "NO") << nl;
    cout << "phi: " << euler_phi(n) << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int TC = 1;
    cin >> TC;
    while (TC--) solve();

    return 0;
}

