/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — LIST COMPLETE GUIDE                                         ║
║           From Zero to Grandmaster — Doubly Linked List                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. What is std::list?
 2. Basic Operations (insert, erase, push/pop)
 3. splice() — O(1) Move Elements Between Lists
 4. merge() — Merge Two Sorted Lists
 5. remove(), reverse(), unique(), sort()
 6. When to Use list vs vector

WHAT IS LIST?
─────────────
  std::list is a DOUBLY LINKED LIST.
  Each node has: [prev | data | next]

  ┌──────┐   ┌──────┐   ┌──────┐   ┌──────┐
  │ null │←──│  10  │←──│  20  │←──│  30  │──→ null
  │  10  │──→│  20  │──→│  30  │──→│ null │
  └──────┘   └──────┘   └──────┘   └──────┘

  O(1) insertion/deletion anywhere (WITH iterator)
  O(n) access (no random access!)
  Iterators remain valid after insert/erase (unlike vector!)
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BASIC OPERATIONS
// ═══════════════════════════════════════════════════════════════

void demonstrateBasicOps() {
    cout << "═══ LIST BASIC OPERATIONS ═══\n\n";

    list<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.push_front(5);

    cout << "List: ";
    for (int x : lst) cout << x << " ";
    cout << "\n";

    // Insert at specific position
    auto it = lst.begin();
    advance(it, 2);  // Move to 3rd position
    lst.insert(it, 15);  // Insert 15 before position 2
    cout << "After insert 15: ";
    for (int x : lst) cout << x << " ";
    cout << "\n";

    // Erase at position
    it = lst.begin();
    advance(it, 1);
    lst.erase(it);
    cout << "After erase index 1: ";
    for (int x : lst) cout << x << " ";
    cout << "\n";

    cout << "Front: " << lst.front() << ", Back: " << lst.back() << "\n";
    cout << "Size: " << lst.size() << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: splice() — THE KILLER FEATURE
// ═══════════════════════════════════════════════════════════════
/*
 splice() moves elements from one list to another in O(1)!
 No copying, no allocating — just pointer manipulation.

 Forms:
   lst1.splice(pos, lst2)            → Move ALL of lst2 into lst1 at pos
   lst1.splice(pos, lst2, it)        → Move single element
   lst1.splice(pos, lst2, first, last) → Move range

 DRY RUN:
   lst1 = {1, 2, 3}, lst2 = {10, 20, 30}
   lst1.splice(lst1.end(), lst2) → lst1 = {1,2,3,10,20,30}, lst2 = {}
   (All done in O(1)!)
*/

void demonstrateSplice() {
    cout << "═══ splice() — O(1) MOVE ═══\n\n";

    list<int> lst1 = {1, 2, 3};
    list<int> lst2 = {10, 20, 30};

    cout << "Before splice:\n";
    cout << "  lst1: "; for (int x : lst1) cout << x << " "; cout << "\n";
    cout << "  lst2: "; for (int x : lst2) cout << x << " "; cout << "\n";

    // Move all of lst2 to end of lst1
    lst1.splice(lst1.end(), lst2);

    cout << "After splice(end, lst2):\n";
    cout << "  lst1: "; for (int x : lst1) cout << x << " "; cout << "\n";
    cout << "  lst2: "; for (int x : lst2) cout << x << " "; cout << "(empty)\n\n";

    // Single element splice
    list<int> a = {1, 2, 3, 4, 5};
    list<int> b = {100};
    auto it = a.begin();
    advance(it, 2);  // Point to 3
    b.splice(b.end(), a, it);  // Move 3 to b
    cout << "After moving element 3:\n";
    cout << "  a: "; for (int x : a) cout << x << " "; cout << "\n";
    cout << "  b: "; for (int x : b) cout << x << " "; cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: merge(), sort(), reverse(), unique(), remove()
// ═══════════════════════════════════════════════════════════════

void demonstrateListAlgorithms() {
    cout << "═══ LIST-SPECIFIC ALGORITHMS ═══\n\n";

    // sort() — list has its OWN sort (can't use std::sort, no random access)
    list<int> lst = {5, 3, 1, 4, 2};
    lst.sort();
    cout << "sort(): "; for (int x : lst) cout << x << " "; cout << "\n";

    // reverse()
    lst.reverse();
    cout << "reverse(): "; for (int x : lst) cout << x << " "; cout << "\n";

    // merge() — merge two sorted lists
    list<int> a = {1, 3, 5, 7};
    list<int> b = {2, 4, 6, 8};
    a.merge(b);  // b becomes empty, a has all elements sorted
    cout << "merge(): "; for (int x : a) cout << x << " "; cout << "\n";

    // remove() — remove all occurrences of value
    list<int> c = {1, 2, 3, 2, 4, 2, 5};
    c.remove(2);
    cout << "remove(2): "; for (int x : c) cout << x << " "; cout << "\n";

    // remove_if()
    list<int> d = {1, 2, 3, 4, 5, 6, 7, 8};
    d.remove_if([](int x) { return x % 2 == 0; });
    cout << "remove_if(even): "; for (int x : d) cout << x << " "; cout << "\n";

    // unique() — remove CONSECUTIVE duplicates (sort first!)
    list<int> e = {1, 1, 2, 2, 2, 3, 3, 1, 1};
    e.unique();
    cout << "unique(): "; for (int x : e) cout << x << " "; cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: WHEN TO USE LIST vs VECTOR
// ═══════════════════════════════════════════════════════════════
/*
 ┌─────────────────────┬──────────────┬──────────────┐
 │ Feature             │ vector       │ list         │
 ├─────────────────────┼──────────────┼──────────────┤
 │ Random access       │ O(1) ✓       │ O(n) ✗       │
 │ Insert at middle    │ O(n)         │ O(1) ✓       │
 │ Erase at middle     │ O(n)         │ O(1) ✓       │
 │ Memory overhead     │ Low          │ High (ptrs)  │
 │ Cache performance   │ Excellent    │ Poor         │
 │ Iterator stability  │ Unstable     │ Stable ✓     │
 │ splice (O(1) move)  │ No           │ Yes ✓        │
 └─────────────────────┴──────────────┴──────────────┘

 VERDICT FOR CP:
 • vector wins 99% of the time (cache + simplicity)
 • list only when you need frequent mid-list insert/erase WITH iterator
 • LRU Cache = classic list + map problem
*/

void demonstrateLRUCachePattern() {
    cout << "═══ LRU CACHE PATTERN (list + map) ═══\n\n";

    // LRU Cache: Most recently used at front, least at back
    int capacity = 3;
    list<pair<int, int>> cache;  // {key, value}
    unordered_map<int, list<pair<int, int>>::iterator> lookup;

    auto put = [&](int key, int value) {
        if (lookup.count(key)) {
            cache.erase(lookup[key]);
        }
        cache.push_front({key, value});
        lookup[key] = cache.begin();
        if ((int)cache.size() > capacity) {
            lookup.erase(cache.back().first);
            cache.pop_back();
        }
    };

    auto get = [&](int key) -> int {
        if (!lookup.count(key)) return -1;
        auto it = lookup[key];
        int val = it->second;
        cache.erase(it);
        cache.push_front({key, val});
        lookup[key] = cache.begin();
        return val;
    };

    put(1, 10);
    put(2, 20);
    put(3, 30);
    cout << "Cache after put(1,10), put(2,20), put(3,30): ";
    for (auto& [k, v] : cache) cout << "(" << k << ":" << v << ") ";
    cout << "\n";

    cout << "get(2) = " << get(2) << "\n";  // Moves 2 to front

    put(4, 40);  // Evicts 1 (least recently used)
    cout << "After put(4,40): ";
    for (auto& [k, v] : cache) cout << "(" << k << ":" << v << ") ";
    cout << "\n";

    cout << "get(1) = " << get(1) << " (evicted!)\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateBasicOps();
    demonstrateSplice();
    demonstrateListAlgorithms();
    demonstrateLRUCachePattern();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. list = doubly linked list, O(1) insert/erase with iterator\n";
    cout << "2. splice() = O(1) move between lists (unique to list)\n";
    cout << "3. list.sort() exists because std::sort needs random access\n";
    cout << "4. Iterators stay valid after insert/erase (unlike vector)\n";
    cout << "5. Use list + map for LRU Cache pattern\n";
    cout << "6. In CP, vector is almost always better (cache performance)\n";

    return 0;
}

