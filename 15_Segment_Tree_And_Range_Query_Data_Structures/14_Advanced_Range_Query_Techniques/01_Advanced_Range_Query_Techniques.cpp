/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║        LEVEL 13 — ADVANCED RANGE QUERY TECHNIQUES                              ║
║        Segment Tree Beats, Parallel Binary Search, Divide & Conquer            ║
║        Author: Sarvan Yaduvanshi                                               ║
╚══════════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Segment Tree Beats (Ji Driver Segment Tree) — Concept
 2. Segment Tree Beats — Implementation (chmin + sum query)
 3. Divide & Conquer + Segment Tree
 4. Parallel Binary Search
 5. Complete Dry Runs

═══════════════════════════════════════════════════════════════
SECTION 1: SEGMENT TREE BEATS CONCEPT
═══════════════════════════════════════════════════════════════

PROBLEM: Support these operations on array:
  1. chmin(l, r, x): for each i in [l,r], a[i] = min(a[i], x)
  2. query_sum(l, r): sum of elements in [l, r]
  3. query_max(l, r): max of elements in [l, r]

WHY IS THIS HARD?
  chmin affects different elements differently!
  • Elements already ≤ x: unchanged
  • Elements > x: set to x
  Normal lazy can't handle this (lazy doesn't distinguish values).

