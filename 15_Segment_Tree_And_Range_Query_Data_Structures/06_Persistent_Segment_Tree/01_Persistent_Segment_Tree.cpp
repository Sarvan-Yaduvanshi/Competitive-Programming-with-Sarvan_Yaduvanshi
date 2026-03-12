/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║        LEVEL 5 — PERSISTENT SEGMENT TREE                                       ║
║        Versioned Trees, Kth Smallest in Range, Path Copying                    ║
║        Author: Sarvan Yaduvanshi                                               ║
╚══════════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Why Persistence? (Motivation)
 2. Path Copying Concept — Visualization
 3. Persistent Segment Tree Implementation
 4. Kth Smallest in Range [L, R] — Classic Application
 5. Versioned Array (CSES Range Queries and Copies)
 6. Memory Analysis
 7. Complete Dry Run

═══════════════════════════════════════════════════════════════
SECTION 1: WHY PERSISTENCE?
═══════════════════════════════════════════════════════════════

PROBLEM 1: "Copy array, modify copy, query any version"
  → Naive: O(n) per copy. With N copies + Q queries → O(N²)
  → Persistent ST: O(log n) per operation!

PROBLEM 2: "Kth smallest element in subarray [L, R]"
  → One of the most asked problems in competitive programming!
  → Persistent ST on sorted values solves it in O(log n).

KEY IDEA: Instead of modifying the tree, create a NEW VERSION
          that shares most nodes with the old version.

═══════════════════════════════════════════════════════════════
SECTION 2: PATH COPYING CONCEPT
═══════════════════════════════════════════════════════════════

When we update one element, only O(log n) nodes change
(the path from leaf to root). We create NEW nodes only
for this path, and REUSE all other nodes.

VISUALIZATION:

  Version 0 (original tree for a = [1, 2, 3, 4]):

       root₀
       /    \
     A₀      B₀
    / \      / \
   1   2    3   4

  Update: a[2] = 5 → Create Version 1:

       root₁  (NEW)       root₀  (still valid!)
       /    \              /    \
     A₀      B₁ (NEW)    A₀    B₀
    / \      / \          / \   / \
   1   2    5   4        1  2  3  4
            ↑ NEW leaf

  Only 3 new nodes created (root₁, B₁, leaf 5)!
  All other nodes are SHARED with version 0.

  Memory per update: O(log n) new nodes
  Total memory for Q updates: O(n + Q log n)

VERSION ARRAY:
  roots[] = [root₀, root₁, root₂, ...]
  To query version k: start from roots[k]

═══════════════════════════════════════════════════════════════
SECTION 3: KTH SMALLEST IN RANGE
═══════════════════════════════════════════════════════════════

PROBLEM: Given array a[], answer Q queries:
  "What is the kth smallest element in a[l..r]?"

APPROACH:
  1. Sort + coordinate compress the values.
  2. Build persistent ST on VALUE DOMAIN [1..n].
  3. Process elements left-to-right:
     Version i = Version (i-1) + insert a[i]
  4. For query(l, r, k):
     Use roots[r] - roots[l-1] to get counts in [l..r]
     Walk down the tree to find kth element.

DRY RUN:
  a[] = {5, 2, 6, 1, 3}    n = 5
  Sorted unique: {1, 2, 3, 5, 6}
  Compressed:     1  2  3  4  5

  Value domain: [1, 5] (5 possible values)

  Version 0: empty tree (all zeros)
       [0]
      /    \
    [0]    [0]
    / \    / \
  [0][0] [0][0]
  (Never actually built, just conceptual)

  Process a[0]=5 (compressed=4): Insert 1 at position 4
  Version 1 = Version 0 + (position 4 incremented)

  Process a[1]=2 (compressed=2): Insert 1 at position 2
  Version 2 = Version 1 + (position 2 incremented)

  Process a[2]=6 (compressed=5): Insert 1 at position 5
  Version 3 = Version 2 + (position 5 incremented)

  Process a[3]=1 (compressed=1): Insert 1 at position 1
  Version 4 = Version 3 + (position 1 incremented)

  Process a[4]=3 (compressed=3): Insert 1 at position 3
  Version 5 = Version 4 + (position 3 incremented)

  Query: kth smallest in a[1..3] (0-indexed), k=2
    Elements: {2, 6, 1} → sorted: {1, 2, 6} → 2nd smallest = 2

    Use roots[4] - roots[1]:  (versions covering indices 1..3)
    Count in left half [1,2]:
      roots[4].left.count - roots[1].left.count
      = 2 - 0 = 2  (elements 1 and 2 are in left half)
    k=2 ≤ 2 → answer is in left half [1,2]
    Go left:
      Count in [1,1]:
        = 1 - 0 = 1
      k=2 > 1 → answer is in right half [2,2]
      k = k - 1 = 1
      Go right to [2,2]: answer = value 2 = original value 2 ✓

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
// IMPLEMENTATION: Persistent Segment Tree
// ═══════════════════════════════════════════════════════════════

