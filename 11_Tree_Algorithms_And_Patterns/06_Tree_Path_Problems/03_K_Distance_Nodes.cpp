/*
╔══════════════════════════════════════════════════════════════════╗
║  03 — K DISTANCE NODES                                          ║
║  Zero to GM Level — Tree Path Problems                           ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 PROBLEM: Find all nodes at distance K from a target node.
═══════════════════════════════════════════════════════════════════

 Tree:
           1
          / \
         2   3
        / \   \
       4   5   6
      /
     7

 Target = 2, K = 2

 Nodes at distance 2 from node 2:
   Down: 7 (2→4→7), none from 5
   Up:   3 (2→1→3)
 Answer: [7, 3]

═══════════════════════════════════════════════════════════════════
 APPROACH
═══════════════════════════════════════════════════════════════════

 1. Build parent map (so we can go UP)
 2. BFS from target node for K steps
 3. Use visited[] to avoid revisiting

═══════════════════════════════════════════════════════════════════
 DRY RUN (Target=2, K=2)
═══════════════════════════════════════════════════════════════════

 BFS from node 2:
   Level 0: [2]           visited={2}
   Level 1: [4, 5, 1]     visited={2,4,5,1}  (children 4,5 + parent 1)
   Level 2: [7, 3]        visited={2,4,5,1,7,3}
              ↑(from 4) ↑(from 1, right child)

 At level K=2: output [7, 3] ✅

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
vec<int> par;

void buildParent(int v, int p) {
    par[v] = p;
    for (int u : adj[v]) if (u != p) buildParent(u, v);
}

vec<int> kDistanceNodes(int target, int k, int n) {
    vec<bool> visited(n + 1, false);
    queue<int> q;
    q.push(target);
    visited[target] = true;

    int dist = 0;
    while (!q.empty() && dist < k) {
        int sz_q = sz(q);
        for (int i = 0; i < sz_q; i++) {
            int v = q.front(); q.pop();
            // Go to children and parent (all neighbors + parent)
            for (int u : adj[v]) {
                if (!visited[u]) { visited[u] = true; q.push(u); }
            }
            if (par[v] != -1 && !visited[par[v]]) {
                visited[par[v]] = true;
                q.push(par[v]);
            }
        }
        dist++;
    }

    vec<int> result;
    while (!q.empty()) { result.pb(q.front()); q.pop(); }
    sort(result.begin(), result.end());
    return result;
}

void solve() {
    int n;
    cin >> n;
    adj.assign(n + 1, {});
    par.assign(n + 1, -1);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }
    buildParent(1, -1);

    int target, k;
    cin >> target >> k;

    vec<int> res = kDistanceNodes(target, k, n);
    cout << "Nodes at distance " << k << " from " << target << ": ";
    for (int x : res) cout << x << " ";
    cout << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1; cin >> TC;
    while (TC--) solve();
    return 0;
}

/*
 Input: 1\n7\n1 2\n1 3\n2 4\n2 5\n3 6\n4 7\n2 2
 Output: Nodes at distance 2 from 2: 3 7

 Time: O(N) | Space: O(N)
*/

