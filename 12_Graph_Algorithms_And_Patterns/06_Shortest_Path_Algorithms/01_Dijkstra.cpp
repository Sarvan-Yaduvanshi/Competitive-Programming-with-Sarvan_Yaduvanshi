/*
╔══════════════════════════════════════════════════════════════════╗
║              01 — DIJKSTRA'S ALGORITHM                          ║
║              Single-Source Shortest Path (Non-negative weights)  ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

Dijkstra finds shortest paths from a single source to ALL vertices
in a graph with NON-NEGATIVE edge weights.

IDEA: Greedily process the closest unprocessed vertex.

ALGORITHM:
  1. Set dist[source] = 0, dist[all others] = INF
  2. Use priority queue (min-heap) with (dist, vertex)
  3. While PQ not empty:
     a. Pop (d, u) with minimum distance
     b. If d > dist[u], skip (outdated entry)
     c. For each neighbor v of u:
        If dist[u] + w(u,v) < dist[v]:
          Update dist[v] = dist[u] + w(u,v)
          Push (dist[v], v) to PQ

═══════════════════════════════════════════════════════════════════
DRY RUN
═══════════════════════════════════════════════════════════════════

Graph (undirected, weighted):
    1 ──(4)── 2
    │         │
   (1)       (2)
    │         │
    3 ──(5)── 4
    │
   (3)
    │
    5

Source: vertex 1

Step │ PQ (dist,vertex)        │ Process │ dist[] updates
═════╪═════════════════════════╪═════════╪══════════════════════
  0  │ [(0,1)]                 │    -    │ dist=[0,∞,∞,∞,∞]
  1  │ [(1,3),(4,2)]           │  (0,1)  │ dist=[0,4,1,∞,∞]
  2  │ [(4,2),(4,5),(6,4)]     │  (1,3)  │ dist=[0,4,1,6,4]
  3  │ [(4,5),(6,4),(6,4)]     │  (4,2)  │ dist=[0,4,1,6,4]
  4  │ [(6,4),(6,4)]           │  (4,5)  │ (no improvement)
  5  │ [(6,4)]                 │  (6,4)  │ (no improvement)
  6  │ []                      │  (6,4)  │ DONE

Final: dist = [0, 4, 1, 6, 4]
Paths: 1→1(0), 1→2(4), 1→3(1), 1→3→4(6), 1→3→5(4)

═══════════════════════════════════════════════════════════════════
COMPLEXITY
═══════════════════════════════════════════════════════════════════

  With binary heap (priority_queue):
    Time:  O((V + E) × log V)
    Space: O(V + E)

  With Fibonacci heap (theoretical):
    Time:  O(V log V + E)

  ⚠️ DOES NOT WORK with negative edge weights!

═══════════════════════════════════════════════════════════════════
WHY DIJKSTRA WORKS (Greedy Proof Sketch)
═══════════════════════════════════════════════════════════════════

When we pop vertex u from PQ, dist[u] is FINAL (optimal).
Proof: All paths to u through unprocessed vertices have dist ≥ dist[u]
because all edge weights are non-negative. So no shorter path exists.

═══════════════════════════════════════════════════════════════════
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
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

constexpr i64 INF64 = 4e18;
#define sz(x) ((int)(x).size())
#define pb push_back
#define fi first
#define se second
#define nl '\n'

void solve() {
    int n, m;
    cin >> n >> m;

    vec<vec<pair<int, i64>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v; i64 w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].pb({v, w});
        adj[v].pb({u, w});  // undirected
    }

    int src;
    cin >> src;
    src--;

    // ========================================
    // DIJKSTRA'S ALGORITHM
    // ========================================
    vec<i64> dist(n, INF64);
    vec<int> parent(n, -1);

    // Min-heap: (distance, vertex)
    priority_queue<pll, vec<pll>, greater<pll>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();

        if (d > dist[u]) continue;  // Skip outdated entries

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    // Output
    cout << "Shortest distances from vertex " << src+1 << ":" << nl;
    for (int i = 0; i < n; i++) {
        cout << "  " << src+1 << " → " << i+1 << ": ";
        if (dist[i] == INF64) cout << "UNREACHABLE";
        else {
            cout << dist[i];
            // Reconstruct path
            vec<int> path;
            for (int v = i; v != -1; v = parent[v]) path.pb(v);
            reverse(path.begin(), path.end());
            cout << " (path: ";
            for (int j = 0; j < sz(path); j++) {
                if (j) cout << "→";
                cout << path[j]+1;
            }
            cout << ")";
        }
        cout << nl;
    }
}

/*
═══════════════════════════════════════════════════════════════════
SAMPLE INPUT/OUTPUT

Input:
1
5 6
1 2 4
1 3 1
2 4 2
3 4 5
3 5 3
4 5 1
1

Output:
Shortest distances from vertex 1:
  1 → 1: 0 (path: 1)
  1 → 2: 4 (path: 1→2)
  1 → 3: 1 (path: 1→3)
  1 → 4: 6 (path: 1→2→4)
  1 → 5: 4 (path: 1→3→5)

═══════════════════════════════════════════════════════════════════
KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
  ✅ Dijkstra = greedy, works for non-negative weights only
  ✅ O((V+E) log V) with binary heap — fast enough for most CP
  ✅ Use pair<long long, int> for large weights
  ✅ Skip outdated PQ entries with: if (d > dist[u]) continue;
  ✅ For negative weights → use Bellman-Ford instead
═══════════════════════════════════════════════════════════════════
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

