/*
╔══════════════════════════════════════════════════════════════════╗
║       03 — EDGE LIST REPRESENTATION                             ║
║       Zero to GM Level — Tree Representations                    ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 CONCEPT
═══════════════════════════════════════════════════════════════════

 Store edges as a list of (u, v) pairs (optionally with weight).

 Useful when:
   - You need to iterate over ALL edges (e.g., Kruskal's MST)
   - You need to reference edges by INDEX
   - Problems ask about specific edges

 Tree:
         1
        / \
       2   3
      /
     4

 Edge list: [(1,2), (1,3), (2,4)]
 Edge indices: edge 0 = (1,2), edge 1 = (1,3), edge 2 = (2,4)

═══════════════════════════════════════════════════════════════════
 DRY RUN: EDGE INDEXING
═══════════════════════════════════════════════════════════════════

 Input: N=5, edges with weights
   1 2 5
   2 3 3
   3 4 7
   4 5 2

 Edge list (0-indexed):
   edge[0] = {1, 2, weight=5}
   edge[1] = {2, 3, weight=3}
   edge[2] = {3, 4, weight=7}
   edge[3] = {4, 5, weight=2}

 To also know which edge connects u and v during DFS:
   Store edge index in adjacency list.
   adj[u] = {(v, edge_index), ...}

 adj[1] = [(2, 0)]
 adj[2] = [(1, 0), (3, 1)]
 adj[3] = [(2, 1), (4, 2)]
 adj[4] = [(3, 2), (5, 3)]
 adj[5] = [(4, 3)]

 Now during DFS, you know WHICH edge you're traversing!

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌──────────────────────────┬────────────┬──────────────┐
 │ Operation                │ Time       │ Space        │
 ├──────────────────────────┼────────────┼──────────────┤
 │ Store edge list          │ O(N)       │ O(N)         │
 │ Access edge by index     │ O(1)       │ —            │
 │ Find neighbors of v      │ O(N) ❌    │ —            │
 │ Iterate all edges        │ O(N)       │ —            │
 └──────────────────────────┴────────────┴──────────────┘

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
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

template<class T>
void read(vec<T> &v) {
    for (auto &x : v) cin >> x;
}
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

struct Edge {
    int u, v;
    i64 w;
};

void solve() {
    int n;
    cin >> n;

    vec<Edge> edges(n - 1);
    // adj stores (neighbor, edge_index)
    vector<vector<pii>> adj(n + 1);

    for (int i = 0; i < n - 1; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        adj[edges[i].u].pb({edges[i].v, i});
        adj[edges[i].v].pb({edges[i].u, i});
    }

    // Print edge list
    cout << "Edge List:" << nl;
    for (int i = 0; i < n - 1; i++) {
        cout << "  edge[" << i << "] = (" << edges[i].u << ", "
             << edges[i].v << ", w=" << edges[i].w << ")" << nl;
    }

    // DFS that tracks which edges are used
    cout << nl << "DFS traversal with edge tracking:" << nl;
    vec<bool> vis(n + 1, false);
    // DFS from root 1
    function<void(int, int)> dfs = [&](int v, int par) {
        vis[v] = true;
        for (auto [u, eidx] : adj[v]) {
            if (u == par) continue;
            cout << "  Traverse edge[" << eidx << "]: "
                 << v << " → " << u << " (weight=" << edges[eidx].w << ")" << nl;
            dfs(u, v);
        }
    };
    dfs(1, -1);

    // Sort edges by weight (useful for Kruskal's-style algorithms)
    vec<int> order(n - 1);
    iota(all(order), 0);
    sort(all(order), [&](int a, int b) {
        return edges[a].w < edges[b].w;
    });

    cout << nl << "Edges sorted by weight:" << nl;
    for (int i : order) {
        cout << "  (" << edges[i].u << ", " << edges[i].v
             << ", w=" << edges[i].w << ")" << nl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    int TC = 1;
    cin >> TC;
    while (TC--) solve();

    return 0;
}

/*
═══════════════════════════════════════════════════════════════════
 SAMPLE INPUT / OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
1
5
1 2 5
2 3 3
3 4 7
4 5 2

Output:
Edge List:
  edge[0] = (1, 2, w=5)
  edge[1] = (2, 3, w=3)
  edge[2] = (3, 4, w=7)
  edge[3] = (4, 5, w=2)

DFS traversal with edge tracking:
  Traverse edge[0]: 1 → 2 (weight=5)
  Traverse edge[1]: 2 → 3 (weight=3)
  Traverse edge[2]: 3 → 4 (weight=7)
  Traverse edge[3]: 4 → 5 (weight=2)

Edges sorted by weight:
  (4, 5, w=2)
  (2, 3, w=3)
  (1, 2, w=5)
  (3, 4, w=7)
═══════════════════════════════════════════════════════════════════
*/

