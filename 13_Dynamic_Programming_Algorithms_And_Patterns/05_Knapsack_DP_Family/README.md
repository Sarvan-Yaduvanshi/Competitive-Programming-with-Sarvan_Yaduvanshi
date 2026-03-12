# 05 — Knapsack DP Family

## What You'll Learn
- 0/1 Knapsack (standard + space optimized)
- Subset Sum, Count Subsets, Min Subset Difference
- Equal Partition, Target Sum
- Unbounded Knapsack (forward iteration trick)
- Bounded Knapsack (binary decomposition)
- Rod Cutting Problem
- Coin Change — Combinations vs Permutations (loop order matters!)

## Files
| File | Topics Covered |
|------|---------------|
| `01_01_Knapsack_And_Variants.cpp` | 0/1 Knapsack, Subset Sum, Partition, Target Sum, Min Diff |
| `02_Unbounded_Bounded_Rod_Cutting.cpp` | Unbounded, Bounded (binary decomp), Rod Cutting, Coin Change |

## Key Insight
> **0/1 Knapsack → iterate capacity BACKWARDS**  
> **Unbounded Knapsack → iterate capacity FORWARDS**  
> **Combinations → outer loop coins, inner loop amount**  
> **Permutations → outer loop amount, inner loop coins**

## Practice Problems
- LeetCode: 416, 494, 322, 518, 377, 474, 1049
- CSES: Book Shop, Money Sums, Two Sets II, Minimizing Coins
- AtCoder DP: D (Knapsack 1), E (Knapsack 2)

