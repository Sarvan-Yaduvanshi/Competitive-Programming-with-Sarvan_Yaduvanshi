/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Graphic Matroid — MST as Greedy on Matroid
 *  Level   : Expert
 * ============================================================================
 *
 *  ▶ GRAPHIC MATROID:
 *  ──────────────────
 *  Given a graph G = (V, E):
 *  - Ground set S = E (edges)
 *  - Independent sets I = all acyclic subsets of E (forests)
 *
 *  VERIFICATION OF MATROID AXIOMS:
 *  1. ∅ is a forest ✓
 *  2. Subset of a forest is a forest ✓ (removing edges from a forest keeps it acyclic)
 *  3. Exchange: If F1, F2 are forests with |F1| < |F2|, then F2 has a component
 *     that's not fully in F1 → we can add an edge from F2 to F1 without creating cycle ✓
 *
 *  CONSEQUENCE:
 *  Greedy on graphic matroid = Kruskal's algorithm = finds MST!
 *  This is the deepest reason WHY Kruskal works.
 *
 *  ▶ GENERIC MATROID GREEDY ALGORITHM:
 *  ───────────────────────────────────
 *  1. Sort elements by weight (descending for max, ascending for min)
 *  2. For each element in sorted order:
 *     If adding it to current solution keeps it independent → add it
 *  3. Result is optimal!
 *
 *  For graphic matroid:
 *  "Independent" = "acyclic" → checked with DSU (Union-Find)
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
    DSU(int n) : parent(n), rank_(n, 0) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false; // Would create cycle → not independent
        if (rank_[x] < rank_[y]) swap(x, y);
        parent[y] = x;
        if (rank_[x] == rank_[y]) rank_[x]++;
        return true; // Independent → safe to add
    }
};

// Generic Matroid Greedy (specialized for Graphic Matroid)
long long graphicMatroidGreedy(int n, vector<tuple<int,int,long long>>& edges) {
    // Sort by weight ascending (for minimum spanning tree)
    sort(edges.begin(), edges.end(), [](auto& a, auto& b) {
        return get<2>(a) < get<2>(b);
    });

    DSU dsu(n);
    long long mstWeight = 0;
    int edgesUsed = 0;

    for (auto& [u, v, w] : edges) {
        // Independence check: does adding this edge keep the forest acyclic?
        if (dsu.unite(u, v)) {
            mstWeight += w;
            edgesUsed++;
            if (edgesUsed == n - 1) break;
        }
    }

    return mstWeight;
}

int main() {
    int n = 4;
    vector<tuple<int,int,long long>> edges = {
        {0,1,10}, {0,2,6}, {0,3,5}, {1,3,15}, {2,3,4}
    };

    cout << "MST weight (Matroid Greedy): " << graphicMatroidGreedy(n, edges) << endl; // 19

    return 0;
}

