/*
╔══════════════════════════════════════════════════════════════════╗
║         05 — STEINER TREE (Bitmask DP)                          ║
║         Min cost tree connecting subset of terminal vertices    ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

Given a weighted graph and k TERMINAL vertices, find minimum weight
subgraph (tree) that connects all terminals.

NP-hard in general, but solvable for small k using bitmask DP.

STATE: dp[mask][v] = min cost tree connecting terminals in 'mask'
       that includes vertex v.

TRANSITIONS:
  1. Merge subtrees: dp[mask][v] = min over sub⊂mask of
     dp[sub][v] + dp[mask\sub][v]
  2. Extend tree: relax dp[mask][v] using Dijkstra/BFS
     dp[mask][u] = min(dp[mask][u], dp[mask][v] + w(v,u))

═══════════════════════════════════════════════════════════════════
COMPLEXITY
  Time:  O(3^k × n + 2^k × (n + m) log n)
  Space: O(2^k × n)
  Works for k ≤ 15-18 terminals
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pli = pair<i64, int>;
constexpr i64 INF64 = 4e18;
#define nl '\n'

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vec<vec<pair<int,i64>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v; i64 w; cin >> u >> v >> w; u--; v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vec<int> terminals(k);
    for (auto& t : terminals) { cin >> t; t--; }

    int FULL = (1 << k) - 1;
    vvec<i64> dp(1 << k, vec<i64>(n, INF64));

    // Base case: each terminal alone
    for (int i = 0; i < k; i++) {
        dp[1 << i][terminals[i]] = 0;
    }

    for (int mask = 1; mask <= FULL; mask++) {
        // Transition 1: Merge subtrees
        for (int sub = (mask - 1) & mask; sub > 0; sub = (sub - 1) & mask) {
            int comp = mask ^ sub;
            if (sub < comp) continue; // avoid double counting
            for (int v = 0; v < n; v++) {
                if (dp[sub][v] != INF64 && dp[comp][v] != INF64) {
                    dp[mask][v] = min(dp[mask][v], dp[sub][v] + dp[comp][v]);
                }
            }
        }

        // Transition 2: Dijkstra relaxation
        priority_queue<pli, vec<pli>, greater<pli>> pq;
        for (int v = 0; v < n; v++) {
            if (dp[mask][v] != INF64) pq.push({dp[mask][v], v});
        }
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dp[mask][u]) continue;
            for (auto [v, w] : adj[u]) {
                if (dp[mask][u] + w < dp[mask][v]) {
                    dp[mask][v] = dp[mask][u] + w;
                    pq.push({dp[mask][v], v});
                }
            }
        }
    }

    i64 ans = INF64;
    for (int v = 0; v < n; v++) ans = min(ans, dp[FULL][v]);

    cout << "Minimum Steiner tree cost: " << (ans == INF64 ? -1 : ans) << nl;
}

/*
Input: 1\n5 6 3\n1 2 1\n2 3 2\n3 4 3\n4 5 4\n1 3 10\n2 5 7\n1 3 5
Output: Minimum Steiner tree cost: 6 (connecting 1,3,5 via 1-2-3 and 2-5)
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

