/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — STL DEQUE: DOUBLE-ENDED QUEUE COMPLETE API                    ║
║           From Zero to Grandmaster — STL Mastery                            ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. std::deque Overview
 2. Internal Structure (Block-Based)
 3. All Member Functions
 4. Deque as Stack + Queue
 5. Sliding Window Pattern (Monotonic Deque)

STD::DEQUE OVERVIEW:
───────────────────
  #include <deque>
  Deque = Double-Ended Queue = supports O(1) push/pop at BOTH ends.

  ┌────────────────────────────────────────────┐
  │           ← push_front / pop_front         │
  │  FRONT [10] [20] [30] [40] [50] BACK      │
  │           push_back / pop_back →           │
  └────────────────────────────────────────────┘

  Unlike vector:
    ✅ O(1) push_front and pop_front
    ✅ O(1) push_back and pop_back
    ✅ Random access O(1) with []
    ❌ Not contiguous (block-based memory)

INTERNAL STRUCTURE:
──────────────────
  Deque uses a "map" of pointers to fixed-size blocks:

  Map:  [Block0*] [Block1*] [Block2*] [Block3*]
            ↓          ↓         ↓         ↓
        [_, _, 10]  [20, 30, 40]  [50, _, _]  [_, _, _]
              ↑                      ↑
            front                   back

  When push_front needs space: allocate new block before Block0
  When push_back needs space: allocate new block after last block

ALL MEMBER FUNCTIONS:
────────────────────
  ┌──────────────────┬──────────┬──────────────────────────────┐
  │ Function         │  Time    │ Description                  │
  ├──────────────────┼──────────┼──────────────────────────────┤
  │ push_front(val)  │  O(1)    │ Add at front                 │
  │ push_back(val)   │  O(1)    │ Add at back                  │
  │ pop_front()      │  O(1)    │ Remove from front            │
  │ pop_back()       │  O(1)    │ Remove from back             │
  │ front()          │  O(1)    │ Access front element         │
  │ back()           │  O(1)    │ Access back element          │
  │ operator[](i)    │  O(1)    │ Random access by index       │
  │ at(i)            │  O(1)    │ Bounds-checked access        │
  │ size()           │  O(1)    │ Number of elements           │
  │ empty()          │  O(1)    │ Check if empty               │
  │ clear()          │  O(n)    │ Remove all elements          │
  │ insert(it,val)   │  O(n)    │ Insert at position           │
  │ erase(it)        │  O(n)    │ Erase at position            │
  │ begin()/end()    │  O(1)    │ Iterators (YES, unlike stack)│
  └──────────────────┴──────────┴──────────────────────────────┘
*/

#include <iostream>
#include <deque>
#include <vector>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BASIC OPERATIONS
// ═══════════════════════════════════════════════════════════════

