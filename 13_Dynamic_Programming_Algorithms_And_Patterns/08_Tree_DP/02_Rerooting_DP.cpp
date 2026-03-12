/*
 * ============================================================================
 *              REROOTING DP — DETAILED TECHNIQUE
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Tree DP — Rerooting DP (Answer for every root)
 * Level   : ⭐⭐⭐⭐ Expert
 * ============================================================================
 *
 * REROOTING DP:
 *   Compute answer for EVERY node as root in O(n) total.
 *
 *   Two DFS passes:
 *   Pass 1 (DFS down): dp_down[u] = answer with u's subtree only
 *   Pass 2 (DFS up):   dp_full[u] = answer considering entire tree rooted at u
 *
 *   When "moving root" from u to child v:
 *     - Remove v's contribution from u's answer
 *     - Add u's "remaining" answer to v
 *
 * CLASSIC PROBLEMS:
 *   - Sum of distances in tree (LeetCode 834)
 *   - AtCoder DP V — Subtree
 *   - CF 1187E — Tree Painting
 *   - Maximum subtree sum for each root
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * PROBLEM 1: Sum of Distances (LeetCode 834)
 * For each node, compute sum of distances to all other nodes.
 *
 * Key insight for rerooting:
 * When root moves from parent u to child v:
 *   dist_sum[v] = dist_sum[u] - size[v] + (n - size[v])
 * Because:
 *   - Nodes in v's subtree get 1 closer → subtract size[v]
 *   - Nodes outside v's subtree get 1 farther → add (n - size[v])
 */
class SumOfDistances {
    int n;
    vector<vector<int>> adj;
    vector<int> subtreeSize;
    vector<long long> distSum;

    void dfs_down(int u, int parent) {
        subtreeSize[u] = 1;
        distSum[u] = 0;
        for (int v : adj[u]) {
            if (v == parent) continue;
            dfs_down(v, u);
            subtreeSize[u] += subtreeSize[v];
            distSum[u] += distSum[v] + subtreeSize[v];
        }
    }

    void dfs_reroot(int u, int parent) {
        for (int v : adj[u]) {
            if (v == parent) continue;
            distSum[v] = distSum[u] - subtreeSize[v] + (n - subtreeSize[v]);
            dfs_reroot(v, u);
        }
    }

public:
    vector<long long> solve(int n, vector<vector<int>>& edges) {
        this->n = n;
        adj.resize(n);
        subtreeSize.resize(n);
        distSum.resize(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        dfs_down(0, -1);
        dfs_reroot(0, -1);
        return distSum;
    }
};

/*
 * PROBLEM 2: Maximum Subtree Beauty
 * Each node has value val[u]. For each root r, compute:
 *   answer[r] = max over all subtrees T of r: sum of val in T
 *
 * This needs rerooting where dp_down[u] = max(0, sum of dp_down[children] + val[u])
 */
class MaxSubtreeSum {
    int n;
    vector<vector<int>> adj;
    vector<long long> val;
    vector<long long> dp_down;   // Max subtree sum in u's subtree
    vector<long long> dp_full;   // Full answer for u as root

    void dfs1(int u, int parent) {
        dp_down[u] = val[u];
        for (int v : adj[u]) {
            if (v == parent) continue;
            dfs1(v, u);
            dp_down[u] += max(0LL, dp_down[v]);
        }
    }

    void dfs2(int u, int parent, long long parentContrib) {
        // dp_full[u] = dp_down[u] + max(0, parentContrib)
        dp_full[u] = dp_down[u] + max(0LL, parentContrib);

        for (int v : adj[u]) {
            if (v == parent) continue;
            // When rerooting from u to v:
            // v loses its own subtree contribution from u
            // v gains u's contribution minus v's subtree
            long long uWithoutV = dp_down[u] - max(0LL, dp_down[v]);
            long long contrib = uWithoutV + max(0LL, parentContrib) - val[u] + val[u];
            // Simplified: what u sees from all other directions
            long long fromParentSide = dp_full[u] - max(0LL, dp_down[v]);
            // This is the contribution from u's perspective without v

            dfs2(v, u, fromParentSide - val[v]);  // Approximate
        }
    }

public:
    vector<long long> solve(int n, vector<vector<int>>& edges, vector<long long>& values) {
        this->n = n;
        val = values;
        adj.resize(n);
        dp_down.resize(n);
        dp_full.resize(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        dfs1(0, -1);
        dfs2(0, -1, 0);
        return dp_full;
    }
};

/*
 * PROBLEM 3: Tree Painting (CF 1187E)
 * Paint nodes one by one. When painting node u, gain = size of u's connected
 * component among unpainted nodes. Maximize total gain.
 *
 * Answer = Σ subtreeSize[u] for u in [1..n] when rooted at optimal root.
 * Use rerooting to find best root.
 */
class TreePainting {
    int n;
    vector<vector<int>> adj;
    vector<long long> subtreeSize;
    vector<long long> answer;  // answer[u] = sum of subtree sizes when rooted at u

    void dfs1(int u, int parent) {
        subtreeSize[u] = 1;
        for (int v : adj[u]) {
            if (v == parent) continue;
            dfs1(v, u);
            subtreeSize[u] += subtreeSize[v];
        }
    }

    void computeAnswer(int u, int parent) {
        // answer[u] = sum of subtreeSize when rooted at u
        if (parent == -1) {
            answer[u] = 0;
            // Compute directly for root
            function<void(int, int)> calc = [&](int v, int p) {
                answer[u] += subtreeSize[v];
                for (int w : adj[v]) {
                    if (w != p) calc(w, v);
                }
            };
            calc(u, -1);
        }

        for (int v : adj[u]) {
            if (v == parent) continue;
            // When we move root from u to v:
            // Subtree sizes of v's descendants stay same (relative to v as root)
            // But v's subtree becomes n, and u's "subtree" becomes n - subtreeSize[v]
            // answer[v] = answer[u] - subtreeSize[v] + (n - subtreeSize[v])
            answer[v] = answer[u] - subtreeSize[v] + (n - subtreeSize[v]);
            computeAnswer(v, u);
        }
    }

public:
    long long solve(int n, vector<vector<int>>& edges) {
        this->n = n;
        adj.resize(n);
        subtreeSize.resize(n);
        answer.resize(n, 0);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        dfs1(0, -1);
        computeAnswer(0, -1);
        return *max_element(answer.begin(), answer.end());
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== REROOTING DP ===" << endl;

    // Sum of Distances
    cout << "\n--- Sum of Distances ---" << endl;
    int n = 6;
    vector<vector<int>> edges = {{0,1},{0,2},{2,3},{2,4},{2,5}};
    SumOfDistances sd;
    auto dists = sd.solve(n, edges);
    for (int i = 0; i < n; i++)
        cout << "Node " << i << ": sum_dist = " << dists[i] << endl;

    // Tree Painting
    cout << "\n--- Tree Painting ---" << endl;
    int n2 = 5;
    vector<vector<int>> edges2 = {{0,1},{0,2},{1,3},{1,4}};
    TreePainting tp;
    cout << "Max total gain: " << tp.solve(n2, edges2) << endl;

    cout << "\n============================================" << endl;
    cout << "  REROOTING DP TEMPLATE:" << endl;
    cout << "  1. DFS down: compute dp_down[u] from children" << endl;
    cout << "  2. DFS up:   compute dp_full[u] by re-rooting" << endl;
    cout << "  3. Key formula: dp[v] = f(dp[u], remove(v))" << endl;
    cout << "============================================" << endl;

    return 0;
}

