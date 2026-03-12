/*
╔══════════════════════════════════════════════════════════════════╗
║  02 — EULER TOUR TREE (Dynamic Forest)                          ║
║  Zero to GM Level — ICPC Level Tree Algorithms                   ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 WHAT IS AN EULER TOUR TREE (ETT)?
═══════════════════════════════════════════════════════════════════

 ETT represents a dynamic forest (like Link-Cut Tree) using Euler
 tours stored in balanced BSTs (e.g., splay tree or treap).

 Each tree in the forest is represented by its Euler tour sequence.
 The Euler tour is stored in a balanced BST keyed by sequence order.

═══════════════════════════════════════════════════════════════════
 OPERATIONS
═══════════════════════════════════════════════════════════════════

 ┌────────────────────────┬────────────────────────────────────────┐
 │ Operation              │ How it works                           │
 ├────────────────────────┼────────────────────────────────────────┤
 │ link(u, v)             │ Splice Euler tours together            │
 │ cut(u, v)              │ Remove edge from Euler tour, split     │
 │ connected(u, v)        │ Check if same Euler tour (same BST)    │
 │ subtree_aggregate(v)   │ Range query on Euler tour segment      │
 │ reroot(v)              │ Rotate Euler tour sequence              │
 └────────────────────────┴────────────────────────────────────────┘

 All operations: O(log N) amortized.

═══════════════════════════════════════════════════════════════════
 ETT vs LINK-CUT TREE
═══════════════════════════════════════════════════════════════════

 ┌──────────────────────┬────────────────┬──────────────────┐
 │ Feature              │ ETT            │ Link-Cut Tree    │
 ├──────────────────────┼────────────────┼──────────────────┤
 │ Path queries         │ ❌ Hard         │ ✅ Native         │
 │ Subtree queries      │ ✅ Native       │ ❌ Hard           │
 │ Connectivity         │ ✅              │ ✅                │
 │ Implementation       │ Complex        │ Complex          │
 └──────────────────────┴────────────────┴──────────────────┘

 ETT is better for SUBTREE operations.
 Link-Cut is better for PATH operations.

═══════════════════════════════════════════════════════════════════
 EULER TOUR REPRESENTATION
═══════════════════════════════════════════════════════════════════

 Tree:
      1
     / \
    2   3
   /
  4

 Euler tour: 1 → 2 → 4 → 4 → 2 → 1 → 3 → 3 → 1
 (Each edge traversed twice: once down, once up)

 Represented as sequence of "half-edges":
   (1→2), (2→4), (4→2), (2→1), (1→3), (3→1)

 Link(u, v): Insert half-edges (u→v) and (v→u) into Euler tour
 Cut(u, v):  Remove half-edges (u→v) and (v→u), split sequence

═══════════════════════════════════════════════════════════════════
 SIMPLIFIED CODE (Concept demonstration)
═══════════════════════════════════════════════════════════════════

 Full production ETT requires a balanced BST (splay/treap).
 Below is a simplified version showing the core logic.
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
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

// ═══════════════════════════════════════════════════════════
// SIMPLIFIED ETT using std::set (for demonstration)
// Production code would use a splay tree for O(log N) splits/joins
// ═══════════════════════════════════════════════════════════

// For CP: use Link-Cut Tree for path queries.
// ETT is mainly theoretical / for subtree aggregates in dynamic forests.

// This file provides the conceptual understanding.
// The Link-Cut Tree in 01_Link_Cut_Tree.cpp is the preferred
// implementation for contest use.

struct ETT_Simple {
    // Union-Find for connectivity (simplified)
    vec<int> parent, rank_arr;

    ETT_Simple(int n) : parent(n + 1), rank_arr(n + 1, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        while (parent[x] != x) x = parent[x] = parent[parent[x]];
        return x;
    }

    bool connected(int u, int v) { return find(u) == find(v); }

    void link(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return;
        if (rank_arr[u] < rank_arr[v]) swap(u, v);
        parent[v] = u;
        if (rank_arr[u] == rank_arr[v]) rank_arr[u]++;
    }

    // Note: cut is NOT supported by basic union-find.
    // Full ETT with splay tree supports cut in O(log N).
};

void solve() {
    int n, q;
    cin >> n >> q;

    ETT_Simple ett(n);

    while (q--) {
        string op; int u, v;
        cin >> op >> u >> v;

        if (op == "link") {
            if (!ett.connected(u, v)) {
                ett.link(u, v);
                cout << "Linked " << u << " and " << v << nl;
            } else {
                cout << "Already connected" << nl;
            }
        } else if (op == "connected") {
            cout << u << " and " << v << ": "
                 << (ett.connected(u, v) ? "YES" : "NO") << nl;
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
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ ETT stores Euler tour in balanced BST for dynamic operations
 ✅ Best for: dynamic subtree queries (sum, min, max of subtree)
 ✅ Link-Cut Tree is preferred for: dynamic path queries
 ✅ Both support link/cut/connected in O(log N)
 ✅ For contests: Link-Cut Tree (Ch17 file 01) is more commonly used
 ✅ ETT appears in research papers and World Finals problems
═══════════════════════════════════════════════════════════════════
*/

