/*
╔══════════════════════════════════════════════════════════════════════════════╗
║          DEPTH FIRST SEARCH (DFS) — ZERO TO GRANDMASTER GUIDE                ║
║          Author: Sarvan.DP.GrandMaster                                       ║
║          Created: 2026-03-07                                                 ║
╚══════════════════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════════════════
TABLE OF CONTENTS
═══════════════════════════════════════════════════════════════════════════════
  PART 0  → What is a Graph? (Prerequisite)
  PART 1  → What is DFS? (The Idea)
  PART 2  → DFS on Adjacency List — Recursive (Basic)
  PART 3  → Step-by-Step Dry Run with Visualization
  PART 4  → DFS on Adjacency List — Iterative (Using Stack)
  PART 5  → DFS Edge Classification (Tree / Back / Forward / Cross)
  PART 6  → DFS Timestamps — Discovery & Finish Time (tin/tout)
  PART 7  → Cycle Detection (Undirected & Directed Graph)
  PART 8  → Connected Components (Undirected Graph)
  PART 9  → Topological Sort using DFS
  PART 10 → DFS on Trees (Parent tracking, Subtree size, Depth)
  PART 11 → Finding Bridges & Articulation Points (Tarjan)
  PART 12 → Strongly Connected Components (Kosaraju & Tarjan)
  PART 13 → Bipartite Check using DFS
  PART 14 → DFS on Grid / 2D Matrix (Flood Fill, Island Count)
  PART 15 → Euler Path & Circuit using DFS
  PART 16 → DFS + Backtracking Patterns (Subsets, Permutations)
  PART 17 → Advanced: DFS Tree & Euler Tour (Flatten Tree)
  PART 18 → Time & Space Complexity Analysis
  PART 19 → Common Mistakes & Tips for CP
  PART 20 → Practice Problems (Codeforces, CSES, LeetCode)
═══════════════════════════════════════════════════════════════════════════════

═══════════════════════════════════════════════════════════════════════════════
PART 0: WHAT IS A GRAPH? (Prerequisite)
═══════════════════════════════════════════════════════════════════════════════

  A Graph G = (V, E) consists of:
    • V = set of vertices (nodes)         → {0, 1, 2, 3, 4}
    • E = set of edges (connections)      → {(0,1), (0,2), (1,3), ...}

  Types:
    ┌─────────────────────────────────────────────────────┐
    │  Undirected Graph:  edge (u,v) = edge (v,u)         │
    │  Directed Graph:    edge (u→v) ≠ edge (v→u)         │
    │  Weighted Graph:    each edge has a cost/weight     │
    │  Unweighted Graph:  all edges have equal weight     │
    │  Tree:              connected graph with N-1 edges  │
    │                     (no cycles)                     │
    └─────────────────────────────────────────────────────┘

  Representation — Adjacency List (most used in CP):

    Graph:
        0 ── 1
        |    |
        2 ── 3
             |
             4

    Adjacency List:
        adj[0] = {1, 2}
        adj[1] = {0, 3}
        adj[2] = {0, 3}
        adj[3] = {1, 2, 4}
        adj[4] = {3}

    Code to build:
        int n, m;  // n = nodes, m = edges
        cin >> n >> m;
        vector<vector<int>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);  // remove this for directed
        }

═══════════════════════════════════════════════════════════════════════════════
PART 1: WHAT IS DFS? (The Core Idea)
═══════════════════════════════════════════════════════════════════════════════

  DFS = Depth First Search

  🧠 Intuition:
    "Go as DEEP as possible before coming back."
    Like exploring a maze — you keep going forward until you hit a dead end,
    then you backtrack and try another path.

  Real-life analogy:
    Imagine you're in a maze. At every junction:
      1. Pick ONE path and walk forward.
      2. Keep going until dead-end.
      3. Come back to the last junction.
      4. Try the next path you haven't tried.
      5. Repeat until every path is explored.

  Algorithm (Pseudocode):
    ┌─────────────────────────────────────────┐
    │  DFS(node):                             │
    │    mark node as visited                 │
    │    for each neighbor of node:           │
    │      if neighbor is NOT visited:        │
    │        DFS(neighbor)                    │
    └─────────────────────────────────────────┘

  Key Properties:
    • Uses a STACK (recursion = implicit stack, or explicit stack)
    • Visits nodes in DEPTH-FIRST order
    • Time Complexity:  O(V + E)
    • Space Complexity: O(V) for visited array + O(V) recursion stack

═══════════════════════════════════════════════════════════════════════════════
PART 2: DFS — RECURSIVE IMPLEMENTATION (The Foundation)
═══════════════════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>
#include <functional>

using namespace std;

using i64 = long long;
using pii = pair<int, int>;
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

// ─────────────────────────────────────────────────────────────────────────────
// SECTION 2A: Simplest DFS — Recursive on Adjacency List
// ─────────────────────────────────────────────────────────────────────────────
/*
    Graph:
        0 ── 1
        |    |
        2 ── 3
             |
             4

    Input format:
        5 5        (n=5 nodes, m=5 edges)
        0 1
        0 2
        1 3
        2 3
        3 4

    Expected DFS from node 0:  0 → 1 → 3 → 2 → 4
    (order may vary based on adjacency list order)
*/

namespace BasicDFS {
    constexpr int MAXN = 1e5 + 5;
    vector<int> adj[MAXN];
    bool visited[MAXN];

    // ╔═══════════════════════════════════════════════════════╗
    // ║  THE CORE DFS FUNCTION — memorize this!               ║
    // ╠═══════════════════════════════════════════════════════╣
    // ║  Step 1: Mark current node as visited                 ║
    // ║  Step 2: Process the node (print, count, etc.)        ║
    // ║  Step 3: Visit all unvisited neighbors recursively    ║
    // ╚═══════════════════════════════════════════════════════╝
    void dfs(int node) {
        visited[node] = true;              // Step 1: Mark visited
        cout << node << " ";              // Step 2: Process (print)

        for (int neighbor : adj[node]) {  // Step 3: Visit neighbors
            if (!visited[neighbor]) {
                dfs(neighbor);             // Recursive call — go DEEPER
            }
        }
    }

