/*
 * ============================================================================
 *           ADVANCED DP — BROKEN PROFILE / PROFILE DP
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Advanced DP — Profile DP, Broken Profile, Tiling
 * Level   : ⭐⭐⭐⭐⭐ Grandmaster
 * ============================================================================
 *
 * PROFILE DP (Broken Profile DP):
 *   Used for grid problems where we process column by column (or row by row)
 *   and maintain a "profile" — a bitmask describing the state of the
 *   boundary between processed and unprocessed cells.
 *
 * CLASSIC PROBLEMS:
 *   1. Count ways to tile M×N grid with 1×2 dominoes (CSES: Counting Tilings)
 *   2. Count connected subsets in grid
 *   3. Maximum independent set in grid graph
 *
 * STATE: dp[col][mask] where mask represents which cells in column boundary
 *        are "sticking out" (occupied by a horizontal domino from left)
 *
 * TIME: O(N * 2^M * 2^M) or O(N * 2^M * M) depending on transitions
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * PROBLEM 1: Count Tilings — CSES Problem
 * Tile an N×M grid with 1×2 dominoes. Count the number of ways.
 *
 * Process column by column. Profile = bitmask of M bits.
 * Bit i = 1 means cell (i, current_col) is already occupied by a
 *         horizontal domino starting from previous column.
 */
const int MOD = 1e9 + 7;

long long countTilings(int N, int M) {
    // Ensure M ≤ N for efficiency (fewer bits in mask)
    if (M > N) swap(N, M);

    int fullMask = (1 << M) - 1;

    // dp[mask] = number of ways to fill current column with profile 'mask'
    vector<long long> dp(1 << M, 0), ndp(1 << M, 0);
    dp[0] = 1;

    for (int col = 0; col < N; col++) {
        // For each column, we fill cells row by row
        // Process each row position within the column
        for (int row = 0; row < M; row++) {
            fill(ndp.begin(), ndp.end(), 0);

            for (int mask = 0; mask <= fullMask; mask++) {
                if (dp[mask] == 0) continue;

                bool occupied = (mask >> row) & 1;

                if (occupied) {
                    // Cell already filled by horizontal domino from prev col
                    // Clear this bit and move to next row
                    ndp[mask ^ (1 << row)] = (ndp[mask ^ (1 << row)] + dp[mask]) % MOD;
                } else {
                    // Option 1: Place vertical domino (fills this cell and cell below)
                    if (row + 1 < M && !((mask >> (row + 1)) & 1)) {
                        ndp[mask | (1 << (row + 1))] =
                            (ndp[mask | (1 << (row + 1))] + dp[mask]) % MOD;
                    }

                    // Option 2: Place horizontal domino (extends into next column)
                    ndp[mask | (1 << row)] = (ndp[mask | (1 << row)] + dp[mask]) % MOD;
                }
            }
            swap(dp, ndp);
        }
    }
    return dp[0];  // Profile 0 means nothing sticks into "column N+1"
}

/*
 * Alternative cleaner approach for counting tilings:
 * Generate all valid transitions between consecutive column profiles.
 */
long long countTilingsV2(int N, int M) {
    if (M > N) swap(N, M);
    int full = (1 << M) - 1;

    // Precompute valid transitions from profile 'from' to profile 'to'
    // from = bits sticking INTO current column from previous
    // to = bits sticking OUT of current column to next
    // The remaining cells in current column must be tileable with vertical dominoes

    vector<vector<int>> transitions(1 << M);

    function<void(int, int, int)> generate = [&](int from, int to, int row) {
        if (row == M) {
            transitions[from].push_back(to);
            return;
        }
        if ((from >> row) & 1) {
            // Cell occupied from left, skip
            generate(from, to, row + 1);
        } else {
            // Option 1: horizontal domino to right
            generate(from, to | (1 << row), row + 1);

            // Option 2: vertical domino (pair with row+1)
            if (row + 1 < M && !((from >> (row + 1)) & 1)) {
                generate(from, to, row + 2);
            }
        }
    };

    for (int mask = 0; mask <= full; mask++)
        generate(mask, 0, 0);

    vector<long long> dp(1 << M, 0);
    dp[0] = 1;

    for (int col = 0; col < N; col++) {
        vector<long long> ndp(1 << M, 0);
        for (int from = 0; from <= full; from++) {
            if (dp[from] == 0) continue;
            for (int to : transitions[from]) {
                ndp[to] = (ndp[to] + dp[from]) % MOD;
            }
        }
        dp = ndp;
    }
    return dp[0];
}

/*
 * PROBLEM 2: Max Independent Set in Grid
 * Select maximum weight cells such that no two selected cells are adjacent.
 * Grid has M rows and N columns. M is small (≤ 20).
 *
 * dp[col][mask] = max weight using first col columns,
 *                 where mask = which cells in column col are selected.
 *
 * Transition: mask for col must be compatible with mask for col-1
 *             (no horizontal adjacency: mask_cur & mask_prev == 0)
 *             (no vertical adjacency within column: no two consecutive bits)
 */
long long maxIndepSetGrid(vector<vector<int>>& grid) {
    int M = grid.size(), N = grid[0].size();
    int full = 1 << M;

    // Check if mask has no two consecutive bits
    auto valid = [](int mask) {
        return (mask & (mask >> 1)) == 0;
    };

    // Precompute valid masks and their weights per column
    vector<vector<int>> validMasks;
    for (int col = 0; col < N; col++) {
        vector<int> masks;
        for (int mask = 0; mask < full; mask++) {
            if (valid(mask)) masks.push_back(mask);
        }
        validMasks.push_back(masks);
    }

    auto weight = [&](int col, int mask) {
        long long w = 0;
        for (int i = 0; i < M; i++)
            if (mask & (1 << i)) w += grid[i][col];
        return w;
    };

    map<int, long long> dp;
    for (int mask : validMasks[0])
        dp[mask] = weight(0, mask);

    for (int col = 1; col < N; col++) {
        map<int, long long> ndp;
        for (int cur : validMasks[col]) {
            long long best = 0;
            for (auto& [prev, val] : dp) {
                if ((cur & prev) == 0) {  // No horizontal conflict
                    best = max(best, val);
                }
            }
            ndp[cur] = best + weight(col, cur);
        }
        dp = ndp;
    }

    long long ans = 0;
    for (auto& [mask, val] : dp) ans = max(ans, val);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== PROFILE / BROKEN PROFILE DP ===" << endl;

    // Counting Tilings
    cout << "\n--- Count Tilings (1×2 dominoes) ---" << endl;
    for (int n = 2; n <= 8; n += 2) {
        cout << "2×" << n << " grid: " << countTilingsV2(n, 2) << " ways" << endl;
    }
    cout << "4×7 grid: " << countTilingsV2(4, 7) << " ways" << endl;

    // Max Independent Set in Grid
    vector<vector<int>> grid = {
        {1, 5, 3, 2},
        {4, 2, 1, 6},
        {3, 1, 5, 2}
    };
    cout << "\n--- Max Independent Set in Grid ---" << endl;
    cout << "Max weight: " << maxIndepSetGrid(grid) << endl;

    return 0;
}