struct PSTNode {
    int left, right;  // indices of children in node pool
    long long val;     // sum/count
};

class PersistentSegTree {
    vector<PSTNode> nodes;
    vector<int> roots;  // root of each version
    int n;

    int newNode(long long val = 0, int left = 0, int right = 0) {
        nodes.push_back({left, right, val});
        return nodes.size() - 1;
    }

    int build(int s, int e) {
        int node = newNode();
        if (s == e) return node;
        int mid = (s + e) / 2;
        nodes[node].left = build(s, mid);
        nodes[node].right = build(mid + 1, e);
        return node;
    }

    // Create new version by updating position pos
    int update(int prev, int s, int e, int pos, long long val) {
        int node = newNode(nodes[prev].val + val, nodes[prev].left, nodes[prev].right);
        if (s == e) return node;
        int mid = (s + e) / 2;
        if (pos <= mid)
            nodes[node].left = update(nodes[prev].left, s, mid, pos, val);
        else
            nodes[node].right = update(nodes[prev].right, mid + 1, e, pos, val);
        nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;
        return node;
    }

    long long query(int node, int s, int e, int l, int r) {
        if (node == 0 || r < s || e < l) return 0;
        if (l <= s && e <= r) return nodes[node].val;
        int mid = (s + e) / 2;
        return query(nodes[node].left, s, mid, l, r)
             + query(nodes[node].right, mid + 1, e, l, r);
    }

    // Kth smallest: walk on two versions simultaneously
    int kthSmallest(int vl, int vr, int s, int e, int k) {
        if (s == e) return s;
        int mid = (s + e) / 2;
        long long leftCount = nodes[nodes[vr].left].val - nodes[nodes[vl].left].val;
        if (k <= leftCount)
            return kthSmallest(nodes[vl].left, nodes[vr].left, s, mid, k);
        else
            return kthSmallest(nodes[vl].right, nodes[vr].right, mid + 1, e, k - leftCount);
    }

public:
    PersistentSegTree(int n) : n(n) {
        nodes.reserve(20 * n); // pre-allocate
        nodes.push_back({0, 0, 0}); // dummy node 0
        roots.push_back(build(0, n - 1));
    }

    // Create new version by inserting val at position pos
    void insert(int pos, long long val = 1) {
        roots.push_back(update(roots.back(), 0, n - 1, pos, val));
    }

    // Query version v for range [l, r]
    long long queryVersion(int v, int l, int r) {
        return query(roots[v], 0, n - 1, l, r);
    }

    // Kth smallest in original array range [l, r] (0-indexed)
    int kthSmallest(int l, int r, int k) {
        return kthSmallest(roots[l], roots[r + 1], 0, n - 1, k);
    }

    int getVersionCount() { return roots.size(); }
    int getNodeCount() { return nodes.size(); }
};

