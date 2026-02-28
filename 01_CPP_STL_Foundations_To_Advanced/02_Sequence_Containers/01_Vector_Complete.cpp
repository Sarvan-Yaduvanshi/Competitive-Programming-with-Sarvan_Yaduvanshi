/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — VECTOR COMPLETE GUIDE                                       ║
║           From Zero to Grandmaster — The King of CP Containers             ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1.  Initialization Methods (7 ways)
 2.  push_back vs emplace_back
 3.  reserve() and capacity() — Avoiding TLE
 4.  resize() vs reserve()
 5.  clear() and shrink_to_fit()
 6.  erase() — Single, Range, Erase-Remove Idiom
 7.  Iteration Methods (5 ways)
 8.  Vector of Vectors (2D)
 9.  CP Tricks with Vector
 10. Example Problem: Coordinate Compression

WHAT IS VECTOR?
───────────────
  vector<T> is a DYNAMIC ARRAY that can grow/shrink.
  It stores elements in CONTIGUOUS memory (cache-friendly!).
  This is the #1 most used container in competitive programming.

  Internal structure:
  ┌───┬───┬───┬───┬───┬───┬───┬───┐
  │ 1 │ 2 │ 3 │ 4 │ 5 │   │   │   │  size=5, capacity=8
  └───┴───┴───┴───┴───┴───┴───┴───┘
  ← used elements →  ← reserved →

  When size exceeds capacity, vector REALLOCATES (doubles capacity).
  This is O(n) but happens rarely → amortized O(1) push_back.
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: INITIALIZATION METHODS
// ═══════════════════════════════════════════════════════════════
/*
 7 WAYS TO CREATE A VECTOR:
 ──────────────────────────
 1. Empty:           vector<int> v;
 2. With size:       vector<int> v(n);         // n zeros
 3. With size+value: vector<int> v(n, val);    // n copies of val
 4. Initializer:     vector<int> v = {1,2,3};
 5. From another:    vector<int> v2(v1);       // copy
 6. From range:      vector<int> v(arr, arr+n);
 7. From iterators:  vector<int> v(s.begin(), s.end());
*/

