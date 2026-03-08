/*
╔══════════════════════════════════════════════════════════════════════════════╗
║        BREADTH FIRST SEARCH (BFS) — ZERO TO GRANDMASTER GUIDE                ║
║        Author: Sarvan.DP.GrandMaster                                         ║
║        Created: 2026-03-07                                                   ║
╚══════════════════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════════════════
TABLE OF CONTENTS
═══════════════════════════════════════════════════════════════════════════════
  PART 0  → Prerequisite: Graph Basics (Quick Recap)
  PART 1  → What is BFS? (The Core Idea)
  PART 2  → BFS — Standard Implementation (Queue Based)
  PART 3  → Step-by-Step Dry Run with Visualization
  PART 4  → Shortest Path in Unweighted Graph (BFS Superpower!)
  PART 5  → Path Reconstruction (Print the Actual Shortest Path)
  PART 6  → BFS Level-by-Level Traversal (Level Order)
  PART 7  → Connected Components using BFS
  PART 8  → Bipartite Check using BFS (2-Coloring)
  PART 9  → Cycle Detection using BFS
  PART 10 → BFS on Grid / 2D Matrix (Shortest Path in Maze)
  PART 11 → Multi-Source BFS (Fire Spread, Rotten Oranges)
  PART 12 → 0-1 BFS (Deque BFS — Weighted with 0/1 edges)
  PART 13 → BFS on Implicit Graphs (State-Space Search)
  PART 14 → Topological Sort using BFS (Kahn's Algorithm)
  PART 15 → BFS on Trees (Level Order, Zigzag, Right View)
  PART 16 → Bidirectional BFS (Meet in the Middle)
  PART 17 → Multi-State BFS (Keys & Doors, Bitmask States)
  PART 18 → BFS vs DFS — When to Use Which?
  PART 19 → Time & Space Complexity + Common Mistakes
  PART 20 → Practice Problems (Codeforces, CSES, LeetCode)
═══════════════════════════════════════════════════════════════════════════════

═══════════════════════════════════════════════════════════════════════════════
PART 0: PREREQUISITE — GRAPH BASICS (Quick Recap)
═══════════════════════════════════════════════════════════════════════════════

  Graph G = (V, E):
    V = vertices (nodes), E = edges (connections)

  Adjacency List (most used in CP):
    vector<vector<int>> adj(n);
    adj[u].push_back(v);  // edge u → v
    adj[v].push_back(u);  // add this for undirected

  Example Graph:
        0 ── 1
        |    |
        2 ── 3
             |
             4

  adj[0] = {1, 2}    adj[1] = {0, 3}    adj[2] = {0, 3}
  adj[3] = {1, 2, 4} adj[4] = {3}

═══════════════════════════════════════════════════════════════════════════════
PART 1: WHAT IS BFS? (The Core Idea)
═══════════════════════════════════════════════════════════════════════════════

  BFS = Breadth First Search

  🧠 Intuition:
    "Explore ALL neighbors first, then go deeper."
    Like a RIPPLE in water — expands outward level by level.

  Real-life analogy:
    Imagine dropping a stone in a pond:
      → First ring = distance 1 from center
      → Second ring = distance 2 from center
      → Third ring = distance 3 from center
    BFS explores the graph in these "rings" (levels).

  Another analogy — telling a rumor:
      → You tell your direct friends (distance 1)
      → They tell THEIR friends (distance 2)
      → Those friends tell THEIR friends (distance 3)
      → Each "round" = one level of BFS

  Algorithm (Pseudocode):
    ┌──────────────────────────────────────────────────────────────┐
    │  BFS(start):                                               │
    │    create a queue Q                                        │
    │    mark start as visited, push to Q                        │
    │    while Q is not empty:                                   │
    │      node = Q.front(); Q.pop()                             │
    │      for each neighbor of node:                            │
    │        if neighbor NOT visited:                            │
    │          mark visited, push to Q                           │
    └──────────────────────────────────────────────────────────────┘

  Key Properties:
    • Uses a QUEUE (FIFO — First In, First Out)
    • Visits nodes LEVEL by LEVEL
    • Finds SHORTEST PATH in unweighted graphs!  ← BFS SUPERPOWER
    • Time Complexity:  O(V + E)
    • Space Complexity: O(V)

  ⚡ THE GOLDEN RULE:
    ╔═══════════════════════════════════════════════════════════╗
    ║  BFS guarantees SHORTEST DISTANCE in UNWEIGHTED graphs!  ║
    ║  DFS does NOT.  This is THE reason to choose BFS.        ║
    ╚═══════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════════════════
PART 2: BFS — STANDARD IMPLEMENTATION
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
#include <deque>
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
constexpr int INF = 1e9;

// ─────────────────────────────────────────────────────────────────────────────
// SECTION 2A: Simplest BFS — Traversal on Adjacency List
// ─────────────────────────────────────────────────────────────────────────────
/*
    Graph:
        0 ── 1
        |    |
        2 ── 3
             |
             4

    BFS from node 0:  0 → 1 → 2 → 3 → 4
    (visits level by level)

    Level 0: {0}
    Level 1: {1, 2}     (neighbors of 0)
    Level 2: {3}         (neighbors of 1,2 not yet visited)
    Level 3: {4}         (neighbor of 3 not yet visited)
*/

namespace BasicBFS {

