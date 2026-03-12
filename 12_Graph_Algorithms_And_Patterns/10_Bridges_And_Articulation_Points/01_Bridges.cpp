/*
╔══════════════════════════════════════════════════════════════════╗
║              01 — BRIDGES (Tarjan's Algorithm)                  ║
║              Find all edges whose removal disconnects graph     ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

A BRIDGE is an edge (u,v) whose removal increases the number
of connected components.

ALGORITHM (Tarjan):
  disc[u] = discovery time
  low[u]  = min discovery time reachable from subtree of u

  Edge (u→v) is a BRIDGE if: low[v] > disc[u]
  (No back edge from v's subtree can reach u or above)

═══════════════════════════════════════════════════════════════════
DRY RUN
═══════════════════════════════════════════════════════════════════

    1 ─── 2 ─── 3 ─── 4
          │     │
          └─────┘

Edges: (1,2), (2,3), (3,4), (2,3) — wait, 2-3 has back edge via cycle

Actually: 1─2, 2─3, 3─2(already), 3─4

DFS from 1:
  disc[1]=0, low[1]=0
  → disc[2]=1, low[2]=1
    → disc[3]=2, low[3]=2
      → 2 is parent, skip; check if back edge?
      → disc[4]=3, low[4]=3
        No unvisited neighbors → low[4]=3
      low[3]=min(2,3)=2
      Edge(3,4): low[4]=3 > disc[3]=2 → BRIDGE!
    low[2]=min(1,2)=1
    Edge(2,3): low[3]=2 > disc[2]=1? 2>1 → BRIDGE!
  low[1]=min(0,1)=0
  Edge(1,2): low[2]=1 > disc[1]=0? 1>0 → BRIDGE!

Bridges: (1,2), (2,3), (3,4)  — this is actually a path, all bridges.

Better example with cycle:
    1 ─── 2 ─── 5
    │     │
    3 ─── 4

Edges: 1-2, 1-3, 2-4, 3-4, 2-5

DFS: disc[1]=0, low[1]=0
  →2: disc=1,low=1 →4: disc=2,low=2 →3: disc=3,low=3
    3→1: back edge! low[3]=min(3,0)=0
    low[4]=min(2,0)=0. Edge(4,3): low[3]=0 ≤ disc[4]=2 → NOT bridge
  low[2]=min(1,0)=0. Edge(2,4): low[4]=0 ≤ disc[2]=1 → NOT bridge
  →5: disc=4,low=4. No more. low[5]=4.
  Edge(2,5): low[5]=4 > disc[2]=1 → BRIDGE!

Only bridge: (2,5) ✅

═══════════════════════════════════════════════════════════════════
Time: O(V+E)    Space: O(V+E)
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
using pii = pair<int,int>;
#define pb push_back
#define nl '\n'

int n, m;
vvec<int> adj;
vec<int> disc, low;
int timer_val;
vec<pii> bridges;

void dfs(int u, int parent) {
    disc[u] = low[u] = timer_val++;

    for (int v : adj[u]) {
        if (v == parent) { parent = -1; continue; } // skip parent edge ONCE (handles multi-edges)
        if (disc[v] == -1) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > disc[u]) {
                bridges.pb({u, v});
            }
        } else {
            low[u] = min(low[u], disc[v]);
        }
    }
}

void solve() {
    cin >> n >> m;
    adj.assign(n, {});
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].pb(v); adj[v].pb(u);
    }

    disc.assign(n, -1);
    low.assign(n, 0);
    timer_val = 0;
    bridges.clear();

    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) dfs(i, -1);
    }

    cout << "Bridges (" << bridges.size() << "):" << nl;
    for (auto [u, v] : bridges) {
        cout << "  " << u+1 << " — " << v+1 << nl;
    }
}

/*
Input: 1\n5 5\n1 2\n1 3\n2 4\n3 4\n2 5
Output:
Bridges (1):
  2 — 5
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

