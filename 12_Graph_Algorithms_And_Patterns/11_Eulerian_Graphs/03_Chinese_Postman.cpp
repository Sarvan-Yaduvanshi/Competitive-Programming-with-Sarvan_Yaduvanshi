/*
╔══════════════════════════════════════════════════════════════════╗
║         03 — CHINESE POSTMAN PROBLEM                            ║
║         Shortest walk visiting every EDGE at least once         ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

EULER CIRCUIT visits every edge exactly once — requires all even degree.
CHINESE POSTMAN: what if some vertices have odd degree?

Answer: find minimum weight set of edges to ADD (duplicate) to make
all degrees even, then find Euler circuit on the new graph.

═══════════════════════════════════════════════════════════════════
ALGORITHM (Undirected)
═══════════════════════════════════════════════════════════════════

1. Find all vertices with ODD degree (always even count)
2. Find shortest path between all pairs of odd-degree vertices
   (Floyd-Warshall or multiple Dijkstra)
3. Find MINIMUM WEIGHT PERFECT MATCHING on odd-degree vertices
   (Bitmask DP for small count, or general matching)
4. Answer = sum of all original edges + matching weight

═══════════════════════════════════════════════════════════════════
DRY RUN
═══════════════════════════════════════════════════════════════════

Graph:
    1 ──(3)── 2
    │         │
   (1)       (2)
    │         │
    3 ──(4)── 4

Degrees: 1:2, 2:2, 3:2, 4:2 → ALL EVEN!
Chinese postman cost = sum of edges = 3+1+2+4 = 10 (it's Eulerian)

Different example:
    1 ──(1)── 2 ──(2)── 3
              │
             (3)
              │
              4

Degrees: 1:1(odd), 2:3(odd), 3:1(odd), 4:1(odd)
Odd vertices: {1, 2, 3, 4}

Shortest paths between odd pairs:
  1↔2: 1, 1↔3: 3, 1↔4: 4, 2↔3: 2, 2↔4: 3, 3↔4: 5

Min perfect matching on {1,2,3,4}:
  Option 1: (1,2)+(3,4) = 1+5 = 6
  Option 2: (1,3)+(2,4) = 3+3 = 6
  Option 3: (1,4)+(2,3) = 4+2 = 6

All same! Cost = sum_edges + 6 = (1+2+3) + 6 = 12

═══════════════════════════════════════════════════════════════════
COMPLEXITY
  Time:  O(V³) for Floyd-Warshall + O(2^k × k²) for matching
         where k = number of odd-degree vertices
  Space: O(V²)
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
#endif
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
constexpr i64 INF64 = 4e18;
#define nl '\n'

void solve() {
    int n, m;
    cin >> n >> m;

    vvec<i64> dist(n, vec<i64>(n, INF64));
    for (int i = 0; i < n; i++) dist[i][i] = 0;

    vec<int> deg(n, 0);
    i64 totalWeight = 0;

    for (int i = 0; i < m; i++) {
        int u, v; i64 w;
        cin >> u >> v >> w; u--; v--;
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
        deg[u]++; deg[v]++;
        totalWeight += w;
    }

    // Floyd-Warshall for all-pairs shortest paths
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] != INF64 && dist[k][j] != INF64)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    // Find odd-degree vertices
    vec<int> odd;
    for (int i = 0; i < n; i++)
        if (deg[i] % 2 == 1) odd.push_back(i);

    int k = (int)odd.size();

    if (k == 0) {
        // Already Eulerian!
        cout << "Chinese Postman cost: " << totalWeight << " (Eulerian)" << nl;
        return;
    }

    // Bitmask DP for minimum weight perfect matching on odd vertices
    // dp[mask] = min cost to match vertices in mask
    vec<i64> dp(1 << k, INF64);
    dp[0] = 0;

    for (int mask = 0; mask < (1 << k); mask++) {
        if (dp[mask] == INF64) continue;

        // Find first unmatched vertex
        int first = -1;
        for (int i = 0; i < k; i++) {
            if (!(mask & (1 << i))) { first = i; break; }
        }
        if (first == -1) continue;

        // Try matching with every other unmatched vertex
        for (int second = first + 1; second < k; second++) {
            if (mask & (1 << second)) continue;
            int newMask = mask | (1 << first) | (1 << second);
            i64 cost = dist[odd[first]][odd[second]];
            if (cost != INF64) {
                dp[newMask] = min(dp[newMask], dp[mask] + cost);
            }
        }
    }

    i64 matchingCost = dp[(1 << k) - 1];
    cout << "Chinese Postman cost: " << totalWeight + matchingCost << nl;
    cout << "  (Original edges: " << totalWeight << ", Added: " << matchingCost << ")" << nl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

