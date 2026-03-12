/*
╔══════════════════════════════════════════════════════════════════╗
║        01 — BIPARTITE CHECK (BFS/DFS 2-Coloring)               ║
╚══════════════════════════════════════════════════════════════════╝

Complete bipartite check with both BFS and DFS.
A graph is bipartite iff it has no odd-length cycle.

Time: O(V+E)    Space: O(V)
*/
#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
#endif
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define pb push_back
#define nl '\n'

// DFS 2-coloring
bool dfsBipartite(int u, int c, vec<int>& color, vvec<int>& adj) {
    color[u] = c;
    for(int v : adj[u]) {
        if(color[v] == -1) { if(!dfsBipartite(v, 1-c, color, adj)) return false; }
        else if(color[v] == c) return false;
    }
    return true;
}

void solve() {
    int n, m; cin >> n >> m;
    vvec<int> adj(n);
    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v; u--;v--;
        adj[u].pb(v); adj[v].pb(u);
    }

    vec<int> color(n, -1);
    bool bipartite = true;
    for(int i=0;i<n && bipartite;i++)
        if(color[i]==-1)
            bipartite = dfsBipartite(i, 0, color, adj);

    cout << (bipartite ? "YES — Bipartite (2-colorable)" : "NO — Not bipartite") << nl;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin>>TC; while(TC--) solve();
}

