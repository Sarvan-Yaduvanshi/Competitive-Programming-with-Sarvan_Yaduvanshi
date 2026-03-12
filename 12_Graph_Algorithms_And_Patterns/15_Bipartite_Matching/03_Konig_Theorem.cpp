/*
╔══════════════════════════════════════════════════════════════════╗
║              03 — KÖNIG'S THEOREM                               ║
║     Min Vertex Cover = Max Matching (in bipartite graphs)       ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
THEOREM
═══════════════════════════════════════════════════════════════════

In a BIPARTITE graph:
  Maximum Matching = Minimum Vertex Cover

VERTEX COVER: smallest set of vertices that touches every edge.
INDEPENDENT SET = V - Vertex Cover

So: Max Independent Set = V - Max Matching (bipartite only!)

FINDING THE VERTEX COVER:
1. Compute max matching using Kuhn/Hopcroft-Karp
2. From UNMATCHED left vertices, do alternating BFS/DFS
3. Vertex cover = (unvisited LEFT vertices) ∪ (visited RIGHT vertices)

Time: O(VE) or O(E√V)    Space: O(V+E)
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
#define pb push_back
#define nl '\n'

int nL, nR, m;
vvec<int> adj;
vec<int> matchL, matchR;
vec<bool> used;

bool tryKuhn(int u) {
    for(int v:adj[u]) if(!used[v]){
        used[v]=true;
        if(matchR[v]==-1||tryKuhn(matchR[v])){ matchL[u]=v; matchR[v]=u; return true; }
    }
    return false;
}

void solve() {
    cin >> nL >> nR >> m;
    adj.assign(nL,{});
    for(int i=0;i<m;i++){ int u,v; cin>>u>>v; u--;v--; adj[u].pb(v); }

    matchL.assign(nL,-1); matchR.assign(nR,-1);
    int matching = 0;
    for(int u=0;u<nL;u++){ used.assign(nR,false); if(tryKuhn(u)) matching++; }

    cout << "Max Matching = Min Vertex Cover = " << matching << nl;
    cout << "Max Independent Set = " << nL+nR-matching << nl;

    // Find actual vertex cover using König's construction
    // BFS from unmatched left vertices through alternating paths
    vec<bool> visitL(nL,false), visitR(nR,false);
    queue<int> q;
    for(int u=0;u<nL;u++) if(matchL[u]==-1){ q.push(u); visitL[u]=true; }

    while(!q.empty()){
        int u=q.front(); q.pop();
        for(int v:adj[u]){
            if(!visitR[v]){
                visitR[v]=true;
                if(matchR[v]!=-1 && !visitL[matchR[v]]){
                    visitL[matchR[v]]=true;
                    q.push(matchR[v]);
                }
            }
        }
    }

    // Vertex cover = unvisited left ∪ visited right
    cout << "Vertex Cover:" << nl << "  Left: ";
    for(int i=0;i<nL;i++) if(!visitL[i]) cout<<i+1<<" ";
    cout << nl << "  Right: ";
    for(int i=0;i<nR;i++) if(visitR[i]) cout<<i+1<<" ";
    cout << nl;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin>>TC; while(TC--) solve();
}

