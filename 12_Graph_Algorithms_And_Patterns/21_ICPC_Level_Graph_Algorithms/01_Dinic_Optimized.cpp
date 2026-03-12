/*
╔══════════════════════════════════════════════════════════════════╗
║         01 — DINIC OPTIMIZED (Scaling + Applications)           ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DINIC OPTIMIZATIONS FOR ICPC
═══════════════════════════════════════════════════════════════════

1. CAPACITY SCALING: Only consider edges with cap ≥ threshold.
   Start with large threshold, halve each phase.
   Improves worst case to O(V²E log U) where U = max capacity.

2. CURRENT ARC: Already in standard Dinic (iter[] array).

3. UNIT CAPACITY: When all caps = 1, Dinic runs in O(E√V).
   Perfect for bipartite matching!

4. For ICPC: this Dinic template handles virtually all flow problems.

Below is a CLEAN, OPTIMIZED Dinic template ready for ICPC.
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

// ═══════════════════════════════════════════════════
// ICPC-READY DINIC'S MAX FLOW TEMPLATE
// ═══════════════════════════════════════════════════
struct Dinic {
    struct Edge { int to, rev; i64 cap; };
    vec<vec<Edge>> g;
    vec<int> level, iter;

    Dinic(int n) : g(n), level(n), iter(n) {}

    void addEdge(int u, int v, i64 c, i64 rc = 0) {
        g[u].push_back({v, sz(g[v]), c});
        g[v].push_back({u, sz(g[u])-1, rc}); // rc=c for undirected
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q; q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto& e : g[v])
                if (e.cap > 0 && level[e.to] < 0)
                    level[e.to] = level[v] + 1, q.push(e.to);
        }
        return level[t] >= 0;
    }

    i64 dfs(int v, int t, i64 f) {
        if (v == t) return f;
        for (int& i = iter[v]; i < sz(g[v]); i++) {
            auto& e = g[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                i64 d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) { e.cap -= d; g[e.to][e.rev].cap += d; return d; }
            }
        }
        return 0;
    }

    i64 maxflow(int s, int t) {
        i64 flow = 0;
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            for (i64 d; (d = dfs(s, t, LLONG_MAX)) > 0;) flow += d;
        }
        return flow;
    }

    // Min cut: after maxflow, BFS reachable from s
    vec<bool> mincut(int s) {
        vec<bool> vis(sz(g), false);
        queue<int> q; q.push(s); vis[s] = true;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto& e : g[v])
                if (e.cap > 0 && !vis[e.to]) vis[e.to] = true, q.push(e.to);
        }
        return vis;
    }
};

void solve() {
    int n, m, s, t;
    cin >> n >> m >> s >> t; s--; t--;
    Dinic dinic(n);
    for (int i = 0; i < m; i++) {
        int u, v; i64 c; cin >> u >> v >> c; u--; v--;
        dinic.addEdge(u, v, c);
    }
    cout << dinic.maxflow(s, t) << nl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

