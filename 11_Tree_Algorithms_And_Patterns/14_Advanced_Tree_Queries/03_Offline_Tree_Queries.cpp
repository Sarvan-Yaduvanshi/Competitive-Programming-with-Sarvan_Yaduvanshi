/*
╔══════════════════════════════════════════════════════════════════╗
║  03 — OFFLINE TREE QUERIES (Batch Processing)                   ║
║  Zero to GM Level — Advanced Tree Queries                        ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 CONCEPT: Process all queries together, not one-by-one
═══════════════════════════════════════════════════════════════════

 When queries are independent and order doesn't matter:
   - Sort/group queries by node or subtree
   - Process during a single DFS
   - Answer all at once

═══════════════════════════════════════════════════════════════════
 TECHNIQUE 1: DFS + Collect Queries at Nodes
═══════════════════════════════════════════════════════════════════

 Problem: For each query (v, k), answer "count of nodes in
 subtree(v) with value ≤ k."

 Offline approach:
   1. Store queries at their target node v
   2. DFS the tree; maintain a data structure (BIT/merge sort)
   3. When entering subtree(v), record state
   4. When leaving subtree(v), answer queries for v by
      comparing current state vs entry state

═══════════════════════════════════════════════════════════════════
 TECHNIQUE 2: Euler Tour + Offline Sort
═══════════════════════════════════════════════════════════════════

 Convert subtree queries to range queries via Euler tour:
   subtree(v) = [tin[v], tout[v]]

 Then sort all queries + all node positions together,
 sweep left-to-right with a BIT.

═══════════════════════════════════════════════════════════════════
 DRY RUN — Offline subtree sum queries
═══════════════════════════════════════════════════════════════════

 Tree: val = [_, 3, 1, 4, 1, 5]
         1(3)
        / \
    (1)2   3(4)
      / \
  (1)4   5(5)

 Euler tour: tin=[_,0,1,4,2,3], tout=[_,4,3,4,2,3]
 DFS order: [1, 2, 4, 5, 3]
 vals in order: [3, 1, 1, 5, 4]

 Queries: subtree_sum(2), subtree_sum(1), subtree_sum(3)

 subtree_sum(2) = range [1,3] = 1+1+5 = 7
 subtree_sum(1) = range [0,4] = 3+1+1+5+4 = 14
 subtree_sum(3) = range [4,4] = 4

 Batch: compute all prefix sums once, answer all in O(1) each!

═══════════════════════════════════════════════════════════════════
 TECHNIQUE 3: Offline LCA Queries (Tarjan) — see Ch08 file 04
═══════════════════════════════════════════════════════════════════

═══════════════════════════════════════════════════════════════════
 CODE — Offline subtree queries with Euler tour
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
vec<i64> val;
vec<int> tin, tout, euler_order;
int timer_val;

void eulerTour(int v, int par) {
    tin[v] = timer_val;
    euler_order.pb(v);
    timer_val++;
    for (int u : adj[v])
        if (u != par) eulerTour(u, v);
    tout[v] = timer_val - 1;
}

void solve() {
    int n, q;
    cin >> n >> q;

    val.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> val[i];

    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    tin.assign(n + 1, 0);
    tout.assign(n + 1, 0);
    euler_order.clear();
    timer_val = 0;
    eulerTour(1, -1);

    // Build prefix sums on Euler order values
    vec<i64> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + val[euler_order[i]];
    }

    // Answer all subtree sum queries in O(1) each
    while (q--) {
        int v; cin >> v;
        i64 subtreeSum = prefix[tout[v] + 1] - prefix[tin[v]];
        cout << subtreeSum << nl;
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
3 1 4 1 5
1 2
1 3
2 4
2 5
2
1
3

Output:
7
14
4

 subtree_sum(2) = val[2]+val[4]+val[5] = 1+1+5 = 7
 subtree_sum(1) = 3+1+4+1+5 = 14
 subtree_sum(3) = 4

═══════════════════════════════════════════════════════════════════
 OFFLINE QUERY TECHNIQUES SUMMARY
═══════════════════════════════════════════════════════════════════

 ┌────────────────────────────┬───────────────────────────────────┐
 │ Technique                  │ Use Case                          │
 ├────────────────────────────┼───────────────────────────────────┤
 │ Euler tour + prefix sum    │ Static subtree sum/count queries  │
 │ Euler tour + BIT           │ Subtree queries with updates      │
 │ Tarjan offline LCA (Ch08)  │ Batch LCA queries                 │
 │ Mo on tree (Ch16)          │ Distinct values on path           │
 │ DFS + store queries at node│ Complex subtree aggregations      │
 │ Centroid D&C (Ch13)        │ Distance-based path queries       │
 └────────────────────────────┴───────────────────────────────────┘

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Offline = process all queries at once during single DFS
 ✅ Euler tour converts subtree → range → use prefix sums/BIT
 ✅ Group queries by node, answer during DFS
 ✅ Often O(N + Q) or O((N+Q) log N) vs O(NQ) online
 ✅ See also: Tarjan LCA (Ch08), Mo on Tree (Ch16)
═══════════════════════════════════════════════════════════════════
*/

