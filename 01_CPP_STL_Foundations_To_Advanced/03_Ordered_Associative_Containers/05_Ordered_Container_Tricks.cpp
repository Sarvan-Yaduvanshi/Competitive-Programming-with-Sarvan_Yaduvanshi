/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           05 — ORDERED CONTAINER ADVANCED TRICKS                           ║
║           From Zero to Grandmaster — Expert Patterns                       ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. C++17 Node Handles (extract/merge)
 2. Set as Sorted Array Replacement
 3. Interval Set Pattern
 4. Ordered Iteration Tricks
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: SET AS SORTED ARRAY REPLACEMENT
// ═══════════════════════════════════════════════════════════════
/*
 Sometimes you need a "sorted array" with fast insert/delete.
 set provides exactly that!

 Operations:
   k-th smallest → advance(s.begin(), k)  O(k) — or use PBDS for O(log n)
   Rank of x     → distance(s.begin(), s.find(x))  O(n) — or use PBDS
   Predecessor   → prev(s.lower_bound(x))
   Successor     → s.upper_bound(x)
*/

void setAsSortedArray() {
    cout << "═══ SET AS SORTED ARRAY ═══\n\n";

    set<int> s = {10, 30, 50, 20, 40};

    // k-th smallest (0-indexed)
    int k = 2;
    auto it = s.begin();
    advance(it, k);
    cout << k << "-th smallest: " << *it << "\n";

    // Rank of element
    int x = 30;
    int rank = distance(s.begin(), s.find(x));
    cout << "Rank of " << x << ": " << rank << "\n";

    // Delete and re-insert (modify element)
    // Can't modify set elements directly — erase + insert
    s.erase(30);
    s.insert(35);
    cout << "After replace 30→35: ";
    for (int v : s) cout << v << " ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: INTERVAL SET PATTERN (GM-LEVEL)
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Maintain a set of non-overlapping intervals.
 Support: add interval, remove interval, query point.

 Use set<pair<int,int>> sorted by start point.
 When adding [l,r], merge with overlapping intervals.

 DRY RUN:
   Add [1,3]: intervals = {[1,3]}
   Add [5,7]: intervals = {[1,3], [5,7]}
   Add [2,6]: merge! → {[1,7]}
   Add [9,10]: intervals = {[1,7], [9,10]}
   Remove [4,5]: split [1,7] → {[1,3], [6,7], [9,10]}
*/

void intervalSetPattern() {
    cout << "═══ INTERVAL SET PATTERN ═══\n\n";

    // Store intervals as set<pair<int,int>> sorted by start
    set<pair<int, int>> intervals;

    // Add interval with merge
    auto addInterval = [&](int l, int r) {
        auto it = intervals.lower_bound({l, l});
        // Check previous interval too
        if (it != intervals.begin()) {
            --it;
            if (it->second < l) ++it;  // No overlap with previous
        }
        // Merge overlapping intervals
        while (it != intervals.end() && it->first <= r) {
            l = min(l, it->first);
            r = max(r, it->second);
            it = intervals.erase(it);
        }
        intervals.insert({l, r});
    };

    // Query if point is covered
    auto queryPoint = [&](int p) -> bool {
        auto it = intervals.upper_bound({p, INT_MAX});
        if (it == intervals.begin()) return false;
        --it;
        return it->first <= p && p <= it->second;
    };

    addInterval(1, 3);
    cout << "Add [1,3]: ";
    for (auto& [a, b] : intervals) cout << "[" << a << "," << b << "] ";
    cout << "\n";

    addInterval(5, 7);
    cout << "Add [5,7]: ";
    for (auto& [a, b] : intervals) cout << "[" << a << "," << b << "] ";
    cout << "\n";

    addInterval(2, 6);
    cout << "Add [2,6] (merge!): ";
    for (auto& [a, b] : intervals) cout << "[" << a << "," << b << "] ";
    cout << "\n";

    addInterval(9, 10);
    cout << "Add [9,10]: ";
    for (auto& [a, b] : intervals) cout << "[" << a << "," << b << "] ";
    cout << "\n\n";

    cout << "Query point 4: " << (queryPoint(4) ? "covered" : "not covered") << "\n";
    cout << "Query point 8: " << (queryPoint(8) ? "covered" : "not covered") << "\n";
    cout << "Query point 9: " << (queryPoint(9) ? "covered" : "not covered") << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: EXTRACT AND MERGE (C++17)
// ═══════════════════════════════════════════════════════════════

void demonstrateExtractMerge() {
    cout << "═══ EXTRACT & MERGE (C++17) ═══\n\n";

    // extract — remove node without deallocation, can reinsert elsewhere
    set<int> s1 = {1, 2, 3, 4, 5};
    set<int> s2 = {10, 20, 30};

    auto node = s1.extract(3);  // Remove 3 from s1
    if (!node.empty()) {
        node.value() = 33;  // Modify the extracted value!
        s2.insert(move(node));  // Insert into s2
    }

    cout << "s1 (after extract 3→33): ";
    for (int x : s1) cout << x << " ";
    cout << "\n";
    cout << "s2 (after insert 33): ";
    for (int x : s2) cout << x << " ";
    cout << "\n\n";

    // merge — move all elements from one set to another
    set<int> a = {1, 3, 5, 7};
    set<int> b = {2, 4, 6, 8};
    a.merge(b);  // Moves elements from b to a (b becomes mostly empty)
    cout << "After merge: a = ";
    for (int x : a) cout << x << " ";
    cout << "\n";
    cout << "After merge: b = ";
    for (int x : b) cout << x << " ";
    cout << "(empty or only duplicates)\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: PRACTICAL CP PATTERN — NEXT/PREV ELEMENT
// ═══════════════════════════════════════════════════════════════

void nextPrevPattern() {
    cout << "═══ NEXT/PREV ELEMENT PATTERN ═══\n\n";

    set<int> s = {2, 5, 8, 12, 15, 20};
    int query = 10;

    // Find next >= query
    auto nextIt = s.lower_bound(query);
    if (nextIt != s.end()) {
        cout << "Next >= " << query << ": " << *nextIt << "\n";
    }

    // Find prev < query
    if (nextIt != s.begin()) {
        auto prevIt = prev(nextIt);
        cout << "Prev < " << query << ": " << *prevIt << "\n";
    }

    // Find ceiling and floor
    // ceiling(x) = smallest element >= x = *lower_bound(x)
    // floor(x) = largest element <= x = *prev(upper_bound(x))
    auto ceil_it = s.lower_bound(query);
    auto floor_it = s.upper_bound(query);
    if (ceil_it != s.end()) cout << "Ceiling(" << query << ") = " << *ceil_it << "\n";
    if (floor_it != s.begin()) cout << "Floor(" << query << ") = " << *prev(floor_it) << "\n";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    setAsSortedArray();
    intervalSetPattern();
    demonstrateExtractMerge();
    nextPrevPattern();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. Set works as sorted array with O(log n) insert/erase\n";
    cout << "2. Interval set: use set<pair> + merge on add\n";
    cout << "3. C++17 extract() lets you modify keys without realloc\n";
    cout << "4. merge() transfers nodes between sets in O(n log n)\n";
    cout << "5. ceiling/floor pattern: lower_bound/prev(upper_bound)\n";

    return 0;
}

