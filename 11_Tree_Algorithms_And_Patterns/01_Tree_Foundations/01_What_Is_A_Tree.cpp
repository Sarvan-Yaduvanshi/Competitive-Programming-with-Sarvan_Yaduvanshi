/*
╔══════════════════════════════════════════════════════════════════╗
║       01 — WHAT IS A TREE? (Definition & Properties)            ║
║       Zero to GM Level — Tree Foundations                        ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 DEFINITION
═══════════════════════════════════════════════════════════════════

 A TREE is a connected, undirected graph with NO CYCLES.

 Equivalent definitions (ALL are the same!):
   1. Connected graph with N nodes and N-1 edges
   2. Connected acyclic graph
   3. Graph where there is EXACTLY ONE path between any two nodes
   4. Minimally connected graph (removing any edge disconnects it)
   5. Maximally acyclic graph (adding any edge creates a cycle)

═══════════════════════════════════════════════════════════════════
 VISUALIZATION
═══════════════════════════════════════════════════════════════════

 THIS IS A TREE (N=7, edges=6):

         1
        / \
       2   3
      / \   \
     4   5   6
    /
   7

 ✅ Connected: can reach any node from any other
 ✅ N-1 edges: 7 nodes, 6 edges
 ✅ No cycles: no way to start at a node and return without backtracking
 ✅ Unique path: exactly one path from 7 to 6 (7→4→2→1→3→6)

 THIS IS NOT A TREE:

     1 — 2
     |   |      ← Cycle: 1→2→3→1
     3 — 4

 ❌ Has cycle (1-2-4-3-1)
 ❌ 4 nodes but 4 edges (need exactly 3)

═══════════════════════════════════════════════════════════════════
 KEY PROPERTIES (MEMORIZE!)
═══════════════════════════════════════════════════════════════════

 ┌────────────────────────────────────────────────────────────────┐
 │ Property                           │ Value                    │
 ├────────────────────────────────────┼──────────────────────────┤
 │ Number of edges                    │ ALWAYS N - 1             │
 │ Number of paths between u and v    │ ALWAYS exactly 1         │
 │ Removing any edge                  │ Disconnects into 2 parts │
 │ Adding any edge                    │ Creates exactly 1 cycle  │
 │ Minimum leaves (N≥2)              │ At least 2               │
 │ Sum of all degrees                 │ 2 × (N-1) = 2N - 2      │
 └────────────────────────────────────┴──────────────────────────┘

═══════════════════════════════════════════════════════════════════
 TREE vs FOREST vs GRAPH
═══════════════════════════════════════════════════════════════════

 TREE:   Connected, acyclic (one component)
 FOREST: Acyclic but possibly disconnected (multiple trees)
         K components → N nodes, N-K edges
 GRAPH:  May have cycles, may be disconnected

═══════════════════════════════════════════════════════════════════
 CODE — Verify if a given graph is a tree
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
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

// Check if graph is a tree: connected + N-1 edges
bool isTree(int n, int m, vvec<int>& adj) {
    if (m != n - 1) return false; // must have N-1 edges

    // BFS to check connectivity
    vec<bool> visited(n + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    int count = 1;

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int u : adj[v]) {
            if (!visited[u]) {
                visited[u] = true;
                count++;
                q.push(u);
            }
        }
    }
    return count == n; // all nodes reachable?
}

void solve() {
    int n, m;
    cin >> n >> m;

    vvec<int> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    if (isTree(n, m, adj)) {
        cout << "YES — This is a TREE" << nl;
        cout << "  Nodes: " << n << ", Edges: " << m << " = " << n << "-1 ✅" << nl;
    } else {
        cout << "NO — This is NOT a tree" << nl;
        if (m != n - 1) cout << "  Wrong edge count: " << m << " ≠ " << n-1 << nl;
        else cout << "  Not connected" << nl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1; cin >> TC;
    while (TC--) solve();
    return 0;
}

/*
 Input: 2\n5 4\n1 2\n1 3\n2 4\n2 5\n4 4\n1 2\n2 3\n3 4\n4 1
 Output:
 YES — This is a TREE
   Nodes: 5, Edges: 4 = 5-1 ✅
 NO — This is NOT a tree
   Wrong edge count: 4 ≠ 3
*/

