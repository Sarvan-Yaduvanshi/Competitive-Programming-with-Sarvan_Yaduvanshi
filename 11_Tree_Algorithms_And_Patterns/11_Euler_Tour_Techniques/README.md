# Chapter 11 — Euler Tour Techniques

## 📋 Files

| # | File | Topic | Key Concepts |
|---|------|-------|-------------|
| 01 | `01_Euler_Tour_Flattening.cpp` | Flatten tree to array | tin/tout, DFS order, subtree = range |
| 02 | `02_Subtree_Queries_With_BIT.cpp` | Subtree queries using BIT | Point update + subtree sum via Euler tour |
| 03 | `03_Path_Queries_With_LCA.cpp` | Path queries | Prefix sums + LCA for path queries |

## 🎯 Key Insight
Euler tour converts subtree operations into RANGE operations on an array.
This lets us use Segment Tree / BIT for O(log N) queries!

