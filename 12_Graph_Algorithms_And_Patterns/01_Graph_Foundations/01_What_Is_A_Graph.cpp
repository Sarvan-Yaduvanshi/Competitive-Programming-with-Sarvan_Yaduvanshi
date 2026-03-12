/*
╔══════════════════════════════════════════════════════════════════╗
║              01 — WHAT IS A GRAPH?                               ║
║              Graph Foundations                                   ║
╚══════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS
─────────────────
1. Definition of a Graph
2. Vertices (Nodes) and Edges
3. Real-World Examples
4. Graph Notation
5. Visualization & Dry Run
6. Complexity Notes
7. Working Code
8. Key Takeaways

═══════════════════════════════════════════════════════════════════
1. DEFINITION OF A GRAPH
═══════════════════════════════════════════════════════════════════

A GRAPH G = (V, E) is a mathematical structure consisting of:
  • V = Set of VERTICES (also called NODES)
  • E = Set of EDGES (connections between pairs of vertices)

An edge connects two vertices. If vertex u is connected to vertex v,
we write the edge as (u, v).

Think of it like a social network:
  - People = Vertices
  - Friendships = Edges

═══════════════════════════════════════════════════════════════════
2. VERTICES (NODES) AND EDGES
═══════════════════════════════════════════════════════════════════

VERTEX (Node):
  - A fundamental unit of a graph
  - Represents an entity (person, city, state, etc.)
  - Usually labeled with numbers: 0, 1, 2, ... or 1, 2, 3, ...

EDGE:
  - A connection between two vertices
  - Represents a relationship (friendship, road, dependency)
  - Can be DIRECTED (one-way) or UNDIRECTED (two-way)
  - Can have a WEIGHT (cost, distance, capacity)

═══════════════════════════════════════════════════════════════════
3. REAL-WORLD EXAMPLES
═══════════════════════════════════════════════════════════════════

┌─────────────────────────────────────────────────────────────┐
│ Real World          │ Vertices        │ Edges               │
├─────────────────────┼─────────────────┼─────────────────────┤
│ Social Network      │ People          │ Friendships         │
│ Road Map            │ Cities          │ Roads               │
│ Internet            │ Computers       │ Cables              │
│ Course Prerequisites│ Courses         │ Dependencies        │
│ Chess Board         │ Squares         │ Valid Moves         │
│ Web Pages           │ Pages           │ Hyperlinks          │
└─────────────────────────────────────────────────────────────┘

═══════════════════════════════════════════════════════════════════
4. GRAPH NOTATION
═══════════════════════════════════════════════════════════════════

  |V| = n = number of vertices
  |E| = m = number of edges

  For an UNDIRECTED graph:
    - Maximum edges = n*(n-1)/2  (complete graph)
    - Minimum edges = 0          (no connections)

  For a DIRECTED graph:
    - Maximum edges = n*(n-1)    (complete directed graph)
    - Minimum edges = 0

═══════════════════════════════════════════════════════════════════
5. VISUALIZATION & DRY RUN
═══════════════════════════════════════════════════════════════════

Example: A simple undirected graph with 5 vertices and 6 edges

    V = {0, 1, 2, 3, 4}
    E = {(0,1), (0,2), (1,2), (1,3), (2,4), (3,4)}

    Visual:

        0 ─── 1
        │   ╱ │
        │  ╱  │
        │ ╱   │
        2     3
         ╲   ╱
          ╲ ╱
           4

    Properties:
    - |V| = 5 (5 vertices)
    - |E| = 6 (6 edges)
    - Undirected (edges go both ways)
    - Unweighted (no costs on edges)
    - Connected (can reach any vertex from any other)
    - Contains cycles (e.g., 0→1→2→0)

═══════════════════════════════════════════════════════════════════
6. COMPLEXITY NOTES
═══════════════════════════════════════════════════════════════════

  Most graph algorithms have complexity in terms of V and E:
  - BFS/DFS: O(V + E)
  - Dijkstra: O((V + E) log V)
  - Floyd-Warshall: O(V³)

  Space:
  - Adjacency List: O(V + E)
  - Adjacency Matrix: O(V²)

═══════════════════════════════════════════════════════════════════
7. KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════

  ✅ A graph = vertices + edges
  ✅ Graphs model relationships between entities
  ✅ Key parameters: n (vertices), m (edges)
  ✅ In CP, graphs are usually given as edge lists in input
  ✅ Always check: directed? weighted? 1-indexed?

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
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

template<class T>
void read(vec<T> &v) {
    for (auto &x : v) cin >> x;
}
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

inline i64 gcd(i64 a, i64 b) { return std::gcd(a, b); }
inline i64 lcm(i64 a, i64 b) { return (a / std::gcd(a, b)) * b; }

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD) {
    i64 res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

/*
═══════════════════════════════════════════════════════════════════
DEMONSTRATION: Building and printing a simple graph
═══════════════════════════════════════════════════════════════════
*/

void solve() {
    // Read number of vertices and edges
    int n, m;
    cin >> n >> m;

    // Build adjacency list (undirected graph)
    vvec<int> adj(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;  // Convert to 0-indexed
        adj[u].pb(v);
        adj[v].pb(u);  // undirected: add both directions
    }

    // Print the adjacency list
    cout << "Graph with " << n << " vertices and " << m << " edges:" << nl;
    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i + 1 << " -> ";
        for (int j = 0; j < sz(adj[i]); j++) {
            if (j > 0) cout << ", ";
            cout << adj[i][j] + 1;
        }
        cout << nl;
    }

    // Print degree of each vertex
    cout << nl << "Degrees:" << nl;
    for (int i = 0; i < n; i++) {
        cout << "deg(" << i + 1 << ") = " << sz(adj[i]) << nl;
    }

    // Verify handshaking lemma: sum of degrees = 2 * |E|
    int sumDeg = 0;
    for (int i = 0; i < n; i++) sumDeg += sz(adj[i]);
    cout << nl << "Sum of degrees = " << sumDeg << " = 2 * " << m << nl;
}

/*
═══════════════════════════════════════════════════════════════════
SAMPLE INPUT/OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
1
5 6
1 2
1 3
2 3
2 4
3 5
4 5

Output:
Graph with 5 vertices and 6 edges:
Vertex 1 -> 2, 3
Vertex 2 -> 1, 3, 4
Vertex 3 -> 1, 2, 5
Vertex 4 -> 2, 5
Vertex 5 -> 3, 4

Degrees:
deg(1) = 2
deg(2) = 3
deg(3) = 3
deg(4) = 2
deg(5) = 2

Sum of degrees = 12 = 2 * 6

═══════════════════════════════════════════════════════════════════
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    int TC = 1;
    cin >> TC;
    while (TC--) solve();

    return 0;
}

