/*
 * ============================================================================
 *             BOUNDARY TRAVERSAL - ZERO TO GM MASTERY
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Topic   : Matrix Boundary/Border Traversal
 * Level   : 0 (Beginner) → 5 (GM)
 * ============================================================================
 *
 *  TABLE OF CONTENTS
 *  ─────────────────
 *  Level 0 : Simple Boundary Check (is element on boundary?)
 *  Level 1 : Clockwise Boundary Traversal
 *  Level 2 : Anti-Clockwise Boundary Traversal
 *  Level 3 : Boundary Sum / Boundary Elements Collection
 *  Level 4 : Print Only Boundary (rest as *)
 *  Level 5 : Edge Cases (Single Row, Single Column, 1x1)
 *
 * ============================================================================
 *  Time Complexity: O(2*(N + M) - 4) = O(N + M) for boundary
 *  Space Complexity: O(1) extra (O(N + M) if storing elements)
 *
 *  BOUNDARY ELEMENTS COUNT:
 *  - For N×M matrix: 2*(N + M) - 4 boundary elements
 *  - For N=M (square): 4*N - 4 boundary elements
 *  - Special: N=1 → M elements; M=1 → N elements; N=M=1 → 1 element
 * ============================================================================
 */

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <random>
#include <chrono>

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
// LEVEL 0: IS ELEMENT ON BOUNDARY?
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  An element mat[i][j] is on the boundary if:
 *  - i == 0 (first row) OR
 *  - i == n-1 (last row) OR
 *  - j == 0 (first column) OR
 *  - j == m-1 (last column)
 *
 *  Visualization (B = Boundary, I = Interior):
 *  B B B B B
 *  B I I I B
 *  B I I I B
 *  B B B B B
 */
bool isBoundary(int i, int j, int n, int m) {
    return (i == 0 || i == n - 1 || j == 0 || j == m - 1);
}

