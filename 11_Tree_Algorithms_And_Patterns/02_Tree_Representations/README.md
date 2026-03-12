# Chapter 02 — Tree Representations

## 📋 Files

| # | File | Topic | Key Concepts |
|---|------|-------|-------------|
| 01 | `01_Adjacency_List_Representation.cpp` | Adjacency List | vector<vector<int>>, weighted, unweighted |
| 02 | `02_Parent_Array_Representation.cpp` | Parent Array | par[i], convert to/from adj list |
| 03 | `03_Edge_List_Representation.cpp` | Edge List | Store edges, edge indexing |
| 04 | `04_Binary_Tree_Array_Representation.cpp` | Array-Based BT | 1-indexed: 2*i, 2*i+1, segment tree layout |
| 05 | `05_Binary_Tree_Node_Structure.cpp` | Node Pointers | Left/right child pointers, struct TreeNode |

## 🎯 Learning Goals
- Master all tree representation techniques
- Know which representation to use for which problem
- Convert between representations efficiently

## 💡 GM Tips
- Adjacency list is the DEFAULT for CP — always use `vector<vector<int>>`
- Array representation is used for segment trees and binary heaps
- Edge list is useful when you need to iterate over edges (Kruskal's, etc.)

