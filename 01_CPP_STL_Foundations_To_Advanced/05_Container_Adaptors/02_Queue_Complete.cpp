/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — QUEUE COMPLETE GUIDE                                        ║
║           From Zero to Grandmaster — FIFO Power                            ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

  Queue = FIFO (First In, First Out)
  push(x) → O(1), pop() → O(1), front() → O(1), back() → O(1)

  PRIMARY USE IN CP: BFS (Breadth-First Search)
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BASIC OPERATIONS
// ═══════════════════════════════════════════════════════════════

void demonstrateBasics() {
    cout << "═══ QUEUE BASICS ═══\n\n";

    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);

    cout << "Front: " << q.front() << "\n";
    cout << "Back:  " << q.back() << "\n";
    cout << "Size:  " << q.size() << "\n";

    cout << "Dequeue order (FIFO): ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: BFS PATTERN (THE #1 QUEUE USE IN CP)
// ═══════════════════════════════════════════════════════════════
/*
 BFS explores all nodes at distance d before distance d+1.
 Uses queue to process level by level.

 DRY RUN: Graph with 6 nodes, start from 0
   0 → [1, 2]
   1 → [3]
   2 → [3, 4]
   3 → [5]
   4 → [5]

   Queue: [0]         Level 0: {0}
   Queue: [1, 2]      Level 1: {1, 2}
   Queue: [3, 4]      Level 2: {3, 4}
   Queue: [5]         Level 3: {5}
*/

void bfsPattern() {
    cout << "═══ BFS PATTERN ═══\n\n";

    int n = 6;
    vector<vector<int>> adj(n);
    adj[0] = {1, 2};
    adj[1] = {3};
    adj[2] = {3, 4};
    adj[3] = {5};
    adj[4] = {5};

    vector<int> dist(n, -1);
    queue<int> q;
    q.push(0);
    dist[0] = 0;

    cout << "BFS from node 0:\n";
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << "  Visit node " << u << " (distance " << dist[u] << ")\n";

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    cout << "\nDistances: ";
    for (int i = 0; i < n; i++) cout << i << ":" << dist[i] << " ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: LEVEL-ORDER BFS (PROCESS BY LEVEL)
// ═══════════════════════════════════════════════════════════════
/*
 Sometimes you need to process nodes LEVEL BY LEVEL.
 Trick: use q.size() to process one level at a time.
*/

void levelOrderBFS() {
    cout << "═══ LEVEL-ORDER BFS ═══\n\n";

    int n = 7;
    vector<vector<int>> adj(n);
    adj[0] = {1, 2};
    adj[1] = {3, 4};
    adj[2] = {5, 6};

    queue<int> q;
    vector<bool> visited(n, false);
    q.push(0);
    visited[0] = true;

    int level = 0;
    while (!q.empty()) {
        int sz = q.size();  // Number of nodes at this level
        cout << "Level " << level << ": ";
        for (int i = 0; i < sz; i++) {
            int u = q.front();
            q.pop();
            cout << u << " ";
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << "\n";
        level++;
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: GRID BFS (SHORTEST PATH IN MAZE)
// ═══════════════════════════════════════════════════════════════

void gridBFS() {
    cout << "═══ GRID BFS (MAZE) ═══\n\n";

    vector<string> grid = {
        ".....",
        ".###.",
        "...#.",
        ".#...",
        "....."
    };
    int rows = grid.size(), cols = grid[0].size();

    cout << "Grid:\n";
    for (auto& row : grid) cout << "  " << row << "\n";

    // BFS from (0,0) to (rows-1, cols-1)
    vector<vector<int>> dist(rows, vector<int>(cols, -1));
    queue<pair<int, int>> q;
    q.push({0, 0});
    dist[0][0] = 0;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
                grid[nx][ny] == '.' && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    cout << "\nShortest path (0,0) → (" << rows - 1 << "," << cols - 1 << "): "
         << dist[rows - 1][cols - 1] << "\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateBasics();
    bfsPattern();
    levelOrderBFS();
    gridBFS();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. Queue = FIFO, O(1) all operations\n";
    cout << "2. BFS = queue + visited → shortest path in unweighted graph\n";
    cout << "3. Level-order: use q.size() to process one level at a time\n";
    cout << "4. Grid BFS: 4-directional with bounds checking\n";
    cout << "5. BFS finds shortest path in unweighted graphs\n";

    return 0;
}

/*
 PRACTICE:
 1. [CSES Labyrinth]      https://cses.fi/problemset/task/1193
 2. [LC Number of Islands] https://leetcode.com/problems/number-of-islands/
 3. [CF Maze BFS problems] Grid BFS
*/

