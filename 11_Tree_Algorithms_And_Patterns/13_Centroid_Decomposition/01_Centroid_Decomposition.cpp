/*
╔══════════════════════════════════════════════════════════════════╗
║  01 — CENTROID DECOMPOSITION                                    ║
║  Zero to GM Level — Centroid Decomposition                       ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 WHAT IS A CENTROID?
═══════════════════════════════════════════════════════════════════

 Centroid of a tree = node whose removal splits the tree into
 components of size ≤ N/2.

 Every tree has at least one centroid (at most two).

═══════════════════════════════════════════════════════════════════
 CENTROID DECOMPOSITION — THE IDEA
═══════════════════════════════════════════════════════════════════

 1. Find centroid C of the tree
 2. Remove C — splits into components
 3. Recursively find centroid of each component
 4. Build a "centroid tree" where C is parent of sub-centroids

 The centroid tree has height O(log N)!
 Every path in original tree passes through O(log N) centroids.

═══════════════════════════════════════════════════════════════════
 DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree (N=7):
         1
        / \
       2   3
      / \   \
     4   5   6
    /
   7

 Sub sizes from root: sub[1]=7, sub[2]=5, sub[3]=2, sub[4]=2, etc.

 Find centroid: for each node v, max component after removal =
   max(N - sub[v], max_child_sub)
   Node 2: components = {4,7}, {5}, {1,3,6} → sizes 2,1,3 → max=3 ≤ 7/2? 3≤3.5 ✅
   Centroid = 2

 Remove 2. Components: {4,7}, {5}, {1,3,6}
   Centroid of {4,7}: 4
   Centroid of {5}: 5
   Centroid of {1,3,6}: 3 or 1

 Centroid tree:
         2
       / | \
      4  5  1(or 3)
      |     |
      7     ...

 Height = O(log N) ✅

═══════════════════════════════════════════════════════════════════
 APPLICATIONS
═══════════════════════════════════════════════════════════════════

 ✅ Count paths of length K in tree
 ✅ Distance queries (offline)
 ✅ Closest marked node query
 ✅ Tree divide & conquer

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌──────────────────────────────┬────────────────┬──────────────┐
 │ Operation                    │ Time           │ Space        │
 ├──────────────────────────────┼────────────────┼──────────────┤
 │ Build centroid decomposition │ O(N log N)     │ O(N)         │
 │ Centroid tree height         │ O(log N)       │ —            │
 │ Process all paths through C  │ O(sub_size)    │ varies       │
 └──────────────────────────────┴────────────────┴──────────────┘

═══════════════════════════════════════════════════════════════════
 CODE
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

const int MAXN = 200005;

vvec<int> adj;
int sub_sz[MAXN];
bool removed[MAXN]; // is this node removed (centroid already processed)?
int centroid_par[MAXN]; // parent in centroid tree

// ═══════════════════════════════════════════════════════════
// Step 1: Compute subtree sizes (only non-removed nodes)
// ═══════════════════════════════════════════════════════════
void computeSize(int v, int par) {
    sub_sz[v] = 1;
    for (int u : adj[v]) {
        if (u == par || removed[u]) continue;
        computeSize(u, v);
        sub_sz[v] += sub_sz[u];
    }
}

// ═══════════════════════════════════════════════════════════
// Step 2: Find centroid of the component containing v
// ═══════════════════════════════════════════════════════════
int findCentroid(int v, int par, int treeSize) {
    for (int u : adj[v]) {
        if (u == par || removed[u]) continue;
        if (sub_sz[u] > treeSize / 2)
            return findCentroid(u, v, treeSize);
    }
    return v;
}

// ═══════════════════════════════════════════════════════════
// Step 3: Build centroid decomposition recursively
// ═══════════════════════════════════════════════════════════
void buildCentroidDecomp(int v, int cPar) {
    computeSize(v, -1);
    int c = findCentroid(v, -1, sub_sz[v]);

    centroid_par[c] = cPar;
    removed[c] = true;

    for (int u : adj[c]) {
        if (removed[u]) continue;
        buildCentroidDecomp(u, c);
    }
}

void solve() {
    int n; cin >> n;
    adj.assign(n + 1, {});
    memset(removed, false, sizeof(removed));
    memset(centroid_par, 0, sizeof(centroid_par));

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    buildCentroidDecomp(1, 0);

    // Print centroid tree
    cout << "Centroid Tree:" << nl;
    cout << "Node | Centroid Parent" << nl;
    cout << "─────┼────────────────" << nl;
    for (int i = 1; i <= n; i++) {
        cout << "  " << i << "  | "
             << (centroid_par[i] == 0 ? "ROOT" : to_string(centroid_par[i])) << nl;
    }

    // Print centroid tree structure
    cout << nl << "Centroid tree children:" << nl;
    vvec<int> ctree(n + 1);
    int root = -1;
    for (int i = 1; i <= n; i++) {
        if (centroid_par[i] == 0) root = i;
        else ctree[centroid_par[i]].pb(i);
    }

    for (int i = 1; i <= n; i++) {
        if (sz(ctree[i]) > 0) {
            cout << "  " << i << " → {";
            for (int j = 0; j < sz(ctree[i]); j++) {
                if (j) cout << ", ";
                cout << ctree[i][j];
            }
            cout << "}" << nl;
        }
    }
    cout << "  Root = " << root << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1; cin >> TC;
    while (TC--) solve();
    return 0;
}

/*
═══════════════════════════════════════════════════════════════════
 SAMPLE I/O
═══════════════════════════════════════════════════════════════════

Input:
1
7
1 2
1 3
2 4
2 5
3 6
4 7

Output shows centroid tree structure.
Centroid tree has height O(log 7) ≈ 3.

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Centroid = node that minimizes max component after removal
 ✅ Centroid tree height = O(log N)
 ✅ Build: find centroid → remove → recurse on components
 ✅ Every path passes through O(log N) centroids → efficient queries
 ✅ Applications: path counting, distance queries, divide & conquer
═══════════════════════════════════════════════════════════════════
*/

