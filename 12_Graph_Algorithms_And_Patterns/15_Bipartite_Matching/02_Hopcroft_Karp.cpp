/*
╔══════════════════════════════════════════════════════════════════╗
║              02 — HOPCROFT-KARP ALGORITHM                       ║
║              Maximum Bipartite Matching O(E√V)                  ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
ALGORITHM
═══════════════════════════════════════════════════════════════════

Improvement over Kuhn: find MULTIPLE augmenting paths per phase.

1. BFS: find shortest augmenting path length (level graph)
2. DFS: find all vertex-disjoint augmenting paths of that length
3. Repeat until no augmenting path exists

Each phase takes O(E). At most O(√V) phases needed.
Total: O(E × √V)

═══════════════════════════════════════════════════════════════════
COMPLEXITY
  Time:  O(E × √V) — much faster than Kuhn for large graphs
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
using namespace std;

template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

constexpr int NIL = -1;
constexpr int INF = 1e9;

struct HopcroftKarp {
    int nL, nR;
    vvec<int> adj;
    vec<int> matchL, matchR, dist;

    HopcroftKarp(int nL, int nR) : nL(nL), nR(nR), adj(nL), matchL(nL, NIL), matchR(nR, NIL), dist(nL) {}

    void addEdge(int u, int v) { adj[u].pb(v); }

    bool bfs() {
        queue<int> q;
        for (int u = 0; u < nL; u++) {
            if (matchL[u] == NIL) { dist[u] = 0; q.push(u); }
            else dist[u] = INF;
        }
        bool found = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                int w = matchR[v]; // w is the left vertex matched to right v
                if (w == NIL) { found = true; }
                else if (dist[w] == INF) {
                    dist[w] = dist[u] + 1;
                    q.push(w);
                }
            }
        }
        return found;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            int w = matchR[v];
            if (w == NIL || (dist[w] == dist[u] + 1 && dfs(w))) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        dist[u] = INF;
        return false;
    }

    int maxMatching() {
        int result = 0;
        while (bfs()) {
            for (int u = 0; u < nL; u++) {
                if (matchL[u] == NIL && dfs(u)) result++;
            }
        }
        return result;
    }
};

void solve() {
    int nL, nR, m;
    cin >> nL >> nR >> m;

    HopcroftKarp hk(nL, nR);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        hk.addEdge(u, v);
    }

    int matching = hk.maxMatching();
    cout << "Maximum matching (Hopcroft-Karp): " << matching << nl;

    for (int u = 0; u < nL; u++) {
        if (hk.matchL[u] != NIL) {
            cout << "  L" << u+1 << " — R" << hk.matchL[u]+1 << nl;
        }
    }
}

/*
Input: 1\n3 3 5\n1 1\n1 2\n2 1\n2 3\n3 2
Output:
Maximum matching (Hopcroft-Karp): 3
  L1 — R1
  L2 — R3
  L3 — R2
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

