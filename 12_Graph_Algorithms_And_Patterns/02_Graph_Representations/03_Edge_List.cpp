/*
╔══════════════════════════════════════════════════════════════════╗
║              03 — EDGE LIST                                     ║
║              Store edges as array of structs                    ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION: Store all edges in a single array/vector.
  Each edge = {u, v, w} (or just {u, v} for unweighted)

WHEN TO USE:
  ✅ Kruskal's MST (need sorted edges)
  ✅ Bellman-Ford (iterate all edges)
  ✅ Problems requiring edge operations (remove, sort, etc.)

COMPLEXITY:
  Space: O(E)
  Sort: O(E log E)
  Iterate all: O(E)

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
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;

#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

struct Edge {
    int u, v, w;
    bool operator<(const Edge& o) const { return w < o.w; }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vec<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].u--; edges[i].v--;
    }

    // Sort by weight (useful for Kruskal)
    sort(all(edges));

    cout << "Edge list sorted by weight:" << nl;
    for (auto& [u, v, w] : edges) {
        cout << "(" << u+1 << " — " << v+1 << ") weight=" << w << nl;
    }

    // Convert edge list to adjacency list
    vvec<pii> adj(n);
    for (auto& [u, v, w] : edges) {
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }

    cout << nl << "Converted to adjacency list:" << nl;
    for (int i = 0; i < n; i++) {
        cout << i+1 << " → ";
        for (auto [v, w] : adj[i]) {
            cout << "(" << v+1 << ",w=" << w << ") ";
        }
        cout << nl;
    }
}

/*
═══════════════════════════════════════════════════════════════════
SAMPLE INPUT/OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
1
4 5
1 2 10
1 3 1
2 3 5
2 4 8
3 4 2

Output:
Edge list sorted by weight:
(1 — 3) weight=1
(3 — 4) weight=2
(2 — 3) weight=5
(2 — 4) weight=8
(1 — 2) weight=10

Converted to adjacency list:
1 → (3,w=1) (2,w=10)
2 → (3,w=5) (4,w=8) (1,w=10)
3 → (1,w=1) (4,w=2) (2,w=5)
4 → (3,w=2) (2,w=8)

═══════════════════════════════════════════════════════════════════
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    return 0;
}

