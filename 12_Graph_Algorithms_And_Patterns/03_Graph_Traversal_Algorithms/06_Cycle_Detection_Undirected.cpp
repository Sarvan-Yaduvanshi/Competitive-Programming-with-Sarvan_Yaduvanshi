/*
╔══════════════════════════════════════════════════════════════════╗
║              06 — CYCLE DETECTION IN UNDIRECTED GRAPH            ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

A cycle in an undirected graph exists if during DFS we encounter
a visited vertex that is NOT the parent of the current vertex.

Key: In undirected graph, edge (u,v) means both u→v and v→u.
     When we DFS from u to v, we don't want to count going back
     to the parent as a cycle. A back edge to a NON-PARENT ancestor
     means there's a cycle.

Alternative: A graph has a cycle iff |E| >= |V| (in same component)
             i.e., more edges than a tree would have.

═══════════════════════════════════════════════════════════════════
DRY RUN
═══════════════════════════════════════════════════════════════════

Graph:
    1 ─── 2
    │     │
    3 ─── 4

DFS from 1 (parent = -1):
  Visit 1, go to 2 (parent[2] = 1)
  Visit 2, go to 4 (parent[4] = 2) (skip 1, it's parent)
  Visit 4, check 3:
    4 → 3: not visited, visit 3 (parent[3] = 4)
  Visit 3, check 1:
    3 → 1: 1 is VISITED and 1 ≠ parent[3]=4 → CYCLE FOUND!
           Cycle: 1 → 2 → 4 → 3 → 1

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
vec<bool> visited;
vec<int> parent;
bool hasCycle;
vec<int> cycleNodes;

void dfs(int u, int par) {
    visited[u] = true;
    parent[u] = par;

    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, u);
            if (hasCycle) return;
        } else if (v != par) {
            // Found a cycle! v is visited and not parent
            hasCycle = true;

            // Reconstruct cycle: go from u back to v through parents
            cycleNodes.clear();
            cycleNodes.pb(v);
            for (int x = u; x != v; x = parent[x]) {
                cycleNodes.pb(x);
            }
            cycleNodes.pb(v);  // close the cycle
            return;
        }
    }
}

void solve() {
    cin >> n >> m;
    adj.assign(n, {});
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    visited.assign(n, false);
    parent.assign(n, -1);
    hasCycle = false;

    for (int i = 0; i < n && !hasCycle; i++) {
        if (!visited[i]) {
            dfs(i, -1);
        }
    }

    if (hasCycle) {
        cout << "CYCLE FOUND: ";
        for (int i = 0; i < sz(cycleNodes); i++) {
            if (i > 0) cout << " → ";
            cout << cycleNodes[i] + 1;
        }
        cout << nl;
    } else {
        cout << "No cycle (this is a forest)" << nl;
    }
}

/*
SAMPLE: 1\n4 4\n1 2\n2 4\n4 3\n3 1
OUTPUT: CYCLE FOUND: 1 → 3 → 4 → 2 → 1
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    return 0;
}

