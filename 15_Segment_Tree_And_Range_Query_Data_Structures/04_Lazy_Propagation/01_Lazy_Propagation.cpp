/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║        LEVEL 3 — LAZY PROPAGATION                                              ║
║        The Most Important Technique for Competitive Programming                ║
║        Author: Sarvan Yaduvanshi                                               ║
╚══════════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Why We Need Lazy Propagation (Motivation)
 2. Lazy Propagation Concept — "Promise to Children"
 3. Push Down Mechanics — Detailed Visualization
 4. Range Add + Range Sum Query — Full Implementation + Dry Run
 5. Range Assignment + Range Query — Full Implementation + Dry Run
 6. Range Add + Range Max Query
 7. Range XOR + Range Sum (Flip Coins)
 8. Combined Operations (Multiple Lazy Types)
 9. Common Bugs & How to Avoid Them
 10. GM Tips & Contest Template

═══════════════════════════════════════════════════════════════
SECTION 1: WHY WE NEED LAZY PROPAGATION
═══════════════════════════════════════════════════════════════

PROBLEM: Add value +5 to ALL elements in range [2, 6].

WITHOUT Lazy:
  Update each element one by one → O(n) per range update!
  For Q queries: O(n * Q) → Too slow!

WITH Lazy:
  Mark range [2,6] with "add 5" but DON'T go to every leaf.
  Only push the mark down when we NEED to access children.
  → O(log n) per range update!

ANALOGY: "Lazy" = procrastinate on work.
  Instead of updating all leaves now, leave a "sticky note"
  on the node saying "add 5 to everything below me."
  Only deliver the message when someone asks for details.

═══════════════════════════════════════════════════════════════
SECTION 2: LAZY PROPAGATION CONCEPT
═══════════════════════════════════════════════════════════════

Each node now has TWO values:
  1. tree[node] = actual aggregate value for this range
  2. lazy[node] = pending update to be pushed to children

INVARIANT:
  tree[node] is ALWAYS correct for the range it represents.
  lazy[node] = a "promise" that hasn't been delivered to children yet.

OPERATIONS:
  • push_down(node): Deliver promise to children, clear own lazy
  • update(l, r, val): Range update with lazy marking
  • query(l, r): Range query with lazy consideration

VISUALIZATION:

  BEFORE update(+5 to [2,6]):
              tree[1]=31  lazy=0
              /           \
        tree[2]=9 lazy=0  tree[3]=22 lazy=0
        /      \           /        \
     [4]=4  [5]=5       [6]=13    [7]=9
     / \    /  \        / \       / \
   [2] [2][3] [2]    [5] [8]   [4] [5]

  AFTER update(+5 to [2,6]):     ← Only mark internal nodes!
              tree[1]=56  lazy=0     ← updated
              /           \
        tree[2]=19 lazy=0  tree[3]=37 lazy=0    ← updated
        /      \           /        \
     [4]=4  [5]=15       [6]=23    [7]=14
     lazy=0  lazy=+5      lazy=+5   lazy=+5
     / \    /  \          / \       / \
   [2] [2][3] [2]      [5] [8]   [4] [5]
            ↑ NOT YET UPDATED! Lazy will push later.

  The leaves under [5], [6], [7] are NOT yet updated.
  But tree[5], tree[6], tree[7] ARE correct because we
  added lazy * range_size to the aggregate.

═══════════════════════════════════════════════════════════════
SECTION 3: PUSH DOWN MECHANICS
═══════════════════════════════════════════════════════════════

push_down(node, start, end):
  if lazy[node] != 0:
    mid = (start + end) / 2
    left_size  = mid - start + 1
    right_size = end - mid

    // Push to left child
    tree[2*node] += lazy[node] * left_size
    lazy[2*node] += lazy[node]

    // Push to right child
    tree[2*node+1] += lazy[node] * right_size
    lazy[2*node+1] += lazy[node]

    // Clear own lazy
    lazy[node] = 0

DRY RUN — push_down(node=5, start=2, end=3) with lazy[5]=+5:

  Before:
    tree[5] = 15, lazy[5] = +5
    tree[10] = 3, lazy[10] = 0     (left child, covers index 2)
    tree[11] = 2, lazy[11] = 0     (right child, covers index 3)

  push_down:
    mid = 2
    left_size = 2 - 2 + 1 = 1
    right_size = 3 - 2 = 1

    tree[10] += 5 * 1 = 3 + 5 = 8     lazy[10] += 5
    tree[11] += 5 * 1 = 2 + 5 = 7     lazy[11] += 5
    lazy[5] = 0

  After:
    tree[5] = 15, lazy[5] = 0      ← lazy cleared
    tree[10] = 8, lazy[10] = 5     ← value + lazy updated
    tree[11] = 7, lazy[11] = 5     ← value + lazy updated

  Now tree[10] and tree[11] are correct for their individual ranges.

