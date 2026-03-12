/*
╔══════════════════════════════════════════════════════════════════╗
║  02 — CARTESIAN TREE                                            ║
║  Zero to GM Level — Special Trees                                ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 WHAT IS A CARTESIAN TREE?
═══════════════════════════════════════════════════════════════════

 A Cartesian tree of an array A[] is a binary tree where:
   1. HEAP property: parent ≤ children (min-heap) or parent ≥ children
   2. BST property on INDICES: inorder traversal gives original array

 In other words: root = index of minimum element,
                 left subtree = Cartesian tree of elements to the left,
                 right subtree = Cartesian tree of elements to the right.

═══════════════════════════════════════════════════════════════════
 DRY RUN
═══════════════════════════════════════════════════════════════════

 Array: [3, 2, 6, 1, 9]
 Index:  0  1  2  3  4

 Step 1: Minimum = 1 at index 3 → root
         Left:  [3, 2, 6] (indices 0-2)
         Right: [9] (index 4)

 Step 2 (left): Minimum of [3,2,6] = 2 at index 1
         Left:  [3] (index 0)
         Right: [6] (index 2)

 Result:
            1 (idx=3)
           / \
       2(1)   9(4)
       / \
    3(0)  6(2)

 Inorder: 3, 2, 6, 1, 9 = original array ✅
 Min-heap: 1 < 2, 1 < 9, 2 < 3, 2 < 6 ✅

═══════════════════════════════════════════════════════════════════
 O(N) CONSTRUCTION USING STACK
═══════════════════════════════════════════════════════════════════

 Process elements left to right. Maintain a stack of "right spine"
 of the tree built so far.

 For each new element:
   Pop all elements from stack that are GREATER than current
   The last popped becomes left child of current
   Current becomes right child of top of stack (if any)

═══════════════════════════════════════════════════════════════════
 APPLICATIONS
═══════════════════════════════════════════════════════════════════

 ✅ RMQ (Range Minimum Query) ↔ LCA on Cartesian tree
 ✅ Treap = Tree + Heap = randomized Cartesian tree
 ✅ Max rectangle in histogram
 ✅ Efficiently building segment-tree-like structures

═══════════════════════════════════════════════════════════════════
 CODE — O(N) Cartesian Tree Construction
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

struct CartesianNode {
    int val, left, right, parent;
};

// Build Cartesian tree in O(N) using stack
// Returns root index
int buildCartesian(vec<int>& arr, vec<CartesianNode>& tree) {
    int n = sz(arr);
    tree.resize(n);
    for (int i = 0; i < n; i++) {
        tree[i] = {arr[i], -1, -1, -1};
    }

    stack<int> stk; // indices on right spine

    for (int i = 0; i < n; i++) {
        int last = -1;

        // Pop all elements greater than current (min-heap)
        while (!stk.empty() && tree[stk.top()].val > arr[i]) {
            last = stk.top();
            stk.pop();
        }

        // Last popped becomes left child of current
        if (last != -1) {
            tree[i].left = last;
            tree[last].parent = i;
        }

        // Current becomes right child of stack top
        if (!stk.empty()) {
            tree[stk.top()].right = i;
            tree[i].parent = stk.top();
        }

        stk.push(i);
    }

    // Root is the bottom of the stack
    while (stk.size() > 1) stk.pop();
    return stk.top();
}

// Verify: inorder should give original array
void inorder(int v, vec<CartesianNode>& tree, vec<int>& result) {
    if (v == -1) return;
    inorder(tree[v].left, tree, result);
    result.pb(tree[v].val);
    inorder(tree[v].right, tree, result);
}

void printTree(int v, vec<CartesianNode>& tree, string prefix, bool isLeft) {
    if (v == -1) return;
    cout << prefix << (isLeft ? "├── " : "└── ") << tree[v].val
         << " (idx=" << v << ")" << nl;
    printTree(tree[v].left, tree, prefix + (isLeft ? "│   " : "    "), true);
    printTree(tree[v].right, tree, prefix + (isLeft ? "│   " : "    "), false);
}

void solve() {
    int n; cin >> n;
    vec<int> arr(n);
    for (auto& x : arr) cin >> x;

    vec<CartesianNode> tree;
    int root = buildCartesian(arr, tree);

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << nl << nl;

    cout << "Cartesian Tree (root=" << tree[root].val << "):" << nl;
    printTree(root, tree, "", false);

    // Verify inorder = original
    vec<int> inorderResult;
    inorder(root, tree, inorderResult);
    cout << nl << "Inorder: ";
    for (int x : inorderResult) cout << x << " ";
    cout << nl;

    bool correct = (inorderResult == arr);
    cout << "Inorder matches original: " << (correct ? "YES ✅" : "NO ❌") << nl;
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
5
3 2 6 1 9

Output:
Array: 3 2 6 1 9

Cartesian Tree (root=1):
└── 1 (idx=3)
    ├── 2 (idx=1)
    │   ├── 3 (idx=0)
    │   └── 6 (idx=2)
    └── 9 (idx=4)

Inorder: 3 2 6 1 9
Inorder matches original: YES ✅

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Cartesian tree: heap property + BST on indices
 ✅ Root = minimum element; inorder = original array
 ✅ O(N) construction using monotonic stack
 ✅ RMQ(l,r) = LCA(l,r) in Cartesian tree!
 ✅ Treap is a randomized Cartesian tree (random priorities)
═══════════════════════════════════════════════════════════════════
*/

