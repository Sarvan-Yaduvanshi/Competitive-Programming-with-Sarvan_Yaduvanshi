/*
╔══════════════════════════════════════════════════════════════════╗
║         09 — DIAL'S ALGORITHM                                   ║
║         Shortest path when weights are small integers [0, W]    ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

When edge weights are SMALL INTEGERS in [0, W], use bucket-based
BFS instead of Dijkstra's priority queue.

Maintain W+1 buckets. Process vertices from bucket 0, 1, 2, ...
When relaxing edge (u,v,w): add v to bucket dist[u]+w.

Time:  O(V × W + E) — better than Dijkstra when W is small
Space: O(V × W)

GENERALIZATION: 0-1 BFS is Dial's with W=1 (deque = 2 buckets).

═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
#endif
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
constexpr int INF = 2e9;
#define nl '\n'

void solve() {
    int n, m, W; // W = max edge weight
    cin >> n >> m >> W;

    vec<vec<pair<int,int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w; u--; v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int src; cin >> src; src--;

    vec<int> dist(n, INF);
    dist[src] = 0;

    int maxDist = (i64)n * W; // upper bound on distance
    vec<vec<int>> bucket(maxDist + 1);
    bucket[0].push_back(src);

    int idx = 0;
    for (int b = 0; b <= maxDist; b++) {
        for (int i = 0; i < (int)bucket[b].size(); i++) {
            int u = bucket[b][i];
            if (dist[u] != b) continue; // outdated

            for (auto [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    bucket[dist[v]].push_back(v);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << "dist[" << i+1 << "] = ";
        if (dist[i] == INF) cout << "INF"; else cout << dist[i];
        cout << nl;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

