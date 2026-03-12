/*
╔══════════════════════════════════════════════════════════════════╗
║  01 — KTH ANCESTOR WITH BINARY LIFTING                         ║
║  Zero to GM Level — Binary Lifting                               ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
 CONCEPT — Same up[][] table from LCA
═══════════════════════════════════════════════════════════════════

 To find the K-th ancestor of node v:
 Decompose K in binary, jump for each set bit.

 Example: K = 5 = 101 in binary
   Jump 2^0 = 1 step, then 2^2 = 4 steps (total 5)
   v → up[v][0] → up[...][2]

═══════════════════════════════════════════════════════════════════
 DRY RUN
═══════════════════════════════════════════════════════════════════

 Tree:
   1—2—3—4—5—6—7—8 (a chain/path)

 Find 5th ancestor of 8:
   K=5 = 101₂
   bit 0 set: 8 → up[8][0] = 7     (jumped 1)
   bit 1 not set: skip
   bit 2 set: 7 → up[7][2] = 3     (jumped 4)
   Total: 1+4 = 5, answer = 3 ✅ (8→7→6→5→4→3)

═══════════════════════════════════════════════════════════════════
 CSES: Company Queries I — direct application
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
#include <cstring>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define pb push_back
#define nl '\n'

const int LOG = 20;
const int MAXN = 200005;

vvec<int> adj;
int up[MAXN][LOG];
int depth[MAXN];

void dfs(int v, int p, int d) {
    depth[v] = d;
    up[v][0] = p;
    for (int k = 1; k < LOG; k++)
        up[v][k] = up[up[v][k-1]][k-1];
    for (int u : adj[v])
        if (u != p) dfs(u, v, d + 1);
}

int kthAncestor(int v, int k) {
    for (int i = LOG - 1; i >= 0; i--) {
        if (k >= (1 << i)) {
            v = up[v][i];
            k -= (1 << i);
            if (v == 0) return -1; // went above root
        }
    }
    return v;
}

void solve() {
    int n, q;
    cin >> n >> q;
    adj.assign(n + 1, {});
    memset(up, 0, sizeof(up));

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }
    dfs(1, 0, 0);

    while (q--) {
        int v, k; cin >> v >> k;
        int ans = kthAncestor(v, k);
        cout << (ans <= 0 ? -1 : ans) << nl;
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
 Time: O(N log N) build, O(log N) per query
 Space: O(N log N)

 CSES Company Queries I: exactly this problem.
*/

