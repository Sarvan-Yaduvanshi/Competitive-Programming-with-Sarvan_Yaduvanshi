/*
╔══════════════════════════════════════════════════════════════════╗
║              02 — BELLMAN-FORD ALGORITHM                        ║
║              Handles negative weights + detects negative cycles  ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

Bellman-Ford finds shortest paths from single source.
Unlike Dijkstra, it handles NEGATIVE EDGE WEIGHTS.
Also detects NEGATIVE WEIGHT CYCLES.

ALGORITHM:
  1. Set dist[source] = 0, dist[others] = INF
  2. Repeat V-1 times:
     For each edge (u, v, w):
       If dist[u] + w < dist[v]: dist[v] = dist[u] + w
  3. One more iteration: if any distance decreases → NEGATIVE CYCLE

WHY V-1 iterations?
  Shortest path has at most V-1 edges (in a simple path).
  Each iteration relaxes paths of one more edge.
  After k iterations, all shortest paths using ≤ k edges are correct.

═══════════════════════════════════════════════════════════════════
DRY RUN
═══════════════════════════════════════════════════════════════════

Graph: 1→2(4), 1→3(3), 2→3(-2), 3→4(1)
Source: 1

Iteration 1:
  Edge(1,2,4):  dist[2] = min(∞, 0+4) = 4
  Edge(1,3,3):  dist[3] = min(∞, 0+3) = 3
  Edge(2,3,-2): dist[3] = min(3, 4-2) = 2  ← negative weight helps!
  Edge(3,4,1):  dist[4] = min(∞, 2+1) = 3

Iteration 2:
  Edge(2,3,-2): dist[3] = min(2, 4-2) = 2 (no change)
  Edge(3,4,1):  dist[4] = min(3, 2+1) = 3 (no change)

Final: dist = [0, 4, 2, 3]

═══════════════════════════════════════════════════════════════════
COMPLEXITY
═══════════════════════════════════════════════════════════════════

  Time:  O(V × E)
  Space: O(V)

  Slower than Dijkstra, but handles negative weights!
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
constexpr i64 INF64 = 4e18;
#define sz(x) ((int)(x).size())
#define nl '\n'

struct Edge { int u, v; i64 w; };

void solve() {
    int n, m;
    cin >> n >> m;

    vec<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].u--; edges[i].v--;
    }

    int src;
    cin >> src; src--;

    vec<i64> dist(n, INF64);
    vec<int> parent(n, -1);
    dist[src] = 0;

    // V-1 iterations
    for (int iter = 0; iter < n - 1; iter++) {
        bool updated = false;
        for (auto& [u, v, w] : edges) {
            if (dist[u] != INF64 && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                updated = true;
            }
        }
        if (!updated) break;  // Early termination
    }

    // Check for negative cycle (V-th iteration)
    bool negCycle = false;
    for (auto& [u, v, w] : edges) {
        if (dist[u] != INF64 && dist[u] + w < dist[v]) {
            negCycle = true;
            break;
        }
    }

    if (negCycle) {
        cout << "NEGATIVE CYCLE DETECTED!" << nl;
    } else {
        cout << "Shortest distances from " << src+1 << ":" << nl;
        for (int i = 0; i < n; i++) {
            cout << "  → " << i+1 << ": ";
            if (dist[i] == INF64) cout << "INF";
            else cout << dist[i];
            cout << nl;
        }
    }
}

/*
Input: 1\n4 4\n1 2 4\n1 3 3\n2 3 -2\n3 4 1\n1
Output:
Shortest distances from 1:
  → 1: 0
  → 2: 4
  → 3: 2
  → 4: 3
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

