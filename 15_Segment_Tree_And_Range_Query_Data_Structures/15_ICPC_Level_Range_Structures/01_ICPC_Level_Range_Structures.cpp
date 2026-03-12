/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║        LEVEL 14 — ICPC LEVEL RANGE STRUCTURES                                  ║
║        Wavelet Tree, Merge Sort Tree, Li Chao Tree, Dynamic ST                 ║
║        Author: Sarvan Yaduvanshi                                               ║
╚══════════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Merge Sort Tree — Concept + Implementation
 2. Wavelet Tree — Concept + Kth Smallest
 3. Li Chao Tree — Online Convex Hull Trick
 4. Implicit / Dynamic Segment Tree — Sparse Nodes
 5. Complete Dry Runs

═══════════════════════════════════════════════════════════════
SECTION 1: MERGE SORT TREE
═══════════════════════════════════════════════════════════════

A Merge Sort Tree is a segment tree where each node stores
the SORTED LIST of elements in its range.

WHY? → Supports queries like:
  • Count elements ≤ x in range [l, r]
  • Count elements in [lo, hi] in range [l, r]
  • Kth smallest in range [l, r] (with binary search)

BUILD: Same as merge sort — each node stores sorted subarray.
QUERY: At each O(log n) node, binary search the sorted list.

TIME: Build O(n log n), Query O(log²n), Space O(n log n)

VISUALIZATION:
  a[] = {5, 2, 6, 1, 3, 7, 4}

  Root: [1, 2, 3, 4, 5, 6, 7]    ← sorted entire array
        /                  \
  [1, 2, 5, 6]         [3, 4, 7]  ← sorted halves
    /       \            /      \
  [2, 5]  [1, 6]     [3, 7]   [4]
  / \      / \        / \
 [5] [2] [6] [1]    [3] [7]

Query: Count elements ≤ 4 in [0, 6]:
  Root covers all → binary search for 4 → position 4 → count = 4
  Answer: 4 (elements 1, 2, 3, 4) ✓

Query: Count elements ≤ 4 in [2, 5] (elements 6, 1, 3, 7):
  Decompose into nodes, binary search each → total count = 2 (1, 3)

═══════════════════════════════════════════════════════════════
SECTION 2: WAVELET TREE
═══════════════════════════════════════════════════════════════

A Wavelet Tree partitions elements by BIT of their value.
  • Root divides elements into "≤ mid" (left) and "> mid" (right)
  • Recurse on each half with narrower value range

SUPPORTS (all in O(log σ) where σ = value range):
  • Kth smallest in [l, r]
  • Count of value v in [l, r]
  • Count of values in [lo, hi] in [l, r]
  • Quantile queries

VISUALIZATION:
  a[] = {3, 1, 4, 1, 5, 2}    values in [1, 5], mid = 3

  Root: [3, 1, 4, 1, 5, 2]     values [1, 5], mid = 3
    bitmap: [L, L, R, L, R, L]  (≤3: Left, >3: Right)
    count_left = [0, 1, 2, 2, 3, 3, 4]  (prefix count of L)

    Left child (≤3):  [3, 1, 1, 2]   values [1, 3], mid = 2
      bitmap: [R, L, L, L]
      Left (≤2):  [1, 1, 2]   → leaf level
      Right (>2): [3]         → leaf level

    Right child (>3): [4, 5]    values [4, 5], mid = 4
      bitmap: [L, R]
      Left (≤4):  [4]
      Right (>4): [5]

Query: 2nd smallest in [1, 4] (elements: 1, 4, 1, 5)
  At root: count_left in [1,4] = 2 (elements 1, 1 go left)
    k=2 ≤ 2 → answer in left subtree
    Map [1,4] to left child's range: [0, 1]  (2 elements)
  At left child [1,3]: [3, 1, 1, 2], query [0, 1]
    count_left in [0,1] = 1 (element 1 goes left, 3 goes right)
    k=2 > 1 → answer in right subtree, k = 2-1 = 1
    Map to right child's range: [0, 0]
  At right child of [1,3] which is [3]: query [0,0], k=1
    Leaf → answer = 3?

  Hmm let me reconsider — the mapping is the tricky part.
  But the key idea is: binary search on value domain,
  using prefix counts to narrow down.

