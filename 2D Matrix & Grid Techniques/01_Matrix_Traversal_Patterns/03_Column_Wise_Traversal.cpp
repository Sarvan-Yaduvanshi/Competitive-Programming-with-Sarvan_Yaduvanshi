/*
 * ============================================================================
 *            COLUMN-WISE MATRIX TRAVERSAL - ZERO TO GM MASTERY
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Topic   : Column-Wise Traversal (Top→Bottom, Bottom→Top, Aggregations)
 * Level   : 0 (Beginner) → 4 (Advanced)
 * ============================================================================
 *
 *  TABLE OF CONTENTS
 *  ─────────────────
 *  Level 0 : Column-Wise Top to Bottom Traversal
 *  Level 1 : Column-Wise Bottom to Top Traversal
 *  Level 2 : Right-to-Left Column Traversal
 *  Level 3 : Column-Wise Aggregation (Sum, Max, Min)
 *  Level 4 : Flatten Column-Wise & Cache Performance Analysis
 *
 * ============================================================================
 *  Time Complexity: O(N × M) for all traversals
 *  Space Complexity: O(1) extra
 *
 *  ⚠ CACHE WARNING:
 *  Column-wise traversal is NOT cache-friendly in C++ (row-major layout).
 *  For N > 1000, column-wise can be 2-5x slower than row-wise.
 *  In competitive programming, this usually doesn't matter for typical
 *  constraints (N, M ≤ 1000), but be aware for N, M ≥ 5000.
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
        for (int val : row)
            cout << setw(4) << val;
        cout << "\n";
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 0: COLUMN-WISE TOP TO BOTTOM TRAVERSAL
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Visit each column from top to bottom, moving left to right.
 *
 *  For matrix:     Traversal Order:
 *  1  2  3         ↓     ↓     ↓
 *  4  5  6         1→4→7 2→5→8 3→6→9
 *  7  8  9
 *
 *  Result: 1, 4, 7, 2, 5, 8, 3, 6, 9
 *
 *  KEY DIFFERENCE from Row-Wise:
 *  - Outer loop = columns (j)
 *  - Inner loop = rows (i)
 */
