/*
╔══════════════════════════════════════════════════════════════════╗
║              03 — BIPARTITE GRAPH CHECK                         ║
║              2-Coloring with BFS/DFS                            ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

A graph is BIPARTITE if its vertices can be split into two sets
such that every edge connects a vertex from one set to the other.

Equivalent: The graph is 2-COLORABLE (no two adjacent vertices
            have the same color).

Equivalent: The graph contains NO ODD-LENGTH CYCLE.

═══════════════════════════════════════════════════════════════════
ALGORITHM (BFS-based 2-coloring)
═══════════════════════════════════════════════════════════════════

1. Pick an uncolored vertex, color it 0
2. BFS: for each neighbor, assign opposite color
3. If a neighbor already has the SAME color → NOT bipartite
4. Repeat for all components

═══════════════════════════════════════════════════════════════════
DRY RUN
═══════════════════════════════════════════════════════════════════

Example 1 (Bipartite):          Example 2 (NOT Bipartite):
  1 ─── 2                        1 ─── 2
  │     │                        │     │
  3 ─── 4                        3 ─── 4 ─── 5
                                       │     │
  Color: 1=R, 2=B, 3=B, 4=R          └─────┘
  ✅ Bipartite!
                                  Odd cycle: 3─4─5─3 (length 3)
                                  ❌ NOT Bipartite!

DRY RUN (Example 1):
  Queue: [1(R)]
  Process 1(R): color 2=B, color 3=B → Queue: [2(B), 3(B)]
  Process 2(B): check 1=R(OK), color 4=R → Queue: [3(B), 4(R)]
  Process 3(B): check 1=R(OK), check 4=R(OK) → Queue: [4(R)]
  Process 4(R): check 2=B(OK), check 3=B(OK) → Queue: []
  ✅ All neighbors have different colors → Bipartite!

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
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    vec<int> color(n, -1);
    bool bipartite = true;

    for (int start = 0; start < n && bipartite; start++) {
        if (color[start] != -1) continue;

        color[start] = 0;
        queue<int> q;
        q.push(start);

        while (!q.empty() && bipartite) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    q.push(v);
                } else if (color[v] == color[u]) {
                    bipartite = false;
                }
            }
        }
    }

    if (bipartite) {
        cout << "YES (Bipartite)" << nl;
        cout << "Set A: ";
        for (int i = 0; i < n; i++) if (color[i] == 0) cout << i+1 << " ";
        cout << nl << "Set B: ";
        for (int i = 0; i < n; i++) if (color[i] == 1) cout << i+1 << " ";
        cout << nl;
    } else {
        cout << "NO (Not Bipartite — contains odd cycle)" << nl;
    }
}

/*
Input: 1\n4 4\n1 2\n2 4\n4 3\n3 1
Output:
YES (Bipartite)
Set A: 1 4
Set B: 2 3
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

