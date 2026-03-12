/*
╔══════════════════════════════════════════════════════════════════════════╗
║                   GRAPH ALGORITHMS — QUICK REFERENCE                    ║
║             Complete CP/ICPC Cheat Sheet with Template Code             ║
╚══════════════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════════════
1. COMPLEXITY TABLE
═══════════════════════════════════════════════════════════════════════════

┌────────────────────────────────┬────────────────┬──────────────┐
│  Algorithm                     │  Time           │  Space       │
├────────────────────────────────┼────────────────┼──────────────┤
│  BFS / DFS                     │  O(V+E)         │  O(V)        │
│  Multi-source BFS              │  O(V+E)         │  O(V)        │
│  0-1 BFS (deque)               │  O(V+E)         │  O(V)        │
│  Kahn's Topo Sort              │  O(V+E)         │  O(V+E)      │
│  Dijkstra (binary heap)        │  O((V+E)logV)   │  O(V+E)      │
│  Bellman-Ford                  │  O(VE)          │  O(V)        │
│  SPFA (avg)                    │  O(E) avg       │  O(V+E)      │
│  Floyd-Warshall                │  O(V³)          │  O(V²)       │
│  Kruskal (MST)                 │  O(ElogE)       │  O(V+E)      │
│  Prim (MST)                    │  O((V+E)logV)   │  O(V+E)      │
│  DSU (path comp + rank)        │  O(α(V))≈O(1)   │  O(V)        │
│  Kosaraju (SCC)                │  O(V+E)         │  O(V+E)      │
│  Tarjan (SCC/Bridges/AP)       │  O(V+E)         │  O(V+E)      │
│  Kuhn (matching)               │  O(VE)          │  O(V+E)      │
│  Hopcroft-Karp                 │  O(E√V)         │  O(V+E)      │
│  Edmonds-Karp (max flow)       │  O(VE²)         │  O(V+E)      │
│  Dinic (max flow)              │  O(V²E)         │  O(V+E)      │
│  Dinic (unit cap)              │  O(E√V)         │  O(V+E)      │
│  TSP (bitmask DP)              │  O(2^n × n²)    │  O(2^n × n)  │
│  Steiner Tree                  │  O(3^k×n+2^k...)│  O(2^k × n)  │
│  Blossom                       │  O(V³)          │  O(V²)       │
└────────────────────────────────┴────────────────┴──────────────┘

═══════════════════════════════════════════════════════════════════════════
2. DECISION TREE — WHICH ALGORITHM TO USE?
═══════════════════════════════════════════════════════════════════════════

SHORTEST PATH:
  ├─ Unweighted? → BFS
  ├─ Weights {0,1}? → 0-1 BFS (deque)
  ├─ All non-negative? → Dijkstra
  ├─ Negative weights? → Bellman-Ford / SPFA
  ├─ All pairs? → Floyd-Warshall (V≤400)
  └─ DAG? → Topo sort + relax

CYCLE DETECTION:
  ├─ Undirected → DFS (parent check)
  └─ Directed → 3-color DFS or Kahn's topo sort

CONNECTIVITY:
  ├─ Static undirected → DFS/BFS or DSU
  ├─ Directed → SCC (Kosaraju/Tarjan)
  ├─ Bridge edges → Tarjan bridges
  └─ Cut vertices → Tarjan articulation points

MST: → Kruskal (usually) or Prim (dense)

MATCHING:
  ├─ Bipartite → Kuhn O(VE) or Hopcroft-Karp O(E√V)
  └─ General → Blossom O(V³)

FLOW:
  ├─ Max flow → Dinic
  ├─ Min cut → Dinic + BFS on residual
  └─ Min cost max flow → SPFA-based MCMF

═══════════════════════════════════════════════════════════════════════════
3. TEMPLATE SNIPPETS (Ready to copy-paste)
═══════════════════════════════════════════════════════════════════════════
*/

// ─── DSU ───
struct DSU {
    vector<int> p, r;
    DSU(int n):p(n),r(n,0){ iota(p.begin(),p.end(),0); }
    int find(int x){ while(p[x]!=x) x=p[x]=p[p[x]]; return x; }
    bool unite(int a,int b){
        a=find(a);b=find(b); if(a==b) return false;
        if(r[a]<r[b]) swap(a,b); p[b]=a; if(r[a]==r[b]) r[a]++;
        return true;
    }
};

// ─── DIJKSTRA ───
// vec<i64> dist(n, INF64); dist[src]=0;
// priority_queue<pll, vec<pll>, greater<pll>> pq; pq.push({0,src});
// while(!pq.empty()){ auto[d,u]=pq.top();pq.pop(); if(d>dist[u])continue;
//   for(auto[v,w]:adj[u]) if(dist[u]+w<dist[v]){ dist[v]=dist[u]+w; pq.push({dist[v],v}); } }

// ─── DINIC ───
// See 13_Network_Flow/02_Dinic_Algorithm.cpp for full template

/*
═══════════════════════════════════════════════════════════════════════════
4. COMMON MISTAKES IN GRAPH PROBLEMS
═══════════════════════════════════════════════════════════════════════════

❌ Using Dijkstra with negative weights → Use Bellman-Ford!
❌ Forgetting to mark visited BEFORE pushing to BFS queue → duplicates
❌ Using DFS for shortest path → Always use BFS for unweighted
❌ Not handling disconnected graphs → Always loop over all components
❌ Integer overflow in Dijkstra → Use long long for distances
❌ Not initializing dist to INF → Undefined behavior
❌ Stack overflow with large DFS → Use iterative DFS or increase stack
❌ Wrong parent check in undirected cycle detection with multi-edges
❌ Floyd-Warshall: wrong loop order (k MUST be outermost!)
❌ Forgetting reverse edges in max flow

═══════════════════════════════════════════════════════════════════════════
5. COMMON PROBLEM PATTERNS IN CF/ICPC
═══════════════════════════════════════════════════════════════════════════

PATTERN 1: "Can we reach X from Y?" → BFS/DFS connectivity
PATTERN 2: "Minimum steps/cost" → BFS (unweighted) / Dijkstra (weighted)
PATTERN 3: "Order of tasks" → Topological Sort
PATTERN 4: "Groups of connected things" → DSU / Connected Components
PATTERN 5: "Minimum cost to connect all" → MST (Kruskal/Prim)
PATTERN 6: "Is there a cycle?" → DFS cycle detection / Kahn's
PATTERN 7: "Assign 2 categories" → Bipartite check (2-coloring)
PATTERN 8: "Maximum pairings" → Bipartite matching
PATTERN 9: "Minimum bottleneck" → Binary search + BFS/DSU
PATTERN 10: "All-pairs distances" → Floyd-Warshall (small) / n × Dijkstra (large)

═══════════════════════════════════════════════════════════════════════════
*/

