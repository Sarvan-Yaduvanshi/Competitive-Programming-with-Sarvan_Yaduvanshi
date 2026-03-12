/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║        LEVEL 2 — SEGMENT TREE VARIANTS                                         ║
║        Range Sum, Min, Max, GCD, LCM, Count, Frequency, XOR/AND/OR            ║
║        Author: Sarvan Yaduvanshi                                               ║
╚══════════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Range Sum Segment Tree (review)
 2. Range Minimum Query (RMQ) Segment Tree
 3. Range Maximum Query Segment Tree
 4. GCD Segment Tree
 5. LCM Segment Tree
 6. Count Segment Tree (count elements satisfying condition)
 7. Frequency Segment Tree
 8. XOR / AND / OR Segment Trees
 9. How to Change Merge Function — Generic Template
 10. Complete Dry Runs for Each Variant

KEY INSIGHT:
──────────────
The ONLY thing that changes between variants is the MERGE function!
  • Sum: merge(a, b) = a + b,       identity = 0
  • Min: merge(a, b) = min(a, b),   identity = INT_MAX
  • Max: merge(a, b) = max(a, b),   identity = INT_MIN
  • GCD: merge(a, b) = gcd(a, b),   identity = 0
  • XOR: merge(a, b) = a ^ b,       identity = 0
  • AND: merge(a, b) = a & b,       identity = all 1s (~0)
  • OR:  merge(a, b) = a | b,       identity = 0

═══════════════════════════════════════════════════════════════
SECTION 2: RANGE MINIMUM QUERY (RMQ) SEGMENT TREE
═══════════════════════════════════════════════════════════════

Array: a[] = {3, 1, 4, 1, 5, 9, 2, 6}

Min Segment Tree:
                     [1]                    ← min(0..7) = 1
                   /      \
               [1]          [2]             ← min(0..3)=1, min(4..7)=2
              /    \       /    \
           [1]    [1]   [5]    [2]
          /   \  /   \  /  \  /   \
        [3] [1][4] [1][5] [9][2] [6]

Query min(2, 5) = min(4, 1, 5, 9) = 1

DRY RUN — query min(2, 5):
  query(1, 0, 7, 2, 5) → PARTIAL
  ├── query(2, 0, 3, 2, 5) → PARTIAL
  │   ├── query(4, 0, 1, 2, 5) → NO OVERLAP → INT_MAX
  │   └── query(5, 2, 3, 2, 5) → COMPLETE → return 1
  │   return min(INT_MAX, 1) = 1
  └── query(3, 4, 7, 2, 5) → PARTIAL
      ├── query(6, 4, 5, 2, 5) → COMPLETE → return 5
      └── query(7, 6, 7, 2, 5) → NO OVERLAP → INT_MAX
      return min(5, INT_MAX) = 5
  return min(1, 5) = 1 ✅

═══════════════════════════════════════════════════════════════
SECTION 4: GCD SEGMENT TREE
═══════════════════════════════════════════════════════════════

Array: a[] = {12, 8, 6, 18, 9}

GCD Segment Tree:
                [1]=gcd(all)=1  ? Let's compute:
  gcd(12,8)=4, gcd(6,18)=6, gcd(4,6)=2, gcd(2,9)=1

                     [1]                    ← gcd(0..4) = 1
                   /      \
               [2]          [gcd(18,9)=9]
              /    \            /    \
         [gcd(12,8)=4] [6]  [18]   [9]
          /   \
        [12] [8]

Wait, let me redo for 5 elements:
         node 1: gcd(12,8,6,18,9) = 1
         node 2: gcd(12,8,6) = 2
         node 3: gcd(18,9) = 9
         node 4: gcd(12,8) = 4
         node 5: 6
         node 6: 18
         node 7: 9
         node 8: 12
         node 9: 8

GCD property: gcd(a, 0) = a  (0 is the identity for GCD)

Query gcd(1, 3) = gcd(8, 6, 18) = gcd(8, gcd(6, 18)) = gcd(8, 6) = 2

═══════════════════════════════════════════════════════════════
SECTION 5: LCM SEGMENT TREE
═══════════════════════════════════════════════════════════════