    // ╔═══════════════════════════════════════════════════════╗
    // ║  THE CORE BFS FUNCTION — memorize this!              ║
    // ╠═══════════════════════════════════════════════════════╣
    // ║  Step 1: Create queue, mark start visited, push it   ║
    // ║  Step 2: While queue not empty:                      ║
    // ║    a) Pop front node                                 ║
    // ║    b) Process it (print, count, etc.)                ║
    // ║    c) Push all unvisited neighbors, mark visited     ║
    // ╚═══════════════════════════════════════════════════════╝
    void bfs(int start, vector<vector<int>>& adj, int n) {
        vector<bool> visited(n, false);
        queue<int> q;

        visited[start] = true;   // Mark BEFORE pushing!
        q.push(start);

        cout << "BFS Traversal: ";
        while (!q.empty()) {
            int node = q.front();
            q.pop();

            cout << node << " ";  // Process the node

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;  // Mark visited NOW (not later!)
                    q.push(neighbor);
                }
            }
        }
        cout << nl;
    }

    /*
    ⚠️ CRITICAL: Mark visited when PUSHING, not when POPPING!
       Why? If you mark when popping, a node might get pushed
       multiple times by different neighbors → wasteful & wrong.

       WRONG:                           CORRECT:
       while (!q.empty()) {             while (!q.empty()) {
         node = q.front(); q.pop();       node = q.front(); q.pop();
         if (visited[node]) continue;     // already guaranteed visited
         visited[node] = true;            for (nbr : adj[node]) {
         for (nbr : adj[node])              if (!visited[nbr]) {
           q.push(nbr);                      visited[nbr] = true;
       }                                     q.push(nbr);
                                          }
                                        }
    */

    void run() {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        bfs(0, adj, n);
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

  BFS from node 0:

  ┌───────────────────────────────────────────────────────────────────────────┐
  │ STEP │ QUEUE (front→back)│ POP  │ ACTION                │ VISITED       │
  ├───────────────────────────────────────────────────────────────────────────┤
  │  0   │ [0]               │  -   │ Start: push 0         │ {0}           │
  │  1   │ []→process 0      │  0   │ Print 0               │ {0}           │
  │      │                   │      │ nbr 1: !vis → push    │ {0,1}         │
  │      │                   │      │ nbr 2: !vis → push    │ {0,1,2}       │
  │      │ [1, 2]            │      │                       │               │
  │  2   │ [2]→process 1     │  1   │ Print 1               │ {0,1,2}       │
  │      │                   │      │ nbr 0: visited → skip │               │
  │      │                   │      │ nbr 3: !vis → push    │ {0,1,2,3}     │
  │      │ [2, 3]            │      │                       │               │
  │  3   │ [3]→process 2     │  2   │ Print 2               │ {0,1,2,3}     │
  │      │                   │      │ nbr 0: visited → skip │               │
  │      │                   │      │ nbr 3: visited → skip │               │
  │      │ [3]               │      │                       │               │
  │  4   │ []→process 3      │  3   │ Print 3               │ {0,1,2,3}     │
  │      │                   │      │ nbr 1: visited → skip │               │
  │      │                   │      │ nbr 2: visited → skip │               │
  │      │                   │      │ nbr 4: !vis → push    │ {0,1,2,3,4}   │
  │      │ [4]               │      │                       │               │
  │  5   │ []→process 4      │  4   │ Print 4               │ {0,1,2,3,4}   │
  │      │                   │      │ nbr 3: visited → skip │               │
  │      │ []                │      │ QUEUE EMPTY → DONE!   │               │
  └───────────────────────────────────────────────────────────────────────────┘

  Output: 0 1 2 3 4

  ⚡ Notice the LEVEL ORDER:
        Level 0: [0]         ← distance 0 from start
        Level 1: [1, 2]      ← distance 1 from start
        Level 2: [3]         ← distance 2 from start
        Level 3: [4]         ← distance 3 from start

  BFS Tree Visualization:
               0          ← Level 0
              / \
             1   2        ← Level 1
              \ /
               3          ← Level 2
               |
               4          ← Level 3

  Compare with DFS (from DFS file):
    DFS output: 0 1 3 2 4  (goes deep: 0→1→3→2 then backtracks)
    BFS output: 0 1 2 3 4  (goes wide: level by level)

═══════════════════════════════════════════════════════════════════════════════
PART 4: SHORTEST PATH IN UNWEIGHTED GRAPH (BFS Superpower!)
═══════════════════════════════════════════════════════════════════════════════

  🏆 THIS IS THE #1 REASON TO USE BFS!

  BFS naturally computes shortest distance from source to ALL other nodes
  in an UNWEIGHTED graph (all edges have weight 1).

  Why? Because BFS explores nodes level by level:
    → Level 0 = distance 0 (just the source)
    → Level 1 = distance 1
    → Level 2 = distance 2
    → ...
  The FIRST time BFS reaches a node = the SHORTEST distance to it!
*/

namespace ShortestPathBFS {

    // ╔═══════════════════════════════════════════════════════════╗
    // ║  BFS for Shortest Distance — THE MOST IMPORTANT BFS!     ║
    // ║  Returns dist[] where dist[v] = shortest distance from   ║
    // ║  source to v. dist[v] = -1 if unreachable.               ║
    // ╚═══════════════════════════════════════════════════════════╝
    vector<int> bfs_shortest(int source, vector<vector<int>>& adj, int n) {
        vector<int> dist(n, -1);  // -1 means unreachable
        queue<int> q;

        dist[source] = 0;
        q.push(source);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor : adj[node]) {
                if (dist[neighbor] == -1) {  // not visited yet
                    dist[neighbor] = dist[node] + 1;  // distance = parent + 1
                    q.push(neighbor);
                }
            }
        }

        return dist;
    }

    /*
    Dry Run (same graph, source = 0):

        dist = [-1, -1, -1, -1, -1]   initially

        Push 0, dist[0] = 0
        dist = [0, -1, -1, -1, -1]

        Pop 0: neighbors 1, 2
          dist[1] = dist[0]+1 = 1, push 1
          dist[2] = dist[0]+1 = 1, push 2
        dist = [0, 1, 1, -1, -1]

        Pop 1: neighbors 0, 3
          dist[0] ≠ -1 → skip
          dist[3] = dist[1]+1 = 2, push 3
        dist = [0, 1, 1, 2, -1]

        Pop 2: neighbors 0, 3
          dist[0] ≠ -1 → skip
          dist[3] ≠ -1 → skip (already found shorter!)
        dist = [0, 1, 1, 2, -1]

        Pop 3: neighbors 1, 2, 4
          dist[1] ≠ -1 → skip
          dist[2] ≠ -1 → skip
          dist[4] = dist[3]+1 = 3, push 4
        dist = [0, 1, 1, 2, 3]

        Pop 4: neighbors 3
          dist[3] ≠ -1 → skip

        DONE!

        Result:
        ┌──────┬───────────┐
        │ Node │ Distance  │
        ├──────┼───────────┤
        │  0   │    0      │
        │  1   │    1      │
        │  2   │    1      │
        │  3   │    2      │
        │  4   │    3      │
        └──────┴───────────┘

        Visualization of distances:
              0(d=0)
             / \
          1(d=1) 2(d=1)
             \ /
           3(d=2)
              |
           4(d=3)
    */

    void run() {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
        }

        vector<int> dist = bfs_shortest(0, adj, n);

        cout << "Shortest distances from node 0:" << nl;
        for (int i = 0; i < n; i++) {
            cout << "  Node " << i << ": " << dist[i] << nl;
        }
    }
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 5: PATH RECONSTRUCTION (Print the Actual Shortest Path)
═══════════════════════════════════════════════════════════════════════════════

  BFS gives us distances, but sometimes we need the ACTUAL PATH.

  Technique: Track parent[v] = the node that discovered v during BFS.
  Then backtrack from destination to source using parent[].

  Example: Find shortest path from 0 to 4:
      0 ── 1
      |    |
      2 ── 3
           |
           4

  Path: 0 → 1 → 3 → 4  (or 0 → 2 → 3 → 4, both length 3)
*/

namespace PathReconstruction {

