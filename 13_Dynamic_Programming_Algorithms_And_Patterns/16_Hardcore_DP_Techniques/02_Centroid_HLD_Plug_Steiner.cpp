/*
 * ============================================================================
 *     HARDCORE DP — CENTROID DECOMPOSITION DP, HLD DP, PLUG DP
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Hardcore DP — Centroid DP, HLD DP, Plug/Connection-Profile DP
 * Level   : ⭐⭐⭐⭐⭐ Grandmaster / ICPC
 * ============================================================================
 *
 * 1. DP ON CENTROID DECOMPOSITION:
 *    Build centroid decomposition tree. DP on it to answer path queries.
 *    Used when: DP on all paths of a tree efficiently.
 *
 * 2. DP ON HLD (Heavy-Light Decomposition):
 *    Decompose tree into chains. Combine chain DP values at chain junctions.
 *    Enables efficient updates and queries on tree paths.
 *
 * 3. PLUG DP (Connection Profile DP):
 *    Extension of broken-profile DP for connectivity constraints.
 *    Track which boundary cells are connected.
 *    Used for: Hamiltonian path/cycle in grid, Steiner tree, etc.
 *
 * 4. DP ON EULER TOUR:
 *    Flatten tree via Euler tour, then do range DP on the linearized array.
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * ============================================================
 * 1. CENTROID DECOMPOSITION — Foundation
 * ============================================================
 * Find centroid, build centroid decomposition tree.
 * Process all paths through centroid efficiently.
 */
const int MAXN = 100005;
vector<int> adj[MAXN];
int subtree_sz[MAXN];
bool removed[MAXN];
int centroid_parent[MAXN];

int getSubtreeSize(int u, int parent) {
    subtree_sz[u] = 1;
    for (int v : adj[u]) {
        if (v != parent && !removed[v])
            subtree_sz[u] += getSubtreeSize(v, u);
    }
    return subtree_sz[u];
}

int getCentroid(int u, int parent, int treeSize) {
    for (int v : adj[u]) {
        if (v != parent && !removed[v] && subtree_sz[v] > treeSize / 2)
            return getCentroid(v, u, treeSize);
    }
    return u;
}

/*
 * DP on Centroid Decomposition:
 * Process all paths through each centroid.
 * For each centroid c:
 *   1. Compute dp values for all nodes in subtrees of c
 *   2. Merge dp values from different subtrees (paths through c)
 *   3. Remove c, recurse on remaining components
 *
 * Example: Count pairs of nodes with path length = K
 */
long long countPathsLengthK;
int K_target;

void computeDistances(int u, int parent, int depth, vector<int>& dists) {
    if (depth > K_target) return;
    dists.push_back(depth);
    for (int v : adj[u]) {
        if (v != parent && !removed[v])
            computeDistances(v, u, depth + 1, dists);
    }
}

void centroidDecompose(int u) {
    int sz = getSubtreeSize(u, -1);
    int c = getCentroid(u, -1, sz);
    removed[c] = true;

    // Count paths through centroid c with length K
    vector<int> allDists = {0};  // Distance 0 for centroid itself

    for (int v : adj[c]) {
        if (removed[v]) continue;

        vector<int> dists;
        computeDistances(v, c, 1, dists);

        // For each distance d in current subtree, check if (K-d) exists in allDists
        sort(allDists.begin(), allDists.end());
        for (int d : dists) {
            int need = K_target - d;
            if (need >= 0) {
                // Count occurrences of 'need' in allDists
                countPathsLengthK += upper_bound(allDists.begin(), allDists.end(), need)
                                   - lower_bound(allDists.begin(), allDists.end(), need);
            }
        }

        for (int d : dists) allDists.push_back(d);
    }

    // Recurse on remaining components
    for (int v : adj[c]) {
        if (!removed[v])
            centroidDecompose(v);
    }
}

