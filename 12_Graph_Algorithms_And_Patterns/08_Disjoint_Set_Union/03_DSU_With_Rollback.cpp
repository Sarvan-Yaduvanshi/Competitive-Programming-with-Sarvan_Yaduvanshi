/*
╔══════════════════════════════════════════════════════════════════╗
║              03 — DSU WITH ROLLBACK                             ║
║              Undo union operations (for offline algorithms)     ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

Standard DSU with path compression CANNOT undo operations.
DSU with rollback uses UNION BY RANK (no path compression)
and saves history to a stack, allowing undo.

KEY: Use union by rank ONLY (no path compression).
     find() is O(log n) instead of O(α(n)), but rollback works!

Used in: Parallel binary search, offline dynamic connectivity,
         divide and conquer on queries.

Time: O(log n) per operation    Space: O(n + history)
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

template<class T> using vec = vector<T>;
#define nl '\n'

struct DSU_Rollback {
    vec<int> parent, rank_;
    int components;

    // History stack for rollback
    struct Snapshot {
        int a, b, rankA, rankB;
    };
    vec<Snapshot> history;

    DSU_Rollback(int n) : parent(n), rank_(n, 0), components(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    // find WITHOUT path compression (needed for rollback!)
    int find(int x) {
        while (parent[x] != x) x = parent[x];
        return x;
    }

    // union with history tracking
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) {
            history.push_back({-1, -1, 0, 0}); // no-op marker
            return false;
        }
        if (rank_[a] < rank_[b]) swap(a, b);

        // Save state BEFORE modification
        history.push_back({a, b, rank_[a], rank_[b]});

        parent[b] = a;
        if (rank_[a] == rank_[b]) rank_[a]++;
        components--;
        return true;
    }

    // ROLLBACK: undo the last union operation
    void rollback() {
        if (history.empty()) return;
        auto [a, b, rA, rB] = history.back();
        history.pop_back();

        if (a == -1) return; // was a no-op

        parent[b] = b; // b was attached to a, undo it
        rank_[a] = rA;
        rank_[b] = rB;
        components++;
    }

    // Save current history size for batch rollback
    int saveState() { return (int)history.size(); }

    // Rollback to a saved state
    void rollbackTo(int state) {
        while ((int)history.size() > state) rollback();
    }

    bool connected(int a, int b) { return find(a) == find(b); }
};

void solve() {
    int n, q;
    cin >> n >> q;

    DSU_Rollback dsu(n);

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            // Union
            int u, v; cin >> u >> v; u--; v--;
            dsu.unite(u, v);
            cout << "Union " << u+1 << " " << v+1 << " → Components: " << dsu.components << nl;
        } else if (type == 2) {
            // Query
            int u, v; cin >> u >> v; u--; v--;
            cout << (dsu.connected(u, v) ? "YES" : "NO") << nl;
        } else {
            // Rollback last operation
            dsu.rollback();
            cout << "Rolled back → Components: " << dsu.components << nl;
        }
    }
}

/*
Input: 1\n5 7\n1 1 2\n1 3 4\n2 1 4\n1 1 3\n2 1 4\n3\n2 1 4
Output:
Union 1 2 → Components: 4
Union 3 4 → Components: 3
NO
Union 1 3 → Components: 2
YES
Rolled back → Components: 3
NO
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

