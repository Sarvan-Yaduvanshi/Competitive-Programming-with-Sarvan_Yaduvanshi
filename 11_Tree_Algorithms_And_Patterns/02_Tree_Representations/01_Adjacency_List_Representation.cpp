/*
╔══════════════════════════════════════════════════════════════════╗
║       01 — ADJACENCY LIST REPRESENTATION (THE CP STANDARD)      ║
║       Zero to GM Level — Tree Representations                    ║
╚══════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS
─────────────────
 1. What is an Adjacency List?
 2. Unweighted Tree
 3. Weighted Tree
 4. Memory Layout Visualization
 5. Dry Run: Building Adjacency List
 6. Complexity Analysis
 7. Code

═══════════════════════════════════════════════════════════════════
 1. WHAT IS AN ADJACENCY LIST?
═══════════════════════════════════════════════════════════════════

 For each node v, store a LIST of its neighbors.

 Implementation: vector<vector<int>> adj(N+1);
                 adj[v] = {all neighbors of v}

 This is the #1 representation used in competitive programming.

═══════════════════════════════════════════════════════════════════
 2. UNWEIGHTED TREE — VISUALIZATION
═══════════════════════════════════════════════════════════════════

 Tree:
         1
        / \
       2   3
      / \   \
     4   5   6

 Edges: (1,2), (1,3), (2,4), (2,5), (3,6)

 Adjacency List (stored as vector<vector<int>>):

 Index  │  List
 ───────┼──────────────
  adj[1]│  [2, 3]
  adj[2]│  [1, 4, 5]
  adj[3]│  [1, 6]
  adj[4]│  [2]
  adj[5]│  [2]
  adj[6]│  [3]

 Memory visualization (each row is a vector):
  adj[1]: ┌───┬───┐
          │ 2 │ 3 │
          └───┴───┘
  adj[2]: ┌───┬───┬───┐
          │ 1 │ 4 │ 5 │
          └───┴───┴───┘
  adj[3]: ┌───┬───┐
          │ 1 │ 6 │
          └───┴───┘
  adj[4]: ┌───┐
          │ 2 │
          └───┘
  adj[5]: ┌───┐
          │ 2 │
          └───┘
  adj[6]: ┌───┐
          │ 3 │
          └───┘

═══════════════════════════════════════════════════════════════════
 3. WEIGHTED TREE — VISUALIZATION
═══════════════════════════════════════════════════════════════════

 Tree with weights:
         1
        /5\3
       2    3
      /2\7   \4
     4    5    6

 Use vector<vector<pair<int,int>>> adj;
 adj[v] stores {neighbor, weight} pairs.

 Index  │  List of (neighbor, weight)
 ───────┼─────────────────────────────
  adj[1]│  [(2,5), (3,3)]
  adj[2]│  [(1,5), (4,2), (5,7)]
  adj[3]│  [(1,3), (6,4)]
  adj[4]│  [(2,2)]
  adj[5]│  [(2,7)]
  adj[6]│  [(3,4)]

═══════════════════════════════════════════════════════════════════
 4. DRY RUN: BUILDING ADJACENCY LIST
═══════════════════════════════════════════════════════════════════

 Input: N=5, Edges: (1,2), (1,3), (2,4), (2,5)

 Initially: adj = {[], [], [], [], [], []}  (indices 0-5)

 Read edge (1,2):
   adj[1].push_back(2) → adj[1] = [2]
   adj[2].push_back(1) → adj[2] = [1]

 Read edge (1,3):
   adj[1].push_back(3) → adj[1] = [2, 3]
   adj[3].push_back(1) → adj[3] = [1]

 Read edge (2,4):
   adj[2].push_back(4) → adj[2] = [1, 4]
   adj[4].push_back(2) → adj[4] = [2]

 Read edge (2,5):
   adj[2].push_back(5) → adj[2] = [1, 4, 5]
   adj[5].push_back(2) → adj[5] = [2]

 Final adjacency list:
   adj[1] = [2, 3]
   adj[2] = [1, 4, 5]
   adj[3] = [1]
   adj[4] = [2]
   adj[5] = [2]

 Total entries stored = 2 × (N-1) = 2 × 4 = 8  ✅
 (Each edge stored in BOTH directions)

═══════════════════════════════════════════════════════════════════
 5. COMPLEXITY ANALYSIS
═══════════════════════════════════════════════════════════════════

 ┌───────────────────────────┬────────────┬───────────────────┐
 │ Operation                 │ Time       │ Space             │
 ├───────────────────────────┼────────────┼───────────────────┤
 │ Build adj list            │ O(N)       │ O(N)              │
 │ Access neighbors of v     │ O(degree v)│ —                 │
 │ Check if edge (u,v) exists│ O(degree v)│ —                 │
 │ Traverse entire tree      │ O(N)       │ O(N) for visited  │
 │ Space for adj list        │ —          │ O(2·(N-1)) = O(N) │
 └───────────────────────────┴────────────┴───────────────────┘

 WHY adjacency list is best for trees:
   - O(N) space (no wasted memory like adjacency matrix O(N²))
   - O(degree) to iterate neighbors (fast for trees)
   - Easy to implement

═══════════════════════════════════════════════════════════════════
 6. CODE
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

void solve() {
    int n;
    cin >> n;

    // ═══════════════════════════════════════════════════
    // METHOD 1: Unweighted adjacency list
    // ═══════════════════════════════════════════════════
    vvec<int> adj(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);  // UNDIRECTED: add both ways!
    }

    // Print adjacency list
    cout << "Unweighted Adjacency List:" << nl;
    for (int i = 1; i <= n; i++) {
        cout << "  " << i << " → [";
        for (int j = 0; j < sz(adj[i]); j++) {
            if (j > 0) cout << ", ";
            cout << adj[i][j];
        }
        cout << "]" << nl;
    }

    // DFS traversal using adjacency list
    cout << nl << "DFS from node 1: ";
    vec<bool> vis(n + 1, false);
    stack<int> stk;
    stk.push(1);
    vis[1] = true;
    while (!stk.empty()) {
        int v = stk.top(); stk.pop();
        cout << v << " ";
        for (int u : adj[v]) {
            if (!vis[u]) {
                vis[u] = true;
                stk.push(u);
            }
        }
    }
    cout << nl;

    // BFS traversal using adjacency list
    cout << "BFS from node 1: ";
    fill(all(vis), false);
    queue<int> q;
    q.push(1);
    vis[1] = true;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        cout << v << " ";
        for (int u : adj[v]) {
            if (!vis[u]) {
                vis[u] = true;
                q.push(u);
            }
        }
    }
    cout << nl;
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
6
1 2
1 3
2 4
2 5
3 6

Output:
Unweighted Adjacency List:
  1 → [2, 3]
  2 → [1, 4, 5]
  3 → [1, 6]
  4 → [2]
  5 → [2]
  6 → [3]

DFS from node 1: 1 3 6 2 5 4
BFS from node 1: 1 2 3 4 5 6

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ vector<vector<int>> adj(N+1) — the CP standard
 ✅ For weighted: vector<vector<pair<int,int>>> adj(N+1)
 ✅ Always add BOTH directions for undirected trees
 ✅ Total entries = 2·(N-1) → O(N) space
 ✅ Traversal (DFS/BFS) = O(N) time
═══════════════════════════════════════════════════════════════════
*/

