/*
 * ============================================================
 *  Topic   : Game on DAG (Directed Acyclic Graph) & Minimax
 *  Pattern : Determine W/L for each node in a game graph
 *            + Alpha-Beta style Minimax for partisan games
 *
 *  Problems:
 *    - CSES Coin Game variant
 *    - Codeforces 936B — Game on Graph
 *    - LeetCode 913 — Cat and Mouse (BFS game on graph)
 *    - LeetCode 486 — Predict the Winner (Minimax)
 *
 *  Complexity:
 *    DAG game: O(V + E)
 *    Minimax: O(b^d) without pruning, O(b^(d/2)) with alpha-beta
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
 *  GAME ON DAG — BFS-based W/L Classification
 * ============================================================
 *
 *  Given a directed acyclic graph where:
 *  - Nodes are game states
 *  - Edges are valid moves (state → next_state)
 *  - Sinks (no outgoing edges) are LOSING positions
 *  - Two players alternate; player who can't move LOSES
 *
 *  ALGORITHM (Reverse BFS):
 *  1. Mark all sinks as LOSING
 *  2. Process in reverse topological order:
 *     - If ANY successor is L → mark as W
 *     - If ALL successors are W → mark as L
 *
 *  Implementation: Use reverse graph + BFS from known states.
 *  Track outdegree; when a node has all successors classified W,
 *  it becomes L.
 *
 *  TIME: O(V + E)
 * ============================================================
 */

// state[v] = 0 (LOSING), 1 (WINNING), -1 (unclassified)
vec<int> gameOnDAG(int n, vvec<int>& adj) {
    // Build reverse graph and compute out-degree
    vvec<int> radj(n);
    vec<int> outdeg(n, 0);

    for (int u = 0; u < n; u++) {
        outdeg[u] = sz(adj[u]);
        for (int v : adj[u]) {
            radj[v].pb(u);
        }
    }

    vec<int> state(n, -1);  // -1 = unclassified
    queue<int> q;

    // Step 1: Sinks (outdeg = 0) are LOSING
    for (int v = 0; v < n; v++) {
        if (outdeg[v] == 0) {
            state[v] = 0;  // Losing
            q.push(v);
        }
    }

    // Step 2: BFS on reverse graph
    while (!q.empty()) {
        int v = q.front(); q.pop();

        for (int u : radj[v]) {
            if (state[u] != -1) continue;  // already classified

            if (state[v] == 0) {
                // v is Losing → u can move to a Losing state → u is Winning
                state[u] = 1;
                q.push(u);
            } else {
                // v is Winning → u has one fewer "hope" for L successor
                outdeg[u]--;
                if (outdeg[u] == 0) {
                    // All successors of u are Winning → u is Losing
                    state[u] = 0;
                    q.push(u);
                }
            }
        }
    }

    // Any remaining unclassified nodes are in cycles → draw (or handle per problem)
    return state;
}

/*
 * ============================================================
 *  MINIMAX ALGORITHM (for Partisan Games)
 * ============================================================
 *
 *  When two players have DIFFERENT objectives (maximize vs minimize),
 *  use Minimax:
 *
 *  maximizer's turn: pick move with MAXIMUM evaluation
 *  minimizer's turn: pick move with MINIMUM evaluation
 *
 *  ALPHA-BETA PRUNING:
 *  - alpha = best score maximizer can guarantee
 *  - beta  = best score minimizer can guarantee
 *  - If alpha >= beta, prune the subtree
 *
 *  Time: O(b^d) without pruning → O(b^(d/2)) with optimal pruning
 *  (b = branching factor, d = depth)
 * ============================================================
 */

// Example: Minimax on an array game (like Predict the Winner)
// Two players take from either end. Maximize your own score.
// dp[i][j] = max(current player's advantage) on subarray [i..j]
int minimaxArrayGame(vec<int>& nums) {
    int n = sz(nums);
    // dp[i][j] = best score difference the current player can achieve
    vvec<int> dp(n, vec<int>(n, 0));

    for (int i = 0; i < n; i++) dp[i][i] = nums[i];

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            // Current player picks left or right
            dp[i][j] = max(nums[i] - dp[i+1][j],  // pick left
                           nums[j] - dp[i][j-1]);   // pick right
        }
    }

    return dp[0][n-1];  // ≥ 0 means first player wins
}

