/*
 * ============================================================================
 *              DP ON FUNCTIONAL GRAPHS & BFS/DFS TRANSITIONS
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Graph DP — Functional Graphs, Layered Graphs, DP with BFS/DFS
 * Level   : ⭐⭐⭐ Advanced
 * ============================================================================
 *
 * DP ON FUNCTIONAL GRAPH:
 *   Every node has exactly ONE outgoing edge (successor function).
 *   Forms "rho" (ρ) shape: tail + cycle.
 *   Use cycle detection (Floyd/Brent) + DP along path.
 *
 * DP ON LAYERED GRAPH:
 *   Nodes organized in layers. Edges only go to next layer.
 *   Natural for DP: process layer by layer.
 *
 * DP WITH BFS/DFS TRANSITIONS:
 *   DP where transitions follow BFS/DFS order.
 *   Shortest path problems as DP.
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * 1. DP ON FUNCTIONAL GRAPH
 *    Each node has exactly one successor: next[i].
 *    Find length of path from each node before entering a cycle.
 *    Also: compute some aggregate (sum/max) along the path.
 */
class FunctionalGraphDP {
    int n;
    vector<int> next_node;
    vector<int> dp;     // dp[i] = answer for node i
    vector<int> state;  // 0: unvisited, 1: in-progress, 2: done

    void dfs(int u) {
        if (state[u] == 2) return;  // Already computed
        if (state[u] == 1) {
            // Found cycle! Mark all nodes in cycle
            dp[u] = 0;  // Cycle node: dp = 0 (or cycle length)
            state[u] = 2;
            return;
        }

        state[u] = 1;  // In progress
        int v = next_node[u];
        dfs(v);

        if (state[u] != 2) {  // Not part of cycle
            dp[u] = dp[v] + 1;  // Distance to cycle
            state[u] = 2;
        }
    }

public:
    // Compute distance from each node to cycle
    vector<int> distanceToCycle(int n, vector<int>& succ) {
        this->n = n;
        next_node = succ;
        dp.assign(n, 0);
        state.assign(n, 0);

        // First, find all cycle nodes
        vector<bool> inCycle(n, false);
        vector<bool> visited(n, false);

        for (int i = 0; i < n; i++) {
            if (visited[i]) continue;

            // Tortoise and hare to detect cycle
            int slow = i, fast = i;
            do {
                slow = succ[slow];
                fast = succ[succ[fast]];
            } while (slow != fast);

            // Mark cycle nodes
            int node = slow;
            do {
                inCycle[node] = true;
                visited[node] = true;
                node = succ[node];
            } while (node != slow);
        }

        // DP: distance from each non-cycle node to cycle
        dp.assign(n, 0);
        vector<int> dist(n, -1);
        for (int i = 0; i < n; i++) {
            if (inCycle[i]) dist[i] = 0;
        }

        // BFS from cycle nodes backwards
        // Build reverse graph
        vector<vector<int>> rev(n);
        for (int i = 0; i < n; i++) rev[succ[i]].push_back(i);

        queue<int> q;
        for (int i = 0; i < n; i++)
            if (inCycle[i]) q.push(i);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : rev[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return dist;
    }
};

/*
 * 2. DP ON LAYERED GRAPH — Shortest path in k layers
 *    n nodes, m edges. Find shortest path using at most k edges.
 *    dp[layer][node] = shortest distance using at most 'layer' edges.
 *    (This is essentially Bellman-Ford!)
 */
vector<long long> layeredGraphDP(int n, vector<tuple<int,int,long long>>& edges, int src, int k) {
    const long long INF = 1e18;
    vector<long long> dp(n, INF);
    dp[src] = 0;

    for (int layer = 0; layer < k; layer++) {
        vector<long long> ndp = dp;  // Copy current layer
        for (auto& [u, v, w] : edges) {
            if (dp[u] != INF) {
                ndp[v] = min(ndp[v], dp[u] + w);
            }
        }
        dp = ndp;
    }
    return dp;
}

/*
 * 3. 0-1 BFS as DP
 *    Graph with edge weights 0 or 1.
 *    Use deque: weight 0 → push front, weight 1 → push back.
 *    dp[v] = shortest distance from source.
 */
vector<int> bfs01(int n, vector<vector<pair<int,int>>>& adj, int src) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    deque<int> dq;
    dq.push_back(src);

