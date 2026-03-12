/*
╔══════════════════════════════════════════════════════════════════╗
║              02 — PRIM'S ALGORITHM                              ║
║              Grow MST from a vertex using priority queue         ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
ALGORITHM
═══════════════════════════════════════════════════════════════════

1. Start from any vertex, add it to MST set
2. Push all its edges to a min-heap
3. While MST doesn't have n-1 edges:
   a. Pop cheapest edge (w, u, v) from heap
   b. If v already in MST → skip
   c. Else: add v to MST, add edge, push v's edges to heap

Like Dijkstra but instead of dist[v], we track min edge to MST.

═══════════════════════════════════════════════════════════════════
DRY RUN (same graph as Kruskal example)
═══════════════════════════════════════════════════════════════════

Start at vertex 1:
  MST = {1}, PQ: [(1,1,3), (4,1,2)]

  Pop (1,1,3): add 3 to MST. MST={1,3}, push 3's edges
  PQ: [(2,3,4), (4,1,2)]

  Pop (2,3,4): add 4 to MST. MST={1,3,4}, push 4's edges
  PQ: [(3,4,2), (4,1,2), (5,4,5)]

  Pop (3,4,2): add 2 to MST. MST={1,2,3,4}
  PQ: [(4,1,2)skip, (5,4,5), (7,2,5)]

  Pop (5,4,5): add 5 to MST. MST={1,2,3,4,5}. DONE.

  MST weight = 1 + 2 + 3 + 5 = 11 ✅

═══════════════════════════════════════════════════════════════════
COMPLEXITY
  Time:  O((V + E) log V)    Space: O(V + E)
  Same as Dijkstra! Better for dense graphs than Kruskal.
═══════════════════════════════════════════════════════════════════
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
using pii = pair<i64, int>;
#define nl '\n'

void solve() {
    int n, m;
    cin >> n >> m;

    vec<vec<pair<int,i64>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v; i64 w;
        cin >> u >> v >> w; u--; v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // PRIM'S ALGORITHM
    vec<bool> inMST(n, false);
    priority_queue<pii, vec<pii>, greater<pii>> pq;  // min-heap (weight, vertex)

    i64 mstWeight = 0;
    int edgesAdded = 0;

    // Start from vertex 0
    pq.push({0, 0});

    while (!pq.empty() && edgesAdded < n) {
        auto [w, u] = pq.top(); pq.pop();
        if (inMST[u]) continue;

        inMST[u] = true;
        mstWeight += w;
        edgesAdded++;

        for (auto [v, weight] : adj[u]) {
            if (!inMST[v]) {
                pq.push({weight, v});
            }
        }
    }

    if (edgesAdded != n) cout << "Not connected!" << nl;
    else cout << "MST weight (Prim): " << mstWeight << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

