/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           04 — STL PRIORITY QUEUE: MAX HEAP & MIN HEAP                       ║
║           From Zero to Grandmaster — STL Mastery                            ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. std::priority_queue Overview
 2. Max Heap (Default)
 3. Min Heap
 4. Heap with Pairs
 5. Heap of Custom Objects
 6. Internal Heap Operations Visualization
 7. Dry Run & Complexity

STD::PRIORITY_QUEUE OVERVIEW:
─────────────────────────────
  #include <queue>
  std::priority_queue<T> — Container adaptor implementing a HEAP.

  Default: MAX HEAP (largest element on top)
  Min Heap: priority_queue<int, vector<int>, greater<int>>

  ┌────────────────────────────────────────────────────────┐
  │  MAX HEAP (default):                                   │
  │  priority_queue<int> pq;                               │
  │  pq.push(10); pq.push(40); pq.push(20);               │
  │                                                        │
  │       40           ← pq.top() always returns MAX       │
  │      /  \                                              │
  │    10    20                                            │
  │                                                        │
  │  MIN HEAP:                                             │
  │  priority_queue<int, vector<int>, greater<int>> pq;    │
  │                                                        │
  │       10           ← pq.top() always returns MIN       │
  │      /  \                                              │
  │    40    20                                            │
  └────────────────────────────────────────────────────────┘

ALL MEMBER FUNCTIONS:
────────────────────
  ┌────────────────┬──────────┬────────────────────────────────────┐
  │ Function       │  Time    │ Description                        │
  ├────────────────┼──────────┼────────────────────────────────────┤
  │ push(val)      │ O(log n) │ Insert element, maintains heap     │
  │ pop()          │ O(log n) │ Remove top element (void!)         │
  │ top()          │ O(1)     │ Access top element (max or min)    │
  │ empty()        │ O(1)     │ Check if heap is empty             │
  │ size()         │ O(1)     │ Number of elements                 │
  │ emplace(args)  │ O(log n) │ Construct in-place                 │
  │ swap(other)    │ O(1)     │ Swap contents                      │
  └────────────────┴──────────┴────────────────────────────────────┘

  ⚠️ NO: iterator, clear(), find(), decrease-key, random access
  For decrease-key → use Indexed Priority Queue (Chapter 08)
*/

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <functional>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: MAX HEAP (DEFAULT)
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN — push 10, 30, 20, 40, 5 into MAX HEAP:

  push(10):     10

  push(30):     30          (30 > 10, bubble up)
               /
              10

  push(20):     30
               / \
              10   20

  push(40):     40          (40 > 10 → swap, 40 > 30 → swap)
               / \
              30   20
             /
            10

  push(5):      40
               / \
              30   20
             / \
            10   5

  top() → 40 (maximum always at root)

  pop():
    Remove 40, put last element (5) at root, heapify down:
        5           30          30
       / \    →    / \    →    / \
      30   20    5    20     10   20
     /          /            /
    10         10           5

  top() → 30
*/

