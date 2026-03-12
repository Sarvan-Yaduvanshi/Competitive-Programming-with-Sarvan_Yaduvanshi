# 07 — Interval DP

## What You'll Learn
- Interval DP pattern: dp[i][j] = answer for range [i..j]
- Matrix Chain Multiplication (MCM)
- Burst Balloons (think LAST, not first!)
- Minimum Cost to Merge Stones (k-way merge)
- Palindrome Partitioning II (min cuts)
- Optimal Binary Search Tree
- Stone Game merge variants
- Strange Printer, Min Cost to Cut a Stick
- Polygon Triangulation
- Boolean Parenthesization

## Files
| File | Topics Covered |
|------|---------------|
| `01_MCM_Burst_Balloons_Merge.cpp` | MCM, Burst Balloons, Merge Stones, Palindrome Partition, Optimal BST |
| `02_Stone_Game_Range_DP.cpp` | Stone Merge, Strange Printer, Cut Stick, Triangulation, Boolean Parenthesization |

## Interval DP Template
```
for (len = 2; len <= n; len++)        // increasing length
  for (i = 0; i + len - 1 < n; i++)  // start
    j = i + len - 1;                  // end
    for (k = i; k < j; k++)           // split point
      dp[i][j] = optimize(dp[i][k] + dp[k+1][j] + cost)
```

## Practice Problems
- LeetCode: 312, 1039, 1000, 132, 1547, 664, 87
- CSES: Rectangle Cutting, Removal Game
- AtCoder DP: N (Slimes)

