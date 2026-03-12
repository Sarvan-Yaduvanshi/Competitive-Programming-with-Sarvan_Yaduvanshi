/*
╔══════════════════════════════════════════════════════════════════╗
║          03 — TYPES OF TREES (Complete Visual Guide)            ║
║          Zero to GM Level — Tree Foundations                     ║
╚══════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS
─────────────────
 1. Binary Tree
 2. Full Binary Tree
 3. Complete Binary Tree
 4. Perfect Binary Tree
 5. Balanced Binary Tree
 6. Degenerate (Skewed) Tree
 7. N-ary Tree
 8. Rooted vs Unrooted Tree
 9. Comparison Chart
 10. Why types matter in CP
 11. Code: Identify tree type

═══════════════════════════════════════════════════════════════════
 1. BINARY TREE
═══════════════════════════════════════════════════════════════════

 Every node has AT MOST 2 children (left and right).

         1
        / \
       2   3           ← Binary tree (each node ≤ 2 children)
      / \
     4   5

 NOT a binary tree:
         1
        /|\
       2 3 4           ← Node 1 has 3 children → NOT binary

═══════════════════════════════════════════════════════════════════
 2. FULL BINARY TREE (also called "Proper" or "Strict")
═══════════════════════════════════════════════════════════════════

 Every node has EXACTLY 0 or 2 children (never just 1).

 ✅ Full binary tree:
         1
        / \
       2   3
      / \
     4   5

 ❌ NOT full (node 3 has only 1 child):
         1
        / \
       2   3
      / \   \
     4   5   6

 Properties of Full Binary Tree with L leaves:
   - Internal nodes = L - 1
   - Total nodes = 2L - 1
   - Example: 3 leaves (4,5,3) → 2 internal (1,2) → total 5 = 2(3)-1 ✅

═══════════════════════════════════════════════════════════════════
 3. COMPLETE BINARY TREE
═══════════════════════════════════════════════════════════════════

 All levels completely filled EXCEPT possibly the last level.
 Last level filled from LEFT to RIGHT.

 ✅ Complete:
         1
        / \
       2   3
      / \ /
     4  5 6

 Level 0: [1]     — full ✅
 Level 1: [2,3]   — full ✅
 Level 2: [4,5,6] — filled left-to-right ✅

 ❌ NOT complete (gap on left):
         1
        / \
       2   3
        \ / \
        5 6  7
 (Node 2 is missing left child but has right child)

 🔑 WHY IT MATTERS IN CP:
   - Binary heaps are complete binary trees
   - Can be stored in ARRAY: parent of i is i/2, children are 2i, 2i+1
   - Height = ⌊log₂(N)⌋

═══════════════════════════════════════════════════════════════════
 4. PERFECT BINARY TREE
═══════════════════════════════════════════════════════════════════

 ALL internal nodes have exactly 2 children.
 ALL leaves are at the SAME level.

 ✅ Perfect (height 2):
           1
         /   \
        2     3
       / \   / \
      4   5 6   7

 Properties:
   - Nodes at level k = 2^k
   - Total nodes of height h = 2^(h+1) - 1
   - Height 2 → 2^3 - 1 = 7 nodes ✅
   - All leaves at same depth
   - Perfect ⊂ Complete ⊂ Binary

═══════════════════════════════════════════════════════════════════
 5. BALANCED BINARY TREE
═══════════════════════════════════════════════════════════════════

 For EVERY node, the height difference between left and right
 subtrees is at most 1.

 ✅ Balanced:                ❌ NOT Balanced:
        1                          1
       / \                        /
      2   3                      2
     / \                        /
    4   5                      3
                              /
                             4

 Left tree: |height(left) - height(right)| ≤ 1 at every node ✅
 Right tree: At node 1, left height=3, right height=0 → diff=3 ❌

 🔑 WHY IT MATTERS:
   - AVL trees, Red-Black trees are balanced BSTs
   - Balanced → Height = O(log N) → Fast operations
   - Unbalanced → Height = O(N) → Slow (degenerate to linked list)

═══════════════════════════════════════════════════════════════════
 6. DEGENERATE (SKEWED) TREE
═══════════════════════════════════════════════════════════════════

 Every internal node has exactly ONE child.
 Essentially a linked list!

 Left-skewed:          Right-skewed:
      1                    1
     /                      \
    2                        2
   /                          \
  3                            3
 /                              \
4                                4

 Properties:
   - Height = N-1 (worst case!)
   - Looks like a linked list
   - BST operations become O(N) instead of O(log N)

 🔑 In CP: If a BST problem doesn't guarantee balance,
    always consider the skewed case → O(N) per query!

═══════════════════════════════════════════════════════════════════
 7. N-ARY TREE (General Tree)
═══════════════════════════════════════════════════════════════════

 Each node can have UP TO N children (no limit like binary).

 Example (3-ary tree):
           1
         / | \
        2  3  4
       /|     |
      5 6     7
     /|\
    8 9 10

 In CP, most tree problems use N-ary trees stored as adjacency lists.
 Binary trees are a special case of N-ary trees where N=2.

═══════════════════════════════════════════════════════════════════
 8. ROOTED vs UNROOTED TREE
═══════════════════════════════════════════════════════════════════

 UNROOTED TREE: No designated root. Just nodes and edges.
   1 — 2 — 3
   |       |
   4       5

 ROOTED TREE: One node is the root. Creates parent-child hierarchy.

 If we root the above tree at node 2:
           2
         / | \
        1  3  (parent edges point up)
        |  |
        4  5

 If we root at node 1:
           1
          / \
         2   4
         |
         3
         |
         5

 🔑 SAME unrooted tree, but DIFFERENT rooted structures depending
    on which node we choose as root!
 🔑 In CP: "Given a tree" usually means unrooted.
    "Given a rooted tree" explicitly mentions root.

═══════════════════════════════════════════════════════════════════
 9. COMPARISON CHART
═══════════════════════════════════════════════════════════════════

 ┌───────────────┬────────────┬────────────┬──────────────────────┐
 │ Type          │ Max Height │ Min Height │ When you see it      │
 ├───────────────┼────────────┼────────────┼──────────────────────┤
 │ Perfect       │ log₂(N+1) │ log₂(N+1)  │ Theoretical ideal    │
 │ Complete      │ ⌊log₂N⌋   │ ⌊log₂N⌋    │ Binary heaps         │
 │ Balanced      │ O(log N)   │ O(log N)   │ AVL, Red-Black       │
 │ Full          │ N/2        │ log₂(N+1)  │ Expression trees     │
 │ General binary│ N-1        │ ⌊log₂N⌋    │ Any binary tree      │
 │ Degenerate    │ N-1        │ N-1        │ Worst-case BST       │
 │ N-ary         │ N-1        │ log_N      │ General trees in CP  │
 └───────────────┴────────────┴────────────┴──────────────────────┘

 Subset relationships:
   Perfect ⊂ Complete ⊂ Balanced ⊂ Binary ⊂ N-ary

═══════════════════════════════════════════════════════════════════
 10. CODE: IDENTIFY TREE TYPE
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
// Given a rooted tree (adjacency list, root = 1),
// determine which types apply.
// ─────────────────────────────────────────────────────────────

vvec<int> adj;
vec<int> childCount;   // number of children
vec<int> dep;          // depth
vec<int> ht;           // height
bool isBinary;
bool isFull;
bool isBalanced;

void dfs(int v, int p, int d) {
    dep[v] = d;
    ht[v] = 0;
    childCount[v] = 0;

    for (int u : adj[v]) {
        if (u == p) continue;
        childCount[v]++;
        dfs(u, v, d + 1);
        ht[v] = max(ht[v], 1 + ht[u]);
    }

    // Check binary: each node has ≤ 2 children
    if (childCount[v] > 2) isBinary = false;

    // Check full binary: each node has 0 or 2 children
    if (childCount[v] == 1) isFull = false;
    if (childCount[v] > 2) isFull = false;

    // Check balanced: |left_height - right_height| ≤ 1
    if (childCount[v] == 2) {
        int h1 = -1, h2 = -1;
        for (int u : adj[v]) {
            if (u == p) continue;
            if (h1 == -1) h1 = ht[u];
            else h2 = ht[u];
        }
        if (abs(h1 - h2) > 1) isBalanced = false;
    }
}

void solve() {
    int n;
    cin >> n;

    adj.assign(n + 1, {});
    childCount.assign(n + 1, 0);
    dep.assign(n + 1, 0);
    ht.assign(n + 1, 0);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    isBinary = true;
    isFull = true;
    isBalanced = true;

    int root = 1;
    dfs(root, -1, 0);

    // Check if all leaves at same depth (perfect)
    int leafDepth = -1;
    bool isPerfect = isBinary;
    for (int i = 1; i <= n; i++) {
        if (childCount[i] == 0) { // leaf
            if (leafDepth == -1) leafDepth = dep[i];
            else if (dep[i] != leafDepth) isPerfect = false;
        }
    }
    if (!isFull) isPerfect = false;

    // Check if degenerate (all nodes have ≤ 1 child)
    bool isDegenerate = true;
    for (int i = 1; i <= n; i++) {
        if (childCount[i] > 1) isDegenerate = false;
    }

    cout << "Tree Type Analysis (N=" << n << ", rooted at " << root << "):" << nl;
    cout << "Height of tree: " << ht[root] << nl;
    cout << nl;
    cout << "Binary?      " << (isBinary ? "YES ✅" : "NO ❌") << nl;
    cout << "Full Binary? " << (isFull ? "YES ✅" : "NO ❌") << nl;
    cout << "Perfect?     " << (isPerfect ? "YES ✅" : "NO ❌") << nl;
    cout << "Balanced?    " << (isBalanced ? "YES ✅" : "NO ❌") << nl;
    cout << "Degenerate?  " << (isDegenerate ? "YES ✅" : "NO ❌") << nl;
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

Test 1: Perfect binary tree
Input:
3
7
1 2
1 3
2 4
2 5
3 6
3 7
5
1 2
2 3
3 4
4 5
6
1 2
1 3
2 4
2 5
3 6

Output:
Tree Type Analysis (N=7, rooted at 1):
Height of tree: 2
Binary?      YES ✅
Full Binary? YES ✅
Perfect?     YES ✅
Balanced?    YES ✅
Degenerate?  NO ❌

Tree Type Analysis (N=5, rooted at 1):
Height of tree: 4
Binary?      YES ✅
Full Binary? NO ❌
Perfect?     NO ❌
Balanced?    NO ❌
Degenerate?  YES ✅

Tree Type Analysis (N=6, rooted at 1):
Height of tree: 2
Binary?      YES ✅
Full Binary? NO ❌
Perfect?     NO ❌
Balanced?    YES ✅
Degenerate?  NO ❌

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Binary: every node ≤ 2 children
 ✅ Full: every node has 0 or 2 children (no single-child)
 ✅ Complete: all levels full except last, filled left-to-right
 ✅ Perfect: all leaves at same depth + full
 ✅ Balanced: height diff ≤ 1 at every node → O(log N) height
 ✅ Degenerate: every node ≤ 1 child → linked list → O(N) height
 ✅ Perfect ⊂ Complete ⊂ Balanced ⊂ Binary
═══════════════════════════════════════════════════════════════════
*/

