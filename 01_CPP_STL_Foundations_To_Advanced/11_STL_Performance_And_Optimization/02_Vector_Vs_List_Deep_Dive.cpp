/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — VECTOR vs LIST DEEP DIVE                                    ║
║           From Zero to Grandmaster — The Truth About Linked Lists          ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Memory Layout: Contiguous vs Node-Based
 2. Cache Locality — Why vector DESTROYS list
 3. Insertion/Deletion Benchmark
 4. When list ACTUALLY Wins (splice, iterator stability)
 5. The GM Verdict

═══════════════════════════════════════════════════════════════════════════════
 MEMORY LAYOUT COMPARISON
═══════════════════════════════════════════════════════════════════════════════

 VECTOR (contiguous memory):
 ┌────┬────┬────┬────┬────┬────┬────┬────┐
 │ 10 │ 20 │ 30 │ 40 │ 50 │ 60 │ 70 │ 80 │  ← All in ONE block
 └────┴────┴────┴────┴────┴────┴────┴────┘
  CPU loads entire cache line (64 bytes = 16 ints) in ONE memory fetch!
  Next element = current address + sizeof(T) → PREDICTABLE

 LIST (scattered nodes):
       ┌──────────┐     ┌──────────┐     ┌──────────┐
  ──→  │prev|10|nxt│──→ │prev|20|nxt│──→ │prev|30|nxt│──→
       └──────────┘     └──────────┘     └──────────┘
       addr: 0xA000      addr: 0xF500      addr: 0x3200
  Each node is SOMEWHERE in memory → CPU can't predict next address
  Every node access = potential CACHE MISS = ~100x slower!

 MEMORY OVERHEAD PER ELEMENT:
   vector: sizeof(T) per element (4 bytes for int)
   list:   sizeof(T) + 2×sizeof(pointer) = 4 + 16 = 20 bytes per int!
   → list uses 5× more memory than vector for ints
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: SEQUENTIAL ACCESS BENCHMARK
// ═══════════════════════════════════════════════════════════════
/*
 Simply iterating through all elements.
 vector should CRUSH list due to cache locality.
*/

void benchmarkSequentialAccess() {
    cout << "═══ SEQUENTIAL ACCESS BENCHMARK ═══\n\n";

    const int N = 500000;

    // Vector
    vector<int> v(N);
    iota(v.begin(), v.end(), 0);

    auto start = chrono::steady_clock::now();
    long long sum = 0;
    for (int rep = 0; rep < 100; rep++)
        for (int x : v) sum += x;
    auto t_vec = chrono::duration_cast<chrono::milliseconds>(
        chrono::steady_clock::now() - start).count();

    // List
    list<int> lst(v.begin(), v.end());

    start = chrono::steady_clock::now();
    sum = 0;
    for (int rep = 0; rep < 100; rep++)
        for (int x : lst) sum += x;
    auto t_list = chrono::duration_cast<chrono::milliseconds>(
        chrono::steady_clock::now() - start).count();

    cout << "Iterate 5×10^5 elements × 100 times:\n";
    cout << "  vector: " << t_vec << " ms\n";
    cout << "  list:   " << t_list << " ms\n";
    cout << "  Ratio:  list is ~" << (t_list > 0 && t_vec > 0 ? t_list / max(t_vec, 1L) : 0)
         << "x slower\n";
    cout << "  Reason: CACHE MISSES on every node hop\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: MIDDLE INSERTION BENCHMARK
// ═══════════════════════════════════════════════════════════════
/*
 "But list is O(1) for insert, vector is O(n)!"

 REALITY CHECK:
   list insert = O(1) if you HAVE the iterator
   But FINDING the position = O(n) in list (no random access!)

   vector insert at middle = O(n) to shift elements
   But shifting contiguous memory is FAST (memcpy-like)

   For small-to-medium N, vector insert is FASTER than list insert
   because cache-friendly shifting beats pointer-chasing!
*/

void benchmarkMiddleInsert() {
    cout << "═══ MIDDLE INSERTION BENCHMARK ═══\n\n";

    const int N = 50000;

    // Vector: insert at middle
    {
        vector<int> v;
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < N; i++) {
            auto pos = v.begin() + v.size() / 2;
            v.insert(pos, i);
        }
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "Insert at middle (5×10^4):\n";
        cout << "  vector: " << ms << " ms\n";
    }

    // List: insert at middle (need to traverse to find middle!)
    {
        list<int> lst;
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < N; i++) {
            auto pos = lst.begin();
            advance(pos, lst.size() / 2);  // O(n) to find middle!
            lst.insert(pos, i);
        }
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "  list:   " << ms << " ms (includes O(n) to find middle!)\n\n";
    }
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: WHEN LIST ACTUALLY WINS
// ═══════════════════════════════════════════════════════════════
/*
 LIST WINS WHEN:
 ───────────────
 1. You have iterators and do frequent insert/erase WITHOUT traversal
 2. You need splice() — O(1) move between lists
 3. You need iterator stability (iterators don't invalidate on insert/erase)
 4. LRU Cache pattern (list + map)

 DRY RUN — splice():
   lst1 = {1, 2, 3, 4, 5}
   lst2 = {10, 20, 30}

   lst1.splice(lst1.end(), lst2)  → O(1)!
   lst1 = {1, 2, 3, 4, 5, 10, 20, 30}
   lst2 = {}

   With vector, this would be O(n) copy!
*/

