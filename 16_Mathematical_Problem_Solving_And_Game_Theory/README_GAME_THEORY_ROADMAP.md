# 📐 Chapter 16: Mathematical Problem Solving & Game Theory

## 🎯 Complete Roadmap — Zero to Grandmaster Level

> **Goal**: Master every math trick, game theory concept, and puzzle pattern asked in **FAANG interviews** and **Codeforces/CSES/LeetCode contests** — from basic parity arguments to Sprague-Grundy theorem and beyond.

---

## 📚 Table of Contents

| # | Folder | Key Concepts | Difficulty |
|---|--------|-------------|------------|
| 01 | [Math Problem Solving Foundations](01_Math_Problem_Solving_Foundations/) | Pigeonhole, Parity, Invariants, Monovariants, Induction, Symmetry | ⭐ – ⭐⭐ |
| 02 | [Number Pattern Problems](02_Number_Pattern_Problems/) | Digit Manipulation, Digit Sum, Palindromes, Base Conversion | ⭐ – ⭐⭐ |
| 03 | [Modular Arithmetic Problem Solving](03_Modular_Arithmetic_Problem_Solving/) | Mod Tricks, Mod Exponentiation, Mod Inverse, Modular Combinatorics | ⭐⭐ – ⭐⭐⭐ |
| 04 | [Combinatorics Problem Solving](04_Combinatorics_Problem_Solving/) | P&C, Stars & Bars, Derangements, Catalan, Counting Paths | ⭐⭐ – ⭐⭐⭐⭐ |
| 05 | [Probability Problems](05_Probability_Problems/) | Expected Value, Random Walks, Probability DP, Dice/Coin | ⭐⭐ – ⭐⭐⭐⭐ |
| 06 | [Game Theory Foundations](06_Game_Theory_Foundations/) | Impartial Games, Normal Play, W/L States, Backward Induction | ⭐⭐ – ⭐⭐⭐ |
| 07 | [Nim & Sprague-Grundy](07_Nim_And_Sprague_Grundy/) | Classic Nim, Grundy Numbers, Mex, Composite Games | ⭐⭐⭐ – ⭐⭐⭐⭐ |
| 08 | [Combinatorial Game Theory](08_Combinatorial_Game_Theory/) | Subtraction Games, Wythoff, Moore's Nim, Take-and-Break | ⭐⭐⭐ – ⭐⭐⭐⭐⭐ |
| 09 | [Math Optimization Problems](09_Math_Optimization_Problems/) | Greedy Math, AM-GM, Convexity, Inequality Tricks | ⭐⭐⭐ – ⭐⭐⭐⭐ |
| 10 | [Advanced Contest Math](10_Advanced_Contest_Math/) | Generating Functions, Matrix Recurrence, Lagrange Interpolation | ⭐⭐⭐⭐ – ⭐⭐⭐⭐⭐ |
| 11 | [🏆 Top Game Theory Problem Solving](11_Top_Game_Theory_Problem_Solving/) | Curated Problems + Cheat Sheet (LeetCode, CF, CSES, AtCoder) | All Levels |

---

## 🗺️ Dependency Graph

```
                    ┌─────────────────────┐
                    │ 01. Math Foundations │
                    └─────────┬───────────┘
                              │
              ┌───────────────┼───────────────┐
              ▼               ▼               ▼
    ┌─────────────┐  ┌──────────────┐  ┌───────────────┐
    │ 02. Number  │  │ 03. Modular  │  │ 06. Game      │
    │ Patterns    │  │ Arithmetic   │  │ Theory Basics │
    └─────────────┘  └──────┬───────┘  └───────┬───────┘
                            │                  │
                            ▼                  ▼
                   ┌──────────────┐   ┌──────────────────┐
                   │ 04. Combina- │   │ 07. Nim &        │
                   │ torics       │   │ Sprague-Grundy   │
                   └──────┬───────┘   └────────┬─────────┘
                          │                    │
                          ▼                    ▼
                   ┌──────────────┐   ┌──────────────────┐
                   │ 05. Probab-  │   │ 08. Combinatorial│
                   │ ility        │   │ Game Theory      │
                   └──────┬───────┘   └────────┬─────────┘
                          │                    │
                          └────────┬───────────┘
                                   ▼
                          ┌──────────────────┐
                          │ 09. Math Optim.  │
                          └────────┬─────────┘
                                   ▼
                          ┌──────────────────┐
                          │ 10. Advanced     │
                          │ Contest Math     │
                          └────────┬─────────┘
                                   ▼
                          ┌──────────────────┐
                          │ 11. 🏆 Top       │
                          │ Problem Solving  │
                          └──────────────────┘
```

