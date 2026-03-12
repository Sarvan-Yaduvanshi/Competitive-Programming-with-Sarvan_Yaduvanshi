/*
╔══════════════════════════════════════════════════════════════════╗
║         08 — JOHNSON'S ALGORITHM                                ║
║         All-pairs shortest path for sparse graphs               ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

Johnson's combines Bellman-Ford + Dijkstra for ALL-PAIRS shortest
paths. Better than Floyd-Warshall for SPARSE graphs.

IDEA:
  1. Add dummy vertex 0 connected to all vertices with weight 0
  2. Run Bellman-Ford from 0 → get potential h[v] for each vertex
  3. Reweight: w'(u,v) = w(u,v) + h[u] - h[v] ≥ 0 (no negatives!)
  4. Run Dijkstra from EACH vertex on reweighted graph
  5. Convert back: dist(u,v) = dist'(u,v) - h[u] + h[v]

═══════════════════════════════════════════════════════════════════
WHEN TO USE
═══════════════════════════════════════════════════════════════════

  Floyd-Warshall: O(V³)        — better for dense graphs
  Johnson's:     O(VE + V(V+E)logV) — better for sparse graphs

  If E ≈ V²: Floyd wins.  If E ≈ V: Johnson wins.

═══════════════════════════════════════════════════════════════════
DRY RUN
═══════════════════════════════════════════════════════════════════

Graph: 1→2(3), 2→3(-2), 1→3(8)

Step 1: Add vertex 0: 0→1(0), 0→2(0), 0→3(0)
Step 2: Bellman-Ford from 0: h = [0, 0, 0, -2]
  (h[3] = -2 because 0→2(0)→3(-2) = -2)
Step 3: Reweight:
  1→2: 3 + 0 - 0 = 3
  2→3: -2 + 0 - (-2) = 0
  1→3: 8 + 0 - (-2) = 10
  All non-negative! ✅
Step 4: Dijkstra from each vertex on reweighted graph
Step 5: Convert back

Time: O(VE + V(V+E)logV)    Space: O(V² + E)
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
#include <climits>
using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pli = pair<i64, int>;
constexpr i64 INF64 = 4e18;
#define sz(x) ((int)(x).size())
#define nl '\n'

void solve() {
    int n, m; cin >> n >> m;

    struct Edge { int u, v; i64 w; };
    vec<Edge> edges(m);
    vec<vec<pair<int,i64>>> adj(n);

    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].u--; edges[i].v--;
        adj[edges[i].u].push_back({edges[i].v, edges[i].w});
    }

    // Step 1-2: Bellman-Ford from virtual vertex (distance 0 to all)
    vec<i64> h(n, 0); // h[v] = shortest dist from virtual source
    for (int iter = 0; iter < n - 1; iter++) {
        for (auto& [u, v, w] : edges) {
            if (h[u] + w < h[v]) h[v] = h[u] + w;
        }
    }

    // Check negative cycle
    for (auto& [u, v, w] : edges) {
        if (h[u] + w < h[v]) {
            cout << "Negative cycle detected!" << nl;
            return;
        }
    }

    // Step 3: Reweight edges
    vec<vec<pair<int,i64>>> radj(n);
    for (auto& [u, v, w] : edges) {
        i64 nw = w + h[u] - h[v]; // guaranteed non-negative
        radj[u].push_back({v, nw});
    }

    // Step 4: Dijkstra from each vertex
    vvec<i64> dist(n, vec<i64>(n, INF64));

    for (int src = 0; src < n; src++) {
        auto& d = dist[src];
        d[src] = 0;
        priority_queue<pli, vec<pli>, greater<pli>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [dd, u] = pq.top(); pq.pop();
            if (dd > d[u]) continue;
            for (auto [v, w] : radj[u]) {
                if (d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    pq.push({d[v], v});
                }
            }
        }

        // Step 5: Convert back
        for (int v = 0; v < n; v++) {
            if (d[v] != INF64) d[v] = d[v] - h[src] + h[v];
        }
    }

    // Output
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF64) cout << "INF";
            else cout << dist[i][j];
            cout << " \n"[j==n-1];
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

