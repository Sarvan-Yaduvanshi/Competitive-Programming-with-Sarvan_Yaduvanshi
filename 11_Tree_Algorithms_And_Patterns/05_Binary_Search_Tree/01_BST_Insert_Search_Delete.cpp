/*
╔══════════════════════════════════════════════════════════════════╗
║  01 — BST INSERT, SEARCH & DELETE                               ║
║  Zero to GM Level — Binary Search Tree                           ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 BST PROPERTY
═══════════════════════════════════════════════════════════════════

 For every node v:
   ALL values in LEFT subtree < v.val
   ALL values in RIGHT subtree > v.val

 Example BST:
          8
        /   \
       3     10
      / \      \
     1   6     14
        / \   /
       4   7 13

 Inorder: 1 3 4 6 7 8 10 13 14 → SORTED! ✅

═══════════════════════════════════════════════════════════════════
 SEARCH IN BST — DRY RUN
═══════════════════════════════════════════════════════════════════

 Search for 6 in the BST above:
   At 8: 6 < 8 → go LEFT
   At 3: 6 > 3 → go RIGHT
   At 6: FOUND! ✅

 Search for 5:
   At 8: 5 < 8 → go LEFT
   At 3: 5 > 3 → go RIGHT
   At 6: 5 < 6 → go LEFT
   At 4: 5 > 4 → go RIGHT
   null → NOT FOUND ❌

 Time: O(H) where H = height

═══════════════════════════════════════════════════════════════════
 INSERT IN BST — DRY RUN
═══════════════════════════════════════════════════════════════════

 Insert 5 into the BST:
   At 8: 5 < 8 → go LEFT
   At 3: 5 > 3 → go RIGHT
   At 6: 5 < 6 → go LEFT
   At 4: 5 > 4 → go RIGHT → null
   Create node 5 as right child of 4!

 Result:
          8
        /   \
       3     10
      / \      \
     1   6     14
        / \   /
       4   7 13
        \
         5  ← NEW

═══════════════════════════════════════════════════════════════════
 DELETE IN BST — DRY RUN (3 CASES)
═══════════════════════════════════════════════════════════════════

 CASE 1: Node is a LEAF → just remove it
   Delete 7:
          8              8
        /   \          /   \
       3     10  →    3     10
      / \      \     / \      \
     1   6     14   1   6     14
        / \   /        /     /
       4   7 13       4     13

 CASE 2: Node has ONE child → replace with child
   Delete 10:
          8              8
        /   \          /   \
       3     10  →    3     14
      / \      \     / \   /
     1   6     14   1   6 13
        / \   /        / \
       4   7 13       4   7

 CASE 3: Node has TWO children → replace with inorder successor
   Delete 3 (has children 1 and 6):
   Inorder successor of 3 = smallest in right subtree = 4
   Replace 3's value with 4, then delete 4 from right subtree.

          8              8
        /   \          /   \
       3     10  →    4     10
      / \      \     / \      \
     1   6     14   1   6     14
        / \   /          \   /
       4   7 13           7 13

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌────────────────┬───────────┬────────────┬──────────────┐
 │ Operation      │ Average   │ Worst      │ Space        │
 ├────────────────┼───────────┼────────────┼──────────────┤
 │ Search         │ O(log N)  │ O(N)       │ O(H)         │
 │ Insert         │ O(log N)  │ O(N)       │ O(H)         │
 │ Delete         │ O(log N)  │ O(N)       │ O(H)         │
 └────────────────┴───────────┴────────────┴──────────────┘

 Worst case O(N) happens when tree is DEGENERATE (sorted insert)

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

// BST Node pool (array-based to avoid dynamic allocation)
struct BSTNode {
    int val, left, right; // -1 means null
};

vec<BSTNode> pool;
int poolSize;

int newBSTNode(int v) {
    pool.pb({v, -1, -1});
    return poolSize++;
}

// ═══════════════════════════════════════════════════════════
// SEARCH
// ═══════════════════════════════════════════════════════════
bool bstSearch(int root, int key) {
    if (root == -1) return false;
    if (pool[root].val == key) return true;
    if (key < pool[root].val) return bstSearch(pool[root].left, key);
    return bstSearch(pool[root].right, key);
}

// ═══════════════════════════════════════════════════════════
// INSERT
// ═══════════════════════════════════════════════════════════
int bstInsert(int root, int key) {
    if (root == -1) return newBSTNode(key);
    if (key < pool[root].val)
        pool[root].left = bstInsert(pool[root].left, key);
    else if (key > pool[root].val)
        pool[root].right = bstInsert(pool[root].right, key);
    // duplicate: do nothing
    return root;
}

// Find minimum value node in BST
int findMin(int root) {
    while (pool[root].left != -1)
        root = pool[root].left;
    return root;
}

// ═══════════════════════════════════════════════════════════
// DELETE
// ═══════════════════════════════════════════════════════════
int bstDelete(int root, int key) {
    if (root == -1) return -1;

    if (key < pool[root].val) {
        pool[root].left = bstDelete(pool[root].left, key);
    } else if (key > pool[root].val) {
        pool[root].right = bstDelete(pool[root].right, key);
    } else {
        // Found the node to delete
        // Case 1 & 2: 0 or 1 child
        if (pool[root].left == -1) return pool[root].right;
        if (pool[root].right == -1) return pool[root].left;

        // Case 3: 2 children → replace with inorder successor
        int successor = findMin(pool[root].right);
        pool[root].val = pool[successor].val;
        pool[root].right = bstDelete(pool[root].right, pool[successor].val);
    }
    return root;
}

// Inorder print
void inorderPrint(int root) {
    if (root == -1) return;
    inorderPrint(pool[root].left);
    cout << pool[root].val << " ";
    inorderPrint(pool[root].right);
}

void solve() {
    pool.clear();
    poolSize = 0;

    int q;
    cin >> q;

    int root = -1;
    while (q--) {
        char op;
        int x;
        cin >> op >> x;

        if (op == 'I') {  // Insert
            root = bstInsert(root, x);
            cout << "Insert " << x << " → Inorder: ";
            inorderPrint(root); cout << nl;
        } else if (op == 'S') {  // Search
            cout << "Search " << x << ": "
                 << (bstSearch(root, x) ? "FOUND" : "NOT FOUND") << nl;
        } else if (op == 'D') {  // Delete
            root = bstDelete(root, x);
            cout << "Delete " << x << " → Inorder: ";
            inorderPrint(root); cout << nl;
        }
    }
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
10
I 8
I 3
I 10
I 1
I 6
I 14
I 4
I 7
S 6
D 3

Output:
Insert 8 → Inorder: 8
Insert 3 → Inorder: 3 8
Insert 10 → Inorder: 3 8 10
Insert 1 → Inorder: 1 3 8 10
Insert 6 → Inorder: 1 3 6 8 10
Insert 14 → Inorder: 1 3 6 8 10 14
Insert 4 → Inorder: 1 3 4 6 8 10 14
Insert 7 → Inorder: 1 3 4 6 7 8 10 14
Search 6: FOUND
Delete 3 → Inorder: 1 4 6 7 8 10 14

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ BST property: left < root < right
 ✅ Inorder traversal of BST = sorted order
 ✅ Search/Insert: follow left/right based on comparison
 ✅ Delete 3 cases: leaf, one child, two children (inorder successor)
 ✅ All ops O(H), balanced H=O(log N), worst H=O(N)
 ✅ In CP: use std::set/map instead (self-balancing BST)
═══════════════════════════════════════════════════════════════════
*/

