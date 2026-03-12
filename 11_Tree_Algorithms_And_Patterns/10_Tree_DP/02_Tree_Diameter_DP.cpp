/*
╔══════════════════════════════════════════════════════════════════╗
║  02 — TREE DIAMETER VIA DP                                      ║
║  Zero to GM Level — Tree DP                                      ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 CONCEPT: Diameter = max over all nodes v of (down1[v] + down2[v])
═══════════════════════════════════════════════════════════════════

 down1[v] = longest path going DOWN from v (through best child)
 down2[v] = second longest path going DOWN from v (through 2nd best)

 Diameter through v = down1[v] + down2[v]
 Answer = max of this over all v.

═══════════════════════════════════════════════════════════════════
 DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree:
           1
          / \
         2   3
        / \   \
       4   5   6
      /
     7

 Bottom-up DFS:
   Node 7: leaf → down1=0, down2=0
   Node 4: child 7 gives depth 1 → down1=1, down2=0
   Node 5: leaf → down1=0, down2=0
   Node 2: children give depths {1+1=2, 0+1=1} → down1=2, down2=1
           Diameter through 2 = 2+1 = 3
   Node 6: leaf → down1=0, down2=0
   Node 3: child 6 gives depth 1 → down1=1, down2=0
   Node 1: children give depths {2+1=3, 1+1=2} → down1=3, down2=2
           Diameter through 1 = 3+2 = 5 ✅

 Answer = max(3, 5) = 5  (path: 7→4→2→1→3→6)

═══════════════════════════════════════════════════════════════════
 CODE (CSES Tree Diameter)
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

vvec<int> adj;
int diameter;

// Returns longest path going DOWN from v
int dfs(int v, int par) {
    int d1 = 0, d2 = 0; // best and second best
    for (int u : adj[v]) {
        if (u == par) continue;
        int d = 1 + dfs(u, v);
        if (d >= d1) { d2 = d1; d1 = d; }
        else if (d > d2) { d2 = d; }
    }
    diameter = max(diameter, d1 + d2);
    return d1;
}

void solve() {
    int n; cin >> n;
    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }
    diameter = 0;
    dfs(1, -1);
    cout << diameter << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1;
    // cin >> TC; // CSES single test case
    while (TC--) solve();
    return 0;
}

/*
 Input: 5\n1 2\n1 3\n2 4\n2 5
 Output: 3 (path: 4→2→1→3 or 5→2→1→3)

 Time: O(N) | Space: O(N)

 ┌─────────────────────────────────────────────────────────────┐
 │ KEY: d1+d2 at each node = potential diameter through node   │
 │ Return d1 upward = longest chain for parent to extend       │
 └─────────────────────────────────────────────────────────────┘
*/

