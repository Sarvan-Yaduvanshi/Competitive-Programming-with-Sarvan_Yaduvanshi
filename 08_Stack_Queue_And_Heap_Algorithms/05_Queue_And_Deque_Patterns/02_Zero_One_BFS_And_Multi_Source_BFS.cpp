/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — 0-1 BFS & MULTI-SOURCE BFS                                    ║
║           From Zero to Grandmaster — Queue & Deque Patterns                 ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

0-1 BFS:
───────
  Shortest path in graph with edge weights 0 or 1.
  Use DEQUE instead of priority queue!
  - Weight 0 edge → push_front (treat like same distance)
  - Weight 1 edge → push_back (treat like next distance)

  Why it works: Deque maintains sorted distance order naturally.
  Time: O(V + E) — much better than Dijkstra's O((V+E) log V)

DRY RUN: Grid with walls (1) and empty (0)
  0 1 0
  0 0 1
  1 0 0

  From (0,0) to (2,2), cost = number of walls broken.
  Moving to wall cell costs 1, empty cell costs 0.

  dist: [[0, 1, 1],
         [0, 0, 1],
         [1, 0, 0]]
  Answer: 0 (path: (0,0)→(1,0)→(1,1)→(2,1)→(2,2), all zeros)

MULTI-SOURCE BFS:
────────────────
  BFS from MULTIPLE starting points simultaneously.
  Push ALL sources into queue initially.
  Classic problems: Rotten oranges, nearest gate, nearest 0.

  DRY RUN (Rotten Oranges):
  Grid: 2 1 1    (2=rotten, 1=fresh, 0=empty)
        1 1 0
        0 1 1

  Start: push all 2s into queue: [(0,0)]
  Level 0: rot (0,0) neighbors → (0,1), (1,0) become rotten
  Level 1: rot (0,1),(1,0) → (0,2),(1,1) become rotten
  Level 2: rot (0,2),(1,1) → (2,1) becomes rotten
  Level 3: rot (2,1) → (2,2) becomes rotten
  Answer: 4 minutes ✅
*/

#include <iostream>
#include <deque>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// 0-1 BFS: Minimum cost to reach bottom-right (wall breaking)
// ═══════════════════════════════════════════════════════════════

int zerOneBFS(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    deque<pair<int,int>> dq;

    dist[0][0] = grid[0][0];
    dq.push_front({0, 0});

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!dq.empty()) {
        auto [x, y] = dq.front();
        dq.pop_front();

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

            int newDist = dist[x][y] + grid[nx][ny];
            if (newDist < dist[nx][ny]) {
                dist[nx][ny] = newDist;
                if (grid[nx][ny] == 0)
                    dq.push_front({nx, ny});   // 0-weight → front
                else
                    dq.push_back({nx, ny});    // 1-weight → back
            }
        }
    }
    return dist[n-1][m-1];
}

// ═══════════════════════════════════════════════════════════════
// MULTI-SOURCE BFS: Rotten Oranges (LC 994)
// ═══════════════════════════════════════════════════════════════

int orangesRotting(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    queue<pair<int,int>> q;
    int fresh = 0;

    // Push all rotten oranges (multiple sources)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 2) q.push({i, j});
            else if (grid[i][j] == 1) fresh++;
        }
    }

    if (fresh == 0) return 0;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    int minutes = 0;

    while (!q.empty()) {
        int sz = q.size();
        bool rotted = false;
        for (int i = 0; i < sz; i++) {
            auto [x, y] = q.front();
            q.pop();
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1) {
                    grid[nx][ny] = 2;
                    fresh--;
                    q.push({nx, ny});
                    rotted = true;
                }
            }
        }
        if (rotted) minutes++;
    }

    return fresh == 0 ? minutes : -1;
}

// ═══════════════════════════════════════════════════════════════
// MULTI-SOURCE BFS: 01 Matrix — Distance to Nearest 0 (LC 542)
// ═══════════════════════════════════════════════════════════════

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    queue<pair<int,int>> q;

    // Push all 0s as sources
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mat[i][j] == 0) {
                dist[i][j] = 0;
                q.push({i, j});
            }

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                dist[nx][ny] > dist[x][y] + 1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    return dist;
}

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  0-1 BFS & MULTI-SOURCE BFS                              ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // 0-1 BFS
    cout << "═══ 0-1 BFS (Wall Breaking) ═══\n";
    vector<vector<int>> grid = {{0,1,0},{0,0,1},{1,0,0}};
    cout << "Grid:\n";
    for (auto& row : grid) {
        cout << "  ";
        for (int x : row) cout << x << " ";
        cout << "\n";
    }
    cout << "Min walls to break: " << zerOneBFS(grid) << "\n\n";

    // Rotten Oranges
    cout << "═══ ROTTEN ORANGES (LC 994) ═══\n";
    vector<vector<int>> oranges = {{2,1,1},{1,1,0},{0,1,1}};
    cout << "Minutes to rot all: " << orangesRotting(oranges) << "\n\n";

    // 01 Matrix
    cout << "═══ 01 MATRIX (LC 542) ═══\n";
    vector<vector<int>> mat = {{0,0,0},{0,1,0},{1,1,1}};
    auto dist = updateMatrix(mat);
    cout << "Distance to nearest 0:\n";
    for (auto& row : dist) {
        cout << "  ";
        for (int x : row) cout << x << " ";
        cout << "\n";
    }

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE:\n";
    cout << "  LC 994  — Rotting Oranges\n";
    cout << "  LC 542  — 01 Matrix\n";
    cout << "  LC 1293 — Shortest Path with Obstacles Elimination\n";
    cout << "  CF — 0-1 BFS problems in Codeforces\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

