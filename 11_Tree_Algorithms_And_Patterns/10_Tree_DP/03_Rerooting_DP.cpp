/*
╔══════════════════════════════════════════════════════════════════╗
║  03 — REROOTING DP ⭐ (Answer for Every Root)                  ║
║  Zero to GM Level — Tree DP                                      ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 PROBLEM: Sum of Distances (CSES Tree Distances II)
═══════════════════════════════════════════════════════════════════

 For each node v, compute the sum of distances to all other nodes.
 Naive: O(N²). Rerooting: O(N)!

═══════════════════════════════════════════════════════════════════
 KEY INSIGHT
═══════════════════════════════════════════════════════════════════

 When we move the root from v to its child u:
   - All sub[u] nodes get 1 closer → subtract sub[u]
   - All (N - sub[u]) nodes get 1 farther → add (N - sub[u])

 So: ans[u] = ans[v] - sub[u] + (N - sub[u])
            = ans[v] + N - 2·sub[u]

═══════════════════════════════════════════════════════════════════
 DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree (N=5):
         1
        / \
       2   3
      / \
     4   5

 Step 1: Compute sub[] rooted at 1
   sub[4]=1, sub[5]=1, sub[2]=3, sub[3]=1, sub[1]=5

 Step 2: Compute ans[1] = sum of distances from node 1
   depth[1]=0, depth[2]=1, depth[3]=1, depth[4]=2, depth[5]=2
   ans[1] = 0+1+1+2+2 = 6

 Step 3: Reroot to compute ans for all nodes
   ans[u] = ans[parent] + N - 2·sub[u]

   ans[2] = ans[1] + 5 - 2·3 = 6 + 5 - 6 = 5
   Verify: dist from 2: 0+1+2+1+1 = 5 ✅

   ans[3] = ans[1] + 5 - 2·1 = 6 + 5 - 2 = 9
   Verify: dist from 3: 0+1+2+3+3 = ? Wait let me recalculate
   From 3: to 1=1, to 2=2, to 4=3, to 5=3 → 1+2+3+3 = 9 ✅

   ans[4] = ans[2] + 5 - 2·1 = 5 + 5 - 2 = 8
   Verify: from 4: to 2=1, to 1=2, to 3=3, to 5=2 → 1+2+3+2 = 8 ✅

   ans[5] = ans[2] + 5 - 2·1 = 5 + 5 - 2 = 8
   Verify: from 5: to 2=1, to 1=2, to 3=3, to 4=2 → 1+2+3+2 = 8 ✅

 Final: ans = [_, 6, 5, 9, 8, 8]

═══════════════════════════════════════════════════════════════════
 COMPLEXITY: O(N) — two DFS passes!
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

vvec<int> adj;
vec<i64> sub, ans, dep;
int n;

// DFS 1: Compute subtree sizes and ans[root] = sum of depths
void dfs1(int v, int par, int d) {
    sub[v] = 1;
    dep[v] = d;
    for (int u : adj[v]) {
        if (u == par) continue;
        dfs1(u, v, d + 1);
        sub[v] += sub[u];
    }
}

// DFS 2: Reroot — propagate answer to children
void dfs2(int v, int par) {
    for (int u : adj[v]) {
        if (u == par) continue;
        // KEY FORMULA: ans[u] = ans[v] + n - 2*sub[u]
        ans[u] = ans[v] + n - 2 * sub[u];
        dfs2(u, v);
    }
}

void solve() {
    cin >> n;
    adj.assign(n + 1, {});
    sub.assign(n + 1, 0);
    ans.assign(n + 1, 0);
    dep.assign(n + 1, 0);

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    // Step 1: Root at 1, compute subtree sizes and sum of depths
    dfs1(1, -1, 0);
    ans[1] = 0;
    for (int i = 1; i <= n; i++) ans[1] += dep[i];

    // Step 2: Reroot to compute answer for all nodes
    dfs2(1, -1);

    // Output
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1;
    // cin >> TC;  // Usually single test case for CSES
    while (TC--) solve();
    return 0;
}

/*
═══════════════════════════════════════════════════════════════════
 SAMPLE INPUT / OUTPUT (CSES Tree Distances II format)
═══════════════════════════════════════════════════════════════════

Input:
5
1 2
1 3
2 4
2 5

Output:
6 5 9 8 8

═══════════════════════════════════════════════════════════════════
 REROOTING DP GENERAL TEMPLATE
═══════════════════════════════════════════════════════════════════

 The rerooting pattern works for many problems:
 1. Compute dp[root] for ONE fixed root (DFS 1)
 2. For each child u of v:
    dp[u] = f(dp[v], contribution_of_u_removed, contribution_of_rest)
 3. The formula depends on the specific problem.

 Common rerooting problems:
   - Sum of distances (this file)
   - Max distance (Tree Distances I on CSES)
   - Count nodes closer to each endpoint of each edge

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ ans[u] = ans[v] + N - 2·sub[u]  (sum of distances formula)
 ✅ Two DFS passes: one to compute from root, one to reroot
 ✅ O(N) total time — incredibly efficient!
 ✅ CSES: Tree Distances II — direct application
 ✅ Rerooting DP is one of the most elegant tree techniques
═══════════════════════════════════════════════════════════════════
*/

