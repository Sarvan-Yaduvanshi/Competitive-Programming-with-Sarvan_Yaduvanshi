/*
 * ============================================================================
 *  📘 04 — Lifting the Exponent Lemma (LTE)
 * ============================================================================
 *
 *  LTE gives the exact power of a prime p dividing (a^n ± b^n).
 *  Notation: v_p(x) = largest power of p dividing x.
 *
 *  ═══════════════════════════════════════════════════════════════
 *  THEOREM 1 (LTE for odd prime p, a^n - b^n):
 *    If p is odd, p | (a - b), p ∤ a, p ∤ b:
 *      v_p(a^n - b^n) = v_p(a - b) + v_p(n)
 *
 *  THEOREM 2 (LTE for odd prime p, a^n + b^n):
 *    If p is odd, p | (a + b), p ∤ a, p ∤ b, n is odd:
 *      v_p(a^n + b^n) = v_p(a + b) + v_p(n)
 *
 *  THEOREM 3 (LTE for p = 2, a^n - b^n):
 *    If 2 | (a - b), a,b odd, n even:
 *      v_2(a^n - b^n) = v_2(a - b) + v_2(a + b) + v_2(n) - 1
 *    If n odd:
 *      v_2(a^n - b^n) = v_2(a - b)
 *
 *  THEOREM 4 (LTE for p = 2, a^n + b^n):
 *    If a,b odd, n odd (but 2 | a+b implicitly since both odd):
 *      v_2(a^n + b^n) = v_2(a + b)
 *  ═══════════════════════════════════════════════════════════════
 *
 *  PROOF IDEA (odd p, a^n - b^n):
 *    a^n - b^n = (a-b)(a^{n-1} + a^{n-2}b + ... + b^{n-1})
 *    Let S = Σ a^{n-1-i}b^i.  Modulo p: since a ≡ b, S ≡ n × a^{n-1}.
 *    So v_p(S) = v_p(n) (since p ∤ a).
 *    Hence v_p(a^n - b^n) = v_p(a-b) + v_p(n). ∎
 *
 *  DRY RUN: v_3(7^12 - 1^12) = ?
 *    a=7, b=1, n=12, p=3
 *    p | (a-b)? 3 | 6 ✓, p ∤ a ✓, p ∤ b ✓
 *    v_3(7-1) = v_3(6) = 1
 *    v_3(12) = 1
 *    v_3(7^12 - 1) = 1 + 1 = 2
 *    Check: 7^12 = 13841287201, 7^12-1 = 13841287200
 *    13841287200 / 9 = 1537920800  (divisible by 9 = 3²)
 *    13841287200 / 27 = 512640... not integer → v_3 = 2 ✓
 *
 *  APPLICATIONS:
 *    - Finding exact prime power in factorial-like expressions
 *    - Many CF problems about divisibility of a^n - b^n
 *    - Useful when combined with order / CRT arguments
 *
 *  Reference: https://cp-algorithms.com/algebra/lifting-the-exponent.html
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
using pii = pair<int, int>;
using pll = pair<i64, i64>;

constexpr i64 MOD   = 1'000'000'007LL;

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
//  📌 v_p(n) — p-adic valuation (largest power of p dividing n)
// ============================================================================

i64 v_p(i64 n, i64 p) {
    if (n == 0) return 1e18; // infinity
    i64 cnt = 0;
    while (n % p == 0) { n /= p; cnt++; }
    return cnt;
}

// ============================================================================
//  📌 LTE for ODD prime p: v_p(a^n - b^n)
// ============================================================================
//  Conditions: p odd, p | (a - b), p ∤ a, p ∤ b
//  Result: v_p(a-b) + v_p(n)
// ============================================================================

i64 lte_minus_odd(i64 a, i64 b, i64 n, i64 p) {
    assert(p > 2);
    assert((a - b) % p == 0);
    assert(a % p != 0 && b % p != 0);
    return v_p(a - b, p) + v_p(n, p);
}

// ============================================================================
//  📌 LTE for ODD prime p: v_p(a^n + b^n)
// ============================================================================
//  Conditions: p odd, p | (a + b), p ∤ a, p ∤ b, n ODD
//  Result: v_p(a+b) + v_p(n)
// ============================================================================

i64 lte_plus_odd(i64 a, i64 b, i64 n, i64 p) {
    assert(p > 2);
    assert((a + b) % p == 0);
    assert(a % p != 0 && b % p != 0);
    assert(n % 2 == 1);
    return v_p(a + b, p) + v_p(n, p);
}

// ============================================================================
//  📌 LTE for p = 2: v_2(a^n - b^n)
// ============================================================================

i64 lte_minus_2(i64 a, i64 b, i64 n) {
    assert(a % 2 != 0 && b % 2 != 0);  // both odd
    if (n % 2 == 1) {
        return v_p(a - b, 2);
    } else {
        // n even
        return v_p(a - b, 2) + v_p(a + b, 2) + v_p(n, 2) - 1;
    }
}

// ============================================================================
//  📌 LTE for p = 2: v_2(a^n + b^n), n odd
// ============================================================================

i64 lte_plus_2(i64 a, i64 b, i64 n) {
    assert(a % 2 != 0 && b % 2 != 0);
    assert(n % 2 == 1);
    return v_p(a + b, 2);
}

// ============================================================================
//  📌 BRUTE FORCE CHECK (for verification)
// ============================================================================

i64 brute_vp_power(i64 a, i64 b, i64 n, i64 p, bool is_plus) {
    // Compute a^n ± b^n mod p^k for increasing k
    // Use modpow with large mod
    // For small values, direct computation
    if (n <= 40 && a <= 15 && b <= 15) {
        __int128 val_a = 1, val_b = 1;
        __int128 A = a, B = b;
        for (int i = 0; i < n; i++) { val_a *= A; val_b *= B; }
        __int128 result = is_plus ? val_a + val_b : val_a - val_b;
        if (result < 0) result = -result;
        i64 cnt = 0;
        while (result % p == 0 && result > 0) { result /= p; cnt++; }
        return cnt;
    }
    return -1;  // too large for brute force
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Lifting the Exponent Lemma ===" << nl << nl;

    // Test 1: v_3(7^12 - 1^12)
    cout << "--- v_3(7^12 - 1^12) ---" << nl;
    {
        i64 a = 7, b = 1, n = 12, p = 3;
        i64 lte = lte_minus_odd(a, b, n, p);
        i64 brute = brute_vp_power(a, b, n, p, false);
        cout << "LTE: " << lte << ", Brute: " << brute
             << (lte == brute ? " ✓" : " ✗") << nl;
    }

    // Test 2: v_5(3^100 - 2^100)
    cout << nl << "--- v_5(3^100 - 2^100) ---" << nl;
    {
        i64 a = 3, b = 2, n = 100, p = 5;
        // a - b = 1, 5 ∤ 1 → condition not met!
        // Try a different one: v_5(7^100 - 2^100)
        // 7 - 2 = 5, 5 | 5 ✓
        a = 7; b = 2;
        i64 lte = lte_minus_odd(a, b, n, p);
        cout << "v_5(7^100 - 2^100) = " << lte << nl;
        cout << "v_5(7-2) = " << v_p(5, 5) << ", v_5(100) = " << v_p(100, 5) << nl;
    }

    // Test 3: v_2(7^6 - 1^6) for p=2
    cout << nl << "--- v_2(7^6 - 1^6) ---" << nl;
    {
        i64 a = 7, b = 1, n = 6;
        i64 lte = lte_minus_2(a, b, n);
        i64 brute = brute_vp_power(a, b, n, 2, false);
        cout << "LTE: " << lte << ", Brute: " << brute
             << (lte == brute ? " ✓" : " ✗") << nl;
        cout << "v_2(7-1)=" << v_p(6,2) << ", v_2(7+1)=" << v_p(8,2)
             << ", v_2(6)=" << v_p(6,2) << nl;
    }

    // Test 4: v_3(a^n + b^n)
    cout << nl << "--- v_3(2^9 + 1^9) ---" << nl;
    {
        i64 a = 2, b = 1, n = 9, p = 3;
        // a + b = 3, 3 | 3 ✓, n=9 odd ✓
        i64 lte = lte_plus_odd(a, b, n, p);
        i64 brute = brute_vp_power(a, b, n, p, true);
        cout << "LTE: " << lte << ", Brute: " << brute
             << (lte == brute ? " ✓" : " ✗") << nl;
    }

    // Multiple verification tests
    cout << nl << "--- Batch Verification (odd p, minus) ---" << nl;
    int pass = 0, fail = 0;
    for (i64 p : {3LL, 5LL, 7LL}) {
        for (i64 a = 2; a <= 20; a++) {
            if (a % p == 0) continue;
            for (i64 b = 1; b < a; b++) {
                if (b % p == 0 || (a - b) % p != 0) continue;
                for (i64 n = 1; n <= 30; n++) {
                    i64 lte = lte_minus_odd(a, b, n, p);
                    i64 brute = brute_vp_power(a, b, n, p, false);
                    if (brute >= 0) {
                        if (lte == brute) pass++;
                        else { fail++; cout << "FAIL: a=" << a << " b=" << b << " n=" << n << " p=" << p << nl; }
                    }
                }
            }
        }
    }
    cout << "Passed: " << pass << ", Failed: " << fail << nl;

    return 0;
}

