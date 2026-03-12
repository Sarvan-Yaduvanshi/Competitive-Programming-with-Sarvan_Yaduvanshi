/*
╔══════════════════════════════════════════════════════════════════╗
║  01 — NAIVE LCA (Climb to Same Depth)                           ║
║  Zero to GM Level — LCA Algorithms                               ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 WHAT IS LCA? (Lowest Common Ancestor)
═══════════════════════════════════════════════════════════════════

 LCA(u, v) = deepest node that is ancestor of BOTH u and v.

 Tree:
           1
          / \
         2   3
        / \   \
       4   5   6
      /
     7

 LCA(7, 5) = 2  (2 is ancestor of both 7 and 5)
 LCA(7, 6) = 1  (only 1 is ancestor of both)
 LCA(4, 7) = 4  (4 is ancestor of 7, and ancestor of itself)

═══════════════════════════════════════════════════════════════════
 NAIVE ALGORITHM — DRY RUN
═══════════════════════════════════════════════════════════════════

 Step 1: Bring both nodes to SAME DEPTH
 Step 2: Climb both up simultaneously until they meet

 Find LCA(7, 6):
   depth[7]=3, depth[6]=2
   Step 1: 7 is deeper. Climb 7 up once: 7→4 (depth 2)
           Now both at depth 2: node 4 and node 6
   Step 2: 4 ≠ 6 → climb both: 4→2, 6→3 (depth 1)
           2 ≠ 3 → climb both: 2→1, 3→1 (depth 0)
           1 == 1 → LCA = 1 ✅

 Find LCA(7, 5):
   depth[7]=3, depth[5]=2
   Step 1: Climb 7 up once: 7→4 (depth 2)
           Now: 4 and 5 at depth 2
   Step 2: 4 ≠ 5 → climb: 4→2, 5→2
           2 == 2 → LCA = 2 ✅

 Find LCA(4, 7):
   depth[4]=2, depth[7]=3
   Step 1: Climb 7: 7→4 (depth 2)
           Now: 4 and 4 → same node!
   LCA = 4 ✅

═══════════════════════════════════════════════════════════════════
 COMPLEXITY: O(N) per query (worst case: skewed tree)
             Preprocessing: O(N) for DFS
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
    for (int u : adj[v]) if (u != p) dfs(u, v, d + 1);
}

int naiveLCA(int u, int v) {
    // Step 1: Equalize depths
    while (depth[u] > depth[v]) u = par[u];
    while (depth[v] > depth[u]) v = par[v];
    // Step 2: Climb together
    while (u != v) { u = par[u]; v = par[v]; }
    return u;
}

void solve() {
    int n;
    cin >> n;
    adj.assign(n + 1, {});
    depth.assign(n + 1, 0);
    par.assign(n + 1, 0);

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }
    dfs(1, 0, 0);

    int q; cin >> q;
    while (q--) {
        int u, v; cin >> u >> v;
        int lca = naiveLCA(u, v);
        int dist = depth[u] + depth[v] - 2 * depth[lca];
        cout << "LCA(" << u << ", " << v << ") = " << lca
             << "  dist = " << dist << nl;
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
 Input: 1\n7\n1 2\n1 3\n2 4\n2 5\n3 6\n4 7\n3\n7 6\n7 5\n4 7
 Output:
 LCA(7, 6) = 1  dist = 5
 LCA(7, 5) = 2  dist = 3
 LCA(4, 7) = 4  dist = 1

 ⚠️ Too slow for Q×N > 10^7. Use Binary Lifting (next file)!
*/

