/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║        LEVEL 7 — ADVANCED FENWICK TREE                                         ║
║        Range Update, 2D BIT, Coordinate Compression                            ║
║        Author: Sarvan Yaduvanshi                                               ║
╚══════════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Range Update + Point Query BIT
 2. Point Update + Range Query BIT (standard)
 3. Range Update + Range Query BIT (Two BIT trick)
 4. 2D Fenwick Tree
 5. Fenwick Tree with Coordinate Compression
 6. Complete Dry Runs

═══════════════════════════════════════════════════════════════
SECTION 1: RANGE UPDATE + POINT QUERY
═══════════════════════════════════════════════════════════════

IDEA: Store DIFFERENCE ARRAY in BIT.
  range_add(l, r, val):
    bit.update(l, +val)
    bit.update(r+1, -val)
  point_query(i):
    return bit.prefix_sum(i)   ← prefix sum of diff = actual value

DRY RUN:
  a[] = [0, 0, 0, 0, 0]  (1-indexed)
  Add +3 to [2, 4]:
    BIT update at 2: +3
    BIT update at 5: -3
  Point query at 3:
    prefix_sum(3) = BIT[1]+BIT[2]+BIT[3] = 0+3+0 = 3 ✓

═══════════════════════════════════════════════════════════════
SECTION 3: RANGE UPDATE + RANGE QUERY (Two BIT Trick)
═══════════════════════════════════════════════════════════════

PROBLEM: Support both range_add(l, r, val) AND range_sum(l, r).

MATH: Let d[i] = amount added to position i (conceptual difference).
  prefix_sum(x) = Σ(i=1 to x) Σ(j=1 to i) d[j]
                = Σ(j=1 to x) d[j] * (x - j + 1)
                = (x + 1) * Σ(j=1 to x) d[j] - Σ(j=1 to x) d[j] * j

  So we need TWO BITs:
    B1[i] stores d[i]
    B2[i] stores d[i] * i

  prefix_sum(x) = (x + 1) * B1.query(x) - B2.query(x)

  For range_add(l, r, val):
    B1.update(l, +val);     B1.update(r+1, -val);
    B2.update(l, +val*l);   B2.update(r+1, -val*(r+1));

═══════════════════════════════════════════════════════════════
SECTION 4: 2D FENWICK TREE
═══════════════════════════════════════════════════════════════

Extends BIT to 2D grid:
  update(x, y, delta): add delta to cell (x, y)
  query(x, y): prefix sum from (1,1) to (x,y)
  query(x1,y1,x2,y2): sum of rectangle

Same lowbit trick, but nested loops:
  update: for i=x; i<=n; i+=i&(-i)
            for j=y; j<=m; j+=j&(-j)
              bit[i][j] += delta

  query:  for i=x; i>0; i-=i&(-i)
            for j=y; j>0; j-=j&(-j)
              sum += bit[i][j]

VISUALIZATION (4x4 grid):

  (1,1)  (1,2)  (1,3)  (1,4)
  (2,1)  (2,2)  (2,3)  (2,4)
  (3,1)  (3,2)  (3,3)  (3,4)
  (4,1)  (4,2)  (4,3)  (4,4)

  update(2, 3, +5): affects BIT cells:
    (2,3)→(2,4)→(4,3)→(4,4)

  query(3, 3): sum of rectangle (1,1)→(3,3)
    Visit: (3,3)→(3,2)→(2,3)→(2,2)→→...

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
// Basic FenwickTree (1-indexed) — needed for demos below
// ═══════════════════════════════════════════════════════════════

class FenwickTree {
    int n;
    vector<long long> bit;
public:
    FenwickTree(int n) : n(n), bit(n + 1, 0) {}
    void update(int i, long long delta) {
        for (; i <= n; i += i & (-i)) bit[i] += delta;
    }
    long long query(int i) {
        long long s = 0;
        for (; i > 0; i -= i & (-i)) s += bit[i];
        return s;
    }
    long long query(int l, int r) { return query(r) - query(l - 1); }
};

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 1: Range Update + Point Query BIT
// ═══════════════════════════════════════════════════════════════

class BITRangeUpdatePointQuery {
    int n;
    vector<long long> bit;

    void update(int i, long long delta) {
        for (; i <= n; i += i & (-i))
            bit[i] += delta;
    }

    long long prefixSum(int i) {
        long long sum = 0;
        for (; i > 0; i -= i & (-i))
            sum += bit[i];
        return sum;
    }

public:
    BITRangeUpdatePointQuery(int n) : n(n), bit(n + 1, 0) {}

