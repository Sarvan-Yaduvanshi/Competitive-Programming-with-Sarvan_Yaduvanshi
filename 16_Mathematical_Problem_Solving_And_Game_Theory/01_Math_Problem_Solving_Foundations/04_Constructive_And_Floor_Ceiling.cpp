/*
 * ============================================================
 *  Topic   : Constructive Algorithms & Floor/Ceiling Tricks
 *  Pattern : Build valid solutions, integer division properties
 *
 *  Problems:
 *    - Codeforces constructive algorithms tag
 *    - LeetCode 991 — Broken Calculator (reverse greedy)
 *    - LeetCode 2178 — Maximum Split of Positive Even Integers
 *    - Floor sum optimization (harmonic trick)
 *
 *  Complexity: Problem-dependent
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
 *  FLOOR / CEILING UTILITIES
 * ============================================================
 *
 *  ⌈a/b⌉ = (a + b - 1) / b              for a, b > 0
 *  ⌊a/b⌋ = a / b                          C++ integer division (a,b > 0)
 *  a mod b = a - b × ⌊a/b⌋
 *
 *  PROPERTY: ⌊a/b⌋ takes at most O(2√a) distinct values
 *  as b ranges from 1 to a.
 *  → Used in "block decomposition" for sum optimizations.
 * ============================================================
 */

// Ceiling division (positive a, b)
inline i64 ceildiv(i64 a, i64 b) {
    return (a + b - 1) / b;
}

// Floor division (handles negative correctly)
inline i64 floordiv(i64 a, i64 b) {
    return a / b - (a % b != 0 && (a ^ b) < 0);
}

/*
 *  HARMONIC SUM OPTIMIZATION
 *  ─────────────────────────
 *  Compute Σ_{i=1}^{n} f(⌊n/i⌋) efficiently in O(√n) time.
 *
 *  Key insight: ⌊n/i⌋ takes at most O(2√n) distinct values.
 *  Group consecutive i's with the same ⌊n/i⌋ value.
 *
 *  For each block where ⌊n/i⌋ = q:
 *    the block spans i from lo to hi where hi = ⌊n/q⌋
 */

// Count Σ_{i=1}^{n} ⌊n/i⌋ in O(√n)
i64 sumFloorDiv(i64 n) {
    i64 result = 0;
    i64 i = 1;
    while (i <= n) {
        i64 q = n / i;           // current ⌊n/i⌋ value
        i64 hi = n / q;          // last i with same ⌊n/i⌋
        result += q * (hi - i + 1);  // add q for each i in [i, hi]
        i = hi + 1;
    }
    return result;
}

// Count numbers in [1, n] divisible by d
inline i64 countDiv(i64 n, i64 d) {
    return n / d;  // = ⌊n/d⌋
}

/*
 * ============================================================
 *  CONSTRUCTIVE ALGORITHM PATTERNS
 * ============================================================
 *
 *  PATTERN 1: Build array with given properties
 *  ─────────────────────────────────────────────
 *  - Check necessary conditions first (parity, sum, etc.)
 *  - Use greedy: place elements left-to-right
 *  - Often: alternate between two choices
 *
 *  PATTERN 2: Reverse engineering (work backwards)
 *  ───────────────────────────────────────────────
 *  Instead of going from start → end, go from end → start.
 *  Example: Broken Calculator (LeetCode 991)
 *    Forward: multiply by 2 or subtract 1
 *    Backward: divide by 2 or add 1 (much simpler greedy!)
 *
 *  PATTERN 3: Use invariant to guide construction
 *  ───────────────────────────────────────────────
 *  Maintain the invariant at every step of construction.
 *  If invariant holds at end → solution is valid.
 * ============================================================
 */

/*
 *  LeetCode 991 — Broken Calculator
 *  ─────────────────────────────────
 *  Start with startValue. Reach target using:
 *    - Multiply by 2
 *    - Subtract 1
 *  Minimum operations?
 *
 *  TRICK: Work backwards from target.
 *    - If target > start:
 *      - If target is even: target /= 2
 *      - If target is odd: target += 1 (then divide)
 *    - If target <= start: answer += (start - target)
 */
int brokenCalc(int startValue, int target) {
    int ops = 0;
    while (target > startValue) {
        if (target % 2 == 0)
            target /= 2;
        else
            target += 1;
        ops++;
    }
    return ops + (startValue - target);
}

/*
 *  LeetCode 2178 — Maximum Split of Positive Even Integers
 *  ───────────────────────────────────────────────────────
 *  Split even number into maximum distinct positive even integers.
 *
 *  Greedy: use 2, 4, 6, 8, ... and dump remainder into last number.
 */
vec<i64> maximumEvenSplit(i64 finalSum) {
    if (finalSum % 2 != 0) return {};  // odd → impossible

    vec<i64> result;
    i64 remaining = finalSum;
    i64 current = 2;

    while (remaining > 0) {
        if (remaining - current > current) {
            // Can still add more numbers after this
            result.pb(current);
            remaining -= current;
            current += 2;
        } else {
            // Dump everything remaining as the last number
            result.pb(remaining);
            remaining = 0;
        }
    }
    return result;
}

/*
 *  DISTRIBUTE n INTO k GROUPS
 *  ──────────────────────────
 *  Each group gets ⌊n/k⌋ or ⌈n/k⌉ items.
 *  Exactly (n % k) groups get ⌈n/k⌉.
 *  Exactly (k - n%k) groups get ⌊n/k⌋.
 */
vec<i64> distributeEvenly(i64 n, i64 k) {
    i64 base = n / k;
    i64 extra = n % k;
    vec<i64> groups(k);
    for (int i = 0; i < k; i++) {
        groups[i] = base + (i < extra ? 1 : 0);
    }
    return groups;
}

void solve() {
    i64 n;
    cin >> n;

    cout << "Sum of floor(n/i) for i=1.." << n << " = " << sumFloorDiv(n) << nl;
    cout << "ceil(" << n << "/3) = " << ceildiv(n, 3) << nl;
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

