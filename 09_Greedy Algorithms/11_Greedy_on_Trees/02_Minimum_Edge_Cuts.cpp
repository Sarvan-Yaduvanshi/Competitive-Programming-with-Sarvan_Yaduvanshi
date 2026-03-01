/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Minimum Edge Cuts in Trees — Greedy Edge Removal
 *  Level   : Expert
 * ============================================================================
 *
 *  PROBLEMS:
 *  1. Split tree into components with even number of nodes
 *  2. CSES Tree Matching — maximum matching in a tree
 *  3. Remove edges to disconnect tree into k components
 *
 *  KEY IDEA: In a tree with N nodes and N-1 edges, removing k edges creates k+1 components.
 *  Greedy: Process edges/nodes in a specific order (usually leaf-to-root).
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <functional>
using namespace std;

// ============================================================================
// CSES 1130: Tree Matching — Maximum matching in a tree
// Greedy: Process leaves first. If a leaf edge is unmatched, match it.
// ============================================================================
int treeMatching(int n, vector<vector<int>>& adj) {
    vector<bool> matched(n, false);
    int matching = 0;

    // Post-order DFS: try to match each node with its parent
    function<void(int, int)> dfs = [&](int u, int parent) {
        for (int v : adj[u]) {
            if (v == parent) continue;
            dfs(v, u);

            // If both u and v are unmatched, match this edge
            if (!matched[u] && !matched[v]) {
                matched[u] = matched[v] = true;
                matching++;
            }
        }
    };

    dfs(0, -1);
    return matching;
}

// ============================================================================
// Split tree into max components with even size
// Remove edges where both resulting subtrees have even size
// ============================================================================
int maxEvenComponents(int n, vector<vector<int>>& adj) {
    if (n % 2 != 0) return 0; // Can't split odd total into even parts

    vector<int> subtreeSize(n, 1);
    int cuts = 0;

    function<void(int, int)> dfs = [&](int u, int parent) {
        for (int v : adj[u]) {
            if (v == parent) continue;
            dfs(v, u);
            subtreeSize[u] += subtreeSize[v];

            // If subtree has even size, we can cut this edge
            if (subtreeSize[v] % 2 == 0) {
                cuts++;
                // Reset subtree size as if cut
            }
        }
    };

    dfs(0, -1);
    return cuts; // Number of components = cuts + 1
}

int main() {
    // Tree Matching
    int n = 5;
    vector<vector<int>> adj(n);
    auto addEdge = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };
    addEdge(0, 1); addEdge(1, 2); addEdge(2, 3); addEdge(3, 4);
    cout << "Tree matching: " << treeMatching(n, adj) << endl; // 2

    return 0;
}

