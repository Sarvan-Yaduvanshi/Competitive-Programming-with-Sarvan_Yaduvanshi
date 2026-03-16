/*
 * ============================================================
 *  Topic   : Parity Arguments & Invariants
 *  Pattern : Use odd/even analysis + unchanging quantities
 *            to prove possibility/impossibility
 *
 *  Covers:
 *    1. Parity of sum / count to determine game winners
 *    2. Invariants — prove a state is unreachable
 *    3. Classic chessboard / tiling invariants
 *
 *  Complexity: Problem-dependent (usually O(n) analysis)
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
 *  PARITY ARGUMENTS
 * ============================================================
 *
 *  KEY IDEA: Track whether a quantity is odd or even.
 *  Operations often preserve or toggle parity.
 *
 *  PATTERN 1: Game winner by parity
 *  ─────────────────────────────────
 *  If each move removes exactly 1 element, and there are n elements:
 *    n odd  → First player wins
 *    n even → Second player wins
 *
 *  PATTERN 2: Sum parity invariant
 *  ───────────────────────────────
 *  If each operation changes the sum by an even amount,
 *  the parity of the sum is an invariant.
 *
 *  PATTERN 3: Chessboard coloring
 *  ──────────────────────────────
 *  Color the board like a chessboard. Each domino covers
 *  exactly 1 black + 1 white cell. If counts differ → impossible.
 * ============================================================
 */

// Example 1: Can we reach target sum from initial sum
// using operations that change sum by 'delta' each step?
bool canReachByParity(i64 initial_sum, i64 target_sum, i64 delta) {
    i64 diff = target_sum - initial_sum;
    // Need diff to be achievable as a multiple of delta
    if (delta == 0) return diff == 0;
    if (diff % delta != 0) return false;
    return true;  // simplified — real problems check more constraints
}

// Example 2: Parity-based game — each player removes 1 stone at a time
// n stones, player who takes last stone wins
string simpleGameWinner(int n) {
    return (n % 2 == 1) ? "First" : "Second";
}

/*
 * ============================================================
 *  INVARIANTS
 * ============================================================
 *
 *  An INVARIANT is a quantity that does NOT change under
 *  the allowed operations.
 *
 *  HOW TO USE:
 *  1. Compute the invariant at the INITIAL state
 *  2. Compute the invariant at the TARGET state
 *  3. If they differ → IMPOSSIBLE
 *
 *  EXAMPLE: Array has elements. Operation: pick two elements
 *  a[i], a[j], replace both with (a[i]+a[j])/2.
 *  Invariant: sum of all elements never changes.
 *  If initial sum ≠ n * target_value → impossible to make all equal.
 *
 *  EXAMPLE: 15-puzzle — the parity of the permutation + row of
 *  blank determines reachability.
 * ============================================================
 */

// Check if array can become all equal using "replace pair with average"
// Invariant: total sum
bool canMakeAllEqual(vec<int>& a, int target) {
    int n = sz(a);
    i64 total = accumulate(all(a), 0LL);
    return total == (i64)n * target;
}

/*
 *  EXAMPLE: Coin Flip Invariant
 *  n coins, all Heads. Each move: flip exactly k coins.
 *  Can we make all Tails?
 *
 *  Let H = number of heads.
 *  Start: H = n (parity = n%2)
 *  Goal:  H = 0 (parity = 0)
 *  Each flip of k coins changes H by some amount whose parity = k%2
 *
 *  If k is even: H changes by even amount → parity invariant
 *    → Need n%2 == 0 (necessary condition)
 *  If k is odd: H parity flips each step
 *    → After even steps: same parity as start
 *    → After odd steps: flipped parity
 */
bool canFlipAllCoins(int n, int k) {
    // Simplified: can we reach 0 heads from n heads?
    if (k > n) return false;
    // If k is even, need n to be even
    if (k % 2 == 0) return n % 2 == 0;
    // If k is odd, we can always reach 0 (sufficient moves)
    return true;
}

void solve() {
    int n;
    cin >> n;

    // Simple parity game: n stones, alternate taking 1
    cout << simpleGameWinner(n) << nl;
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