    void run() {
        int n, m;
        cin >> n >> m;

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);  // undirected
        }

        cout << "DFS Traversal: ";
        dfs(0);  // start from node 0
        cout << nl;
    }
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 3: STEP-BY-STEP DRY RUN WITH VISUALIZATION
═══════════════════════════════════════════════════════════════════════════════

  Graph:
        0 ── 1
        |    |
        2 ── 3
             |
             4

  adj[0] = {1, 2}
  adj[1] = {0, 3}
  adj[2] = {0, 3}
  adj[3] = {1, 2, 4}
  adj[4] = {3}

  Starting DFS from node 0:

  ┌─────────────────────────────────────────────────────────────────────────┐
  │ CALL STACK           │ ACTION                  │ VISITED                │
  ├─────────────────────────────────────────────────────────────────────────┤
  │ dfs(0)               │ Visit 0, print "0"      │ {0}                    │
  │   └─ neighbor 1      │  → not visited, call     │                       │
  │ dfs(0) → dfs(1)      │ Visit 1, print "1"      │ {0, 1}                 │
  │   └─ neighbor 0      │  → already visited, skip │                      │
  │   └─ neighbor 3      │  → not visited, call     │                      │
  │ dfs(0)→dfs(1)→dfs(3) │ Visit 3, print "3"      │ {0, 1, 3}            │
  │   └─ neighbor 1      │  → already visited, skip │                      │
  │   └─ neighbor 2      │  → not visited, call     │                      │
  │ ...→dfs(3)→dfs(2)    │ Visit 2, print "2"      │ {0, 1, 3, 2}         │
  │   └─ neighbor 0      │  → already visited, skip │                      │
  │   └─ neighbor 3      │  → already visited, skip │                      │
  │   └─ returns to dfs(3)│ backtrack               │                      │
  │ ...→dfs(3)           │                          │                      │
  │   └─ neighbor 4      │  → not visited, call     │                      │
  │ ...→dfs(3)→dfs(4)    │ Visit 4, print "4"      │ {0, 1, 3, 2, 4}      │
  │   └─ neighbor 3      │  → already visited, skip │                      │
  │   └─ returns to dfs(3)│ backtrack               │                      │
  │ dfs(3) returns        │ backtrack to dfs(1)     │                      │
  │ dfs(1) returns        │ backtrack to dfs(0)     │                      │
  │ dfs(0)               │                          │                      │
  │   └─ neighbor 2      │  → already visited, skip │                      │
  │ dfs(0) returns        │ DONE!                   │ {0, 1, 3, 2, 4}      │
  └─────────────────────────────────────────────────────────────────────────┘

  Output: 0 1 3 2 4

  Visual traversal tree (DFS Tree):

        0
       /
      1
       \
        3
       / \
      2   4

  ⚡ KEY INSIGHT: DFS creates a TREE structure from the graph!
  The edges used to discover new nodes form the "DFS Tree".
  Edges NOT in the DFS tree are called "Back Edges" (they go to ancestors).
  Edge (0,2) is NOT used because 2 was already visited via 0→1→3→2.
  Edge (2,3) going back to 3 is a "Back Edge".

═══════════════════════════════════════════════════════════════════════════════
PART 4: DFS — ITERATIVE IMPLEMENTATION (Using Explicit Stack)
═══════════════════════════════════════════════════════════════════════════════

  Why iterative?
    • Recursive DFS can cause STACK OVERFLOW for large graphs (N > 10^5)
    • Iterative gives you explicit control over the stack
    • Some problems are easier to solve iteratively

  ⚠️ NOTE: Iterative DFS visits nodes in a slightly different order
  than recursive DFS because it processes the LAST pushed neighbor first.
  To match recursive order, push neighbors in REVERSE.
*/

namespace IterativeDFS {

    void dfs_iterative(int start, vector<vector<int>>& adj, int n) {
        vector<bool> visited(n, false);
        stack<int> st;

        st.push(start);

        cout << "Iterative DFS: ";
        while (!st.empty()) {
            int node = st.top();
            st.pop();

            if (visited[node]) continue;  // already processed
            visited[node] = true;
            cout << node << " ";

            // Push neighbors in REVERSE to match recursive order
            for (int i = sz(adj[node]) - 1; i >= 0; i--) {
                int neighbor = adj[node][i];
                if (!visited[neighbor]) {
                    st.push(neighbor);
                }
            }
        }
        cout << nl;
    }

    /*
    Dry Run (same graph):
        adj[0]={1,2}, adj[1]={0,3}, adj[2]={0,3}, adj[3]={1,2,4}, adj[4]={3}

        Stack (top→right):  [0]
        ─────────────────────────────────────────
        Pop 0 → visit, push 2,1 (reverse)  → Stack: [2, 1]
        Pop 1 → visit, push 3 (0 visited)  → Stack: [2, 3]
        Pop 3 → visit, push 4,2 (1 visited)→ Stack: [2, 4, 2]
        Pop 2 → visit, push (0,3 visited)  → Stack: [2, 4]
        Pop 4 → visit, push (3 visited)    → Stack: [2]
        Pop 2 → already visited, skip      → Stack: []
        DONE!

        Output: 0 1 3 2 4  ✓ (matches recursive)
    */

    void run() {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        dfs_iterative(0, adj, n);
    }
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 5: DFS EDGE CLASSIFICATION
═══════════════════════════════════════════════════════════════════════════════

  When DFS traverses a graph, every edge falls into one of 4 categories:

  ┌──────────────────────────────────────────────────────────────────────────┐
  │  Edge Type       │ Description                    │ Detection           │
  ├──────────────────────────────────────────────────────────────────────────┤
  │  Tree Edge       │ Edge used to discover new node │ !visited[v]         │
  │  Back Edge       │ Goes to an ANCESTOR in DFS tree│ visited & !finished │
  │  Forward Edge    │ Goes to a DESCENDANT (directed)│ tin[u] < tin[v]     │
  │  Cross Edge      │ Goes to unrelated node(directed│ tin[u] > tin[v]     │
  └──────────────────────────────────────────────────────────────────────────┘

  For UNDIRECTED graphs: Only Tree Edges and Back Edges exist!
  For DIRECTED graphs: All 4 types can exist.

  ⚡ WHY THIS MATTERS:
    • Back Edge exists → Graph has a CYCLE!
    • No Back Edges → Graph is a DAG (Directed Acyclic Graph)
    • This is the foundation of cycle detection & topological sort

═══════════════════════════════════════════════════════════════════════════════
PART 6: DFS TIMESTAMPS — DISCOVERY (tin) & FINISH (tout) TIME
═══════════════════════════════════════════════════════════════════════════════

  Every node gets TWO timestamps:
    • tin[v]  = time when we FIRST visit v (discovery time)
    • tout[v] = time when we FINISH processing v (all descendants done)

  ⚡ KEY PROPERTY:
    Node u is an ANCESTOR of node v in DFS tree
    ⟺  tin[u] < tin[v]  AND  tout[u] > tout[v]
    (u's interval completely contains v's interval)

  This is EXTREMELY useful for:
    • Subtree queries (Euler Tour / Flatten tree into array)
    • LCA (Lowest Common Ancestor)
    • Checking ancestor-descendant relationship in O(1)
*/

namespace DFS_Timestamps {

    const int MAXN = 1e5 + 5;
    vector<int> adj[MAXN];
    bool visited[MAXN];
    int tin[MAXN], tout[MAXN];
    int timer_val = 0;

    void dfs(int node) {
        visited[node] = true;
        tin[node] = timer_val++;     // discovery time

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor);
            }
        }

