# Module 07: Greedy on Graphs

> **Level:** ⭐⭐⭐ Advanced  
> **Prerequisites:** Graphs, DSU (Union-Find), Priority Queue

## Concepts Covered

| # | File | Topic | Difficulty |
|---|------|-------|-----------|
| 1 | `01_Kruskals_MST.cpp` | Kruskal's MST with DSU, proof of correctness | Advanced |
| 2 | `02_Prims_MST.cpp` | Prim's MST with Priority Queue | Advanced |
| 3 | `03_Dijkstras_Shortest_Path.cpp` | Dijkstra's algorithm (greedy + relaxation) | Advanced |
| 4 | `04_Boruvkas_MST.cpp` | Borůvka's MST (component-merge) | Advanced |
| 5 | `05_Reverse_Delete_MST.cpp` | Reverse greedy for MST | Advanced |

## Key Insight
Graph greedy algorithms are among the most important in CS:
- **Kruskal**: Sort edges by weight, add if no cycle (DSU)
- **Prim**: Grow MST from a vertex, always add cheapest edge to tree
- **Dijkstra**: Process nearest unvisited vertex, relax edges
- All three are **provably optimal** using cut property / exchange arguments

