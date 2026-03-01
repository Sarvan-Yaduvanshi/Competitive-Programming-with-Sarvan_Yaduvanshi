# 🚀 Recursion: Zero to Grandmaster (GM) Complete Roadmap

## By Sarvan Yaduvanshi

---

## 📋 Curriculum Overview

| Level | Topic | Difficulty | Folder |
|-------|-------|-----------|--------|
| **1** | Recursion Fundamentals | ⭐ Beginner | `Recursion Fundamentals/` |
| **2** | Recursion Patterns (Subsequences, Subsets) | ⭐⭐ Intermediate | `Recursion Patterns/` |
| **3** | Backtracking & State Space Search | ⭐⭐⭐ Intermediate-Advanced | `Backtracking & State Space Search/` |
| **4** | Divide and Conquer | ⭐⭐⭐ Advanced | `Divide and Conquer/` |
| **5** | Advanced/GM-Level Recursion | ⭐⭐⭐⭐⭐ Expert-GM | `Advanced Recursion (GM Level)/` |

---

## 🧠 The 3 Golden Rules of Recursion
1. **Base Case** — When to STOP (prevents infinite recursion)
2. **Recursive Case** — Break problem into SMALLER subproblem
3. **Trust the Recursion** — Assume the function works for smaller input

---

## 🔥 Core Recursion Patterns (Master These!)

### Pattern 1: Linear Recursion
```
f(n) depends on f(n-1)
Example: factorial, fibonacci
```

### Pattern 2: Take / Not-Take (Include/Exclude)
```
At each index: either INCLUDE current element or SKIP it
Used for: subsets, subsequences, knapsack
```

### Pattern 3: Explore All Choices + Backtrack
```
Try every option → recurse → UNDO choice → try next
Used for: permutations, N-Queens, Sudoku
```

### Pattern 4: Divide and Conquer
```
Split into halves → solve each → merge results
Used for: merge sort, count inversions, closest pair
```

### Pattern 5: Recursion + Memoization (→ DP)
```
Cache results of subproblems to avoid recomputation
Used for: all DP problems, digit DP, bitmask DP
```

### Pattern 6: Recursion + Bitmask
```
Use bitmask to represent subset state
Used for: TSP, assignment problem, SOS DP
```

---

## 📊 Practice Problem Tracker

### Level 1: Fundamentals
- [ ] Factorial
- [ ] Fibonacci
- [ ] Sum of digits
- [ ] Power (fast exponentiation)
- [ ] Print array recursively
- [ ] Reverse a string
- [ ] Check palindrome
- [ ] Tower of Hanoi

### Level 2: Patterns
- [ ] Print all subsequences
- [ ] Print subsequences with sum = K
- [ ] Count subsequences with sum = K
- [ ] Generate all subsets (power set) — LC 78
- [ ] Combination Sum — LC 39
- [ ] Combination Sum II — LC 40
- [ ] Subset Sum I — LC 416 (recursive)
- [ ] Target Sum — LC 494 (recursive)

### Level 3: Backtracking
- [ ] Permutations — LC 46
- [ ] Permutations II — LC 47
- [ ] N-Queens — LC 51
- [ ] Sudoku Solver — LC 37
- [ ] Rat in a Maze — GFG
- [ ] Word Search — LC 79
- [ ] Letter Combinations — LC 17
- [ ] Palindrome Partitioning — LC 131
- [ ] M-Coloring — GFG

### Level 4: Divide and Conquer
- [ ] Merge Sort
- [ ] Quick Sort
- [ ] Count Inversions — CF / GFG
- [ ] Closest Pair of Points
- [ ] Power (recursive) — LC 50

### Level 5: GM-Level
- [ ] Bitmask + Recursion (TSP)
- [ ] Digit DP — Count numbers with property
- [ ] SOS DP (Sum over Subsets)
- [ ] Meet in the Middle
- [ ] Sprague-Grundy (Game Theory)
- [ ] Tree DFS / Rerooting
- [ ] CF 1594D (Div 2 D — backtracking)
- [ ] CF 1525D (Div 2 D — meet in middle)
- [ ] CF 1208F (Bitmask DP)

---

## ⏱ Suggested Study Plan
| Day | Topic |
|-----|-------|
| Day 1-2 | Level 1: Fundamentals (all files) |
| Day 3-4 | Level 2: Subsequences & Subsets |
| Day 5-7 | Level 3: Backtracking (practice heavy) |
| Day 8-9 | Level 4: Divide and Conquer |
| Day 10-14 | Level 5: GM-Level patterns |
| Day 15+ | Codeforces practice (Div 2 C, D, E problems) |

---

**Let's become GM! 🏆**