void demonstrateMaxHeap() {
    cout << "═══ SECTION 1: MAX HEAP (default) ═══\n\n";

    priority_queue<int> maxHeap;

    // Push elements
    for (int v : {10, 30, 20, 40, 5}) {
        maxHeap.push(v);
        cout << "  Push " << v << " → top = " << maxHeap.top() << "\n";
    }
    cout << "\n  Size: " << maxHeap.size() << "\n";

    // Extract all in sorted (descending) order
    cout << "  Extract all (descending): ";
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: MIN HEAP
// ═══════════════════════════════════════════════════════════════
/*
  Three parameters: priority_queue<Type, Container, Comparator>

  Min Heap: priority_queue<int, vector<int>, greater<int>>

  greater<int> means: parent should be GREATER than children?
  NO! It means the comparison function returns true when a > b,
  and priority_queue puts the element that is NOT "greater" on top.
  So the SMALLEST element ends up on top.

  Memory trick:
    MAX heap = default = less<int>    → LARGEST on top
    MIN heap = greater<int>            → SMALLEST on top
*/

void demonstrateMinHeap() {
    cout << "═══ SECTION 2: MIN HEAP ═══\n\n";

    priority_queue<int, vector<int>, greater<int>> minHeap;

    for (int v : {10, 30, 20, 40, 5}) {
        minHeap.push(v);
        cout << "  Push " << v << " → top = " << minHeap.top() << "\n";
    }

    cout << "\n  Extract all (ascending): ";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: HEAP WITH PAIRS
// ═══════════════════════════════════════════════════════════════
/*
  pair<int,int> comparison: first by .first, then by .second

  MAX HEAP of pairs: largest (first, second) on top
  MIN HEAP of pairs: smallest (first, second) on top

  Use case: Dijkstra's algorithm → min heap of (distance, node)
*/

void demonstratePairHeap() {
    cout << "═══ SECTION 3: HEAP WITH PAIRS ═══\n\n";

    // Max heap of pairs
    priority_queue<pair<int, string>> maxPQ;
    maxPQ.push({3, "Apple"});
    maxPQ.push({1, "Banana"});
    maxPQ.push({5, "Cherry"});
    maxPQ.push({2, "Date"});

    cout << "Max heap of (priority, item):\n";
    while (!maxPQ.empty()) {
        auto [pri, item] = maxPQ.top();
        maxPQ.pop();
        cout << "  (" << pri << ", " << item << ")\n";
    }

    // Min heap of pairs (Dijkstra style)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minPQ;
    minPQ.push({10, 0});  // (distance=10, node=0)
    minPQ.push({5, 1});
    minPQ.push({15, 2});
    minPQ.push({3, 3});

    cout << "\nMin heap of (distance, node) — Dijkstra style:\n";
    while (!minPQ.empty()) {
        auto [dist, node] = minPQ.top();
        minPQ.pop();
        cout << "  (dist=" << dist << ", node=" << node << ")\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: HEAP SORT USING PRIORITY QUEUE
// ═══════════════════════════════════════════════════════════════
/*
  To sort array in ASCENDING order:
    1. Push all into MIN HEAP
    2. Pop all → sorted ascending

  Or:
    1. Push all into MAX HEAP
    2. Pop all → sorted descending → reverse

  Time: O(n log n)  Space: O(n)
*/

void demonstrateHeapSort() {
    cout << "═══ SECTION 4: HEAP SORT USING PQ ═══\n\n";

    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};

    cout << "Original: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    // Method 1: Min heap → ascending
    priority_queue<int, vector<int>, greater<int>> minH(arr.begin(), arr.end());
    cout << "Ascending:  ";
    while (!minH.empty()) {
        cout << minH.top() << " ";
        minH.pop();
    }
    cout << "\n";

    // Method 2: Max heap → descending
    priority_queue<int> maxH(arr.begin(), arr.end());
    cout << "Descending: ";
    while (!maxH.empty()) {
        cout << maxH.top() << " ";
        maxH.pop();
    }
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: BUILD HEAP FROM VECTOR
// ═══════════════════════════════════════════════════════════════

void demonstrateBuildHeap() {
    cout << "═══ SECTION 5: BUILD HEAP FROM VECTOR ═══\n\n";

    vector<int> v = {10, 20, 30, 5, 15};

    // Method 1: Constructor with iterators — O(n)
    priority_queue<int> pq1(v.begin(), v.end());
    cout << "Built from vector (O(n)): top = " << pq1.top() << "\n";

    // Method 2: Push one by one — O(n log n)
    priority_queue<int> pq2;
    for (int x : v) pq2.push(x);
    cout << "Push one by one (O(n log n)): top = " << pq2.top() << "\n";

    cout << "\n  ✅ Constructor method is faster (O(n) vs O(n log n))\n";
    cout << "     Use it when you have all elements upfront!\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  STL PRIORITY QUEUE: MAX HEAP & MIN HEAP                 ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    demonstrateMaxHeap();
    demonstrateMinHeap();
    demonstratePairHeap();
    demonstrateHeapSort();
    demonstrateBuildHeap();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "QUICK REFERENCE:\n";
    cout << "─────────────────\n";
    cout << "  Max Heap: priority_queue<int> pq;\n";
    cout << "  Min Heap: priority_queue<int, vector<int>, greater<int>> pq;\n";
    cout << "  Pair Max: priority_queue<pair<int,int>> pq;\n";
    cout << "  Pair Min: priority_queue<pair<int,int>,\n";
    cout << "              vector<pair<int,int>>, greater<pair<int,int>>> pq;\n\n";
    cout << "PRACTICE PROBLEMS:\n";
    cout << "───────────────────\n";
    cout << "1. LC 215  — Kth Largest Element\n";
    cout << "2. LC 347  — Top K Frequent Elements\n";
    cout << "3. LC 23   — Merge K Sorted Lists\n";
    cout << "4. LC 295  — Find Median from Data Stream\n";
    cout << "5. LC 1046 — Last Stone Weight\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