    pair<vector<int>, vector<int>> bfs_with_parent(int source,
                                                     vector<vector<int>>& adj, int n) {
        vector<int> dist(n, -1);
        vector<int> parent(n, -1);
        queue<int> q;

        dist[source] = 0;
        q.push(source);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor : adj[node]) {
                if (dist[neighbor] == -1) {
                    dist[neighbor] = dist[node] + 1;
                    parent[neighbor] = node;   // track who discovered this node
                    q.push(neighbor);
                }
            }
        }

        return {dist, parent};
    }

    // Reconstruct path from source to destination
    vector<int> getPath(int source, int dest, vector<int>& parent) {
        if (parent[dest] == -1 && dest != source) {
            return {};  // unreachable
        }

        vector<int> path;
        for (int v = dest; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(all(path));
        return path;
    }

    /*
    Dry Run (source=0, dest=4):

        BFS runs, parent[] gets filled:
        parent = [-1, 0, 0, 1, 3]
                  ↑   ↑  ↑  ↑  ↑
                  0   1  2  3  4

        Meaning:
          0's parent = -1 (source, no parent)
          1's parent = 0  (discovered by 0)
          2's parent = 0  (discovered by 0)
          3's parent = 1  (discovered by 1)
          4's parent = 3  (discovered by 3)

        Reconstruct path to 4:
          Start at 4 → parent = 3
          At 3 → parent = 1
          At 1 → parent = 0
          At 0 → parent = -1 → STOP

        Path (reversed): 0 → 1 → 3 → 4  ✓
        Distance: 3  ✓
    */

    void run() {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
        }

        int source, dest;
        cin >> source >> dest;

        auto [dist, parent] = bfs_with_parent(source, adj, n);
        vector<int> path = getPath(source, dest, parent);

        if (path.empty()) {
            cout << "No path exists!" << nl;
        } else {
            cout << "Shortest distance: " << dist[dest] << nl;
            cout << "Path: ";
            for (int i = 0; i < sz(path); i++) {
                cout << path[i];
                if (i + 1 < sz(path)) cout << " → ";
            }
            cout << nl;
        }
    }
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 6: BFS LEVEL-BY-LEVEL TRAVERSAL
═══════════════════════════════════════════════════════════════════════════════

  Sometimes we need to process nodes level by level
  (e.g., tree level order, shortest path counting).

  Technique: Process all nodes at current level before moving to next.
  Use the queue size to know how many nodes are at the current level.
*/

namespace LevelBFS {

    void bfs_levels(int start, vector<vector<int>>& adj, int n) {
        vector<bool> visited(n, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);
        int level = 0;

        while (!q.empty()) {
            int levelSize = q.size();  // nodes at THIS level
            cout << "Level " << level << ": ";

            for (int i = 0; i < levelSize; i++) {
                int node = q.front();
                q.pop();
                cout << node << " ";

                for (int neighbor : adj[node]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
            cout << nl;
            level++;
        }
    }

    /*
    Dry Run (same graph, start=0):

        Queue: [0]
        Level 0: levelSize=1
          Pop 0, push 1,2   → Queue: [1, 2]
          Output: "Level 0: 0"

        Level 1: levelSize=2
          Pop 1, push 3     → Queue: [2, 3]
          Pop 2, push -     → Queue: [3]     (0,3 already visited)
          Output: "Level 1: 1 2"

        Level 2: levelSize=1
          Pop 3, push 4     → Queue: [4]
          Output: "Level 2: 3"

        Level 3: levelSize=1
          Pop 4, push -     → Queue: []
          Output: "Level 3: 4"

        Full Output:
          Level 0: 0
          Level 1: 1 2
          Level 2: 3
          Level 3: 4
    */
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 7: CONNECTED COMPONENTS USING BFS
═══════════════════════════════════════════════════════════════════════════════

  Same idea as DFS connected components, but using BFS.
  Run BFS from each unvisited node → each BFS = one component.
*/

namespace ConnectedComponentsBFS {

    void bfs(int start, vector<vector<int>>& adj, vector<bool>& visited,
             vector<int>& component) {
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            component.push_back(node);

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
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
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                count++;
                vector<int> comp;
                bfs(i, adj, visited, comp);
                cout << "Component " << count << ": ";
                for (int v : comp) cout << v << " ";
                cout << nl;
            }
        }
        cout << "Total: " << count << " components" << nl;
    }
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 8: BIPARTITE CHECK USING BFS (2-Coloring)
═══════════════════════════════════════════════════════════════════════════════

  Same idea as DFS bipartite, but using BFS:
    • Color source with 0
    • Color all neighbors with 1
    • Color their neighbors with 0
    • If conflict (neighbor has SAME color) → NOT bipartite

  A graph is bipartite ⟺ no odd-length cycle exists.
*/

namespace BipartiteBFS {

    bool isBipartite(int n, vector<vector<int>>& adj) {
        vector<int> color(n, -1);

        for (int start = 0; start < n; start++) {
            if (color[start] != -1) continue;  // already colored

            queue<int> q;
            color[start] = 0;
            q.push(start);

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (int neighbor : adj[node]) {
                    if (color[neighbor] == -1) {
                        color[neighbor] = 1 - color[node];  // opposite color
                        q.push(neighbor);
                    }
                    else if (color[neighbor] == color[node]) {
                        // Same color → conflict → NOT bipartite!
                        return false;
                    }
                }
            }
        }
        return true;
    }

    /*
    Dry Run — Bipartite graph (square: 0-1, 1-2, 2-3, 3-0):

        color = [-1, -1, -1, -1]

        Start BFS from 0: color[0] = 0
        Queue: [0]

        Pop 0: neighbors 1, 3
          color[1] = 1-0 = 1 → push 1
          color[3] = 1-0 = 1 → push 3
        Queue: [1, 3]

        Pop 1: neighbors 0, 2
          color[0] = 0 ≠ color[1]=1 → OK
          color[2] = 1-1 = 0 → push 2
        Queue: [3, 2]

        Pop 3: neighbors 2, 0
          color[2] = 0 ≠ color[3]=1 → OK ✓
          color[0] = 0 ≠ color[3]=1 → OK ✓
        Queue: [2]

        Pop 2: neighbors 1, 3
          color[1] = 1 ≠ color[2]=0 → OK ✓
          color[3] = 1 ≠ color[2]=0 → OK ✓
        Queue: []

        Result: Bipartite! ✓  Colors: [0, 1, 0, 1]

        Visualization:
          Color 0: {0, 2}     Color 1: {1, 3}
            0(R) ── 1(B)
            |       |
            3(B) ── 2(R)

    ───────────────────────────────────────────────────────────
    Dry Run — NOT bipartite (triangle: 0-1, 1-2, 2-0):

        color[0] = 0, push 0
        Pop 0: color[1] = 1, color[2] = 1
        Pop 1: color[2] = 1 == color[1] = 1 → CONFLICT! Not bipartite ✗
    */
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 9: CYCLE DETECTION USING BFS
═══════════════════════════════════════════════════════════════════════════════

  Undirected Graph:
    Cycle exists if we find a visited neighbor that is NOT the parent.
    (Same logic as DFS, but implemented with BFS.)

  Directed Graph:
    Use Kahn's Algorithm (Part 14). If topological sort doesn't include
    all nodes → cycle exists.
*/

namespace CycleDetectionBFS {

    // Undirected graph cycle detection using BFS
    bool hasCycle(int n, vector<vector<int>>& adj) {
        vector<bool> visited(n, false);

        for (int start = 0; start < n; start++) {
            if (visited[start]) continue;

            queue<pii> q;  // {node, parent}
            visited[start] = true;
            q.push({start, -1});

            while (!q.empty()) {
                auto [node, parent] = q.front();
                q.pop();

                for (int neighbor : adj[node]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push({neighbor, node});
                    }
                    else if (neighbor != parent) {
                        // Visited and not parent → CYCLE!
                        return true;
                    }
                }
            }
        }
        return false;
    }

    /*
    Dry Run (cycle: 0-1, 1-2, 2-0):

        BFS from 0: visited[0]=true, push (0,-1)
        Pop (0,-1): neighbors 1, 2
          visited[1]=true, push (1,0)
          visited[2]=true, push (2,0)

        Pop (1,0): neighbors 0, 2
          0: visited, == parent → skip
          2: visited, ≠ parent(0) → CYCLE FOUND! ✓
    */
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 10: BFS ON GRID / 2D MATRIX (Shortest Path in Maze)
═══════════════════════════════════════════════════════════════════════════════

  Grid BFS is THE most common BFS application in CP & interviews!

  Grid = implicit graph:
    • Each cell (i,j) is a node
    • Edges go to 4 (or 8) adjacent cells
    • Walls/obstacles = blocked cells

  🏆 BFS on grid finds SHORTEST PATH (minimum steps) from source to target!

  Common problems:
    • Shortest path through maze
    • Minimum steps to reach destination
    • Nearest exit from entrance
    • Count islands (also doable with DFS)
*/

namespace GridBFS {

    int dx[] = {-1, 1, 0, 0};  // up, down, left, right
    int dy[] = {0, 0, -1, 1};

    // ═══════════════════════════════════════════
    // 10A: Shortest Path in a Maze
    // ═══════════════════════════════════════════
    /*
        Grid (0=free, 1=wall):
        0 0 0 0 0
        0 1 1 0 0
        0 0 0 0 1
        1 1 0 0 0

        Start: (0,0)  End: (3,4)
        Find minimum steps.

        Shortest path:
        S → → ↓         S = start, E = end
              ↓
            ← ↓
            ↓
            → → → E
        Steps: 7
    */

    int shortestPath(vector<vector<int>>& grid, pii start, pii end) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> dist(n, vector<int>(m, -1));
        queue<pii> q;

        dist[start.first][start.second] = 0;
        q.push(start);

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            if (x == end.first && y == end.second) {
                return dist[x][y];  // found shortest path!
            }

            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];

                // Check bounds, not wall, not visited
                if (nx >= 0 && nx < n && ny >= 0 && ny < m
                    && grid[nx][ny] == 0 && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }

        return -1;  // unreachable
    }

