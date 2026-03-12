# 09 — Graph DP

## What You'll Learn
- DP on DAGs — process in topological order
- Longest Path in DAG
- Count Paths in DAG
- Floyd-Warshall — All Pairs Shortest Path (DP on intermediate nodes)
- Bellman-Ford as DP (relax k edges)
- **SOS DP** (Sum Over Subsets) — O(n × 2^n) instead of O(3^n)
- DP on layered/functional graphs

## Files
| File | Topics Covered |
|------|---------------|
| `01_DAG_DP_And_Floyd_Warshall.cpp` | Longest Path, Count Paths, Floyd-Warshall, Bellman-Ford, SOS DP |

## Key Insight
> **Any DP can be seen as shortest/longest path on a DAG of states.**
> Floyd-Warshall: dp[k][i][j] = shortest using nodes {0..k} as intermediates.

## Practice Problems
- CSES: Longest Flight Route, Game Routes, Shortest Routes II
- AtCoder DP: G (Longest Path)
- CF: 1131D, related SOS problems

