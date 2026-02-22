/*
 * ============================================================================
 *              ROW-WISE MATRIX TRAVERSAL - ZERO TO GM MASTERY
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Topic   : Row-Wise Traversal (Left→Right, Right→Left, Even/Odd Rows)
 * Level   : 0 (Beginner) → 3 (Advanced)
 * ============================================================================
 *
 *  TABLE OF CONTENTS
 *  ─────────────────
 *  Level 0 : Row-Wise Left to Right Traversal
 *  Level 1 : Row-Wise Right to Left Traversal
 *  Level 2 : Row-Wise with Conditions (Even/Odd rows, specific rows)
 *  Level 3 : Row-Wise Aggregation (Row Sum, Row Max, Row Min)
 *  Level 4 : Flatten Matrix Row-Wise to 1D
 *  Level 5 : Reconstruct Matrix from 1D Array
 *
 * ============================================================================
 *  Time Complexity: O(N × M) for all traversals
 *  Space Complexity: O(1) extra (O(N×M) for storing results)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// Utility: Print Matrix
void printMatrix(const vector<vector<int>>& mat, const string& title = "") {
    if (!title.empty()) cout << "--- " << title << " ---" << endl;
    for (const auto& row : mat) {
        for (int val : row)
            cout << setw(4) << val;
        cout << "\n";
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 0: ROW-WISE LEFT TO RIGHT TRAVERSAL
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  The most natural traversal: visit each row from left to right.
 *
 *  For matrix:     Traversal Order:
 *  1  2  3         1 → 2 → 3 →
 *  4  5  6         4 → 5 → 6 →
 *  7  8  9         7 → 8 → 9
 *
 *  Result: 1, 2, 3, 4, 5, 6, 7, 8, 9
 */
