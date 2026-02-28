# Module 04: Fast & Slow Pointers (Floyd's Cycle Detection)

> **Level:** ⭐⭐ Intermediate  
> **Prerequisites:** Module 01

## Concepts Covered

| # | File | Topic | Difficulty |
|---|------|-------|-----------|
| 1 | `01_Floyd_Cycle_Detection.cpp` | Theory + LL Cycle (LC 141, 142) | Easy-Medium |
| 2 | `02_Find_Duplicate_Number.cpp` | LC 287 — Array as linked list, Floyd's | Medium |
| 3 | `03_Happy_Number_And_List_Apps.cpp` | LC 202, 876, 19, 2095 — Floyd's on math, middle, remove Nth | Easy-Medium |
| 4 | `04_Reorder_Sort_List_Circular_Loop.cpp` | LC 143, 148, 457, 61 — Reorder, Merge Sort, Circular Array Loop | Medium-Hard |

## Key Takeaways
- Slow=1 step, Fast=2 steps → meet inside cycle (if cycle exists)
- To find cycle START: reset one to head, both move 1 step → meet at start
- LC 287: Treat arr[i] as "next pointer" → cycle entry = duplicate
- Finding middle: when fast reaches end, slow is at middle
- **Reorder List (LC 143):** Find middle → reverse second half → merge alternately
- **Sort List (LC 148):** Merge sort using fast/slow to split
- **Circular Array Loop (LC 457):** Floyd's with same-direction constraint

