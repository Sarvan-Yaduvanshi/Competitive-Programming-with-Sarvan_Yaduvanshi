/*
╔══════════════════════════════════════════════════════════════════╗
║              01 — GRAPH THEORY FACTS & FORMULAS                 ║
║              Planarity, Complement, Ramsey, Turán               ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
1. EULER'S FORMULA FOR PLANAR GRAPHS
═══════════════════════════════════════════════════════════════════

V - E + F = 2    (V=vertices, E=edges, F=faces)

Corollaries:
  E ≤ 3V - 6     (for simple planar graph, V ≥ 3)
  E ≤ 2V - 4     (for bipartite planar graph)

K₅ and K₃,₃ are NOT planar (Kuratowski's theorem).

═══════════════════════════════════════════════════════════════════
2. GRAPH COMPLEMENT
═══════════════════════════════════════════════════════════════════

G' (complement of G): edge (u,v) exists in G' iff NOT in G.

Properties:
  |E(G)| + |E(G')| = n(n-1)/2
  G is connected OR G' is connected (or both)
  α(G) = ω(G') — independence number = clique of complement

═══════════════════════════════════════════════════════════════════
3. TURÁN'S THEOREM
═══════════════════════════════════════════════════════════════════

Max edges in graph with n vertices and no K_{r+1} (no clique of r+1):

  ex(n, K_{r+1}) = (1 - 1/r) × n² / 2

Example: Triangle-free (r=2): max edges = n²/4

The extremal graph is the complete r-partite graph with
parts as equal as possible (Turán graph).

═══════════════════════════════════════════════════════════════════
4. RAMSEY NUMBERS
═══════════════════════════════════════════════════════════════════

R(s,t) = smallest n such that any 2-coloring of edges of K_n
contains a red K_s or blue K_t.

Known values:
  R(3,3) = 6    R(3,4) = 9     R(3,5) = 14
  R(4,4) = 18   R(4,5) = 25

Upper bound: R(s,t) ≤ C(s+t-2, s-1)

═══════════════════════════════════════════════════════════════════
5. GRAPH ISOMORPHISM
═══════════════════════════════════════════════════════════════════

Two graphs are isomorphic if there's a bijection between vertices
preserving edges. In general, no known polynomial algorithm.

For trees: can use canonical form / hash for O(n log n) comparison.
For small graphs: check degree sequence first, then try matching.

═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
#endif
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using i64 = long long;
#define nl '\n'

void solve() {
    int n, m;
    cin >> n >> m;

    // Check planarity (necessary condition)
    cout << "Vertices: " << n << ", Edges: " << m << nl;

    if (n >= 3) {
        bool couldBePlanar = (m <= 3 * n - 6);
        cout << "Could be planar (E ≤ 3V-6 = " << 3*n-6 << "): "
             << (couldBePlanar ? "YES" : "NO") << nl;
    }

    // Complement edges
    i64 compEdges = (i64)n * (n - 1) / 2 - m;
    cout << "Complement has " << compEdges << " edges" << nl;

    // Max triangle-free edges (Turán, r=2)
    i64 maxTriangleFree = (i64)n * n / 4;
    cout << "Max triangle-free edges: " << maxTriangleFree << nl;
    if (m > maxTriangleFree) {
        cout << "Graph MUST contain a triangle (by Turán)" << nl;
    }

    // Euler's formula
    if (m <= 3 * n - 6 && n >= 3) {
        int faces = 2 - n + m;  // F = 2 - V + E (if planar)
        cout << "If planar, faces = " << faces << nl;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

