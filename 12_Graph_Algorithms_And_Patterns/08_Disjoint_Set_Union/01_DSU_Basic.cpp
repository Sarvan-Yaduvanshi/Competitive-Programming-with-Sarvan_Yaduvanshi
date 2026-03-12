/*
╔══════════════════════════════════════════════════════════════════╗
║              01 — DSU BASIC                                     ║
║              Union-Find with Path Compression + Union by Rank   ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

DSU (Disjoint Set Union) / Union-Find maintains a collection of
disjoint sets and supports two operations:

  FIND(x):     Return the representative (root) of set containing x
  UNION(x,y):  Merge the sets containing x and y

TWO OPTIMIZATIONS (both needed!):
  1. PATH COMPRESSION: During find, make every node point directly
     to root → nearly flattens the tree.
  2. UNION BY RANK/SIZE: Always attach smaller tree under larger
     → keeps trees shallow.

With BOTH optimizations:
  Amortized O(α(n)) per operation, where α = inverse Ackermann ≈ O(1)

═══════════════════════════════════════════════════════════════════
VISUALIZATION & DRY RUN
═══════════════════════════════════════════════════════════════════

Operations: union(1,2), union(3,4), union(1,3), find(4)

Initially: each element is its own set
  {1} {2} {3} {4} {5}
  parent: [1, 2, 3, 4, 5]
  rank:   [0, 0, 0, 0, 0]

union(1,2):
  find(1)=1, find(2)=2, different sets
  Attach 2 under 1 (same rank, 1 becomes root)
  parent: [1, 1, 3, 4, 5]   rank: [1, 0, 0, 0, 0]

     1        Tree:  1
    /                |
   2                 2

union(3,4):
  find(3)=3, find(4)=4
  Attach 4 under 3
  parent: [1, 1, 3, 3, 5]   rank: [1, 0, 1, 0, 0]

     1    3
     |    |
     2    4

union(1,3):
  find(1)=1, find(3)=3
  Both rank 1 → attach 3 under 1
  parent: [1, 1, 1, 3, 5]   rank: [2, 0, 1, 0, 0]

       1
      / \
     2   3
         |
         4

find(4):
  4 → parent[4]=3 → parent[3]=1 → parent[1]=1 (root!)
  PATH COMPRESSION: set parent[4]=1, parent[3]=1
  Now: parent: [1, 1, 1, 1, 5]

       1          (flattened!)
     / | \
    2  3  4

═══════════════════════════════════════════════════════════════════
COMPLEXITY
═══════════════════════════════════════════════════════════════════

  ┌─────────────────────────────────────────────────────────┐
  │  Optimization         │  find()      │  union()        │
  ├───────────────────────┼──────────────┼─────────────────┤
  │  None                 │  O(n)        │  O(n)           │
  │  Path compression     │  O(log n)*   │  O(log n)*      │
  │  Union by rank        │  O(log n)    │  O(log n)       │
  │  BOTH (recommended!)  │  O(α(n))≈O(1)│ O(α(n))≈O(1)  │
  └─────────────────────────────────────────────────────────┘
  * amortized

═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
#define sz(x) ((int)(x).size())
#define nl '\n'

// ═══════════════════════════════════════════
// DSU IMPLEMENTATION (Gold Standard for CP)
// ═══════════════════════════════════════════
struct DSU {
    vec<int> parent, rank_;
    int components;

    DSU() {}
    DSU(int n) : parent(n), rank_(n, 0), components(n) {
        iota(parent.begin(), parent.end(), 0); // parent[i] = i
    }

    // FIND with path compression
    int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]]; // path halving (simpler, same complexity)
            x = parent[x];
        }
        return x;
    }

    // UNION by rank
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false; // already same set

        // Attach smaller rank under larger rank
        if (rank_[a] < rank_[b]) swap(a, b);
        parent[b] = a;
        if (rank_[a] == rank_[b]) rank_[a]++;
        components--;
        return true;
    }

    bool connected(int a, int b) {
        return find(a) == find(b);
    }

    int getComponents() { return components; }
};

// Alternative: DSU by SIZE (also common, tracks set sizes)
struct DSU_Size {
    vec<int> parent, size_;

    DSU_Size(int n) : parent(n), size_(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        while (parent[x] != x) { parent[x] = parent[parent[x]]; x = parent[x]; }
        return x;
    }

    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (size_[a] < size_[b]) swap(a, b);
        parent[b] = a;
        size_[a] += size_[b];
        return true;
    }

    int getSize(int x) { return size_[find(x)]; }
};

void solve() {
    int n, q;
    cin >> n >> q;

    DSU dsu(n);

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            // UNION
            int u, v; cin >> u >> v; u--; v--;
            if (dsu.unite(u, v)) {
                cout << "Merged " << u+1 << " and " << v+1 << nl;
            } else {
                cout << u+1 << " and " << v+1 << " already connected" << nl;
            }
        } else {
            // QUERY: same set?
            int u, v; cin >> u >> v; u--; v--;
            cout << (dsu.connected(u, v) ? "YES" : "NO") << nl;
        }
    }
    cout << "Components: " << dsu.getComponents() << nl;
}

/*
Input: 1\n5 6\n1 1 2\n1 3 4\n2 1 4\n1 1 3\n2 1 4\n2 3 5
Output:
Merged 1 and 2
Merged 3 and 4
NO
Merged 1 and 3
YES
NO
Components: 2
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

