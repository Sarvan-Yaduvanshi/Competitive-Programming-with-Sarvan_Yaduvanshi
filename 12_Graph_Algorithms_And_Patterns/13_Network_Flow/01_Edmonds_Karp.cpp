/*
╔══════════════════════════════════════════════════════════════════╗
║              01 — MAX FLOW: FORD-FULKERSON CONCEPT              ║
║              + Edmonds-Karp (BFS) Implementation                ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

FLOW NETWORK: Directed graph with:
  - Source s, Sink t
  - Each edge (u,v) has capacity c(u,v)
  - Flow f(u,v) ≤ c(u,v) for each edge
  - Flow conservation: ∑flow_in = ∑flow_out (except s,t)

MAX FLOW: Maximum total flow from s to t.

FORD-FULKERSON METHOD:
  1. While there exists an augmenting path from s to t in residual graph:
     a. Find bottleneck (min residual capacity on path)
     b. Push that much flow along the path
     c. Update residual capacities

RESIDUAL GRAPH:
  - Forward edge: remaining capacity = cap - flow
  - Backward edge: can "undo" flow = flow sent

═══════════════════════════════════════════════════════════════════
DRY RUN
═══════════════════════════════════════════════════════════════════

Network:
    s ──(10)──→ A ──(5)──→ t
    │                       ↑
    └──(8)──→ B ──(7)──→──┘
              A ──(3)──→ B

Path 1: s→A→t, bottleneck=5, push 5
  Residual: s→A(5), A→t(0), A→s(5 back)

Path 2: s→B→t, bottleneck=7, push 7
  Residual: s→B(1), B→t(0)

Path 3: s→A→B→t — wait, A→t is full. But s→A has cap 5 left.
  s→A(5)→B(3)→t... B→t is full too.

Actually with back edges:
Path 3: s→B→... B→t full.
  s has 5 remaining to A, 1 remaining to B.
  s→A→B→... but B→t is full.

Max flow = 5 + 7 = 12? Let's check:
  s→A: cap 10, s→B: cap 8
  A→t: cap 5, A→B: cap 3, B→t: cap 7

  Optimal: s→A→t: 5, s→A→B→t: 3, s→B→t: 4
  Wait: s→A = 5+3=8, A→t=5, A→B=3, s→B=4, B→t=3+4=7
  Total flow = 5 + 3 + 4 = 12? Out of s = 8+4 = 12.
  Into t = 5+7 = 12. ✅ Max flow = 12.

═══════════════════════════════════════════════════════════════════
EDMONDS-KARP: Use BFS to find augmenting paths.
Guarantees O(VE²) time.
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

struct MaxFlow {
    struct Edge {
        int to, rev;
        i64 cap;
    };

    int n;
    vec<vec<Edge>> graph;

    MaxFlow(int n) : n(n), graph(n) {}

    void addEdge(int from, int to, i64 cap) {
        graph[from].push_back({to, sz(graph[to]), cap});
        graph[to].push_back({from, sz(graph[from])-1, 0}); // reverse edge
    }

    // Edmonds-Karp (BFS augmenting paths)
    i64 maxflow(int s, int t) {
        i64 flow = 0;

        while (true) {
            // BFS to find augmenting path
            vec<int> parent(n, -1);
            vec<int> parentEdge(n, -1);
            parent[s] = s;

            queue<int> q;
            q.push(s);

            while (!q.empty() && parent[t] == -1) {
                int u = q.front(); q.pop();
                for (int i = 0; i < sz(graph[u]); i++) {
                    auto& e = graph[u][i];
                    if (parent[e.to] == -1 && e.cap > 0) {
                        parent[e.to] = u;
                        parentEdge[e.to] = i;
                        q.push(e.to);
                    }
                }
            }

            if (parent[t] == -1) break; // no augmenting path

            // Find bottleneck
            i64 aug = LLONG_MAX;
            for (int v = t; v != s; ) {
                int u = parent[v];
                aug = min(aug, graph[u][parentEdge[v]].cap);
                v = u;
            }

            // Update residual graph
            for (int v = t; v != s; ) {
                int u = parent[v];
                graph[u][parentEdge[v]].cap -= aug;
                graph[v][graph[u][parentEdge[v]].rev].cap += aug;
                v = u;
            }

            flow += aug;
        }

        return flow;
    }
};

void solve() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--; t--;

    MaxFlow mf(n);
    for (int i = 0; i < m; i++) {
        int u, v; i64 c;
        cin >> u >> v >> c; u--; v--;
        mf.addEdge(u, v, c);
    }

    cout << "Max Flow: " << mf.maxflow(s, t) << nl;
}

/*
Input: 1\n4 5 1 4\n1 2 10\n1 3 8\n2 4 5\n2 3 3\n3 4 7
Output: Max Flow: 12
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

