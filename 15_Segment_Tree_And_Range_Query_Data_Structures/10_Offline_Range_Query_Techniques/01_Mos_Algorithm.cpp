/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║        LEVEL 9 — OFFLINE RANGE QUERY TECHNIQUES (Mo's Algorithm)               ║
║        Sqrt Decomposition for Offline Queries                                  ║
║        Author: Sarvan Yaduvanshi                                               ║
╚══════════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Mo's Algorithm Concept (Sqrt Decomposition for Queries)
 2. How Mo's Algorithm Works — Step by Step
 3. Basic Mo's Implementation — Count Distinct
 4. Mo's Algorithm with Updates
 5. Hilbert Curve Ordering Optimization
 6. Offline Queries with Sorting
 7. Complete Dry Run

═══════════════════════════════════════════════════════════════
SECTION 1: MO'S ALGORITHM CONCEPT
═══════════════════════════════════════════════════════════════

Mo's Algorithm answers OFFLINE range queries in O((N+Q)√N).

KEY IDEA: Sort queries smartly, then maintain a "current window"
[curL, curR] that we expand/shrink by adding/removing one element
at a time.

WHY SQRT?
  Divide indices into blocks of size √N.
  Sort queries by (block of L, then R).
  This ensures that:
    • L moves O(Q√N) total (within blocks, max √N per query)
    • R moves O(N√N) total (sorted within each block, monotone)
  Total: O((N+Q)√N)

REQUIREMENTS:
  ① Queries must be OFFLINE (read all first, answer in any order)
  ② Must be able to ADD/REMOVE single elements efficiently
  ③ Element addition/removal must be O(1) or O(log n)

═══════════════════════════════════════════════════════════════
SECTION 2: HOW MO'S WORKS — STEP BY STEP
═══════════════════════════════════════════════════════════════

Array: a[] = {1, 2, 1, 3, 2, 1, 4}    n = 7
Block size: √7 ≈ 2

Queries (0-indexed):
  Q0: [1, 4]  (elements: 2, 1, 3, 2)
  Q1: [0, 3]  (elements: 1, 2, 1, 3)
  Q2: [3, 6]  (elements: 3, 2, 1, 4)
  Q3: [1, 2]  (elements: 2, 1)

Assign blocks (block = L / √N):
  Q0: L=1, block=0
  Q1: L=0, block=0
  Q2: L=3, block=1
  Q3: L=1, block=0

Sort by (block, R):
  Block 0: Q1(0,3), Q3(1,2), Q0(1,4)   ← sorted by R
  Block 1: Q2(3,6)

Processing order: Q1, Q3, Q0, Q2

Step 1: Process Q1 [0, 3]
  Window: expand from empty to [0, 3]
  Add a[0]=1, a[1]=2, a[2]=1, a[3]=3
  Distinct count = 3 (values: 1, 2, 3)

Step 2: Process Q3 [1, 2]
  Move L from 0 → 1: remove a[0]=1
  Move R from 3 → 2: remove a[3]=3
  Window: [1, 2], elements: 2, 1
  Distinct count = 2

Step 3: Process Q0 [1, 4]
  Move R from 2 → 4: add a[3]=3, a[4]=2
  Window: [1, 4], elements: 2, 1, 3, 2
  Distinct count = 3

Step 4: Process Q2 [3, 6]
  Move L from 1 → 3: remove a[1]=2, a[2]=1
  Move R from 4 → 6: add a[5]=1, a[6]=4
  Window: [3, 6], elements: 3, 2, 1, 4
  Distinct count = 4

Results (reorder to original): Q0=3, Q1=3, Q2=4, Q3=2

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
// IMPLEMENTATION 1: Mo's Algorithm — Count Distinct Elements
// ═══════════════════════════════════════════════════════════════

class MoDistinct {
    int n, blockSize;
    vector<int> a;
    vector<int> cnt;  // frequency of each value
    int distinct;     // current number of distinct elements

    void add(int idx) {
        if (cnt[a[idx]]++ == 0) distinct++;
    }

    void remove(int idx) {
        if (--cnt[a[idx]] == 0) distinct--;
    }

public:
    // Solve all queries, return answers in original order
    vector<int> solve(const vector<int>& arr, vector<pair<int,int>>& queries) {
        a = arr;
        n = a.size();
        blockSize = max(1, (int)sqrt(n));

        // Coordinate compress if values are large
        int maxVal = *max_element(a.begin(), a.end());
        cnt.assign(maxVal + 1, 0);
        distinct = 0;

        int Q = queries.size();
        vector<int> answers(Q);

        // Create query indices and sort
        vector<int> order(Q);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int i, int j) {
            int bi = queries[i].first / blockSize;
            int bj = queries[j].first / blockSize;
            if (bi != bj) return bi < bj;
            return (bi & 1) ? (queries[i].second > queries[j].second)
                            : (queries[i].second < queries[j].second);
            // Alternating sort direction = zigzag optimization
        });

        int curL = 0, curR = -1;

        for (int qi : order) {
            int l = queries[qi].first;
            int r = queries[qi].second;

            // Expand/shrink window to [l, r]
            while (curR < r) add(++curR);
            while (curL > l) add(--curL);
            while (curR > r) remove(curR--);
            while (curL < l) remove(curL++);

            answers[qi] = distinct;
        }

        return answers;
    }
};

