/*
╔══════════════════════════════════════════════════════════════════╗
║  01 — SUBTREE & PATH QUERIES (CSES Combined)                   ║
║  Zero to GM Level — Advanced Tree Queries                        ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 PROBLEM: Handle both subtree and path queries on same tree
═══════════════════════════════════════════════════════════════════

 Euler tour for subtree queries: subtree(v) = [tin[v], tout[v]]

 Path queries using Euler tour + prefix sums:
   Assign +val[v] at tin[v] and -val[v] at tout[v]+1
   Then path sum from root to v = prefix_sum(tin[v])
   Path sum(u,v) = prefix(u) + prefix(v) - 2*prefix(LCA) + val[LCA]

═══════════════════════════════════════════════════════════════════
 CODE — PATH QUERIES (CSES)
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
i64 val[MAXN];
int tin[MAXN], tout[MAXN], par_arr[MAXN], dep[MAXN];
int up[MAXN][LOG];
int timer_val;
int euler[MAXN]; // DFS order

// BIT for prefix path sums
i64 bit[2 * MAXN];
int bit_n;

void bit_update(int i, i64 delta) {
    for (++i; i <= bit_n; i += i & (-i)) bit[i] += delta;
}

i64 bit_query(int i) {
    i64 s = 0;
    for (++i; i > 0; i -= i & (-i)) s += bit[i];
    return s;
}

void dfs(int v, int p, int d) {
    par_arr[v] = p;
    dep[v] = d;
    up[v][0] = p;
    for (int k = 1; k < LOG; k++) up[v][k] = up[up[v][k-1]][k-1];

    tin[v] = timer_val++;
    for (int u : adj[v]) if (u != p) dfs(u, v, d + 1);
    tout[v] = timer_val++;
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

void solve() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) cin >> val[i];

    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    timer_val = 0;
    memset(up, 0, sizeof(up));
    dfs(1, 0, 0);

    bit_n = 2 * n + 5;
    memset(bit, 0, sizeof(bit));

    // Initialize: +val at entry, -val at exit
    for (int i = 1; i <= n; i++) {
        bit_update(tin[i], val[i]);
        bit_update(tout[i], -val[i]);
    }

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int s; i64 x; cin >> s >> x;
            // Update node s: remove old, add new
            bit_update(tin[s], x - val[s]);
            bit_update(tout[s], -(x - val[s]));
            val[s] = x;
        } else {
            int u, v; cin >> u >> v;
            int l = lca(u, v);
            // Path sum = root_to_u + root_to_v - 2*root_to_lca + val[lca]
            i64 ans = bit_query(tin[u]) + bit_query(tin[v])
                    - 2 * bit_query(tin[l]) + val[l];
            cout << ans << nl;
        }
    }
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
15

 Path(4,5): val[4]+val[2]+val[5] = 1+2+3 = 6
 Update 4→10: val[4]=10
 Path(4,5): 10+2+3 = 15

═══════════════════════════════════════════════════════════════════
 KEY: root_to_v sum via Euler tour BIT prefix query.
 Path(u,v) = root_to_u + root_to_v - 2·root_to_LCA + val[LCA]
═══════════════════════════════════════════════════════════════════
*/

