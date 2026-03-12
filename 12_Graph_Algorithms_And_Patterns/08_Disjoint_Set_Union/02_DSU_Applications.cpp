/*
╔══════════════════════════════════════════════════════════════════╗
║              02 — DSU APPLICATIONS                              ║
║              Connected components, Kruskal, Cycle detection     ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
APPLICATION 1: Dynamic Connected Components
  - Process edges online, answer "are u,v connected?" queries

APPLICATION 2: Kruskal's MST (see 07_MST)
  - Sort edges, union if different components

APPLICATION 3: Cycle Detection (undirected)
  - Adding edge (u,v): if find(u)==find(v) → CYCLE!

APPLICATION 4: Count/Track component sizes
  - Use DSU by size, track largest component

APPLICATION 5: Offline dynamic connectivity
  - Process queries in reverse (delete → union)
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

template<class T> using vec = vector<T>;
#define nl '\n'

struct DSU {
    vec<int> p, sz;
    int comps;
    DSU(int n) : p(n), sz(n, 1), comps(n) { iota(p.begin(), p.end(), 0); }
    int find(int x) { while(p[x]!=x) x=p[x]=p[p[x]]; return x; }
    bool unite(int a, int b) {
        a=find(a); b=find(b);
        if(a==b) return false;
        if(sz[a]<sz[b]) swap(a,b);
        p[b]=a; sz[a]+=sz[b]; comps--;
        return true;
    }
    int getSize(int x) { return sz[find(x)]; }
};

void solve() {
    int n, m;
    cin >> n >> m;

    DSU dsu(n);
    int cycleEdges = 0;
    int maxComp = 1;

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        if (!dsu.unite(u, v)) {
            cycleEdges++;
            cout << "Edge " << u+1 << "-" << v+1 << " creates a CYCLE" << nl;
        } else {
            maxComp = max(maxComp, dsu.getSize(u));
        }
    }

    cout << "Connected components: " << dsu.comps << nl;
    cout << "Largest component size: " << maxComp << nl;
    cout << "Cycle-creating edges: " << cycleEdges << nl;
    cout << "Is tree: " << (dsu.comps == 1 && cycleEdges == 0 ? "YES" : "NO") << nl;
}

/*
Input: 1\n5 5\n1 2\n2 3\n3 1\n4 5\n1 4
Output:
Edge 3-1 creates a CYCLE
Connected components: 1
Largest component size: 5
Cycle-creating edges: 1
Is tree: NO
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC; cin >> TC;
    while (TC--) solve();
}