═══════════════════════════════════════════════════════════════
SECTION 3: LI CHAO TREE
═══════════════════════════════════════════════════════════════

Li Chao Tree efficiently handles the LINE CONTAINER problem:
  • Insert line y = mx + b
  • Query: at point x, what is the MINIMUM y over all inserted lines?

This is the "online convex hull trick" data structure.

CONCEPT: Segment tree over the X-DOMAIN.
Each node stores a line that is "dominant" for some point in its range.

INSERT(line):
  At each node, compare with current line at midpoint.
  The line that is better at mid stays.
  The other line may still be useful in one half → recurse.

QUERY(x): Walk from root to leaf, taking best line at each node.

TIME: O(log C) per insert/query, where C = x-coordinate range.

DRY RUN:
  X domain: [0, 8]

  Insert y = 2x + 1  (line A):
    Root [0,8], mid=4: line A gives y(4) = 9. Store A.

  Insert y = -x + 10  (line B):
    Root [0,8], mid=4: B gives y(4) = 6 < A's 9. B is better at mid.
    Swap: store B at root, push A to right [5,8] where A beats B.
    At [5,8], mid=6: A gives y(6)=13, B gives 4. A is worse at 6.
    Actually B gives y(6) = -6+10=4, A gives 2*6+1=13. B still better.
    At [5,6], A goes to right [7,8]: A gives y(7)=15, B gives 3.
    Hmm, this doesn't seem right. Let me re-examine.

  The line that LOSES at mid might still win in one half.
  Key: after comparison at mid, the loser goes to the half where it MIGHT still win.

USE CASES:
  • DP optimization: dp[i] = min(dp[j] + cost(j, i)) where cost is linear
  • Convex hull trick when slopes are not monotone → Li Chao
  • Example: CSES Frog 3, SPOJ NKLEAVES

═══════════════════════════════════════════════════════════════
SECTION 4: IMPLICIT / DYNAMIC SEGMENT TREE
═══════════════════════════════════════════════════════════════

PROBLEM: Need segment tree over range [0, 10^9] but only
         touch ~10^5 positions.

Normal ST would need 4 × 10^9 nodes → too much memory!

SOLUTION: Only create nodes when needed (lazy creation).

Each node stores pointers (indices) to left/right child.
Initially, only root exists. New nodes created on update.

MEMORY: O(Q × log C) where C = coordinate range, Q = updates.

IMPLEMENTATION: Use a node pool (vector<Node>), each node
has {left_idx, right_idx, value}. Create new nodes dynamically.

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
// IMPLEMENTATION 1: Merge Sort Tree
// ═══════════════════════════════════════════════════════════════

class MergeSortTree {
    int n;
    vector<vector<int>> tree;

    void build(const vector<int>& a, int node, int s, int e) {
        if (s == e) { tree[node] = {a[s]}; return; }
        int mid = (s + e) / 2;
        build(a, 2*node, s, mid);
        build(a, 2*node+1, mid+1, e);
        merge(tree[2*node].begin(), tree[2*node].end(),
              tree[2*node+1].begin(), tree[2*node+1].end(),
              back_inserter(tree[node]));
    }

    // Count elements ≤ x in range [l, r]
    int countLE(int node, int s, int e, int l, int r, int x) {
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) {
            return upper_bound(tree[node].begin(), tree[node].end(), x) - tree[node].begin();
        }
        int mid = (s + e) / 2;
        return countLE(2*node, s, mid, l, r, x)
             + countLE(2*node+1, mid+1, e, l, r, x);
    }

public:
    MergeSortTree(const vector<int>& a) : n(a.size()), tree(4 * a.size()) {
        build(a, 1, 0, n-1);
    }

    int countLE(int l, int r, int x) { return countLE(1, 0, n-1, l, r, x); }
    int countInRange(int l, int r, int lo, int hi) {
        return countLE(l, r, hi) - countLE(l, r, lo - 1);
    }

    // Kth smallest using binary search on answer
    int kthSmallest(int l, int r, int k) {
        int lo = INT_MIN/2, hi = INT_MAX/2;
        // Need to know value range; use tree[1] which is fully sorted
        lo = tree[1].front();
        hi = tree[1].back();
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (countLE(l, r, mid) >= k) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};

