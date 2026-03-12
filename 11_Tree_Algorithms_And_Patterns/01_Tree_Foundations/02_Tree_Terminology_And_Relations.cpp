/*
╔══════════════════════════════════════════════════════════════════╗
║    02 — TREE TERMINOLOGY & RELATIONSHIPS (Complete Guide)       ║
║    Zero to GM Level — Tree Foundations                           ║
╚══════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS
─────────────────
 1. All Tree Terms with Visuals
 2. Depth vs Height
 3. Degree of a Node
 4. Parent / Child / Sibling / Ancestor / Descendant
 5. Subtree Concept
 6. Edge vs Node Count
 7. Dry Run: Calculate all properties for a tree
 8. Code: Compute all properties

═══════════════════════════════════════════════════════════════════
 MASTER DIAGRAM — Learn all terms from ONE tree
═══════════════════════════════════════════════════════════════════

   Consider this tree (rooted at node 1):

                    1          ← ROOT (no parent)
                  / | \
                 2  3  4       ← Children of 1
                / \    |
               5   6   7      ← Children of 2 and 4
              /   / \
             8   9  10        ← Children of 5 and 6

   NODES: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}  →  N = 10
   EDGES: 9 (= N-1)

═══════════════════════════════════════════════════════════════════
 1. TERMINOLOGY TABLE
═══════════════════════════════════════════════════════════════════

 ┌──────────────┬─────────────────────────────────────────────────┐
 │ Term         │ Definition & Example                            │
 ├──────────────┼─────────────────────────────────────────────────┤
 │ ROOT         │ Top node with no parent. Node 1.                │
 │ LEAF         │ Node with no children. Nodes: 3, 7, 8, 9, 10.  │
 │ INTERNAL     │ Node that is NOT a leaf. Nodes: 1, 2, 4, 5, 6. │
 │ PARENT       │ Direct ancestor. Parent of 5 is 2.              │
 │ CHILD        │ Direct descendant. Children of 2 are {5, 6}.    │
 │ SIBLING      │ Same parent. 5 and 6 are siblings (parent = 2). │
 │ ANCESTOR     │ Any node on path to root.                       │
 │              │ Ancestors of 8: {5, 2, 1}                       │
 │ DESCENDANT   │ Any node in subtree below.                      │
 │              │ Descendants of 2: {5, 6, 8, 9, 10}              │
 │ SUBTREE      │ A node + all its descendants.                   │
 │              │ Subtree(2) = {2, 5, 6, 8, 9, 10}                │
 │ EDGE         │ Connection between parent-child pair.            │
 │ DEGREE       │ Number of children. Degree(1) = 3, Degree(3) = 0│
 │ DEPTH        │ # edges from root to node. Depth(8) = 3.        │
 │ HEIGHT       │ # edges from node to deepest leaf below.         │
 │              │ Height(2) = 3, Height(leaf) = 0.                 │
 │ LEVEL        │ All nodes at same depth. Level 0 = {1},          │
 │              │ Level 1 = {2,3,4}, Level 2 = {5,6,7}             │
 └──────────────┴─────────────────────────────────────────────────┘

═══════════════════════════════════════════════════════════════════
 2. DEPTH vs HEIGHT — Most confused terms!
═══════════════════════════════════════════════════════════════════

 DEPTH of a node = # of edges from ROOT to that node
 (Depth goes DOWN from root)

                    1    depth=0
                  / | \
                 2  3  4  depth=1
                / \    |
               5   6   7  depth=2
              /   / \
             8   9  10    depth=3

 HEIGHT of a node = # of edges from that node to its deepest leaf
 (Height goes DOWN to leaves)

                    1    height=3  (1→2→5→8 = 3 edges)
                  / | \
                 2  3  4  height(2)=2, height(3)=0, height(4)=1
                / \    |
               5   6   7  height(5)=1, height(6)=1, height(7)=0
              /   / \
             8   9  10    height=0 (all leaves)

 HEIGHT OF TREE = Height of root = 3 (maximum depth of any node)

 ⚠️ IMPORTANT: Depth counts from TOP, Height counts from BOTTOM

═══════════════════════════════════════════════════════════════════
 3. DEGREE OF A NODE
═══════════════════════════════════════════════════════════════════

 Degree = Number of CHILDREN (not counting parent edge)

                    1    degree=3 (children: 2,3,4)
                  / | \
                 2  3  4  degree(2)=2, degree(3)=0, degree(4)=1
                / \    |
               5   6   7  degree(5)=1, degree(6)=2, degree(7)=0
              /   / \
             8   9  10    degree=0 (leaves)

 Max degree in this tree = 3 (node 1)

 Note: In some definitions, degree includes parent edge too.
 In CP, we usually mean "number of children" for rooted trees
 and "number of adjacent edges" for unrooted trees.

═══════════════════════════════════════════════════════════════════
 4. SUBTREE CONCEPT
═══════════════════════════════════════════════════════════════════

 Subtree rooted at node X = X + all descendants of X

 Subtree(1) — the entire tree:
                    1
                  / | \
                 2  3  4
                / \    |
               5   6   7
              /   / \
             8   9  10
 Size = 10

 Subtree(2):
                 2
                / \
               5   6
              /   / \
             8   9  10
 Size = 6

 Subtree(6):
               6
              / \
             9  10
 Size = 3

 Subtree(8):     (just the node itself — it's a leaf)
             8
 Size = 1

 ⚠️ FORMULA: SubtreeSize(v) = 1 + Σ SubtreeSize(child)
             for each child of v

═══════════════════════════════════════════════════════════════════
 5. DRY RUN: COMPUTE ALL PROPERTIES
═══════════════════════════════════════════════════════════════════

 Tree:
              1
            /   \
           2     3
          / \   / \
         4   5 6   7

 N = 7, Edges = 6

 ┌──────┬────────┬───────┬────────┬──────────┬───────────────┐
 │ Node │ Parent │ Depth │ Height │ Degree   │ Subtree Size  │
 ├──────┼────────┼───────┼────────┼──────────┼───────────────┤
 │  1   │  none  │   0   │   2    │   2      │      7        │
 │  2   │   1    │   1   │   1    │   2      │      3        │
 │  3   │   1    │   1   │   1    │   2      │      3        │
 │  4   │   2    │   2   │   0    │   0      │      1        │
 │  5   │   2    │   2   │   0    │   0      │      1        │
 │  6   │   3    │   2   │   0    │   0      │      1        │
 │  7   │   3    │   2   │   0    │   0      │      1        │
 └──────┴────────┴───────┴────────┴──────────┴───────────────┘

 Leaves: {4, 5, 6, 7} (degree = 0)
 Internal nodes: {1, 2, 3}
 Height of tree: 2

 DFS dry run to compute depth and subtree size:
   DFS(1, depth=0):
     depth[1] = 0, sub[1] starts at 1
     → DFS(2, depth=1):
         depth[2] = 1, sub[2] starts at 1
         → DFS(4, depth=2): depth[4]=2, sub[4]=1, return
         → DFS(5, depth=2): depth[5]=2, sub[5]=1, return
         sub[2] = 1 + sub[4] + sub[5] = 1+1+1 = 3, return
     → DFS(3, depth=1):
         depth[3] = 1, sub[3] starts at 1
         → DFS(6, depth=2): depth[6]=2, sub[6]=1, return
         → DFS(7, depth=2): depth[7]=2, sub[7]=1, return
         sub[3] = 1 + sub[6] + sub[7] = 1+1+1 = 3, return
     sub[1] = 1 + sub[2] + sub[3] = 1+3+3 = 7

═══════════════════════════════════════════════════════════════════
 6. COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌────────────────────────────┬────────────────┬─────────────────┐
 │ Operation                  │ Time           │ Space           │
 ├────────────────────────────┼────────────────┼─────────────────┤
 │ Compute all depths         │ O(N)           │ O(N)            │
 │ Compute all heights        │ O(N)           │ O(N)            │
 │ Compute all subtree sizes  │ O(N)           │ O(N)            │
 │ Find all leaves            │ O(N)           │ O(N)            │
 │ Find parent array          │ O(N)           │ O(N)            │
 └────────────────────────────┴────────────────┴─────────────────┘

═══════════════════════════════════════════════════════════════════
 7. CODE
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

// ─────────────────────────────────────────────────────────────
// Global arrays to store all tree properties
// ─────────────────────────────────────────────────────────────
const int MAXN = 200005;
vvec<int> adj;
vec<int> par;       // parent of each node (-1 for root)
vec<int> depth_arr; // depth of each node
vec<int> height_arr;// height of each node
vec<int> sub_size;  // subtree size of each node
vec<int> degree_arr;// number of children

// ─────────────────────────────────────────────────────────────
// DFS to compute depth, parent, subtree size, degree
// ─────────────────────────────────────────────────────────────
void dfs(int v, int p, int d) {
    par[v] = p;
    depth_arr[v] = d;
    sub_size[v] = 1;
    degree_arr[v] = 0;
    height_arr[v] = 0;

    for (int u : adj[v]) {
        if (u == p) continue;  // don't go back to parent
        degree_arr[v]++;       // u is a child
        dfs(u, v, d + 1);
        sub_size[v] += sub_size[u];
        height_arr[v] = max(height_arr[v], 1 + height_arr[u]);
    }
}

void solve() {
    int n;
    cin >> n;

    adj.assign(n + 1, {});
    par.assign(n + 1, -1);
    depth_arr.assign(n + 1, 0);
    height_arr.assign(n + 1, 0);
    sub_size.assign(n + 1, 0);
    degree_arr.assign(n + 1, 0);

    // Read tree edges (N-1 edges)
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    // Root the tree at node 1
    int root = 1;
    dfs(root, -1, 0);

    // Print all properties
    cout << "Tree Properties (rooted at " << root << "):" << nl;
    cout << "Height of tree = " << height_arr[root] << nl;
    cout << nl;

    cout << "┌──────┬────────┬───────┬────────┬────────┬──────────────┐" << nl;
    cout << "│ Node │ Parent │ Depth │ Height │ Degree │ Subtree Size │" << nl;
    cout << "├──────┼────────┼───────┼────────┼────────┼──────────────┤" << nl;

    for (int i = 1; i <= n; i++) {
        cout << "│  " << i << "   │  ";
        if (par[i] == -1) cout << "root ";
        else cout << " " << par[i] << "   ";
        cout << "│   " << depth_arr[i] << "   │   " << height_arr[i]
             << "    │   " << degree_arr[i] << "    │      " << sub_size[i] << "       │" << nl;
    }
    cout << "└──────┴────────┴───────┴────────┴────────┴──────────────┘" << nl;

    // Find and print leaves
    cout << nl << "Leaves: ";
    for (int i = 1; i <= n; i++) {
        if (degree_arr[i] == 0) cout << i << " ";
    }
    cout << nl;

    // Find and print internal nodes
    cout << "Internal nodes: ";
    for (int i = 1; i <= n; i++) {
        if (degree_arr[i] > 0) cout << i << " ";
    }
    cout << nl;
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
7
1 2
1 3
2 4
2 5
3 6
3 7

Output:
Tree Properties (rooted at 1):
Height of tree = 2

┌──────┬────────┬───────┬────────┬────────┬──────────────┐
│ Node │ Parent │ Depth │ Height │ Degree │ Subtree Size │
├──────┼────────┼───────┼────────┼────────┼──────────────┤
│  1   │  root  │   0   │   2    │   2    │      7       │
│  2   │   1    │   1   │   1    │   2    │      3       │
│  3   │   1    │   1   │   1    │   2    │      3       │
│  4   │   2    │   2   │   0    │   0    │      1       │
│  5   │   2    │   2   │   0    │   0    │      1       │
│  6   │   3    │   2   │   0    │   0    │      1       │
│  7   │   3    │   2   │   0    │   0    │      1       │
└──────┴────────┴───────┴────────┴────────┴──────────────┘

Leaves: 4 5 6 7
Internal nodes: 1 2 3

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Depth = from root DOWN to node (root has depth 0)
 ✅ Height = from node DOWN to deepest leaf (leaf has height 0)
 ✅ Degree = number of children
 ✅ Subtree size computed bottom-up: sub[v] = 1 + Σ sub[child]
 ✅ All properties computable in ONE DFS pass → O(N)
═══════════════════════════════════════════════════════════════════
*/

