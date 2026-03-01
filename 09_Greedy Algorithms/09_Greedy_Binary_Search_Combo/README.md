# Module 09: Greedy + Binary Search Combo

> **Level:** ⭐⭐⭐ Advanced  
> **Prerequisites:** Binary Search, Greedy fundamentals

## Concepts Covered

| # | File | Topic | Difficulty |
|---|------|-------|-----------|
| 1 | `01_Binary_Search_on_Answer_Greedy_Check.cpp` | Parametric search + greedy feasibility check | Advanced |
| 2 | `02_Greedy_Validation_in_BS.cpp` | Writing greedy check functions for BS | Advanced |

## Key Insight
**Binary Search on the Answer + Greedy Check** is one of the most powerful combos in CP:
1. Binary search over the answer space (min/max value)
2. For each candidate answer, use a greedy O(N) check: "Is this answer feasible?"
3. Total: O(N log(answer_range))

This pattern appears in 50%+ of CF Div2 C/D problems!