    /*
    Dry Run (simplified 3×3 grid, no walls):
        Grid:         Start (0,0) → End (2,2)
        0 0 0
        0 0 0
        0 0 0

        dist after BFS:
        0  1  2
        1  2  3
        2  3  4

        Minimum steps from (0,0) to (2,2) = 4

        BFS expansion (level by level):
        Level 0: (0,0)
        Level 1: (0,1), (1,0)
        Level 2: (0,2), (1,1), (2,0)
        Level 3: (1,2), (2,1)
        Level 4: (2,2)  ← FOUND!

        Visual:
        0 → 1 → 2
        ↓   ↓   ↓
        1 → 2 → 3
        ↓   ↓   ↓
        2 → 3 → 4
    */

    // ═══════════════════════════════════════════
    // 10B: Count Islands (BFS version)
    // ═══════════════════════════════════════════
    void bfs_island(int sx, int sy, vector<vector<int>>& grid,
                    vector<vector<bool>>& visited) {
        int n = grid.size(), m = grid[0].size();
        queue<pii> q;
        visited[sx][sy] = true;
        q.push({sx, sy});

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m
                    && !visited[nx][ny] && grid[nx][ny] == 1) {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
    }

    int countIslands(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int count = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    count++;
                    bfs_island(i, j, grid, visited);
                }
            }
        }
        return count;
    }
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 11: MULTI-SOURCE BFS (Fire Spread, Rotten Oranges)
═══════════════════════════════════════════════════════════════════════════════

  🧠 Key Idea: Instead of starting BFS from ONE source, start from
  MULTIPLE sources simultaneously! Push ALL sources into queue at once.

  This simulates things spreading from multiple points:
    • Fire spreading from multiple fires
    • Rotten oranges rotting adjacent oranges
    • Flood filling from multiple points
    • Distance from nearest '1' for every cell

  ⚡ Super useful pattern — asked in Google, Amazon, Facebook interviews!
*/

namespace MultiSourceBFS {

    // ═══════════════════════════════════════════
    // 11A: Rotten Oranges (LeetCode 994)
    // ═══════════════════════════════════════════
    /*
        Grid: 0=empty, 1=fresh orange, 2=rotten orange
        Each minute, rotten oranges rot their 4-directional neighbors.
        Return minimum time to rot all oranges, or -1 if impossible.

        Example:
        2 1 1       2 2 1       2 2 2       2 2 2       2 2 2
        1 1 0  →(1) 2 1 0  →(2) 2 2 0  →(3) 2 2 0  →(4) 2 2 0
        0 1 1       0 1 1       0 1 1       0 2 1       0 2 2

        Answer: 4 minutes
    */

    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        queue<pii> q;
        int fresh = 0;

        // Step 1: Push ALL rotten oranges as sources
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 2) q.push({i, j});
                if (grid[i][j] == 1) fresh++;
            }
        }

        if (fresh == 0) return 0;  // no fresh oranges

        int time = 0;

        // Step 2: BFS level by level
        while (!q.empty()) {
            int sz = q.size();
            bool rotted = false;

            for (int i = 0; i < sz; i++) {
                auto [x, y] = q.front();
                q.pop();

                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d], ny = y + dy[d];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m
                        && grid[nx][ny] == 1) {
                        grid[nx][ny] = 2;  // rot it!
                        fresh--;
                        q.push({nx, ny});
                        rotted = true;
                    }
                }
            }
            if (rotted) time++;
        }

        return fresh == 0 ? time : -1;
    }

    // ═══════════════════════════════════════════
    // 11B: Distance from Nearest 0 (LeetCode 542)
    // ═══════════════════════════════════════════
    /*
        For each cell, find distance to nearest '0'.
        Multi-source BFS: start from ALL 0s simultaneously!

        Input:          Output:
        0 0 0           0 0 0
        0 1 0    →      0 1 0
        1 1 1           1 2 1
    */

    vector<vector<int>> nearestZero(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        vector<vector<int>> dist(n, vector<int>(m, -1));
        queue<pii> q;

        // Push all 0s as sources
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 0) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        // BFS from all 0s simultaneously
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m
                    && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }

        return dist;
    }

    /*
    Dry Run (3×3 grid):
        Input:     Initial dist:     After BFS:
        0 0 0      0  0  0           0  0  0
        0 1 0     →0 -1  0      →    0  1  0
        1 1 1     -1 -1 -1           1  2  1

        Sources in queue: (0,0),(0,1),(0,2),(1,0),(1,2)
        Level 0: Process all 0s → dist set for them
        Level 1: (1,1) gets dist=1, (2,0) gets dist=1, (2,2) gets dist=1
        Level 2: (2,1) gets dist=2

        Visualization:
        0 → 0 → 0
        ↓       ↓
        0   1   0
        ↓   ↑   ↓
        1 → 2 ← 1
    */
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 12: 0-1 BFS (Deque BFS — Edges with Weight 0 or 1)
═══════════════════════════════════════════════════════════════════════════════

  🧠 What if edges have weights 0 or 1?
    Normal BFS doesn't work (it assumes all weights = 1).
    Dijkstra works but is O((V+E) log V) — overkill!

  0-1 BFS: Use a DEQUE instead of a queue!
    • Weight 0 edge → push to FRONT (high priority)
    • Weight 1 edge → push to BACK  (normal priority)

  This maintains the invariant that the deque is always sorted by distance.
  Time Complexity: O(V + E) — same as normal BFS!

  When to use:
    • Grid problems with "free" vs "costly" moves
    • "Flip at most K obstacles" type problems
    • Any shortest path with only two distinct weights
