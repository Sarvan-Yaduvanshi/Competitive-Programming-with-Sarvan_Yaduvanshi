/*
╔══════════════════════════════════════════════════════════════════╗
║  04 — OFFLINE LCA (Tarjan's Algorithm)                          ║
║  Zero to GM Level — LCA Algorithms                               ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 WHAT IS TARJAN'S OFFLINE LCA?
═══════════════════════════════════════════════════════════════════

 Answer ALL LCA queries at once (offline) using DFS + Union-Find.
 Time: O((N + Q) · α(N)) ≈ O(N + Q)  (α = inverse Ackermann ≈ constant)

 Requirement: ALL queries must be known BEFORE processing.

═══════════════════════════════════════════════════════════════════
 ALGORITHM
═══════════════════════════════════════════════════════════════════

 DFS the tree. For each node v:
   1. Process all children (recurse), union child with v after return.
   2. Mark v as visited.
   3. For all queries (v, u): if u is already visited,
      LCA(v, u) = find(u)  (the representative of u's set = LCA)

═══════════════════════════════════════════════════════════════════
 DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree:
         1
        / \
       2   3
      / \   \
     4   5   6

 Queries: LCA(4,5), LCA(4,6), LCA(5,3)

 DFS(1):
   DFS(2):
     DFS(4): mark 4 visited. Queries with 4: (4,5)→5 not visited yet, skip.
             (4,6)→6 not visited. Union(4, 2).
     DFS(5): mark 5 visited. Query (4,5)→4 visited! LCA = find(4) = 2 ✅
             Union(5, 2).
     Mark 2 visited. Query (5,3)→3 not visited. Union(2, 1).
   DFS(3):
     DFS(6): mark 6 visited. Query (4,6)→4 visited! LCA = find(4).
             find(4)→find(2)→find(1)→1. LCA(4,6) = 1 ✅
             Union(6, 3).
     Mark 3 visited. Query (5,3)→5 visited! LCA = find(5).
             find(5)→find(2)→find(1)→1. LCA(5,3) = 1 ✅
             Union(3, 1).
   Mark 1 visited.

 Results: LCA(4,5)=2, LCA(4,6)=1, LCA(5,3)=1 ✅

═══════════════════════════════════════════════════════════════════
 KEY INSIGHT: After DFS finishes node v and unions it with parent,
 find(v) points to the highest ancestor that's been fully processed.
 When we check a query partner u that's already visited, find(u)
 is exactly the LCA!
═══════════════════════════════════════════════════════════════════

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌──────────────────────────────┬──────────────────┐
 │ Operation                    │ Time             │
 ├──────────────────────────────┼──────────────────┤
 │ Build (DFS + DSU)            │ O((N+Q) α(N))    │
 │ Per query                    │ O(α(N)) ≈ O(1)   │
 │ Total                        │ O(N + Q)          │
 │ Space                        │ O(N + Q)          │
 └──────────────────────────────┴──────────────────┘

 Fastest LCA method in total time (but offline only).

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

const int MAXN = 200005;

// DSU (Union-Find)
int parent_dsu[MAXN], rnk[MAXN];
int ancestor[MAXN]; // ancestor[find(v)] = current LCA candidate

void init_dsu(int n) {
    for (int i = 0; i <= n; i++) {
        parent_dsu[i] = i;
        rnk[i] = 0;
        ancestor[i] = i;
    }
}

int find(int x) {
    if (parent_dsu[x] != x) parent_dsu[x] = find(parent_dsu[x]);
    return parent_dsu[x];
}

void unite(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return;
    if (rnk[x] < rnk[y]) swap(x, y);
    parent_dsu[y] = x;
    if (rnk[x] == rnk[y]) rnk[x]++;
    ancestor[x] = ancestor[find(x)]; // keep ancestor pointer valid
}

vvec<int> adj;
vec<bool> visited;
vec<pii> queries_at[MAXN]; // queries_at[v] = list of (other_node, query_idx)
vec<int> lca_ans;

void tarjanLCA(int v, int par) {
    ancestor[v] = v;

    for (int u : adj[v]) {
        if (u == par) continue;
        tarjanLCA(u, v);
        unite(v, u);
        ancestor[find(v)] = v; // after union, ancestor of set = v
    }

    visited[v] = true;

    // Answer queries involving v
    for (auto [u, idx] : queries_at[v]) {
        if (visited[u]) {
            lca_ans[idx] = ancestor[find(u)];
        }
    }
}

void solve() {
    int n, q;
    cin >> n >> q;

    adj.assign(n + 1, {});
    visited.assign(n + 1, false);
    lca_ans.assign(q, -1);
    init_dsu(n);

    for (int i = 0; i <= n; i++) queries_at[i].clear();

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    for (int i = 0; i < q; i++) {
        int u, v; cin >> u >> v;
        queries_at[u].pb({v, i});
        queries_at[v].pb({u, i}); // add to both sides
    }

    tarjanLCA(1, -1);

    for (int i = 0; i < q; i++) {
        cout << lca_ans[i] << nl;
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
6 3
1 2
1 3
2 4
2 5
3 6
4 5
4 6
5 3

Output:
2
1
1

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Tarjan's offline LCA: DFS + Union-Find → O(N + Q)
 ✅ After DFS(child), union child with parent, set ancestor
 ✅ For query (v, u): if u visited, LCA = ancestor[find(u)]
 ✅ OFFLINE only — all queries must be known beforehand
 ✅ Fastest total time for batch LCA queries
═══════════════════════════════════════════════════════════════════
*/

