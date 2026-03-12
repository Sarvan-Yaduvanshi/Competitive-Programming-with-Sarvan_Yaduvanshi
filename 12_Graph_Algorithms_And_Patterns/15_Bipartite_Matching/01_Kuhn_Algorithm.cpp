/*
╔══════════════════════════════════════════════════════════════════╗
║              01 — KUHN'S ALGORITHM (Hungarian Matching)         ║
║              Maximum Bipartite Matching via DFS                 ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

A MATCHING in a graph is a set of edges with no shared vertices.
MAXIMUM MATCHING = matching with the largest number of edges.

In a BIPARTITE graph (left set L, right set R):
  We try to match each left vertex to exactly one right vertex.

KUHN'S ALGORITHM:
  For each left vertex u:
    Try to find an AUGMENTING PATH using DFS.
    An augmenting path alternates: unmatched→matched→unmatched→...
    If found, flip all edges on the path (matched↔unmatched).

═══════════════════════════════════════════════════════════════════
DRY RUN
═══════════════════════════════════════════════════════════════════

Left: {A, B, C}    Right: {1, 2, 3}
Edges: A-1, A-2, B-1, B-3, C-2

Step 1: Try matching A
  A→1: 1 is free → match A-1. Matching: {A-1}

Step 2: Try matching B
  B→1: 1 matched to A. Try to rematch A.
    A→2: 2 is free → match A-2.
  Now 1 is free → match B-1. Matching: {A-2, B-1}

Step 3: Try matching C
  C→2: 2 matched to A. Try to rematch A.
    A→1: 1 matched to B. Try to rematch B.
      B→3: 3 is free → match B-3.
    Now 1 is free → match A-1.
  Now 2 is free → match C-2. Matching: {A-1, B-3, C-2}

Maximum matching = 3 (perfect matching!)

═══════════════════════════════════════════════════════════════════
COMPLEXITY
═══════════════════════════════════════════════════════════════════
  Time:  O(V × E)  — for each left vertex, DFS takes O(E)
  Space: O(V + E)

  For better complexity, use Hopcroft-Karp: O(E × √V)

═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

int nL, nR, m;  // left vertices, right vertices, edges
vvec<int> adj;   // adj[left_vertex] = list of right vertices
vec<int> matchL, matchR;  // matchL[l] = matched right, matchR[r] = matched left
vec<bool> used;

// Try to find augmenting path from left vertex u
bool tryKuhn(int u) {
    for (int v : adj[u]) {
        if (!used[v]) {
            used[v] = true;
            // v is free OR we can rematch the vertex currently matched to v
            if (matchR[v] == -1 || tryKuhn(matchR[v])) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}

void solve() {
    cin >> nL >> nR >> m;

    adj.assign(nL, {});
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].pb(v);
    }

    matchL.assign(nL, -1);
    matchR.assign(nR, -1);

    int matching = 0;
    for (int u = 0; u < nL; u++) {
        used.assign(nR, false);
        if (tryKuhn(u)) matching++;
    }

    cout << "Maximum matching: " << matching << nl;
    for (int u = 0; u < nL; u++) {
        if (matchL[u] != -1) {
            cout << "  L" << u+1 << " — R" << matchL[u]+1 << nl;
        }
    }
}

/*
═══════════════════════════════════════════════════════════════════
SAMPLE INPUT/OUTPUT

Input:
1
3 3 5
1 1
1 2
2 1
2 3
3 2

Output:
Maximum matching: 3
  L1 — R1
  L2 — R3
  L3 — R2
═══════════════════════════════════════════════════════════════════
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

