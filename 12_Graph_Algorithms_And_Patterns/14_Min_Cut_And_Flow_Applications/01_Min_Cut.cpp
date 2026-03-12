/*
╔══════════════════════════════════════════════════════════════════╗
║              01 — MIN CUT (Max-Flow Min-Cut Theorem)            ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
MAX-FLOW MIN-CUT THEOREM
═══════════════════════════════════════════════════════════════════

The MAXIMUM FLOW from s to t equals the MINIMUM CUT capacity.

A CUT (S, T) is a partition of vertices into S (containing s)
and T (containing t). The capacity of the cut = sum of capacities
of edges from S to T.

FINDING THE MIN CUT:
1. Compute max flow using Dinic/Edmonds-Karp
2. BFS from s on the RESIDUAL graph (only edges with cap > 0)
3. Reachable vertices = S side, unreachable = T side
4. Cut edges = edges (u,v) where u∈S, v∈T, and original cap > 0

═══════════════════════════════════════════════════════════════════
APPLICATIONS
═══════════════════════════════════════════════════════════════════
- Network reliability (minimum edges to disconnect)
- Image segmentation
- Project selection (profit maximization with dependencies)
- Minimum vertex cut (split vertices into in/out)

Time: Same as max flow    Space: O(V+E)
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
#endif
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
#define sz(x) ((int)(x).size())
#define nl '\n'

struct Dinic {
    struct Edge { int to, rev; i64 cap; };
    int n;
    vec<vec<Edge>> graph;
    vec<int> level, iter;
    Dinic(int n):n(n),graph(n),level(n),iter(n){}
    void addEdge(int u,int v,i64 c){
        graph[u].push_back({v,sz(graph[v]),c});
        graph[v].push_back({u,sz(graph[u])-1,0});
    }
    bool bfs(int s,int t){
        fill(level.begin(),level.end(),-1);
        queue<int>q; level[s]=0; q.push(s);
        while(!q.empty()){int v=q.front();q.pop();for(auto&e:graph[v])if(e.cap>0&&level[e.to]<0){level[e.to]=level[v]+1;q.push(e.to);}}
        return level[t]>=0;
    }
    i64 dfs(int v,int t,i64 f){
        if(v==t)return f;
        for(int&i=iter[v];i<sz(graph[v]);i++){auto&e=graph[v][i];if(e.cap>0&&level[v]<level[e.to]){i64 d=dfs(e.to,t,min(f,e.cap));if(d>0){e.cap-=d;graph[e.to][e.rev].cap+=d;return d;}}}
        return 0;
    }
    i64 maxflow(int s,int t){
        i64 flow=0;
        while(bfs(s,t)){fill(iter.begin(),iter.end(),0);i64 d;while((d=dfs(s,t,LLONG_MAX))>0)flow+=d;}
        return flow;
    }

    // FIND MIN CUT after computing maxflow
    vec<bool> minCutSide(int s) {
        vec<bool> reachable(n, false);
        queue<int> q;
        reachable[s] = true; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto& e : graph[u]) {
                if (e.cap > 0 && !reachable[e.to]) {
                    reachable[e.to] = true;
                    q.push(e.to);
                }
            }
        }
        return reachable;
    }
};

void solve() {
    int n, m, s, t;
    cin >> n >> m >> s >> t; s--; t--;

    Dinic dinic(n);
    vec<tuple<int,int,i64>> edges;
    for(int i=0;i<m;i++){
        int u,v; i64 c; cin>>u>>v>>c; u--;v--;
        edges.push_back({u,v,c});
        dinic.addEdge(u,v,c);
    }

    i64 flow = dinic.maxflow(s, t);
    cout << "Max Flow = Min Cut = " << flow << nl;

    auto reachable = dinic.minCutSide(s);

    cout << "S side: "; for(int i=0;i<n;i++) if(reachable[i]) cout<<i+1<<" "; cout<<nl;
    cout << "T side: "; for(int i=0;i<n;i++) if(!reachable[i]) cout<<i+1<<" "; cout<<nl;

    cout << "Cut edges:" << nl;
    for(auto [u,v,c] : edges){
        if(reachable[u] && !reachable[v]){
            cout << "  " << u+1 << " → " << v+1 << " (cap=" << c << ")" << nl;
        }
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin>>TC; while(TC--) solve();
}

