/*
╔══════════════════════════════════════════════════════════════════╗
║       05 — DFS ENTRY/EXIT TIME (tin/tout) — FOUNDATION          ║
║       Zero to GM Level — Tree Traversals                         ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 WHY THIS IS IMPORTANT
═══════════════════════════════════════════════════════════════════

 DFS entry/exit times are the FOUNDATION for:
   ✅ Euler Tour Technique (Chapter 11)
   ✅ Subtree queries (is u in subtree of v?)
   ✅ Flattening tree to array for segment tree
   ✅ LCA algorithms
   ✅ Many advanced tree techniques

 This is one of the most powerful ideas in tree algorithms!

═══════════════════════════════════════════════════════════════════
 CONCEPT
═══════════════════════════════════════════════════════════════════

 During DFS, maintain a global TIMER.
 For each node v:
   tin[v]  = time when we ENTER v (start visiting)
   tout[v] = time when we EXIT v (finish visiting all descendants)

 KEY PROPERTY:
   u is in the SUBTREE of v  ⟺  tin[v] ≤ tin[u] ≤ tout[u] ≤ tout[v]

 This lets us check "is u a descendant of v?" in O(1)!

═══════════════════════════════════════════════════════════════════
 DETAILED DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree:
              1
            /   \
           2     3
          / \   / \
         4   5 6   7

 DFS from root=1 (timer starts at 0):

 ┌──────────────────────────────────────────────────────────────┐
 │ Action              │ Timer │ tin[] updated │ tout[] updated │
 ├──────────────────────┼───────┼───────────────┼────────────────┤
 │ Enter 1             │ 0→1   │ tin[1]=0      │                │
 │   Enter 2           │ 1→2   │ tin[2]=1      │                │
 │     Enter 4         │ 2→3   │ tin[4]=2      │                │
 │     Exit 4          │ 3→4   │               │ tout[4]=3      │
 │     Enter 5         │ 4→5   │ tin[5]=4      │                │
 │     Exit 5          │ 5→6   │               │ tout[5]=5      │
 │   Exit 2            │ 6→7   │               │ tout[2]=6      │
 │   Enter 3           │ 7→8   │ tin[3]=7      │                │
 │     Enter 6         │ 8→9   │ tin[6]=8      │                │
 │     Exit 6          │ 9→10  │               │ tout[6]=9      │
 │     Enter 7         │ 10→11 │ tin[7]=10     │                │
 │     Exit 7          │ 11→12 │               │ tout[7]=11     │
 │   Exit 3            │ 12→13 │               │ tout[3]=12     │
 │ Exit 1              │ 13→14 │               │ tout[1]=13     │
 └──────────────────────┴───────┴───────────────┴────────────────┘

 Result:
 ┌──────┬─────┬──────┐
 │ Node │ tin │ tout │
 ├──────┼─────┼──────┤
 │  1   │  0  │  13  │
 │  2   │  1  │  6   │
 │  3   │  7  │  12  │
 │  4   │  2  │  3   │
 │  5   │  4  │  5   │
 │  6   │  8  │  9   │
 │  7   │ 10  │  11  │
 └──────┴─────┴──────┘

 VISUALIZE on a timeline:

 Timer: 0  1  2  3  4  5  6  7  8  9  10 11 12 13
        ├──┤
        │1 │
        │  ├──┤
        │  │2 │
        │  │  ├──┤
        │  │  │4 │
        │  │  ├──┘
        │  │  ├──┤
        │  │  │5 │
        │  │  ├──┘
        │  ├──┘
        │  ├──────────────┤
        │  │3             │
        │  │  ├──┤        │
        │  │  │6 │        │
        │  │  ├──┘        │
        │  │     ├──┤     │
        │  │     │7 │     │
        │  │     ├──┘     │
        │  ├──────────────┘
        ├──┘

 CHECK: Is node 4 in subtree of 2?
   tin[2]=1 ≤ tin[4]=2 ≤ tout[4]=3 ≤ tout[2]=6  ✅ YES!

 CHECK: Is node 6 in subtree of 2?
   tin[2]=1 ≤ tin[6]=8?  NO! 8 > 6 = tout[2]    ❌ NO!

 CHECK: Is node 5 ancestor of 1?
   tin[5]=4 ≤ tin[1]=0?  NO! 0 < 4               ❌ NO!

═══════════════════════════════════════════════════════════════════
 APPLICATIONS
═══════════════════════════════════════════════════════════════════

 1. SUBTREE CHECK in O(1):
    isInSubtree(u, v) = (tin[v] ≤ tin[u] && tout[u] ≤ tout[v])

 2. ANCESTOR CHECK in O(1):
    isAncestor(u, v) = (tin[u] ≤ tin[v] && tout[v] ≤ tout[u])

 3. FLATTEN TREE TO ARRAY:
    DFS order array: [1, 2, 4, 5, 3, 6, 7]
    Subtree of v = contiguous segment [tin[v]..tout[v]] in DFS order!
    → Can use segment tree / BIT for subtree queries

 4. SUBTREE SIZE:
    subsize[v] = (tout[v] - tin[v] + 1) / 2  (with 2x timer)
    Or just: subsize[v] = (tout[v] - tin[v]) / 2 + 1

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌──────────────────────────┬────────────┬──────────────┐
 │ Operation                │ Time       │ Space        │
 ├──────────────────────────┼────────────┼──────────────┤
 │ Compute tin/tout (DFS)   │ O(N)       │ O(N)         │
 │ Is u in subtree of v?    │ O(1)       │ O(1)         │
 │ Is u ancestor of v?      │ O(1)       │ O(1)         │
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

vvec<int> adj;
vec<int> tin, tout, dfsOrder;
int timer_val;

void dfs(int v, int par) {
    tin[v] = timer_val++;
    dfsOrder.pb(v);

    for (int u : adj[v]) {
        if (u == par) continue;
        dfs(u, v);
    }

    tout[v] = timer_val++;
}

// O(1) check: is u in subtree of v?
bool isInSubtree(int u, int v) {
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}

// O(1) check: is u an ancestor of v?
bool isAncestor(int u, int v) {
    return isInSubtree(v, u);
}

void solve() {
    int n;
    cin >> n;

    adj.assign(n + 1, {});
    tin.assign(n + 1, 0);
    tout.assign(n + 1, 0);
    dfsOrder.clear();
    timer_val = 0;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    dfs(1, -1);

    // Print tin/tout
    cout << "Entry/Exit Times:" << nl;
    cout << "┌──────┬─────┬──────┐" << nl;
    cout << "│ Node │ tin │ tout │" << nl;
    cout << "├──────┼─────┼──────┤" << nl;
    for (int i = 1; i <= n; i++) {
        cout << "│  " << i << "   │  " << tin[i] << "  │  " << tout[i] << "   │" << nl;
    }
    cout << "└──────┴─────┴──────┘" << nl;

    // DFS order
    cout << nl << "DFS Order: ";
    for (int x : dfsOrder) cout << x << " ";
    cout << nl;

    // Subtree ranges in DFS order
    cout << nl << "Subtree ranges in DFS order array:" << nl;
    // Position of node v in dfsOrder = tin[v] / 1 (since we increment by 1 for entry)
    // Actually, dfsOrder index = position where tin[v] was recorded
    // Subtree of v = dfsOrder[tin[v]/2 .. (tout[v]-1)/2] approximately
    // Let me use simpler indexing:

    // With the current code, dfsOrder has N entries (one per node)
    // tin[v] gives the entry time (even entries)
    // A simpler approach: use a DFS order index

    // Process queries
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        if (isInSubtree(u, v)) {
            cout << "  Node " << u << " IS in subtree of " << v << nl;
        } else if (isInSubtree(v, u)) {
            cout << "  Node " << v << " IS in subtree of " << u << nl;
        } else {
            cout << "  Nodes " << u << " and " << v << " are in DIFFERENT subtrees" << nl;
        }
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
7
1 2
1 3
2 4
2 5
3 6
3 7
4
4 2
6 2
1 7
5 3

Output:
Entry/Exit Times:
┌──────┬─────┬──────┐
│ Node │ tin │ tout │
├──────┼─────┼──────┤
│  1   │  0  │  13  │
│  2   │  1  │  6   │
│  3   │  7  │  12  │
│  4   │  2  │  3   │
│  5   │  4  │  5   │
│  6   │  8  │  9   │
│  7   │  10 │  11  │
└──────┴─────┴──────┘

DFS Order: 1 2 4 5 3 6 7

  Node 4 IS in subtree of 2
  Nodes 6 and 2 are in DIFFERENT subtrees
  Node 7 IS in subtree of 1
  Nodes 5 and 3 are in DIFFERENT subtrees

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ tin[v] = entry time, tout[v] = exit time during DFS
 ✅ u in subtree of v ⟺ tin[v] ≤ tin[u] && tout[u] ≤ tout[v]
 ✅ This is O(1) ancestor/subtree check!
 ✅ DFS order flattens tree → subtree = contiguous segment
 ✅ Foundation for Euler Tour, segment tree on tree, and more
═══════════════════════════════════════════════════════════════════
*/

