/*
╔══════════════════════════════════════════════════════════════════╗
║              04 — WEIGHTED DSU                                  ║
║              Track relative distances/potentials between nodes  ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

Weighted DSU stores a "potential" or "distance from root" for each
element. When merging, we maintain: pot[x] - pot[y] = given relation.

Used for:
  - "A is D units heavier than B" type constraints
  - Relative ordering problems
  - Finding contradictions in constraints

pot[x] = distance from x to its root representative
To get relation between x and y (same component):
  relation(x, y) = pot[x] - pot[y]

Time: O(α(n)) per operation    Space: O(n)
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

using i64 = long long;
template<class T> using vec = vector<T>;
#define nl '\n'

struct WeightedDSU {
    vec<int> parent, rank_;
    vec<i64> pot;  // potential (distance to root)

    WeightedDSU(int n) : parent(n), rank_(n, 0), pot(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    // find with path compression, updating potentials
    int find(int x) {
        if (parent[x] == x) return x;
        int root = find(parent[x]);
        pot[x] += pot[parent[x]];  // accumulate potential
        parent[x] = root;
        return root;
    }

    // unite: establish relation pot[x] - pot[y] = w
    // i.e., "x is w units more than y"
    bool unite(int x, int y, i64 w) {
        int rx = find(x), ry = find(y);
        if (rx == ry) {
            // Check consistency: pot[x] - pot[y] should equal w
            return (pot[x] - pot[y] == w);
        }
        // w = pot[x] - pot[y]
        // pot[ry] should be pot[rx] + (pot[x] - w - pot[y]) after merge...
        // More carefully:
        // After find: pot[x] = dist from x to rx, pot[y] = dist from y to ry
        // We want dist(x→root) - dist(y→root) = w in new tree
        // Attach ry under rx: pot[ry] = pot[x] - w - pot[y]
        if (rank_[rx] < rank_[ry]) {
            swap(rx, ry);
            swap(x, y);
            w = -w;
        }
        parent[ry] = rx;
        pot[ry] = pot[x] - w - pot[y];
        if (rank_[rx] == rank_[ry]) rank_[rx]++;
        return true;
    }

    // Get relation: returns pot[x] - pot[y] if same component
    // Returns {true, diff} or {false, 0}
    pair<bool, i64> query(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx != ry) return {false, 0};
        return {true, pot[x] - pot[y]};
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    WeightedDSU dsu(n);

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            // Relation: x - y = w
            int x, y; i64 w;
            cin >> x >> y >> w; x--; y--;
            if (dsu.unite(x, y, w)) {
                cout << "Consistent" << nl;
            } else {
                cout << "CONTRADICTION!" << nl;
            }
        } else {
            // Query: what is x - y?
            int x, y; cin >> x >> y; x--; y--;
            auto [ok, diff] = dsu.query(x, y);
            if (ok) cout << x+1 << " - " << y+1 << " = " << diff << nl;
            else cout << "Unknown (different components)" << nl;
        }
    }
}

/*
Example: People on a line. "A is 3 units right of B" → A - B = 3.
Input: 1\n4 5\n1 1 2 3\n1 2 3 2\n2 1 3\n1 1 3 4\n1 1 3 5
Output:
Consistent
Consistent
1 - 3 = 5
CONTRADICTION!
Consistent... (depends on actual values)
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

