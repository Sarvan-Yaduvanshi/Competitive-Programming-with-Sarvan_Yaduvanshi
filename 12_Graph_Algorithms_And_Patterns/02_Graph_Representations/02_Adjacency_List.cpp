/*
╔══════════════════════════════════════════════════════════════════╗
║              02 — ADJACENCY LIST                                ║
║              Most Used Representation in CP                     ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

An ADJACENCY LIST stores, for each vertex, a list of its neighbors.

  adj[u] = list of all vertices v such that edge (u,v) exists.

  Implementation: vector<vector<int>> adj(n);

═══════════════════════════════════════════════════════════════════
VISUALIZATION
═══════════════════════════════════════════════════════════════════

Graph:
    1 ─── 2
    │   ╱ │
    │  ╱  │
    3     4
     ╲
      5

Edges: (1,2), (1,3), (2,3), (2,4), (3,5)

Adjacency List:
  1 → [2, 3]
  2 → [1, 3, 4]
  3 → [1, 2, 5]
  4 → [2]
  5 → [3]

DRY RUN of building:
  Read edge (1,2): adj[1].push_back(2), adj[2].push_back(1)
  Read edge (1,3): adj[1].push_back(3), adj[3].push_back(1)
  Read edge (2,3): adj[2].push_back(3), adj[3].push_back(2)
  Read edge (2,4): adj[2].push_back(4), adj[4].push_back(2)
  Read edge (3,5): adj[3].push_back(5), adj[5].push_back(3)

═══════════════════════════════════════════════════════════════════
WHEN TO USE
═══════════════════════════════════════════════════════════════════

  ✅ Almost ALL graph problems in CP
  ✅ BFS, DFS, Dijkstra, Bellman-Ford, etc.
  ✅ Sparse graphs (most CP graphs)
  ✅ Memory efficient: O(V + E)

  ❌ O(degree) to check if specific edge exists
     (use set/unordered_set if needed)

═══════════════════════════════════════════════════════════════════
COMPLEXITY
═══════════════════════════════════════════════════════════════════

  ┌────────────────────────────────────────────────┐
  │  Operation              │  Complexity          │
  ├─────────────────────────┼──────────────────────┤
  │  Space                  │  O(V + E)            │
  │  Add edge               │  O(1) amortized      │
  │  Remove edge            │  O(degree)           │
  │  Check if edge exists   │  O(degree)           │
  │  Iterate all neighbors  │  O(degree)           │
  │  Iterate all edges      │  O(V + E)            │
  └────────────────────────────────────────────────┘

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

void solve() {
    int n, m;
    cin >> n >> m;

    // --- Build Adjacency List (Undirected) ---
    vvec<int> adj(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    // --- Print Adjacency List ---
    cout << "Adjacency List:" << nl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << " → [";
        for (int j = 0; j < sz(adj[i]); j++) {
            if (j > 0) cout << ", ";
            cout << adj[i][j] + 1;
        }
        cout << "]" << nl;
    }

    // --- Iterate all edges (avoiding duplicates for undirected) ---
    cout << nl << "All edges:" << nl;
    int edgeCount = 0;
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            if (u < v) {  // print each edge once
                cout << "(" << u+1 << ", " << v+1 << ")" << nl;
                edgeCount++;
            }
        }
    }
    cout << "Total: " << edgeCount << " edges" << nl;

    // --- Memory usage comparison ---
    i64 listMemory = n * 24 + 2LL * m * 4;  // approximate bytes
    i64 matrixMemory = (i64)n * n * 4;
    cout << nl << "Approx memory:" << nl;
    cout << "Adj List:   ~" << listMemory << " bytes" << nl;
    cout << "Adj Matrix: ~" << matrixMemory << " bytes" << nl;
    cout << "Savings: " << fixed << setprecision(1)
         << (1.0 - (double)listMemory/matrixMemory) * 100 << "%" << nl;
}

/*
═══════════════════════════════════════════════════════════════════
SAMPLE INPUT/OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
1
5 5
1 2
1 3
2 3
2 4
3 5

Output:
Adjacency List:
1 → [2, 3]
2 → [1, 3, 4]
3 → [1, 2, 5]
4 → [2]
5 → [3]

All edges:
(1, 2)
(1, 3)
(2, 3)
(2, 4)
(3, 5)
Total: 5 edges

Approx memory:
Adj List:   ~160 bytes
Adj Matrix: ~100 bytes
Savings: -60.0%

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