        tout[node] = timer_val++;    // finish time
    }

    // Check if u is ancestor of v in O(1)
    bool isAncestor(int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    /*
    Dry Run on our graph (DFS from 0):

        DFS order: 0 → 1 → 3 → 2 → 4

        ┌──────┬──────┬───────┐
        │ Node │ tin  │ tout  │
        ├──────┼──────┼───────┤
        │  0   │  0   │  9    │
        │  1   │  1   │  8    │
        │  3   │  2   │  7    │
        │  2   │  3   │  4    │
        │  4   │  5   │  6    │
        └──────┴──────┴───────┘

        Timeline:
        0    1    2    3    4    5    6    7    8    9
        |    |    |    |    |    |    |    |    |    |
        0-in 1-in 3-in 2-in 2-out 4-in 4-out 3-out 1-out 0-out

        Is 0 ancestor of 4?  tin[0]=0 < tin[4]=5 && tout[0]=9 > tout[4]=6 → YES ✓
        Is 2 ancestor of 4?  tin[2]=3 < tin[4]=5 && tout[2]=4 > tout[4]=6 → NO (4>6 is false) ✓
    */

    void run() {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        dfs(0);
        cout << "Timestamps (tin / tout):" << nl;
        for (int i = 0; i < n; i++) {
            cout << "Node " << i << ": tin=" << tin[i] << " tout=" << tout[i] << nl;
        }
    }
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 7: CYCLE DETECTION USING DFS
═══════════════════════════════════════════════════════════════════════════════

  ┌─────────────────────────────────────────────────────────────────────────┐
  │  UNDIRECTED GRAPH: Cycle exists if we find a visited neighbor          │
  │                    that is NOT the parent of current node.             │
  │                                                                       │
  │  DIRECTED GRAPH:   Cycle exists if we find a node that is currently   │
  │                    IN THE RECURSION STACK (gray node / in-progress).   │
  └─────────────────────────────────────────────────────────────────────────┘
*/

namespace CycleDetection {

    // ═══════════════════════════════════════════
    // 7A: Cycle Detection in UNDIRECTED Graph
    // ═══════════════════════════════════════════
    /*
        Graph with cycle:
            0 ── 1
            |    |
            2 ── 3     (0-1-3-2-0 is a cycle!)

        Graph without cycle:
            0 ── 1
                 |
                 2      (this is a tree, no cycle)
    */

    namespace Undirected {
        bool dfs(int node, int parent, vector<vector<int>>& adj, vector<bool>& visited) {
            visited[node] = true;

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    // Tree edge — explore further
                    if (dfs(neighbor, node, adj, visited))
                        return true;  // cycle found deeper
                }
                else if (neighbor != parent) {
                    // Back edge to a visited non-parent → CYCLE!
                    return true;
                }
            }
            return false;
        }

        bool hasCycle(int n, vector<vector<int>>& adj) {
            vector<bool> visited(n, false);
            for (int i = 0; i < n; i++) {
                if (!visited[i]) {
                    if (dfs(i, -1, adj, visited))
                        return true;
                }
            }
            return false;
        }

        /*
        Dry Run (graph with cycle: 0-1, 0-2, 1-3, 2-3):

            dfs(0, -1):  visit 0
              → dfs(1, 0):  visit 1
                  → neighbor 0: visited but parent → skip
                  → dfs(3, 1):  visit 3
                      → neighbor 1: visited but parent → skip
                      → neighbor 2: NOT visited
                      → dfs(2, 3):  visit 2
                          → neighbor 0: visited AND ≠ parent(3) → CYCLE FOUND! ✓

        Dry Run (tree: 0-1, 1-2):

            dfs(0, -1):  visit 0
              → dfs(1, 0):  visit 1
                  → neighbor 0: visited but parent → skip
                  → dfs(2, 1):  visit 2
                      → neighbor 1: visited but parent → skip
                      → return false
                  → return false
              → return false
            → No cycle ✓
        */
    }

    // ═══════════════════════════════════════════
    // 7B: Cycle Detection in DIRECTED Graph
    // ═══════════════════════════════════════════
    /*
        Uses 3 colors:
          WHITE (0) = not visited
          GRAY  (1) = in current DFS path (recursion stack)
          BLACK (2) = fully processed

        If we see a GRAY node → it's in our current path → CYCLE!
    */

    namespace Directed {
        // color: 0=white, 1=gray, 2=black
        bool dfs(int node, vector<vector<int>>& adj, vector<int>& color) {
            color[node] = 1;  // GRAY — entering recursion

            for (int neighbor : adj[node]) {
                if (color[neighbor] == 1) {
                    // neighbor is GRAY → still in recursion stack → CYCLE!
                    return true;
                }
                if (color[neighbor] == 0) {
                    // WHITE → not visited, explore
                    if (dfs(neighbor, adj, color))
                        return true;
                }
                // BLACK (2) → fully processed, safe to skip
            }

            color[node] = 2;  // BLACK — fully processed
            return false;
        }

        bool hasCycle(int n, vector<vector<int>>& adj) {
            vector<int> color(n, 0);
            for (int i = 0; i < n; i++) {
                if (color[i] == 0) {
                    if (dfs(i, adj, color))
                        return true;
                }
            }
            return false;
        }

        /*
        Dry Run (directed graph: 0→1, 1→2, 2→0):

            dfs(0): color[0]=GRAY
              → dfs(1): color[1]=GRAY
                  → dfs(2): color[2]=GRAY
                      → neighbor 0: color[0]=GRAY → CYCLE! ✓

        Dry Run (DAG: 0→1, 0→2, 1→2):

            dfs(0): color[0]=GRAY
              → dfs(1): color[1]=GRAY
                  → dfs(2): color[2]=GRAY
                      → no neighbors → color[2]=BLACK, return false
                  → color[1]=BLACK, return false
              → neighbor 2: color[2]=BLACK → skip
              → color[0]=BLACK, return false
            → No cycle ✓
        */
    }
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 8: CONNECTED COMPONENTS (Undirected Graph)
═══════════════════════════════════════════════════════════════════════════════

  A connected component = a maximal set of nodes where every pair is reachable.

  Example:
      0 ── 1    3 ── 4    6
           |         |
           2         5

  Components: {0,1,2}, {3,4,5}, {6}  → 3 components

  Algorithm: Run DFS from each unvisited node. Each DFS call = one component.
*/

namespace ConnectedComponents {

