/*
╔══════════════════════════════════════════════════════════════════╗
║  01 — SUBTREE DP BASICS                                         ║
║  Zero to GM Level — Tree DP                                      ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 WHAT IS TREE DP?
═══════════════════════════════════════════════════════════════════

 Dynamic Programming on trees: compute dp[v] for each node v
 based on dp values of v's children (bottom-up).

 PATTERN:
   void dfs(int v, int par) {
       dp[v] = base_case;
       for (int u : adj[v]) {
           if (u == par) continue;
           dfs(u, v);
           dp[v] = combine(dp[v], dp[u]);  // merge child into parent
       }
   }

═══════════════════════════════════════════════════════════════════
 EXAMPLE 1: SUBTREE SIZE
═══════════════════════════════════════════════════════════════════

 Tree:
         1
        / \
       2   3
      / \
     4   5

 sub[v] = 1 + Σ sub[child]

 DFS postorder:
   sub[4] = 1
   sub[5] = 1
   sub[2] = 1 + 1 + 1 = 3
   sub[3] = 1
   sub[1] = 1 + 3 + 1 = 5 ✅

═══════════════════════════════════════════════════════════════════
 EXAMPLE 2: SUBTREE SUM (node values)
═══════════════════════════════════════════════════════════════════

 Tree with values: val = [_, 10, 20, 30, 40, 50]
         10(1)
        /    \
      20(2)  30(3)
      /   \
    40(4) 50(5)

 sum[4]=40, sum[5]=50
 sum[2]=20+40+50=110
 sum[3]=30
 sum[1]=10+110+30=150 ✅

═══════════════════════════════════════════════════════════════════
 EXAMPLE 3: COUNT NODES AT EACH DEPTH IN SUBTREE
═══════════════════════════════════════════════════════════════════

 For each node v, how many nodes are at depth d in subtree(v)?

 This is a more complex DP where we merge vectors/maps.
 Common in "DSU on tree" problems (Chapter 16).

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
vec<i64> val, subSize, subSum;

void dfs(int v, int par) {
    subSize[v] = 1;
    subSum[v] = val[v];

    for (int u : adj[v]) {
        if (u == par) continue;
        dfs(u, v);
        subSize[v] += subSize[u];  // merge subtree size
        subSum[v] += subSum[u];    // merge subtree sum
    }
}

void solve() {
    int n; cin >> n;
    adj.assign(n + 1, {});
    val.assign(n + 1, 0);
    subSize.assign(n + 1, 0);
    subSum.assign(n + 1, 0);

    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    dfs(1, -1);

    cout << "Subtree sizes and sums:" << nl;
    for (int i = 1; i <= n; i++) {
        cout << "  Node " << i << ": size=" << subSize[i]
             << ", sum=" << subSum[i] << nl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1; cin >> TC;
    while (TC--) solve();
    return 0;
}

/*
 Input: 1\n5\n10 20 30 40 50\n1 2\n1 3\n2 4\n2 5
 Output:
 Subtree sizes and sums:
   Node 1: size=5, sum=150
   Node 2: size=3, sum=110
   Node 3: size=1, sum=30
   Node 4: size=1, sum=40
   Node 5: size=1, sum=50
*/

