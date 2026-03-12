/*
╔══════════════════════════════════════════════════════════════════╗
║          01 — WHAT IS A TREE? DEFINITION & PROPERTIES            ║
║          Zero to GM Level — Tree Foundations                     ║
╚══════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS
─────────────────
 1. What is a Tree?
 2. Formal Definition
 3. Key Properties (with proof)
 4. Visual Examples
 5. Dry Run: Verify Tree Properties
 6. Complexity Analysis
 7. Code: Check if a graph is a tree

═══════════════════════════════════════════════════════════════════
 1. WHAT IS A TREE?
═══════════════════════════════════════════════════════════════════

 A TREE is a special kind of graph with these properties:
   ✅ Connected — you can reach any node from any other node
   ✅ Acyclic   — there are NO cycles (no way to go in a loop)

 Think of it like a family tree:
   - One ancestor at top (root)
   - Branches going down
   - No branch ever loops back up

═══════════════════════════════════════════════════════════════════
 2. FORMAL DEFINITION
═══════════════════════════════════════════════════════════════════

 A tree is an undirected graph G = (V, E) where:
   |V| = N  (number of nodes/vertices)
   |E| = N - 1  (number of edges)
   G is connected

 ANY TWO of these three conditions imply the third:
   (a) Connected
   (b) Acyclic
   (c) |E| = N - 1

 This means:
   - Connected + (N-1 edges) → Acyclic
   - Connected + Acyclic → (N-1 edges)
   - Acyclic + (N-1 edges) → Connected

═══════════════════════════════════════════════════════════════════
 3. KEY PROPERTIES
═══════════════════════════════════════════════════════════════════

 Property 1: N nodes, exactly N-1 edges
 ─────────────────────────────────────────
   Tree with 5 nodes → exactly 4 edges
   Tree with 1 node  → exactly 0 edges
   Tree with 2 nodes → exactly 1 edge

 Property 2: Unique path between any two nodes
 ─────────────────────────────────────────
   Between node u and node v, there is EXACTLY ONE path.
   (If there were two paths, there would be a cycle → contradiction)

 Property 3: Removing any edge disconnects the tree
 ─────────────────────────────────────────
   Every edge is a "bridge." Remove one → two components.

 Property 4: Adding any edge creates exactly one cycle
 ─────────────────────────────────────────
   Since there's already a unique path between u and v,
   adding edge (u,v) creates a cycle through that path.

═══════════════════════════════════════════════════════════════════
 4. VISUAL EXAMPLES
═══════════════════════════════════════════════════════════════════

 Example 1: A tree with 7 nodes and 6 edges
 ─────────────────────────────────────────
              1
            / | \
           2  3  4
          / \    |
         5   6   7

   Nodes: {1, 2, 3, 4, 5, 6, 7}  →  N = 7
   Edges: {(1,2),(1,3),(1,4),(2,5),(2,6),(4,7)}  →  E = 6  ✅ (N-1 = 6)
   Connected? YES ✅
   Cycles? NO ✅
   ⟹ This IS a tree!

 Example 2: NOT a tree (has a cycle)
 ─────────────────────────────────────────
              1
            / | \
           2  3  4
          / \ |
         5   6

   Edges: {(1,2),(1,3),(1,4),(2,5),(2,6),(3,6)}  →  E = 6
   N = 6, E = 6  → E ≠ N-1  ❌
   Cycle: 1→2→6→3→1 ❌
   ⟹ This is NOT a tree!

 Example 3: NOT a tree (disconnected)
 ─────────────────────────────────────────
         1        4
        / \       |
       2   3      5

   Nodes: {1,2,3,4,5}  →  N = 5
   Edges: {(1,2),(1,3),(4,5)}  →  E = 3
   E = 3 ≠ N-1 = 4  ❌
   Connected? NO (can't reach 4 from 1) ❌
   ⟹ This is NOT a tree! (It's a forest — collection of trees)

═══════════════════════════════════════════════════════════════════
 5. DRY RUN: VERIFY TREE PROPERTIES
═══════════════════════════════════════════════════════════════════

 Given: N = 5, Edges = {(1,2), (1,3), (2,4), (2,5)}

 Step 1: Check edge count
         E = 4, N-1 = 4  ✅

 Step 2: Build adjacency list
         1 → [2, 3]
         2 → [1, 4, 5]
         3 → [1]
         4 → [2]
         5 → [2]

 Step 3: BFS/DFS from node 1 to check connectivity
         Start: queue = [1], visited = {1}
         Pop 1: visit neighbors 2, 3
           queue = [2, 3], visited = {1, 2, 3}
         Pop 2: visit neighbors 4, 5 (1 already visited)
           queue = [3, 4, 5], visited = {1, 2, 3, 4, 5}
         Pop 3: neighbor 1 already visited
           queue = [4, 5]
         Pop 4: neighbor 2 already visited
           queue = [5]
         Pop 5: neighbor 2 already visited
           queue = []

         All 5 nodes visited ✅ → Connected!

 Step 4: Check for cycle
         Since E = N-1 AND connected → automatically acyclic ✅

 RESULT: This IS a tree! ✅

 Visualization of this tree:
              1
            /   \
           2     3
          / \
         4   5

═══════════════════════════════════════════════════════════════════
 6. COMPLEXITY ANALYSIS
═══════════════════════════════════════════════════════════════════

 ┌─────────────────────────┬────────────────┬─────────────────┐
 │ Operation               │ Time           │ Space           │
 ├─────────────────────────┼────────────────┼─────────────────┤
 │ Build adjacency list    │ O(N)           │ O(N)            │
 │ BFS/DFS to check tree   │ O(N)           │ O(N)            │
 │ Check edge count        │ O(1)           │ O(1)            │
 │ Overall: Is it a tree?  │ O(N)           │ O(N)            │
 └─────────────────────────┴────────────────┴─────────────────┘

 Why O(N) and not O(N+E)?
   Because in a tree, E = N-1 → O(N + N-1) = O(N)

═══════════════════════════════════════════════════════════════════
 7. CODE: CHECK IF A GRAPH IS A TREE
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
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

template<class T>
void read(vec<T> &v) {
    for (auto &x : v) cin >> x;
}
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

// ─────────────────────────────────────────────────────────────
// Function: Check if a graph with N nodes and given edges is a tree
// Method:   1. Check E == N-1
//           2. BFS from node 1, check all nodes visited (connected)
// ─────────────────────────────────────────────────────────────
bool isTree(int n, vvec<int>& adj, int edgeCount) {
    // Property: A tree must have exactly N-1 edges
    if (edgeCount != n - 1) return false;

    // BFS to check connectivity
    vec<bool> visited(n + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    int count = 1;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                count++;
                q.push(neighbor);
            }
        }
    }

    // All nodes must be reachable
    return count == n;
}

void solve() {
    int n, m;
    cin >> n >> m;

    // Build adjacency list
    vvec<int> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    if (isTree(n, adj, m)) {
        cout << "YES — This is a tree!" << nl;
        cout << "Nodes: " << n << ", Edges: " << m << " (= N-1 = " << n-1 << ")" << nl;
    } else {
        cout << "NO — This is NOT a tree!" << nl;
        if (m != n - 1) {
            cout << "Reason: Edge count " << m << " != N-1 = " << n-1 << nl;
        } else {
            cout << "Reason: Graph is not connected" << nl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    int TC = 1;
    cin >> TC;
    while (TC--) solve();

    return 0;
}

/*
═══════════════════════════════════════════════════════════════════
 SAMPLE INPUT / OUTPUT
═══════════════════════════════════════════════════════════════════

Input:
3
5 4
1 2
1 3
2 4
2 5
4 4
1 2
2 3
3 4
4 1
5 3
1 2
1 3
4 5

Output:
YES — This is a tree!
Nodes: 5, Edges: 4 (= N-1 = 4)
NO — This is NOT a tree!
Reason: Edge count 4 != N-1 = 3
NO — This is NOT a tree!
Reason: Graph is not connected

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Tree = Connected + Acyclic undirected graph
 ✅ N nodes → exactly N-1 edges
 ✅ Unique path between every pair of nodes
 ✅ Removing any edge disconnects the tree
 ✅ Adding any edge creates exactly one cycle
 ✅ To verify: check E == N-1 AND connectivity (BFS/DFS)
═══════════════════════════════════════════════════════════════════
*/

