/*
 * ============================================================================
 *              TRANSPOSE OF MATRIX - ZERO TO GM MASTERY
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Topic   : Matrix Transpose (In-Place, Extra Space, Rectangular)
 * Level   : 0 (Beginner) → 5 (GM)
 * ============================================================================
 *
 *  TABLE OF CONTENTS
 *  ─────────────────
 *  Level 0 : What is Transpose? (Concept + Visualization)
 *  Level 1 : Transpose with Extra Space
 *  Level 2 : In-Place Transpose (Square Matrix)
 *  Level 3 : Rectangular Matrix Transpose
 *  Level 4 : Transpose Properties & Applications
 *  Level 5 : Symmetric Matrix Check & Skew-Symmetric Check
 *
 * ============================================================================
 *  WHAT IS TRANSPOSE?
 *  ──────────────────
 *  Transpose of matrix A is A^T where:
 *  A^T[i][j] = A[j][i]
 *
 *  Rows become columns and columns become rows.
 *
 *  Original (3×4):        Transpose (4×3):
 *  1  2  3  4             1  5  9
 *  5  6  7  8             2  6  10
 *  9  10 11 12            3  7  11
 *                         4  8  12
 *
 *  Properties:
 *  - (A^T)^T = A
 *  - (A + B)^T = A^T + B^T
 *  - (kA)^T = kA^T
 *  - (AB)^T = B^T × A^T
 *  - If A = A^T → Symmetric Matrix
 *
 *  Related Problems:
 *  - LeetCode 867: Transpose Matrix
 *  - LeetCode 48: Rotate Image (uses transpose + reverse)
 * ============================================================================
 *  Time Complexity: O(N × M)
 *  Space Complexity: O(1) for in-place (square), O(N × M) for rectangular
 * ============================================================================
 */

#include <bits/stdc++.h>
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
// LEVEL 1: TRANSPOSE WITH EXTRA SPACE
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Create a new M×N matrix where result[j][i] = mat[i][j]
 *
 *  Works for both square and rectangular matrices.
 *  Time: O(N×M), Space: O(N×M)
 */
