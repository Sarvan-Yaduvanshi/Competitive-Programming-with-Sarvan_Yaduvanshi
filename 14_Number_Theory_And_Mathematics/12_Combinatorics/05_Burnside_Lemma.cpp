/*
 * ============================================================================
 *  📘 05 — Burnside's Lemma (Counting Under Symmetry)
 * ============================================================================
 *
 *  THEOREM (Burnside's Lemma / Cauchy-Frobenius):
 *    Number of distinct objects under a group of symmetries G:
 *
 *      |orbits| = (1/|G|) × Σ_{g ∈ G} |Fix(g)|
 *
 *    where Fix(g) = number of objects fixed by symmetry g.
 *
 *  PROOF SKETCH:
 *    Count pairs (g, x) where g fixes x, in two ways:
 *    Σ_g |Fix(g)| = Σ_x |Stab(x)|
 *    By orbit-stabilizer: |Stab(x)| = |G|/|Orb(x)|
 *    So Σ_x |G|/|Orb(x)| = |G| × (number of orbits). ∎
 *
 *  APPLICATION 1: COUNTING NECKLACES
 *    n beads, k colors. Rotational symmetry group = Z_n.
 *    Rotation by r positions fixes colorings where period divides gcd(r, n).
 *    Fix(rotation by r) = k^gcd(r, n)
 *    Answer = (1/n) × Σ_{r=0}^{n-1} k^gcd(r, n)
 *           = (1/n) × Σ_{d|n} φ(n/d) × k^d
 *
 *  APPLICATION 2: COUNTING GRIDS
 *    n×n grid with k colors, symmetry group of the square (8 elements).
 *
 *  CSES PROBLEMS:
 *    - Counting Necklaces: https://cses.fi/problemset/task/2209
 *    - Counting Grids: https://cses.fi/problemset/task/2210
 *
 *  Reference: https://cp-algorithms.com/combinatorics/burnside.html
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
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

template<class T>
void read(vec<T> &v) { for (auto &x : v) cin >> x; }
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

inline i64 gcd(i64 a, i64 b) { return std::gcd(a, b); }
inline i64 lcm(i64 a, i64 b) { return (a / std::gcd(a, b)) * b; }

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD) {
    i64 res = 1; base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// ============================================================================
//  📌 EULER TOTIENT
// ============================================================================
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

// ============================================================================
//  📌 COUNTING NECKLACES (Burnside + rotation group)
// ============================================================================
//  n beads, k colors. Rotations only (no reflections).
//  Answer = (1/n) × Σ_{d|n} φ(n/d) × k^d  (mod p)
//
//  DRY RUN: n=4, k=2
//    d|4: {1, 2, 4}
//    d=1: φ(4) × 2^1 = 2 × 2 = 4
//    d=2: φ(2) × 2^2 = 1 × 4 = 4
//    d=4: φ(1) × 2^4 = 1 × 16 = 16
//    Sum = 24, Answer = 24/4 = 6
//    Necklaces: {AAAA, AAAB, AABB, ABAB, ABBB, BBBB} → 6 ✓
// ============================================================================

i64 count_necklaces(i64 n, i64 k) {
    i64 ans = 0;
    // Iterate over divisors d of n
    for (i64 d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            // d divides n
            ans = (ans + euler_phi(n / d) % MOD * modpow(k, d) % MOD) % MOD;
            if (d != n / d) {
                i64 d2 = n / d;
                ans = (ans + euler_phi(n / d2) % MOD * modpow(k, d2) % MOD) % MOD;
            }
        }
    }
    // Divide by n (multiply by modular inverse)
    ans = ans % MOD * modpow(n, MOD - 2) % MOD;
    return ans;
}

// ============================================================================
//  📌 COUNTING GRIDS (Burnside + square symmetry group, 4 rotations)
// ============================================================================
//  n×n grid, k colors. 4 rotational symmetries:
//    0°:   all n² cells free → k^(n²) fixed
//    90°:  cells in orbits of 4 → k^ceil(n²/4) (need careful counting)
//    180°: cells in orbits of 2 → k^ceil(n²/2)
//    270°: same as 90°
//
//  Answer = (1/4)(k^(n²) + 2×k^f(90°) + k^f(180°))
// ============================================================================

i64 count_grids(i64 n, i64 k) {
    i64 total = 0;

    // 0° rotation: all cells free
    total = (total + modpow(k, n * n % (MOD - 1))) % MOD;

    // 180° rotation: pairs (i,j) ↔ (n-1-i, n-1-j)
    i64 fixed_180;
    if (n % 2 == 0)
        fixed_180 = n * n / 2;
    else
        fixed_180 = (n * n - 1) / 2 + 1;  // center cell fixed
    total = (total + modpow(k, fixed_180)) % MOD;

    // 90° and 270° rotations: orbits of size 4
    i64 fixed_90;
    if (n % 2 == 0)
        fixed_90 = n * n / 4;
    else
        fixed_90 = (n * n - 1) / 4 + 1;  // center cell
    total = (total + 2 * modpow(k, fixed_90)) % MOD;

    // Divide by 4
    total = total % MOD * modpow(4, MOD - 2) % MOD;
    return total;
}

void solve() {
    i64 n, k;
    cin >> n >> k;
    cout << count_necklaces(n, k) << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int TC = 1;
    // cin >> TC;
    while (TC--) solve();

    return 0;
}

