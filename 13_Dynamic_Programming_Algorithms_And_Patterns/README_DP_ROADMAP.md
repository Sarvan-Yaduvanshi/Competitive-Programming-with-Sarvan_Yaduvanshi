# 🏆 Dynamic Programming — Complete Roadmap (Basic → Grandmaster / ICPC Level)

> **Author:** Sarvan Yaduvanshi  
> **Chapter:** 13 — Dynamic Programming Algorithms & Patterns  
> **Difficulty Progression:** ⭐ Beginner → ⭐⭐⭐⭐⭐ Grandmaster/ICPC

---

## 📖 Table of Contents

| # | Folder | Difficulty | Key Topics |
|---|--------|-----------|------------|
| 01 | [DP Foundations](01_DP_Foundations/) | ⭐ | What is DP, Memoization, Tabulation, State & Transition |
| 02 | [1D DP Patterns](02_1D_DP_Patterns/) | ⭐ | Fibonacci, Stairs, House Robber, Coin Change, Kadane, Jump Game, Word Break, Stock |
| 03 | [2D DP Patterns](03_2D_DP_Patterns/) | ⭐⭐ | Grid DP, Unique Paths, Min Path, Edit Distance |
| 04 | [Subsequence & String DP](04_Subsequence_And_String_DP/) | ⭐⭐ | LCS, Palindrome DP, Wildcard/Regex, SCS |
| 05 | [Knapsack DP Family](05_Knapsack_DP_Family/) | ⭐⭐ | 0/1, Unbounded, Bounded, Subset Sum, Target Sum, MitM, Value-Indexed |
| 06 | [LIS & Sequence DP](06_LIS_And_Sequence_DP/) | ⭐⭐⭐ | LIS O(n²), LIS O(n log n), Bitonic, Russian Dolls |
| 07 | [Interval DP](07_Interval_DP/) | ⭐⭐⭐ | MCM, Burst Balloons, Merge Stones, Palindrome Partition |
| 08 | [Tree DP](08_Tree_DP/) | ⭐⭐⭐ | Subtree DP, Rerooting, Diameter, Matching, Tree Knapsack |
| 09 | [Graph DP](09_Graph_DP/) | ⭐⭐⭐ | DAG DP, Longest Path, Floyd-Warshall, SOS DP |
| 10 | [Bitmask DP](10_Bitmask_DP/) | ⭐⭐⭐⭐ | TSP, Assignment, Profile DP, Subset DP |
| 11 | [Digit DP](11_Digit_DP/) | ⭐⭐⭐⭐ | Digit DP Template, Range Queries, Constraints |
| 12 | [DP Optimization](12_DP_Optimization_Techniques/) | ⭐⭐⭐⭐ | CHT, D&C Opt, Knuth Opt, Aliens, Slope Trick, Matrix Exponentiation |
| 13 | [Advanced DP Patterns](13_Advanced_DP_Patterns/) | ⭐⭐⭐⭐⭐ | Broken Profile, SOS, Permutation, Combinatorial, Circular, Burnside |
| 14 | [Probability DP](14_Probability_DP/) | ⭐⭐⭐⭐ | Expected Value, Markov, Random Walk, Dice DP |
| 15 | [Game Theory DP](15_Game_Theory_DP/) | ⭐⭐⭐⭐ | Grundy, Sprague-Grundy, Minimax, Stone Games |
| 16 | [Hardcore DP](16_Hardcore_DP_Techniques/) | ⭐⭐⭐⭐⭐ | DP+SegTree, DP+BIT, Li Chao, Centroid, HLD, Plug, String Automaton, NTT/CDQ |

---

## 🧠 DP Decision Flowchart

```
START: Can the problem be broken into overlapping subproblems?
  │
  ├── YES → Does it have optimal substructure?
  │     │
  │     ├── YES → Use DP!
  │     │     │
  │     │     ├── Single parameter? → 1D DP (Folder 02)
  │     │     ├── Two parameters? → 2D DP (Folder 03)
  │     │     ├── Strings/Subsequences? → String DP (Folder 04)
  │     │     ├── Weight + Value? → Knapsack (Folder 05)
  │     │     ├── Ordering/Sequence? → LIS DP (Folder 06)
  │     │     ├── Range [i..j]? → Interval DP (Folder 07)
  │     │     ├── Tree structure? → Tree DP (Folder 08)
  │     │     ├── DAG/Graph? → Graph DP (Folder 09)
  │     │     ├── Subset selection? → Bitmask DP (Folder 10)
  │     │     ├── Number digits? → Digit DP (Folder 11)
  │     │     ├── TLE on basic DP? → Optimization (Folder 12)
  │     │     ├── Probability/Expected? → Probability DP (Folder 14)
  │     │     └── Two-player game? → Game Theory DP (Folder 15)
  │     │
  │     └── NO → Greedy / Other approach
  │
  └── NO → Not a DP problem (try Greedy, D&C, etc.)
```

