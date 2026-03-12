/*
╔══════════════════════════════════════════════════════════════════╗
║       03 — PREORDER, INORDER, POSTORDER (Binary Tree)           ║
║       Zero to GM Level — Tree Traversals                         ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 THE BIG PICTURE — THREE TRAVERSAL ORDERS
═══════════════════════════════════════════════════════════════════

 For a BINARY TREE, there are 3 classic DFS traversals:

 PREORDER:  Node → Left → Right    (NLR)
 INORDER:   Left → Node → Right    (LNR)
 POSTORDER: Left → Right → Node    (LRN)

 Tree:
              1
            /   \
           2     3
          / \   / \
         4   5 6   7

 PREORDER:  1 2 4 5 3 6 7  (root first)
 INORDER:   4 2 5 1 6 3 7  (left, root, right)
 POSTORDER: 4 5 2 6 7 3 1  (root last)

═══════════════════════════════════════════════════════════════════
 PREORDER DRY RUN (Node → Left → Right)
═══════════════════════════════════════════════════════════════════

 Tree:
              1
            /   \
           2     3
          / \     \
         4   5     6

 preorder(1):
   PRINT 1
   preorder(2):                    ← go LEFT
     PRINT 2
     preorder(4):                  ← go LEFT
       PRINT 4
       preorder(null): return      ← no left
       preorder(null): return      ← no right
     preorder(5):                  ← go RIGHT
       PRINT 5
       preorder(null): return
       preorder(null): return
   preorder(3):                    ← go RIGHT
     PRINT 3
     preorder(null): return        ← no left
     preorder(6):                  ← go RIGHT
       PRINT 6
       preorder(null): return
       preorder(null): return

 OUTPUT: 1 2 4 5 3 6

═══════════════════════════════════════════════════════════════════
 INORDER DRY RUN (Left → Node → Right)
═══════════════════════════════════════════════════════════════════

 Same tree:
              1
            /   \
           2     3
          / \     \
         4   5     6

 inorder(1):
   inorder(2):                     ← go LEFT first
     inorder(4):                   ← go LEFT first
       inorder(null): return       ← no left
       PRINT 4                     ← print node
       inorder(null): return       ← no right
     PRINT 2                       ← print node
     inorder(5):                   ← go RIGHT
       inorder(null): return
       PRINT 5
       inorder(null): return
   PRINT 1                         ← print node (root)
   inorder(3):                     ← go RIGHT
     inorder(null): return         ← no left
     PRINT 3
     inorder(6):
       inorder(null): return
       PRINT 6
       inorder(null): return

 OUTPUT: 4 2 5 1 3 6

 🔑 For BST, inorder gives SORTED order!

═══════════════════════════════════════════════════════════════════
 POSTORDER DRY RUN (Left → Right → Node)
═══════════════════════════════════════════════════════════════════

 Same tree:
              1
            /   \
           2     3
          / \     \
         4   5     6

 postorder(1):
   postorder(2):                   ← LEFT first
     postorder(4):
       postorder(null): return
       postorder(null): return
       PRINT 4                     ← print after both children
     postorder(5):
       postorder(null): return
       postorder(null): return
       PRINT 5
     PRINT 2
   postorder(3):                   ← RIGHT
     postorder(null): return
     postorder(6):
       postorder(null): return
       postorder(null): return
       PRINT 6
     PRINT 3
   PRINT 1                         ← root is LAST

 OUTPUT: 4 5 2 6 3 1

═══════════════════════════════════════════════════════════════════
 ITERATIVE TRAVERSALS USING STACK
═══════════════════════════════════════════════════════════════════

 ITERATIVE PREORDER:
   Push root → while stack not empty:
     pop v, print v
     push RIGHT child first (so LEFT is processed first)
     push LEFT child

 ITERATIVE INORDER (using stack):
   cur = root
   while cur != null OR stack not empty:
     while cur != null:
       push cur, go left (cur = cur->left)
     pop cur, print cur
     go right (cur = cur->right)

 ITERATIVE POSTORDER (two-stack method):
   Push root to stack1
   while stack1 not empty:
     pop v, push to stack2
     push LEFT child to stack1
     push RIGHT child to stack1
   Print stack2 (reverse order)

═══════════════════════════════════════════════════════════════════
 ITERATIVE INORDER DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree:
         1
        / \
       2   3
      / \
     4   5

 Step-by-step:
 ┌──────┬──────────────────┬───────┬────────┐
 │ Step │ Stack            │ cur   │ Output │
 ├──────┼──────────────────┼───────┼────────┤
 │  1   │ []               │ 1     │        │
 │  2   │ [1]              │ 2     │ push 1, go left │
 │  3   │ [1, 2]           │ 4     │ push 2, go left │
 │  4   │ [1, 2, 4]        │ null  │ push 4, go left │
 │  5   │ [1, 2]           │ null  │ pop 4, print 4, go right │
 │  6   │ [1]              │ null  │ pop 2, print 2, go right to 5 │
 │  7   │ [1, 5]           │ null  │ push 5, go left (null) │
 │  8   │ [1]              │ null  │ pop 5, print 5, go right │
 │  9   │ []               │ null  │ pop 1, print 1, go right to 3 │
 │ 10   │ [3]              │ null  │ push 3, go left (null) │
 │ 11   │ []               │ null  │ pop 3, print 3, go right │
 └──────┴──────────────────┴───────┴────────┘

 Output: 4 2 5 1 3 ✅

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌──────────────────────────┬────────────┬──────────────┐
 │ Traversal                │ Time       │ Space        │
 ├──────────────────────────┼────────────┼──────────────┤
 │ Recursive (any order)    │ O(N)       │ O(H) stack   │
 │ Iterative preorder       │ O(N)       │ O(H) stack   │
 │ Iterative inorder        │ O(N)       │ O(H) stack   │
 │ Iterative postorder      │ O(N)       │ O(H) stack   │
 └──────────────────────────┴────────────┴──────────────┘

═══════════════════════════════════════════════════════════════════
 CODE (Using adjacency list for binary tree with left[]/right[])
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

// Binary tree using arrays (left[i], right[i])
// 0 means null/no child
vec<int> leftChild, rightChild, val;

// ═══════════════════════════════════════════════════════════════
// RECURSIVE TRAVERSALS
// ═══════════════════════════════════════════════════════════════
void preorder(int v, vec<int>& res) {
    if (v == 0) return;
    res.pb(v);                    // Node first
    preorder(leftChild[v], res);  // Left
    preorder(rightChild[v], res); // Right
}

void inorder(int v, vec<int>& res) {
    if (v == 0) return;
    inorder(leftChild[v], res);   // Left first
    res.pb(v);                    // Node
    inorder(rightChild[v], res);  // Right
}

void postorder(int v, vec<int>& res) {
    if (v == 0) return;
    postorder(leftChild[v], res); // Left first
    postorder(rightChild[v], res);// Right
    res.pb(v);                    // Node last
}

// ═══════════════════════════════════════════════════════════════
// ITERATIVE PREORDER
// ═══════════════════════════════════════════════════════════════
vec<int> iterativePreorder(int root) {
    vec<int> res;
    if (root == 0) return res;
    stack<int> stk;
    stk.push(root);
    while (!stk.empty()) {
        int v = stk.top(); stk.pop();
        res.pb(v);
        if (rightChild[v]) stk.push(rightChild[v]); // right first!
        if (leftChild[v]) stk.push(leftChild[v]);   // so left pops first
    }
    return res;
}

// ═══════════════════════════════════════════════════════════════
// ITERATIVE INORDER
// ═══════════════════════════════════════════════════════════════
vec<int> iterativeInorder(int root) {
    vec<int> res;
    stack<int> stk;
    int cur = root;
    while (cur != 0 || !stk.empty()) {
        while (cur != 0) {
            stk.push(cur);
            cur = leftChild[cur]; // go as far left as possible
        }
        cur = stk.top(); stk.pop();
        res.pb(cur);             // visit node
        cur = rightChild[cur];    // go right
    }
    return res;
}

// ═══════════════════════════════════════════════════════════════
// ITERATIVE POSTORDER (two-stack method)
// ═══════════════════════════════════════════════════════════════
vec<int> iterativePostorder(int root) {
    vec<int> res;
    if (root == 0) return res;
    stack<int> stk1, stk2;
    stk1.push(root);
    while (!stk1.empty()) {
        int v = stk1.top(); stk1.pop();
        stk2.push(v);
        if (leftChild[v]) stk1.push(leftChild[v]);
        if (rightChild[v]) stk1.push(rightChild[v]);
    }
    while (!stk2.empty()) {
        res.pb(stk2.top());
        stk2.pop();
    }
    return res;
}

void solve() {
    int n;
    cin >> n;

    leftChild.assign(n + 1, 0);
    rightChild.assign(n + 1, 0);

    // Input: for each node, its left and right children (0 = null)
    for (int i = 1; i <= n; i++) {
        cin >> leftChild[i] >> rightChild[i];
    }

    int root = 1;

    // Recursive
    vec<int> pre, in, post;
    preorder(root, pre);
    inorder(root, in);
    postorder(root, post);

    cout << "=== RECURSIVE ===" << nl;
    cout << "Preorder:  "; for (int x : pre) cout << x << " "; cout << nl;
    cout << "Inorder:   "; for (int x : in) cout << x << " "; cout << nl;
    cout << "Postorder: "; for (int x : post) cout << x << " "; cout << nl;

    // Iterative
    vec<int> iPre = iterativePreorder(root);
    vec<int> iIn = iterativeInorder(root);
    vec<int> iPost = iterativePostorder(root);

    cout << nl << "=== ITERATIVE ===" << nl;
    cout << "Preorder:  "; for (int x : iPre) cout << x << " "; cout << nl;
    cout << "Inorder:   "; for (int x : iIn) cout << x << " "; cout << nl;
    cout << "Postorder: "; for (int x : iPost) cout << x << " "; cout << nl;
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

Input format: N, then for each node i (1..N): left_child right_child (0=null)

Input:
1
7
2 3
4 5
6 7
0 0
0 0
0 0
0 0

Tree:
         1
        / \
       2   3
      / \ / \
     4  5 6  7

Output:
=== RECURSIVE ===
Preorder:  1 2 4 5 3 6 7
Inorder:   4 2 5 1 6 3 7
Postorder: 4 5 2 6 7 3 1

=== ITERATIVE ===
Preorder:  1 2 4 5 3 6 7
Inorder:   4 2 5 1 6 3 7
Postorder: 4 5 2 6 7 3 1

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Preorder: N-L-R → root first → good for "copying" tree structure
 ✅ Inorder: L-N-R → gives sorted order for BST
 ✅ Postorder: L-R-N → root last → good for "deleting" or "evaluating"
 ✅ Iterative inorder: go left until null, pop & visit, go right
 ✅ Iterative preorder: push right first, then left (stack is LIFO)
 ✅ Iterative postorder: two-stack trick (reverse of modified preorder)
═══════════════════════════════════════════════════════════════════
*/

