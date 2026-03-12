/*
 * ============================================================================
 *  📘 02 — Recursive Binary Exponentiation
 * ============================================================================
 *
 *  RECURSIVE FORMULATION:
 *    a^0 = 1
 *    a^n = (a^(n/2))² × a^(n mod 2)
 *
 *  This is mathematically elegant but slightly slower due to recursion.
 *  Stack depth: O(log n).
 *
 *  Reference: https://cp-algorithms.com/algebra/binary-exp.html
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
//  📌 RECURSIVE Binary Exponentiation
// ============================================================================
//
//  DRY RUN: rec_pow(2, 10, MOD)
//    rec_pow(2, 10) → half = rec_pow(2, 5) → result = half² mod m
//    rec_pow(2, 5)  → half = rec_pow(2, 2) → result = half² × 2 mod m
//    rec_pow(2, 2)  → half = rec_pow(2, 1) → result = half² mod m
//    rec_pow(2, 1)  → half = rec_pow(2, 0) → result = half² × 2 mod m
//    rec_pow(2, 0)  → return 1
//
//  Unwinding:
//    rec_pow(2, 0) = 1
//    rec_pow(2, 1) = 1² × 2 = 2
//    rec_pow(2, 2) = 2² = 4
//    rec_pow(2, 5) = 4² × 2 = 32
//    rec_pow(2, 10) = 32² = 1024 ✓
// ============================================================================

i64 rec_pow(i64 base, i64 exp, i64 mod) {
    if (exp == 0) return 1;

    i64 half = rec_pow(base, exp / 2, mod);
    i64 result = half * half % mod;

    if (exp & 1) {  // odd exponent
        result = result * (base % mod) % mod;
    }
    return result;
}

// ============================================================================
//  📌 RECURSIVE with Trace
// ============================================================================

i64 rec_pow_trace(i64 base, i64 exp, i64 mod, int depth = 0) {
    string indent(depth * 2, ' ');

    if (exp == 0) {
        cout << indent << "rec_pow(" << base << ", 0) = 1" << nl;
        return 1;
    }

    cout << indent << "rec_pow(" << base << ", " << exp << "):" << nl;

    i64 half = rec_pow_trace(base, exp / 2, mod, depth + 1);
    i64 result = half * half % mod;

    if (exp & 1) {
        result = result * (base % mod) % mod;
        cout << indent << "  = " << half << "² × " << base << " = " << result << nl;
    } else {
        cout << indent << "  = " << half << "² = " << result << nl;
    }

    return result;
}

// ============================================================================
//  📌 APPLICATION: Modular Inverse via Fermat's Little Theorem
// ============================================================================
//  If p is prime and gcd(a, p) = 1:
//    a^(p-1) ≡ 1 (mod p)          [Fermat's Little Theorem]
//    a × a^(p-2) ≡ 1 (mod p)
//    So: a^(-1) ≡ a^(p-2) (mod p)
// ============================================================================

i64 mod_inverse(i64 a, i64 p) {
    return rec_pow(a, p - 2, p);
}

// ============================================================================
//  📌 APPLICATION: Large Power of a Sum
// ============================================================================
//  Compute (a + b)^n mod m using binomial theorem is expensive.
//  But a^n mod m is O(log n).
// ============================================================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Recursive Binary Exponentiation ===" << nl << nl;

    // Dry run with trace
    cout << "--- Trace: 2^10 mod 10^9+7 ---" << nl;
    i64 r1 = rec_pow_trace(2, 10, MOD);
    cout << "Result: " << r1 << nl << nl;

    cout << "--- Trace: 3^7 mod 10^9+7 ---" << nl;
    i64 r2 = rec_pow_trace(3, 7, MOD);
    cout << "Result: " << r2 << "  (3^7 = " << (i64)pow(3, 7) << ")" << nl << nl;

    // Modular inverse
    cout << "--- Modular Inverse (Fermat) ---" << nl;
    for (i64 a : {2LL, 3LL, 5LL, 7LL, 11LL}) {
        i64 inv = mod_inverse(a, MOD);
        cout << a << "^(-1) mod " << MOD << " = " << inv
             << "  [check: " << a << " × " << inv << " mod " << MOD << " = "
             << (a * inv % MOD) << "]" << nl;
    }

    // nCr using modular inverse
    cout << nl << "--- nCr mod p using Fermat ---" << nl;
    int N = 20;
    vec<i64> fact(N + 1);
    fact[0] = 1;
    for (int i = 1; i <= N; i++) fact[i] = fact[i-1] * i % MOD;

    auto nCr = [&](int n, int r) -> i64 {
        if (r < 0 || r > n) return 0;
        return fact[n] % MOD * mod_inverse(fact[r], MOD) % MOD * mod_inverse(fact[n-r], MOD) % MOD;
    };

    for (auto [n, r] : vec<pii>{{5,2},{10,3},{20,10},{10,0},{10,10}}) {
        cout << "C(" << n << "," << r << ") = " << nCr(n, r) << nl;
    }

    return 0;
}

