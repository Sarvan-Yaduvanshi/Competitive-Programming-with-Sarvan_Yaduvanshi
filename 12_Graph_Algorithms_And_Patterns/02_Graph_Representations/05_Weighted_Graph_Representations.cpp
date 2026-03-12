/*
╔══════════════════════════════════════════════════════════════════╗
║              05 — WEIGHTED GRAPH REPRESENTATIONS                ║
║              Storing weights in all representations             ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
3 WAYS TO STORE WEIGHTED GRAPHS
═══════════════════════════════════════════════════════════════════

METHOD 1: Adjacency List with pair
  vector<vector<pair<int,int>>> adj(n);
  adj[u].push_back({v, weight});

METHOD 2: Adjacency Matrix
  int dist[N][N];  // dist[u][v] = weight, INF if no edge

METHOD 3: Edge List (struct)
  struct Edge { int u, v, w; };
  vector<Edge> edges;

═══════════════════════════════════════════════════════════════════
COMPARISON FOR WEIGHTED GRAPHS
═══════════════════════════════════════════════════════════════════

  ┌─────────────────────────────────────────────────────────────┐
  │  Method          │  Space    │  Best For                    │
  ├──────────────────┼───────────┼──────────────────────────────┤
  │  Adj List + pair │  O(V+E)   │  Dijkstra, BFS, DFS          │
  │  Adj Matrix      │  O(V²)    │  Floyd-Warshall, small V     │
  │  Edge List       │  O(E)     │  Kruskal, Bellman-Ford        │
  └─────────────────────────────────────────────────────────────┘

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

constexpr int INF32 = 2e9;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

void solve() {
    int n, m;
    cin >> n >> m;

    // Method 1: Adjacency List with pairs
    vec<vec<pii>> adjList(n);

    // Method 2: Adjacency Matrix (only if n is small)
    vvec<int> adjMat(n, vec<int>(n, INF32));
    for (int i = 0; i < n; i++) adjMat[i][i] = 0;

    // Method 3: Edge List
    struct Edge { int u, v, w; };
    vec<Edge> edges;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;

        // Store in all three
        adjList[u].pb({v, w});
        adjList[v].pb({u, w});

        adjMat[u][v] = min(adjMat[u][v], w);  // handle multi-edges
        adjMat[v][u] = min(adjMat[v][u], w);

        edges.pb({u, v, w});
    }

    // Print adjacency list
    cout << "=== Adjacency List ===" << nl;
    for (int i = 0; i < n; i++) {
        cout << i+1 << ": ";
        for (auto [v, w] : adjList[i]) {
            cout << "(" << v+1 << ",w=" << w << ") ";
        }
        cout << nl;
    }

    // Print adjacency matrix
    cout << nl << "=== Adjacency Matrix ===" << nl;
    cout << "    ";
    for (int j = 0; j < n; j++) cout << setw(4) << j+1;
    cout << nl;
    for (int i = 0; i < n; i++) {
        cout << setw(2) << i+1 << " [";
        for (int j = 0; j < n; j++) {
            if (adjMat[i][j] == INF32) cout << " INF";
            else cout << setw(4) << adjMat[i][j];
        }
        cout << " ]" << nl;
    }

    // Print edge list
    cout << nl << "=== Edge List ===" << nl;
    for (auto& [u, v, w] : edges) {
        cout << u+1 << " — " << v+1 << " (w=" << w << ")" << nl;
    }
}

/*
═══════════════════════════════════════════════════════════════════
SAMPLE INPUT/OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
1
4 5
1 2 3
1 3 1
2 3 7
2 4 5
3 4 2

Output:
=== Adjacency List ===
1: (2,w=3) (3,w=1)
2: (1,w=3) (3,w=7) (4,w=5)
3: (1,w=1) (2,w=7) (4,w=2)
4: (2,w=5) (3,w=2)

=== Adjacency Matrix ===
       1   2   3   4
 1 [   0   3   1 INF ]
 2 [   3   0   7   5 ]
 3 [   1   7   0   2 ]
 4 [ INF   5   2   0 ]

=== Edge List ===
1 — 2 (w=3)
1 — 3 (w=1)
2 — 3 (w=7)
2 — 4 (w=5)
3 — 4 (w=2)
═══════════════════════════════════════════════════════════════════
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    return 0;
}

