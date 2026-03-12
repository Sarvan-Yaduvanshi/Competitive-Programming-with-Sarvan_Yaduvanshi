/*
 * ============================================================================
 *  📘 01 — Chinese Remainder Theorem (Coprime Moduli)
 * ============================================================================
 *
 *  PROBLEM: Solve the system:
 *    x ≡ r₁ (mod m₁)
 *    x ≡ r₂ (mod m₂)
 *    ...
 *    x ≡ rₖ (mod mₖ)
 *    where m₁, m₂, ..., mₖ are pairwise coprime.
 *
 *  UNIQUE SOLUTION exists modulo M = m₁ × m₂ × ... × mₖ.
 *
 *  CONSTRUCTION:
 *    Mᵢ = M / mᵢ
 *    yᵢ = Mᵢ⁻¹ mod mᵢ  (via Extended Euclidean)
 *    x = Σ(rᵢ × Mᵢ × yᵢ) mod M
 *
 *  Reference: https://cp-algorithms.com/algebra/chinese-remainder-theorem.html
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
#include <cassert>

using namespace std;
using i64 = long long;
using u128 = __uint128_t;
template<class T> using vec = vector<T>;
using pll = pair<i64, i64>;
#define nl '\n'
#define sz(x) ((int)(x).size())

i64 extgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    i64 x1, y1;
    i64 g = extgcd(b, a % b, x1, y1);
    x = y1; y = x1 - (a / b) * y1;
    return g;
}

i64 mod_inverse(i64 a, i64 m) {
    i64 x, y;
    i64 g = extgcd(a % m, m, x, y);
    assert(g == 1);
    return ((x % m) + m) % m;
}

// ============================================================================
//  📌 CRT for coprime moduli
// ============================================================================

i64 crt_coprime(const vec<i64>& remainders, const vec<i64>& moduli) {
    int k = sz(remainders);
    i64 M = 1;
    for (i64 m : moduli) M *= m;

    i64 x = 0;
    for (int i = 0; i < k; i++) {
        i64 Mi = M / moduli[i];
        i64 yi = mod_inverse(Mi % moduli[i], moduli[i]);
        // Use __int128 to prevent overflow
        x = (x + (i64)((u128)remainders[i] * Mi % M * yi % M)) % M;
    }
    return (x % M + M) % M;
}

// ============================================================================
//  📌 CRT for two congruences (general, possibly non-coprime)
// ============================================================================
//  x ≡ r1 (mod m1)
//  x ≡ r2 (mod m2)
//  Returns {solution, lcm(m1,m2)} or {-1, -1} if no solution
// ============================================================================

pll crt_two(i64 r1, i64 m1, i64 r2, i64 m2) {
    i64 x, y;
    i64 g = extgcd(m1, m2, x, y);

    if ((r2 - r1) % g != 0) return {-1, -1}; // no solution

    i64 lcm = m1 / g * m2;
    i64 diff = (r2 - r1) / g;
    // x ≡ r1 + m1 * (diff * x) mod lcm
    // Be careful with overflow
    i64 t = (i64)((u128)((diff % (m2/g)) * (x % (m2/g)) % (m2/g) + (m2/g)) % (m2/g));
    i64 result = r1 + m1 * t;
    result = ((result % lcm) + lcm) % lcm;

    return {result, lcm};
}

// ============================================================================
//  📌 CRT for multiple congruences (general)
// ============================================================================

pll crt_general(const vec<i64>& remainders, const vec<i64>& moduli) {
    i64 cur_r = remainders[0], cur_m = moduli[0];

    for (int i = 1; i < sz(remainders); i++) {
        auto [new_r, new_m] = crt_two(cur_r, cur_m, remainders[i], moduli[i]);
        if (new_m == -1) return {-1, -1};
        cur_r = new_r;
        cur_m = new_m;
    }
    return {cur_r, cur_m};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Chinese Remainder Theorem ===" << nl << nl;

    // Example 1: x ≡ 2 (mod 3), x ≡ 3 (mod 5), x ≡ 2 (mod 7)
    cout << "--- Example 1 ---" << nl;
    {
        vec<i64> r = {2, 3, 2}, m = {3, 5, 7};
        i64 x = crt_coprime(r, m);
        cout << "x ≡ 2 (mod 3), x ≡ 3 (mod 5), x ≡ 2 (mod 7)" << nl;
        cout << "Solution: x = " << x << " (mod " << 3*5*7 << ")" << nl;
        for (int i = 0; i < 3; i++)
            cout << "  Check: " << x << " mod " << m[i] << " = " << x % m[i] << nl;
    }

    // Example 2: non-coprime
    cout << nl << "--- Example 2 (non-coprime) ---" << nl;
    {
        // x ≡ 3 (mod 6), x ≡ 5 (mod 10)
        auto [r, m] = crt_two(3, 6, 5, 10);
        cout << "x ≡ 3 (mod 6), x ≡ 5 (mod 10)" << nl;
        if (m == -1) cout << "No solution" << nl;
        else {
            cout << "Solution: x = " << r << " (mod " << m << ")" << nl;
            cout << "  Check: " << r << " mod 6 = " << r%6 << ", mod 10 = " << r%10 << nl;
        }
    }

    // Example 3: no solution
    cout << nl << "--- Example 3 (no solution) ---" << nl;
    {
        auto [r, m] = crt_two(1, 4, 2, 6);
        cout << "x ≡ 1 (mod 4), x ≡ 2 (mod 6)" << nl;
        cout << "gcd(4,6) = 2, (2-1)%2 = 1 ≠ 0 → ";
        if (m == -1) cout << "No solution ✓" << nl;
        else cout << "x = " << r << nl;
    }

    return 0;
}

