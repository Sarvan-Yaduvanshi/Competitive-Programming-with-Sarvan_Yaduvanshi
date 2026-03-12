/*
 * ============================================================================
 *                     GRAPH DP — DAG & SHORTEST PATHS
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Graph DP — DAG DP, Longest Path, Floyd-Warshall, SOS DP
 * Level   : ⭐⭐⭐ Advanced
 * ============================================================================
 *
 * GRAPH DP PATTERN:
 *   DP on graphs works when there's a natural ordering (DAG/topological).
 *   Process nodes in topological order, each node's dp depends on predecessors.
 *
 * KEY PROBLEMS:
 * 1. Longest/Shortest Path in DAG — topo sort + relax
 * 2. Count Paths in DAG
 * 3. Floyd-Warshall — All pairs shortest path
 * 4. Bellman-Ford as DP
 * 5. SOS DP (Sum over Subsets)
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * 1. LONGEST PATH IN DAG
 *    Topological sort + relax edges
 *    dp[u] = longest path ending at u
 *    Time: O(V + E)
 */
int longestPathDAG(int n, vector<vector<pair<int,int>>>& adj) {
    // Compute in-degree
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; u++)
        for (auto [v, w] : adj[u])
            indeg[v]++;

    // Topological sort (Kahn's)
    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0) q.push(i);

    vector<int> topo;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (auto [v, w] : adj[u])
            if (--indeg[v] == 0) q.push(v);
    }

    // DP: longest path
    vector<int> dp(n, 0);
    for (int u : topo) {
        for (auto [v, w] : adj[u]) {
            dp[v] = max(dp[v], dp[u] + w);
        }
    }
    return *max_element(dp.begin(), dp.end());
}

/*
 * 2. COUNT PATHS IN DAG (from source to all nodes)
 *    dp[v] = number of paths from source to v
 *    dp[v] = sum of dp[u] for all u → v edges
 */
vector<long long> countPathsDAG(int n, vector<vector<int>>& adj, int source) {
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; u++)
        for (int v : adj[u])
            indeg[v]++;

    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0) q.push(i);

    vector<int> topo;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (int v : adj[u])
            if (--indeg[v] == 0) q.push(v);
    }

    vector<long long> dp(n, 0);
    dp[source] = 1;
    for (int u : topo) {
        for (int v : adj[u]) {
            dp[v] += dp[u];
        }
    }
    return dp;
}

/*
 * 3. FLOYD-WARSHALL — All Pairs Shortest Path
 *    dp[k][i][j] = shortest path from i to j using intermediate nodes {0..k}
 *    dp[k][i][j] = min(dp[k-1][i][j], dp[k-1][i][k] + dp[k-1][k][j])
 *
 *    Space optimized to O(n²) — just dp[i][j] updated in-place
 *    Time: O(n³)
 */
const int INF = 1e9;
vector<vector<int>> floydWarshall(int n, vector<vector<int>>& dist) {
    // dist[i][j] = direct edge weight (INF if no edge)
    auto dp = dist;

    for (int k = 0; k < n; k++)        // Intermediate node
        for (int i = 0; i < n; i++)    // Source
            for (int j = 0; j < n; j++) // Destination
                if (dp[i][k] != INF && dp[k][j] != INF)
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);

    return dp;
}

/*
 * 4. BELLMAN-FORD as DP
 *    dp[k][v] = shortest path from source to v using at most k edges
 *    dp[k][v] = min over all edges (u,v,w): dp[k-1][u] + w
 *    Time: O(V*E)
 */
vector<int> bellmanFord(int n, vector<tuple<int,int,int>>& edges, int source) {
    vector<int> dp(n, INF);
    dp[source] = 0;

    for (int k = 0; k < n - 1; k++) {
        vector<int> newDp = dp;
        for (auto [u, v, w] : edges) {
            if (dp[u] != INF) {
                newDp[v] = min(newDp[v], dp[u] + w);
            }
        }
        dp = newDp;
    }
    return dp;
}

/*
 * 5. SOS DP (Sum over Subsets)
 *    For each mask, compute f[mask] = sum of a[sub] for all submasks sub of mask
 *
 *    Naive: O(3^n) by iterating submasks
 *    SOS: O(n * 2^n) — process one bit at a time
 *
 *    dp[mask][i] = sum over all subsets that differ from mask only in bits 0..i
 *    Final: dp[mask][n-1] = sum over all subsets of mask
 */
vector<long long> sosDP(vector<int>& a, int n) {
    int N = 1 << n;
    vector<long long> dp(N);

    for (int i = 0; i < N; i++) dp[i] = a[i];

    for (int bit = 0; bit < n; bit++) {
        for (int mask = 0; mask < N; mask++) {
            if (mask & (1 << bit)) {
                dp[mask] += dp[mask ^ (1 << bit)];
            }
        }
    }
    return dp;
    // dp[mask] = sum of a[sub] for all submasks sub of mask
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== GRAPH DP ===" << endl;

    // Longest Path in DAG
    int n = 6;
    vector<vector<pair<int,int>>> adj(n);
    adj[0].push_back({1, 5}); adj[0].push_back({2, 3});
    adj[1].push_back({3, 6}); adj[1].push_back({2, 2});
    adj[2].push_back({4, 4}); adj[2].push_back({5, 2}); adj[2].push_back({3, 7});
    adj[3].push_back({5, 1}); adj[3].push_back({4, -1});
    adj[4].push_back({5, -2});

    cout << "\n--- Longest Path in DAG ---" << endl;
    cout << "Longest path: " << longestPathDAG(n, adj) << endl;

    // Floyd-Warshall
    vector<vector<int>> dist = {
        {0, 3, INF, 7},
        {8, 0, 2, INF},
        {5, INF, 0, 1},
        {2, INF, INF, 0}
    };
    auto apsp = floydWarshall(4, dist);
    cout << "\n--- Floyd-Warshall ---" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            cout << (apsp[i][j] >= INF ? "INF" : to_string(apsp[i][j])) << "\t";
        cout << endl;
    }

    // SOS DP
    int bits = 3;
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8};  // 2^3 = 8 values
    auto sos = sosDP(a, bits);
    cout << "\n--- SOS DP ---" << endl;
    for (int mask = 0; mask < (1 << bits); mask++) {
        cout << "f[" << bitset<3>(mask) << "] = " << sos[mask] << endl;
    }

    return 0;
}

