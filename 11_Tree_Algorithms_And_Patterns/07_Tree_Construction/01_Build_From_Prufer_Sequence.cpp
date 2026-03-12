/*
╔══════════════════════════════════════════════════════════════════╗
║  01 — PRÜFER SEQUENCE ↔ LABELED TREE                           ║
║  Zero to GM Level — Tree Construction                            ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 CAYLEY'S FORMULA: # of labeled trees on N nodes = N^(N-2)
═══════════════════════════════════════════════════════════════════

 N=3: 3^1 = 3 trees: (1-2-3), (1-3-2), (2-1-3)
 N=4: 4^2 = 16 labeled trees

 PRÜFER SEQUENCE: bijection between labeled trees and sequences
 of length N-2 from {1..N}

═══════════════════════════════════════════════════════════════════
 TREE → PRÜFER SEQUENCE — DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree (N=5):
   Edges: (1,2), (1,3), (2,4), (2,5)

        1
       / \
      2   3
     / \
    4   5

 Algorithm: Repeatedly remove the leaf with smallest label,
 record its neighbor.

 Step 1: Leaves = {3, 4, 5}. Smallest = 3. Neighbor = 1. Remove 3.
         Sequence: [1]
         Remaining: 1—2, 2—4, 2—5

 Step 2: Leaves = {4, 5}. Smallest = 4. Neighbor = 2. Remove 4.
         Sequence: [1, 2]
         Remaining: 1—2, 2—5

 Step 3: Leaves = {1, 5}. Smallest = 1. Neighbor = 2. Remove 1.
         Sequence: [1, 2, 2]
         Remaining: 2—5

 Stop (2 nodes left). Prüfer = [1, 2, 2] (length N-2 = 3) ✅

═══════════════════════════════════════════════════════════════════
 PRÜFER SEQUENCE → TREE — DRY RUN
═══════════════════════════════════════════════════════════════════

 Prüfer = [1, 2, 2], N=5

 Step 1: Count occurrences of each node in Prüfer
         degree[i] = (count in prüfer) + 1
         occ: 1→1, 2→2 → degree: 1→2, 2→3, 3→1, 4→1, 5→1

 Step 2: ptr = smallest node with degree 1 (leaf) = 3
 Step 3: Process prüfer sequence:
   prüfer[0]=1: connect leaf=3 to 1. degree[3]-- → 0, degree[1]-- → 1
                ptr was 3, next smallest degree-1 node: check 1 (degree=1→ yes, 1<ptr+1?)
                Edge: (3, 1)

   prüfer[1]=2: leaf ptr=1 (smallest deg-1). connect 1 to 2.
                degree[1]-- → 0, degree[2]-- → 2
                Edge: (1, 2)

   prüfer[2]=2: leaf ptr=4 (smallest deg-1). connect 4 to 2.
                degree[4]-- → 0, degree[2]-- → 1
                Edge: (4, 2)

 Step 4: Two nodes left with degree 1: {2, 5}. Connect them.
         Edge: (2, 5)

 Edges: (3,1), (1,2), (4,2), (2,5) ✅ Same tree!

═══════════════════════════════════════════════════════════════════
 CODE — O(N log N) with set, or O(N) with pointer trick
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
using pii = pair<int, int>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

// ═══════════════════════════════════════════════════════════
// TREE → PRÜFER SEQUENCE (O(N) with pointer trick)
// ═══════════════════════════════════════════════════════════
vec<int> treeToPrufer(int n, vvec<int>& adj) {
    vec<int> degree(n + 1, 0);
    for (int i = 1; i <= n; i++) degree[i] = sz(adj[i]);

    vec<int> prufer;
    int ptr = 1;
    // Find first leaf
    while (degree[ptr] != 1) ptr++;
    int leaf = ptr;

    for (int i = 0; i < n - 2; i++) {
        // Find the neighbor of leaf (the one with degree > 0)
        int next = -1;
        for (int u : adj[leaf]) {
            if (degree[u] > 0) { next = u; break; }
        }
        prufer.pb(next);
        degree[leaf]--;
        degree[next]--;

        if (degree[next] == 1 && next < ptr) {
            leaf = next; // reuse without scanning
        } else {
            ptr++;
            while (ptr <= n && degree[ptr] != 1) ptr++;
            leaf = ptr;
        }
    }
    return prufer;
}

// ═══════════════════════════════════════════════════════════
// PRÜFER SEQUENCE → TREE (O(N) with pointer trick)
// ═══════════════════════════════════════════════════════════
vec<pii> pruferToTree(int n, vec<int>& prufer) {
    vec<int> degree(n + 1, 1);
    for (int x : prufer) degree[x]++;

    vec<pii> edges;
    int ptr = 1;
    while (degree[ptr] != 1) ptr++;
    int leaf = ptr;

    for (int x : prufer) {
        edges.pb({leaf, x});
        degree[leaf]--;
        degree[x]--;
        if (degree[x] == 1 && x < ptr) {
            leaf = x;
        } else {
            ptr++;
            while (ptr <= n && degree[ptr] != 1) ptr++;
            leaf = ptr;
        }
    }
    // Last edge: two remaining nodes with degree 1
    edges.pb({leaf, n}); // node n always remains
    return edges;
}

void solve() {
    int n;
    cin >> n;

    vvec<int> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    // Tree → Prüfer
    vec<int> prufer = treeToPrufer(n, adj);
    cout << "Prüfer sequence: ";
    for (int x : prufer) cout << x << " ";
    cout << nl;

    // Prüfer → Tree (verify roundtrip)
    vec<pii> edges = pruferToTree(n, prufer);
    cout << "Reconstructed edges: ";
    for (auto [u, v] : edges) cout << "(" << u << "," << v << ") ";
    cout << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1; cin >> TC;
    while (TC--) solve();
    return 0;
}

/*
 Input: 1\n5\n1 2\n1 3\n2 4\n2 5
 Output:
 Prüfer sequence: 1 2 2
 Reconstructed edges: (3,1) (1,2) (4,2) (2,5)

 Time: O(N) | Space: O(N)

 KEY: Cayley's formula N^(N-2) — # labeled trees with N vertices.
      Prüfer sequence gives a constructive proof.
*/

