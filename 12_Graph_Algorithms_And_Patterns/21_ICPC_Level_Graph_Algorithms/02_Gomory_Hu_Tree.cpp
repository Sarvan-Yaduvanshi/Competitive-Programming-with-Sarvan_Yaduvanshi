/*
╔══════════════════════════════════════════════════════════════════╗
║         02 — GOMORY-HU TREE                                     ║
║         All-pairs min cut in n-1 max flow computations          ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

Gomory-Hu tree encodes ALL pairwise min-cuts:
  - Tree on same n vertices
  - Min cut between any u,v = min edge weight on path u→v in tree
  - Built using only n-1 max flow computations!

ALGORITHM:
  1. Initialize: all vertices point to vertex 0 (star tree)
  2. For i = 1 to n-1:
     a. Let p[i] = current parent of i
     b. Compute max flow between i and p[i]
     c. Set tree edge weight = max flow value
     d. For all j > i with p[j] == p[i]:
        If j is on i's side of the min cut, set p[j] = i

Time: O(n × MaxFlowTime)    Space: O(V + E)

═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
#endif
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
#define sz(x) ((int)(x).size())
#define nl '\n'

struct Dinic {
    struct Edge { int to, rev; i64 cap; };
    vec<vec<Edge>> g;
    vec<int> level, iter;
    Dinic(int n):g(n),level(n),iter(n){}
    void addEdge(int u,int v,i64 c){
        g[u].push_back({v,sz(g[v]),c});
        g[v].push_back({u,sz(g[u])-1,c}); // undirected: both caps = c
    }
    bool bfs(int s,int t){fill(level.begin(),level.end(),-1);level[s]=0;queue<int>q;q.push(s);while(!q.empty()){int v=q.front();q.pop();for(auto&e:g[v])if(e.cap>0&&level[e.to]<0){level[e.to]=level[v]+1;q.push(e.to);}}return level[t]>=0;}
    i64 dfs(int v,int t,i64 f){if(v==t)return f;for(int&i=iter[v];i<sz(g[v]);i++){auto&e=g[v][i];if(e.cap>0&&level[v]<level[e.to]){i64 d=dfs(e.to,t,min(f,e.cap));if(d>0){e.cap-=d;g[e.to][e.rev].cap+=d;return d;}}}return 0;}
    i64 maxflow(int s,int t){i64 flow=0;while(bfs(s,t)){fill(iter.begin(),iter.end(),0);for(i64 d;(d=dfs(s,t,LLONG_MAX))>0;)flow+=d;}return flow;}
    vec<bool> mincut(int s){vec<bool>vis(sz(g),false);queue<int>q;q.push(s);vis[s]=true;while(!q.empty()){int v=q.front();q.pop();for(auto&e:g[v])if(e.cap>0&&!vis[e.to]){vis[e.to]=true;q.push(e.to);}}return vis;}
};

void solve() {
    int n, m;
    cin >> n >> m;

    // Store original edges for rebuilding flow network
    struct OrigEdge { int u, v; i64 w; };
    vec<OrigEdge> edges(m);
    for(auto&[u,v,w]:edges){ cin>>u>>v>>w; u--;v--; }

    // Gomory-Hu tree construction
    vec<int> parent(n, 0);      // parent in GH tree
    vec<i64> parentWeight(n, 0); // weight of edge to parent

    for(int i = 1; i < n; i++){
        // Build fresh flow network
        Dinic dinic(n);
        for(auto&[u,v,w]:edges) dinic.addEdge(u,v,w);

        i64 flow = dinic.maxflow(i, parent[i]);
        parentWeight[i] = flow;

        // Update parents for other vertices
        auto side = dinic.mincut(i); // vertices reachable from i
        for(int j = i+1; j < n; j++){
            if(parent[j] == parent[i] && side[j]){
                parent[j] = i;
            }
        }
    }

    cout << "Gomory-Hu Tree:" << nl;
    i64 totalMinCut = 0;
    for(int i = 1; i < n; i++){
        cout << "  " << i+1 << " — " << parent[i]+1 << " (min-cut=" << parentWeight[i] << ")" << nl;
        totalMinCut += parentWeight[i];
    }

    // Query: min cut between any two vertices = min edge on path in tree
    // (Would need LCA + path min query for efficient answering)
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin>>TC; while(TC--) solve();
}

