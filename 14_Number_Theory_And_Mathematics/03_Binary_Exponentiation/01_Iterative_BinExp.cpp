/*
 * ============================================================================
 *  📘 01 — Iterative Binary Exponentiation
 * ============================================================================
 *
 *  PROBLEM: Compute a^n mod m efficiently.
 *
 *  KEY IDEA: Write n in binary. For each set bit i, multiply result by a^(2^i).
 *    a^13 = a^(1101₂) = a^8 × a^4 × a^1
 *
 *  LOOP INVARIANT: answer = result × base^n
 *
 *  TIME: O(log n) multiplications
 *  SPACE: O(1)
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
//  📌 BINARY EXPONENTIATION — Iterative (Standard CP Version)
// ============================================================================

i64 binpow(i64 base, i64 exp, i64 mod) {
    i64 result = 1;
    base %= mod;
    if (base < 0) base += mod;  // handle negative base
    while (exp > 0) {
        if (exp & 1) {
            result = result * base % mod;
        }
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

// ============================================================================
//  📌 BINARY EXPONENTIATION — With Step-by-Step Trace
// ============================================================================
//
//  DRY RUN: binpow_trace(2, 10, 1000000007)
//
//  Step | exp (binary)  | exp odd? | result          | base
//  -----|---------------|----------|-----------------|------
//    0  | 1010 (10)     | NO       | 1               | 2² = 4
//    1  | 0101 (5)      | YES      | 1 × 4 = 4       | 4² = 16
//    2  | 0010 (2)      | NO       | 4               | 16² = 256
//    3  | 0001 (1)      | YES      | 4 × 256 = 1024  | 256² (done)
//
//  Result: 2^10 = 1024 ✓
// ============================================================================

i64 binpow_trace(i64 base, i64 exp, i64 mod) {
    cout << "  Computing " << base << "^" << exp << " mod " << mod << nl;
    i64 result = 1;
    base %= mod;
    int step = 0;

    cout << "  Step | exp      | odd? | result     | base" << nl;
    cout << "  -----|----------|------|------------|------" << nl;

    while (exp > 0) {
        bool is_odd = exp & 1;
        if (is_odd) {
            result = result * base % mod;
        }
        cout << "  " << step << "    | " << exp << "\t| " << (is_odd ? "YES" : "NO ")
             << "  | " << result << "\t| ";

        base = base * base % mod;
        exp >>= 1;

        cout << base << nl;
        step++;
    }
    cout << "  Final result: " << result << nl;
    return result;
}

// ============================================================================
//  📌 WITHOUT MODULO (for small exponents only)
// ============================================================================

i64 binpow_no_mod(i64 base, i64 exp) {
    i64 result = 1;
    while (exp > 0) {
        if (exp & 1) result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}

// ============================================================================
//  📌 BINARY MULTIPLICATION (for large modulus)
// ============================================================================
//  When mod > 10^9, a*b can overflow even long long.
//  Use __int128 or binary multiplication.
//
//  Binary multiplication: compute a*b mod m in O(log b)
//  Same idea as binary exponentiation, but with addition.
// ============================================================================

i64 mulmod(i64 a, i64 b, i64 mod) {
    return (__int128)a * b % mod;
}

i64 binpow_large_mod(i64 base, i64 exp, i64 mod) {
    i64 result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = mulmod(result, base, mod);
        base = mulmod(base, base, mod);
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Binary Exponentiation ===" << nl << nl;

    // Dry run 1
    cout << "--- Dry Run: 2^10 ---" << nl;
    binpow_trace(2, 10, MOD);
    cout << nl;

    // Dry run 2
    cout << "--- Dry Run: 3^13 ---" << nl;
    binpow_trace(3, 13, MOD);
    cout << nl;

    // Dry run 3
    cout << "--- Dry Run: 7^256 mod 13 ---" << nl;
    binpow_trace(7, 256, 13);
    cout << nl;

    // Verification with small values
    cout << "--- Verification ---" << nl;
    for (int b = 2; b <= 5; b++) {
        for (int e = 0; e <= 10; e++) {
            i64 fast = binpow(b, e, MOD);
            i64 naive = binpow_no_mod(b, e);
            assert(fast == naive % MOD);
        }
    }
    cout << "All small tests passed!" << nl << nl;

    // Large exponent
    cout << "--- Large Exponents ---" << nl;
    cout << "2^1000000000 mod 10^9+7 = " << binpow(2, 1000000000LL, MOD) << nl;
    cout << "2^(10^18) mod 10^9+7 = " << binpow(2, (i64)1e18, MOD) << nl;

    // Fermat's Little Theorem application
    cout << nl << "--- Fermat's Little Theorem ---" << nl;
    cout << "a^(p-1) ≡ 1 (mod p) for prime p, gcd(a,p) = 1" << nl;
    i64 p = MOD;
    for (i64 a : {2LL, 3LL, 7LL, 42LL, 1000000006LL}) {
        cout << a << "^" << (p-1) << " mod " << p << " = " << binpow(a, p - 1, p) << nl;
    }

    return 0;
}

