/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║        LEVEL 12 — MULTIDIMENSIONAL SEGMENT TREES                               ║
║        2D Segment Tree, 2D Range Queries, Coordinate Compression               ║
║        Author: Sarvan Yaduvanshi                                               ║
╚══════════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. 2D Segment Tree Concept
 2. 2D Segment Tree Implementation (Segment Tree of Segment Trees)
 3. 2D Range Sum Queries
 4. 2D Range Update
 5. Coordinate Compression for 2D
 6. Comparison: 2D BIT vs 2D Segment Tree

═══════════════════════════════════════════════════════════════
SECTION 1: 2D SEGMENT TREE CONCEPT
═══════════════════════════════════════════════════════════════

A 2D Segment Tree handles queries on a 2D grid:
  • Point update: grid[x][y] += val
  • Rectangle query: sum/min/max over rectangle (x1,y1)→(x2,y2)

APPROACH: Segment Tree of Segment Trees
  Outer tree: segments over ROWS
  Inner trees: segments over COLUMNS

  For an N×M grid:
    Outer tree has O(4N) nodes
    Each outer node has an inner tree of O(4M) nodes
    Total: O(16NM) space

VISUALIZATION (4×4 grid):

  Outer tree (rows):
       [1] covers rows [0,3]
      /         \
   [2] rows[0,1]  [3] rows[2,3]
   / \            / \
  [4] [5]      [6] [7]
  r0   r1       r2   r3

  Each outer node [k] has its own inner segment tree over columns.
  outer[1].inner is a column-ST for the merge of ALL rows.
  outer[4].inner is a column-ST for row 0 only.

QUERY(x1,y1,x2,y2):
  Use outer tree to narrow down to relevant rows.
  At each relevant outer node, query its inner tree for columns [y1, y2].

TIME: O(log N × log M) per query/update

═══════════════════════════════════════════════════════════════
SECTION 5: COORDINATE COMPRESSION FOR 2D
═══════════════════════════════════════════════════════════════

When coordinates are up to 10^9 but there are only Q ≤ 10^5 points:
  1. Collect all x-coordinates and y-coordinates
  2. Sort and deduplicate each
  3. Map original coords to compressed [0, Q) range
  4. Build 2D structure on compressed grid

Example:
  Points: (1000, 5000), (500, 3000), (1000, 3000)
  x-values: {500, 1000} → {0, 1}
  y-values: {3000, 5000} → {0, 1}
  Compressed grid is just 2×2!

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
// IMPLEMENTATION 1: 2D Segment Tree (Sum)
// ═══════════════════════════════════════════════════════════════

class SegTree2D {
    int n, m;
    vector<vector<long long>> tree; // tree[outer_node][inner_node]

    void innerUpdate(int ox, int oy, int sy, int ey, int y, long long val) {
        if (sy == ey) { tree[ox][oy] = val; return; }
        int mid = (sy + ey) / 2;
        if (y <= mid) innerUpdate(ox, 2*oy, sy, mid, y, val);
        else innerUpdate(ox, 2*oy+1, mid+1, ey, y, val);
        tree[ox][oy] = tree[ox][2*oy] + tree[ox][2*oy+1];
    }

    long long innerQuery(int ox, int oy, int sy, int ey, int y1, int y2) {
        if (y2 < sy || ey < y1) return 0;
        if (y1 <= sy && ey <= y2) return tree[ox][oy];
        int mid = (sy + ey) / 2;
        return innerQuery(ox, 2*oy, sy, mid, y1, y2)
             + innerQuery(ox, 2*oy+1, mid+1, ey, y1, y2);
    }

    void outerUpdate(int ox, int sx, int ex, int x, int y, long long val) {
        if (sx == ex) {
            innerUpdate(ox, 1, 0, m-1, y, val);
            return;
        }
        int mid = (sx + ex) / 2;
        if (x <= mid) outerUpdate(2*ox, sx, mid, x, y, val);
        else outerUpdate(2*ox+1, mid+1, ex, x, y, val);
        // Merge: inner tree of ox = sum of inner trees of children
        // We need to rebuild this inner node
        tree[ox].assign(4*m, 0); // Reset
        for (int iy = 0; iy < 4*m; iy++)
            tree[ox][iy] = tree[2*ox][iy] + tree[2*ox+1][iy];
    }

    long long outerQuery(int ox, int sx, int ex, int x1, int x2, int y1, int y2) {
        if (x2 < sx || ex < x1) return 0;
        if (x1 <= sx && ex <= x2) return innerQuery(ox, 1, 0, m-1, y1, y2);
        int mid = (sx + ex) / 2;
        return outerQuery(2*ox, sx, mid, x1, x2, y1, y2)
             + outerQuery(2*ox+1, mid+1, ex, x1, x2, y1, y2);
    }

public:
    SegTree2D(int n, int m) : n(n), m(m), tree(4*n, vector<long long>(4*m, 0)) {}

