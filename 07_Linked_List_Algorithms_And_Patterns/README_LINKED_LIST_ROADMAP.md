<div align="center">

# 🔗 Linked List Algorithms & Patterns — Zero to Grandmaster

### Complete Competitive Programming & Interview Mastery Guide

[![C++17](https://img.shields.io/badge/C%2B%2B-17%2F20-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Chapters](https://img.shields.io/badge/Chapters-12-blueviolet?style=for-the-badge)](.)
[![Files](https://img.shields.io/badge/Files-27%20CPP-orange?style=for-the-badge)](.)
[![Difficulty](https://img.shields.io/badge/Level-Zero%20→%20Grandmaster-red?style=for-the-badge)](.)
[![Author](https://img.shields.io/badge/Author-Sarvan%20Yaduvanshi-green?style=for-the-badge)](https://github.com/Sarvan-Yaduvanshi)

> *"Linked Lists aren't just data structures — they're the foundation of memory management, cache design, and pointer mastery. If you can't think in nodes and pointers, you can't crack FAANG."*  
> — **Sarvan Yaduvanshi**

</div>

---

## 📖 About This Module

This module is the **most comprehensive Linked List resource** for competitive programmers and interview preparation. Every concept is taught from **absolute zero** to **Grandmaster-level design patterns**, with node-by-node dry runs, ASCII visualizations, and real interview problems.

**What makes this different?**
- 🧠 **Node-level visualization** — Every operation shown with ASCII pointer diagrams
- 🔄 **Step-by-step dry runs** — Watch algorithms execute node by node
- 💻 **Separate .cpp per concept** — Clean, focused, runnable files with test cases
- 📊 **Complexity tables** — Every operation's time/space at a glance
- 🏆 **100+ practice problems** — Curated from LeetCode, Codeforces, GFG, CSES
- 🎯 **Design patterns** — LRU Cache, LFU Cache, Browser History, Skip List
- 🔗 **Integration patterns** — Linked List + Stack, Queue, Heap, HashMap, Graph

---

## 🗂️ Chapter Index

### 🟢 Level 1 — Foundation (Newbie → Pupil)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 01 | [**Linked List Basics**](01_Linked_List_Basics/) | Node structure, SLL, DLL, Circular LL, Memory layout, Dynamic allocation, Head pointer, Null handling | ⭐ |
| 02 | [**Basic Operations**](02_Basic_Operations/) | Insert (head/tail/position), Delete (head/tail/value/position), Search, Length, Print, Reverse print, Traversal | ⭐ |

### 🟡 Level 2 — Intermediate (Pupil → Specialist)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 03 | [**Reversal Patterns**](03_Reversal_Patterns/) | Iterative/Recursive reverse, Reverse sublist [L,R], Reverse K-group, Alternate K, Circular reverse, DLL reverse | ⭐⭐ |
| 04 | [**Fast & Slow Pointer Techniques**](04_Fast_Slow_Pointer_Techniques/) | Find middle, Floyd's cycle detection, Cycle start/length, Happy number, Nth from end, Palindrome check, Intersection | ⭐⭐ |
| 05 | [**Merge & Sort Patterns**](05_Merge_And_Sort_Patterns/) | Merge 2 sorted, Merge K sorted, Merge sort on LL, Insertion sort, Partition, Remove duplicates (sorted/unsorted) | ⭐⭐⭐ |

### 🔴 Level 3 — Advanced (Specialist → Expert)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 06 | [**Structural Modification Patterns**](06_Structural_Modification_Patterns/) | Reorder list, Rotate list, Swap pairs, Swap Kth nodes, Odd-Even list, Flatten multilevel, Add/Subtract numbers | ⭐⭐⭐ |
| 07 | [**Doubly & Circular Linked List**](07_Doubly_And_Circular_Linked_List/) | DLL operations, Circular SLL/DLL, Josephus problem, Flatten multilevel DLL | ⭐⭐⭐ |
| 08 | [**Advanced Pointer Manipulation**](08_Advanced_Pointer_Manipulation/) | Clone with random pointer, Deep vs shallow copy, Multi-level LL, XOR linked list, Memory optimization | ⭐⭐⭐ |

### 🟣 Level 4 — Master (Expert → Master)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 09 | [**Linked List Design Problems**](09_Linked_List_Design_Problems/) | LRU Cache, LFU Cache, Browser History, Text Editor, HashMap using LL, Skip List, Deque using DLL | ⭐⭐⭐⭐ |
| 10 | [**Linked List With Other DS**](10_Linked_List_With_Other_Data_Structures/) | LL + Stack, LL + Queue, LL + Heap, LL + HashMap, LL cycle in graph, Polynomial representation | ⭐⭐⭐⭐ |

### 💎 Level 5 — Grandmaster (Master → Grandmaster)

| # | Chapter | Key Topics | Difficulty |
|:-:|---------|------------|:----------:|
| 11 | [**Advanced Linked List Tricks**](11_Advanced_Linked_List_Tricks/) | Binary search on LL, Persistent LL, Adjacency list, Euler tour, Memory-constrained problems, Pointer compression | ⭐⭐⭐⭐⭐ |
| 12 | [**Edge Cases & Debugging**](12_Edge_Cases_And_Debugging/) | Single/Empty/Two node lists, Even/Odd length, Null pointer crashes, Infinite loops, Memory leaks, Dangling pointers | ⭐⭐⭐⭐⭐ |

---

## 📁 Complete File Structure

```
07_Linked_List_Algorithms_And_Patterns/
│
├── README_LINKED_LIST_ROADMAP.md              ← You are here
│
├── 01_Linked_List_Basics/
│   ├── 01_Singly_Linked_List_Node.cpp         — Node struct, pointers, dynamic memory
│   ├── 02_Doubly_Linked_List_Node.cpp         — DLL node, prev/next pointers
│   ├── 03_Circular_Linked_List.cpp            — Circular SLL & DLL, traversal
│   ├── 04_Traversal_And_Counting.cpp          — Iterative/recursive traversal, count
│   └── 05_Memory_Layout_And_LL_Class.cpp      — Array vs LL, cache, OOP LL class
│
├── 02_Basic_Operations/
│   ├── 01_Insertion_Operations.cpp            — Insert head/tail/position with dry runs
│   ├── 02_Deletion_Operations.cpp             — Delete head/tail/value/position
│   └── 03_Search_Length_Print.cpp             — Search, length, print, reverse print
│
├── 03_Reversal_Patterns/
│   ├── 01_Iterative_Reversal.cpp              — Three-pointer technique, step-by-step
│   ├── 02_Recursive_Reversal.cpp              — Head & tail recursion
│   ├── 03_Reverse_K_Group.cpp                 — LC 25, alternate K, sublist [L,R]
│   ├── 04_Reverse_DLL_And_Circular.cpp        — Reverse DLL & circular list
│   └── 05_Reverse_Even_Groups_And_More.cpp    — LC 2074, 92, 1721
│
├── 04_Fast_Slow_Pointer_Techniques/
│   ├── 01_Floyds_Cycle_Detection.cpp          — Detect cycle, start, length, middle
│   └── 02_Palindrome_Nth_Intersection_Happy.cpp — LC 19, 234, 160, 202
│
├── 05_Merge_And_Sort_Patterns/
│   ├── 01_Merge_Two_Sorted_Lists.cpp          — Iterative & recursive merge
│   ├── 02_Merge_K_Sorted_Lists.cpp            — Min-heap & divide-conquer
│   ├── 03_Sort_And_Remove_Duplicates.cpp      — Merge sort, insertion sort, 0-1-2
│   └── 04_Partition_And_Interleave.cpp        — Partition, 3-way, interleave, split
│
├── 06_Structural_Modification_Patterns/
│   ├── 01_Reorder_Rotate_OddEven.cpp          — LC 143, 61, 328, 24, 86
│   └── 02_Add_Numbers_Swap_Delete.cpp         — LC 2, 445, swap Kth, delete greater
│
├── 07_Doubly_And_Circular_Linked_List/
│   ├── 01_Doubly_Linked_List_Complete.cpp      — Full DLL ops, flatten multilevel
│   └── 02_Circular_List_And_Josephus.cpp       — Circular ops, Josephus (3 solutions)
│
├── 08_Advanced_Pointer_Manipulation/
│   ├── 01_Clone_Random_Pointer.cpp            — HashMap & interleaving, XOR LL concept
│   └── 02_Flatten_And_MultiLevel.cpp          — Flatten sorted sublists, multi-level
│
├── 09_Linked_List_Design_Problems/
│   ├── 01_LRU_Cache.cpp                       — LC 146, DLL + HashMap, full dry run
│   ├── 02_LFU_Cache.cpp                       — LC 460, frequency tracking
│   ├── 03_Browser_HashMap_Deque_SkipList.cpp  — LC 1472, 706, deque, skip list concept
│   └── 04_Design_Linked_List_And_TextEditor.cpp — LC 707, 2296, SLL/DLL design
│
├── 10_Linked_List_With_Other_Data_Structures/
│   ├── 01_Stack_Queue_Graph_Polynomial.cpp    — LL-based stack/queue, adjacency list
│   └── 02_Tree_To_LL_And_Heap.cpp            — LC 114, BST to DLL, sort with heap
│
├── 11_Advanced_Linked_List_Tricks/
│   ├── 01_BinarySearch_Persistent_ArrayLL.cpp — Binary search on LL, persistent LL, CP tricks
│   └── 02_SkipList_And_SelfOrganizing.cpp     — LC 1206 skip list, self-organizing list
│
└── 12_Edge_Cases_And_Debugging/
    └── 01_Edge_Cases_And_Debugging.cpp        — All edge cases, memory leaks, debugging utils
```

---

## 🔗 Node Structure Visualization

### Singly Linked List Node
```
┌──────────────────────────┐
│       SINGLY NODE        │
│                          │
│  ┌───────┬──────────┐    │
│  │ data  │  next ───┼──▶ (points to next node or NULL)
│  └───────┴──────────┘    │
│                          │
│  struct Node {           │
│      int data;           │
│      Node* next;         │
│  };                      │
└──────────────────────────┘
```

### Doubly Linked List Node
```
┌─────────────────────────────────────┐
│          DOUBLY NODE                │
│                                     │
│  ┌──────────┬───────┬──────────┐    │
│  │  prev ◀──┼ data  │  next ───┼──▶ │
│  └──────────┴───────┴──────────┘    │
│                                     │
│  struct DNode {                     │
│      int data;                      │
│      DNode* prev;                   │
│      DNode* next;                   │
│  };                                 │
└─────────────────────────────────────┘
```

### Circular Linked List
```
┌──────────────────────────────────────────────────────────┐
│                 CIRCULAR LINKED LIST                     │
│                                                          │
│      ┌───┬───┐    ┌───┬───┐    ┌───┬───┐               │
│  ┌──▶│ 1 │ ──┼──▶ │ 2 │ ──┼──▶│ 3 │ ──┼──┐            │
│  │   └───┴───┘    └───┴───┘    └───┴───┘  │            │
│  │                                          │            │
│  └──────────────────────────────────────────┘            │
│                                                          │
│  Last node's next points back to first node              │
└──────────────────────────────────────────────────────────┘
```

---

## 📊 Memory Layout: Array vs Linked List

```
ARRAY (Contiguous Memory):
┌─────┬─────┬─────┬─────┬─────┐
│  10 │  20 │  30 │  40 │  50 │    Elements stored side by side
├─────┼─────┼─────┼─────┼─────┤
│0x100│0x104│0x108│0x10C│0x110│    Addresses differ by sizeof(int)
└─────┴─────┴─────┴─────┴─────┘

LINKED LIST (Scattered Memory):
┌─────┬──────┐   ┌─────┬──────┐   ┌─────┬──────┐
│ 10  │0x2F0 │──▶│ 20  │0x8A4 │──▶│ 30  │ NULL │
├─────┼──────┤   ├─────┼──────┤   ├─────┼──────┤
│0x100│      │   │0x2F0│      │   │0x8A4│      │
└─────┴──────┘   └─────┴──────┘   └─────┴──────┘
  Node at            Node at           Node at
  random addr        random addr       random addr
```

---

## 🔄 Core Algorithm Dry Runs

### 🔁 Dry Run: Reverse Linked List (Iterative)

```
Input: 1 → 2 → 3 → 4 → NULL

Algorithm: Three pointers — prev, curr, next

Step 0: prev = NULL, curr = head(1)
        NULL    1 → 2 → 3 → 4 → NULL
         ↑      ↑
        prev   curr

Step 1: next = curr->next(2), curr->next = prev(NULL), prev = curr(1), curr = next(2)
        NULL ← 1    2 → 3 → 4 → NULL
               ↑    ↑
              prev  curr

Step 2: next = curr->next(3), curr->next = prev(1), prev = curr(2), curr = next(3)
        NULL ← 1 ← 2    3 → 4 → NULL
                    ↑    ↑
                   prev  curr

Step 3: next = curr->next(4), curr->next = prev(2), prev = curr(3), curr = next(4)
        NULL ← 1 ← 2 ← 3    4 → NULL
                         ↑    ↑
                        prev  curr

Step 4: next = curr->next(NULL), curr->next = prev(3), prev = curr(4), curr = next(NULL)
        NULL ← 1 ← 2 ← 3 ← 4    NULL
                              ↑    ↑
                             prev  curr

curr == NULL → STOP. Return prev (new head = 4)

Result: 4 → 3 → 2 → 1 → NULL ✅
```

### 🐢🐇 Dry Run: Floyd's Cycle Detection

```
Input: 1 → 2 → 3 → 4 → 5 → 3 (cycle back to node 3)

        ┌────────────────────┐
        ▼                    │
   1 → 2 → 3 → 4 → 5 ──────┘

slow moves 1 step, fast moves 2 steps

Step 0: slow = 1, fast = 1
Step 1: slow = 2, fast = 3
Step 2: slow = 3, fast = 5
Step 3: slow = 4, fast = 4  ← MEET! Cycle detected! ✅

Finding Cycle Start:
  Reset slow to head, keep fast at meeting point
  Both move 1 step at a time

Step 0: slow = 1, fast = 4
Step 1: slow = 2, fast = 5
Step 2: slow = 3, fast = 3  ← MEET! Cycle starts at node 3 ✅

Cycle Length:
  Keep one pointer fixed, move other until they meet again
  Count = 3 (nodes 3 → 4 → 5 → back to 3)
```

### 🔀 Dry Run: Merge Two Sorted Lists

```
List A: 1 → 3 → 5 → NULL
List B: 2 → 4 → 6 → NULL

Step 1: Compare 1 vs 2 → pick 1
        Result: 1 →
        A: 3 → 5 → NULL, B: 2 → 4 → 6 → NULL

Step 2: Compare 3 vs 2 → pick 2
        Result: 1 → 2 →
        A: 3 → 5 → NULL, B: 4 → 6 → NULL

Step 3: Compare 3 vs 4 → pick 3
        Result: 1 → 2 → 3 →
        A: 5 → NULL, B: 4 → 6 → NULL

Step 4: Compare 5 vs 4 → pick 4
        Result: 1 → 2 → 3 → 4 →
        A: 5 → NULL, B: 6 → NULL

Step 5: Compare 5 vs 6 → pick 5
        Result: 1 → 2 → 3 → 4 → 5 →
        A: NULL, B: 6 → NULL

Step 6: A is NULL → append remaining B
        Result: 1 → 2 → 3 → 4 → 5 → 6 → NULL ✅
```

### 🔄 Dry Run: Reverse K-Group (K=3)

```
Input: 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → NULL, K = 3

Group 1: [1, 2, 3] → Reverse → [3, 2, 1]
         3 → 2 → 1 → 4 → 5 → 6 → 7 → 8 → NULL

Group 2: [4, 5, 6] → Reverse → [6, 5, 4]
         3 → 2 → 1 → 6 → 5 → 4 → 7 → 8 → NULL

Group 3: [7, 8] → Only 2 nodes (< K) → Keep as is
         3 → 2 → 1 → 6 → 5 → 4 → 7 → 8 → NULL ✅

Pointer Management:
  ┌───┐   ┌───┐   ┌───┐   ┌───┐   ┌───┐   ┌───┐   ┌───┐   ┌───┐
  │ 3 │──▶│ 2 │──▶│ 1 │──▶│ 6 │──▶│ 5 │──▶│ 4 │──▶│ 7 │──▶│ 8 │──▶NULL
  └───┘   └───┘   └───┘   └───┘   └───┘   └───┘   └───┘   └───┘
  \_________↑_________/   \_________↑_________/   \______↑______/
     Reversed Group 1       Reversed Group 2      Kept (< K)
```

### 🔄 Dry Run: Reorder List (L0 → Ln → L1 → Ln-1...)

```
Input: 1 → 2 → 3 → 4 → 5 → NULL

Step 1: Find middle → split into two halves
        First:  1 → 2 → 3 → NULL
        Second: 4 → 5 → NULL

Step 2: Reverse second half
        Second: 5 → 4 → NULL

Step 3: Merge alternately
        Pick from first:  1 →
        Pick from second: 1 → 5 →
        Pick from first:  1 → 5 → 2 →
        Pick from second: 1 → 5 → 2 → 4 →
        Pick from first:  1 → 5 → 2 → 4 → 3 → NULL ✅

Result: 1 → 5 → 2 → 4 → 3 → NULL
```

### 🗄️ Dry Run: LRU Cache (Capacity = 3)

```
Operations: put(1,A), put(2,B), put(3,C), get(1), put(4,D)

State: DLL (Most Recent ← → Least Recent) + HashMap

put(1,A): DLL: [1:A]                  Map: {1→node1}
put(2,B): DLL: [2:B] ↔ [1:A]         Map: {1→node1, 2→node2}
put(3,C): DLL: [3:C] ↔ [2:B] ↔ [1:A] Map: {1→node1, 2→node2, 3→node3}

get(1):   Move 1 to front
          DLL: [1:A] ↔ [3:C] ↔ [2:B] Map: {1→node1, 2→node2, 3→node3}
          Returns: A ✅

put(4,D): Cache full! Evict LRU (2:B from tail)
          DLL: [4:D] ↔ [1:A] ↔ [3:C] Map: {1→node1, 3→node3, 4→node4}

  HashMap gives O(1) lookup
  DLL gives O(1) insert/delete for LRU ordering

  ┌─────────────────────────────────────────────────┐
  │  HashMap: key → DLL Node pointer                │
  │                                                  │
  │  DLL: HEAD ↔ [4:D] ↔ [1:A] ↔ [3:C] ↔ TAIL     │
  │        ↑                                ↑        │
  │   Most Recent                    Least Recent    │
  │   (just used)                    (evict this)    │
  └─────────────────────────────────────────────────┘
```

---

## 📊 Master Complexity Reference

### Linked List Operations Cheat Sheet

```
┌────────────────────────────┬──────────┬──────────┬──────────┬──────────┐
│ Operation                  │  SLL     │  DLL     │ Circular │  Array   │
├────────────────────────────┼──────────┼──────────┼──────────┼──────────┤
│ Access by index            │  O(n)    │  O(n)    │  O(n)    │  O(1)    │
│ Insert at head             │  O(1)    │  O(1)    │  O(1)    │  O(n)    │
│ Insert at tail             │  O(n)*   │  O(1)    │  O(1)    │  O(1)**  │
│ Insert at position         │  O(n)    │  O(n)    │  O(n)    │  O(n)    │
│ Delete head                │  O(1)    │  O(1)    │  O(1)    │  O(n)    │
│ Delete tail                │  O(n)    │  O(1)    │  O(n)*   │  O(1)    │
│ Delete by value            │  O(n)    │  O(n)    │  O(n)    │  O(n)    │
│ Search                     │  O(n)    │  O(n)    │  O(n)    │  O(n)*** │
│ Reverse                    │  O(n)    │  O(n)    │  O(n)    │  O(n)    │
│ Merge (sorted)             │  O(n+m)  │  O(n+m)  │  O(n+m)  │  O(n+m)  │
│ Sort (merge sort)          │O(nlogn)  │O(nlogn)  │O(nlogn)  │O(nlogn)  │
│ Space per element          │  O(1)    │  O(1)    │  O(1)    │  O(1)    │
│ Extra space (pointers)     │  +8B     │  +16B    │  +8B     │  +0B     │
└────────────────────────────┴──────────┴──────────┴──────────┴──────────┘
  *  O(1) if tail pointer maintained
  ** Amortized O(1) for dynamic array
  *** O(log n) if sorted (binary search)
```

### Design Problems Complexity

```
┌──────────────────────┬──────────┬──────────┬─────────────────────────┐
│ Design               │  Get     │  Put     │  Data Structures Used   │
├──────────────────────┼──────────┼──────────┼─────────────────────────┤
│ LRU Cache            │  O(1)    │  O(1)    │  DLL + HashMap          │
│ LFU Cache            │  O(1)    │  O(1)    │  DLL + 2 HashMaps       │
│ Browser History      │  O(1)    │  O(1)    │  DLL                    │
│ Text Editor          │  O(k)    │  O(k)    │  DLL + Stack            │
│ Skip List            │ O(logn)  │ O(logn)  │  Multi-level LL         │
│ HashMap (chaining)   │  O(1)*   │  O(1)*   │  Array of SLL           │
│ Deque (DLL)          │  O(1)    │  O(1)    │  DLL                    │
└──────────────────────┴──────────┴──────────┴─────────────────────────┘
  * Average case
```

---

## 🧭 When to Use Which Linked List?

```
Need a linked list?
├── Need bidirectional traversal?
│   ├── YES → Need circular access?
│   │         ├── YES → Circular Doubly Linked List
│   │         └── NO  → Doubly Linked List (DLL)
│   └── NO  → Need circular access?
│             ├── YES → Circular Singly Linked List
│             └── NO  → Singly Linked List (SLL)
├── Need O(1) insert/delete at both ends?
│   └── Doubly Linked List
├── Need LRU/LFU Cache?
│   └── DLL + HashMap
├── Need O(log n) search in linked structure?
│   └── Skip List
├── Need memory efficiency?
│   └── XOR Linked List (saves 50% pointer space)
└── Need contiguous cache-friendly access?
    └── DON'T use linked list — use vector/array!
```

---

## 🏆 Top 15 Linked List Interview & CP Tips

### 🔥 Must-Know Patterns

1. **Dummy Node Trick** — Use `Node dummy(0); dummy.next = head;` to simplify edge cases (empty list, single node, delete head)
2. **Two Pointer (Fast/Slow)** — Find middle, detect cycle, find nth from end — ALL in one pattern
3. **Three Pointer Reversal** — `prev, curr, next` — The most fundamental linked list pattern
4. **Recursive vs Iterative** — Recursive is cleaner but uses O(n) stack space; iterative is O(1) space
5. **In-place Modification** — Most LL problems expect O(1) extra space — don't create new nodes!
6. **Split + Reverse + Merge** — Reorder List, Palindrome Check, Sort List — all use this combo
7. **HashMap + DLL = O(1) Cache** — The key insight for LRU/LFU cache design
8. **Always Handle Edge Cases** — Empty list, single node, two nodes — test these FIRST
9. **Draw It Out** — ALWAYS draw the pointer diagram before coding LL problems
10. **Sentinel/Dummy Nodes** — Use head and tail sentinels for DLL to avoid null checks
11. **Count First, Then Act** — For "reverse K group", first count total nodes to handle remainder
12. **Copy with Random Pointer** — Use interleaving technique (O(1) space) or HashMap (O(n) space)
13. **Merge Sort is King** — Only O(n log n) sort that works well on linked lists (no random access needed)
14. **Circular List = Josephus** — The classic circular elimination problem
15. **XOR Trick** — `prev XOR next` in one pointer — saves memory but rarely used in practice

### ⚡ Common Mistakes to Avoid

```
❌ Forgetting to update head after reversal
❌ Not handling NULL pointer before dereferencing
❌ Losing reference to next node during reversal
❌ Off-by-one in "insert at position"
❌ Memory leak — not deleting removed nodes
❌ Infinite loop in circular list (no exit condition)
❌ Using std::sort on linked list (use merge sort!)
❌ Forgetting to set last node's next to NULL after operations
```

---

## 📚 Curated Problem Sets

### 🟢 Beginner (LeetCode Easy)
| # | Problem | Platform | Key Pattern |
|:-:|---------|----------|-------------|
| 1 | [Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/) | LC 206 | Three-pointer reversal |
| 2 | [Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/) | LC 21 | Two-pointer merge |
| 3 | [Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/) | LC 141 | Floyd's slow/fast |
| 4 | [Remove Duplicates from Sorted List](https://leetcode.com/problems/remove-duplicates-from-sorted-list/) | LC 83 | Pointer skip |
| 5 | [Palindrome Linked List](https://leetcode.com/problems/palindrome-linked-list/) | LC 234 | Split + Reverse + Compare |
| 6 | [Middle of Linked List](https://leetcode.com/problems/middle-of-the-linked-list/) | LC 876 | Fast/Slow pointer |
| 7 | [Intersection of Two Linked Lists](https://leetcode.com/problems/intersection-of-two-linked-lists/) | LC 160 | Two-pointer length equalization |
| 8 | [Remove Linked List Elements](https://leetcode.com/problems/remove-linked-list-elements/) | LC 203 | Dummy node |

### 🟡 Intermediate (LeetCode Medium)
| # | Problem | Platform | Key Pattern |
|:-:|---------|----------|-------------|
| 1 | [Add Two Numbers](https://leetcode.com/problems/add-two-numbers/) | LC 2 | Carry propagation |
| 2 | [Remove Nth Node From End](https://leetcode.com/problems/remove-nth-node-from-end-of-list/) | LC 19 | Two-pointer gap |
| 3 | [Swap Nodes in Pairs](https://leetcode.com/problems/swap-nodes-in-pairs/) | LC 24 | Pairwise pointer swap |
| 4 | [Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/) | LC 142 | Floyd's cycle start |
| 5 | [Sort List](https://leetcode.com/problems/sort-list/) | LC 148 | Merge sort on LL |
| 6 | [Reorder List](https://leetcode.com/problems/reorder-list/) | LC 143 | Split + Reverse + Merge |
| 7 | [Copy List with Random Pointer](https://leetcode.com/problems/copy-list-with-random-pointer/) | LC 138 | Interleaving / HashMap |
| 8 | [Flatten a Multilevel DLL](https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/) | LC 430 | DFS flatten |
| 9 | [Rotate List](https://leetcode.com/problems/rotate-list/) | LC 61 | Find length + connect |
| 10 | [Partition List](https://leetcode.com/problems/partition-list/) | LC 86 | Two dummy lists |
| 11 | [Odd Even Linked List](https://leetcode.com/problems/odd-even-linked-list/) | LC 328 | Separate + Connect |
| 12 | [Design Linked List](https://leetcode.com/problems/design-linked-list/) | LC 707 | OOP encapsulation |

### 🔴 Advanced (LeetCode Hard)
| # | Problem | Platform | Key Pattern |
|:-:|---------|----------|-------------|
| 1 | [Reverse Nodes in K-Group](https://leetcode.com/problems/reverse-nodes-in-k-group/) | LC 25 | K-group reversal |
| 2 | [Merge K Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/) | LC 23 | Min-heap / Divide & Conquer |
| 3 | [LRU Cache](https://leetcode.com/problems/lru-cache/) | LC 146 | DLL + HashMap |
| 4 | [LFU Cache](https://leetcode.com/problems/lfu-cache/) | LC 460 | DLL + 2 HashMaps |
| 5 | [Design Skiplist](https://leetcode.com/problems/design-skiplist/) | LC 1206 | Probabilistic multi-level |
| 6 | [Reverse Linked List II](https://leetcode.com/problems/reverse-linked-list-ii/) | LC 92 | Sublist reversal |
| 7 | [Design Browser History](https://leetcode.com/problems/design-browser-history/) | LC 1472 | DLL navigation |

### 🏆 Grandmaster (CSES / Codeforces / GFG)
| # | Problem | Platform | Key Pattern |
|:-:|---------|----------|-------------|
| 1 | [Josephus Problem I](https://cses.fi/problemset/task/2162) | CSES | Circular list simulation |
| 2 | [Josephus Problem II](https://cses.fi/problemset/task/2163) | CSES | PBDS / indexed set |
| 3 | [Flatten a Linked List](https://practice.geeksforgeeks.org/problems/flattening-a-linked-list/1) | GFG | Sorted merge flatten |
| 4 | [Clone with Random Pointer](https://practice.geeksforgeeks.org/problems/clone-a-linked-list-with-next-and-random-pointer/1) | GFG | O(1) space interleaving |
| 5 | [Delete Greater Value on Right](https://practice.geeksforgeeks.org/problems/delete-nodes-having-greater-value-on-right/1) | GFG | Reverse + Track max |

---

## 🎓 How to Study This Module

```
Week 1: Chapters 01-02 (Basics + Operations — Build the Foundation)
         → Must be able to code SLL/DLL from scratch in 5 minutes
Week 2: Chapters 03-04 (Reversal + Fast/Slow Pointer — Core Patterns)
         → Solve 15+ problems using these two patterns alone
Week 3: Chapters 05-06 (Merge/Sort + Structural Modifications)
         → Focus on merge sort and reorder list — top interview questions
Week 4: Chapters 07-08 (DLL/Circular + Advanced Pointers)
         → Practice Josephus, Clone with Random, XOR linked list
Week 5: Chapters 09-10 (Design Problems + LL with Other DS)
         → LRU Cache is asked in 90% of FAANG interviews. Master it.
Week 6: Chapters 11-12 (Advanced Tricks + Edge Cases)
         → Polish skills, practice edge cases, time yourself
```

**For each chapter:**
1. 📖 Read the theory sections with ASCII diagrams first
2. 💻 Run each .cpp file and study the dry-run output
3. ✏️ Code each algorithm from scratch WITHOUT looking at the file
4. 🧪 Test with edge cases: empty list, single node, two nodes
5. 🏆 Solve the practice problems at the end of each file
6. ⏱️ Time yourself — aim for < 15 min per medium problem

---

## 🧪 The Linked List Pattern Matrix

```
┌──────────────────────┬────────────────────────────────────────────────┐
│ Pattern              │ Problems That Use It                          │
├──────────────────────┼────────────────────────────────────────────────┤
│ Three-Pointer Rev    │ Reverse LL, Rev K-Group, Rev Sublist,         │
│                      │ Palindrome, Reorder List                      │
├──────────────────────┼────────────────────────────────────────────────┤
│ Fast/Slow Pointer    │ Find Middle, Detect Cycle, Cycle Start,       │
│                      │ Nth From End, Happy Number, Palindrome        │
├──────────────────────┼────────────────────────────────────────────────┤
│ Dummy Node           │ Merge Sorted, Remove Elements, Partition,     │
│                      │ Insert Sorted, Swap Pairs, Delete N-th        │
├──────────────────────┼────────────────────────────────────────────────┤
│ Split + Reverse +    │ Reorder List, Palindrome Check,               │
│ Merge                │ Sort List, Even-Odd Split                     │
├──────────────────────┼────────────────────────────────────────────────┤
│ DLL + HashMap        │ LRU Cache, LFU Cache, All O(1) DS,           │
│                      │ First Unique in Stream                        │
├──────────────────────┼────────────────────────────────────────────────┤
│ Recursive            │ Reverse LL, Merge Sorted, Flatten,            │
│                      │ Remove Nodes, Deep Copy                       │
├──────────────────────┼────────────────────────────────────────────────┤
│ Two-Pointer          │ Intersection, Nth from End, Merge,            │
│ (different start)    │ Compare Lists, Find Loop                      │
├──────────────────────┼────────────────────────────────────────────────┤
│ Carry/Math           │ Add Two Numbers, Subtract, Multiply,          │
│                      │ Polynomial Operations                         │
├──────────────────────┼────────────────────────────────────────────────┤
│ Circular Logic       │ Josephus, Round-Robin, Circular Buffer,       │
│                      │ Rotate List                                   │
└──────────────────────┴────────────────────────────────────────────────┘
```

---

<div align="center">

### Made with ❤️ for the Competitive Programming & Interview Community

*"Every FAANG interview has at least one Linked List problem. Master the pointers, master the interview."*  
— **Sarvan Yaduvanshi**

**⭐ Star this repo if it helped you! ⭐**

</div>

