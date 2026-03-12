/*
╔══════════════════════════════════════════════════════════════════╗
║              06 — SHORTEST PATH IN DAG                          ║
║              Topo sort + relaxation O(V+E)                      ║
╚══════════════════════════════════════════════════════════════════╝

For DAGs, process vertices in topological order and relax edges.
Handles negative weights! Faster than Dijkstra for DAGs.

Time: O(V+E)    Space: O(V+E)
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
using pii = pair<int,i64>;
constexpr i64 INF64 = 4e18;
#define pb push_back
#define nl '\n'

void solve() {
    int n, m; cin >> n >> m;
    vec<vec<pii>> adj(n);
    vec<int> inDeg(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v; i64 w; cin >> u >> v >> w; u--; v--;
        adj[u].pb({v, w}); inDeg[v]++;
    }
    int src; cin >> src; src--;

    // Topological sort
    queue<int> q;
    for (int i = 0; i < n; i++) if (!inDeg[i]) q.push(i);
    vec<int> topo;
    while (!q.empty()) {
        int u = q.front(); q.pop(); topo.pb(u);
        for (auto [v, w] : adj[u]) if (--inDeg[v]==0) q.push(v);
    }

    // Relax in topological order
    vec<i64> dist(n, INF64);
    dist[src] = 0;
    for (int u : topo) {
        if (dist[u] == INF64) continue;
        for (auto [v, w] : adj[u]) {
            dist[v] = min(dist[v], dist[u] + w);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << "dist[" << i+1 << "] = ";
        cout << (dist[i]==INF64 ? "INF" : to_string(dist[i])) << nl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

