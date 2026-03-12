/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║        LEVEL 10 — SEGMENT TREE + BINARY SEARCH (Walking on ST)                 ║
║        Find First ≥ X, Kth Order Statistics, Descending on ST                  ║
║        Author: Sarvan Yaduvanshi                                               ║
╚══════════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Walking on Segment Tree — Concept
 2. Find First Element ≥ X in Range
 3. Kth Order Statistics on Segment Tree
 4. Count Elements in Value Range
 5. Binary Search on Segment Tree
 6. Complete Dry Runs

═══════════════════════════════════════════════════════════════
SECTION 1: WALKING ON SEGMENT TREE — CONCEPT
═══════════════════════════════════════════════════════════════

"Walking" = Binary search WITHIN the segment tree.
Instead of doing binary search + separate query = O(log²n),
we combine them into a SINGLE traversal = O(log n).

IDEA: At each node, check the left child's aggregate.
  If the answer is in the left subtree, go left.
  Otherwise, go right (adjusting the search parameter).

═══════════════════════════════════════════════════════════════
SECTION 2: FIND FIRST ELEMENT ≥ X
═══════════════════════════════════════════════════════════════

PROBLEM: Given array a[], find the leftmost index i in [l, r]
         where a[i] ≥ x. (CSES Hotel Queries style)

APPROACH: Build a MAX segment tree.
  Walk: if max of left subtree ≥ x, answer is in left.
        Otherwise, answer is in right.

VISUALIZATION:
  a[] = {3, 1, 4, 1, 5, 9, 2, 6}
  Max ST:
              [9]
           /       \
        [4]         [9]
       /   \       /   \
     [3]  [4]   [9]   [6]
     /\   /\    /\    /\
    3  1 4  1  5  9  2  6

  Query: First element ≥ 5 in [0, 7]:
    Node [9] (root): max ≥ 5 → check left
      Node [4]: max = 4 < 5 → NOT in left
      → Go right: Node [9]: max ≥ 5 → check left
        Node [9] (covering [4,5]): max = 9 ≥ 5 → check left
          Node [5]: leaf, a[4] = 5 ≥ 5 → FOUND at index 4!

DRY RUN:
  find_first_ge(1, 0, 7, 0, 7, 5)
  Node 1: max=9 ≥ 5, range [0,7] overlaps [0,7]
    Check left child (node 2, [0,3]): max=4 < 5 → skip left
    Go to right child (node 3, [4,7]): max=9 ≥ 5
      Check left child (node 6, [4,5]): max=9 ≥ 5
        Check left child (node 12, [4,4]): max=5 ≥ 5 → FOUND at 4!
  Answer: index 4 ✓

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
// IMPLEMENTATION 1: Walking on Max Segment Tree
// ═══════════════════════════════════════════════════════════════

class WalkingSegTree {
    int n;
    vector<long long> tree;

    void build(const vector<int>& a, int node, int s, int e) {
        if (s == e) { tree[node] = a[s]; return; }
        int mid = (s + e) / 2;
        build(a, 2*node, s, mid);
        build(a, 2*node+1, mid+1, e);
        tree[node] = max(tree[2*node], tree[2*node+1]);
    }

    void update(int node, int s, int e, int idx, long long val) {
        if (s == e) { tree[node] = val; return; }
        int mid = (s + e) / 2;
        if (idx <= mid) update(2*node, s, mid, idx, val);
        else update(2*node+1, mid+1, e, idx, val);
        tree[node] = max(tree[2*node], tree[2*node+1]);
    }

    // Find first index ≥ x in range [l, r], starting search from left
    int findFirstGE(int node, int s, int e, int l, int r, long long x) {
        if (r < s || e < l || tree[node] < x) return -1; // No valid element
        if (s == e) return s; // Found!
        int mid = (s + e) / 2;
        // Try left first (we want FIRST/leftmost)
        int res = findFirstGE(2*node, s, mid, l, r, x);
        if (res != -1) return res;
        return findFirstGE(2*node+1, mid+1, e, l, r, x);
    }

    // Find kth one (assuming tree stores 0/1 counts)
    int findKth(int node, int s, int e, int k) {
        if (s == e) return s;
        int mid = (s + e) / 2;
        if (tree[2*node] >= k)
            return findKth(2*node, s, mid, k);
        else
            return findKth(2*node+1, mid+1, e, k - tree[2*node]);
    }

public:
    WalkingSegTree(const vector<int>& a) : n(a.size()), tree(4 * a.size()) {
        build(a, 1, 0, n-1);
    }

    void update(int idx, long long val) { update(1, 0, n-1, idx, val); }

    int findFirstGE(int l, int r, long long x) {
        return findFirstGE(1, 0, n-1, l, r, x);
    }

    int findKth(int k) { return findKth(1, 0, n-1, k); }

    long long getMax(int l, int r) {
        // Quick max query
        function<long long(int, int, int, int, int)> query = [&](int node, int s, int e, int l, int r) -> long long {
            if (r < s || e < l) return LLONG_MIN;
            if (l <= s && e <= r) return tree[node];
            int mid = (s + e) / 2;
            return max(query(2*node, s, mid, l, r), query(2*node+1, mid+1, e, l, r));
        };
        return query(1, 0, n-1, l, r);
    }
};

