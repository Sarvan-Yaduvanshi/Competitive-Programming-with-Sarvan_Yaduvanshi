/*
╔══════════════════════════════════════════════════════════════════╗
║              03 — SPFA (Shortest Path Faster Algorithm)          ║
║              Queue-optimized Bellman-Ford                        ║
╚══════════════════════════════════════════════════════════════════╝

SPFA optimizes Bellman-Ford using a queue:
  Only re-process vertices whose distance was updated.

Average: O(E), Worst: O(VE)

Detect negative cycle: if any vertex enters queue ≥ V times.

⚠️ Can be hacked to O(VE) in CF. Prefer Dijkstra when possible.

Time: Average O(E), Worst O(VE)
Space: O(V+E)
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
using pii = pair<int, i64>;
constexpr i64 INF64 = 4e18;
#define pb push_back
#define nl '\n'

void solve() {
    int n, m;
    cin >> n >> m;

    vec<vec<pii>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v; i64 w;
        cin >> u >> v >> w; u--; v--;
        adj[u].pb({v, w});
    }

    int src; cin >> src; src--;

    vec<i64> dist(n, INF64);
    vec<bool> inQueue(n, false);
    vec<int> cnt(n, 0);  // count entries into queue

    queue<int> q;
    dist[src] = 0;
    q.push(src);
    inQueue[src] = true;
    cnt[src]++;

    bool negCycle = false;

    while (!q.empty() && !negCycle) {
        int u = q.front(); q.pop();
        inQueue[u] = false;

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = true;
                    cnt[v]++;
                    if (cnt[v] >= n) { negCycle = true; break; }
                }
            }
        }
    }

    if (negCycle) cout << "Negative cycle!" << nl;
    else {
        for (int i = 0; i < n; i++) {
            cout << "dist[" << i+1 << "] = ";
            if (dist[i]==INF64) cout << "INF"; else cout << dist[i];
            cout << nl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

