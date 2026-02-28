# 📘 Chapter 02 — Sequence Containers

## Overview
Sequence containers store elements in **linear order** based on insertion position. They are the **workhorses** of competitive programming — you'll use `vector` in 90% of problems.

## Files in This Chapter

| # | File | Topic | Key Concepts |
|:-:|------|-------|-------------|
| 01 | `01_Vector_Complete.cpp` | vector | Init, push_back, emplace_back, reserve, capacity, resize, erase, shrink_to_fit, iteration, 2D vectors |
| 02 | `02_Deque_Complete.cpp` | deque | push_front/back, differences from vector, BFS 0-1 trick |
| 03 | `03_List_Complete.cpp` | list | Doubly linked, splice, merge, reverse, remove, when to use |
| 04 | `04_Forward_List.cpp` | forward_list | Singly linked, before_begin, insert_after |
| 05 | `05_Array_Fixed_Size.cpp` | std::array | Fixed-size, fill, comparison, vs C-array |
| 06 | `06_Sequence_Container_Comparison.cpp` | Comparison | When to use which, performance characteristics |

## 🎯 GM Tips
- `vector` is the default choice — use it unless you have a specific reason not to
- Always `reserve()` if you know the size — prevents reallocations
- `emplace_back` > `push_back` — avoids copy construction
- `deque` for BFS (0-1 BFS trick), sliding window front-back operations
- `list` is rarely used in CP — only when you need O(1) splice/merge
- Use `vector<vector<int>>` for adjacency lists in graphs

## 📊 Complexity Comparison
```
┌──────────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
│ Operation    │ vector   │ deque    │ list     │ fwd_list │ array    │
├──────────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
│ Access [i]   │ O(1)     │ O(1)     │ O(n)     │ O(n)     │ O(1)     │
│ push_back    │ O(1)*    │ O(1)*    │ O(1)     │ N/A      │ N/A      │
│ push_front   │ O(n)     │ O(1)*    │ O(1)     │ O(1)     │ N/A      │
│ Insert mid   │ O(n)     │ O(n)     │ O(1)**   │ O(1)**   │ N/A      │
│ Erase mid    │ O(n)     │ O(n)     │ O(1)**   │ O(1)**   │ N/A      │
│ Find         │ O(n)     │ O(n)     │ O(n)     │ O(n)     │ O(n)     │
└──────────────┴──────────┴──────────┴──────────┴──────────┴──────────┘
  * amortized   ** with iterator
```

