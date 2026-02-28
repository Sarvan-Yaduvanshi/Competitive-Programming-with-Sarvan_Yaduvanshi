/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — CONTAINERS VS ALGORITHMS                                    ║
║           From Zero to Grandmaster — STL Architecture                      ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Containers — What They Are & Categories
 2. Algorithms — What They Are & Categories
 3. How They Work Together (Separation of Concerns)
 4. Choosing the Right Container + Algorithm Combo

CORE IDEA:
──────────
  Containers STORE data. Algorithms PROCESS data. Iterators CONNECT them.
  This separation means:
    • Any algorithm works with any container (via iterators)
    • You can swap containers without changing algorithms
    • You can swap algorithms without changing containers

  This is the GENIUS of STL design!
*/

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: CONTAINERS — Storage Components
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Containers are template classes that manage collections of objects.

 THREE CATEGORIES:
 ┌─────────────────────────────────────────────────────────┐
 │ Category        │ Examples              │ Key Property  │
 ├─────────────────┼───────────────────────┼───────────────┤
 │ Sequence        │ vector, deque, list   │ Order matters │
 │ Associative     │ set, map, multiset    │ Auto-sorted   │
 │ Unordered       │ unordered_set/map     │ Hash-based    │
 │ Adaptors        │ stack, queue, pq      │ Restricted    │
 └─────────────────┴───────────────────────┴───────────────┘

 EACH CONTAINER IS OPTIMIZED FOR DIFFERENT OPERATIONS:
   vector   → Random access, back insertion
   deque    → Front AND back insertion
   list     → Insertion/deletion anywhere
   set/map  → Sorted queries, log-time search
   unordered → O(1) average lookup
*/

