/*
╔══════════════════════════════════════════════════════════════════╗
║          04 — ROOTING A TREE (Unrooted → Rooted)                ║
║          Zero to GM Level — Tree Foundations                     ║
╚══════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS
─────────────────
 1. Unrooted vs Rooted Trees
 2. How to Root a Tree
 3. Visual Dry Run: Rooting at Different Nodes
 4. Building Parent Array via DFS
 5. Complexity Analysis
 6. Code

═══════════════════════════════════════════════════════════════════
 1. UNROOTED vs ROOTED TREES
═══════════════════════════════════════════════════════════════════

 UNROOTED: Just edges, no hierarchy. No "up" or "down."

   1 — 2 — 3
   |       |
   4       5

 ROOTED: One node designated as root → creates hierarchy.
 Parent-child relationships are defined by "who is closer to root."

═══════════════════════════════════════════════════════════════════
 2. HOW TO ROOT A TREE
═══════════════════════════════════════════════════════════════════

 Given an unrooted tree (edge list) and a chosen root R:
   1. Build adjacency list
   2. Run DFS/BFS from R
   3. For each node v visited from node u:
      - u is the parent of v
      - v is a child of u

 This creates the parent[] array and establishes the hierarchy.

═══════════════════════════════════════════════════════════════════
 3. VISUAL DRY RUN: Rooting at Different Nodes
═══════════════════════════════════════════════════════════════════

 Given unrooted tree with edges:
   (1,2), (2,3), (3,4), (3,5), (1,6)

 As undirected graph:
       6 — 1 — 2 — 3 — 4
                    |
                    5

 CASE A: Root at node 1
 ─────────────────────
   DFS from 1:
     Visit 1 (root, parent=-1)
       → Visit 6 (parent=1)
       → Visit 2 (parent=1)
         → Visit 3 (parent=2)
           → Visit 4 (parent=3)
           → Visit 5 (parent=3)

   Result:
           1
          / \
         6   2
             |
             3
            / \
           4   5

   parent[] = [-1, -1, 1, 2, 3, 3, 1]
   (index)     0    1  2  3  4  5  6

 CASE B: Root at node 3
 ─────────────────────
   DFS from 3:
     Visit 3 (root, parent=-1)
       → Visit 2 (parent=3)
         → Visit 1 (parent=2)
           → Visit 6 (parent=1)
       → Visit 4 (parent=3)
       → Visit 5 (parent=3)

   Result:
           3
         / | \
        2  4  5
        |
        1
        |
        6

   parent[] = [-1, 2, 3, -1, 3, 3, 1]

 🔑 SAME tree structure, DIFFERENT hierarchy!
    The choice of root CHANGES parent-child relationships.

═══════════════════════════════════════════════════════════════════
 4. DRY RUN: Building Parent Array Step by Step
═══════════════════════════════════════════════════════════════════

 Tree: edges = {(1,2),(1,3),(2,4),(2,5),(3,6)}, Root = 1

 Adjacency list:
   1 → [2, 3]
   2 → [1, 4, 5]
   3 → [1, 6]
   4 → [2]
   5 → [2]
   6 → [3]

 DFS(node=1, parent=-1):
   parent[1] = -1
   Neighbors of 1: [2, 3]
     2 ≠ parent(-1), so DFS(2, 1)
       parent[2] = 1
       Neighbors of 2: [1, 4, 5]
         1 == parent(1), SKIP
         4 ≠ parent(1), so DFS(4, 2)
           parent[4] = 2
           Neighbors of 4: [2]
             2 == parent(2), SKIP
           return
         5 ≠ parent(1), so DFS(5, 2)
           parent[5] = 2
           Neighbors of 5: [2]
             2 == parent(2), SKIP
           return
       return
     3 ≠ parent(-1), so DFS(3, 1)
       parent[3] = 1
       Neighbors of 3: [1, 6]
         1 == parent(1), SKIP
         6 ≠ parent(1), so DFS(6, 3)
           parent[6] = 3
           Neighbors of 6: [3]
             3 == parent(3), SKIP
           return
       return

 Final parent array:
   parent[1]=-1, parent[2]=1, parent[3]=1,
   parent[4]=2,  parent[5]=2, parent[6]=3

 Rooted tree:
           1
          / \
         2   3
        / \   \
       4   5   6

═══════════════════════════════════════════════════════════════════
 5. COMPLEXITY ANALYSIS
═══════════════════════════════════════════════════════════════════

 ┌──────────────────────────┬────────────────┬─────────────────┐
 │ Operation                │ Time           │ Space           │
 ├──────────────────────────┼────────────────┼─────────────────┤
 │ Build adjacency list     │ O(N)           │ O(N)            │
 │ DFS to root the tree     │ O(N)           │ O(N) stack      │
 │ Build parent array       │ O(N)           │ O(N)            │
 │ Total                    │ O(N)           │ O(N)            │
 └──────────────────────────┴────────────────┴─────────────────┘

═══════════════════════════════════════════════════════════════════
 6. CODE
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

vvec<int> adj;
vec<int> par;
vec<int> dep;
vvec<int> children; // children[v] = list of children of v

// DFS to root the tree
void rootTree(int v, int p, int d) {
    par[v] = p;
    dep[v] = d;
    for (int u : adj[v]) {
        if (u == p) continue;
        children[v].pb(u);
        rootTree(u, v, d + 1);
    }
}

void solve() {
    int n, root;
    cin >> n >> root;

    adj.assign(n + 1, {});
    par.assign(n + 1, -1);
    dep.assign(n + 1, 0);
    children.assign(n + 1, {});

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    rootTree(root, -1, 0);

    cout << "Tree rooted at node " << root << ":" << nl;
    cout << nl;

    // Print parent array
    cout << "Parent array:" << nl;
    for (int i = 1; i <= n; i++) {
        cout << "  parent[" << i << "] = ";
        if (par[i] == -1) cout << "none (root)";
        else cout << par[i];
        cout << nl;
    }

    cout << nl;

    // Print children
    cout << "Children:" << nl;
    for (int i = 1; i <= n; i++) {
        cout << "  children[" << i << "] = {";
        for (int j = 0; j < sz(children[i]); j++) {
            if (j > 0) cout << ", ";
            cout << children[i][j];
        }
        cout << "}" << nl;
    }

    cout << nl;

    // Print depth
    cout << "Depth:" << nl;
    for (int i = 1; i <= n; i++) {
        cout << "  depth[" << i << "] = " << dep[i] << nl;
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
6 1
1 2
1 3
2 4
2 5
3 6

Output:
Tree rooted at node 1:

Parent array:
  parent[1] = none (root)
  parent[2] = 1
  parent[3] = 1
  parent[4] = 2
  parent[5] = 2
  parent[6] = 3

Children:
  children[1] = {2, 3}
  children[2] = {4, 5}
  children[3] = {6}
  children[4] = {}
  children[5] = {}
  children[6] = {}

Depth:
  depth[1] = 0
  depth[2] = 1
  depth[3] = 1
  depth[4] = 2
  depth[5] = 2
  depth[6] = 2

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ To root a tree: DFS/BFS from chosen root
 ✅ Parent of root = -1 (or 0 for 1-indexed)
 ✅ When visiting neighbor u from v: if u ≠ parent(v), then u is child
 ✅ Same unrooted tree → different structure with different roots
 ✅ All done in O(N) time and space
═══════════════════════════════════════════════════════════════════
*/

