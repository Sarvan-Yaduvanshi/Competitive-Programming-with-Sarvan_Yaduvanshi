/*
 * ============================================================================
 *           DIAGONAL TRAVERSAL - ZERO TO GM MASTERY
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Topic   : All Diagonal Traversal Patterns
 * Level   : 0 (Beginner) → 7 (GM)
 * ============================================================================
 *
 *  TABLE OF CONTENTS
 *  ─────────────────
 *  Level 0 : Primary Diagonal (Main Diagonal)
 *  Level 1 : Secondary Diagonal (Anti-Diagonal)
 *  Level 2 : All Diagonals Parallel to Primary (i - j = constant)
 *  Level 3 : All Anti-Diagonals (i + j = constant)
 *  Level 4 : Zigzag Diagonal Traversal [LC #498]
 *  Level 5 : Diagonal Sum, Diagonal Difference
 *  Level 6 : Diagonal of Rectangular Matrix
 *  Level 7 : GM-Level: Diagonal Traverse with Grouping
 *
 * ============================================================================
 *  DIAGONAL KEY INSIGHT:
 *  ┌────────────────────────────────────────────────────────────────┐
 *  │  Primary diagonals:  Elements with same (i - j) value          │
 *  │  Anti-diagonals:     Elements with same (i + j) value          │
 *  │                                                                │
 *  │  For N×M matrix:                                               │
 *  │  - (i-j) ranges from -(M-1) to (N-1)  → N+M-1 diagonals        │
 *  │  - (i+j) ranges from 0 to (N+M-2)     → N+M-1 anti-diags       │
 *  └────────────────────────────────────────────────────────────────┘
 *
 *  Related Problems:
 *  - LC #498: Diagonal Traverse
 *  - LC #1424: Diagonal Traverse II
 *  - LC #1572: Matrix Diagonal Sum
 * ============================================================================
 *  Time Complexity: O(N × M) for all traversals
 *  Space Complexity: O(1) extra (O(N×M) for output)
 * ============================================================================
 */

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

