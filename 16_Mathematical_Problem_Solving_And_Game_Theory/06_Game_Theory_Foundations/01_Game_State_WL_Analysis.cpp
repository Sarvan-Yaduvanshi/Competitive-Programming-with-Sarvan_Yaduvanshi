/*
 * ============================================================
 *  Topic   : Game State W/L Analysis & Backward Induction
 *  Pattern : Classify positions as W or L from terminal states
 *
 *  Problems:
 *    - CSES Stick Game (1729)
 *    - LeetCode 292 — Nim Game
 *    - LeetCode 464 — Can I Win
 *
 *  Complexity: O(n × |moves|) for backward induction
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
 *  BACKWARD INDUCTION — W/L State Classification
 * ============================================================
 *
 *  ALGORITHM:
 *  1. State 0 (no stones) is LOSING (can't move)
 *  2. For each state n from 1 to N:
 *     - If ANY move leads to an L state → W
 *     - If ALL moves lead to W states → L
 *
 *  This is the foundation of ALL game theory in CP!
 *
 *  EXAMPLE: CSES Stick Game
 *  ────────────────────────
 *  n sticks. Allowed move sizes: {s1, s2, ..., sk}.
 *  Take exactly si sticks. Last to take wins.
 *  For each n from 1 to N, output W or L.
 * ============================================================
 */

// CSES 1729: Stick Game
// Given n sticks, allowed moves in set S
// Output W/L for each position 0..n
void stickGame() {
    int n, k;
    cin >> n >> k;

    vec<int> moves(k);
    read(moves);

    // state[i] = true if position i is WINNING
    vec<bool> win(n + 1, false);
    // win[0] = false (losing — can't move)

    for (int i = 1; i <= n; i++) {
        for (int s : moves) {
            if (i >= s && !win[i - s]) {
                win[i] = true;  // found a move to a losing state
                break;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << (win[i] ? 'W' : 'L');
    }
    cout << nl;
}

/*
 * ============================================================
 *  SIMPLE NIM GAME (LeetCode 292)
 * ============================================================
 *  n stones. Each turn take 1, 2, or 3 stones.
 *  Last to take wins.
 *
 *  Analysis: L when n % 4 == 0
 *
 *  Proof:
 *    n=0: L (no moves)
 *    n=1,2,3: W (take all)
 *    n=4: take 1→3(W), take 2→2(W), take 3→1(W) → all W → L
 *    n=5: take 1→4(L) → W
 *    Pattern: L iff n ≡ 0 (mod 4)
 *
 *  Strategy: always leave opponent at multiple of 4.
 *  Take (n % 4) stones to do this.
 * ============================================================
 */

bool canWinNim(int n) {
    return n % 4 != 0;
}

/*
 * ============================================================
 *  GAME DP WITH BITMASK (LeetCode 464 — Can I Win)
 * ============================================================
 *  Numbers 1..maxChoosable, choose without replacement.
 *  First to make running total >= desiredTotal wins.
 *
 *  State: bitmask of used numbers + whose turn
 *  Since maxChoosable ≤ 20, bitmask fits in int.
 *
 *  dp[mask] = can the current player win given this set of used numbers?
 * ============================================================
 */

int memo_canIWin[1 << 21];

bool canIWin_helper(int maxC, int desired, int total, int mask) {
    if (memo_canIWin[mask] != -1) return memo_canIWin[mask];

    for (int i = 1; i <= maxC; i++) {
        if (mask & (1 << i)) continue;  // already used
        if (total + i >= desired) {
            return memo_canIWin[mask] = true;  // current player wins
        }
        // If opponent loses after we pick i → we win
        if (!canIWin_helper(maxC, desired, total + i, mask | (1 << i))) {
            return memo_canIWin[mask] = true;
        }
    }

    return memo_canIWin[mask] = false;  // all moves lead to opponent winning
}

bool canIWin(int maxChoosableInteger, int desiredTotal) {
    int maxC = maxChoosableInteger;
    int total_sum = maxC * (maxC + 1) / 2;

    if (total_sum < desiredTotal) return false;  // impossible
    if (desiredTotal <= 0) return true;

    memset(memo_canIWin, -1, sizeof(memo_canIWin));
    return canIWin_helper(maxC, desiredTotal, 0, 0);
}

/*
 * ============================================================
 *  PREDICT THE WINNER / MINIMAX DP (LeetCode 486)
 * ============================================================
 *  Array of scores. Players take turns picking from either end.
 *  First player wins if their score >= second player's score.
 *
 *  dp[i][j] = maximum advantage (my score - opponent's score)
 *             for the subarray [i..j]
 *
 *  dp[i][j] = max(a[i] - dp[i+1][j], a[j] - dp[i][j-1])
 * ============================================================
 */

bool predictTheWinner(vec<int>& nums) {
    int n = sz(nums);
    vvec<int> dp(n, vec<int>(n, 0));

    for (int i = 0; i < n; i++) dp[i][i] = nums[i];

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = max(nums[i] - dp[i + 1][j],
                           nums[j] - dp[i][j - 1]);
        }
    }

    return dp[0][n - 1] >= 0;
}

void solve() {
    // Default: CSES Stick Game
    stickGame();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    int TC = 1;
    // cin >> TC;  // Stick game is single test case
    while (TC--) solve();

    return 0;
}

