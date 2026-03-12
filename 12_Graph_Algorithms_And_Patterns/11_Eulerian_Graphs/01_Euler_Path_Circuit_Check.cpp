/*
╔══════════════════════════════════════════════════════════════════╗
║              01 — EULER PATH / CIRCUIT CHECK                    ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

EULER PATH:    A path that visits every EDGE exactly once.
EULER CIRCUIT: An Euler path that starts and ends at same vertex.

CONDITIONS (Undirected):
  ┌─────────────────────────────────────────────────────────────┐
  │  Type     │ Condition                                       │
  ├───────────┼─────────────────────────────────────────────────┤
  │  Circuit  │ Connected + ALL vertices have even degree       │
  │  Path     │ Connected + exactly 0 or 2 odd-degree vertices  │
  │  Neither  │ > 2 odd-degree vertices                         │
  └─────────────────────────────────────────────────────────────┘

CONDITIONS (Directed):
  Circuit: connected + in-degree = out-degree for ALL vertices
  Path:    connected + at most 1 vertex with out-in=1 (start)
                     + at most 1 vertex with in-out=1 (end)
                     + all others: in = out

═══════════════════════════════════════════════════════════════════
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
#define nl '\n'

void solve() {
    int n, m; cin >> n >> m;
    vvec<int> adj(n);
    vec<int> deg(n, 0);
    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v; u--;v--;
        adj[u].push_back(v); adj[v].push_back(u);
        deg[u]++; deg[v]++;
    }

    // Check connected (only among vertices with edges)
    vec<bool> vis(n,false);
    int start = -1;
    for(int i=0;i<n;i++) if(deg[i]>0) { start=i; break; }

    if(start==-1) { cout << "Empty graph — trivial Euler circuit" << nl; return; }

    queue<int> q; q.push(start); vis[start]=true; int cnt=0;
    while(!q.empty()){
        int u=q.front(); q.pop(); cnt++;
        for(int v:adj[u]) if(!vis[v]) { vis[v]=true; q.push(v); }
    }

    int edgeVertices = 0;
    for(int i=0;i<n;i++) if(deg[i]>0) edgeVertices++;

    if(cnt != edgeVertices) { cout << "NOT connected — no Euler path/circuit" << nl; return; }

    int oddCount = 0;
    vec<int> oddVertices;
    for(int i=0;i<n;i++) if(deg[i]%2==1) { oddCount++; oddVertices.push_back(i); }

    if(oddCount == 0) cout << "EULER CIRCUIT exists (all even degrees)" << nl;
    else if(oddCount == 2) {
        cout << "EULER PATH exists from " << oddVertices[0]+1 << " to " << oddVertices[1]+1 << nl;
    } else {
        cout << "NO Euler path/circuit (" << oddCount << " odd-degree vertices)" << nl;
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin>>TC; while(TC--) solve();
}

