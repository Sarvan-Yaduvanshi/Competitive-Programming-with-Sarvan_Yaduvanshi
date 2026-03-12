/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║        LEVEL 8 — SPARSE TABLE (Static Range Queries)                           ║
║        O(1) RMQ, GCD, Idempotent Operations                                   ║
║        Author: Sarvan Yaduvanshi                                               ║
╚══════════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Sparse Table Concept
 2. Build O(n log n) — Precomputation
 3. Range Minimum Query O(1) — Idempotent
 4. Range Maximum Query O(1)
 5. GCD Sparse Table O(1)
 6. Idempotent vs Non-Idempotent Operations
 7. Disjoint Sparse Table (for non-idempotent like Sum)
 8. Complete Dry Runs

═══════════════════════════════════════════════════════════════
SECTION 1: SPARSE TABLE CONCEPT
═══════════════════════════════════════════════════════════════

A Sparse Table preprocesses a STATIC array to answer
RANGE QUERIES in O(1) time.

KEY IDEA: Precompute answers for all ranges of length 2^k.
  table[k][i] = answer for range [i, i + 2^k - 1]

BUILD:
  table[0][i] = a[i]                              (ranges of length 1)
  table[k][i] = merge(table[k-1][i], table[k-1][i + 2^(k-1)])

VISUALIZATION:

  a[] = {3, 1, 4, 1, 5, 9, 2, 6}    n = 8

  k=0 (length 1): [3] [1] [4] [1] [5] [9] [2] [6]
  k=1 (length 2): [1] [1] [1] [1] [5] [2] [2]  _
                    ↑ min(3,1)  ↑ min(4,1)
  k=2 (length 4): [1] [1] [1] [1] [2]  _  _  _
                    ↑ min(1,1)=1     ↑ min(5,2)=2
  k=3 (length 8): [1]  _  _  _  _  _  _  _
                    ↑ min(1,2)=1

  Table (for MINIMUM):
  ┌────┬───┬───┬───┬───┬───┬───┬───┬───┐
  │ k\i│ 0 │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │
  ├────┼───┼───┼───┼───┼───┼───┼───┼───┤
  │  0 │ 3 │ 1 │ 4 │ 1 │ 5 │ 9 │ 2 │ 6 │
  │  1 │ 1 │ 1 │ 1 │ 1 │ 5 │ 2 │ 2 │ - │
  │  2 │ 1 │ 1 │ 1 │ 1 │ 2 │ - │ - │ - │
  │  3 │ 1 │ - │ - │ - │ - │ - │ - │ - │
  └────┴───┴───┴───┴───┴───┴───┴───┴───┘

QUERY — min(2, 6):
  Length = 6 - 2 + 1 = 5
  k = floor(log2(5)) = 2   (2^2 = 4)
  Answer = min(table[2][2], table[2][6 - 4 + 1])
         = min(table[2][2], table[2][3])
         = min(1, 1) = 1

  The two ranges OVERLAP:
    table[2][2] covers [2, 5]
    table[2][3] covers [3, 6]
    Together they cover [2, 6] ✓

  For IDEMPOTENT operations (min, max, gcd), overlap is fine!
    min(x, x) = x → no double-counting issue.

═══════════════════════════════════════════════════════════════
SECTION 6: IDEMPOTENT vs NON-IDEMPOTENT
═══════════════════════════════════════════════════════════════

IDEMPOTENT: f(x, x) = x
  ✅ min, max, gcd, bitwise AND, bitwise OR
  → Can use overlapping ranges → O(1) query!

NON-IDEMPOTENT: f(x, x) ≠ x
  ❌ sum (x + x = 2x ≠ x), count, product
  → Can NOT overlap → must use Disjoint Sparse Table (O(log n) query)

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
// IMPLEMENTATION 1: Sparse Table (Min/Max/GCD — O(1) query)
// ═══════════════════════════════════════════════════════════════

template<typename T, typename F>
class SparseTable {
    vector<vector<T>> table;
    vector<int> lg;
    F merge;

public:
    SparseTable() {}
    SparseTable(const vector<T>& a, F merge) : merge(merge) {
        int n = a.size();
        int K = (n > 1) ? (int)floor(log2(n)) + 1 : 1;
        table.assign(K, vector<T>(n));
        lg.resize(n + 1);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;

        // k = 0: base case
        table[0] = a;

        // k > 0: merge two halves
        for (int k = 1; k < K; k++) {
            for (int i = 0; i + (1 << k) <= n; i++) {
                table[k][i] = merge(table[k-1][i], table[k-1][i + (1 << (k-1))]);
            }
        }
    }

    // O(1) query for idempotent operations [l, r]
    T query(int l, int r) {
        int k = lg[r - l + 1];
        return merge(table[k][l], table[k][r - (1 << k) + 1]);
    }
};