void demonstrateInitialization() {
    cout << "═══ VECTOR INITIALIZATION ═══\n\n";

    // Method 1: Empty
    vector<int> v1;
    cout << "Empty vector, size: " << v1.size() << "\n";

    // Method 2: With size (all zeros)
    vector<int> v2(5);
    cout << "Size 5 (zeros): ";
    for (int x : v2) cout << x << " ";
    cout << "\n";

    // Method 3: Size + default value
    vector<int> v3(5, 42);
    cout << "Size 5 (val=42): ";
    for (int x : v3) cout << x << " ";
    cout << "\n";

    // Method 4: Initializer list
    vector<int> v4 = {10, 20, 30, 40, 50};
    cout << "Initializer list: ";
    for (int x : v4) cout << x << " ";
    cout << "\n";

    // Method 5: Copy constructor
    vector<int> v5(v4);
    cout << "Copy of v4: ";
    for (int x : v5) cout << x << " ";
    cout << "\n";

    // Method 6: From C-array
    int arr[] = {100, 200, 300};
    vector<int> v6(arr, arr + 3);
    cout << "From array: ";
    for (int x : v6) cout << x << " ";
    cout << "\n";

    // Method 7: From set (sorted!)
    set<int> s = {5, 3, 1, 4, 2};
    vector<int> v7(s.begin(), s.end());
    cout << "From set (sorted): ";
    for (int x : v7) cout << x << " ";
    cout << "\n\n";

    // GM TRICK: Fill with iota
    vector<int> indices(10);
    iota(indices.begin(), indices.end(), 0);  // 0, 1, 2, ..., 9
    cout << "iota (0..9): ";
    for (int x : indices) cout << x << " ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: push_back vs emplace_back
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 push_back(value)    → Copies/moves the value into vector
 emplace_back(args)  → Constructs the element IN-PLACE (no copy!)

 For simple types (int, double), difference is negligible.
 For complex types (pair, struct), emplace_back avoids a copy.

 DRY RUN with pair:
   push_back(make_pair(1, 2)):
     1. Create temporary pair{1,2}
     2. COPY it into vector
     3. Destroy temporary → 2 operations

   emplace_back(1, 2):
     1. Construct pair{1,2} directly in vector memory → 1 operation!
*/

void demonstratePushVsEmplace() {
    cout << "═══ push_back vs emplace_back ═══\n\n";

    // For simple types — essentially same
    vector<int> v;
    v.push_back(10);
    v.emplace_back(20);
    cout << "Simple types: ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // For pairs — emplace_back is cleaner
    vector<pair<int, int>> pairs;
    pairs.push_back(make_pair(1, 2));  // Old way
    pairs.push_back({3, 4});           // C++11 way
    pairs.emplace_back(5, 6);          // Best way! No copy!
    cout << "Pairs: ";
    for (auto& [a, b] : pairs) cout << "(" << a << "," << b << ") ";
    cout << "\n";

    // For vectors of vectors
    vector<vector<int>> grid;
    grid.push_back({1, 2, 3});
    grid.emplace_back(vector<int>{4, 5, 6});
    grid.emplace_back(initializer_list<int>{7, 8, 9});
    cout << "Grid:\n";
    for (auto& row : grid) {
        cout << "  ";
        for (int x : row) cout << x << " ";
        cout << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: reserve() and capacity() — AVOIDING TLE
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 size()     → Number of elements currently stored
 capacity() → Total allocated memory (>= size)
 reserve(n) → Pre-allocate memory for n elements

 WHY RESERVE MATTERS:
 ────────────────────
 Without reserve: vector reallocates when capacity is exceeded.
   Reallocation = allocate new memory + copy ALL elements + free old → O(n)!

 With reserve: No reallocation if you don't exceed reserved capacity.

 DRY RUN:
   vector v; (size=0, capacity=0)
   v.push_back(1) → capacity grows to 1 (allocate 1)
   v.push_back(2) → capacity grows to 2 (reallocate + copy!)
   v.push_back(3) → capacity grows to 4 (reallocate + copy!)
   v.push_back(4) → fits (no realloc)
   v.push_back(5) → capacity grows to 8 (reallocate + copy!)

   With reserve(5):
   v.reserve(5) → capacity = 5
   v.push_back(1..5) → NO reallocations at all!

 GM TIP: If you know the size, ALWAYS reserve.
         It can be the difference between AC and TLE.
*/

void demonstrateReserveCapacity() {
    cout << "═══ reserve() and capacity() ═══\n\n";

    // Without reserve — watch capacity grow
    vector<int> v1;
    cout << "Without reserve:\n";
    for (int i = 0; i < 20; i++) {
        v1.push_back(i);
        if (i < 10 || v1.size() == v1.capacity())
            cout << "  size=" << v1.size() << ", capacity=" << v1.capacity() << "\n";
    }
    cout << "\n";

    // With reserve — no reallocation
    vector<int> v2;
    v2.reserve(20);
    cout << "With reserve(20):\n";
    cout << "  Before: size=" << v2.size() << ", capacity=" << v2.capacity() << "\n";
    for (int i = 0; i < 20; i++) v2.push_back(i);
    cout << "  After:  size=" << v2.size() << ", capacity=" << v2.capacity() << "\n\n";

    // Performance comparison
    const int N = 10000000;
    {
        auto start = chrono::steady_clock::now();
        vector<int> v;
        for (int i = 0; i < N; i++) v.push_back(i);
        auto end = chrono::steady_clock::now();
        cout << "Without reserve (10^7): "
             << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
    }
    {
        auto start = chrono::steady_clock::now();
        vector<int> v;
        v.reserve(N);
        for (int i = 0; i < N; i++) v.push_back(i);
        auto end = chrono::steady_clock::now();
        cout << "With reserve (10^7):    "
             << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n\n";
    }
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: resize() vs reserve()
// ═══════════════════════════════════════════════════════════════
/*
 resize(n)  → Changes SIZE to n. Adds default elements or removes extras.
 reserve(n) → Changes CAPACITY only. Size stays the same.

 resize(n, val) → New elements get value 'val'

 DRY RUN:
   vector v = {1, 2, 3}  (size=3)
   v.resize(5)    → v = {1, 2, 3, 0, 0}  (size=5, added 0s)
   v.resize(2)    → v = {1, 2}            (size=2, removed last 3)
   v.resize(4, 9) → v = {1, 2, 9, 9}     (size=4, added 9s)
*/

void demonstrateResize() {
    cout << "═══ resize() vs reserve() ═══\n\n";

    vector<int> v = {1, 2, 3};
    cout << "Original: size=" << v.size() << " → ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    v.resize(6);  // Expand with zeros
    cout << "resize(6): size=" << v.size() << " → ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    v.resize(3);  // Shrink
    cout << "resize(3): size=" << v.size() << " → ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    v.resize(6, 99);  // Expand with 99s
    cout << "resize(6,99): size=" << v.size() << " → ";
    for (int x : v) cout << x << " ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: clear() and shrink_to_fit()
// ═══════════════════════════════════════════════════════════════

void demonstrateClearShrink() {
    cout << "═══ clear() and shrink_to_fit() ═══\n\n";

    vector<int> v(1000000, 42);
    cout << "Before clear: size=" << v.size() << ", cap=" << v.capacity() << "\n";

    v.clear();  // Removes all elements, capacity stays!
    cout << "After clear:  size=" << v.size() << ", cap=" << v.capacity() << "\n";

    v.shrink_to_fit();  // Release unused memory
    cout << "After shrink: size=" << v.size() << ", cap=" << v.capacity() << "\n\n";

    // GM TRICK: Swap to force deallocation
    vector<int> big(1000000, 1);
    cout << "Before swap trick: cap=" << big.capacity() << "\n";
    vector<int>().swap(big);  // Force complete deallocation
    cout << "After swap trick:  cap=" << big.capacity() << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: erase() — The Tricky One
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 v.erase(iterator)      → Remove single element at position
 v.erase(first, last)   → Remove range [first, last)

 ERASE-REMOVE IDIOM (CRITICAL FOR CP):
 ─────────────────────────────────────
 Problem: remove() doesn't actually remove! It moves unwanted elements
          to the end and returns iterator to new "end".
 Solution: v.erase(remove(...), v.end());

 DRY RUN:
   v = {1, 2, 3, 2, 4, 2, 5}
   remove(v.begin(), v.end(), 2) → {1, 3, 4, 5, ?, ?, ?}
                                    returns iterator to first '?'
   erase(it, v.end()) → {1, 3, 4, 5}
*/

void demonstrateErase() {
    cout << "═══ erase() AND ERASE-REMOVE IDIOM ═══\n\n";

    // Single element erase
    vector<int> v = {10, 20, 30, 40, 50};
    v.erase(v.begin() + 2);  // Remove 30 (index 2)
    cout << "After erase index 2: ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // Range erase
    v = {10, 20, 30, 40, 50};
    v.erase(v.begin() + 1, v.begin() + 3);  // Remove [20, 30)... actually [20,30]
    cout << "After erase range [1,3): ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // ERASE-REMOVE IDIOM — remove all occurrences of a value
    v = {1, 2, 3, 2, 4, 2, 5};
    cout << "Before remove 2: ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    v.erase(remove(v.begin(), v.end(), 2), v.end());
    cout << "After erase-remove 2: ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // Remove elements matching condition
    v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    v.erase(remove_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), v.end());
    cout << "After remove even: ";
    for (int x : v) cout << x << " ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 7: ITERATION METHODS
// ═══════════════════════════════════════════════════════════════

void demonstrateIteration() {
    cout << "═══ ITERATION METHODS ═══\n\n";

    vector<int> v = {10, 20, 30, 40, 50};

    // Method 1: Index-based
    cout << "Index:       ";
    for (int i = 0; i < (int)v.size(); i++) cout << v[i] << " ";
    cout << "\n";

    // Method 2: Iterator
    cout << "Iterator:    ";
    for (auto it = v.begin(); it != v.end(); ++it) cout << *it << " ";
    cout << "\n";

    // Method 3: Range-for
    cout << "Range-for:   ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // Method 4: Reverse
    cout << "Reverse:     ";
    for (auto it = v.rbegin(); it != v.rend(); ++it) cout << *it << " ";
    cout << "\n";

    // Method 5: for_each algorithm
    cout << "for_each:    ";
    for_each(v.begin(), v.end(), [](int x) { cout << x << " "; });
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 8: VECTOR OF VECTORS (2D)
// ═══════════════════════════════════════════════════════════════
/*
 vector<vector<int>> = 2D dynamic array
 Used for: adjacency lists, grids, matrices, DP tables

 DRY RUN (adjacency list):
   Graph: 0→1, 0→2, 1→3, 2→3
   adj[0] = {1, 2}
   adj[1] = {3}
   adj[2] = {3}
   adj[3] = {}
*/

void demonstrateVectorOfVectors() {
    cout << "═══ VECTOR OF VECTORS (2D) ═══\n\n";

    // Fixed-size 2D grid
    int rows = 3, cols = 4;
    vector<vector<int>> grid(rows, vector<int>(cols, 0));
    grid[0][0] = 1;
    grid[1][2] = 5;
    grid[2][3] = 9;
    cout << "Grid (3x4):\n";
    for (auto& row : grid) {
        cout << "  ";
        for (int val : row) cout << val << " ";
        cout << "\n";
    }
    cout << "\n";

    // Adjacency list
    int n = 5;
    vector<vector<int>> adj(n);
    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[1].push_back(3);
    adj[2].push_back(3);
    adj[3].push_back(4);
    cout << "Adjacency list:\n";
    for (int i = 0; i < n; i++) {
        cout << "  " << i << " → ";
        for (int j : adj[i]) cout << j << " ";
        cout << "\n";
    }
    cout << "\n";

    // Jagged array (different row sizes)
    vector<vector<int>> jagged;
    jagged.push_back({1});
    jagged.push_back({1, 2});
    jagged.push_back({1, 2, 3});
    jagged.push_back({1, 2, 3, 4});
    cout << "Pascal-like jagged:\n";
    for (auto& row : jagged) {
        cout << "  ";
        for (int x : row) cout << x << " ";
        cout << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 9: CP PROBLEM — COORDINATE COMPRESSION
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Coordinate Compression
 Given large values (up to 10^9), map them to [0, n-1] range.

 TECHNIQUE: sort + unique + lower_bound using vector

 DRY RUN:
   Input: {100, 5, 1000000000, 5, 100, 42}
   Step 1: Copy and sort → {5, 42, 100, 1000000000}
   Step 2: unique → {5, 42, 100, 1000000000}
   Step 3: lower_bound each:
     100 → index 2
     5 → index 0
     1000000000 → index 3
     5 → index 0
     100 → index 2
     42 → index 1
   Output: {2, 0, 3, 0, 2, 1}
*/

void coordinateCompression() {
    cout << "═══ CP PROBLEM: COORDINATE COMPRESSION ═══\n\n";

    vector<int> arr = {100, 5, 1000000000, 5, 100, 42};
    cout << "Original: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    // Step 1: Create sorted unique copy
    vector<int> sorted_arr(arr);
    sort(sorted_arr.begin(), sorted_arr.end());
    sorted_arr.erase(unique(sorted_arr.begin(), sorted_arr.end()), sorted_arr.end());

    cout << "Sorted unique: ";
    for (int x : sorted_arr) cout << x << " ";
    cout << "\n";

    // Step 2: Map each value to its compressed index
    vector<int> compressed(arr.size());
    for (int i = 0; i < (int)arr.size(); i++) {
        compressed[i] = lower_bound(sorted_arr.begin(), sorted_arr.end(), arr[i])
                        - sorted_arr.begin();
    }

    cout << "Compressed:    ";
    for (int x : compressed) cout << x << " ";
    cout << "\n";
    cout << "Values up to 10^9 mapped to [0, " << sorted_arr.size() - 1 << "]\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateInitialization();
    demonstratePushVsEmplace();
    demonstrateReserveCapacity();
    demonstrateResize();
    demonstrateClearShrink();
    demonstrateErase();
    demonstrateIteration();
    demonstrateVectorOfVectors();
    coordinateCompression();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. vector is THE default CP container — O(1) access, O(1)* push_back\n";
    cout << "2. ALWAYS reserve() if you know the size\n";
    cout << "3. emplace_back > push_back for complex types\n";
    cout << "4. Erase-remove idiom: v.erase(remove(...), v.end())\n";
    cout << "5. vector<vector<int>> for graphs, grids, DP tables\n";
    cout << "6. Coordinate compression: sort + unique + lower_bound\n";

    return 0;
}

/*
 PRACTICE PROBLEMS:
 ──────────────────
 1. [CSES Distinct Numbers] https://cses.fi/problemset/task/1621 (sort+unique)
 2. [CF Towers]             https://codeforces.com/problemset/problem/37/A
 3. [LC Remove Duplicates]  https://leetcode.com/problems/remove-duplicates-from-sorted-array/
*/

