/*
╔══════════════════════════════════════════════════════════════════╗
║  05 — VERTEX COVER & TREE COLORING DP                           ║
║  Zero to GM Level — Tree DP                                      ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 1. MINIMUM VERTEX COVER
═══════════════════════════════════════════════════════════════════

 Vertex cover: subset of nodes such that EVERY EDGE has at least
 one endpoint in the set. Find MINIMUM size.

 dp[v][0] = min vertex cover of subtree(v) when v is NOT in cover
 dp[v][1] = min vertex cover of subtree(v) when v IS in cover

 Transitions:
   dp[v][0] = Σ dp[u][1]     ← if v not in cover, ALL children MUST be
   dp[v][1] = 1 + Σ min(dp[u][0], dp[u][1])  ← children can be either

═══════════════════════════════════════════════════════════════════
 DRY RUN — Minimum Vertex Cover
═══════════════════════════════════════════════════════════════════

 Tree:
         1
        / \
       2   3
      / \
     4   5

 dp[4][0]=0, dp[4][1]=1
 dp[5][0]=0, dp[5][1]=1
 dp[2][0] = dp[4][1] + dp[5][1] = 1+1 = 2
 dp[2][1] = 1 + min(0,1) + min(0,1) = 1+0+0 = 1
 dp[3][0]=0, dp[3][1]=1
 dp[1][0] = dp[2][1] + dp[3][1] = 1+1 = 2
 dp[1][1] = 1 + min(2,1) + min(0,1) = 1+1+0 = 2

 Answer = min(dp[1][0], dp[1][1]) = min(2, 2) = 2
 Cover: {2, 3} — covers edges (1,2), (1,3), (2,4), (2,5) ✅

═══════════════════════════════════════════════════════════════════
 RELATIONSHIP: Independent Set + Vertex Cover = N
               (König's theorem on trees)
═══════════════════════════════════════════════════════════════════

 Max Independent Set = N - Min Vertex Cover
 For the tree above: 5 - 2 = 3 (nodes {1, 4, 5}) ✅

═══════════════════════════════════════════════════════════════════
 2. TREE COLORING — Minimum colors to color tree
═══════════════════════════════════════════════════════════════════

 A tree is BIPARTITE → always 2-colorable!
 (no odd cycles → chromatic number = 2, or 1 if single node)

 Proof: BFS/DFS assigns alternating colors by depth.
   depth even → color 0
   depth odd  → color 1
 No two adjacent nodes have same depth → valid 2-coloring ✅

═══════════════════════════════════════════════════════════════════
 3. TREE 2-COLORING (Bipartite Check) — DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree:
         1 (depth 0 → color 0)
        / \
       2   3 (depth 1 → color 1)
      / \
     4   5 (depth 2 → color 0)

 Coloring: {1→0, 2→1, 3→1, 4→0, 5→0}
 Check: every edge connects different colors ✅

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

// ═══════════════════════════════════════════════════════════
// MINIMUM VERTEX COVER DP
// ═══════════════════════════════════════════════════════════
vec<int> vc0, vc1; // dp[v][0/1]

void dfsVertexCover(int v, int par) {
    vc0[v] = 0; // v not in cover
    vc1[v] = 1; // v in cover
    for (int u : adj[v]) {
        if (u == par) continue;
        dfsVertexCover(u, v);
        vc0[v] += vc1[u];           // children MUST be in cover
        vc1[v] += min(vc0[u], vc1[u]); // children can be either
    }
}

// ═══════════════════════════════════════════════════════════
// TREE 2-COLORING (bipartite)
// ═══════════════════════════════════════════════════════════
vec<int> color;

void dfsColor(int v, int par, int c) {
    color[v] = c;
    for (int u : adj[v]) {
        if (u == par) continue;
        dfsColor(u, v, 1 - c); // alternate color
    }
}

void solve() {
    int n; cin >> n;
    adj.assign(n + 1, {});
    vc0.assign(n + 1, 0);
    vc1.assign(n + 1, 0);
    color.assign(n + 1, -1);

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    // Vertex Cover
    dfsVertexCover(1, -1);
    int minVC = min(vc0[1], vc1[1]);
    cout << "Minimum Vertex Cover: " << minVC << nl;
    cout << "Maximum Independent Set: " << n - minVC << nl;

    // 2-Coloring
    dfsColor(1, -1, 0);
    int cnt0 = 0, cnt1 = 0;
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) cnt0++;
        else cnt1++;
    }
    cout << "2-Coloring: " << cnt0 << " nodes color 0, " << cnt1 << " nodes color 1" << nl;
    cout << "  Colors: ";
    for (int i = 1; i <= n; i++) cout << color[i] << " ";
    cout << nl;
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
1 2
1 3
2 4
2 5

Output:
Minimum Vertex Cover: 2
Maximum Independent Set: 3
2-Coloring: 3 nodes color 0, 2 nodes color 1
  Colors: 0 1 1 0 0

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Min Vertex Cover: dp[v][0]=Σ dp[u][1], dp[v][1]=1+Σ min(dp[u][0/1])
 ✅ Max Independent Set = N - Min Vertex Cover (König on trees)
 ✅ Trees are always bipartite → 2-colorable
 ✅ 2-coloring: alternate colors by depth (BFS/DFS)
 ✅ All O(N) time, O(N) space
═══════════════════════════════════════════════════════════════════
*/