/*
 * ============================================================
 *  CAT AND MOUSE GAME — BFS Game on Graph (LeetCode 913)
 * ============================================================
 *
 *  Graph game with TWO tokens and position-dependent rules.
 *  State: (mouse_pos, cat_pos, whose_turn)
 *
 *  BFS from terminal states (mouse at hole → mouse wins,
 *  mouse == cat → cat wins) backward to classify all states.
 *
 *  This is a 2-player game on a graph with ~O(n² × 2) states.
 * ============================================================
 */

// Simplified: determine winner from starting state
int catAndMouse(vvec<int>& graph) {
    int n = sz(graph);
    // state[mouse][cat][turn] : 0=draw, 1=mouse wins, 2=cat wins
    // turn: 0 = mouse's turn, 1 = cat's turn

    int state[51][51][2];
    int outdeg[51][51][2];
    memset(state, 0, sizeof(state));
    memset(outdeg, 0, sizeof(outdeg));

    // Compute out-degrees
    for (int m = 0; m < n; m++) {
        for (int c = 0; c < n; c++) {
            outdeg[m][c][0] = sz(graph[m]);      // mouse moves
            outdeg[m][c][1] = sz(graph[c]);       // cat moves
            // Cat cannot go to node 0 (hole)
            for (int next : graph[c]) {
                if (next == 0) outdeg[m][c][1]--;
            }
        }
    }

    // BFS from terminal states
    queue<tuple<int,int,int>> q;

    for (int i = 0; i < n; i++) {
        // Mouse at hole (0) → mouse wins (unless cat is also there which is invalid)
        for (int t = 0; t < 2; t++) {
            if (i != 0) {  // cat can't be at 0
                state[0][i][t] = 1;  // mouse wins
                q.push({0, i, t});
            }
        }
        // Mouse == Cat → cat wins
        if (i != 0) {
            for (int t = 0; t < 2; t++) {
                state[i][i][t] = 2;  // cat wins
                q.push({i, i, t});
            }
        }
    }

    while (!q.empty()) {
        auto [m, c, t] = q.front(); q.pop();
        int prevTurn = 1 - t;

        if (prevTurn == 0) {
            // Previous was mouse's turn → iterate over mouse's predecessors
            for (int pm : graph[m]) {
                if (state[pm][c][0] != 0) continue;
                if (state[m][c][t] == 1) {
                    // Mouse can move to a winning state
                    state[pm][c][0] = 1;
                    q.push({pm, c, 0});
                } else {
                    outdeg[pm][c][0]--;
                    if (outdeg[pm][c][0] == 0) {
                        state[pm][c][0] = 2;  // all moves lead to cat wins
                        q.push({pm, c, 0});
                    }
                }
            }
        } else {
            // Previous was cat's turn
            for (int pc : graph[c]) {
                if (pc == 0) continue;  // cat can't be at hole
                if (state[m][pc][1] != 0) continue;
                if (state[m][c][t] == 2) {
                    state[m][pc][1] = 2;
                    q.push({m, pc, 1});
                } else {
                    outdeg[m][pc][1]--;
                    if (outdeg[m][pc][1] == 0) {
                        state[m][pc][1] = 1;
                        q.push({m, pc, 1});
                    }
                }
            }
        }
    }

    return state[1][2][0];  // mouse at 1, cat at 2, mouse's turn
}

void solve() {
    int n, m;
    cin >> n >> m;

    vvec<int> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
    }

    vec<int> result = gameOnDAG(n, adj);

    // Output W/L for starting node 0
    if (result[0] == 1) cout << "First" << nl;
    else if (result[0] == 0) cout << "Second" << nl;
    else cout << "Draw" << nl;
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

