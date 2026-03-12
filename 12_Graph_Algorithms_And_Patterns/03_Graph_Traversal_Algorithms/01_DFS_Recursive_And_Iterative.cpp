/*
╔══════════════════════════════════════════════════════════════════╗
║              01 — DFS: RECURSIVE & ITERATIVE                    ║
║              Depth-First Search — The Foundation                 ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

DFS (Depth-First Search) explores a graph by going as DEEP as
possible before backtracking.

  Algorithm:
  1. Start at a source vertex, mark it visited
  2. For each unvisited neighbor, recursively visit it
  3. Backtrack when all neighbors are visited

  Uses a STACK (explicit or via recursion call stack).

═══════════════════════════════════════════════════════════════════
VISUALIZATION & DRY RUN
═══════════════════════════════════════════════════════════════════

Graph (undirected):
    1 ─── 2
    │     │
    3 ─── 4 ─── 5
          │
          6

Adjacency List:
  1: [2, 3]
  2: [1, 4]
  3: [1, 4]
  4: [2, 3, 5, 6]
  5: [4]
  6: [4]

DFS from vertex 1 (recursive):
═══════════════════════════════════════════════════════════
Step │ Current │ Stack(call) │ Visited          │ Action
═══════════════════════════════════════════════════════════
  1  │    1    │ [1]         │ {1}              │ Visit 1, go to neighbor 2
  2  │    2    │ [1,2]       │ {1,2}            │ Visit 2, go to neighbor 4
  3  │    4    │ [1,2,4]     │ {1,2,4}          │ Visit 4, go to neighbor 3
  4  │    3    │ [1,2,4,3]   │ {1,2,4,3}        │ Visit 3, neighbors 1,4 visited
  5  │    3    │ [1,2,4]     │ {1,2,4,3}        │ Backtrack from 3
  6  │    4    │ [1,2,4]     │ {1,2,4,3}        │ Go to neighbor 5
  7  │    5    │ [1,2,4,5]   │ {1,2,4,3,5}      │ Visit 5, neighbor 4 visited
  8  │    5    │ [1,2,4]     │ {1,2,4,3,5}      │ Backtrack from 5
  9  │    4    │ [1,2,4]     │ {1,2,4,3,5}      │ Go to neighbor 6
 10  │    6    │ [1,2,4,6]   │ {1,2,4,3,5,6}    │ Visit 6, neighbor 4 visited
 11  │    6    │ [1,2,4]     │ {1,2,4,3,5,6}    │ Backtrack from 6
 12  │    4    │ [1,2]       │ {1,2,4,3,5,6}    │ Backtrack from 4
 13  │    2    │ [1]         │ {1,2,4,3,5,6}    │ Backtrack from 2
 14  │    1    │ []          │ {1,2,4,3,5,6}    │ Backtrack from 1, DONE
═══════════════════════════════════════════════════════════

DFS Order: 1, 2, 4, 3, 5, 6

═══════════════════════════════════════════════════════════════════
TIME & SPACE COMPLEXITY
═══════════════════════════════════════════════════════════════════

  Time:  O(V + E)  — visit each vertex once, check each edge once
  Space: O(V)      — visited array + recursion stack

  ⚠️ Recursion depth can be up to V (for a path graph).
     If V > 10⁵, use ITERATIVE DFS to avoid stack overflow!

═══════════════════════════════════════════════════════════════════
RECURSIVE vs ITERATIVE
═══════════════════════════════════════════════════════════════════

  RECURSIVE:
    ✅ Clean, easy to write
    ❌ Stack overflow for deep graphs (V > 10⁵)
    ❌ Cannot easily pause/resume

  ITERATIVE:
    ✅ No stack overflow
    ✅ Can handle any depth
    ❌ Slightly more code
    ⚠️ Different visit order than recursive (reversed neighbor order)

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

template<class T>
void read(vec<T> &v) { for (auto &x : v) cin >> x; }

// ============================================================
// METHOD 1: RECURSIVE DFS
// ============================================================
// Time: O(V + E)    Space: O(V) for visited + O(V) recursion stack

vvec<int> adj;
vec<bool> visited;
vec<int> dfsOrder;

void dfsRecursive(int u) {
    visited[u] = true;
    dfsOrder.pb(u);
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfsRecursive(v);
        }
    }
}

// ============================================================
// METHOD 2: ITERATIVE DFS (using explicit stack)
// ============================================================
// Time: O(V + E)    Space: O(V) for visited + O(V) for stack
// Note: visits neighbors in REVERSE order compared to recursive

vec<int> dfsIterative(int start, int n) {
    vec<bool> vis(n, false);
    vec<int> order;
    stack<int> st;

    st.push(start);

    while (!st.empty()) {
        int u = st.top(); st.pop();

        if (vis[u]) continue;  // already processed
        vis[u] = true;
        order.pb(u);

        // Push neighbors in reverse order to match recursive order
        for (int i = sz(adj[u]) - 1; i >= 0; i--) {
            int v = adj[u][i];
            if (!vis[v]) {
                st.push(v);
            }
        }
    }

    return order;
}

// ============================================================
// METHOD 3: DFS with entry/exit times (crucial for advanced algorithms)
// ============================================================

vec<int> tin, tout;
int timer_val = 0;

void dfsWithTimer(int u, int parent) {
    visited[u] = true;
    tin[u] = timer_val++;

    for (int v : adj[u]) {
        if (!visited[v]) {
            dfsWithTimer(v, u);
        }
    }

    tout[u] = timer_val++;
}

/*
  Entry/Exit times are useful for:
  ✅ Check if u is ancestor of v: tin[u] <= tin[v] && tout[v] <= tout[u]
  ✅ Euler tour for tree queries
  ✅ Bridge and articulation point detection
*/

