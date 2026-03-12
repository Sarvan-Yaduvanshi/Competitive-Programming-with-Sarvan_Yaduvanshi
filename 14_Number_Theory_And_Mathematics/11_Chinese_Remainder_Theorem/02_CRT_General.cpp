/*
 * ============================================================================
 *  📘 02 — CRT for General (Non-Coprime) Moduli
 * ============================================================================
 *
 *  For x ≡ r₁ (mod m₁) and x ≡ r₂ (mod m₂):
 *    Solution exists iff gcd(m₁, m₂) | (r₂ - r₁)
 *    If so: x ≡ r₁ + m₁ × t (mod lcm(m₁, m₂))
 *    where t satisfies m₁ × t ≡ (r₂ - r₁) (mod m₂)
 *
 *  For multiple congruences: process pairs iteratively.
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

i64 safe_mod(i64 a, i64 m) { return ((a % m) + m) % m; }

// ============================================================================
//  📌 CRT for TWO congruences (handles non-coprime)
// ============================================================================
//  x ≡ r1 (mod m1)
//  x ≡ r2 (mod m2)
//  Returns {solution mod lcm, lcm} or {-1, -1} if impossible
// ============================================================================

pll crt2(i64 r1, i64 m1, i64 r2, i64 m2) {
    i64 x, y;
    i64 g = extgcd(m1, m2, x, y);

    if ((r2 - r1) % g != 0) return {-1, -1};

    i64 lcm = m1 / g * m2;
    i64 diff = (r2 - r1) / g;
    i64 m2g = m2 / g;

    // t = diff * x mod (m2/g)
    i64 t = safe_mod((i64)((u128)safe_mod(diff, m2g) * safe_mod(x, m2g) % m2g), m2g);

    i64 result = safe_mod(r1 + (i64)((u128)m1 % lcm * t % lcm), lcm);
    return {result, lcm};
}

// ============================================================================
//  📌 CRT for MULTIPLE congruences (general)
// ============================================================================

pll crt_general(const vec<i64>& r, const vec<i64>& m) {
    i64 cur_r = r[0], cur_m = m[0];
    for (int i = 1; i < sz(r); i++) {
        auto [nr, nm] = crt2(cur_r, cur_m, r[i], m[i]);
        if (nm == -1) return {-1, -1};
        cur_r = nr; cur_m = nm;
    }
    return {cur_r, cur_m};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== General CRT (Non-Coprime) ===" << nl << nl;

    // Example 1: coprime (should work normally)
    cout << "--- Coprime: x≡2(mod 3), x≡3(mod 5) ---" << nl;
    {
        auto [r, m] = crt2(2, 3, 3, 5);
        cout << "x = " << r << " (mod " << m << ")" << nl;
        cout << "Check: " << r%3 << ", " << r%5 << nl;
    }

    // Example 2: non-coprime, solution exists
    cout << nl << "--- Non-coprime: x≡3(mod 6), x≡5(mod 10) ---" << nl;
    {
        // gcd(6,10) = 2, (5-3) = 2, 2 | 2 → solution exists
        auto [r, m] = crt2(3, 6, 5, 10);
        if (m == -1) cout << "No solution" << nl;
        else {
            cout << "x = " << r << " (mod " << m << ")" << nl;
            cout << "Check: " << r%6 << ", " << r%10 << nl;
        }
    }

    // Example 3: no solution
    cout << nl << "--- No solution: x≡1(mod 4), x≡2(mod 6) ---" << nl;
    {
        // gcd(4,6) = 2, (2-1) = 1, 2 ∤ 1 → no solution
        auto [r, m] = crt2(1, 4, 2, 6);
        cout << (m == -1 ? "No solution ✓" : "ERROR") << nl;
    }

    // Example 4: multiple non-coprime
    cout << nl << "--- Multiple: x≡1(mod 6), x≡7(mod 10), x≡13(mod 15) ---" << nl;
    {
        auto [r, m] = crt_general({1, 7, 13}, {6, 10, 15});
        if (m == -1) cout << "No solution" << nl;
        else {
            cout << "x = " << r << " (mod " << m << ")" << nl;
            cout << "Check: " << r%6 << ", " << r%10 << ", " << r%15 << nl;
        }
    }

    return 0;
}

