# 🏆 Greedy Algorithms — Zero to Grandmaster (GM) Level

> **Author:** Sarvan Yaduvanshi  
> **Level:** Beginner → Intermediate → Advanced → Expert → Grandmaster  
> **Language:** C++ (C++20)

---

## 📋 What is Greedy?

A **Greedy Algorithm** makes the **locally optimal choice** at each step, hoping that these local choices lead to a **globally optimal solution**. Unlike Dynamic Programming, greedy never reconsiders past decisions.

### When Does Greedy Work?
1. **Greedy Choice Property** — A globally optimal solution can be assembled by making locally optimal (greedy) choices.
2. **Optimal Substructure** — An optimal solution to the problem contains optimal solutions to subproblems.

---

## 🗺️ Complete Roadmap (14 Modules)

```
                         ┌──────────────────────────────────────┐
                         │     GREEDY ALGORITHMS ROADMAP        │
                         │     Zero ──────────► GM Level        │
                         └──────────────────────────────────────┘

    ┌─────────────────┐     ┌─────────────────────┐     ┌──────────────────────┐
    │ 01. Fundamentals │────►│ 02. Basic Patterns   │────►│ 03. Sorting-Based    │
    │   (What/Why/How) │     │ (Classic Problems)   │     │ (Custom Comparators) │
    └────────┬────────┘     └─────────┬───────────┘     └──────────┬───────────┘
             │                        │                             │
             ▼                        ▼                             ▼
    ┌─────────────────┐     ┌─────────────────────┐     ┌──────────────────────┐
    │ 04. Two Pointer  │────►│ 05. Greedy on Arrays │────►│ 06. Greedy on Strings│
    │   + Greedy       │     │ (Jump/Gas/Candy)     │     │ (Lexicographic)      │
    └────────┬────────┘     └─────────┬───────────┘     └──────────┬───────────┘
             │                        │                             │
             ▼                        ▼                             ▼
    ┌─────────────────┐     ┌─────────────────────┐     ┌──────────────────────┐
    │ 07. Greedy on    │────►│ 08. Greedy + DS      │────►│ 09. Greedy + BinSrch │
    │   Graphs (MST)   │     │ (PQ/Stack/DSU)       │     │ (Parametric Search)  │
    └────────┬────────┘     └─────────┬───────────┘     └──────────┬───────────┘
             │                        │                             │
             ▼                        ▼                             ▼
    ┌─────────────────┐     ┌─────────────────────┐     ┌──────────────────────┐
    │ 10. Interval     │────►│ 11. Greedy on Trees  │────►│ 12. Matroid Theory   │
    │   Greedy         │     │ (Leaf-Root Greedy)   │     │ (Exchange Arguments) │
    └────────┬────────┘     └─────────┬───────────┘     └──────────┬───────────┘
             │                        │                             │
             ▼                        ▼                             ▼
    ┌─────────────────────┐     ┌───────────────────────────────────┐
    │ 13. Advanced Greedy  │────►│ 14. CF GM-Level Greedy            │
    │ (Regret/Rollback)    │     │ (Construction/Math/Interactive)   │
    └──────────────────────┘     └───────────────────────────────────┘
```

---

## 📁 Module Index

| # | Module | Level | Key Concepts |
|---|--------|-------|-------------|
| 01 | [Greedy Fundamentals](01_Greedy_Fundamentals/) | ⭐ Beginner | Definition, Greedy vs DP, Proof Techniques |
| 02 | [Basic Greedy Patterns](02_Basic_Greedy_Patterns/) | ⭐ Beginner | Activity Selection, Knapsack, Huffman |
| 03 | [Sorting-Based Greedy](03_Sorting_Based_Greedy/) | ⭐⭐ Intermediate | Custom Sort, Interval Scheduling, Lateness |
| 04 | [Two Pointer + Greedy](04_Two_Pointer_Greedy_Hybrids/) | ⭐⭐ Intermediate | Merge Intervals, Sweep Line |
| 05 | [Greedy on Arrays](05_Greedy_on_Arrays/) | ⭐⭐ Intermediate | Jump Game, Gas Station, Candy |
| 06 | [Greedy on Strings](06_Greedy_on_Strings/) | ⭐⭐⭐ Advanced | Lexicographic, Remove Digits, Reorganize |
| 07 | [Greedy on Graphs](07_Greedy_on_Graphs/) | ⭐⭐⭐ Advanced | Kruskal, Prim, Dijkstra, Boruvka |
| 08 | [Greedy + Data Structures](08_Greedy_with_Data_Structures/) | ⭐⭐⭐ Advanced | PQ Greedy, Stack Greedy, DSU Greedy |
| 09 | [Greedy + Binary Search](09_Greedy_Binary_Search_Combo/) | ⭐⭐⭐ Advanced | Parametric Search, Feasibility Check |
| 10 | [Interval Greedy Problems](10_Interval_Greedy_Problems/) | ⭐⭐⭐⭐ Expert | All Variants, Sweep Line, Weighted Bridge |
| 11 | [Greedy on Trees](11_Greedy_on_Trees/) | ⭐⭐⭐⭐ Expert | Leaf-to-Root, Edge Cuts, Tree Cameras |
| 12 | [Matroid Theory & Exchange](12_Matroid_Theory_and_Exchange_Arguments/) | ⭐⭐⭐⭐ Expert | Matroids, Formal Proofs, Counter-examples |
| 13 | [Advanced Greedy](13_Advanced_Greedy/) | ⭐⭐⭐⭐⭐ GM | Regret Greedy, Rollback, Online Algorithms |
| 14 | [CF GM-Level Greedy](14_Codeforces_GM_Level_Greedy/) | ⭐⭐⭐⭐⭐ GM | Construction, Math+Greedy, Interactive |

---

## 📊 Difficulty Progression

```
Problems:  Easy ──────► Medium ──────► Hard ──────► Expert ──────► GM
CF Rating: 800-1200     1200-1600      1600-2000    2000-2400      2400+
LC Level:  Easy          Medium         Hard         Hard+          —
Module:    01-02         03-05          06-09        10-12          13-14
```

---

## 🔥 Master Problem Cheat Sheet

See **[00_Greedy_Master_Problem_CheatSheet.cpp](00_Greedy_Master_Problem_CheatSheet.cpp)** for all 120+ curated problems organized by pattern with links, difficulty, and key technique.

---

## 💡 How to Study This Module

1. **Read theory files first** (numbered `.cpp` files with detailed comments)
2. **Understand the proof** — WHY greedy works for each pattern
3. **Solve problems in order** — Easy → Medium → Hard → Expert → GM
4. **Track progress** in the cheat sheet (mark problems as solved)
5. **Revisit exchange arguments** — the #1 skill for proving greedy correctness

---

> *"Greedy is not about being greedy — it's about proving that being greedy is optimal."*

