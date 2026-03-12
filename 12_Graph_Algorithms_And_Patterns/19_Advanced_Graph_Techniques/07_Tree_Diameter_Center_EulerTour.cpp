/*
╔══════════════════════════════════════════════════════════════════╗
║         TREE DIAMETER, CENTER, EULER TOUR                       ║
║         Fundamental tree properties used in graph algorithms    ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
1. TREE DIAMETER — longest path in tree
═══════════════════════════════════════════════════════════════════

Two-BFS method:
  1. BFS from any vertex → find farthest vertex u
  2. BFS from u → find farthest vertex v
  Distance u-v = diameter

Time: O(V)

═══════════════════════════════════════════════════════════════════
2. TREE CENTER — vertex minimizing max distance to any vertex
═══════════════════════════════════════════════════════════════════

Center is the middle vertex (or 2 vertices) of the diameter path.
Alternatively: repeatedly remove all leaves until 1-2 remain.

═══════════════════════════════════════════════════════════════════
3. EULER TOUR — flatten tree to array for range queries
═══════════════════════════════════════════════════════════════════

Enter/exit times (tin, tout): subtree of v = [tin[v], tout[v]]
Enables range queries on subtrees using segment tree/BIT.

═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
#endif
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define pb push_back
#define nl '\n'

int n;
vvec<int> adj;

// ═══════════════════════════════════════════
// TREE DIAMETER (Two-BFS)
// ═══════════════════════════════════════════
pair<int,vec<int>> bfs(int src) {
    vec<int> dist(n, -1);
    dist[src] = 0;
    queue<int> q; q.push(src);
    int farthest = src;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) if (dist[v]==-1) {
            dist[v] = dist[u]+1;
            q.push(v);
            if (dist[v] > dist[farthest]) farthest = v;
        }
    }
    return {farthest, dist};
}

// ═══════════════════════════════════════════
// EULER TOUR
// ═══════════════════════════════════════════
vec<int> tin, tout, euler;
int timer_val = 0;

void dfsEuler(int u, int p) {
    tin[u] = timer_val++;
    euler.pb(u);
    for (int v : adj[u]) if (v != p) {
        dfsEuler(v, u);
        euler.pb(u);
    }
    tout[u] = timer_val++;
}

void solve() {
    cin >> n;
    adj.assign(n, {});
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].pb(v); adj[v].pb(u);
    }

    // DIAMETER
    auto [u, d1] = bfs(0);
    auto [v, d2] = bfs(u);
    cout << "Diameter: " << d2[v] << " (between " << u+1 << " and " << v+1 << ")" << nl;

    // CENTER (middle of diameter path)
    // Reconstruct diameter path
    vec<int> parent(n, -1);
    vec<int> dist(n, -1);
    dist[u] = 0;
    queue<int> q; q.push(u);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int y : adj[x]) if (dist[y]==-1) {
            dist[y] = dist[x]+1;
            parent[y] = x;
            q.push(y);
        }
    }
    vec<int> path;
    for (int x = v; x != -1; x = parent[x]) path.pb(x);
    int center = path[path.size()/2];
    cout << "Center: " << center+1 << nl;

    // EULER TOUR
    tin.assign(n, 0); tout.assign(n, 0);
    euler.clear(); timer_val = 0;
    dfsEuler(0, -1);

    cout << "Euler tour: ";
    for (int x : euler) cout << x+1 << " ";
    cout << nl;
    cout << "Subtree of vertex 1: [" << tin[0] << ", " << tout[0] << ")" << nl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

