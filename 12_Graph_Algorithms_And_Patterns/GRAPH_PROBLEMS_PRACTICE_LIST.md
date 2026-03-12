# 📋 Graph Problems Practice List
## 200+ Curated Problems — LeetCode, CSES, Codeforces, CodeChef

> *"Solving problems without understanding theory is gambling. Understanding theory without solving problems is dreaming."*

---

## 🟢 BEGINNER — BFS / DFS / Basic Traversal

### LeetCode
| # | Problem | Topic | Difficulty |
|---|---------|-------|------------|
| 200 | Number of Islands | DFS/BFS, Connected Components | Medium |
| 733 | Flood Fill | DFS/BFS | Easy |
| 695 | Max Area of Island | DFS | Medium |
| 463 | Island Perimeter | Grid Traversal | Easy |
| 994 | Rotting Oranges | Multi-source BFS | Medium |
| 542 | 01 Matrix | Multi-source BFS | Medium |
| 1091 | Shortest Path in Binary Matrix | BFS | Medium |
| 797 | All Paths From Source to Target | DFS/Backtracking | Medium |
| 841 | Keys and Rooms | DFS | Medium |
| 547 | Number of Provinces | DFS/DSU, Connected Components | Medium |
| 1971 | Find if Path Exists in Graph | BFS/DFS/DSU | Easy |
| 1306 | Jump Game III | BFS | Medium |
| of | Clone Graph (133) | BFS/DFS | Medium |

### CSES
| Problem | Topic |
|---------|-------|
| Counting Rooms | Connected Components, Grid DFS |
| Labyrinth | Grid BFS, Path Reconstruction |
| Building Roads | Connected Components |
| Message Route | BFS Shortest Path |
| Building Teams | Bipartite Check |
| Round Trip | Cycle Detection (Undirected) |
| Round Trip II | Cycle Detection (Directed) |

### Codeforces
| Problem | Topic | Rating |
|---------|-------|--------|
| 580C — Kefa and Park | Tree DFS | 1500 |
| 115A — Party | DFS, Tree Depth | 900 |
| 1037D — Valid BFS? | BFS Simulation | 1700 |
| 1037E — Trips | Offline Graph | 1900 |
| 520B — Two Buttons | BFS | 1400 |
| 1176E — Cover it! | Bipartite BFS | 1700 |
| 1272D — Remove One Element | DP + Graph | 1500 |

---

## 🟡 EASY-MEDIUM — Shortest Path / Topological Sort / MST

### LeetCode
| # | Problem | Topic | Difficulty |
|---|---------|-------|------------|
| 207 | Course Schedule | Topological Sort | Medium |
| 210 | Course Schedule II | Topological Sort | Medium |
| 743 | Network Delay Time | Dijkstra | Medium |
| 787 | Cheapest Flights Within K Stops | Bellman-Ford / BFS | Medium |
| 1584 | Min Cost to Connect All Points | MST (Prim/Kruskal) | Medium |
| 1514 | Path with Maximum Probability | Modified Dijkstra | Medium |
| 802 | Find Eventual Safe States | Cycle Detection, Topo Sort | Medium |
| 1631 | Path With Minimum Effort | Binary Search + BFS / Dijkstra | Medium |
| 1168 | Optimize Water Distribution | MST | Hard |
| 778 | Swim in Rising Water | Binary Search + BFS / Dijkstra | Hard |
| 1368 | Minimum Cost to Make at Least One Valid Path | 0-1 BFS | Hard |
| 882 | Reachable Nodes In Subdivided Graph | Dijkstra | Hard |
| 1334 | Find the City With Smallest Number of Neighbors | Floyd-Warshall | Medium |
| 399 | Evaluate Division | Weighted Graph BFS | Medium |
| 684 | Redundant Connection | DSU / Cycle Detection | Medium |
| 685 | Redundant Connection II | Directed Graph + DSU | Hard |
| 1489 | Find Critical and Pseudo-Critical Edges in MST | MST + Enumeration | Hard |

### CSES
| Problem | Topic |
|---------|-------|
| Shortest Routes I | Dijkstra |
| Shortest Routes II | Floyd-Warshall |
| High Score | Longest Path (Bellman-Ford) |
| Flight Discount | Dijkstra on State Graph |
| Cycle Finding | Bellman-Ford Negative Cycle |
| Course Schedule | Topological Sort |
| Longest Flight Route | DP on DAG |
| Game Routes | Path Counting on DAG |
| Investigation | Dijkstra + Counting |
| Road Reparation | MST (Kruskal) |

