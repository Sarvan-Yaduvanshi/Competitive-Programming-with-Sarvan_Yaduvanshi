/*
╔══════════════════════════════════════════════════════════════════╗
║              03 — CONDENSATION GRAPH (SCC → DAG)                ║
║              Compress each SCC into a single node               ║
╚══════════════════════════════════════════════════════════════════╝

After finding SCCs, create a new graph where:
  - Each SCC = one super-node
  - Edge between super-nodes if original graph has edge between SCCs
  - Result is always a DAG!

This enables DP on the condensed graph (topological order).

Time: O(V+E)    Space: O(V+E)
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

// Kosaraju to find SCCs
vvec<int> adj, radj;
vec<bool> visited;
vec<int> order, comp;

void dfs1(int u) { visited[u]=true; for(int v:adj[u]) if(!visited[v]) dfs1(v); order.pb(u); }
void dfs2(int u, int c) { comp[u]=c; for(int v:radj[u]) if(comp[v]==-1) dfs2(v,c); }

void solve() {
    int n, m; cin >> n >> m;
    adj.assign(n,{}); radj.assign(n,{});

    vec<pair<int,int>> edges(m);
    for(auto&[u,v]:edges){ cin>>u>>v; u--;v--; adj[u].pb(v); radj[v].pb(u); }

    // Find SCCs
    visited.assign(n,false); order.clear();
    for(int i=0;i<n;i++) if(!visited[i]) dfs1(i);
    comp.assign(n,-1);
    int numSCC=0;
    for(int i=n-1;i>=0;i--){ int u=order[i]; if(comp[u]==-1) dfs2(u,numSCC++); }

    // Build condensation DAG
    vvec<int> dag(numSCC);
    vec<int> sccSize(numSCC, 0);
    set<pair<int,int>> dagEdges;

    for(int i=0;i<n;i++) sccSize[comp[i]]++;

    for(auto&[u,v]:edges){
        if(comp[u]!=comp[v] && !dagEdges.count({comp[u],comp[v]})){
            dag[comp[u]].pb(comp[v]);
            dagEdges.insert({comp[u],comp[v]});
        }
    }

    cout << "SCCs: " << numSCC << nl;
    for(int i=0;i<numSCC;i++){
        cout << "SCC " << i << " (size=" << sccSize[i] << "): {";
        bool first=true;
        for(int j=0;j<n;j++) if(comp[j]==i){ if(!first) cout<<","; cout<<j+1; first=false; }
        cout << "}" << nl;
    }

    cout << nl << "Condensation DAG edges:" << nl;
    for(auto&[u,v]:dagEdges) cout << "  SCC" << u << " → SCC" << v << nl;

    // Example DP on DAG: longest path (by SCC sizes)
    // Topological order via Kahn's on DAG
    vec<int> inDeg(numSCC,0);
    for(int u=0;u<numSCC;u++) for(int v:dag[u]) inDeg[v]++;
    queue<int> q;
    for(int i=0;i<numSCC;i++) if(!inDeg[i]) q.push(i);
    vec<i64> dp(numSCC);
    for(int i=0;i<numSCC;i++) dp[i]=sccSize[i];

    while(!q.empty()){
        int u=q.front(); q.pop();
        for(int v:dag[u]){
            dp[v]=max(dp[v], dp[u]+sccSize[v]);
            if(--inDeg[v]==0) q.push(v);
        }
    }

    cout << nl << "Max vertices on any path: " << *max_element(dp.begin(),dp.end()) << nl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin>>TC;
    while(TC--) solve();
}

