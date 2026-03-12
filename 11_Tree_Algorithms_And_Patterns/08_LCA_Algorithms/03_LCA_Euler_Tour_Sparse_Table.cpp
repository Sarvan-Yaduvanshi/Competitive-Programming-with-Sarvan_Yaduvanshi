/*
╔══════════════════════════════════════════════════════════════════╗
║  03 — LCA VIA EULER TOUR + SPARSE TABLE (O(1) Query!)          ║
║  Zero to GM Level — LCA Algorithms                               ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 CONCEPT: Convert LCA → RMQ (Range Minimum Query)
═══════════════════════════════════════════════════════════════════

 1. Build Euler tour: write node each time you visit it (enter+exit)
    Array size = 2N-1
 2. Record first occurrence of each node: first[v]
 3. LCA(u,v) = node with MINIMUM DEPTH in Euler tour
    between first[u] and first[v]
 4. Use Sparse Table for O(1) RMQ!

═══════════════════════════════════════════════════════════════════
 DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree:
         1
        / \
       2   3
      / \
     4   5

 Euler tour (visit node at enter AND when returning):
   Enter 1, Enter 2, Enter 4, Exit 4 (back to 2), Enter 5,
   Exit 5 (back to 2), Exit 2 (back to 1), Enter 3, Exit 3

 Euler:  [1, 2, 4, 2, 5, 2, 1, 3, 1]
 Depth:  [0, 1, 2, 1, 2, 1, 0, 1, 0]
 Index:   0  1  2  3  4  5  6  7  8

 first[1]=0, first[2]=1, first[3]=7, first[4]=2, first[5]=4

 LCA(4, 5):
   first[4]=2, first[5]=4
   Range [2..4] in depth array: [2, 1, 2]
   Minimum depth = 1 at index 3 → Euler[3] = 2
   LCA = 2 ✅

 LCA(4, 3):
   first[4]=2, first[3]=7
   Range [2..7]: depth = [2, 1, 2, 1, 0, 1]
   Minimum = 0 at index 6 → Euler[6] = 1
   LCA = 1 ✅

═══════════════════════════════════════════════════════════════════
 SPARSE TABLE — O(N log N) build, O(1) query
═══════════════════════════════════════════════════════════════════

 sparse[i][k] = index of minimum in range [i, i + 2^k - 1]
 sparse[i][0] = i
 sparse[i][k] = argmin(sparse[i][k-1], sparse[i + 2^(k-1)][k-1])

 Query [l, r]:
   k = floor(log2(r-l+1))
   answer = argmin(sparse[l][k], sparse[r - 2^k + 1][k])
   (Two overlapping ranges that cover [l,r])

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 Build:  O(N log N) for Euler tour + sparse table
 Query:  O(1) per LCA query!
 Space:  O(N log N)

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

// Euler tour arrays
vec<int> euler, euler_depth;
int first_occ[MAXN]; // first occurrence of node v in euler tour
int depth_arr[MAXN];
int euler_sz;

void eulerDFS(int v, int par, int d) {
    depth_arr[v] = d;
    first_occ[v] = euler_sz;
    euler.pb(v);
    euler_depth.pb(d);
    euler_sz++;

    for (int u : adj[v]) {
        if (u == par) continue;
        eulerDFS(u, v, d + 1);
        euler.pb(v);          // add v again when returning
        euler_depth.pb(d);
        euler_sz++;
    }
}

// Sparse Table for RMQ (range minimum query on depth)
int sparse[2 * MAXN][LOG]; // stores INDEX of min depth
int lg[2 * MAXN];

void buildSparseTable() {
    int n = euler_sz;

    // Precompute log2
    lg[1] = 0;
    for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;

    // Base case
    for (int i = 0; i < n; i++) sparse[i][0] = i;

    // Build
    for (int k = 1; (1 << k) <= n; k++) {
        for (int i = 0; i + (1 << k) - 1 < n; i++) {
            int left = sparse[i][k - 1];
            int right = sparse[i + (1 << (k - 1))][k - 1];
            sparse[i][k] = (euler_depth[left] <= euler_depth[right]) ? left : right;
        }
    }
}

// RMQ query: index of minimum in euler_depth[l..r]
int rmq(int l, int r) {
    int k = lg[r - l + 1];
    int left = sparse[l][k];
    int right = sparse[r - (1 << k) + 1][k];
    return (euler_depth[left] <= euler_depth[right]) ? left : right;
}

// LCA in O(1)!
int lca(int u, int v) {
    int l = first_occ[u], r = first_occ[v];
    if (l > r) swap(l, r);
    return euler[rmq(l, r)];
}

int dist(int u, int v) {
    return depth_arr[u] + depth_arr[v] - 2 * depth_arr[lca(u, v)];
}

void solve() {
    int n; cin >> n;
    adj.assign(n + 1, {});
    euler.clear();
    euler_depth.clear();
    euler_sz = 0;

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    eulerDFS(1, 0, 0);
    buildSparseTable();

    int q; cin >> q;
    while (q--) {
        int u, v; cin >> u >> v;
        int l = lca(u, v);
        cout << "LCA(" << u << "," << v << ") = " << l
             << ", dist = " << dist(u, v) << nl;
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
7
1 2
1 3
2 4
2 5
3 6
4 7
3
7 6
4 5
7 3

Output:
LCA(7,6) = 1, dist = 5
LCA(4,5) = 2, dist = 2
LCA(7,3) = 1, dist = 4

═══════════════════════════════════════════════════════════════════
 COMPARISON OF LCA METHODS
═══════════════════════════════════════════════════════════════════

 ┌─────────────────────────┬──────────────┬──────────────┬────────┐
 │ Method                  │ Build Time   │ Query Time   │ Space  │
 ├─────────────────────────┼──────────────┼──────────────┼────────┤
 │ Naive (climb)           │ O(N)         │ O(N)         │ O(N)   │
 │ Binary Lifting          │ O(N log N)   │ O(log N)     │O(NlogN)│
 │ Euler Tour + Sparse Tbl │ O(N log N)   │ O(1) ⭐      │O(NlogN)│
 │ Tarjan Offline          │ O(N α(N))    │ offline      │ O(N)   │
 └─────────────────────────┴──────────────┴──────────────┴────────┘

 ✅ This method gives O(1) query — fastest possible!
 ✅ But can't do Kth ancestor (binary lifting can)
 ✅ For pure LCA queries, this is the best
═══════════════════════════════════════════════════════════════════
*/

