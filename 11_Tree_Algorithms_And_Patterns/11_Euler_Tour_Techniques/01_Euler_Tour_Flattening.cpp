/*
╔══════════════════════════════════════════════════════════════════╗
║  01 — EULER TOUR FLATTENING (Tree → Array)                     ║
║  Zero to GM Level — Euler Tour Techniques                        ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 THE BIG IDEA
═══════════════════════════════════════════════════════════════════

 Euler tour "flattens" a tree into an array such that:
   Subtree of v = contiguous range [tin[v], tout[v]] in the array!

 This means ANY subtree query becomes a RANGE query on an array.
 → Use Segment Tree / BIT / Sparse Table for O(log N) operations!

═══════════════════════════════════════════════════════════════════
 DRY RUN — EULER TOUR
═══════════════════════════════════════════════════════════════════

 Tree:
              1
            /   \
           2     3
          / \     \
         4   5     6

 DFS order with timer (starting from 0):

 DFS(1): tin[1]=0, visit children...
   DFS(2): tin[2]=1
     DFS(4): tin[4]=2, tout[4]=2  (leaf)
     DFS(5): tin[5]=3, tout[5]=3  (leaf)
   tout[2]=3
   DFS(3): tin[3]=4
     DFS(6): tin[6]=5, tout[6]=5  (leaf)
   tout[3]=5
 tout[1]=5

 Result:
 ┌──────┬─────┬──────┐
 │ Node │ tin │ tout │
 ├──────┼─────┼──────┤
 │  1   │  0  │  5   │
 │  2   │  1  │  3   │
 │  3   │  4  │  5   │
 │  4   │  2  │  2   │
 │  5   │  3  │  3   │
 │  6   │  5  │  5   │
 └──────┴─────┴──────┘

 DFS order array (flat): [1, 2, 4, 5, 3, 6]
 Indices:                  0  1  2  3  4  5

 KEY PROPERTY:
   Subtree(2) = indices [1..3] = [2, 4, 5] ✅
   Subtree(3) = indices [4..5] = [3, 6] ✅
   Subtree(1) = indices [0..5] = entire array ✅

═══════════════════════════════════════════════════════════════════
 WHY THIS IS POWERFUL
═══════════════════════════════════════════════════════════════════

 Problem: "Update value of node v, query sum of subtree of v"

 Without Euler tour: DFS each time → O(N) per query
 With Euler tour:
   - Values stored in array at positions tin[v]
   - Subtree sum = range sum [tin[v], tout[v]]
   - Use BIT/SegTree: O(log N) per operation!

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌──────────────────────────────┬────────────┬──────────────┐
 │ Operation                    │ Time       │ Space        │
 ├──────────────────────────────┼────────────┼──────────────┤
 │ Build Euler tour (DFS)       │ O(N)       │ O(N)         │
 │ Subtree query (with SegTree) │ O(log N)   │ O(N)         │
 │ Point update                 │ O(log N)   │ —            │
 └──────────────────────────────┴────────────┴──────────────┘

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
vec<int> tin, tout, euler_order;
int timer_val;

void eulerTour(int v, int par) {
    tin[v] = timer_val;
    euler_order.pb(v);
    timer_val++;

    for (int u : adj[v]) {
        if (u == par) continue;
        eulerTour(u, v);
    }

    tout[v] = timer_val - 1;
}

// Check if u is in subtree of v
bool isInSubtree(int u, int v) {
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}

void solve() {
    int n; cin >> n;
    adj.assign(n + 1, {});
    tin.assign(n + 1, 0);
    tout.assign(n + 1, 0);
    euler_order.clear();
    timer_val = 0;

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    eulerTour(1, -1);

    cout << "Euler Tour (DFS order): ";
    for (int x : euler_order) cout << x << " ";
    cout << nl << nl;

    cout << "Node | tin | tout | Subtree range" << nl;
    cout << "─────┼─────┼──────┼──────────────" << nl;
    for (int i = 1; i <= n; i++) {
        cout << "  " << i << "  |  " << tin[i] << "  |  " << tout[i]
             << "   | [" << tin[i] << ", " << tout[i] << "] = {";
        for (int j = tin[i]; j <= tout[i]; j++) {
            if (j > tin[i]) cout << ",";
            cout << euler_order[j];
        }
        cout << "}" << nl;
    }

    // Example queries
    int q; cin >> q;
    while (q--) {
        int u, v; cin >> u >> v;
        if (isInSubtree(u, v))
            cout << u << " is in subtree of " << v << nl;
        else if (isInSubtree(v, u))
            cout << v << " is in subtree of " << u << nl;
        else
            cout << u << " and " << v << " are in different subtrees" << nl;
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
═══════════════════════════════════════════════════════════════════
 SAMPLE I/O
═══════════════════════════════════════════════════════════════════

Input:
1
6
1 2
1 3
2 4
2 5
3 6
2
4 2
4 3

Output:
Euler Tour (DFS order): 1 2 4 5 3 6

Node | tin | tout | Subtree range
─────┼─────┼──────┼──────────────
  1  |  0  |  5   | [0, 5] = {1,2,4,5,3,6}
  2  |  1  |  3   | [1, 3] = {2,4,5}
  3  |  4  |  5   | [4, 5] = {3,6}
  4  |  2  |  2   | [2, 2] = {4}
  5  |  3  |  3   | [3, 3] = {5}
  6  |  5  |  5   | [5, 5] = {6}

4 is in subtree of 2
4 and 3 are in different subtrees

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Euler tour: DFS order assigns tin[v], tout[v] to each node
 ✅ Subtree(v) = contiguous range [tin[v], tout[v]] in DFS order
 ✅ This converts subtree operations → range operations on array
 ✅ Use with BIT/SegTree for O(log N) subtree queries
 ✅ CSES: Subtree Queries — direct application (next file)
═══════════════════════════════════════════════════════════════════
*/

