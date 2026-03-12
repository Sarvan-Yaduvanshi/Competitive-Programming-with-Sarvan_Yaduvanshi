/*
 * ============================================================================
 *                        TREE DP — FOUNDATIONS
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Tree DP — Subtree DP, Diameter, Independent Set, Rerooting
 * Level   : ⭐⭐⭐ Advanced
 * ============================================================================
 *
 * TREE DP PATTERN:
 *   Process tree via DFS. Compute dp values bottom-up (leaves → root).
 *   dp[node] depends on dp[children].
 *
 * COMMON PROBLEMS:
 * 1. Tree Diameter — longest path in tree
 * 2. House Robber III — max sum non-adjacent nodes
 * 3. Max Independent Set — max weight set with no adjacent nodes
 * 4. Vertex Cover — min nodes covering all edges
 * 5. Rerooting DP — answer for every node as root
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int val[MAXN];

/*
 * 1. TREE DIAMETER (longest path)
 *    For each node: maintain two longest paths through children
 *    Diameter = max(top1 + top2) over all nodes
 */
int diameter;
int treeDiameter(int u, int parent) {
    int top1 = 0, top2 = 0;  // Two longest paths

    for (int v : adj[u]) {
        if (v == parent) continue;
        int d = treeDiameter(v, u) + 1;
        if (d > top1) { top2 = top1; top1 = d; }
        else if (d > top2) { top2 = d; }
    }

    diameter = max(diameter, top1 + top2);
    return top1;
}

/*
 * 2. HOUSE ROBBER III / MAX INDEPENDENT SET
 *    dp[u][0] = max sum if we DON'T take node u
 *    dp[u][1] = max sum if we DO take node u
 *
 *    dp[u][0] = Σ max(dp[v][0], dp[v][1])  — children can be taken or not
 *    dp[u][1] = val[u] + Σ dp[v][0]         — children must NOT be taken
 */
long long dp_take[MAXN], dp_skip[MAXN];

void maxIndependentSet(int u, int parent) {
    dp_take[u] = val[u];
    dp_skip[u] = 0;

    for (int v : adj[u]) {
        if (v == parent) continue;
        maxIndependentSet(v, u);
        dp_take[u] += dp_skip[v];
        dp_skip[u] += max(dp_take[v], dp_skip[v]);
    }
}

/*
 * 3. VERTEX COVER (min nodes to cover all edges)
 *    dp[u][0] = min vertex cover if u NOT in cover
 *    dp[u][1] = min vertex cover if u IS in cover
 *
 *    dp[u][0] = Σ dp[v][1]                  — all children MUST be in cover
 *    dp[u][1] = 1 + Σ min(dp[v][0], dp[v][1])
 */
int vc_take[MAXN], vc_skip[MAXN];

void vertexCover(int u, int parent) {
    vc_take[u] = 1;
    vc_skip[u] = 0;

    for (int v : adj[u]) {
        if (v == parent) continue;
        vertexCover(v, u);
        vc_take[u] += min(vc_take[v], vc_skip[v]);
        vc_skip[u] += vc_take[v];  // Child must be in cover
    }
}

/*
 * 4. TREE COLORING — Min cost to color tree with 2 colors
 *    No two adjacent nodes same color
 *    cost[u][c] = cost of coloring u with color c
 */
int color_cost[MAXN][2];
int color_dp[MAXN][2];

void treeColoring(int u, int parent) {
    color_dp[u][0] = color_cost[u][0];
    color_dp[u][1] = color_cost[u][1];

    for (int v : adj[u]) {
        if (v == parent) continue;
        treeColoring(v, u);
        color_dp[u][0] += color_dp[v][1];  // u=0 → child must be 1
        color_dp[u][1] += color_dp[v][0];  // u=1 → child must be 0
    }
}

/*
 * 5. REROOTING DP — Answer for every node as root
 *    Two passes:
 *    Pass 1 (DFS down): compute dp[u] with u's subtree
 *    Pass 2 (DFS up): "re-root" — compute answer if parent's part is included
 *
 *    Example: Sum of distances from every node (LeetCode 834)
 */
long long dist_sum[MAXN];  // sum of distances from node u
int subtree_size[MAXN];
int n_nodes;

void dfs_down(int u, int parent) {
    subtree_size[u] = 1;
    dist_sum[u] = 0;

    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs_down(v, u);
        subtree_size[u] += subtree_size[v];
        dist_sum[u] += dist_sum[v] + subtree_size[v];
    }
}

void dfs_reroot(int u, int parent) {
    for (int v : adj[u]) {
        if (v == parent) continue;
        // When we move root from u to v:
        // subtree_size[v] nodes get 1 closer, (n - subtree_size[v]) get 1 farther
        dist_sum[v] = dist_sum[u] - subtree_size[v] + (n_nodes - subtree_size[v]);
        dfs_reroot(v, u);
    }
}

/*
 * 6. MAX MATCHING IN TREE
 *    dp[u][0] = max matching in subtree of u, u not matched
 *    dp[u][1] = max matching in subtree of u, u matched with one child
 */
int match_dp[MAXN][2];

void maxMatching(int u, int parent) {
    match_dp[u][0] = 0;
    match_dp[u][1] = 0;

    for (int v : adj[u]) {
        if (v == parent) continue;
        maxMatching(v, u);
        match_dp[u][0] += max(match_dp[v][0], match_dp[v][1]);
    }

    // Try matching u with each child
    for (int v : adj[u]) {
        if (v == parent) continue;
        int gain = 1 + match_dp[v][0] - max(match_dp[v][0], match_dp[v][1]);
        match_dp[u][1] = max(match_dp[u][1], match_dp[u][0] + gain);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== TREE DP ===" << endl;

    // Build sample tree:
    //      1
    //    / | \
    //   2  3  4
    //  / \    |
    // 5   6   7
    int n = 7;
    n_nodes = n;
    auto addEdge = [](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    addEdge(1, 2); addEdge(1, 3); addEdge(1, 4);
    addEdge(2, 5); addEdge(2, 6); addEdge(4, 7);

    for (int i = 1; i <= n; i++) val[i] = i * 10;  // Weights

    // Tree Diameter
    diameter = 0;
    treeDiameter(1, 0);
    cout << "\n--- Tree Diameter ---" << endl;
    cout << "Diameter: " << diameter << endl;

    // Max Independent Set
    maxIndependentSet(1, 0);
    cout << "\n--- Max Independent Set ---" << endl;
    cout << "Max sum: " << max(dp_take[1], dp_skip[1]) << endl;

    // Vertex Cover
    vertexCover(1, 0);
    cout << "\n--- Vertex Cover ---" << endl;
    cout << "Min cover: " << min(vc_take[1], vc_skip[1]) << endl;

    // Rerooting — Sum of distances
    dfs_down(1, 0);
    dfs_reroot(1, 0);
    cout << "\n--- Rerooting DP (Sum of Distances) ---" << endl;
    for (int i = 1; i <= n; i++) {
        cout << "Node " << i << ": dist_sum = " << dist_sum[i] << endl;
    }

    // Max Matching
    maxMatching(1, 0);
    cout << "\n--- Max Matching ---" << endl;
    cout << "Max matching: " << max(match_dp[1][0], match_dp[1][1]) << endl;

    // Cleanup
    for (int i = 0; i <= n; i++) adj[i].clear();

    return 0;
}

