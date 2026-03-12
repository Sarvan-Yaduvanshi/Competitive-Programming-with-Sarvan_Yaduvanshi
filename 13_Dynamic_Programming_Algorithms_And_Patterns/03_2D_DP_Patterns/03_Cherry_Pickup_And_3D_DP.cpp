/*
 * ============================================================================
 *               CHERRY PICKUP & 3D GRID DP
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : 2D/3D DP — Cherry Pickup, Multi-path Grid DP
 * Level   : ⭐⭐⭐ Advanced
 * ============================================================================
 *
 * CHERRY PICKUP I (LeetCode 741):
 *   Grid N×N with cherries. Go (0,0)→(N-1,N-1) and back.
 *   Collect max cherries. Equivalent to TWO simultaneous paths going down-right.
 *   dp[r1][c1][r2] = max cherries, person1 at (r1,c1), person2 at (r2,c2)
 *   where c2 = r1+c1-r2 (same number of steps)
 *
 * CHERRY PICKUP II (LeetCode 1463):
 *   Two robots start at (0,0) and (0,n-1).
 *   Both move down one row each step, collecting cherries.
 *   dp[row][c1][c2] = max cherries with robots at columns c1, c2
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// Cherry Pickup I — Two simultaneous paths
int cherryPickup1(vector<vector<int>>& grid) {
    int n = grid.size();
    // dp[r1][c1][r2] — c2 = r1+c1-r2
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, -1)));
    dp[0][0][0] = grid[0][0];

    for (int r1 = 0; r1 < n; r1++) {
        for (int c1 = 0; c1 < n; c1++) {
            for (int r2 = 0; r2 < n; r2++) {
                int c2 = r1 + c1 - r2;
                if (c2 < 0 || c2 >= n) continue;
                if (grid[r1][c1] == -1 || grid[r2][c2] == -1) continue;

                // Try all 4 combinations of previous moves
                int best = -1;
                for (int dr1 : {0, 1}) {
                    for (int dr2 : {0, 1}) {
                        int pr1 = r1 - dr1, pc1 = c1 - (1 - dr1);
                        int pr2 = r2 - dr2;
                        if (pr1 < 0 || pc1 < 0 || pr2 < 0) continue;
                        if (dp[pr1][pc1][pr2] >= 0)
                            best = max(best, dp[pr1][pc1][pr2]);
                    }
                }

                if (best < 0 && !(r1 == 0 && c1 == 0)) continue;
                if (best < 0) best = 0;

                int cherries = grid[r1][c1];
                if (r1 != r2 || c1 != c2) cherries += grid[r2][c2];
                dp[r1][c1][r2] = best + cherries;
            }
        }
    }
    return max(0, dp[n-1][n-1][n-1]);
}

// Cherry Pickup II — Two robots moving down
int cherryPickup2(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    // dp[c1][c2] = max cherries with robot1 at col c1, robot2 at col c2
    vector<vector<int>> dp(n, vector<int>(n, -1));
    dp[0][n-1] = grid[0][0] + grid[0][n-1];

    for (int row = 1; row < m; row++) {
        vector<vector<int>> ndp(n, vector<int>(n, -1));

        for (int c1 = 0; c1 < n; c1++) {
            for (int c2 = c1; c2 < n; c2++) {
                // Try all 9 combinations of moves for both robots
                for (int d1 = -1; d1 <= 1; d1++) {
                    for (int d2 = -1; d2 <= 1; d2++) {
                        int pc1 = c1 - d1, pc2 = c2 - d2;
                        if (pc1 < 0 || pc1 >= n || pc2 < 0 || pc2 >= n) continue;
                        int prev_c1 = min(pc1, pc2), prev_c2 = max(pc1, pc2);
                        if (dp[prev_c1][prev_c2] < 0) continue;

                        int cherries = grid[row][c1];
                        if (c1 != c2) cherries += grid[row][c2];

                        int nc1 = min(c1, c2), nc2 = max(c1, c2);
                        ndp[nc1][nc2] = max(ndp[nc1][nc2],
                                           dp[prev_c1][prev_c2] + cherries);
                    }
                }
            }
        }
        dp = ndp;
    }

    int ans = 0;
    for (int c1 = 0; c1 < n; c1++)
        for (int c2 = c1; c2 < n; c2++)
            if (dp[c1][c2] > ans) ans = dp[c1][c2];
    return ans;
}

// Paint House II — K colors, O(nk) solution
int paintHouseII(vector<vector<int>>& costs) {
    int n = costs.size(), k = costs[0].size();
    int min1 = 0, min2 = 0, minIdx = -1;

    for (int i = 0; i < n; i++) {
        int newMin1 = INT_MAX, newMin2 = INT_MAX, newMinIdx = -1;

        for (int c = 0; c < k; c++) {
            int cost = costs[i][c] + (c == minIdx ? min2 : min1);
            if (cost < newMin1) {
                newMin2 = newMin1;
                newMin1 = cost;
                newMinIdx = c;
            } else if (cost < newMin2) {
                newMin2 = cost;
            }
        }
        min1 = newMin1; min2 = newMin2; minIdx = newMinIdx;
    }
    return min1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== CHERRY PICKUP & 3D DP ===" << endl;

    // Cherry Pickup I
    vector<vector<int>> grid1 = {
        {0, 1, -1},
        {1, 0, -1},
        {1, 1, 1}
    };
    cout << "\n--- Cherry Pickup I ---" << endl;
    cout << "Max cherries: " << cherryPickup1(grid1) << endl;

    // Cherry Pickup II
    vector<vector<int>> grid2 = {
        {3, 1, 1},
        {2, 5, 1},
        {1, 5, 5},
        {2, 1, 1}
    };
    cout << "\n--- Cherry Pickup II ---" << endl;
    cout << "Max cherries: " << cherryPickup2(grid2) << endl;

    // Paint House II
    vector<vector<int>> costs = {
        {1, 5, 3},
        {2, 9, 4}
    };
    cout << "\n--- Paint House II (k colors) ---" << endl;
    cout << "Min cost: " << paintHouseII(costs) << endl;

    return 0;
}

