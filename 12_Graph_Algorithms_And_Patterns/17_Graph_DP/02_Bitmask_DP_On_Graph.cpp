/*
╔══════════════════════════════════════════════════════════════════╗
║              02 — BITMASK DP ON GRAPH                           ║
║              TSP / Hamiltonian Path using dp[mask][v]           ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

HAMILTONIAN PATH: visits every vertex exactly once.
TSP: find minimum-cost Hamiltonian cycle.

Both are NP-hard in general, but solvable with bitmask DP
when n ≤ 20.

STATE: dp[mask][v] = min cost to visit exactly the vertices in 'mask',
       ending at vertex v.

TRANSITION:
  dp[mask | (1<<u)][u] = min(dp[mask][v] + cost[v][u])
  for all v in mask, u not in mask, edge v→u exists.

BASE: dp[1<<start][start] = 0

ANSWER (TSP): min over all v of dp[(1<<n)-1][v] + cost[v][start]
ANSWER (Hamiltonian path): min over all v of dp[(1<<n)-1][v]

═══════════════════════════════════════════════════════════════════
DRY RUN (n=3, complete graph)
═══════════════════════════════════════════════════════════════════

Vertices: 0, 1, 2
Cost matrix:     0   1   2
              0 [ -  10  15]
              1 [10   -  20]
              2 [15  20   -]

Start at 0: dp[001][0] = 0

From 0→1: dp[011][1] = dp[001][0] + 10 = 10
From 0→2: dp[101][2] = dp[001][0] + 15 = 15

From 1→2: dp[111][2] = dp[011][1] + 20 = 30
From 2→1: dp[111][1] = dp[101][2] + 20 = 35

Hamiltonian path: min(dp[111][1], dp[111][2]) = min(35, 30) = 30
TSP: dp[111][2] + cost[2][0] = 30 + 15 = 45
     dp[111][1] + cost[1][0] = 35 + 10 = 45

═══════════════════════════════════════════════════════════════════
COMPLEXITY
  Time:  O(2^n × n²)    Space: O(2^n × n)
  Works for n ≤ 20 (2^20 ≈ 10^6)
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
constexpr i64 INF64 = 4e18;
#define nl '\n'

void solve() {
    int n, m;
    cin >> n >> m;

    vvec<i64> cost(n, vec<i64>(n, INF64));
    for (int i = 0; i < n; i++) cost[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v; i64 w;
        cin >> u >> v >> w; u--; v--;
        cost[u][v] = min(cost[u][v], w);
        cost[v][u] = min(cost[v][u], w); // undirected
    }

    int FULL = (1 << n) - 1;

    // dp[mask][v] = min cost visiting vertices in mask, ending at v
    vvec<i64> dp(1 << n, vec<i64>(n, INF64));

    // Start from vertex 0
    dp[1][0] = 0;

    for (int mask = 1; mask <= FULL; mask++) {
        for (int v = 0; v < n; v++) {
            if (dp[mask][v] == INF64) continue;
            if (!(mask & (1 << v))) continue;

            // Try extending to unvisited vertex u
            for (int u = 0; u < n; u++) {
                if (mask & (1 << u)) continue; // already visited
                if (cost[v][u] == INF64) continue; // no edge

                int newMask = mask | (1 << u);
                dp[newMask][u] = min(dp[newMask][u], dp[mask][v] + cost[v][u]);
            }
        }
    }

    // Hamiltonian path: min cost to visit all vertices
    i64 hamPath = INF64;
    for (int v = 0; v < n; v++) {
        hamPath = min(hamPath, dp[FULL][v]);
    }

    // TSP: return to start vertex 0
    i64 tsp = INF64;
    for (int v = 0; v < n; v++) {
        if (dp[FULL][v] != INF64 && cost[v][0] != INF64) {
            tsp = min(tsp, dp[FULL][v] + cost[v][0]);
        }
    }

    cout << "Hamiltonian path min cost: " << (hamPath == INF64 ? -1 : hamPath) << nl;
    cout << "TSP min cost: " << (tsp == INF64 ? -1 : tsp) << nl;
}

/*
Input: 1\n4 6\n1 2 10\n1 3 15\n1 4 20\n2 3 25\n2 4 30\n3 4 35
Output:
Hamiltonian path min cost: 55 (0→1→2→3: 10+25+35=70 or 0→2→1→3: 15+25+30=70...)
TSP min cost: 95 (optimal tour)
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