*/

namespace ZeroOneBFS {

    // Edge with weight: {neighbor, weight}
    vector<int> bfs01(int source, vector<vector<pii>>& adj, int n) {
        vector<int> dist(n, INF);
        deque<int> dq;

        dist[source] = 0;
        dq.push_front(source);

        while (!dq.empty()) {
            int node = dq.front();
            dq.pop_front();

            for (auto [neighbor, weight] : adj[node]) {
                int newDist = dist[node] + weight;
                if (newDist < dist[neighbor]) {
                    dist[neighbor] = newDist;
                    if (weight == 0)
                        dq.push_front(neighbor);  // 0-weight → front
                    else
                        dq.push_back(neighbor);   // 1-weight → back
                }
            }
        }

        return dist;
    }

    /*
    Example Graph (edges with 0 or 1 weights):
        0 →(1)→ 1 →(0)→ 2
        |                |
       (0)              (1)
        ↓                ↓
        3 →(1)→ 4 →(0)→ 5

    dist from 0:
        dist[0] = 0
        dist[3] = 0 (0-weight edge)
        dist[1] = 1
        dist[2] = 1 (0→1→2: 1+0=1)
        dist[4] = 1 (0→3→4: 0+1=1)
        dist[5] = 1 (0→3→4→5: 0+1+0=1)

    Dry Run:
        Deque: [0]  dist[0]=0
        Pop 0:
          → 1 (w=1): dist[1]=1, push_back → Deque: [1]
          → 3 (w=0): dist[3]=0, push_front → Deque: [3, 1]

        Pop 3 (front, dist=0):
          → 4 (w=1): dist[4]=1, push_back → Deque: [1, 4]

        Pop 1 (front, dist=1):
          → 2 (w=0): dist[2]=1, push_front → Deque: [2, 4]

        Pop 2 (front, dist=1):
          → 5 (w=1): dist[5]=2, push_back → Deque: [4, 5]

        Pop 4 (front, dist=1):
          → 5 (w=0): dist[5]=min(2,1)=1, push_front → Deque: [5, 5]

        Pop 5: done
        Pop 5: already optimal → skip

        Result: dist = [0, 1, 1, 0, 1, 1] ✓
    */

    // ═══════════════════════════════════════════
    // 12A: Grid 0-1 BFS Example
    // ═══════════════════════════════════════════
    /*
        Grid with free paths (0) and walls that cost 1 to break:
          . . #
          . # .
          . . .
        '.' = weight 0, '#' = weight 1

        Shortest cost from (0,0) to (2,2)?
        Optimal: go down-down-right-right = cost 0
        Or: (0,0)→(0,1)→(0,2 break #, cost 1)→... compare paths
    */

    int gridBFS01(vector<string>& grid, pii start, pii end) {
        int n = grid.size(), m = grid[0].size();
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        vector<vector<int>> dist(n, vector<int>(m, INF));
        deque<pii> dq;

        dist[start.first][start.second] = 0;
        dq.push_front(start);

        while (!dq.empty()) {
            auto [x, y] = dq.front();
            dq.pop_front();

            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    int w = (grid[nx][ny] == '#') ? 1 : 0;
                    if (dist[x][y] + w < dist[nx][ny]) {
                        dist[nx][ny] = dist[x][y] + w;
                        if (w == 0)
                            dq.push_front({nx, ny});
                        else
                            dq.push_back({nx, ny});
                    }
                }
            }
        }

        return dist[end.first][end.second];
    }
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 13: BFS ON IMPLICIT GRAPHS (State-Space Search)
═══════════════════════════════════════════════════════════════════════════════

  🧠 Sometimes the "graph" isn't given explicitly — you construct it
  from the problem's states and transitions.

  Examples:
    • Word Ladder: each word is a node, edges connect words differing by 1 letter
    • Sliding Puzzle: each board configuration is a node
    • Knight moves on chessboard: each position is a node

  The graph is IMPLICIT — you generate neighbors on-the-fly during BFS.
*/

namespace ImplicitBFS {

    // ═══════════════════════════════════════════
    // 13A: Knight's Minimum Moves on Chessboard
    // ═══════════════════════════════════════════
    /*
        Given N×N chessboard, find minimum moves for a knight
        to go from (sx,sy) to (ex,ey).

        Knight moves: (±1,±2) and (±2,±1) → 8 possible moves

        Example: N=8, (0,0) → (7,7)
        Answer: 6 moves
    */

    int knightMoves(int n, pii start, pii end) {
        // 8 knight move directions
        int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
        int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

        vector<vector<int>> dist(n, vector<int>(n, -1));
        queue<pii> q;

        dist[start.first][start.second] = 0;
        q.push(start);

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            if (x == end.first && y == end.second) {
                return dist[x][y];
            }

            for (int d = 0; d < 8; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < n && ny >= 0 && ny < n
                    && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }

        return -1;  // unreachable
    }

    // ═══════════════════════════════════════════
    // 13B: Word Ladder (LeetCode 127)
    // ═══════════════════════════════════════════
    /*
        Transform "hit" → "cog" changing one letter at a time,
        each intermediate word must be in dictionary.

        hit → hot → dot → dog → cog
        Answer: 5 (length of transformation sequence)
    */

