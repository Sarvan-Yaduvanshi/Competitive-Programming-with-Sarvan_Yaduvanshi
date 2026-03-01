/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Prim's Minimum Spanning Tree
 *  Level   : Advanced
 * ============================================================================
 *
 *  ALGORITHM:
 *  1. Start from any vertex, add to MST set
 *  2. Pick the minimum weight edge from MST set to non-MST vertex
 *  3. Add that vertex to MST set
 *  4. Repeat until all vertices in MST
 *
 *  TIME:  O(E log V) with priority queue (binary heap)
 *         O(E + V log V) with Fibonacci heap (theoretical)
 *  SPACE: O(V + E)
 *
 *  IMPLEMENTATION: Use min-heap of {weight, vertex}. Lazy deletion.
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

using pii = pair<long long, int>; // {weight, vertex}

long long primsMST(int n, vector<vector<pii>>& adj) {
    vector<bool> inMST(n, false);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    long long mstWeight = 0;
    int edgesAdded = 0;
    pq.push({0, 0}); // Start from vertex 0

    while (!pq.empty() && edgesAdded < n) {
        auto [w, u] = pq.top(); pq.pop();

        if (inMST[u]) continue; // Already in MST (lazy deletion)
        inMST[u] = true;
        mstWeight += w;
        edgesAdded++;

        for (auto& [weight, v] : adj[u]) {
            if (!inMST[v]) {
                pq.push({weight, v});
            }
        }
    }

    return (edgesAdded == n) ? mstWeight : -1; // -1 if disconnected
}

int main() {
    int n = 5;
    vector<vector<pii>> adj(n);
    // Add undirected edges
    auto addEdge = [&](int u, int v, long long w) {
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    };

    addEdge(0, 1, 2);
    addEdge(0, 3, 6);
    addEdge(1, 2, 3);
    addEdge(1, 3, 8);
    addEdge(1, 4, 5);
    addEdge(2, 4, 7);
    addEdge(3, 4, 9);

    cout << "MST weight (Prim's): " << primsMST(n, adj) << endl; // 16

    return 0;
}

