/*
╔══════════════════════════════════════════════════════════════════╗
║         01 — 0-1 BFS ADVANCED + STATE GRAPH MODELING            ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
MULTI-LAYER / STATE GRAPH
═══════════════════════════════════════════════════════════════════

Many advanced problems require modeling the graph with extra state
dimensions. Examples:

1. GRID WITH WALL REMOVAL (k walls removable):
   State: (row, col, walls_removed)
   Edge weights: 0 (free cell) or 1 (wall, costs one removal)
   → 0-1 BFS on state (r, c, k)

2. MINIMUM OPERATIONS TO REACH TARGET:
   State: (value, operations_used)
   → BFS/0-1 BFS depending on cost structure

3. MULTI-LAYER GRAPH:
   Multiple copies of graph with different edge rules
   Cross-layer edges have special costs

═══════════════════════════════════════════════════════════════════
EXAMPLE: Grid shortest path with at most K wall breaks
═══════════════════════════════════════════════════════════════════

Grid: '.' = free (cost 0), '#' = wall (cost 1 to break)
Find min walls broken to go from (0,0) to (R-1,C-1).

Use 0-1 BFS: free cell → push_front, wall → push_back.
If limited to K breaks: state = (r, c, breaks_used)

Time: O(R × C × K)    Space: O(R × C × K)
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

template<class T> using vec = vector<T>;
using pii = pair<int,int>;
constexpr int INF = 1e9;
#define nl '\n'

void solve() {
    int R, C, K;
    cin >> R >> C >> K;

    vec<string> grid(R);
    for (auto& s : grid) cin >> s;

    // dist[r][c][k] = min cost to reach (r,c) having broken k walls
    vec<vec<vec<int>>> dist(R, vec<vec<int>>(C, vec<int>(K+1, INF)));

    // 0-1 BFS with state (row, col, walls_broken)
    struct State { int r, c, k; };
    deque<State> dq;

    dist[0][0][0] = 0;
    dq.push_back({0, 0, 0});

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    while (!dq.empty()) {
        auto [r, c, k] = dq.front(); dq.pop_front();

        if (dist[r][c][k] < 0) continue; // sentinel for processed
        int curDist = dist[r][c][k];

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;

            if (grid[nr][nc] == '.') {
                // Free cell — weight 0
                if (curDist < dist[nr][nc][k]) {
                    dist[nr][nc][k] = curDist;
                    dq.push_front({nr, nc, k});
                }
            } else {
                // Wall — weight 1 (if we have remaining breaks)
                if (k < K && curDist + 1 < dist[nr][nc][k+1]) {
                    dist[nr][nc][k+1] = curDist + 1;
                    dq.push_back({nr, nc, k+1});
                }
            }
        }
    }

    int ans = INF;
    for (int k = 0; k <= K; k++) {
        ans = min(ans, dist[R-1][C-1][k]);
    }

    cout << (ans == INF ? -1 : ans) << nl;
}

/*
Input:
1
5 5 2
.....
.###.
.#...
.#.#.
...#.

Output: 1 (need to break 1 wall to find shortest path)
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

