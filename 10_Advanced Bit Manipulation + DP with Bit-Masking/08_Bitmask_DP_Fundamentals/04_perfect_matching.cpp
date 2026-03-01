/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 08.04 — PERFECT MATCHING                                 ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Given a bipartite graph with 2n vertices (n left, n right),
    count/find perfect matchings (every vertex matched exactly once).

RECURRENCE:
═══════════
    dp[mask] = number of ways to match the first popcount(mask) left vertices
               using exactly the right vertices in mask.

    dp[mask] = Σ dp[mask ^ (1<<j)] for all j ∈ mask where edge(worker, j) exists
    where worker = popcount(mask) - 1.

BASE: dp[0] = 1.
ANSWER: dp[(1<<n)-1].

APPLICATION: Count number of ways to assign tasks, count derangements with constraints.

TIME: O(n × 2ⁿ)

PRACTICE PROBLEMS:
══════════════════
    CSES: Elevator Rides
    Codeforces: 580D
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

long long countPerfectMatchings(vector<vector<bool>>& adj) {
    int n = adj.size();
    vector<long long> dp(1 << n, 0);
    dp[0] = 1;

    for (int mask = 1; mask < (1 << n); mask++) {
        int leftVertex = __builtin_popcount(mask) - 1;
        for (int j = 0; j < n; j++) {
            if (!(mask & (1 << j))) continue;
            if (!adj[leftVertex][j]) continue;
            dp[mask] += dp[mask ^ (1 << j)];
        }
    }
    return dp[(1 << n) - 1];
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   PERFECT MATCHING                              ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Complete bipartite graph K3,3 → 3! = 6 perfect matchings
    vector<vector<bool>> adj1 = {{1,1,1},{1,1,1},{1,1,1}};
    cout << "  K3,3: " << countPerfectMatchings(adj1) << " matchings (expected 6)" << endl;
    assert(countPerfectMatchings(adj1) == 6);

    // Restricted graph
    vector<vector<bool>> adj2 = {{1,1,0},{0,1,1},{1,0,1}};
    cout << "  Restricted: " << countPerfectMatchings(adj2) << " matchings" << endl;

    // No perfect matching possible
    vector<vector<bool>> adj3 = {{1,0,0},{1,0,0},{1,0,0}};
    cout << "  No matching: " << countPerfectMatchings(adj3) << endl;
    assert(countPerfectMatchings(adj3) == 0);

    cout << "\n✅ Perfect matching counting verified!" << endl;
    return 0;
}

