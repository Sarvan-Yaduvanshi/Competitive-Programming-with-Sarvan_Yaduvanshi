/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — EDGE CASES, OPTIMIZATION & COMPLETE PROBLEM CHEAT SHEET       ║
║           From Zero to Grandmaster — Edge Cases & Optimization              ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Stack Edge Cases
 2. Queue Edge Cases
 3. Heap Edge Cases
 4. Performance Optimization Tips
 5. TLE Avoidance Guide
 6. Complete Problem Cheat Sheet (150+ Problems)

STACK EDGE CASES:
────────────────
  ❌ top() on empty stack → UNDEFINED BEHAVIOR!
     ✅ Always check empty() first

  ❌ pop() on empty stack → UNDEFINED BEHAVIOR!
     ✅ Guard with if (!st.empty()) st.pop();

  ❌ Assuming pop() returns value
     ✅ STL pop() is void! Use top() then pop().

  ❌ Stack overflow with deep recursion
     ✅ Use iterative stack instead, or increase stack size
     ✅ #pragma comment(linker, "/STACK:1000000000") // Windows
     ✅ ulimit -s unlimited  // Linux

  ❌ Forgetting to handle single element
     ✅ A single element can be both NGE and NSE target

QUEUE EDGE CASES:
────────────────
  ❌ front() or back() on empty queue → UB!
  ❌ Circular queue: confusing full vs empty
     ✅ Use count variable, not just front==rear
  ❌ BFS: not marking visited BEFORE pushing
     ✅ Mark visited when pushing, not when popping (avoids TLE!)

HEAP / PRIORITY QUEUE EDGE CASES:
─────────────────────────────────
  ❌ top() on empty PQ → UB!
  ❌ Assuming PQ supports find() or erase() → it doesn't!
     ✅ Use multiset for ordered set with erase
     ✅ Use lazy deletion pattern
  ❌ Integer overflow in comparisons
     ✅ Use long long for distances in Dijkstra
  ❌ Stale entries after updates → Dijkstra TLE
     ✅ Check if dist[u] != d before processing
  ❌ Custom comparator logic inverted → max instead of min
     ✅ comp(a,b)=true means "a has LOWER priority"

PERFORMANCE OPTIMIZATION:
────────────────────────
  1. reserve() for vectors inside PQ → fewer reallocations
  2. Build heap from vector O(n) instead of n inserts O(n log n)
     priority_queue<int> pq(v.begin(), v.end());
  3. Use emplace instead of push for complex objects
  4. For Dijkstra: skip stale entries → if (d > dist[u]) continue;
  5. In BFS: mark visited WHEN pushing, not when popping
  6. For monotonic stack/deque: each element pushed/popped once → O(n)
  7. Avoid std::endl (flushes buffer), use "\n" instead
  8. Use scanf/printf or ios::sync_with_stdio(false) for fast I/O
*/

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <cassert>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: SAFE WRAPPERS
// ═══════════════════════════════════════════════════════════════

template<typename T>
class SafeStack {
    stack<T> st;
public:
    void push(T val) { st.push(val); }

    bool pop() {
        if (st.empty()) return false;
        st.pop();
        return true;
    }

    bool top(T& result) {
        if (st.empty()) return false;
        result = st.top();
        return true;
    }

    bool empty() { return st.empty(); }
    int size() { return st.size(); }
};

// ═══════════════════════════════════════════════════════════════
// SECTION 2: EDGE CASE TESTS
// ═══════════════════════════════════════════════════════════════

