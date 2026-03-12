/*
╔══════════════════════════════════════════════════════════════════╗
║              03 — MULTI-SOURCE BFS                              ║
║              BFS from multiple starting points simultaneously   ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

Multi-source BFS starts BFS from MULTIPLE sources at once.
All sources are pushed into the queue at the beginning with dist=0.

This finds the MINIMUM DISTANCE from ANY source to each vertex.

═══════════════════════════════════════════════════════════════════
VISUALIZATION
═══════════════════════════════════════════════════════════════════

Problem: Given a grid with some fire cells ('F') and empty cells ('.'),
find the minimum distance from each empty cell to the nearest fire.

Grid:           Distances:
. . . . .       2 1 2 3 4
. F . . .       1 0 1 2 3
. . . . .       2 1 2 2 2
. . . F .       3 2 1 0 1
. . . . .       4 3 2 1 2

DRY RUN:
  Start: Push all F cells with dist=0
  Queue: [(1,1,0), (3,3,0)]   dist=0 for both fires

  Process (1,1): neighbors (0,1),(1,0),(1,2),(2,1) get dist=1
  Process (3,3): neighbors (2,3),(3,2),(3,4),(4,3) get dist=1
  ... wave expands outward from BOTH sources simultaneously

═══════════════════════════════════════════════════════════════════
TIME & SPACE COMPLEXITY
═══════════════════════════════════════════════════════════════════

  Time:  O(V + E)  — same as normal BFS!
  Space: O(V)      — queue + distance array

  KEY INSIGHT: Don't run BFS from each source separately!
  That would be O(k * (V+E)) where k = number of sources.
  Multi-source BFS does it in O(V+E) total.

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

// ============================================================
// EXAMPLE 1: Multi-source BFS on Grid
// Find distance from each cell to nearest special cell
// ============================================================

void solveGrid() {
    int R, C;
    cin >> R >> C;
    vec<string> grid(R);
    for (int i = 0; i < R; i++) cin >> grid[i];

    vvec<int> dist(R, vec<int>(C, -1));
    queue<pii> q;

    // Push ALL sources (fire cells) into queue at once
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == 'F') {
                dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 0 && nx < R && ny >= 0 && ny < C
                && grid[nx][ny] != '#' && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    cout << "Distance to nearest fire:" << nl;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (j > 0) cout << " ";
            if (dist[i][j] == -1) cout << "#";
            else cout << dist[i][j];
        }
        cout << nl;
    }
}

// ============================================================
// EXAMPLE 2: Multi-source BFS on Graph
// Given k special vertices, find min distance from any special vertex
// ============================================================

void solveGraph() {
    int n, m, k;
    cin >> n >> m >> k;

    vvec<int> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    vec<int> dist(n, -1);
    queue<int> q;

    // Read k sources and push all at once
    for (int i = 0; i < k; i++) {
        int s;
        cin >> s;
        s--;
        dist[s] = 0;
        q.push(s);
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    cout << "Min distance from any source:" << nl;
    for (int i = 0; i < n; i++) {
        cout << "  Vertex " << i+1 << ": " << dist[i] << nl;
    }
}

void solve() {
    int type;
    cin >> type;
    if (type == 1) solveGrid();
    else solveGraph();
}

/*
═══════════════════════════════════════════════════════════════════
SAMPLE INPUT/OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
2
1
5 5
.....
.F...
.....
...F.
.....
2
8 8 2
1 2
2 3
3 4
4 5
5 6
6 7
7 8
1 3
1 5

Output:
Distance to nearest fire:
2 1 2 3 4
1 0 1 2 3
2 1 2 2 2
3 2 1 0 1
4 3 2 1 2

Min distance from any source:
  Vertex 1: 0
  Vertex 2: 1
  Vertex 3: 1
  Vertex 4: 2
  Vertex 5: 0
  Vertex 6: 1
  Vertex 7: 2
  Vertex 8: 3

═══════════════════════════════════════════════════════════════════
KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
  ✅ Multi-source BFS = push ALL sources at once with dist=0
  ✅ Finds MINIMUM distance to ANY source
  ✅ Same O(V+E) complexity as single-source BFS
  ✅ Common in: fire spreading, nearest facility, border distance
  ✅ Think of it as adding a virtual source connected to all real sources
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

