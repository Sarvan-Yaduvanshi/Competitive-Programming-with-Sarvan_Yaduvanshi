/*
╔══════════════════════════════════════════════════════════════════════════════╗
║       04 — BFS LEVEL ORDER TRAVERSAL + BFS SHORTEST PATH                     ║
║           From Zero to Grandmaster — Queue & Deque Patterns                 ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. BFS Level Order Traversal (LC 102)
 2. BFS Shortest Path in Unweighted Graph
 3. BFS on Grid (LC 1091)
 4. Zigzag Level Order (LC 103)

LEVEL ORDER TRAVERSAL:
─────────────────────
  BFS uses a QUEUE to process nodes level by level.

  Tree:
          3
         / \
        9   20
           / \
          15   7

  Queue state by level:
    Init: [3]
    Level 0: pop 3, push 9,20     → queue=[9,20]  result=[[3]]
    Level 1: pop 9, push nothing   → queue=[20]
             pop 20, push 15,7    → queue=[15,7]  result=[[3],[9,20]]
    Level 2: pop 15, pop 7        → queue=[]      result=[[3],[9,20],[15,7]]

  Key Pattern: Process all nodes at current size of queue (one level at a time).

  for (int sz = q.size(); sz > 0; sz--) {
      auto node = q.front(); q.pop();
      // process node
      // push children
  }

BFS SHORTEST PATH:
─────────────────
  In an unweighted graph, BFS finds the shortest path.
  Each "level" of BFS corresponds to distance+1 from source.

  ┌─────────────────────────────────────────────┐
  │  Why BFS gives shortest path in unweighted:  │
  │  BFS explores ALL nodes at distance d         │
  │  before ANY node at distance d+1.             │
  │  First time we reach a node = shortest path!  │
  └─────────────────────────────────────────────┘

  DRY RUN: Graph with 6 nodes, source=0
  Edges: 0-1, 0-2, 1-3, 2-3, 3-4, 4-5

  Level 0: [0]          dist[0]=0
  Level 1: [1,2]        dist[1]=1, dist[2]=1
  Level 2: [3]          dist[3]=2
  Level 3: [4]          dist[4]=3
  Level 4: [5]          dist[5]=4

TIME: O(V + E)  SPACE: O(V)
*/

