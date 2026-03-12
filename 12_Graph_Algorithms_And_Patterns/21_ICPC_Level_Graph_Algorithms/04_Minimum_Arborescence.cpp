/*
╔══════════════════════════════════════════════════════════════════╗
║         04 — MINIMUM ARBORESCENCE (Edmonds/Chu-Liu)             ║
║         Directed MST rooted at given vertex                     ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

MINIMUM ARBORESCENCE: Given directed weighted graph and root r,
find minimum weight set of edges such that:
  - Every vertex is reachable from r
  - Each non-root vertex has exactly one incoming edge
  - Forms a directed tree rooted at r

EDMONDS' ALGORITHM (Chu-Liu/Edmonds):
  1. For each non-root vertex, pick cheapest incoming edge
  2. If no cycle → done (this IS the arborescence)
  3. If cycle found:
     a. Contract cycle to single super-vertex
     b. Adjust edge weights
     c. Recursively solve on contracted graph
     d. Expand and reconstruct

═══════════════════════════════════════════════════════════════════
COMPLEXITY
  Time:  O(VE) naive, O(E log V) with Fibonacci heap
  Space: O(V + E)
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
#endif
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
constexpr i64 INF64 = 4e18;
#define nl '\n'

struct Edge { int u, v; i64 w; };

// Edmonds' algorithm: O(VE)
i64 minArborescence(int n, int root, vec<Edge>& edges) {
    i64 totalCost = 0;

    while (true) {
        // Step 1: Find min incoming edge for each vertex
        vec<i64> minIn(n, INF64);
        vec<int> minEdge(n, -1);

        for (int i = 0; i < (int)edges.size(); i++) {
            auto& [u, v, w] = edges[i];
            if (u != v && v != root && w < minIn[v]) {
                minIn[v] = w;
                minEdge[v] = i;
            }
        }

        // Check if all vertices reachable
        for (int i = 0; i < n; i++) {
            if (i != root && minIn[i] == INF64) return -1; // unreachable
        }

        // Add min incoming edges cost
        for (int i = 0; i < n; i++) {
            if (i != root) totalCost += minIn[i];
        }

        // Step 2: Detect cycle in selected edges
        vec<int> id(n, -1), vis(n, -1);
        int numCycles = 0;

        for (int i = 0; i < n; i++) {
            if (i == root) continue;
            int u = i;
            while (vis[u] == -1 && id[u] == -1 && u != root) {
                vis[u] = i;
                u = edges[minEdge[u]].u;
            }
            if (u != root && id[u] == -1 && vis[u] == i) {
                // Found cycle starting at u
                int v = u;
                do {
                    id[v] = numCycles;
                    v = edges[minEdge[v]].u;
                } while (v != u);
                numCycles++;
            }
        }

        if (numCycles == 0) break; // No cycles, we're done

        // Assign non-cycle vertices to their own "component"
        for (int i = 0; i < n; i++) {
            if (id[i] == -1) id[i] = numCycles++;
        }

        // Contract cycles and adjust edges
        for (auto& [u, v, w] : edges) {
            i64 oldMinIn = (v != root ? minIn[v] : 0);
            u = id[u];
            v = id[v];
            if (u != v) w -= oldMinIn; // adjust weight
        }

        n = numCycles;
        root = id[root];
    }

    return totalCost;
}

void solve() {
    int n, m, root;
    cin >> n >> m >> root; root--;

    vec<Edge> edges(m);
    for (auto& [u, v, w] : edges) { cin >> u >> v >> w; u--; v--; }

    i64 result = minArborescence(n, root, edges);
    if (result == -1) cout << "No arborescence exists" << nl;
    else cout << "Minimum arborescence cost: " << result << nl;
}

/*
Input: 1\n4 5 1\n1 2 1\n1 3 3\n2 3 1\n3 4 1\n2 4 5
Output: Minimum arborescence cost: 3 (edges: 1→2(1), 2→3(1), 3→4(1))
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

