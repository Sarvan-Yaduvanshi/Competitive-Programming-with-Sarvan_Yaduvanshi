/*
╔══════════════════════════════════════════════════════════════════╗
║  03 — VIRTUAL TREE (Auxiliary Tree)                             ║
║  Zero to GM Level — Advanced Tree Techniques                     ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 WHAT IS A VIRTUAL TREE?
═══════════════════════════════════════════════════════════════════

 Given a tree of N nodes and a subset S of K "important" nodes,
 build a SMALL tree containing only:
   - The K important nodes
   - Their pairwise LCAs
   - The root (if needed)

 Size of virtual tree: O(K), regardless of N!

═══════════════════════════════════════════════════════════════════
 WHY? — REDUCE N TO K
═══════════════════════════════════════════════════════════════════

 Many problems ask: "For each query, given K nodes, compute
 something on the tree." If K is small but N is large,
 virtual tree reduces the problem from O(N) to O(K) per query.

 Total across queries: if ΣK = O(N), total work = O(N log N).

═══════════════════════════════════════════════════════════════════
 DRY RUN
═══════════════════════════════════════════════════════════════════

 Original tree (N=11):
              1
           /  |  \
          2   3   4
         / \     / \
        5   6   7   8
       /       / \
      9       10  11

 Important nodes S = {9, 6, 10, 11}

 Step 1: Sort S by Euler tour (DFS) order: [9, 6, 10, 11]
         (Assume tin: 9→4, 6→6, 10→9, 11→11)
         Sorted: [9, 6, 10, 11]

 Step 2: Find pairwise LCAs of consecutive pairs:
         LCA(9, 6) = 5... wait, LCA(9,6) = 2 (since 9 is under 5 under 2)
         Actually: LCA(9,6) = 2, LCA(6,10) = 1, LCA(10,11) = 7

 Step 3: Virtual tree nodes = {9, 6, 10, 11} ∪ {2, 1, 7} = {1, 2, 6, 7, 9, 10, 11}

 Virtual tree structure:
         1
        / \
       2   7
      / \ / \
     9  6 10 11

 Size = 7 nodes instead of 11 ← much smaller for large N!

═══════════════════════════════════════════════════════════════════
 ALGORITHM
═══════════════════════════════════════════════════════════════════

 1. Sort important nodes by tin (Euler tour entry time)
 2. Add consecutive LCAs: for i=0..k-2: add LCA(S[i], S[i+1])
 3. Also add root if needed
 4. Remove duplicates, sort by tin again
 5. Build virtual tree using stack (parent = last node on stack
    whose subtree range contains current node)

═══════════════════════════════════════════════════════════════════
 COMPLEXITY: O(K log K) per query + O(N log N) preprocessing
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
#include <cstring>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

const int MAXN = 200005;
const int LOG = 20;

vvec<int> adj;
int tin[MAXN], tout[MAXN], dep[MAXN], up[MAXN][LOG];
int timer_val;

void dfs(int v, int p, int d) {
    dep[v] = d; up[v][0] = p;
    for (int k = 1; k < LOG; k++) up[v][k] = up[up[v][k-1]][k-1];
    tin[v] = timer_val++;
    for (int u : adj[v]) if (u != p) dfs(u, v, d + 1);
    tout[v] = timer_val++;
}

bool isAnc(int u, int v) { return tin[u] <= tin[v] && tout[v] <= tout[u]; }

int lca(int u, int v) {
    if (isAnc(u, v)) return u;
    if (isAnc(v, u)) return v;
    for (int k = LOG-1; k >= 0; k--)
        if (!isAnc(up[u][k], v)) u = up[u][k];
    return up[u][0];
}

// ═══════════════════════════════════════════════════════════
// BUILD VIRTUAL TREE
// ═══════════════════════════════════════════════════════════
// Returns adjacency list of virtual tree + list of virtual nodes
vvec<int> vtree_adj;

vec<int> buildVirtualTree(vec<int>& important) {
    // Sort by DFS entry time
    sort(important.begin(), important.end(), [](int a, int b) {
        return tin[a] < tin[b];
    });

    // Remove duplicates
    important.erase(unique(important.begin(), important.end()), important.end());

    // Add pairwise LCAs
    vec<int> all_nodes = important;
    for (int i = 0; i + 1 < sz(important); i++) {
        all_nodes.pb(lca(important[i], important[i + 1]));
    }

    // Add root if not present
    if (!important.empty()) {
        all_nodes.pb(lca(important.front(), important.back()));
    }

    // Sort and deduplicate
    sort(all_nodes.begin(), all_nodes.end(), [](int a, int b) {
        return tin[a] < tin[b];
    });
    all_nodes.erase(unique(all_nodes.begin(), all_nodes.end()), all_nodes.end());

    int k = sz(all_nodes);
    vtree_adj.assign(k, {});

    // Build virtual tree using stack
    // Map nodes to indices 0..k-1
    map<int, int> nodeToIdx;
    for (int i = 0; i < k; i++) nodeToIdx[all_nodes[i]] = i;

    stack<int> stk; // stack of original node IDs
    stk.push(all_nodes[0]);

    for (int i = 1; i < k; i++) {
        int v = all_nodes[i];
        int l = lca(v, stk.top());

        if (l != stk.top()) {
            // Pop until we find l or an ancestor of l
            while (stk.size() > 1) {
                int top = stk.top();
                stk.pop();
                int below = stk.top();
                if (dep[below] <= dep[l]) {
                    // Add edge: l → top
                    vtree_adj[nodeToIdx[l]].pb(nodeToIdx[top]);
                    if (below != l) stk.push(l); // push l if not already there
                    break;
                }
                // Add edge: below → top
                vtree_adj[nodeToIdx[below]].pb(nodeToIdx[top]);
            }
            if (stk.top() != l) stk.push(l);
        }
        stk.push(v);
    }

    // Pop remaining
    while (stk.size() > 1) {
        int top = stk.top(); stk.pop();
        vtree_adj[nodeToIdx[stk.top()]].pb(nodeToIdx[top]);
    }

    return all_nodes;
}

void solve() {
    int n; cin >> n;
    adj.assign(n + 1, {});
    memset(up, 0, sizeof(up));
    timer_val = 0;

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }
    dfs(1, 0, 0);

    int q; cin >> q;
    while (q--) {
        int k; cin >> k;
        vec<int> imp(k);
        for (auto& x : imp) cin >> x;

        vec<int> vnodes = buildVirtualTree(imp);

        cout << "Virtual tree nodes (" << sz(vnodes) << "): ";
        for (int x : vnodes) cout << x << " ";
        cout << nl;

        cout << "Virtual tree edges:" << nl;
        for (int i = 0; i < sz(vnodes); i++) {
            for (int j : vtree_adj[i]) {
                cout << "  " << vnodes[i] << " → " << vnodes[j] << nl;
            }
        }
        cout << nl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1;
    // cin >> TC;
    while (TC--) solve();
    return 0;
}

/*
═══════════════════════════════════════════════════════════════════
 SAMPLE I/O
═══════════════════════════════════════════════════════════════════

Input:
7
1 2
1 3
2 4
2 5
3 6
3 7
1
3 4 5 7

Output:
Virtual tree nodes (4): 1 2 4 5 7  (or similar with LCAs added)
Virtual tree edges:
  1 → 2
  1 → 7
  2 → 4
  2 → 5

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Virtual tree: compress N-node tree to O(K) node tree
 ✅ Contains only important nodes + their pairwise LCAs
 ✅ Sort by DFS order, add consecutive LCAs, build with stack
 ✅ Useful when ΣK across queries is small (e.g., ΣK ≤ N)
 ✅ Reduces per-query work from O(N) to O(K)
═══════════════════════════════════════════════════════════════════
*/

