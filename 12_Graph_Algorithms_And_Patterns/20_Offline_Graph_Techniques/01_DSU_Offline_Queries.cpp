/*
╔══════════════════════════════════════════════════════════════════╗
║         01 — DSU OFFLINE QUERIES                                ║
║         Process connectivity queries offline with sorted edges  ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
PROBLEM PATTERN
═══════════════════════════════════════════════════════════════════

Given weighted edges and queries "are u,v connected using only
edges with weight ≤ W?", process ALL queries offline:

1. Sort edges by weight
2. Sort queries by weight threshold
3. Process queries in order: add edges until threshold, answer query

═══════════════════════════════════════════════════════════════════
EXAMPLE
═══════════════════════════════════════════════════════════════════

Edges: (1,2,3), (2,3,5), (1,3,7), (3,4,1)
Queries:
  Q1: are 1,4 connected with edges ≤ 4?
  Q2: are 1,3 connected with edges ≤ 4?
  Q3: are 1,4 connected with edges ≤ 6?

Sort edges: (3,4,1), (1,2,3), (2,3,5), (1,3,7)
Sort queries: Q1(W=4), Q2(W=4), Q3(W=6)

Process Q1,Q2 (W=4): add edges w≤4: (3,4,1),(1,2,3)
  Components: {1,2},{3,4}
  Q1(1,4): NO  Q2(1,3): NO

Process Q3 (W=6): add (2,3,5)
  Components: {1,2,3,4}
  Q3(1,4): YES

Time: O((E+Q) log(E+Q) + E α(V))
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
#endif
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
#define nl '\n'

struct DSU {
    vec<int> p, r;
    DSU(int n):p(n),r(n,0){ iota(p.begin(),p.end(),0); }
    int find(int x){ while(p[x]!=x) x=p[x]=p[p[x]]; return x; }
    bool unite(int a,int b){ a=find(a);b=find(b); if(a==b) return false;
        if(r[a]<r[b]) swap(a,b); p[b]=a; if(r[a]==r[b]) r[a]++; return true; }
    bool connected(int a,int b){ return find(a)==find(b); }
};

struct Edge { int u,v; i64 w; bool operator<(const Edge& o)const{return w<o.w;} };

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vec<Edge> edges(m);
    for(auto&[u,v,w]:edges){ cin>>u>>v>>w; u--;v--; }
    sort(edges.begin(), edges.end());

    struct Query { int u, v, idx; i64 w; };
    vec<Query> queries(q);
    for(int i=0;i<q;i++){
        cin>>queries[i].u>>queries[i].v>>queries[i].w;
        queries[i].u--; queries[i].v--;
        queries[i].idx = i;
    }
    sort(queries.begin(), queries.end(), [](const Query&a,const Query&b){ return a.w<b.w; });

    DSU dsu(n);
    vec<bool> ans(q);
    int ei = 0;

    for(auto& [u,v,idx,w] : queries) {
        // Add all edges with weight ≤ w
        while(ei < m && edges[ei].w <= w) {
            dsu.unite(edges[ei].u, edges[ei].v);
            ei++;
        }
        ans[idx] = dsu.connected(u, v);
    }

    for(int i=0;i<q;i++) cout << (ans[i] ? "YES" : "NO") << nl;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin>>TC; while(TC--) solve();
}