void solve() {
    int n, m;
    cin >> n >> m;

    adj.assign(n, {});
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    // --- Recursive DFS ---
    visited.assign(n, false);
    dfsOrder.clear();

    cout << "=== Recursive DFS ===" << nl;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfsRecursive(i);
        }
    }
    cout << "Order: ";
    for (int i = 0; i < sz(dfsOrder); i++) {
        if (i > 0) cout << " → ";
        cout << dfsOrder[i] + 1;
    }
    cout << nl;

    // --- Iterative DFS ---
    cout << nl << "=== Iterative DFS ===" << nl;
    vec<int> iterOrder = dfsIterative(0, n);
    cout << "Order: ";
    for (int i = 0; i < sz(iterOrder); i++) {
        if (i > 0) cout << " → ";
        cout << iterOrder[i] + 1;
    }
    cout << nl;

    // --- DFS with Entry/Exit Times ---
    cout << nl << "=== DFS with Entry/Exit Times ===" << nl;
    visited.assign(n, false);
    tin.assign(n, 0);
    tout.assign(n, 0);
    timer_val = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfsWithTimer(i, -1);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i+1 << ": entry=" << tin[i] << ", exit=" << tout[i] << nl;
    }

    // Check ancestor relationships
    cout << nl << "Ancestor checks:" << nl;
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (u != v && tin[u] <= tin[v] && tout[v] <= tout[u]) {
                cout << u+1 << " is ancestor of " << v+1 << nl;
            }
        }
    }
}

/*
═══════════════════════════════════════════════════════════════════
SAMPLE INPUT/OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
1
6 6
1 2
1 3
2 4
3 4
4 5
4 6

Output:
=== Recursive DFS ===
Order: 1 → 2 → 4 → 3 → 5 → 6

=== Iterative DFS ===
Order: 1 → 2 → 4 → 3 → 5 → 6

=== DFS with Entry/Exit Times ===
Vertex 1: entry=0, exit=11
Vertex 2: entry=1, exit=10
Vertex 3: entry=4, exit=5
Vertex 4: entry=2, exit=9
Vertex 5: entry=3, exit=6   (note: may vary)
Vertex 6: entry=7, exit=8

═══════════════════════════════════════════════════════════════════
KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
  ✅ DFS is O(V + E) — visits every vertex and edge exactly once
  ✅ Use recursive for clean code, iterative for large graphs
  ✅ Entry/exit times enable O(1) ancestor checks
  ✅ DFS is the basis for: topological sort, SCC, bridges, tree DP
  ✅ Always handle disconnected graphs!
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

