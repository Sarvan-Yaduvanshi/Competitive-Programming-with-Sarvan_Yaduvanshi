/*
╔══════════════════════════════════════════════════════════════════╗
║              01 — ADJACENCY MATRIX                              ║
║              O(1) edge lookup, O(V²) space                     ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

An ADJACENCY MATRIX is a 2D array A[n][n] where:
  A[i][j] = 1 if there's an edge from i to j
  A[i][j] = 0 otherwise
  (For weighted: A[i][j] = weight of edge, or INF if no edge)

═══════════════════════════════════════════════════════════════════
VISUALIZATION
═══════════════════════════════════════════════════════════════════

Graph:
    1 ─── 2
    │   ╱
    │  ╱
    3 ─── 4

Edges: (1,2), (1,3), (2,3), (3,4)

Matrix (1-indexed):
       1  2  3  4
    1 [0  1  1  0]
    2 [1  0  1  0]
    3 [1  1  0  1]
    4 [0  0  1  0]

Properties:
  ✅ Symmetric for undirected graphs: A[i][j] = A[j][i]
  ✅ Diagonal is 0 (no self-loops): A[i][i] = 0
  ✅ Sum of row i = degree of vertex i

═══════════════════════════════════════════════════════════════════
WHEN TO USE
═══════════════════════════════════════════════════════════════════

  ✅ Small n (≤ 500-1000)
  ✅ Dense graphs (many edges)
  ✅ Floyd-Warshall (needs matrix)
  ✅ Need O(1) edge existence check
  ✅ Matrix exponentiation for path counting

  ❌ Large n (> 10000) — too much memory
  ❌ Sparse graphs — wastes space

═══════════════════════════════════════════════════════════════════
COMPLEXITY
═══════════════════════════════════════════════════════════════════

  ┌────────────────────────────────────────────────┐
  │  Operation              │  Complexity          │
  ├─────────────────────────┼──────────────────────┤
  │  Space                  │  O(V²)               │
  │  Add edge               │  O(1)                │
  │  Remove edge            │  O(1)                │
  │  Check if edge exists   │  O(1)                │
  │  Find all neighbors     │  O(V)                │
  │  Build from input       │  O(V² + E)           │
  └────────────────────────────────────────────────┘

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

constexpr int INF32 = 2e9;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

template<class T>
void read(vec<T> &v) { for (auto &x : v) cin >> x; }

void solve() {
    int n, m;
    cin >> n >> m;

    // --- Build Adjacency Matrix ---
    vvec<int> mat(n, vec<int>(n, 0));

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        mat[u][v] = 1;
        mat[v][u] = 1;  // undirected
    }

    // --- Print Matrix ---
    cout << "Adjacency Matrix:" << nl;
    cout << "    ";
    for (int j = 0; j < n; j++) cout << j + 1 << " ";
    cout << nl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << " [ ";
        for (int j = 0; j < n; j++) {
            cout << mat[i][j] << " ";
        }
        cout << "]" << nl;
    }

    // --- Check edge existence O(1) ---
    cout << nl << "Edge queries:" << nl;
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        cout << "Edge (" << u+1 << "," << v+1 << "): "
             << (mat[u][v] ? "EXISTS" : "NOT FOUND") << nl;
    }

    // --- Count edges (from matrix) ---
    int edgeCount = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (mat[i][j]) edgeCount++;
    cout << nl << "Total edges: " << edgeCount << nl;
}

/*
═══════════════════════════════════════════════════════════════════
SAMPLE INPUT/OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
1
4 4
1 2
1 3
2 3
3 4
3
1 2
1 4
3 4

Output:
Adjacency Matrix:
    1 2 3 4
1 [ 0 1 1 0 ]
2 [ 1 0 1 0 ]
3 [ 1 1 0 1 ]
4 [ 0 0 1 0 ]

Edge queries:
Edge (1,2): EXISTS
Edge (1,4): NOT FOUND
Edge (3,4): EXISTS

Total edges: 4

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

