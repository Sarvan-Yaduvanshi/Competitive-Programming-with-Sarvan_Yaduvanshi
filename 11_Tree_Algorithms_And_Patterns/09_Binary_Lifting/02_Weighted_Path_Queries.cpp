/*
╔══════════════════════════════════════════════════════════════════╗
║  02 — WEIGHTED PATH QUERIES (Min/Max/Sum on Path)              ║
║  Zero to GM Level — Binary Lifting                               ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 CONCEPT
═══════════════════════════════════════════════════════════════════

 Extend binary lifting table to store path aggregates:
   upMax[v][k] = maximum edge weight on path from v to its 2^k-th ancestor
   upMin[v][k] = minimum edge weight ...
   upSum[v][k] = sum of edge weights ...

 Recurrence:
   upMax[v][k] = max(upMax[v][k-1], upMax[up[v][k-1]][k-1])

 Query max on path(u, v):
   Lift u and v to LCA while tracking max.

═══════════════════════════════════════════════════════════════════
 DRY RUN — Max Weight on Path
═══════════════════════════════════════════════════════════════════

 Tree:
        1
       / \(5)
      2    3
     /(3)\(7) \(2)
    4     5     6

 Edges: (1,2,w=5), (1,3,w=2), (2,4,w=3), (2,5,w=7), (3,6,w=2)

 Query: max weight on path(4, 6)?
   LCA(4,6) = 1
   Path: 4 →(3)→ 2 →(5)→ 1 →(2)→ 3 →(2)→ 6
   Max weight = max(3, 5, 2, 2) = 7? No wait...

   Path 4→2: weight 3
   Path 2→1: weight 5
   Path 1→3: weight 2
   Path 3→6: weight 2
   Max = 5 ✅

 Using binary lifting:
   Lift 4 to depth of 6 (both depth 2, same)
   up[4][0]=2, upMax[4][0]=3
   up[6][0]=3, upMax[6][0]=2
   4≠6, up[4][0]=2≠up[6][0]=3 → lift
   u=2, v=3, trackMax = max(3, 2) = 3
   LCA = up[2][0] = 1
   Answer = max(3, upMax[2][0]=5, upMax[3][0]=2) = 5 ✅

═══════════════════════════════════════════════════════════════════
 CODE
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
#include <cstring>
#include <climits>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
using pii = pair<int, int>;
#define pb push_back
#define nl '\n'

const int LOG = 20;
const int MAXN = 200005;

vector<vector<pii>> adj; // {neighbor, weight}
int up[MAXN][LOG];
int upMax[MAXN][LOG]; // max edge weight on path of 2^k jumps
int dep[MAXN];

void dfs(int v, int p, int d, int w) {
    dep[v] = d;
    up[v][0] = p;
    upMax[v][0] = w; // weight of edge to parent
    for (int k = 1; k < LOG; k++) {
        up[v][k] = up[up[v][k-1]][k-1];
        upMax[v][k] = max(upMax[v][k-1], upMax[up[v][k-1]][k-1]);
    }
    for (auto [u, ew] : adj[v]) {
        if (u != p) dfs(u, v, d + 1, ew);
    }
}

// Query: max edge weight on path from u to v
int queryMaxOnPath(int u, int v) {
    int ans = 0;
    if (dep[u] < dep[v]) swap(u, v);

    int diff = dep[u] - dep[v];
    for (int k = LOG - 1; k >= 0; k--) {
        if ((diff >> k) & 1) {
            ans = max(ans, upMax[u][k]);
            u = up[u][k];
        }
    }
    if (u == v) return ans;

    for (int k = LOG - 1; k >= 0; k--) {
        if (up[u][k] != up[v][k]) {
            ans = max(ans, max(upMax[u][k], upMax[v][k]));
            u = up[u][k];
            v = up[v][k];
        }
    }
    ans = max(ans, max(upMax[u][0], upMax[v][0]));
    return ans;
}

void solve() {
    int n; cin >> n;
    adj.assign(n + 1, {});
    memset(up, 0, sizeof(up));
    memset(upMax, 0, sizeof(upMax));

    for (int i = 0; i < n - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].pb({v, w}); adj[v].pb({u, w});
    }
    dfs(1, 0, 0, 0);

    int q; cin >> q;
    while (q--) {
        int u, v; cin >> u >> v;
        cout << "Max weight on path(" << u << "," << v << ") = "
             << queryMaxOnPath(u, v) << nl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1; cin >> TC;
    while (TC--) solve();
    return 0;
}

/*
 Input: 1\n6\n1 2 5\n1 3 2\n2 4 3\n2 5 7\n3 6 2\n2\n4 6\n4 5
 Output:
 Max weight on path(4,6) = 5
 Max weight on path(4,5) = 7

 Time: O(N log N) build, O(log N) per query
*/

