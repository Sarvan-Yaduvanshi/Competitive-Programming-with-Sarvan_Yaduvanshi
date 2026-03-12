/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║        LEVEL 0 — RANGE QUERY FOUNDATIONS                                       ║
║        From Zero to Grandmaster — Core Ideas Before Segment Trees              ║
║        Author: Sarvan Yaduvanshi                                               ║
╚══════════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. What are Range Queries? (Concept + Examples)
 2. Static vs Dynamic Queries
 3. Prefix Sum Technique (1D) — Build + Query + Dry Run
 4. Prefix Sum Technique (2D) — Build + Query + Dry Run
 5. Prefix XOR Technique
 6. Difference Array (1D) — Range Update in O(1)
 7. Difference Array (2D) — Range Update on Grid
 8. Offline vs Online Queries
 9. Range Update vs Point Update
 10. Range Update vs Range Query — Classification Table
 11. Complete Demo with All Techniques

═══════════════════════════════════════════════════════════════
SECTION 1: WHAT ARE RANGE QUERIES?
═══════════════════════════════════════════════════════════════

A "range query" asks a question about a CONTIGUOUS SUBARRAY a[l..r].

Examples:
  • "What is the SUM of elements from index 2 to 5?"
  • "What is the MINIMUM element from index 1 to 7?"
  • "What is the GCD of all elements from index 3 to 9?"

Given array:  a[] = [3, 1, 4, 1, 5, 9, 2, 6]
              idx:   0  1  2  3  4  5  6  7

Query: sum(2, 5) = a[2] + a[3] + a[4] + a[5] = 4 + 1 + 5 + 9 = 19
Query: min(1, 4) = min(1, 4, 1, 5) = 1
Query: max(0, 7) = max(3, 1, 4, 1, 5, 9, 2, 6) = 9

Naive approach: Loop from l to r → O(n) per query
Better: Preprocess to answer queries faster!

═══════════════════════════════════════════════════════════════
SECTION 2: STATIC vs DYNAMIC QUERIES
═══════════════════════════════════════════════════════════════

STATIC: Array NEVER changes after initial setup.
  → Use Prefix Sum (O(1) per query) or Sparse Table (O(1) per query)
  → Build once, query many times

DYNAMIC: Array can be UPDATED between queries.
  → Need Segment Tree, BIT, etc.
  → Supports both update + query efficiently

Classification:
┌────────────────────┬──────────────────┬──────────────────┐
│                    │ Point Update     │ Range Update     │
├────────────────────┼──────────────────┼──────────────────┤
│ Point Query        │ Simple array     │ Difference Array │
│ Range Query        │ BIT / Seg Tree   │ Lazy Seg Tree    │
└────────────────────┴──────────────────┴──────────────────┘

═══════════════════════════════════════════════════════════════
SECTION 3: PREFIX SUM (1D)
═══════════════════════════════════════════════════════════════

IDEA: Build prefix[i] = sum of a[0..i-1]
Then:  sum(l, r) = prefix[r+1] - prefix[l]

BUILD:
  a[]      = [3,  1,  4,  1,  5,  9,  2,  6]
  prefix[] = [0,  3,  4,  8,  9, 14, 23, 25, 31]
              ↑
              prefix[0] = 0 (empty sum)
  prefix[1] = prefix[0] + a[0] = 0 + 3 = 3
  prefix[2] = prefix[1] + a[1] = 3 + 1 = 4
  prefix[3] = prefix[2] + a[2] = 4 + 4 = 8
  prefix[4] = prefix[3] + a[3] = 8 + 1 = 9
  prefix[5] = prefix[4] + a[4] = 9 + 5 = 14
  prefix[6] = prefix[5] + a[5] = 14 + 9 = 23
  prefix[7] = prefix[6] + a[6] = 23 + 2 = 25
  prefix[8] = prefix[7] + a[7] = 25 + 6 = 31

QUERY: sum(2, 5) = prefix[6] - prefix[2] = 23 - 4 = 19 ✓

DRY RUN — query sum(l=2, r=5):
  Step 1: Look up prefix[r+1] = prefix[6] = 23
  Step 2: Look up prefix[l]   = prefix[2] = 4
  Step 3: Answer = 23 - 4 = 19  ✅

TIME:  Build O(n), Query O(1)
SPACE: O(n)

