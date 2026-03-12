/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║        LEVEL 1 — SEGMENT TREE FUNDAMENTALS                                     ║
║        From Zero to Grandmaster — Build, Query, Update from Scratch            ║
║        Author: Sarvan Yaduvanshi                                               ║
╚══════════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. What is a Segment Tree? (Concept + Visualization)
 2. Tree Representation in Array (Indexing)
 3. Build Segment Tree — O(n)
 4. Range Query (Sum) — O(log n)
 5. Point Update — O(log n)
 6. Iterative Segment Tree (Competitive Style)
 7. Time Complexity Analysis (Proof)
 8. Memory Usage Analysis (Why 4*N?)
 9. Complete Dry Run of Build → Update → Query
 10. GM Tips + Contest Template

═══════════════════════════════════════════════════════════════
SECTION 1: WHAT IS A SEGMENT TREE?
═══════════════════════════════════════════════════════════════

A Segment Tree is a binary tree where:
  • Each LEAF stores one element of the array
  • Each INTERNAL NODE stores the result of merging its children
  • "Merge" = sum, min, max, GCD, XOR, etc.

WHY? → Answer range queries + point updates in O(log n) each!

EXAMPLE: Array a[] = {2, 1, 5, 3, 4}

Segment Tree (Range Sum):

                     [15]               ← sum of a[0..4]
                   /      \
               [8]          [7]         ← sum of a[0..2], a[3..4]
              /    \       /    \
           [3]    [5]   [3]    [4]      ← sum of a[0..1], a[2], a[3], a[4]
          /   \
        [2]   [1]                       ← a[0], a[1]

Each node stores sum of its range.
Root = sum of entire array.
Leaves = individual elements.

═══════════════════════════════════════════════════════════════
SECTION 2: TREE REPRESENTATION IN ARRAY
═══════════════════════════════════════════════════════════════

We store the tree in a 1D array (1-indexed):

Node numbering:
  • Root = node 1
  • Left child of node i  = 2*i
  • Right child of node i = 2*i + 1
  • Parent of node i      = i / 2

For array of size n, we need array of size 4*n:

Index:  1    2    3    4    5    6    7    8    9   10   11
       [15]  [8]  [7]  [3]  [5]  [3]  [4]  [2]  [1]  [0]  [0]
        ↑    ↑    ↑    ↑    ↑    ↑    ↑    ↑    ↑
       root  left right ...     ...     leaves → padding

Tree Layout:
               [1] = 15
              /        \
          [2] = 8     [3] = 7
          /    \      /     \
      [4]=3  [5]=5  [6]=3  [7]=4
      /   \
   [8]=2 [9]=1

WHY 4*N?
─────────
Worst case: when n is NOT a power of 2, the tree may have
up to 2 * (next_power_of_2(n)) - 1 nodes.
  next_power_of_2(n) ≤ 2n
  So total ≤ 4n - 1 nodes.
  We allocate 4n to be safe.

Example: n=5
  next_pow2(5) = 8
  tree nodes = 2*8 - 1 = 15
  4*5 = 20 > 15  ✓ Safe!

═══════════════════════════════════════════════════════════════
SECTION 3: BUILD — O(n)
═══════════════════════════════════════════════════════════════

ALGORITHM:
  build(node, start, end):
    if start == end:            // Leaf node
      tree[node] = a[start]
      return
    mid = (start + end) / 2
    build(2*node, start, mid)        // Build left child
    build(2*node+1, mid+1, end)      // Build right child
    tree[node] = tree[2*node] + tree[2*node+1]  // Merge

DRY RUN — Build for a[] = {2, 1, 5, 3, 4}:

  build(1, 0, 4)
    mid = 2
    ├── build(2, 0, 2)
    │     mid = 1
    │     ├── build(4, 0, 1)
    │     │     mid = 0
    │     │     ├── build(8, 0, 0) → tree[8] = a[0] = 2   [LEAF]
    │     │     └── build(9, 1, 1) → tree[9] = a[1] = 1   [LEAF]
    │     │     tree[4] = 2 + 1 = 3
    │     └── build(5, 2, 2) → tree[5] = a[2] = 5         [LEAF]
    │     tree[2] = 3 + 5 = 8
    └── build(3, 3, 4)
          mid = 3
          ├── build(6, 3, 3) → tree[6] = a[3] = 3         [LEAF]
          └── build(7, 4, 4) → tree[7] = a[4] = 4         [LEAF]
          tree[3] = 3 + 4 = 7
    tree[1] = 8 + 7 = 15

  Result: tree[] = {_, 15, 8, 7, 3, 5, 3, 4, 2, 1}
                       ↑ index 1 is root

