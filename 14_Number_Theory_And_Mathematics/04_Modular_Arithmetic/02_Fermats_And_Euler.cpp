/*
 * ============================================================================
 *  📘 02 — Fermat's & Euler's Theorem
 * ============================================================================
 *
 *  FERMAT'S LITTLE THEOREM:
 *    If p is prime and gcd(a, p) = 1: a^(p-1) ≡ 1 (mod p)
 *
 *  EULER'S THEOREM (Generalization):
 *    If gcd(a, n) = 1: a^φ(n) ≡ 1 (mod n)
 *
 *  Reference: https://cp-algorithms.com/algebra/phi-function.html
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

constexpr i64 MOD = 1'000'000'007LL;

i64 powmod(i64 base, i64 exp, i64 mod) {
    i64 res = 1; base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Fermat's Little Theorem ===" << nl;
    cout << "a^(p-1) ≡ 1 (mod p) for prime p, gcd(a,p) = 1" << nl << nl;

    // Verify for p = 7
    for (int a = 1; a < 7; a++) {
        cout << a << "^6 mod 7 = " << powmod(a, 6, 7) << nl;
    }

    cout << nl << "=== Euler's Theorem ===" << nl;
    cout << "a^φ(n) ≡ 1 (mod n) when gcd(a,n) = 1" << nl << nl;

    for (int n : {10, 12, 15, 20}) {
        i64 phi = euler_phi(n);
        cout << "n=" << n << ", φ(" << n << ")=" << phi << ": ";
        bool all_ok = true;
        for (int a = 1; a < n; a++) {
            if (__gcd(a, n) == 1) {
                i64 val = powmod(a, phi, n);
                if (val != 1) { all_ok = false; break; }
            }
        }
        cout << (all_ok ? "ALL ≡ 1 ✓" : "FAILED") << nl;
    }

    // Application: compute a^b mod m where b is huge
    cout << nl << "=== Application: a^b mod m for huge b ===" << nl;
    cout << "When gcd(a, m) = 1: a^b mod m = a^(b mod φ(m)) mod m" << nl;
    i64 a = 2, b = (i64)1e18, m = 1000;
    i64 phi_m = euler_phi(m);
    cout << "2^(10^18) mod 1000" << nl;
    cout << "φ(1000) = " << phi_m << nl;
    cout << "10^18 mod " << phi_m << " = " << (b % phi_m) << nl;
    cout << "2^" << (b % phi_m) << " mod 1000 = " << powmod(a, b % phi_m, m) << nl;
    cout << "Direct: 2^(10^18) mod 1000 = " << powmod(a, b, m) << nl;

    return 0;
}

