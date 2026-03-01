/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           08 — RANGE-BASED FOR LOOPS                                         ║
║           From Zero to Grandmaster — Modern C++ Iteration                    ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Basic Range-Based For Loop
 2. By-Value vs By-Reference
 3. Range Loops with Different Containers
 4. Index Tricks with Range Loops
 5. When to Use Index Loops vs Range Loops

CORE IDEA:
──────────
  Range-based for loops (C++11) iterate over ALL elements of a container
  without explicit iterators.

  Old: for (int i = 0; i < v.size(); i++) cout << v[i];
  New: for (int x : v) cout << x;

  Cleaner, safer, less bug-prone.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BASIC RANGE-BASED FOR
// ═══════════════════════════════════════════════════════════════
/*
 SYNTAX:
 ───────
 for (declaration : container) {
     // use element
 }

 Equivalent to:
 for (auto it = container.begin(); it != container.end(); ++it) {
     auto element = *it;
     // use element
 }

 DRY RUN:
   vector v = {10, 20, 30}
   for (int x : v)     →  x=10, print 10
                        →  x=20, print 20
                        →  x=30, print 30
*/

void demonstrateBasicRangeFor() {
    cout << "═══ BASIC RANGE-BASED FOR ═══\n\n";

    // With vector
    vector<int> v = {10, 20, 30, 40, 50};
    cout << "vector: ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // With set (auto-sorted!)
    set<int> s = {50, 10, 30, 20, 40};
    cout << "set:    ";
    for (int x : s) cout << x << " ";
    cout << "\n";

    // With string
    string str = "Hello";
    cout << "string: ";
    for (char c : str) cout << c << " ";
    cout << "\n";

    // With array
    int arr[] = {1, 2, 3, 4, 5};
    cout << "array:  ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    // With initializer list directly
    cout << "init:   ";
    for (int x : {100, 200, 300}) cout << x << " ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: BY-VALUE vs BY-REFERENCE
// ═══════════════════════════════════════════════════════════════
/*
 THREE FORMS:
 ────────────
 for (int x : v)           → Copy (safe, can't modify original)
 for (int& x : v)          → Reference (can modify original!)
 for (const int& x : v)    → Const reference (read-only, no copy)

 WHEN TO USE WHAT:
 ┌────────────────────┬──────────────┬──────────────────────────┐
 │ Form               │ Use When     │ Example                  │
 ├────────────────────┼──────────────┼──────────────────────────┤
 │ auto x             │ Small types  │ int, char, bool          │
 │ auto& x            │ Need modify  │ double all values        │
 │ const auto& x      │ Large types  │ string, vector, struct   │
 └────────────────────┴──────────────┴──────────────────────────┘

 GM TIP: For int/char, copy is fine (cheap). For string/vector,
         ALWAYS use const auto& to avoid expensive copies!
*/

void demonstrateByValueVsRef() {
    cout << "═══ BY-VALUE vs BY-REFERENCE ═══\n\n";

    vector<int> v = {1, 2, 3, 4, 5};

    // By value — COPIES, original unchanged
    for (int x : v) x *= 2;
    cout << "After by-value *2:     ";
    for (int x : v) cout << x << " ";
    cout << "(unchanged)\n";

    // By reference — MODIFIES original
    for (int& x : v) x *= 2;
    cout << "After by-reference *2: ";
    for (int x : v) cout << x << " ";
    cout << "(changed!)\n\n";

    // Const reference for strings (efficient reading)
    vector<string> names = {"Alice", "Bob", "Charlie"};
    cout << "Const ref (no copy): ";
    for (const auto& name : names) {
        cout << name << " ";
        // name = "X";  // COMPILE ERROR: const!
    }
    cout << "\n\n";

    // Map iteration with structured bindings + reference
    map<string, int> scores = {{"A", 90}, {"B", 80}, {"C", 70}};
    for (auto& [name, score] : scores) {
        score += 5;  // Curve everyone's score!
    }
    cout << "After curving scores:\n";
    for (const auto& [name, score] : scores) {
        cout << "  " << name << ": " << score << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: RANGE LOOPS WITH ALL CONTAINERS
// ═══════════════════════════════════════════════════════════════

void demonstrateWithContainers() {
    cout << "═══ RANGE LOOPS WITH ALL CONTAINERS ═══\n\n";

    // vector
    vector<int> vec = {1, 2, 3};
    cout << "vector:         ";
    for (auto x : vec) cout << x << " ";
    cout << "\n";

    // deque
    deque<int> dq = {10, 20, 30};
    cout << "deque:          ";
    for (auto x : dq) cout << x << " ";
    cout << "\n";

    // list
    list<int> lst = {100, 200, 300};
    cout << "list:           ";
    for (auto x : lst) cout << x << " ";
    cout << "\n";

    // set
    set<int> s = {30, 10, 20};
    cout << "set (sorted):   ";
    for (auto x : s) cout << x << " ";
    cout << "\n";

    // multiset
    multiset<int> ms = {3, 1, 4, 1, 5};
    cout << "multiset:       ";
    for (auto x : ms) cout << x << " ";
    cout << "\n";

    // map
    map<string, int> m = {{"b", 2}, {"a", 1}, {"c", 3}};
    cout << "map:            ";
    for (auto& [k, v] : m) cout << k << ":" << v << " ";
    cout << "\n";

    // unordered_map
    unordered_map<string, int> um = {{"x", 1}, {"y", 2}};
    cout << "unordered_map:  ";
    for (auto& [k, v] : um) cout << k << ":" << v << " ";
    cout << "\n";

    // string
    string str = "CPP";
    cout << "string:         ";
    for (char c : str) cout << c << " ";
    cout << "\n";

    // 2D vector
    vector<vector<int>> grid = {{1, 2}, {3, 4}, {5, 6}};
    cout << "2D vector:\n";
    for (const auto& row : grid) {
        cout << "  ";
        for (int val : row) cout << val << " ";
        cout << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: INDEX TRICKS
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Range-for doesn't give you the INDEX.
 SOLUTIONS:

 1. Counter variable (simple)
 2. Address arithmetic (for vectors only)
 3. enumerate-style with index

 GM TIP: If you need the index, just use a regular for loop.
         Don't fight the range-for.
*/

void demonstrateIndexTricks() {
    cout << "═══ INDEX TRICKS ═══\n\n";

    vector<int> v = {10, 20, 30, 40, 50};

    // Trick 1: Counter variable
    cout << "Counter variable:\n";
    int idx = 0;
    for (int x : v) {
        cout << "  [" << idx++ << "] = " << x << "\n";
    }

    // Trick 2: Address arithmetic (vector only!)
    cout << "\nAddress arithmetic:\n";
    for (auto& x : v) {
        int i = &x - &v[0];  // Works because vector is contiguous!
        cout << "  [" << i << "] = " << x << "\n";
    }

    // When you need index — just use regular loop
    cout << "\nRegular loop (best for index):\n";
    for (int i = 0; i < (int)v.size(); i++) {
        cout << "  [" << i << "] = " << v[i] << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: WHEN TO USE WHICH LOOP
// ═══════════════════════════════════════════════════════════════
/*
 DECISION GUIDE:
 ───────────────

 ┌─────────────────────────┬────────────────────────────────┐
 │ Use Range-For When      │ Use Index-For When             │
 ├─────────────────────────┼────────────────────────────────┤
 │ Just reading all elems  │ Need index for logic           │
 │ Modifying all elements  │ Need to access neighbors [i±1] │
 │ Map/Set iteration       │ Need to iterate backwards      │
 │ Clean, readable code    │ Need to skip/jump elements     │
 │                         │ Two-pointer technique          │
 │                         │ Sliding window                 │
 └─────────────────────────┴────────────────────────────────┘

 CP EXAMPLES:
   Range-for: frequency counting, printing, transforming
   Index-for: two pointers, sliding window, DP, graph BFS/DFS
*/

void demonstrateWhenToUse() {
    cout << "═══ WHEN TO USE WHICH ═══\n\n";

    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Range-for: Frequency counting
    map<int, int> freq;
    for (int x : v) freq[x % 3]++;
    cout << "Frequency of x%3:\n";
    for (auto& [rem, cnt] : freq)
        cout << "  " << rem << " → " << cnt << " times\n";

    // Index-for: Two pointers (need index)
    cout << "\nTwo Sum (target=11):\n";
    int lo = 0, hi = (int)v.size() - 1;
    while (lo < hi) {
        int sum = v[lo] + v[hi];
        if (sum == 11) {
            cout << "  Pair: " << v[lo] << " + " << v[hi] << " = 11\n";
            lo++; hi--;
        } else if (sum < 11) lo++;
        else hi--;
    }

    // Index-for: Checking neighbors
    cout << "\nLocal maxima (v[i] > v[i-1] and v[i] > v[i+1]):\n";
    for (int i = 1; i < (int)v.size() - 1; i++) {
        if (v[i] > v[i - 1] && v[i] > v[i + 1]) {
            cout << "  Index " << i << ": " << v[i] << "\n";
        }
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateBasicRangeFor();
    demonstrateByValueVsRef();
    demonstrateWithContainers();
    demonstrateIndexTricks();
    demonstrateWhenToUse();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. Range-for: clean, safe, use for simple iteration\n";
    cout << "2. auto& to modify, const auto& for large types\n";
    cout << "3. Works with ALL STL containers + arrays + strings\n";
    cout << "4. Use index loops when you need i, neighbors, or two pointers\n";
    cout << "5. 2D iteration: for (const auto& row : grid) for (int x : row)\n";

    return 0;
}