void colWiseTopToBottom(const vector<vector<int>>& mat) {
    cout << "=== Column-Wise Top to Bottom ===" << endl;
    int n = mat.size(), m = mat[0].size();

    cout << "Traversal: ";
    for (int j = 0; j < m; j++) {           // For each column
        for (int i = 0; i < n; i++) {       // Top to Bottom
            cout << mat[i][j] << " ";
        }
    }
    cout << "\n\n";
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 1: COLUMN-WISE BOTTOM TO TOP TRAVERSAL
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Visit each column from bottom to top, moving left to right.
 *
 *  For matrix:     Traversal Order:
 *  1  2  3         ↑     ↑     ↑
 *  4  5  6         7→4→1 8→5→2 9→6→3
 *  7  8  9
 *
 *  Result: 7, 4, 1, 8, 5, 2, 9, 6, 3
 */
void colWiseBottomToTop(const vector<vector<int>>& mat) {
    cout << "=== Column-Wise Bottom to Top ===" << endl;
    int n = mat.size(), m = mat[0].size();

    cout << "Traversal: ";
    for (int j = 0; j < m; j++) {           // For each column
        for (int i = n - 1; i >= 0; i--) {  // Bottom to Top
            cout << mat[i][j] << " ";
        }
    }
    cout << "\n\n";
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 2: RIGHT-TO-LEFT COLUMN TRAVERSAL
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Visit columns from right to left, each column top to bottom.
 *
 *  For matrix:     Traversal Order:
 *  1  2  3         Col2↓  Col1↓  Col0↓
 *  4  5  6         3→6→9  2→5→8  1→4→7
 *  7  8  9
 *
 *  Result: 3, 6, 9, 2, 5, 8, 1, 4, 7
 */
void colWiseRightToLeft(const vector<vector<int>>& mat) {
    cout << "=== Column-Wise Right to Left ===" << endl;
    int n = mat.size(), m = mat[0].size();

    cout << "Traversal: ";
    for (int j = m - 1; j >= 0; j--) {      // Right to Left columns
        for (int i = 0; i < n; i++) {        // Top to Bottom
            cout << mat[i][j] << " ";
        }
    }
    cout << "\n\n";
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 2B: ALL 4 COLUMN TRAVERSAL COMBINATIONS
// ─────────────────────────────────────────────────────────────────────────────
void allColumnTraversals(const vector<vector<int>>& mat) {
    cout << "=== All 4 Column Traversal Combinations ===" << endl;
    int n = mat.size(), m = mat[0].size();

    // 1. Left-to-Right columns, Top-to-Bottom rows (standard)
    cout << "L→R cols, T→B rows: ";
    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++)
            cout << mat[i][j] << " ";
    cout << endl;

    // 2. Left-to-Right columns, Bottom-to-Top rows
    cout << "L→R cols, B→T rows: ";
    for (int j = 0; j < m; j++)
        for (int i = n-1; i >= 0; i--)
            cout << mat[i][j] << " ";
    cout << endl;

    // 3. Right-to-Left columns, Top-to-Bottom rows
    cout << "R→L cols, T→B rows: ";
    for (int j = m-1; j >= 0; j--)
        for (int i = 0; i < n; i++)
            cout << mat[i][j] << " ";
    cout << endl;

    // 4. Right-to-Left columns, Bottom-to-Top rows
    cout << "R→L cols, B→T rows: ";
    for (int j = m-1; j >= 0; j--)
        for (int i = n-1; i >= 0; i--)
            cout << mat[i][j] << " ";
    cout << "\n\n";
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 3: COLUMN-WISE AGGREGATION
// ─────────────────────────────────────────────────────────────────────────────

// Column Sums
void colSums(const vector<vector<int>>& mat) {
    cout << "=== Column Sums ===" << endl;
    int n = mat.size(), m = mat[0].size();

    for (int j = 0; j < m; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++)
            sum += mat[i][j];
        cout << "Col " << j << " sum = " << sum << endl;
    }
    cout << endl;
}

// Column Maximum and Minimum
void colMaxMin(const vector<vector<int>>& mat) {
    cout << "=== Column Max and Min ===" << endl;
    int n = mat.size(), m = mat[0].size();

    for (int j = 0; j < m; j++) {
        int mx = INT_MIN, mn = INT_MAX;
        for (int i = 0; i < n; i++) {
            mx = max(mx, mat[i][j]);
            mn = min(mn, mat[i][j]);
        }
        cout << "Col " << j << ": max = " << mx << ", min = " << mn << endl;
    }
    cout << endl;
}

// Column with Maximum Sum
void colWithMaxSum(const vector<vector<int>>& mat) {
    cout << "=== Column with Maximum Sum ===" << endl;
    int n = mat.size(), m = mat[0].size();
    int maxSum = INT_MIN, maxCol = 0;

    for (int j = 0; j < m; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++)
            sum += mat[i][j];
        if (sum > maxSum) {
            maxSum = sum;
            maxCol = j;
        }
    }
    cout << "Col " << maxCol << " has max sum = " << maxSum << endl << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 4: FLATTEN COLUMN-WISE & RECONSTRUCT
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Flatten matrix in column-major order:
 *
 *  Matrix:           1D (Column-Major):
 *  1  2  3           [1, 4, 7, 2, 5, 8, 3, 6, 9]
 *  4  5  6
 *  7  8  9
 *
 *  Index Mapping (Column-Major):
 *  mat[i][j] → arr[j * N + i]
 *  arr[k] → mat[k % N][k / N]
 */
void flattenColumnWise(const vector<vector<int>>& mat) {
    cout << "=== Flatten Column-Wise ===" << endl;
    int n = mat.size(), m = mat[0].size();
    vector<int> result;

    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++)
            result.push_back(mat[i][j]);

    cout << "Column-major 1D: ";
    for (int x : result) cout << x << " ";
    cout << endl;

    // Reconstruct back
    cout << "Reconstructed:" << endl;
    vector<vector<int>> rebuilt(n, vector<int>(m));
    for (int k = 0; k < (int)result.size(); k++) {
        int i = k % n;
        int j = k / n;
        rebuilt[i][j] = result[k];
    }
    printMatrix(rebuilt);
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 4B: CACHE PERFORMANCE COMPARISON
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  This demonstrates the performance difference between
 *  row-wise (cache-friendly) and column-wise (cache-unfriendly) traversal.
 *
 *  For large matrices, row-wise traversal is significantly faster
 *  because C++ stores arrays in row-major order.
 *
 *  ┌──────────────────────────────────────────────────────┐
 *  │  Row-wise:    Memory access pattern: [0][1][2][3]... │
 *  │               Sequential → Cache HITS               │
 *  │                                                      │
 *  │  Column-wise: Memory access pattern: [0][M][2M]...   │
 *  │               Jumping → Cache MISSES                 │
 *  └──────────────────────────────────────────────────────┘
 */
void cachePerformanceDemo() {
    cout << "=== Cache Performance Demo ===" << endl;
    const int N = 2000;
    vector<vector<int>> mat(N, vector<int>(N, 1));

    // Row-wise sum (cache friendly)
    auto start = chrono::high_resolution_clock::now();
    long long rowSum = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            rowSum += mat[i][j];
    auto end = chrono::high_resolution_clock::now();
    auto rowTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Column-wise sum (cache unfriendly)
    start = chrono::high_resolution_clock::now();
    long long colSum = 0;
    for (int j = 0; j < N; j++)
        for (int i = 0; i < N; i++)
            colSum += mat[i][j];
    end = chrono::high_resolution_clock::now();
    auto colTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Matrix size: " << N << " x " << N << endl;
    cout << "Row-wise sum time: " << rowTime << " μs (sum = " << rowSum << ")" << endl;
    cout << "Col-wise sum time: " << colTime << " μs (sum = " << colSum << ")" << endl;
    cout << "Ratio (col/row): " << (double)colTime / rowTime << "x" << endl;
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   COLUMN-WISE TRAVERSAL - ZERO TO GM MASTERY    ║" << endl;
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
    colWiseTopToBottom(mat);

    // Level 1
    colWiseBottomToTop(mat);

    // Level 2
    colWiseRightToLeft(mat);
    allColumnTraversals(mat);

    // Level 3
    colSums(mat);
    colMaxMin(mat);
    colWithMaxSum(mat);

    // Level 4
    flattenColumnWise(mat);
    cachePerformanceDemo();

    return 0;
}

