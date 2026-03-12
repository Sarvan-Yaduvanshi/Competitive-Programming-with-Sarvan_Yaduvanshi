/*
╔══════════════════════════════════════════════════════════════════╗
║       05 — TREE INPUT PATTERNS FOR COMPETITIVE PROGRAMMING      ║
║       Zero to GM Level — Tree Foundations                        ║
╚══════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS
─────────────────
 1. Common Input Formats in CP
 2. Format 1: Edge List (Most Common!)
 3. Format 2: Parent Array
 4. Format 3: Weighted Edge List
 5. Format 4: Rooted tree with children
 6. Dry Run: Reading each format
 7. Code: Read all formats

═══════════════════════════════════════════════════════════════════
 1. COMMON INPUT FORMATS IN CP
═══════════════════════════════════════════════════════════════════

 In competitive programming, trees can be given in many formats.
 You MUST be able to read all of them quickly!

 ┌──────────────────────┬──────────────────────────────────────────┐
 │ Format               │ When you see it                          │
 ├──────────────────────┼──────────────────────────────────────────┤
 │ Edge list (u,v)      │ Codeforces, CSES, most contests          │
 │ Parent array         │ CSES, AtCoder (rooted tree problems)     │
 │ Weighted edges       │ Shortest path on tree, MST problems      │
 │ Adjacency list       │ Rare in input, but common in code        │
 └──────────────────────┴──────────────────────────────────────────┘

═══════════════════════════════════════════════════════════════════
 2. FORMAT 1: EDGE LIST (MOST COMMON!)
═══════════════════════════════════════════════════════════════════

 Input format:
   N            (number of nodes)
   u₁ v₁       (edge between u₁ and v₁)
   u₂ v₂
   ...
   u_{N-1} v_{N-1}   (N-1 edges total)

 Example:
   5
   1 2
   1 3
   2 4
   2 5

 Tree:
         1
        / \
       2   3
      / \
     4   5

 How to read: Build adjacency list
   adj[u].push_back(v);
   adj[v].push_back(u);

═══════════════════════════════════════════════════════════════════
 3. FORMAT 2: PARENT ARRAY
═══════════════════════════════════════════════════════════════════

 Input format:
   N            (number of nodes, root is node 1)
   p₂ p₃ ... pₙ   (parent of node i for i = 2..N)

 Example:
   5
   1 1 2 2

 Meaning:
   parent[2] = 1
   parent[3] = 1
   parent[4] = 2
   parent[5] = 2

 Tree (root = 1):
         1
        / \
       2   3
      / \
     4   5

 How to read: Convert to adjacency list
   for i = 2 to N:
     adj[i].push_back(parent[i]);
     adj[parent[i]].push_back(i);

═══════════════════════════════════════════════════════════════════
 4. FORMAT 3: WEIGHTED EDGE LIST
═══════════════════════════════════════════════════════════════════

 Input format:
   N
   u₁ v₁ w₁    (edge with weight w)
   u₂ v₂ w₂
   ...

 Example:
   4
   1 2 5
   1 3 3
   2 4 2

 Tree with weights:
         1
        / \(5)  \(3)
       2       3
      /(2)
     4

 How to read: adj[u].push_back({v, w});

═══════════════════════════════════════════════════════════════════
 5. DRY RUN: READING EDGE LIST
═══════════════════════════════════════════════════════════════════

 Input:
   5
   1 2
   1 3
   2 4
   2 5

 Step 1: Read N = 5
 Step 2: Create adj[6] (1-indexed, size N+1)
 Step 3: Read N-1 = 4 edges:
   Edge (1,2): adj[1]={2}, adj[2]={1}
   Edge (1,3): adj[1]={2,3}, adj[3]={1}
   Edge (2,4): adj[2]={1,4}, adj[4]={2}
   Edge (2,5): adj[2]={1,4,5}, adj[5]={2}

 Final adjacency list:
   adj[1] = [2, 3]
   adj[2] = [1, 4, 5]
   adj[3] = [1]
   adj[4] = [2]
   adj[5] = [2]

═══════════════════════════════════════════════════════════════════
 6. CODE: ALL INPUT FORMATS
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

// ═══════════════════════════════════════════════════════════════
// FORMAT 1: Edge List (MOST COMMON in Codeforces/CSES)
// ═══════════════════════════════════════════════════════════════
void readEdgeList() {
    int n;
    cin >> n;
    vvec<int> adj(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    // Print adjacency list
    cout << "Edge List → Adjacency List:" << nl;
    for (int i = 1; i <= n; i++) {
        cout << "  " << i << " → [";
        for (int j = 0; j < sz(adj[i]); j++) {
            if (j > 0) cout << ", ";
            cout << adj[i][j];
        }
        cout << "]" << nl;
    }
}

// ═══════════════════════════════════════════════════════════════
// FORMAT 2: Parent Array
// ═══════════════════════════════════════════════════════════════
void readParentArray() {
    int n;
    cin >> n;

    vec<int> par(n + 1, 0);
    vvec<int> adj(n + 1);

    // Root is node 1 (no parent given)
    par[1] = 0;
    for (int i = 2; i <= n; i++) {
        cin >> par[i];
        adj[i].pb(par[i]);
        adj[par[i]].pb(i);
    }

    cout << "Parent Array → Adjacency List:" << nl;
    for (int i = 1; i <= n; i++) {
        cout << "  " << i << " → [";
        for (int j = 0; j < sz(adj[i]); j++) {
            if (j > 0) cout << ", ";
            cout << adj[i][j];
        }
        cout << "]" << nl;
    }
}

// ═══════════════════════════════════════════════════════════════
// FORMAT 3: Weighted Edge List
// ═══════════════════════════════════════════════════════════════
void readWeightedEdgeList() {
    int n;
    cin >> n;

    vector<vector<pii>> adj(n + 1); // {neighbor, weight}

    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }

    cout << "Weighted Edge List → Adjacency List:" << nl;
    for (int i = 1; i <= n; i++) {
        cout << "  " << i << " → [";
        for (int j = 0; j < sz(adj[i]); j++) {
            if (j > 0) cout << ", ";
            cout << "(" << adj[i][j].fi << ",w=" << adj[i][j].se << ")";
        }
        cout << "]" << nl;
    }
}

void solve() {
    int format;
    cin >> format;

    if (format == 1) readEdgeList();
    else if (format == 2) readParentArray();
    else if (format == 3) readWeightedEdgeList();
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
3
1
5
1 2
1 3
2 4
2 5
2
5
1 1 2 2
3
4
1 2 5
1 3 3
2 4 2

Output:
Edge List → Adjacency List:
  1 → [2, 3]
  2 → [1, 4, 5]
  3 → [1]
  4 → [2]
  5 → [2]
Parent Array → Adjacency List:
  1 → [2, 3]
  2 → [1, 4]
  3 → [1, 5]
  4 → [2]
  5 → [3]
Weighted Edge List → Adjacency List:
  1 → [(2,w=5), (3,w=3)]
  2 → [(1,w=5), (4,w=2)]
  3 → [(1,w=3)]
  4 → [(2,w=2)]

═══════════════════════════════════════════════════════════════════
 CP TIPS — FAST INPUT PATTERNS
═══════════════════════════════════════════════════════════════════

 🔑 EDGE LIST (99% of tree problems):
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

 🔑 PARENT ARRAY:
    for (int i = 2; i <= n; i++) {
        cin >> par[i];
        adj[i].pb(par[i]); adj[par[i]].pb(i);
    }

 🔑 WEIGHTED EDGES:
    for (int i = 0; i < n-1; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].pb({v,w}); adj[v].pb({u,w});
    }

 ⚠️ ALWAYS use 1-indexed adjacency list (size N+1)
 ⚠️ ALWAYS add BOTH directions for undirected tree
═══════════════════════════════════════════════════════════════════
*/

