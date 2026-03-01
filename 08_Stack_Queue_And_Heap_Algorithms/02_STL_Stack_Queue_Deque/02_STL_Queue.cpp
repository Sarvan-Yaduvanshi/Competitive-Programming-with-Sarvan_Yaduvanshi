/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — STL QUEUE: COMPLETE API & USAGE                               ║
║           From Zero to Grandmaster — STL Mastery                            ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. std::queue Overview
 2. All Member Functions
 3. BFS Pattern with Queue
 4. Level-Order Traversal Pattern
 5. Common Patterns & Tips

STD::QUEUE OVERVIEW:
───────────────────
  #include <queue>
  std::queue<T> — container adaptor, FIFO.
  Default underlying container: std::deque<T>

  ┌────────────────────────────────────────────┐
  │  queue<int> q;                             │
  │                                            │
  │  Internally uses deque:                    │
  │  deque: [10, 20, 30, 40]                   │
  │          ↑               ↑                 │
  │        FRONT            BACK               │
  │                                            │
  │  q.push(50) → deque.push_back(50)         │
  │  q.pop()    → deque.pop_front()           │
  │  q.front()  → deque.front()              │
  │  q.back()   → deque.back()               │
  └────────────────────────────────────────────┘

ALL MEMBER FUNCTIONS:
────────────────────
  ┌────────────────┬──────────┬────────────────────────────────┐
  │ Function       │  Time    │ Description                    │
  ├────────────────┼──────────┼────────────────────────────────┤
  │ push(val)      │  O(1)    │ Add element at back            │
  │ pop()          │  O(1)    │ Remove front element (void!)   │
  │ front()        │  O(1)    │ Reference to front element     │
  │ back()         │  O(1)    │ Reference to back element      │
  │ empty()        │  O(1)    │ Check if queue is empty        │
  │ size()         │  O(1)    │ Number of elements             │
  │ emplace(args)  │  O(1)    │ Construct element in-place     │
  │ swap(other)    │  O(1)    │ Swap contents                  │
  └────────────────┴──────────┴────────────────────────────────┘
*/

#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BASIC OPERATIONS
// ═══════════════════════════════════════════════════════════════

void demonstrateBasics() {
    cout << "═══ SECTION 1: STL QUEUE BASICS ═══\n\n";

    queue<int> q;

    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);

    cout << "After push(10, 20, 30, 40):\n";
    cout << "  Front: " << q.front() << "\n";     // 10
    cout << "  Back: " << q.back() << "\n";        // 40
    cout << "  Size: " << q.size() << "\n\n";      // 4

    // Pop removes from FRONT
    q.pop();
    cout << "After pop(): Front = " << q.front() << "\n\n";  // 20

    // Print all (destructive)
    cout << "Print all (FIFO order): ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: BFS PATTERN (MOST IMPORTANT QUEUE USAGE)
// ═══════════════════════════════════════════════════════════════
/*
  BFS using queue — explore level by level:

  Graph:  0 — 1 — 3
          |   |
          2   4

  Adjacency list:
    0: [1, 2]
    1: [0, 3, 4]
    2: [0]
    3: [1]
    4: [1]

  BFS from node 0:
  ┌────────────────────────────────────────────────────────┐
  │ Step 0: queue=[0], visited={0}                         │
  │ Step 1: process 0, enqueue 1,2 → queue=[1,2]          │
  │ Step 2: process 1, enqueue 3,4 → queue=[2,3,4]        │
  │ Step 3: process 2 (no new)     → queue=[3,4]          │
  │ Step 4: process 3 (no new)     → queue=[4]            │
  │ Step 5: process 4 (no new)     → queue=[]             │
  │                                                        │
  │ Visit order: 0 → 1 → 2 → 3 → 4                      │
  └────────────────────────────────────────────────────────┘
*/

void demonstrateBFS() {
    cout << "═══ SECTION 2: BFS USING QUEUE ═══\n\n";

    // Simple graph as adjacency list
    int n = 5;
    vector<vector<int>> adj(n);
    adj[0] = {1, 2};
    adj[1] = {0, 3, 4};
    adj[2] = {0};
    adj[3] = {1};
    adj[4] = {1};

    // BFS
    vector<bool> visited(n, false);
    queue<int> q;

    q.push(0);
    visited[0] = true;

    cout << "BFS traversal from node 0: ";
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: LEVEL-ORDER PROCESSING
// ═══════════════════════════════════════════════════════════════
/*
  Processing level by level using size-based technique:

  Queue: [A, B, C, D, E]
  Level sizes: [1, 2, 2]  (example)

  for each level:
      sz = q.size()  // Number of nodes in THIS level
      for i in 0..sz-1:
          process q.front()
          q.pop()
          enqueue children
*/

void demonstrateLevelOrder() {
    cout << "═══ SECTION 3: LEVEL ORDER PATTERN ═══\n\n";

    // Simulating level-order with numbers
    queue<int> q;
    q.push(1);  // Level 0

    cout << "Simulated level-order (binary tree 1..7):\n";
    int level = 0;
    int nextVal = 2;

    while (!q.empty() && level < 3) {
        int sz = q.size();
        cout << "  Level " << level << ": ";
        for (int i = 0; i < sz; i++) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            // Add children (simulating complete binary tree)
            if (nextVal <= 7) { q.push(nextVal++); }
            if (nextVal <= 7) { q.push(nextVal++); }
        }
        cout << "\n";
        level++;
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: GENERATE BINARY NUMBERS 1 TO N
// ═══════════════════════════════════════════════════════════════
/*
  Generate binary: 1, 10, 11, 100, 101, 110, 111...
  Use queue: start with "1", generate by appending "0" and "1"

  Queue state:
  Start: ["1"]
  Pop "1", print, push "10", "11" → Queue: ["10", "11"]
  Pop "10", print, push "100", "101" → Queue: ["11", "100", "101"]
  Pop "11", print, push "110", "111" → Queue: ["100", "101", "110", "111"]
  ...
*/

void generateBinaryNumbers(int n) {
    cout << "═══ SECTION 4: BINARY NUMBERS 1 TO " << n << " ═══\n\n";

    queue<string> q;
    q.push("1");

    cout << "Binary representations:\n  ";
    for (int i = 1; i <= n; i++) {
        string front = q.front();
        q.pop();
        cout << i << "=" << front << "  ";
        q.push(front + "0");
        q.push(front + "1");
    }
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  STL QUEUE: COMPLETE API & USAGE                         ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    demonstrateBasics();
    demonstrateBFS();
    demonstrateLevelOrder();
    generateBinaryNumbers(10);

    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE PROBLEMS:\n";
    cout << "───────────────────\n";
    cout << "1. LC 200  — Number of Islands (BFS)\n";
    cout << "2. LC 994  — Rotting Oranges (Multi-source BFS)\n";
    cout << "3. LC 102  — Binary Tree Level Order Traversal\n";
    cout << "4. LC 107  — Level Order Traversal II (Bottom Up)\n";
    cout << "5. LC 1091 — Shortest Path in Binary Matrix\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

