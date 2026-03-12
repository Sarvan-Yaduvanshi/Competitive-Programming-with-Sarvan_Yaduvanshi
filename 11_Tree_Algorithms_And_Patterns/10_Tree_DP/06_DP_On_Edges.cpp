/*
╔══════════════════════════════════════════════════════════════════╗
║  06 — DP ON EDGES (Edge-based Tree DP)                          ║
║  Zero to GM Level — Tree DP                                      ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 CONCEPT: DP on edges instead of nodes
═══════════════════════════════════════════════════════════════════

 Sometimes the DP state is associated with EDGES, not nodes.
 Common pattern: for each edge (u, v) where v is child of u,
 dp_edge = some function of the subtree rooted at v.

 Two key problems:
   1. Edge coloring: color each edge black/white, minimize cost
   2. Edge contribution: for each edge, how many paths use it?

═══════════════════════════════════════════════════════════════════
 PROBLEM: Count paths using each edge
═══════════════════════════════════════════════════════════════════

 For edge (u, v) where v is child of u:
   Nodes in subtree(v) = sub[v]
   Nodes OUTSIDE subtree(v) = N - sub[v]
   Paths crossing this edge = sub[v] × (N - sub[v])

═══════════════════════════════════════════════════════════════════
 DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree (N=5):
         1
        / \
       2   3
      / \
     4   5

 sub[1]=5, sub[2]=3, sub[3]=1, sub[4]=1, sub[5]=1

 Edge (1,2): sub[2]=3, paths = 3 × 2 = 6
   (pairs: {4,1},{4,3},{5,1},{5,3},{2,1},{2,3})
 Edge (1,3): sub[3]=1, paths = 1 × 4 = 4
   (pairs: {3,1},{3,2},{3,4},{3,5})
 Edge (2,4): sub[4]=1, paths = 1 × 4 = 4
 Edge (2,5): sub[5]=1, paths = 1 × 4 = 4

 Total path count = Σ paths = 6+4+4+4 = 18
 Verify: C(5,2) = 10 paths × avg length... actually
 Total sum of all pairwise distances = 6+4+4+4 = 18 / 2 = ...

 Wait — each UNORDERED pair is counted once per edge on its path.
 So sum of all pairwise distances = Σ sub[v] × (N - sub[v])
                                   = 6+4+4+4 = 18 ← for ordered pairs
 For unordered: total = 18 (already unordered since sub[v]*(N-sub[v]))

 Actually this counts each ordered pair once. So sum of distances
 for all unordered pairs = Σ sub[v] × (N - sub[v]) = 18.

 Verify: dist pairs:
   (1,2)=1, (1,3)=1, (1,4)=2, (1,5)=2
   (2,3)=2, (2,4)=1, (2,5)=1
   (3,4)=3, (3,5)=3
   (4,5)=2
 Sum = 1+1+2+2+2+1+1+3+3+2 = 18 ✅

═══════════════════════════════════════════════════════════════════
 APPLICATION: Sum of all pairwise distances
═══════════════════════════════════════════════════════════════════

 Formula: answer = Σ over all edges of sub[v] × (N - sub[v])

 This is O(N) — incredibly efficient!

═══════════════════════════════════════════════════════════════════
 EDGE COLORING DP — Another classic
═══════════════════════════════════════════════════════════════════

 Color each edge black or white. Cost depends on coloring.
 dp[v][c] = min cost of subtree when edge to parent has color c.

 Similar structure to node-based DP but state lives on edges.

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
using pii = pair<int, int>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

vvec<pii> adj; // {neighbor, edge_weight}
vec<i64> sub_sz;
int n;

void dfs(int v, int par) {
    sub_sz[v] = 1;
    for (auto [u, w] : adj[v]) {
        if (u == par) continue;
        dfs(u, v);
        sub_sz[v] += sub_sz[u];
    }
}

void solve() {
    cin >> n;
    adj.assign(n + 1, {});
    sub_sz.assign(n + 1, 0);

    vec<tuple<int,int,i64>> edges(n - 1);
    for (auto& [u, v, w] : edges) {
        cin >> u >> v >> w;
        adj[u].pb({v, (int)w}); adj[v].pb({u, (int)w});
    }

    dfs(1, -1);

    // Sum of all pairwise distances (weighted)
    i64 totalDist = 0;
    cout << "Edge contributions:" << nl;
    for (auto [u, v, w] : edges) {
        // Make v the child (deeper node)
        if (sub_sz[u] < sub_sz[v]) swap(u, v);
        // sub_sz[v] is the smaller subtree
        i64 paths = (i64)sub_sz[v] * (n - sub_sz[v]);
        i64 contribution = paths * w;
        totalDist += contribution;
        cout << "  Edge (" << u << "," << v << ") w=" << w
             << ": " << sub_sz[v] << " × " << (n - sub_sz[v])
             << " × " << w << " = " << contribution << nl;
    }

    cout << nl << "Sum of all pairwise distances: " << totalDist << nl;
    cout << "(This is Σ dist(u,v) for all unordered pairs {u,v})" << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1; cin >> TC;
    while (TC--) solve();
    return 0;
}

/*
═══════════════════════════════════════════════════════════════════
 SAMPLE I/O
═══════════════════════════════════════════════════════════════════

Input:
1
5
1 2 1
1 3 1
2 4 1
2 5 1

Output:
Edge contributions:
  Edge (1,2) w=1: 3 × 2 × 1 = 6
  Edge (1,3) w=1: 1 × 4 × 1 = 4
  Edge (2,4) w=1: 1 × 4 × 1 = 4
  Edge (2,5) w=1: 1 × 4 × 1 = 4

Sum of all pairwise distances: 18

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Edge contribution: sub[v] × (N - sub[v]) paths cross edge (u,v)
 ✅ Sum of all pairwise distances = Σ sub[v]·(N-sub[v])·w(edge)
 ✅ This is O(N) — much faster than O(N²) brute force!
 ✅ Edge DP: dp state on edge instead of node
 ✅ Common pattern: subtree size determines edge usage count
═══════════════════════════════════════════════════════════════════
*/

