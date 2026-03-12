/*
╔══════════════════════════════════════════════════════════════════╗
║       02 — TREE TERMINOLOGY (Complete Reference)                ║
║       Zero to GM Level — Tree Foundations                        ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 ALL TERMINOLOGY WITH VISUALIZATION
═══════════════════════════════════════════════════════════════════

 ROOTED TREE (root = 1):

         1          ← ROOT (no parent)    depth=0, height=3
        / \
       2   3        ← INTERNAL nodes      depth=1
      / \   \
     4   5   6      ← 5,6 are LEAVES      depth=2
    /
   7                ← LEAF                 depth=3

 ┌───────────────────────────────────────────────────────────────┐
 │ Term              │ Definition              │ Example         │
 ├───────────────────┼─────────────────────────┼─────────────────┤
 │ ROOT              │ Topmost node            │ Node 1          │
 │ LEAF              │ Node with no children   │ 5, 6, 7         │
 │ INTERNAL NODE     │ Node with ≥1 child      │ 1, 2, 3, 4      │
 │ PARENT of v       │ Node directly above v   │ par(4)=2        │
 │ CHILD of v        │ Node directly below v   │ children(2)={4,5}│
 │ SIBLINGS          │ Same parent             │ 4 and 5         │
 │ ANCESTOR of v     │ v, parent, grandparent..│ ancestors(7)={7,4,2,1}│
 │ DESCENDANT of v   │ v and all below         │ desc(2)={2,4,5,7}│
 │ SUBTREE of v      │ v + all descendants     │ subtree(2) has 4 nodes│
 │ DEPTH of v        │ # edges from root to v  │ depth(7)=3      │
 │ HEIGHT of v       │ # edges to deepest leaf  │ height(2)=2     │
 │ HEIGHT of tree    │ Height of root          │ height(1)=3     │
 │ DEGREE of v       │ # children of v         │ degree(2)=2     │
 │ LEVEL             │ Set of nodes at same depth│ level 2={4,5,6}│
 │ EDGE              │ Connection between nodes │ (1,2), (2,4)... │
 │ PATH              │ Sequence of edges       │ 7→4→2→1→3→6    │
 │ DIAMETER          │ Longest path in tree    │ 7→4→2→1→3→6 = 5│
 └───────────────────┴─────────────────────────┴─────────────────┘

═══════════════════════════════════════════════════════════════════
 CODE — Compute all properties
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
vec<int> parent_arr, depth_arr, height_arr, degree_arr, subtree_size;

void dfs(int v, int par, int d) {
    parent_arr[v] = par;
    depth_arr[v] = d;
    subtree_size[v] = 1;
    degree_arr[v] = 0;
    int maxChildH = -1;

    for (int u : adj[v]) {
        if (u == par) continue;
        degree_arr[v]++;
        dfs(u, v, d + 1);
        subtree_size[v] += subtree_size[u];
        maxChildH = max(maxChildH, height_arr[u]);
    }
    height_arr[v] = maxChildH + 1;
}

void solve() {
    int n; cin >> n;
    adj.assign(n + 1, {});
    parent_arr.assign(n + 1, 0);
    depth_arr.assign(n + 1, 0);
    height_arr.assign(n + 1, 0);
    degree_arr.assign(n + 1, 0);
    subtree_size.assign(n + 1, 0);

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    dfs(1, 0, 0);

    int leaves = 0, internals = 0;
    for (int i = 1; i <= n; i++) {
        if (degree_arr[i] == 0) leaves++;
        else internals++;
    }

    cout << "Tree Properties (rooted at 1):" << nl;
    cout << "  Total nodes: " << n << ", Edges: " << n-1 << nl;
    cout << "  Leaves: " << leaves << ", Internal: " << internals << nl;
    cout << "  Tree height: " << height_arr[1] << nl;
    cout << nl;

    cout << "Node | Parent | Depth | Height | Degree | SubSize | Type" << nl;
    cout << "─────┼────────┼───────┼────────┼────────┼─────────┼─────" << nl;
    for (int i = 1; i <= n; i++) {
        string type = (i == 1) ? "ROOT" : (degree_arr[i] == 0 ? "LEAF" : "INTERNAL");
        cout << "  " << i << "  |   " << parent_arr[i] << "    |   "
             << depth_arr[i] << "   |   " << height_arr[i] << "    |   "
             << degree_arr[i] << "    |    " << subtree_size[i] << "    | " << type << nl;
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
 Input: 1\n7\n1 2\n1 3\n2 4\n2 5\n3 6\n4 7
 Output shows complete properties for every node.
*/