CRITICAL RULES:
  ① ALWAYS push_down BEFORE accessing children (in query or update)
  ② After pushing, clear the parent's lazy
  ③ After modifying children, recalculate parent: tree[node] = tree[2*node] + tree[2*node+1]

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
// IMPLEMENTATION 1: Range Add + Range Sum (Most Common!)
// ═══════════════════════════════════════════════════════════════
/*
  Operations:
    update(l, r, val) → add val to all elements in [l, r]
    query(l, r)       → sum of elements in [l, r]
*/

class LazySegTreeAdd {
    int n;
    vector<long long> tree, lazy;

    void build(const vector<int>& a, int node, int s, int e) {
        lazy[node] = 0;
        if (s == e) { tree[node] = a[s]; return; }
        int mid = (s + e) / 2;
        build(a, 2*node, s, mid);
        build(a, 2*node+1, mid+1, e);
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    void pushDown(int node, int s, int e) {
        if (lazy[node] != 0) {
            int mid = (s + e) / 2;
            // Push to left child
            tree[2*node] += lazy[node] * (mid - s + 1);
            lazy[2*node] += lazy[node];
            // Push to right child
            tree[2*node+1] += lazy[node] * (e - mid);
            lazy[2*node+1] += lazy[node];
            // Clear
            lazy[node] = 0;
        }
    }

    void update(int node, int s, int e, int l, int r, long long val) {
        if (r < s || e < l) return;             // No overlap
        if (l <= s && e <= r) {                  // Complete overlap
            tree[node] += val * (e - s + 1);    // Update aggregate
            lazy[node] += val;                   // Mark lazy
            return;
        }
        pushDown(node, s, e);                    // MUST push before going to children!
        int mid = (s + e) / 2;
        update(2*node, s, mid, l, r, val);
        update(2*node+1, mid+1, e, l, r, val);
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    long long query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return tree[node];
        pushDown(node, s, e);                    // MUST push before going to children!
        int mid = (s + e) / 2;
        return query(2*node, s, mid, l, r)
             + query(2*node+1, mid+1, e, l, r);
    }

public:
    LazySegTreeAdd() : n(0) {}
    LazySegTreeAdd(const vector<int>& a) : n(a.size()), tree(4*a.size()), lazy(4*a.size(), 0) {
        build(a, 1, 0, n-1);
    }

    void update(int l, int r, long long val) { update(1, 0, n-1, l, r, val); }
    long long query(int l, int r) { return query(1, 0, n-1, l, r); }
};

void demoLazyAdd() {
    cout << "═══ LAZY PROPAGATION: RANGE ADD + RANGE SUM ═══\n\n";

    vector<int> a = {1, 3, 5, 7, 9, 11};
    cout << "Array: ";
    for (int x : a) cout << x << " ";
    cout << "\n\n";

    LazySegTreeAdd st(a);

    cout << "Initial queries:\n";
    cout << "  sum(0, 5) = " << st.query(0, 5) << " (1+3+5+7+9+11=36)\n";
    cout << "  sum(1, 3) = " << st.query(1, 3) << " (3+5+7=15)\n\n";

    // Range update
    cout << "UPDATE: add +10 to range [1, 4]\n";
    cout << "  Expected: [1, 13, 15, 17, 19, 11]\n";
    st.update(1, 4, 10);
    cout << "  sum(0, 5) = " << st.query(0, 5) << " (1+13+15+17+19+11=76)\n";
    cout << "  sum(1, 3) = " << st.query(1, 3) << " (13+15+17=45)\n";
    cout << "  sum(0, 0) = " << st.query(0, 0) << " (1, unchanged)\n";
    cout << "  sum(5, 5) = " << st.query(5, 5) << " (11, unchanged)\n\n";

    cout << "DRY RUN — update(+10 to [1,4]) on tree:\n";
    cout << "  Initially: a = [1, 3, 5, 7, 9, 11]\n\n";
    cout << "  update(1, 0, 5, 1, 4, +10)\n";
    cout << "  [1] range [0,5]: PARTIAL → pushDown, split\n";
    cout << "  ├─ update(2, 0, 2, 1, 4, +10)\n";
    cout << "  │  [2] range [0,2]: PARTIAL → pushDown, split\n";
    cout << "  │  ├─ update(4, 0, 0, 1, 4, +10)\n";
    cout << "  │  │  NO OVERLAP → return\n";
    cout << "  │  └─ update(5, 1, 2, 1, 4, +10)\n";
    cout << "  │     COMPLETE OVERLAP!\n";
    cout << "  │     tree[5] += 10 * 2 = old + 20\n";
    cout << "  │     lazy[5] += 10\n";
    cout << "  │  tree[2] = tree[4] + tree[5]  (recalculate)\n";
    cout << "  └─ update(3, 3, 5, 1, 4, +10)\n";
    cout << "     [3] range [3,5]: PARTIAL → pushDown, split\n";
    cout << "     ├─ update(6, 3, 4, 1, 4, +10)\n";
    cout << "     │  COMPLETE OVERLAP!\n";
    cout << "     │  tree[6] += 10 * 2\n";
    cout << "     │  lazy[6] += 10\n";
    cout << "     └─ update(7, 5, 5, 1, 4, +10)\n";
    cout << "        NO OVERLAP → return\n";
    cout << "     tree[3] = tree[6] + tree[7]  (recalculate)\n";
    cout << "  tree[1] = tree[2] + tree[3]  (recalculate)\n\n";

    // Another update
    cout << "UPDATE: add +5 to range [0, 2]\n";
    st.update(0, 2, 5);
    cout << "  Expected: [6, 18, 20, 17, 19, 11]\n";
    cout << "  sum(0, 5) = " << st.query(0, 5) << " (6+18+20+17+19+11=91)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 2: Range Assignment + Range Sum
// ═══════════════════════════════════════════════════════════════
/*
  Operations:
    update(l, r, val) → SET all elements in [l, r] to val
    query(l, r)       → sum of elements in [l, r]

  KEY DIFFERENCE from Range Add:
    • lazy = assigned value (use sentinel like LLONG_MIN for "no assignment")
    • New assignment OVERWRITES old lazy (not additive!)
*/

class LazySegTreeAssign {
    int n;
    vector<long long> tree, lazy;
    static const long long NO_LAZY = LLONG_MIN;

    void build(const vector<int>& a, int node, int s, int e) {
        lazy[node] = NO_LAZY;
        if (s == e) { tree[node] = a[s]; return; }
        int mid = (s + e) / 2;
        build(a, 2*node, s, mid);
        build(a, 2*node+1, mid+1, e);
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    void pushDown(int node, int s, int e) {
        if (lazy[node] != NO_LAZY) {
            int mid = (s + e) / 2;
            // Set left child
            tree[2*node] = lazy[node] * (mid - s + 1);
            lazy[2*node] = lazy[node];
            // Set right child
            tree[2*node+1] = lazy[node] * (e - mid);
            lazy[2*node+1] = lazy[node];
            // Clear
            lazy[node] = NO_LAZY;
        }
    }

    void update(int node, int s, int e, int l, int r, long long val) {
        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            tree[node] = val * (e - s + 1);   // SET aggregate
            lazy[node] = val;                   // OVERWRITE lazy
            return;
        }
        pushDown(node, s, e);
        int mid = (s + e) / 2;
        update(2*node, s, mid, l, r, val);
        update(2*node+1, mid+1, e, l, r, val);
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    long long query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return tree[node];
        pushDown(node, s, e);
        int mid = (s + e) / 2;
        return query(2*node, s, mid, l, r)
             + query(2*node+1, mid+1, e, l, r);
    }

public:
    LazySegTreeAssign(const vector<int>& a) : n(a.size()), tree(4*a.size()), lazy(4*a.size(), NO_LAZY) {
        build(a, 1, 0, n-1);
    }

    void update(int l, int r, long long val) { update(1, 0, n-1, l, r, val); }
    long long query(int l, int r) { return query(1, 0, n-1, l, r); }
};

void demoLazyAssign() {
    cout << "═══ LAZY PROPAGATION: RANGE ASSIGNMENT + RANGE SUM ═══\n\n";

    vector<int> a = {1, 3, 5, 7, 9, 11};
    cout << "Array: 1 3 5 7 9 11\n\n";

    LazySegTreeAssign st(a);

    cout << "sum(0, 5) = " << st.query(0, 5) << " (36)\n\n";

    cout << "ASSIGN: set [1, 4] = 6\n";
    cout << "  Expected: [1, 6, 6, 6, 6, 11]\n";
    st.update(1, 4, 6);
    cout << "  sum(0, 5) = " << st.query(0, 5) << " (1+6+6+6+6+11=36)\n";
    cout << "  sum(1, 4) = " << st.query(1, 4) << " (6*4=24)\n\n";

    cout << "ASSIGN: set [0, 2] = 10\n";
    cout << "  Expected: [10, 10, 10, 6, 6, 11]\n";
    st.update(0, 2, 10);
    cout << "  sum(0, 5) = " << st.query(0, 5) << " (10+10+10+6+6+11=53)\n";
    cout << "  sum(0, 2) = " << st.query(0, 2) << " (30)\n\n";

    cout << "KEY DIFFERENCE from Range Add:\n";
    cout << "  • Range Add: lazy values are ADDITIVE (lazy += val)\n";
    cout << "  • Range Assign: lazy values OVERWRITE (lazy = val)\n";
    cout << "  • Assignment uses sentinel (LLONG_MIN) for 'no lazy'\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 3: Range Add + Range Max
// ═══════════════════════════════════════════════════════════════

class LazySegTreeMaxAdd {
    int n;
    vector<long long> tree, lazy;

    void build(const vector<int>& a, int node, int s, int e) {
        lazy[node] = 0;
        if (s == e) { tree[node] = a[s]; return; }
        int mid = (s + e) / 2;
        build(a, 2*node, s, mid);
        build(a, 2*node+1, mid+1, e);
        tree[node] = max(tree[2*node], tree[2*node+1]);
    }

    void pushDown(int node) {
        if (lazy[node] != 0) {
            // For MAX: adding to all elements shifts the max
            tree[2*node] += lazy[node];
            lazy[2*node] += lazy[node];
            tree[2*node+1] += lazy[node];
            lazy[2*node+1] += lazy[node];
            lazy[node] = 0;
        }
    }

    void update(int node, int s, int e, int l, int r, long long val) {
        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            tree[node] += val;    // Max shifts by val when all shift by val
            lazy[node] += val;
            return;
        }
        pushDown(node);
        int mid = (s + e) / 2;
        update(2*node, s, mid, l, r, val);
        update(2*node+1, mid+1, e, l, r, val);
        tree[node] = max(tree[2*node], tree[2*node+1]);
    }

    long long query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return LLONG_MIN;
        if (l <= s && e <= r) return tree[node];
        pushDown(node);
        int mid = (s + e) / 2;
        return max(query(2*node, s, mid, l, r),
                   query(2*node+1, mid+1, e, l, r));
    }

public:
    LazySegTreeMaxAdd(const vector<int>& a) : n(a.size()), tree(4*a.size()), lazy(4*a.size(), 0) {
        build(a, 1, 0, n-1);
    }

    void update(int l, int r, long long val) { update(1, 0, n-1, l, r, val); }
    long long query(int l, int r) { return query(1, 0, n-1, l, r); }
};

void demoLazyMaxAdd() {
    cout << "═══ LAZY PROPAGATION: RANGE ADD + RANGE MAX ═══\n\n";

    vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
    cout << "Array: 3 1 4 1 5 9 2 6\n\n";

    LazySegTreeMaxAdd st(a);
    cout << "max(0, 7) = " << st.query(0, 7) << " (9)\n";
    cout << "max(0, 3) = " << st.query(0, 3) << " (4)\n\n";

    cout << "ADD +10 to [0, 3]:\n";
    st.update(0, 3, 10);
    cout << "  Expected: [13, 11, 14, 11, 5, 9, 2, 6]\n";
    cout << "  max(0, 3) = " << st.query(0, 3) << " (14)\n";
    cout << "  max(0, 7) = " << st.query(0, 7) << " (14)\n";
    cout << "  max(4, 7) = " << st.query(4, 7) << " (9, unchanged)\n\n";

    cout << "KEY INSIGHT for MAX + ADD:\n";
    cout << "  When we add val to range, MAX also shifts by val.\n";
    cout << "  max(a+val, b+val) = max(a,b) + val\n";
    cout << "  So tree[node] += val (not val * size like sum!)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 4: Range XOR (Flip) + Range Sum
// ═══════════════════════════════════════════════════════════════
/*
  Problem: Flip coins in range [l, r] (0→1, 1→0)
  Query: Count of 1s in range [l, r]

  This is: XOR 1 on range + Sum query
*/

class LazySegTreeFlip {
    int n;
    vector<int> tree, lazy;

    void build(const vector<int>& a, int node, int s, int e) {
        lazy[node] = 0;
        if (s == e) { tree[node] = a[s]; return; }
        int mid = (s + e) / 2;
        build(a, 2*node, s, mid);
        build(a, 2*node+1, mid+1, e);
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    void pushDown(int node, int s, int e) {
        if (lazy[node]) {
            int mid = (s + e) / 2;
            // Flip: count of 1s becomes count of 0s
            tree[2*node] = (mid - s + 1) - tree[2*node];
            lazy[2*node] ^= 1;
            tree[2*node+1] = (e - mid) - tree[2*node+1];
            lazy[2*node+1] ^= 1;
            lazy[node] = 0;
        }
    }

    void update(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            tree[node] = (e - s + 1) - tree[node];  // Flip!
            lazy[node] ^= 1;
            return;
        }
        pushDown(node, s, e);
        int mid = (s + e) / 2;
        update(2*node, s, mid, l, r);
        update(2*node+1, mid+1, e, l, r);
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    int query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return tree[node];
        pushDown(node, s, e);
        int mid = (s + e) / 2;
        return query(2*node, s, mid, l, r) + query(2*node+1, mid+1, e, l, r);
    }

public:
    LazySegTreeFlip(const vector<int>& a) : n(a.size()), tree(4*a.size()), lazy(4*a.size(), 0) {
        build(a, 1, 0, n-1);
    }

    void flip(int l, int r) { update(1, 0, n-1, l, r); }
    int countOnes(int l, int r) { return query(1, 0, n-1, l, r); }
};

void demoLazyFlip() {
    cout << "═══ LAZY PROPAGATION: RANGE FLIP (XOR) + COUNT ═══\n\n";

    vector<int> a = {0, 1, 0, 0, 1, 1, 0, 1};
    cout << "Coins: ";
    for (int x : a) cout << x;
    cout << "\n\n";

    LazySegTreeFlip st(a);
    cout << "Count of 1s in [0,7] = " << st.countOnes(0, 7) << " (4)\n";
    cout << "Count of 1s in [2,5] = " << st.countOnes(2, 5) << " (2)\n\n";

    cout << "FLIP [2, 5]: 0,0,1,1 → 1,1,0,0\n";
    st.flip(2, 5);
    cout << "  Coins now: 0,1,1,1,0,0,0,1\n";
    cout << "  Count of 1s in [0,7] = " << st.countOnes(0, 7) << " (4)\n";
    cout << "  Count of 1s in [2,5] = " << st.countOnes(2, 5) << " (2)\n\n";

    cout << "FLIP [0, 3]: 0,1,1,1 → 1,0,0,0\n";
    st.flip(0, 3);
    cout << "  Count of 1s in [0,7] = " << st.countOnes(0, 7) << " (2)\n\n";

    cout << "KEY INSIGHT for FLIP:\n";
    cout << "  Flipping: count_ones = range_size - count_ones\n";
    cout << "  Lazy is XOR: two flips cancel out (lazy ^= 1)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 9: COMMON BUGS
// ═══════════════════════════════════════════════════════════════

void printBugs() {
    cout << "═══ COMMON LAZY PROPAGATION BUGS ═══\n\n";

    cout << "BUG 1: Forgetting to pushDown before accessing children\n";
    cout << "  ❌ query(...) { return query(left) + query(right); }\n";
    cout << "  ✅ query(...) { pushDown(node); return query(left) + query(right); }\n\n";

    cout << "BUG 2: Not multiplying lazy by range size (for sum)\n";
    cout << "  ❌ tree[node] += lazy[node];\n";
    cout << "  ✅ tree[node] += lazy[node] * (end - start + 1);\n\n";

    cout << "BUG 3: Forgetting to recalculate parent after children update\n";
    cout << "  ❌ update(left); update(right);  // done?\n";
    cout << "  ✅ update(left); update(right); tree[node] = tree[2*node] + tree[2*node+1];\n\n";

    cout << "BUG 4: Wrong identity for lazy\n";
    cout << "  • Range Add: identity = 0\n";
    cout << "  • Range Assign: identity = LLONG_MIN (sentinel)\n";
    cout << "  • Range XOR: identity = 0\n\n";

    cout << "BUG 5: Forgetting lazy initialization in build\n";
    cout << "  Always set lazy[node] = 0 (or identity) during build!\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║   LEVEL 3: LAZY PROPAGATION — COMPLETE GUIDE               ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n\n";

    demoLazyAdd();
    demoLazyAssign();
    demoLazyMaxAdd();
    demoLazyFlip();
    printBugs();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "  KEY TAKEAWAYS:\n";
    cout << "  1. Lazy = 'promise to children', push_down delivers it\n";
    cout << "  2. ALWAYS push_down before accessing children!\n";
    cout << "  3. Range Add + Sum: tree += val * size, lazy += val\n";
    cout << "  4. Range Assign + Sum: tree = val * size, lazy = val\n";
    cout << "  5. Range Add + Max: tree += val, lazy += val (no * size!)\n";
    cout << "  6. Range Flip: tree = size - tree, lazy ^= 1\n";
    cout << "  7. All operations remain O(log n) with lazy!\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