    void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited,
             vector<int>& component) {
        visited[node] = true;
        component.push_back(node);
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, adj, visited, component);
            }
        }
    }

    void run() {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
        }

        vector<bool> visited(n, false);
        int numComponents = 0;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                numComponents++;
                vector<int> component;
                dfs(i, adj, visited, component);

                cout << "Component " << numComponents << ": ";
                for (int v : component) cout << v << " ";
                cout << nl;
            }
        }
        cout << "Total components: " << numComponents << nl;
    }

    /*
    Dry Run (7 nodes, edges: 0-1, 1-2, 3-4, 4-5):

        i=0: not visited → DFS(0) → visits {0,1,2} → Component 1
        i=1: visited → skip
        i=2: visited → skip
        i=3: not visited → DFS(3) → visits {3,4,5} → Component 2
        i=4: visited → skip
        i=5: visited → skip
        i=6: not visited → DFS(6) → visits {6}     → Component 3

        Output:
        Component 1: 0 1 2
        Component 2: 3 4 5
        Component 3: 6
        Total components: 3
    */
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 9: TOPOLOGICAL SORT USING DFS
═══════════════════════════════════════════════════════════════════════════════

  Topological Sort: Order vertices so that for every edge u→v, u comes before v.
  Only works on DAGs (Directed Acyclic Graphs).

  🧠 Intuition:
    In DFS, when a node FINISHES (all descendants processed), push it to result.
    Then REVERSE the result → Topological Order!

    WHY? Because a node finishes AFTER all nodes it depends on.

  Example DAG:
      5 → 0 ← 4
      ↓       ↓
      2 → 3 → 1

  Topological orders: [4, 5, 2, 3, 1, 0] or [5, 4, 2, 3, 0, 1] etc.
  (Multiple valid answers possible)
*/

namespace TopologicalSort {

    void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited,
             vector<int>& order) {
        visited[node] = true;

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, adj, visited, order);
            }
        }

        order.push_back(node);  // push AFTER all descendants finish
    }

    vector<int> topoSort(int n, vector<vector<int>>& adj) {
        vector<bool> visited(n, false);
        vector<int> order;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, adj, visited, order);
            }
        }

        reverse(all(order));  // reverse to get topological order
        return order;
    }

    void run() {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            adj[u].pb(v);  // directed edge u → v
        }

        vector<int> order = topoSort(n, adj);
        cout << "Topological Order: ";
        for (int v : order) cout << v << " ";
        cout << nl;
    }

    /*
    Dry Run (DAG: 5→0, 4→0, 5→2, 4→1, 2→3, 3→1):
        n=6, adj[5]={0,2}, adj[4]={0,1}, adj[2]={3}, adj[3]={1}

        DFS from 0: visits 0 → finishes → order=[0]
        DFS from 1: visits 1 → finishes → order=[0,1]
        DFS from 2: visits 2 → 3 → 1(visited) → 3 finishes → 2 finishes
                    → order=[0,1,3,2]
        DFS from 3: visited → skip
        DFS from 4: visits 4 → 0(visited) → 1(visited) → finishes
                    → order=[0,1,3,2,4]
        DFS from 5: visits 5 → 0(visited) → 2(visited) → finishes
                    → order=[0,1,3,2,4,5]

        Reverse: [5,4,2,3,1,0] → Valid topological order! ✓

        Verify: 5→0 (5 before 0 ✓), 5→2 (5 before 2 ✓),
                4→0 (4 before 0 ✓), 4→1 (4 before 1 ✓),
                2→3 (2 before 3 ✓), 3→1 (3 before 1 ✓)
    */
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 10: DFS ON TREES (Parent, Depth, Subtree Size)
═══════════════════════════════════════════════════════════════════════════════

  Trees are the most common DFS application!
  A tree = connected graph with N nodes and N-1 edges (no cycles).

  When doing DFS on a tree, we track:
    • parent[v] = who discovered v
    • depth[v]  = distance from root to v
    • sz[v]     = size of subtree rooted at v

  Example Tree (rooted at 0):
            0
           / \
          1   2
         / \   \
        3   4   5

  parent: [-1, 0, 0, 1, 1, 2]
  depth:  [0,  1, 1, 2, 2, 2]
  sz:     [6,  3, 2, 1, 1, 1]
*/

namespace DFS_Tree {

    const int MAXN = 2e5 + 5;
    vector<int> adj[MAXN];
    int par[MAXN], dep[MAXN], subtree_sz[MAXN];

    void dfs(int node, int parent, int depth) {
        par[node] = parent;
        dep[node] = depth;
        subtree_sz[node] = 1;  // count self

        for (int child : adj[node]) {
            if (child != parent) {  // don't go back to parent
                dfs(child, node, depth + 1);
                subtree_sz[node] += subtree_sz[child];  // add child's subtree
            }
        }
    }

    /*
    Dry Run (Tree: 0-1, 0-2, 1-3, 1-4, 2-5):

        dfs(0, -1, 0):  par[0]=-1, dep[0]=0, sz[0]=1
          → dfs(1, 0, 1):  par[1]=0, dep[1]=1, sz[1]=1
              → dfs(3, 1, 2):  par[3]=1, dep[3]=2, sz[3]=1
                  → no children → return (sz[3]=1)
              → sz[1] += sz[3] = 2
              → dfs(4, 1, 2):  par[4]=1, dep[4]=2, sz[4]=1
                  → no children → return (sz[4]=1)
              → sz[1] += sz[4] = 3
              → return (sz[1]=3)
          → sz[0] += sz[1] = 4
          → dfs(2, 0, 1):  par[2]=0, dep[2]=1, sz[2]=1
              → dfs(5, 2, 2):  par[5]=2, dep[5]=2, sz[5]=1
                  → no children → return (sz[5]=1)
              → sz[2] += sz[5] = 2
              → return (sz[2]=2)
          → sz[0] += sz[2] = 6
          → return (sz[0]=6)

        Result:
        ┌──────┬────────┬───────┬──────┐
        │ Node │ Parent │ Depth │ Size │
        ├──────┼────────┼───────┼──────┤
        │  0   │  -1    │   0   │  6   │
        │  1   │   0    │   1   │  3   │
        │  2   │   0    │   1   │  2   │
        │  3   │   1    │   2   │  1   │
        │  4   │   1    │   2   │  1   │
        │  5   │   2    │   2   │  1   │
        └──────┴────────┴───────┴──────┘
    */

