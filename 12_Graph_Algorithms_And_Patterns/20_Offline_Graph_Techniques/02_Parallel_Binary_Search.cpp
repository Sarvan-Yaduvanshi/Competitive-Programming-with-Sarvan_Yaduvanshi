/*
╔══════════════════════════════════════════════════════════════════╗
║         02 — PARALLEL BINARY SEARCH ON GRAPH                    ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
CONCEPT
═══════════════════════════════════════════════════════════════════

Problem: For each query, find the MINIMUM weight threshold W such
that u and v become connected using edges with weight ≤ W.

Naive: Binary search per query × DSU per check = O(Q × E log E × α)
PBS: Binary search ALL queries simultaneously = O((Q + E) × log E × α)

ALGORITHM:
1. Sort edges by weight
2. All queries start with search range [0, m-1]
3. For each iteration:
   a. Group queries by their midpoint
   b. Process edges 0..mid, check which queries are satisfied
   c. Narrow search range for each query
4. Repeat O(log m) times

Time: O((Q + E) × log E × α(V))

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
#define sz(x) ((int)(x).size())
#define nl '\n'

struct DSU {
    vec<int> p, rk;
    vec<pair<int*,int>> history; // for rollback
    DSU(int n):p(n),rk(n,0){ iota(p.begin(),p.end(),0); }
    int find(int x){ while(p[x]!=x) x=p[x]; return x; }
    bool unite(int a,int b){
        a=find(a);b=find(b); if(a==b) return false;
        if(rk[a]<rk[b]) swap(a,b);
        history.push_back({&p[b],p[b]});
        history.push_back({&rk[a],rk[a]});
        p[b]=a; if(rk[a]==rk[b]) rk[a]++;
        return true;
    }
    int save(){ return sz(history); }
    void rollback(int s){ while(sz(history)>s){ auto [ptr,val]=history.back(); *ptr=val; history.pop_back(); } }
    bool connected(int a,int b){ return find(a)==find(b); }
};

struct Edge { int u,v; i64 w; bool operator<(const Edge&o)const{return w<o.w;} };

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vec<Edge> edges(m);
    for(auto&[u,v,w]:edges){ cin>>u>>v>>w; u--;v--; }
    sort(edges.begin(), edges.end());

    struct Query { int u, v, idx; };
    vec<Query> queries(q);
    for(int i=0;i<q;i++){
        cin>>queries[i].u>>queries[i].v;
        queries[i].u--; queries[i].v--;
        queries[i].idx = i;
    }

    // Parallel Binary Search
    vec<int> lo(q, 0), hi(q, m); // answer in range [lo, hi)
    // answer[i] = min index such that adding edges[0..ans] connects query

    for(int iter = 0; iter < 20; iter++) { // log2(m) iterations
        // Group queries by midpoint
        vec<vec<int>> bucket(m + 1);
        bool any = false;
        for(int i = 0; i < q; i++) {
            if(lo[i] < hi[i]) {
                int mid = (lo[i] + hi[i]) / 2;
                bucket[mid].push_back(i);
                any = true;
            }
        }
        if(!any) break;

        DSU dsu(n);
        int ei = 0;
        for(int mid = 0; mid < m; mid++) {
            dsu.unite(edges[mid].u, edges[mid].v);
            for(int qi : bucket[mid]) {
                if(dsu.connected(queries[qi].u, queries[qi].v)) {
                    hi[qi] = mid; // can do with fewer edges
                } else {
                    lo[qi] = mid + 1; // need more edges
                }
            }
        }
    }

    for(int i = 0; i < q; i++) {
        if(lo[i] >= m) cout << -1 << nl; // never connected
        else cout << edges[lo[i]].w << nl; // minimum weight threshold
    }
}

/*
Input: 1\n4 4 2\n1 2 3\n2 3 5\n3 4 1\n1 4 7\n1 4\n2 4
Output:
5  (need edges w≤5: (3,4,1),(1,2,3),(2,3,5) connects 1-4)
5  (same threshold connects 2-4)
*/

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin>>TC; while(TC--) solve();
}

