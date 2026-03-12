/*
╔══════════════════════════════════════════════════════════════════╗
║         02 — PROJECT SELECTION (Flow Modeling)                   ║
║         Profit maximization with dependencies via min-cut       ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
PROBLEM PATTERN
═══════════════════════════════════════════════════════════════════

Given:
  - Projects with profits (positive = gain, negative = cost)
  - Dependencies: "if you do project A, you MUST do project B"

Find: subset of projects maximizing total profit.

═══════════════════════════════════════════════════════════════════
FLOW MODELING
═══════════════════════════════════════════════════════════════════

1. Create source S, sink T
2. For each project i:
   - If profit[i] > 0: edge S → i with capacity profit[i]
   - If profit[i] < 0: edge i → T with capacity -profit[i]
3. For each dependency (i must do j):
   - Edge i → j with capacity INF
4. Answer = sum of positive profits - max flow (min cut)

WHY?
  Min-cut separates vertices into S-side (selected) and T-side (not).
  Cutting S→i means NOT doing profitable project i (lose profit).
  Cutting i→T means doing costly project i (pay cost).
  INF edges ensure dependencies are respected.

Time: O(MaxFlow)    Space: O(V+E)
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
    vec<bool> mincut(int s){vec<bool>vis(sz(g),false);queue<int>q;q.push(s);vis[s]=true;while(!q.empty()){int v=q.front();q.pop();for(auto&e:g[v])if(e.cap>0&&!vis[e.to]){vis[e.to]=true;q.push(e.to);}}return vis;}
};

void solve() {
    int n, m;  // n projects, m dependencies
    cin >> n >> m;

    vec<i64> profit(n);
    for (auto& p : profit) cin >> p;

    // Vertices: 0=S, 1..n=projects, n+1=T
    int S = 0, T = n + 1;
    Dinic dinic(n + 2);

    i64 totalPositive = 0;

    for (int i = 0; i < n; i++) {
        if (profit[i] > 0) {
            dinic.addEdge(S, i+1, profit[i]);
            totalPositive += profit[i];
        } else if (profit[i] < 0) {
            dinic.addEdge(i+1, T, -profit[i]);
        }
    }

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--;
        // Dependency: if we do a, we must do b
        dinic.addEdge(a+1, b+1, LLONG_MAX / 2);
    }

    i64 minCut = dinic.maxflow(S, T);
    i64 maxProfit = totalPositive - minCut;

    cout << "Maximum profit: " << maxProfit << nl;

    // Find selected projects
    auto selected = dinic.mincut(S);
    cout << "Selected projects: ";
    for (int i = 0; i < n; i++) {
        if (selected[i+1]) cout << i+1 << " ";
    }
    cout << nl;
}

/*
Input: 1\n4 2\n5 -3 8 -2\n1 2\n3 4
Projects: 1(+5), 2(-3), 3(+8), 4(-2)
Dep: 1→2 (doing 1 requires 2), 3→4 (doing 3 requires 4)
Best: do {1,2} for 5-3=2, do {3,4} for 8-2=6. Total = 8.
Output: Maximum profit: 8
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

