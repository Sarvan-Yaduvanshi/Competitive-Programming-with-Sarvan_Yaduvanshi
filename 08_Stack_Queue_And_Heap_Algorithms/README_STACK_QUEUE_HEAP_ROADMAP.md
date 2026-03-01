<div align="center">

# 📚 Stack, Queue & Heap Algorithms — Zero to Grandmaster

### Complete Competitive Programming & Interview Mastery Guide

[![C++17](https://img.shields.io/badge/C%2B%2B-17%2F20-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Chapters](https://img.shields.io/badge/Chapters-12-blueviolet?style=for-the-badge)](.)
[![Files](https://img.shields.io/badge/Files-37%20CPP-orange?style=for-the-badge)](.)
[![Difficulty](https://img.shields.io/badge/Level-Zero%20→%20Grandmaster-red?style=for-the-badge)](.)
[![Author](https://img.shields.io/badge/Author-Sarvan%20Yaduvanshi-green?style=for-the-badge)](https://github.com/Sarvan-Yaduvanshi)

> *"Stacks, Queues, and Heaps are the backbone of algorithm design — from expression parsing to Dijkstra's shortest path. Master these three, and you unlock 40% of all competitive programming problems."*  
> — **Sarvan Yaduvanshi**

</div>

---

## 📖 About This Module

This module is the **most comprehensive Stack, Queue & Heap resource** for competitive programmers and interview preparation. Every concept is taught from **absolute zero** to **Grandmaster-level patterns**, with element-by-element dry runs, ASCII visualizations, and real competition problems.

**What makes this different?**
- 🧠 **State-by-state visualization** — Every operation shown with ASCII stack/queue/heap diagrams
- 🔄 **Step-by-step dry runs** — Watch algorithms execute element by element with mathematical traces
- 💻 **Separate .cpp per concept** — Clean, focused, runnable files with test cases
- 📊 **Complexity tables** — Every operation's time/space at a glance
- 🏆 **150+ practice problems** — Curated from LeetCode, Codeforces, GFG, CSES
- 🎯 **Design patterns** — Min Stack, LRU Cache, LFU Cache, Median Stream
- 🔗 **Integration patterns** — Stack + DP, Heap + Graph, Deque + Sliding Window, Queue + BFS

---

## 🗂️ Chapter Index

### 🟢 Level 1 — Foundation (Newbie → Pupil)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 01 | [**Stack & Queue Basics**](01_Stack_Queue_Basics/) | LIFO/FIFO concept, Array/LL implementation, Circular queue, Overflow/Underflow | ⭐ |
| 02 | [**STL Stack, Queue, Deque**](02_STL_Stack_Queue_Deque/) | `stack`, `queue`, `deque`, `priority_queue`, Custom comparators, Min/Max heap | ⭐ |

### 🟡 Level 2 — Intermediate (Pupil → Specialist)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 03 | [**Classical Stack Problems**](03_Classical_Stack_Problems/) | Valid parentheses, NGE/NSE/PGE/PSE, Stock span, Infix/Postfix/Prefix conversion & evaluation | ⭐⭐ |
| 04 | [**Monotonic Stack Patterns**](04_Monotonic_Stack_Patterns/) | NGE II circular, Largest rectangle histogram, Trapping rain water, Subarray min/max sums | ⭐⭐ |
| 05 | [**Queue & Deque Patterns**](05_Queue_And_Deque_Patterns/) | Sliding window max/min, First negative in window, 0-1 BFS, Multi-source BFS | ⭐⭐⭐ |

### 🔴 Level 3 — Advanced (Specialist → Expert)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 06 | [**Heap Basics & Implementation**](06_Heap_Basics_And_Implementation/) | Binary heap from scratch, Heapify, Build heap O(n), Heap sort, Complexity analysis | ⭐⭐⭐ |
| 07 | [**Priority Queue Patterns**](07_Priority_Queue_Patterns/) | Kth element, Top K frequent, Merge K sorted, Median stream, Dijkstra, Task scheduler | ⭐⭐⭐ |
| 08 | [**Advanced Heap Techniques**](08_Advanced_Heap_Techniques/) | Custom comparator struct, Lazy deletion, Indexed PQ, Two-heap technique, Sliding window median | ⭐⭐⭐ |

### 🟣 Level 4 — Master (Expert → Master)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 09 | [**Stack & Queue Design Problems**](09_Stack_Queue_Design_Problems/) | Min/Max stack, Queue using stacks, Stack using queues, LRU Cache, LFU Cache, Browser history | ⭐⭐⭐⭐ |
| 10 | [**Advanced Competitive Patterns**](10_Advanced_Competitive_Patterns/) | Monotonic deque DP, Convex hull trick, Kahn's topological sort, Sweep line + PQ | ⭐⭐⭐⭐ |

### 💎 Level 5 — Grandmaster (Master → Grandmaster)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 11 | [**Advanced Heap Data Structures**](11_Advanced_Heap_Data_Structures/) | d-ary heap, Binomial heap, Fibonacci heap, Pairing heap, Leftist/Skew heap | ⭐⭐⭐⭐⭐ |
| 12 | [**Edge Cases & Optimization**](12_Edge_Cases_And_Optimization/) | Empty structure, Single element, Large input TLE avoidance, Lazy deletion bugs | ⭐⭐⭐⭐⭐ |

---

## 📁 Complete File Structure

```
08_Stack_Queue_And_Heap_Algorithms/
│
├── README_STACK_QUEUE_HEAP_ROADMAP.md                ← You are here
│
├── 01_Stack_Queue_Basics/
│   ├── 01_Stack_LIFO_Array_Implementation.cpp        — LIFO concept, array-based stack
│   ├── 02_Stack_Linked_List_Implementation.cpp       — Stack using linked list
│   ├── 03_Queue_FIFO_Array_Implementation.cpp        — FIFO concept, array-based queue
│   ├── 04_Queue_Linked_List_Implementation.cpp       — Queue using linked list
│   └── 05_Circular_Queue_Implementation.cpp          — Circular queue, modulo arithmetic
│
├── 02_STL_Stack_Queue_Deque/
│   ├── 01_STL_Stack.cpp                              — std::stack full API
│   ├── 02_STL_Queue.cpp                              — std::queue full API
│   ├── 03_STL_Deque.cpp                              — std::deque full API
│   ├── 04_STL_Priority_Queue.cpp                     — Max/Min heap with priority_queue
│   └── 05_Custom_Comparators_In_Heap.cpp             — Custom struct comparators
│
├── 03_Classical_Stack_Problems/
│   ├── 01_Valid_Parentheses.cpp                      — Balanced brackets checking
│   ├── 02_Next_Greater_Element.cpp                   — NGE with monotonic stack
│   ├── 03_Next_Smaller_Element.cpp                   — NSE pattern
│   ├── 04_Previous_Greater_Element.cpp               — PGE pattern
│   ├── 05_Previous_Smaller_Element.cpp               — PSE pattern
│   ├── 06_Stock_Span_Problem.cpp                     — Span using stack
│   ├── 07_Infix_Postfix_Prefix_Conversion.cpp        — Expression conversion
│   ├── 08_Postfix_Prefix_Evaluation.cpp              — Expression evaluation & tree
│   └── 09_Balanced_Brackets_Extensions.cpp           — LC 32, 921, 1249, 1963, 856
│
├── 04_Monotonic_Stack_Patterns/
│   ├── 01_NGE_Circular_Array.cpp                     — Next greater element II (LC 503)
│   ├── 02_Largest_Rectangle_Histogram.cpp            — LC 84 (PSE+NSE & single stack)
│   ├── 03_Trapping_Rain_Water_Stack.cpp              — LC 42 stack + two pointer
│   ├── 04_Sum_Subarray_Minimums.cpp                  — LC 907 + 2104 contribution tech
│   ├── 05_Remove_K_Digits_DailyTemps_Asteroid.cpp    — LC 402, 739, 735 combined
│   └── 06_Visible_People_In_Queue.cpp                — LC 1944 monotonic stack
│
├── 05_Queue_And_Deque_Patterns/
│   ├── 01_Sliding_Window_Maximum.cpp                 — LC 239 monotonic deque + min + neg
│   ├── 02_Zero_One_BFS_And_Multi_Source_BFS.cpp      — 0-1 BFS, rotten oranges, 01 matrix
│   ├── 03_Two_Deque_Technique_And_Shortest_Subarray.cpp — LC 1438, 862 two deques
│   └── 04_BFS_Level_Order_Shortest_Path.cpp          — LC 102, 103, 1091 BFS patterns
│
├── 06_Heap_Basics_And_Implementation/
│   └── 01_Binary_Heap_From_Scratch.cpp               — Max/Min heap, build O(n), heap sort
│
├── 07_Priority_Queue_Patterns/
│   ├── 01_Kth_Largest_Smallest_Element.cpp           — LC 215, K closest, nearly sorted
│   ├── 02_Top_K_Frequent_And_Merge_K_Sorted.cpp     — LC 347, merge K sorted arrays
│   ├── 03_Median_Stream_TaskScheduler_Dijkstra.cpp   — LC 295, 621, Dijkstra
│   └── 04_Connect_Ropes_Reorganize_HireWorkers.cpp   — Huffman, LC 767, 857
│
├── 08_Advanced_Heap_Techniques/
│   ├── 01_Lazy_Deletion_IndexedPQ_TwoHeap.cpp        — Lazy delete, indexed PQ, LC 480
│   └── 02_Custom_Comparator_Heap_Pairs_DoubleHeap.cpp— Comparators, pairs, decrease-key
│
├── 09_Stack_Queue_Design_Problems/
│   ├── 01_Min_Stack.cpp                              — LC 155 (3 approaches)
│   ├── 02_Queue_Using_Stacks_And_Stack_Using_Queues.cpp — LC 232, 225
│   ├── 03_LRU_Cache_And_LFU_Cache.cpp               — LC 146, 460
│   └── 04_Circular_Deque_Browser_History_Max_Stack.cpp — LC 641, 1472, 716
│
├── 10_Advanced_Competitive_Patterns/
│   ├── 01_Deque_DP_CHT_Kahns_Topo.cpp               — Deque DP, Kahn's algo, LC 207
│   ├── 02_Sweep_Line_Heap_Event_Simulation.cpp       — LC 253, 218, 1353
│   └── 03_Multiset_Offline_Queries_Simulation.cpp    — CSES 1163, offline + heap
│
├── 11_Advanced_Heap_Data_Structures/
│   └── 01_DAry_Binomial_Fibonacci_Leftist_Heap.cpp   — D-ary, leftist, Fib concepts
│
└── 12_Edge_Cases_And_Optimization/
    └── 01_Edge_Cases_Optimization_Cheat_Sheet.cpp    — Edge cases, TLE tips, 150+ problems
```

---

## 📊 Data Structure Quick Reference

### Stack Operations
```
┌─────────────────────────────┬──────────┬──────────┐
│ Operation                   │  Array   │  LL      │
├─────────────────────────────┼──────────┼──────────┤
│ Push                        │  O(1)*   │  O(1)    │
│ Pop                         │  O(1)    │  O(1)    │
│ Top/Peek                    │  O(1)    │  O(1)    │
│ isEmpty                     │  O(1)    │  O(1)    │
│ Size                        │  O(1)    │  O(1)    │
│ Search                      │  O(n)    │  O(n)    │
└─────────────────────────────┴──────────┴──────────┘
  * Amortized for dynamic array
```

### Queue Operations
```
┌─────────────────────────────┬──────────┬──────────┬──────────┐
│ Operation                   │  Array   │  LL      │ Circular │
├─────────────────────────────┼──────────┼──────────┼──────────┤
│ Enqueue                     │  O(1)*   │  O(1)    │  O(1)    │
│ Dequeue                     │  O(n)**  │  O(1)    │  O(1)    │
│ Front                       │  O(1)    │  O(1)    │  O(1)    │
│ Rear                        │  O(1)    │  O(1)    │  O(1)    │
│ isEmpty                     │  O(1)    │  O(1)    │  O(1)    │
└─────────────────────────────┴──────────┴──────────┴──────────┘
  *  Amortized for dynamic array
  ** O(1) with circular indexing
```

### Heap / Priority Queue Operations
```
┌─────────────────────────────┬──────────┬──────────┐
│ Operation                   │ Binary   │ Fibonacci│
├─────────────────────────────┼──────────┼──────────┤
│ Insert                      │ O(log n) │ O(1)*    │
│ Extract Min/Max             │ O(log n) │ O(log n)*│
│ Peek Min/Max                │ O(1)     │ O(1)     │
│ Decrease Key                │ O(log n) │ O(1)*    │
│ Delete                      │ O(log n) │ O(log n)*│
│ Merge                       │ O(n)     │ O(1)     │
│ Build Heap                  │ O(n)     │ O(n)     │
│ Heap Sort                   │O(n log n)│    —     │
└─────────────────────────────┴──────────┴──────────┘
  * Amortized
```

---

## 🔄 Core Algorithm Dry Runs

### 📚 Stack Push/Pop Dry Run (LIFO)
```
Operations: push(10), push(20), push(30), pop(), push(40), pop(), pop()

push(10):  │ 10 │     top=0
           └────┘

push(20):  │ 20 │     top=1
           │ 10 │
           └────┘

push(30):  │ 30 │     top=2
           │ 20 │
           │ 10 │
           └────┘

pop()→30:  │ 20 │     top=1    (returned 30)
           │ 10 │
           └────┘

push(40):  │ 40 │     top=2
           │ 20 │
           │ 10 │
           └────┘

pop()→40:  │ 20 │     top=1    (returned 40)
           │ 10 │
           └────┘

pop()→20:  │ 10 │     top=0    (returned 20)
           └────┘
```

### 📬 Queue Enqueue/Dequeue Dry Run (FIFO)
```
Operations: enqueue(10), enqueue(20), enqueue(30), dequeue(), enqueue(40)

enqueue(10): front→ [10] ←rear

enqueue(20): front→ [10][20] ←rear

enqueue(30): front→ [10][20][30] ←rear

dequeue()→10: front→ [20][30] ←rear    (returned 10)

enqueue(40): front→ [20][30][40] ←rear
```

### 🔺 Heap Insert Dry Run (Max-Heap)
```
Insert sequence: 10, 20, 15, 30, 25

Insert 10:      [10]
                  10

Insert 20:      [20, 10]         (20 > 10, swap with parent)
                  20
                 /
               10

Insert 15:      [20, 10, 15]    (15 < 20, no swap needed)
                  20
                 /  \
               10    15

Insert 30:      [30, 20, 15, 10]  (30 > 10 → swap, 30 > 20 → swap)
                  30
                 /  \
               20    15
              /
            10

Insert 25:      [30, 25, 15, 10, 20]  (25 > 20 → swap, 25 < 30 → stop)
                  30
                 /  \
               25    15
              /  \
            10    20
```

### 📊 Next Greater Element Dry Run
```
Array: [4, 5, 2, 25, 7, 8]
Stack (monotonic decreasing from bottom to top)

i=0: arr[0]=4    stack=[]         → push 4      stack=[4]
i=1: arr[1]=5    5 > 4 → NGE[4]=5, pop → push 5   stack=[5]
i=2: arr[2]=2    2 < 5 → push 2   stack=[5,2]
i=3: arr[3]=25   25 > 2 → NGE[2]=25, pop
                  25 > 5 → NGE[5]=25, pop → push 25  stack=[25]
i=4: arr[4]=7    7 < 25 → push 7  stack=[25,7]
i=5: arr[5]=8    8 > 7 → NGE[7]=8, pop → push 8  stack=[25,8]

Remaining: NGE[25]=-1, NGE[8]=-1

Result: [5, 25, 25, -1, 8, -1]
```

### 🏗️ Largest Rectangle in Histogram Dry Run
```
Heights: [2, 1, 5, 6, 2, 3]
Stack stores indices, monotonic increasing

i=0: h=2, stack=[], push 0           stack=[0]
i=1: h=1, 1<2 → pop 0, area=2×1=2   stack=[]
     push 1                           stack=[1]
i=2: h=5, 5>1 → push 2              stack=[1,2]
i=3: h=6, 6>5 → push 3              stack=[1,2,3]
i=4: h=2, 2<6 → pop 3, area=6×1=6   stack=[1,2]
     2<5 → pop 2, area=5×2=10        stack=[1]
     2>1 → push 4                    stack=[1,4]
i=5: h=3, 3>2 → push 5              stack=[1,4,5]

Drain stack:
  pop 5: area=3×1=3
  pop 4: area=2×2=4
  pop 1: area=1×6=6

Max area = 10 ✅
```

---

## 🧭 When to Use Which Data Structure?

```
Need LIFO access (last in, first out)?
├── YES → Use Stack
│   ├── Need min/max in O(1)? → Min Stack / Max Stack
│   ├── Expression parsing? → Stack
│   ├── Backtracking/DFS? → Stack (explicit or recursion)
│   └── Monotonic pattern? → Monotonic Stack
│
Need FIFO access (first in, first out)?
├── YES → Use Queue
│   ├── BFS traversal? → Queue
│   ├── Sliding window? → Deque
│   ├── 0-1 BFS? → Deque
│   └── Level-order? → Queue
│
Need quick access to min/max element?
├── YES → Use Heap / Priority Queue
│   ├── Kth largest/smallest? → Min/Max Heap of size K
│   ├── Merge K sorted? → Min Heap
│   ├── Running median? → Two Heaps
│   ├── Shortest path? → Min Heap (Dijkstra)
│   ├── Need decrease-key? → Indexed Priority Queue
│   └── Frequent insert + extract? → Binary Heap
│
Need both ends access?
├── YES → Use Deque
│   ├── Sliding window max/min? → Monotonic Deque
│   ├── Palindrome check? → Deque
│   └── DP optimization? → Monotonic Deque
```

---

## 🏆 The Stack/Queue/Heap Pattern Matrix

```
┌────────────────────────┬────────────────────────────────────────────────┐
│ Pattern                │ Problems That Use It                           │
├────────────────────────┼────────────────────────────────────────────────┤
│ Monotonic Stack        │ NGE/NSE/PGE/PSE, Stock Span, Histogram,       │
│                        │ Trapping Rain Water, Daily Temperatures        │
├────────────────────────┼────────────────────────────────────────────────┤
│ Monotonic Deque        │ Sliding Window Max/Min, DP Optimization,       │
│                        │ Max-Min ≤ K Window                            │
├────────────────────────┼────────────────────────────────────────────────┤
│ Two Heaps              │ Running Median, Sliding Window Median,         │
│                        │ Balance Partitioning                           │
├────────────────────────┼────────────────────────────────────────────────┤
│ Top-K / Kth Element    │ Kth Largest, Top K Frequent, K Closest        │
│                        │ Points, Sort Nearly Sorted                    │
├────────────────────────┼────────────────────────────────────────────────┤
│ Merge K Pattern        │ Merge K Sorted Lists/Arrays, Smallest Range   │
│                        │ Covering K Lists                              │
├────────────────────────┼────────────────────────────────────────────────┤
│ BFS + Queue            │ Level Order, Shortest Path, Multi-source BFS, │
│                        │ Rotten Oranges, 0-1 BFS                       │
├────────────────────────┼────────────────────────────────────────────────┤
│ Stack + Design         │ Min Stack, Max Stack, Queue using Stacks,     │
│                        │ LRU Cache, Browser History                    │
├────────────────────────┼────────────────────────────────────────────────┤
│ Expression Parsing     │ Infix↔Postfix↔Prefix, Calculator, Expression │
│                        │ Tree, Evaluate RPN                            │
├────────────────────────┼────────────────────────────────────────────────┤
│ Greedy + Heap          │ Task Scheduler, Reorganize String, Min Cost   │
│                        │ Ropes, Huffman Coding                         │
├────────────────────────┼────────────────────────────────────────────────┤
│ Graph + Heap           │ Dijkstra, Prim's MST, A* Search,             │
│                        │ Network Delay                                 │
└────────────────────────┴────────────────────────────────────────────────┘
```

---

## 📚 Curated Problem Sets

### 🟢 Beginner (LeetCode Easy)
| # | Problem | Platform | Key Pattern |
|:-:|---------|----------|-------------|
| 1 | [Valid Parentheses](https://leetcode.com/problems/valid-parentheses/) | LC 20 | Stack matching |
| 2 | [Min Stack](https://leetcode.com/problems/min-stack/) | LC 155 | Two-stack design |
| 3 | [Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/) | LC 232 | Amortized O(1) |
| 4 | [Implement Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/) | LC 225 | Push-costly / Pop-costly |
| 5 | [Next Greater Element I](https://leetcode.com/problems/next-greater-element-i/) | LC 496 | Monotonic stack + map |
| 6 | [Baseball Game](https://leetcode.com/problems/baseball-game/) | LC 682 | Stack simulation |
| 7 | [Kth Largest in Stream](https://leetcode.com/problems/kth-largest-element-in-a-stream/) | LC 703 | Min-heap of size K |
| 8 | [Last Stone Weight](https://leetcode.com/problems/last-stone-weight/) | LC 1046 | Max-heap simulation |

### 🟡 Intermediate (LeetCode Medium)
| # | Problem | Platform | Key Pattern |
|:-:|---------|----------|-------------|
| 1 | [Daily Temperatures](https://leetcode.com/problems/daily-temperatures/) | LC 739 | Monotonic stack |
| 2 | [Next Greater Element II](https://leetcode.com/problems/next-greater-element-ii/) | LC 503 | Circular monotonic stack |
| 3 | [Evaluate RPN](https://leetcode.com/problems/evaluate-reverse-polish-notation/) | LC 150 | Stack evaluation |
| 4 | [Asteroid Collision](https://leetcode.com/problems/asteroid-collision/) | LC 735 | Stack simulation |
| 5 | [Remove K Digits](https://leetcode.com/problems/remove-k-digits/) | LC 402 | Greedy + monotonic stack |
| 6 | [Online Stock Span](https://leetcode.com/problems/online-stock-span/) | LC 901 | Stack span |
| 7 | [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/) | LC 239 | Monotonic deque |
| 8 | [Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) | LC 347 | Min-heap of size K |
| 9 | [Kth Largest Element](https://leetcode.com/problems/kth-largest-element-in-an-array/) | LC 215 | Quick select / Heap |
| 10 | [Task Scheduler](https://leetcode.com/problems/task-scheduler/) | LC 621 | Greedy + Max-heap |
| 11 | [Reorganize String](https://leetcode.com/problems/reorganize-string/) | LC 767 | Max-heap greedy |
| 12 | [Sum of Subarray Minimums](https://leetcode.com/problems/sum-of-subarray-minimums/) | LC 907 | Contribution + monotonic |
| 13 | [Car Fleet](https://leetcode.com/problems/car-fleet/) | LC 853 | Stack |
| 14 | [Decode String](https://leetcode.com/problems/decode-string/) | LC 394 | Stack recursion |
| 15 | [Design Circular Deque](https://leetcode.com/problems/design-circular-deque/) | LC 641 | Circular array |

### 🔴 Advanced (LeetCode Hard)
| # | Problem | Platform | Key Pattern |
|:-:|---------|----------|-------------|
| 1 | [Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/) | LC 84 | Monotonic stack |
| 2 | [Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/) | LC 42 | Stack / Two-pointer |
| 3 | [Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/) | LC 295 | Two heaps |
| 4 | [Merge K Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/) | LC 23 | Min-heap |
| 5 | [LRU Cache](https://leetcode.com/problems/lru-cache/) | LC 146 | DLL + HashMap |
| 6 | [LFU Cache](https://leetcode.com/problems/lfu-cache/) | LC 460 | DLL + 2 HashMaps |
| 7 | [Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/) | LC 85 | Histogram per row |
| 8 | [Sliding Window Median](https://leetcode.com/problems/sliding-window-median/) | LC 480 | Two heaps + lazy delete |
| 9 | [Basic Calculator](https://leetcode.com/problems/basic-calculator/) | LC 224 | Stack + recursion |
| 10 | [Max Stack](https://leetcode.com/problems/max-stack/) | LC 716 | DLL + TreeMap |

### 🏆 Grandmaster (CSES / Codeforces)
| # | Problem | Platform | Key Pattern |
|:-:|---------|----------|-------------|
| 1 | [Course Schedule](https://cses.fi/problemset/task/1679) | CSES | Kahn's topological sort |
| 2 | [Shortest Routes I](https://cses.fi/problemset/task/1671) | CSES | Dijkstra + PQ |
| 3 | [Traffic Lights](https://cses.fi/problemset/task/1163) | CSES | Multiset / heap |
| 4 | [Nearest Smaller Values](https://cses.fi/problemset/task/1645) | CSES | Monotonic stack |
| 5 | [Sliding Window Cost](https://cses.fi/problemset/task/1077) | CSES | Two heaps |

---

## 🎓 How to Study This Module

```
Week 1: Chapters 01-02 (Basics + STL — Build the Foundation)
         → Must be able to implement stack/queue from scratch in 5 minutes
Week 2: Chapters 03-04 (Classical Stack + Monotonic Stack — Core Patterns)
         → Solve 20+ problems using monotonic stack alone
Week 3: Chapters 05-06 (Queue/Deque Patterns + Heap Basics)
         → Focus on sliding window deque and heap implementation
Week 4: Chapters 07-08 (PQ Patterns + Advanced Heap)
         → Two-heap technique and Dijkstra are asked in 80% of interviews
Week 5: Chapters 09-10 (Design Problems + Competitive Patterns)
         → LRU Cache is asked in 90% of FAANG interviews. Master it.
Week 6: Chapters 11-12 (Advanced DS + Edge Cases)
         → Polish skills, practice edge cases, time yourself
```

**For each chapter:**
1. 📖 Read the theory sections with ASCII diagrams first
2. 💻 Run each .cpp file and study the dry-run output
3. ✏️ Code each algorithm from scratch WITHOUT looking at the file
4. 🧪 Test with edge cases: empty structure, single element, duplicates
5. 🏆 Solve the practice problems at the end of each file
6. ⏱️ Time yourself — aim for < 15 min per medium problem

---

<div align="center">

### Made with ❤️ for the Competitive Programming & Interview Community

*"Stack gives you history, Queue gives you order, Heap gives you priority. Together, they solve half of competitive programming."*  
— **Sarvan Yaduvanshi**

**⭐ Star this repo if it helped you! ⭐**

</div>

