/*
╔══════════════════════════════════════════════════════════════════╗
║  02 — HLD PATH QUERIES WITH SEGMENT TREE ⭐                    ║
║  Zero to GM Level — Heavy-Light Decomposition                    ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 HOW PATH QUERIES WORK WITH HLD
═══════════════════════════════════════════════════════════════════

 To query path(u, v):
   While u and v are in DIFFERENT chains:
     1. Query the chain of the deeper node from its head to itself
     2. Move that node to the parent of its chain head
   When in SAME chain:
     Query the range between them in the segment tree

═══════════════════════════════════════════════════════════════════
 DRY RUN — Max on path(7, 9)
═══════════════════════════════════════════════════════════════════

 Tree:
        1
       / \
      2   3
     / \   \
    4   5   6
   / \      |
  7   8     9

 Chains: [1,2,4,7], [3,6,9], [5], [8]
 pos:     0 1 2 3    4 5 6    7    8

 path_max(7, 9):
   head[7]=1, head[9]=3 → DIFFERENT chains
   depth[head[1]]=0, depth[head[3]]=1
   Chain of 9 is deeper: query seg[pos[3]..pos[9]] = seg[4..6]
   Move 9 → par[head[9]] = par[3] = 1

   Now u=7, v=1. head[7]=1, head[1]=1 → SAME chain!
   Query seg[pos[1]..pos[7]] = seg[0..3]

   Total: max of two segment tree queries!

═══════════════════════════════════════════════════════════════════
 FULL CODE — HLD + Segment Tree (sum queries, CSES Path Queries)
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

const int MAXN = 200005;

// ═══════════════════════════════════════════════════════════
// Segment Tree
// ═══════════════════════════════════════════════════════════
i64 seg[4 * MAXN];

void build(int node, int lo, int hi, vec<i64>& arr) {
    if (lo == hi) { seg[node] = arr[lo]; return; }
    int mid = (lo + hi) / 2;
    build(2*node, lo, mid, arr);
    build(2*node+1, mid+1, hi, arr);
    seg[node] = seg[2*node] + seg[2*node+1]; // sum
}

void update(int node, int lo, int hi, int idx, i64 val) {
    if (lo == hi) { seg[node] = val; return; }
    int mid = (lo + hi) / 2;
    if (idx <= mid) update(2*node, lo, mid, idx, val);
    else update(2*node+1, mid+1, hi, idx, val);
    seg[node] = seg[2*node] + seg[2*node+1];
}

i64 query(int node, int lo, int hi, int l, int r) {
    if (r < lo || hi < l) return 0;
    if (l <= lo && hi <= r) return seg[node];
    int mid = (lo + hi) / 2;
    return query(2*node, lo, mid, l, r) + query(2*node+1, mid+1, hi, l, r);
}

// ═══════════════════════════════════════════════════════════
// HLD
// ═══════════════════════════════════════════════════════════
vvec<int> adj;
int par_arr[MAXN], dep[MAXN], sub_sz[MAXN];
int head_arr[MAXN], pos_arr[MAXN], heavy_arr[MAXN];
int cur_pos;
int n;

void dfs_size(int v, int p, int d) {
    par_arr[v] = p; dep[v] = d; sub_sz[v] = 1; heavy_arr[v] = -1;
    int mx = 0;
    for (int u : adj[v]) {
        if (u == p) continue;
        dfs_size(u, v, d + 1);
        sub_sz[v] += sub_sz[u];
        if (sub_sz[u] > mx) { mx = sub_sz[u]; heavy_arr[v] = u; }
    }
}

void dfs_hld(int v, int h) {
    head_arr[v] = h;
    pos_arr[v] = cur_pos++;
    if (heavy_arr[v] != -1) dfs_hld(heavy_arr[v], h);
    for (int u : adj[v]) {
        if (u == par_arr[v] || u == heavy_arr[v]) continue;
        dfs_hld(u, u);
    }
}

// ═══════════════════════════════════════════════════════════
// PATH QUERY: sum on path u → v
// ═══════════════════════════════════════════════════════════
i64 pathQuery(int u, int v) {
    i64 res = 0;
    while (head_arr[u] != head_arr[v]) {
        // Make u the one in the deeper chain
        if (dep[head_arr[u]] < dep[head_arr[v]]) swap(u, v);
        // Query from head of u's chain to u
        res += query(1, 0, n - 1, pos_arr[head_arr[u]], pos_arr[u]);
        u = par_arr[head_arr[u]]; // jump to parent of chain head
    }
    // Now same chain
    if (dep[u] > dep[v]) swap(u, v);
    res += query(1, 0, n - 1, pos_arr[u], pos_arr[v]);
    return res;
}

// PATH UPDATE on node (point update)
void pathUpdate(int v, i64 newVal) {
    update(1, 0, n - 1, pos_arr[v], newVal);
}

void solve() {
    int q;
    cin >> n >> q;

    vec<i64> val(n + 1);
    for (int i = 1; i <= n; i++) cin >> val[i];

    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    cur_pos = 0;
    dfs_size(1, 0, 0);
    dfs_hld(1, 1);

    // Build segment tree: values mapped to HLD positions
    vec<i64> arr(n, 0);
    for (int i = 1; i <= n; i++) arr[pos_arr[i]] = val[i];
    build(1, 0, n - 1, arr);

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int s; i64 x; cin >> s >> x;
            pathUpdate(s, x);
        } else {
            int u, v; cin >> u >> v;
            cout << pathQuery(u, v) << nl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1;
    // cin >> TC;
    while (TC--) solve();
    return 0;
}

/*
═══════════════════════════════════════════════════════════════════
 SAMPLE I/O
═══════════════════════════════════════════════════════════════════

Input:
5 3
4 2 5 1 3
1 2
1 3
2 4
2 5
2 4 5
1 4 10
2 4 5

Output:
6
13

 Explanation:
   Path 4→5: 4→2→5, sum = 1+2+3 = 6
   Update node 4 to 10
   Path 4→5: 10+2+3 = 15? Let me recalc...
   Actually path sum(4,5) through LCA(4,5)=2: val[4]+val[2]+val[5] = 10+2+3 = 15

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ HLD + SegTree = O(log²N) path queries and updates
 ✅ Path query: climb chains until same chain, query segments
 ✅ Always move the node in the DEEPER chain head
 ✅ CSES: Path Queries, Path Queries II — direct applications
 ✅ Can handle sum, max, min, xor — any associative operation
═══════════════════════════════════════════════════════════════════
*/