    while (!dq.empty()) {
        int u = dq.front(); dq.pop_front();

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) dq.push_front(v);
                else dq.push_back(v);
            }
        }
    }
    return dist;
}

/*
 * 4. COUNTING PATHS IN GRID WITH FORBIDDEN CELLS
 *    Grid n×m, some cells forbidden. Count paths (0,0)→(n-1,m-1).
 *    Use inclusion-exclusion with DP.
 *
 *    Sort forbidden cells by (row, col).
 *    dp[i] = paths from (0,0) to forbidden[i] avoiding other forbidden cells before it.
 *    answer = total_paths - Σ dp[i] × paths(forbidden[i] → end)
 *
 *    This is AtCoder DP Y — Grid 2.
 */
const int MOD = 1e9 + 7;

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

long long modInverse(long long a, long long mod) { return power(a, mod - 2, mod); }

// Precompute factorials for nCr
vector<long long> fact, inv_fact;
void precompute(int n) {
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i % MOD;
    inv_fact[n] = modInverse(fact[n], MOD);
    for (int i = n - 1; i >= 0; i--) inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
}

long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] % MOD * inv_fact[r] % MOD * inv_fact[n-r] % MOD;
}

// Count paths from (r1,c1) to (r2,c2) in grid (only right/down)
long long gridPaths(int r1, int c1, int r2, int c2) {
    int dr = r2 - r1, dc = c2 - c1;
    if (dr < 0 || dc < 0) return 0;
    return nCr(dr + dc, dr);
}

long long gridWithForbidden(int H, int W, vector<pair<int,int>>& forbidden) {
    precompute(H + W + 10);

    int k = forbidden.size();
    sort(forbidden.begin(), forbidden.end());

    // Add destination as last "forbidden" point
    forbidden.push_back({H - 1, W - 1});
    k++;

    vector<long long> dp(k, 0);

    for (int i = 0; i < k; i++) {
        auto [r, c] = forbidden[i];
        dp[i] = gridPaths(0, 0, r, c);

        for (int j = 0; j < i; j++) {
            auto [rj, cj] = forbidden[j];
            if (rj <= r && cj <= c) {
                dp[i] = (dp[i] - dp[j] % MOD * gridPaths(rj, cj, r, c) % MOD + MOD) % MOD;
            }
        }
    }

    return dp[k - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== GRAPH DP — ADVANCED ===" << endl;

    // Functional Graph
    FunctionalGraphDP fgdp;
    vector<int> succ = {1, 2, 3, 4, 2};  // 0→1→2→3→4→2 (cycle: 2→3→4→2)
    auto dist = fgdp.distanceToCycle(5, succ);
    cout << "\n--- Functional Graph DP ---" << endl;
    cout << "Successor: "; for (int s : succ) cout << s << " ";
    cout << "\nDistance to cycle: ";
    for (int i = 0; i < 5; i++) cout << i << ":" << dist[i] << " ";
    cout << endl;

    // 0-1 BFS
    int n = 5;
    vector<vector<pair<int,int>>> adj(n);
    adj[0].push_back({1, 1}); adj[0].push_back({2, 0});
    adj[1].push_back({3, 1}); adj[2].push_back({3, 0});
    adj[2].push_back({4, 1}); adj[3].push_back({4, 0});

    auto dist01 = bfs01(n, adj, 0);
    cout << "\n--- 0-1 BFS ---" << endl;
    for (int i = 0; i < n; i++)
        cout << "dist[" << i << "] = " << dist01[i] << endl;

    // Grid with forbidden cells
    vector<pair<int,int>> forbidden = {{1, 1}};
    cout << "\n--- Grid with Forbidden (3×3, blocked (1,1)) ---" << endl;
    cout << "Paths: " << gridWithForbidden(3, 3, forbidden) << endl;

    return 0;
}

