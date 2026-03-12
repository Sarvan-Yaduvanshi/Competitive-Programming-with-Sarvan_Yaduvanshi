/*
╔══════════════════════════════════════════════════════════════════╗
║              03 — TYPES OF GRAPHS                               ║
║              Directed, Undirected, Weighted, DAG, Bipartite     ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
1. UNDIRECTED GRAPH
═══════════════════════════════════════════════════════════════════

  Edge (u, v) = Edge (v, u). No direction.

      1 ─── 2
      │     │
      3 ─── 4

  If 1 connects to 2, then 2 also connects to 1.
  In adjacency list: adj[u].push_back(v) AND adj[v].push_back(u)

═══════════════════════════════════════════════════════════════════
2. DIRECTED GRAPH (DIGRAPH)
═══════════════════════════════════════════════════════════════════

  Edge (u → v) ≠ Edge (v → u). Edges have direction.

      1 ──→ 2
      ↑     │
      │     ↓
      3 ←── 4

  If 1 → 2 exists, it does NOT mean 2 → 1 exists.
  In adjacency list: adj[u].push_back(v) ONLY

═══════════════════════════════════════════════════════════════════
3. WEIGHTED GRAPH
═══════════════════════════════════════════════════════════════════

  Each edge has a WEIGHT (cost, distance, capacity).

      1 ──5── 2
      │       │
      3       7
      │       │
      3 ──2── 4

  Edge (1,2) has weight 5, edge (3,4) has weight 2.
  Store as: adj[u].push_back({v, w})

═══════════════════════════════════════════════════════════════════
4. UNWEIGHTED GRAPH
═══════════════════════════════════════════════════════════════════

  All edges have the same cost (implicitly 1).
  Most BFS problems use unweighted graphs.

═══════════════════════════════════════════════════════════════════
5. CYCLIC vs ACYCLIC GRAPH
═══════════════════════════════════════════════════════════════════

  CYCLIC: Contains at least one cycle.
      1 → 2 → 3 → 1  (cycle!)

  ACYCLIC: Contains no cycles.
      1 → 2 → 3     (no way back)

  DAG = Directed Acyclic Graph
    - Used in: topological sort, DP on graphs, scheduling

  TREE = Undirected Acyclic Connected Graph
    - n vertices, n-1 edges, unique path between any two vertices

═══════════════════════════════════════════════════════════════════
6. SPARSE vs DENSE GRAPH
═══════════════════════════════════════════════════════════════════

  SPARSE: m ≈ O(n)     (few edges relative to vertices)
    → Use adjacency LIST

  DENSE: m ≈ O(n²)     (many edges, close to complete graph)
    → Can use adjacency MATRIX

  COMPLETE GRAPH K_n: Every pair of vertices is connected.
    - Edges = n*(n-1)/2

  ┌────────────────────────────────────────────────────────┐
  │  Graph Type  │  Edge Count  │  Best Representation    │
  ├──────────────┼──────────────┼─────────────────────────┤
  │  Sparse      │  ≈ n         │  Adjacency List         │
  │  Dense       │  ≈ n²        │  Adjacency Matrix       │
  │  Complete    │  n(n-1)/2    │  Adjacency Matrix       │
  └────────────────────────────────────────────────────────┘

═══════════════════════════════════════════════════════════════════
7. BIPARTITE GRAPH
═══════════════════════════════════════════════════════════════════

  Vertices can be split into TWO sets such that every edge
  connects a vertex from Set A to a vertex from Set B.
  NO edge within the same set.

      Set A: {1, 3, 5}     Set B: {2, 4, 6}

      1 ─── 2
      │     │
      3 ─── 4
      │     │
      5 ─── 6

  A graph is bipartite ⟺ it contains no ODD-length cycle.

═══════════════════════════════════════════════════════════════════
8. SPECIAL GRAPH TYPES
═══════════════════════════════════════════════════════════════════

  TREE:       Connected, acyclic, n-1 edges
  FOREST:     Collection of trees (acyclic, not necessarily connected)
  DAG:        Directed acyclic graph
  COMPLETE:   Every pair connected (K_n)
  BIPARTITE:  2-colorable, no odd cycles
  PLANAR:     Can be drawn on a plane without edge crossings

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

#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

template<class T>
void read(vec<T> &v) { for (auto &x : v) cin >> x; }

/*
═══════════════════════════════════════════════════════════════════
CODE: Classify a given graph
═══════════════════════════════════════════════════════════════════
*/

void solve() {
    int n, m;
    bool directed;
    cin >> n >> m >> directed;
    // directed = 1 for directed, 0 for undirected

    vvec<int> adj(n);
    vec<int> inDeg(n, 0), outDeg(n, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        outDeg[u]++;
        inDeg[v]++;
        if (!directed) {
            adj[v].pb(u);
            outDeg[v]++;
            inDeg[u]++;
        }
    }

    // --- Check if connected (undirected) or weakly connected ---
    vec<bool> vis(n, false);
    queue<int> q;
    q.push(0);
    vis[0] = true;
    int visited_count = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        visited_count++;
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    bool connected = (visited_count == n);

    // --- Check if bipartite (2-colorable) ---
    vec<int> color(n, -1);
    bool bipartite = true;
    for (int i = 0; i < n && bipartite; i++) {
        if (color[i] != -1) continue;
        color[i] = 0;
        queue<int> bq;
        bq.push(i);
        while (!bq.empty() && bipartite) {
            int u = bq.front(); bq.pop();
            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    bq.push(v);
                } else if (color[v] == color[u]) {
                    bipartite = false;
                }
            }
        }
    }

    // --- Classify ---
    cout << "=== Graph Classification ===" << nl;
    cout << "Vertices: " << n << ", Edges: " << m << nl;
    cout << "Type: " << (directed ? "Directed" : "Undirected") << nl;
    cout << "Connected: " << (connected ? "Yes" : "No") << nl;
    cout << "Bipartite: " << (bipartite ? "Yes" : "No") << nl;

    // Sparse vs Dense
    i64 maxEdges = directed ? (i64)n * (n - 1) : (i64)n * (n - 1) / 2;
    double density = (double)m / maxEdges;
    cout << "Density: " << fixed << setprecision(2) << density * 100 << "%" << nl;
    cout << "Classification: " << (density > 0.5 ? "Dense" : "Sparse") << nl;

    // Is it a tree?
    if (!directed && connected && m == n - 1) {
        cout << "This is a TREE!" << nl;
    }

    // Is it a forest?
    if (!directed && !connected && bipartite && m < n) {
        cout << "This might be a FOREST!" << nl;
    }
}

/*
═══════════════════════════════════════════════════════════════════
SAMPLE INPUT/OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
1
6 7 0
1 2
2 3
3 4
4 5
5 6
6 1
2 5

Output:
=== Graph Classification ===
Vertices: 6, Edges: 7
Type: Undirected
Connected: Yes
Bipartite: No
Density: 46.67%
Classification: Sparse
═══════════════════════════════════════════════════════════════════
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);
    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    return 0;
}

