/*
╔══════════════════════════════════════════════════════════════════╗
║  02 — KTH NODE ON PATH (u → v)                                 ║
║  Zero to GM Level — Advanced Tree Queries                        ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 PROBLEM: Find the K-th node on the path from u to v
═══════════════════════════════════════════════════════════════════

 Path u→v goes: u → ... → LCA(u,v) → ... → v
 Length = dist(u, LCA) + dist(LCA, v)

 If K ≤ dist(u, LCA): answer is the K-th ancestor of u toward LCA
 Else: answer is from LCA toward v

═══════════════════════════════════════════════════════════════════
 DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree:
         1
        / \
       2   3
      / \   \
     4   5   6
    /
   7

 Path from 7 to 6: 7 → 4 → 2 → 1 → 3 → 6  (length 5)

 K=1: node 7 (start)
 K=2: node 4 (1st step from 7)
 K=3: node 2
 K=4: node 1 = LCA(7,6)
 K=5: node 3
 K=6: node 6 (end)

 LCA(7,6) = 1, dist(7,LCA)=3, dist(6,LCA)=2

 For K=5: K > 3, so we need (K - dist(7,LCA)) = 2 steps from LCA
 But we need to go from LCA toward v=6, so we need the
 (dist(LCA,v) - (K - dist(u,LCA))) = 2 - 2 = 0th ancestor of v
 → answer = v itself = 6? No wait, K=5 should be node 3.

 Correction: Total path length = 5 (edges). K=5 means 5th node (0-indexed from u):
   0:7, 1:4, 2:2, 3:1, 4:3, 5:6

 If K ≤ dist(u,LCA)=3: kth_ancestor(u, K)
 Else: we need (total_dist - K)th ancestor of v from LCA side
   kth_ancestor(v, dist(u,v) - K) = kth_ancestor(6, 5-4) = kth_ancestor(6, 1) = 3 ✅

═══════════════════════════════════════════════════════════════════
 ALGORITHM
═══════════════════════════════════════════════════════════════════

 1. L = LCA(u, v)
 2. du = depth[u] - depth[L]  (dist from u to LCA)
 3. dv = depth[v] - depth[L]  (dist from v to LCA)
 4. If K ≤ du: return kth_ancestor(u, K)
 5. Else: return kth_ancestor(v, du + dv - K)

═══════════════════════════════════════════════════════════════════
 CODE (uses binary lifting from Chapter 08)
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
#include <cstring>
#include <climits>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

const int MAXN = 200005;
const int LOG = 20;

vvec<int> adj;
int dep[MAXN], up[MAXN][LOG];

void dfs(int v, int p, int d) {
    dep[v] = d; up[v][0] = p;
    for (int k = 1; k < LOG; k++) up[v][k] = up[up[v][k-1]][k-1];
    for (int u : adj[v]) if (u != p) dfs(u, v, d + 1);
}

int kthAnc(int v, int k) {
    for (int i = LOG - 1; i >= 0; i--)
        if (k >= (1 << i)) { v = up[v][i]; k -= (1 << i); }
    return v;
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    u = kthAnc(u, dep[u] - dep[v]);
    if (u == v) return u;
    for (int k = LOG - 1; k >= 0; k--)
        if (up[u][k] != up[v][k]) { u = up[u][k]; v = up[v][k]; }
    return up[u][0];
}

// K-th node on path from u to v (0-indexed: K=0 means u)
int kthOnPath(int u, int v, int k) {
    int l = lca(u, v);
    int du = dep[u] - dep[l]; // distance from u to LCA
    int dv = dep[v] - dep[l]; // distance from v to LCA

    if (k <= du) {
        return kthAnc(u, k); // climb from u
    } else {
        return kthAnc(v, du + dv - k); // climb from v
    }
}

void solve() {
    int n, q; cin >> n >> q;
    adj.assign(n + 1, {});
    memset(up, 0, sizeof(up));

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }
    dfs(1, 0, 0);

    while (q--) {
        int u, v, k; cin >> u >> v >> k;
        k--; // convert to 0-indexed
        int total = dep[u] + dep[v] - 2 * dep[lca(u, v)];
        if (k > total) {
            cout << -1 << nl; // K exceeds path length
        } else {
            cout << kthOnPath(u, v, k) << nl;
        }
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
═══════════════════════════════════════════════════════════════════
 SAMPLE I/O
═══════════════════════════════════════════════════════════════════

Input:
1
7
1 2
1 3
2 4
2 5
3 6
4 7
4
7 6 1
7 6 4
7 6 6
4 5 2

Output:
7
1
6
2

 Path 7→6: [7, 4, 2, 1, 3, 6]
 K=1→7, K=4→1, K=6→6
 Path 4→5: [4, 2, 5], K=2→2

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Kth node on path: split at LCA into two halves
 ✅ If K ≤ dist(u, LCA): climb from u
 ✅ Else: climb from v by (total_dist - K)
 ✅ Requires: binary lifting for kth_ancestor + LCA
 ✅ O(log N) per query
═══════════════════════════════════════════════════════════════════
*/

