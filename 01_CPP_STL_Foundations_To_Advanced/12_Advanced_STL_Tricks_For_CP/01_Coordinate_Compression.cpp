/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — COORDINATE COMPRESSION                                      ║
║           From Zero to Grandmaster                                         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

 PROBLEM: Values up to 10^9 but only N ≤ 10^5 distinct values.
          Need to use as array indices (segment tree, BIT, DP).

 TECHNIQUE: Map values to [0, N-1] range preserving relative order.

 STEPS:
   1. Collect all values
   2. sort + unique
   3. For each value, index = lower_bound position

 DRY RUN: [100, 5, 10^9, 5, 100, 42]
   sorted unique: [5, 42, 100, 10^9]
   compressed:    [2, 0, 3, 0, 2, 1]
*/

#include <bits/stdc++.h>
using namespace std;

// Generic coordinate compression
struct CoordCompress {
    vector<int> vals;

    void add(int x) { vals.push_back(x); }

    void build() {
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
    }

    int compress(int x) {
        return lower_bound(vals.begin(), vals.end(), x) - vals.begin();
    }

    int decompress(int idx) { return vals[idx]; }

    int size() { return vals.size(); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "═══ COORDINATE COMPRESSION ═══\n\n";

    // Example 1: Basic compression
    vector<int> arr = {1000000000, 5, 100, 5, 1000000000, 42};
    CoordCompress cc;
    for (int x : arr) cc.add(x);
    cc.build();

    cout << "Original:   ";
    for (int x : arr) cout << x << " ";
    cout << "\nCompressed: ";
    for (int x : arr) cout << cc.compress(x) << " ";
    cout << "\nDistinct values: " << cc.size() << "\n\n";

    // Example 2: Use with BIT/Segment Tree
    cout << "═══ USE CASE: Count Inversions with BIT ═══\n\n";
    /*
     After compression, values fit in [0, N-1] range.
     Can now use BIT/Fenwick tree for:
       - Inversions counting
       - Range frequency queries
       - Segment tree updates
    */
    vector<int> arr2 = {5, 3, 8, 1, 7};
    CoordCompress cc2;
    for (int x : arr2) cc2.add(x);
    cc2.build();

    cout << "Array: ";
    for (int x : arr2) cout << x << " ";
    cout << "\nCompressed: ";
    for (int x : arr2) cout << cc2.compress(x) << " ";
    cout << "\nNow usable as BIT/SegTree indices!\n\n";

    // Example 3: 2D coordinate compression
    cout << "═══ 2D COORDINATE COMPRESSION ═══\n\n";
    vector<pair<int, int>> points = {{100, 200}, {50, 300}, {100, 100}, {200, 200}};

    CoordCompress cx, cy;
    for (auto& [x, y] : points) { cx.add(x); cy.add(y); }
    cx.build(); cy.build();

    cout << "Points:     ";
    for (auto& [x, y] : points) cout << "(" << x << "," << y << ") ";
    cout << "\nCompressed: ";
    for (auto& [x, y] : points)
        cout << "(" << cx.compress(x) << "," << cy.compress(y) << ") ";
    cout << "\n\n";

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. sort + unique + lower_bound = coordinate compression\n";
    cout << "2. Maps 10^9 range to [0, N-1] for BIT/SegTree\n";
    cout << "3. Works for 2D by compressing x and y separately\n";
    cout << "4. Preserve relative order of values\n";
    cout << "5. O(N log N) preprocessing, O(log N) per query\n";

    return 0;
}

