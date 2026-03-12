/*
╔══════════════════════════════════════════════════════════════════╗
║  04 — INVERT BINARY TREE & FLATTEN TO LINKED LIST               ║
║  Zero to GM Level — Binary Tree Problems                         ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 1. INVERT BINARY TREE (LeetCode 226) — DRY RUN
═══════════════════════════════════════════════════════════════════

 Swap left and right children at EVERY node.

 Before:            After:
      1                 1
     / \               / \
    2   3             3   2
   / \   \           /   / \
  4   5   6         6   5   4

 invert(1):
   swap(left=2, right=3) → now left=3, right=2
   invert(3):  (was right, now left)
     swap(left=null, right=6) → left=6, right=null
     invert(6): leaf, done
   invert(2):  (was left, now right)
     swap(left=4, right=5) → left=5, right=4
     invert(5): leaf
     invert(4): leaf

═══════════════════════════════════════════════════════════════════
 2. FLATTEN TO LINKED LIST (LeetCode 114) — DRY RUN
═══════════════════════════════════════════════════════════════════

 Convert binary tree to a right-skewed "linked list" in preorder.

 Before:            After (right-only chain):
      1                 1
     / \                 \
    2   5                 2
   / \   \                 \
  3   4   6                 3
                             \
                              4
                               \
                                5
                                 \
                                  6

 Preorder: 1 2 3 4 5 6 → each node's right = next in preorder

 Algorithm (reverse postorder):
   Process right, then left, then current.
   Keep a `prev` pointer to the last processed node.

   flatten(6): prev=6
   flatten(5): right=prev=6, left=null, prev=5
   flatten(4): prev=4
   flatten(3): prev=3
   flatten(2): right=prev=3, left=null, prev=2
   flatten(1): right=prev=2, left=null, prev=1

 Result: 1→2→3→4→5→6 ✅

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

vec<int> L, R;
int n;

// ═══════════════════════════════════════════════════════════
// 1. INVERT BINARY TREE — swap left and right everywhere
// ═══════════════════════════════════════════════════════════
void invertTree(int v) {
    if (v == 0) return;
    swap(L[v], R[v]);  // swap children
    invertTree(L[v]);
    invertTree(R[v]);
}

// ═══════════════════════════════════════════════════════════
// 2. FLATTEN TO LINKED LIST (preorder right-chain)
// ═══════════════════════════════════════════════════════════
int prev_node;

void flatten(int v) {
    if (v == 0) return;
    // Process right subtree first, then left, then current
    flatten(R[v]);
    flatten(L[v]);
    R[v] = prev_node;
    L[v] = 0;
    prev_node = v;
}

// Print tree in preorder
void printPreorder(int v) {
    if (v == 0) return;
    cout << v << " ";
    printPreorder(L[v]);
    printPreorder(R[v]);
}

// Print flattened chain (follow right pointers)
void printChain(int v) {
    while (v != 0) {
        cout << v;
        if (R[v]) cout << " → ";
        v = R[v];
    }
    cout << nl;
}

void solve() {
    cin >> n;
    L.assign(n + 1, 0);
    R.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> L[i] >> R[i];

    cout << "Original preorder: ";
    printPreorder(1);
    cout << nl;

    // Invert
    invertTree(1);
    cout << "After invert: ";
    printPreorder(1);
    cout << nl;

    // Invert back for flatten demo
    invertTree(1);

    // Flatten
    prev_node = 0;
    flatten(1);
    cout << "Flattened chain: ";
    printChain(1);
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
5
2 3
4 5
0 0
0 0
0 0

Tree:     1
        /   \
       2     3
      / \
     4   5

Output:
Original preorder: 1 2 4 5 3
After invert: 1 3 2 5 4
Flattened chain: 1 → 2 → 4 → 5 → 3

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Invert: swap(left, right) at every node recursively
 ✅ Flatten: reverse-postorder trick with prev pointer
 ✅ Both are O(N) time, O(H) space
═══════════════════════════════════════════════════════════════════
*/

