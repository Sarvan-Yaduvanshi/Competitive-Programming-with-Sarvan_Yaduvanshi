/*
 * ============================================================================
 *       FLOOD FILL / DFS / BFS ON GRID - ZERO TO GM MASTERY
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Topic   : Grid DFS, BFS, Flood Fill, Connected Components, Islands
 * Level   : 0 (Beginner) → 8 (GM)
 * ============================================================================
 *
 *  TABLE OF CONTENTS
 *  ─────────────────
 *  Level 0 : 4-Directional and 8-Directional Movement
 *  Level 1 : DFS on Grid (Recursive)
 *  Level 2 : BFS on Grid (Iterative with Queue)
 *  Level 3 : Flood Fill [LC #733]
 *  Level 4 : Number of Islands [LC #200]
 *  Level 5 : Max Area of Island [LC #695]
 *  Level 6 : Surrounded Regions [LC #130]
 *  Level 7 : Rotting Oranges (Multi-source BFS) [LC #994]
 *  Level 8 : Shortest Path in Binary Matrix [LC #1091]
 *
 * ============================================================================
 *  KEY PATTERNS:
 *  ┌────────────────────────────────────────────────────────────────┐
 *  │  DFS: Use recursion or stack. Good for exploring connected    │
 *  │       components, backtracking, counting areas.               │
 *  │                                                                │
 *  │  BFS: Use queue. Good for shortest paths in unweighted grids, │
 *  │       level-by-level expansion, multi-source problems.         │
 *  │                                                                │
 *  │  4-dir: dx={-1,1,0,0}, dy={0,0,-1,1}                        │
 *  │  8-dir: dx={-1,-1,-1,0,0,1,1,1}, dy={-1,0,1,-1,1,-1,0,1}   │
 *  │                                                                │
 *  │  Visited marking:                                              │
 *  │  - Separate visited array                                     │
 *  │  - Modify grid in-place (change value)                        │
 *  └────────────────────────────────────────────────────────────────┘
 *
 *  Related Problems:
 *  - LC #733:  Flood Fill
 *  - LC #200:  Number of Islands
 *  - LC #695:  Max Area of Island
 *  - LC #130:  Surrounded Regions
 *  - LC #994:  Rotting Oranges
 *  - LC #1091: Shortest Path in Binary Matrix
 *  - LC #542:  01 Matrix
 *  - LC #417:  Pacific Atlantic Water Flow
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

void printGrid(const vector<vector<int>>& grid, const string& title = "") {
    if (!title.empty()) cout << "--- " << title << " ---" << endl;
    for (const auto& row : grid) {
        for (int val : row) cout << setw(3) << val;
        cout << "\n";
    }
    cout << endl;
}

void printCharGrid(const vector<vector<char>>& grid, const string& title = "") {
    if (!title.empty()) cout << "--- " << title << " ---" << endl;
    for (const auto& row : grid) {
        for (char c : row) cout << " " << c;
        cout << "\n";
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 0: DIRECTION ARRAYS
// ─────────────────────────────────────────────────────────────────────────────
// 4-directional
const int dx4[] = {-1, 1, 0, 0};
const int dy4[] = {0, 0, -1, 1};

// 8-directional
const int dx8[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy8[] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool isValid(int r, int c, int n, int m) {
    return r >= 0 && r < n && c >= 0 && c < m;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 1: DFS ON GRID (RECURSIVE)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Explore all reachable cells from a starting point using DFS.
 *  Mark visited cells to avoid revisiting.
 *
 *  Time: O(N×M), Space: O(N×M) for recursion stack
 *
 *  ⚠ WARNING: For large grids (N×M > 10^6), recursive DFS may cause
 *  stack overflow. Use iterative DFS with explicit stack instead.
 */
void dfsRecursive(vector<vector<int>>& grid, int r, int c, int n, int m,
                  vector<vector<bool>>& visited) {
    if (!isValid(r, c, n, m) || visited[r][c] || grid[r][c] == 0)
        return;

    visited[r][c] = true;
    cout << "(" << r << "," << c << ") ";

    for (int d = 0; d < 4; d++) {
        dfsRecursive(grid, r + dx4[d], c + dy4[d], n, m, visited);
    }
}

