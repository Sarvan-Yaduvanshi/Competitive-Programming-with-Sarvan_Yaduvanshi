/*
╔══════════════════════════════════════════════════════════════════╗
║  02 — BUILD BST FROM PREORDER & BUILD FROM LEVEL ORDER          ║
║  Zero to GM Level — Tree Construction                            ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 1. BUILD BST FROM PREORDER — DRY RUN
═══════════════════════════════════════════════════════════════════

 Given BST's preorder traversal, reconstruct the BST.

 Preorder: [8, 5, 1, 7, 10, 12]

 Key insight: In a BST, all values < root go LEFT, > root go RIGHT.
 Use a BOUND to determine when to stop building left subtree.

 Step-by-step:
   idx=0: root=8, bound=INF
     idx=1: 5 < 8 → left child. Build left(bound=8)
       idx=2: 1 < 5 → left child. Build left(bound=5)
         idx=3: 7 > 5 → stop (violates bound=5). Return null.
       return node(1)
       idx=3: 7 < 8 → right child. Build right(bound=8)
         idx=4: 10 > 8 → stop. Return null.
       return node(7)
     return node(5, left=1, right=7)
     idx=4: 10 < INF → right child. Build right(bound=INF)
       idx=5: 12 < INF → right child.
     return node(10, right=12)
   return node(8, left=5{1,7}, right=10{12})

 Result:
         8
        / \
       5   10
      / \    \
     1   7   12   ✅ Valid BST!

═══════════════════════════════════════════════════════════════════
 2. BUILD TREE FROM LEVEL ORDER — DRY RUN
═══════════════════════════════════════════════════════════════════

 Level order: [1, 2, 3, 4, 5, 6, 7]
 Using -1 for null children.

 Build using queue: process parent, assign left/right from next values.

 Result:
         1
        / \
       2   3
      / \ / \
     4  5 6  7

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
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

struct Node { int val, left, right; };
vec<Node> nodes;
int cnt;

int newNode(int v) { nodes.pb({v, -1, -1}); return cnt++; }

// ═══════════════════════════════════════════════════════════
// 1. BUILD BST FROM PREORDER — O(N) with bound
// ═══════════════════════════════════════════════════════════
int preIdx;

int bstFromPreorder(vec<int>& pre, int bound) {
    if (preIdx >= sz(pre) || pre[preIdx] > bound) return -1;

    int root = newNode(pre[preIdx++]);
    nodes[root].left = bstFromPreorder(pre, nodes[root].val);
    nodes[root].right = bstFromPreorder(pre, bound);
    return root;
}

// ═══════════════════════════════════════════════════════════
// 2. BUILD TREE FROM LEVEL ORDER
// ═══════════════════════════════════════════════════════════
int buildFromLevelOrder(vec<int>& level) {
    if (level.empty() || level[0] == -1) return -1;

    int root = newNode(level[0]);
    queue<int> q;
    q.push(root);
    int idx = 1;

    while (!q.empty() && idx < sz(level)) {
        int par = q.front(); q.pop();

        // Left child
        if (idx < sz(level) && level[idx] != -1) {
            nodes[par].left = newNode(level[idx]);
            q.push(nodes[par].left);
        }
        idx++;

        // Right child
        if (idx < sz(level) && level[idx] != -1) {
            nodes[par].right = newNode(level[idx]);
            q.push(nodes[par].right);
        }
        idx++;
    }
    return root;
}

void printInorder(int v) {
    if (v == -1) return;
    printInorder(nodes[v].left);
    cout << nodes[v].val << " ";
    printInorder(nodes[v].right);
}

void printTree(int v, string prefix, bool isLeft) {
    if (v == -1) return;
    cout << prefix << (isLeft ? "├── " : "└── ") << nodes[v].val << nl;
    printTree(nodes[v].left, prefix + (isLeft ? "│   " : "    "), true);
    printTree(nodes[v].right, prefix + (isLeft ? "│   " : "    "), false);
}

void solve() {
    // BST from preorder
    int n; cin >> n;
    vec<int> pre(n);
    for (auto& x : pre) cin >> x;

    nodes.clear(); cnt = 0; preIdx = 0;
    int root1 = bstFromPreorder(pre, INT_MAX);

    cout << "=== BST from Preorder ===" << nl;
    printTree(root1, "", false);
    cout << "Inorder (should be sorted): ";
    printInorder(root1);
    cout << nl;

    // Tree from level order
    int m; cin >> m;
    vec<int> level(m);
    for (auto& x : level) cin >> x;

    nodes.clear(); cnt = 0;
    int root2 = buildFromLevelOrder(level);

    cout << nl << "=== Tree from Level Order ===" << nl;
    printTree(root2, "", false);
    cout << "Inorder: ";
    printInorder(root2);
    cout << nl;
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
6
8 5 1 7 10 12
7
1 2 3 4 5 6 7

Output:
=== BST from Preorder ===
└── 8
    ├── 5
    │   ├── 1
    │   └── 7
    └── 10
        └── 12
Inorder (should be sorted): 1 5 7 8 10 12

=== Tree from Level Order ===
└── 1
    ├── 2
    │   ├── 4
    │   └── 5
    └── 3
        ├── 6
        └── 7
Inorder: 4 2 5 1 6 3 7

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ BST from preorder: use upper bound trick → O(N)
 ✅ Tree from level order: BFS with queue, assign children in order
 ✅ BST preorder: first element = root, split by value for L/R
 ✅ Both constructions are O(N) time
═══════════════════════════════════════════════════════════════════
*/

