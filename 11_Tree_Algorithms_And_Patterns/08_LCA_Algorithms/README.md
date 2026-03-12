# Chapter 08 — LCA Algorithms

## 📋 Files

| # | File | Topic | Complexity |
|---|------|-------|-----------|
| 01 | `01_LCA_Naive.cpp` | Naive LCA (climb to same depth) | O(N) per query |
| 02 | `02_LCA_Binary_Lifting.cpp` | Binary Lifting LCA ⭐ | O(N log N) build, O(log N) query |
| 03 | `03_LCA_Euler_Tour_Sparse_Table.cpp` | Euler Tour + RMQ | O(N log N) build, O(1) query |
| 04 | `04_LCA_Tarjan_Offline.cpp` | Tarjan Offline LCA | O(N α(N)) total |

## 🎯 THIS IS THE MOST IMPORTANT CHAPTER FOR CP!
- Binary Lifting LCA is used in 50%+ of tree contest problems
- Learn it perfectly — it's the foundation for path queries, distance, etc.

## 💡 GM Tips
- Binary Lifting: up[v][k] = 2^k-th ancestor of v
- Always use LOG = 20 for N ≤ 2×10^5, LOG = 25 for N ≤ 10^7
- LCA(u,v) → distance, path queries, Kth ancestor

