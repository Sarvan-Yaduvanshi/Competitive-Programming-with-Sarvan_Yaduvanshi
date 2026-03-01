/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Kruskal's Minimum Spanning Tree
 *  Level   : Advanced
 * ============================================================================
 *
 *  ALGORITHM:
 *  1. Sort all edges by weight (ascending)
 *  2. For each edge, if it connects two different components → add to MST
 *  3. Use DSU (Union-Find) to track components
 *
 *  TIME:  O(E log E) for sorting + O(E α(V)) for DSU ≈ O(E log E)
 *  SPACE: O(V) for DSU
 *
 *  WHY GREEDY WORKS (Cut Property):
 *  For any cut of the graph, the minimum weight edge crossing the cut
 *  must be in the MST. Kruskal always picks the global minimum weight
 *  edge that crosses some cut → guaranteed to be in MST.
 *
 *  WHEN TO USE KRUSKAL vs PRIM:
 *  - Kruskal: Better for sparse graphs (E ≈ V), edge list representation
 *  - Prim: Better for dense graphs (E ≈ V²), adjacency list/matrix
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class DSU {
    vector<int> parent, rank_;
public:
    DSU(int n) : parent(n), rank_(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (rank_[x] < rank_[y]) swap(x, y);
        parent[y] = x;
        if (rank_[x] == rank_[y]) rank_[x]++;
        return true;
    }
};

struct Edge {
    int u, v;
    long long w;
    bool operator<(const Edge& other) const { return w < other.w; }
};

// Returns {MST weight, MST edges}
pair<long long, vector<Edge>> kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    DSU dsu(n);

    long long mstWeight = 0;
    vector<Edge> mstEdges;

    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mstWeight += e.w;
            mstEdges.push_back(e);
            if ((int)mstEdges.size() == n - 1) break;
        }
    }

    return {mstWeight, mstEdges};
}

int main() {
    // CSES 1675: Road Reparation style
    int n = 5;
    vector<Edge> edges = {
        {0,1,2}, {0,3,6}, {1,2,3}, {1,3,8}, {1,4,5}, {2,4,7}, {3,4,9}
    };

    auto [weight, mst] = kruskal(n, edges);
    cout << "MST weight: " << weight << endl; // 16
    cout << "MST edges:" << endl;
    for (auto& e : mst)
        cout << "  " << e.u << " -- " << e.v << " (w=" << e.w << ")" << endl;

    return 0;
}

