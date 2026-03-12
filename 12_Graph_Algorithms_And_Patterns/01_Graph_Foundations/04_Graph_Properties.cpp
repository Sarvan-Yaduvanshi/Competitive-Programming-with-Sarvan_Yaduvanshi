/*
╔══════════════════════════════════════════════════════════════════╗
║              04 — GRAPH PROPERTIES                              ║
║              Handshaking, Tree Props, Complete Graph, etc.       ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
1. HANDSHAKING LEMMA
═══════════════════════════════════════════════════════════════════

  ∑ deg(v) = 2|E|    (for undirected graphs)

  Proof: Each edge (u,v) contributes 1 to deg(u) and 1 to deg(v).

  Corollary: Number of odd-degree vertices is always EVEN.

═══════════════════════════════════════════════════════════════════
2. TREE PROPERTIES
═══════════════════════════════════════════════════════════════════

  A tree with n vertices has:
    ✅ Exactly n-1 edges
    ✅ Exactly ONE path between any two vertices
    ✅ Connected
    ✅ Acyclic
    ✅ Removing any edge disconnects it
    ✅ Adding any edge creates exactly ONE cycle

  ANY TWO of these three imply the third:
    (a) Connected
    (b) Acyclic
    (c) |E| = |V| - 1

═══════════════════════════════════════════════════════════════════
3. COMPLETE GRAPH K_n
═══════════════════════════════════════════════════════════════════

  Every pair of vertices is connected.

  K_1: •        (0 edges)
  K_2: •──•     (1 edge)
  K_3: Triangle  (3 edges)
  K_4: 4 vertices, every pair connected (6 edges)
  K_n: n*(n-1)/2 edges

  K_3:      K_4:
   1          1
  / \       / |\
 2───3     2──3 |
           |  |/
           4──┘

═══════════════════════════════════════════════════════════════════
4. GRAPH CONNECTIVITY PROPERTIES
═══════════════════════════════════════════════════════════════════

  CONNECTED: There's a path between every pair of vertices.

  BRIDGE: An edge whose removal disconnects the graph.

  ARTICULATION POINT: A vertex whose removal disconnects the graph.

  k-CONNECTED: Graph remains connected after removing any k-1 vertices.

  k-EDGE-CONNECTED: Graph remains connected after removing any k-1 edges.

═══════════════════════════════════════════════════════════════════
5. IMPORTANT FORMULAS
═══════════════════════════════════════════════════════════════════

  ┌────────────────────────────────────────────────────────────┐
  │  Property                │  Formula                       │
  ├──────────────────────────┼────────────────────────────────┤
  │  Max edges (undirected)  │  n*(n-1)/2                     │
  │  Max edges (directed)    │  n*(n-1)                       │
  │  Tree edges              │  n-1                           │
  │  Forest edges (k trees)  │  n-k                           │
  │  Euler's formula (planar)│  V - E + F = 2                 │
  │  Sum of degrees          │  2*E                           │
  │  Bipartite max edges     │  ⌊n²/4⌋ (Turán for K_3-free) │
  └────────────────────────────────────────────────────────────┘

═══════════════════════════════════════════════════════════════════
6. DEGREE SEQUENCE
═══════════════════════════════════════════════════════════════════

  The degree sequence is the sorted list of all vertex degrees.

  ERDŐS–GALLAI THEOREM: A sequence d₁ ≥ d₂ ≥ ... ≥ dₙ is a
  valid degree sequence of a simple graph iff:
    1. Sum is even
    2. For each k: ∑ᵢ₌₁ᵏ dᵢ ≤ k(k-1) + ∑ᵢ₌ₖ₊₁ⁿ min(dᵢ, k)

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

#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

template<class T>
void read(vec<T> &v) { for (auto &x : v) cin >> x; }

// Erdős–Gallai check: is a degree sequence valid?
bool isValidDegreeSequence(vec<int> deg) {
    sort(deg.rbegin(), deg.rend());
    int n = sz(deg);
    i64 sum = 0;
    for (int d : deg) sum += d;
    if (sum % 2 != 0) return false;  // sum must be even

    i64 leftSum = 0;
    for (int k = 1; k <= n; k++) {
        leftSum += deg[k - 1];
        i64 rightSum = (i64)k * (k - 1);
        for (int i = k; i < n; i++) {
            rightSum += min(deg[i], k);
        }
        if (leftSum > rightSum) return false;
    }
    return true;
}

void solve() {
    int n;
    cin >> n;
    vec<int> deg(n);
    read(deg);

    cout << "Degree sequence: ";
    vec<int> sorted_deg = deg;
    sort(sorted_deg.rbegin(), sorted_deg.rend());
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << ", ";
        cout << sorted_deg[i];
    }
    cout << nl;

    i64 sum = 0;
    for (int d : deg) sum += d;
    cout << "Sum of degrees: " << sum << nl;
    cout << "Number of edges: " << sum / 2 << nl;

    if (isValidDegreeSequence(deg)) {
        cout << "This IS a valid degree sequence (Erdős–Gallai)." << nl;
    } else {
        cout << "This is NOT a valid degree sequence." << nl;
    }

    // Check if it could be a tree: sum = 2*(n-1), all degrees >= 1
    bool couldBeTree = (sum == 2 * (n - 1));
    for (int d : deg) if (d == 0) couldBeTree = false;
    if (couldBeTree) {
        cout << "This could represent a TREE." << nl;
    }
}

/*
═══════════════════════════════════════════════════════════════════
SAMPLE INPUT/OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
1
5
3 2 2 1 2

Output:
Degree sequence: 3, 2, 2, 2, 1
Sum of degrees: 10
Number of edges: 5
This IS a valid degree sequence (Erdős–Gallai).

═══════════════════════════════════════════════════════════════════
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    return 0;
}

