/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Borůvka's MST Algorithm
 *  Level   : Advanced
 * ============================================================================
 *
 *  ALGORITHM:
 *  1. Each vertex starts as its own component
 *  2. For each component, find the cheapest edge leaving it
 *  3. Add all such cheapest edges to MST
 *  4. Repeat until one component remains
 *
 *  TIME:  O(E log V) — at most O(log V) phases, each O(E)
 *  SPACE: O(V + E)
 *
 *  ADVANTAGE: Easily parallelizable. Used in practice for massive graphs.
 *  USED IN: Codeforces problems requiring component-based MST
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <climits>
using namespace std;

class DSU {
public:
    vector<int> parent, rank_;
    int components;
    DSU(int n) : parent(n), rank_(n, 0), components(n) {
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
        components--;
        return true;
    }
};

struct Edge { int u, v; long long w; };

long long boruvkaMST(int n, vector<Edge>& edges) {
    DSU dsu(n);
    long long mstWeight = 0;

    while (dsu.components > 1) {
        // cheapest[comp] = index of cheapest edge leaving component comp
        vector<int> cheapest(n, -1);

        for (int i = 0; i < (int)edges.size(); i++) {
            int cu = dsu.find(edges[i].u);
            int cv = dsu.find(edges[i].v);
            if (cu == cv) continue;

            if (cheapest[cu] == -1 || edges[i].w < edges[cheapest[cu]].w)
                cheapest[cu] = i;
            if (cheapest[cv] == -1 || edges[i].w < edges[cheapest[cv]].w)
                cheapest[cv] = i;
        }

        bool merged = false;
        for (int i = 0; i < n; i++) {
            if (cheapest[i] != -1) {
                auto& e = edges[cheapest[i]];
                if (dsu.unite(e.u, e.v)) {
                    mstWeight += e.w;
                    merged = true;
                }
            }
        }
        if (!merged) break; // Graph is disconnected
    }

    return mstWeight;
}

int main() {
    int n = 5;
    vector<Edge> edges = {
        {0,1,2}, {0,3,6}, {1,2,3}, {1,3,8}, {1,4,5}, {2,4,7}, {3,4,9}
    };
    cout << "MST weight (Borůvka): " << boruvkaMST(n, edges) << endl; // 16
    return 0;
}

