/*
 * ============================================================
 *  Topic   : Convexity, Ternary Search & Binary Search on Answer
 *  Pattern : Optimize unimodal functions, binary search on answer
 *
 *  Problems:
 *    - LeetCode 410 — Split Array Largest Sum (BS on answer)
 *    - LeetCode 1011 — Capacity To Ship Packages (BS on answer)
 *    - Codeforces — minimize/maximize convex function
 *    - Closest pair / minimum distance problems
 *
 *  Complexity:
 *    Ternary Search: O(log((hi-lo)/eps)) iterations
 *    Binary Search on Answer: O(log(range) × check_time)
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

/*
 * ============================================================
 *  TERNARY SEARCH — Find extremum of unimodal function
 * ============================================================
 *
 *  A function f is UNIMODAL on [lo, hi] if it first
 *  increases then decreases (single peak) or first
 *  decreases then increases (single valley).
 *
 *  ALGORITHM: Divide interval into 3 parts, compare two interior
 *  points, discard 1/3 of the interval.
 *
 *  CONTINUOUS VERSION: ~200 iterations for 10^-15 precision
 *  INTEGER VERSION: iterate until hi - lo < 3, then check all
 * ============================================================
 */

// Find minimum of a convex function on [lo, hi]
ld ternarySearchMinContinuous(ld lo, ld hi, function<ld(ld)> f) {
    for (int iter = 0; iter < 200; iter++) {
        ld m1 = lo + (hi - lo) / 3;
        ld m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2))
            hi = m2;
        else
            lo = m1;
    }
    return (lo + hi) / 2;
}

// Find maximum of a concave function on [lo, hi]
ld ternarySearchMaxContinuous(ld lo, ld hi, function<ld(ld)> f) {
    for (int iter = 0; iter < 200; iter++) {
        ld m1 = lo + (hi - lo) / 3;
        ld m2 = hi - (hi - lo) / 3;
        if (f(m1) > f(m2))
            hi = m2;
        else
            lo = m1;
    }
    return (lo + hi) / 2;
}

// Integer ternary search — find x in [lo, hi] that minimizes f(x)
i64 ternarySearchMinInteger(i64 lo, i64 hi, function<i64(i64)> f) {
    while (hi - lo > 2) {
        i64 m1 = lo + (hi - lo) / 3;
        i64 m2 = hi - (hi - lo) / 3;
        if (f(m1) <= f(m2))
            hi = m2;
        else
            lo = m1;
    }
    // Check all remaining candidates
    i64 best = lo;
    for (i64 x = lo; x <= hi; x++) {
        if (f(x) < f(best)) best = x;
    }
    return best;
}

/*
 * ============================================================
 *  BINARY SEARCH ON ANSWER
 * ============================================================
 *
 *  Pattern: "Minimize the maximum" or "Maximize the minimum"
 *
 *  1. Binary search on the answer value X
 *  2. For each X, check: "Is it possible to achieve answer ≤ X?"
 *     (or ≥ X)
 *  3. The check function is typically greedy O(n) or O(n log n)
 *
 *  TEMPLATE:
 *  i64 lo = min_possible, hi = max_possible;
 *  while (lo < hi) {
 *      i64 mid = lo + (hi - lo) / 2;
 *      if (check(mid)) hi = mid;
 *      else lo = mid + 1;
 *  }
 *  answer = lo;
 * ============================================================
 */

/*
 *  EXAMPLE: LeetCode 410 — Split Array Largest Sum
 *  Split array into k subarrays to minimize the largest sum.
 *
 *  Binary search on the answer (the maximum allowed sum).
 *  Check: can we split into ≤ k subarrays such that each ≤ mid?
 */

bool canSplit(vec<int>& nums, int k, i64 maxSum) {
    int parts = 1;
    i64 curSum = 0;
    for (int x : nums) {
        if (curSum + x > maxSum) {
            parts++;
            curSum = x;
            if (parts > k) return false;
        } else {
            curSum += x;
        }
    }
    return true;
}

i64 splitArrayLargestSum(vec<int>& nums, int k) {
    i64 lo = *max_element(all(nums));  // at least one element per part
    i64 hi = accumulate(all(nums), 0LL);  // all in one part

    while (lo < hi) {
        i64 mid = lo + (hi - lo) / 2;
        if (canSplit(nums, k, mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

/*
 *  EXAMPLE: Minimize max distance between gas stations
 *  (LeetCode 774 / similar problems)
 *
 *  Binary search on the answer (maximum gap).
 *  Check: can we place k stations so all gaps ≤ mid?
 *  For each existing gap g: need ceil(g / mid) - 1 stations.
 */

/*
 * ============================================================
 *  CONVEXITY TRICKS
 * ============================================================
 *
 *  WHEN IS f(x) CONVEX?
 *  - f(x) = x² → convex
 *  - f(x) = |x| → convex
 *  - f(x) = max(g₁(x), g₂(x)) → convex if both gᵢ are convex
 *  - f(x) = Σ convex functions → convex
 *
 *  CONSEQUENCE: Sum of squares is minimized by equal distribution
 *  - Minimize Σ xᵢ² s.t. Σ xᵢ = S → all xᵢ = S/n
 *  - For integers: use ⌊S/n⌋ and ⌈S/n⌉
 *
 *  CONSEQUENCE: Sum of |xᵢ - c| is minimized at median
 * ============================================================
 */

// Minimum sum of squares when distributing S into n parts
i64 minSumOfSquares(i64 S, i64 n) {
    i64 q = S / n, r = S % n;
    // r parts get (q+1), (n-r) parts get q
    return r * (q + 1) * (q + 1) + (n - r) * q * q;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vec<int> a(n);
    read(a);

    cout << splitArrayLargestSum(a, k) << nl;
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