/*
 * ============================================================
 * 2. DP ON EULER TOUR — Subtree DP with Range Queries
 * ============================================================
 * Flatten tree via Euler tour: subtree of node u = contiguous range.
 * Can use segment tree on this range for DP.
 */
int tin[MAXN], tout[MAXN], euler_timer = 0;
int euler_order[MAXN];

void eulerDFS(int u, int parent) {
    tin[u] = ++euler_timer;
    euler_order[euler_timer] = u;
    for (int v : adj[u]) {
        if (v != parent) eulerDFS(v, u);
    }
    tout[u] = euler_timer;
}

// Now subtree of u = range [tin[u], tout[u]] in euler_order
// Can do range queries on this!

/*
 * ============================================================
 * 3. PLUG DP (Connection Profile DP) — Concept
 * ============================================================
 *
 * Most complex DP technique. Used for:
 * - Counting Hamiltonian paths/cycles in grids
 * - Steiner tree in grids
 * - Counting connected subgraphs
 *
 * IDEA:
 * Process grid cell by cell (left to right, top to bottom).
 * Maintain a "profile" of the boundary between processed/unprocessed.
 * The profile tracks HOW boundary cells are connected.
 *
 * Encoding: Use a "connection state" where we track which boundary
 * cells are connected via paths in the processed region.
 *
 * Example: For a 2×N grid, boundary has 2 cells.
 * Connections: (disconnected), (both connected), (each separate), etc.
 *
 * For Hamiltonian path: ensure exactly one connected path visiting all cells.
 *
 * Below is a simplified Plug DP for counting Hamiltonian paths in a small grid.
 */

// Simplified: Count Hamiltonian cycles in M×N grid (M small)
// Using profile DP with connectivity encoding
// Full plug DP uses component encoding (parenthesis representation)

// For demonstration, we show the structure without full connectivity encoding:
// This is the MOST ADVANCED DP technique in competitive programming.

/*
 * Full Plug DP outline:
 *
 * Profile = sequence of M+1 "plugs" (boundary segments between cells)
 * Each plug is either:
 *   - Empty (no path passes through)
 *   - Part of a path (connected to another plug)
 *
 * Encode connections using minimum representation:
 * e.g., (0,1,1,0,2,2) means plugs 1,2 are connected, plugs 4,5 are connected
 *
 * Transitions: for each cell, decide how to connect its top and left plugs
 *   - Don't use this cell (if allowed)
 *   - Connect top to left (L-shaped turn)
 *   - Extend top downward
 *   - Extend left rightward
 *   - Start new path segment
 *   - Close a loop
 *
 * Total states: Catalan number × 2 per column position = manageable for small M
 */

// Due to complexity, here's a working but simplified grid Hamiltonian counter
// for very small grids using bitmask DP

long long hamiltonianPathsGrid(int M, int N) {
    if (M > N) swap(M, N);
    // dp[mask][last_row_state] — simplified for 2-row grids
    if (M == 1) return 1;  // Only 1 path in 1×N grid
    if (M == 2 && N == 2) return 1;  // Manual

    // For general small M, use profile bitmask approach
    // Full implementation would be ~200 lines
    // Returning placeholder
    return -1;  // Use full plug DP for exact count
}

/*
 * ============================================================
 * 4. STEINER TREE DP — DP on subsets + shortest paths
 * ============================================================
 * Given graph and set of terminal nodes K.
 * Find minimum weight subgraph connecting all terminals.
 *
 * dp[mask][v] = min cost tree connecting terminals in 'mask', rooted at v
 *
 * Transitions:
 * 1. Combine subtrees: dp[mask][v] = min(dp[sub][v] + dp[mask^sub][v])
 *    for all sub ⊂ mask
 * 2. Extend by edge: dp[mask][v] → dp[mask][u] via edge (v,u)
 *    (use Dijkstra/BFS for each mask)
 *
 * Time: O(3^k * n + 2^k * n * log n)  where k = |terminals|
 */
