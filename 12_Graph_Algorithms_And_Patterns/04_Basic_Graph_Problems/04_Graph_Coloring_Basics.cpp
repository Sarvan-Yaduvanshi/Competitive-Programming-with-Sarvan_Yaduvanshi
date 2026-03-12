/*
╔══════════════════════════════════════════════════════════════════╗
║              04 — GRAPH COLORING BASICS                         ║
║              Greedy coloring, chromatic number concepts          ║
╚══════════════════════════════════════════════════════════════════╝

Chromatic number χ(G) = minimum colors to color graph so no two
adjacent vertices share a color.

  χ(G) = 1 → graph has no edges
  χ(G) = 2 → bipartite
  χ(G) = 3+ → has odd cycle

Greedy coloring: Assign smallest available color to each vertex.
  Worst case uses Δ+1 colors (Δ = max degree).

  Brooks' Theorem: χ(G) ≤ Δ unless G is complete or odd cycle.

Time: O(V + E)    Space: O(V)
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <set>
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
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].pb(v); adj[v].pb(u);
    }

    vec<int> color(n, -1);
    int maxColor = 0;

    for (int u = 0; u < n; u++) {
        set<int> usedColors;
        for (int v : adj[u]) {
            if (color[v] != -1) usedColors.insert(color[v]);
        }
        // Assign smallest unused color
        int c = 0;
        while (usedColors.count(c)) c++;
        color[u] = c;
        maxColor = max(maxColor, c);
    }

    cout << "Colors used: " << maxColor + 1 << nl;
    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i+1 << ": color " << color[i] << nl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

