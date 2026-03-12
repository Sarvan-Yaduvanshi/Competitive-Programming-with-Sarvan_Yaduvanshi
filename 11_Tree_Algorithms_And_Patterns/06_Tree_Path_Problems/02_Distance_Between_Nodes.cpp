/*
╔══════════════════════════════════════════════════════════════════╗
║  02 — DISTANCE BETWEEN NODES (Using LCA)                       ║
║  Zero to GM Level — Tree Path Problems                           ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 FORMULA: dist(u,v) = depth[u] + depth[v] - 2 * depth[LCA(u,v)]
═══════════════════════════════════════════════════════════════════

 Tree:
           1 (depth=0)
          / \
         2   3 (depth=1)
        / \   \
       4   5   6 (depth=2)

 dist(4, 6):
   LCA(4, 6) = 1
   dist = depth[4] + depth[6] - 2·depth[1] = 2 + 2 - 0 = 4

 Path: 4 → 2 → 1 → 3 → 6 = 4 edges ✅

 dist(4, 5):
   LCA(4, 5) = 2
   dist = 2 + 2 - 2·1 = 2

 Path: 4 → 2 → 5 = 2 edges ✅

═══════════════════════════════════════════════════════════════════
 NAIVE LCA — O(N) per query
═══════════════════════════════════════════════════════════════════

 Method: Find paths from root to u and root to v.
 LCA = last common node in both paths.

 Path to 4: [1, 2, 4]
 Path to 6: [1, 3, 6]
 Common prefix: [1] → LCA = 1

═══════════════════════════════════════════════════════════════════
 CODE
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
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

vvec<int> adj;
vec<int> depth, par;

void dfs(int v, int p, int d) {
    par[v] = p;
    depth[v] = d;
    for (int u : adj[v])
        if (u != p) dfs(u, v, d + 1);
}

// Naive LCA: climb both nodes to same depth, then climb together
int naiveLCA(int u, int v) {
    // Bring to same depth
    while (depth[u] > depth[v]) u = par[u];
    while (depth[v] > depth[u]) v = par[v];
    // Climb together
    while (u != v) { u = par[u]; v = par[v]; }
    return u;
}

int dist(int u, int v) {
    int lca = naiveLCA(u, v);
    return depth[u] + depth[v] - 2 * depth[lca];
}

void solve() {
    int n;
    cin >> n;
    adj.assign(n + 1, {});
    depth.assign(n + 1, 0);
    par.assign(n + 1, -1);

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }
    dfs(1, -1, 0);

    int q; cin >> q;
    while (q--) {
        int u, v; cin >> u >> v;
        int lca = naiveLCA(u, v);
        cout << "LCA(" << u << "," << v << ") = " << lca
             << ", dist = " << dist(u, v) << nl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1; cin >> TC;
    while (TC--) solve();
    return 0;
}

/*
 Input: 1\n6\n1 2\n1 3\n2 4\n2 5\n3 6\n3\n4 6\n4 5\n2 6
 Output:
 LCA(4,6) = 1, dist = 4
 LCA(4,5) = 2, dist = 2
 LCA(2,6) = 1, dist = 3

 Time: O(N) per query (naive). Binary lifting → O(log N). See Ch 08.
*/