void demoMoBasic() {
    cout << "═══ MO'S ALGORITHM — COUNT DISTINCT ELEMENTS ═══\n\n";

    vector<int> a = {1, 2, 1, 3, 2, 1, 4};
    cout << "Array: ";
    for (int x : a) cout << x << " ";
    cout << "\n\n";

    vector<pair<int,int>> queries = {{1, 4}, {0, 3}, {3, 6}, {1, 2}, {0, 6}};
    cout << "Queries:\n";
    for (int i = 0; i < (int)queries.size(); i++)
        cout << "  Q" << i << ": [" << queries[i].first << ", " << queries[i].second << "]\n";
    cout << "\n";

    MoDistinct mo;
    vector<int> answers = mo.solve(a, queries);

    cout << "Answers:\n";
    for (int i = 0; i < (int)queries.size(); i++) {
        int l = queries[i].first, r = queries[i].second;
        cout << "  Q" << i << " [" << l << "," << r << "]: distinct = " << answers[i];

        // Verify
        set<int> s;
        for (int j = l; j <= r; j++) s.insert(a[j]);
        cout << " (verify: " << s.size() << ")" << (answers[i] == (int)s.size() ? " ✓" : " ✗");
        cout << "\n";
    }
    cout << "\n";

    cout << "Block size = √7 ≈ 2\n";
    cout << "Complexity: O((N+Q)√N) = O((7+5)√7) ≈ O(32)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// IMPLEMENTATION 2: Mo's with Updates (3D Mo)
// ═══════════════════════════════════════════════════════════════

void demoMoWithUpdates() {
    cout << "═══ MO'S ALGORITHM WITH UPDATES (3D MO) ═══\n\n";

    cout << "CONCEPT: Handle update operations BETWEEN queries.\n\n";

    cout << "Each query becomes: (L, R, timestamp)\n";
    cout << "  timestamp = number of updates before this query\n\n";

    cout << "Block size: n^(2/3)  (not √n!)\n";
    cout << "Sort: by (L/block, R/block, timestamp)\n";
    cout << "Complexity: O(n^(5/3))\n\n";

    cout << "ALGORITHM:\n";
    cout << "  1. Separate operations into queries[] and updates[]\n";
    cout << "  2. For each query, record its timestamp\n";
    cout << "  3. Sort queries by (L/block, R/block, time)\n";
    cout << "  4. When processing, also advance/retreat time:\n";
    cout << "     • Apply update: if pos ∈ [curL, curR], swap values\n";
    cout << "     • Undo update: swap back\n\n";

    cout << "PSEUDO-CODE:\n";
    cout << "  for each query in sorted order:\n";
    cout << "    // Move time forward/backward\n";
    cout << "    while (curTime < query.time)\n";
    cout << "      apply update[curTime++]\n";
    cout << "    while (curTime > query.time)\n";
    cout << "      undo update[--curTime]\n";
    cout << "    // Move L and R as usual\n";
    cout << "    // ... (same as basic Mo's)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: HILBERT CURVE ORDERING
// ═══════════════════════════════════════════════════════════════

void demoHilbert() {
    cout << "═══ HILBERT CURVE ORDERING OPTIMIZATION ═══\n\n";

    cout << "Standard Mo's sort: by (block of L, R)\n";
    cout << "  • Good but not optimal constant factor\n\n";

    cout << "Hilbert curve sort: maps 2D point (L, R) to 1D Hilbert index\n";
    cout << "  • Sort queries by Hilbert index\n";
    cout << "  • Reduces total pointer movement by ~2-3x in practice\n\n";

    cout << "Hilbert index computation (for K bits):\n";
    cout << "  long long hilbert(int x, int y) {\n";
    cout << "    long long d = 0;\n";
    cout << "    for (int s = (1 << K) >> 1; s; s >>= 1) {\n";
    cout << "      bool rx = (x & s) > 0;\n";
    cout << "      bool ry = (y & s) > 0;\n";
    cout << "      d += (long long)s * s * ((3 * rx) ^ ry);\n";
    cout << "      // Rotate quadrant\n";
    cout << "      if (!ry) {\n";
    cout << "        if (rx) { x = s-1-x; y = s-1-y; }\n";
    cout << "        swap(x, y);\n";
    cout << "      }\n";
    cout << "    }\n";
    cout << "    return d;\n";
    cout << "  }\n\n";

    cout << "Then sort queries by hilbert(L, R).\n";
    cout << "This gives ~2-3x speedup over standard Mo's on random data.\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║   LEVEL 9: OFFLINE RANGE QUERY TECHNIQUES                  ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n\n";

    demoMoBasic();
    demoMoWithUpdates();
    demoHilbert();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "  KEY TAKEAWAYS:\n";
    cout << "  1. Mo's = OFFLINE sqrt decomposition for range queries\n";
    cout << "  2. Sort by (block of L, R with zigzag): O((N+Q)√N)\n";
    cout << "  3. Add/Remove must be O(1) for optimal performance\n";
    cout << "  4. With Updates: block = n^(2/3), O(n^(5/3))\n";
    cout << "  5. Hilbert ordering: ~2-3x faster in practice\n";
    cout << "  6. Use for: distinct count, mode, XOR, frequency queries\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

