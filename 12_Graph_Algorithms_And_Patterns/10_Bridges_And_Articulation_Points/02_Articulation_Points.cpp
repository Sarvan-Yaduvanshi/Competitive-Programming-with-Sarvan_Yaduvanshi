/*
╔══════════════════════════════════════════════════════════════════╗
║              02 — ARTICULATION POINTS (Cut Vertices)            ║
║              Vertices whose removal disconnects graph           ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
ALGORITHM
═══════════════════════════════════════════════════════════════════

Vertex u is an articulation point if:
  1. u is ROOT and has ≥ 2 children in DFS tree
  2. u is NOT root and has a child v where low[v] >= disc[u]
     (v's subtree cannot reach above u without going through u)

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
#include <set>
using namespace std;

template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define pb push_back
#define nl '\n'

int n, m;
vvec<int> adj;
vec<int> disc, low;
int timer_val;
set<int> articulationPoints;

void dfs(int u, int parent) {
    disc[u] = low[u] = timer_val++;
    int children = 0;

    for (int v : adj[u]) {
        if (disc[v] == -1) {
            children++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            // Case 1: u is root with >= 2 children
            if (parent == -1 && children > 1)
                articulationPoints.insert(u);

            // Case 2: u is not root and low[v] >= disc[u]
            if (parent != -1 && low[v] >= disc[u])
                articulationPoints.insert(u);
        } else if (v != parent) {
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

    disc.assign(n, -1); low.assign(n, 0);
    timer_val = 0;
    articulationPoints.clear();

    for (int i = 0; i < n; i++)
        if (disc[i] == -1) dfs(i, -1);

    cout << "Articulation points (" << articulationPoints.size() << "):" << nl;
    for (int v : articulationPoints) cout << "  " << v+1 << nl;
}

/*
Input: 1\n7 7\n1 2\n1 3\n2 3\n3 4\n4 5\n4 6\n5 6
(Vertex 3 and 4 are articulation points)
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

