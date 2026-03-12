/*
 * ============================================================================
 *  📘 02 — Extended GCD Inverse
 * ============================================================================
 *
 *  Find a^(-1) mod m using Extended Euclidean Algorithm.
 *  Works for ANY m (not just prime), as long as gcd(a, m) = 1.
 *
 *  From extgcd(a, m): ax + my = 1  →  a × x ≡ 1 (mod m)  →  x = a^(-1)
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
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
#define nl '\n'

i64 extgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    i64 x1, y1;
    i64 g = extgcd(b, a % b, x1, y1);
    x = y1; y = x1 - (a / b) * y1;
    return g;
}

// Works for any m, gcd(a, m) = 1
i64 mod_inv_extgcd(i64 a, i64 m) {
    i64 x, y;
    i64 g = extgcd(a % m + m, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Modular Inverse via Extended GCD ===" << nl << nl;

    // Works for non-prime moduli too
    cout << "--- Non-prime modulus m=26 ---" << nl;
    for (int a = 1; a < 26; a++) {
        if (__gcd(a, 26) == 1) {
            i64 inv = mod_inv_extgcd(a, 26);
            cout << a << "^(-1) mod 26 = " << inv
                 << " [check: " << (a * inv % 26) << "]" << nl;
        }
    }

    // Compare with Fermat's for prime
    cout << nl << "--- Prime modulus m=13: ExtGCD vs Fermat ---" << nl;
    for (int a = 1; a < 13; a++) {
        i64 inv1 = mod_inv_extgcd(a, 13);
        i64 base = a, exp = 11, mod = 13, inv2 = 1;
        while (exp > 0) { if (exp & 1) inv2 = inv2 * base % mod; base = base * base % mod; exp >>= 1; }
        cout << a << ": ExtGCD=" << inv1 << ", Fermat=" << inv2
             << (inv1 == inv2 ? " ✓" : " ✗") << nl;
    }

    return 0;
}