⚠️ WARNING: LCM can overflow very quickly!
  lcm(a, b) = a / gcd(a, b) * b   (divide first to avoid overflow)

Array: a[] = {2, 3, 4, 6}
  lcm(2,3)=6, lcm(4,6)=12, lcm(6,12)=12

Identity for LCM = 1 (lcm(a, 1) = a)

═══════════════════════════════════════════════════════════════
SECTION 6-7: COUNT / FREQUENCY SEGMENT TREE
═══════════════════════════════════════════════════════════════

Count ST: Each leaf = 1 if element satisfies condition, else 0.
          Internal node = sum of children.
          Range query = count of elements satisfying condition in [l, r].

Example: Count elements > 3 in range
  a[] = {5, 1, 4, 1, 5, 9}
  Count array: [1, 0, 1, 0, 1, 1] (>3 check)
  Build sum segment tree on this.
  query(1, 4) = 0 + 1 + 0 + 1 = 2 ✓

Frequency ST: Store frequency counts.
  Used when values are bounded (e.g., values in [1, 100000]).
  tree[v] = count of value v in current range.
  Support: add(val), remove(val), count_in_range(l, r).

═══════════════════════════════════════════════════════════════
SECTION 8: XOR / AND / OR SEGMENT TREES
═══════════════════════════════════════════════════════════════

XOR Segment Tree:
  merge(a, b) = a ^ b
  identity = 0
  a[] = {3, 5, 2, 7}  →  3 = 011, 5 = 101, 2 = 010, 7 = 111
  XOR(0,3) = 3^5^2^7 = 011^101^010^111 = 001 = 1

AND Segment Tree:
  merge(a, b) = a & b
  identity = ~0 (all bits set)
  a[] = {7, 5, 3, 6}  →  7=111, 5=101, 3=011, 6=110
  AND(0,3) = 111 & 101 & 011 & 110 = 000 = 0

OR Segment Tree:
  merge(a, b) = a | b
  identity = 0
  a[] = {1, 2, 4, 8}  →  0001, 0010, 0100, 1000
  OR(0,3) = 0001 | 0010 | 0100 | 1000 = 1111 = 15

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
// GENERIC SEGMENT TREE TEMPLATE
// ═══════════════════════════════════════════════════════════════
/*
   Just change:
     1. merge(a, b) → the combine function
     2. IDENTITY    → the neutral element
   And you get ANY segment tree variant!
*/

template<typename T>
class GenericSegTree {
    int n;
    vector<T> tree;
    T identity;
    function<T(T, T)> merge;

    void build(const vector<T>& a, int node, int s, int e) {
        if (s == e) { tree[node] = a[s]; return; }
        int mid = (s + e) / 2;
        build(a, 2*node, s, mid);
        build(a, 2*node+1, mid+1, e);
        tree[node] = merge(tree[2*node], tree[2*node+1]);
    }

    T query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return identity;
        if (l <= s && e <= r) return tree[node];
        int mid = (s + e) / 2;
        return merge(query(2*node, s, mid, l, r),
                     query(2*node+1, mid+1, e, l, r));
    }

    void update(int node, int s, int e, int idx, T val) {
        if (s == e) { tree[node] = val; return; }
        int mid = (s + e) / 2;
        if (idx <= mid) update(2*node, s, mid, idx, val);
        else update(2*node+1, mid+1, e, idx, val);
        tree[node] = merge(tree[2*node], tree[2*node+1]);
    }

public:
    GenericSegTree(const vector<T>& a, T identity, function<T(T, T)> merge)
        : n(a.size()), tree(4 * a.size()), identity(identity), merge(merge) {
        build(a, 1, 0, n-1);
    }

    T query(int l, int r) { return query(1, 0, n-1, l, r); }
    void update(int idx, T val) { update(1, 0, n-1, idx, val); }
};

// ═══════════════════════════════════════════════════════════════
// DEMO 1: Range Sum Segment Tree
// ═══════════════════════════════════════════════════════════════

