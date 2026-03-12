/*
╔══════════════════════════════════════════════════════════════════╗
║         COMPLEMENT GRAPH BFS + SHORTEST CYCLE IN GRAPH          ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
1. COMPLEMENT GRAPH BFS — O(V + E)
═══════════════════════════════════════════════════════════════════

BFS on complement graph WITHOUT building it explicitly.
Trick: maintain set of "unvisited" vertices. For each BFS vertex,
iterate unvisited set and add non-neighbors.

Time: O(V + E)  (each vertex removed from unvisited set once)

═══════════════════════════════════════════════════════════════════
2. SHORTEST CYCLE (GIRTH)
═══════════════════════════════════════════════════════════════════

GIRTH = length of shortest cycle in graph.

For unweighted: BFS from each vertex, track when we find a
vertex already visited at same or earlier level → cycle found.

Time: O(V × (V + E))    Optimization: O(V × E) for sparse

═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
#endif
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define nl '\n'

// ═══════════════════════════════════════════
// COMPLEMENT GRAPH BFS
// ═══════════════════════════════════════════
int complementBFS(int n, vvec<int>& adj) {
    // Find connected components of complement graph
    set<int> unvisited;
    for (int i = 0; i < n; i++) unvisited.insert(i);

    int components = 0;

    for (int i = 0; i < n; i++) {
        if (unvisited.find(i) == unvisited.end()) continue;

        components++;
        queue<int> q;
        q.push(i);
        unvisited.erase(i);

        while (!q.empty()) {
            int u = q.front(); q.pop();

            set<int> neighbors(adj[u].begin(), adj[u].end());
            set<int> toVisit;

            for (int v : unvisited) {
                if (neighbors.find(v) == neighbors.end()) {
                    // v is NOT neighbor of u in original → IS neighbor in complement
                    toVisit.insert(v);
                }
            }

            for (int v : toVisit) {
                unvisited.erase(v);
                q.push(v);
            }
        }
    }

    return components;
}

// ═══════════════════════════════════════════
// SHORTEST CYCLE (GIRTH)
// ═══════════════════════════════════════════
int shortestCycle(int n, vvec<int>& adj) {
    int girth = n + 1; // INF

    for (int src = 0; src < n; src++) {
        vec<int> dist(n, -1);
        dist[src] = 0;
        queue<int> q;
        q.push(src);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                } else if (dist[v] >= dist[u]) {
                    // Found a cycle!
                    girth = min(girth, dist[u] + dist[v] + 1);
                }
            }
        }
    }

    return girth > n ? -1 : girth;
}

void solve() {
    int n, m; cin >> n >> m;
    vvec<int> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].push_back(v); adj[v].push_back(u);
    }

    int girth = shortestCycle(n, adj);
    cout << "Shortest cycle (girth): " << (girth == -1 ? -1 : girth) << nl;

    int compComps = complementBFS(n, adj);
    cout << "Complement graph components: " << compComps << nl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

