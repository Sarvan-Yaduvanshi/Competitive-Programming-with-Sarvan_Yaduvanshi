/*
╔══════════════════════════════════════════════════════════════════╗
║              02 — GRAPH TERMINOLOGY                             ║
║              Degree, Path, Walk, Cycle, Components              ║
╚══════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS
─────────────────
1. Degree of a Node
2. Walk vs Path vs Trail
3. Cycle
4. Connected Components
5. Handshaking Lemma
6. Visualization & Dry Run
7. Working Code

═══════════════════════════════════════════════════════════════════
1. DEGREE OF A NODE
═══════════════════════════════════════════════════════════════════

UNDIRECTED GRAPH:
  degree(v) = number of edges incident to vertex v

DIRECTED GRAPH:
  in-degree(v)  = number of edges COMING INTO v
  out-degree(v) = number of edges GOING OUT of v
  degree(v)     = in-degree(v) + out-degree(v)

Example:
        1 ──── 2
        │    ╱ │
        │   ╱  │
        │  ╱   │
        3      4

  deg(1) = 2  (edges to 2, 3)
  deg(2) = 3  (edges to 1, 3, 4)
  deg(3) = 2  (edges to 1, 2)
  deg(4) = 1  (edge to 2)

═══════════════════════════════════════════════════════════════════
2. WALK vs PATH vs TRAIL
═══════════════════════════════════════════════════════════════════

WALK: A sequence of vertices where each adjacent pair is connected
      by an edge. Vertices AND edges CAN repeat.
      Example: 1 → 2 → 3 → 2 → 4 (vertex 2 repeats — OK)

TRAIL: A walk where NO EDGE repeats (but vertices can repeat).
       Example: 1 → 2 → 3 → 1 → 4 (no edge repeats)

PATH: A walk where NO VERTEX repeats (and therefore no edge repeats).
      Example: 1 → 2 → 3 → 4 (all unique vertices)

┌─────────────────────────────────────────────────────────────┐
│  Type  │ Vertex Repeat? │ Edge Repeat? │ Most Restrictive? │
├────────┼────────────────┼──────────────┼───────────────────┤
│  Walk  │      YES       │     YES      │        No         │
│  Trail │      YES       │     NO       │        Mid        │
│  Path  │      NO        │     NO       │        Yes        │
└─────────────────────────────────────────────────────────────┘

═══════════════════════════════════════════════════════════════════
3. CYCLE
═══════════════════════════════════════════════════════════════════

CYCLE: A path that starts and ends at the SAME vertex.
       Minimum cycle length:
         - Undirected graph: 3 (triangle)
         - Directed graph: 2 (or even 1 with self-loop)

Example of a cycle:
        1 → 2 → 3 → 1  (cycle of length 3)

        1 ─── 2
         ╲   │
          ╲  │
           ╲ │
            3

ACYCLIC GRAPH: A graph with NO cycles.
  - Undirected acyclic connected graph = TREE
  - Directed acyclic graph = DAG

═══════════════════════════════════════════════════════════════════
4. CONNECTED COMPONENTS
═══════════════════════════════════════════════════════════════════

A CONNECTED COMPONENT is a maximal set of vertices such that
there is a path between every pair of vertices in the set.

Example:
        1 ─── 2     4 ─── 5     7
        │           │
        3           6

  Component 1: {1, 2, 3}
  Component 2: {4, 5, 6}
  Component 3: {7}

  Number of connected components = 3

For DIRECTED graphs: we talk about
  - Weakly Connected Components (ignore edge directions)
  - Strongly Connected Components (respect edge directions)

═══════════════════════════════════════════════════════════════════
5. HANDSHAKING LEMMA
═══════════════════════════════════════════════════════════════════

THEOREM: In any undirected graph,
         Sum of all degrees = 2 × |E|

Why? Each edge contributes exactly 2 to the total degree sum
     (one for each endpoint).

COROLLARY: The number of vertices with ODD degree is always EVEN.

═══════════════════════════════════════════════════════════════════
6. VISUALIZATION & DRY RUN
═══════════════════════════════════════════════════════════════════

Graph:
    1 ─── 2 ─── 3
    │           │
    4     5 ─── 6     7 ─── 8

  Degrees: deg(1)=2, deg(2)=2, deg(3)=2, deg(4)=1,
           deg(5)=1, deg(6)=2, deg(7)=1, deg(8)=1

  Sum of degrees = 2+2+2+1+1+2+1+1 = 12
  Number of edges = 12/2 = 6 ✓

  Connected Components:
    CC1: {1, 2, 3, 4, 6, 5}  (1-2, 2-3, 1-4, 3-6, 5-6)
    CC2: {7, 8}               (7-8)

  Paths from 1 to 6:
    1 → 2 → 3 → 6  (length 3)
    1 → 4? No, 4 connects only to 1. So path is via 2→3→6.

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
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
#define fi first
#define se second
#define nl '\n'

template<class T>
void read(vec<T> &v) { for (auto &x : v) cin >> x; }

/*
═══════════════════════════════════════════════════════════════════
CODE: Compute degree, find connected components, check for cycles
═══════════════════════════════════════════════════════════════════

Time:  O(V + E)  — single DFS/BFS pass
Space: O(V + E)  — adjacency list + visited array
*/

void solve() {
    int n, m;
    cin >> n >> m;

    vvec<int> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    // --- DEGREE COMPUTATION ---
    cout << "=== Degrees ===" << nl;
    int sumDeg = 0;
    int oddDegCount = 0;
    for (int i = 0; i < n; i++) {
        int deg = sz(adj[i]);
        cout << "deg(" << i+1 << ") = " << deg << nl;
        sumDeg += deg;
        if (deg % 2 == 1) oddDegCount++;
    }
    cout << "Sum of degrees = " << sumDeg << " = 2 * " << m << nl;
    cout << "Vertices with odd degree = " << oddDegCount << " (always even!)" << nl;

    // --- CONNECTED COMPONENTS using BFS ---
    cout << nl << "=== Connected Components ===" << nl;
    vec<bool> visited(n, false);
    int numComponents = 0;

    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        numComponents++;

        // BFS from vertex i
        queue<int> q;
        q.push(i);
        visited[i] = true;
        vec<int> component;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            component.pb(u);
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        cout << "Component " << numComponents << ": {";
        for (int j = 0; j < sz(component); j++) {
            if (j > 0) cout << ", ";
            cout << component[j] + 1;
        }
        cout << "}" << nl;
    }

    cout << "Total connected components: " << numComponents << nl;

    // --- IS IT A TREE? ---
    // A graph is a tree if: connected (1 component) AND m == n-1
    if (numComponents == 1 && m == n - 1) {
        cout << "This graph is a TREE!" << nl;
    } else {
        cout << "This graph is NOT a tree." << nl;
    }
}

/*
═══════════════════════════════════════════════════════════════════
SAMPLE INPUT/OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
1
8 6
1 2
2 3
1 4
3 6
5 6
7 8

Output:
=== Degrees ===
deg(1) = 2
deg(2) = 2
deg(3) = 2
deg(4) = 1
deg(5) = 1
deg(6) = 2
deg(7) = 1
deg(8) = 1
Sum of degrees = 12 = 2 * 6
Vertices with odd degree = 4 (always even!)

=== Connected Components ===
Component 1: {1, 2, 4, 3, 6, 5}
Component 2: {7, 8}
Total connected components: 2
This graph is NOT a tree.

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