void demoRangeSum() {
    cout << "═══ RANGE SUM SEGMENT TREE ═══\n\n";

    vector<long long> a = {3, 1, 4, 1, 5, 9, 2, 6};
    cout << "Array: ";
    for (auto x : a) cout << x << " ";
    cout << "\n\n";

    GenericSegTree<long long> st(a, 0LL, [](long long a, long long b) { return a + b; });

    cout << "sum(0, 7) = " << st.query(0, 7) << " (3+1+4+1+5+9+2+6=31)\n";
    cout << "sum(2, 5) = " << st.query(2, 5) << " (4+1+5+9=19)\n";
    cout << "sum(0, 0) = " << st.query(0, 0) << " (3)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// DEMO 2: Range Minimum Query Segment Tree
// ═══════════════════════════════════════════════════════════════

void demoRangeMin() {
    cout << "═══ RANGE MINIMUM QUERY SEGMENT TREE ═══\n\n";

    vector<long long> a = {3, 1, 4, 1, 5, 9, 2, 6};
    cout << "Array: ";
    for (auto x : a) cout << x << " ";
    cout << "\n\n";

    GenericSegTree<long long> st(a, LLONG_MAX,
        [](long long a, long long b) { return min(a, b); });

    cout << "min(0, 7) = " << st.query(0, 7) << " (min of all = 1)\n";
    cout << "min(2, 5) = " << st.query(2, 5) << " (min(4,1,5,9) = 1)\n";
    cout << "min(4, 7) = " << st.query(4, 7) << " (min(5,9,2,6) = 2)\n";
    cout << "min(5, 5) = " << st.query(5, 5) << " (9)\n\n";

    cout << "DRY RUN — min(4, 7):\n";
    cout << "  Tree for min:\n";
    cout << "              [1]=1\n";
    cout << "             /      \\\n";
    cout << "         [2]=1     [3]=2\n";
    cout << "         /  \\     /    \\\n";
    cout << "      [1]  [1]  [5]   [2]\n";
    cout << "      / \\  / \\  / \\  / \\\n";
    cout << "     3  1 4  1 5  9 2  6\n\n";
    cout << "  query(1, 0, 7, 4, 7)\n";
    cout << "  └─ Right child [3] covers [4,7] → COMPLETE → return 2 ✓\n\n";

    // Update
    cout << "Update: a[6] = 0 (was 2)\n";
    st.update(6, 0);
    cout << "min(4, 7) = " << st.query(4, 7) << " (min(5,9,0,6) = 0)\n";
    cout << "min(0, 7) = " << st.query(0, 7) << " (0 is now global min)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// DEMO 3: Range Maximum Query Segment Tree
// ═══════════════════════════════════════════════════════════════

void demoRangeMax() {
    cout << "═══ RANGE MAXIMUM QUERY SEGMENT TREE ═══\n\n";

    vector<long long> a = {3, 1, 4, 1, 5, 9, 2, 6};
    GenericSegTree<long long> st(a, LLONG_MIN,
        [](long long a, long long b) { return max(a, b); });

    cout << "Array: 3 1 4 1 5 9 2 6\n";
    cout << "max(0, 7) = " << st.query(0, 7) << " (9)\n";
    cout << "max(0, 3) = " << st.query(0, 3) << " (4)\n";
    cout << "max(4, 7) = " << st.query(4, 7) << " (9)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// DEMO 4: GCD Segment Tree
// ═══════════════════════════════════════════════════════════════

void demoGCD() {
    cout << "═══ GCD SEGMENT TREE ═══\n\n";

    vector<long long> a = {12, 8, 6, 18, 9};
    cout << "Array: ";
    for (auto x : a) cout << x << " ";
    cout << "\n\n";

    GenericSegTree<long long> st(a, 0LL,
        [](long long a, long long b) { return (a == 0) ? b : (b == 0) ? a : std::gcd(abs(a), abs(b)); });

    cout << "GCD Segment Tree Visualization:\n";
    cout << "              [1]=gcd(all)=" << st.query(0, 4) << "\n";
    cout << "             /            \\\n";
    cout << "        [2]=gcd(12,8,6)  [3]=gcd(18,9)\n";
    cout << "         = " << st.query(0, 2) << "                = " << st.query(3, 4) << "\n";
    cout << "        / \\              / \\\n";
    cout << "   [4]=4  [5]=6     [6]=18 [7]=9\n";
    cout << "   / \\\n";
    cout << " 12   8\n\n";

    cout << "gcd(0, 4) = " << st.query(0, 4) << " (gcd(12,8,6,18,9) = 1)\n";
    cout << "gcd(0, 2) = " << st.query(0, 2) << " (gcd(12,8,6) = 2)\n";
    cout << "gcd(1, 3) = " << st.query(1, 3) << " (gcd(8,6,18) = 2)\n";
    cout << "gcd(3, 4) = " << st.query(3, 4) << " (gcd(18,9) = 9)\n\n";

    cout << "DRY RUN — gcd(1, 3):\n";
    cout << "  query(1, 0, 4, 1, 3) → PARTIAL\n";
    cout << "  ├─ query(2, 0, 2, 1, 3) → PARTIAL\n";
    cout << "  │  ├─ query(4, 0, 1, 1, 3) → PARTIAL\n";
    cout << "  │  │  ├─ query(8, 0, 0, 1, 3) → NO OVERLAP → 0\n";
    cout << "  │  │  └─ query(9, 1, 1, 1, 3) → COMPLETE → 8\n";
    cout << "  │  │  gcd(0, 8) = 8\n";
    cout << "  │  └─ query(5, 2, 2, 1, 3) → COMPLETE → 6\n";
    cout << "  │  gcd(8, 6) = 2\n";
    cout << "  └─ query(3, 3, 4, 1, 3) → PARTIAL\n";
    cout << "     ├─ query(6, 3, 3, 1, 3) → COMPLETE → 18\n";
    cout << "     └─ query(7, 4, 4, 1, 3) → NO OVERLAP → 0\n";
    cout << "     gcd(18, 0) = 18\n";
    cout << "  gcd(2, 18) = 2 ✓\n\n";
}

// ═══════════════════════════════════════════════════════════════
// DEMO 5: LCM Segment Tree
// ═══════════════════════════════════════════════════════════════

void demoLCM() {
    cout << "═══ LCM SEGMENT TREE ═══\n\n";

    vector<long long> a = {2, 3, 4, 6, 5};
    cout << "Array: ";
    for (auto x : a) cout << x << " ";
    cout << "\n\n";

    GenericSegTree<long long> st(a, 1LL,
        [](long long a, long long b) {
            if (a == 0 || b == 0) return max(a, b);
            return a / std::gcd(abs(a), abs(b)) * b;  // Divide first to avoid overflow!
        });

    cout << "lcm(0, 4) = " << st.query(0, 4) << " (lcm(2,3,4,6,5) = 60)\n";
    cout << "lcm(0, 2) = " << st.query(0, 2) << " (lcm(2,3,4) = 12)\n";
    cout << "lcm(2, 4) = " << st.query(2, 4) << " (lcm(4,6,5) = 60)\n\n";

    cout << "⚠️  WARNING: LCM overflows quickly!\n";
    cout << "  lcm(2,3) = 6\n";
    cout << "  lcm(6,4) = 12\n";
    cout << "  lcm(12,6) = 12\n";
    cout << "  lcm(12,5) = 60\n";
    cout << "  For large values, use __int128 or check overflow!\n\n";
}

// ═══════════════════════════════════════════════════════════════
// DEMO 6: Count Segment Tree
// ═══════════════════════════════════════════════════════════════

void demoCount() {
    cout << "═══ COUNT SEGMENT TREE ═══\n\n";

    vector<int> original = {5, 1, 4, 1, 5, 9, 2, 6};
    int threshold = 3;

    cout << "Array: ";
    for (int x : original) cout << x << " ";
    cout << "\nCount elements > " << threshold << " in ranges\n\n";

    // Transform: 1 if > threshold, else 0
    vector<long long> a(original.size());
    cout << "Transformed (>3): ";
    for (int i = 0; i < (int)original.size(); i++) {
        a[i] = (original[i] > threshold) ? 1 : 0;
        cout << a[i] << " ";
    }
    cout << "\n\n";

    GenericSegTree<long long> st(a, 0LL, [](long long a, long long b) { return a + b; });

    cout << "count(>3 in [0,7]) = " << st.query(0, 7) << " (5,4,5,9,6 → 5)\n";
    cout << "count(>3 in [1,4]) = " << st.query(1, 4) << " (4,5 → 2)\n";
    cout << "count(>3 in [5,7]) = " << st.query(5, 7) << " (9,6 → 2)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// DEMO 7: XOR / AND / OR Segment Trees
// ═══════════════════════════════════════════════════════════════

void demoBitwise() {
    cout << "═══ XOR / AND / OR SEGMENT TREES ═══\n\n";

    vector<long long> a = {3, 5, 2, 7, 4};
    cout << "Array: ";
    for (auto x : a) cout << x << " ";
    cout << "\nBinary: 011 101 010 111 100\n\n";

    // XOR
    GenericSegTree<long long> xorST(a, 0LL,
        [](long long a, long long b) { return a ^ b; });
    cout << "XOR Segment Tree:\n";
    cout << "  XOR(0,4) = " << xorST.query(0, 4)
         << " (3^5^2^7^4 = " << (3^5^2^7^4) << ")\n";
    cout << "  XOR(1,3) = " << xorST.query(1, 3)
         << " (5^2^7 = " << (5^2^7) << ")\n\n";

    // AND
    GenericSegTree<long long> andST(a, ~0LL,
        [](long long a, long long b) { return a & b; });
    cout << "AND Segment Tree:\n";
    cout << "  AND(0,4) = " << andST.query(0, 4)
         << " (3&5&2&7&4 = " << (3&5&2&7&4) << ")\n";
    cout << "  AND(0,1) = " << andST.query(0, 1)
         << " (3&5 = " << (3&5) << " = 001)\n\n";

    // OR
    GenericSegTree<long long> orST(a, 0LL,
        [](long long a, long long b) { return a | b; });
    cout << "OR Segment Tree:\n";
    cout << "  OR(0,4) = " << orST.query(0, 4)
         << " (3|5|2|7|4 = " << (3|5|2|7|4) << ")\n";
    cout << "  OR(0,1) = " << orST.query(0, 1)
         << " (3|5 = " << (3|5) << " = 111)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SUMMARY: Merge Function Reference
// ═══════════════════════════════════════════════════════════════

void printSummary() {
    cout << "═══ MERGE FUNCTION REFERENCE ═══\n\n";
    cout << "┌──────────┬─────────────────────────┬──────────────┐\n";
    cout << "│ Variant  │ Merge Function           │ Identity     │\n";
    cout << "├──────────┼─────────────────────────┼──────────────┤\n";
    cout << "│ Sum      │ a + b                   │ 0            │\n";
    cout << "│ Min      │ min(a, b)               │ INT_MAX      │\n";
    cout << "│ Max      │ max(a, b)               │ INT_MIN      │\n";
    cout << "│ GCD      │ gcd(a, b)               │ 0            │\n";
    cout << "│ LCM      │ a/gcd(a,b)*b            │ 1            │\n";
    cout << "│ Count    │ a + b (on 0/1 array)    │ 0            │\n";
    cout << "│ XOR      │ a ^ b                   │ 0            │\n";
    cout << "│ AND      │ a & b                   │ ~0 (all 1s)  │\n";
    cout << "│ OR       │ a | b                   │ 0            │\n";
    cout << "│ Product  │ a * b                   │ 1            │\n";
    cout << "└──────────┴─────────────────────────┴──────────────┘\n\n";

    cout << "GM TIP: The identity element is the value that doesn't\n";
    cout << "affect the result when merged with any element:\n";
    cout << "  min(x, INT_MAX) = x   ← INT_MAX never wins\n";
    cout << "  gcd(x, 0) = x         ← 0 doesn't affect GCD\n";
    cout << "  a & (~0) = a           ← all 1s don't change AND\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║   LEVEL 2: SEGMENT TREE VARIANTS — COMPLETE GUIDE          ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n\n";

    demoRangeSum();
    demoRangeMin();
    demoRangeMax();
    demoGCD();
    demoLCM();
    demoCount();
    demoBitwise();
    printSummary();

    return 0;
}

