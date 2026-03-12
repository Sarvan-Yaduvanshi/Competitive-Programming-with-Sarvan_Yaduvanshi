/*
╔══════════════════════════════════════════════════════════════════╗
║              04 — FLOYD-WARSHALL ALGORITHM                      ║
║              All-Pairs Shortest Path O(V³)                      ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

Floyd-Warshall finds shortest paths between ALL pairs of vertices.

IDEA (Dynamic Programming):
  dist[i][j][k] = shortest path from i to j using only
                   vertices {1, 2, ..., k} as intermediates.

  dist[i][j][k] = min(dist[i][j][k-1],
                       dist[i][k][k-1] + dist[k][j][k-1])

  We optimize space by updating in-place (2D array).

ALGORITHM:
  for k = 0 to n-1:          // intermediate vertex
    for i = 0 to n-1:        // source
      for j = 0 to n-1:      // destination
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

═══════════════════════════════════════════════════════════════════
DRY RUN
═══════════════════════════════════════════════════════════════════

Graph: 1→2(3), 1→3(8), 2→3(2), 3→1(5)

Initial dist matrix:
     1    2    3
1  [ 0    3    8  ]
2  [ ∞    0    2  ]
3  [ 5    ∞    0  ]

k=1 (through vertex 1):
  dist[2][3] = min(2, ∞+8) = 2 (no change)
  dist[3][2] = min(∞, 5+3) = 8

k=2 (through vertex 2):
  dist[1][3] = min(8, 3+2) = 5 ← improved!
  dist[3][1] = min(5, 8+∞) = 5

k=3 (through vertex 3):
  dist[1][2] = min(3, 5+8) = 3
  dist[2][1] = min(∞, 2+5) = 7 ← improved!

Final:
     1    2    3
1  [ 0    3    5  ]
2  [ 7    0    2  ]
3  [ 5    8    0  ]

═══════════════════════════════════════════════════════════════════
COMPLEXITY
  Time:  O(V³)
  Space: O(V²)

  ✅ Handles negative weights
  ✅ Detects negative cycles: dist[i][i] < 0
  ✅ Very simple to code (3 nested loops)
  ❌ Only for small V (≤ 400-500)
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
constexpr i64 INF64 = 4e18;
#define nl '\n'

void solve() {
    int n, m;
    cin >> n >> m;

    vvec<i64> dist(n, vec<i64>(n, INF64));
    for (int i = 0; i < n; i++) dist[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v; i64 w;
        cin >> u >> v >> w; u--; v--;
        dist[u][v] = min(dist[u][v], w);  // handle multi-edges
    }

    // Floyd-Warshall: THE 3 LOOPS (order k, i, j is CRITICAL!)
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF64 && dist[k][j] != INF64) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Check for negative cycles
    bool negCycle = false;
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) { negCycle = true; break; }
    }

    if (negCycle) {
        cout << "Negative cycle detected!" << nl;
        return;
    }

    // Print all-pairs distances
    cout << "All-pairs shortest distances:" << nl;
    cout << "     ";
    for (int j = 0; j < n; j++) cout << setw(5) << j+1;
    cout << nl;
    for (int i = 0; i < n; i++) {
        cout << setw(3) << i+1 << " [";
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF64) cout << "  INF";
            else cout << setw(5) << dist[i][j];
        }
        cout << " ]" << nl;
    }
}

/*
Input: 1\n3 3\n1 2 3\n1 3 8\n2 3 2
Output:
All-pairs shortest distances:
         1    2    3
  1 [    0    3    5 ]
  2 [  INF    0    2 ]
  3 [  INF  INF    0 ]
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

