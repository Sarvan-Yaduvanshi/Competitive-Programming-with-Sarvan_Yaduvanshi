/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — ITERATORS CONCEPT                                           ║
║           From Zero to Grandmaster — The Glue of STL                       ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. What Are Iterators?
 2. Iterator Categories (5 Types)
 3. Basic Iterator Operations
 4. Iterator Arithmetic
 5. Why Iterators Matter in CP

WHAT ARE ITERATORS?
───────────────────
  Iterators are generalized POINTERS that point to elements in containers.
  They abstract away the internal structure of containers.

  Think of them as: "A universal way to traverse ANY container"

  pointer → array element
  iterator → container element  (works for vector, set, map, list, etc.)

ITERATOR CATEGORIES:
────────────────────
 ┌────────────────────┬────────────┬──────────────────────────────┐
 │ Category           │ Operations │ Containers                   │
 ├────────────────────┼────────────┼──────────────────────────────┤
 │ Input Iterator     │ ++, *, ==  │ istream_iterator             │
 │ Output Iterator    │ ++, *      │ ostream_iterator             │
 │ Forward Iterator   │ ++, *, ==  │ forward_list, unordered_*    │
 │ Bidirectional      │ ++, --, *  │ list, set, map               │
 │ Random Access      │ +n, -n, [] │ vector, deque, array         │
 └────────────────────┴────────────┴──────────────────────────────┘

 Hierarchy: Random Access > Bidirectional > Forward > Input/Output

 GM TIP: sort() needs Random Access iterators → works on vector, NOT on list!
         That's why list has its own .sort() member function.
*/

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BASIC ITERATOR USAGE
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Every container provides:
   .begin()  → iterator to FIRST element
   .end()    → iterator PAST the last element (one-past-end)

 Range: [begin, end)  ← HALF-OPEN interval
   This is fundamental to STL design!
   Why? Because empty range = begin == end (elegant!)

 DRY RUN:
   vector v = {10, 20, 30, 40, 50}

   v.begin() → points to 10
   v.end()   → points PAST 50 (invalid position)

   *v.begin() = 10  (dereference = get value)
   *(v.end()-1) = 50 (last element)

   Iteration: begin→10, ++→20, ++→30, ++→40, ++→50, ++→end (stop!)
*/

void demonstrateBasicIterators() {
    cout << "═══ BASIC ITERATOR USAGE ═══\n\n";

    vector<int> v = {10, 20, 30, 40, 50};

    // Method 1: Traditional iterator loop
    cout << "Method 1 (iterator loop): ";
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";  // Dereference to get value
    }
    cout << "\n";

    // Method 2: Auto keyword (much cleaner!)
    cout << "Method 2 (auto):          ";
    for (auto it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";

    // Method 3: Range-based for (cleanest!)
    cout << "Method 3 (range-for):     ";
    for (int x : v) {
        cout << x << " ";
    }
    cout << "\n";

    // Reverse iteration
    cout << "Reverse (rbegin/rend):    ";
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        cout << *it << " ";
    }
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: ITERATOR ARITHMETIC
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Random-access iterators (vector, deque) support arithmetic:
   it + n    → advance by n positions
   it - n    → go back n positions
   it1 - it2 → distance between two iterators
   it[n]     → access n-th element from it

 Bidirectional iterators (set, map, list) support:
   ++it, --it  only! No +n, no -n!

 Use std::advance(it, n) for non-random-access iterators.
 Use std::distance(it1, it2) for any iterator pair.
*/

