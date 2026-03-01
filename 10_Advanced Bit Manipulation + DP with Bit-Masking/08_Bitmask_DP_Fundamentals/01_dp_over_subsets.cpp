/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 08.01 — DP OVER SUBSETS (Fundamentals)                   ║
║           Bit Manipulation — Bitmask DP Fundamentals                       ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

CORE IDEA:
══════════
    When n is small (n ≤ 20), we can use bitmask as DP state.
    dp[mask] = answer for the subset represented by mask.
    State space: O(2ⁿ), each state processed in O(n) → O(n × 2ⁿ).

GENERAL TEMPLATE:
═════════════════
    for (int mask = 0; mask < (1 << n); mask++) {
        // Process dp[mask]
        // Transition: try adding element i NOT in mask
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i))) {
                int newMask = mask | (1 << i);
                dp[newMask] = f(dp[mask], i);
            }
        }
    }

EXAMPLE: Find minimum cost to visit all n cities (simplified TSP without return).
    dp[mask] = min cost to visit exactly the cities in mask (ending at any of them).
    More precisely: dp[mask][i] = min cost when mask is visited and last city is i.

TRANSITIONS:
════════════
    dp[mask | (1<<j)][j] = min(dp[mask][i] + cost[i][j])
    for all i ∈ mask, j ∉ mask.

BASE CASE: dp[1<<i][i] = 0 (or cost to start at city i).

DRY RUN — 3 cities, cost = [[0,10,15],[10,0,20],[15,20,0]]:
    dp[001][0] = 0 (start at city 0)
    dp[010][1] = 0
    dp[100][2] = 0
    dp[011][1] = dp[001][0] + cost[0][1] = 10
    dp[011][0] = dp[010][1] + cost[1][0] = 10
    dp[101][2] = dp[001][0] + cost[0][2] = 15
    dp[101][0] = dp[100][2] + cost[2][0] = 15
    dp[110][2] = dp[010][1] + cost[1][2] = 20
    dp[110][1] = dp[100][2] + cost[2][1] = 20
    dp[111][2] = min(dp[011][0]+15, dp[011][1]+20) = min(25,30) = 25
    dp[111][1] = min(dp[101][0]+10, dp[101][2]+20) = min(25,35) = 25
    dp[111][0] = min(dp[110][1]+10, dp[110][2]+15) = min(30,35) = 30
    Answer = min(dp[111][0], dp[111][1], dp[111][2]) = 25

TIME: O(n² × 2ⁿ), SPACE: O(n × 2ⁿ)
CONSTRAINT: n ≤ 20 (2²⁰ ≈ 10⁶)

PRACTICE PROBLEMS:
══════════════════
    CSES: Hamiltonian Flights
    Codeforces: 580D, 453B
    LeetCode 847: Shortest Path Visiting All Nodes
*/
#include <iostream>
#include <vector>
#include <climits>
#include <cassert>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   DP OVER SUBSETS — FUNDAMENTALS                ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int n = 3;
    vector<vector<int>> cost = {{0,10,15},{10,0,20},{15,20,0}};

    // dp[mask][i] = min cost to visit cities in mask, ending at i
    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));

    // Base: start at each city
    for (int i = 0; i < n; i++) dp[1 << i][i] = 0;

    // Fill DP
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (dp[mask][i] == INT_MAX) continue;
            if (!(mask & (1 << i))) continue;
            // Try extending to city j
            for (int j = 0; j < n; j++) {
                if (mask & (1 << j)) continue; // already visited
                int newMask = mask | (1 << j);
                dp[newMask][j] = min(dp[newMask][j], dp[mask][i] + cost[i][j]);
            }
        }
    }

    // Answer: visit all cities
    int fullMask = (1 << n) - 1;
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) ans = min(ans, dp[fullMask][i]);

    cout << "\n  Cost matrix:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "    ";
        for (int j = 0; j < n; j++) cout << cost[i][j] << " ";
        cout << endl;
    }
    cout << "\n  Min cost to visit all cities: " << ans << endl;
    assert(ans == 25);

    // Print DP table
    cout << "\n  DP Table:" << endl;
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (dp[mask][i] != INT_MAX) {
                cout << "    dp[" << bitset<3>(mask) << "][" << i << "] = " << dp[mask][i] << endl;
            }
        }
    }

    cout << "\n✅ DP over subsets fundamentals verified!" << endl;
    return 0;
}