    void run() {
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; i++) {
            int u, v; cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        dfs(0, -1, 0);  // root = 0

        for (int i = 0; i < n; i++) {
            cout << "Node " << i << ": parent=" << par[i]
                 << " depth=" << dep[i]
                 << " subtree_size=" << subtree_sz[i] << nl;
        }
    }
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 11: BRIDGES & ARTICULATION POINTS (Tarjan's Algorithm)
═══════════════════════════════════════════════════════════════════════════════

  Bridge: An edge whose removal DISCONNECTS the graph.
  Articulation Point: A vertex whose removal DISCONNECTS the graph.

  These are critical in network reliability problems!

  🧠 Key Idea (Tarjan's):
    • Track tin[v] = discovery time
    • Track low[v] = minimum tin reachable from subtree of v via back edges

    Bridge condition:    low[child] > tin[node]
      (child can't reach above node via back edges → removing edge disconnects)

    Articulation Point:  low[child] >= tin[node]  (and node is not root)
                    OR   node is root with >= 2 children in DFS tree

  Example:
        0 ── 1 ── 3
        |    |    |
        2 ────    4

    Bridge: edge (1,3) — removing it disconnects {3,4} from {0,1,2}
    Articulation Points: node 1 (removing disconnects) and node 3
*/

namespace Bridges_AP {

    const int MAXN = 1e5 + 5;
    vector<int> adj[MAXN];
    int tin_val[MAXN], low[MAXN];
    bool visited[MAXN];
    int timer_counter = 0;
    vector<pii> bridges;
    vector<int> articulationPoints;

    void dfs(int node, int parent) {
        visited[node] = true;
        tin_val[node] = low[node] = timer_counter++;
        int children = 0;
        bool isAP = false;

        for (int neighbor : adj[node]) {
            if (neighbor == parent) continue;

            if (visited[neighbor]) {
                // Back edge → update low
                low[node] = min(low[node], tin_val[neighbor]);
            } else {
                // Tree edge → DFS deeper
                children++;
                dfs(neighbor, node);
                low[node] = min(low[node], low[neighbor]);

                // Check for Bridge
                if (low[neighbor] > tin_val[node]) {
                    bridges.push_back({node, neighbor});
                }

                // Check for Articulation Point
                if (parent != -1 && low[neighbor] >= tin_val[node]) {
                    isAP = true;
                }
            }
        }

        // Root is AP if it has 2+ children in DFS tree
        if (parent == -1 && children >= 2) {
            isAP = true;
        }

        if (isAP) articulationPoints.push_back(node);
    }

    /*
    Dry Run (Graph: 0-1, 0-2, 1-2, 1-3, 3-4):

        adj[0]={1,2}, adj[1]={0,2,3}, adj[2]={0,1}, adj[3]={1,4}, adj[4]={3}

        dfs(0, -1): tin[0]=0, low[0]=0
          → dfs(1, 0): tin[1]=1, low[1]=1
              → neighbor 0: parent, skip
              → dfs(2, 1): tin[2]=2, low[2]=2
                  → neighbor 0: visited, back edge → low[2]=min(2,0)=0
                  → neighbor 1: parent, skip
                  → return. low[2]=0
              → low[1] = min(1, low[2]=0) = 0
              → low[2]=0 >= tin[1]=1? No bridge (0 is not > 1)
              → dfs(3, 1): tin[3]=3, low[3]=3
                  → dfs(4, 3): tin[4]=4, low[4]=4
                      → neighbor 3: parent, skip
                      → return. low[4]=4
                  → low[3] = min(3, low[4]=4) = 3
                  → low[4]=4 > tin[3]=3 → BRIDGE (3,4)! ✓
                  → low[4]=4 >= tin[3]=3 → AP candidate (3 has parent) → YES
                  → return. low[3]=3
              → low[1] = min(0, low[3]=3) = 0
              → low[3]=3 > tin[1]=1 → BRIDGE (1,3)! ✓
              → low[3]=3 >= tin[1]=1 → AP candidate (1 has parent) → YES
              → return. low[1]=0
          → low[0] = min(0, low[1]=0) = 0
          → return

        Bridges: (1,3), (3,4) ✓
        Articulation Points: 1, 3 ✓

        Visualization:
            0 ── 1 ══ 3 ══ 4     (══ = bridge)
            |    |
            2 ────
            (0,1,2 form a cycle → no bridge within)
    */

    void run() {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
        }

        for (int i = 0; i < n; i++) {
            if (!visited[i]) dfs(i, -1);
        }

        cout << "Bridges:" << nl;
        for (auto [u, v] : bridges) cout << u << " - " << v << nl;
        cout << "Articulation Points: ";
        for (int v : articulationPoints) cout << v << " ";
        cout << nl;
    }
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 12: STRONGLY CONNECTED COMPONENTS (SCC) — Kosaraju's Algorithm
═══════════════════════════════════════════════════════════════════════════════

  SCC: A maximal set of vertices where every vertex is reachable from every other.
  Only for DIRECTED graphs.

  Kosaraju's Algorithm (2-pass DFS):
    1. Run DFS on original graph, push nodes to stack by finish order
    2. Build reverse graph (flip all edges)
    3. Pop from stack, run DFS on reverse graph → each DFS = one SCC

  Example:
      0 → 1 → 2 → 0     (SCC: {0,1,2})
            ↓
            3 → 4 → 3    (SCC: {3,4})

  Why it works:
    • First DFS orders nodes by finish time (like topo sort)
    • In reverse graph, we can only reach nodes in the same SCC
    • Processing in reverse finish order ensures we don't cross SCC boundaries
*/

namespace Kosaraju {

    void dfs1(int node, vector<vector<int>>& adj, vector<bool>& visited,
              vector<int>& order) {
        visited[node] = true;
        for (int v : adj[node]) {
            if (!visited[v]) dfs1(v, adj, visited, order);
        }
        order.push_back(node);  // push on finish
    }

    void dfs2(int node, vector<vector<int>>& radj, vector<bool>& visited,
              vector<int>& component) {
        visited[node] = true;
        component.push_back(node);
        for (int v : radj[node]) {
            if (!visited[v]) dfs2(v, radj, visited, component);
        }
    }

    void run() {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> adj(n), radj(n);
        for (int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            adj[u].pb(v);
            radj[v].pb(u);  // reverse edge
        }

        // Pass 1: Get finish order
        vector<bool> visited(n, false);
        vector<int> order;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) dfs1(i, adj, visited, order);
        }

        // Pass 2: Process in reverse finish order on reverse graph
        fill(all(visited), false);
        int scc_count = 0;
        for (int i = n - 1; i >= 0; i--) {
            int node = order[i];
            if (!visited[node]) {
                scc_count++;
                vector<int> component;
                dfs2(node, radj, visited, component);
                cout << "SCC " << scc_count << ": ";
                for (int v : component) cout << v << " ";
                cout << nl;
            }
        }
    }

    /*
    Dry Run (5 nodes, edges: 0→1, 1→2, 2→0, 1→3, 3→4, 4→3):

        Pass 1 (original graph):
            dfs1(0): 0→1→2→0(visited)→ 2 finishes,
                     1→3→4→3(visited)→ 4 finishes, 3 finishes,
                     1 finishes, 0 finishes
            order = [2, 4, 3, 1, 0]

        Reverse graph:
            radj[1]={0}, radj[2]={1}, radj[0]={2}, radj[3]={1,4}, radj[4]={3}

        Pass 2 (process order reversed: 0, 1, 3, 4, 2):
            node=0: dfs2(0) → 0→2(radj)→1(radj)→0(visited)
                    SCC 1: {0, 2, 1}  ✓
            node=1: visited → skip
            node=3: dfs2(3) → 3→4(radj)→3(visited)
                    SCC 2: {3, 4}  ✓
            node=4: visited → skip
            node=2: visited → skip

        Result: 2 SCCs → {0,1,2} and {3,4} ✓
    */
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 13: BIPARTITE CHECK USING DFS
═══════════════════════════════════════════════════════════════════════════════

  Bipartite = Can we color the graph with 2 colors such that no two adjacent
              nodes have the same color?

  ⚡ A graph is bipartite ⟺ it has NO odd-length cycle.

  Algorithm: Try to 2-color the graph using DFS.
    • Color start node with 0
    • Color all its neighbors with 1
    • Color their neighbors with 0
    • If we find a neighbor with SAME color → NOT bipartite!
*/

namespace BipartiteCheck {

    bool dfs(int node, int c, vector<vector<int>>& adj, vector<int>& color) {
        color[node] = c;

        for (int neighbor : adj[node]) {
            if (color[neighbor] == -1) {
                // Not colored yet → color with opposite
                if (!dfs(neighbor, 1 - c, adj, color))
                    return false;
            }
            else if (color[neighbor] == c) {
                // Same color as current → NOT bipartite!
                return false;
            }
        }
        return true;
    }

    bool isBipartite(int n, vector<vector<int>>& adj) {
        vector<int> color(n, -1);
        for (int i = 0; i < n; i++) {
            if (color[i] == -1) {
                if (!dfs(i, 0, adj, color))
                    return false;
            }
        }
        return true;
    }

    /*
    Example 1 (Bipartite):     Example 2 (NOT Bipartite):
        0 ── 1                     0 ── 1
        |    |                     |  /
        3 ── 2                     2     (triangle 0-1-2)

    Dry Run Example 1 (square: edges 0-1, 1-2, 2-3, 3-0):
        dfs(0, 0): color[0]=0
          → dfs(1, 1): color[1]=1
              → dfs(2, 0): color[2]=0
                  → dfs(3, 1): color[3]=1
                      → neighbor 0: color=0 ≠ 1 → OK
                  → OK
              → OK
          → neighbor 3: color=1 ≠ 0 → OK
        → Bipartite! ✓ (colors: 0,1,0,1)

    Dry Run Example 2 (triangle: 0-1, 1-2, 2-0):
        dfs(0, 0): color[0]=0
          → dfs(1, 1): color[1]=1
              → dfs(2, 0): color[2]=0
                  → neighbor 0: color=0 == 0 → NOT bipartite! ✗
    */
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 14: DFS ON GRID / 2D MATRIX (Flood Fill, Island Count)
═══════════════════════════════════════════════════════════════════════════════

  Grid DFS is EXTREMELY common in CP & interviews!

  Grid = implicit graph where:
    • Each cell (i,j) is a node
    • Neighbors are adjacent cells (up, down, left, right)
    • Sometimes diagonals too (8-directional)

  Common problems:
    • Count islands (connected components of '1's)
    • Flood fill (paint bucket tool)
    • Find largest connected region
    • Check if path exists from source to destination
*/

namespace GridDFS {

    int dx[] = {-1, 1, 0, 0};  // up, down, left, right
    int dy[] = {0, 0, -1, 1};

    // For 8-directional:
    // int dx[] = {-1,-1,-1,0,0,1,1,1};
    // int dy[] = {-1,0,1,-1,1,-1,0,1};

    int n, m;

    bool isValid(int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    }

    // ═══════════════════════════════════════════
    // 14A: Count Islands (Number of Connected Components)
    // ═══════════════════════════════════════════
    /*
        Grid:
        1 1 0 0 0
        1 1 0 0 0
        0 0 1 0 0
        0 0 0 1 1

        Islands (connected groups of 1's):
        Island 1: top-left 2×2 block
        Island 2: middle '1'
        Island 3: bottom-right pair
        Answer: 3
    */

    void dfs_island(int x, int y, vector<vector<int>>& grid,
                    vector<vector<bool>>& visited) {
        visited[x][y] = true;

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (isValid(nx, ny) && !visited[nx][ny] && grid[nx][ny] == 1) {
                dfs_island(nx, ny, grid, visited);
            }
        }
    }

    int countIslands(vector<vector<int>>& grid) {
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int count = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    count++;
                    dfs_island(i, j, grid, visited);
                }
            }
        }
        return count;
    }