void demoSparseTableMin() {
    cout << "═══ SPARSE TABLE — RANGE MINIMUM QUERY O(1) ═══\n\n";

    vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
    cout << "Array: ";
    for (int x : a) cout << x << " ";
    cout << "\n\n";

    SparseTable<int, function<int(int,int)>> st(a, [](int a, int b) { return min(a, b); });

    cout << "Sparse Table (min):\n";
    cout << "  k=0: ";
    for (int x : a) cout << x << " ";
    cout << "\n";

    cout << "  k=1: ";
    for (int i = 0; i + 2 <= 8; i++) cout << min(a[i], a[i+1]) << " ";
    cout << "\n";

    cout << "  k=2: ";
    for (int i = 0; i + 4 <= 8; i++) {
        int v = min({a[i], a[i+1], a[i+2], a[i+3]});
        cout << v << " ";
    }
    cout << "\n\n";

    // Queries
    cout << "QUERIES (all O(1)):\n";
    cout << "  min(0, 7) = " << st.query(0, 7) << " (1)\n";
    cout << "  min(2, 6) = " << st.query(2, 6) << " (1)\n";
    cout << "  min(4, 7) = " << st.query(4, 7) << " (2)\n";
    cout << "  min(0, 0) = " << st.query(0, 0) << " (3)\n";
    cout << "  min(5, 5) = " << st.query(5, 5) << " (9)\n\n";

    cout << "DRY RUN — query min(2, 6):\n";
    cout << "  Length = 6 - 2 + 1 = 5\n";
    cout << "  k = floor(log2(5)) = 2\n";
    cout << "  Left range:  table[2][2] = min(a[2..5]) = min(4,1,5,9) = 1\n";
    cout << "  Right range: table[2][3] = min(a[3..6]) = min(1,5,9,2) = 1\n";
    cout << "  Answer = min(1, 1) = 1 ✓\n";
    cout << "  Overlap at indices [3,5] — OK because min is idempotent!\n\n";
}

void demoSparseTableMax() {
    cout << "═══ SPARSE TABLE — RANGE MAXIMUM QUERY O(1) ═══\n\n";

    vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
    SparseTable<int, function<int(int,int)>> st(a, [](int a, int b) { return max(a, b); });

    cout << "Array: 3 1 4 1 5 9 2 6\n";
    cout << "  max(0, 7) = " << st.query(0, 7) << " (9)\n";
    cout << "  max(0, 3) = " << st.query(0, 3) << " (4)\n";
    cout << "  max(4, 7) = " << st.query(4, 7) << " (9)\n\n";
}

void demoSparseTableGCD() {
    cout << "═══ SPARSE TABLE — RANGE GCD QUERY O(1) ═══\n\n";

    vector<int> a = {12, 8, 6, 18, 9, 15, 3};
    cout << "Array: ";
    for (int x : a) cout << x << " ";
    cout << "\n\n";

    SparseTable<int, function<int(int,int)>> st(a, [](int a, int b) { return (a == 0) ? b : (b == 0) ? a : (int)std::gcd(abs(a), abs(b)); });

    cout << "  gcd(0, 6) = " << st.query(0, 6) << " (gcd of all = 1? No: gcd(12,8,6,18,9,15,3) = 1)\n";
    cout << "  gcd(0, 2) = " << st.query(0, 2) << " (gcd(12,8,6) = 2)\n";
    cout << "  gcd(3, 5) = " << st.query(3, 5) << " (gcd(18,9,15) = 3)\n";
    cout << "  gcd(0, 3) = " << st.query(0, 3) << " (gcd(12,8,6,18) = 2)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// COMPARISON
// ═══════════════════════════════════════════════════════════════

void printComparison() {
    cout << "═══ SPARSE TABLE vs SEGMENT TREE ═══\n\n";

    cout << "┌────────────────┬──────────────┬──────────────┐\n";
    cout << "│ Feature        │ Sparse Table │ Segment Tree │\n";
    cout << "├────────────────┼──────────────┼──────────────┤\n";
    cout << "│ Build          │ O(n log n)   │ O(n)         │\n";
    cout << "│ Query          │ O(1) !!!     │ O(log n)     │\n";
    cout << "│ Point Update   │ ❌ Impossible │ O(log n)     │\n";
    cout << "│ Space          │ O(n log n)   │ O(4n)        │\n";
    cout << "│ Coding time    │ ~15 lines    │ ~40 lines    │\n";
    cout << "│ Operations     │ Idempotent   │ Any          │\n";
    cout << "└────────────────┴──────────────┴──────────────┘\n\n";

    cout << "USE SPARSE TABLE WHEN:\n";
    cout << "  ✅ Array is STATIC (no updates)\n";
    cout << "  ✅ Need O(1) per query (many queries)\n";
    cout << "  ✅ Operation is idempotent (min, max, GCD)\n\n";

    cout << "USE SEGMENT TREE WHEN:\n";
    cout << "  ✅ Array has updates\n";
    cout << "  ✅ Need non-idempotent operations (sum)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║   LEVEL 8: SPARSE TABLE — COMPLETE GUIDE                   ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n\n";

    demoSparseTableMin();
    demoSparseTableMax();
    demoSparseTableGCD();
    printComparison();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "  KEY TAKEAWAYS:\n";
    cout << "  1. Sparse Table = O(n log n) build, O(1) query\n";
    cout << "  2. Only for STATIC arrays (no updates!)\n";
    cout << "  3. O(1) works because we allow overlap for idempotent ops\n";
    cout << "  4. table[k][i] = answer for range of length 2^k starting at i\n";
    cout << "  5. Query: k = floor(log2(len)), merge two overlapping ranges\n";
    cout << "  6. Perfect for LCA, static RMQ, competitive programming\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

