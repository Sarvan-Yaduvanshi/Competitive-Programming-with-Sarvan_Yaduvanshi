/*
╔══════════════════════════════════════════════════════════════════╗
║              02 — DFS TOPOLOGICAL SORT                          ║
║              Post-order reverse gives topological order          ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
ALGORITHM
═══════════════════════════════════════════════════════════════════

1. Run DFS from every unvisited vertex
2. After processing ALL children of vertex u, push u to stack
3. Pop stack → topological order

WHY? A vertex is pushed AFTER all its descendants are pushed.
So in reverse (stack), it appears BEFORE all its descendants.

═══════════════════════════════════════════════════════════════════
DRY RUN
═══════════════════════════════════════════════════════════════════

DAG: 1→2, 1→3, 2→4, 3→4, 3→5

DFS(1):
  DFS(2):
    DFS(4): no unvisited neighbors → push 4. Stack: [4]
  push 2. Stack: [4, 2]
  DFS(3):
    4 already visited
    DFS(5): push 5. Stack: [4, 2, 5]
  push 3. Stack: [4, 2, 5, 3]
push 1. Stack: [4, 2, 5, 3, 1]

Reverse: [1, 3, 5, 2, 4] ← topological order ✅

Time: O(V+E)    Space: O(V)
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
vvec<int> adj;
vec<bool> visited;
vec<int> order;

void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) dfs(v);
    }
    order.pb(u);  // post-order
}

void solve() {
    cin >> n >> m;
    adj.assign(n, {});
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].pb(v);
    }

    visited.assign(n, false);
    order.clear();

    for (int i = 0; i < n; i++) {
        if (!visited[i]) dfs(i);
    }

    reverse(order.begin(), order.end());

    cout << "Topological Order (DFS): ";
    for (int i = 0; i < n; i++) {
        if (i) cout << " → ";
        cout << order[i] + 1;
    }
    cout << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

