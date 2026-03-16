/*
 * ============================================================
 *  Topic   : Random Walks & Geometric Distribution
 *  Pattern : Gambler's ruin, random walk absorption probabilities
 *
 *  Problems:
 *    - Gambler's ruin probability
 *    - Expected steps in absorbing Markov chain
 *    - Geometric distribution expected value
 *    - LeetCode 1227 — Airplane Seat Assignment Probability
 *
 *  Complexity: O(n) for linear walk, O(1) for formulas
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

/*
 * ============================================================
 *  GAMBLER'S RUIN
 * ============================================================
 *
 *  Start with $k. Each step:
 *    - Win $1 with probability p
 *    - Lose $1 with probability q = 1 - p
 *  Game ends when you reach $0 (ruin) or $n (win).
 *
 *  PROBABILITY OF REACHING $n FROM $k:
 *
 *  If p ≠ q (unfair coin):
 *    P(win | start at k) = (1 - (q/p)^k) / (1 - (q/p)^n)
 *
 *  If p = q = 1/2 (fair coin):
 *    P(win | start at k) = k / n
 *
 *  EXPECTED STEPS UNTIL ABSORPTION:
 *
 *  If p ≠ q:
 *    E[steps | start at k] = (k/(q-p)) - (n/(q-p)) × P(win|k)
 *    (for p < q case)
 *
 *  If p = q = 1/2:
 *    E[steps | start at k] = k × (n - k)
 * ============================================================
 */

// Probability of reaching n from k
ld gamblerRuinProb(int k, int n, ld p) {
    ld q = 1.0L - p;
    if (abs(p - q) < 1e-12) {
        // Fair coin
        return (ld)k / n;
    }
    ld ratio = q / p;
    return (1.0L - powl(ratio, k)) / (1.0L - powl(ratio, n));
}

// Expected steps until absorption (fair coin case)
ld gamblerRuinExpectedStepsFair(int k, int n) {
    return (ld)k * (n - k);
}

/*
 * ============================================================
 *  GEOMETRIC DISTRIBUTION
 * ============================================================
 *
 *  Repeat independent Bernoulli trials with success probability p.
 *  X = number of trials until first success.
 *
 *  P(X = k) = (1-p)^(k-1) × p
 *  E[X] = 1/p
 *  Var[X] = (1-p)/p²
 *
 *  APPLICATION: Coupon Collector
 *  After collecting i coupons, prob of getting new one = (n-i)/n.
 *  Expected trials for next coupon: n/(n-i) (geometric with p=(n-i)/n).
 *  Total: E = Σ_{i=0}^{n-1} n/(n-i) = n × H_n
 * ============================================================
 */

/*
 * ============================================================
 *  AIRPLANE SEAT PROBLEM (LeetCode 1227)
 * ============================================================
 *
 *  n passengers board a plane with n seats. Passenger 1 has
 *  lost their boarding pass and sits randomly. Each subsequent
 *  passenger sits in their seat if available, otherwise randomly.
 *  What's the probability that passenger n gets their seat?
 *
 *  ANSWER: 1/2 for all n ≥ 2 (and 1 for n = 1).
 *
 *  PROOF SKETCH:
 *  At any point, the only seats that matter are seat 1 and seat n.
 *  By symmetry, they are equally likely to be chosen.
 *  So P(seat n is free when passenger n boards) = 1/2.
 * ============================================================
 */

ld airplaneProb(int n) {
    if (n == 1) return 1.0;
    return 0.5;
}

/*
 * ============================================================
 *  RANDOM WALK SIMULATION (for verification)
 * ============================================================
 */
ld simulateGamblerRuin(int k, int n, ld p, int trials = 100000) {
    int wins = 0;
    for (int t = 0; t < trials; t++) {
        int pos = k;
        while (pos > 0 && pos < n) {
            ld r = (ld)rng() / rng.max();
            if (r < p) pos++;
            else pos--;
        }
        if (pos == n) wins++;
    }
    return (ld)wins / trials;
}

void solve() {
    int k, n;
    ld p;
    cin >> k >> n >> p;

    cout << "P(reach " << n << " from " << k << ") = "
         << gamblerRuinProb(k, n, p) << nl;

    if (abs(p - 0.5) < 1e-9) {
        cout << "E[steps] (fair) = " << gamblerRuinExpectedStepsFair(k, n) << nl;
    }
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