void demoKthSmallest() {
    cout << "═══ KTH SMALLEST IN RANGE (PERSISTENT ST) ═══\n\n";

    vector<int> a = {5, 2, 6, 1, 3};
    int n = a.size();
    cout << "Array: ";
    for (int x : a) cout << x << " ";
    cout << "\n\n";

    // Coordinate compression
    vector<int> sorted_vals = a;
    sort(sorted_vals.begin(), sorted_vals.end());
    sorted_vals.erase(unique(sorted_vals.begin(), sorted_vals.end()), sorted_vals.end());
    int m = sorted_vals.size();

    auto compress = [&](int val) {
        return lower_bound(sorted_vals.begin(), sorted_vals.end(), val) - sorted_vals.begin();
    };

    cout << "Compressed values: ";
    for (int i = 0; i < m; i++) cout << sorted_vals[i] << "→" << i << " ";
    cout << "\n\n";

    // Build persistent segment tree
    PersistentSegTree pst(m);
    for (int i = 0; i < n; i++) {
        pst.insert(compress(a[i]));
    }

    cout << "Versions created: " << pst.getVersionCount() << "\n";
    cout << "Total nodes: " << pst.getNodeCount() << "\n\n";

    // Queries
    cout << "Kth smallest queries:\n";

    // Query: 2nd smallest in a[1..3] = {2, 6, 1} → sorted {1,2,6} → 2nd = 2
    int idx = pst.kthSmallest(1, 3, 2);
    cout << "  2nd smallest in a[1..3] = " << sorted_vals[idx]
         << "  (elements: 2,6,1 → sorted: 1,2,6 → 2nd = 2)\n";

    // Query: 1st smallest in a[0..4] = {5,2,6,1,3} → 1
    idx = pst.kthSmallest(0, 4, 1);
    cout << "  1st smallest in a[0..4] = " << sorted_vals[idx] << "\n";

    // Query: 3rd smallest in a[0..4] = 3
    idx = pst.kthSmallest(0, 4, 3);
    cout << "  3rd smallest in a[0..4] = " << sorted_vals[idx] << "\n";

    // Query: 1st smallest in a[2..4] = {6,1,3} → 1
    idx = pst.kthSmallest(2, 4, 1);
    cout << "  1st smallest in a[2..4] = " << sorted_vals[idx] << "\n";

    // Query: 2nd smallest in a[0..1] = {5,2} → 5
    idx = pst.kthSmallest(0, 1, 2);
    cout << "  2nd smallest in a[0..1] = " << sorted_vals[idx] << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// DEMO 2: Versioned Array (CSES Range Queries and Copies)
// ═══════════════════════════════════════════════════════════════

void demoVersionedArray() {
    cout << "═══ VERSIONED ARRAY (CSES 1737 STYLE) ═══\n\n";

    cout << "Concept: Multiple versions of an array.\n";
    cout << "  Operation 1: Set a[i] = val (creates new version)\n";
    cout << "  Operation 2: Copy array (creates new version = old version)\n";
    cout << "  Operation 3: Query sum(l, r) on specific version\n\n";

    cout << "This is directly supported by Persistent ST:\n";
    cout << "  • Set a[i] = val → update(root_v, pos, val) → new root\n";
    cout << "  • Copy → just duplicate the root pointer!\n";
    cout << "  • Query → query(root_v, l, r)\n\n";

    cout << "Memory: O(n + Q * log n) total nodes\n";
    cout << "  Each update creates O(log n) new nodes\n";
    cout << "  Copy creates 0 new nodes (just store root pointer)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MEMORY ANALYSIS
// ═══════════════════════════════════════════════════════════════

void demoMemory() {
    cout << "═══ MEMORY ANALYSIS ═══\n\n";

    cout << "Normal Segment Tree: O(4n) nodes\n";
    cout << "Persistent ST initial build: O(2n) nodes\n";
    cout << "Each update: O(log n) new nodes\n";
    cout << "Q updates total: O(n + Q * log n) nodes\n\n";

    cout << "Practical estimate:\n";
    for (int n : {100000, 200000, 500000, 1000000}) {
        int Q = n;
        long long nodes = 2LL * n + (long long)Q * 20; // ~20 = log(10^6)
        long long bytes = nodes * 20; // ~20 bytes per node (2 ints + 1 long long)
        cout << "  n=" << n << ", Q=" << Q << ": ~" << nodes / 1000 << "K nodes, ~"
             << bytes / (1024 * 1024) << " MB\n";
    }
    cout << "\n";

    cout << "GM TIP: Pre-allocate node pool!\n";
    cout << "  nodes.reserve(n * 25) for safety\n";
    cout << "  Never use new/delete in contest (too slow)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║   LEVEL 5: PERSISTENT SEGMENT TREE — COMPLETE GUIDE        ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n\n";

    demoKthSmallest();
    demoVersionedArray();
    demoMemory();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "  KEY TAKEAWAYS:\n";
    cout << "  1. Persistent ST = create new version per update\n";
    cout << "  2. Path Copying: only O(log n) new nodes per update\n";
    cout << "  3. Kth smallest: build PST on value domain, walk 2 roots\n";
    cout << "  4. Versioned array: copy = duplicate root pointer\n";
    cout << "  5. Memory: O(n + Q * log n), pre-allocate!\n";
    cout << "  6. Never modify old nodes — persistence = immutability\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

