# Module 12: Variable Window — Distinct & Frequency Patterns

> **Level:** ⭐⭐⭐ Advanced  
> **Prerequisites:** Module 11

## Concepts Covered

| # | File | Topic | Difficulty |
|---|------|-------|-----------|
| 1 | `01_AtMostK_Distinct.cpp` | LC 340, 159, 904 — Longest with at most K distinct | Medium |
| 2 | `02_ExactK_Trick.cpp` | LC 992, 930, 1248, 1358 — exactK = atMost(K) - atMost(K-1) | Medium-Hard |
| 3 | `03_Count_Subarrays_Patterns.cpp` | LC 2962, 2537, 2799, 1695 — Count subarrays with conditions | Medium |

## 🔥 THE EXACT K TRICK (Most Important Pattern!)
```
exactlyK(K) = atMostK(K) - atMostK(K - 1)
```
This converts "exactly K" (hard) into two "at most K" (easy) calls!

## Key Takeaways
- **At Most K Distinct:** Standard variable window with hashmap, shrink when > K distinct
- **Fruit Into Baskets (LC 904)** = Longest subarray with at most 2 distinct
- **Subarrays with K Different (LC 992)** = atMost(K) - atMost(K-1)
- **Binary Subarrays with Sum (LC 930)** = atMost(goal) - atMost(goal-1)
- **Nice Subarrays (LC 1248)** = same trick with odd count

