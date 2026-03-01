# Module 03: Sorting-Based Greedy

> **Level:** ⭐⭐ Intermediate  
> **Prerequisites:** Module 01-02, Sorting algorithms

## Concepts Covered

| # | File | Topic | Difficulty |
|---|------|-------|-----------|
| 1 | `01_Custom_Sorting_for_Greedy.cpp` | Comparator design, proof of correctness | Intermediate |
| 2 | `02_Interval_Scheduling_Maximization.cpp` | Earliest-finish-time selection | Intermediate |
| 3 | `03_Interval_Partitioning.cpp` | Minimum resources / rooms needed | Intermediate |
| 4 | `04_Minimizing_Lateness.cpp` | Earliest-deadline-first scheduling | Intermediate |
| 5 | `05_Optimal_Merge_Pattern.cpp` | Merge cost minimization with PQ | Intermediate |

## Key Insight
**80% of greedy problems start with sorting.** The hard part is figuring out WHAT to sort by.

Common sorting criteria:
- End time (interval scheduling)
- Start time (merge intervals)
- Deadline (lateness minimization)
- Ratio (knapsack, weighted scheduling)
- Difference (two-city scheduling)

