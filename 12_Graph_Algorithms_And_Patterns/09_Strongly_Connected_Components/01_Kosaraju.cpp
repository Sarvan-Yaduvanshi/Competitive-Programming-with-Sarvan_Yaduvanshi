/*
╔══════════════════════════════════════════════════════════════════╗
║              01 — KOSARAJU'S ALGORITHM                          ║
║              Find all SCCs using two DFS passes                 ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

A Strongly Connected Component (SCC) is a maximal set of vertices
such that there exists a path FROM any vertex TO any other vertex
within the set (in a directed graph).

KOSARAJU'S ALGORITHM:
  1. Run DFS on original graph, record finish order (post-order)
  2. Transpose the graph (reverse all edges)
  3. Process vertices in REVERSE finish order on transposed graph
     Each DFS from step 3 finds one SCC

═══════════════════════════════════════════════════════════════════
DRY RUN
═══════════════════════════════════════════════════════════════════

Graph:
    1 → 2 → 3 → 1    (SCC: {1,2,3})
         ↓
         4 → 5 → 6 → 4    (SCC: {4,5,6})

PASS 1 (DFS on original, record finish order):
  DFS(1): visit 1→2→3→(1 visited)→(back to 2)→4→5→6→(4 visited)
  Finish order: [6, 5, 4, 3, 2, 1]

PASS 2 (DFS on TRANSPOSED graph in reverse finish order):
  Reversed graph: 2→1, 3→2, 1→3, 2→4 becomes 4→2, 5→4, 6→5, 4→6

  Process vertex 1 (last finished): DFS finds {1, 3, 2} → SCC #1
  Process vertex 4: DFS finds {4, 6, 5} → SCC #2

═══════════════════════════════════════════════════════════════════
COMPLEXITY: Time O(V+E), Space O(V+E)
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

template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

int n, m;
vvec<int> adj, radj;  // original and reversed graph
vec<bool> visited;
vec<int> order;        // finish order
vec<int> comp;         // SCC id for each vertex

void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u]) if (!visited[v]) dfs1(v);
    order.pb(u);  // post-order
}

void dfs2(int u, int c) {
    comp[u] = c;
    for (int v : radj[u]) if (comp[v] == -1) dfs2(v, c);
}

void solve() {
    cin >> n >> m;
    adj.assign(n, {}); radj.assign(n, {});

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].pb(v);
        radj[v].pb(u);  // reversed edge
    }

    // PASS 1: DFS on original graph
    visited.assign(n, false);
    order.clear();
    for (int i = 0; i < n; i++) if (!visited[i]) dfs1(i);

    // PASS 2: DFS on reversed graph in reverse finish order
    comp.assign(n, -1);
    int numSCC = 0;
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        if (comp[u] == -1) {
            dfs2(u, numSCC);
            numSCC++;
        }
    }

    cout << "Number of SCCs: " << numSCC << nl;
    for (int c = 0; c < numSCC; c++) {
        cout << "SCC " << c+1 << ": {";
        bool first = true;
        for (int i = 0; i < n; i++) {
            if (comp[i] == c) {
                if (!first) cout << ", ";
                cout << i+1;
                first = false;
            }
        }
        cout << "}" << nl;
    }
}

/*
Input: 1\n6 7\n1 2\n2 3\n3 1\n2 4\n4 5\n5 6\n6 4
Output:
Number of SCCs: 2
SCC 1: {1, 2, 3}
SCC 2: {4, 5, 6}
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