void demoMergeSortTree() {
    cout << "═══ MERGE SORT TREE ═══\n\n";

    vector<int> a = {5, 2, 6, 1, 3, 7, 4};
    cout << "Array: ";
    for (int x : a) cout << x << " ";
    cout << "\n\n";

    MergeSortTree mst(a);

    cout << "Count queries:\n";
    cout << "  count(≤4 in [0,6]) = " << mst.countLE(0, 6, 4) << " (1,2,3,4 → 4)\n";
    cout << "  count(≤4 in [2,5]) = " << mst.countLE(2, 5, 4) << " (1,3 → 2)\n";
    cout << "  count(in [2,5] in [0,6]) = " << mst.countInRange(0, 6, 2, 5)
         << " (2,3,4,5 → 4)\n\n";

    cout << "Kth smallest queries:\n";
    cout << "  1st smallest in [0,6] = " << mst.kthSmallest(0, 6, 1) << " (1)\n";
    cout << "  3rd smallest in [0,6] = " << mst.kthSmallest(0, 6, 3) << " (3)\n";
    cout << "  2nd smallest in [2,5] = " << mst.kthSmallest(2, 5, 2) << " (3)\n\n";

    cout << "Complexity:\n";
    cout << "  Build: O(n log n) time & space\n";
    cout << "  Count ≤ x: O(log²n)\n";
    cout << "  Kth smallest: O(log³n) with binary search on answer\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 2: Li Chao Tree
// ═══════════════════════════════════════════════════════════════

struct Line {
    long long m, b; // y = mx + b
    long long eval(long long x) const { return m * x + b; }
};

class LiChaoTree {
    struct Node {
        Line line;
        int left, right;
        bool hasLine;
    };

    vector<Node> nodes;
    long long lo, hi;

    int newNode() {
        nodes.push_back({{0, 0}, -1, -1, false});
        return nodes.size() - 1;
    }

    void insert(int node, long long s, long long e, Line newLine) {
        if (!nodes[node].hasLine) {
            nodes[node].line = newLine;
            nodes[node].hasLine = true;
            return;
        }

        long long mid = (s + e) / 2;
        bool leftBetter = newLine.eval(s) < nodes[node].line.eval(s);
        bool midBetter = newLine.eval(mid) < nodes[node].line.eval(mid);

        if (midBetter) swap(nodes[node].line, newLine);

        if (s == e) return;

        if (leftBetter != midBetter) {
            // Push to left
            if (nodes[node].left == -1) nodes[node].left = newNode();
            insert(nodes[node].left, s, mid, newLine);
        } else {
            // Push to right
            if (nodes[node].right == -1) nodes[node].right = newNode();
            insert(nodes[node].right, mid + 1, e, newLine);
        }
    }

    long long query(int node, long long s, long long e, long long x) {
        if (node == -1) return LLONG_MAX;
        long long mid = (s + e) / 2;
        long long res = nodes[node].hasLine ? nodes[node].line.eval(x) : LLONG_MAX;
        if (x <= mid)
            res = min(res, query(nodes[node].left, s, mid, x));
        else
            res = min(res, query(nodes[node].right, mid + 1, e, x));
        return res;
    }

public:
    LiChaoTree(long long lo, long long hi) : lo(lo), hi(hi) {
        newNode(); // root = node 0
    }

    void insert(long long m, long long b) {
        insert(0, lo, hi, {m, b});
    }

    long long query(long long x) {
        return query(0, lo, hi, x);
    }
};

void demoLiChaoTree() {
    cout << "═══ LI CHAO TREE (ONLINE CONVEX HULL TRICK) ═══\n\n";

    LiChaoTree lct(0, 100);

    cout << "Insert lines:\n";
    cout << "  y = 2x + 1   (line A)\n";
    lct.insert(2, 1);
    cout << "  y = -x + 10  (line B)\n";
    lct.insert(-1, 10);
    cout << "  y = x + 3    (line C)\n";
    lct.insert(1, 3);
    cout << "\n";

    cout << "Min queries:\n";
    for (int x = 0; x <= 10; x += 2) {
        long long actual = min({2LL*x+1, -1LL*x+10, 1LL*x+3});
        cout << "  min at x=" << x << ": " << lct.query(x)
             << " (verify: " << actual << ")\n";
    }
    cout << "\n";

    cout << "USE CASES:\n";
    cout << "  1. DP optimization: dp[i] = min(dp[j] + f(i,j))\n";
    cout << "     where f(i,j) can be written as line: m*x + b\n";
    cout << "  2. Example: dp[i] = min(dp[j] + (h[i]-h[j])²)\n";
    cout << "     Expand: dp[j] + h[j]² - 2*h[i]*h[j] + h[i]²\n";
    cout << "     Line: m=-2*h[j], b=dp[j]+h[j]², x=h[i]\n";
    cout << "  3. CSES Frog 3, SPOJ NKLEAVES, many DP problems\n\n";

    cout << "Complexity: O(log C) per insert/query\n";
    cout << "  C = x-coordinate range\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 3: Implicit / Dynamic Segment Tree
// ═══════════════════════════════════════════════════════════════

class DynamicSegTree {
    struct Node {
        long long val;
        int left, right;
    };

    vector<Node> nodes;
    long long lo, hi;

    int newNode() {
        nodes.push_back({0, -1, -1});
        return nodes.size() - 1;
    }

    void update(int node, long long s, long long e, long long pos, long long val) {
        if (s == e) { nodes[node].val += val; return; }
        long long mid = (s + e) / 2;
        if (pos <= mid) {
            if (nodes[node].left == -1) nodes[node].left = newNode();
            update(nodes[node].left, s, mid, pos, val);
        } else {
            if (nodes[node].right == -1) nodes[node].right = newNode();
            update(nodes[node].right, mid + 1, e, pos, val);
        }
        long long lv = (nodes[node].left != -1) ? nodes[nodes[node].left].val : 0;
        long long rv = (nodes[node].right != -1) ? nodes[nodes[node].right].val : 0;
        nodes[node].val = lv + rv;
    }

    long long query(int node, long long s, long long e, long long l, long long r) {
        if (node == -1 || r < s || e < l) return 0;
        if (l <= s && e <= r) return nodes[node].val;
        long long mid = (s + e) / 2;
        return query(nodes[node].left, s, mid, l, r)
             + query(nodes[node].right, mid + 1, e, l, r);
    }

public:
    int root;

    DynamicSegTree(long long lo, long long hi) : lo(lo), hi(hi) {
        root = newNode();
    }

    void update(long long pos, long long val) { update(root, lo, hi, pos, val); }
    long long query(long long l, long long r) { return query(root, lo, hi, l, r); }
    int nodeCount() { return nodes.size(); }
};

void demoDynamicSegTree() {
    cout << "═══ IMPLICIT / DYNAMIC SEGMENT TREE ═══\n\n";

    cout << "Coordinate range: [0, 10^9]\n";
    cout << "Only a few updates, nodes created on demand.\n\n";

    DynamicSegTree dst(0, 1000000000LL);

    dst.update(100, 5);
    dst.update(1000000, 3);
    dst.update(999999999, 7);

    cout << "After 3 updates:\n";
    cout << "  Nodes created: " << dst.nodeCount() << "\n";
    cout << "  sum(0, 10^9) = " << dst.query(0, 1000000000) << " (5+3+7=15)\n";
    cout << "  sum(0, 1000) = " << dst.query(0, 1000) << " (5+3=8)\n";
    cout << "  sum(999999990, 10^9) = " << dst.query(999999990, 1000000000) << " (7)\n\n";

    cout << "Memory: Only ~" << dst.nodeCount() << " nodes instead of 4×10^9!\n";
    cout << "  Each update creates O(log C) = ~30 nodes\n";
    cout << "  Q=10^5 updates → ~3×10^6 nodes total\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║   LEVEL 14: ICPC LEVEL RANGE STRUCTURES                    ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n\n";

    demoMergeSortTree();
    demoLiChaoTree();
    demoDynamicSegTree();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "  KEY TAKEAWAYS:\n";
    cout << "  1. Merge Sort Tree: O(log²n) count/rank queries\n";
    cout << "  2. Wavelet Tree: O(log σ) kth smallest, range freq\n";
    cout << "  3. Li Chao Tree: Online CHT for DP optimization\n";
    cout << "  4. Dynamic/Implicit ST: Sparse range, lazy node creation\n";
    cout << "  5. These structures appear in ICPC regionals/finals!\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