### Codeforces
| Problem | Topic | Rating |
|---------|-------|--------|
| 20C — Dijkstra? | Dijkstra | 1900 |
| 545E — Paths and Trees | Dijkstra + MST | 2000 |
| 1005F — Berland and the Shortest Paths | Dijkstra + BFS Tree | 2100 |
| 449B — Jzzhu and Cities | Dijkstra | 2000 |
| 1076D — Edge Deletion | Dijkstra + Shortest Path Tree | 1800 |
| 1325E — Ehab's TORTURE | DSU + Greedy | 2000 |
| 1153D — Serval and Rooted Tree | DFS + DP | 1900 |
| 1213G — Path Queries | DSU + Sorting | 1800 |

### CodeChef
| Problem | Topic |
|---------|-------|
| FIRESC | Connected Components |
| REVERSE | 0-1 BFS |
| DIGJUMP | BFS |
| COLTREE | Tree Coloring |

---

## 🟠 ADVANCED — SCC / Bridges / DSU / Euler

### LeetCode
| # | Problem | Topic | Difficulty |
|---|---------|-------|------------|
| 1192 | Critical Connections in a Network | **Bridges (Tarjan)** | Hard |
| 332 | Reconstruct Itinerary | **Euler Path (Hierholzer)** | Hard |
| 928 | Minimize Malware Spread II | **DSU + Articulation** | Hard |
| 721 | Accounts Merge | **DSU** | Medium |
| 959 | Regions Cut By Slashes | **DSU on Grid** | Medium |
| 990 | Satisfiability of Equality Equations | **DSU** | Medium |
| 1319 | Number of Operations to Make Network Connected | **DSU** | Medium |
| 952 | Largest Component Size by Common Factor | **DSU + Primes** | Hard |
| 1579 | Remove Max Number of Edges | **DSU** | Hard |
| 765 | Couples Holding Hands | **DSU / Cycle** | Hard |

### CSES
| Problem | Topic |
|---------|-------|
| Flight Routes Check | SCC / Reachability |
| Planets and Kingdoms | **SCC (Kosaraju/Tarjan)** |
| Coin Collector | **SCC Condensation + DP** |
| Mail Delivery | **Euler Circuit** |
| De Bruijn Sequence | **Euler Path** |
| Teleporters Path | **Euler Path (Directed)** |
| Road Construction | **DSU Online** |
| New Roads Queries | **DSU + LCA** |

### Codeforces
| Problem | Topic | Rating |
|---------|-------|--------|
| 427C — Checkposts | **SCC** | 1700 |
| 505B — Mr. Kitayuta's Colorful Graph | **DSU per Color** | 1600 |
| 1249F — Maximum Weight Subset | Tree DP | 2200 |
| 1141F — Same Sum Blocks | DSU / Segments | 1600 |
| 118E — Bertown roads | **Bridges** | 2000 |
| 732F — Tourist Reform | **Bridges + DFS** | 2300 |
| 652E — Pursuit For Artifacts | **Bridge Tree** | 2300 |
| 1702F — Equate Multisets | DSU / Multiset | 1900 |

---

## 🔴 HARD — Flow / Matching / Graph DP

### LeetCode
| # | Problem | Topic | Difficulty |
|---|---------|-------|------------|
| 1349 | Maximum Students Taking Exam | **Bitmask DP / Matching** | Hard |
| 943 | Find the Shortest Superstring | **Bitmask DP (TSP-like)** | Hard |
| 847 | Shortest Path Visiting All Nodes | **Bitmask BFS** | Hard |
| 1494 | Parallel Courses II | **Bitmask DP + Topo** | Hard |
| 1125 | Smallest Sufficient Team | **Bitmask DP** | Hard |
| 1066 | Campus Bikes II | **Hungarian / Bitmask DP** | Medium |
| 1595 | Minimum Cost to Connect Two Groups | **Bitmask DP** | Hard |
| 1857 | Largest Color Value in a Directed Graph | **Topo Sort + DP** | Hard |

### CSES
| Problem | Topic |
|---------|-------|
| Hamiltonian Flights | **Bitmask DP** |
| Knight's Tour | **Backtracking / Warnsdorff** |
| Download Speed | **Max Flow (Dinic)** |
| Police Chase | **Min Cut** |
| School Dance | **Bipartite Matching** |
| Distinct Routes | **Max Flow (edge-disjoint paths)** |

### Codeforces
| Problem | Topic | Rating |
|---------|-------|--------|
| 498C — Array and Operations | **Max Flow / Matching** | 2100 |
| 653D — Delivery Bears | **Binary Search + Max Flow** | 2200 |
| 653E — Bear and Forgotten Tree 2 | **LCA + Flow** | 2400 |
| 1355F — Guess Divisors Count | **Bitmask** | 2300 |
| 1592F1 — Alice and Recoloring 1 | **Graph DP** | 2200 |
| 1363F — Rotating Substrings | **DP** | 2300 |

