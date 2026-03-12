/*
╔══════════════════════════════════════════════════════════════════╗
║              01 — COUNT ISLANDS (Flood Fill on Grid)             ║
║              Classic DFS/BFS Grid Problem                       ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

Given a 2D grid of '1' (land) and '0' (water), count the number
of ISLANDS. An island is a group of '1's connected 4-directionally.

This is equivalent to: Count connected components in a grid graph.

═══════════════════════════════════════════════════════════════════
VISUALIZATION & DRY RUN
═══════════════════════════════════════════════════════════════════

Grid:
  1 1 0 0 0
  1 1 0 0 0
  0 0 1 0 0
  0 0 0 1 1

Step-by-step:
  Scan (0,0): '1', not visited → Start DFS → Island #1
    DFS visits: (0,0)→(0,1)→(1,0)→(1,1)
    Mark all as visited.

  Scan (0,2),(0,3),(0,4): '0', skip
  Scan (1,0)...(1,4): already visited or '0'

  Scan (2,2): '1', not visited → Start DFS → Island #2
    DFS visits: (2,2)

  Scan (3,3): '1', not visited → Start DFS → Island #3
    DFS visits: (3,3)→(3,4)

  Answer: 3 islands

  Island visualization:
  A A 0 0 0        A = island 1
  A A 0 0 0        B = island 2
  0 0 B 0 0        C = island 3
  0 0 0 C C

═══════════════════════════════════════════════════════════════════
COMPLEXITY
═══════════════════════════════════════════════════════════════════
  Time:  O(R × C) — visit each cell once
  Space: O(R × C) — visited array (or modify grid in-place)

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
#include <queue>
using namespace std;

template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

int R, C;
vec<string> grid;
vvec<bool> visited;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

// DFS flood fill
void dfs(int x, int y) {
    visited[x][y] = true;
    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx >= 0 && nx < R && ny >= 0 && ny < C
            && !visited[nx][ny] && grid[nx][ny] == '1') {
            dfs(nx, ny);
        }
    }
}

// BFS flood fill (alternative — safer for large grids)
void bfs(int sx, int sy) {
    queue<pii> q;
    q.push({sx, sy});
    visited[sx][sy] = true;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 0 && nx < R && ny >= 0 && ny < C
                && !visited[nx][ny] && grid[nx][ny] == '1') {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
}

void solve() {
    cin >> R >> C;
    grid.resize(R);
    for (int i = 0; i < R; i++) cin >> grid[i];

    visited.assign(R, vec<bool>(C, false));
    int islands = 0;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == '1' && !visited[i][j]) {
                islands++;
                bfs(i, j);  // or dfs(i, j)
            }
        }
    }

    cout << "Number of islands: " << islands << nl;
}

/*
═══════════════════════════════════════════════════════════════════
SAMPLE INPUT/OUTPUT

Input:
1
4 5
11000
11000
00100
00011

Output:
Number of islands: 3
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

