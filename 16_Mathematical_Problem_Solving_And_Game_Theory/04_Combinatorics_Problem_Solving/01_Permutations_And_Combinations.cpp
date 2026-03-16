/*
 * ============================================================
 *  Topic   : Permutations, Combinations, Stars and Bars
 *  Pattern : Core counting techniques with modular arithmetic
 *
 *  Problems:
 *    - CSES Distributing Apples (1716)
 *    - CSES Binomial Coefficients (1079)
 *    - LeetCode 62 — Unique Paths
 *
 *  Complexity: O(n) precomputation, O(1) per query
 * ============================================================
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

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD) {
    i64 res = 1; base %= mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

// ────────────────────────────────────────────
// FACTORIAL PRECOMPUTATION
// ────────────────────────────────────────────
const int MAXN = 2'000'001;
i64 fact[MAXN], ifact[MAXN];

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++)
        fact[i] = fact[i - 1] * i % MOD;
    ifact[MAXN - 1] = modpow(fact[MAXN - 1], MOD - 2, MOD);
    for (int i = MAXN - 2; i >= 0; i--)
        ifact[i] = ifact[i + 1] * (i + 1) % MOD;
}

// nCr — O(1) per query after precomputation
i64 C(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] % MOD * ifact[r] % MOD * ifact[n - r] % MOD;
}

// nPr — O(1) per query
i64 P(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] % MOD * ifact[n - r] % MOD;
}

/*
 * ============================================================
 *  STARS AND BARS
 * ============================================================
 *
 *  Problem: How many non-negative integer solutions to
 *           x1 + x2 + ... + xk = n ?
 *
 *  Answer: C(n + k - 1, k - 1)
 *
 *  With lower bounds xi >= ai:
 *    Substitute yi = xi - ai, then y1 + ... + yk = n - sum(ai)
 *    Answer: C(n - sum(ai) + k - 1, k - 1)
 *
 *  With upper bounds xi <= bi:
 *    Use inclusion-exclusion
 * ============================================================
 */

// Stars and bars: n identical into k distinct, each >= 0
i64 starsAndBars(int n, int k) {
    return C(n + k - 1, k - 1);
}

/*
 * ============================================================
 *  GRID PATH COUNTING
 * ============================================================
 *
 *  From (0,0) to (r,c) going only right and down:
 *  Total steps = r + c, choose r of them to be "down"
 *  Answer: C(r + c, r)
 * ============================================================
 */

i64 gridPaths(int rows, int cols) {
    return C(rows + cols, rows);
}

/*
 * ============================================================
 *  MULTINOMIAL COEFFICIENT
 * ============================================================
 *
 *  n! / (k1! * k2! * ... * km!)
 *  Number of ways to arrange n items where ki are identical
 * ============================================================
 */

i64 multinomial(int n, vec<int>& groups) {
    i64 res = fact[n];
    for (int k : groups) {
        res = res % MOD * ifact[k] % MOD;
    }
    return res;
}

void solve() {
    int n, k;
    cin >> n >> k;

    // CSES Distributing Apples: n apples into k children
    // Stars and bars: C(n + k - 1, k - 1)
    cout << starsAndBars(n, k) << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    precompute();

    int TC = 1;
    cin >> TC;
    while (TC--) solve();

    return 0;
}

