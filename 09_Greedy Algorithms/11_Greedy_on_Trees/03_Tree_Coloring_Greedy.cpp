/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Tree Coloring Greedy / Bipartite Greedy
 *  Level   : Expert
 * ============================================================================
 *
 *  KEY FACTS:
 *  1. Every tree is bipartite (2-colorable)
 *  2. Chromatic number of a tree = 2 (if edges exist)
 *  3. Trees have unique paths between any two nodes
 *
 *  GREEDY COLORING on trees:
 *  - BFS/DFS from root, alternate colors
 *  - For general graphs: order vertices, assign smallest color not used by neighbors
 *
 *  APPLICATIONS:
 *  - LC 2246: Longest Path with Different Adjacent Characters
 *  - Binary Tree Maximum Path Sum (LC 124)
 *  - Tree DP problems with greedy flavor
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// ============================================================================
// LC 2246: Longest Path with Different Adjacent Characters
// Greedy: For each node, take the two longest paths from children with different chars
// ============================================================================
int longestPathDiffChars(int n, vector<int>& parent, string& s) {
    vector<vector<int>> children(n);
    for (int i = 1; i < n; i++)
        children[parent[i]].push_back(i);

    int ans = 1;

    function<int(int)> dfs = [&](int u) -> int {
        int longest1 = 0, longest2 = 0; // Two longest paths from children

        for (int v : children[u]) {
            int childLen = dfs(v);
            if (s[v] == s[u]) continue; // Same char → can't extend

            if (childLen >= longest1) {
                longest2 = longest1;
                longest1 = childLen;
            } else if (childLen > longest2) {
                longest2 = childLen;
            }
        }

        ans = max(ans, longest1 + longest2 + 1);
        return longest1 + 1;
    };

    dfs(0);
    return ans;
}

// ============================================================================
// Binary Tree Maximum Path Sum (LC 124)
// Greedy: At each node, decide whether to include left/right paths
// ============================================================================
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

int maxPathSumHelper(TreeNode* node, int& globalMax) {
    if (!node) return 0;

    int left = max(0, maxPathSumHelper(node->left, globalMax));
    int right = max(0, maxPathSumHelper(node->right, globalMax));

    // Through this node: left + node + right
    globalMax = max(globalMax, left + right + node->val);

    // Return max path going UP through this node
    return max(left, right) + node->val;
}

int maxPathSum(TreeNode* root) {
    int globalMax = INT_MIN;
    maxPathSumHelper(root, globalMax);
    return globalMax;
}

// ============================================================================
// Greedy 2-Coloring of a Tree (BFS)
// ============================================================================
vector<int> twoColorTree(int n, vector<vector<int>>& adj) {
    vector<int> color(n, -1);
    vector<int> q = {0};
    color[0] = 0;

    for (int i = 0; i < (int)q.size(); i++) {
        int u = q[i];
        for (int v : adj[u]) {
            if (color[v] == -1) {
                color[v] = 1 - color[u];
                q.push_back(v);
            }
        }
    }
    return color;
}

int main() {
    // Longest Path with Different Chars
    int n = 7;
    vector<int> parent = {-1, 0, 0, 1, 1, 2, 2};
    string s = "abacaba";
    // Note: parent[0] = -1 means 0 is root
    // Build for LC format
    cout << "Longest path diff chars: " << longestPathDiffChars(n, parent, s) << endl;

    // 2-Coloring
    vector<vector<int>> adj(5);
    adj[0].push_back(1); adj[1].push_back(0);
    adj[0].push_back(2); adj[2].push_back(0);
    adj[1].push_back(3); adj[3].push_back(1);
    adj[1].push_back(4); adj[4].push_back(1);
    auto colors = twoColorTree(5, adj);
    cout << "Colors: ";
    for (int c : colors) cout << c << " ";
    cout << endl;

    return 0;
}