// Iterative DFS using explicit stack (stack-safe for large grids)
void dfsIterative(vector<vector<int>>& grid, int startR, int startC,
                  int n, int m, vector<vector<bool>>& visited) {
    stack<pair<int,int>> stk;
    stk.push({startR, startC});
    visited[startR][startC] = true;

    while (!stk.empty()) {
        auto [r, c] = stk.top();
        stk.pop();
        cout << "(" << r << "," << c << ") ";

        for (int d = 0; d < 4; d++) {
            int nr = r + dx4[d], nc = c + dy4[d];
            if (isValid(nr, nc, n, m) && !visited[nr][nc] && grid[nr][nc] == 1) {
                visited[nr][nc] = true;
                stk.push({nr, nc});
            }
        }
    }
}

void dfsDemo() {
    cout << "=== DFS on Grid Demo ===" << endl;
    vector<vector<int>> grid = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 1, 1},
        {0, 0, 0, 1, 1},
        {0, 0, 1, 0, 0}
    };
    int n = grid.size(), m = grid[0].size();
    printGrid(grid, "Grid (1=land, 0=water)");

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    cout << "Recursive DFS from (0,0): ";
    dfsRecursive(grid, 0, 0, n, m, visited);
    cout << "\n";

    vector<vector<bool>> visited2(n, vector<bool>(m, false));
    cout << "Iterative DFS from (1,3): ";
    dfsIterative(grid, 1, 3, n, m, visited2);
    cout << "\n\n";
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 2: BFS ON GRID
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  BFS explores level by level (distance by distance).
 *  Use queue (FIFO) instead of stack/recursion.
 *
 *  Time: O(N×M), Space: O(N×M) for queue
 *
 *  BFS guarantees SHORTEST PATH in unweighted grids!
 */
