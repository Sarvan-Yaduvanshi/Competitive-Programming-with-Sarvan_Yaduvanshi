/*
╔══════════════════════════════════════════════════════════════════╗
║  01 — HLD: CONCEPT & DECOMPOSITION                             ║
║  Zero to GM Level — Heavy-Light Decomposition                    ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 WHAT IS HLD?
═══════════════════════════════════════════════════════════════════

 HLD decomposes a tree into "heavy chains" so that:
   - Any root-to-leaf path crosses at most O(log N) chains
   - Each chain is a contiguous range in an array → use SegTree!

═══════════════════════════════════════════════════════════════════
 HEAVY vs LIGHT EDGES
═══════════════════════════════════════════════════════════════════

 For each node v with children, the HEAVY CHILD is the child
 with the LARGEST subtree size. All other children are LIGHT.

 Tree:
              1 (sub=9)
            /   \
     (sub=5)2   3(sub=3)
          / \     \
   (sub=3)4 5(1) 6(sub=2)
        / \       |
    (1)7  8(1)   9(1)

 Heavy children (largest subtree):
   1 → heavy child = 2 (sub=5 > sub=3)
   2 → heavy child = 4 (sub=3 > sub=1)
   3 → heavy child = 6 (sub=2)
   4 → heavy child = 7 or 8 (tie, pick either, say 7)

 Heavy edges (→) and light edges (⟶):
   1 → 2 → 4 → 7   (one heavy chain!)
   1 ⟶ 3 → 6 → 9   (another chain starting at 3)
   2 ⟶ 5             (chain of just 5)
   4 ⟶ 8             (chain of just 8)

═══════════════════════════════════════════════════════════════════
 CHAINS VISUALIZATION
═══════════════════════════════════════════════════════════════════

 Chain 1 (head=1): 1 → 2 → 4 → 7    (heavy path from root)
 Chain 2 (head=3): 3 → 6 → 9
 Chain 3 (head=5): 5
 Chain 4 (head=8): 8

 Position array (DFS order following heavy child first):
   pos: 1→0, 2→1, 4→2, 7→3, 8→4, 5→5, 3→6, 6→7, 9→8

   Index: 0  1  2  3  4  5  6  7  8
   Node:  1  2  4  7  8  5  3  6  9
          ├────────────┤  │  ├────────┤
            Chain 1     Ch3   Chain 2
                           Ch4

 Each chain = contiguous segment in this array!

═══════════════════════════════════════════════════════════════════
 KEY PROPERTY: O(log N) chain crossings
═══════════════════════════════════════════════════════════════════

 From any node to root, you cross at most O(log N) light edges.
 Why? Each light edge means subtree size at least halves.
 So max O(log N) light edges → O(log N) chains.

═══════════════════════════════════════════════════════════════════
 HOW TO BUILD HLD
═══════════════════════════════════════════════════════════════════

 Step 1: Compute subtree sizes
 Step 2: DFS again — always visit heavy child FIRST
          Assign position numbers in this order
          Set head[v] = head of the chain containing v
          Heavy child gets same head as parent
          Light children start new chains (head = themselves)

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌──────────────────────────────┬────────────────┬──────────────┐
 │ Operation                    │ Time           │ Space        │
 ├──────────────────────────────┼────────────────┼──────────────┤
 │ Build HLD                    │ O(N)           │ O(N)         │
 │ Path query (with SegTree)    │ O(log²N)       │ —            │
 │ Subtree query                │ O(log N)       │ —            │
 └──────────────────────────────┴────────────────┴──────────────┘

═══════════════════════════════════════════════════════════════════
 CODE — HLD BUILD
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

vvec<int> adj;
int par[MAXN], depth[MAXN], sub[MAXN];
int head[MAXN]; // head of the chain containing v
int pos[MAXN];  // position of v in the HLD array
int heavy[MAXN]; // heavy child of v (-1 if leaf)
int cur_pos;

// DFS 1: compute subtree sizes and heavy children
void dfs_size(int v, int p, int d) {
    par[v] = p;
    depth[v] = d;
    sub[v] = 1;
    heavy[v] = -1;
    int maxChildSub = 0;

    for (int u : adj[v]) {
        if (u == p) continue;
        dfs_size(u, v, d + 1);
        sub[v] += sub[u];
        if (sub[u] > maxChildSub) {
            maxChildSub = sub[u];
            heavy[v] = u;
        }
    }
}

// DFS 2: assign positions (heavy child first → contiguous chains)
void dfs_hld(int v, int h) {
    head[v] = h;
    pos[v] = cur_pos++;

    // Visit heavy child FIRST (stays in same chain)
    if (heavy[v] != -1) {
        dfs_hld(heavy[v], h); // same chain head
    }

    // Then visit light children (start new chains)
    for (int u : adj[v]) {
        if (u == par[v] || u == heavy[v]) continue;
        dfs_hld(u, u); // new chain, head = u itself
    }
}

void solve() {
    int n; cin >> n;
    adj.assign(n + 1, {});
    cur_pos = 0;

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    dfs_size(1, 0, 0);
    dfs_hld(1, 1);

    cout << "HLD Decomposition:" << nl;
    cout << "Node | pos | head | heavy_child | sub_size" << nl;
    cout << "─────┼─────┼──────┼─────────────┼─────────" << nl;
    for (int i = 1; i <= n; i++) {
        cout << "  " << i << "  |  " << pos[i] << "  |  " << head[i]
             << "   |     " << (heavy[i] == -1 ? 0 : heavy[i])
             << "       |    " << sub[i] << nl;
    }

    // Show chains
    cout << nl << "Chains:" << nl;
    map<int, vec<int>> chains;
    for (int i = 1; i <= n; i++) chains[head[i]].pb(i);
    for (auto& [h, nodes] : chains) {
        sort(nodes.begin(), nodes.end(), [](int a, int b) {
            return ::pos[a] < ::pos[b];
        });
        cout << "  Head " << h << ": ";
        for (int v : nodes) cout << v << " ";
        cout << nl;
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
9
1 2
1 3
2 4
2 5
3 6
4 7
4 8
6 9

Output shows the HLD decomposition with chains.

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Heavy child = largest subtree → stays in same chain
 ✅ Visit heavy child first in DFS → chain = contiguous positions
 ✅ Each chain stored as range in segment tree
 ✅ Any path crosses O(log N) chains → O(log²N) path queries
 ✅ Next file: actual path queries with segment tree
═══════════════════════════════════════════════════════════════════
*/

