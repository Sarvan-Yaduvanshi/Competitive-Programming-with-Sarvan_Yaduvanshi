/*
╔══════════════════════════════════════════════════════════════════╗
║              06 — IS GRAPH A TREE?                              ║
╚══════════════════════════════════════════════════════════════════╝

A graph is a TREE iff:
  ✅ Connected (1 component)  AND
  ✅ |E| = |V| - 1           AND
  ✅ Acyclic

Any TWO of these three conditions imply the third.

Fastest check: BFS/DFS to verify connected + check m == n-1.
Time: O(V+E)   Space: O(V)
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define pb push_back
#define nl '\n'

void solve() {
    int n, m;
    cin >> n >> m;
    vvec<int> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].pb(v); adj[v].pb(u);
    }

    // Check connected via BFS
    vec<bool> vis(n, false);
    queue<int> q;
    q.push(0); vis[0] = true;
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop(); cnt++;
        for (int v : adj[u]) if (!vis[v]) { vis[v]=true; q.push(v); }
    }

    bool isTree = (cnt == n && m == n - 1);
    cout << (isTree ? "YES — It's a tree" : "NO — Not a tree") << nl;
    if (!isTree) {
        if (cnt != n) cout << "Reason: Not connected (" << cnt << "/" << n << " reachable)" << nl;
        if (m != n-1) cout << "Reason: Edge count " << m << " != " << n-1 << nl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