void demonstrateListWins() {
    cout << "═══ WHEN LIST WINS ═══\n\n";

    // Case 1: splice — O(1) element transfer
    cout << "--- splice() = O(1) Move ---\n";
    list<int> lst1 = {1, 2, 3, 4, 5};
    list<int> lst2 = {10, 20, 30, 40, 50};

    cout << "Before: lst1="; for (int x : lst1) cout << x << " ";
    cout << "  lst2="; for (int x : lst2) cout << x << " ";
    cout << "\n";

    auto start = chrono::steady_clock::now();
    for (int i = 0; i < 100000; i++) {
        // Move all of lst2 to end of lst1, then move back
        lst1.splice(lst1.end(), lst2);
        lst2.splice(lst2.begin(), lst1, next(lst1.begin(), 5), lst1.end());
    }
    auto t_splice = chrono::duration_cast<chrono::microseconds>(
        chrono::steady_clock::now() - start).count();

    cout << "After 10^5 splice round-trips: " << t_splice << " μs\n";
    cout << "lst1="; for (int x : lst1) cout << x << " ";
    cout << "  lst2="; for (int x : lst2) cout << x << " ";
    cout << "\n\n";

    // Case 2: Iterator stability
    cout << "--- Iterator Stability ---\n";
    list<int> lst = {10, 20, 30, 40, 50};
    auto it = next(lst.begin(), 2);  // Points to 30
    cout << "Iterator points to: " << *it << "\n";

    lst.insert(it, 25);  // Insert before 30
    cout << "After insert 25: iterator STILL points to " << *it << " ✓\n";

    lst.erase(lst.begin());  // Erase 10
    cout << "After erase front: iterator STILL points to " << *it << " ✓\n";
    cout << "List: "; for (int x : lst) cout << x << " "; cout << "\n";
    cout << "(In vector, both operations would INVALIDATE the iterator!)\n\n";

    // Case 3: LRU Cache (classic list + map)
    cout << "--- LRU Cache Pattern ---\n";
    cout << "list<Key> + unordered_map<Key, list::iterator>\n";
    cout << "• Access: move element to front via splice → O(1)\n";
    cout << "• Evict:  pop_back → O(1)\n";
    cout << "• Lookup: unordered_map → O(1)\n";
    cout << "THIS is the canonical use of list in CP/interviews.\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: COMPLETE COMPARISON TABLE
// ═══════════════════════════════════════════════════════════════

void printComparisonTable() {
    cout << "═══ COMPLETE vector vs list COMPARISON ═══\n\n";
    cout << "┌─────────────────────────┬──────────────────┬──────────────────┐\n";
    cout << "│ Feature                 │ vector           │ list             │\n";
    cout << "├─────────────────────────┼──────────────────┼──────────────────┤\n";
    cout << "│ Memory layout           │ Contiguous ✓     │ Scattered nodes  │\n";
    cout << "│ Cache performance       │ Excellent ✓      │ Terrible         │\n";
    cout << "│ Random access           │ O(1) ✓           │ O(n)             │\n";
    cout << "│ push_back               │ O(1) amort ✓     │ O(1)             │\n";
    cout << "│ push_front              │ O(n)             │ O(1) ✓           │\n";
    cout << "│ Insert at middle        │ O(n) shift       │ O(1) w/iter ✓    │\n";
    cout << "│ Erase at middle         │ O(n) shift       │ O(1) w/iter ✓    │\n";
    cout << "│ Find element            │ O(n)             │ O(n)             │\n";
    cout << "│ sort                    │ O(n log n) ✓     │ O(n log n)       │\n";
    cout << "│ splice (O(1) transfer)  │ N/A              │ O(1) ✓           │\n";
    cout << "│ Iterator stability      │ Invalidated ✗    │ Stable ✓         │\n";
    cout << "│ Memory per int          │ 4 bytes          │ ~20 bytes        │\n";
    cout << "│ Use in CP               │ 99% ✓            │ 1% (LRU only)   │\n";
    cout << "└─────────────────────────┴──────────────────┴──────────────────┘\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: DEQUE — THE MIDDLE GROUND
// ═══════════════════════════════════════════════════════════════

void dequeComparison() {
    cout << "═══ DEQUE — THE MIDDLE GROUND ═══\n\n";

    cout << "deque = double-ended queue (blocks of contiguous memory)\n\n";
    cout << "┌─────────────────────────┬──────────┬──────────┬──────────┐\n";
    cout << "│ Feature                 │ vector   │ deque    │ list     │\n";
    cout << "├─────────────────────────┼──────────┼──────────┼──────────┤\n";
    cout << "│ push_front              │ O(n)     │ O(1) ✓   │ O(1)     │\n";
    cout << "│ push_back               │ O(1)     │ O(1) ✓   │ O(1)     │\n";
    cout << "│ Random access           │ O(1) ✓   │ O(1) ✓   │ O(n)     │\n";
    cout << "│ Cache performance       │ Best ✓   │ Good     │ Bad      │\n";
    cout << "│ Iterator invalidation   │ All ✗    │ All ✗    │ None ✓   │\n";
    cout << "│ When to use             │ Default  │ BFS/     │ LRU/     │\n";
    cout << "│                         │          │ Monotonic│ splice   │\n";
    cout << "└─────────────────────────┴──────────┴──────────┴──────────┘\n\n";

    cout << "CP USE CASES FOR DEQUE:\n";
    cout << "  • 0-1 BFS (push_front for 0-cost, push_back for 1-cost)\n";
    cout << "  • Monotonic deque for sliding window min/max\n";
    cout << "  • Underlying container for queue, stack (default)\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    benchmarkSequentialAccess();
    benchmarkMiddleInsert();
    demonstrateListWins();
    printComparisonTable();
    dequeComparison();

    cout << "═══ GM VERDICT ═══\n";
    cout << "1. Use vector for 99% of problems — cache is king\n";
    cout << "2. Use deque for 0-1 BFS and monotonic queue\n";
    cout << "3. Use list ONLY for LRU Cache (list + map pattern)\n";
    cout << "4. 'list is O(1) insert' is misleading — finding position is O(n)\n";
    cout << "5. Memory: vector=4 bytes/int, list=20 bytes/int\n";
    cout << "6. Cache miss costs ~100 cycles vs ~4 for cache hit\n";

    return 0;
}

