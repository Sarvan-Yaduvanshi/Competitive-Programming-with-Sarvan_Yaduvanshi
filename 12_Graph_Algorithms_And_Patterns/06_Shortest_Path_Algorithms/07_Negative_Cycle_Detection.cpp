/*
╔══════════════════════════════════════════════════════════════════╗
║              07 — NEGATIVE CYCLE DETECTION                      ║
║              Find and print a negative cycle                    ║
╚══════════════════════════════════════════════════════════════════╝

Use Bellman-Ford: run V iterations. If V-th iteration still relaxes
some edge (u,v), then v is in or reachable from a negative cycle.
Trace parent[] to reconstruct the cycle.

Time: O(VE)    Space: O(V+E)
*/
#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
#endif
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
constexpr i64 INF64 = 4e18;
#define pb push_back
#define nl '\n'

struct Edge { int u, v; i64 w; };

void solve() {
    int n, m; cin >> n >> m;
    vec<Edge> edges(m);
    for (auto& [u,v,w] : edges) { cin >> u >> v >> w; u--; v--; }

    vec<i64> dist(n, 0);  // start all at 0 to detect any negative cycle
    vec<int> par(n, -1);
    int lastUpdated = -1;

    for (int iter = 0; iter < n; iter++) {
        lastUpdated = -1;
        for (auto& [u, v, w] : edges) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                par[v] = u;
                lastUpdated = v;
            }
        }
    }

    if (lastUpdated == -1) {
        cout << "No negative cycle" << nl;
    } else {
        // Trace back n steps to ensure we're in the cycle
        int v = lastUpdated;
        for (int i = 0; i < n; i++) v = par[v];

        vec<int> cycle;
        int u = v;
        do {
            cycle.pb(u);
            u = par[u];
        } while (u != v);
        cycle.pb(v);
        reverse(cycle.begin(), cycle.end());

        cout << "Negative cycle: ";
        for (int i = 0; i < (int)cycle.size(); i++) {
            if (i) cout << " → ";
            cout << cycle[i]+1;
        }
        cout << nl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

