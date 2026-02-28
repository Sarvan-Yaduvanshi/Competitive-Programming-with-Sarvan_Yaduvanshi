/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Mo's Algorithm — Offline Query Processing with Two Pointer Movement
 *  Level   : Expert → GM (Codeforces 1800 → 2400+)
 * ============================================================================
 *
 *  ▶ WHAT IS MO'S ALGORITHM?
 *  ─────────────────────────
 *  Mo's Algorithm is an OFFLINE technique for answering range queries
 *  [L, R] on an array. It uses a conceptual "two pointer" that slides
 *  across the array, adding/removing elements at the boundaries.
 *
 *  KEY IDEA:
 *  - Sort all queries in a special order (by block of L, then by R).
 *  - Maintain a "current window" [curL, curR] with two pointers.
 *  - For each query, expand/shrink the window to match [L, R].
 *  - Because of the sorting order, total pointer movement is O(N√N).
 *
 *  ▶ WHY IS THIS TWO POINTER?
 *  ──────────────────────────
 *  Mo's Algorithm IS literally a two pointer technique:
 *  - curL pointer moves left/right
 *  - curR pointer moves left/right
 *  - We "add" or "remove" elements at the boundaries
 *  - The trick is the ORDERING of queries that minimizes total movement
 *
 *  ▶ COMPLEXITY:
 *  ─────────────
 *  Block size B = √N
 *  Total pointer movement: O(N√N + Q√N) ≈ O((N+Q)√N)
 *  Each add/remove: O(1) amortized
 *  Overall: O((N+Q)√N)
 *
 *  ▶ REQUIREMENTS:
 *  ───────────────
 *  ✅ OFFLINE (all queries known in advance)
 *  ✅ add(element) and remove(element) both O(1) or O(log)
 *  ✅ No updates to the array (for basic Mo's — Mo with updates exists)
 *
 *  PROBLEMS:
 *  CF 86D  — Powerful Array (classic Mo's, 2000)
 *            https://codeforces.com/problemset/problem/86/D
 *  CF 617E — XOR and Favorite Number (Mo's + XOR prefix, 2100)
 *            https://codeforces.com/problemset/problem/617/E
 *  SPOJ DQUERY — D-query (count distinct in range, Mo's)
 *            https://www.spoj.com/problems/DQUERY/
 *  CF 220B — Little Elephant and Array (Mo's, 1800)
 *            https://codeforces.com/problemset/problem/220/B
 *  CF 375D — Tree and Queries (Mo's on Euler tour, 2000)
 *            https://codeforces.com/problemset/problem/375/D
 *  CSES 1734 — Distinct Values Queries (merge sort tree OR Mo's)
 *            https://cses.fi/problemset/task/1734
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
using ll = long long;

// ============================================================================
// MO'S ALGORITHM — TEMPLATE
// ============================================================================
/*
 * STEP 1: Read all queries and store them with their indices.
 * STEP 2: Sort queries by (L / block_size, R). If same block, sort by R.
 *         OPTIMIZATION: For even blocks sort R ascending, odd blocks R descending.
 * STEP 3: Maintain curL, curR = 0, -1 (empty window).
 * STEP 4: For each query [ql, qr]:
 *         - Expand/shrink curR to qr by calling add/remove.
 *         - Expand/shrink curL to ql by calling add/remove.
 *         - Store the current answer for this query.
 * STEP 5: Output answers in original query order.
 */

const int MAXN = 200005;
int freq[MAXN]; // Frequency of each value in current window
int arr[MAXN];
int n, q;
int BLOCK;

struct Query {
    int l, r, idx;
    bool operator<(const Query& other) const {
        int blockL = l / BLOCK, blockR = other.l / BLOCK;
        if (blockL != blockR) return blockL < blockR;
        // Zigzag optimization
        return (blockL & 1) ? (r > other.r) : (r < other.r);
    }
};

// ============================================================================
// EXAMPLE 1: Count Distinct Elements in Range (SPOJ DQUERY)
// ============================================================================
/*
 * For each query [L, R], count how many distinct values appear.
 *
 * add(x): freq[x]++; if freq[x] == 1, distinctCount++.
 * remove(x): freq[x]--; if freq[x] == 0, distinctCount--.
 */
int distinctCount = 0;

void addDistinct(int idx) {
    if (freq[arr[idx]]++ == 0) distinctCount++;
}

void removeDistinct(int idx) {
    if (--freq[arr[idx]] == 0) distinctCount--;
}

void solveDistinct() {
    cin >> n;
    BLOCK = max(1, (int)sqrt(n));
    for (int i = 0; i < n; i++) cin >> arr[i];

    cin >> q;
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--; queries[i].r--; // 0-indexed
        queries[i].idx = i;
    }

    sort(queries.begin(), queries.end());

    vector<int> answers(q);
    int curL = 0, curR = -1;

    for (auto& qr : queries) {
        // Expand/shrink to match query range
        while (curR < qr.r) addDistinct(++curR);
        while (curL > qr.l) addDistinct(--curL);
        while (curR > qr.r) removeDistinct(curR--);
        while (curL < qr.l) removeDistinct(curL++);

        answers[qr.idx] = distinctCount;
    }

    for (int i = 0; i < q; i++) cout << answers[i] << "\n";

    // Cleanup
    fill(freq, freq + MAXN, 0);
    distinctCount = 0;
}

// ============================================================================
// EXAMPLE 2: CF 86D — Powerful Array — Sum of cnt[x]² * x
// ============================================================================
/*
 * For each query [L, R], compute sum of (count(x))² * x for all x in [L,R].
 *
 * When we add element x (freq goes from c to c+1):
 *   Change = (c+1)²*x - c²*x = (2c+1)*x
 * When we remove element x (freq goes from c to c-1):
 *   Change = (c-1)²*x - c²*x = -(2c-1)*x
 */
ll powerSum = 0;

void addPower(int idx) {
    int x = arr[idx];
    powerSum += (2LL * freq[x] + 1) * x;
    freq[x]++;
}

void removePower(int idx) {
    int x = arr[idx];
    freq[x]--;
    powerSum -= (2LL * freq[x] + 1) * x;
}

void solvePowerful() {
    cin >> n >> q;
    BLOCK = max(1, (int)sqrt(n));
    for (int i = 0; i < n; i++) cin >> arr[i];

    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--; queries[i].r--;
        queries[i].idx = i;
    }

    sort(queries.begin(), queries.end());

    vector<ll> answers(q);
    int curL = 0, curR = -1;

    for (auto& qr : queries) {
        while (curR < qr.r) addPower(++curR);
        while (curL > qr.l) addPower(--curL);
        while (curR > qr.r) removePower(curR--);
        while (curL < qr.l) removePower(curL++);

        answers[qr.idx] = powerSum;
    }

    for (int i = 0; i < q; i++) cout << answers[i] << "\n";

    // Cleanup
    fill(freq, freq + MAXN, 0);
    powerSum = 0;
}

// ============================================================================
// VISUAL EXPLANATION OF MO'S POINTER MOVEMENT
// ============================================================================
/*
 * Array:  [a0, a1, a2, a3, a4, a5, a6, a7]
 * Block:  [  BLOCK 0  ][  BLOCK 1  ][  BLK 2  ]
 *
 * Queries sorted by (L/block, R):
 * Q1: [0, 3]  → Block 0, R=3
 * Q2: [1, 5]  → Block 0, R=5
 * Q3: [0, 7]  → Block 0, R=7
 * Q4: [3, 4]  → Block 1, R=4
 * Q5: [4, 7]  → Block 1, R=7
 *
 * Pointer movement:
 * Start: [0, -1] (empty)
 * Q1: expand R to 3 → [0, 3]  (4 add ops)
 * Q2: expand R to 5, shrink L to 1 → [1, 5]  (2+1 = 3 ops)
 * Q3: expand R to 7, expand L to 0 → [0, 7]  (2+1 = 3 ops)
 * Q4: shrink R to 4, shrink L to 3 → [3, 4]  (3+3 = 6 ops)
 * Q5: expand R to 7, shrink L to 4 → [4, 7]  (3+1 = 4 ops)
 *
 * Total: 20 ops for 5 queries. Without Mo's: could be O(N*Q).
 * With Mo's: guaranteed O(N√N) total.
 *
 * ZIGZAG OPTIMIZATION:
 * In even blocks, sort R ascending. In odd blocks, sort R descending.
 * This makes R pointer zigzag instead of jumping back, reducing constant factor ~40%.
 */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Uncomment one to test:
    // solveDistinct();   // SPOJ DQUERY style
    // solvePowerful();   // CF 86D style

    // Demo with hardcoded data
    cout << "Mo's Algorithm Template Loaded.\n";
    cout << "Complexity: O((N+Q) * sqrt(N))\n";
    cout << "\nKey insight: Mo's IS a two-pointer technique!\n";
    cout << "curL and curR are the two pointers that slide across the array.\n";
    cout << "The sorting order ensures total movement is O(N*sqrt(N)).\n";

    return 0;
}

