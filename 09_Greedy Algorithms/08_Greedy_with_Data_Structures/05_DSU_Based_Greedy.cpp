/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : DSU-Based Greedy
 *  Level   : Advanced
 * ============================================================================
 *
 *  PATTERN: Use Union-Find to greedily group/assign elements.
 *
 *  APPLICATIONS:
 *  1. Kruskal's MST (Module 07)
 *  2. Job Sequencing with DSU (Module 02)
 *  3. Accounts Merge (LC 721)
 *  4. Redundant Connection (LC 684)
 *  5. Greedy edge addition in CF problems
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
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

    bool connected(int x, int y) { return find(x) == find(y); }
};

// ============================================================================
// LC 684: Redundant Connection — Find the edge that creates a cycle
// Greedy: Process edges in order, first edge creating a cycle is answer
// ============================================================================
vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int n = edges.size();
    DSU dsu(n + 1);

    for (auto& e : edges) {
        if (!dsu.unite(e[0], e[1])) return e; // Creates cycle
    }
    return {};
}

// ============================================================================
// Building Roads (CSES 1666) — Connect all cities with minimum roads
// ============================================================================
vector<pair<int,int>> buildRoads(int n, vector<pair<int,int>>& roads) {
    DSU dsu(n + 1);
    for (auto& [u, v] : roads) dsu.unite(u, v);

    vector<pair<int,int>> newRoads;
    for (int i = 2; i <= n; i++) {
        if (!dsu.connected(1, i)) {
            dsu.unite(1, i);
            newRoads.push_back({1, i});
        }
    }
    return newRoads;
}

int main() {
    // Redundant Connection
    vector<vector<int>> edges = {{1,2}, {1,3}, {2,3}};
    auto red = findRedundantConnection(edges);
    cout << "Redundant: " << red[0] << " " << red[1] << endl; // 2 3

    return 0;
}

