# 🌳 Chapter 11 — Tree Algorithms & Patterns
## Zero to GM Level | ICPC Complete Guide

> **"Trees are the most important data structure in competitive programming.  
> Master trees, master CP."** — Every Red Coder Ever

---

## 📚 COMPLETE ROADMAP (17 Sub-Chapters)

### 🟢 BEGINNER (Foundations)
| # | Chapter | Files | Topics |
|---|---------|-------|--------|
| 01 | [Tree Foundations](01_Tree_Foundations/) | 7 | What is a tree, terminology, types, properties, rooting, input patterns |
| 02 | [Tree Representations](02_Tree_Representations/) | 5 | Adj list, parent array, edge list, array BT, node struct |
| 03 | [Tree Traversals](03_Tree_Traversals/) | 6 | DFS, BFS, preorder/inorder/postorder, zigzag, boundary, tin/tout, diameter |
| 04 | [Binary Tree Problems](04_Binary_Tree_Problems/) | 5 | Depth, diameter, path sum, symmetric, construct from traversals |
| 05 | [Binary Search Tree](05_Binary_Search_Tree/) | 5 | Insert/delete/search, validate, floor/ceil/kth, sorted→BST, BST iterator |

### 🟡 INTERMEDIATE (Path Problems & Construction)
| # | Chapter | Files | Topics |
|---|---------|-------|--------|
| 06 | [Tree Path Problems](06_Tree_Path_Problems/) | 3 | Root-to-node path, distance via LCA, K-distance nodes |
| 07 | [Tree Construction](07_Tree_Construction/) | 2 | Prüfer sequence, BST from preorder, tree from level order |

### 🔴 ADVANCED (The Core of CP)
| # | Chapter | Files | Topics |
|---|---------|-------|--------|
| 08 | [LCA Algorithms](08_LCA_Algorithms/) | 4 | Naive LCA, **Binary Lifting** ⭐, Euler Tour+RMQ O(1), **Tarjan Offline** |
| 09 | [Binary Lifting](09_Binary_Lifting/) | 2 | Kth ancestor, weighted path queries (min/max on path) |
| 10 | [Tree DP](10_Tree_DP/) | 6 | Subtree DP, diameter, **Rerooting** ⭐, independent set/matching, **vertex cover/coloring**, **DP on edges** |
| 11 | [Euler Tour](11_Euler_Tour_Techniques/) | 3 | Flatten tree→array, subtree queries with BIT, path queries |
| 12 | [Heavy-Light Decomposition](12_Heavy_Light_Decomposition/) | 2 | HLD build, **path queries + SegTree** ⭐ |
| 13 | [Centroid Decomposition](13_Centroid_Decomposition/) | 2 | Centroid finding, decomposition, count paths of length K |

### ⚫ EXPERT (ICPC / World Finals)
| # | Chapter | Files | Topics |
|---|---------|-------|--------|
| 14 | [Advanced Queries](14_Advanced_Tree_Queries/) | 3 | Combined subtree+path queries, Kth node on path, **offline tree queries** |
| 15 | [Special Trees](15_Special_Trees/) | 3 | Trie (string + XOR), Cartesian tree, **Fenwick tree structure** |
| 16 | [Advanced Techniques](16_Advanced_Tree_Techniques/) | 5 | **DSU on Tree** ⭐, Tree Hashing, **Virtual Tree**, **Mo on Tree**, **Persistent SegTree** |
| 17 | [ICPC Level](17_ICPC_Level_Tree_Algorithms/) | 3 | **Link-Cut Tree**, Euler Tour Tree, **Dynamic Connectivity** |

---

## 🎯 MUST-KNOW for Different Levels

### Specialist (1400+)
- [x] Tree DFS/BFS traversals
- [x] Subtree size computation
- [x] Tree diameter (two-BFS)
- [x] Basic path problems

### Expert (1600+)
- [x] Binary Lifting LCA
- [x] Euler Tour (tin/tout)
- [x] Basic Tree DP
- [x] Distance queries

### Candidate Master (1900+)
- [x] Rerooting DP
- [x] Euler Tour + BIT/SegTree
- [x] Centroid Decomposition
- [x] DSU on Tree

### Master (2100+)
- [x] HLD + Segment Tree
- [x] Advanced Tree DP
- [x] Tree Hashing
- [x] All LCA variants

### Grandmaster (2400+)
- [x] Link-Cut Trees
- [x] Virtual Tree
- [x] Persistent SegTree on Tree
- [x] All techniques combined

---

## 📊 CSES Problem Mapping

| CSES Problem | Chapter | Technique |
|-------------|---------|-----------|
| Subordinates | 10 | Subtree DP |
| Tree Matching | 10 | Max Matching DP |
| Tree Diameter | 03/10 | Two-BFS or DP |
| Tree Distances I | 10 | Rerooting (max dist) |
| Tree Distances II | 10 | Rerooting (sum dist) |
| Company Queries I | 09 | Kth Ancestor |
| Company Queries II | 08 | LCA Binary Lifting |
| Distance Queries | 08 | dist = dep[u]+dep[v]-2·dep[LCA] |
| Subtree Queries | 11 | Euler Tour + BIT |
| Path Queries | 14 | Euler Tour + LCA + BIT |
| Path Queries II | 12 | HLD + SegTree |
| Distinct Colors | 16 | DSU on Tree |

---

## 🏗️ Study Order (Recommended)

```
Week 1: Chapters 01-03 (Foundations, Representations, Traversals)
Week 2: Chapters 04-05 (Binary Tree Problems, BST)
Week 3: Chapters 06-08 (Path Problems, LCA ⭐)
Week 4: Chapters 09-10 (Binary Lifting, Tree DP ⭐)
Week 5: Chapters 11-12 (Euler Tour, HLD ⭐)
Week 6: Chapters 13-14 (Centroid Decomp, Advanced Queries)
Week 7: Chapters 15-17 (Special Trees, ICPC Level)
```

**Total: 66 .cpp files + 19 READMEs = 85 files | All with dry runs, ASCII visualizations, and working code!**
