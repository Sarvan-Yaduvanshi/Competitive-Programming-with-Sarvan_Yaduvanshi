/*
╔══════════════════════════════════════════════════════════════════╗
║         04 — BICONNECTED COMPONENTS                             ║
║         Edge & vertex biconnected decomposition                 ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

A graph is BICONNECTED if it's connected and has NO articulation
points (removing any single vertex keeps it connected).

BICONNECTED COMPONENT (Block): maximal biconnected subgraph.

BLOCK-CUT TREE:
  - Each block = one node
  - Each articulation point = one node
  - Edge between block and articulation point if AP is in that block
  - Result is always a TREE!

═══════════════════════════════════════════════════════════════════
ALGORITHM (using Tarjan's DFS + stack)
═══════════════════════════════════════════════════════════════════

1. Run Tarjan's DFS, maintain edge stack
2. When u is root with ≥2 children, or non-root with low[v]≥disc[u]:
   Pop edges from stack until (u,v) → one biconnected component

Time: O(V+E)    Space: O(V+E)

═══════════════════════════════════════════════════════════════════
DRY RUN
═══════════════════════════════════════════════════════════════════

    1 ─── 2 ─── 5
    │     │
    3 ─── 4

Blocks:
  Block 1: {1,2,3,4} (edges: 1-2, 2-4, 4-3, 3-1) — biconnected
  Block 2: {2,5}     (edge: 2-5) — bridge forms its own block

Articulation point: vertex 2 (appears in both blocks)

Block-Cut Tree:
  [Block1] — (2) — [Block2]

═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
#endif

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
using namespace std;

template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int,int>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

int n, m;
vvec<int> adj;
vec<int> disc, low;
int timer_val;
stack<pii> edgeStack;
vvec<set<int>> bcc; // biconnected components (sets of vertices)

void dfs(int u, int parent) {
    disc[u] = low[u] = timer_val++;
    int children = 0;

    for (int v : adj[u]) {
        if (disc[v] == -1) {
            children++;
            edgeStack.push({u, v});
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            // Check if u is root/articulation point
            bool isRoot = (parent == -1 && children > 1);
            bool isAP = (parent != -1 && low[v] >= disc[u]);

            if (isRoot || isAP || (parent == -1 && children == 1 && edgeStack.size() > 0)) {
                // Pop edges to form biconnected component
                if (low[v] >= disc[u]) {
                    set<int> component;
                    while (true) {
                        auto [a, b] = edgeStack.top(); edgeStack.pop();
                        component.insert(a);
                        component.insert(b);
                        if (a == u && b == v) break;
                    }
                    bcc.pb(component);
                }
            }
        } else if (v != parent && disc[v] < disc[u]) {
            low[u] = min(low[u], disc[v]);
            edgeStack.push({u, v});
        }
    }
}

void solve() {
    cin >> n >> m;
    adj.assign(n, {});
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].pb(v); adj[v].pb(u);
    }

    disc.assign(n, -1);
    low.assign(n, 0);
    timer_val = 0;
    bcc.clear();
    while (!edgeStack.empty()) edgeStack.pop();

    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) {
            dfs(i, -1);
            // Pop remaining edges
            if (!edgeStack.empty()) {
                set<int> component;
                while (!edgeStack.empty()) {
                    auto [a, b] = edgeStack.top(); edgeStack.pop();
                    component.insert(a);
                    component.insert(b);
                }
                bcc.pb(component);
            }
        }
    }

    cout << "Biconnected Components: " << sz(bcc) << nl;
    for (int i = 0; i < sz(bcc); i++) {
        cout << "  Block " << i+1 << ": {";
        bool first = true;
        for (int v : bcc[i]) {
            if (!first) cout << ", ";
            cout << v+1;
            first = false;
        }
        cout << "}" << nl;
    }

    // Find articulation points (vertices in multiple blocks)
    vec<int> blockCount(n, 0);
    for (auto& comp : bcc) {
        for (int v : comp) blockCount[v]++;
    }
    cout << "Articulation points: ";
    bool any = false;
    for (int i = 0; i < n; i++) {
        if (blockCount[i] > 1) { cout << i+1 << " "; any = true; }
    }
    if (!any) cout << "(none)";
    cout << nl;
}

/*
Input: 1\n5 5\n1 2\n2 4\n4 3\n3 1\n2 5
Output:
Biconnected Components: 2
  Block 1: {1, 2, 3, 4}
  Block 2: {2, 5}
Articulation points: 2
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

