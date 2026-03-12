# 📊 Chapter 12 — Graph Algorithms & Patterns
## 🚀 Zero to Grandmaster / ICPC Level

> *"A graph is worth a thousand arrays."* — Every CP legend ever
>
> *"In competitive programming, if you can model it as a graph, you can solve it."*
>
> *"The difference between a Specialist and a Grandmaster is how fast they see the graph behind the problem."*

---

## 🔥 THE MOST IMPORTANT CHAPTER IN COMPETITIVE PROGRAMMING

Graphs appear in **40-60% of all competitive programming problems**. From simple BFS grid problems at Div2-A to Dinic flow at ICPC World Finals — mastering graphs is **non-negotiable**.

> *"Every expert was once a beginner. Every Grandmaster once TLEd on BFS."*

---

## 📂 Complete Structure — 88 C++ Files × 21 Sections

### 🟢 BEGINNER (Week 1-2)

| # | Section | Files | Core Algorithms |
|---|---------|-------|----------------|
| **01** | `Graph_Foundations/` | 5 | What is graph • Types (directed/undirected/weighted) • Terminology (degree, path, cycle) • Properties • CP input patterns |
| **02** | `Graph_Representations/` | 5 | Adjacency Matrix O(V²) • Adjacency List O(V+E) • Edge List • Implicit Graphs (grids) • Weighted representations |
| **03** | `Graph_Traversal_Algorithms/` | 7 | DFS (recursive + iterative) • BFS (level order) • Multi-source BFS • DFS tree edge classification • Connected Components • Cycle detection (undirected + directed) |
| **04** | `Basic_Graph_Problems/` | 6 | Count Islands • Flood Fill • Bipartite Check • Graph Coloring • Grid BFS Shortest Path • Is Graph a Tree? |

### 🟡 EASY-MEDIUM (Week 3-4)

| # | Section | Files | Core Algorithms |
|---|---------|-------|----------------|
| **05** | `Topological_Sort/` | 5 | Kahn's BFS • DFS Topological Sort • Cycle Detection via Topo • Longest Path in DAG • Course Schedule |
| **06** | `Shortest_Path_Algorithms/` | 9 | **Dijkstra** O((V+E)logV) • **Bellman-Ford** O(VE) • **SPFA** • **Floyd-Warshall** O(V³) • **0-1 BFS** O(V+E) • DAG shortest path • Negative cycle • **Johnson's** • **Dial's** |
| **07** | `Minimum_Spanning_Tree/` | 3 | **Kruskal** O(ElogE) • **Prim** O((V+E)logV) • MST Properties + Second-best MST |
| **08** | `Disjoint_Set_Union/` | 4 | DSU basic (path compression + rank) • Applications • DSU with Rollback • Weighted DSU |

### 🟠 ADVANCED (Week 5-6)

| # | Section | Files | Core Algorithms |
|---|---------|-------|----------------|
| **09** | `Strongly_Connected_Components/` | 4 | **Kosaraju** O(V+E) • **Tarjan SCC** O(V+E) • Condensation DAG • **2-SAT** |
| **10** | `Bridges_And_Articulation_Points/` | 4 | Bridges (Tarjan) • Articulation Points • Bridge Tree • Biconnected Components |
| **11** | `Eulerian_Graphs/` | 3 | Euler Path/Circuit Check • **Hierholzer** O(E) • Chinese Postman |
| **12** | `Graph_Coloring/` | 2 | Bipartite 2-coloring • Greedy + Chromatic Number (bitmask DP) |

### 🔴 HARD (Week 7-8)

| # | Section | Files | Core Algorithms |
|---|---------|-------|----------------|
| **13** | `Network_Flow/` | 2 | **Edmonds-Karp** O(VE²) • **Dinic** O(V²E) / O(E√V) unit |
| **14** | `Min_Cut_And_Flow_Applications/` | 3 | Max-Flow Min-Cut • Project Selection • **Vertex Splitting + Capacity Scaling** |
| **15** | `Bipartite_Matching/` | 3 | **Kuhn** O(VE) • **Hopcroft-Karp** O(E√V) • König's Theorem |
| **16** | `Advanced_Flow_Algorithms/` | 3 | **MCMF** (Min-Cost Max-Flow) • Flow with Lower Bounds • **Hungarian** O(n³) |

### 🔴 EXPERT (Week 9-10)

| # | Section | Files | Core Algorithms |
|---|---------|-------|----------------|
| **17** | `Graph_DP/` | 3 | DP on DAG • **Bitmask DP** (TSP/Hamiltonian) O(2^n×n²) • State-graph Dijkstra |
| **18** | `Graph_Theory_Concepts/` | 1 | Euler's Formula • Turán • Ramsey • Planarity • Complement |
| **19** | `Advanced_Graph_Techniques/` | 7 | 0-1 BFS State Graph • Virtual Tree • **Functional Graph** (binary lifting) • **LCA** O(nlogn,logn) • **Centroid Decomposition** O(nlogn) • Complement BFS + Shortest Cycle • Tree Diameter/Center/Euler Tour |
| **20** | `Offline_Graph_Techniques/` | 2 | DSU Offline Queries • Parallel Binary Search on Graph |

