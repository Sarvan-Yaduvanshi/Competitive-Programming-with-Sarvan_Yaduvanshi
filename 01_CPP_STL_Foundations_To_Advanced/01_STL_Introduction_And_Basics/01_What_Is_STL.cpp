/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — WHAT IS STL? (Standard Template Library)                      ║
║           From Zero to Grandmaster — Complete Foundation                     ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. What is STL?
 2. The Four Pillars of STL
 3. Why STL Matters in Competitive Programming
 4. STL Architecture Overview
 5. Example: Solving a Problem Without STL vs With STL

WHAT IS STL?
────────────
STL = Standard Template Library
It is a collection of template classes and functions in C++ that provides:
  • Containers   — Data structures (vector, set, map, etc.)
  • Algorithms   — Functions (sort, search, transform, etc.)
  • Iterators    — Connectors between containers and algorithms
  • Functors     — Function objects for custom operations

KEY INSIGHT:
  STL is GENERIC — it works with ANY data type via templates.
  One sort() works for int, double, string, custom structs — everything!

WHY STL MATTERS FOR CP:
───────────────────────
  • Saves 50-100 lines per problem (no manual data structures)
  • Optimized implementations (often faster than hand-written code)
  • Bug-free — tested by millions of developers
  • Standard across all judges (Codeforces, LeetCode, AtCoder, etc.)

  GM TIP: A Grandmaster who knows STL well can solve problems 2-3x faster
          than someone who writes everything from scratch.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: THE FOUR PILLARS OF STL
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 STL has 4 main components:

 ┌──────────────────────────────────────────────────────────┐
 │                    STL ARCHITECTURE                      │
 │                                                          │
 │   ┌─────────────┐     ┌──────────────┐                   │
 │   │  CONTAINERS  │────▶│  ITERATORS  │                   │
 │   │ (store data) │     │ (point/scan)│                   │
 │   └─────────────┘     └──────┬───────┘                   │
 │                              │                           │
 │                              ▼                           │
 │                      ┌──────────────┐                    │
 │                      │  ALGORITHMS  │                    │
 │                      │ (process)    │                    │
 │                      └──────┬───────┘                    │
 │                              │                           │
 │                              ▼                           │
 │                      ┌──────────────┐                    │
 │                      │  FUNCTORS    │                    │
 │                      │ (customize)  │                    │
 │                      └──────────────┘                    │
 └──────────────────────────────────────────────────────────┘

 1. CONTAINERS — Store collections of objects
    • Sequence:   vector, deque, list, array, forward_list
    • Associative: set, map, multiset, multimap
    • Unordered:   unordered_set, unordered_map
    • Adaptors:    stack, queue, priority_queue

 2. ALGORITHMS — Process data in containers
    • sort, find, binary_search, reverse, accumulate, etc.
    • 80+ algorithms in <algorithm> and <numeric>

 3. ITERATORS — Point to elements, enable traversal
    • Like pointers but generalized for any container
    • begin(), end(), rbegin(), rend()

 4. FUNCTORS — Function objects for customization
    • less<>, greater<>, custom comparators
    • Lambdas (modern C++ way)
*/

void demonstrateSTLPillars() {
    cout << "═══ THE FOUR PILLARS OF STL ═══\n\n";

    // PILLAR 1: CONTAINER — vector stores data
    vector<int> nums = {5, 2, 8, 1, 9, 3};
    cout << "1. Container (vector): ";
    for (int x : nums) cout << x << " ";
    cout << "\n";

    // PILLAR 2: ALGORITHM — sort processes the data
    sort(nums.begin(), nums.end());
    cout << "2. Algorithm (sort):   ";
    for (int x : nums) cout << x << " ";
    cout << "\n";

    // PILLAR 3: ITERATOR — begin()/end() connect container to algorithm
    auto it = find(nums.begin(), nums.end(), 8);
    cout << "3. Iterator (find 8):  found at index " << (it - nums.begin()) << "\n";

    // PILLAR 4: FUNCTOR — greater<> customizes sort to descending
    sort(nums.begin(), nums.end(), greater<int>());
    cout << "4. Functor (desc sort): ";
    for (int x : nums) cout << x << " ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: WITHOUT STL vs WITH STL
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Given N numbers, find the number of distinct elements.

 WITHOUT STL: Manual sorting + counting unique → 20+ lines
 WITH STL:    set<int> → 3 lines

 DRY RUN: Input = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3}
   Without STL: Sort → {1,1,2,3,3,4,5,5,6,9}, count changes → 8
   With STL:    set = {1,2,3,4,5,6,9}, size = 7... wait, let me recount
                set = {1, 2, 3, 4, 5, 6, 9} → size = 7
