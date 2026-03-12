/*
╔══════════════════════════════════════════════════════════════════╗
║  04 — MAX INDEPENDENT SET & MAX MATCHING ON TREE                ║
║  Zero to GM Level — Tree DP                                      ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 MAX INDEPENDENT SET — DRY RUN
═══════════════════════════════════════════════════════════════════

 Independent set: no two adjacent nodes selected.
 dp[v][0] = max IS in subtree(v) when v is NOT selected
 dp[v][1] = max IS in subtree(v) when v IS selected

 Transitions:
   dp[v][0] = Σ max(dp[u][0], dp[u][1])  (children can be either)
   dp[v][1] = val[v] + Σ dp[u][0]         (children must NOT be selected)

 Tree: val = [_, 1, 5, 3, 2, 4]
         1(val=1)
        / \
    (5)2   3(3)
      / \
  (2)4   5(4)

 dp[4][0]=0, dp[4][1]=2
 dp[5][0]=0, dp[5][1]=4
 dp[2][0]=max(0,2)+max(0,4)=2+4=6
 dp[2][1]=5+0+0=5
 dp[3][0]=0, dp[3][1]=3
 dp[1][0]=max(6,5)+max(0,3)=6+3=9
 dp[1][1]=1+6+0=7

 Answer = max(dp[1][0], dp[1][1]) = max(9, 7) = 9
 Selected: {4, 5, 3} with sum 2+4+3=9 ✅

═══════════════════════════════════════════════════════════════════
 MAX MATCHING — DRY RUN (CSES Tree Matching)
═══════════════════════════════════════════════════════════════════

 Matching: select edges so no vertex appears twice.
 dp[v][0] = max matching in subtree(v), v is NOT matched
 dp[v][1] = max matching in subtree(v), v IS matched to one child

 dp[v][0] = Σ max(dp[u][0], dp[u][1])
 dp[v][1] = max over children u of:
            1 + dp[u][0] + Σ_{w≠u} max(dp[w][0], dp[w][1])

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
vec<i64> val;
vec<i64> dp0, dp1; // [not selected/matched], [selected/matched]

// ═══════════════════════════════════════════════════════════
// MAX INDEPENDENT SET
// ═══════════════════════════════════════════════════════════
void dfsIS(int v, int par) {
    dp0[v] = 0;
    dp1[v] = val[v];
    for (int u : adj[v]) {
        if (u == par) continue;
        dfsIS(u, v);
        dp0[v] += max(dp0[u], dp1[u]); // child can be either
        dp1[v] += dp0[u];               // child must NOT be selected
    }
}

// ═══════════════════════════════════════════════════════════
// MAX MATCHING (CSES Tree Matching)
// ═══════════════════════════════════════════════════════════
void dfsMatching(int v, int par) {
    dp0[v] = 0; // v not matched
    dp1[v] = 0; // v matched with some child

    i64 sumBest = 0; // sum of max(dp0[u], dp1[u]) for all children
    for (int u : adj[v]) {
        if (u == par) continue;
        dfsMatching(u, v);
        sumBest += max(dp0[u], dp1[u]);
    }
    dp0[v] = sumBest;

    // Try matching v with each child u
    for (int u : adj[v]) {
        if (u == par) continue;
        // Match edge (v, u): remove u's contribution, add 1 + dp0[u]
        i64 candidate = sumBest - max(dp0[u], dp1[u]) + 1 + dp0[u];
        dp1[v] = max(dp1[v], candidate);
    }
}

void solve() {
    int n; cin >> n;
    adj.assign(n + 1, {});
    val.assign(n + 1, 0);
    dp0.assign(n + 1, 0);
    dp1.assign(n + 1, 0);

    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    // Max Independent Set
    dfsIS(1, -1);
    cout << "Max Independent Set: " << max(dp0[1], dp1[1]) << nl;

    // Max Matching
    dp0.assign(n + 1, 0);
    dp1.assign(n + 1, 0);
    dfsMatching(1, -1);
    cout << "Max Matching: " << max(dp0[1], dp1[1]) << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1; cin >> TC;
    while (TC--) solve();
    return 0;
}

/*
 Input: 1\n5\n1 5 3 2 4\n1 2\n1 3\n2 4\n2 5
 Output:
 Max Independent Set: 9
 Max Matching: 2

 Time: O(N) | Space: O(N)
*/

