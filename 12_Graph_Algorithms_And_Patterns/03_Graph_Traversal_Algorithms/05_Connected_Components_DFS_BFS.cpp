/*
╔══════════════════════════════════════════════════════════════════╗
║              05 — CONNECTED COMPONENTS (DFS & BFS)              ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

A CONNECTED COMPONENT is a maximal set of vertices such that
there exists a path between every pair of vertices in the set.

Algorithm:
  For each unvisited vertex, start DFS/BFS → all visited vertices
  form one connected component.

Time: O(V + E)    Space: O(V)

═══════════════════════════════════════════════════════════════════
VISUALIZATION
═══════════════════════════════════════════════════════════════════

    1 ─── 2     5 ─── 6     8
    │           │
    3 ─── 4     7

  Component 1: {1,2,3,4}
  Component 2: {5,6,7}
  Component 3: {8}

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
#include <numeric>
using namespace std;

using i64 = long long;
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
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    vec<int> comp(n, -1);  // component ID for each vertex
    int numComp = 0;

    for (int i = 0; i < n; i++) {
        if (comp[i] != -1) continue;

        // BFS to find all vertices in this component
        queue<int> q;
        q.push(i);
        comp[i] = numComp;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (comp[v] == -1) {
                    comp[v] = numComp;
                    q.push(v);
                }
            }
        }
        numComp++;
    }

    // Print results
    cout << "Number of components: " << numComp << nl;
    for (int c = 0; c < numComp; c++) {
        cout << "Component " << c+1 << ": {";
        bool first = true;
        for (int i = 0; i < n; i++) {
            if (comp[i] == c) {
                if (!first) cout << ", ";
                cout << i+1;
                first = false;
            }
        }
        cout << "}" << nl;
    }
}

/*
SAMPLE INPUT: 1\n8 5\n1 2\n1 3\n3 4\n5 6\n5 7
OUTPUT:
Number of components: 3
Component 1: {1, 2, 3, 4}
Component 2: {5, 6, 7}
Component 3: {8}
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    return 0;
}

