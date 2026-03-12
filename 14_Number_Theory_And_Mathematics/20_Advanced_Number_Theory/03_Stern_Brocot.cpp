/*
 * ============================================================================
 *  📘 03 — Stern-Brocot Tree & Best Rational Approximation
 * ============================================================================
 *
 *  STERN-BROCOT TREE:
 *    Contains ALL positive rationals in lowest terms, in order.
 *    Between a/b and c/d, the mediant is (a+c)/(b+d).
 *    Start with 0/1 and 1/0 as sentinels.
 *
 *  NAVIGATION:
 *    To find p/q in the tree, use binary search:
 *      - Start with left = 0/1, right = 1/0
 *      - mediant = (a+c)/(b+d)
 *      - If mediant = p/q: found
 *      - If mediant < p/q: go right (left = mediant)
 *      - If mediant > p/q: go left (right = mediant)
 *
 *  APPLICATION:
 *    Best rational approximation of α with denominator ≤ N.
 *
 *  Reference: https://cp-algorithms.com/algebra/stern_brocot_tree_farey_sequences.html
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
//  📌 STERN-BROCOT TREE SEARCH
// ============================================================================
//  Find path from root to fraction p/q.
//  Returns string of 'L' and 'R' moves.
// ============================================================================

string sb_path(i64 p, i64 q) {
    string path;
    i64 la = 0, lb = 1;  // left boundary
    i64 ra = 1, rb = 0;  // right boundary

    while (true) {
        i64 ma = la + ra, mb = lb + rb;  // mediant

        if (ma == p && mb == q) break;

        if (p * mb > ma * q) {
            // target > mediant: go right
            path += 'R';
            la = ma; lb = mb;
        } else {
            // target < mediant: go left
            path += 'L';
            ra = ma; rb = mb;
        }
    }
    return path;
}

// ============================================================================
//  📌 BEST RATIONAL APPROXIMATION
// ============================================================================
//  Find fraction a/b closest to p/q with b ≤ max_den.
//  Uses the Stern-Brocot tree structure.
// ============================================================================

pll best_rational_approx(i64 p, i64 q, i64 max_den) {
    // Use continued fraction approach (equivalent to Stern-Brocot)
    i64 a = p, b = q;

    // Compute continued fraction
    vec<i64> cf;
    while (b != 0) {
        cf.pb(a / b);
        i64 r = a % b;
        a = b; b = r;
    }

    // Compute convergents and semiconvergents
    pll best = {0, 1};
    double best_err = 1e18;
    double target = (double)p / q;

    i64 p_prev = 1, p_curr = cf[0];
    i64 q_prev = 0, q_curr = 1;

    auto check = [&](i64 pn, i64 qn) {
        if (qn > max_den || qn <= 0) return;
        double err = abs((double)pn / qn - target);
        if (err < best_err) {
            best_err = err;
            best = {pn, qn};
        }
    };

    check(p_curr, q_curr);

    for (int i = 1; i < sz(cf); i++) {
        // Full convergent
        i64 p_next = cf[i] * p_curr + p_prev;
        i64 q_next = cf[i] * q_curr + q_prev;
        check(p_next, q_next);

        // Semiconvergents: try largest k such that k*q_curr + q_prev ≤ max_den
        if (q_next > max_den) {
            i64 k = (max_den - q_prev) / q_curr;
            if (k > 0) check(k * p_curr + p_prev, k * q_curr + q_prev);
        }

        p_prev = p_curr; p_curr = p_next;
        q_prev = q_curr; q_curr = q_next;
    }

    return best;
}

// ============================================================================
//  📌 FAREY SEQUENCE F_n
// ============================================================================

vec<pll> farey(int n) {
    vec<pll> seq;
    seq.pb({0, 1});
    i64 a = 0, b = 1, c = 1, d = n;
    while (c <= n) {
        i64 k = (n + b) / d;
        i64 na = c, nb = d;
        c = k * c - a;
        d = k * d - b;
        a = na; b = nb;
        seq.pb({a, b});
    }
    return seq;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Stern-Brocot Tree ===" << nl << nl;

    // Path to some fractions
    cout << "--- Paths in Stern-Brocot Tree ---" << nl;
    vec<pll> fracs = {{1,2},{1,3},{2,3},{3,5},{5,8},{7,11}};
    for (auto [p, q] : fracs) {
        cout << p << "/" << q << ": " << sb_path(p, q) << nl;
    }

    // Best approximation of pi ≈ 355/113
    cout << nl << "--- Best Approximation of 355/113 ---" << nl;
    for (int max_den : {5, 10, 50, 100, 200}) {
        auto [p, q] = best_rational_approx(355, 113, max_den);
        cout << "den ≤ " << max_den << ": " << p << "/" << q
             << " ≈ " << (double)p/q << nl;
    }

    // Farey sequence
    cout << nl << "--- Farey Sequence F_7 ---" << nl;
    auto f7 = farey(7);
    for (auto [a, b] : f7) cout << a << "/" << b << " ";
    cout << nl;

    // Verify Farey property: consecutive a/b, c/d → bc - ad = 1
    cout << nl << "--- Verify Farey Property: bc - ad = 1 ---" << nl;
    bool ok = true;
    for (int i = 0; i + 1 < sz(f7); i++) {
        auto [a, b] = f7[i];
        auto [c, d] = f7[i+1];
        if (b * c - a * d != 1) ok = false;
    }
    cout << (ok ? "All consecutive pairs satisfy bc-ad=1 ✓" : "FAILED") << nl;

    return 0;
}

