/*
 * ============================================================================
 *  📘 01 — Baby-Step Giant-Step (BSGS)
 * ============================================================================
 *
 *  PROBLEM: Find smallest x ≥ 0 such that a^x ≡ b (mod m)
 *
 *  ALGORITHM:
 *    k = ceil(√m)
 *    Write x = i*k - j, 0 ≤ j < k
 *    Then a^(ik) ≡ b × a^j (mod m)
 *
 *    Baby steps: compute b × a^j for j = 0..k-1, store in hash map
 *    Giant steps: compute (a^k)^i for i = 1..k, check hash map
 *
 *  TIME: O(√m)   SPACE: O(√m)
 *
 *  REQUIREMENT: gcd(a, m) = 1 (for basic BSGS)
 *  For general case, use Extended BSGS.
 *
 *  Reference: https://cp-algorithms.com/algebra/discrete-log.html
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
#include <unordered_map>
#include <cmath>
#include <numeric>
#include <cassert>

using namespace std;
using i64 = long long;
using u128 = __uint128_t;
template<class T> using vec = vector<T>;
#define nl '\n'

i64 mulmod(i64 a, i64 b, i64 m) { return (u128)a * b % m; }

i64 powmod(i64 base, i64 exp, i64 mod) {
    i64 res = 1; base %= mod;
    while (exp > 0) {
        if (exp & 1) res = mulmod(res, base, mod);
        base = mulmod(base, base, mod);
        exp >>= 1;
    }
    return res;
}

// ============================================================================
//  📌 BABY-STEP GIANT-STEP (Basic, requires gcd(a, m) = 1)
// ============================================================================

i64 bsgs(i64 a, i64 b, i64 m) {
    a %= m; b %= m;
    if (b == 1 % m) return 0;

    i64 k = (i64)ceil(sqrt((double)m));

    // Baby steps: store b * a^j for j = 0..k-1
    unordered_map<i64, i64> table;
    i64 cur = b;
    for (i64 j = 0; j < k; j++) {
        table[cur] = j;
        cur = mulmod(cur, a, m);
    }

    // Giant steps: check a^(ik) for i = 1..k
    i64 giant = powmod(a, k, m);  // a^k mod m
    cur = giant;
    for (i64 i = 1; i <= k; i++) {
        if (table.count(cur)) {
            i64 x = i * k - table[cur];
            return x;  // smallest non-negative
        }
        cur = mulmod(cur, giant, m);
    }

    return -1;  // no solution
}

// ============================================================================
//  📌 EXTENDED BSGS (handles gcd(a, m) > 1)
// ============================================================================

i64 bsgs_extended(i64 a, i64 b, i64 m) {
    a %= m; b %= m;
    if (m == 1) return 0;
    if (b == 1 % m) return 0;

    // Phase 1: reduce until gcd(a, m) = 1
    i64 extra = 0;  // a^extra × ... ≡ b (mod m)
    i64 mult = 1;   // coefficient from extracted factors

    while (true) {
        i64 g = __gcd(a, m);
        if (g == 1) break;
        if (b % g != 0) return -1;  // no solution

        m /= g;
        b /= g;
        mult = mulmod(mult, a / g, m);
        extra++;

        if (mult == b) return extra;
    }

    // Phase 2: standard BSGS for a^x ≡ b/mult (mod m)
    // Need: mult × a^x ≡ b (mod m) → a^x ≡ b × mult^(-1) (mod m)
    i64 inv_mult = powmod(mult, m - 2, m);  // Might not work if m not prime
    // Use extgcd for general case
    // For simplicity, use BSGS searching for mult * a^x ≡ b

    i64 k = (i64)ceil(sqrt((double)m));

    unordered_map<i64, i64> table;
    i64 cur = b;
    for (i64 j = 0; j < k; j++) {
        table[cur] = j;
        cur = mulmod(cur, a, m);
    }

    i64 giant = powmod(a, k, m);
    cur = mulmod(mult, giant, m);  // mult × a^k
    for (i64 i = 1; i <= k; i++) {
        if (table.count(cur)) {
            return i * k - table[cur] + extra;
        }
        cur = mulmod(cur, giant, m);
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Baby-Step Giant-Step ===" << nl << nl;

    // Example 1: 3^x ≡ 13 (mod 17)
    cout << "--- 3^x ≡ 13 (mod 17) ---" << nl;
    i64 x = bsgs(3, 13, 17);
    cout << "x = " << x << nl;
    cout << "Check: 3^" << x << " mod 17 = " << powmod(3, x, 17) << nl << nl;

    // Example 2: 2^x ≡ 3 (mod 7)
    cout << "--- 2^x ≡ 3 (mod 7) ---" << nl;
    x = bsgs(2, 3, 7);
    if (x == -1) cout << "No solution" << nl;
    else {
        cout << "x = " << x << nl;
        cout << "Check: 2^" << x << " mod 7 = " << powmod(2, x, 7) << nl;
    }
    cout << nl;

    // Example 3: Various
    vec<tuple<i64,i64,i64>> tests = {
        {2, 1, 1000000007},
        {3, 7, 11},
        {5, 3, 13},
        {2, 64, 1000000007},
    };
    for (auto [a, b, m] : tests) {
        x = bsgs(a, b, m);
        cout << a << "^x ≡ " << b << " (mod " << m << "): x = " << x;
        if (x != -1) cout << "  [check: " << powmod(a, x, m) << "]";
        cout << nl;
    }

    return 0;
}