*/

// WITHOUT STL — Manual approach
int countDistinctManual(int arr[], int n) {
    // Manual bubble sort
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);

    // Count distinct
    int count = 1;
    for (int i = 1; i < n; i++)
        if (arr[i] != arr[i - 1])
            count++;
    return count;
}

// WITH STL — Clean, fast, bug-free
int countDistinctSTL(vector<int>& nums) {
    set<int> s(nums.begin(), nums.end());
    return s.size();
    // That's it. One line.
}

void demonstrateComparison() {
    cout << "═══ WITHOUT STL vs WITH STL ═══\n\n";

    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int n = 10;
    cout << "Input: 3 1 4 1 5 9 2 6 5 3\n";
    cout << "Distinct (manual): " << countDistinctManual(arr, n) << "\n";

    vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    cout << "Distinct (STL):    " << countDistinctSTL(v) << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: STL CONTAINER TAXONOMY
// ═══════════════════════════════════════════════════════════════
/*
 CONTAINER CLASSIFICATION:
 ─────────────────────────

 Sequence Containers (ordered by insertion):
   vector      — Dynamic array, O(1) random access
   deque       — Double-ended queue, O(1) front/back
   list        — Doubly linked list, O(1) insert/erase
   forward_list — Singly linked list
   array       — Fixed-size array

 Associative Containers (sorted by key):
   set         — Unique sorted elements
   multiset    — Sorted, allows duplicates
   map         — Key-value pairs, sorted by key
   multimap    — Key-value, allows duplicate keys

 Unordered Containers (hash-based):
   unordered_set — O(1) average lookup
   unordered_map — O(1) average key-value lookup

 Container Adaptors (restricted interfaces):
   stack          — LIFO (Last In, First Out)
   queue          — FIFO (First In, First Out)
   priority_queue — Heap-based, largest element on top
*/

void demonstrateTaxonomy() {
    cout << "═══ STL CONTAINER TAXONOMY DEMO ═══\n\n";

    // Sequence
    vector<int> v = {1, 2, 3};
    cout << "vector: ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // Associative
    set<int> s = {3, 1, 4, 1, 5};
    cout << "set:    ";
    for (int x : s) cout << x << " ";  // Automatically sorted, no duplicates
    cout << "\n";

    // Unordered
    map<string, int> m;
    m["hello"] = 1;
    m["world"] = 2;
    cout << "map:    ";
    for (auto& [k, v] : m) cout << k << "=" << v << " ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateSTLPillars();
    demonstrateComparison();
    demonstrateTaxonomy();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. STL = Containers + Algorithms + Iterators + Functors\n";
    cout << "2. STL saves time, reduces bugs, and is optimized\n";
    cout << "3. Every CP problem can benefit from at least one STL component\n";
    cout << "4. Master STL = Master competitive programming speed\n";

    return 0;
}

/*
 PRACTICE PROBLEMS:
 ──────────────────
 1. [Distinct Numbers] https://cses.fi/problemset/task/1621  (Use set)
 2. [Two Sum]          https://leetcode.com/problems/two-sum/ (Use unordered_map)
 3. [Sort the Array]   https://codeforces.com/problemset/problem/451/B (Use sort)
*/

