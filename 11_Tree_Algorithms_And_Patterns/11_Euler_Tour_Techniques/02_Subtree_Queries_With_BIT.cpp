/*
╔══════════════════════════════════════════════════════════════════╗
║  02 — SUBTREE QUERIES WITH BIT (CSES Subtree Queries)          ║
║  Zero to GM Level — Euler Tour Techniques                        ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 PROBLEM (CSES Subtree Queries)
═══════════════════════════════════════════════════════════════════

 Given a rooted tree with node values:
   Type 1: Update value of node s to x
   Type 2: Query sum of values in subtree of s

═══════════════════════════════════════════════════════════════════
 APPROACH
═══════════════════════════════════════════════════════════════════

 1. Euler tour: flatten tree so subtree(s) = range [tin[s], tout[s]]
 2. Store values in BIT at position tin[v]
 3. Update node s: BIT point update at tin[s]
 4. Subtree sum of s: BIT range sum [tin[s], tout[s]]

═══════════════════════════════════════════════════════════════════
 DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree: val = [_, 4, 2, 5, 1, 3]
         1(4)
        / \
    (2)2   3(5)
      / \
  (1)4   5(3)

 Euler tour: tin=[_,0,1,4,2,3], tout=[_,4,3,4,2,3]
 DFS order: [1, 2, 4, 5, 3]
 BIT array: [4, 2, 1, 3, 5] (values in DFS order)

 Query subtree sum of 2: range [1, 3] = val[2]+val[4]+val[5] = 2+1+3 = 6

 Update node 4 to value 10: BIT update at index 2 (add 10-1=9)
 BIT array: [4, 2, 10, 3, 5]

 Query subtree sum of 2: range [1, 3] = 2+10+3 = 15 ✅

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

// ═══════════════════════════════════════════════════════════
// BIT (Fenwick Tree) for range sum queries
// ═══════════════════════════════════════════════════════════
struct BIT {
    int n;
    vec<i64> tree;

    BIT() : n(0) {}
    BIT(int n) : n(n), tree(n + 1, 0) {}

    void update(int i, i64 delta) { // 1-indexed
        for (++i; i <= n; i += i & (-i))
            tree[i] += delta;
    }

    i64 query(int i) { // prefix sum [0, i]
        i64 s = 0;
        for (++i; i > 0; i -= i & (-i))
            s += tree[i];
        return s;
    }

    i64 query(int l, int r) { // range sum [l, r]
        return query(r) - (l > 0 ? query(l - 1) : 0);
    }
};

vvec<int> adj;
vec<int> tin, tout;
vec<i64> val;
int timer_val;

void eulerTour(int v, int par) {
    tin[v] = timer_val++;
    for (int u : adj[v])
        if (u != par) eulerTour(u, v);
    tout[v] = timer_val - 1;
}

void solve() {
    int n, q;
    cin >> n >> q;

    val.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> val[i];

    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    tin.assign(n + 1, 0);
    tout.assign(n + 1, 0);
    timer_val = 0;
    eulerTour(1, -1);

    // Initialize BIT with values in Euler order
    BIT bit(n);
    for (int i = 1; i <= n; i++) {
        bit.update(tin[i], val[i]);
    }

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            // Update value of node s to x
            int s; i64 x; cin >> s >> x;
            bit.update(tin[s], x - val[s]); // add difference
            val[s] = x;
        } else {
            // Query subtree sum of s
            int s; cin >> s;
            cout << bit.query(tin[s], tout[s]) << nl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1;
    // cin >> TC; // CSES single test case
    while (TC--) solve();
    return 0;
}

/*
═══════════════════════════════════════════════════════════════════
 SAMPLE I/O (CSES format)
═══════════════════════════════════════════════════════════════════

Input:
5 3
4 2 5 1 3
1 2
1 3
2 4
2 5
2 1
1 4 10
2 2

Output:
15
15

 Explanation:
   Query subtree(1): 4+2+5+1+3 = 15
   Update node 4 → 10
   Query subtree(2): 2+10+3 = 15

═══════════════════════════════════════════════════════════════════
 KEY TAKEAWAYS
═══════════════════════════════════════════════════════════════════
 ✅ Euler tour + BIT = O(log N) subtree queries + updates
 ✅ Map node v to position tin[v] in BIT
 ✅ Subtree sum of v = BIT range query [tin[v], tout[v]]
 ✅ Point update: BIT.update(tin[s], delta)
 ✅ CSES: Subtree Queries — exactly this pattern
═══════════════════════════════════════════════════════════════════
*/

