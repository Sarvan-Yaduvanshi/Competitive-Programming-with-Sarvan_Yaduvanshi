/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Greedy with Rollback — DSU Rollback
 *  Level   : Grandmaster
 * ============================================================================
 *
 *  ▶ DSU WITH ROLLBACK:
 *  ────────────────────
 *  Standard DSU with path compression is NOT rollback-friendly (path compression
 *  is destructive). Instead, use union-by-rank WITHOUT path compression,
 *  and maintain a stack of operations to undo.
 *
 *  USE CASES:
 *  - Offline queries with additions AND deletions of edges
 *  - Divide and conquer on queries
 *  - Problems where you need to "undo" some unions
 *
 *  TIME: O(log N) per find (no path compression), O(1) per undo
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class DSURollback {
    vector<int> parent, rank_;
    struct Change { int u, v, oldRankU; };
    vector<Change> history;

public:
    int components;

    DSURollback(int n) : parent(n), rank_(n, 0), components(n) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    // NO path compression — so we can rollback
    int find(int x) {
        while (parent[x] != x) x = parent[x];
        return x;
    }

    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) {
            history.push_back({-1, -1, -1}); // No-op (still save a slot)
            return false;
        }
        if (rank_[x] < rank_[y]) swap(x, y);
        // Save state for rollback
        history.push_back({y, x, rank_[x]});
        parent[y] = x;
        if (rank_[x] == rank_[y]) rank_[x]++;
        components--;
        return true;
    }

    // Undo the last unite operation
    void rollback() {
        if (history.empty()) return;
        auto [u, v, oldRank] = history.back();
        history.pop_back();

        if (u == -1) return; // Was a no-op

        parent[u] = u;
        rank_[v] = oldRank;
        components++;
    }

    // Save current state (number of operations in history)
    int savepoint() { return history.size(); }

    // Rollback to a savepoint
    void rollbackTo(int savepoint) {
        while ((int)history.size() > savepoint) rollback();
    }
};

int main() {
    DSURollback dsu(5);

    // Unite some edges
    dsu.unite(0, 1);
    dsu.unite(1, 2);
    cout << "Components after {0-1, 1-2}: " << dsu.components << endl; // 3

    int sp = dsu.savepoint(); // Save state

    dsu.unite(2, 3);
    dsu.unite(3, 4);
    cout << "Components after {2-3, 3-4}: " << dsu.components << endl; // 1

    // Rollback to savepoint
    dsu.rollbackTo(sp);
    cout << "After rollback: " << dsu.components << endl; // 3

    return 0;
}

