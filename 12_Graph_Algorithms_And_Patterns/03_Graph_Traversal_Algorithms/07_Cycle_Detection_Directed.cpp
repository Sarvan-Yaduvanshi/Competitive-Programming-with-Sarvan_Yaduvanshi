/*
╔══════════════════════════════════════════════════════════════════╗
║              07 — CYCLE DETECTION IN DIRECTED GRAPH              ║
║              Using 3-Color DFS (White/Gray/Black)               ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

In a DIRECTED graph, a cycle exists if during DFS we find a
BACK EDGE — an edge to a GRAY vertex (one currently in our
recursion stack).

3-Color scheme:
  WHITE (0): Not yet visited
  GRAY  (1): Currently in recursion stack (being processed)
  BLACK (2): Completely processed

Edge (u→v):
  v is WHITE → Tree edge, continue DFS
  v is GRAY  → BACK EDGE → CYCLE!
  v is BLACK → No cycle through this edge

⚠️ For directed graphs, we CANNOT use the parent trick!
   Edge u→v where v is visited but not parent does NOT
   necessarily mean a cycle in directed graphs.

═══════════════════════════════════════════════════════════════════
DRY RUN
═══════════════════════════════════════════════════════════════════

Directed Graph:
    1 → 2 → 3
    ↑       │
    └───────┘

DFS from 1:
  color[1] = GRAY
  → Visit 2: color[2] = GRAY
    → Visit 3: color[3] = GRAY
      → Check 1: color[1] = GRAY → BACK EDGE → CYCLE!
      Cycle: 1 → 2 → 3 → 1

═══════════════════════════════════════════════════════════════════
TIME & SPACE: O(V + E) time, O(V) space
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

int n, m;
vvec<int> adj;
vec<int> color;  // 0=white, 1=gray, 2=black
vec<int> parent;
bool hasCycle;
int cycleStart, cycleEnd;

void dfs(int u) {
    color[u] = 1;  // GRAY

    for (int v : adj[u]) {
        if (color[v] == 1) {
            // BACK EDGE → cycle found!
            hasCycle = true;
            cycleStart = v;
            cycleEnd = u;
            return;
        }
        if (color[v] == 0) {
            parent[v] = u;
            dfs(v);
            if (hasCycle) return;
        }
    }

    color[u] = 2;  // BLACK
}

void solve() {
    cin >> n >> m;
    adj.assign(n, {});
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);  // DIRECTED
    }

    color.assign(n, 0);
    parent.assign(n, -1);
    hasCycle = false;

    for (int i = 0; i < n && !hasCycle; i++) {
        if (color[i] == 0) dfs(i);
    }

    if (hasCycle) {
        // Reconstruct cycle
        vec<int> cycle;
        cycle.pb(cycleStart);
        for (int v = cycleEnd; v != cycleStart; v = parent[v]) {
            cycle.pb(v);
        }
        cycle.pb(cycleStart);
        reverse(cycle.begin(), cycle.end());

        cout << "CYCLE: ";
        for (int i = 0; i < sz(cycle); i++) {
            if (i > 0) cout << " → ";
            cout << cycle[i] + 1;
        }
        cout << nl;
    } else {
        cout << "No cycle (this is a DAG)" << nl;
    }
}

/*
SAMPLE: 1\n4 4\n1 2\n2 3\n3 4\n4 2
OUTPUT: CYCLE: 2 → 3 → 4 → 2
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    return 0;
}

