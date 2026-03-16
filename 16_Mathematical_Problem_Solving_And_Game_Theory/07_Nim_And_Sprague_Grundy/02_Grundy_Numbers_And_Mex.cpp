/*
 * ============================================================
 *  Topic   : Grundy Numbers, Mex, & Sprague-Grundy Theorem
 *  Pattern : Compute Grundy values → XOR for composite games
 *
 *  Problems:
 *    - CSES Grundy's Game (2207)
 *    - CSES Stick Game (1729)
 *    - CSES Nim Game II (1098)
 *    - LeetCode 1510 — Stone Game IV
 *
 *  Complexity: O(n × |moves|) for single game,
 *              O(k × n) for composite games with k sub-games
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
 *  MEX (Minimum EXcludant)
 * ============================================================
 *  mex(S) = smallest non-negative integer NOT in set S
 *
 *  mex({0,1,2}) = 3
 *  mex({1,2,3}) = 0
 *  mex({0,2,3}) = 1
 *  mex({})      = 0
 * ============================================================
 */

int mex(set<int>& S) {
    int m = 0;
    while (S.count(m)) m++;
    return m;
}

// Faster mex using vector (when values are small)
int mex_vec(vec<int>& vals) {
    set<int> S(all(vals));
    int m = 0;
    while (S.count(m)) m++;
    return m;
}

/*
 * ============================================================
 *  GRUNDY NUMBERS — General Computation
 * ============================================================
 *
 *  G(position) = mex({ G(next_position) for all valid moves })
 *
 *  G(position) = 0  ⟺  LOSING position
 *  G(position) > 0  ⟺  WINNING position
 *
 *  SPRAGUE-GRUNDY THEOREM:
 *  For independent sub-games:
 *    G(game1 + game2 + ... + gamek) = G(game1) ⊕ G(game2) ⊕ ... ⊕ G(gamek)
 * ============================================================
 */

/*
 *  EXAMPLE 1: Subtraction Game
 *  ───────────────────────────
 *  Pile of n stones. Move set S = {s1, s2, ..., sk}.
 *  Can take exactly si stones. Last to move wins.
 */

vec<int> grundy_subtraction(int maxN, vec<int>& moves) {
    vec<int> G(maxN + 1, 0);
    for (int n = 1; n <= maxN; n++) {
        set<int> reachable;
        for (int m : moves) {
            if (n >= m) {
                reachable.insert(G[n - m]);
            }
        }
        G[n] = mex(reachable);
    }
    return G;
}

/*
 *  EXAMPLE 2: Take Square Numbers (LeetCode 1510)
 *  ──────────────────────────────────────────────
 *  n stones. Each turn: take a perfect square number of stones.
 *  Last to take wins.
 *
 *  G(0) = 0
 *  G(n) = mex({ G(n - 1²), G(n - 2²), G(n - 3²), ... })
 *         for all k² ≤ n
 */

vec<int> grundy_square_subtraction(int maxN) {
    vec<int> G(maxN + 1, 0);
    for (int n = 1; n <= maxN; n++) {
        set<int> reachable;
        for (int k = 1; k * k <= n; k++) {
            reachable.insert(G[n - k * k]);
        }
        G[n] = mex(reachable);
    }
    return G;
}

/*
 *  EXAMPLE 3: Bounded Nim — Take 1..m stones
 *  ─────────────────────────────────────────
 *  G(n) = n % (m + 1)
 *
 *  Proof: moves lead to G(n-1), G(n-2), ..., G(n-m)
 *  which are n%m, n%m-1, ..., (n-m)%(m+1)
 *  The mex of {0,1,...,m-1,m}\{some} cycles with period m+1.
 *
 *  For CSES Nim Game II: Each pile, can take 1..3 stones.
 *  Grundy(pile) = pile % 4
 *  XOR of all Grundy values → winner.
 */

/*
 *  EXAMPLE 4: Grundy's Game (CSES 2207)
 *  ────────────────────────────────────
 *  Split a pile of n stones into two non-empty piles of DIFFERENT sizes.
 *  Last to move wins.
 *
 *  No known closed-form! Must compute Grundy values.
 *  Key: a pile is split into (a, n-a) where a < n-a, i.e. a < n/2.
 *  The resulting game is TWO independent sub-piles: G = G(a) ⊕ G(n-a).
 */

const int MAXN_GRUNDY = 1000;
int grundy_game[MAXN_GRUNDY + 1];
bool computed[MAXN_GRUNDY + 1];

int grundyGame(int n) {
    if (n <= 2) return 0;  // can't split into two different sizes
    if (computed[n]) return grundy_game[n];

    computed[n] = true;
    set<int> reachable;
    for (int a = 1; 2 * a < n; a++) {  // a < n - a
        int b = n - a;
        reachable.insert(grundyGame(a) ^ grundyGame(b));
    }

    grundy_game[n] = mex(reachable);
    return grundy_game[n];
}

/*
 * ============================================================
 *  COMPOSITE GAME — Multiple independent sub-games
 * ============================================================
 *  If the game consists of k independent piles/sub-games:
 *  G(total) = G(pile1) ⊕ G(pile2) ⊕ ... ⊕ G(pilek)
 *
 *  First player wins ⟺ G(total) ≠ 0
 * ============================================================
 */

void solve() {
    int k;
    cin >> k;

    vec<int> piles(k);
    read(piles);

    // Example: Grundy's game — split piles
    memset(computed, false, sizeof(computed));

    int xorSum = 0;
    for (int p : piles) {
        xorSum ^= grundyGame(p);
    }

    cout << (xorSum != 0 ? "first" : "second") << nl;
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