void demonstrateContainers() {
    cout << "═══ CONTAINERS DEMO ═══\n\n";

    // Sequence: maintains insertion order
    vector<int> v = {5, 3, 1, 4, 2};
    cout << "vector (insertion order): ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // Associative: auto-sorts
    set<int> s(v.begin(), v.end());
    cout << "set (auto-sorted):        ";
    for (int x : s) cout << x << " ";
    cout << "\n";

    // Map: key-value pairs
    map<string, int> scores;
    scores["Alice"] = 95;
    scores["Bob"] = 87;
    scores["Charlie"] = 92;
    cout << "map (sorted by key):      ";
    for (auto& [name, score] : scores)
        cout << name << ":" << score << " ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: ALGORITHMS — Processing Components
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Algorithms are template FUNCTIONS that operate on ranges [begin, end).

 KEY CATEGORIES:
   • Sorting:     sort, stable_sort, partial_sort, nth_element
   • Searching:   find, binary_search, lower_bound, upper_bound
   • Modifying:   reverse, rotate, fill, replace, remove
   • Numeric:     accumulate, partial_sum, iota, inner_product
   • Set ops:     set_union, set_intersection, set_difference
   • Min/Max:     min_element, max_element, minmax_element

 CRITICAL INSIGHT:
   Algorithms take ITERATORS, not containers directly.
   This means sort() works on vector, deque, array — anything with
   random-access iterators!

 DRY RUN of sort():
   Input:  [5, 3, 1, 4, 2]
   sort() uses IntroSort internally:
     → QuickSort → [2, 3, 1, 4, 5] → [1, 2, 3, 4, 5]
   Output: [1, 2, 3, 4, 5]
*/

void demonstrateAlgorithms() {
    cout << "═══ ALGORITHMS DEMO ═══\n\n";

    vector<int> v = {5, 3, 1, 4, 2};

    // Sorting algorithm
    sort(v.begin(), v.end());
    cout << "sort():         ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // Searching algorithm
    bool found = binary_search(v.begin(), v.end(), 3);
    cout << "binary_search(3): " << (found ? "Found" : "Not Found") << "\n";

    // Numeric algorithm
    int sum = accumulate(v.begin(), v.end(), 0);
    cout << "accumulate():   sum = " << sum << "\n";

    // Modifying algorithm
    reverse(v.begin(), v.end());
    cout << "reverse():      ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // Min/Max algorithm
    auto [minIt, maxIt] = minmax_element(v.begin(), v.end());
    cout << "min=" << *minIt << ", max=" << *maxIt << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: THE POWER OF SEPARATION
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 The same algorithm works across different containers!
 This is called "generic programming" — the core philosophy of STL.

 sort() works on: vector, deque, array (anything with random-access iterators)
 find() works on: vector, list, deque, set* (anything with input iterators)

 * For set/map, use member functions (.find()) for O(log n) instead of O(n)

 GM TIP:
 ───────
 ALWAYS use member functions for associative containers:
   s.find(x)        NOT  find(s.begin(), s.end(), x)  // O(log n) vs O(n)
   s.lower_bound(x) NOT  lower_bound(s.begin(), s.end(), x)  // O(log n) vs O(n)
*/

void demonstrateSeparation() {
    cout << "═══ SAME ALGORITHM, DIFFERENT CONTAINERS ═══\n\n";

    // same data
    vector<int> vec = {5, 3, 1, 4, 2};
    deque<int> deq(vec.begin(), vec.end());
    list<int> lst(vec.begin(), vec.end());

    // sort works on vector and deque (random-access iterators)
    sort(vec.begin(), vec.end());
    sort(deq.begin(), deq.end());
    lst.sort();  // list has its OWN sort (no random access)

    cout << "vector after sort: ";
    for (int x : vec) cout << x << " ";
    cout << "\n";

    cout << "deque after sort:  ";
    for (int x : deq) cout << x << " ";
    cout << "\n";

    cout << "list after sort:   ";
    for (int x : lst) cout << x << " ";
    cout << "\n";

    // find works on ALL containers
    auto it1 = find(vec.begin(), vec.end(), 3);
    auto it2 = find(deq.begin(), deq.end(), 3);
    auto it3 = find(lst.begin(), lst.end(), 3);
    cout << "\nfind(3) works on vector, deque, and list — all found!\n";

    // But for set, use MEMBER function
    set<int> s(vec.begin(), vec.end());
    auto it4 = s.find(3);  // O(log n) — CORRECT
    // auto it5 = find(s.begin(), s.end(), 3);  // O(n) — WRONG approach
    cout << "set.find(3): " << (it4 != s.end() ? "Found" : "Not found") << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: CHOOSING THE RIGHT COMBO
// ═══════════════════════════════════════════════════════════════
/*
 COMMON PATTERNS IN CP:
 ──────────────────────

 ┌───────────────────────┬──────────────────────────────────────┐
 │ Problem Pattern       │ Container + Algorithm Combo          │
 ├───────────────────────┼──────────────────────────────────────┤
 │ Sort and search       │ vector + sort + binary_search        │
 │ Frequency counting    │ map or unordered_map                 │
 │ Unique elements       │ set or sort + unique                 │
 │ K-th smallest         │ nth_element or priority_queue        │
 │ Sliding window max    │ deque (monotonic)                    │
 │ Graph BFS             │ queue                                │
 │ Graph DFS             │ stack (or recursion)                 │
 │ Dijkstra              │ priority_queue + vector (adj list)   │
 │ Range queries         │ set + lower_bound                    │
 │ Expression parsing    │ stack                                │
 └───────────────────────┴──────────────────────────────────────┘
*/

void demonstrateCombo() {
    cout << "═══ COMMON CP COMBOS ═══\n\n";

    // COMBO 1: vector + sort + binary_search
    // Problem: Does value X exist in the array?
    vector<int> a = {7, 3, 9, 1, 5, 8, 2};
    sort(a.begin(), a.end());
    cout << "Combo 1 - Sort + Binary Search:\n";
    cout << "  Array: 1 2 3 5 7 8 9 (sorted)\n";
    cout << "  Search 5: " << (binary_search(a.begin(), a.end(), 5) ? "YES" : "NO") << "\n";
    cout << "  Search 6: " << (binary_search(a.begin(), a.end(), 6) ? "YES" : "NO") << "\n\n";

    // COMBO 2: map for frequency counting
    // Problem: Count frequency of each element
    vector<int> arr = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    map<int, int> freq;
    for (int x : arr) freq[x]++;
    cout << "Combo 2 - Map Frequency:\n";
    for (auto& [val, cnt] : freq)
        cout << "  " << val << " appears " << cnt << " times\n";
    cout << "\n";

    // COMBO 3: set for unique + sorted
    // Problem: Find distinct elements in sorted order
    vector<int> b = {5, 3, 5, 1, 3, 1, 4};
    set<int> unique_sorted(b.begin(), b.end());
    cout << "Combo 3 - Set for Unique Sorted: ";
    for (int x : unique_sorted) cout << x << " ";
    cout << "\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateContainers();
    demonstrateAlgorithms();
    demonstrateSeparation();
    demonstrateCombo();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. Containers STORE, Algorithms PROCESS, Iterators CONNECT\n";
    cout << "2. Same algorithm works on different containers (generic)\n";
    cout << "3. Use member functions for set/map (O(log n) vs O(n))\n";
    cout << "4. Choose the right container-algorithm combo for each problem\n";

    return 0;
}

/*
 PRACTICE PROBLEMS:
 ──────────────────
 1. [CSES Distinct Numbers]  https://cses.fi/problemset/task/1621
 2. [CF Bear and Big Brother] https://codeforces.com/problemset/problem/791/A
 3. [LC Contains Duplicate]  https://leetcode.com/problems/contains-duplicate/
*/

