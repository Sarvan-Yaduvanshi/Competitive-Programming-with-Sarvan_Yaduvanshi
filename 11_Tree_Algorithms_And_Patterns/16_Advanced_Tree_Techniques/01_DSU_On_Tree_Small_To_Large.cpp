/*
╔══════════════════════════════════════════════════════════════════╗
║  01 — DSU ON TREE (Small-to-Large Merging) ⭐                  ║
║  Zero to GM Level — Advanced Tree Techniques                     ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 PROBLEM: For each node v, count distinct colors in subtree(v)
═══════════════════════════════════════════════════════════════════

 Naive: O(N²) — for each node, DFS its subtree
 DSU on tree: O(N log N) — merge smaller sets into larger ones

═══════════════════════════════════════════════════════════════════
 KEY IDEA — SMALL-TO-LARGE MERGING
═══════════════════════════════════════════════════════════════════

 For each node, maintain a set of colors in its subtree.
 When merging children, ALWAYS merge the SMALLER set into the LARGER.

 Why O(N log N)? Each element moves to a larger set each time
 it's merged. A set can double at most O(log N) times before
 reaching size N. So each element is moved at most O(log N) times.

═══════════════════════════════════════════════════════════════════
 DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree: color = [_, R, B, R, G, B]
         1(R)
        / \
    (B)2   3(R)
      / \
  (G)4   5(B)

 DFS postorder:
   Node 4: set = {G}
   Node 5: set = {B}
   Node 2: set starts as {B}
     Merge set[4]={G} into set[2] → set[2]={B,G}
     Merge set[5]={B} into set[2] → {B,G} (B already present)
     ans[2] = 2 distinct colors
   Node 3: set = {R}, ans[3] = 1
   Node 1: set starts as {R}
     set[2] is larger ({B,G}), set[1] is smaller ({R})
     Swap! set[1] takes set[2]'s set → set[1]={B,G}, add R → {R,B,G}
     Merge set[3]={R} into set[1] → {R,B,G} (R already present)
     ans[1] = 3 distinct colors

 Answer: [_, 3, 2, 1, 1, 1]

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 Time: O(N log²N) with std::set, O(N log N) with custom DSU
 Space: O(N)

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
vec<int> color, ans;
vec<set<int>*> nodeSet; // pointer to color set of each node

void dfs(int v, int par) {
    nodeSet[v] = new set<int>();
    nodeSet[v]->insert(color[v]);

    for (int u : adj[v]) {
        if (u == par) continue;
        dfs(u, v);

        // SMALL-TO-LARGE MERGE
        if (sz(*nodeSet[u]) > sz(*nodeSet[v])) {
            swap(nodeSet[u], nodeSet[v]); // keep the larger set
        }
        // Merge smaller into larger
        for (int c : *nodeSet[u]) {
            nodeSet[v]->insert(c);
        }
        delete nodeSet[u];
    }

    ans[v] = sz(*nodeSet[v]);
}

void solve() {
    int n; cin >> n;
    adj.assign(n + 1, {});
    color.assign(n + 1, 0);
    ans.assign(n + 1, 0);
    nodeSet.assign(n + 1, nullptr);

    for (int i = 1; i <= n; i++) cin >> color[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    dfs(1, -1);

    cout << "Distinct colors in each subtree:" << nl;
    for (int i = 1; i <= n; i++) {
        cout << "  Node " << i << ": " << ans[i] << " distinct colors" << nl;
    }

    delete nodeSet[1]; // cleanup
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1; cin >> TC;
    while (TC--) solve();
    return 0;
}

/*
═══════════════════════════════════════════════════════════════════
 SAMPLE I/O
═══════════════════════════════════════════════════════════════════

Input:
1
5
1 2 1 3 2
1 2
1 3
2 4
2 5

Output:
Distinct colors in each subtree:
  Node 1: 3 distinct colors
  Node 2: 2 distinct colors  (colors: 2, 3, 2 → {2,3})
  Node 3: 1 distinct colors
  Node 4: 1 distinct colors
  Node 5: 1 distinct colors

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Small-to-large: always merge smaller set INTO larger
 ✅ Each element moves O(log N) times → total O(N log N) inserts
 ✅ With std::set: O(N log²N). With unordered: O(N log N) amortized
 ✅ CSES: Distinct Colors — direct application
 ✅ Same technique for: most frequent color, sum by color, etc.
═══════════════════════════════════════════════════════════════════
*/