TIME: O(n) — each node visited once, n leaves + n-1 internal = 2n-1 nodes.

═══════════════════════════════════════════════════════════════
SECTION 4: RANGE QUERY — O(log n)
═══════════════════════════════════════════════════════════════

ALGORITHM:
  query(node, start, end, l, r):
    if r < start OR end < l:     // No overlap
      return 0                   // (identity for sum)
    if l <= start AND end <= r:  // Complete overlap
      return tree[node]
    mid = (start + end) / 2      // Partial overlap
    left  = query(2*node,   start,  mid,  l, r)
    right = query(2*node+1, mid+1, end, l, r)
    return left + right

THREE CASES:
  1. NO OVERLAP:     [start...end] is entirely outside [l...r] → return 0
  2. COMPLETE OVERLAP: [start...end] is entirely inside [l...r] → return tree[node]
  3. PARTIAL OVERLAP:  Split into children and combine

DRY RUN — query(1, 0, 4, 1, 3):  (sum of a[1..3])

  query(1, 0, 4, 1, 3)  → Partial (0<1, 4>3)
    mid = 2
    ├── query(2, 0, 2, 1, 3)  → Partial
    │     mid = 1
    │     ├── query(4, 0, 1, 1, 3)  → Partial
    │     │     mid = 0
    │     │     ├── query(8, 0, 0, 1, 3) → NO OVERLAP (0 < 1) → return 0
    │     │     └── query(9, 1, 1, 1, 3) → COMPLETE (1 ∈ [1,3]) → return 1
    │     │     return 0 + 1 = 1
    │     └── query(5, 2, 2, 1, 3) → COMPLETE (2 ∈ [1,3]) → return 5
    │     return 1 + 5 = 6
    └── query(3, 3, 4, 1, 3) → Partial
          mid = 3
          ├── query(6, 3, 3, 1, 3) → COMPLETE (3 ∈ [1,3]) → return 3
          └── query(7, 4, 4, 1, 3) → NO OVERLAP (4 > 3) → return 0
          return 3 + 0 = 3
    return 6 + 3 = 9

  Answer: 9
  Verify: a[1]+a[2]+a[3] = 1+5+3 = 9 ✅

TIME: O(log n) — at most 2 nodes per level, O(log n) levels.

═══════════════════════════════════════════════════════════════
SECTION 5: POINT UPDATE — O(log n)
═══════════════════════════════════════════════════════════════

ALGORITHM:
  update(node, start, end, idx, val):
    if start == end:            // Found the leaf
      tree[node] = val
      return
    mid = (start + end) / 2
    if idx <= mid:
      update(2*node, start, mid, idx, val)
    else:
      update(2*node+1, mid+1, end, idx, val)
    tree[node] = tree[2*node] + tree[2*node+1]  // Recalculate

DRY RUN — update index 2 from 5 to 10:

  update(1, 0, 4, 2, 10)
    mid = 2, idx=2 <= mid → go left
    ├── update(2, 0, 2, 2, 10)
    │     mid = 1, idx=2 > mid → go right
    │     └── update(5, 2, 2, 2, 10)
    │           start == end → tree[5] = 10  [LEAF UPDATED]
    │     tree[2] = tree[4] + tree[5] = 3 + 10 = 13
    tree[1] = tree[2] + tree[3] = 13 + 7 = 20

  Before: tree[] = {_, 15, 8, 7, 3, 5, 3, 4, 2, 1}
  After:  tree[] = {_, 20, 13, 7, 3, 10, 3, 4, 2, 1}
                         ↑    ↑       ↑
                       root  node2   leaf changed

  Only nodes on the PATH from leaf to root are updated!
  Path length = O(log n) → O(log n) time.

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
#include <functional>

using namespace std;

// --- Type Definitions ---
using i64 = long long;
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

// --- Constants ---
constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;

// --- Macros ---
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define nl '\n'

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 1: Recursive Segment Tree (Sum)
// ═══════════════════════════════════════════════════════════════

class SegmentTreeRecursive {
    int n;
    vector<long long> tree;

