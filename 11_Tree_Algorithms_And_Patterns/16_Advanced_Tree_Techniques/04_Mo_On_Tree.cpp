/*
╔══════════════════════════════════════════════════════════════════╗
║  04 — MO'S ALGORITHM ON TREE                                   ║
║  Zero to GM Level — Advanced Tree Techniques                     ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 CONCEPT: Apply Mo's algorithm to path queries on tree
═══════════════════════════════════════════════════════════════════

 1. Flatten tree using Euler tour (enter + exit times)
 2. For path query (u, v) with L = LCA(u, v):
    - If L == u or L == v: query on range [tin[u], tin[v]] (or vice versa)
    - Else: query on range [tout[u], tin[v]] + add LCA separately
 3. Each node toggled in/out based on whether it appears odd times

═══════════════════════════════════════════════════════════════════
 DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree: color = [_, 1, 2, 1, 3, 2]
         1(c=1)
        / \
    (2)2   3(1)
      / \
  (3)4   5(2)

 Euler tour (enter+exit):
   Enter 1(0), Enter 2(1), Enter 4(2), Exit 4(3), Enter 5(4),
   Exit 5(5), Exit 2(6), Enter 3(7), Exit 3(8)

 flat = [1, 2, 4, 4, 5, 5, 2, 3, 3]  (node at each position)

 Query: distinct colors on path(4, 3)?
   LCA(4, 3) = 1
   L ≠ u and L ≠ v → range = [tout[4]=3, tin[3]=7] + add LCA
   Range [3..7]: flat = [4, 5, 5, 2, 3]
   Toggle: 4 appears 1 time (active), 5 appears 2 times (inactive),
           2 appears 1 time (active), 3 appears 1 time (active)
   Active nodes: {4, 2, 3} + LCA = {4, 2, 3, 1}
   Colors: {3, 2, 1, 1} → distinct = 3 ✅

 Path: 4→2→1→3, colors: 3,2,1,1 → distinct = 3 ✅

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 Sort queries by Mo's blocks: O(Q log Q)
 Process: O((N + Q) · √N) total

═══════════════════════════════════════════════════════════════════
 CODE (Distinct colors on paths — Mo on tree)
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
#include <cmath>
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
int color[MAXN];
int tin[MAXN], tout[MAXN], flat_arr[2 * MAXN]; // Euler tour (2N)
int dep[MAXN], up[MAXN][LOG];
int timer_val;

void dfs(int v, int p, int d) {
    dep[v] = d; up[v][0] = p;
    for (int k = 1; k < LOG; k++) up[v][k] = up[up[v][k-1]][k-1];
    tin[v] = timer_val;
    flat_arr[timer_val++] = v;
    for (int u : adj[v]) if (u != p) dfs(u, v, d + 1);
    tout[v] = timer_val;
    flat_arr[timer_val++] = v;
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v];
    for (int k = LOG-1; k >= 0; k--)
        if ((diff >> k) & 1) u = up[u][k];
    if (u == v) return u;
    for (int k = LOG-1; k >= 0; k--)
        if (up[u][k] != up[v][k]) { u = up[u][k]; v = up[v][k]; }
    return up[u][0];
}

// Mo's data structures
int cnt[MAXN]; // frequency of each color in current window
bool active[MAXN]; // is node active (toggled odd times)?
int distinct_count;

void toggle(int node) {
    if (active[node]) {
        // Remove
        cnt[color[node]]--;
        if (cnt[color[node]] == 0) distinct_count--;
        active[node] = false;
    } else {
        // Add
        if (cnt[color[node]] == 0) distinct_count++;
        cnt[color[node]]++;
        active[node] = true;
    }
}

struct Query {
    int l, r, lca_node, idx;
};

void solve() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) cin >> color[i];

    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    timer_val = 0;
    memset(up, 0, sizeof(up));
    dfs(1, 0, 0);

    int BLOCK = max(1, (int)sqrt(2 * n));

    vec<Query> queries(q);
    for (int i = 0; i < q; i++) {
        int u, v; cin >> u >> v;
        if (tin[u] > tin[v]) swap(u, v);
        int l = lca(u, v);

        if (l == u) {
            queries[i] = {tin[u], tin[v], 0, i}; // LCA is one endpoint
        } else {
            queries[i] = {tout[u], tin[v], l, i}; // need to add LCA separately
        }
    }

    // Sort by Mo's blocks
    sort(queries.begin(), queries.end(), [&](const Query& a, const Query& b) {
        int ba = a.l / BLOCK, bb = b.l / BLOCK;
        if (ba != bb) return ba < bb;
        return (ba & 1) ? (a.r > b.r) : (a.r < b.r);
    });

    memset(cnt, 0, sizeof(cnt));
    memset(active, false, sizeof(active));
    distinct_count = 0;

    vec<int> ans(q);
    int curL = 0, curR = -1;

    for (auto& qr : queries) {
        while (curR < qr.r) toggle(flat_arr[++curR]);
        while (curL > qr.l) toggle(flat_arr[--curL]);
        while (curR > qr.r) toggle(flat_arr[curR--]);
        while (curL < qr.l) toggle(flat_arr[curL++]);

        if (qr.lca_node) toggle(qr.lca_node); // add LCA
        ans[qr.idx] = distinct_count;
        if (qr.lca_node) toggle(qr.lca_node); // remove LCA
    }

    for (int i = 0; i < q; i++) cout << ans[i] << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1;
    while (TC--) solve();
    return 0;
}

/*
═══════════════════════════════════════════════════════════════════
 SAMPLE I/O
═══════════════════════════════════════════════════════════════════

Input:
5 2
1 2 1 3 2
1 2
1 3
2 4
2 5
4 3
4 5

Output:
3
2

 Path(4,3): 4→2→1→3, colors {3,2,1,1} → 3 distinct
 Path(4,5): 4→2→5, colors {3,2,2} → 2 distinct

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Flatten tree: Euler tour with 2N array (enter+exit)
 ✅ Path query → range query on flattened array
 ✅ Toggle mechanism: nodes active if they appear odd times
 ✅ If LCA ≠ endpoint, add it separately
 ✅ O((N + Q) · √N) total time
 ✅ Solves: distinct values on path, most frequent on path, etc.
═══════════════════════════════════════════════════════════════════
*/

