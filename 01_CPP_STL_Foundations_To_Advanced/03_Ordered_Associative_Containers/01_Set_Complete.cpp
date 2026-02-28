/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — SET COMPLETE GUIDE                                          ║
║           From Zero to Grandmaster — Sorted Unique Collection              ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. What is set? (Red-Black Tree internals)
 2. insert, emplace, erase, find, count
 3. lower_bound, upper_bound — THE POWER TOOLS
 4. Custom Comparator
 5. Set Iteration Tricks
 6. CP Problem: Find Closest Element

SET INTERNALS:
──────────────
  set is implemented as a BALANCED BST (Red-Black Tree).
  All elements are UNIQUE and AUTO-SORTED.

  set = {1, 3, 5, 7, 9}

  Internal BST:        5
                     /   \
                    3     7
                   /       \
                  1         9

  All operations: O(log n) — insert, erase, find, lower_bound
  Space: O(n) with ~40 bytes per node overhead (pointers + color)

GM TIP: set is your go-to when you need:
  1. Unique sorted elements
  2. O(log n) predecessor/successor queries
  3. Range-based queries with lower_bound/upper_bound
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BASIC OPERATIONS
// ═══════════════════════════════════════════════════════════════

void demonstrateBasicOps() {
    cout << "═══ SET BASIC OPERATIONS ═══\n\n";

    set<int> s;

    // insert
    s.insert(5);
    s.insert(3);
    s.insert(8);
    s.insert(1);
    s.insert(5);  // Duplicate — IGNORED!
    cout << "After inserts: ";
    for (int x : s) cout << x << " ";
    cout << "(5 appears once)\n";

    // emplace (slightly faster, constructs in-place)
    s.emplace(7);
    s.emplace(2);

    // find
    auto it = s.find(3);
    if (it != s.end()) cout << "Found 3 ✓\n";
    it = s.find(4);
    if (it == s.end()) cout << "4 not found ✓\n";

    // count (0 or 1 for set)
    cout << "count(5) = " << s.count(5) << "\n";
    cout << "count(4) = " << s.count(4) << "\n";

    // erase
    s.erase(3);  // Erase by value
    cout << "After erase(3): ";
    for (int x : s) cout << x << " ";
    cout << "\n";

    s.erase(s.begin());  // Erase by iterator (smallest element)
    cout << "After erase(begin): ";
    for (int x : s) cout << x << " ";
    cout << "\n";

    // size, empty
    cout << "Size: " << s.size() << ", Empty: " << s.empty() << "\n";

    // Min and max
    cout << "Min: " << *s.begin() << ", Max: " << *prev(s.end()) << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: lower_bound & upper_bound — THE POWER TOOLS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 s.lower_bound(x) → iterator to FIRST element >= x
 s.upper_bound(x) → iterator to FIRST element > x

 CRITICAL: Use MEMBER functions, not std:: versions!
   s.lower_bound(x)  → O(log n) ✓
   lower_bound(s.begin(), s.end(), x) → O(n) ✗ (no random access!)

 DRY RUN:
   s = {1, 3, 5, 7, 9}

   lower_bound(5) → iterator to 5 (first >= 5)
   upper_bound(5) → iterator to 7 (first > 5)
   lower_bound(4) → iterator to 5 (first >= 4)
   upper_bound(4) → iterator to 5 (first > 4)
   lower_bound(10) → end() (nothing >= 10)

 USEFUL PATTERNS:
   Predecessor of x: prev(s.lower_bound(x))  (if exists)
   Successor of x:   s.upper_bound(x)         (if != end)
   Elements in [a,b]: iterate from lower_bound(a) to upper_bound(b)
*/

void demonstrateBounds() {
    cout << "═══ lower_bound & upper_bound ═══\n\n";

    set<int> s = {10, 20, 30, 40, 50, 60, 70};

    cout << "Set: ";
    for (int x : s) cout << x << " ";
    cout << "\n\n";

    // lower_bound
    auto lb = s.lower_bound(30);
    cout << "lower_bound(30) = " << *lb << " (first >= 30)\n";
    lb = s.lower_bound(35);
    cout << "lower_bound(35) = " << *lb << " (first >= 35 → 40)\n";

    // upper_bound
    auto ub = s.upper_bound(30);
    cout << "upper_bound(30) = " << *ub << " (first > 30 → 40)\n\n";

    // Find predecessor (element just before x)
    int x = 45;
    auto it = s.lower_bound(x);
    if (it != s.begin()) {
        --it;
        cout << "Predecessor of " << x << " = " << *it << "\n";
    }

    // Find successor (element just after x)
    it = s.upper_bound(x);
    if (it != s.end()) {
        cout << "Successor of " << x << " = " << *it << "\n\n";
    }

    // Count elements in range [a, b]
    int a = 25, b = 55;
    auto from = s.lower_bound(a);
    auto to = s.upper_bound(b);
    cout << "Elements in [" << a << ", " << b << "]: ";
    for (auto it = from; it != to; ++it) cout << *it << " ";
    cout << "\n";
    cout << "Count: " << distance(from, to) << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: CUSTOM COMPARATOR
// ═══════════════════════════════════════════════════════════════
/*
 Default: set<int> uses less<int> → ascending order
 Custom:  set<int, greater<int>> → descending order

 For custom structs, define operator< or pass comparator.
*/

void demonstrateCustomComparator() {
    cout << "═══ CUSTOM COMPARATOR ═══\n\n";

    // Descending set
    set<int, greater<int>> desc_set = {3, 1, 4, 1, 5, 9};
    cout << "Descending set: ";
    for (int x : desc_set) cout << x << " ";
    cout << "\n";

    // Custom struct
    struct Point {
        int x, y;
    };

    // Comparator as lambda
    auto cmp = [](const Point& a, const Point& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    };

    set<Point, decltype(cmp)> points(cmp);
    points.insert({3, 4});
    points.insert({1, 2});
    points.insert({3, 1});
    points.insert({1, 5});

    cout << "Points sorted (x then y): ";
    for (auto& [px, py] : points) cout << "(" << px << "," << py << ") ";
    cout << "\n";

    // Sort by distance from origin
    auto dist_cmp = [](const Point& a, const Point& b) {
        int da = a.x * a.x + a.y * a.y;
        int db = b.x * b.x + b.y * b.y;
        if (da != db) return da < db;
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    };

    set<Point, decltype(dist_cmp)> by_dist(dist_cmp);
    by_dist.insert({3, 4});  // dist=25
    by_dist.insert({1, 1});  // dist=2
    by_dist.insert({0, 5});  // dist=25
    by_dist.insert({2, 2});  // dist=8

    cout << "Points by distance: ";
    for (auto& [px, py] : by_dist)
        cout << "(" << px << "," << py << ":d²=" << px*px+py*py << ") ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: CP PROBLEM — FIND CLOSEST ELEMENT
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Given a set of numbers and queries, for each query find
          the element closest to the query value.

 APPROACH: Use lower_bound, check both predecessor and successor.

 DRY RUN:
   Set: {1, 5, 10, 15, 20}
   Query: 7
     lower_bound(7) → 10 (first >= 7)
     predecessor: 5 (prev of 10)
     |7-5| = 2, |7-10| = 3 → closest = 5

   Query: 13
     lower_bound(13) → 15
     predecessor: 10
     |13-10| = 3, |13-15| = 2 → closest = 15
*/

void findClosest() {
    cout << "═══ CP PROBLEM: FIND CLOSEST ELEMENT ═══\n\n";

    set<int> s = {1, 5, 10, 15, 20};
    vector<int> queries = {7, 13, 0, 25, 10};

    cout << "Set: ";
    for (int x : s) cout << x << " ";
    cout << "\n\n";

    for (int q : queries) {
        auto it = s.lower_bound(q);
        int closest;

        if (it == s.end()) {
            closest = *prev(it);  // q > all elements
        } else if (it == s.begin()) {
            closest = *it;  // q <= smallest element
        } else {
            int upper = *it;
            int lower = *prev(it);
            closest = (q - lower <= upper - q) ? lower : upper;
        }

        cout << "Query " << q << " → closest = " << closest
             << " (distance = " << abs(q - closest) << ")\n";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateBasicOps();
    demonstrateBounds();
    demonstrateCustomComparator();
    findClosest();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. set = balanced BST, unique sorted elements, O(log n) all ops\n";
    cout << "2. ALWAYS use s.lower_bound() (not std::lower_bound) → O(log n)!\n";
    cout << "3. Min = *s.begin(), Max = *prev(s.end())\n";
    cout << "4. Predecessor/Successor via lower_bound + prev/next\n";
    cout << "5. Custom comparator for structs or non-default ordering\n";
    cout << "6. set handles duplicates by IGNORING them\n";

    return 0;
}

/*
 PRACTICE PROBLEMS:
 ──────────────────
 1. [CSES Distinct Numbers]  https://cses.fi/problemset/task/1621
 2. [CSES Towers]            https://cses.fi/problemset/task/1073
 3. [LC Contains Duplicate III] https://leetcode.com/problems/contains-duplicate-iii/
 4. [CF B. Towers]           https://codeforces.com/problemset/problem/37/A
*/

