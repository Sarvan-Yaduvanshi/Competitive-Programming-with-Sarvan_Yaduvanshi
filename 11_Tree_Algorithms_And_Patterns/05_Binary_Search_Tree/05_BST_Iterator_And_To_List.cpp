/*
╔══════════════════════════════════════════════════════════════════╗
║  05 — BST ITERATOR & BST TO SORTED LIST                        ║
║  Zero to GM Level — Binary Search Tree                           ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 1. BST ITERATOR (LeetCode 173)
═══════════════════════════════════════════════════════════════════

 next() returns the next smallest element in BST.
 hasNext() returns whether there's a next element.

 Key idea: use a stack to simulate inorder traversal iteratively.
 Push all left children first, pop gives next smallest.

═══════════════════════════════════════════════════════════════════
 DRY RUN — BST Iterator
═══════════════════════════════════════════════════════════════════

 BST:
       7
      / \
     3   15
        / \
       9   20

 Inorder: 3, 7, 9, 15, 20

 Init: push all left from root → stack = [7, 3]

 next(): pop 3, no right child → return 3. Stack = [7]
 next(): pop 7, push all left from 15 → stack = [15, 9]
         return 7
 next(): pop 9, no right child → return 9. Stack = [15]
 next(): pop 15, push all left from 20 → stack = [20]
         return 15
 next(): pop 20 → return 20. Stack = []
 hasNext(): stack empty → false

═══════════════════════════════════════════════════════════════════
 2. BST TO SORTED DOUBLY LINKED LIST (LeetCode 426)
═══════════════════════════════════════════════════════════════════

 Convert BST to sorted circular doubly linked list IN-PLACE.
 Inorder traversal, maintain prev pointer.

 BST:       4            Sorted List:
           / \       →   1 ↔ 2 ↔ 3 ↔ 4 ↔ 5
          2   5              ↕_________↕
         / \                (circular)
        1   3

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 BST Iterator: O(1) amortized per next(), O(H) space
 BST to Sorted List: O(N) time, O(H) stack space

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

vec<int> val, L, R;

// ═══════════════════════════════════════════════════════════
// BST ITERATOR — Stack-based inorder traversal
// ═══════════════════════════════════════════════════════════
struct BSTIterator {
    stack<int> stk;

    BSTIterator(int root) {
        pushAllLeft(root);
    }

    void pushAllLeft(int v) {
        while (v != 0) {
            stk.push(v);
            v = L[v];
        }
    }

    bool hasNext() {
        return !stk.empty();
    }

    int next() {
        int node = stk.top();
        stk.pop();
        if (R[node] != 0) pushAllLeft(R[node]);
        return val[node];
    }
};

// ═══════════════════════════════════════════════════════════
// BST TO SORTED LIST — Inorder with prev pointer
// ═══════════════════════════════════════════════════════════
vec<int> sortedOrder;

void inorder(int v) {
    if (v == 0) return;
    inorder(L[v]);
    sortedOrder.pb(val[v]);
    inorder(R[v]);
}

void solve() {
    int n; cin >> n;
    val.assign(n + 1, 0);
    L.assign(n + 1, 0);
    R.assign(n + 1, 0);

    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 1; i <= n; i++) cin >> L[i] >> R[i];

    // BST Iterator demo
    cout << "BST Iterator output: ";
    BSTIterator it(1);
    while (it.hasNext()) {
        cout << it.next();
        if (it.hasNext()) cout << " → ";
    }
    cout << nl;

    // BST to sorted list
    sortedOrder.clear();
    inorder(1);
    cout << "Sorted list: ";
    for (int i = 0; i < sz(sortedOrder); i++) {
        if (i) cout << " ↔ ";
        cout << sortedOrder[i];
    }
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
5
7 3 15 9 20
2 3
0 0
4 5
0 0
0 0

BST:   7
      / \
     3   15
        / \
       9   20

Output:
BST Iterator output: 3 → 7 → 9 → 15 → 20
Sorted list: 3 ↔ 7 ↔ 9 ↔ 15 ↔ 20

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ BST Iterator: stack stores left spine, O(1) amortized next()
 ✅ Push all left → pop → push all left of right child → repeat
 ✅ BST to sorted list: inorder traversal gives sorted order
 ✅ In CP: use std::set with iterators instead (much simpler!)
═══════════════════════════════════════════════════════════════════
*/

