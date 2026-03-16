/*
 * ============================================================
 *  Topic   : Euclid's Game & Classic Combinatorial Games
 *  Pattern : GCD-based game analysis, classic game theory puzzles
 *
 *  Covers:
 *    1. Euclid's Game — take multiples of smaller from larger
 *    2. Chomp — eat from a chocolate bar grid
 *    3. Nim on a graph (game on general graph with SG)
 *
 *  Problems:
 *    - SPOJ EUCLID — Euclid's Game
 *    - Codeforces various Euclid-game variants
 *    - Chomp (theoretical — strategy stealing proves first wins)
 *
 *  Complexity: O(log(max(a,b))) for Euclid's Game
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
 *  EUCLID'S GAME
 * ============================================================
 *
 *  Two players start with two positive integers (a, b).
 *  Each turn: subtract any positive MULTIPLE of the smaller
 *  number from the larger number. The multiple must leave
 *  the result non-negative.
 *  Player who makes a number 0 wins (or player who can't
 *  move without going negative loses — equivalent).
 *
 *  ANALYSIS:
 *  ─────────
 *  Let a ≥ b (WLOG).
 *
 *  CASE 1: a ≥ 2b
 *    Current player has CHOICE: subtract b or 2b or ... from a.
 *    They can reach BOTH (a - b, b) and (a - 2b, b).
 *    These two states have DIFFERENT parities of "distance" to
 *    the terminal, so one must be W and one must be L for opponent.
 *    → Current player can ALWAYS win (choose the right one).
 *    ⟹ a ≥ 2b → FIRST player WINS
 *
 *  CASE 2: b ≤ a < 2b
 *    Only one move possible: (a - b, b) = (a - b, b) and
 *    since a - b < b, the game flips: next state is (b, a - b).
 *    This is forced — no choice.
 *    → Recurse on (b, a - b).
 *    → The game follows the Euclidean algorithm!
 *
 *  CASE 3: a == b
 *    Subtract b from a → (0, b) → current player wins.
 *
 *  CASE 4: b == 0
 *    Previous player won (they made 0). Current player loses.
 *
 *  ALGORITHM:
 *  Simulate the Euclidean algorithm. First player who faces
 *  a ≥ 2b (or a == b) WINS. Track whose turn it is.
 * ============================================================
 */

// Returns "First" or "Second" — winner of Euclid's Game
string euclidGame(i64 a, i64 b) {
    bool firstPlayerTurn = true;

    while (a > 0 && b > 0) {
        if (a < b) swap(a, b);

        // If a == b, current player takes all and wins
        if (a == b) {
            return firstPlayerTurn ? "First" : "Second";
        }

        // If a >= 2b, current player has a choice → they win
        if (a >= 2 * b) {
            return firstPlayerTurn ? "First" : "Second";
        }

        // a < 2b: forced move a → a - b
        a -= b;
        firstPlayerTurn = !firstPlayerTurn;
    }

    // If we reach here, someone made 0 → the OTHER player won
    return firstPlayerTurn ? "Second" : "First";
}

/*
 *  DRY RUN: Euclid's Game with (a=25, b=7)
 *
 *  Step 1: a=25, b=7 → 25 ≥ 14 (2×7) → First player WINS!
 *  (First can choose to subtract 7 or 14 or 21 from 25)
 *
 *  DRY RUN: (a=11, b=7)
 *  Step 1: 11 < 14 → forced move → (7, 4), switch to Second
 *  Step 2: 7 < 8 → forced move → (4, 3), switch to First
 *  Step 3: 4 < 6 → forced move → (3, 1), switch to Second
 *  Step 4: 3 ≥ 2 (2×1) → Second player WINS!
 */

/*
 * ============================================================
 *  CHOMP (Theoretical)
 * ============================================================
 *
 *  m × n chocolate bar. Players take turns eating a square
 *  and everything above and to the right. The player who eats
 *  the bottom-left square (poisoned) LOSES.
 *
 *  THEOREM: First player ALWAYS wins for any m×n > 1×1.
 *
 *  PROOF (Strategy Stealing):
 *  Suppose Second has a winning strategy S.
 *  Then First eats only the top-right square on move 1.
 *  Now if Second applies S, First can "steal" it — contradiction
 *  because First's initial move only made the board smaller/equal.
 *
 *  NOTE: This is a pure EXISTENCE proof — no efficient strategy
 *  is known for general m×n! Specific small cases can be computed.
 *
 *  For 2-row Chomp (2×n):
 *    First player eats (2, 2) leaving an "L" shape → then mirrors.
 * ============================================================
 */

// Chomp: brute force for small boards (memoized)
// State: vector of column heights
// Returns true if current player can win
map<vec<int>, bool> chompMemo;

bool chompWins(vec<int>& heights) {
    if (chompMemo.count(heights)) return chompMemo[heights];

    int cols = sz(heights);

    // Try every possible bite
    for (int c = 0; c < cols; c++) {
        for (int h = 1; h <= heights[c]; h++) {
            // Skip eating the poison square (0,0)
            if (c == 0 && h == 1 && heights[c] == 1) {
                // Check if this is the only remaining square
                bool onlyOne = true;
                for (int i = 1; i < cols; i++) if (heights[i] > 0) onlyOne = false;
                if (onlyOne) continue;  // eating poison → lose
            }

            // Make move: set column c to height h-1, and all columns
            // to the right to min(their height, h-1)
            vec<int> next = heights;
            for (int i = c; i < cols; i++) {
                next[i] = min(next[i], h - 1);
            }
            // Remove trailing zero columns
            while (!next.empty() && next.back() == 0) next.pop_back();

            if (next.empty()) continue;  // ate everything including poison

            if (!chompWins(next)) {
                // Opponent loses → current player wins
                return chompMemo[heights] = true;
            }
        }
    }

    return chompMemo[heights] = false;
}

/*
 * ============================================================
 *  NIM ON GENERAL GRAPH (Sprague-Grundy on game graph)
 * ============================================================
 *
 *  Given a DAG, each node has outgoing edges (moves).
 *  A token starts at some node. Players alternate moving
 *  the token along an edge. Player who can't move loses.
 *
 *  Grundy number of each node:
 *  G(v) = mex({ G(u) : u is a successor of v })
 *
 *  For multiple tokens on independent parts of the graph:
 *  XOR all their Grundy values.
 * ============================================================
 */

vec<int> grundyOnDAG(int n, vvec<int>& adj) {
    // Topological sort first
    vec<int> indeg(n, 0);
    for (int u = 0; u < n; u++)
        for (int v : adj[u]) indeg[v]++;

    // Process in reverse topological order
    // Use DFS + memoization
    vec<int> grundy(n, -1);

    function<int(int)> dfs = [&](int u) -> int {
        if (grundy[u] != -1) return grundy[u];
        set<int> reachable;
        for (int v : adj[u]) {
            reachable.insert(dfs(v));
        }
        int m = 0;
        while (reachable.count(m)) m++;
        return grundy[u] = m;
    };

    for (int i = 0; i < n; i++) {
        if (grundy[i] == -1) dfs(i);
    }

    return grundy;
}

void solve() {
    i64 a, b;
    cin >> a >> b;

    cout << euclidGame(a, b) << nl;
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