void demonstrateBasics() {
    cout << "═══ SECTION 1: DEQUE BASICS ═══\n\n";

    deque<int> dq;

    // Push from both ends
    dq.push_back(20);
    dq.push_back(30);
    dq.push_front(10);
    dq.push_front(5);

    // State: [5, 10, 20, 30]
    cout << "After push_front(5,10) push_back(20,30):\n  ";
    for (int x : dq) cout << x << " ";
    cout << "\n";

    cout << "  Front: " << dq.front() << "\n";   // 5
    cout << "  Back: " << dq.back() << "\n";      // 30
    cout << "  Size: " << dq.size() << "\n";
    cout << "  dq[2]: " << dq[2] << "\n\n";       // 20 (random access!)

    // Pop from both ends
    dq.pop_front();  // Remove 5
    dq.pop_back();   // Remove 30
    cout << "After pop_front, pop_back:\n  ";
    for (int x : dq) cout << x << " ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: DEQUE AS STACK AND QUEUE
// ═══════════════════════════════════════════════════════════════
/*
  Deque can act as BOTH stack and queue simultaneously!

  As Stack (LIFO):
    push_back() = push
    pop_back()  = pop
    back()      = top

  As Queue (FIFO):
    push_back()  = enqueue
    pop_front()  = dequeue
    front()      = peek
*/

void demonstrateStackQueue() {
    cout << "═══ SECTION 2: DEQUE AS STACK + QUEUE ═══\n\n";

    deque<int> dq;

    // Use as QUEUE (FIFO)
    cout << "As Queue (FIFO):\n";
    dq.push_back(10);   // enqueue
    dq.push_back(20);
    dq.push_back(30);
    cout << "  Enqueued: 10, 20, 30\n";
    cout << "  Dequeue: " << dq.front() << "\n";  // 10
    dq.pop_front();
    cout << "  Dequeue: " << dq.front() << "\n";  // 20
    dq.pop_front();
    dq.clear();

    // Use as STACK (LIFO)
    cout << "\nAs Stack (LIFO):\n";
    dq.push_back(10);   // push
    dq.push_back(20);
    dq.push_back(30);
    cout << "  Pushed: 10, 20, 30\n";
    cout << "  Pop: " << dq.back() << "\n";  // 30
    dq.pop_back();
    cout << "  Pop: " << dq.back() << "\n";  // 20
    dq.pop_back();
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: MONOTONIC DEQUE PATTERN (SLIDING WINDOW MAX)
// ═══════════════════════════════════════════════════════════════
/*
  Sliding Window Maximum — Find max in each window of size k.

  Array: [1, 3, -1, -3, 5, 3, 6, 7], k = 3

  Deque stores INDICES (not values).
  Deque maintains DECREASING order of values.

  DRY RUN:
  ┌─────┬─────────────────┬─────────────────────┬────────────┐
  │  i  │ arr[i]          │ Deque (indices)      │ Window Max │
  ├─────┼─────────────────┼─────────────────────┼────────────┤
  │  0  │  1              │ [0]                  │ —          │
  │  1  │  3 (3>1,pop 0)  │ [1]                  │ —          │
  │  2  │ -1 (-1<3)       │ [1, 2]               │ arr[1]=3   │
  │  3  │ -3 (-3<-1)      │ [1, 2, 3]→pop 1(out) │            │
  │     │                 │ [2, 3]               │ arr[2]=-1  │
  │  4  │  5 (5>all,clear)│ [4]                  │ arr[4]=5   │
  │  5  │  3 (3<5)        │ [4, 5]               │ arr[4]=5   │
  │  6  │  6 (6>3,pop 5)  │ [4,6]→pop 4(out)     │            │
  │     │                 │ [6]                  │ arr[6]=6   │
  │  7  │  7 (7>6,pop 6)  │ [7]                  │ arr[7]=7   │
  └─────┴─────────────────┴─────────────────────┴────────────┘

  Result: [3, -1, 5, 5, 6, 7]  ← Wait, let me recalculate...
  Actually: [3, 3, 5, 5, 6, 7] ✅
*/

vector<int> slidingWindowMax(vector<int>& nums, int k) {
    deque<int> dq;  // Stores indices
    vector<int> result;

    for (int i = 0; i < (int)nums.size(); i++) {
        // Remove indices outside the window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }

        // Remove smaller elements from back (maintain decreasing order)
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // Window is valid when i >= k-1
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    return result;
}

void demonstrateSlidingWindowMax() {
    cout << "═══ SECTION 3: SLIDING WINDOW MAXIMUM ═══\n\n";

    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    cout << "Array: ";
    for (int x : nums) cout << x << " ";
    cout << "\nk = " << k << "\n";

    vector<int> result = slidingWindowMax(nums, k);

    cout << "Sliding window maximums: ";
    for (int x : result) cout << x << " ";
    cout << "\n\n";

    // Trace
    cout << "Step-by-step trace:\n";
    cout << "Window [1,3,-1] → max=3\n";
    cout << "Window [3,-1,-3] → max=3\n";
    cout << "Window [-1,-3,5] → max=5\n";
    cout << "Window [-3,5,3] → max=5\n";
    cout << "Window [5,3,6] → max=6\n";
    cout << "Window [3,6,7] → max=7\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: DEQUE ITERATION & ALGORITHMS
// ═══════════════════════════════════════════════════════════════

void demonstrateIteration() {
    cout << "═══ SECTION 4: DEQUE ITERATION ═══\n\n";

    deque<int> dq = {10, 20, 30, 40, 50};

    // Forward iteration
    cout << "Forward: ";
    for (auto it = dq.begin(); it != dq.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";

    // Reverse iteration
    cout << "Reverse: ";
    for (auto it = dq.rbegin(); it != dq.rend(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";

    // Range-for
    cout << "Range-for: ";
    for (int x : dq) cout << x << " ";
    cout << "\n";

    // Insert and erase
    dq.insert(dq.begin() + 2, 25);  // Insert 25 at index 2
    cout << "After insert 25 at idx 2: ";
    for (int x : dq) cout << x << " ";
    cout << "\n";

    dq.erase(dq.begin() + 3);  // Erase element at index 3
    cout << "After erase at idx 3: ";
    for (int x : dq) cout << x << " ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  STL DEQUE: DOUBLE-ENDED QUEUE COMPLETE API              ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    demonstrateBasics();
    demonstrateStackQueue();
    demonstrateSlidingWindowMax();
    demonstrateIteration();

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "DEQUE vs VECTOR vs LIST:\n";
    cout << "───────────────────────────\n";
    cout << "┌──────────────┬─────────┬─────────┬─────────┐\n";
    cout << "│ Operation    │ deque   │ vector  │ list    │\n";
    cout << "├──────────────┼─────────┼─────────┼─────────┤\n";
    cout << "│ push_front   │ O(1)    │ O(n)    │ O(1)    │\n";
    cout << "│ push_back    │ O(1)    │ O(1)*   │ O(1)    │\n";
    cout << "│ pop_front    │ O(1)    │ O(n)    │ O(1)    │\n";
    cout << "│ pop_back     │ O(1)    │ O(1)    │ O(1)    │\n";
    cout << "│ Random access│ O(1)    │ O(1)    │ O(n)    │\n";
    cout << "│ Insert mid   │ O(n)    │ O(n)    │ O(1)**  │\n";
    cout << "│ Contiguous   │ NO      │ YES     │ NO      │\n";
    cout << "└──────────────┴─────────┴─────────┴─────────┘\n";
    cout << "  * amortized  ** with iterator\n\n";
    cout << "PRACTICE PROBLEMS:\n";
    cout << "───────────────────\n";
    cout << "1. LC 239  — Sliding Window Maximum\n";
    cout << "2. LC 641  — Design Circular Deque\n";
    cout << "3. LC 862  — Shortest Subarray with Sum at Least K\n";
    cout << "4. LC 1425 — Constrained Subsequence Sum\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

