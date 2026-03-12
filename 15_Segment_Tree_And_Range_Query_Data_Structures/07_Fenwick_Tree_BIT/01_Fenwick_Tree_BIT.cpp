/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║        LEVEL 6 — FENWICK TREE (BINARY INDEXED TREE)                            ║
║        The Simplest Range Query Structure for Competitive Programming           ║
║        Author: Sarvan Yaduvanshi                                               ║
╚══════════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. What is a Fenwick Tree? (Concept + Why It's Brilliant)
 2. The lowbit Trick: i & (-i)
 3. Point Update — O(log n)
 4. Prefix Sum Query — O(log n)
 5. Range Sum Query — O(log n)
 6. O(n) Build Technique
 7. BIT vs Segment Tree Comparison
 8. BIT Optimizations & Tricks
 9. Complete Dry Run

═══════════════════════════════════════════════════════════════
SECTION 1: WHAT IS A FENWICK TREE?
═══════════════════════════════════════════════════════════════

A Fenwick Tree (Binary Indexed Tree, BIT) is a data structure
that supports:
  • Point update: a[i] += val  → O(log n)
  • Prefix sum:   sum(1..i)    → O(log n)
  • Range sum:    sum(l..r)    → O(log n) via prefix difference

It uses only O(n) space (a single array!) and is MUCH simpler
to code than a segment tree. The constant factor is also smaller.

KEY IDEA: Each index i is "responsible" for a range of elements.
The range length = lowbit(i) = i & (-i).

BIT[i] stores the sum of elements from [i - lowbit(i) + 1, i].

VISUALIZATION (1-indexed, n=8):

  Index:    1    2    3    4    5    6    7    8
  lowbit:   1    2    1    4    1    2    1    8
  Range:  [1,1][1,2][3,3][1,4][5,5][5,6][7,7][1,8]

  Responsibility tree:
  BIT[8] covers [1..8] ─────────────────────────┐
  BIT[4] covers [1..4] ─────────┐               │
  BIT[2] covers [1..2] ──┐      │               │
  BIT[1] covers [1..1]   │      │               │
                          │      │               │
  BIT[6] covers [5..6] ──┤      │               │
  BIT[5] covers [5..5]   │      │               │
                          │      │               │
  BIT[3] covers [3..3]   │      │               │
  BIT[7] covers [7..7]   │      │               │

  Array:  a[] = [_, 3, 1, 4, 1, 5, 9, 2, 6]  (1-indexed)
  BIT:         [_, 3, 4, 4, 8, 5, 14, 2, 31]

  BIT[1] = a[1] = 3           (lowbit=1, range=[1,1])
  BIT[2] = a[1]+a[2] = 4      (lowbit=2, range=[1,2])
  BIT[3] = a[3] = 4           (lowbit=1, range=[3,3])
  BIT[4] = a[1]+..+a[4] = 9   Wait, let me recalculate:
    a = [3, 1, 4, 1, 5, 9, 2, 6]
    BIT[1] = a[1] = 3
    BIT[2] = a[1]+a[2] = 3+1 = 4
    BIT[3] = a[3] = 4
    BIT[4] = a[1]+a[2]+a[3]+a[4] = 3+1+4+1 = 9
    BIT[5] = a[5] = 5
    BIT[6] = a[5]+a[6] = 5+9 = 14
    BIT[7] = a[7] = 2
    BIT[8] = a[1]+..+a[8] = 31

═══════════════════════════════════════════════════════════════
SECTION 2: THE LOWBIT TRICK
═══════════════════════════════════════════════════════════════

lowbit(i) = i & (-i) = lowest set bit of i

HOW IT WORKS:
  i   = 12 = 0000 1100
  -i  = -12 = 1111 0100  (two's complement)
  i&-i =      0000 0100 = 4

  i   = 6  = 0110
  -i  = -6 = 1010
  i&-i =     0010 = 2

  i   = 7  = 0111
  -i  = -7 = 1001
  i&-i =     0001 = 1

WHY IS THIS USEFUL?
  • Query (go DOWN): subtract lowbit to visit all contributing ranges
    sum(7) = BIT[7] + BIT[6] + BIT[4]
             7→7-1=6→6-2=4→4-4=0 (stop)

  • Update (go UP): add lowbit to propagate changes
    update(3) affects BIT[3], BIT[4], BIT[8]
              3→3+1=4→4+4=8→8+8=16 (stop, > n)

═══════════════════════════════════════════════════════════════
SECTION 3-5: UPDATE AND QUERY — DRY RUNS
═══════════════════════════════════════════════════════════════

QUERY — prefix_sum(6):
  Start at i=6
  Step 1: res += BIT[6] = 14    (6 in binary: 110)
  Step 2: i -= lowbit(6) = 6-2 = 4
  Step 3: res += BIT[4] = 14+9 = 23  (4 in binary: 100)
  Step 4: i -= lowbit(4) = 4-4 = 0
  Step 5: i=0, STOP
  Answer: 23
  Verify: 3+1+4+1+5+9 = 23 ✓

UPDATE — add +10 to index 3:
  Start at i=3
  Step 1: BIT[3] += 10    (3 in binary: 011)
  Step 2: i += lowbit(3) = 3+1 = 4
  Step 3: BIT[4] += 10    (4 in binary: 100)
  Step 4: i += lowbit(4) = 4+4 = 8
  Step 5: BIT[8] += 10    (8 in binary: 1000)
  Step 6: i += lowbit(8) = 8+8 = 16 > n, STOP

  Only 3 updates! Path: 3 → 4 → 8
  O(log n) operations.

═══════════════════════════════════════════════════════════════
SECTION 6: O(n) BUILD
═══════════════════════════════════════════════════════════════

NAIVE BUILD: Insert elements one by one → O(n log n)
SMART BUILD: O(n) using "propagation":

  for i = 1 to n:
    BIT[i] = a[i]
  for i = 1 to n:
    j = i + lowbit(i)
    if j <= n: BIT[j] += BIT[i]

DRY RUN for a[] = [_, 3, 1, 4, 1, 5, 9, 2, 6]:
  Initialize BIT = a = [_, 3, 1, 4, 1, 5, 9, 2, 6]

  i=1: j = 1+1 = 2    BIT[2] += BIT[1] → 1+3 = 4
  i=2: j = 2+2 = 4    BIT[4] += BIT[2] → 1+4 = 5
  i=3: j = 3+1 = 4    BIT[4] += BIT[3] → 5+4 = 9
  i=4: j = 4+4 = 8    BIT[8] += BIT[4] → 6+9 = 15
  i=5: j = 5+1 = 6    BIT[6] += BIT[5] → 9+5 = 14
  i=6: j = 6+2 = 8    BIT[8] += BIT[6] → 15+14 = 29
  i=7: j = 7+1 = 8    BIT[8] += BIT[7] → 29+2 = 31
  i=8: j = 8+8 = 16 > 8, skip

  Result: BIT = [_, 3, 4, 4, 9, 5, 14, 2, 31] ✓

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
// IMPLEMENTATION: Fenwick Tree (1-indexed)
// ═══════════════════════════════════════════════════════════════

class FenwickTree {
    int n;
    vector<long long> bit;

public:
    FenwickTree(int n) : n(n), bit(n + 1, 0) {}

    // Build from array in O(n)
    FenwickTree(const vector<int>& a) : n(a.size()), bit(a.size() + 1, 0) {
        for (int i = 1; i <= n; i++) bit[i] = a[i - 1];
        for (int i = 1; i <= n; i++) {
            int j = i + (i & (-i));
            if (j <= n) bit[j] += bit[i];
        }
    }

    // Point update: a[i] += delta (1-indexed)
    void update(int i, long long delta) {
        for (; i <= n; i += i & (-i))
            bit[i] += delta;
    }

    // Prefix sum: sum(1..i) (1-indexed)
    long long query(int i) {
        long long sum = 0;
        for (; i > 0; i -= i & (-i))
            sum += bit[i];
        return sum;
    }

    // Range sum: sum(l..r) (1-indexed)
    long long query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

void demoBIT() {
    cout << "═══ FENWICK TREE (BIT) — BASIC OPERATIONS ═══\n\n";

    vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = a.size();
    cout << "Array (1-indexed): ";
    for (int i = 0; i < n; i++) cout << "[" << i+1 << "]=" << a[i] << " ";
    cout << "\n\n";

    FenwickTree bit(a);

    // Prefix sum queries
    cout << "PREFIX SUM QUERIES:\n";
    for (int i = 1; i <= n; i++) {
        cout << "  sum(1.." << i << ") = " << bit.query(i) << "\n";
    }
    cout << "\n";

    // Range sum queries
    cout << "RANGE SUM QUERIES:\n";
    cout << "  sum(2, 5) = " << bit.query(2, 5) << " (1+4+1+5=11)\n";
    cout << "  sum(3, 7) = " << bit.query(3, 7) << " (4+1+5+9+2=21)\n";
    cout << "  sum(1, 8) = " << bit.query(1, 8) << " (31)\n";
    cout << "  sum(4, 4) = " << bit.query(4, 4) << " (1)\n\n";

    // DRY RUN
    cout << "DRY RUN — prefix_sum(6):\n";
    cout << "  i=6 (110₂): res += BIT[6]   (covers [5,6])\n";
    cout << "  i=6-2=4 (100₂): res += BIT[4]   (covers [1,4])\n";
    cout << "  i=4-4=0: STOP\n";
    cout << "  Result = BIT[6] + BIT[4] = " << bit.query(6) << "\n\n";

    // Update
    cout << "UPDATE: a[3] += 10\n";
    bit.update(3, 10);
    cout << "  sum(1, 8) = " << bit.query(1, 8) << " (was 31, now 41)\n";
    cout << "  sum(2, 5) = " << bit.query(2, 5) << " (was 11, now 21)\n";
    cout << "  sum(1, 2) = " << bit.query(1, 2) << " (4, unchanged)\n\n";

    cout << "DRY RUN — update(3, +10):\n";
    cout << "  i=3 (011₂): BIT[3] += 10\n";
    cout << "  i=3+1=4 (100₂): BIT[4] += 10\n";
    cout << "  i=4+4=8 (1000₂): BIT[8] += 10\n";
    cout << "  i=8+8=16 > 8: STOP\n";
    cout << "  Updated indices: 3, 4, 8\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION: Fenwick Tree (0-indexed version)
// ═══════════════════════════════════════════════════════════════

class FenwickTree0 {
    int n;
    vector<long long> bit;

public:
    FenwickTree0(int n) : n(n), bit(n, 0) {}

    void update(int i, long long delta) {
        for (; i < n; i |= (i + 1))
            bit[i] += delta;
    }

    long long query(int i) {
        long long sum = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1)
            sum += bit[i];
        return sum;
    }

    long long query(int l, int r) {
        return query(r) - (l > 0 ? query(l - 1) : 0);
    }
};

// ═══════════════════════════════════════════════════════════════
// COMPARISON: BIT vs Segment Tree
// ═══════════════════════════════════════════════════════════════

void demoComparison() {
    cout << "═══ BIT vs SEGMENT TREE COMPARISON ═══\n\n";

    cout << "┌─────────────────┬──────────────┬──────────────┐\n";
    cout << "│ Feature         │ Fenwick Tree │ Segment Tree │\n";
    cout << "├─────────────────┼──────────────┼──────────────┤\n";
    cout << "│ Code length     │ ~15 lines    │ ~40 lines    │\n";
    cout << "│ Memory          │ O(n)         │ O(4n)        │\n";
    cout << "│ Build           │ O(n)         │ O(n)         │\n";
    cout << "│ Point Update    │ O(log n)     │ O(log n)     │\n";
    cout << "│ Range Sum       │ O(log n)     │ O(log n)     │\n";
    cout << "│ Range Min/Max   │ ❌ Not easy   │ ✅ Easy       │\n";
    cout << "│ Range Update    │ ✅ With trick │ ✅ With lazy  │\n";
    cout << "│ Constant factor │ ~2x faster   │ Standard     │\n";
    cout << "│ Coding time     │ ~3 min       │ ~8 min       │\n";
    cout << "└─────────────────┴──────────────┴──────────────┘\n\n";

    cout << "WHEN TO USE BIT:\n";
    cout << "  ✅ Point update + prefix/range SUM\n";
    cout << "  ✅ Counting inversions\n";
    cout << "  ✅ Coordinate compression + counting\n";
    cout << "  ✅ When you need speed and simplicity\n\n";

    cout << "WHEN TO USE SEGMENT TREE:\n";
    cout << "  ✅ Range min/max/GCD queries\n";
    cout << "  ✅ Range updates with lazy propagation\n";
    cout << "  ✅ Custom merge functions\n";
    cout << "  ✅ Walking/binary search on tree\n\n";
}

// ═══════════════════════════════════════════════════════════════
// TRICK: Finding kth element using BIT
// ═══════════════════════════════════════════════════════════════

void demoKthElement() {
    cout << "═══ FINDING KTH ELEMENT USING BIT ═══\n\n";

    cout << "Problem: Find the kth smallest active element.\n";
    cout << "BIT stores count of active elements.\n\n";

    int n = 8;
    FenwickTree bit(n);
    // Add elements 1..8
    for (int i = 1; i <= n; i++) bit.update(i, 1);

    // Find kth using binary lifting on BIT
    auto findKth = [&](int k) -> int {
        int pos = 0;
        int bitMask = 1;
        while (bitMask <= n) bitMask <<= 1;
        bitMask >>= 1;

        for (; bitMask > 0; bitMask >>= 1) {
            int next = pos + bitMask;
            if (next <= n && bit.query(next) < k) {
                pos = next;
                // Note: we need to subtract, but query gives prefix sum
                // Actually, let's use the standard approach:
            }
        }
        // Simpler O(log²n) approach for demo:
        int lo = 1, hi = n;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (bit.query(mid) >= k) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    };

    cout << "Elements: {1,2,3,4,5,6,7,8} all active\n";
    cout << "  3rd smallest = " << findKth(3) << "\n";
    cout << "  5th smallest = " << findKth(5) << "\n\n";

    // Remove element 3
    bit.update(3, -1);
    cout << "After removing 3: {1,2,_,4,5,6,7,8}\n";
    cout << "  3rd smallest = " << findKth(3) << " (was 3, now 4)\n";
    cout << "  5th smallest = " << findKth(5) << " (was 5, now 6)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║   LEVEL 6: FENWICK TREE (BIT) — COMPLETE GUIDE             ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n\n";

    demoBIT();
    demoComparison();
    demoKthElement();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "  KEY TAKEAWAYS:\n";
    cout << "  1. BIT = simplest range query structure (~15 lines)\n";
    cout << "  2. lowbit(i) = i & (-i) is the magic behind BIT\n";
    cout << "  3. Update: go UP (i += lowbit), Query: go DOWN (i -= lowbit)\n";
    cout << "  4. O(n) build possible with propagation technique\n";
    cout << "  5. Use BIT for sums, ST for everything else\n";
    cout << "  6. ~2x faster than segment tree in practice\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