void demoFindFirstGE() {
    cout << "═══ FIND FIRST ELEMENT ≥ X (WALKING ON ST) ═══\n\n";

    vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
    cout << "Array: ";
    for (int i = 0; i < (int)a.size(); i++) cout << "[" << i << "]=" << a[i] << " ";
    cout << "\n\n";

    WalkingSegTree st(a);

    cout << "Queries:\n";
    auto query = [&](int l, int r, int x) {
        int idx = st.findFirstGE(l, r, x);
        cout << "  First ≥ " << x << " in [" << l << "," << r << "] = ";
        if (idx == -1) cout << "NOT FOUND\n";
        else cout << "index " << idx << " (a[" << idx << "]=" << a[idx] << ")\n";
    };

    query(0, 7, 5);  // First ≥ 5 → index 4 (a[4]=5)
    query(0, 7, 7);  // First ≥ 7 → index 5 (a[5]=9)
    query(0, 3, 3);  // First ≥ 3 in [0,3] → index 0 (a[0]=3)
    query(0, 3, 5);  // First ≥ 5 in [0,3] → NOT FOUND
    query(6, 7, 3);  // First ≥ 3 in [6,7] → index 7 (a[7]=6)
    cout << "\n";

    cout << "DRY RUN — First ≥ 5 in [0, 7]:\n";
    cout << "  Root: max=9 ≥ 5 ✓\n";
    cout << "  ├─ Left [0,3]: max=4 < 5 → skip\n";
    cout << "  └─ Right [4,7]: max=9 ≥ 5 ✓\n";
    cout << "     ├─ Left [4,5]: max=9 ≥ 5 ✓\n";
    cout << "     │  ├─ Left [4,4]: a[4]=5 ≥ 5 → FOUND index 4! ✓\n";
    cout << "  Total: O(log n) steps\n\n";
}

// ═══════════════════════════════════════════════════════════════
// DEMO 2: Kth Order Statistics (Hotel Queries / Josephus)
// ═══════════════════════════════════════════════════════════════

void demoKthElement() {
    cout << "═══ KTH ORDER STATISTICS ON SEGMENT TREE ═══\n\n";

    cout << "PROBLEM: Maintain set of active elements, find kth active.\n";
    cout << "  Used in: CSES Hotel Queries, Josephus Problem\n\n";

    // Count ST: each leaf = 1 if active, 0 if not
    int n = 8;
    vector<int> a(n, 1); // All active initially

    // Use sum segment tree for counting
    vector<long long> tree(4 * n, 0);

    function<void(int, int, int)> build = [&](int node, int s, int e) {
        if (s == e) { tree[node] = a[s]; return; }
        int mid = (s + e) / 2;
        build(2*node, s, mid);
        build(2*node+1, mid+1, e);
        tree[node] = tree[2*node] + tree[2*node+1];
    };

    function<void(int, int, int, int, long long)> update = [&](int node, int s, int e, int idx, long long val) {
        if (s == e) { tree[node] = val; return; }
        int mid = (s + e) / 2;
        if (idx <= mid) update(2*node, s, mid, idx, val);
        else update(2*node+1, mid+1, e, idx, val);
        tree[node] = tree[2*node] + tree[2*node+1];
    };

    // Find kth active element (1-indexed k)
    function<int(int, int, int, int)> findKth = [&](int node, int s, int e, int k) -> int {
        if (s == e) return s;
        int mid = (s + e) / 2;
        if (tree[2*node] >= k)
            return findKth(2*node, s, mid, k);
        else
            return findKth(2*node+1, mid+1, e, k - tree[2*node]);
    };

    build(1, 0, n-1);

    cout << "8 active elements: {0,1,2,3,4,5,6,7}\n\n";
    cout << "Find 3rd active: index " << findKth(1, 0, n-1, 3) << " (→ 2)\n";
    cout << "Find 5th active: index " << findKth(1, 0, n-1, 5) << " (→ 4)\n\n";

    cout << "Deactivate index 2 and 4:\n";
    update(1, 0, n-1, 2, 0);
    update(1, 0, n-1, 4, 0);
    cout << "Active: {0,1,_,3,_,5,6,7}\n";
    cout << "Find 3rd active: index " << findKth(1, 0, n-1, 3) << " (→ 3)\n";
    cout << "Find 5th active: index " << findKth(1, 0, n-1, 5) << " (→ 6)\n\n";

    cout << "DRY RUN — findKth(k=3) after removals:\n";
    cout << "  Active: {0,1,_,3,_,5,6,7}, tree sums:\n";
    cout << "  Root sum=6, left sum=2, right sum=4\n";
    cout << "  k=3 > left_sum=2 → go right, k=3-2=1\n";
    cout << "    Left[4,5] sum=1, Right[6,7] sum=2\n";
    cout << "    k=1 ≤ 1 → go left\n";
    cout << "      Left[4] sum=0, Right[5] sum=1\n";
    cout << "      k=1 > 0 → go right, k=1-0=1\n";
    cout << "        Leaf [5]: return 5? Wait...\n";
    cout << "  Actually after removing 2,4: active are 0,1,3,5,6,7\n";
    cout << "  3rd active = index 3 ✓\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║   LEVEL 10: SEGMENT TREE + BINARY SEARCH (WALKING)         ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n\n";

    demoFindFirstGE();
    demoKthElement();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "  KEY TAKEAWAYS:\n";
    cout << "  1. Walking = binary search INSIDE the segment tree\n";
    cout << "  2. O(log n) instead of O(log²n) for BS + query\n";
    cout << "  3. Find First ≥ X: check left first, then right\n";
    cout << "  4. Kth element: compare left count with k\n";
    cout << "  5. Used in Hotel Queries, Josephus, List Removals\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

