/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Tree Greedy Techniques — Leaf-to-Root & Root-to-Leaf
 *  Level   : Expert
 * ============================================================================
 *
 *  ▶ LEAF-TO-ROOT GREEDY (Bottom-Up):
 *  ──────────────────────────────────
 *  Process nodes from leaves upward. Make greedy decisions at each level.
 *  Classic: Binary Tree Cameras (LC 968)
 *
 *  ▶ ROOT-TO-LEAF GREEDY (Top-Down):
 *  ─────────────────────────────────
 *  Process root first, propagate information downward.
 *  Classic: Sum of Distances in Tree (LC 834 — re-rooting technique)
 *
 *  ▶ LEAF PRUNING:
 *  ───────────────
 *  Repeatedly remove leaves. The last 1-2 remaining nodes are the answer.
 *  Classic: Minimum Height Trees (LC 310)
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ============================================================================
// LC 968: Binary Tree Cameras — Leaf-to-Root Greedy
// ============================================================================
/*
 * States for each node:
 * 0 = NOT covered (needs camera from parent)
 * 1 = HAS camera
 * 2 = COVERED (by child's camera)
 *
 * Greedy: Don't place cameras at leaves — place at their parents.
 * Process bottom-up (post-order).
 */
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

int cameras;
int dfs_camera(TreeNode* node) {
    if (!node) return 2; // null is considered covered

    int left = dfs_camera(node->left);
    int right = dfs_camera(node->right);

    if (left == 0 || right == 0) {
        // A child is NOT covered → MUST place camera here
        cameras++;
        return 1;
    }
    if (left == 1 || right == 1) {
        // A child HAS a camera → this node is covered
        return 2;
    }
    // Both children are covered but no camera nearby → NOT covered
    return 0;
}

int minCameraCover(TreeNode* root) {
    cameras = 0;
    if (dfs_camera(root) == 0) cameras++; // Root not covered
    return cameras;
}

// ============================================================================
// LC 310: Minimum Height Trees — Leaf Pruning
// ============================================================================
vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    if (n == 1) return {0};

    vector<vector<int>> adj(n);
    vector<int> degree(n, 0);

    for (auto& e : edges) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
        degree[e[0]]++;
        degree[e[1]]++;
    }

    // Start with all leaves
    queue<int> q;
    for (int i = 0; i < n; i++)
        if (degree[i] == 1) q.push(i);

    int remaining = n;
    while (remaining > 2) {
        int sz = q.size();
        remaining -= sz;
        while (sz--) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (--degree[v] == 1) q.push(v);
            }
        }
    }

    vector<int> result;
    while (!q.empty()) { result.push_back(q.front()); q.pop(); }
    return result;
}

// ============================================================================
// LC 834: Sum of Distances in Tree — Re-rooting Technique
// ============================================================================
/*
 * Two DFS passes:
 * DFS 1 (bottom-up): Compute subtree sizes and sum of distances from root 0
 * DFS 2 (top-down): Shift answer from parent to child:
 *   ans[child] = ans[parent] - subtreeSize[child] + (n - subtreeSize[child])
 *   (Moving root to child: subtreeSize[child] nodes get 1 closer,
 *    n-subtreeSize[child] nodes get 1 farther)
 */
vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
    vector<vector<int>> adj(n);
    for (auto& e : edges) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }

    vector<int> subtreeSize(n, 1), ans(n, 0);

    // DFS 1: Compute subtree sizes and ans[0]
    function<void(int, int)> dfs1 = [&](int u, int parent) {
        for (int v : adj[u]) {
            if (v == parent) continue;
            dfs1(v, u);
            subtreeSize[u] += subtreeSize[v];
            ans[0] += subtreeSize[v]; // Each node in subtree contributes +1 to distance from root
        }
    };
    dfs1(0, -1);

    // DFS 2: Re-root from parent to child
    function<void(int, int)> dfs2 = [&](int u, int parent) {
        for (int v : adj[u]) {
            if (v == parent) continue;
            ans[v] = ans[u] - subtreeSize[v] + (n - subtreeSize[v]);
            dfs2(v, u);
        }
    };
    dfs2(0, -1);

    return ans;
}

int main() {
    // Minimum Height Trees
    int n = 6;
    vector<vector<int>> edges = {{3,0},{3,1},{3,2},{3,4},{5,4}};
    auto mht = findMinHeightTrees(n, edges);
    cout << "MHT roots: ";
    for (int r : mht) cout << r << " ";
    cout << endl; // 3 4

    // Sum of Distances
    vector<vector<int>> edges2 = {{0,1},{0,2},{2,3},{2,4},{2,5}};
    auto sod = sumOfDistancesInTree(6, edges2);
    cout << "Sum of distances: ";
    for (int d : sod) cout << d << " ";
    cout << endl; // 8 12 6 10 10 10

    return 0;
}

