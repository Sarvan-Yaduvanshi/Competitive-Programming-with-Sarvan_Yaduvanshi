/*
╔══════════════════════════════════════════════════════════════════╗
║        03 — BRIDGE TREE (2-Edge-Connected Components)           ║
║        Compress each 2-edge-connected component to single node  ║
╚══════════════════════════════════════════════════════════════════╝

A 2-EDGE-CONNECTED COMPONENT is a maximal subgraph with no bridges.
Removing bridges partitions graph into these components.

Bridge Tree: compress each component → result is a tree!
(bridges become the edges of this tree)

Useful for: path queries that need to avoid bridges

Time: O(V+E)    Space: O(V+E)
*/
#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
#endif
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define pb push_back
#define nl '\n'

int n, m;
vvec<int> adj;
vec<int> disc, low, comp;
int timer_val, numComp;

void dfs(int u, int parent) {
    disc[u] = low[u] = timer_val++;
    for(int v : adj[u]) {
        if(v == parent) { parent = -1; continue; }
        if(disc[v] == -1) { dfs(v, u); low[u] = min(low[u], low[v]); }
        else low[u] = min(low[u], disc[v]);
    }
}

void dfsComp(int u, int c, vec<vec<pair<int,bool>>>& adjBridge) {
    comp[u] = c;
    for(auto [v, isBridge] : adjBridge[u]) {
        if(comp[v] == -1 && !isBridge) dfsComp(v, c, adjBridge);
    }
}

void solve() {
    cin >> n >> m;
    adj.assign(n, {});
    vec<pair<int,int>> edges(m);
    for(int i = 0; i < m; i++) {
        auto&[u,v] = edges[i];
        cin >> u >> v; u--; v--;
        adj[u].pb(v); adj[v].pb(u);
    }

    disc.assign(n,-1); low.assign(n,0); timer_val=0;
    for(int i=0;i<n;i++) if(disc[i]==-1) dfs(i,-1);

    // Mark bridges
    vec<vec<pair<int,bool>>> adjBridge(n);
    for(auto [u,v] : edges) {
        bool bridge = (low[v] > disc[u]) || (low[u] > disc[v]);
        adjBridge[u].pb({v, bridge});
        adjBridge[v].pb({u, bridge});
    }

    // Find 2-edge-connected components
    comp.assign(n,-1); numComp=0;
    for(int i=0;i<n;i++) if(comp[i]==-1) dfsComp(i, numComp++, adjBridge);

    cout << "2-edge-connected components: " << numComp << nl;
    for(int c=0;c<numComp;c++){
        cout << "Comp " << c << ": ";
        for(int i=0;i<n;i++) if(comp[i]==c) cout << i+1 << " ";
        cout << nl;
    }

    // Bridge tree edges
    cout << "Bridge tree edges:" << nl;
    for(auto [u,v] : edges) {
        if(comp[u] != comp[v]) {
            cout << "  Comp" << comp[u] << " — Comp" << comp[v] << nl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin>>TC;
    while(TC--) solve();
}

