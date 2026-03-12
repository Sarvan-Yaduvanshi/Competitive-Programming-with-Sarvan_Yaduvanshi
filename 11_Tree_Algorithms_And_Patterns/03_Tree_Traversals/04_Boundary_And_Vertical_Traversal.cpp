/*
╔══════════════════════════════════════════════════════════════════╗
║       04 — BOUNDARY & VERTICAL TRAVERSAL                        ║
║       Zero to GM Level — Tree Traversals                         ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 VERTICAL ORDER TRAVERSAL
═══════════════════════════════════════════════════════════════════

 Assign a COLUMN number to each node:
   Root = column 0
   Left child = parent_column - 1
   Right child = parent_column + 1

 Tree:
              1 (col=0)
            /   \
     (col=-1)2   3(col=1)
          / \   / \
   (c=-2)4 5(0)6(0) 7(c=2)

 Columns:
   col -2: [4]
   col -1: [2]
   col  0: [1, 5, 6]    ← nodes at same column, sorted by level
   col  1: [3]
   col  2: [7]

 Vertical order: [4] [2] [1,5,6] [3] [7]

═══════════════════════════════════════════════════════════════════
 BOUNDARY TRAVERSAL
═══════════════════════════════════════════════════════════════════

 Walk around the boundary of the tree:
   1. Left boundary (excluding leaves)
   2. All leaves (left to right)
   3. Right boundary (bottom to top, excluding leaves)

 Tree:
              1
            /   \
           2     3
          / \   / \
         4   5 6   7
            / \
           8   9

 Left boundary:  [1, 2]        (go left: 1→2, stop at leaf)
 Leaves:         [4, 8, 9, 6, 7]  (all leaves left to right)
 Right boundary:  [3]          (go right: 3, exclude 7 (leaf))

 Boundary = [1, 2, 4, 8, 9, 6, 7, 3]

═══════════════════════════════════════════════════════════════════
 DRY RUN: VERTICAL ORDER TRAVERSAL
═══════════════════════════════════════════════════════════════════

 Tree:
              1
            /   \
           2     3
          / \     \
         4   5     6

 BFS with columns:
 Queue: [(1, col=0)]

 Pop (1, col=0): map[0] = [1]
   Push (2, col=-1), (3, col=1)

 Pop (2, col=-1): map[-1] = [2]
   Push (4, col=-2), (5, col=0)

 Pop (3, col=1): map[1] = [3]
   Push (6, col=2)

 Pop (4, col=-2): map[-2] = [4]
 Pop (5, col=0): map[0] = [1, 5]
 Pop (6, col=2): map[2] = [6]

 Result (sorted by column):
   col -2: [4]
   col -1: [2]
   col  0: [1, 5]
   col  1: [3]
   col  2: [6]

═══════════════════════════════════════════════════════════════════
 COMPLEXITY
═══════════════════════════════════════════════════════════════════

 ┌──────────────────────────┬────────────────┬──────────────┐
 │ Traversal                │ Time           │ Space        │
 ├──────────────────────────┼────────────────┼──────────────┤
 │ Vertical order (BFS+map) │ O(N log N)     │ O(N)         │
 │ Boundary traversal       │ O(N)           │ O(N)         │
 └──────────────────────────┴────────────────┴──────────────┘

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

vec<int> L, R; // left[i], right[i] children (0 = null)
int n;

// ═══════════════════════════════════════════════════════════════
// VERTICAL ORDER TRAVERSAL (BFS + column tracking)
// ═══════════════════════════════════════════════════════════════
void verticalOrder(int root) {
    if (root == 0) return;

    // map<column, vector of (level, node)>
    map<int, vec<pii>> cols;
    queue<tuple<int, int, int>> q; // (node, column, level)
    q.push({root, 0, 0});

    while (!q.empty()) {
        auto [node, col, level] = q.front(); q.pop();
        cols[col].pb({level, node});
        if (L[node]) q.push({L[node], col - 1, level + 1});
        if (R[node]) q.push({R[node], col + 1, level + 1});
    }

    cout << "Vertical Order Traversal:" << nl;
    for (auto& [col, nodes] : cols) {
        sort(all(nodes)); // sort by level, then by value
        cout << "  Column " << col << ": [";
        for (int i = 0; i < sz(nodes); i++) {
            if (i) cout << ", ";
            cout << nodes[i].se;
        }
        cout << "]" << nl;
    }
}

// ═══════════════════════════════════════════════════════════════
// BOUNDARY TRAVERSAL
// ═══════════════════════════════════════════════════════════════
bool isLeaf(int v) {
    return v != 0 && L[v] == 0 && R[v] == 0;
}

void addLeftBoundary(int v, vec<int>& res) {
    int cur = L[v]; // start from root's left child
    while (cur != 0) {
        if (!isLeaf(cur)) res.pb(cur);
        if (L[cur]) cur = L[cur];
        else cur = R[cur];
    }
}

void addLeaves(int v, vec<int>& res) {
    if (v == 0) return;
    if (isLeaf(v)) { res.pb(v); return; }
    addLeaves(L[v], res);
    addLeaves(R[v], res);
}

void addRightBoundary(int v, vec<int>& res) {
    int cur = R[v]; // start from root's right child
    vec<int> tmp;
    while (cur != 0) {
        if (!isLeaf(cur)) tmp.pb(cur);
        if (R[cur]) cur = R[cur];
        else cur = L[cur];
    }
    reverse(all(tmp)); // bottom to top
    for (int x : tmp) res.pb(x);
}

void boundaryTraversal(int root) {
    if (root == 0) return;
    vec<int> res;
    res.pb(root); // add root
    if (!isLeaf(root)) {
        addLeftBoundary(root, res);
        addLeaves(root, res);
        addRightBoundary(root, res);
    }

    cout << "Boundary Traversal:" << nl << "  ";
    for (int i = 0; i < sz(res); i++) {
        if (i) cout << " → ";
        cout << res[i];
    }
    cout << nl;
}

void solve() {
    cin >> n;
    L.assign(n + 1, 0);
    R.assign(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> L[i] >> R[i];
    }

    verticalOrder(1);
    cout << nl;
    boundaryTraversal(1);
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
2 3
4 5
6 7
0 0
0 0
0 0
0 0

Tree:
         1
        / \
       2   3
      / \ / \
     4  5 6  7

Output:
Vertical Order Traversal:
  Column -2: [4]
  Column -1: [2]
  Column 0: [1, 5, 6]
  Column 1: [3]
  Column 2: [7]

Boundary Traversal:
  1 → 2 → 4 → 5 → 6 → 7 → 3

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Vertical order: BFS with column tracking using map
 ✅ Boundary: left boundary + leaves + right boundary (reversed)
 ✅ Column assignment: left child = col-1, right child = col+1
 ✅ These are common interview problems (LeetCode 987, 199, 545)
═══════════════════════════════════════════════════════════════════
*/