vector<vector<int>> transposeExtraSpace(const vector<vector<int>>& mat) {
    cout << "=== Transpose (Extra Space) ===" << endl;
    int n = mat.size(), m = mat[0].size();

    // Create M×N matrix (rows and cols swapped)
    vector<vector<int>> result(m, vector<int>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            result[j][i] = mat[i][j]; // Key: swap indices

    printMatrix(mat, "Original");
    printMatrix(result, "Transposed");
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 2: IN-PLACE TRANSPOSE (SQUARE MATRIX ONLY)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  For square matrix (N×N), swap mat[i][j] with mat[j][i].
 *  Only swap UPPER TRIANGLE to avoid double-swapping!
 *
 *  Before:          After:
 *  1  2  3          1  4  7
 *  4  5  6          2  5  8
 *  7  8  9          3  6  9
 *
 *  Swap pairs: (0,1)↔(1,0), (0,2)↔(2,0), (1,2)↔(2,1)
 *  Only iterate j > i (upper triangle)
 *
 *  Time: O(N²), Space: O(1) ← In-place!
 */
void transposeInPlace(vector<vector<int>>& mat) {
    cout << "=== In-Place Transpose (Square) ===" << endl;
    int n = mat.size();

    printMatrix(mat, "Before Transpose");

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) { // j starts from i+1 (upper triangle)
            swap(mat[i][j], mat[j][i]);
        }
    }

    printMatrix(mat, "After Transpose");
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 3: RECTANGULAR MATRIX TRANSPOSE
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Cannot do in-place for rectangular matrices (dimensions change!)
 *  Must use extra space: N×M → M×N
 *
 *  Original (2×4):       Transposed (4×2):
 *  1  2  3  4            1  5
 *  5  6  7  8            2  6
 *                        3  7
 *                        4  8
 */
vector<vector<int>> transposeRectangular(const vector<vector<int>>& mat) {
    cout << "=== Rectangular Matrix Transpose ===" << endl;
    int n = mat.size(), m = mat[0].size();

    vector<vector<int>> result(m, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            result[j][i] = mat[i][j];

    cout << "Original (" << n << "x" << m << ") → Transposed (" << m << "x" << n << ")" << endl;
    printMatrix(mat, "Original");
    printMatrix(result, "Transposed");
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 4: TRANSPOSE PROPERTIES & APPLICATIONS
// ─────────────────────────────────────────────────────────────────────────────

// Verify (A^T)^T = A
void verifyDoubleTranspose() {
    cout << "=== Verify (A^T)^T = A ===" << endl;
    vector<vector<int>> A = {{1,2,3},{4,5,6}};

    // First transpose: 2×3 → 3×2
    int n = A.size(), m = A[0].size();
    vector<vector<int>> AT(m, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            AT[j][i] = A[i][j];

    // Second transpose: 3×2 → 2×3
    int n2 = AT.size(), m2 = AT[0].size();
    vector<vector<int>> ATT(m2, vector<int>(n2));
    for (int i = 0; i < n2; i++)
        for (int j = 0; j < m2; j++)
            ATT[j][i] = AT[i][j];

    cout << "(A^T)^T == A? " << (A == ATT ? "YES ✓" : "NO ✗") << endl << endl;
}

// APPLICATION: Rotate Matrix 90° Clockwise = Transpose + Reverse each row
void rotate90CW(vector<vector<int>>& mat) {
    cout << "=== Rotate 90° CW = Transpose + Reverse Rows ===" << endl;
    int n = mat.size();
    printMatrix(mat, "Before Rotation");

    // Step 1: Transpose
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            swap(mat[i][j], mat[j][i]);

    // Step 2: Reverse each row
    for (int i = 0; i < n; i++)
        reverse(mat[i].begin(), mat[i].end());

    printMatrix(mat, "After 90° CW Rotation");
}

// APPLICATION: Rotate Matrix 90° Counter-Clockwise = Transpose + Reverse each column
void rotate90CCW(vector<vector<int>>& mat) {
    cout << "=== Rotate 90° CCW = Transpose + Reverse Columns ===" << endl;
    int n = mat.size();
    printMatrix(mat, "Before Rotation");

    // Step 1: Transpose
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            swap(mat[i][j], mat[j][i]);

    // Step 2: Reverse each column
    for (int j = 0; j < n; j++) {
        int top = 0, bottom = n - 1;
        while (top < bottom) {
            swap(mat[top][j], mat[bottom][j]);
            top++;
            bottom--;
        }
    }

    printMatrix(mat, "After 90° CCW Rotation");
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 5: SYMMETRIC MATRIX CHECK
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  A matrix is SYMMETRIC if A = A^T, i.e., A[i][j] = A[j][i] for all i, j.
 *
 *  Example of Symmetric Matrix:
 *  1  2  3
 *  2  5  6
 *  3  6  9
 *
 *  Time: O(N²), but only need to check upper triangle → O(N²/2)
 */
bool isSymmetric(const vector<vector<int>>& mat) {
    int n = mat.size();
    if (n == 0) return true;

    // Must be square
    for (const auto& row : mat)
        if ((int)row.size() != n) return false;

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (mat[i][j] != mat[j][i])
                return false;

    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 5B: SKEW-SYMMETRIC MATRIX CHECK
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  A matrix is SKEW-SYMMETRIC if A^T = -A, i.e., A[i][j] = -A[j][i]
 *  Also: diagonal elements must be 0 (since A[i][i] = -A[i][i] → 0)
 *
 *  Example:
 *   0   2  -3
 *  -2   0   5
 *   3  -5   0
 */
bool isSkewSymmetric(const vector<vector<int>>& mat) {
    int n = mat.size();
    for (const auto& row : mat)
        if ((int)row.size() != n) return false;

    for (int i = 0; i < n; i++) {
        if (mat[i][i] != 0) return false; // Diagonal must be 0
        for (int j = i + 1; j < n; j++)
            if (mat[i][j] != -mat[j][i])
                return false;
    }
    return true;
}

void symmetryDemo() {
    cout << "=== Symmetric & Skew-Symmetric Check ===" << endl;

    vector<vector<int>> sym = {
        {1, 2, 3},
        {2, 5, 6},
        {3, 6, 9}
    };
    printMatrix(sym, "Test Matrix 1");
    cout << "Symmetric? " << (isSymmetric(sym) ? "YES ✓" : "NO ✗") << endl;
    cout << "Skew-Symmetric? " << (isSkewSymmetric(sym) ? "YES ✓" : "NO ✗") << endl;
    cout << endl;

    vector<vector<int>> skew = {
        {0,  2, -3},
        {-2, 0,  5},
        {3, -5,  0}
    };
    printMatrix(skew, "Test Matrix 2");
    cout << "Symmetric? " << (isSymmetric(skew) ? "YES ✓" : "NO ✗") << endl;
    cout << "Skew-Symmetric? " << (isSkewSymmetric(skew) ? "YES ✓" : "NO ✗") << endl;
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║    TRANSPOSE MATRIX - ZERO TO GM MASTERY        ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << endl;

    // Level 1: Extra Space Transpose
    vector<vector<int>> mat1 = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    transposeExtraSpace(mat1);

    // Level 2: In-Place Transpose (Square)
    vector<vector<int>> mat2 = {{1,2,3},{4,5,6},{7,8,9}};
    transposeInPlace(mat2);

    // Level 3: Rectangular Transpose
    vector<vector<int>> mat3 = {{1,2,3,4},{5,6,7,8}};
    transposeRectangular(mat3);

    // Level 4: Properties & Applications
    verifyDoubleTranspose();

    vector<vector<int>> mat4 = {{1,2,3},{4,5,6},{7,8,9}};
    rotate90CW(mat4);

    vector<vector<int>> mat5 = {{1,2,3},{4,5,6},{7,8,9}};
    rotate90CCW(mat5);

    // Level 5: Symmetry Checks
    symmetryDemo();

    return 0;
}

