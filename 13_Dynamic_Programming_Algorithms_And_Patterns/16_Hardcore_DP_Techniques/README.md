# 16 — Hardcore DP Techniques (ICPC / GM Level)

## What You'll Learn
- **DP with Segment Tree** — O(n log n) transitions using range queries
- **DP with Fenwick Tree (BIT)** — LIS counting, weighted LIS, inversions
- **DP with Li Chao Tree** — non-monotonic CHT queries
- **Centroid Decomposition DP** — process all tree paths through centroid
- **Euler Tour DP** — flatten tree, use range DP on linearized array
- **Plug DP / Connection Profile DP** — Hamiltonian paths in grids
- **Steiner Tree DP** — O(3^k × n) for connecting terminal nodes
- **DP on HLD** — combine chain DP values at junctions

## Files
| File | Topics Covered |
|------|---------------|
| `01_DP_With_SegTree_BIT.cpp` | Flowers (LIS+BIT), Count Inversions, LIS Count, Weighted Interval Scheduling+SegTree |
| `02_Centroid_HLD_Plug_Steiner.cpp` | Centroid Decomposition (count paths), Euler Tour, Plug DP concept, Steiner Tree DP |

## Difficulty: ⭐⭐⭐⭐⭐
These are the most advanced DP techniques used in ICPC World Finals and Grandmaster-level Codeforces.

## When to Use
| Technique | Use Case |
|-----------|----------|
| DP + SegTree/BIT | DP transition needs range max/sum query |
| Centroid DP | DP on all tree paths efficiently |
| Euler Tour DP | Subtree → contiguous range on segment tree |
| Plug DP | Grid Hamiltonian path/cycle, connected subsets |
| Steiner Tree | Min cost to connect k terminals (k ≤ 15) |

## Practice Problems
- AtCoder DP: Q (Flowers — BIT), W (Intervals — SegTree)
- CF: 868F (D&C + SegTree), centroid problems
- ICPC: Plug DP, Steiner Tree problems
- CSES: Counting Tilings (profile DP)

