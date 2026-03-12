/*
 * ============================================================================
 *  📘 02 — Miller-Rabin Primality Test
 * ============================================================================
 *
 *  ALGORITHM:
 *    Write n-1 = 2^s × d (d odd).
 *    For each witness a:
 *      x = a^d mod n
 *      if x == 1 or x == n-1: next witness
 *      repeat s-1 times:
 *        x = x² mod n
 *        if x == n-1: break (probably prime)
 *        if x == 1: return COMPOSITE
 *      if never hit n-1: return COMPOSITE
 *
 *  DETERMINISTIC for n < 3.3×10^18:
 *    witnesses = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}
 *
 *  KEY THEOREM: If n is an odd prime and x² ≡ 1 (mod n),
 *    then x ≡ ±1 (mod n).
 *
 *  PROOF:
 *    x² ≡ 1 → n | (x²-1) → n | (x-1)(x+1)
 *    Since n is prime: n | (x-1) or n | (x+1)
 *    So x ≡ 1 or x ≡ -1 (mod n). ∎
 *
 *  Reference: https://cp-algorithms.com/algebra/primality_tests.html
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
#include <random>
#include <chrono>
#include <cassert>

using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using u128 = __uint128_t;
template<class T> using vec = vector<T>;
#define nl '\n'
#define sz(x) ((int)(x).size())

// ============================================================================
//  📌 Modular multiplication using __int128 (prevents overflow)
// ============================================================================

i64 mulmod(i64 a, i64 b, i64 m) {
    return (u128)a * b % m;
}

i64 powmod(i64 base, i64 exp, i64 mod) {
    i64 result = 1;
    base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) result = mulmod(result, base, mod);
        base = mulmod(base, base, mod);
        exp >>= 1;
    }
    return result;
}

// ============================================================================
//  📌 MILLER-RABIN TEST (single witness)
// ============================================================================
//  Returns true if n is probably prime for witness a.
//  Returns false if n is definitely composite.
// ============================================================================

bool miller_rabin_witness(i64 n, i64 a) {
    if (n % a == 0) return n == a;

    // Write n-1 = 2^s * d
    i64 d = n - 1;
    int s = 0;
    while (d % 2 == 0) { d /= 2; s++; }

    // x = a^d mod n
    i64 x = powmod(a, d, n);

    if (x == 1 || x == n - 1) return true;

    for (int r = 0; r < s - 1; r++) {
        x = mulmod(x, x, n);
        if (x == n - 1) return true;
        if (x == 1) return false;  // non-trivial sqrt of 1
    }

    return false;  // never hit n-1
}

// ============================================================================
//  📌 DETERMINISTIC MILLER-RABIN
// ============================================================================
//  For n < 3.3 × 10^18, the following 12 witnesses suffice.
// ============================================================================

bool is_prime(i64 n) {
    if (n < 2) return false;
    if (n < 4) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    // Deterministic witnesses
    for (i64 a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a) return true;
        if (!miller_rabin_witness(n, a)) return false;
    }
    return true;
}

// ============================================================================
//  📌 FERMAT TEST (for comparison — defeated by Carmichael numbers)
// ============================================================================

bool fermat_test(i64 n, int iterations = 20) {
    if (n < 4) return n >= 2;
    mt19937_64 rng(42);
    for (int i = 0; i < iterations; i++) {
        i64 a = 2 + rng() % (n - 3);
        if (powmod(a, n - 1, n) != 1) return false;
    }
    return true;  // probably prime (but Carmichael numbers fool this!)
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Miller-Rabin Primality Test ===" << nl << nl;

    // Basic tests
    cout << "--- Basic Tests ---" << nl;
    vec<i64> test = {2, 3, 4, 5, 17, 561, 1000000007, 998244353, 999999937};
    for (i64 n : test) {
        cout << n << ": " << (is_prime(n) ? "PRIME" : "COMPOSITE") << nl;
    }

    // Carmichael numbers (fool Fermat, but NOT Miller-Rabin)
    cout << nl << "--- Carmichael Numbers ---" << nl;
    vec<i64> carmichael = {561, 1105, 1729, 2465, 2821, 6601, 8911};
    for (i64 n : carmichael) {
        cout << n << ": Fermat=" << (fermat_test(n) ? "prime?" : "composite")
             << "  Miller-Rabin=" << (is_prime(n) ? "prime" : "COMPOSITE") << nl;
    }

    // Large primes
    cout << nl << "--- Large Primes ---" << nl;
    vec<i64> large = {
        1000000007LL, 998244353LL, 999999937LL,
        1000000000000000003LL, // 10^18 + 3 (prime)
        999999999999999989LL,  // large prime
    };
    for (i64 n : large) {
        cout << n << ": " << (is_prime(n) ? "PRIME" : "COMPOSITE") << nl;
    }

    // Dry run trace for n = 221 = 13 × 17
    cout << nl << "--- Dry Run: n = 221, witness a = 174 ---" << nl;
    {
        i64 n = 221, a = 174;
        i64 d = n - 1; int s = 0;
        while (d % 2 == 0) { d /= 2; s++; }
        cout << "n-1 = " << n-1 << " = 2^" << s << " × " << d << nl;

        i64 x = powmod(a, d, n);
        cout << "x = " << a << "^" << d << " mod " << n << " = " << x << nl;

        for (int r = 0; r < s - 1; r++) {
            i64 x_new = mulmod(x, x, n);
            cout << "x = " << x << "² mod " << n << " = " << x_new;
            if (x_new == n - 1) cout << " = n-1 → probably prime for this witness";
            cout << nl;
            x = x_new;
        }
        cout << "Miller-Rabin(221, 174): " << (miller_rabin_witness(221, 174) ? "probably prime" : "COMPOSITE") << nl;
        cout << "Miller-Rabin(221, 137): " << (miller_rabin_witness(221, 137) ? "probably prime" : "COMPOSITE") << nl;
        cout << "Final: is_prime(221) = " << (is_prime(221) ? "prime" : "COMPOSITE") << nl;
    }

    return 0;
}