    // Add val to all elements in [l, r] (1-indexed)
    void rangeAdd(int l, int r, long long val) {
        update(l, val);
        if (r + 1 <= n) update(r + 1, -val);
    }

    // Get value at position i (1-indexed)
    long long pointQuery(int i) {
        return prefixSum(i);
    }
};

void demoRangeUpdatePointQuery() {
    cout << "═══ RANGE UPDATE + POINT QUERY BIT ═══\n\n";

    int n = 8;
    BITRangeUpdatePointQuery bit(n);

    cout << "Initial: [0, 0, 0, 0, 0, 0, 0, 0]\n\n";

    cout << "Add +3 to [2, 5]:\n";
    bit.rangeAdd(2, 5, 3);
    cout << "  Expected: [0, 3, 3, 3, 3, 0, 0, 0]\n  Result:   ";
    for (int i = 1; i <= n; i++) cout << bit.pointQuery(i) << " ";
    cout << "\n\n";

    cout << "Add +5 to [4, 7]:\n";
    bit.rangeAdd(4, 7, 5);
    cout << "  Expected: [0, 3, 3, 8, 8, 5, 5, 0]\n  Result:   ";
    for (int i = 1; i <= n; i++) cout << bit.pointQuery(i) << " ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 2: Range Update + Range Query BIT (Two BIT trick)
// ═══════════════════════════════════════════════════════════════

class BITRangeUpdateRangeQuery {
    int n;
    vector<long long> b1, b2; // Two BITs

    void update(vector<long long>& bit, int i, long long delta) {
        for (; i <= n; i += i & (-i))
            bit[i] += delta;
    }

    long long query(const vector<long long>& bit, int i) {
        long long sum = 0;
        for (int j = i; j > 0; j -= j & (-j))
            sum += bit[j];
        return sum;
    }

public:
    BITRangeUpdateRangeQuery(int n) : n(n), b1(n + 1, 0), b2(n + 1, 0) {}

    // Add val to all elements in [l, r] (1-indexed)
    void rangeAdd(int l, int r, long long val) {
        update(b1, l, val);
        update(b1, r + 1, -val);
        update(b2, l, val * l);
        update(b2, r + 1, -val * (r + 1));
    }

    // Prefix sum: sum(1..x)
    long long prefixSum(int x) {
        return (long long)(x + 1) * query(b1, x) - query(b2, x);
    }

    // Range sum: sum(l..r)
    long long rangeSum(int l, int r) {
        return prefixSum(r) - prefixSum(l - 1);
    }
};

void demoRangeUpdateRangeQuery() {
    cout << "═══ RANGE UPDATE + RANGE QUERY BIT (TWO BIT TRICK) ═══\n\n";

    int n = 8;
    BITRangeUpdateRangeQuery bit(n);

    cout << "Add +3 to [2, 5]: expected [0,3,3,3,3,0,0,0]\n";
    bit.rangeAdd(2, 5, 3);
    cout << "  sum(1, 8) = " << bit.rangeSum(1, 8) << " (12)\n";
    cout << "  sum(2, 5) = " << bit.rangeSum(2, 5) << " (12)\n";
    cout << "  sum(1, 3) = " << bit.rangeSum(1, 3) << " (6)\n\n";

    cout << "Add +5 to [4, 7]: expected [0,3,3,8,8,5,5,0]\n";
    bit.rangeAdd(4, 7, 5);
    cout << "  sum(1, 8) = " << bit.rangeSum(1, 8) << " (32)\n";
    cout << "  sum(4, 7) = " << bit.rangeSum(4, 7) << " (26)\n";
    cout << "  sum(1, 1) = " << bit.rangeSum(1, 1) << " (0)\n\n";

    cout << "DRY RUN — rangeAdd(2, 5, 3):\n";
    cout << "  B1: update(2, +3), update(6, -3)\n";
    cout << "  B2: update(2, +3*2=6), update(6, -3*6=-18)\n";
    cout << "  prefixSum(5) = 6 * B1.query(5) - B2.query(5)\n";
    cout << "               = 6 * 3 - 6 = 12 ✓\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 3: 2D Fenwick Tree
// ═══════════════════════════════════════════════════════════════

class FenwickTree2D {
    int n, m;
    vector<vector<long long>> bit;

public:
    FenwickTree2D(int n, int m) : n(n), m(m), bit(n + 1, vector<long long>(m + 1, 0)) {}

    // Add delta to cell (x, y) — 1-indexed
    void update(int x, int y, long long delta) {
        for (int i = x; i <= n; i += i & (-i))
            for (int j = y; j <= m; j += j & (-j))
                bit[i][j] += delta;
    }

    // Prefix sum from (1,1) to (x,y)
    long long query(int x, int y) {
        long long sum = 0;
        for (int i = x; i > 0; i -= i & (-i))
            for (int j = y; j > 0; j -= j & (-j))
                sum += bit[i][j];
        return sum;
    }

    // Sum of rectangle (x1,y1) to (x2,y2) — 1-indexed
    long long query(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
};

void demo2DBIT() {
    cout << "═══ 2D FENWICK TREE ═══\n\n";

    int n = 4, m = 4;
    FenwickTree2D bit(n, m);

    // Fill grid
    int grid[5][5] = {
        {0,0,0,0,0},
        {0,1,2,3,4},
        {0,5,6,7,8},
        {0,9,10,11,12},
        {0,13,14,15,16}
    };

    cout << "Grid (1-indexed):\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            bit.update(i, j, grid[i][j]);
            cout << setw(4) << grid[i][j];
        }
        cout << "\n";
    }
    cout << "\n";

    cout << "Rectangle sum queries:\n";
    cout << "  (1,1)→(4,4) = " << bit.query(1, 1, 4, 4) << " (sum 1..16 = 136)\n";
    cout << "  (2,2)→(3,3) = " << bit.query(2, 2, 3, 3) << " (6+7+10+11 = 34)\n";
    cout << "  (1,1)→(2,2) = " << bit.query(1, 1, 2, 2) << " (1+2+5+6 = 14)\n";
    cout << "  (3,3)→(4,4) = " << bit.query(3, 3, 4, 4) << " (11+12+15+16 = 54)\n\n";

    cout << "Update: add +10 to cell (2, 3)\n";
    bit.update(2, 3, 10);
    cout << "  (2,2)→(3,3) = " << bit.query(2, 2, 3, 3) << " (was 34, now 44)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 4: BIT with Coordinate Compression
// ═══════════════════════════════════════════════════════════════

void demoCoordinateCompression() {
    cout << "═══ BIT WITH COORDINATE COMPRESSION ═══\n\n";

    cout << "PROBLEM: Count elements ≤ x in a stream of values up to 10^9.\n";
    cout << "  Values are huge → can't create BIT of size 10^9!\n";
    cout << "  SOLUTION: Compress values to [1, n].\n\n";

    vector<int> values = {1000000, 50, 999999, 50, 75, 1000000};
    cout << "Values: ";
    for (int x : values) cout << x << " ";
    cout << "\n\n";

    // Coordinate compression
    vector<int> sorted_vals = values;
    sort(sorted_vals.begin(), sorted_vals.end());
    sorted_vals.erase(unique(sorted_vals.begin(), sorted_vals.end()), sorted_vals.end());

    auto compress = [&](int val) -> int {
        return lower_bound(sorted_vals.begin(), sorted_vals.end(), val) - sorted_vals.begin() + 1;
    };

    int m = sorted_vals.size();
    cout << "Compressed mapping:\n";
    for (int i = 0; i < m; i++)
        cout << "  " << sorted_vals[i] << " → " << i + 1 << "\n";
    cout << "\n";

    FenwickTree bit(m); // BIT of size = number of unique values

    cout << "Processing values and counting:\n";
    for (int i = 0; i < (int)values.size(); i++) {
        int c = compress(values[i]);
        // Count of elements ≤ values[i] already inserted
        long long countLE = bit.query(c);
        cout << "  Insert " << values[i] << " (→" << c << "), "
             << "elements ≤ " << values[i] << " before = " << countLE << "\n";
        bit.update(c, 1);
    }
    cout << "\n";

    cout << "After all insertions:\n";
    for (int i = 0; i < m; i++) {
        cout << "  Count of value " << sorted_vals[i] << " = "
             << bit.query(i + 1, i + 1) << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║   LEVEL 7: ADVANCED FENWICK TREE — COMPLETE GUIDE          ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n\n";

    demoRangeUpdatePointQuery();
    demoRangeUpdateRangeQuery();
    demo2DBIT();
    demoCoordinateCompression();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "  KEY TAKEAWAYS:\n";
    cout << "  1. Range Update + Point Query: Store diff array in BIT\n";
    cout << "  2. Range Update + Range Query: Two BIT trick\n";
    cout << "  3. 2D BIT: Nested lowbit loops, O(log n * log m)\n";
    cout << "  4. Coordinate Compression: Map huge values to [1,n]\n";
    cout << "  5. All BIT tricks maintain O(log n) per operation\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

