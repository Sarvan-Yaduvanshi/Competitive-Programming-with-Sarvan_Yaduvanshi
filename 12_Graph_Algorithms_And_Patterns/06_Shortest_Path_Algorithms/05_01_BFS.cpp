/*
╔══════════════════════════════════════════════════════════════════╗
║              05 — 0-1 BFS                                       ║
║              Shortest path when weights are 0 or 1              ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

When edge weights are only 0 or 1, use a DEQUE instead of
priority queue for O(V+E) instead of O((V+E)logV).

ALGORITHM:
  - If edge weight = 0 → push_front (treat as same level)
  - If edge weight = 1 → push_back (next level)

This maintains the deque in sorted order!

═══════════════════════════════════════════════════════════════════
WHEN TO USE
═══════════════════════════════════════════════════════════════════

  ✅ Grid problems: move to same-color cell = 0, different = 1
  ✅ Graph with some free edges and some costing 1
  ✅ Any problem reducible to 0/1 weights

Time: O(V+E)    Space: O(V+E)
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
using pii = pair<int,int>;
constexpr int INF32 = 2e9;
#define nl '\n'

void solve() {
    int n, m;
    cin >> n >> m;

    vec<vec<pii>> adj(n);  // (neighbor, weight 0 or 1)
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w; u--; v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int src; cin >> src; src--;

    vec<int> dist(n, INF32);
    deque<int> dq;

    dist[src] = 0;
    dq.push_back(src);

    while (!dq.empty()) {
        int u = dq.front(); dq.pop_front();

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) dq.push_front(v);   // weight 0 → front
                else        dq.push_back(v);    // weight 1 → back
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << "dist[" << i+1 << "] = ";
        if (dist[i]==INF32) cout << "INF"; else cout << dist[i];
        cout << nl;
    }
}

/*
Example: Grid problem — cost 0 to stay on same color, cost 1 to change.
Input: 1\n4 5\n1 2 0\n2 3 1\n1 3 1\n3 4 0\n2 4 1\n1
Output:
dist[1] = 0
dist[2] = 0
dist[3] = 1
dist[4] = 1
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

