/*
 * ============================================================================
 *  📘 01 — Modular Arithmetic Basics
 * ============================================================================
 *
 *  MODULAR OPERATIONS:
 *    (a + b) mod m = ((a%m) + (b%m)) % m
 *    (a - b) mod m = ((a%m) - (b%m) + m) % m     ← +m for safety
 *    (a × b) mod m = ((a%m) × (b%m)) % m
 *    (a / b) mod m = (a × b^(-1)) mod m           ← needs inverse
 *
 *  WHY +m in subtraction?
 *    In C++, (-3) % 7 = -3 (not 4). Adding m fixes this.
 *
 *  OVERFLOW PREVENTION:
 *    For m ≤ 10^9: (a%m)*(b%m) ≤ (10^9)² = 10^18 → fits in long long ✓
 *    For m > 10^9: Use __int128 or binary multiplication
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
#define sz(x) ((int)(x).size())
#define pb push_back
#define fi first
#define se second
#define nl '\n'

template<class T>
void read(vec<T> &v) { for (auto &x : v) cin >> x; }

// ============================================================================
//  📌 SAFE MODULAR OPERATIONS
// ============================================================================

inline i64 mod_add(i64 a, i64 b, i64 m = MOD) {
    return ((a % m) + (b % m)) % m;
}

inline i64 mod_sub(i64 a, i64 b, i64 m = MOD) {
    return ((a % m) - (b % m) + m) % m;
}

inline i64 mod_mul(i64 a, i64 b, i64 m = MOD) {
    return (a % m) * (b % m) % m;
}

inline i64 mod_pow(i64 base, i64 exp, i64 m = MOD) {
    i64 result = 1;
    base %= m;
    while (exp > 0) {
        if (exp & 1) result = result * base % m;
        base = base * base % m;
        exp >>= 1;
    }
    return result;
}

// Modular inverse (p must be prime)
inline i64 mod_inv(i64 a, i64 m = MOD) {
    return mod_pow(a, m - 2, m);
}

inline i64 mod_div(i64 a, i64 b, i64 m = MOD) {
    return mod_mul(a, mod_inv(b, m), m);
}

// ============================================================================
//  📌 MINT STRUCT (Modular Integer — clean CP style)
// ============================================================================
//  Wraps all operations so you never forget to take mod.
//  Usage: mint a = 5, b = 3; mint c = a * b + a;
// ============================================================================

template<i64 MOD_VAL>
struct Mint {
    i64 val;

    Mint(i64 v = 0) : val((v % MOD_VAL + MOD_VAL) % MOD_VAL) {}

    Mint operator+(const Mint &o) const { return Mint(val + o.val); }
    Mint operator-(const Mint &o) const { return Mint(val - o.val + MOD_VAL); }
    Mint operator*(const Mint &o) const { return Mint(val * o.val); }

    Mint power(i64 e) const {
        Mint res(1), base(val);
        while (e > 0) {
            if (e & 1) res = res * base;
            base = base * base;
            e >>= 1;
        }
        return res;
    }

    Mint inv() const { return power(MOD_VAL - 2); }
    Mint operator/(const Mint &o) const { return *this * o.inv(); }

    Mint& operator+=(const Mint &o) { return *this = *this + o; }
    Mint& operator-=(const Mint &o) { return *this = *this - o; }
    Mint& operator*=(const Mint &o) { return *this = *this * o; }
    Mint& operator/=(const Mint &o) { return *this = *this / o; }

    bool operator==(const Mint &o) const { return val == o.val; }
    bool operator!=(const Mint &o) const { return val != o.val; }

    friend ostream& operator<<(ostream &os, const Mint &m) { return os << m.val; }
    friend istream& operator>>(istream &is, Mint &m) { is >> m.val; m.val = (m.val % MOD_VAL + MOD_VAL) % MOD_VAL; return is; }
};

using mint = Mint<1000000007>;
using mint9 = Mint<998244353>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Modular Arithmetic Basics ===" << nl << nl;

    // Basic operations demo
    cout << "--- Basic Operations (mod 10^9+7) ---" << nl;
    i64 a = 1000000006, b = 5;
    cout << "a = " << a << ", b = " << b << ", m = " << MOD << nl;
    cout << "(a + b) mod m = " << mod_add(a, b) << nl;
    cout << "(a - b) mod m = " << mod_sub(a, b) << nl;
    cout << "(a × b) mod m = " << mod_mul(a, b) << nl;
    cout << nl;

    // Subtraction safety
    cout << "--- Subtraction Safety ---" << nl;
    cout << "C++ native: (-3) % 7 = " << ((-3) % 7) << " (WRONG for math!)" << nl;
    cout << "Safe:       mod_sub(0, 3, 7) = " << mod_sub(0, 3, 7) << " ✓" << nl;
    cout << nl;

    // Mint demo
    cout << "--- Mint Struct Demo ---" << nl;
    mint x = 1000000006;
    mint y = 5;
    cout << "x = " << x << ", y = " << y << nl;
    cout << "x + y = " << x + y << nl;
    cout << "x * y = " << x * y << nl;
    cout << "x / y = " << x / y << " (= x * y^(-1))" << nl;
    cout << "y^(-1) = " << y.inv() << nl;
    cout << "Check: y * y^(-1) = " << y * y.inv() << nl;
    cout << nl;

    // Practical: Compute n! mod p
    cout << "--- Factorial mod 10^9+7 ---" << nl;
    mint fact = 1;
    for (int i = 1; i <= 20; i++) {
        fact *= mint(i);
        cout << i << "! mod p = " << fact << nl;
    }

    return 0;
}