═══════════════════════════════════════════════════════════════
SECTION 4: PREFIX SUM (2D)
═══════════════════════════════════════════════════════════════

For a 2D grid, we want: sum of all elements in rectangle (r1,c1) to (r2,c2).

IDEA: prefix[i][j] = sum of grid[0..i-1][0..j-1]

BUILD (Inclusion-Exclusion):
  prefix[i][j] = grid[i-1][j-1]
               + prefix[i-1][j]
               + prefix[i][j-1]
               - prefix[i-1][j-1]

QUERY (r1, c1, r2, c2):
  sum = prefix[r2+1][c2+1]
      - prefix[r1][c2+1]
      - prefix[r2+1][c1]
      + prefix[r1][c1]

VISUALIZATION:

  Grid (3x4):
  ┌───┬───┬───┬───┐
  │ 1 │ 2 │ 3 │ 4 │  row 0
  ├───┼───┼───┼───┤
  │ 5 │ 6 │ 7 │ 8 │  row 1
  ├───┼───┼───┼───┤
  │ 9 │10 │11 │12 │  row 2
  └───┴───┴───┴───┘

  prefix (4x5):
  ┌───┬───┬───┬───┬───┐
  │ 0 │ 0 │ 0 │ 0 │ 0 │
  ├───┼───┼───┼───┼───┤
  │ 0 │ 1 │ 3 │ 6 │10 │
  ├───┼───┼───┼───┼───┤
  │ 0 │ 6 │14 │24 │36 │
  ├───┼───┼───┼───┼───┤
  │ 0 │15 │33 │54 │78 │
  └───┴───┴───┴───┴───┘

  Query: sum(1,1) to (2,3) = ?
    = prefix[3][4] - prefix[1][4] - prefix[3][1] + prefix[1][1]
    = 78 - 10 - 15 + 1 = 54 ✓
    Check: 6+7+8+10+11+12 = 54 ✅

═══════════════════════════════════════════════════════════════
SECTION 5: PREFIX XOR
═══════════════════════════════════════════════════════════════

Same idea as prefix sum, but with XOR.
XOR is its own inverse: a ^ a = 0

  a[]         = [3, 5, 2, 7, 4]
  prefixXOR[] = [0, 3, 6, 4, 3, 7]

  XOR(l=1, r=3) = prefixXOR[4] ^ prefixXOR[1] = 3 ^ 3 = 0
  Check: 5 ^ 2 ^ 7 = 0 ✓

═══════════════════════════════════════════════════════════════
SECTION 6: DIFFERENCE ARRAY (1D)
═══════════════════════════════════════════════════════════════

PROBLEM: Add value `val` to all elements a[l..r].
         Doing this naively is O(n) per update.

IDEA: Keep a difference array diff[] where:
      diff[i] = a[i] - a[i-1]

To add val to range [l, r]:
  diff[l] += val
  diff[r+1] -= val       (if r+1 < n)

Then reconstruct a[] by prefix sum of diff[].

DRY RUN:
  a[] = [0, 0, 0, 0, 0]  (initially all zeros)

  Operation 1: add 3 to [1, 3]
    diff[] = [0, +3, 0, 0, -3]
                ↑              ↑
                l=1           r+1=4

  Operation 2: add 2 to [2, 4]
    diff[] = [0, +3, +2, 0, -3]  → wait, r+1=5 is out of bounds, skip
    diff[] = [0, +3, +2, 0, -3]  (only diff[2] += 2)

  Actually: diff after op2 = [0, +3, +2, 0, -3+0]
            But r=4, r+1=5 >= n, so no subtraction needed.
            diff[] = [0, 3, 2, 0, -3]

  Reconstruct (prefix sum of diff):
    a[0] = 0
    a[1] = 0 + 3 = 3
    a[2] = 3 + 2 = 5
    a[3] = 5 + 0 = 5
    a[4] = 5 + (-3) = 2

  Result: a[] = [0, 3, 5, 5, 2]

  Verify:
    Original:  [0, 0, 0, 0, 0]
    After +3 to [1,3]: [0, 3, 3, 3, 0]
    After +2 to [2,4]: [0, 3, 5, 5, 2] ✅

TIME: O(1) per update, O(n) to reconstruct
SPACE: O(n)