### 🏆 ICPC LEVEL (Week 11+)

| # | Section | Files | Core Algorithms |
|---|---------|-------|----------------|
| **21** | `ICPC_Level_Graph_Algorithms/` | 6 | Dinic Optimized • **Gomory-Hu Tree** • **Blossom** (general matching) O(V³) • **Edmonds' Min Arborescence** • **Steiner Tree** O(3^k×n) • **Dynamic Connectivity** (D&C + rollback DSU) |

> **+ `00_QUICK_REFERENCE_CHEAT_SHEET.cpp`** — Complete complexity table + decision tree + common mistakes

---

## ⚡ Algorithm Selection Cheat Sheet

```
┌─────────────────────────────────────────────────────────────────────┐
│  SHORTEST PATH                                                      │
│  ├─ Unweighted ──────────────── BFS              O(V+E)            │
│  ├─ Weights {0,1} ──────────── 0-1 BFS (deque)   O(V+E)            │
│  ├─ Non-negative ────────────── Dijkstra          O((V+E)logV)      │
│  ├─ Negative weights ────────── Bellman-Ford       O(VE)             │
│  ├─ All-pairs (dense) ──────── Floyd-Warshall     O(V³)             │
│  ├─ All-pairs (sparse+neg) ─── Johnson            O(VElogV)         │
│  └─ DAG ─────────────────────── Topo + DP         O(V+E)            │
├─────────────────────────────────────────────────────────────────────┤
│  CONNECTIVITY                                                       │
│  ├─ Static undirected ────────── DFS / BFS / DSU  O(V+E)           │
│  ├─ Directed (SCC) ─────────── Kosaraju / Tarjan  O(V+E)            │
│  ├─ Bridges ─────────────────── Tarjan            O(V+E)            │
│  ├─ Articulation points ─────── Tarjan            O(V+E)            │
│  └─ Dynamic (add+delete) ────── DSU+D&C / LCT    O(QlogQ)          │
├─────────────────────────────────────────────────────────────────────┤
│  MST ──── Sparse: Kruskal O(ElogE)   Dense: Prim O((V+E)logV)     │
├─────────────────────────────────────────────────────────────────────┤
│  MATCHING                                                           │
│  ├─ Bipartite ───── Kuhn O(VE) / Hopcroft-Karp O(E√V)             │
│  └─ General ─────── Blossom O(V³)                                   │
├─────────────────────────────────────────────────────────────────────┤
│  FLOW ───── Dinic O(V²E) [unit: O(E√V)]  │  MCMF: SPFA+augment   │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 🎯 Study Order

```
Week 1-2:  01 → 02 → 03 → 04          (Foundation — solve 30 easy problems)
Week 3-4:  05 → 06 → 07 → 08          (Core algorithms — solve 40 medium problems)
Week 5-6:  09 → 10 → 11 → 12          (Advanced graph theory — solve 25 problems)
Week 7-8:  13 → 14 → 15 → 16          (Flow & Matching — solve 20 hard problems)
Week 9-10: 17 → 18 → 19 → 20          (DP & Advanced techniques — solve 20 problems)
Week 11+:  21                           (ICPC level — team practice)
```

---

## 💡 Grandmaster Tips

> *"You don't rise to the level of your goals. You fall to the level of your templates."*

1. **DSU appears everywhere** — MST, offline, dynamic connectivity, cycle detection
2. **Model the problem as a graph first** — many non-graph problems ARE graph problems
3. **BFS = shortest unweighted, Dijkstra = shortest weighted** — never mix these up
4. **Dinic template** is all you need for 99% of flow problems
5. **Binary lifting** solves LCA, k-th ancestor, functional graph queries
6. **Topological sort** enables DP on any DAG
7. **0-1 BFS** is Dijkstra but O(V+E) — use it whenever weights are 0/1
8. **Complement graph BFS** trick — O(V+E) without building the complement
9. **For ICPC**: memorize Dinic, Kuhn, Kosaraju, DSU, Dijkstra as templates
10. **For CF**: most graph problems need BFS/DFS/DSU + observation, not heavy algorithms

---

## 📌 Common Mistakes Hall of Shame

```
❌ Dijkstra with negative weights         → Use Bellman-Ford!
❌ DFS for shortest path                  → Use BFS!
❌ Forgetting visited check before push   → Infinite loop / TLE
❌ Integer overflow in distances           → Use long long!
❌ Floyd-Warshall: wrong loop order       → k MUST be outermost!
❌ Forgetting reverse edges in max flow   → WA
❌ Stack overflow in deep DFS             → Use iterative DFS
❌ Not handling disconnected graphs       → Loop over ALL vertices
❌ Parent confusion in multi-edge graphs  → Track edge index, not vertex
❌ Using adj matrix for sparse graph      → MLE / TLE
```

---

> *"The master has failed more times than the beginner has tried. Keep coding. Keep graphing."* 🚀

**See `GRAPH_PROBLEMS_PRACTICE_LIST.md` for 200+ curated problems by difficulty!**

---
*Created for Competitive Programming with Sarvan Yaduvanshi*