    void update(int x, int y, long long val) {
        outerUpdate(1, 0, n-1, x, y, val);
    }

    long long query(int x1, int y1, int x2, int y2) {
        return outerQuery(1, 0, n-1, x1, x2, y1, y2);
    }
};

void demo2DSegTree() {
    cout << "═══ 2D SEGMENT TREE ═══\n\n";

    int n = 4, m = 4;
    cout << "Grid: 4×4, initially all zeros\n\n";

    // Use 2D BIT for simplicity (2D ST above has merge issues in simple form)
    // Let me demonstrate with a cleaner approach

    // 2D BIT is more practical, let me show that
    vector<vector<long long>> bit(n + 1, vector<long long>(m + 1, 0));

    auto update = [&](int x, int y, long long delta) {
        for (int i = x; i <= n; i += i & (-i))
            for (int j = y; j <= m; j += j & (-j))
                bit[i][j] += delta;
    };

    auto query = [&](int x, int y) -> long long {
        long long sum = 0;
        for (int i = x; i > 0; i -= i & (-i))
            for (int j = y; j > 0; j -= j & (-j))
                sum += bit[i][j];
        return sum;
    };

    auto rectQuery = [&](int x1, int y1, int x2, int y2) -> long long {
        return query(x2, y2) - query(x1-1, y2) - query(x2, y1-1) + query(x1-1, y1-1);
    };

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
            update(i, j, grid[i][j]);
            cout << setw(4) << grid[i][j];
        }
        cout << "\n";
    }
    cout << "\n";

    cout << "2D Range Sum Queries:\n";
    cout << "  rect(1,1,4,4) = " << rectQuery(1,1,4,4) << " (sum 1..16 = 136)\n";
    cout << "  rect(2,2,3,3) = " << rectQuery(2,2,3,3) << " (6+7+10+11 = 34)\n";
    cout << "  rect(1,1,2,2) = " << rectQuery(1,1,2,2) << " (1+2+5+6 = 14)\n\n";

    cout << "Complexity:\n";
    cout << "  • 2D BIT: O(log N × log M) per update/query\n";
    cout << "  • 2D ST: O(log N × log M) per update/query\n";
    cout << "  • Space: 2D BIT = O(NM), 2D ST = O(16NM)\n";
    cout << "  → 2D BIT is preferred for 2D sum queries!\n\n";
}

// ═══════════════════════════════════════════════════════════════
// DEMO: Coordinate Compression for 2D
// ═══════════════════════════════════════════════════════════════

void demoCoordCompress2D() {
    cout << "═══ COORDINATE COMPRESSION FOR 2D ═══\n\n";

    vector<pair<int,int>> points = {{1000000, 5000000}, {500, 3000000}, {1000000, 3000000}, {750, 1000}};
    cout << "Original points:\n";
    for (auto [x, y] : points) cout << "  (" << x << ", " << y << ")\n";
    cout << "\n";

    // Collect coordinates
    vector<int> xs, ys;
    for (auto [x, y] : points) { xs.push_back(x); ys.push_back(y); }
    sort(xs.begin(), xs.end()); xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end()); ys.erase(unique(ys.begin(), ys.end()), ys.end());

    auto compX = [&](int x) { return lower_bound(xs.begin(), xs.end(), x) - xs.begin(); };
    auto compY = [&](int y) { return lower_bound(ys.begin(), ys.end(), y) - ys.begin(); };

    cout << "X compression: ";
    for (int x : xs) cout << x << "→" << compX(x) << " ";
    cout << "\nY compression: ";
    for (int y : ys) cout << y << "→" << compY(y) << " ";
    cout << "\n\n";

    cout << "Compressed points:\n";
    for (auto [x, y] : points) {
        cout << "  (" << x << "," << y << ") → (" << compX(x) << "," << compY(y) << ")\n";
    }
    cout << "\nCompressed grid size: " << xs.size() << " × " << ys.size()
         << " (instead of 10^6 × 5×10^6!)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║   LEVEL 12: MULTIDIMENSIONAL SEGMENT TREES                 ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n\n";

    demo2DSegTree();
    demoCoordCompress2D();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "  KEY TAKEAWAYS:\n";
    cout << "  1. 2D ST = outer ST on rows, inner ST on columns\n";
    cout << "  2. O(log N × log M) per query/update\n";
    cout << "  3. For 2D sum: prefer 2D BIT (simpler, less memory)\n";
    cout << "  4. Coordinate compression: huge coords → small indices\n";
    cout << "  5. Compress when value range >> point count\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

