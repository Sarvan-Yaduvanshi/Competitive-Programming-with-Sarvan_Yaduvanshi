/*
╔══════════════════════════════════════════════════════════════════╗
║       02 — PARENT ARRAY REPRESENTATION                          ║
║       Zero to GM Level — Tree Representations                    ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 CONCEPT
═══════════════════════════════════════════════════════════════════

 For a ROOTED tree, store just the parent of each node.
   par[root] = -1 (or 0)
   par[v] = parent of v

 This is the most COMPACT representation: just N integers!

 Tree (root=1):
         1
        / \
       2   3
      / \
     4   5

 Parent array: par[] = {_, -1, 1, 1, 2, 2}
                index:   0   1  2  3  4  5

═══════════════════════════════════════════════════════════════════
 CONVERTING BETWEEN REPRESENTATIONS
═══════════════════════════════════════════════════════════════════

 Parent Array → Adjacency List:
   for i = 2 to N:
     adj[i].push_back(par[i]);
     adj[par[i]].push_back(i);

 Adjacency List → Parent Array:
   DFS from root, set par[child] = current_node

═══════════════════════════════════════════════════════════════════
 DRY RUN: Parent Array → Adjacency List
═══════════════════════════════════════════════════════════════════

 par[] = {_, -1, 1, 1, 2, 2}  (root=1, N=5)

 i=2: par[2]=1 → adj[2]=[1], adj[1]=[2]
 i=3: par[3]=1 → adj[3]=[1], adj[1]=[2,3]
 i=4: par[4]=2 → adj[4]=[2], adj[2]=[1,4]
 i=5: par[5]=2 → adj[5]=[2], adj[2]=[1,4,5]

 Final:
   adj[1] = [2, 3]
   adj[2] = [1, 4, 5]
   adj[3] = [1]
   adj[4] = [2]
   adj[5] = [2]

═══════════════════════════════════════════════════════════════════
 DRY RUN: Adjacency List → Parent Array (via DFS)
═══════════════════════════════════════════════════════════════════

 adj[1]=[2,3], adj[2]=[1,4,5], adj[3]=[1], adj[4]=[2], adj[5]=[2]
 Root = 1

 DFS(1, parent=-1):
   par[1] = -1
   neighbors: [2, 3]
     2 ≠ -1 → DFS(2, parent=1)
       par[2] = 1
       neighbors: [1, 4, 5]
         1 == parent → skip
         4 ≠ 1 → DFS(4, parent=2)
           par[4] = 2
         5 ≠ 1 → DFS(5, parent=2)
           par[5] = 2
     3 ≠ -1 → DFS(3, parent=1)
       par[3] = 1

 Result: par[] = {_, -1, 1, 1, 2, 2} ✅

═══════════════════════════════════════════════════════════════════
 WHEN TO USE PARENT ARRAY
═══════════════════════════════════════════════════════════════════

 ✅ Finding ancestors (just follow par[v], par[par[v]], ...)
 ✅ LCA problems (climb from both nodes)
 ✅ Path to root (follow parent pointers)
 ✅ Compact storage (only N integers)

 ❌ Cannot find children directly (need to traverse all nodes)
 ❌ Not good for subtree operations
 ❌ Only works for ROOTED trees

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌──────────────────────────┬────────────┬──────────────┐
 │ Operation                │ Time       │ Space        │
 ├──────────────────────────┼────────────┼──────────────┤
 │ Store parent array       │ O(N)       │ O(N)         │
 │ Find parent of v         │ O(1)       │ —            │
 │ Find path to root        │ O(depth)   │ O(depth)     │
 │ Convert to adj list      │ O(N)       │ O(N)         │
 │ Find children of v       │ O(N) ❌    │ —            │
 └──────────────────────────┴────────────┴──────────────┘

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

void solve() {
    int n;
    cin >> n;

    // Read parent array (par[i] for i=2..N, root=1)
    vec<int> par(n + 1, -1);
    for (int i = 2; i <= n; i++) {
        cin >> par[i];
    }

    // ─── Convert Parent Array → Adjacency List ───
    vvec<int> adj(n + 1);
    for (int i = 2; i <= n; i++) {
        adj[i].pb(par[i]);
        adj[par[i]].pb(i);
    }

    cout << "Parent Array:" << nl;
    for (int i = 1; i <= n; i++) {
        cout << "  par[" << i << "] = " << par[i] << nl;
    }

    cout << nl << "Adjacency List:" << nl;
    for (int i = 1; i <= n; i++) {
        cout << "  " << i << " → [";
        for (int j = 0; j < sz(adj[i]); j++) {
            if (j) cout << ", ";
            cout << adj[i][j];
        }
        cout << "]" << nl;
    }

    // ─── Find path from any node to root ───
    int query;
    cin >> query;
    cout << nl << "Path from " << query << " to root:" << nl;
    cout << "  ";
    int cur = query;
    while (cur != -1) {
        cout << cur;
        cur = par[cur];
        if (cur != -1) cout << " → ";
    }
    cout << nl;

    // ─── Find depth of each node using parent array ───
    // depth[v] = depth[par[v]] + 1
    vec<int> depth(n + 1, 0);
    // Process nodes in order (since par[i] < i in typical input)
    for (int i = 2; i <= n; i++) {
        depth[i] = depth[par[i]] + 1;
    }

    cout << nl << "Depths:" << nl;
    for (int i = 1; i <= n; i++) {
        cout << "  depth[" << i << "] = " << depth[i] << nl;
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
5
1 1 2 2
4

Output:
Parent Array:
  par[1] = -1
  par[2] = 1
  par[3] = 1
  par[4] = 2
  par[5] = 2

Adjacency List:
  1 → [2, 3]
  2 → [1, 4, 5]
  3 → [1]
  4 → [2]
  5 → [2]

Path from 4 to root:
  4 → 2 → 1

Depths:
  depth[1] = 0
  depth[2] = 1
  depth[3] = 1
  depth[4] = 2
  depth[5] = 2
═══════════════════════════════════════════════════════════════════
*/