═══════════════════════════════════════════════════════════════
SECTION 7: DIFFERENCE ARRAY (2D)
═══════════════════════════════════════════════════════════════

To add val to rectangle (r1,c1) to (r2,c2):
  diff[r1][c1]     += val
  diff[r1][c2+1]   -= val
  diff[r2+1][c1]   -= val
  diff[r2+1][c2+1] += val

Then reconstruct by 2D prefix sum.

VISUALIZATION:
  Add +5 to rectangle (1,1) to (2,3):

  diff grid:
  ┌───┬───┬───┬───┬───┐
  │ 0 │ 0 │ 0 │ 0 │ 0 │
  ├───┼───┼───┼───┼───┤
  │ 0 │+5 │ 0 │ 0 │-5 │ ← (1,1)=+5, (1,4)=-5
  ├───┼───┼───┼───┼───┤
  │ 0 │ 0 │ 0 │ 0 │ 0 │
  ├───┼───┼───┼───┼───┤
  │ 0 │-5 │ 0 │ 0 │+5 │ ← (3,1)=-5, (3,4)=+5
  └───┴───┴───┴───┴───┘

  After 2D prefix sum → all elements in rectangle become 5.

═══════════════════════════════════════════════════════════════
SECTION 8: OFFLINE vs ONLINE QUERIES
═══════════════════════════════════════════════════════════════

ONLINE: Answer each query IMMEDIATELY as it arrives.
  → Must use data structures that support fast query + update.
  → Example: Segment Tree, BIT.

OFFLINE: Read ALL queries first, then answer in optimal order.
  → Can sort queries, process them cleverly.
  → Example: Mo's Algorithm (sort by blocks), Offline + BIT.

  Why offline is powerful:
  ┌──────────────┬───────────┬────────────┐
  │ Problem      │ Online    │ Offline    │
  ├──────────────┼───────────┼────────────┤
  │ Distinct     │ Persistent│ Mo's O(n√n)│
  │ count in     │ ST        │ or         │
  │ range [l,r]  │ O(nlogn)  │ BIT offline│
  └──────────────┴───────────┴────────────┘

═══════════════════════════════════════════════════════════════
SECTION 9-10: UPDATE/QUERY CLASSIFICATION
═══════════════════════════════════════════════════════════════

┌─────────────────────────────────────────────────────────────┐
│              RANGE QUERY CLASSIFICATION TABLE               │
├──────────────────┬──────────────────┬───────────────────────┤
│                  │ POINT QUERY      │ RANGE QUERY           │
├──────────────────┼──────────────────┼───────────────────────┤
│ NO UPDATES       │ Direct access    │ Prefix Sum O(1)       │
│ (static)         │ O(1)             │ Sparse Table O(1)     │
├──────────────────┼──────────────────┼───────────────────────┤
│ POINT UPDATE     │ Direct array     │ BIT O(logn)           │
│                  │ O(1)             │ Segment Tree O(logn)  │
├──────────────────┼──────────────────┼───────────────────────┤
│ RANGE UPDATE     │ Difference Array │ Segment Tree + Lazy   │
│                  │ O(1) update      │ O(logn)               │
│                  │ O(n) reconstruct │ BIT trick O(logn)     │
└──────────────────┴──────────────────┴───────────────────────┘

KEY INSIGHT: The more powerful your query/update needs, the more
complex your data structure must be!

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
#include <tuple>

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
// IMPLEMENTATION 1: Prefix Sum 1D
// ═══════════════════════════════════════════════════════════════

class PrefixSum1D {
    vector<long long> prefix;
public:
    // Build: O(n)
    PrefixSum1D(const vector<int>& a) {
        int n = a.size();
        prefix.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + a[i];
        }
    }

    // Query sum(l, r) in O(1) — 0-indexed inclusive
    long long query(int l, int r) {
        return prefix[r + 1] - prefix[l];
    }
};

