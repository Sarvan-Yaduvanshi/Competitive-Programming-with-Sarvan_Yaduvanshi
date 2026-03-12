/*
╔══════════════════════════════════════════════════════════════════╗
║              04 — IMPLICIT GRAPHS                               ║
║              Grids, Knight Moves, State Graphs                  ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

An IMPLICIT GRAPH is one where edges are NOT given explicitly.
Instead, edges are defined by RULES.

Examples:
  1. Grid: cell (i,j) connects to (i±1,j) and (i,j±1)
  2. Knight: from (r,c), can reach 8 positions
  3. Word ladder: words connected if differ by 1 letter
  4. Number puzzle: states connected by valid moves

You DON'T build an adjacency list — you compute neighbors on-the-fly.

═══════════════════════════════════════════════════════════════════
GRID AS IMPLICIT GRAPH
═══════════════════════════════════════════════════════════════════

  Grid:         Vertex encoding: cell(i,j) = i * C + j
  . . # .       Edges: 4-directional (or 8-directional)
  . # . .
  . . . #       Vertex count: R * C
  . . . .       Edge count: ≈ 4 * R * C

  Direction arrays:
    4-dir: dx={0,0,1,-1}, dy={1,-1,0,0}
    8-dir: add diagonals: dx={-1,-1,-1,0,0,1,1,1}
                          dy={-1,0,1,-1,1,-1,0,1}

═══════════════════════════════════════════════════════════════════
KNIGHT MOVES AS IMPLICIT GRAPH
═══════════════════════════════════════════════════════════════════

  From position (r,c), a chess knight can move to:
    (r±1, c±2) and (r±2, c±1)  →  8 possible moves

      . . X . X . .
      . X . . . X .
      . . . K . . .
      . X . . . X .
      . . X . X . .

  This creates an implicit graph perfect for BFS shortest path.

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

/*
═══════════════════════════════════════════════════════════════════
EXAMPLE 1: BFS on Grid (Shortest path from top-left to bottom-right)
Time: O(R * C)   Space: O(R * C)
═══════════════════════════════════════════════════════════════════
*/
void gridBFS() {
    int R, C;
    cin >> R >> C;
    vec<string> grid(R);
    for (int i = 0; i < R; i++) cin >> grid[i];

    // BFS from (0,0) to (R-1,C-1)
    vvec<int> dist(R, vec<int>(C, -1));
    queue<pii> q;

    if (grid[0][0] == '.') {
        dist[0][0] = 0;
        q.push({0, 0});
    }

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 0 && nx < R && ny >= 0 && ny < C
                && grid[nx][ny] == '.' && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    cout << "Shortest path length: " << dist[R-1][C-1] << nl;
}

/*
═══════════════════════════════════════════════════════════════════
EXAMPLE 2: Knight Minimum Moves (BFS)
Time: O(N²)   Space: O(N²)   where N = board size
═══════════════════════════════════════════════════════════════════
*/
void knightBFS() {
    int N, sr, sc, er, ec;
    cin >> N >> sr >> sc >> er >> ec;
    sr--; sc--; er--; ec--;

    vvec<int> dist(N, vec<int>(N, -1));
    queue<pii> q;
    dist[sr][sc] = 0;
    q.push({sr, sc});

    // Knight's 8 moves
    int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (r == er && c == ec) break;
        for (int d = 0; d < 8; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr >= 0 && nr < N && nc >= 0 && nc < N && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    cout << "Knight min moves: " << dist[er][ec] << nl;
}

void solve() {
    int type;
    cin >> type;
    if (type == 1) gridBFS();
    else knightBFS();
}

/*
═══════════════════════════════════════════════════════════════════
SAMPLE INPUT/OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
2
1
4 4
....
.##.
..#.
....
2
8 1 1 8 8

Output:
Shortest path length: 6
Knight min moves: 6
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

