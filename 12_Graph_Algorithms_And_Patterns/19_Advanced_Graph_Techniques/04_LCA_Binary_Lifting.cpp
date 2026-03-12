/*
╔══════════════════════════════════════════════════════════════════╗
║         LCA — LOWEST COMMON ANCESTOR (Binary Lifting)           ║
║         Foundation for virtual tree, path queries               ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

LCA(u, v) = deepest node that is ancestor of BOTH u and v.

BINARY LIFTING:
  up[v][k] = 2^k-th ancestor of v
  up[v][0] = parent[v]
  up[v][k] = up[up[v][k-1]][k-1]

QUERY LCA(u,v):
  1. Bring u, v to same depth (jump using binary lifting)
  2. Binary search: jump together until parents differ
  3. Answer = parent of current position

Preprocess: O(n log n)    Query: O(log n)

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

depth: 1=0, 2=1, 3=1, 4=2, 5=2, 6=2, 7=3

LCA(7, 5):
  depth[7]=3, depth[5]=2 → lift 7 by 1 → 7→4
  Now both at depth 2: 4 and 5
  up[4][0]=2, up[5][0]=2 → same! LCA = 2

LCA(7, 6):
  depth[7]=3, depth[6]=2 → lift 7 by 1 → 4
  Now: 4(depth 2) and 6(depth 2)
  up[4][0]=2, up[6][0]=3 → different
  Move up: 2 and 3
  up[2][0]=1, up[3][0]=1 → same! LCA = 1

═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define pb push_back
#define nl '\n'

const int LOG = 20;

struct LCA_BinaryLifting {
    int n;
    vvec<int> adj;
    vec<int> depth, tin, tout;
    int up[200005][20]; // up[v][k] = 2^k ancestor
    int timer = 0;

    LCA_BinaryLifting(int n) : n(n), adj(n), depth(n), tin(n), tout(n) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < LOG; j++) up[i][j] = 0;
    }

    void addEdge(int u, int v) { adj[u].pb(v); adj[v].pb(u); }

    void dfs(int v, int p, int d) {
        depth[v] = d;
        tin[v] = timer++;
        up[v][0] = p;
        for (int k = 1; k < LOG; k++)
            up[v][k] = up[up[v][k-1]][k-1];
        for (int u : adj[v])
            if (u != p) dfs(u, v, d + 1);
        tout[v] = timer++;
    }

    bool isAncestor(int u, int v) {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    int lca(int u, int v) {
        if (isAncestor(u, v)) return u;
        if (isAncestor(v, u)) return v;
        for (int k = LOG - 1; k >= 0; k--)
            if (!isAncestor(up[u][k], v))
                u = up[u][k];
        return up[u][0];
    }

    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    // k-th ancestor of v
    int kthAncestor(int v, int k) {
        for (int j = 0; j < LOG; j++)
            if (k & (1 << j)) v = up[v][j];
        return v;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    LCA_BinaryLifting lca(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v; u--; v--;
        lca.addEdge(u, v);
    }

    lca.dfs(0, 0, 0);

    while (q--) {
        int u, v; cin >> u >> v; u--; v--;
        int l = lca.lca(u, v);
        cout << "LCA(" << u+1 << "," << v+1 << ") = " << l+1
             << ", dist = " << lca.dist(u, v) << nl;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