void demonstrateIteratorArithmetic() {
    cout << "═══ ITERATOR ARITHMETIC ═══\n\n";

    vector<int> v = {10, 20, 30, 40, 50};

    // Random access arithmetic (vector)
    auto it = v.begin();
    cout << "v.begin():     " << *it << "\n";
    cout << "v.begin() + 2: " << *(it + 2) << "\n";
    cout << "v.end() - 1:   " << *(v.end() - 1) << "\n";
    cout << "Distance:      " << (v.end() - v.begin()) << "\n\n";

    // For set (bidirectional — NO arithmetic)
    set<int> s = {10, 20, 30, 40, 50};
    auto sit = s.begin();
    // sit + 2;  ← COMPILE ERROR! Bidirectional can't do +n
    advance(sit, 2);  // Use advance() instead
    cout << "set: advance(begin, 2) = " << *sit << "\n";
    cout << "set: distance = " << distance(s.begin(), s.end()) << "\n\n";

    // next() and prev() — safe alternatives
    auto it2 = next(v.begin(), 3);   // v.begin() + 3
    auto it3 = prev(v.end(), 2);     // v.end() - 2
    cout << "next(begin, 3) = " << *it2 << "\n";
    cout << "prev(end, 2)   = " << *it3 << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: ITERATORS WITH DIFFERENT CONTAINERS
// ═══════════════════════════════════════════════════════════════
/*
 DRY RUN with set:
   set<int> s = {50, 10, 30, 20, 40}  → stored as {10, 20, 30, 40, 50}
   s.begin() → 10 (smallest element!)
   *prev(s.end()) → 50 (largest element!)
   s.lower_bound(25) → iterator to 30 (first >= 25)

 DRY RUN with map:
   map<string,int> m = {{"b",2}, {"a",1}, {"c",3}}
   m.begin() → {"a", 1}  (sorted by KEY!)
   it->first = "a", it->second = 1
*/

void demonstrateContainerIterators() {
    cout << "═══ ITERATORS WITH DIFFERENT CONTAINERS ═══\n\n";

    // Set iterators (bidirectional, sorted)
    set<int> s = {50, 10, 30, 20, 40};
    cout << "set (auto-sorted): ";
    for (auto it = s.begin(); it != s.end(); ++it)
        cout << *it << " ";
    cout << "\n";
    cout << "Smallest: " << *s.begin() << "\n";
    cout << "Largest:  " << *prev(s.end()) << "\n\n";

    // Map iterators (bidirectional, sorted by key)
    map<string, int> m = {{"banana", 2}, {"apple", 1}, {"cherry", 3}};
    cout << "map (sorted by key):\n";
    for (auto it = m.begin(); it != m.end(); ++it) {
        cout << "  " << it->first << " → " << it->second << "\n";
    }

    // Structured binding (C++17) — cleanest way
    cout << "map (structured binding):\n";
    for (auto& [key, value] : m) {
        cout << "  " << key << " → " << value << "\n";
    }
    cout << "\n";

    // List iterators (bidirectional)
    list<int> lst = {5, 3, 1, 4, 2};
    cout << "list: ";
    for (auto it = lst.begin(); it != lst.end(); ++it)
        cout << *it << " ";
    cout << "\n";
    // Can go backward too
    auto back = prev(lst.end());
    cout << "list last: " << *back << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: ITERATOR + ALGORITHM INTERPLAY
// ═══════════════════════════════════════════════════════════════
/*
 GM TIP:
 ───────
 Algorithms return iterators! This is critical for CP.

 Examples:
   find()        → iterator to found element, or end() if not found
   lower_bound() → iterator to first element >= value
   min_element() → iterator to smallest element
   sort()        → void (sorts in-place)

 PATTERN: Always check if returned iterator != end()
   auto it = find(v.begin(), v.end(), target);
   if (it != v.end()) {
       // Found! Index = it - v.begin()
   }
*/

void demonstrateAlgorithmIterators() {
    cout << "═══ ALGORITHM + ITERATOR INTERPLAY ═══\n\n";

    vector<int> v = {10, 25, 30, 45, 50, 65, 70};

    // find returns iterator
    auto it = find(v.begin(), v.end(), 45);
    if (it != v.end()) {
        cout << "Found 45 at index: " << (it - v.begin()) << "\n";
    }

    // lower_bound returns iterator (first >= value)
    auto lb = lower_bound(v.begin(), v.end(), 35);
    cout << "lower_bound(35): " << *lb << " at index " << (lb - v.begin()) << "\n";

    // upper_bound returns iterator (first > value)
    auto ub = upper_bound(v.begin(), v.end(), 45);
    cout << "upper_bound(45): " << *ub << " at index " << (ub - v.begin()) << "\n";

    // min_element, max_element
    auto minIt = min_element(v.begin(), v.end());
    auto maxIt = max_element(v.begin(), v.end());
    cout << "Min: " << *minIt << " at index " << (minIt - v.begin()) << "\n";
    cout << "Max: " << *maxIt << " at index " << (maxIt - v.begin()) << "\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateBasicIterators();
    demonstrateIteratorArithmetic();
    demonstrateContainerIterators();
    demonstrateAlgorithmIterators();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. Iterators = generalized pointers for containers\n";
    cout << "2. [begin, end) = half-open interval (fundamental STL design)\n";
    cout << "3. Random-access (vector) supports +n, bidirectional (set) uses advance()\n";
    cout << "4. Use member functions (set.find) not std::find for associative containers\n";
    cout << "5. Algorithms return iterators — always check against end()\n";

    return 0;
}

/*
 PRACTICE PROBLEMS:
 ──────────────────
 1. [LC Two Sum] https://leetcode.com/problems/two-sum/  (find with iterators)
 2. [CSES Distinct Numbers] https://cses.fi/problemset/task/1621 (set iterators)
 3. [CF Next Round] https://codeforces.com/problemset/problem/158/A (lower_bound)
*/