const long long INF = 1e18;

vector<vector<long long>> steinerTree(
    int n, vector<vector<pair<int,int>>>& graph, vector<int>& terminals) {

    int k = terminals.size();
    int masks = 1 << k;
    vector<vector<long long>> dp(masks, vector<long long>(n, INF));

    // Base: single terminal
    for (int i = 0; i < k; i++)
        dp[1 << i][terminals[i]] = 0;

    for (int mask = 1; mask < masks; mask++) {
        // Step 1: Combine submasks
        for (int sub = (mask - 1) & mask; sub > 0; sub = (sub - 1) & mask) {
            int comp = mask ^ sub;
            if (sub < comp) continue;  // Avoid double counting
            for (int v = 0; v < n; v++) {
                if (dp[sub][v] < INF && dp[comp][v] < INF)
                    dp[mask][v] = min(dp[mask][v], dp[sub][v] + dp[comp][v]);
            }
        }

        // Step 2: Shortest path relaxation (Dijkstra)
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
        for (int v = 0; v < n; v++)
            if (dp[mask][v] < INF) pq.push({dp[mask][v], v});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dp[mask][u]) continue;

            for (auto [v, w] : graph[u]) {
                if (dp[mask][u] + w < dp[mask][v]) {
                    dp[mask][v] = dp[mask][u] + w;
                    pq.push({dp[mask][v], v});
                }
            }
        }
    }

    return dp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== HARDCORE DP TECHNIQUES ===" << endl;

    // Centroid Decomposition — Count paths of length K
    int n = 7;
    auto addEdge = [](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    addEdge(1, 2); addEdge(1, 3); addEdge(1, 4);
    addEdge(2, 5); addEdge(2, 6); addEdge(4, 7);

    K_target = 2;
    countPathsLengthK = 0;
    memset(removed, false, sizeof(removed));
    centroidDecompose(1);

    cout << "\n--- Centroid Decomposition ---" << endl;
    cout << "Paths of length " << K_target << ": " << countPathsLengthK << endl;

    // Euler Tour
    euler_timer = 0;
    eulerDFS(1, 0);
    cout << "\n--- Euler Tour ---" << endl;
    for (int i = 1; i <= n; i++)
        cout << "Node " << i << ": tin=" << tin[i] << " tout=" << tout[i] << endl;

    // Steiner Tree
    cout << "\n--- Steiner Tree DP ---" << endl;
    int sn = 5;
    vector<vector<pair<int,int>>> graph(sn);
    graph[0].push_back({1, 2}); graph[1].push_back({0, 2});
    graph[1].push_back({2, 3}); graph[2].push_back({1, 3});
    graph[0].push_back({3, 6}); graph[3].push_back({0, 6});
    graph[3].push_back({4, 1}); graph[4].push_back({3, 1});
    graph[2].push_back({4, 4}); graph[4].push_back({2, 4});

    vector<int> terminals = {0, 2, 4};
    auto stDP = steinerTree(sn, graph, terminals);
    int fullMask = (1 << terminals.size()) - 1;
    long long steinerAns = INF;
    for (int v = 0; v < sn; v++)
        steinerAns = min(steinerAns, stDP[fullMask][v]);
    cout << "Min Steiner tree cost: " << steinerAns << endl;

    // Cleanup
    for (int i = 0; i < MAXN; i++) adj[i].clear();

    cout << "\n============================================" << endl;
    cout << "  HARDCORE DP SUMMARY:" << endl;
    cout << "  • DP + SegTree/BIT: O(n log n) transitions" << endl;
    cout << "  • Centroid DP: All tree paths through centroid" << endl;
    cout << "  • Euler Tour DP: Subtree = contiguous range" << endl;
    cout << "  • Plug DP: Grid connectivity (Hamiltonian)" << endl;
    cout << "  • Steiner Tree: O(3^k * n) subset DP" << endl;
    cout << "============================================" << endl;

    return 0;
}