void bfsOnGrid(vector<vector<int>>& grid, int startR, int startC) {
    cout << "=== BFS on Grid from (" << startR << "," << startC << ") ===" << endl;
    int n = grid.size(), m = grid[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    queue<pair<int,int>> q;

    q.push({startR, startC});
    visited[startR][startC] = true;
    int level = 0;

    while (!q.empty()) {
        int sz = q.size();
        cout << "Level " << level << ": ";
        for (int i = 0; i < sz; i++) {
            auto [r, c] = q.front();
            q.pop();
            cout << "(" << r << "," << c << ") ";

            for (int d = 0; d < 4; d++) {
                int nr = r + dx4[d], nc = c + dy4[d];
                if (isValid(nr, nc, n, m) && !visited[nr][nc] && grid[nr][nc] == 1) {
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
        cout << endl;
        level++;
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 3: FLOOD FILL — LC #733
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Given image (grid), starting pixel (sr, sc), and new color,
 *  fill all connected pixels of the same original color with new color.
 *
 *  Like the "paint bucket" tool in image editors.
 *
 *  Time: O(N×M), Space: O(N×M)
 */
void floodFillDFS(vector<vector<int>>& image, int r, int c,
                  int origColor, int newColor, int n, int m) {
    if (!isValid(r, c, n, m)) return;
    if (image[r][c] != origColor) return;

    image[r][c] = newColor;
    for (int d = 0; d < 4; d++)
        floodFillDFS(image, r + dx4[d], c + dy4[d], origColor, newColor, n, m);
}

vector<vector<int>> floodFill(vector<vector<int>> image, int sr, int sc, int color) {
    cout << "=== Flood Fill (LC #733) ===" << endl;
    int n = image.size(), m = image[0].size();
    int origColor = image[sr][sc];

    printGrid(image, "Before");

    if (origColor != color) // Avoid infinite loop if colors are same
        floodFillDFS(image, sr, sc, origColor, color, n, m);

    printGrid(image, "After flood fill at (" + to_string(sr) + "," + to_string(sc) + ") with color " + to_string(color));
    return image;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 4: NUMBER OF ISLANDS — LC #200
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Given grid of '1' (land) and '0' (water), count number of islands.
 *  An island is surrounded by water and formed by connecting adjacent '1's.
 *
 *  Approach: DFS/BFS from each unvisited '1', mark component as visited.
 *  Each new DFS/BFS = new island.
 *
 *  Time: O(N×M), Space: O(N×M)
 */
void markIslandDFS(vector<vector<char>>& grid, int r, int c, int n, int m) {
    if (!isValid(r, c, n, m) || grid[r][c] != '1') return;

    grid[r][c] = '0'; // Mark as visited by changing to water
    for (int d = 0; d < 4; d++)
        markIslandDFS(grid, r + dx4[d], c + dy4[d], n, m);
}

int numIslands(vector<vector<char>> grid) {
    cout << "=== Number of Islands (LC #200) ===" << endl;
    int n = grid.size(), m = grid[0].size();
    printCharGrid(grid, "Grid");

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '1') {
                count++;
                markIslandDFS(grid, i, j, n, m);
            }
        }
    }

    cout << "Number of Islands = " << count << "\n\n";
    return count;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 5: MAX AREA OF ISLAND — LC #695
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Find the maximum area of an island in the grid.
 *  Area = number of '1' cells in a connected component.
 *
 *  Time: O(N×M), Space: O(N×M)
 */
int islandAreaDFS(vector<vector<int>>& grid, int r, int c, int n, int m) {
    if (!isValid(r, c, n, m) || grid[r][c] != 1) return 0;

    grid[r][c] = 0; // Mark visited
    int area = 1;
    for (int d = 0; d < 4; d++)
        area += islandAreaDFS(grid, r + dx4[d], c + dy4[d], n, m);
    return area;
}

int maxAreaOfIsland(vector<vector<int>> grid) {
    cout << "=== Max Area of Island (LC #695) ===" << endl;
    int n = grid.size(), m = grid[0].size();
    printGrid(grid, "Grid");

    int maxArea = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) {
                int area = islandAreaDFS(grid, i, j, n, m);
                maxArea = max(maxArea, area);
            }
        }
    }

    cout << "Max Island Area = " << maxArea << "\n\n";
    return maxArea;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 6: SURROUNDED REGIONS — LC #130
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Given grid with 'O' and 'X', capture all 'O' regions that are
 *  completely surrounded by 'X' (flip them to 'X').
 *  'O' connected to border cannot be captured.
 *
 *  Approach:
 *  1. DFS/BFS from all border 'O's, mark them as safe (e.g., 'S')
 *  2. Flip remaining 'O' → 'X' (these are surrounded)
 *  3. Flip 'S' back to 'O'
 *
 *  Time: O(N×M), Space: O(N×M)
 */
void markSafeDFS(vector<vector<char>>& board, int r, int c, int n, int m) {
    if (!isValid(r, c, n, m) || board[r][c] != 'O') return;
    board[r][c] = 'S'; // Safe
    for (int d = 0; d < 4; d++)
        markSafeDFS(board, r + dx4[d], c + dy4[d], n, m);
}

void surroundedRegions(vector<vector<char>> board) {
    cout << "=== Surrounded Regions (LC #130) ===" << endl;
    int n = board.size(), m = board[0].size();
    printCharGrid(board, "Before");

    // Step 1: Mark border-connected 'O' as safe
    for (int i = 0; i < n; i++) {
        markSafeDFS(board, i, 0, n, m);
        markSafeDFS(board, i, m - 1, n, m);
    }
    for (int j = 0; j < m; j++) {
        markSafeDFS(board, 0, j, n, m);
        markSafeDFS(board, n - 1, j, n, m);
    }

    // Step 2 & 3: Flip remaining O → X, S → O
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 'O') board[i][j] = 'X';
            else if (board[i][j] == 'S') board[i][j] = 'O';
        }
    }

    printCharGrid(board, "After");
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 7: ROTTING ORANGES (MULTI-SOURCE BFS) — LC #994
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Grid: 0=empty, 1=fresh, 2=rotten
 *  Each minute, rotten oranges rot adjacent fresh oranges.
 *  Return minimum minutes until no fresh orange remains, or -1.
 *
 *  Approach: Multi-source BFS starting from ALL rotten oranges simultaneously.
 *
 *  Time: O(N×M), Space: O(N×M)
 */
int orangesRotting(vector<vector<int>> grid) {
    cout << "=== Rotting Oranges (LC #994) ===" << endl;
    int n = grid.size(), m = grid[0].size();
    printGrid(grid, "Initial (0=empty, 1=fresh, 2=rotten)");

    queue<pair<int,int>> q;
    int fresh = 0;

    // Step 1: Add all rotten oranges to queue, count fresh
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 2) q.push({i, j});
            else if (grid[i][j] == 1) fresh++;
        }
    }

    if (fresh == 0) {
        cout << "Minutes = 0 (no fresh oranges)" << endl << endl;
        return 0;
    }

    int minutes = 0;

    // Step 2: BFS level by level
    while (!q.empty() && fresh > 0) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            auto [r, c] = q.front();
            q.pop();

            for (int d = 0; d < 4; d++) {
                int nr = r + dx4[d], nc = c + dy4[d];
                if (isValid(nr, nc, n, m) && grid[nr][nc] == 1) {
                    grid[nr][nc] = 2;
                    fresh--;
                    q.push({nr, nc});
                }
            }
        }
        minutes++;
    }

    int result = (fresh == 0) ? minutes : -1;
    cout << "Minutes = " << result << "\n\n";
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 8: SHORTEST PATH IN BINARY MATRIX — LC #1091
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Find shortest path from (0,0) to (N-1,N-1) in binary grid.
 *  0 = passable, 1 = blocked. Can move in 8 directions.
 *  Return path length (number of cells), or -1 if impossible.
 *
 *  BFS guarantees shortest path in unweighted grid!
 *
 *  Time: O(N²), Space: O(N²)
 */
