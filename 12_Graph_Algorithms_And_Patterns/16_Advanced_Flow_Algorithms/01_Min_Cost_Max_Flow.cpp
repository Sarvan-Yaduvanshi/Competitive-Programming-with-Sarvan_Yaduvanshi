/*
╔══════════════════════════════════════════════════════════════════╗
║              01 — MINIMUM COST MAXIMUM FLOW (MCMF)              ║
║              Find max flow with minimum total cost              ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

Each edge has (capacity, cost_per_unit_flow).
Find maximum flow from s to t with minimum total cost.

ALGORITHM (Successive Shortest Paths):
  1. While augmenting path exists from s to t in residual graph:
     a. Find SHORTEST cost path using SPFA/Bellman-Ford
        (not Dijkstra — residual graph may have negative edges!)
     b. Push maximum flow along this path
     c. Update residual graph

Reverse edges have negative cost (undoing flow reduces cost).

═══════════════════════════════════════════════════════════════════
COMPLEXITY
  Time:  O(V × E × flow) with SPFA, or O(V × E × min(V, flow))
  Space: O(V + E)
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
#include <climits>
using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
#define sz(x) ((int)(x).size())
#define nl '\n'

struct MCMF {
    struct Edge {
        int to, rev;
        i64 cap, cost;
    };

    int n;
    vec<vec<Edge>> graph;
    vec<i64> dist, potential;
    vec<int> prevv, preve;
    vec<bool> inQueue;

    MCMF(int n) : n(n), graph(n), dist(n), potential(n, 0), prevv(n), preve(n), inQueue(n) {}

    void addEdge(int from, int to, i64 cap, i64 cost) {
        graph[from].push_back({to, sz(graph[to]), cap, cost});
        graph[to].push_back({from, sz(graph[from])-1, 0, -cost});
    }

    // SPFA to find shortest path (handles negative costs)
    bool spfa(int s, int t) {
        fill(dist.begin(), dist.end(), LLONG_MAX);
        fill(inQueue.begin(), inQueue.end(), false);
        dist[s] = 0;
        queue<int> q;
        q.push(s); inQueue[s] = true;

        while (!q.empty()) {
            int u = q.front(); q.pop(); inQueue[u] = false;
            for (int i = 0; i < sz(graph[u]); i++) {
                auto& e = graph[u][i];
                if (e.cap > 0 && dist[u] + e.cost < dist[e.to]) {
                    dist[e.to] = dist[u] + e.cost;
                    prevv[e.to] = u;
                    preve[e.to] = i;
                    if (!inQueue[e.to]) { q.push(e.to); inQueue[e.to] = true; }
                }
            }
        }
        return dist[t] != LLONG_MAX;
    }

    // Returns {max_flow, min_cost}
    pair<i64, i64> minCostFlow(int s, int t, i64 maxFlow = LLONG_MAX) {
        i64 flow = 0, cost = 0;

        while (flow < maxFlow && spfa(s, t)) {
            // Find bottleneck
            i64 aug = maxFlow - flow;
            for (int v = t; v != s; v = prevv[v]) {
                aug = min(aug, graph[prevv[v]][preve[v]].cap);
            }

            // Update residual graph
            for (int v = t; v != s; v = prevv[v]) {
                auto& e = graph[prevv[v]][preve[v]];
                e.cap -= aug;
                graph[v][e.rev].cap += aug;
            }

            flow += aug;
            cost += aug * dist[t];
        }

        return {flow, cost};
    }
};

void solve() {
    int n, m, s, t;
    cin >> n >> m >> s >> t; s--; t--;

    MCMF mcmf(n);
    for (int i = 0; i < m; i++) {
        int u, v; i64 cap, cost;
        cin >> u >> v >> cap >> cost; u--; v--;
        mcmf.addEdge(u, v, cap, cost);
    }

    auto [flow, cost] = mcmf.minCostFlow(s, t);
    cout << "Max Flow: " << flow << nl;
    cout << "Min Cost: " << cost << nl;
}

/*
Input: 1\n4 5 1 4\n1 2 2 1\n1 3 3 2\n2 4 3 3\n3 4 2 1\n2 3 1 1
Output:
Max Flow: 4
Min Cost: (depends on optimal routing)
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

