/*
 * ============================================================================
 *              TREE DP WITH KNAPSACK — ICPC ESSENTIAL
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Tree DP — Knapsack on Trees, Subtree Selection
 * Level   : ⭐⭐⭐⭐ Expert / ICPC
 * ============================================================================
 *
 * TREE KNAPSACK:
 *   Given a tree where each node has weight and value.
 *   Select at most K nodes such that:
 *   - If you select a node, all ancestors must be selected too
 *   - Maximize total value while total weight ≤ capacity
 *
 *   dp[u][j] = max value using j items from subtree of u (u must be selected)
 *
 *   Merging children: for each child v of u:
 *     dp[u][j] = max over split: dp[u][j-k] + dp[v][k]
 *
 *   KEY: Process children one by one, like merging knapsacks.
 *   TIME: O(n × K²) with careful implementation, or O(n × K) amortized.
 *
 * CLASSIC PROBLEMS:
 *   - CSES: Tree Matching
 *   - BOI 2003: Sequence
 *   - CF Educational Round: Tree + Knapsack problems
 *   - Select K nodes in tree to maximize value with dependency
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;
vector<int> adj[MAXN];
int val[MAXN], weight_node[MAXN];
int subtree_sz[MAXN];

/*
 * 1. TREE KNAPSACK — Select at most K nodes, ancestors required
 *    dp[u][j] = max value taking j nodes from u's subtree (u included)
 *
 *    Time: O(N × K) amortized (not O(N × K²)!) because
 *    each pair of nodes is compared only once.
 */
int K_limit;
long long dp_tree[MAXN][MAXN];  // Careful with memory: use vector for large N

void dfs_knapsack(int u, int parent) {
    subtree_sz[u] = 1;
    dp_tree[u][0] = 0;        // Take 0 from subtree
    dp_tree[u][1] = val[u];   // Take node u itself

    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs_knapsack(v, u);

        // Merge child v's knapsack into u's knapsack
        // Iterate backwards to avoid using same child twice
        for (int j = min(subtree_sz[u] + subtree_sz[v], K_limit); j >= 1; j--) {
            for (int k = max(0, j - subtree_sz[u]); k <= min(j - 1, subtree_sz[v]); k++) {
                dp_tree[u][j] = max(dp_tree[u][j], dp_tree[u][j - k] + dp_tree[v][k]);
            }
        }
        subtree_sz[u] += subtree_sz[v];
    }
}

/*
 * 2. INDEPENDENT SET VARIANT — Select K independent nodes, maximize value
 *    dp[u][j][0] = max value, j nodes from subtree, u NOT selected
 *    dp[u][j][1] = max value, j nodes from subtree, u IS selected
 */
long long dp_indep[MAXN][2];  // Simplified: just take/skip
int dp_k[MAXN][102][2];       // dp_k[u][j][take]

void dfs_indep_k(int u, int parent) {
    subtree_sz[u] = 1;
    memset(dp_k[u], -1, sizeof(dp_k[u]));
    dp_k[u][0][0] = 0;
    dp_k[u][1][1] = val[u];

    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs_indep_k(v, u);

        // Temporary array to merge
        int new_dp[102][2];
        memset(new_dp, -1, sizeof(new_dp));

        for (int j = min(subtree_sz[u] + subtree_sz[v], K_limit); j >= 0; j--) {
            for (int take_u : {0, 1}) {
                for (int k = 0; k <= min(j, subtree_sz[v]); k++) {
                    int from_u = j - k;
                    if (from_u > subtree_sz[u]) continue;
                    if (dp_k[u][from_u][take_u] == -1) continue;

                    // If u is taken, v cannot be taken
                    if (take_u == 1) {
                        if (dp_k[v][k][0] != -1)
                            new_dp[j][take_u] = max(new_dp[j][take_u],
                                dp_k[u][from_u][take_u] + dp_k[v][k][0]);
                    } else {
                        // u not taken, v can be taken or not
                        for (int take_v : {0, 1}) {
                            if (dp_k[v][k][take_v] != -1)
                                new_dp[j][take_u] = max(new_dp[j][take_u],
                                    dp_k[u][from_u][take_u] + dp_k[v][k][take_v]);
                        }
                    }
                }
            }
        }

        subtree_sz[u] += subtree_sz[v];
        memcpy(dp_k[u], new_dp, sizeof(new_dp));
    }
}

/*
 * 3. TREE DP — Select exactly K edges (matching)
 *    dp[u][j][0/1] = max weight matching with j edges in subtree of u
 *    0 = u is unmatched, 1 = u is matched with one child
 */