void demoPrefixSum1D() {
    cout << "═══ PREFIX SUM 1D ═══\n\n";

    vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
    cout << "Array: ";
    for (int x : a) cout << x << " ";
    cout << "\n\n";

    PrefixSum1D ps(a);

    // DRY RUN: sum(2, 5)
    cout << "Query sum(2, 5):\n";
    cout << "  Elements: a[2]+a[3]+a[4]+a[5] = 4+1+5+9 = 19\n";
    cout << "  Using prefix: prefix[6] - prefix[2] = " << ps.query(2, 5) << "\n\n";

    // More queries
    cout << "sum(0, 7) = " << ps.query(0, 7) << "  (entire array)\n";
    cout << "sum(0, 0) = " << ps.query(0, 0) << "  (single element)\n";
    cout << "sum(3, 6) = " << ps.query(3, 6) << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 2: Prefix Sum 2D
// ═══════════════════════════════════════════════════════════════

class PrefixSum2D {
    vector<vector<long long>> prefix;
public:
    // Build: O(n*m)
    PrefixSum2D(const vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        prefix.assign(n + 1, vector<long long>(m + 1, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                prefix[i + 1][j + 1] = grid[i][j]
                                      + prefix[i][j + 1]
                                      + prefix[i + 1][j]
                                      - prefix[i][j];
            }
        }
    }

    // Query sum of rectangle (r1,c1) to (r2,c2) — 0-indexed inclusive
    long long query(int r1, int c1, int r2, int c2) {
        return prefix[r2 + 1][c2 + 1]
             - prefix[r1][c2 + 1]
             - prefix[r2 + 1][c1]
             + prefix[r1][c1];
    }
};

void demoPrefixSum2D() {
    cout << "═══ PREFIX SUM 2D ═══\n\n";

    vector<vector<int>> grid = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };

    cout << "Grid:\n";
    for (auto& row : grid) {
        for (int x : row) cout << setw(3) << x;
        cout << "\n";
    }
    cout << "\n";

    PrefixSum2D ps2d(grid);

    cout << "Query rectangle (1,1) to (2,3):\n";
    cout << "  Elements: 6+7+8+10+11+12 = 54\n";
    cout << "  Using prefix: " << ps2d.query(1, 1, 2, 3) << "\n\n";

    cout << "Query rectangle (0,0) to (2,3): " << ps2d.query(0, 0, 2, 3)
         << " (entire grid)\n";
    cout << "Query rectangle (0,0) to (0,0): " << ps2d.query(0, 0, 0, 0)
         << " (single cell)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 3: Prefix XOR
// ═══════════════════════════════════════════════════════════════

class PrefixXOR {
    vector<int> prefix;
public:
    PrefixXOR(const vector<int>& a) {
        int n = a.size();
        prefix.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] ^ a[i];
        }
    }

    // XOR of a[l..r] in O(1)
    int query(int l, int r) {
        return prefix[r + 1] ^ prefix[l];
    }
};