    /*
    Dry Run:
        Grid:              visited after:
        1 1 0 0 0          T T . . .
        1 1 0 0 0          T T . . .
        0 0 1 0 0    →     . . T . .
        0 0 0 1 1          . . . T T

        (i=0,j=0): grid=1, not visited → count=1, DFS marks (0,0)(0,1)(1,0)(1,1)
        (i=0,j=1): visited → skip
        (i=0,j=2..4): grid=0 → skip
        (i=1,j=0..1): visited → skip
        (i=2,j=2): grid=1, not visited → count=2, DFS marks (2,2)
        (i=3,j=3): grid=1, not visited → count=3, DFS marks (3,3)(3,4)
        Answer: 3 ✓
    */

    // ═══════════════════════════════════════════
    // 14B: Flood Fill (Paint Bucket)
    // ═══════════════════════════════════════════
    void floodFill(int x, int y, int oldColor, int newColor,
                   vector<vector<int>>& grid) {
        if (!isValid(x, y)) return;
        if (grid[x][y] != oldColor) return;
        if (grid[x][y] == newColor) return;  // prevent infinite loop

        grid[x][y] = newColor;

        for (int d = 0; d < 4; d++) {
            floodFill(x + dx[d], y + dy[d], oldColor, newColor, grid);
        }
    }

    // ═══════════════════════════════════════════
    // 14C: Find Largest Island Size
    // ═══════════════════════════════════════════
    int dfs_size(int x, int y, vector<vector<int>>& grid,
                 vector<vector<bool>>& visited) {
        visited[x][y] = true;
        int size = 1;

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (isValid(nx, ny) && !visited[nx][ny] && grid[nx][ny] == 1) {
                size += dfs_size(nx, ny, grid, visited);
            }
        }
        return size;
    }
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 15: EULER PATH & EULER CIRCUIT USING DFS
═══════════════════════════════════════════════════════════════════════════════

  Euler Path:    Visit every EDGE exactly once.
  Euler Circuit: Euler Path that starts and ends at same vertex.

  Conditions (Undirected):
    • Euler Circuit: All vertices have even degree
    • Euler Path: Exactly 0 or 2 vertices have odd degree

  Algorithm: Hierholzer's algorithm using DFS

  This is used in problems like:
    • "Can you draw this figure without lifting your pen?"
    • Route planning (Chinese Postman Problem)