JI DRIVER SEGMENT TREE (Segment Tree Beats):
  Each node stores:
    • max_val: maximum value in range
    • count_max: count of elements equal to max_val
    • second_max: second maximum (strict)
    • sum: sum of all elements

  For chmin(l, r, x):
    Case 1: x ≥ max_val → no change (all elements already ≤ x)
    Case 2: second_max < x < max_val → only the max elements change!
      sum -= count_max * max_val
      sum += count_max * x
      max_val = x
    Case 3: x ≤ second_max → recurse to children (can't update lazily)

  KEY INSIGHT: Case 3 is the "break" condition, but it happens
  at most O(n log n) times total across all operations!
  → Amortized O(log²n) per operation.

VISUALIZATION:
  a[] = [5, 3, 7, 2, 6, 4, 8, 1]

  Node for range [0, 7]:
    max=8, count_max=1, second_max=7, sum=36

  chmin(0, 7, 6):
    x=6, max=8 > 6, second_max=7 > 6 → Case 3! Must recurse.

  chmin(0, 3, 6):
    Node [0,3]: max=7, second_max=5, x=6
    second_max=5 < x=6 < max=7 → Case 2!
    sum = sum - 1*7 + 1*6 = 17 - 7 + 6 = 16
    max = 6
    Done! (Don't recurse further)

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
// IMPLEMENTATION 1: Segment Tree Beats (chmin + sum query)
// ═══════════════════════════════════════════════════════════════

class SegTreeBeats {
    struct Node {
        long long sum;
        long long mx, smx;  // max and second max (strict)
        int cnt_mx;          // count of max
    };

    int n;
    vector<Node> tree;

    void pushUp(int node) {
        int l = 2*node, r = 2*node+1;
        tree[node].sum = tree[l].sum + tree[r].sum;
        if (tree[l].mx == tree[r].mx) {
            tree[node].mx = tree[l].mx;
            tree[node].cnt_mx = tree[l].cnt_mx + tree[r].cnt_mx;
            tree[node].smx = max(tree[l].smx, tree[r].smx);
        } else if (tree[l].mx > tree[r].mx) {
            tree[node].mx = tree[l].mx;
            tree[node].cnt_mx = tree[l].cnt_mx;
            tree[node].smx = max(tree[l].smx, tree[r].mx);
        } else {
            tree[node].mx = tree[r].mx;
            tree[node].cnt_mx = tree[r].cnt_mx;
            tree[node].smx = max(tree[l].mx, tree[r].smx);
        }
    }

    void pushChmin(int node, long long val) {
        if (val >= tree[node].mx) return;
        tree[node].sum -= (long long)tree[node].cnt_mx * (tree[node].mx - val);
        tree[node].mx = val;
    }

    void pushDown(int node) {
        pushChmin(2*node, tree[node].mx);
        pushChmin(2*node+1, tree[node].mx);
    }

    void build(const vector<int>& a, int node, int s, int e) {
        if (s == e) {
            tree[node] = {a[s], a[s], LLONG_MIN, 1};
            return;
        }
        int mid = (s + e) / 2;
        build(a, 2*node, s, mid);
        build(a, 2*node+1, mid+1, e);
        pushUp(node);
    }

    void updateChmin(int node, int s, int e, int l, int r, long long x) {
        if (r < s || e < l || tree[node].mx <= x) return; // Case 1
        if (l <= s && e <= r && tree[node].smx < x) {     // Case 2
            pushChmin(node, x);
            return;
        }
        // Case 3: recurse
        pushDown(node);
        int mid = (s + e) / 2;
        updateChmin(2*node, s, mid, l, r, x);
        updateChmin(2*node+1, mid+1, e, l, r, x);
        pushUp(node);
    }

    long long querySum(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return tree[node].sum;
        pushDown(node);
        int mid = (s + e) / 2;
        return querySum(2*node, s, mid, l, r) + querySum(2*node+1, mid+1, e, l, r);
    }

    long long queryMax(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return LLONG_MIN;
        if (l <= s && e <= r) return tree[node].mx;
        pushDown(node);
        int mid = (s + e) / 2;
        return max(queryMax(2*node, s, mid, l, r), queryMax(2*node+1, mid+1, e, l, r));
    }

public:
    SegTreeBeats(const vector<int>& a) : n(a.size()), tree(4 * a.size()) {
        build(a, 1, 0, n-1);
    }

    void chmin(int l, int r, long long x) { updateChmin(1, 0, n-1, l, r, x); }
    long long querySum(int l, int r) { return querySum(1, 0, n-1, l, r); }
    long long queryMax(int l, int r) { return queryMax(1, 0, n-1, l, r); }
};

void demoSegTreeBeats() {
    cout << "═══ SEGMENT TREE BEATS (JI DRIVER) ═══\n\n";

    vector<int> a = {5, 3, 7, 2, 6, 4, 8, 1};
    cout << "Array: ";
    for (int x : a) cout << x << " ";
    cout << "\n\n";

    SegTreeBeats stb(a);

    cout << "Initial:\n";
    cout << "  sum(0,7) = " << stb.querySum(0, 7) << " (5+3+7+2+6+4+8+1 = 36)\n";
    cout << "  max(0,7) = " << stb.queryMax(0, 7) << " (8)\n\n";

    cout << "chmin(0, 7, 6): set a[i] = min(a[i], 6) for all i\n";
    cout << "  Expected: [5, 3, 6, 2, 6, 4, 6, 1]\n";
    stb.chmin(0, 7, 6);
    cout << "  sum(0,7) = " << stb.querySum(0, 7) << " (5+3+6+2+6+4+6+1 = 33)\n";
    cout << "  max(0,7) = " << stb.queryMax(0, 7) << " (6)\n\n";

    cout << "chmin(2, 5, 4): set a[i] = min(a[i], 4) for i in [2,5]\n";
    cout << "  Expected: [5, 3, 4, 2, 4, 4, 6, 1]\n";
    stb.chmin(2, 5, 4);
    cout << "  sum(0,7) = " << stb.querySum(0, 7) << " (5+3+4+2+4+4+6+1 = 29)\n";
    cout << "  max(2,5) = " << stb.queryMax(2, 5) << " (4)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: PARALLEL BINARY SEARCH — CONCEPT
// ═══════════════════════════════════════════════════════════════

void demoParallelBinarySearch() {
    cout << "═══ PARALLEL BINARY SEARCH ═══\n\n";

    cout << "PROBLEM: Q queries, each asking 'what is the minimum time\n";
    cout << "         such that condition C(query_i) is satisfied?'\n\n";

    cout << "NAIVE: Binary search for each query → O(Q × log T × cost_per_check)\n";
    cout << "PBS:   Binary search ALL queries simultaneously → much fewer total checks!\n\n";

    cout << "ALGORITHM:\n";
    cout << "  1. Each query has [lo, hi] = current binary search range\n";
    cout << "  2. For each iteration:\n";
    cout << "     a. Group queries by their mid = (lo+hi)/2\n";
    cout << "     b. Process events in order of time\n";
    cout << "     c. At each mid, check all queries with that mid\n";
    cout << "     d. Update lo/hi based on check result\n";
    cout << "  3. Repeat for O(log T) iterations\n\n";

    cout << "COMPLEXITY: O((N + Q) × log T × F) where F = cost per update/check\n\n";

    cout << "CLASSIC EXAMPLE: SPOJ METEORS\n";
    cout << "  Events: meteor showers at different times\n";
    cout << "  Query: when does country i collect enough meteors?\n";
    cout << "  → PBS + BIT for range updates\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: DIVIDE & CONQUER WITH SEGMENT TREE
// ═══════════════════════════════════════════════════════════════

void demoDivideConquer() {
    cout << "═══ DIVIDE & CONQUER + SEGMENT TREE ═══\n\n";

    cout << "CONCEPT: Process queries using D&C over the array/time.\n";
    cout << "  Split array into halves, process queries on each half.\n\n";

    cout << "EXAMPLE: Offline query processing\n";
    cout << "  1. Split time range [0, T] into [0, T/2] and [T/2+1, T]\n";
    cout << "  2. Process updates in first half\n";
    cout << "  3. Answer queries that span the midpoint\n";
    cout << "  4. Recurse on both halves\n\n";

    cout << "Common pattern: CDQ divide & conquer\n";
    cout << "  • Sort updates and queries together\n";
    cout << "  • Process left half updates → answer right half queries\n";
    cout << "  • Recurse\n";
    cout << "  → Often combined with BIT/ST for efficient processing\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║   LEVEL 13: ADVANCED RANGE QUERY TECHNIQUES                ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n\n";

    demoSegTreeBeats();
    demoParallelBinarySearch();
    demoDivideConquer();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "  KEY TAKEAWAYS:\n";
    cout << "  1. ST Beats: chmin/chmax with sum queries, amortized O(log²n)\n";
    cout << "  2. Key: 3 cases (no change / only max changes / recurse)\n";
    cout << "  3. PBS: binary search all queries simultaneously\n";
    cout << "  4. D&C + ST: offline processing with divide & conquer\n";
    cout << "  5. These are GM/ICPC level techniques!\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

