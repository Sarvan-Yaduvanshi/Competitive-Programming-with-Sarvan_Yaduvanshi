/*
╔══════════════════════════════════════════════════════════════════╗
║         03 — SHORTEST PATH WITH STATE (Layered BFS/Dijkstra)   ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
CONCEPT
═══════════════════════════════════════════════════════════════════

Sometimes the "state" is more than just the current vertex.
Example: "shortest path with at most k stops" or "collecting keys".

TECHNIQUE: Expand the graph — each node becomes (vertex, state).
  State examples: (vertex, keys_bitmask), (vertex, stops_used)

Run BFS/Dijkstra on the expanded state space.

EXAMPLE: Shortest path with ≤ K edge removals
  State: (vertex, removals_used)
  Transition: normal edge → (v, removals), blocked edge → (v, removals+1)

Time: O(States × Transitions) = O((V × S) × E)
Space: O(V × S)
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
#endif
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int,int>;
constexpr i64 INF64 = 4e18;
#define nl '\n'

// Example: Shortest path where you can use at most K "teleports" (free edges)
void solve() {
    int n, m, K;
    cin >> n >> m >> K;

    vec<vec<pair<int,i64>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v; i64 w;
        cin >> u >> v >> w; u--; v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // State: (vertex, teleports_used)
    // dist[v][k] = shortest distance to v using k teleports
    vvec<i64> dist(n, vec<i64>(K+1, INF64));

    // Dijkstra on state graph
    // PQ: (distance, vertex, teleports_used)
    using State = tuple<i64, int, int>;
    priority_queue<State, vec<State>, greater<State>> pq;

    dist[0][0] = 0;
    pq.push({0, 0, 0});

    while (!pq.empty()) {
        auto [d, u, k] = pq.top(); pq.pop();
        if (d > dist[u][k]) continue;

        for (auto [v, w] : adj[u]) {
            // Normal edge
            if (dist[u][k] + w < dist[v][k]) {
                dist[v][k] = dist[u][k] + w;
                pq.push({dist[v][k], v, k});
            }
            // Teleport (free, uses one teleport)
            if (k < K && dist[u][k] < dist[v][k+1]) {
                dist[v][k+1] = dist[u][k];
                pq.push({dist[v][k+1], v, k+1});
            }
        }
    }

    // Answer: min over all k of dist[n-1][k]
    i64 ans = INF64;
    for (int k = 0; k <= K; k++) ans = min(ans, dist[n-1][k]);

    cout << (ans == INF64 ? -1 : ans) << nl;
}

/*
Input: 1\n4 4 1\n1 2 5\n2 3 3\n3 4 2\n1 4 100
With 1 teleport: 1→2(5)→3(free teleport)→4(2) = 7
Without teleport: 1→2→3→4 = 10 or 1→4 = 100
Answer: 7
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

