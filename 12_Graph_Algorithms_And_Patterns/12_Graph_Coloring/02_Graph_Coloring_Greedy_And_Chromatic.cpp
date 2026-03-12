/*
╔══════════════════════════════════════════════════════════════════╗
║        02 — GREEDY GRAPH COLORING (Welsh-Powell)                ║
║        03 — CHROMATIC NUMBER via BITMASK DP                     ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
GREEDY COLORING
═══════════════════════════════════════════════════════════════════
Welsh-Powell: Sort vertices by degree (descending).
Assign smallest available color.
Gives at most Δ+1 colors. Time: O(V²) or O(V+E).

═══════════════════════════════════════════════════════════════════
CHROMATIC NUMBER (Exact, small n ≤ 20)
═══════════════════════════════════════════════════════════════════
Bitmask DP: dp[mask] = true if vertices in mask form independent set
Then use inclusion-exclusion or iterative DP.

For each mask, check if it's an independent set (no edge within).
Binary search on number of colors k and check if graph is k-colorable.

Time: O(2^n * n) for independent set check
      O(3^n) for partition into independent sets

═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
#endif
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
#define sz(x) ((int)(x).size())
#define nl '\n'

void solve() {
    int n, m; cin >> n >> m;
    vvec<int> adj(n);
    vec<int> adjMask(n, 0); // bitmask of neighbors (for small n)
    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v; u--;v--;
        adj[u].push_back(v); adj[v].push_back(u);
        if(n <= 20) { adjMask[u] |= (1<<v); adjMask[v] |= (1<<u); }
    }

    // GREEDY COLORING (Welsh-Powell)
    vec<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b){
        return sz(adj[a]) > sz(adj[b]);
    });

    vec<int> color(n, -1);
    int maxColor = 0;
    for(int u : order){
        set<int> used;
        for(int v : adj[u]) if(color[v]!=-1) used.insert(color[v]);
        int c = 0;
        while(used.count(c)) c++;
        color[u] = c;
        maxColor = max(maxColor, c);
    }

    cout << "Greedy coloring uses " << maxColor+1 << " colors" << nl;

    // EXACT CHROMATIC NUMBER (only for n <= 20)
    if(n <= 20) {
        // Check which masks are independent sets
        int N = 1 << n;
        vec<bool> isIndep(N, true);
        for(int mask = 0; mask < N; mask++) {
            for(int i = 0; i < n && isIndep[mask]; i++) {
                if(!(mask & (1<<i))) continue;
                if(mask & adjMask[i]) { isIndep[mask] = false; }
                // Actually we need: no two vertices in mask are adjacent
            }
        }
        // Recompute more carefully
        for(int mask = 0; mask < N; mask++) {
            isIndep[mask] = true;
            for(int i = 0; i < n && isIndep[mask]; i++) {
                if(!(mask & (1<<i))) continue;
                if(adjMask[i] & mask & ((1<<i)-1)) // check only bits < i
                    isIndep[mask] = false;
            }
        }

        // dp[mask] = min colors to color all vertices in mask
        vec<int> dp(N, n+1);
        dp[0] = 0;

        // Enumerate submasks
        for(int mask = 1; mask < N; mask++) {
            // Try all independent set submasks of mask
            for(int sub = mask; sub > 0; sub = (sub-1) & mask) {
                if(isIndep[sub]) {
                    dp[mask] = min(dp[mask], dp[mask ^ sub] + 1);
                }
            }
        }

        int fullMask = N - 1;
        cout << "Exact chromatic number: " << dp[fullMask] << nl;
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin>>TC; while(TC--) solve();
}

