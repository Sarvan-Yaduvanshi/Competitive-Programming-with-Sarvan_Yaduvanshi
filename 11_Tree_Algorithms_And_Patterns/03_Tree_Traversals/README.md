# Chapter 03 — Tree Traversals

## 📋 Files

| # | File | Topic | Key Concepts |
|---|------|-------|-------------|
| 01 | `01_DFS_Recursive_And_Iterative.cpp` | DFS on Trees | Recursive & iterative DFS, preorder/postorder on general trees |
| 02 | `02_BFS_Level_Order_Traversal.cpp` | BFS / Level Order | Level grouping, zigzag, vertical order |
| 03 | `03_Preorder_Inorder_Postorder.cpp` | Binary Tree Traversals | All 3 orders, recursive + iterative |
| 04 | `04_Boundary_And_Vertical_Traversal.cpp` | Special Traversals | Boundary, vertical, diagonal |
| 05 | `05_DFS_Entry_Exit_Time.cpp` | DFS Timing | tin/tout arrays, subtree identification |
| 06 | `06_Tree_Diameter_Via_BFS_DFS.cpp` | Diameter | Two-BFS, DFS-based diameter |

## 🎯 Learning Goals
- Master DFS and BFS on trees
- Understand all binary tree traversal orders
- Implement both recursive and iterative versions
- Learn DFS timing (tin/tout) — foundation for Euler tour

## 💡 GM Tips
- DFS on tree: always pass parent to avoid revisiting → `dfs(v, parent)`
- BFS gives level-order automatically
- tin/tout arrays are the basis for Euler tour and subtree queries
- Diameter = longest path = foundation for many tree problems