---

## 🔥 DP Complexity Cheat Sheet

| Pattern | Typical States | Transition | Total Complexity |
|---------|---------------|------------|-----------------|
| 1D DP | O(n) | O(1) | O(n) |
| 2D Grid DP | O(n×m) | O(1) | O(n×m) |
| LCS / Edit Distance | O(n×m) | O(1) | O(n×m) |
| 0/1 Knapsack | O(n×W) | O(1) | O(n×W) |
| LIS (Binary Search) | O(n) | O(log n) | O(n log n) |
| Interval DP | O(n²) | O(n) | O(n³) |
| Tree DP | O(n) | O(children) | O(n) |
| Bitmask DP | O(2ⁿ × n) | O(n) | O(2ⁿ × n²) |
| Digit DP | O(digits × sum × tight) | O(10) | O(D × S × 2) |
| TSP | O(2ⁿ × n) | O(n) | O(2ⁿ × n²) |
| SOS DP | O(2ⁿ × n) | O(1) | O(2ⁿ × n) |
| CHT Optimization | O(n) | O(1) amort | O(n) |
| D&C Optimization | O(n × m) | O(log n) | O(n × m × log n) |
| Knuth Optimization | O(n²) | O(1) amort | O(n²) |
| Matrix Exponentiation | O(k) states | O(k³) per step | O(k³ × log n) |
| NTT/Convolution DP | O(n) | O(n log n) | O(n log² n) |
| Tree Knapsack | O(n × K) | O(K) | O(n × K) amortized |
| String Automaton DP | O(len × states) | O(Σ) | O(n × m × Σ) |

---

## 📅 Suggested Study Schedule

| Week | Folders | Focus |
|------|---------|-------|
| 1 | 01, 02 | DP Thinking + 1D Patterns |
| 2 | 03, 04 | 2D DP + String DP |
| 3 | 05, 06 | Knapsack + LIS |
| 4 | 07, 08 | Interval DP + Tree DP |
| 5 | 09, 10 | Graph DP + Bitmask DP |
| 6 | 11, 12 | Digit DP + Optimizations |
| 7 | 13, 14 | Advanced Patterns + Probability |
| 8 | 15, 16 | Game Theory + Hardcore |

---

## 🎯 Must-Solve Problem Cheat Sheet (By Platform)

### LeetCode Essential DP Problems
| # | Problem | Pattern | Difficulty |
|---|---------|---------|-----------|
| 70 | Climbing Stairs | 1D DP | Easy |
| 198 | House Robber | 1D DP | Medium |
| 322 | Coin Change | 1D DP / Knapsack | Medium |
| 62 | Unique Paths | 2D Grid | Medium |
| 64 | Minimum Path Sum | 2D Grid | Medium |
| 72 | Edit Distance | String DP | Medium |
| 1143 | Longest Common Subsequence | String DP | Medium |
| 5 | Longest Palindromic Substring | String DP | Medium |
| 416 | Partition Equal Subset Sum | Knapsack | Medium |
| 494 | Target Sum | Knapsack | Medium |
| 300 | Longest Increasing Subsequence | LIS | Medium |
| 354 | Russian Doll Envelopes | LIS | Hard |
| 312 | Burst Balloons | Interval DP | Hard |
| 1039 | Min Score Triangulation | Interval DP | Medium |
| 337 | House Robber III | Tree DP | Medium |
| 124 | Binary Tree Max Path Sum | Tree DP | Hard |
| 943 | Shortest Superstring | Bitmask DP | Hard |
| 1125 | Smallest Sufficient Team | Bitmask DP | Hard |
| 233 | Number of Digit One | Digit DP | Hard |
| 877 | Stone Game | Game Theory DP | Medium |
| 1000 | Min Cost Merge Stones | Interval DP | Hard |
| 10 | Regular Expression Matching | String DP | Hard |
| 44 | Wildcard Matching | String DP | Hard |
| 115 | Distinct Subsequences | String DP | Hard |
| 97 | Interleaving String | String DP | Medium |
| 221 | Maximal Square | 2D DP | Medium |
| 1547 | Min Cost to Cut a Stick | Interval DP | Hard |

