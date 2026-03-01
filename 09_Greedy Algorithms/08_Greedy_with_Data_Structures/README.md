# Module 08: Greedy + Data Structures

> **Level:** ⭐⭐⭐ Advanced  
> **Prerequisites:** Priority Queue, Multiset, Stack, DSU

## Concepts Covered

| # | File | Topic | Difficulty |
|---|------|-------|-----------|
| 1 | `01_Priority_Queue_Greedy.cpp` | Heap-based greedy patterns (IPO, refueling) | Advanced |
| 2 | `02_Multiset_Greedy.cpp` | Ordered multiset for greedy assignment | Advanced |
| 3 | `03_Stack_Based_Greedy.cpp` | Monotone stack greedy patterns | Advanced |
| 4 | `04_Deque_Based_Greedy.cpp` | Sliding window + greedy | Advanced |
| 5 | `05_DSU_Based_Greedy.cpp` | Union-Find for greedy problems | Advanced |

## Key Insight
Many hard greedy problems become tractable with the right data structure:
- **Priority Queue**: "Always pick the best available" → O(log N) per operation
- **Multiset**: "Find the best match" → O(log N) lookup + erase
- **Monotone Stack**: "Maintain increasing/decreasing property" → amortized O(1)
- **DSU**: "Group elements greedily" → near O(1) with path compression

