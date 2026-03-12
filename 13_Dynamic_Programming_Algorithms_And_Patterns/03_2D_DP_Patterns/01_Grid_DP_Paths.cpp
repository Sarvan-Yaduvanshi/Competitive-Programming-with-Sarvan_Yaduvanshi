/*
 * ============================================================================
 *                    GRID DP — UNIQUE PATHS & MIN PATH SUM
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : 2D DP — Grid Path Problems
 * Level   : ⭐⭐ Intermediate
 * ============================================================================
 *
 * PATTERN: Grid DP
 *   State: dp[i][j] = answer for cell (i,j)
 *   Transition: dp[i][j] = f(dp[i-1][j], dp[i][j-1]) — from top or left
 *
 * PROBLEMS COVERED:
 * 1. Unique Paths (LeetCode 62)
 * 2. Unique Paths with Obstacles (LeetCode 63)
 * 3. Minimum Path Sum (LeetCode 64)
 * 4. Maximum Path Sum in Grid
 * 5. Triangle DP (LeetCode 120)
 * 6. Dungeon Game (LeetCode 174)
 * 7. Cherry Pickup (LeetCode 741)
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Unique Paths — Count paths from (0,0) to (m-1,n-1) moving right/down
int uniquePaths(int m, int n) {
    vector<int> dp(n, 1);
    for (int i = 1; i < m; i++)
        for (int j = 1; j < n; j++)
            dp[j] += dp[j-1];
    return dp[n-1];
}

// 2. Unique Paths with Obstacles
int uniquePathsWithObstacles(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<int> dp(n, 0);
    dp[0] = (grid[0][0] == 0) ? 1 : 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) { dp[j] = 0; continue; }
            if (j > 0) dp[j] += dp[j-1];
        }
    }
    return dp[n-1];
}

// 3. Minimum Path Sum (LeetCode 64)
int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<int> dp(n);
    dp[0] = grid[0][0];

    for (int j = 1; j < n; j++) dp[j] = dp[j-1] + grid[0][j];

    for (int i = 1; i < m; i++) {
        dp[0] += grid[i][0];
        for (int j = 1; j < n; j++) {
            dp[j] = grid[i][j] + min(dp[j], dp[j-1]);
        }
    }
    return dp[n-1];
}

// 4. Maximum Path Sum in Grid (top-left to bottom-right)
int maxPathSum(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = grid[0][0];

    for (int j = 1; j < n; j++) dp[0][j] = dp[0][j-1] + grid[0][j];
    for (int i = 1; i < m; i++) dp[i][0] = dp[i-1][0] + grid[i][0];

    for (int i = 1; i < m; i++)
        for (int j = 1; j < n; j++)
            dp[i][j] = grid[i][j] + max(dp[i-1][j], dp[i][j-1]);

    return dp[m-1][n-1];
}

// 5. Triangle DP (LeetCode 120)
// Minimum path sum from top to bottom
int triangleMinPath(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<int> dp = triangle[n-1];  // Start from bottom row

    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            dp[j] = triangle[i][j] + min(dp[j], dp[j+1]);
        }
    }
    return dp[0];
}

// 6. Dungeon Game (LeetCode 174) — Min initial health to reach bottom-right
int dungeonGame(vector<vector<int>>& dungeon) {
    int m = dungeon.size(), n = dungeon[0].size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
    dp[m][n-1] = dp[m-1][n] = 1;  // Need at least 1 HP at destination

    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            int minHP = min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j];
            dp[i][j] = max(1, minHP);
        }
    }
    return dp[0][0];
}

// 7. Maximal Square (LeetCode 221) — Largest square of 1s
int maximalSquare(vector<vector<char>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    vector<int> dp(n + 1, 0);
    int maxSide = 0, prev = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int temp = dp[j];
            if (matrix[i-1][j-1] == '1') {
                dp[j] = min({dp[j], dp[j-1], prev}) + 1;
                maxSide = max(maxSide, dp[j]);
            } else {
                dp[j] = 0;
            }
            prev = temp;
        }
    }
    return maxSide * maxSide;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== GRID DP PATTERNS ===" << endl;

    // Unique Paths
    cout << "\n--- Unique Paths ---" << endl;
    cout << "3x7 grid: " << uniquePaths(3, 7) << " paths" << endl;
    cout << "3x3 grid: " << uniquePaths(3, 3) << " paths" << endl;

    // Min Path Sum
    vector<vector<int>> grid = {{1,3,1},{1,5,1},{4,2,1}};
    cout << "\n--- Min Path Sum ---" << endl;
    cout << "Min path: " << minPathSum(grid) << endl;  // 1+3+1+1+1=7

    // Triangle
    vector<vector<int>> tri = {{2},{3,4},{6,5,7},{4,1,8,3}};
    cout << "\n--- Triangle DP ---" << endl;
    cout << "Min path: " << triangleMinPath(tri) << endl;  // 2+3+5+1=11

    // Dungeon Game
    vector<vector<int>> dungeon = {{-2,-3,3},{-5,-10,1},{10,30,-5}};
    cout << "\n--- Dungeon Game ---" << endl;
    cout << "Min HP: " << dungeonGame(dungeon) << endl;  // 7

    // Maximal Square
    vector<vector<char>> matrix = {
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    };
    cout << "\n--- Maximal Square ---" << endl;
    cout << "Max area: " << maximalSquare(matrix) << endl;  // 4

    return 0;
}

