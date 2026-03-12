/*
╔══════════════════════════════════════════════════════════════════╗
║              04 — DFS TREE & EDGE CLASSIFICATION                ║
║              Tree, Back, Forward, Cross Edges                   ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

When we run DFS on a graph, we create a DFS TREE.
Every edge in the original graph falls into one of 4 categories:

1. TREE EDGE: Edge (u,v) where v is first discovered via u.
   These edges form the DFS tree.

2. BACK EDGE: Edge (u,v) where v is an ANCESTOR of u in DFS tree.
   → Back edges indicate CYCLES!

3. FORWARD EDGE: Edge (u,v) where v is a DESCENDANT of u (but not tree edge).
   (Only in directed graphs)

4. CROSS EDGE: Edge (u,v) where v is neither ancestor nor descendant.
   (Only in directed graphs)

═══════════════════════════════════════════════════════════════════
VISUALIZATION
═══════════════════════════════════════════════════════════════════

Directed Graph:         DFS Tree:
  1 → 2                   1
  1 → 3                  / \
  2 → 4                 2   3
  3 → 4                 |
  4 → 1                 4

Edge Classification:
  (1→2): TREE edge     (discovers 2)
  (2→4): TREE edge     (discovers 4)
  (4→1): BACK edge     (1 is ancestor of 4 → CYCLE: 1→2→4→1)
  (1→3): TREE edge     (discovers 3)
  (3→4): CROSS edge    (4 already fully processed, not ancestor/descendant)

═══════════════════════════════════════════════════════════════════
HOW TO CLASSIFY (using colors)
═══════════════════════════════════════════════════════════════════

  Use 3 colors for each vertex:
    WHITE (0): Not yet discovered
    GRAY  (1): Currently being processed (in recursion stack)
    BLACK (2): Fully processed (all descendants visited)

  When processing edge (u → v):
    v is WHITE → TREE edge (explore v)
    v is GRAY  → BACK edge (v is ancestor, CYCLE detected!)
    v is BLACK → FORWARD or CROSS edge
      - tin[u] < tin[v] → FORWARD edge
      - tin[u] > tin[v] → CROSS edge

  For UNDIRECTED graphs:
    Only TREE edges and BACK edges exist!
    (No forward/cross edges)

═══════════════════════════════════════════════════════════════════
WHY THIS MATTERS
═══════════════════════════════════════════════════════════════════

  BACK EDGE → Cycle detection
  TREE EDGE → DFS tree structure (bridges, articulation points)
  CROSS EDGE → SCC algorithms need this understanding
  Edge classification is fundamental to Tarjan's algorithms

═══════════════════════════════════════════════════════════════════
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

using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;

#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

int n, m;
vvec<int> adj;
vec<int> color;  // 0=white, 1=gray, 2=black
vec<int> tin, tout;
int timer_val;

int treeEdges, backEdges, forwardEdges, crossEdges;

void dfs(int u) {
    color[u] = 1;  // GRAY
    tin[u] = timer_val++;

    for (int v : adj[u]) {
        if (color[v] == 0) {
            // TREE EDGE
            cout << "  (" << u+1 << " → " << v+1 << "): TREE edge" << nl;
            treeEdges++;
            dfs(v);
        } else if (color[v] == 1) {
            // BACK EDGE (v is gray = in current path = ancestor)
            cout << "  (" << u+1 << " → " << v+1 << "): BACK edge (CYCLE!)" << nl;
            backEdges++;
        } else {
            // color[v] == 2 (BLACK)
            if (tin[u] < tin[v]) {
                // FORWARD EDGE
                cout << "  (" << u+1 << " → " << v+1 << "): FORWARD edge" << nl;
                forwardEdges++;
            } else {
                // CROSS EDGE
                cout << "  (" << u+1 << " → " << v+1 << "): CROSS edge" << nl;
                crossEdges++;
            }
        }
    }

    color[u] = 2;  // BLACK
    tout[u] = timer_val++;
}

void solve() {
    cin >> n >> m;

    adj.assign(n, {});
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);  // DIRECTED graph
    }

    color.assign(n, 0);
    tin.assign(n, 0);
    tout.assign(n, 0);
    timer_val = 0;
    treeEdges = backEdges = forwardEdges = crossEdges = 0;

    cout << "Edge Classification:" << nl;
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) dfs(i);
    }

    cout << nl << "Summary:" << nl;
    cout << "  Tree edges:    " << treeEdges << nl;
    cout << "  Back edges:    " << backEdges << " (each = a cycle)" << nl;
    cout << "  Forward edges: " << forwardEdges << nl;
    cout << "  Cross edges:   " << crossEdges << nl;
    cout << "  Has cycle: " << (backEdges > 0 ? "YES" : "NO") << nl;

    cout << nl << "Entry/Exit times:" << nl;
    for (int i = 0; i < n; i++) {
        cout << "  " << i+1 << ": [" << tin[i] << ", " << tout[i] << "]" << nl;
    }
}

/*
═══════════════════════════════════════════════════════════════════
SAMPLE INPUT/OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
1
6 8
1 2
1 3
2 4
4 1
4 5
3 4
5 6
6 4

Output:
Edge Classification:
  (1 → 2): TREE edge
  (2 → 4): TREE edge
  (4 → 1): BACK edge (CYCLE!)
  (4 → 5): TREE edge
  (5 → 6): TREE edge
  (6 → 4): BACK edge (CYCLE!)
  (1 → 3): TREE edge
  (3 → 4): CROSS edge

Summary:
  Tree edges:    5
  Back edges:    2 (each = a cycle)
  Forward edges: 0
  Cross edges:   1
  Has cycle: YES

═══════════════════════════════════════════════════════════════════
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    return 0;
}

