/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 09.05 — STEINER TREE DP                                  ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Given a weighted graph and k terminal vertices (k ≤ 15-20),
    find the minimum-weight connected subgraph containing all terminals.

DP STATE: dp[mask][v] = minimum cost of a tree spanning the terminals in mask,
    rooted at vertex v.

TRANSITIONS:
════════════
    1. Merge two subtrees: dp[mask][v] = min over submasks s of mask
        dp[s][v] + dp[mask^s][v] - node_cost[v]  (avoid double-counting v)

    2. Extend by an edge: dp[mask][v] = min over neighbors u
        dp[mask][u] + edge_cost(u, v)

Algorithm: For each mask, first try all splits (merge), then relax edges (Dijkstra/BFS).

TIME: O(3^k × V + 2^k × V × E), where k = number of terminals

This is one of the hardest standard bitmask DP problems!

PRACTICE PROBLEMS:
══════════════════
    SPOJ: STEINERT
    Codeforces: 152E, 609F
*/
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int INF = 1e9;

int steinerTree(int V, vector<vector<pair<int,int>>>& adj, vector<int>& terminals) {
    int k = terminals.size();
    vector<vector<int>> dp(1 << k, vector<int>(V, INF));

    // Base: single terminal
    for (int i = 0; i < k; i++) dp[1 << i][terminals[i]] = 0;

    for (int mask = 1; mask < (1 << k); mask++) {
        // Step 1: Merge submasks
        for (int sub = (mask - 1) & mask; sub > 0; sub = (sub - 1) & mask) {
            int comp = mask ^ sub;
            if (sub < comp) continue; // avoid double counting
            for (int v = 0; v < V; v++) {
                if (dp[sub][v] < INF && dp[comp][v] < INF) {
                    dp[mask][v] = min(dp[mask][v], dp[sub][v] + dp[comp][v]);
                }
            }
        }

        // Step 2: Dijkstra-like relaxation
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        for (int v = 0; v < V; v++)
            if (dp[mask][v] < INF) pq.push({dp[mask][v], v});

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

    int fullMask = (1 << k) - 1;
    int ans = INF;
    for (int v = 0; v < V; v++) ans = min(ans, dp[fullMask][v]);
    return ans;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   STEINER TREE DP                               ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Simple graph: 0-1 (w=1), 1-2 (w=2), 0-2 (w=4), 1-3 (w=3)
    int V = 4;
    vector<vector<pair<int,int>>> adj(V);
    auto addEdge = [&](int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    };
    addEdge(0, 1, 1);
    addEdge(1, 2, 2);
    addEdge(0, 2, 4);
    addEdge(1, 3, 3);

    vector<int> terminals = {0, 2, 3}; // must connect these 3
    int ans = steinerTree(V, adj, terminals);
    cout << "  Terminals: {0, 2, 3}" << endl;
    cout << "  Min Steiner tree cost: " << ans << endl;
    // Optimal: 0-1(1) + 1-2(2) + 1-3(3) = 6

    cout << "\n✅ Steiner Tree DP demonstrated!" << endl;
    return 0;
}

