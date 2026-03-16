/*
 * ============================================================
 *  Topic   : Greedy Math & Inequality-Based Optimization
 *  Pattern : AM-GM, convexity, ternary search for optimization
 *
 *  Problems:
 *    - LeetCode 343 — Integer Break (AM-GM)
 *    - Ternary search on unimodal functions
 *    - Minimize sum of squares with fixed sum
 *
 *  Complexity: O(n) or O(n log n) typically
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
#include <functional>

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

/*
 * ============================================================
 *  INTEGER BREAK — LeetCode 343
 * ============================================================
 *
 *  Split integer n into at least 2 positive integers to
 *  maximize their product.
 *
 *  BY AM-GM:
 *  - Optimal real split: each piece = e ≈ 2.718
 *  - Closest integer: 3
 *  - So use as many 3s as possible
 *  - Exception: if remainder is 1, replace last 3+1 with 2+2
 *    (because 2×2 > 3×1)
 *
 *  RESULT:
 *    n=2: 1
 *    n=3: 2
 *    n%3==0: 3^(n/3)
 *    n%3==1: 4 × 3^((n-4)/3)
 *    n%3==2: 2 × 3^((n-2)/3)
 * ============================================================
 */

int integerBreak(int n) {
    if (n == 2) return 1;
    if (n == 3) return 2;

    int threes = n / 3;
    int rem = n % 3;

    if (rem == 0) return (int)pow(3, threes);
    if (rem == 1) return (int)pow(3, threes - 1) * 4;
    return (int)pow(3, threes) * 2;  // rem == 2
}

// Modular version for large n
i64 integerBreakMod(i64 n) {
    if (n == 2) return 1;
    if (n == 3) return 2;

    i64 threes = n / 3;
    int rem = n % 3;

    if (rem == 0) return modpow(3, threes);
    if (rem == 1) return modpow(3, threes - 1) * 4 % MOD;
    return modpow(3, threes) * 2 % MOD;
}

/*
 * ============================================================
 *  TERNARY SEARCH — Find min/max of unimodal function
 * ============================================================
 *
 *  A function is unimodal if it has a single peak (or valley).
 *  Ternary search finds the extremum in O(log((hi-lo)/eps)) iterations.
 *
 *  For MINIMUM of a convex function f on [lo, hi]:
 *    Evaluate at m1 = lo + (hi-lo)/3 and m2 = hi - (hi-lo)/3
 *    If f(m1) < f(m2): minimum is in [lo, m2]
 *    Else: minimum is in [m1, hi]
 * ============================================================
 */

// Continuous ternary search (for real-valued functions)
ld ternarySearchMin(ld lo, ld hi, function<ld(ld)> f, int iterations = 200) {
    for (int i = 0; i < iterations; i++) {
        ld m1 = lo + (hi - lo) / 3;
        ld m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) hi = m2;
        else lo = m1;
    }
    return (lo + hi) / 2;
}

// Integer ternary search
i64 ternarySearchMinInt(i64 lo, i64 hi, function<i64(i64)> f) {
    while (hi - lo > 2) {
        i64 m1 = lo + (hi - lo) / 3;
        i64 m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) hi = m2;
        else lo = m1;
    }
    i64 best = lo;
    for (i64 x = lo; x <= hi; x++) {
        if (f(x) < f(best)) best = x;
    }
    return best;
}

/*
 * ============================================================
 *  MINIMIZE SUM OF |xi - c| → c = MEDIAN
 *  MINIMIZE SUM OF (xi - c)² → c = MEAN
 * ============================================================
 */

// Optimal c to minimize Σ|xi - c| is the median
ld minimizeAbsoluteDeviations(vec<int>& a) {
    sort(all(a));
    int n = sz(a);
    ld median = (n % 2 == 1) ? a[n/2] : (a[n/2-1] + a[n/2]) / 2.0;

    ld sum = 0;
    for (int x : a) sum += abs(x - median);
    return sum;
}

// Optimal c to minimize Σ(xi - c)² is the mean
ld minimizeSquaredDeviations(vec<int>& a) {
    int n = sz(a);
    ld mean = accumulate(all(a), 0.0) / n;

    ld sum = 0;
    for (int x : a) sum += (x - mean) * (x - mean);
    return sum;
}

void solve() {
    int n;
    cin >> n;

    cout << "Integer Break(" << n << ") = " << integerBreak(n) << nl;
    cout << "Integer Break Mod(" << n << ") = " << integerBreakMod(n) << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    int TC = 1;
    cin >> TC;
    while (TC--) solve();

    return 0;
}

