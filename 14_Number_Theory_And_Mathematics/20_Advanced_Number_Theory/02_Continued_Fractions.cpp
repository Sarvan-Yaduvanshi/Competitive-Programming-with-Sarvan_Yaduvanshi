/*
 * ============================================================================
 *  📘 02 — Continued Fractions
 * ============================================================================
 *
 *  DEFINITION: α = a₀ + 1/(a₁ + 1/(a₂ + ...)) = [a₀; a₁, a₂, ...]
 *
 *  CONVERGENTS p_k/q_k:
 *    p_{-1} = 1, p_0 = a_0
 *    q_{-1} = 0, q_0 = 1
 *    p_k = a_k × p_{k-1} + p_{k-2}
 *    q_k = a_k × q_{k-1} + q_{k-2}
 *
 *  PROPERTY: |α - p_k/q_k| < 1/(q_k × q_{k+1})
 *    (Best rational approximation with denominator ≤ q_k)
 *
 *  RATIONAL → finite CF:  Essentially Euclidean algorithm!
 *    355/113 → 355 = 3×113 + 16 → 113 = 7×16 + 1 → CF = [3; 7, 16]
 *
 *  Reference: https://cp-algorithms.com/algebra/continued-fractions.html
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
#include <cassert>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
using pll = pair<i64, i64>;
#define nl '\n'
#define sz(x) ((int)(x).size())
#define pb push_back

// ============================================================================
//  📌 RATIONAL TO CONTINUED FRACTION
// ============================================================================

vec<i64> to_cf(i64 p, i64 q) {
    vec<i64> cf;
    while (q != 0) {
        cf.pb(p / q);
        i64 r = p % q;
        p = q; q = r;
    }
    return cf;
}

// ============================================================================
//  📌 CONVERGENTS from CF
// ============================================================================

vec<pll> convergents(const vec<i64>& cf) {
    vec<pll> conv;
    i64 p_prev = 1, p_curr = cf[0];
    i64 q_prev = 0, q_curr = 1;
    conv.pb({p_curr, q_curr});

    for (int i = 1; i < sz(cf); i++) {
        i64 p_next = cf[i] * p_curr + p_prev;
        i64 q_next = cf[i] * q_curr + q_prev;
        conv.pb({p_next, q_next});
        p_prev = p_curr; p_curr = p_next;
        q_prev = q_curr; q_curr = q_next;
    }
    return conv;
}

// ============================================================================
//  📌 BEST RATIONAL APPROXIMATION with denominator ≤ max_den
// ============================================================================

pll best_approx(i64 p, i64 q, i64 max_den) {
    auto cf = to_cf(p, q);
    auto conv = convergents(cf);

    pll best = {0, 1};
    for (auto [pn, qn] : conv) {
        if (qn > max_den) break;
        best = {pn, qn};
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Continued Fractions ===" << nl << nl;

    // Example: π ≈ 355/113
    cout << "--- CF of 355/113 ---" << nl;
    auto cf = to_cf(355, 113);
    cout << "[";
    for (int i = 0; i < sz(cf); i++) {
        if (i == 1) cout << "; ";
        else if (i > 1) cout << ", ";
        cout << cf[i];
    }
    cout << "]" << nl;

    auto conv = convergents(cf);
    cout << "Convergents:" << nl;
    for (auto [p, q] : conv) {
        cout << "  " << p << "/" << q << " ≈ " << (double)p/q << nl;
    }

    // CF of rational numbers
    cout << nl << "--- Various CFs ---" << nl;
    vec<pll> fracs = {{22,7}, {355,113}, {1000000007,998244353}, {17,5}};
    for (auto [p, q] : fracs) {
        auto c = to_cf(p, q);
        cout << p << "/" << q << " = [";
        for (int i = 0; i < sz(c); i++) {
            if (i == 1) cout << "; ";
            else if (i > 1) cout << ", ";
            cout << c[i];
        }
        cout << "]" << nl;
    }

    // Best approximation
    cout << nl << "--- Best approx of 355/113 with den ≤ 50 ---" << nl;
    auto [bp, bq] = best_approx(355, 113, 50);
    cout << bp << "/" << bq << " ≈ " << (double)bp/bq << nl;
    cout << "Actual: " << 355.0/113 << nl;

    return 0;
}

