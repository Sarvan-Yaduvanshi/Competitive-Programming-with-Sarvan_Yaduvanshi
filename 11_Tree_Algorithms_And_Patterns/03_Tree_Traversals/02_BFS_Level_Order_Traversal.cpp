/*
╔══════════════════════════════════════════════════════════════════╗
║       02 — BFS / LEVEL ORDER TRAVERSAL                           ║
║       Zero to GM Level — Tree Traversals                         ║
╚══════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS
─────────────────
 1. BFS on Trees
 2. Level Order Traversal
 3. Zigzag Level Order
 4. Visual Dry Runs
 5. Complexity
 6. Code

═══════════════════════════════════════════════════════════════════
 1. BFS ON TREES
═══════════════════════════════════════════════════════════════════

 BFS uses a QUEUE to visit nodes level by level.
 On trees (no cycles), we just skip the parent.

 Algorithm:
   queue.push(root)
   while queue not empty:
     v = queue.front(); queue.pop()
     process v
     for each neighbor u of v:
       if u ≠ parent[v]:
         queue.push(u)

═══════════════════════════════════════════════════════════════════
 2. LEVEL ORDER TRAVERSAL — DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree:
              1
            /   \
           2     3
          / \   / \
         4   5 6   7

 Queue trace:
 ┌──────────┬────────────────────┬──────────────────┐
 │ Step     │ Queue (front→back) │ Output           │
 ├──────────┼────────────────────┼──────────────────┤
 │ Init     │ [1]                │                  │
 │ Pop 1    │ [2, 3]             │ Level 0: [1]     │
 │ Pop 2    │ [3, 4, 5]          │                  │
 │ Pop 3    │ [4, 5, 6, 7]       │ Level 1: [2, 3]  │
 │ Pop 4    │ [5, 6, 7]          │                  │
 │ Pop 5    │ [6, 7]             │                  │
 │ Pop 6    │ [7]                │                  │
 │ Pop 7    │ []                 │ Level 2: [4,5,6,7]│
 └──────────┴────────────────────┴──────────────────┘

 To get nodes GROUPED BY LEVEL:
   Process all nodes in queue at once (levelSize = queue.size())
   Then push all their children → next level.

═══════════════════════════════════════════════════════════════════
 3. ZIGZAG LEVEL ORDER — DRY RUN
═══════════════════════════════════════════════════════════════════

 Same tree:
              1
            /   \
           2     3
          / \   / \
         4   5 6   7

 Level 0 (left→right): [1]
 Level 1 (right→left): [3, 2]       ← REVERSED
 Level 2 (left→right): [4, 5, 6, 7]
 Level 3 (right→left): ...          ← REVERSED

 Trick: Just reverse every odd-indexed level!

═══════════════════════════════════════════════════════════════════
 4. COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌──────────────────────────┬────────────┬──────────────┐
 │ Operation                │ Time       │ Space        │
 ├──────────────────────────┼────────────┼──────────────┤
 │ BFS traversal            │ O(N)       │ O(W) queue   │
 │ Level order (grouped)    │ O(N)       │ O(W) queue   │
 │ Zigzag level order       │ O(N)       │ O(W) queue   │
 └──────────────────────────┴────────────┴──────────────┘

 W = maximum width of tree (max nodes at any level)
 For a complete binary tree: W = N/2

═══════════════════════════════════════════════════════════════════
 5. CODE
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
// LEVEL ORDER TRAVERSAL (grouped by level)
// ═══════════════════════════════════════════════════════════════
vvec<int> levelOrder(int root, int n) {
    vvec<int> levels;
    queue<pii> q; // (node, parent)
    q.push({root, -1});

    while (!q.empty()) {
        int levelSize = sz(q);
        vec<int> currentLevel;

        for (int i = 0; i < levelSize; i++) {
            auto [v, par] = q.front(); q.pop();
            currentLevel.pb(v);

            for (int u : adj[v]) {
                if (u == par) continue;
                q.push({u, v});
            }
        }
        levels.pb(currentLevel);
    }
    return levels;
}

// ═══════════════════════════════════════════════════════════════
// ZIGZAG LEVEL ORDER
// ═══════════════════════════════════════════════════════════════
vvec<int> zigzagLevelOrder(int root, int n) {
    vvec<int> levels = levelOrder(root, n);
    for (int i = 1; i < sz(levels); i += 2) {
        reverse(all(levels[i])); // reverse odd levels
    }
    return levels;
}

// ═══════════════════════════════════════════════════════════════
// BFS WITH DISTANCE COMPUTATION
// ═══════════════════════════════════════════════════════════════
vec<int> bfsDistance(int root, int n) {
    vec<int> dist(n + 1, -1);
    queue<int> q;
    dist[root] = 0;
    q.push(root);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int u : adj[v]) {
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
    return dist;
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

    // Level Order
    vvec<int> levels = levelOrder(1, n);
    cout << "Level Order Traversal:" << nl;
    for (int i = 0; i < sz(levels); i++) {
        cout << "  Level " << i << ": [";
        for (int j = 0; j < sz(levels[i]); j++) {
            if (j) cout << ", ";
            cout << levels[i][j];
        }
        cout << "]" << nl;
    }

    // Zigzag
    vvec<int> zigzag = zigzagLevelOrder(1, n);
    cout << nl << "Zigzag Level Order:" << nl;
    for (int i = 0; i < sz(zigzag); i++) {
        cout << "  Level " << i << " (" << (i%2==0 ? "L→R" : "R→L") << "): [";
        for (int j = 0; j < sz(zigzag[i]); j++) {
            if (j) cout << ", ";
            cout << zigzag[i][j];
        }
        cout << "]" << nl;
    }

    // BFS Distances from root
    vec<int> dist = bfsDistance(1, n);
    cout << nl << "BFS Distances from root 1:" << nl;
    for (int i = 1; i <= n; i++) {
        cout << "  dist[" << i << "] = " << dist[i] << nl;
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
1
7
1 2
1 3
2 4
2 5
3 6
3 7

Output:
Level Order Traversal:
  Level 0: [1]
  Level 1: [2, 3]
  Level 2: [4, 5, 6, 7]

Zigzag Level Order:
  Level 0 (L→R): [1]
  Level 1 (R→L): [3, 2]
  Level 2 (L→R): [4, 5, 6, 7]

BFS Distances from root 1:
  dist[1] = 0
  dist[2] = 1
  dist[3] = 1
  dist[4] = 2
  dist[5] = 2
  dist[6] = 2
  dist[7] = 2

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ BFS on tree = Level order traversal automatically
 ✅ To group by level: process queue.size() nodes at once
 ✅ Zigzag: just reverse alternate levels
 ✅ BFS also computes distances from root in O(N)
 ✅ Space = O(max width) for queue ≈ O(N/2) for balanced tree
═══════════════════════════════════════════════════════════════════
*/

