/*
╔══════════════════════════════════════════════════════════════════╗
║              01 — DP ON DAG                                     ║
║              Shortest/Longest path + Path counting              ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
CONCEPT
═══════════════════════════════════════════════════════════════════

Any DP on a DAG follows the same pattern:
  1. Topologically sort the vertices
  2. Process vertices in topological order
  3. For each vertex, update using already-computed predecessors

APPLICATIONS:
  - Shortest path in DAG (even with negative weights!) — O(V+E)
  - Longest path in DAG — O(V+E)  (NP-hard in general graphs!)
  - Count number of paths from s to t — O(V+E)
  - DP with constraints on DAG (e.g., min cost path with ≤ k edges)

═══════════════════════════════════════════════════════════════════
DRY RUN — PATH COUNTING
═══════════════════════════════════════════════════════════════════

DAG: 1→2, 1→3, 2→4, 3→4, 2→3

Topo order: 1, 2, 3, 4

cnt[1] = 1 (start)
Process 1: cnt[2] += cnt[1] → cnt[2] = 1
           cnt[3] += cnt[1] → cnt[3] = 1
Process 2: cnt[4] += cnt[2] → cnt[4] = 1
           cnt[3] += cnt[2] → cnt[3] = 2
Process 3: cnt[4] += cnt[3] → cnt[4] = 3
Process 4: done

Paths from 1 to 4: 3
  1→2→4, 1→3→4, 1→2→3→4

═══════════════════════════════════════════════════════════════════
Time: O(V+E)    Space: O(V+E)
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, i64>;
constexpr i64 INF64 = 4e18;
constexpr i64 MOD = 1'000'000'007LL;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

void solve() {
    int n, m, src, dst;
    cin >> n >> m >> src >> dst;
    src--; dst--;

    vec<vec<pii>> adj(n);  // (neighbor, weight)
    vec<int> inDeg(n, 0);

    for (int i = 0; i < m; i++) {
        int u, v; i64 w;
        cin >> u >> v >> w; u--; v--;
        adj[u].pb({v, w});
        inDeg[v]++;
    }

    // Topological sort (Kahn's)
    queue<int> q;
    for (int i = 0; i < n; i++) if (!inDeg[i]) q.push(i);
    vec<int> topo;
    while (!q.empty()) {
        int u = q.front(); q.pop(); topo.pb(u);
        for (auto [v, w] : adj[u]) if (--inDeg[v] == 0) q.push(v);
    }

    // 1. SHORTEST PATH
    vec<i64> dist(n, INF64);
    dist[src] = 0;
    for (int u : topo) {
        if (dist[u] == INF64) continue;
        for (auto [v, w] : adj[u]) {
            dist[v] = min(dist[v], dist[u] + w);
        }
    }

    // 2. LONGEST PATH
    vec<i64> longest(n, -INF64);
    longest[src] = 0;
    for (int u : topo) {
        if (longest[u] == -INF64) continue;
        for (auto [v, w] : adj[u]) {
            longest[v] = max(longest[v], longest[u] + w);
        }
    }

    // 3. PATH COUNTING (mod MOD)
    vec<i64> cnt(n, 0);
    cnt[src] = 1;
    for (int u : topo) {
        if (cnt[u] == 0) continue;
        for (auto [v, w] : adj[u]) {
            cnt[v] = (cnt[v] + cnt[u]) % MOD;
        }
    }

    cout << "Shortest path " << src+1 << " → " << dst+1 << ": ";
    cout << (dist[dst] == INF64 ? -1 : dist[dst]) << nl;

    cout << "Longest path " << src+1 << " → " << dst+1 << ": ";
    cout << (longest[dst] == -INF64 ? -1 : longest[dst]) << nl;

    cout << "Number of paths: " << cnt[dst] << nl;
}

/*
Input: 1\n4 5 1 4\n1 2 1\n1 3 4\n2 4 6\n3 4 1\n2 3 2
Output:
Shortest path 1 → 4: 4 (1→2→3→4: 1+2+1=4)
Longest path 1 → 4: 7 (1→2→4: 1+6=7)
Number of paths: 3
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

