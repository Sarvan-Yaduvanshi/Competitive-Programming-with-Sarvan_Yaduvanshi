/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 08.02 — TRAVELING SALESMAN PROBLEM (TSP)                 ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Given n cities and distances, find minimum cost Hamiltonian cycle
    (visit all cities exactly once and return to start).

RECURRENCE:
═══════════
    dp[mask][i] = minimum cost to visit exactly the cities in mask,
                  starting from city 0 and currently at city i.

    dp[1][0] = 0  (start at city 0, only city 0 visited)

    Transition: dp[mask | (1<<j)][j] = min over i∈mask of (dp[mask][i] + dist[i][j])
    where j ∉ mask.

    Answer: min over all i of (dp[(1<<n)-1][i] + dist[i][0])
    (visit all, then return to city 0)

DRY RUN — 4 cities:
    dist = [[0,10,15,20],[10,0,35,25],[15,35,0,30],[20,25,30,0]]
    n=4, states = 2⁴ × 4 = 64
    Optimal tour: 0→1→3→2→0 = 10+25+30+15 = 80

TIME: O(n² × 2ⁿ), SPACE: O(n × 2ⁿ)
FEASIBLE: n ≤ 20

PRACTICE PROBLEMS:
══════════════════
    CSES: Hamiltonian Flights
    Codeforces: 8C
    SPOJ: TSP
*/
#include <iostream>
#include <vector>
#include <climits>
#include <bitset>
#include <cassert>
using namespace std;

int tsp(vector<vector<int>>& dist) {
    int n = dist.size();
    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));

    dp[1][0] = 0; // Start at city 0

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (dp[mask][i] == INT_MAX) continue;
            if (!(mask & (1 << i))) continue;
            for (int j = 0; j < n; j++) {
                if (mask & (1 << j)) continue;
                if (dist[i][j] == INT_MAX) continue;
                int newMask = mask | (1 << j);
                dp[newMask][j] = min(dp[newMask][j], dp[mask][i] + dist[i][j]);
            }
        }
    }

    int fullMask = (1 << n) - 1;
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (dp[fullMask][i] != INT_MAX && dist[i][0] != INT_MAX) {
            ans = min(ans, dp[fullMask][i] + dist[i][0]);
        }
    }
    return ans;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   TRAVELING SALESMAN PROBLEM (TSP)              ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    cout << "\n  Distance matrix (4 cities):" << endl;
    for (auto& row : dist) {
        cout << "    ";
        for (int d : row) cout << d << "\t";
        cout << endl;
    }

    int ans = tsp(dist);
    cout << "\n  Minimum TSP tour cost: " << ans << endl;
    assert(ans == 80); // 0→1→3→2→0 = 10+25+30+15

    cout << "\n  Complexity: O(n² × 2ⁿ) = O(16 × 16) = 256 states" << endl;
    cout << "  For n=20: O(400 × 10⁶) ≈ feasible!" << endl;

    cout << "\n✅ TSP with bitmask DP verified!" << endl;
    return 0;
}

