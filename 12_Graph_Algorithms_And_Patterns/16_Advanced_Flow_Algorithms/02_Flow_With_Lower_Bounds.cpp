/*
╔══════════════════════════════════════════════════════════════════╗
║         02 — FLOW WITH LOWER BOUNDS (Circulation)               ║
║         Flow networks where edges have minimum flow             ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

In standard max flow, each edge has capacity [0, cap].
In flow with lower bounds, each edge has range [lo, hi].

REDUCTION TO STANDARD FLOW:
  For edge (u, v) with flow range [lo, hi]:
  1. Set mandatory flow lo on this edge
  2. Add edge (u, v) with capacity (hi - lo) for optional flow
  3. Adjust excess: vertex v gets excess +lo, vertex u gets excess -lo
  4. Create super-source S' and super-sink T':
     - For each vertex v with positive excess d[v] > 0: add edge S' → v with cap d[v]
     - For each vertex v with negative excess d[v] < 0: add edge v → T' with cap -d[v]
  5. If max flow from S' to T' saturates all edges from S' → feasible!

═══════════════════════════════════════════════════════════════════
TYPES
═══════════════════════════════════════════════════════════════════

1. FEASIBILITY (Circulation): Does a valid flow exist?
2. MIN FLOW: Find minimum flow from s to t satisfying lower bounds
3. MAX FLOW: Find maximum flow from s to t with lower bounds

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
    int n, m;
    cin >> n >> m;

    // Vertices 0..n-1 are original
    // n = super source S', n+1 = super sink T'
    int S = n, T = n + 1;
    Dinic dinic(n + 2);
    vec<i64> excess(n, 0);
    i64 totalLower = 0;

    for (int i = 0; i < m; i++) {
        int u, v; i64 lo, hi;
        cin >> u >> v >> lo >> hi; u--; v--;

        // Add optional capacity edge
        dinic.addEdge(u, v, hi - lo);

        // Track excess from mandatory lower bound
        excess[v] += lo;  // v receives lo
        excess[u] -= lo;  // u sends lo
    }

    // Add edges from/to super source/sink
    i64 needFlow = 0;
    for (int i = 0; i < n; i++) {
        if (excess[i] > 0) {
            dinic.addEdge(S, i, excess[i]);
            needFlow += excess[i];
        } else if (excess[i] < 0) {
            dinic.addEdge(i, T, -excess[i]);
        }
    }

    i64 flow = dinic.maxflow(S, T);

    if (flow == needFlow) {
        cout << "FEASIBLE! A valid circulation exists." << nl;
    } else {
        cout << "INFEASIBLE! No valid circulation." << nl;
    }
}

/*
Input: 1\n3 3\n1 2 1 5\n2 3 2 4\n3 1 0 3
(Edge 1→2 needs flow [1,5], Edge 2→3 needs [2,4], Edge 3→1 needs [0,3])
Output: FEASIBLE! (flow: 1→2:2, 2→3:2, 3→1:2)
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

