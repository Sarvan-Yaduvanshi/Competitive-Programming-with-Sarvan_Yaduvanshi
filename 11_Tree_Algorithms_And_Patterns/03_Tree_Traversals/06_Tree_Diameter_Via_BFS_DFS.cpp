/*
╔══════════════════════════════════════════════════════════════════╗
║       06 — TREE DIAMETER (Two-BFS & DFS Methods)                ║
║       Zero to GM Level — Tree Traversals                         ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 WHAT IS DIAMETER?
═══════════════════════════════════════════════════════════════════

 DIAMETER = longest path between any two nodes in the tree
           (measured in number of edges)

 Also called the "width" of the tree.

 Tree:
              1
            /   \
           2     3
          / \     \
         4   5     6
        /
       7

 Longest path: 7 → 4 → 2 → 1 → 3 → 6 = 5 edges
 DIAMETER = 5

═══════════════════════════════════════════════════════════════════
 METHOD 1: TWO-BFS (Most intuitive!)
═══════════════════════════════════════════════════════════════════

 Algorithm:
   1. BFS from any node → find the FARTHEST node (call it A)
   2. BFS from A → find the FARTHEST node (call it B)
   3. Distance(A, B) = DIAMETER

 WHY IT WORKS:
   - Starting from any node, the farthest node must be one end
     of the diameter path.
   - From that end, the farthest node is the other end.

 DRY RUN:
 ─────────
 Tree:
              1
            /   \
           2     3
          / \     \
         4   5     6
        /
       7

 Step 1: BFS from node 1
   dist[1]=0, dist[2]=1, dist[3]=1, dist[4]=2, dist[5]=2,
   dist[6]=2, dist[7]=3
   Farthest from 1 = node 7 (distance 3)

 Step 2: BFS from node 7
   dist[7]=0, dist[4]=1, dist[2]=2, dist[1]=3, dist[5]=3,
   dist[3]=4, dist[6]=5
   Farthest from 7 = node 6 (distance 5)

 DIAMETER = 5 ✅

═══════════════════════════════════════════════════════════════════
 METHOD 2: DFS-BASED (Tree DP)
═══════════════════════════════════════════════════════════════════

 For each node v, compute:
   depth[v] = max depth of any path going DOWN from v

 Diameter through v = depth(left subtree) + depth(right subtree)
 Answer = max over all nodes v of (sum of two deepest children paths)

 More precisely:
   For each node v, among all its children, take the two largest
   depth values: d1, d2
   Candidate diameter = d1 + d2 (the path goes down one child,
   through v, and down another child)

 DRY RUN:
 ─────────
 Tree:
              1
            /   \
           2     3
          / \     \
         4   5     6
        /
       7

 DFS postorder:
   dfs(7): leaf → depth[7] = 0
   dfs(4): children depths = [depth[7]+1] = [1] → depth[4] = 1
           only 1 child → diameter candidate = 1 (just the chain)
   dfs(5): leaf → depth[5] = 0
   dfs(2): children depths = [depth[4]+1, depth[5]+1] = [2, 1]
           d1=2, d2=1 → candidate = 2+1 = 3
           depth[2] = max(2, 1) = 2
   dfs(6): leaf → depth[6] = 0
   dfs(3): children depths = [depth[6]+1] = [1]
           depth[3] = 1
   dfs(1): children depths = [depth[2]+1, depth[3]+1] = [3, 2]
           d1=3, d2=2 → candidate = 3+2 = 5 ✅
           depth[1] = 3

 DIAMETER = max(3, 5) = 5 ✅

 The diameter path: 7→4→2→1→3→6 (length 5)

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌──────────────────────────┬────────────┬──────────────┐
 │ Method                   │ Time       │ Space        │
 ├──────────────────────────┼────────────┼──────────────┤
 │ Two-BFS                  │ O(N)       │ O(N)         │
 │ DFS (Tree DP)            │ O(N)       │ O(N)         │
 └──────────────────────────┴────────────┴──────────────┘

 Both are O(N). DFS method also finds the actual diameter path.

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

vvec<int> adj;

// ═══════════════════════════════════════════════════════════════
// METHOD 1: TWO-BFS DIAMETER
// ═══════════════════════════════════════════════════════════════

// BFS from source, return (farthest node, distance to it)
pii bfs(int src, int n) {
    vec<int> dist(n + 1, -1);
    queue<int> q;
    dist[src] = 0;
    q.push(src);

    int farthest = src, maxDist = 0;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int u : adj[v]) {
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                q.push(u);
                if (dist[u] > maxDist) {
                    maxDist = dist[u];
                    farthest = u;
                }
            }
        }
    }
    return {farthest, maxDist};
}

int diameterTwoBFS(int n) {
    // Step 1: BFS from any node (use node 1) → find farthest
    auto [nodeA, distA] = bfs(1, n);
    // Step 2: BFS from nodeA → find farthest (other end of diameter)
    auto [nodeB, diameter] = bfs(nodeA, n);

    cout << "  Two-BFS: endpoint A = " << nodeA
         << ", endpoint B = " << nodeB << nl;

    return diameter;
}

// ═══════════════════════════════════════════════════════════════
// METHOD 2: DFS-BASED DIAMETER (Tree DP)
// ═══════════════════════════════════════════════════════════════

int diameterDFS_ans;

// Returns the depth of the deepest path going down from v
int dfsForDiameter(int v, int par) {
    int d1 = 0, d2 = 0; // two deepest paths among children

    for (int u : adj[v]) {
        if (u == par) continue;
        int childDepth = 1 + dfsForDiameter(u, v);

        if (childDepth >= d1) {
            d2 = d1;
            d1 = childDepth;
        } else if (childDepth > d2) {
            d2 = childDepth;
        }
    }

    // Diameter through v = d1 + d2
    diameterDFS_ans = max(diameterDFS_ans, d1 + d2);

    return d1; // return the deepest path going down
}

int diameterDFS(int n) {
    diameterDFS_ans = 0;
    dfsForDiameter(1, -1);
    return diameterDFS_ans;
}

void solve() {
    int n;
    cin >> n;

    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    cout << "Method 1 (Two-BFS):" << nl;
    int d1 = diameterTwoBFS(n);
    cout << "  Diameter = " << d1 << nl;

    cout << nl << "Method 2 (DFS / Tree DP):" << nl;
    int d2 = diameterDFS(n);
    cout << "  Diameter = " << d2 << nl;

    assert(d1 == d2);
    cout << nl << "Both methods agree! Diameter = " << d1 << nl;
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
1
7
1 2
1 3
2 4
2 5
4 7
3 6

Tree:
         1
        / \
       2   3
      / \   \
     4   5   6
    /
   7

Output:
Method 1 (Two-BFS):
  Two-BFS: endpoint A = 7, endpoint B = 6
  Diameter = 5

Method 2 (DFS / Tree DP):
  Diameter = 5

Both methods agree! Diameter = 5

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Diameter = longest path in tree (in edges)
 ✅ Two-BFS: BFS from any node → farthest → BFS again → diameter
 ✅ DFS: for each node, sum two deepest children paths
 ✅ Both methods are O(N)
 ✅ Diameter is used in MANY problems: radius, center, etc.
 ✅ CSES problem: "Tree Diameter" — direct application
═══════════════════════════════════════════════════════════════════
*/

