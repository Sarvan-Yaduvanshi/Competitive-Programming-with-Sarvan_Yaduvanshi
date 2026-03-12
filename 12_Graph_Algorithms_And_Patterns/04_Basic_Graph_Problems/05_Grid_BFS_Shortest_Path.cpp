/*
╔══════════════════════════════════════════════════════════════════╗
║              05 — GRID BFS SHORTEST PATH                        ║
║              Classic BFS on 2D grid                             ║
╚══════════════════════════════════════════════════════════════════╝

Grid: '.' = passable, '#' = wall
Find shortest path from S to E.

DRY RUN:
  S . . #    dist:  0  1  2  #
  # # . #           #  #  3  #
  . . . .           6  5  4  5
  . # # E           7  #  #  6

Path: S→(0,1)→(0,2)→(1,2)→(2,2)→(2,1)→(2,0)→(3,0)→... →E
Shortest = 6

Time: O(R×C)    Space: O(R×C)
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int,int>;
#define nl '\n'

void solve() {
    int R, C;
    cin >> R >> C;
    vec<string> grid(R);
    for (auto &s : grid) cin >> s;

    int sr=-1,sc=-1,er=-1,ec=-1;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (grid[i][j]=='S') { sr=i; sc=j; }
            if (grid[i][j]=='E') { er=i; ec=j; }
        }

    vvec<int> dist(R, vec<int>(C, -1));
    vvec<pii> par(R, vec<pii>(C, {-1,-1}));
    queue<pii> q;
    dist[sr][sc] = 0;
    q.push({sr,sc});

    int dx[]={0,0,1,-1}, dy[]={1,-1,0,0};
    while (!q.empty()) {
        auto [x,y] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nx=x+dx[d], ny=y+dy[d];
            if (nx>=0&&nx<R&&ny>=0&&ny<C&&grid[nx][ny]!='#'&&dist[nx][ny]==-1) {
                dist[nx][ny]=dist[x][y]+1;
                par[nx][ny]={x,y};
                q.push({nx,ny});
            }
        }
    }

    if (dist[er][ec]==-1) { cout << -1 << nl; return; }

    cout << "Shortest distance: " << dist[er][ec] << nl;

    // Reconstruct path
    vec<pii> path;
    for (pii p={er,ec}; p!=pii{-1,-1}; p=par[p.first][p.second])
        path.push_back(p);
    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (int i = 0; i < (int)path.size(); i++) {
        if (i) cout << " → ";
        cout << "(" << path[i].first << "," << path[i].second << ")";
    }
    cout << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