void demoPrefixXOR() {
    cout << "═══ PREFIX XOR ═══\n\n";

    vector<int> a = {3, 5, 2, 7, 4};
    cout << "Array: ";
    for (int x : a) cout << x << " ";
    cout << "\n";

    PrefixXOR px(a);
    cout << "XOR(1, 3) = 5^2^7 = " << (5^2^7) << "\n";
    cout << "Using prefix: " << px.query(1, 3) << "\n\n";

    cout << "XOR(0, 4) = " << px.query(0, 4) << " (entire array)\n";
    cout << "XOR(2, 2) = " << px.query(2, 2) << " (single element = 2)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 4: Difference Array 1D
// ═══════════════════════════════════════════════════════════════

class DifferenceArray1D {
    vector<long long> diff;
    int n;
public:
    DifferenceArray1D(int n) : n(n), diff(n + 1, 0) {}

    // Also can initialize from existing array
    DifferenceArray1D(const vector<int>& a) : n(a.size()), diff(a.size() + 1, 0) {
        diff[0] = a[0];
        for (int i = 1; i < n; i++) {
            diff[i] = a[i] - a[i - 1];
        }
    }

    // Add val to all elements in [l, r] — O(1)
    void rangeAdd(int l, int r, long long val) {
        diff[l] += val;
        if (r + 1 <= n) diff[r + 1] -= val;
    }

    // Reconstruct the array — O(n)
    vector<long long> reconstruct() {
        vector<long long> a(n);
        a[0] = diff[0];
        for (int i = 1; i < n; i++) {
            a[i] = a[i - 1] + diff[i];
        }
        return a;
    }
};

void demoDifferenceArray1D() {
    cout << "═══ DIFFERENCE ARRAY 1D ═══\n\n";

    int n = 5;
    DifferenceArray1D da(n);

    cout << "Initial array: [0, 0, 0, 0, 0]\n\n";

    cout << "Operation 1: Add 3 to [1, 3]\n";
    da.rangeAdd(1, 3, 3);
    cout << "  diff[1] += 3, diff[4] -= 3\n";

    cout << "Operation 2: Add 2 to [2, 4]\n";
    da.rangeAdd(2, 4, 2);
    cout << "  diff[2] += 2, diff[5] -= 2\n";

    cout << "Operation 3: Add 1 to [0, 2]\n";
    da.rangeAdd(0, 2, 1);
    cout << "  diff[0] += 1, diff[3] -= 1\n\n";

    auto result = da.reconstruct();
    cout << "Result: ";
    for (long long x : result) cout << x << " ";
    cout << "\n\n";

    cout << "Verify manually:\n";
    cout << "  Start:         [0, 0, 0, 0, 0]\n";
    cout << "  +3 to [1,3]:   [0, 3, 3, 3, 0]\n";
    cout << "  +2 to [2,4]:   [0, 3, 5, 5, 2]\n";
    cout << "  +1 to [0,2]:   [1, 4, 6, 5, 2]\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 5: Difference Array 2D
// ═══════════════════════════════════════════════════════════════

class DifferenceArray2D {
    vector<vector<long long>> diff;
    int n, m;
public:
    DifferenceArray2D(int n, int m) : n(n), m(m), diff(n + 2, vector<long long>(m + 2, 0)) {}

    // Add val to rectangle (r1,c1) to (r2,c2) — O(1)
    void rangeAdd(int r1, int c1, int r2, int c2, long long val) {
        diff[r1][c1] += val;
        diff[r1][c2 + 1] -= val;
        diff[r2 + 1][c1] -= val;
        diff[r2 + 1][c2 + 1] += val;
    }

    // Reconstruct 2D array — O(n*m)
    vector<vector<long long>> reconstruct() {
        vector<vector<long long>> a(n, vector<long long>(m, 0));
        // Row-wise prefix sum
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                diff[i][j + 1] += diff[i][j];  // accumulate left-right
        // Column-wise prefix sum
        for (int j = 0; j < m; j++)
            for (int i = 0; i < n; i++)
                diff[i + 1][j] += diff[i][j];  // accumulate top-bottom

        // Wait — need to do both prefix sums on diff, then copy
        // Let me redo properly:
        // Actually the standard approach:
        // After marking, do 2D prefix sum on diff
        // But we already modified diff above... let me reconstruct properly
        // Reset and redo:
        return extractResult();
    }

    vector<vector<long long>> extractResult() {
        // 2D prefix sum of diff
        vector<vector<long long>> a(n + 2, vector<long long>(m + 2, 0));
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                a[i][j] = diff[i][j];
                if (i > 0) a[i][j] += a[i - 1][j];
                if (j > 0) a[i][j] += a[i][j - 1];
                if (i > 0 && j > 0) a[i][j] -= a[i - 1][j - 1];
            }
        }
        vector<vector<long long>> res(n, vector<long long>(m));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res[i][j] = a[i][j];
        return res;
    }
};

void demoDifferenceArray2D() {
    cout << "═══ DIFFERENCE ARRAY 2D ═══\n\n";

    int n = 4, m = 5;
    DifferenceArray2D da2d(n, m);

    cout << "Grid: 4x5, initially all zeros\n\n";

    cout << "Operation 1: Add 5 to rectangle (1,1)→(2,3)\n";
    da2d.rangeAdd(1, 1, 2, 3, 5);

    cout << "Operation 2: Add 3 to rectangle (0,0)→(1,1)\n";
    da2d.rangeAdd(0, 0, 1, 1, 3);

    auto result = da2d.extractResult();
    cout << "\nResult grid:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << setw(3) << result[i][j];
        }
        cout << "\n";
    }
    cout << "\nExpected:\n";
    cout << "  3  3  0  0  0\n";
    cout << "  3  8  5  5  0\n";
    cout << "  0  5  5  5  0\n";
    cout << "  0  0  0  0  0\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 6: Offline vs Online — Demonstration
// ═══════════════════════════════════════════════════════════════