int dp_match[MAXN][102][2];

void dfs_matching(int u, int parent) {
    subtree_sz[u] = 1;
    memset(dp_match[u], -1, sizeof(dp_match[u]));
    dp_match[u][0][0] = 0;

    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs_matching(v, u);

        int new_dp[102][2];
        memset(new_dp, -1, sizeof(new_dp));

        for (int j = min(subtree_sz[u] + subtree_sz[v], K_limit); j >= 0; j--) {
            for (int mu : {0, 1}) {  // u matched?
                for (int k = 0; k <= min(j, subtree_sz[v]); k++) {
                    int from_u = j - k;
                    if (from_u > subtree_sz[u]) continue;
                    if (dp_match[u][from_u][mu] == -1) continue;

                    for (int mv : {0, 1}) {  // v matched?
                        if (dp_match[v][k][mv] == -1) continue;

                        // Option 1: don't match edge (u,v)
                        new_dp[j][mu] = max(new_dp[j][mu],
                            dp_match[u][from_u][mu] + dp_match[v][k][mv]);

                        // Option 2: match edge (u,v) — u and v must both be unmatched
                        if (mu == 0 && mv == 0 && j + 1 <= K_limit) {
                            new_dp[j + 1][1] = max(new_dp[j + 1][1],
                                dp_match[u][from_u][0] + dp_match[v][k][0] + 1);
                            // +1 for the edge weight (or use actual edge weight)
                        }
                    }
                }
            }
        }

        subtree_sz[u] += subtree_sz[v];
        memcpy(dp_match[u], new_dp, sizeof(new_dp));
    }
}

/*
 * 4. APPLE TREE PROBLEM (Classic)
 *    Tree with n nodes rooted at 1. Each edge has cost to traverse.
 *    Leaves have apples. Collect max apples using at most K steps.
 *    Must return to root.
 *
 *    dp[u][j] = max apples from subtree of u using j steps
 *    To visit a child and return: costs 2 (go + return) plus child's steps
 */
int apple[MAXN];  // 1 if node has apple
long long dp_apple[MAXN][MAXN];

void dfs_apple(int u, int parent) {
    subtree_sz[u] = 1;
    dp_apple[u][0] = apple[u];

    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs_apple(v, u);

        for (int j = min(subtree_sz[u] + subtree_sz[v], K_limit); j >= 0; j--) {
            for (int k = 1; k <= min(j, subtree_sz[v]); k++) {
                // Use k steps for child v (includes 2 for the edge u-v)
                if (j - k >= 0 && k >= 2) {  // Need at least 2 steps to visit child
                    dp_apple[u][j] = max(dp_apple[u][j],
                        dp_apple[u][j - k] + dp_apple[v][k - 2]);
                }
            }
        }
        subtree_sz[u] += subtree_sz[v];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== TREE DP WITH KNAPSACK ===" << endl;

    // Build sample tree:
    //      1(10)
    //     / \
    //   2(20) 3(5)
    //   / \
    // 4(15) 5(25)
    int n = 5;
    K_limit = 3;
    auto addEdge = [](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    addEdge(1, 2); addEdge(1, 3); addEdge(2, 4); addEdge(2, 5);
    val[1] = 10; val[2] = 20; val[3] = 5; val[4] = 15; val[5] = 25;

    // Initialize dp
    memset(dp_tree, 0, sizeof(dp_tree));
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= K_limit; j++)
            dp_tree[i][j] = -1e18;
    for (int i = 0; i <= n; i++) dp_tree[i][0] = 0;

    dfs_knapsack(1, 0);

    cout << "\n--- Tree Knapsack (Select K nodes, ancestors required) ---" << endl;
    for (int k = 0; k <= K_limit; k++) {
        cout << "K=" << k << ": max value = " << dp_tree[1][k] << endl;
    }

    // Cleanup
    for (int i = 0; i < MAXN; i++) adj[i].clear();

    cout << "\n============================================" << endl;
    cout << "  TREE KNAPSACK KEY IDEA:" << endl;
    cout << "  1. DFS bottom-up" << endl;
    cout << "  2. For each child: merge knapsack tables" << endl;
    cout << "  3. dp[u][j] = max(dp[u][j-k] + dp[v][k])" << endl;
    cout << "  4. Careful iteration order (backward) avoids" << endl;
    cout << "     counting same child twice" << endl;
    cout << "  5. Amortized O(N×K) due to subtree size bound" << endl;
    cout << "============================================" << endl;

    return 0;
}

