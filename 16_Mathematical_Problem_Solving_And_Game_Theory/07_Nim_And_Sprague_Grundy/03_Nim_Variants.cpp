/*
 * ============================================================
 *  Topic   : Staircase Nim & Nim Variants
 *  Pattern : Reduce variants to classic Nim using key insights
 *
 *  Problems:
 *    - CSES Staircase Nim (1099)
 *    - CSES Nim Game II (1098) — Bounded Nim
 *    - Misère Nim
 *
 *  Complexity: O(n) per test case
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
 *  STAIRCASE NIM (CSES 1099)
 * ============================================================
 *
 *  Setup: n stairs indexed 1..n with stones on each.
 *  Move: take any number of stones from stair i and place on stair i-1.
 *  Stair 0 is the "ground" (removed from play).
 *  Last to move wins.
 *
 *  KEY INSIGHT:
 *  - Moving stones from an ODD stair to an EVEN stair is a "real" move
 *  - Moving stones from an EVEN stair to an ODD stair can be "undone"
 *    by the opponent (mirror the move from odd to even)
 *
 *  RESULT: Only ODD-indexed stairs matter!
 *  First player wins ⟺ XOR of stones on ODD stairs ≠ 0
 *
 *  WHY: Moves on even stairs can always be countered.
 *  The game on odd stairs behaves exactly like regular Nim.
 * ============================================================
 */

void staircaseNim() {
    int n;
    cin >> n;

    vec<int> stairs(n);
    read(stairs);

    int xorOdd = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {  // 0-indexed, so even index = odd stair (1-indexed)
            xorOdd ^= stairs[i];
        }
    }

    // Note: if the problem uses 1-indexed stairs, XOR odd-indexed ones
    cout << (xorOdd != 0 ? "first" : "second") << nl;
}

/*
 * ============================================================
 *  BOUNDED NIM (CSES 1098 — Nim Game II)
 * ============================================================
 *
 *  k piles. Each turn: take 1, 2, or 3 stones from one pile.
 *  Last to take wins.
 *
 *  Grundy(n) = n % 4  (since max take is 3, period = 3+1 = 4)
 *  General: if max take is m, Grundy(n) = n % (m+1)
 *
 *  XOR all Grundy values → ≠ 0 means first wins.
 * ============================================================
 */

void boundedNim() {
    int k;
    cin >> k;

    int xorSum = 0;
    for (int i = 0; i < k; i++) {
        int n;
        cin >> n;
        // Take 1, 2, or 3 → Grundy = n % 4
        xorSum ^= (n % 4);
    }

    cout << (xorSum != 0 ? "first" : "second") << nl;
}

/*
 * ============================================================
 *  MISÈRE NIM
 * ============================================================
 *
 *  Same as Nim but the player who takes the LAST stone LOSES.
 *
 *  RULE:
 *  If all piles have size ≤ 1:
 *    - Odd # of piles → Second wins (forced to take last)
 *    - Even # of piles → First wins
 *  If any pile has size > 1:
 *    - XOR ≠ 0 → First wins  (SAME as normal Nim!)
 *    - XOR = 0 → Second wins (SAME as normal Nim!)
 *
 *  WHY: When piles are large, the winning player can always
 *  choose to enter the endgame with all-size-1 in the right parity.
 * ============================================================
 */

string misereNim(vec<int>& piles) {
    int xorSum = 0;
    bool allOne = true;

    for (int p : piles) {
        xorSum ^= p;
        if (p > 1) allOne = false;
    }

    if (allOne) {
        // Number of piles = number of 1s
        int cnt = sz(piles);
        return (cnt % 2 == 0) ? "first" : "second";
    }

    return (xorSum != 0) ? "first" : "second";
}

/*
 * ============================================================
 *  GREEN HACKENBUSH ON TREES (Bonus)
 * ============================================================
 *  Edges of a tree rooted at ground. Each turn: remove an edge
 *  and everything disconnected from ground.
 *
 *  Grundy value of a tree = XOR of (depth of each edge)
 *  ... but for simple paths/bamboo: Grundy = length
 *
 *  For general trees: Colon Principle applies.
 * ============================================================
 */

void solve() {
    // Default: Staircase Nim
    staircaseNim();
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

