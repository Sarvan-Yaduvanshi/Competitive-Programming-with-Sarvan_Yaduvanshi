/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 09.06 — BROKEN PROFILE DP                                ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Count ways to tile an M×N grid with dominoes (1×2 or 2×1 tiles).

BITMASK DP APPROACH:
════════════════════
    Process grid column by column (or row by row).
    dp[col][mask] = number of ways to tile columns 0..col-1 completely,
                    with column col having the "profile" described by mask.

    mask bit i = 1 means cell (i, col) is already filled (by a horizontal domino
    from the previous column).
    mask bit i = 0 means cell (i, col) is still empty.

    Transition: for each column, try all valid ways to fill empty cells
    using vertical dominoes (within column) and horizontal dominoes (extending to next column).

DRY RUN — 2×3 grid:
    n=2 rows, m=3 columns. Process column by column.
    Answer: 3 (well-known: 2×3 grid has 3 tilings)

TIME: O(M × 2^N × 2^N) with pruning, or O(M × 2^N × transitions)
FEASIBLE: N ≤ 15-20

PRACTICE PROBLEMS:
══════════════════
    CSES: Counting Tilings
    SPOJ: M3TILE, MNTILE
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

long long countTilings(int N, int M) {
    // N rows, M columns. Bitmask over N rows.
    if (N > M) swap(N, M); // ensure N is smaller for efficiency

    vector<vector<long long>> dp(M + 1, vector<long long>(1 << N, 0));
    dp[0][0] = 1; // empty profile for column 0

    for (int col = 0; col < M; col++) {
        for (int mask = 0; mask < (1 << N); mask++) {
            if (dp[col][mask] == 0) continue;
            // Generate all valid next-column profiles
            // Use recursive helper to fill column
            // For each mask, try filling row by row
            function<void(int, int, int)> fill = [&](int row, int curMask, int nextMask) {
                if (row == N) {
                    dp[col + 1][nextMask] += dp[col][mask];
                    return;
                }
                if (curMask & (1 << row)) {
                    // Already filled (horizontal from prev) → skip, next column empty here
                    fill(row + 1, curMask, nextMask);
                } else {
                    // Place horizontal domino (fills next column's row)
                    fill(row + 1, curMask, nextMask | (1 << row));
                    // Place vertical domino (fills this and next row in current column)
                    if (row + 1 < N && !(curMask & (1 << (row + 1)))) {
                        fill(row + 2, curMask, nextMask);
                    }
                }
            };
            fill(0, mask, 0);
        }
    }
    return dp[M][0]; // all cells filled, no hanging into column M
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   BROKEN PROFILE DP                             ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "\n--- Domino Tiling Counts ---" << endl;
    cout << "  2×3: " << countTilings(2, 3) << " (expected 3)" << endl;
    cout << "  2×4: " << countTilings(2, 4) << " (expected 5)" << endl;
    cout << "  3×4: " << countTilings(3, 4) << " (expected 11)" << endl;
    cout << "  4×4: " << countTilings(4, 4) << " (expected 36)" << endl;
    cout << "  2×8: " << countTilings(2, 8) << " (expected 34)" << endl;

    assert(countTilings(2, 3) == 3);
    assert(countTilings(2, 4) == 5);

    cout << "\n✅ Broken profile DP verified!" << endl;
    return 0;
}