    int wordLadder(string beginWord, string endWord, vector<string>& wordList) {
        set<string> dict(wordList.begin(), wordList.end());
        if (dict.find(endWord) == dict.end()) return 0;

        queue<string> q;
        q.push(beginWord);
        dict.erase(beginWord);
        int steps = 1;

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                string word = q.front();
                q.pop();

                if (word == endWord) return steps;

                // Try changing each character to a-z
                for (int j = 0; j < sz(word); j++) {
                    char orig = word[j];
                    for (char c = 'a'; c <= 'z'; c++) {
                        word[j] = c;
                        if (dict.count(word)) {
                            dict.erase(word);
                            q.push(word);
                        }
                    }
                    word[j] = orig;  // restore
                }
            }
            steps++;
        }
        return 0;  // no transformation possible
    }
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 14: TOPOLOGICAL SORT USING BFS (Kahn's Algorithm)
═══════════════════════════════════════════════════════════════════════════════

  BFS-based Topological Sort = Kahn's Algorithm

  🧠 Key Idea:
    1. Count in-degree of every node
    2. Push all nodes with in-degree 0 to queue (no dependencies)
    3. Pop from queue → add to result → reduce in-degree of neighbors
    4. If a neighbor's in-degree becomes 0 → push to queue
    5. If result size < n → CYCLE exists (some nodes never reached in-degree 0)

  This is often PREFERRED over DFS topological sort because:
    • Easier to detect cycles
    • Can be extended to count number of topological orders
    • More intuitive for dependency resolution problems
*/

namespace KahnTopoSort {

    vector<int> topoSort(int n, vector<vector<int>>& adj) {
        vector<int> indegree(n, 0);

        // Step 1: Calculate in-degrees
        for (int u = 0; u < n; u++) {
            for (int v : adj[u]) {
                indegree[v]++;
            }
        }

        // Step 2: Push all nodes with in-degree 0
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        // Step 3: Process
        vector<int> order;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            order.push_back(node);

            for (int neighbor : adj[node]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // Step 4: Check for cycle
        if (sz(order) != n) {
            cout << "CYCLE DETECTED! No valid topological order." << nl;
            return {};
        }

        return order;
    }

    /*
    Dry Run (DAG: 5→0, 4→0, 5→2, 4→1, 2→3, 3→1):

        adj[5]={0,2}, adj[4]={0,1}, adj[2]={3}, adj[3]={1}
        adj[0]={}, adj[1]={}

        In-degrees: [2, 2, 1, 1, 0, 0]
                     0  1  2  3  4  5

        Initial queue (indegree=0): [4, 5]

        Pop 4: order=[4]
          → neighbor 0: indegree[0]=2→1
          → neighbor 1: indegree[1]=2→1
        Queue: [5]

        Pop 5: order=[4, 5]
          → neighbor 0: indegree[0]=1→0 → push! Queue: [0]
          → neighbor 2: indegree[2]=1→0 → push! Queue: [0, 2]

        Pop 0: order=[4, 5, 0]
          → no neighbors
        Queue: [2]

        Pop 2: order=[4, 5, 0, 2]
          → neighbor 3: indegree[3]=1→0 → push! Queue: [3]

        Pop 3: order=[4, 5, 0, 2, 3]
          → neighbor 1: indegree[1]=1→0 → push! Queue: [1]

        Pop 1: order=[4, 5, 0, 2, 3, 1]
        Queue empty, order size = 6 = n → No cycle ✓

        Topological Order: [4, 5, 0, 2, 3, 1] ✓
        Verify all edges: 5→0(✓) 4→0(✓) 5→2(✓) 4→1(✓) 2→3(✓) 3→1(✓)
    */

    void run() {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            adj[u].pb(v);
        }

        vector<int> order = topoSort(n, adj);
        if (!order.empty()) {
            cout << "Topological Order: ";
            for (int v : order) cout << v << " ";
            cout << nl;
        }
    }
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 15: BFS ON TREES (Level Order, Zigzag, Right View)
═══════════════════════════════════════════════════════════════════════════════

  BFS on trees = Level Order Traversal
  This is VERY common in interview questions!
*/

namespace TreeBFS {

    // ═══════════════════════════════════════════
    // 15A: Level Order Traversal
    // ═══════════════════════════════════════════
    /*
        Tree:
              1
             / \
            2   3
           / \   \
          4   5   6

        Level Order: [[1], [2,3], [4,5,6]]
    */

    vector<vector<int>> levelOrder(int root, vector<vector<int>>& adj, int n) {
        vector<vector<int>> levels;
        vector<bool> visited(n + 1, false);
        queue<int> q;

        visited[root] = true;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> currentLevel;

            for (int i = 0; i < levelSize; i++) {
                int node = q.front();
                q.pop();
                currentLevel.push_back(node);

                for (int child : adj[node]) {
                    if (!visited[child]) {
                        visited[child] = true;
                        q.push(child);
                    }
                }
            }
            levels.push_back(currentLevel);
        }
        return levels;
    }

    // ═══════════════════════════════════════════
    // 15B: Zigzag Level Order
    // ═══════════════════════════════════════════
    /*
        Same tree, but alternate direction each level:
        Level 0 (L→R): [1]
        Level 1 (R→L): [3, 2]
        Level 2 (L→R): [4, 5, 6]
    */

    vector<vector<int>> zigzagOrder(int root, vector<vector<int>>& adj, int n) {
        vector<vector<int>> levels = levelOrder(root, adj, n);

        for (int i = 1; i < sz(levels); i += 2) {
            reverse(all(levels[i]));  // reverse odd levels
        }
        return levels;
    }

    // ═══════════════════════════════════════════
    // 15C: Right Side View (Last node at each level)
    // ═══════════════════════════════════════════
    /*
        Tree:        Right view: [1, 3, 6]
              1      (see from right side → last node at each level)
             / \
            2   3
           / \   \
          4   5   6
    */

    vector<int> rightView(int root, vector<vector<int>>& adj, int n) {
        vector<vector<int>> levels = levelOrder(root, adj, n);
        vector<int> result;
        for (auto& level : levels) {
            result.push_back(level.back());  // last element at each level
        }
        return result;
    }
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 16: BIDIRECTIONAL BFS (Meet in the Middle)
═══════════════════════════════════════════════════════════════════════════════

  🧠 Key Idea: Run BFS from BOTH source and target simultaneously.
  When the two searches MEET → shortest path found!

  Why it's faster:
    Normal BFS: explores O(b^d) nodes where b=branching, d=depth
    Bidirectional: explores O(2 × b^(d/2)) = O(b^(d/2))
    → EXPONENTIALLY faster for large d!

  When to use:
    • Know both source AND target
    • Branching factor is high
    • State space is large
*/

namespace BidirectionalBFS {

    int bidir_bfs(int source, int target, vector<vector<int>>& adj, int n) {
        if (source == target) return 0;

        vector<int> distS(n, -1), distT(n, -1);
        queue<int> qS, qT;

        distS[source] = 0;
        distT[target] = 0;
        qS.push(source);
        qT.push(target);

        while (!qS.empty() || !qT.empty()) {
            // Expand from source side (one level)
            if (!qS.empty()) {
                int levelSize = qS.size();
                for (int i = 0; i < levelSize; i++) {
                    int node = qS.front();
                    qS.pop();

                    for (int nbr : adj[node]) {
                        if (distS[nbr] == -1) {
                            distS[nbr] = distS[node] + 1;
                            qS.push(nbr);
                        }
                        // Check if target-side already reached this node
                        if (distT[nbr] != -1) {
                            return distS[nbr] + distT[nbr];
                        }
                    }
                }
            }

            // Expand from target side (one level)
            if (!qT.empty()) {
                int levelSize = qT.size();
                for (int i = 0; i < levelSize; i++) {
                    int node = qT.front();
                    qT.pop();

                    for (int nbr : adj[node]) {
                        if (distT[nbr] == -1) {
                            distT[nbr] = distT[node] + 1;
                            qT.push(nbr);
                        }
                        // Check if source-side already reached this node
                        if (distS[nbr] != -1) {
                            return distS[nbr] + distT[nbr];
                        }
                    }
                }
            }
        }

        return -1;  // no path
    }

    /*
    Visualization:

        Normal BFS from A to B (d=6):
        A ============================→ B
        Explores everything within distance 6 from A

        Bidirectional BFS:
        A ============→ M ←============ B
        Each side explores distance 3 → they MEET at M
        Total explored = much less!

    Dry Run (chain: 0-1-2-3-4-5, source=0, target=5):

        Source side:             Target side:
        distS: [0,-1,-1,-1,-1,-1] distT: [-1,-1,-1,-1,-1,0]

        Round 1:
          Source: expand 0 → discover 1 (distS[1]=1)
          Target: expand 5 → discover 4 (distT[4]=1)

        Round 2:
          Source: expand 1 → discover 2 (distS[2]=2)
          Target: expand 4 → discover 3 (distT[3]=2)

        Round 3:
          Source: expand 2 → discover 3 (distS[3]=3)
            → distT[3]=2 already set! → return 3+2 = 5 ✓
    */
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 17: MULTI-STATE BFS (Bitmask States, Keys & Doors)
═══════════════════════════════════════════════════════════════════════════════

  🧠 Sometimes the state isn't just (position), it's (position + extra info).
  The "extra info" can be:
    • Set of keys collected (bitmask)
    • Number of walls broken
    • Direction facing
    • Items carried

  State = (x, y, bitmask) or (x, y, walls_broken)
  visited[x][y][bitmask] or visited[x][y][k]
*/

namespace MultiStateBFS {

    // ═══════════════════════════════════════════
    // 17A: Shortest Path with Obstacle Removal (LeetCode 1293)
    // ═══════════════════════════════════════════
    /*
        Grid with obstacles. You can remove at most K obstacles.
        Find shortest path from (0,0) to (n-1,m-1).

        State: (row, col, obstacles_remaining)
    */

    int shortestPathWithRemovals(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size();
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        // visited[x][y][remaining_removals]
        vector<vector<vector<bool>>> visited(n, vector<vector<bool>>(m,
            vector<bool>(k + 1, false)));

        // State: {x, y, remaining_k}
        queue<tuple<int, int, int>> q;
        q.push({0, 0, k});
        visited[0][0][k] = true;
        int steps = 0;

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                auto [x, y, rem] = q.front();
                q.pop();

                if (x == n - 1 && y == m - 1) return steps;

                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d], ny = y + dy[d];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

                    int newRem = rem - grid[nx][ny]; // costs 1 removal if obstacle
                    if (newRem >= 0 && !visited[nx][ny][newRem]) {
                        visited[nx][ny][newRem] = true;
                        q.push({nx, ny, newRem});
                    }
                }
            }
            steps++;
        }

        return -1;
    }

    // ═══════════════════════════════════════════
    // 17B: Keys and Doors (LeetCode 864)
    // ═══════════════════════════════════════════
    /*
        Grid with keys (a-f) and doors (A-F).
        Door A can only be opened with key 'a'.
        Collect keys, open doors, find shortest path.

        State: (x, y, keys_bitmask)
        Key 'a' → bit 0, 'b' → bit 1, ..., 'f' → bit 5
        Max 6 keys → 2^6 = 64 possible key states

        Example:
        @ . a . #
        # # # . #
        . b A . B

        @ = start, keys: a,b  doors: A,B
    */

    int shortestPathWithKeys(vector<string>& grid) {
        int n = grid.size(), m = grid[0].size();
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        int totalKeys = 0;
        int sx = 0, sy = 0;

        // Find start and count keys
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '@') { sx = i; sy = j; }
                if (grid[i][j] >= 'a' && grid[i][j] <= 'f') totalKeys++;
            }
        }

        int allKeys = (1 << totalKeys) - 1;  // all keys collected

        // visited[x][y][keys_bitmask]
        vector<vector<vector<bool>>> visited(n, vector<vector<bool>>(m,
            vector<bool>(64, false)));

        queue<tuple<int, int, int>> q;
        q.push({sx, sy, 0});
        visited[sx][sy][0] = true;
        int steps = 0;

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                auto [x, y, keys] = q.front();
                q.pop();

                if (keys == allKeys) return steps;  // all keys collected!

                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d], ny = y + dy[d];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

                    char cell = grid[nx][ny];
                    if (cell == '#') continue;  // wall

                    int newKeys = keys;

                    // Door: check if we have the key
                    if (cell >= 'A' && cell <= 'F') {
                        if (!(keys & (1 << (cell - 'A')))) continue;  // no key
                    }

                    // Key: pick it up
                    if (cell >= 'a' && cell <= 'f') {
                        newKeys |= (1 << (cell - 'a'));
                    }

                    if (!visited[nx][ny][newKeys]) {
                        visited[nx][ny][newKeys] = true;
                        q.push({nx, ny, newKeys});
                    }
                }
            }
            steps++;
        }

        return -1;
    }
}

