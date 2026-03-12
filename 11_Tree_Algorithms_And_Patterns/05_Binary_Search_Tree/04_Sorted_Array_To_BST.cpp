/*
╔══════════════════════════════════════════════════════════════════╗
║  04 — SORTED ARRAY TO BALANCED BST                              ║
║  Zero to GM Level — Binary Search Tree                           ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 CONCEPT — DRY RUN
═══════════════════════════════════════════════════════════════════

 Given sorted array, build a HEIGHT-BALANCED BST.
 Key: pick MIDDLE element as root → recurse on left/right halves.

 Array: [1, 3, 5, 7, 9, 11, 13]

 Step 1: mid=3 → root=7
         Left: [1,3,5], Right: [9,11,13]
 Step 2: Left mid=1 → node=3
         Left: [1], Right: [5]
         Right mid=5 → node=11
         Left: [9], Right: [13]

 Result:
           7
         /   \
        3     11
       / \   /  \
      1   5 9   13   ← Perfect BST!

 Height = ⌊log₂(7)⌋ = 2 ✅

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

// Build balanced BST from sorted array
int sortedArrayToBST(vec<int>& arr, int lo, int hi) {
    if (lo > hi) return -1;
    int mid = lo + (hi - lo) / 2;
    int root = newNode(arr[mid]);
    nodes[root].left = sortedArrayToBST(arr, lo, mid - 1);
    nodes[root].right = sortedArrayToBST(arr, mid + 1, hi);
    return root;
}

void printTree(int v, string prefix, bool isLeft) {
    if (v == -1) return;
    cout << prefix << (isLeft ? "├── " : "└── ") << nodes[v].val << nl;
    printTree(nodes[v].left, prefix + (isLeft ? "│   " : "    "), true);
    printTree(nodes[v].right, prefix + (isLeft ? "│   " : "    "), false);
}

void inorder(int v) {
    if (v == -1) return;
    inorder(nodes[v].left);
    cout << nodes[v].val << " ";
    inorder(nodes[v].right);
}

int height(int v) {
    if (v == -1) return 0;
    return 1 + max(height(nodes[v].left), height(nodes[v].right));
}

void solve() {
    int n;
    cin >> n;
    vec<int> arr(n);
    for (auto& x : arr) cin >> x;

    nodes.clear(); cnt = 0;
    int root = sortedArrayToBST(arr, 0, n - 1);

    cout << "Balanced BST from sorted array:" << nl;
    printTree(root, "", false);
    cout << "Inorder: "; inorder(root); cout << nl;
    cout << "Height: " << height(root) << nl;
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
 SAMPLE I/O — Input: 1  7  1 3 5 7 9 11 13
═══════════════════════════════════════════════════════════════════
Output:
Balanced BST from sorted array:
└── 7
    ├── 3
    │   ├── 1
    │   └── 5
    └── 11
        ├── 9
        └── 13
Inorder: 1 3 5 7 9 11 13
Height: 3

 Time: O(N) | Space: O(N) + O(log N) recursion stack
═══════════════════════════════════════════════════════════════════
*/