int shortestPathBinaryMatrix(vector<vector<int>> grid) {
    cout << "=== Shortest Path in Binary Matrix (LC #1091) ===" << endl;
    int n = grid.size();
    printGrid(grid, "Grid (0=free, 1=blocked)");

    if (grid[0][0] == 1 || grid[n-1][n-1] == 1) {
        cout << "Path length = -1 (start or end blocked)\n\n";
        return -1;
    }

    queue<tuple<int,int,int>> q; // (row, col, distance)
    q.push({0, 0, 1});
    grid[0][0] = 1; // Mark visited

    while (!q.empty()) {
        auto [r, c, dist] = q.front();
        q.pop();

        if (r == n - 1 && c == n - 1) {
            cout << "Shortest path length = " << dist << "\n\n";
            return dist;
        }

        for (int d = 0; d < 8; d++) { // 8-directional!
            int nr = r + dx8[d], nc = c + dy8[d];
            if (isValid(nr, nc, n, n) && grid[nr][nc] == 0) {
                grid[nr][nc] = 1; // Mark visited
                q.push({nr, nc, dist + 1});
            }
        }
    }

    cout << "Path length = -1 (no path exists)\n\n";
    return -1;
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   FLOOD FILL / DFS / BFS - ZERO TO GM MASTERY   ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << endl;

    // Level 1: DFS Demo
    dfsDemo();

    // Level 2: BFS Demo
    vector<vector<int>> bfsGrid = {
        {1, 1, 0, 0},
        {1, 1, 0, 1},
        {0, 0, 0, 1},
        {0, 0, 1, 1}
    };
    bfsOnGrid(bfsGrid, 0, 0);

    // Level 3: Flood Fill (LC #733)
    vector<vector<int>> image = {
        {1, 1, 1},
        {1, 1, 0},
        {1, 0, 1}
    };
    floodFill(image, 1, 1, 2);

    // Level 4: Number of Islands (LC #200)
    vector<vector<char>> islandGrid = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    numIslands(islandGrid);

    // Level 5: Max Area of Island (LC #695)
    vector<vector<int>> areaGrid = {
        {0,0,1,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,1,1,0,1,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,1,0,0,1,0,1,0,0},
        {0,1,0,0,1,1,0,0,1,1,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,0,0,0,0,0,0,1,1,0,0,0,0}
    };
    maxAreaOfIsland(areaGrid);

    // Level 6: Surrounded Regions (LC #130)
    vector<vector<char>> board = {
        {'X','X','X','X'},
        {'X','O','O','X'},
        {'X','X','O','X'},
        {'X','O','X','X'}
    };
    surroundedRegions(board);

    // Level 7: Rotting Oranges (LC #994)
    vector<vector<int>> oranges = {
        {2,1,1},
        {1,1,0},
        {0,1,1}
    };
    orangesRotting(oranges);

    // Level 8: Shortest Path (LC #1091)
    vector<vector<int>> pathGrid = {
        {0,0,0},
        {1,1,0},
        {1,1,0}
    };
    shortestPathBinaryMatrix(pathGrid);

    vector<vector<int>> pathGrid2 = {
        {0,1},
        {1,0}
    };
    shortestPathBinaryMatrix(pathGrid2);

    return 0;
}