void printMatrix(const vector<vector<int>>& mat, const string& title = "") {
    if (!title.empty()) cout << "--- " << title << " ---" << endl;
    for (const auto& row : mat) {
        for (int val : row) cout << setw(4) << val;
        cout << "\n";
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 0: PRIMARY DIAGONAL (MAIN DIAGONAL)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Main diagonal: elements where i == j
 *
 *  For matrix:
 *  [1]  2   3   4
 *   5  [6]  7   8
 *   9  10  [11] 12
 *  13  14  15  [16]
 *
 *  Primary Diagonal: 1, 6, 11, 16
 *
 *  For rectangular N×M: min(N, M) elements on main diagonal
 */
void primaryDiagonal(const vector<vector<int>>& mat) {
    cout << "=== Primary (Main) Diagonal ===" << endl;
    int n = mat.size(), m = mat[0].size();
    int len = min(n, m);

    cout << "Elements: ";
    for (int i = 0; i < len; i++)
        cout << mat[i][i] << " ";
    cout << "\n\n";
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 1: SECONDARY DIAGONAL (ANTI-DIAGONAL)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Secondary diagonal: elements where i + j == N - 1 (for square matrix)
 *
 *  For matrix:
 *   1   2   3  [4]
 *   5   6  [7]  8
 *   9  [10] 11  12
 *  [13] 14  15  16
 *
 *  Secondary Diagonal: 4, 7, 10, 13
 */
void secondaryDiagonal(const vector<vector<int>>& mat) {
    cout << "=== Secondary (Anti) Diagonal ===" << endl;
    int n = mat.size(), m = mat[0].size();

    cout << "Elements: ";
    for (int i = 0; i < n; i++) {
        int j = m - 1 - i;
        if (j >= 0 && j < m)
            cout << mat[i][j] << " ";
    }
    cout << "\n\n";
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 2: ALL DIAGONALS PARALLEL TO PRIMARY (i - j = constant)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Each diagonal has a unique (i - j) value.
 *
 *  For 4×4 matrix:
 *  (i-j) = -3: [4]
 *  (i-j) = -2: [3, 8]
 *  (i-j) = -1: [2, 7, 12]
 *  (i-j) =  0: [1, 6, 11, 16]  ← Main diagonal
 *  (i-j) =  1: [5, 10, 15]
 *  (i-j) =  2: [9, 14]
 *  (i-j) =  3: [13]
 *
 *  Visualization (diagonal index = i - j + M - 1):
 *   d3  d2  d1  d0
 *   d4  d3  d2  d1
 *   d5  d4  d3  d2
 *   d6  d5  d4  d3
 */
void allPrimaryDiagonals(const vector<vector<int>>& mat) {
    cout << "=== All Primary Diagonals (i - j = constant) ===" << endl;
    int n = mat.size(), m = mat[0].size();

    // Method 1: Using map to group by (i - j)
    map<int, vector<int>> diags;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            diags[i - j].push_back(mat[i][j]);

    for (auto& [key, vals] : diags) {
        cout << "  i-j = " << setw(2) << key << ": ";
        for (int v : vals) cout << v << " ";
        cout << endl;
    }
    cout << endl;

    // Method 2: Direct traversal (top-right to bottom-left)
    cout << "Direct traversal method:" << endl;
    // Start from first row (right to left)
    for (int startCol = m - 1; startCol >= 0; startCol--) {
        cout << "  Diag: ";
        for (int i = 0, j = startCol; i < n && j < m; i++, j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
    // Then from first column (top to bottom, skip (0,0) since already covered)
    for (int startRow = 1; startRow < n; startRow++) {
        cout << "  Diag: ";
        for (int i = startRow, j = 0; i < n && j < m; i++, j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 3: ALL ANTI-DIAGONALS (i + j = constant)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Each anti-diagonal has a unique (i + j) value.
 *
 *  For 4×4 matrix:
 *  (i+j) = 0: [1]
 *  (i+j) = 1: [2, 5]
 *  (i+j) = 2: [3, 6, 9]
 *  (i+j) = 3: [4, 7, 10, 13]  ← Secondary diagonal
 *  (i+j) = 4: [8, 11, 14]
 *  (i+j) = 5: [12, 15]
 *  (i+j) = 6: [16]
 *
 *  Total anti-diagonals = N + M - 1
 */
void allAntiDiagonals(const vector<vector<int>>& mat) {
    cout << "=== All Anti-Diagonals (i + j = constant) ===" << endl;
    int n = mat.size(), m = mat[0].size();

    // Method 1: Using map
    map<int, vector<int>> antiDiags;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            antiDiags[i + j].push_back(mat[i][j]);

    for (auto& [key, vals] : antiDiags) {
        cout << "  i+j = " << key << ": ";
        for (int v : vals) cout << v << " ";
        cout << endl;
    }
    cout << endl;

    // Method 2: Direct traversal
    cout << "Direct anti-diagonal traversal:" << endl;
    for (int sum = 0; sum <= n + m - 2; sum++) {
        cout << "  Anti-diag " << sum << ": ";
        // Start row = max(0, sum - m + 1), End row = min(n - 1, sum)
        int startRow = max(0, sum - m + 1);
        int endRow = min(n - 1, sum);
        for (int i = startRow; i <= endRow; i++) {
            int j = sum - i;
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 4: ZIGZAG DIAGONAL TRAVERSAL — LC #498
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Traverse anti-diagonals alternating direction:
 *  - Even anti-diag (i+j): upward (bottom-left to top-right)
 *  - Odd anti-diag (i+j):  downward (top-right to bottom-left)
 *
 *  For matrix:
 *  1  2  3
 *  4  5  6
 *  7  8  9
 *
 *  Anti-diag 0: [1]           → up:   1
 *  Anti-diag 1: [2, 4]       → down: 2, 4
 *  Anti-diag 2: [3, 5, 7]   → up:   7, 5, 3
 *  Anti-diag 3: [6, 8]      → down: 6, 8
 *  Anti-diag 4: [9]          → up:   9
 *
 *  Result: 1, 2, 4, 7, 5, 3, 6, 8, 9
 *
 *  Wait — LC #498 uses:
 *  Even sum → go UP (from bottom-left to top-right)
 *  Odd sum  → go DOWN (from top-right to bottom-left)
 *
 *  Result: 1, 2, 4, 7, 5, 3, 6, 8, 9
 *
 *  Time: O(N×M), Space: O(1) extra
 */
vector<int> diagonalTraverseLC498(const vector<vector<int>>& mat) {
    cout << "=== Zigzag Diagonal Traverse (LC #498) ===" << endl;
    vector<int> result;
    if (mat.empty()) return result;

    int n = mat.size(), m = mat[0].size();

    for (int sum = 0; sum <= n + m - 2; sum++) {
        if (sum % 2 == 0) {
            // Go UP: start from bottom of anti-diagonal
            int startRow = min(sum, n - 1);
            int startCol = sum - startRow;
            while (startRow >= 0 && startCol < m) {
                result.push_back(mat[startRow][startCol]);
                startRow--;
                startCol++;
            }
        } else {
            // Go DOWN: start from top of anti-diagonal
            int startCol = min(sum, m - 1);
            int startRow = sum - startCol;
            while (startRow < n && startCol >= 0) {
                result.push_back(mat[startRow][startCol]);
                startRow++;
                startCol--;
            }
        }
    }

    cout << "Zigzag: ";
    for (int x : result) cout << x << " ";
    cout << "\n\n";
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 5: DIAGONAL SUM & DIAGONAL DIFFERENCE — LC #1572
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Primary Diagonal Sum: Σ mat[i][i]
 *  Secondary Diagonal Sum: Σ mat[i][N-1-i]
 *  Total Diagonal Sum: primary + secondary - center (if N is odd)
 *
 *  LC #1572: Matrix Diagonal Sum
 *  Time: O(N), Space: O(1)
 */
void diagonalSums(const vector<vector<int>>& mat) {
    cout << "=== Diagonal Sums (LC #1572) ===" << endl;
    int n = mat.size();
    int primarySum = 0, secondarySum = 0;

    for (int i = 0; i < n; i++) {
        primarySum += mat[i][i];
        secondarySum += mat[i][n - 1 - i];
    }

    // If N is odd, center element is counted twice
    int totalSum = primarySum + secondarySum;
    if (n % 2 == 1)
        totalSum -= mat[n/2][n/2];

    cout << "Primary diagonal sum   = " << primarySum << endl;
    cout << "Secondary diagonal sum = " << secondarySum << endl;
    cout << "Total diagonal sum     = " << totalSum << endl;
    cout << "Diagonal difference    = |" << primarySum << " - " << secondarySum
         << "| = " << abs(primarySum - secondarySum) << endl;
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 6: DIAGONALS IN RECTANGULAR MATRIX
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  For N×M (non-square) matrix, diagonals have varying lengths.
 *
 *  Primary diagonal of rectangular:
 *  - Only min(N, M) elements
 *
 *  All diagonals: same approach using (i-j) and (i+j) keys
 */
void rectangularDiagonals(const vector<vector<int>>& mat) {
    cout << "=== Rectangular Matrix Diagonals ===" << endl;
    int n = mat.size(), m = mat[0].size();

    // All primary diagonals (i - j = constant)
    cout << "Primary diagonals (upper-left to lower-right):" << endl;
    // Start from each column of first row
    for (int startCol = 0; startCol < m; startCol++) {
        cout << "  Start(0," << startCol << "): ";
        for (int i = 0, j = startCol; i < n && j < m; i++, j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
    // Start from each row of first column (skip row 0)
    for (int startRow = 1; startRow < n; startRow++) {
        cout << "  Start(" << startRow << ",0): ";
        for (int i = startRow, j = 0; i < n && j < m; i++, j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 7: GM-LEVEL — DIAGONAL ELEMENTS ON SAME DIAGONAL CHECK
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Two cells (r1,c1) and (r2,c2) are on:
 *  - Same primary diagonal if: r1 - c1 == r2 - c2
 *  - Same anti-diagonal if:    r1 + c1 == r2 + c2
 *
 *  This is used heavily in:
 *  - N-Queens problem
 *  - Bishop attack patterns
 *  - Diagonal DP
 */
bool onSamePrimaryDiagonal(int r1, int c1, int r2, int c2) {
    return (r1 - c1) == (r2 - c2);
}

bool onSameAntiDiagonal(int r1, int c1, int r2, int c2) {
    return (r1 + c1) == (r2 + c2);
}

bool onAnyDiagonal(int r1, int c1, int r2, int c2) {
    return abs(r1 - r2) == abs(c1 - c2); // Equivalent to checking both diagonals
}

void diagonalCheckDemo() {
    cout << "=== Diagonal Check Demo (N-Queens Pattern) ===" << endl;

    int n = 8;
    pair<int,int> queens[] = {{0,0}, {1,2}, {2,4}, {3,6}};

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            auto [r1,c1] = queens[i];
            auto [r2,c2] = queens[j];
            cout << "  Q(" << r1 << "," << c1 << ") & Q(" << r2 << "," << c2 << "): ";

            if (onSamePrimaryDiagonal(r1,c1,r2,c2))
                cout << "Same Primary Diagonal! ";
            if (onSameAntiDiagonal(r1,c1,r2,c2))
                cout << "Same Anti-Diagonal! ";
            if (!onAnyDiagonal(r1,c1,r2,c2))
                cout << "Not on any diagonal (safe!)";
            cout << endl;
        }
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 7B: DIAGONAL TRAVERSE II — LC #1424
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Given a list of lists (not necessarily same length),
 *  traverse in anti-diagonal order.
 *
 *  Group by (i + j), but within each group, iterate bottom-to-top.
 *
 *  Input: [[1,2,3],[4,5,6],[7,8,9]]
 *
 *  i+j=0: [1]    → [1]
 *  i+j=1: [4,2]  → [4,2]  (bottom to top = larger i first)
 *  i+j=2: [7,5,3]→ [7,5,3]
 *  i+j=3: [8,6]  → [8,6]
 *  i+j=4: [9]    → [9]
 *
 *  Result: 1,4,2,7,5,3,8,6,9
 *
 *  Time: O(N×M), Space: O(N×M)
 */
vector<int> diagonalTraverseII(const vector<vector<int>>& nums) {
    cout << "=== Diagonal Traverse II (LC #1424) ===" << endl;
    map<int, vector<int>> diags;

    for (int i = 0; i < (int)nums.size(); i++) {
        for (int j = 0; j < (int)nums[i].size(); j++) {
            diags[i + j].push_back(nums[i][j]);
        }
    }

    vector<int> result;
    for (auto& [key, vals] : diags) {
        // Reverse to get bottom-to-top order
        for (int k = vals.size() - 1; k >= 0; k--)
            result.push_back(vals[k]);
    }

    cout << "Result: ";
    for (int x : result) cout << x << " ";
    cout << "\n\n";
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   DIAGONAL TRAVERSAL - ZERO TO GM MASTERY       ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << endl;

    vector<vector<int>> mat = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9,  10, 11, 12},
        {13, 14, 15, 16}
    };
    printMatrix(mat, "Original 4x4 Matrix");

    // Level 0
    primaryDiagonal(mat);

    // Level 1
    secondaryDiagonal(mat);

    // Level 2
    allPrimaryDiagonals(mat);

    // Level 3
    allAntiDiagonals(mat);

    // Level 4: Zigzag (LC #498)
    vector<vector<int>> mat4 = {{1,2,3},{4,5,6},{7,8,9}};
    printMatrix(mat4, "3x3 for Zigzag");
    diagonalTraverseLC498(mat4);

    // Also test rectangular
    vector<vector<int>> rect = {{1,2,3},{4,5,6}};
    printMatrix(rect, "2x3 for Zigzag");
    diagonalTraverseLC498(rect);

    // Level 5
    diagonalSums(mat);

    // Level 6
    vector<vector<int>> rect2 = {{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15}};
    printMatrix(rect2, "3x5 Rectangular");
    rectangularDiagonals(rect2);

    // Level 7
    diagonalCheckDemo();

    // Level 7B: LC #1424
    vector<vector<int>> nums = {{1,2,3},{4,5,6},{7,8,9}};
    diagonalTraverseII(nums);

    // Jagged array test
    vector<vector<int>> jagged = {{1,2,3,4,5},{6,7},{8},{9,10,11}};
    diagonalTraverseII(jagged);

    return 0;
}