---

## ⚡ Complexity Cheat Sheet

| Algorithm / Technique | Time Complexity | Space |
|----------------------|----------------|-------|
| Modular Exponentiation | O(log n) | O(1) |
| Modular Inverse (Fermat) | O(log p) | O(1) |
| nCr with Precomputation | O(n) precomp, O(1) query | O(n) |
| Catalan Number (DP) | O(n) | O(n) |
| Derangement Count | O(n) | O(n) |
| Grundy Number (brute force) | O(positions × moves) | O(positions) |
| Nim XOR Check | O(n) | O(1) |
| Matrix Exponentiation | O(k³ log n) | O(k²) |
| Lagrange Interpolation | O(n²) or O(n log n) | O(n) |
| Sprague-Grundy (memoized) | O(states × moves) | O(states) |
| Wythoff's Formula | O(1) | O(1) |
| Expected Value DP | O(states) | O(states) |
| Inclusion-Exclusion (k primes) | O(2^k) | O(k) |
| Burnside's Lemma (cyclic n) | O(√n × log) | O(1) |
| Euclid's Game | O(log(max(a,b))) | O(1) |
| Game on DAG (BFS) | O(V + E) | O(V) |
| Ternary Search | O(log(range/eps)) | O(1) |
| Binary Search on Answer | O(log(range) × check) | O(1) |

---

## 📅 4-Week Study Plan

### Week 1: Foundations (Folders 01–03)
| Day | Topic | Focus |
|-----|-------|-------|
| 1-2 | Math Foundations | Pigeonhole, parity, invariants |
| 3-4 | Number Patterns | Digit tricks, palindromes, base conversion |
| 5-7 | Modular Arithmetic | Mod tricks, modexp, mod inverse |

### Week 2: Counting & Probability (Folders 04–05)
| Day | Topic | Focus |
|-----|-------|-------|
| 1-3 | Combinatorics | P&C, Stars & Bars, Catalan, Derangements |
| 4-5 | Probability | Expected value, linearity of expectation |
| 6-7 | Probability DP | Random walks, dice problems |

### Week 3: Game Theory (Folders 06–08)
| Day | Topic | Focus |
|-----|-------|-------|
| 1-2 | Game Theory Basics | W/L states, backward induction |
| 3-5 | Nim & Sprague-Grundy | Classic Nim, Grundy numbers, mex |
| 6-7 | Combinatorial Games | Wythoff, Moore's Nim, subtraction games |

### Week 4: Advanced Topics (Folders 09–11)
| Day | Topic | Focus |
|-----|-------|-------|
| 1-2 | Math Optimization | Greedy math, inequalities |
| 3-5 | Advanced Contest Math | Matrix recurrence, generating functions |
| 6-7 | Problem Solving Marathon | Solve top problems from Folder 11 |

---

## 🔗 Cross-References

- **Chapter 14**: [Number Theory & Mathematics](../14_Number_Theory_And_Mathematics/) — for prime factorization, GCD/LCM, Euler's totient, CRT foundations
- **Chapter 13**: [Dynamic Programming](../13_Dynamic_Programming_Algorithms_And_Patterns/) — for DP techniques used in probability and game theory
- **Chapter 10**: [Bit Manipulation](../10_Advanced%20Bit%20Manipulation%20+%20DP%20with%20Bit-Masking/) — XOR tricks crucial for Nim

---

## 📖 References

1. *Winning Ways for Your Mathematical Plays* — Berlekamp, Conway, Guy
2. *Lessons in Play* — Albert, Nowakowski, Wolfe
3. *Concrete Mathematics* — Graham, Knuth, Patashnik
4. *CP Algorithms* — https://cp-algorithms.com/
5. *CSES Problem Set* — https://cses.fi/problemset/
6. *Codeforces EDU* — Game Theory section

---

*Created by Sarvan Yaduvanshi | Competitive Programming Repository*

