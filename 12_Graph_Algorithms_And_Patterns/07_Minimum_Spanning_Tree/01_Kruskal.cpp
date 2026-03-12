/*
╔══════════════════════════════════════════════════════════════════╗
║              01 — KRUSKAL'S ALGORITHM                           ║
║              MST using sorted edges + Union-Find                ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

A MINIMUM SPANNING TREE (MST) of a connected weighted undirected
graph is a subset of edges that:
  ✅ Connects all vertices (spanning)
  ✅ Forms a tree (no cycles, exactly n-1 edges)
  ✅ Has minimum total weight

KRUSKAL'S ALGORITHM:
  1. Sort all edges by weight
  2. For each edge (u, v, w) in sorted order:
     If u and v are in DIFFERENT components → add edge to MST
     (Use Union-Find/DSU to check and merge components)
  3. Stop when MST has n-1 edges

═══════════════════════════════════════════════════════════════════
DRY RUN
═══════════════════════════════════════════════════════════════════

Graph:
    1 ──(4)── 2
    │         │
   (1)       (3)
    │         │
    3 ──(2)── 4 ──(5)── 5

Edges sorted: (1,3,1), (3,4,2), (2,4,3), (1,2,4), (4,5,5)

Step │ Edge      │ Components        │ Action     │ MST weight
═════╪═══════════╪═══════════════════╪════════════╪═══════════
  1  │ (1,3,1)   │ {1,3},{2},{4},{5} │ ADD        │ 1
  2  │ (3,4,2)   │ {1,3,4},{2},{5}   │ ADD        │ 3
  3  │ (2,4,3)   │ {1,2,3,4},{5}     │ ADD        │ 6
  4  │ (1,2,4)   │ same component    │ SKIP(cycle)│ 6
  5  │ (4,5,5)   │ {1,2,3,4,5}      │ ADD        │ 11

MST edges: (1,3), (3,4), (2,4), (4,5)    Total weight: 11

═══════════════════════════════════════════════════════════════════
COMPLEXITY
═══════════════════════════════════════════════════════════════════
  Time:  O(E log E) for sorting + O(E α(V)) for DSU ≈ O(E log E)
  Space: O(V + E)

═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
#define sz(x) ((int)(x).size())
#define nl '\n'

// ============================
// UNION-FIND (DSU) for Kruskal
// ============================
struct DSU {
    vec<int> parent, rank_;
    int components;

    DSU(int n) : parent(n), rank_(n, 0), components(n) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        while (parent[x] != x) x = parent[x] = parent[parent[x]]; // path compression
        return x;
    }

    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rank_[a] < rank_[b]) swap(a, b);
        parent[b] = a;
        if (rank_[a] == rank_[b]) rank_[a]++;
        components--;
        return true;
    }
};

struct Edge {
    int u, v;
    i64 w;
    bool operator<(const Edge& o) const { return w < o.w; }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vec<Edge> edges(m);
    for (auto& [u, v, w] : edges) {
        cin >> u >> v >> w; u--; v--;
    }

    // KRUSKAL'S ALGORITHM
    sort(edges.begin(), edges.end());  // Sort by weight

    DSU dsu(n);
    i64 mstWeight = 0;
    vec<Edge> mstEdges;

    for (auto& [u, v, w] : edges) {
        if (dsu.unite(u, v)) {
            mstWeight += w;
            mstEdges.push_back({u, v, w});
            if (sz(mstEdges) == n - 1) break;
        }
    }

    if (sz(mstEdges) != n - 1) {
        cout << "Graph is not connected — no MST!" << nl;
    } else {
        cout << "MST weight: " << mstWeight << nl;
        cout << "MST edges:" << nl;
        for (auto& [u, v, w] : mstEdges) {
            cout << "  " << u+1 << " — " << v+1 << " (w=" << w << ")" << nl;
        }
    }
}

/*
Input: 1\n5 6\n1 3 1\n3 4 2\n2 4 3\n1 2 4\n4 5 5\n2 5 7
Output:
MST weight: 11
MST edges:
  1 — 3 (w=1)
  3 — 4 (w=2)
  2 — 4 (w=3)
  4 — 5 (w=5)
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

