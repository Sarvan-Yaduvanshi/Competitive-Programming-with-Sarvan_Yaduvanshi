/*
╔══════════════════════════════════════════════════════════════════╗
║              01 — KAHN'S ALGORITHM (BFS Topological Sort)       ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

TOPOLOGICAL SORT: A linear ordering of vertices in a DAG such that
for every directed edge u → v, u comes before v in the ordering.

Exists ONLY for DAGs (Directed Acyclic Graphs).

KAHN'S ALGORITHM (BFS-based):
  1. Compute in-degree of all vertices
  2. Push all vertices with in-degree 0 into queue
  3. While queue not empty:
     a. Dequeue vertex u, add to result
     b. For each neighbor v of u:
        - Decrease in-degree of v by 1
        - If in-degree becomes 0, push v to queue
  4. If result size ≠ n → cycle exists!

═══════════════════════════════════════════════════════════════════
DRY RUN
═══════════════════════════════════════════════════════════════════

DAG:
    1 → 2 → 4
    │       ↑
    └→ 3 ───┘
       │
       └→ 5

Adjacency: 1→[2,3], 2→[4], 3→[4,5], 4→[], 5→[]

In-degrees: 1:0, 2:1, 3:1, 4:2, 5:1

Step │ Queue    │ Process │ Update in-degrees      │ Result
═════╪══════════╪═════════╪════════════════════════╪════════════
  0  │ [1]      │    -    │ in-deg 0: vertex 1     │ []
  1  │ [2,3]    │    1    │ deg[2]=0, deg[3]=0     │ [1]
  2  │ [3,4]    │    2    │ deg[4]=2→1             │ [1,2]
  3  │ [4,5]    │    3    │ deg[4]=1→0, deg[5]=0   │ [1,2,3]
  4  │ [5]      │    4    │ -                       │ [1,2,3,4]
  5  │ []       │    5    │ -                       │ [1,2,3,4,5]

Result: [1, 2, 3, 4, 5]  ✅ Valid topological order!

═══════════════════════════════════════════════════════════════════
COMPLEXITY
═══════════════════════════════════════════════════════════════════
  Time:  O(V + E)
  Space: O(V + E)

═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
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
        adj[u].pb(v);
        inDeg[v]++;
    }

    // Kahn's Algorithm
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (inDeg[i] == 0) q.push(i);
    }

    vec<int> topoOrder;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        topoOrder.pb(u);

        for (int v : adj[u]) {
            inDeg[v]--;
            if (inDeg[v] == 0) q.push(v);
        }
    }

    if (sz(topoOrder) != n) {
        cout << "CYCLE DETECTED! No valid topological order." << nl;
    } else {
        cout << "Topological Order: ";
        for (int i = 0; i < n; i++) {
            if (i) cout << " → ";
            cout << topoOrder[i] + 1;
        }
        cout << nl;
    }
}

/*
Input: 1\n5 5\n1 2\n1 3\n2 4\n3 4\n3 5
Output: Topological Order: 1 → 2 → 3 → 4 → 5
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

