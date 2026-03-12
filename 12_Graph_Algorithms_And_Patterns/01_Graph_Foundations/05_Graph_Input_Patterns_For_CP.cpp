/*
╔══════════════════════════════════════════════════════════════════╗
║              05 — GRAPH INPUT PATTERNS FOR CP                    ║
║              How to read graphs in competitive programming       ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
COMMON INPUT FORMATS IN COMPETITIVE PROGRAMMING
═══════════════════════════════════════════════════════════════════

FORMAT 1: Edge List (Most Common)
─────────────────────────────────
  First line: n m (vertices, edges)
  Next m lines: u v (or u v w for weighted)

  Example:
    5 4
    1 2
    2 3
    3 4
    4 5

FORMAT 2: Adjacency List Style
───────────────────────────────
  First line: n
  Next n lines: k v1 v2 ... vk (k neighbors listed)

FORMAT 3: Parent Array (for Trees)
──────────────────────────────────
  First line: n
  Next line: p2 p3 ... pn (parent of each node 2..n)

FORMAT 4: Grid/Matrix
─────────────────────
  First line: R C (rows, cols)
  Next R lines: grid characters

  Example:
    3 4
    ....
    .##.
    ....

FORMAT 5: Implicit Graph (no edges given)
─────────────────────────────────────────
  Edges defined by rules (e.g., chess knight moves,
  digit changes, etc.)

═══════════════════════════════════════════════════════════════════
KEY PITFALLS IN CP
═══════════════════════════════════════════════════════════════════

  ⚠️  1-indexed vs 0-indexed (most CP uses 1-indexed!)
  ⚠️  Multiple edges between same pair (multi-graph)
  ⚠️  Self-loops (edge from u to u)
  ⚠️  Disconnected graph (don't assume connected!)
  ⚠️  Large n but small m (sparse) — use adjacency list
  ⚠️  Directed vs undirected — read problem carefully!

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
// PATTERN 1: Unweighted Undirected Graph
// ============================================================
void readUnweightedUndirected() {
    int n, m;
    cin >> n >> m;
    vvec<int> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;  // 0-indexed
        adj[u].pb(v);
        adj[v].pb(u);
    }
    cout << "Read undirected unweighted graph: " << n << " vertices, " << m << " edges" << nl;
}

// ============================================================
// PATTERN 2: Weighted Directed Graph
// ============================================================
void readWeightedDirected() {
    int n, m;
    cin >> n >> m;
    vec<vec<pii>> adj(n);  // adj[u] = {(v, w), ...}
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].pb({v, w});
    }
    cout << "Read directed weighted graph: " << n << " vertices, " << m << " edges" << nl;
}

// ============================================================
// PATTERN 3: Tree from Parent Array
// ============================================================
void readTreeFromParent() {
    int n;
    cin >> n;
    vvec<int> adj(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;  // 0-indexed
        adj[p].pb(i);
        adj[i].pb(p);
    }
    cout << "Read tree from parent array: " << n << " vertices" << nl;
}

// ============================================================
// PATTERN 4: Grid Graph (implicit)
// ============================================================
void readGrid() {
    int R, C;
    cin >> R >> C;
    vec<string> grid(R);
    for (int i = 0; i < R; i++) cin >> grid[i];

    // Implicit edges: 4-directional neighbors
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    int edgeCount = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == '#') continue;  // wall
            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d], nj = j + dy[d];
                if (ni >= 0 && ni < R && nj >= 0 && nj < C && grid[ni][nj] != '#') {
                    edgeCount++;
                }
            }
        }
    }
    cout << "Grid " << R << "x" << C << " with " << edgeCount / 2 << " implicit edges" << nl;
}

// ============================================================
// PATTERN 5: Weighted Undirected with Edge List (for Kruskal)
// ============================================================
struct Edge {
    int u, v, w;
    bool operator<(const Edge& o) const { return w < o.w; }
};

void readEdgeList() {
    int n, m;
    cin >> n >> m;
    vec<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].u--; edges[i].v--;
    }
    sort(all(edges));  // sorted by weight — ready for Kruskal!
    cout << "Read edge list: " << n << " vertices, " << m << " edges (sorted by weight)" << nl;
}

void solve() {
    int type;
    cin >> type;

    switch (type) {
        case 1: readUnweightedUndirected(); break;
        case 2: readWeightedDirected(); break;
        case 3: readTreeFromParent(); break;
        case 4: readGrid(); break;
        case 5: readEdgeList(); break;
    }
}

/*
═══════════════════════════════════════════════════════════════════
SAMPLE INPUT/OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
5
1
5 4
1 2
2 3
3 4
4 5
2
4 3
1 2 5
2 3 3
3 4 1
3
5
1 1 2 2
4
3 4
....
.##.
....
5
4 5
1 2 3
1 3 1
2 3 2
2 4 5
3 4 4

Output:
Read undirected unweighted graph: 5 vertices, 4 edges
Read directed weighted graph: 4 vertices, 3 edges
Read tree from parent array: 5 vertices
Grid 3x4 with 14 implicit edges
Read edge list: 4 vertices, 5 edges (sorted by weight)

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