### Codeforces Essential DP Problems
| Problem | Pattern | Rating |
|---------|---------|--------|
| CF 455A - Boredom | 1D DP | 1500 |
| CF 189A - Cut Ribbon | 1D DP | 1300 |
| CF 1dp - CSES DP Section | All | — |
| CF 580D - Kefa and Dishes | Bitmask DP | 1800 |
| CF 1131D - Gourmet Choice | DAG DP | 1800 |
| CF 1187E - Tree Painting | Rerooting DP | 2100 |
| CF 1542E2 - Digit DP | Digit DP | 2300 |
| CF 868F - Yet Another Minimization | D&C Optimization | 2500 |
| CF 319C - Kalila and Dimna | CHT | 2200 |
| CF 1156F - Card Bag | Probability DP | 2100 |
| CF 850F - Arpa and a Game | Game DP | 2700 |

### CSES DP Problem Set (Must Solve All)
| Problem | Pattern |
|---------|---------|
| Dice Combinations | 1D DP |
| Minimizing Coins | Knapsack |
| Coin Combinations I | Knapsack |
| Coin Combinations II | Knapsack |
| Removing Digits | 1D DP |
| Grid Paths | 2D DP |
| Book Shop | 0/1 Knapsack |
| Array Description | 1D DP |
| Counting Towers | 1D DP |
| Edit Distance | String DP |
| Rectangle Cutting | Interval DP |
| Money Sums | Knapsack |
| Removal Game | Interval DP |
| Two Sets II | Knapsack |
| Increasing Subsequence | LIS |
| Projects | Interval Scheduling DP |
| Elevator Rides | Bitmask DP |
| Counting Tilings | Profile DP |
| Counting Numbers | Digit DP |

### AtCoder DP Contest (All 26 Problems — A to Z)
| Problem | Pattern |
|---------|---------|
| A - Frog 1 | 1D DP |
| B - Frog 2 | 1D DP |
| C - Vacation | 1D DP |
| D - Knapsack 1 | Knapsack |
| E - Knapsack 2 | Knapsack (value-indexed) |
| F - LCS | String DP |
| G - Longest Path | DAG DP |
| H - Grid 1 | 2D DP |
| I - Coins | Probability DP |
| J - Sushi | Expected Value DP |
| K - Stones | Game DP |
| L - Deque | Game DP |
| M - Candies | Prefix Sum DP |
| N - Slimes | Interval DP |
| O - Matching | Bitmask DP |
| P - Independent Set | Tree DP |
| Q - Flowers | LIS + BIT |
| R - Walk | Matrix Exponentiation DP |
| S - Digit Sum | Digit DP |
| T - Permutation | Permutation DP |
| U - Grouping | Bitmask DP |
| V - Subtree | Rerooting DP |
| W - Intervals | DP + Segment Tree |
| X - Tower | Greedy + DP |
| Y - Grid 2 | Inclusion-Exclusion DP |
| Z - Frog 3 | Convex Hull Trick |

---

## 🧩 DP State Design Patterns

```
Pattern 1: Index-based        → dp[i] = answer considering first i elements
Pattern 2: Two-index          → dp[i][j] = answer for subarray/substring [i..j]
Pattern 3: Index + capacity   → dp[i][w] = knapsack with i items, capacity w
Pattern 4: Index + last value → dp[i][v] = answer ending at index i with value v
Pattern 5: Bitmask            → dp[mask] = answer for subset represented by mask
Pattern 6: Bitmask + index    → dp[mask][i] = answer for subset mask ending at i
Pattern 7: Digits + tight     → dp[pos][sum][tight] = digit DP state
Pattern 8: Node + parent      → dp[node][color] = tree DP state
Pattern 9: Interval           → dp[i][j] = answer for merging interval [i..j]
Pattern 10: Profile           → dp[col][profile_mask] = broken profile state
```

---

## 🛠 Common DP Transitions

```
1D Linear:      dp[i] = max(dp[i-1], dp[i-2] + a[i])
Grid:           dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])
LCS:            dp[i][j] = (s[i]==t[j]) ? dp[i-1][j-1]+1 : max(dp[i-1][j], dp[i][j-1])
Knapsack:       dp[i][w] = max(dp[i-1][w], dp[i-1][w-wt[i]] + val[i])
LIS:            dp[i] = max(dp[j] + 1) for all j < i where a[j] < a[i]
Interval:       dp[i][j] = min(dp[i][k] + dp[k+1][j] + cost(i,j)) for k in [i..j-1]
Bitmask:        dp[mask | (1<<j)][j] = min(dp[mask][i] + dist[i][j])
Tree:           dp[node] = f(dp[child1], dp[child2], ...)
Digit:          dp[pos+1][sum+d][tight && (d==limit)] += dp[pos][sum][tight]
Expected Value: E[state] = sum(prob[next] * (E[next] + cost))
```

---

> 💡 **Golden Rule of DP:** If you can define the state clearly, the transition writes itself.  
> 💡 **Pro Tip:** Always start with brute-force recursion → add memoization → convert to tabulation → optimize space.

---

*Happy Coding! 🚀 — Sarvan Yaduvanshi*

