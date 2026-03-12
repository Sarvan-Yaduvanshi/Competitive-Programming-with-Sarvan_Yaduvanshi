/*
╔══════════════════════════════════════════════════════════════════╗
║              02 — FLOOD FILL                                    ║
║              Paint connected region with new color              ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION: Starting from cell (sr,sc), change all connected cells
with the same original color to a new color.

DRY RUN:
  Grid (colors 1-3):     After flood fill from (1,1) with color 3:
  1 1 1                  3 3 3
  1 1 0         →        3 3 0
  1 0 1                  3 0 1

Time: O(R×C)    Space: O(R×C)
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
#define nl '\n'

void solve() {
    int R, C;
    cin >> R >> C;
    vvec<int> grid(R, vec<int>(C));
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            cin >> grid[i][j];

    int sr, sc, newColor;
    cin >> sr >> sc >> newColor;
    sr--; sc--;

    int origColor = grid[sr][sc];
    if (origColor == newColor) {
        // No change needed
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) cout << grid[i][j] << " \n"[j==C-1];
        }
        return;
    }

    // BFS flood fill
    int dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};
    queue<pii> q;
    q.push({sr, sc});
    grid[sr][sc] = newColor;

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x+dx[d], ny = y+dy[d];
            if (nx >= 0 && nx < R && ny >= 0 && ny < C && grid[nx][ny] == origColor) {
                grid[nx][ny] = newColor;
                q.push({nx, ny});
            }
        }
    }

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) cout << grid[i][j] << " \n"[j==C-1];
    }
}

/*
Input: 1\n3 3\n1 1 1\n1 1 0\n1 0 1\n1 1 3
Output:
3 3 3
3 3 0
3 0 1
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

