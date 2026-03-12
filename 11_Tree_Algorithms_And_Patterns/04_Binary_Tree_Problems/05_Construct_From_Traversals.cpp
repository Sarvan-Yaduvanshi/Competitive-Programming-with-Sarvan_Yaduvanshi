/*
╔══════════════════════════════════════════════════════════════════╗
║  05 — CONSTRUCT TREE FROM TRAVERSALS                            ║
║  Zero to GM Level — Binary Tree Problems                         ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 BUILD FROM PREORDER + INORDER — DRY RUN
═══════════════════════════════════════════════════════════════════

 KEY INSIGHT:
   Preorder: first element = ROOT
   Inorder:  everything LEFT of root = left subtree
             everything RIGHT of root = right subtree

 Preorder: [1, 2, 4, 5, 3, 6, 7]
 Inorder:  [4, 2, 5, 1, 6, 3, 7]

 Step 1: root = preorder[0] = 1
         Find 1 in inorder at index 3
         Left inorder: [4, 2, 5] (size=3)
         Right inorder: [6, 3, 7] (size=3)
         Left preorder: [2, 4, 5] (next 3 elements)
         Right preorder: [3, 6, 7] (remaining)

                 1
               /   \
          [4,2,5] [6,3,7]

 Step 2 (left subtree):
   root = 2, find in inorder [4,2,5] at index 1
   Left: [4], Right: [5]

                 1
               /   \
              2   [6,3,7]
             / \
            4   5

 Step 3 (right subtree):
   root = 3, find in inorder [6,3,7] at index 1
   Left: [6], Right: [7]

                 1
               /   \
              2     3
             / \   / \
            4   5 6   7  ✅

═══════════════════════════════════════════════════════════════════
 BUILD FROM INORDER + POSTORDER — DRY RUN
═══════════════════════════════════════════════════════════════════

 KEY INSIGHT:
   Postorder: LAST element = ROOT
   Then same inorder splitting technique.

 Inorder:   [4, 2, 5, 1, 6, 3, 7]
 Postorder: [4, 5, 2, 6, 7, 3, 1]

 Step 1: root = postorder[last] = 1
         Find 1 in inorder at index 3
         (same splitting as above)

 Build RIGHT subtree FIRST (because postorder = L R N,
 so working from end: N R L)

═══════════════════════════════════════════════════════════════════
 UNIQUENESS CONDITIONS
═══════════════════════════════════════════════════════════════════

 ┌─────────────────────────────────┬────────────────────────────┐
 │ Given                           │ Unique tree?               │
 ├─────────────────────────────────┼────────────────────────────┤
 │ Preorder + Inorder              │ YES (if values distinct)   │
 │ Inorder + Postorder             │ YES (if values distinct)   │
 │ Preorder + Postorder            │ NO (not unique in general) │
 │ Preorder + Postorder (full BT)  │ YES (if full binary tree)  │
 └─────────────────────────────────┴────────────────────────────┘

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 With hashmap for inorder index lookup:
 ┌────────────────────────────┬────────────┬──────────────┐
 │ Method                     │ Time       │ Space        │
 ├────────────────────────────┼────────────┼──────────────┤
 │ Pre + In (with map)        │ O(N)       │ O(N)         │
 │ In + Post (with map)       │ O(N)       │ O(N)         │
 │ Without map (find each)    │ O(N²)      │ O(N)         │
 └────────────────────────────┴────────────┴──────────────┘

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
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

// Using struct for clear tree building
struct Node {
    int val;
    int left, right; // index in nodes array, -1 for null
};

vec<Node> nodes;
int nodeCount;

int newNode(int v) {
    nodes.pb({v, -1, -1});
    return nodeCount++;
}

// ═══════════════════════════════════════════════════════════
// BUILD FROM PREORDER + INORDER
// ═══════════════════════════════════════════════════════════
map<int, int> inorderIndex; // value → index in inorder
int preIdx;

int buildPreIn(vec<int>& preorder, vec<int>& inorder, int inL, int inR) {
    if (inL > inR) return -1;

    int rootVal = preorder[preIdx++];
    int root = newNode(rootVal);

    int mid = inorderIndex[rootVal]; // position of root in inorder

    // Build left subtree (elements before mid in inorder)
    nodes[root].left = buildPreIn(preorder, inorder, inL, mid - 1);
    // Build right subtree (elements after mid in inorder)
    nodes[root].right = buildPreIn(preorder, inorder, mid + 1, inR);

    return root;
}

// ═══════════════════════════════════════════════════════════
// BUILD FROM INORDER + POSTORDER
// ═══════════════════════════════════════════════════════════
int postIdx;

int buildInPost(vec<int>& inorder, vec<int>& postorder, int inL, int inR) {
    if (inL > inR) return -1;

    int rootVal = postorder[postIdx--]; // take from END
    int root = newNode(rootVal);

    int mid = inorderIndex[rootVal];

    // Build RIGHT first (postorder = L R N, going backwards = N R L)
    nodes[root].right = buildInPost(inorder, postorder, mid + 1, inR);
    nodes[root].left = buildInPost(inorder, postorder, inL, mid - 1);

    return root;
}

// Print tree traversals for verification
void printInorder(int v) {
    if (v == -1) return;
    printInorder(nodes[v].left);
    cout << nodes[v].val << " ";
    printInorder(nodes[v].right);
}

void printPreorder(int v) {
    if (v == -1) return;
    cout << nodes[v].val << " ";
    printPreorder(nodes[v].left);
    printPreorder(nodes[v].right);
}

void printPostorder(int v) {
    if (v == -1) return;
    printPostorder(nodes[v].left);
    printPostorder(nodes[v].right);
    cout << nodes[v].val << " ";
}

// Print tree structure (indented)
void printTree(int v, string prefix, bool isLeft) {
    if (v == -1) return;
    cout << prefix << (isLeft ? "├── " : "└── ") << nodes[v].val << nl;
    printTree(nodes[v].left, prefix + (isLeft ? "│   " : "    "), true);
    printTree(nodes[v].right, prefix + (isLeft ? "│   " : "    "), false);
}

void solve() {
    int n;
    cin >> n;

    vec<int> preorder(n), inorder(n), postorder(n);

    // Read preorder and inorder
    for (int i = 0; i < n; i++) cin >> preorder[i];
    for (int i = 0; i < n; i++) cin >> inorder[i];
    for (int i = 0; i < n; i++) cin >> postorder[i];

    // Build index map for inorder
    inorderIndex.clear();
    for (int i = 0; i < n; i++) inorderIndex[inorder[i]] = i;

    // Method 1: Build from preorder + inorder
    nodes.clear(); nodeCount = 0;
    preIdx = 0;
    int root1 = buildPreIn(preorder, inorder, 0, n - 1);

    cout << "=== Built from Preorder + Inorder ===" << nl;
    printTree(root1, "", false);
    cout << "Verify preorder:  "; printPreorder(root1); cout << nl;
    cout << "Verify inorder:   "; printInorder(root1); cout << nl;
    cout << "Verify postorder: "; printPostorder(root1); cout << nl;

    // Method 2: Build from inorder + postorder
    nodes.clear(); nodeCount = 0;
    postIdx = n - 1;
    int root2 = buildInPost(inorder, postorder, 0, n - 1);

    cout << nl << "=== Built from Inorder + Postorder ===" << nl;
    printTree(root2, "", false);
    cout << "Verify preorder:  "; printPreorder(root2); cout << nl;
    cout << "Verify inorder:   "; printInorder(root2); cout << nl;
    cout << "Verify postorder: "; printPostorder(root2); cout << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    return 0;
}

/*
═══════════════════════════════════════════════════════════════════
 SAMPLE I/O
═══════════════════════════════════════════════════════════════════

Input:
1
7
1 2 4 5 3 6 7
4 2 5 1 6 3 7
4 5 2 6 7 3 1

Output:
=== Built from Preorder + Inorder ===
└── 1
    ├── 2
    │   ├── 4
    │   └── 5
    └── 3
        ├── 6
        └── 7
Verify preorder:  1 2 4 5 3 6 7
Verify inorder:   4 2 5 1 6 3 7
Verify postorder: 4 5 2 6 7 3 1

=== Built from Inorder + Postorder ===
└── 1
    ├── 2
    │   ├── 4
    │   └── 5
    └── 3
        ├── 6
        └── 7
Verify preorder:  1 2 4 5 3 6 7
Verify inorder:   4 2 5 1 6 3 7
Verify postorder: 4 5 2 6 7 3 1

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Preorder first element = root → split inorder → recurse
 ✅ Postorder last element = root → split inorder → recurse RIGHT first
 ✅ HashMap for O(1) lookup of root position in inorder → O(N) total
 ✅ Preorder+Inorder OR Inorder+Postorder → unique tree
 ✅ Preorder+Postorder → NOT unique (except for full binary trees)
═══════════════════════════════════════════════════════════════════
*/