/*
═══════════════════════════════════════════════════════════════════════════════
PART 18: BFS vs DFS — WHEN TO USE WHICH?
═══════════════════════════════════════════════════════════════════════════════

  ┌─────────────────────────────────────────────────────────────────────────┐
  │              │     BFS                │     DFS                        │
  ├─────────────────────────────────────────────────────────────────────────┤
  │ Data struct  │ Queue (FIFO)           │ Stack / Recursion (LIFO)       │
  │ Order        │ Level by level         │ Go deep then backtrack         │
  │ Shortest path│ ✅ YES (unweighted)    │ ❌ NO                          │
  │ Memory       │ O(width of graph)      │ O(height of graph)             │
  │ Completeness │ Always finds solution  │ May go into infinite branch    │
  ├─────────────────────────────────────────────────────────────────────────┤
  │ USE BFS FOR:                                                          │
  │  ✅ Shortest path (unweighted)                                        │
  │  ✅ Level-order traversal                                             │
  │  ✅ Multi-source shortest distance                                    │
  │  ✅ Nearest/closest/minimum steps problems                            │
  │  ✅ Kahn's topological sort                                           │
  │  ✅ 0-1 weighted shortest path                                        │
  ├─────────────────────────────────────────────────────────────────────────┤
  │ USE DFS FOR:                                                          │
  │  ✅ Cycle detection                                                   │
  │  ✅ Topological sort                                                  │
  │  ✅ Connected / Strongly connected components                          │
  │  ✅ Bridges & Articulation points                                     │
  │  ✅ Backtracking (subsets, permutations, N-queens)                     │
  │  ✅ Euler tour / tree flattening                                      │
  │  ✅ Path existence (any path, not shortest)                           │
  ├─────────────────────────────────────────────────────────────────────────┤
  │ BOTH WORK FOR:                                                        │
  │  • Connectivity check                                                 │
  │  • Bipartite check                                                    │
  │  • Flood fill / Island count                                          │
  │  • Tree traversal                                                     │
  └─────────────────────────────────────────────────────────────────────────┘

  ⚡ RULE OF THUMB:
    "Need SHORTEST distance?" → BFS
    "Need to EXPLORE ALL paths / backtrack?" → DFS
    "Just need connectivity?" → Either works, DFS is simpler

═══════════════════════════════════════════════════════════════════════════════
PART 19: TIME & SPACE COMPLEXITY + COMMON MISTAKES
═══════════════════════════════════════════════════════════════════════════════

  ┌────────────────────────────────────────────────────────────────────────────┐
  │  Operation              │ Time         │ Space           │ Notes          │
  ├────────────────────────────────────────────────────────────────────────────┤
  │  Basic BFS              │ O(V + E)     │ O(V)            │                │
  │  BFS Shortest Path      │ O(V + E)     │ O(V)            │ Unweighted     │
  │  BFS on Grid            │ O(N × M)     │ O(N × M)        │                │
  │  Multi-Source BFS       │ O(V + E)     │ O(V)            │                │
  │  0-1 BFS                │ O(V + E)     │ O(V)            │ Deque          │
  │  Kahn's Topo Sort       │ O(V + E)     │ O(V)            │                │
  │  Bidirectional BFS      │ O(b^(d/2))   │ O(b^(d/2))      │ Meet in middle │
  │  Multi-State BFS        │ O(V×S + E×S) │ O(V×S)          │ S = states     │
  │  BFS on Tree            │ O(N)         │ O(N)            │ Level order    │
  └────────────────────────────────────────────────────────────────────────────┘

  ❌ COMMON MISTAKES:

  ❌ MISTAKE 1: Marking visited when POPPING instead of PUSHING
     → A node gets pushed multiple times → MLE or TLE!
     WRONG:  while(!q.empty()) { node = q.front(); q.pop();
                                  visited[node] = true; ... }
     RIGHT:  visited[nbr] = true; q.push(nbr);  // mark BEFORE push

  ❌ MISTAKE 2: Using BFS for weighted graphs
     → BFS only gives shortest path for UNWEIGHTED (or 0-1 weighted) graphs!
     → For general weights → use Dijkstra or Bellman-Ford

  ❌ MISTAKE 3: Forgetting to handle disconnected graphs
     → Always loop: for(int i=0; i<n; i++) if(!vis[i]) bfs(i);

  ❌ MISTAKE 4: Not checking grid bounds before accessing grid[nx][ny]
     → Always: if(nx>=0 && nx<n && ny>=0 && ny<m) THEN access

  ❌ MISTAKE 5: In multi-state BFS, forgetting to include state in visited
     → visited[x][y] is wrong if state includes keys/walls etc.
     → Need visited[x][y][state]

  ✅ TIP 1: dist[v] = -1 can double as visited check (saves space)
  ✅ TIP 2: For grid BFS, use direction arrays: dx[]={-1,1,0,0}, dy[]={0,0,-1,1}
  ✅ TIP 3: Level-by-level BFS: use int levelSize = q.size() at start of each level
  ✅ TIP 4: For shortest path problems, first think "Can BFS solve this?"

═══════════════════════════════════════════════════════════════════════════════
PART 20: PRACTICE PROBLEMS — GRADED BY DIFFICULTY
═══════════════════════════════════════════════════════════════════════════════

  🟢 BEGINNER (Learn the basics):
    1. CSES: Labyrinth                    → Grid BFS shortest path
    2. CSES: Message Route                → BFS shortest path + reconstruction
    3. LeetCode 200: Number of Islands    → BFS flood fill
    4. LeetCode 994: Rotting Oranges      → Multi-source BFS
    5. LeetCode 733: Flood Fill           → BFS/DFS grid

  🟡 INTERMEDIATE (Apply patterns):
    6.  CSES: Monsters                    → Multi-source BFS (escape before monster)
    7.  LeetCode 127: Word Ladder         → Implicit graph BFS
    8.  LeetCode 542: 01 Matrix           → Multi-source BFS
    9.  LeetCode 1091: Shortest Path Binary Matrix → Grid BFS (8-direction)
    10. CF 580C: Kefa and Park            → BFS on tree with conditions

  🔴 ADVANCED (Master level):
    11. CSES: Flight Routes               → BFS variant / Dijkstra
    12. LeetCode 1293: Shortest Path Grid Obstacle Removal → Multi-state BFS
    13. LeetCode 864: Shortest Path with Keys → Bitmask BFS
    14. CF 1063B: Labyrinth               → 0-1 BFS variant
    15. LeetCode 847: Shortest Path Visiting All Nodes → Bitmask BFS

  ⚫ GRANDMASTER (Competition level):
    16. CF 1572A: Book                    → Kahn's algorithm variant
    17. CF 1607E: Robot on the Board      → BFS on implicit state
    18. CSES: Game Routes                 → DAG BFS + DP
    19. CF 1900D: Small GCD               → Number theory + BFS
    20. AtCoder ABC 277E: Crystal Switches → Multi-state BFS with toggles

═══════════════════════════════════════════════════════════════════════════════
SUMMARY CHEAT SHEET
═══════════════════════════════════════════════════════════════════════════════

    ╔═══════════════════════════════════════════════════════════════════════╗
    ║  BFS = Explore level by level (BREADTH first)                      ║
    ║  Uses: Queue (FIFO)                                                ║
    ║  Time: O(V + E) | Space: O(V)                                     ║
    ║                                                                     ║
    ║  Core template:                                                     ║
    ║    queue<int> q;                                                   ║
    ║    dist[src] = 0; q.push(src);                                     ║
    ║    while (!q.empty()) {                                            ║
    ║        int u = q.front(); q.pop();                                 ║
    ║        for (int v : adj[u])                                        ║
    ║            if (dist[v] == -1) {                                    ║
    ║                dist[v] = dist[u] + 1;                              ║
    ║                q.push(v);                                          ║
    ║            }                                                       ║
    ║    }                                                               ║
    ║                                                                     ║
    ║  🏆 SUPERPOWER: Shortest path in unweighted graphs!                ║
    ║                                                                     ║
    ║  Variants:                                                          ║
    ║    • Multi-source BFS  → Push all sources at once                  ║
    ║    • 0-1 BFS           → Deque: 0-weight front, 1-weight back     ║
    ║    • Level-by-level    → Use q.size() at start of each level       ║
    ║    • Multi-state       → State = (pos, extra_info)                 ║
    ║    • Bidirectional     → BFS from both ends, meet in middle        ║
    ║    • Kahn's algorithm  → BFS topological sort using in-degree      ║
    ╚═══════════════════════════════════════════════════════════════════════╝
*/

// ═══════════════════════════════════════════════════════════════════════════════
// MAIN — Uncomment the section you want to test
// ═══════════════════════════════════════════════════════════════════════════════

void solve() {
    // Uncomment ONE of these to test:

    // BasicBFS::run();
    // ShortestPathBFS::run();
    // PathReconstruction::run();
    // ConnectedComponentsBFS::run();
    // KahnTopoSort::run();

    // For quick demo:
    cout << "=== BFS Masterclass ===" << nl;
    cout << "Uncomment a section in solve() to test!" << nl;
    cout << "Read the comments for complete theory & dry runs." << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}