### CodeChef
| Problem | Topic |
|---------|-------|
| HAMILG | Hamiltonian Path |
| MAXMATCH | Maximum Matching |
| FLOODED | Max Flow |

---

## 🏆 ICPC / GRANDMASTER LEVEL

### CSES (Advanced)
| Problem | Topic |
|---------|-------|
| Planets Queries I | **Functional Graph + Binary Lifting** |
| Planets Queries II | **Functional Graph + LCA** |
| Planets Cycles | **Functional Graph Cycle** |
| Road Construction | **Dynamic Connectivity** |

### Codeforces (2400+)
| Problem | Topic | Rating |
|---------|-------|--------|
| 1284D — New Year and Conference | **Offline + DSU** | 2400 |
| 786B — Legacy | **Segment Tree + Dijkstra** | 2300 |
| 757F — Team Formation | **Bitmask + Matching** | 2800 |
| 100551A — Connecting Universities | **Tree Centroid** | 2200 |
| 504E — Misha and LCP on Tree | **HLD + SA** | 2800 |
| 1361E — James and the Chase | **DFS Tree + SCC** | 2600 |
| 464E — The Classic Problem | **Dijkstra + Big Numbers** | 3000 |

### Classic ICPC Problems
| Problem | Topic |
|---------|-------|
| UVa 820 — Internet Bandwidth | Max Flow |
| UVa 10801 — Lift Hopping | Multi-layer Dijkstra |
| UVa 11380 — Down Went The Titanic | Vertex-split Flow |
| SPOJ MATCHING | Bipartite Matching |
| SPOJ SHPATH | Dijkstra |
| SPOJ BITMAP | Multi-source BFS |
| POJ 1273 — Drainage Ditches | Max Flow (classic) |
| POJ 3041 — Asteroids | Min Vertex Cover = Max Matching |
| POJ 2195 — Going Home | Min Cost Max Flow |
| POJ 3281 — Dining | Network Flow with Vertex Split |

---

## 📊 Topic-Wise Problem Count Summary

| Topic | Easy | Medium | Hard | ICPC | Total |
|-------|------|--------|------|------|-------|
| BFS/DFS/Traversal | 8 | 12 | 3 | 2 | **25** |
| Shortest Path (Dijkstra/BF/FW) | 2 | 10 | 5 | 3 | **20** |
| Topological Sort | 1 | 5 | 3 | 1 | **10** |
| DSU (Union-Find) | 2 | 8 | 5 | 2 | **17** |
| MST (Kruskal/Prim) | 0 | 3 | 3 | 1 | **7** |
| SCC / Bridges / AP | 0 | 3 | 5 | 3 | **11** |
| Euler Path/Circuit | 0 | 1 | 2 | 2 | **5** |
| Network Flow | 0 | 0 | 5 | 8 | **13** |
| Bipartite Matching | 0 | 1 | 3 | 4 | **8** |
| Graph DP / Bitmask | 0 | 2 | 8 | 3 | **13** |
| 0-1 BFS / State Graph | 0 | 3 | 3 | 2 | **8** |
| LCA / Centroid / Tree | 0 | 2 | 4 | 5 | **11** |
| Functional Graph | 0 | 1 | 2 | 3 | **6** |
| **TOTAL** | | | | | **~154** |

---

## 🎯 Recommended Solving Order

```
PHASE 1 (Foundation):     CSES Graph Section (first 10 problems)
PHASE 2 (Core):           LeetCode Easy/Medium graph problems (30 problems)
PHASE 3 (Intermediate):   CSES remaining + CF 1500-1900 (25 problems)
PHASE 4 (Advanced):       LeetCode Hard + CF 2000-2200 (20 problems)
PHASE 5 (Expert):         CSES Advanced + CF 2300+ + ICPC archives (20 problems)
```

---

## 🔗 Practice Links

- **CSES Graph Section**: https://cses.fi/problemset/list/
- **LeetCode Graph Tag**: https://leetcode.com/tag/graph/
- **CF Graph Tag**: https://codeforces.com/problemset?tags=graphs
- **CF DFS/BFS Tag**: https://codeforces.com/problemset?tags=dfs+and+similar
- **CF Shortest Path**: https://codeforces.com/problemset?tags=shortest+paths
- **CF Flow**: https://codeforces.com/problemset?tags=flows
- **SPOJ Classical**: https://www.spoj.com/problems/classical/

---

> *"The best time to start practicing graphs was yesterday. The second best time is now."* 🚀

*Created for Competitive Programming with Sarvan Yaduvanshi*

