/*
╔══════════════════════════════════════════════════════════════════╗
║              02 — DINIC'S ALGORITHM                             ║
║              The Gold Standard for Max Flow in CP               ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

Dinic's algorithm improves on Edmonds-Karp:
  1. BFS to build LEVEL GRAPH (only forward edges by BFS layers)
  2. Find BLOCKING FLOW in level graph using DFS
  3. Repeat until BFS can't reach t

BLOCKING FLOW: a flow such that every s→t path in level graph
has at least one saturated edge.

═══════════════════════════════════════════════════════════════════
COMPLEXITY
═══════════════════════════════════════════════════════════════════

  General:     O(V² × E)
  Unit cap:    O(E × √V)   ← great for bipartite matching!
  Bipartite:   O(E × √V)

This is THE flow algorithm for competitive programming.

═══════════════════════════════════════════════════════════════════
KEY OPTIMIZATION: "current arc" optimization
  Track next edge to try from each vertex to avoid re-scanning.
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

// ═══════════════════════════════════════════
// DINIC'S MAX FLOW (Copy-paste ready for CP)
// ═══════════════════════════════════════════
struct Dinic {
    struct Edge {
        int to, rev;
        i64 cap;
    };

    int n;
    vec<vec<Edge>> graph;
    vec<int> level, iter;

    Dinic(int n) : n(n), graph(n), level(n), iter(n) {}

    void addEdge(int from, int to, i64 cap) {
        graph[from].push_back({to, sz(graph[to]), cap});
        graph[to].push_back({from, sz(graph[from])-1, 0});
    }

    // BFS to build level graph
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);

        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto& e : graph[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }

    // DFS to find blocking flow (with current arc optimization)
    i64 dfs(int v, int t, i64 f) {
        if (v == t) return f;
        for (int& i = iter[v]; i < sz(graph[v]); i++) {
            Edge& e = graph[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                i64 d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    graph[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    i64 maxflow(int s, int t) {
        i64 flow = 0;
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            i64 d;
            while ((d = dfs(s, t, LLONG_MAX)) > 0) {
                flow += d;
            }
        }
        return flow;
    }
};

void solve() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--; t--;

    Dinic dinic(n);
    for (int i = 0; i < m; i++) {
        int u, v; i64 c;
        cin >> u >> v >> c; u--; v--;
        dinic.addEdge(u, v, c);
    }

    cout << "Max Flow (Dinic): " << dinic.maxflow(s, t) << nl;
}

/*
Input: 1\n4 5 1 4\n1 2 10\n1 3 8\n2 4 5\n2 3 3\n3 4 7
Output: Max Flow (Dinic): 12
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

