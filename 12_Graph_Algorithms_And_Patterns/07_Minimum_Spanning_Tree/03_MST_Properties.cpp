/*
╔══════════════════════════════════════════════════════════════════╗
║              03 — MST PROPERTIES                                ║
║              Cut property, Cycle property, Uniqueness           ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
KEY PROPERTIES OF MST
═══════════════════════════════════════════════════════════════════

1. CUT PROPERTY:
   For any cut (S, V-S), the minimum weight edge crossing the cut
   MUST be in the MST.
   → This is why Kruskal and Prim work!

2. CYCLE PROPERTY:
   For any cycle, the maximum weight edge in the cycle
   is NOT in any MST (if weights are distinct).

3. UNIQUENESS:
   If all edge weights are DISTINCT, the MST is UNIQUE.
   If some weights are equal, multiple MSTs may exist.

4. NUMBER OF EDGES:
   MST of n vertices always has exactly n-1 edges.

5. SECOND-BEST MST:
   Differs from MST by exactly one edge swap:
   Remove one MST edge, add one non-MST edge.

═══════════════════════════════════════════════════════════════════
SECOND-BEST MST ALGORITHM
═══════════════════════════════════════════════════════════════════

1. Find MST using Kruskal
2. For each non-MST edge (u,v,w):
   - Find maximum weight edge on MST path from u to v
   - Swap: remove max edge, add (u,v,w)
   - Track minimum increase
3. Best swap = second-best MST

Time: O(E log E + V²) or O(E log E + V log V) with LCA

═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
constexpr i64 INF64 = 4e18;
#define nl '\n'

struct DSU {
    vec<int> p, r;
    DSU(int n) : p(n), r(n,0) { for(int i=0;i<n;i++) p[i]=i; }
    int find(int x) { while(p[x]!=x) x=p[x]=p[p[x]]; return x; }
    bool unite(int a, int b) {
        a=find(a); b=find(b);
        if(a==b) return false;
        if(r[a]<r[b]) swap(a,b);
        p[b]=a; if(r[a]==r[b]) r[a]++;
        return true;
    }
};

struct Edge { int u,v; i64 w; bool operator<(const Edge& o)const{return w<o.w;} };

void solve() {
    int n, m; cin >> n >> m;
    vec<Edge> edges(m);
    for(auto&[u,v,w]:edges){cin>>u>>v>>w;u--;v--;}

    sort(edges.begin(),edges.end());
    DSU dsu(n);

    i64 mstW = 0;
    vec<bool> inMST(m, false);
    vvec<pair<int,i64>> adj(n);  // MST adjacency

    for(int i=0;i<m;i++){
        auto&[u,v,w]=edges[i];
        if(dsu.unite(u,v)){
            mstW += w;
            inMST[i] = true;
            adj[u].push_back({v,w});
            adj[v].push_back({u,w});
        }
    }

    cout << "MST weight: " << mstW << nl;

    // Find max weight edge on path between u,v in MST (brute force BFS for small n)
    // For each non-MST edge, find improvement
    auto maxOnPath = [&](int s, int t) -> i64 {
        // BFS to find path from s to t on MST, track max weight
        vec<i64> maxW(n, -1);
        vec<bool> vis(n, false);
        queue<int> q;
        q.push(s); vis[s]=true; maxW[s]=0;
        while(!q.empty()){
            int u=q.front();q.pop();
            for(auto[v,w]:adj[u]){
                if(!vis[v]){
                    vis[v]=true;
                    maxW[v]=max(maxW[u],w);
                    q.push(v);
                }
            }
        }
        return maxW[t];
    };

    i64 secondBest = INF64;
    for(int i=0;i<m;i++){
        if(inMST[i]) continue;
        auto&[u,v,w]=edges[i];
        i64 maxE = maxOnPath(u, v);
        if(maxE >= 0 && w - maxE < secondBest - mstW + mstW) {
            secondBest = min(secondBest, mstW - maxE + w);
        }
    }

    if(secondBest == INF64) cout << "No second-best MST" << nl;
    else cout << "Second-best MST weight: " << secondBest << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

