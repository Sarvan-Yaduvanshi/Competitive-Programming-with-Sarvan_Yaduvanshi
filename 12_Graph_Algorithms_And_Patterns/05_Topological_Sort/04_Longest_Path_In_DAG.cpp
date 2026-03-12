/*
╔══════════════════════════════════════════════════════════════════╗
║              04 — LONGEST PATH IN DAG                           ║
║              DP on topological order                            ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

Finding the longest path in a general graph is NP-hard.
But in a DAG, we can solve it in O(V+E) using topological sort + DP!

dp[v] = length of longest path ending at v

For each vertex v in topological order:
  dp[v] = max(dp[u] + w(u,v)) for all edges u → v

═══════════════════════════════════════════════════════════════════
DRY RUN
═══════════════════════════════════════════════════════════════════

DAG with weights:
  1 →(3)→ 2 →(2)→ 4
  1 →(1)→ 3 →(5)→ 4
             3 →(2)→ 5

Topo order: 1, 2, 3, 4, 5 (or 1, 3, 2, 5, 4)

dp[1] = 0  (start)
dp[2] = dp[1]+3 = 3
dp[3] = dp[1]+1 = 1
dp[4] = max(dp[2]+2, dp[3]+5) = max(5, 6) = 6
dp[5] = dp[3]+2 = 3

Longest path: 1→3→4 with length 6

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
using pii = pair<int,int>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

void solve() {
    int n, m;
    cin >> n >> m;

    vec<vec<pii>> adj(n);  // adj[u] = {(v, weight)}
    vec<int> inDeg(n, 0);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].pb({v, w});
        inDeg[v]++;
    }

    // Kahn's for topological order
    queue<int> q;
    for (int i = 0; i < n; i++) if (inDeg[i]==0) q.push(i);

    vec<int> topo;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.pb(u);
        for (auto [v, w] : adj[u]) {
            if (--inDeg[v]==0) q.push(v);
        }
    }

    // DP for longest path
    vec<i64> dp(n, 0);  // longest path ending at each vertex
    vec<int> par(n, -1);

    for (int u : topo) {
        for (auto [v, w] : adj[u]) {
            if (dp[u] + w > dp[v]) {
                dp[v] = dp[u] + w;
                par[v] = u;
            }
        }
    }

    // Find vertex with max dp value
    int endV = max_element(dp.begin(), dp.end()) - dp.begin();

    cout << "Longest path length: " << dp[endV] << nl;

    // Reconstruct path
    vec<int> path;
    for (int v = endV; v != -1; v = par[v]) path.pb(v);
    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (int i = 0; i < sz(path); i++) {
        if (i) cout << " → ";
        cout << path[i]+1;
    }
    cout << nl;
}

/*
Input: 1\n5 5\n1 2 3\n1 3 1\n2 4 2\n3 4 5\n3 5 2
Output:
Longest path length: 6
Path: 1 → 3 → 4
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