void rowWiseLeftToRight(const vector<vector<int>>& mat) {
    cout << "=== Row-Wise Left to Right ===" << endl;
    int n = mat.size(), m = mat[0].size();

    cout << "Traversal: ";
    for (int i = 0; i < n; i++) {           // For each row
        for (int j = 0; j < m; j++) {       // Left to Right
            cout << mat[i][j] << " ";
        }
    }
    cout << "\n\n";
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 1: ROW-WISE RIGHT TO LEFT TRAVERSAL
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Visit each row from right to left.
 *
 *  For matrix:     Traversal Order:
 *  1  2  3         ← 3 ← 2 ← 1
 *  4  5  6         ← 6 ← 5 ← 4
 *  7  8  9         ← 9 ← 8 ← 7
 *
 *  Result: 3, 2, 1, 6, 5, 4, 9, 8, 7
 */
void rowWiseRightToLeft(const vector<vector<int>>& mat) {
    cout << "=== Row-Wise Right to Left ===" << endl;
    int n = mat.size(), m = mat[0].size();

    cout << "Traversal: ";
    for (int i = 0; i < n; i++) {           // For each row
        for (int j = m - 1; j >= 0; j--) {  // Right to Left
            cout << mat[i][j] << " ";
        }
    }
    cout << "\n\n";
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 1B: BOTTOM-UP ROW-WISE TRAVERSAL
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Start from the last row and go upward.
 *
 *  For matrix:     Traversal Order:
 *  1  2  3         7 → 8 → 9 (last row first)
 *  4  5  6         4 → 5 → 6
 *  7  8  9         1 → 2 → 3 (first row last)
 *
 *  Result: 7, 8, 9, 4, 5, 6, 1, 2, 3
 */
void rowWiseBottomUp(const vector<vector<int>>& mat) {
    cout << "=== Row-Wise Bottom to Top ===" << endl;
    int n = mat.size(), m = mat[0].size();

    cout << "Traversal: ";
    for (int i = n - 1; i >= 0; i--) {      // Bottom to Top
        for (int j = 0; j < m; j++) {        // Left to Right
            cout << mat[i][j] << " ";
        }
    }
    cout << "\n\n";
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 2: CONDITIONAL ROW TRAVERSAL
// ─────────────────────────────────────────────────────────────────────────────

// Only Even-Indexed Rows (0, 2, 4, ...)
void evenRowTraversal(const vector<vector<int>>& mat) {
    cout << "=== Even-Indexed Rows Only ===" << endl;
    int n = mat.size(), m = mat[0].size();

    cout << "Traversal: ";
    for (int i = 0; i < n; i += 2) {        // Step by 2
        for (int j = 0; j < m; j++)
            cout << mat[i][j] << " ";
    }
    cout << "\n\n";
}

// Only Odd-Indexed Rows (1, 3, 5, ...)
void oddRowTraversal(const vector<vector<int>>& mat) {
    cout << "=== Odd-Indexed Rows Only ===" << endl;
    int n = mat.size(), m = mat[0].size();

    cout << "Traversal: ";
    for (int i = 1; i < n; i += 2) {
        for (int j = 0; j < m; j++)
            cout << mat[i][j] << " ";
    }
    cout << "\n\n";
}

// Specific Row Range [startRow, endRow)
void rowRangeTraversal(const vector<vector<int>>& mat, int startRow, int endRow) {
    cout << "=== Rows [" << startRow << ", " << endRow << ") ===" << endl;
    int m = mat[0].size();

    cout << "Traversal: ";
    for (int i = startRow; i < endRow; i++) {
        for (int j = 0; j < m; j++)
            cout << mat[i][j] << " ";
    }
    cout << "\n\n";
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 3: ROW-WISE AGGREGATION
// ─────────────────────────────────────────────────────────────────────────────

// Row Sums
void rowSums(const vector<vector<int>>& mat) {
    cout << "=== Row Sums ===" << endl;
    int n = mat.size(), m = mat[0].size();

    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++)
            sum += mat[i][j];
        cout << "Row " << i << " sum = " << sum << endl;
    }
    // Using accumulate (STL)
    cout << "\nUsing STL accumulate:" << endl;
    for (int i = 0; i < n; i++) {
        int sum = accumulate(mat[i].begin(), mat[i].end(), 0);
        cout << "Row " << i << " sum = " << sum << endl;
    }
    cout << endl;
}

// Row Maximum and Minimum
void rowMaxMin(const vector<vector<int>>& mat) {
    cout << "=== Row Max and Min ===" << endl;
    int n = mat.size();

    for (int i = 0; i < n; i++) {
        int mx = *max_element(mat[i].begin(), mat[i].end());
        int mn = *min_element(mat[i].begin(), mat[i].end());
        cout << "Row " << i << ": max = " << mx << ", min = " << mn << endl;
    }
    cout << endl;
}

// Row with Maximum Sum
void rowWithMaxSum(const vector<vector<int>>& mat) {
    cout << "=== Row with Maximum Sum ===" << endl;
    int n = mat.size();
    int maxSum = INT_MIN, maxRow = 0;

    for (int i = 0; i < n; i++) {
        int sum = accumulate(mat[i].begin(), mat[i].end(), 0);
        if (sum > maxSum) {
            maxSum = sum;
            maxRow = i;
        }
    }
    cout << "Row " << maxRow << " has max sum = " << maxSum << endl << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 4: FLATTEN MATRIX ROW-WISE TO 1D
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Convert 2D matrix to 1D array (row-major order)
 *
 *  Matrix:           1D Array:
 *  1  2  3           [1, 2, 3, 4, 5, 6, 7, 8, 9]
 *  4  5  6
 *  7  8  9
 *
 *  Index Mapping: mat[i][j] → arr[i * M + j]
 */
vector<int> flattenRowWise(const vector<vector<int>>& mat) {
    cout << "=== Flatten Matrix Row-Wise ===" << endl;
    vector<int> result;
    for (const auto& row : mat)
        for (int val : row)
            result.push_back(val);

    cout << "1D: ";
    for (int x : result) cout << x << " ";
    cout << "\n\n";
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 5: RECONSTRUCT MATRIX FROM 1D ARRAY
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Convert 1D array back to 2D matrix
 *
 *  1D Array:         Matrix (3×3):
 *  [1,2,3,4,5,6,7,8,9]  →  1  2  3
 *                            4  5  6
 *                            7  8  9
 *
 *  Index Mapping: arr[k] → mat[k / M][k % M]
 */
vector<vector<int>> reconstructMatrix(const vector<int>& arr, int n, int m) {
    cout << "=== Reconstruct Matrix " << n << "x" << m << " ===" << endl;
    vector<vector<int>> mat(n, vector<int>(m));
    for (int k = 0; k < (int)arr.size(); k++) {
        mat[k / m][k % m] = arr[k];
    }
    printMatrix(mat);
    return mat;
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN - DEMO ALL CONCEPTS
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   ROW-WISE TRAVERSAL - ZERO TO GM MASTERY       ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << endl;

    // Sample Matrix
    vector<vector<int>> mat = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9,  10, 11, 12},
        {13, 14, 15, 16}
    };
    printMatrix(mat, "Original 4x4 Matrix");

    // Level 0
    rowWiseLeftToRight(mat);

    // Level 1
    rowWiseRightToLeft(mat);
    rowWiseBottomUp(mat);

    // Level 2
    evenRowTraversal(mat);
    oddRowTraversal(mat);
    rowRangeTraversal(mat, 1, 3); // Rows 1 and 2

    // Level 3
    rowSums(mat);
    rowMaxMin(mat);
    rowWithMaxSum(mat);

    // Level 4
    auto flat = flattenRowWise(mat);

    // Level 5
    reconstructMatrix(flat, 4, 4);

    return 0;
}