*/

namespace EulerPath {

    // Hierholzer's algorithm for Euler Circuit/Path in directed graph
    void dfs(int node, vector<vector<int>>& adj, vector<int>& idx,
             vector<int>& circuit) {
        while (idx[node] < sz(adj[node])) {
            int next = adj[node][idx[node]++];
            dfs(next, adj, idx, circuit);
        }
        circuit.push_back(node);
    }

    vector<int> findEulerCircuit(int n, vector<vector<int>>& adj) {
        vector<int> idx(n, 0);  // next edge to visit for each node
        vector<int> circuit;
        dfs(0, adj, idx, circuit);
        reverse(all(circuit));
        return circuit;
    }
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 16: DFS + BACKTRACKING PATTERNS
═══════════════════════════════════════════════════════════════════════════════

  DFS is the backbone of ALL backtracking algorithms!
  The key difference: in backtracking, we UNDO our choice before trying next.

  Pattern:
    void backtrack(state):
        if (goal reached):
            record solution
            return
        for each choice:
            make choice
            backtrack(new state)
            undo choice          ← THIS IS THE BACKTRACKING STEP!
*/

namespace Backtracking {

    // ═══════════════════════════════════════════
    // 16A: Generate All Subsets
    // ═══════════════════════════════════════════
    /*
        Input: [1, 2, 3]
        Output: [], [1], [2], [3], [1,2], [1,3], [2,3], [1,2,3]
    */
    void generateSubsets(int idx, vector<int>& nums, vector<int>& current,
                         vector<vector<int>>& result) {
        result.push_back(current);  // every state is a valid subset

        for (int i = idx; i < sz(nums); i++) {
            current.push_back(nums[i]);           // make choice
            generateSubsets(i + 1, nums, current, result);
            current.pop_back();                    // undo choice (backtrack)
        }
    }

    /*
    Dry Run (nums = [1,2,3]):

        idx=0, current=[]        → result: [[]]
          i=0: push 1, current=[1]
            idx=1, current=[1]   → result: [[], [1]]
              i=1: push 2, current=[1,2]
                idx=2, current=[1,2] → result: [[], [1], [1,2]]
                  i=2: push 3, current=[1,2,3]
                    idx=3 → result: [[], [1], [1,2], [1,2,3]]
                  pop 3
                idx=3 → return
              pop 2
              i=2: push 3, current=[1,3]
                idx=3 → result: [[], [1], [1,2], [1,2,3], [1,3]]
              pop 3
            return
          pop 1
          i=1: push 2, current=[2]
            idx=2, current=[2] → result: [..., [2]]
              i=2: push 3, current=[2,3]
                idx=3 → result: [..., [2,3]]
              pop 3
            return
          pop 2
          i=2: push 3, current=[3]
            idx=3 → result: [..., [3]]
          pop 3

        Final: [[], [1], [1,2], [1,2,3], [1,3], [2], [2,3], [3]]
    */

    // ═══════════════════════════════════════════
    // 16B: Generate All Permutations
    // ═══════════════════════════════════════════
    void generatePermutations(vector<int>& nums, int start,
                               vector<vector<int>>& result) {
        if (start == sz(nums)) {
            result.push_back(nums);
            return;
        }

        for (int i = start; i < sz(nums); i++) {
            swap(nums[start], nums[i]);          // make choice
            generatePermutations(nums, start + 1, result);
            swap(nums[start], nums[i]);          // undo choice
        }
    }

    // ═══════════════════════════════════════════
    // 16C: N-Queens Problem
    // ═══════════════════════════════════════════
    bool isSafe(int row, int col, int n, vector<bool>& colUsed,
                vector<bool>& diag1, vector<bool>& diag2) {
        return !colUsed[col] && !diag1[row + col] && !diag2[row - col + n - 1];
    }

    void solveNQueens(int row, int n, vector<string>& board,
                      vector<bool>& colUsed, vector<bool>& diag1,
                      vector<bool>& diag2, int& count) {
        if (row == n) {
            count++;
            return;
        }

        for (int col = 0; col < n; col++) {
            if (isSafe(row, col, n, colUsed, diag1, diag2)) {
                board[row][col] = 'Q';
                colUsed[col] = diag1[row + col] = diag2[row - col + n - 1] = true;

                solveNQueens(row + 1, n, board, colUsed, diag1, diag2, count);

                board[row][col] = '.';  // BACKTRACK
                colUsed[col] = diag1[row + col] = diag2[row - col + n - 1] = false;
            }
        }
    }
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 17: ADVANCED — DFS TREE & EULER TOUR (Flatten Tree into Array)
═══════════════════════════════════════════════════════════════════════════════

  Euler Tour flattens a tree into an array so we can use RANGE QUERIES
  (Segment Tree, BIT) on subtrees!

  Technique:
    • Record tin[v] when entering node v
    • Record tout[v] when leaving node v
    • Subtree of v = range [tin[v], tout[v]] in the Euler Tour array

  This enables:
    • Subtree sum/min/max queries in O(log n)
    • Path queries combined with LCA
    • Update a node's value and query subtree → Segment Tree on Euler Tour
*/

namespace EulerTour {

    const int MAXN = 2e5 + 5;
    vector<int> adj[MAXN];
    int tin[MAXN], tout[MAXN], euler[MAXN];  // euler[pos] = node at position pos
    int timer_val = 0;

    void dfs(int node, int parent) {
        tin[node] = timer_val;
        euler[timer_val] = node;
        timer_val++;

        for (int child : adj[node]) {
            if (child != parent) {
                dfs(child, node);
            }
        }

        tout[node] = timer_val - 1;
    }

    /*
    Example Tree:
            0
           / \
          1   2
         / \
        3   4

    DFS from 0:
        tin[0]=0, euler[0]=0
          tin[1]=1, euler[1]=1
            tin[3]=2, euler[2]=3, tout[3]=2
            tin[4]=3, euler[3]=4, tout[4]=3
          tout[1]=3
          tin[2]=4, euler[4]=2, tout[2]=4
        tout[0]=4

    Euler Tour Array: [0, 1, 3, 4, 2]
    Subtree of node 1 = euler[tin[1]..tout[1]] = euler[1..3] = [1, 3, 4] ✓

    Now you can use a Segment Tree on this array for subtree queries!
    */
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 18: TIME & SPACE COMPLEXITY ANALYSIS
═══════════════════════════════════════════════════════════════════════════════

