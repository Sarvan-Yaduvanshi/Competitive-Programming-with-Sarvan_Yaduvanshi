# Module 10: Interval Greedy Problems

> **Level:** ⭐⭐⭐⭐ Expert  
> **Prerequisites:** Sorting, PQ, Binary Search, Module 03

## Concepts Covered

| # | File | Topic | Difficulty |
|---|------|-------|-----------|
| 1 | `01_Interval_Scheduling_All_Variants.cpp` | Max non-overlapping, min removal, arrows, chain | Expert |
| 2 | `02_Weighted_Job_Scheduling_Bridge.cpp` | Where greedy meets DP (weighted intervals) | Expert |
| 3 | `03_Sweep_Line_Technique.cpp` | Event processing for complex interval problems | Expert |

## Key Insight
Interval problems are a **massive** category. The bridge from greedy to DP:
- **Unweighted**: Pure greedy (sort by end time)
- **Weighted**: DP + Binary Search (sort by end, dp[i] = max(dp[i-1], profit[i] + dp[last_compatible]))
- **Sweep Line**: Process events (start/end) in sorted order with a running state

