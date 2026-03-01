/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Reverse Delete Algorithm for MST
 *  Level   : Advanced
 * ============================================================================
 *
 *  ALGORITHM (Opposite of Kruskal):
 *  1. Sort all edges by weight DESCENDING
 *  2. For each edge, if removing it keeps the graph connected → remove it
 *  3. Remaining edges form the MST
 *
 *  TIME:  O(E log E * (V+E)) — less efficient than Kruskal
 *  SPACE: O(V + E)
 *
 *  WHY IT WORKS:
 *  If an edge is the heaviest in some cycle, it's NOT in the MST.
 *  By removing the heaviest edges that don't disconnect the graph,
 *  we're removing exactly the non-MST edges.
 *
 *  PRIMARILY THEORETICAL — Kruskal/Prim are preferred in practice.
 *  But useful to understand the duality of greedy approaches.
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct Edge { int u, v; long long w; };

// BFS/DFS to check connectivity after removing some edges
bool isConnected(int n, vector<Edge>& edges, vector<bool>& removed) {
    vector<vector<int>> adj(n);
    for (int i = 0; i < (int)edges.size(); i++) {
        if (!removed[i]) {
            adj[edges[i].u].push_back(edges[i].v);
            adj[edges[i].v].push_back(edges[i].u);
        }
    }

    vector<bool> visited(n, false);
    vector<int> stack = {0};
    visited[0] = true;
    int count = 1;

    while (!stack.empty()) {
        int u = stack.back(); stack.pop_back();
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                stack.push_back(v);
                count++;
            }
        }
    }
    return count == n;
}

long long reverseDeleteMST(int n, vector<Edge>& edges) {
    // Sort by weight descending
    vector<int> order(edges.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        return edges[a].w > edges[b].w;
    });

    vector<bool> removed(edges.size(), false);
    long long mstWeight = 0;

    for (int idx : order) {
        removed[idx] = true;
        if (!isConnected(n, edges, removed)) {
            removed[idx] = false; // Can't remove — it's a bridge → in MST
        }
    }

    for (int i = 0; i < (int)edges.size(); i++)
        if (!removed[i]) mstWeight += edges[i].w;

    return mstWeight;
}

int main() {
    int n = 5;
    vector<Edge> edges = {
        {0,1,2}, {0,3,6}, {1,2,3}, {1,3,8}, {1,4,5}, {2,4,7}, {3,4,9}
    };
    cout << "MST weight (Reverse Delete): " << reverseDeleteMST(n, edges) << endl; // 16
    return 0;
}