  ┌────────────────────────────────────────────────────────────────────────────┐
  │  Operation              │ Time         │ Space           │ Notes          │
  ├────────────────────────────────────────────────────────────────────────────┤
  │  Basic DFS              │ O(V + E)     │ O(V)            │ Best case      │
  │  DFS on Tree            │ O(N)         │ O(N)            │ E = N-1        │
  │  DFS on Grid            │ O(N × M)     │ O(N × M)        │ Visit all cells│
  │  Cycle Detection        │ O(V + E)     │ O(V)            │                │
  │  Topological Sort       │ O(V + E)     │ O(V)            │ DAG only       │
  │  Bridges/AP (Tarjan)    │ O(V + E)     │ O(V)            │                │
  │  SCC (Kosaraju)         │ O(V + E)     │ O(V + E)        │ Reverse graph  │
  │  Backtracking           │ O(2^N) etc.  │ O(N)            │ Varies by prob │
  │  N-Queens               │ O(N!)        │ O(N)            │                │
  └────────────────────────────────────────────────────────────────────────────┘

  ⚡ Important limits for CP:
    • N ≤ 10^5 → Recursive DFS is fine
    • N ≤ 10^6 → Use iterative DFS (stack overflow risk)
    • N ≤ 10^7 → Be careful with constant factors

═══════════════════════════════════════════════════════════════════════════════
PART 19: COMMON MISTAKES & TIPS FOR CP
═══════════════════════════════════════════════════════════════════════════════

  ❌ MISTAKE 1: Forgetting to mark visited BEFORE recursive call
     → Can cause infinite loops or TLE

  ❌ MISTAKE 2: Not handling disconnected graphs
     → Always loop over ALL nodes: for(int i=0; i<n; i++) if(!vis[i]) dfs(i);

  ❌ MISTAKE 3: Stack overflow on large inputs
     → Solution: Use iterative DFS or increase stack size
     → In competitive programming: #pragma comment(linker, "/STACK:1000000000")
     → Or: ulimit -s unlimited (Linux)

  ❌ MISTAKE 4: Not clearing global arrays between test cases
     → Use fill() or memset() at the start of each test case
     → Or use local vectors instead of global arrays

  ❌ MISTAKE 5: Using visited[] for directed cycle detection
     → Need 3 colors (white/gray/black), not just visited/unvisited

  ❌ MISTAKE 6: Wrong parent check in undirected graph
     → For multi-edges: track parent EDGE INDEX, not parent NODE

  ✅ TIP 1: For trees, use parent tracking instead of visited array
     → dfs(child, node) where child != parent is cleaner

  ✅ TIP 2: Use lambda DFS in modern C++ for cleaner code:
     auto dfs = [&](auto self, int u, int p) -> void {
         for (int v : adj[u]) if (v != p) self(self, v, u);
     };
     dfs(dfs, 0, -1);

  ✅ TIP 3: For grids, always check bounds BEFORE accessing the array

  ✅ TIP 4: Use 0-indexed graphs in CP (consistent with arrays)

═══════════════════════════════════════════════════════════════════════════════
PART 20: PRACTICE PROBLEMS — GRADED BY DIFFICULTY
═══════════════════════════════════════════════════════════════════════════════

  🟢 BEGINNER (Learn the basics):
    1. CSES: Counting Rooms          → Grid DFS, count components
    2. CSES: Building Roads          → Connected components
    3. LeetCode 200: Number of Islands → Grid DFS classic
    4. LeetCode 733: Flood Fill      → Grid DFS
    5. CF 580C: Kefa and Park        → DFS on tree

  🟡 INTERMEDIATE (Apply patterns):
    6.  CSES: Round Trip              → Cycle detection + path printing
    7.  CSES: Course Schedule         → Topological sort (or cycle in directed)
    8.  LeetCode 207: Course Schedule → Directed cycle detection
    9.  LeetCode 785: Is Graph Bipartite → Bipartite check
    10. CF 1143C: Queen               → DFS on tree with conditions

  🔴 ADVANCED (Master level):
    11. CSES: Planets and Kingdoms   → SCC (Kosaraju)
    12. CSES: Coin Collector         → SCC + DAG DP
    13. CF 1702F: Equate Multisets   → DFS with backtracking
    14. LeetCode 1192: Critical Connections → Bridges (Tarjan)
    15. CF 1364D: Ehab's Last Corollary → DFS tree + cycle/bipartite

  ⚫ GRANDMASTER (Competition level):
    16. CF 1702G: Passable Paths     → DFS order + LCA
    17. CSES: Path Queries           → Euler Tour + Segment Tree
    18. CF 1833G: Ksysha and Chinchilla → Tree DFS + greedy
    19. CF 1903F: Babysitting         → DFS timestamps + offline
    20. AtCoder ABC 222F: Costly Experiment → Rerooting technique

═══════════════════════════════════════════════════════════════════════════════
SUMMARY CHEAT SHEET
═══════════════════════════════════════════════════════════════════════════════

    ╔═══════════════════════════════════════════════════════════════════════╗
    ║  DFS = Go DEEP first, then backtrack                               ║
    ║  Uses: Stack (implicit via recursion, or explicit)                  ║
    ║  Time: O(V + E) | Space: O(V)                                     ║
    ║                                                                     ║
    ║  Core template:                                                     ║
    ║    void dfs(int u) {                                               ║
    ║        vis[u] = 1;                                                 ║
    ║        for (int v : adj[u])                                        ║
    ║            if (!vis[v]) dfs(v);                                    ║
    ║    }                                                               ║
    ║                                                                     ║
    ║  Applications:                                                      ║
    ║    • Connectivity    • Cycle detection  • Topological sort          ║
    ║    • Bridges/AP      • SCC              • Bipartite check          ║
    ║    • Tree problems   • Grid traversal   • Backtracking             ║
    ║    • Euler Tour      • Euler Path       • Flood fill               ║
    ╚═══════════════════════════════════════════════════════════════════════╝
*/

// ═══════════════════════════════════════════════════════════════════════════════
// MAIN — Uncomment the section you want to test
// ═══════════════════════════════════════════════════════════════════════════════

void solve() {
    // Uncomment ONE of these to test:

    // BasicDFS::run();
    // IterativeDFS::run();
    // DFS_Timestamps::run();
    // ConnectedComponents::run();
    // TopologicalSort::run();
    // DFS_Tree::run();
    // Bridges_AP::run();
    // Kosaraju::run();

    // For quick demo — basic DFS:
    cout << "=== DFS Masterclass ===" << nl;
    cout << "Uncomment a section in solve() to test!" << nl;
    cout << "Read the comments for complete theory & dry runs." << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}