#include <iostream>
#include <queue>
#include <vector>
#include <deque>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// TREE NODE DEFINITION
// ═══════════════════════════════════════════════════════════════

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// ═══════════════════════════════════════════════════════════════
// 1. LEVEL ORDER TRAVERSAL (LC 102)
// ═══════════════════════════════════════════════════════════════

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int sz = q.size();
        vector<int> level;
        for (int i = 0; i < sz; i++) {
            TreeNode* node = q.front(); q.pop();
            level.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(level);
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// 2. ZIGZAG LEVEL ORDER (LC 103)
// ═══════════════════════════════════════════════════════════════
/*
  Same as level order but alternate direction each level.
  Level 0: left→right, Level 1: right→left, Level 2: left→right...

  Just reverse alternate levels in result!
*/

vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;

    while (!q.empty()) {
        int sz = q.size();
        deque<int> level;
        for (int i = 0; i < sz; i++) {
            TreeNode* node = q.front(); q.pop();
            if (leftToRight)
                level.push_back(node->val);
            else
                level.push_front(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(vector<int>(level.begin(), level.end()));
        leftToRight = !leftToRight;
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// 3. BFS SHORTEST PATH — UNWEIGHTED GRAPH
// ═══════════════════════════════════════════════════════════════

vector<int> bfsShortestPath(int n, vector<vector<int>>& adj, int src) {
    vector<int> dist(n, -1);
    queue<int> q;

    dist[src] = 0;
    q.push(src);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {  // Not visited
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

// ═══════════════════════════════════════════════════════════════
// 4. SHORTEST PATH IN BINARY MATRIX (LC 1091)
// ═══════════════════════════════════════════════════════════════
/*
  8-directional BFS in an n×n grid.
  Find shortest path from (0,0) to (n-1,n-1).
  0 = passable, 1 = blocked.

  DRY RUN: [[0,0,0],
             [1,1,0],
             [1,1,0]]

  BFS from (0,0):
  Level 1: (0,0) → neighbors (0,1),(1,0),(1,1)
    (0,1) ok, (1,0)=1 blocked, (1,1)=1 blocked
  Level 2: (0,1) → (0,2),(1,2)
    (0,2) ok, (1,2) ok
  Level 3: (0,2) → (1,2) already visited
           (1,2) → (2,2) ok!
  Level 4: reached (2,2)! distance = 4 ✅
*/

int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int n = grid.size();
    if (grid[0][0] == 1 || grid[n-1][n-1] == 1) return -1;

    // 8 directions
    int dx[] = {-1,-1,-1,0,0,1,1,1};
    int dy[] = {-1,0,1,-1,1,-1,0,1};

    queue<pair<int,int>> q;
    q.push({0, 0});
    grid[0][0] = 1;  // Mark visited
    int dist = 1;

    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            auto [x, y] = q.front(); q.pop();
            if (x == n-1 && y == n-1) return dist;

            for (int d = 0; d < 8; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 0) {
                    grid[nx][ny] = 1;  // Mark visited WHEN PUSHING!
                    q.push({nx, ny});
                }
            }
        }
        dist++;
    }
    return -1;
}

// ═══════════════════════════════════════════════════════════════

void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  BFS LEVEL ORDER + SHORTEST PATH                         ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Build tree:      3
    //                 / \
    //                9   20
    //                   / \
    //                  15   7
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    // Level Order
    cout << "═══ LEVEL ORDER TRAVERSAL (LC 102) ═══\n";
    auto levels = levelOrder(root);
    cout << "  Tree: [3,9,20,null,null,15,7]\n  Levels: [";
    for (int i = 0; i < (int)levels.size(); i++) {
        cout << "[";
        for (int j = 0; j < (int)levels[i].size(); j++) {
            cout << levels[i][j];
            if (j+1<(int)levels[i].size()) cout << ",";
        }
        cout << "]";
        if (i+1<(int)levels.size()) cout << ",";
    }
    cout << "]\n\n";

    // Zigzag
    cout << "═══ ZIGZAG LEVEL ORDER (LC 103) ═══\n";
    auto zig = zigzagLevelOrder(root);
    cout << "  Zigzag: [";
    for (int i = 0; i < (int)zig.size(); i++) {
        cout << "[";
        for (int j = 0; j < (int)zig[i].size(); j++) {
            cout << zig[i][j];
            if (j+1<(int)zig[i].size()) cout << ",";
        }
        cout << "]";
        if (i+1<(int)zig.size()) cout << ",";
    }
    cout << "]\n\n";

    freeTree(root);

    // BFS Shortest Path
    cout << "═══ BFS SHORTEST PATH (UNWEIGHTED GRAPH) ═══\n";
    int n = 6;
    vector<vector<int>> adj(n);
    adj[0] = {1, 2}; adj[1] = {0, 3}; adj[2] = {0, 3};
    adj[3] = {1, 2, 4}; adj[4] = {3, 5}; adj[5] = {4};
    auto dist = bfsShortestPath(n, adj, 0);
    cout << "  Graph: 0-1, 0-2, 1-3, 2-3, 3-4, 4-5\n";
    cout << "  Distances from 0: ";
    for (int i = 0; i < n; i++) cout << "d[" << i << "]=" << dist[i] << " ";
    cout << "\n\n";

    // Shortest Path Binary Matrix
    cout << "═══ SHORTEST PATH BINARY MATRIX (LC 1091) ═══\n";
    vector<vector<int>> grid = {{0,0,0},{1,1,0},{1,1,0}};
    cout << "  Grid: [[0,0,0],[1,1,0],[1,1,0]]\n";
    cout << "  Shortest path: " << shortestPathBinaryMatrix(grid) << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE:\n";
    cout << "  LC 102  — Binary Tree Level Order Traversal\n";
    cout << "  LC 103  — Zigzag Level Order Traversal\n";
    cout << "  LC 1091 — Shortest Path in Binary Matrix\n";
    cout << "  LC 200  — Number of Islands\n";
    cout << "  LC 733  — Flood Fill\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

