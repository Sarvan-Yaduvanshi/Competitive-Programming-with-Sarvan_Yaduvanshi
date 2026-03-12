# 12 — DP Optimization Techniques

## What You'll Learn
- **Convex Hull Trick (CHT)** — deque-based O(n) for monotonic slopes
- **Li Chao Tree** — O(n log n) for arbitrary slopes
- **Divide & Conquer DP** — when opt(i,j) ≤ opt(i,j+1)
- **Knuth's Optimization** — O(n³) → O(n²) for interval DP
- **Monotonic Queue Optimization** — sliding window DP
- **Slope Trick** — piecewise-linear convex DP functions
- **Aliens Trick (Lambda/Penalty)** — remove exact-k constraint via binary search

## Files
| File | Topics Covered |
|------|---------------|
| `01_Convex_Hull_Trick.cpp` | CHT (deque), Li Chao Tree, Frog 3 (AtCoder DP Z) |
| `02_DnC_Knuth_Slope_Aliens.cpp` | D&C Optimization, Knuth Optimization, Monotonic Queue, Slope Trick, Aliens Trick |

## When to Use Which
| Technique | Recurrence Form | Reduces |
|-----------|----------------|---------|
| CHT | dp[i] = min(dp[j] + b[j]×a[i]) | O(n²) → O(n) |
| Li Chao | Same, non-monotonic slopes | O(n²) → O(n log n) |
| D&C DP | dp[i][j] = min(dp[i-1][k] + C(k,j)), opt monotone | O(kn²) → O(kn log n) |
| Knuth | dp[i][j] = min(dp[i][k]+dp[k+1][j]+w), QI holds | O(n³) → O(n²) |
| Mono Queue | dp[i] = min(dp[j]+C) for j in sliding window | O(nw) → O(n) |
| Slope Trick | Convex piecewise-linear dp | Case specific |
| Aliens | min f(x) s.t. exactly k items | Removes k constraint |

## Practice Problems
- AtCoder DP Z (Frog 3 — CHT)
- CF 319C (Kalila and Dimna — CHT)
- CF 868F (D&C Optimization)
- CF 321E (Knuth)

