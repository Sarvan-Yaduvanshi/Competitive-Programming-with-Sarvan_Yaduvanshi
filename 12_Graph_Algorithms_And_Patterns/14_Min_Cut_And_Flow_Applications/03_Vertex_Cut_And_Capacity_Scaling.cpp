/*
╔══════════════════════════════════════════════════════════════════╗
║         VERTEX SPLITTING + CAPACITY SCALING (Flow)              ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
1. VERTEX SPLITTING — Handle vertex capacities in flow
═══════════════════════════════════════════════════════════════════

Problem: vertex v has capacity c (max flow THROUGH it = c).
Solution: Split v into v_in and v_out:
  - All incoming edges → v_in
  - All outgoing edges → v_out
  - Add edge v_in → v_out with capacity c

Now vertex capacity = edge capacity!

VERTEX CUT: min vertices to disconnect s from t.
  Split all vertices (except s, t), find min cut.

═══════════════════════════════════════════════════════════════════
2. CAPACITY SCALING — Flow optimization
═══════════════════════════════════════════════════════════════════

Only use edges with residual capacity ≥ Δ.
Start Δ = largest power of 2 ≤ max_capacity.
Each phase: find augmenting paths with cap ≥ Δ.
When done, Δ /= 2. Repeat until Δ = 0.

Time: O(E² log U) where U = max capacity
Better than Edmonds-Karp O(VE²) when capacities large.

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

// Dinic for vertex splitting
struct Dinic {
    struct Edge { int to, rev; i64 cap; };
    vec<vec<Edge>> g;
    vec<int> level, iter;
    Dinic(int n):g(n),level(n),iter(n){}
    void addEdge(int u,int v,i64 c){
        g[u].push_back({v,sz(g[v]),c});
        g[v].push_back({u,sz(g[u])-1,0});
    }
    bool bfs(int s,int t){fill(level.begin(),level.end(),-1);level[s]=0;queue<int>q;q.push(s);while(!q.empty()){int v=q.front();q.pop();for(auto&e:g[v])if(e.cap>0&&level[e.to]<0){level[e.to]=level[v]+1;q.push(e.to);}}return level[t]>=0;}
    i64 dfs(int v,int t,i64 f){if(v==t)return f;for(int&i=iter[v];i<sz(g[v]);i++){auto&e=g[v][i];if(e.cap>0&&level[v]<level[e.to]){i64 d=dfs(e.to,t,min(f,e.cap));if(d>0){e.cap-=d;g[e.to][e.rev].cap+=d;return d;}}}return 0;}
    i64 maxflow(int s,int t){i64 flow=0;while(bfs(s,t)){fill(iter.begin(),iter.end(),0);for(i64 d;(d=dfs(s,t,LLONG_MAX))>0;)flow+=d;}return flow;}
};

void solve() {
    int n, m, s, t;
    cin >> n >> m >> s >> t; s--; t--;

    // Vertex splitting: vertex i → i_in (=i), i_out (=i+n)
    Dinic dinic(2 * n);

    // Vertex capacities
    for (int i = 0; i < n; i++) {
        i64 vc; cin >> vc;
        if (i == s || i == t) vc = LLONG_MAX / 2; // s,t have infinite capacity
        dinic.addEdge(i, i + n, vc); // v_in → v_out
    }

    // Edges: go from u_out to v_in
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        dinic.addEdge(u + n, v, LLONG_MAX / 2); // u_out → v_in
        dinic.addEdge(v + n, u, LLONG_MAX / 2); // undirected
    }

    i64 minVertexCut = dinic.maxflow(s, t + n);
    cout << "Minimum vertex cut: " << minVertexCut << nl;
}

/*
Min vertex cut = min vertices to remove to disconnect s from t.
Input: 1\n5 5 1 5\n1 1 1 1 1\n1 2\n1 3\n2 4\n3 4\n4 5
Each vertex has capacity 1.
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