void testEdgeCases() {
    cout << "═══ EDGE CASE TESTS ═══\n\n";

    // Empty stack operations
    cout << "1. Empty structure tests:\n";
    SafeStack<int> ss;
    int val;
    cout << "  top() on empty: " << (ss.top(val) ? "OK" : "SAFE: returned false") << "\n";
    cout << "  pop() on empty: " << (ss.pop() ? "OK" : "SAFE: returned false") << "\n";

    // Single element
    cout << "\n2. Single element tests:\n";
    ss.push(42);
    cout << "  top(): "; ss.top(val); cout << val << "\n";
    ss.pop();
    cout << "  After pop, empty: " << ss.empty() << "\n";

    // Priority queue edge cases
    cout << "\n3. PQ edge cases:\n";
    priority_queue<int> pq;
    // pq.top() here would be UB!
    pq.push(5); pq.push(3); pq.push(5);
    cout << "  Duplicates in PQ: ";
    while (!pq.empty()) { cout << pq.top() << " "; pq.pop(); }
    cout << "(duplicates preserved!)\n";

    // Large values
    cout << "\n4. Large value test:\n";
    priority_queue<long long, vector<long long>, greater<long long>> llpq;
    llpq.push(1e18);
    llpq.push(-1e18);
    llpq.push(0);
    cout << "  Min of {1e18, -1e18, 0}: " << llpq.top() << "\n";

    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: PERFORMANCE TIPS
// ═══════════════════════════════════════════════════════════════

void performanceTips() {
    cout << "═══ PERFORMANCE OPTIMIZATION DEMO ═══\n\n";

    // Tip 1: Build heap from vector (O(n) vs O(n log n))
    vector<int> v = {5, 3, 8, 1, 9, 2, 7};

    // Slow: push one by one
    priority_queue<int> slow;
    for (int x : v) slow.push(x);  // O(n log n)

    // Fast: construct from iterators
    priority_queue<int> fast(v.begin(), v.end());  // O(n)

    cout << "  Build heap: constructor O(n) > push loop O(n log n)\n";

    // Tip 2: Fast I/O
    cout << "  Fast I/O: ios::sync_with_stdio(false); cin.tie(0);\n";
    cout << "  Use '\\n' not endl (endl flushes buffer!)\n";

    // Tip 3: BFS mark when pushing
    cout << "  BFS: Mark visited WHEN PUSHING, not when popping!\n";
    cout << "  Wrong: pop → check visited → process\n";
    cout << "  Right: push → mark visited → later pop → process\n";

    // Tip 4: Dijkstra skip stale
    cout << "  Dijkstra: if (d > dist[u]) continue; // Skip stale\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: COMPLETE CHEAT SHEET
// ═══════════════════════════════════════════════════════════════

void printCheatSheet() {
    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "    COMPLETE PROBLEM CHEAT SHEET — 150+ PROBLEMS          \n";
    cout << "═══════════════════════════════════════════════════════════\n\n";

    cout << "📚 STACK PROBLEMS:\n";
    cout << "─────────────────\n";
    cout << "  LC 20   — Valid Parentheses\n";
    cout << "  LC 32   — Longest Valid Parentheses ★\n";
    cout << "  LC 71   — Simplify Path\n";
    cout << "  LC 84   — Largest Rectangle in Histogram ★★★\n";
    cout << "  LC 85   — Maximal Rectangle ★★\n";
    cout << "  LC 150  — Evaluate Reverse Polish Notation\n";
    cout << "  LC 155  — Min Stack ★\n";
    cout << "  LC 224  — Basic Calculator ★★\n";
    cout << "  LC 227  — Basic Calculator II\n";
    cout << "  LC 316  — Remove Duplicate Letters ★\n";
    cout << "  LC 394  — Decode String ★\n";
    cout << "  LC 402  — Remove K Digits ★\n";
    cout << "  LC 456  — 132 Pattern ★★\n";
    cout << "  LC 496  — Next Greater Element I\n";
    cout << "  LC 503  — Next Greater Element II\n";
    cout << "  LC 636  — Exclusive Time of Functions\n";
    cout << "  LC 682  — Baseball Game\n";
    cout << "  LC 716  — Max Stack ★★\n";
    cout << "  LC 735  — Asteroid Collision ★\n";
    cout << "  LC 739  — Daily Temperatures ★\n";
    cout << "  LC 853  — Car Fleet ★\n";
    cout << "  LC 856  — Score of Parentheses\n";
    cout << "  LC 895  — Maximum Frequency Stack ★★\n";
    cout << "  LC 901  — Online Stock Span ★\n";
    cout << "  LC 907  — Sum of Subarray Minimums ★★★\n";
    cout << "  LC 921  — Minimum Add to Make Valid\n";
    cout << "  LC 1019 — Next Greater Node in Linked List\n";
    cout << "  LC 1047 — Remove All Adjacent Duplicates\n";
    cout << "  LC 1249 — Minimum Remove to Make Valid\n";
    cout << "  LC 1673 — Most Competitive Subsequence\n";
    cout << "  LC 2104 — Sum of Subarray Ranges ★★\n";
    cout << "  CSES 1645 — Nearest Smaller Values\n\n";

    cout << "📬 QUEUE & DEQUE PROBLEMS:\n";
    cout << "──────────────────────────\n";
    cout << "  LC 102  — Binary Tree Level Order Traversal\n";
    cout << "  LC 200  — Number of Islands (BFS)\n";
    cout << "  LC 225  — Implement Stack using Queues\n";
    cout << "  LC 232  — Implement Queue using Stacks ★\n";
    cout << "  LC 239  — Sliding Window Maximum ★★★\n";
    cout << "  LC 346  — Moving Average from Data Stream\n";
    cout << "  LC 542  — 01 Matrix (Multi-source BFS)\n";
    cout << "  LC 622  — Design Circular Queue\n";
    cout << "  LC 641  — Design Circular Deque\n";
    cout << "  LC 862  — Shortest Subarray with Sum ≥ K ★★★\n";
    cout << "  LC 933  — Number of Recent Calls\n";
    cout << "  LC 994  — Rotting Oranges ★\n";
    cout << "  LC 1091 — Shortest Path in Binary Matrix\n";
    cout << "  LC 1293 — Shortest Path with Obstacles ★★\n";
    cout << "  LC 1425 — Constrained Subsequence Sum ★★\n";
    cout << "  LC 1438 — Longest Subarray |max-min| ≤ k ★★\n";
    cout << "  LC 1472 — Design Browser History\n\n";

    cout << "🔺 HEAP & PRIORITY QUEUE PROBLEMS:\n";
    cout << "──────────────────────────────────\n";
    cout << "  LC 23   — Merge K Sorted Lists ★★★\n";
    cout << "  LC 42   — Trapping Rain Water ★★\n";
    cout << "  LC 146  — LRU Cache ★★★\n";
    cout << "  LC 215  — Kth Largest Element ★\n";
    cout << "  LC 218  — The Skyline Problem ★★★\n";
    cout << "  LC 253  — Meeting Rooms II ★\n";
    cout << "  LC 264  — Ugly Number II\n";
    cout << "  LC 295  — Find Median from Data Stream ★★★\n";
    cout << "  LC 313  — Super Ugly Number\n";
    cout << "  LC 347  — Top K Frequent Elements ★★\n";
    cout << "  LC 355  — Design Twitter\n";
    cout << "  LC 373  — Find K Pairs with Smallest Sums ★\n";
    cout << "  LC 378  — Kth Smallest in Sorted Matrix ★\n";
    cout << "  LC 407  — Trapping Rain Water II (3D) ★★★\n";
    cout << "  LC 451  — Sort Characters By Frequency\n";
    cout << "  LC 460  — LFU Cache ★★★\n";
    cout << "  LC 480  — Sliding Window Median ★★★\n";
    cout << "  LC 502  — IPO ★★\n";
    cout << "  LC 621  — Task Scheduler ★★\n";
    cout << "  LC 632  — Smallest Range Covering K Lists ★★★\n";
    cout << "  LC 692  — Top K Frequent Words ★\n";
    cout << "  LC 703  — Kth Largest Element in Stream\n";
    cout << "  LC 743  — Network Delay Time (Dijkstra) ★★\n";
    cout << "  LC 767  — Reorganize String ★\n";
    cout << "  LC 778  — Swim in Rising Water ★★\n";
    cout << "  LC 787  — Cheapest Flights K Stops ★★\n";
    cout << "  LC 857  — Minimum Cost to Hire K Workers ★★★\n";
    cout << "  LC 973  — K Closest Points ★\n";
    cout << "  LC 1046 — Last Stone Weight\n";
    cout << "  LC 1353 — Maximum Number of Events ★★\n";
    cout << "  LC 1792 — Maximum Average Pass Ratio ★\n";
    cout << "  CSES 1163 — Traffic Lights ★★\n";
    cout << "  CSES 1671 — Shortest Routes I (Dijkstra)\n";
    cout << "  CSES 1077 — Sliding Window Cost ★★\n\n";

    cout << "🏆 TOPOLOGICAL SORT (KAHN'S):\n";
    cout << "─────────────────────────────\n";
    cout << "  LC 207  — Course Schedule\n";
    cout << "  LC 210  — Course Schedule II ★\n";
    cout << "  LC 269  — Alien Dictionary ★★\n";
    cout << "  LC 310  — Minimum Height Trees ★★\n";
    cout << "  LC 1136 — Parallel Courses ★\n";
    cout << "  CSES 1679 — Course Schedule\n\n";

    cout << "★ = Important  ★★ = Very Important  ★★★ = Must Know\n\n";
}

// ═══════════════════════════════════════════════════════════════

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  EDGE CASES, OPTIMIZATION & PROBLEM CHEAT SHEET          ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    testEdgeCases();
    performanceTips();
    printCheatSheet();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "FINAL TIPS FOR COMPETITIVE PROGRAMMING:\n";
    cout << "───────────────────────────────────────\n";
    cout << "1. Always check empty() before top()/front()/pop()\n";
    cout << "2. STL pop() is void — save value first!\n";
    cout << "3. For Kth largest → MIN heap of size K\n";
    cout << "4. For Kth smallest → MAX heap of size K\n";
    cout << "5. Monotonic stack: each element pushed/popped ONCE → O(n)\n";
    cout << "6. Sliding window + deque = O(n) for min/max queries\n";
    cout << "7. Two heaps = running median / partitioning\n";
    cout << "8. Build heap from vector = O(n), push loop = O(n log n)\n";
    cout << "9. Dijkstra: skip stale entries for TLE prevention\n";
    cout << "10. BFS: mark visited WHEN PUSHING!\n";
    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "\n  Made with ❤️  by Sarvan Yaduvanshi\n";
    cout << "  \"Stack, Queue, Heap — Master these three,\n";
    cout << "   and you unlock 40%% of all CP problems.\"\n\n";

    return 0;
}

