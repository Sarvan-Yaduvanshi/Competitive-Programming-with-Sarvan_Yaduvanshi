/*
╔══════════════════════════════════════════════════════════════════╗
║              03 — CYCLE DETECTION USING TOPOLOGICAL SORT        ║
╚══════════════════════════════════════════════════════════════════╝

If Kahn's algorithm processes fewer than n vertices → CYCLE exists.
This is because vertices in a cycle never reach in-degree 0.

Time: O(V+E)    Space: O(V+E)
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
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

void solve() {
    int n, m;
    cin >> n >> m;
    vvec<int> adj(n);
    vec<int> inDeg(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].pb(v); inDeg[v]++;
    }

    queue<int> q;
    for (int i = 0; i < n; i++) if (inDeg[i]==0) q.push(i);

    int processed = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        processed++;
        for (int v : adj[u]) {
            if (--inDeg[v] == 0) q.push(v);
        }
    }

    if (processed == n) cout << "DAG (No cycle)" << nl;
    else cout << "CYCLE EXISTS (" << n - processed << " vertices in cycle(s))" << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