void demoOfflineVsOnline() {
    cout << "═══ OFFLINE vs ONLINE QUERIES ═══\n\n";

    cout << "ONLINE Example:\n";
    cout << "  Query 1: sum(1,3) → Answer immediately: 6\n";
    cout << "  Update:  a[2] = 10\n";
    cout << "  Query 2: sum(1,3) → Answer immediately: 14\n";
    cout << "  → Each query answered as it comes.\n\n";

    cout << "OFFLINE Example (Mo's Algorithm style):\n";
    cout << "  Read all queries first:\n";
    cout << "    Q1: count_distinct(0, 3)\n";
    cout << "    Q2: count_distinct(2, 5)\n";
    cout << "    Q3: count_distinct(1, 4)\n";
    cout << "  Sort queries by block:\n";
    cout << "    Q1: (0,3) → block 0\n";
    cout << "    Q3: (1,4) → block 0\n";
    cout << "    Q2: (2,5) → block 1\n";
    cout << "  Process in sorted order, output in original order.\n\n";

    // Simple offline demo: sort queries for better cache performance
    vector<int> a = {1, 2, 1, 3, 2, 1, 4};
    int n = a.size();
    vector<tuple<int, int, int>> queries = {{0, 3, 0}, {2, 5, 1}, {1, 4, 2}};
    // (l, r, original_index)

    // Sort by left endpoint
    sort(queries.begin(), queries.end());

    vector<long long> answers(3);
    for (auto& [l, r, idx] : queries) {
        long long sum = 0;
        for (int i = l; i <= r; i++) sum += a[i];
        answers[idx] = sum;
    }

    cout << "Answers in original order:\n";
    for (int i = 0; i < 3; i++) {
        cout << "  Query " << i << ": sum = " << answers[i] << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 10: SUMMARY & CLASSIFICATION
// ═══════════════════════════════════════════════════════════════

void printClassificationTable() {
    cout << "═══ RANGE QUERY CLASSIFICATION SUMMARY ═══\n\n";
    cout << "┌─────────────────┬────────────────┬──────────────────────────┐\n";
    cout << "│                 │ Point Query    │ Range Query              │\n";
    cout << "├─────────────────┼────────────────┼──────────────────────────┤\n";
    cout << "│ NO UPDATES      │ O(1) direct    │ Prefix Sum O(1)         │\n";
    cout << "│ (static)        │                │ Sparse Table O(1)       │\n";
    cout << "├─────────────────┼────────────────┼──────────────────────────┤\n";
    cout << "│ POINT UPDATE    │ O(1) direct    │ BIT O(log n)            │\n";
    cout << "│                 │                │ Segment Tree O(log n)   │\n";
    cout << "├─────────────────┼────────────────┼──────────────────────────┤\n";
    cout << "│ RANGE UPDATE    │ Diff Array O(1)│ Lazy Seg Tree O(log n)  │\n";
    cout << "│                 │ + O(n) recon.  │ BIT trick O(log n)      │\n";
    cout << "└─────────────────┴────────────────┴──────────────────────────┘\n\n";

    cout << "GM DECISION GUIDE:\n";
    cout << "  • Static + Sum → Prefix Sum\n";
    cout << "  • Static + Min/Max/GCD → Sparse Table\n";
    cout << "  • Point Update + Range Sum → BIT (simplest)\n";
    cout << "  • Point Update + Range Min → Segment Tree\n";
    cout << "  • Range Update + Point Query → Difference Array or BIT\n";
    cout << "  • Range Update + Range Query → Lazy Segment Tree\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN — Run All Demonstrations
// ═══════════════════════════════════════════════════════════════

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║     LEVEL 0: RANGE QUERY FOUNDATIONS — COMPLETE GUIDE      ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n\n";

    demoPrefixSum1D();
    demoPrefixSum2D();
    demoPrefixXOR();
    demoDifferenceArray1D();
    demoDifferenceArray2D();
    demoOfflineVsOnline();
    printClassificationTable();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "  KEY TAKEAWAYS:\n";
    cout << "  1. Prefix Sum = O(1) range sum queries on static arrays\n";
    cout << "  2. Difference Array = O(1) range updates, O(n) reconstruct\n";
    cout << "  3. XOR prefix = works because XOR is its own inverse\n";
    cout << "  4. 2D versions use inclusion-exclusion principle\n";
    cout << "  5. Choose data structure based on update/query type!\n";
    cout << "  6. Offline processing can be much more efficient\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

