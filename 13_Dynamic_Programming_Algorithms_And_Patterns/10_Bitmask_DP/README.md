# 10 — Bitmask DP

## What You'll Learn
- Bitmask DP foundations — encoding subsets as integers
- **Traveling Salesman Problem (TSP)** — dp[mask][i]
- Assignment Problem — dp[mask] with popcount
- Minimum Hamiltonian Path
- Subset Partition DP (k equal subsets)
- **DP over submasks** — O(3^n) iteration trick
- **SOS DP** (Sum over Subsets / Supersets)
- Perfect Matching count (AtCoder DP O)
- Grouping DP (AtCoder DP U)
- Elevator Rides (CSES)

## Files
| File | Topics Covered |
|------|---------------|
| `01_TSP_Assignment_Subset.cpp` | TSP, Assignment, Hamiltonian Path, K-Partition, Submask iteration, Counting Hamiltonian |
| `02_Profile_Matching_SOS.cpp` | Perfect Matching, Grouping DP, Elevator Rides, SOS DP (subset + superset) |

## Bit Operations Cheat Sheet
```
Check bit i set:   mask & (1 << i)
Set bit i:         mask | (1 << i)
Clear bit i:       mask & ~(1 << i)
Toggle bit i:      mask ^ (1 << i)
Count set bits:    __builtin_popcount(mask)
Lowest set bit:    mask & (-mask)
Iterate submasks:  for(s=mask; s>0; s=(s-1)&mask)
```

## Practice Problems
- LeetCode: 943, 1125, 698, 473
- CSES: Elevator Rides, Counting Tilings
- AtCoder DP: O (Matching), U (Grouping)

