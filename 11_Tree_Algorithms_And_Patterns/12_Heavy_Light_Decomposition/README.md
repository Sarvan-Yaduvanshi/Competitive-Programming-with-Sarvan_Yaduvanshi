# Chapter 12 — Heavy-Light Decomposition (HLD)

## 📋 Files

| # | File | Topic | Key Concepts |
|---|------|-------|-------------|
| 01 | `01_HLD_Concept_And_Build.cpp` | HLD decomposition | Heavy/light edges, chain heads, position mapping |
| 02 | `02_HLD_Path_Queries.cpp` | Path queries with SegTree ⭐ | Sum/max on path, CSES Path Queries II |

## 🎯 HLD decomposes a tree into O(log N) chains.
Any path u→v crosses at most O(log N) chains.
Combined with segment tree → O(log²N) path queries!

## 💡 GM Tips
- Heavy child = child with largest subtree size
- Each chain = contiguous segment in position array → SegTree
- Always implement with segment tree for full power