    void build(const vector<int>& a, int node, int start, int end) {
        if (start == end) {
            tree[node] = a[start];
            return;
        }
        int mid = (start + end) / 2;
        build(a, 2 * node, start, mid);
        build(a, 2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    long long query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;          // No overlap
        if (l <= start && end <= r) return tree[node]; // Complete overlap
        int mid = (start + end) / 2;
        return query(2 * node, start, mid, l, r)
             + query(2 * node + 1, mid + 1, end, l, r);
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid)
            update(2 * node, start, mid, idx, val);
        else
            update(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

public:
    SegmentTreeRecursive(const vector<int>& a) : n(a.size()), tree(4 * a.size(), 0) {
        build(a, 1, 0, n - 1);
    }

    long long query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    void update(int idx, int val) {
        update(1, 0, n - 1, idx, val);
    }

    // Print tree for visualization
    void printTree() {
        cout << "  Tree array (1-indexed): ";
        for (int i = 1; i < min((int)tree.size(), 4 * n); i++) {
            if (tree[i] != 0 || i <= 2 * n)
                cout << "[" << i << "]=" << tree[i] << " ";
        }
        cout << "\n";
    }
};

void demoRecursiveSegTree() {
    cout << "═══ RECURSIVE SEGMENT TREE (SUM) ═══\n\n";

    vector<int> a = {2, 1, 5, 3, 4};
    cout << "Array: ";
    for (int x : a) cout << x << " ";
    cout << "\n\n";

    SegmentTreeRecursive st(a);

    cout << "After build:\n";
    st.printTree();
    cout << "\n";

    // Query demonstrations
    cout << "--- QUERY DEMO ---\n";
    cout << "  sum(0, 4) = " << st.query(0, 4) << "  (entire array: 2+1+5+3+4=15)\n";
    cout << "  sum(1, 3) = " << st.query(1, 3) << "  (1+5+3=9)\n";
    cout << "  sum(2, 2) = " << st.query(2, 2) << "  (single element: 5)\n";
    cout << "  sum(0, 1) = " << st.query(0, 1) << "  (2+1=3)\n";
    cout << "  sum(3, 4) = " << st.query(3, 4) << "  (3+4=7)\n\n";

    // Update demonstration
    cout << "--- UPDATE DEMO ---\n";
    cout << "Update: a[2] = 10 (was 5)\n";
    st.update(2, 10);
    cout << "After update:\n";
    st.printTree();
    cout << "  sum(0, 4) = " << st.query(0, 4) << "  (2+1+10+3+4=20)\n";
    cout << "  sum(1, 3) = " << st.query(1, 3) << "  (1+10+3=14)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 2: Iterative Segment Tree (Competitive Style)
// ═══════════════════════════════════════════════════════════════

/*
ITERATIVE SEGMENT TREE:
─────────────────────────
Much faster in practice (no recursion overhead).
Uses BOTTOM-UP approach with array of size 2*N.

Key insight:
  • Leaves are at positions [n, 2n-1]
  • Internal nodes at [1, n-1]
  • tree[i] = tree[2i] + tree[2i+1]

Build:
  1. Copy array to leaves: tree[n+i] = a[i]
  2. Build bottom-up: tree[i] = tree[2i] + tree[2i+1]

Update(pos, val):
  1. Set tree[pos+n] = val
  2. Walk up: pos/=2, recalculate

Query(l, r): [l, r) half-open interval
  1. Set l += n, r += n + 1  (convert to leaf indices)
  2. Accumulate from both sides, moving up

VISUALIZATION for n=4, a[] = {2, 1, 5, 3}:

  Index:  [0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]
  tree:    -   11    3    8    2    1    5    3
                ↑   ↑    ↑    ↑    ↑    ↑    ↑
              root  l    r  leaves ──────────────→

  tree[1] = 11 (root = sum of all)
  tree[2] = 3  (sum of a[0..1])
  tree[3] = 8  (sum of a[2..3])
  tree[4] = 2, tree[5] = 1, tree[6] = 5, tree[7] = 3  (leaves)
*/

class SegmentTreeIterative {
    int n;
    vector<long long> tree;

public:
    SegmentTreeIterative(const vector<int>& a) {
        n = a.size();
        tree.assign(2 * n, 0);
        // Copy leaves
        for (int i = 0; i < n; i++)
            tree[n + i] = a[i];
        // Build internal nodes bottom-up
        for (int i = n - 1; i >= 1; i--)
            tree[i] = tree[2 * i] + tree[2 * i + 1];
    }

    // Point update: set a[pos] = val
    void update(int pos, long long val) {
        pos += n;          // Go to leaf
        tree[pos] = val;
        // Walk up to root
        for (pos /= 2; pos >= 1; pos /= 2)
            tree[pos] = tree[2 * pos] + tree[2 * pos + 1];
    }

    // Range query: sum of a[l..r] (inclusive)
    long long query(int l, int r) {
        long long res = 0;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) res += tree[l++];   // l is right child → include it
            if (r & 1) res += tree[--r];   // r is right child → include left sibling
        }
        return res;
    }

    void printTree() {
        cout << "  Iterative tree: ";
        for (int i = 1; i < 2 * n; i++)
            cout << "[" << i << "]=" << tree[i] << " ";
        cout << "\n";
    }
};

void demoIterativeSegTree() {
    cout << "═══ ITERATIVE SEGMENT TREE ═══\n\n";

    vector<int> a = {2, 1, 5, 3, 4};
    SegmentTreeIterative st(a);

    cout << "Array: 2 1 5 3 4\n";
    st.printTree();
    cout << "\n";

    cout << "sum(0, 4) = " << st.query(0, 4) << "\n";
    cout << "sum(1, 3) = " << st.query(1, 3) << "\n";
    cout << "sum(2, 2) = " << st.query(2, 2) << "\n\n";

    cout << "Update: a[2] = 10\n";
    st.update(2, 10);
    st.printTree();
    cout << "sum(0, 4) = " << st.query(0, 4) << "\n";
    cout << "sum(1, 3) = " << st.query(1, 3) << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 7: TIME COMPLEXITY ANALYSIS
// ═══════════════════════════════════════════════════════════════

void demoComplexityAnalysis() {
    cout << "═══ COMPLEXITY ANALYSIS ═══\n\n";

    cout << "BUILD: O(n)\n";
    cout << "  • Total nodes in tree = 2n - 1 (approx)\n";
    cout << "  • Each node computed once → O(n)\n\n";

    cout << "QUERY: O(log n)\n";
    cout << "  • Tree height = ceil(log2(n))\n";
    cout << "  • At each level, we visit AT MOST 2 partial-overlap nodes\n";
    cout << "  • Proof: If 3+ partial nodes at one level, middle one is fully covered\n";
    cout << "  • So max nodes visited = 2 * log2(n) = O(log n)\n\n";

    cout << "UPDATE: O(log n)\n";
    cout << "  • Update leaf, then walk to root\n";
    cout << "  • Path length = tree height = O(log n)\n\n";

    cout << "SPACE: O(4n) for recursive, O(2n) for iterative\n";
    cout << "  • Recursive: Need 4n to handle non-power-of-2 sizes safely\n";
    cout << "  • Iterative: Exactly 2n (pad array to size n)\n\n";

    // Empirical demonstration
    cout << "Empirical timing for different n:\n";
    for (int n : {1000, 10000, 100000, 1000000}) {
        vector<int> a(n, 1);
        auto t1 = chrono::high_resolution_clock::now();

        SegmentTreeRecursive st(a);
        for (int i = 0; i < n; i++) st.query(0, i);

        auto t2 = chrono::high_resolution_clock::now();
        auto ms = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
        cout << "  n=" << setw(7) << n << " → " << setw(8) << ms << " μs"
             << " (n queries)\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 9: COMPLETE DRY RUN WALKTHROUGH
// ═══════════════════════════════════════════════════════════════

void completeWalkthrough() {
    cout << "═══ COMPLETE DRY RUN WALKTHROUGH ═══\n\n";

    vector<int> a = {3, 7, 2, 5, 1};
    cout << "Array a[] = {3, 7, 2, 5, 1}\n\n";

    cout << "STEP 1: BUILD\n";
    cout << "─────────────\n";
    cout << "  build(1, 0, 4)\n";
    cout << "  │\n";
    cout << "  ├─ build(2, 0, 2)\n";
    cout << "  │  ├─ build(4, 0, 1)\n";
    cout << "  │  │  ├─ build(8, 0, 0) → tree[8] = 3\n";
    cout << "  │  │  └─ build(9, 1, 1) → tree[9] = 7\n";
    cout << "  │  │  tree[4] = 3 + 7 = 10\n";
    cout << "  │  └─ build(5, 2, 2) → tree[5] = 2\n";
    cout << "  │  tree[2] = 10 + 2 = 12\n";
    cout << "  │\n";
    cout << "  └─ build(3, 3, 4)\n";
    cout << "     ├─ build(6, 3, 3) → tree[6] = 5\n";
    cout << "     └─ build(7, 4, 4) → tree[7] = 1\n";
    cout << "     tree[3] = 5 + 1 = 6\n";
    cout << "  tree[1] = 12 + 6 = 18\n\n";

    SegmentTreeRecursive st(a);

    cout << "  Tree visualization:\n";
    cout << "              [1]=18\n";
    cout << "             /      \\\n";
    cout << "         [2]=12    [3]=6\n";
    cout << "         /    \\    /   \\\n";
    cout << "     [4]=10 [5]=2 [6]=5 [7]=1\n";
    cout << "      / \\\n";
    cout << "   [8]=3 [9]=7\n\n";

    cout << "STEP 2: QUERY sum(1, 3) = ?\n";
    cout << "─────────────────────────────\n";
    cout << "  query(1, 0, 4, 1, 3)  → PARTIAL\n";
    cout << "  ├─ query(2, 0, 2, 1, 3)  → PARTIAL\n";
    cout << "  │  ├─ query(4, 0, 1, 1, 3) → PARTIAL\n";
    cout << "  │  │  ├─ query(8, 0, 0, 1, 3) → NO OVERLAP → 0\n";
    cout << "  │  │  └─ query(9, 1, 1, 1, 3) → COMPLETE → 7\n";
    cout << "  │  │  return 0 + 7 = 7\n";
    cout << "  │  └─ query(5, 2, 2, 1, 3) → COMPLETE → 2\n";
    cout << "  │  return 7 + 2 = 9\n";
    cout << "  └─ query(3, 3, 4, 1, 3) → PARTIAL\n";
    cout << "     ├─ query(6, 3, 3, 1, 3) → COMPLETE → 5\n";
    cout << "     └─ query(7, 4, 4, 1, 3) → NO OVERLAP → 0\n";
    cout << "     return 5 + 0 = 5\n";
    cout << "  return 9 + 5 = 14\n";
    cout << "  Answer: " << st.query(1, 3) << " ✓ (7+2+5=14)\n\n";

    cout << "STEP 3: UPDATE a[2] = 8 (was 2)\n";
    cout << "─────────────────────────────────\n";
    cout << "  update(1, 0, 4, 2, 8)\n";
    cout << "  mid=2, idx=2 ≤ 2 → go LEFT\n";
    cout << "  ├─ update(2, 0, 2, 2, 8)\n";
    cout << "  │  mid=1, idx=2 > 1 → go RIGHT\n";
    cout << "  │  └─ update(5, 2, 2, 2, 8)\n";
    cout << "  │     tree[5] = 8  [LEAF]\n";
    cout << "  │  tree[2] = tree[4]+tree[5] = 10+8 = 18\n";
    cout << "  tree[1] = tree[2]+tree[3] = 18+6 = 24\n\n";

    st.update(2, 8);
    cout << "  After update:\n";
    cout << "              [1]=24\n";
    cout << "             /      \\\n";
    cout << "         [2]=18    [3]=6\n";
    cout << "         /    \\    /   \\\n";
    cout << "     [4]=10 [5]=8 [6]=5 [7]=1\n";
    cout << "      / \\\n";
    cout << "   [8]=3 [9]=7\n\n";

    cout << "  Verify: sum(0,4) = 3+7+8+5+1 = " << st.query(0, 4) << " ✓\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║   LEVEL 1: SEGMENT TREE FUNDAMENTALS — COMPLETE GUIDE      ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n\n";

    demoRecursiveSegTree();
    demoIterativeSegTree();
    demoComplexityAnalysis();
    completeWalkthrough();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "  KEY TAKEAWAYS:\n";
    cout << "  1. Segment Tree = binary tree, each node = merge of range\n";
    cout << "  2. Build O(n), Query O(log n), Update O(log n)\n";
    cout << "  3. Array size = 4*N (recursive) or 2*N (iterative)\n";
    cout << "  4. 3 cases: No overlap, Complete overlap, Partial overlap\n";
    cout << "  5. Iterative is ~2x faster (no recursion overhead)\n";
    cout << "  6. Always use 1-indexed for recursive segment tree\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