void boundaryCheckDemo(const vector<vector<int>>& mat) {
    cout << "=== Boundary Check Demo ===" << endl;
    int n = mat.size(), m = mat[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (isBoundary(i, j, n, m))
                cout << setw(4) << mat[i][j];
            else
                cout << "   *";
        }
        cout << "\n";
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 1: CLOCKWISE BOUNDARY TRAVERSAL
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Traverse boundary elements in clockwise order:
 *
 *  Step 1: Top row (left → right)     →→→→→
 *  Step 2: Right column (top → bottom)     ↓
 *  Step 3: Bottom row (right → left)  ←←←←←
 *  Step 4: Left column (bottom → top) ↑
 *
 *  Example 4×5 matrix:
 *   1  2  3  4  5
 *   6  7  8  9 10
 *  11 12 13 14 15
 *  16 17 18 19 20
 *
 *  Clockwise: 1,2,3,4,5, 10,15,20, 19,18,17,16, 11,6
 */
vector<int> clockwiseBoundary(const vector<vector<int>>& mat) {
    cout << "=== Clockwise Boundary Traversal ===" << endl;
    int n = mat.size(), m = mat[0].size();
    vector<int> result;

    if (n == 0 || m == 0) return result;

    // Handle single row
    if (n == 1) {
        for (int j = 0; j < m; j++)
            result.push_back(mat[0][j]);
        return result;
    }

    // Handle single column
    if (m == 1) {
        for (int i = 0; i < n; i++)
            result.push_back(mat[i][0]);
        return result;
    }

    // Step 1: Top row → (left to right)
    for (int j = 0; j < m; j++)
        result.push_back(mat[0][j]);

    // Step 2: Right column ↓ (top+1 to bottom)
    for (int i = 1; i < n; i++)
        result.push_back(mat[i][m - 1]);

    // Step 3: Bottom row ← (right-1 to left)
    for (int j = m - 2; j >= 0; j--)
        result.push_back(mat[n - 1][j]);

    // Step 4: Left column ↑ (bottom-1 to top+1)
    for (int i = n - 2; i >= 1; i--)
        result.push_back(mat[i][0]);

    cout << "Order: ";
    for (int x : result) cout << x << " ";
    cout << "\nCount: " << result.size() << " elements\n\n";
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 2: ANTI-CLOCKWISE BOUNDARY TRAVERSAL
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Traverse boundary in anti-clockwise (counter-clockwise) order:
 *
 *  Step 1: Top row (left → right)          →→→→→
 *  Step 2: Left column (top+1 → bottom)    ↓
 *  Step 3: Bottom row (left+1 → right)     →→→→→
 *  Step 4: Right column (bottom-1 → top+1) ↑
 *
 *  Actually for true anti-clockwise starting from top-left:
 *  Step 1: Left column ↓ (top → bottom)
 *  Step 2: Bottom row → (left+1 → right)
 *  Step 3: Right column ↑ (bottom-1 → top)
 *  Step 4: Top row ← (right-1 → left+1)
 */
vector<int> antiClockwiseBoundary(const vector<vector<int>>& mat) {
    cout << "=== Anti-Clockwise Boundary Traversal ===" << endl;
    int n = mat.size(), m = mat[0].size();
    vector<int> result;

    if (n == 0 || m == 0) return result;
    if (n == 1) {
        for (int j = 0; j < m; j++) result.push_back(mat[0][j]);
        return result;
    }
    if (m == 1) {
        for (int i = 0; i < n; i++) result.push_back(mat[i][0]);
        return result;
    }

    // Step 1: Left column ↓
    for (int i = 0; i < n; i++)
        result.push_back(mat[i][0]);

    // Step 2: Bottom row →
    for (int j = 1; j < m; j++)
        result.push_back(mat[n - 1][j]);

    // Step 3: Right column ↑
    for (int i = n - 2; i >= 0; i--)
        result.push_back(mat[i][m - 1]);

    // Step 4: Top row ←
    for (int j = m - 2; j >= 1; j--)
        result.push_back(mat[0][j]);

    cout << "Order: ";
    for (int x : result) cout << x << " ";
    cout << "\nCount: " << result.size() << " elements\n\n";
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 3: BOUNDARY SUM & INTERIOR SUM
// ─────────────────────────────────────────────────────────────────────────────
void boundarySumAndInterior(const vector<vector<int>>& mat) {
    cout << "=== Boundary Sum vs Interior Sum ===" << endl;
    int n = mat.size(), m = mat[0].size();
    long long boundarySum = 0, interiorSum = 0, totalSum = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            totalSum += mat[i][j];
            if (isBoundary(i, j, n, m))
                boundarySum += mat[i][j];
            else
                interiorSum += mat[i][j];
        }
    }

    cout << "Boundary Sum  = " << boundarySum << endl;
    cout << "Interior Sum  = " << interiorSum << endl;
    cout << "Total Sum     = " << totalSum << endl;
    cout << "Boundary + Interior = " << boundarySum + interiorSum << endl;
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 4: BOUNDARY ELEMENTS COLLECTION (various methods)
// ─────────────────────────────────────────────────────────────────────────────

// Get all boundary elements as a sorted vector
vector<int> getBoundaryElements(const vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    vector<int> boundary;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (isBoundary(i, j, n, m))
                boundary.push_back(mat[i][j]);

    return boundary;
}

// Replace boundary with a specific value
vector<vector<int>> replaceBoundary(vector<vector<int>> mat, int val) {
    int n = mat.size(), m = mat[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (isBoundary(i, j, n, m))
                mat[i][j] = val;
    return mat;
}

// Replace interior with a specific value
vector<vector<int>> replaceInterior(vector<vector<int>> mat, int val) {
    int n = mat.size(), m = mat[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (!isBoundary(i, j, n, m))
                mat[i][j] = val;
    return mat;
}

void boundaryOperationsDemo(const vector<vector<int>>& mat) {
    cout << "=== Boundary Operations Demo ===" << endl;

    auto boundary = getBoundaryElements(mat);
    sort(boundary.begin(), boundary.end());
    cout << "Sorted boundary elements: ";
    for (int x : boundary) cout << x << " ";
    cout << endl;

    cout << "Min boundary = " << boundary.front() << endl;
    cout << "Max boundary = " << boundary.back() << endl;

    auto replaced = replaceBoundary(mat, 0);
    printMatrix(replaced, "Boundary replaced with 0");

    auto interior = replaceInterior(mat, 0);
    printMatrix(interior, "Interior replaced with 0");
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 5: EDGE CASES
// ─────────────────────────────────────────────────────────────────────────────
void edgeCasesDemo() {
    cout << "=== Edge Cases ===" << endl;

    // 1x1 Matrix
    cout << "1x1 Matrix:" << endl;
    vector<vector<int>> mat1 = {{42}};
    auto b1 = clockwiseBoundary(mat1);

    // Single Row
    cout << "1xM (Single Row):" << endl;
    vector<vector<int>> mat2 = {{1, 2, 3, 4, 5}};
    auto b2 = clockwiseBoundary(mat2);

    // Single Column
    cout << "Nx1 (Single Column):" << endl;
    vector<vector<int>> mat3 = {{1}, {2}, {3}, {4}};
    auto b3 = clockwiseBoundary(mat3);

    // 2x2 Matrix (all boundary, no interior)
    cout << "2x2 Matrix (all boundary):" << endl;
    vector<vector<int>> mat4 = {{1, 2}, {3, 4}};
    auto b4 = clockwiseBoundary(mat4);
    cout << "Interior count = 0 (all elements are boundary)" << endl;

    // 3x3 Matrix (1 interior element)
    cout << "3x3 Matrix (1 interior):" << endl;
    vector<vector<int>> mat5 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto b5 = clockwiseBoundary(mat5);
    cout << "Interior element = mat[1][1] = " << mat5[1][1] << endl;
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║    BOUNDARY TRAVERSAL - ZERO TO GM MASTERY      ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << endl;

    vector<vector<int>> mat = {
        {1,  2,  3,  4,  5},
        {6,  7,  8,  9,  10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20}
    };
    printMatrix(mat, "Original 4x5 Matrix");

    // Level 0
    boundaryCheckDemo(mat);

    // Level 1
    clockwiseBoundary(mat);

    // Level 2
    antiClockwiseBoundary(mat);

    // Level 3
    boundarySumAndInterior(mat);

    // Level 4
    boundaryOperationsDemo(mat);

    // Level 5
    edgeCasesDemo();

    return 0;
}

