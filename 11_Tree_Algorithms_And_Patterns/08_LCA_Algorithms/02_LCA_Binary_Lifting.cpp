/*
╔══════════════════════════════════════════════════════════════════╗
║  02 — LCA WITH BINARY LIFTING ⭐ (THE MOST IMPORTANT FILE)     ║
║  Zero to GM Level — LCA Algorithms                               ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 BINARY LIFTING — THE CORE IDEA
═══════════════════════════════════════════════════════════════════

 Instead of climbing one step at a time (O(N)), jump in powers of 2!
 Like binary search but for climbing up the tree.

 up[v][k] = 2^k-th ancestor of v

 Example: up[v][0] = parent of v (2^0 = 1 step)
          up[v][1] = grandparent of v (2^1 = 2 steps)
          up[v][2] = 4th ancestor of v (2^2 = 4 steps)

 KEY RECURRENCE:
   up[v][0] = parent(v)
   up[v][k] = up[ up[v][k-1] ][k-1]

 In words: the 2^k-th ancestor = go 2^(k-1) steps, then 2^(k-1) more.
 (Because 2^k = 2^(k-1) + 2^(k-1))

═══════════════════════════════════════════════════════════════════
 BUILDING THE TABLE — DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree (root=1):
           1
          / \
         2   3
        / \   \
       4   5   6
      /
     7

 depth: [_, 0, 1, 1, 2, 2, 2, 3]

 LOG = 3 (since N=7, ⌊log₂7⌋+1 = 3)

 up[v][0] (parent):
   up[1][0]=0, up[2][0]=1, up[3][0]=1, up[4][0]=2
   up[5][0]=2, up[6][0]=3, up[7][0]=4

 up[v][1] = up[up[v][0]][0] (grandparent):
   up[1][1]=up[0][0]=0, up[2][1]=up[1][0]=0
   up[3][1]=up[1][0]=0, up[4][1]=up[2][0]=1
   up[5][1]=up[2][0]=1, up[6][1]=up[3][0]=1
   up[7][1]=up[4][0]=2

 up[v][2] = up[up[v][1]][1] (4th ancestor):
   up[7][2]=up[2][1]=0 (7's 4th ancestor = root's parent = 0 ✅)

═══════════════════════════════════════════════════════════════════
 LCA QUERY — DRY RUN
═══════════════════════════════════════════════════════════════════

 LCA(7, 6): depth[7]=3, depth[6]=2

 Step 1: Equalize depths (lift deeper node)
   diff = 3 - 2 = 1 = binary: 1
   Lift 7 by 2^0 = 1: 7 → up[7][0] = 4
   Now u=4 (depth 2), v=6 (depth 2)

 Step 2: If u == v, return u. 4 ≠ 6, continue.

 Step 3: Lift both TOGETHER using binary lifting
   k=2: up[4][2]=0, up[6][2]=0 → same → skip (don't lift)
   k=1: up[4][1]=1, up[6][1]=1 → same → skip
   k=0: up[4][0]=2, up[6][0]=3 → different → LIFT!
     u = up[4][0] = 2, v = up[6][0] = 3

 Step 4: LCA = parent of u = up[2][0] = 1 ✅

 ─────────────────────────────────────────────────────────────
 LCA(7, 5): depth[7]=3, depth[5]=2

 Step 1: diff = 1. Lift 7 by 1: 7→4. Now u=4, v=5

 Step 2: 4 ≠ 5

 Step 3:
   k=1: up[4][1]=1, up[5][1]=1 → same → skip
   k=0: up[4][0]=2, up[5][0]=2 → same → skip

 Wait, all same? That means u and v are already children of LCA.
 LCA = up[4][0] = 2 ✅

═══════════════════════════════════════════════════════════════════
 LCA ALGORITHM SUMMARY
═══════════════════════════════════════════════════════════════════

 1. If depth[u] < depth[v], swap(u, v) so u is deeper
 2. Lift u to same depth as v using binary lifting
    For each bit k from high to low:
      if (depth[u] - depth[v]) has bit k set → u = up[u][k]
 3. If u == v, return u (v was ancestor of original u)
 4. Lift both u and v together:
    For each k from high to low:
      if up[u][k] ≠ up[v][k] → u = up[u][k], v = up[v][k]
 5. LCA = up[u][0] = parent of u

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌──────────────────────────┬──────────────────┬──────────────┐
 │ Operation                │ Time             │ Space        │
 ├──────────────────────────┼──────────────────┼──────────────┤
 │ Build up[][] table       │ O(N log N)       │ O(N log N)   │
 │ LCA query                │ O(log N)         │ O(1)         │
 │ Distance query           │ O(log N)         │ O(1)         │
 │ Kth ancestor query       │ O(log N)         │ O(1)         │
 └──────────────────────────┴──────────────────┴──────────────┘

═══════════════════════════════════════════════════════════════════
 CODE — PRODUCTION-READY BINARY LIFTING LCA
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

// ═══════════════════════════════════════════════════════════
// BINARY LIFTING LCA — COMPLETE IMPLEMENTATION
// ═══════════════════════════════════════════════════════════
const int LOG = 20; // enough for N ≤ 10^6

vvec<int> adj;
vec<int> depth;
int up[200005][LOG]; // up[v][k] = 2^k-th ancestor of v

void dfs(int v, int p, int d) {
    depth[v] = d;
    up[v][0] = p;
    for (int k = 1; k < LOG; k++) {
        up[v][k] = up[up[v][k-1]][k-1]; // KEY RECURRENCE
    }
    for (int u : adj[v]) {
        if (u != p) dfs(u, v, d + 1);
    }
}

// Kth ancestor of v (returns 0 if doesn't exist)
int kthAncestor(int v, int k) {
    for (int i = LOG - 1; i >= 0; i--) {
        if (k >= (1 << i)) {
            v = up[v][i];
            k -= (1 << i);
        }
    }
    return v;
}

// LCA in O(log N)
int lca(int u, int v) {
    // Step 1: Make u the deeper node
    if (depth[u] < depth[v]) swap(u, v);

    // Step 2: Lift u to same depth as v
    int diff = depth[u] - depth[v];
    for (int k = LOG - 1; k >= 0; k--) {
        if ((diff >> k) & 1) {
            u = up[u][k];
        }
    }

    // Step 3: If same node, we found LCA
    if (u == v) return u;

    // Step 4: Lift both until just below LCA
    for (int k = LOG - 1; k >= 0; k--) {
        if (up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k];
        }
    }

    // Step 5: LCA is the parent
    return up[u][0];
}

// Distance between u and v
int dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}

void solve() {
    int n;
    cin >> n;
    adj.assign(n + 1, {});
    depth.assign(n + 1, 0);
    memset(up, 0, sizeof(up));

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    dfs(1, 0, 0); // root=1, parent=0 (sentinel)

    int q; cin >> q;
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            // LCA query
            int u, v; cin >> u >> v;
            cout << "LCA(" << u << ", " << v << ") = " << lca(u, v) << nl;
        } else if (type == 2) {
            // Distance query
            int u, v; cin >> u >> v;
            cout << "dist(" << u << ", " << v << ") = " << dist(u, v) << nl;
        } else {
            // Kth ancestor
            int v, k; cin >> v >> k;
            int ans = kthAncestor(v, k);
            cout << "ancestor(" << v << ", " << k << ") = "
                 << (ans == 0 ? -1 : ans) << nl;
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
 SAMPLE INPUT / OUTPUT
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
6
1 7 6
1 7 5
1 4 7
2 7 6
3 7 2
3 7 1

Output:
LCA(7, 6) = 1
LCA(7, 5) = 2
LCA(4, 7) = 4
dist(7, 6) = 5
ancestor(7, 2) = 2
ancestor(7, 1) = 4

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS — MEMORIZE THIS!
═══════════════════════════════════════════════════════════════════
 ✅ up[v][0] = parent(v)
 ✅ up[v][k] = up[up[v][k-1]][k-1]  (the MAGIC recurrence)
 ✅ LCA: equalize depth, then lift both until just below LCA
 ✅ dist(u,v) = depth[u] + depth[v] - 2·depth[LCA(u,v)]
 ✅ Build: O(N log N), Query: O(log N)
 ✅ Use LOG=20 for N≤10^6, LOG=25 for N≤3×10^7
 ✅ CSES problems: Company Queries I (Kth ancestor),
    Company Queries II (LCA), Distance Queries
═══════════════════════════════════════════════════════════════════
*/

