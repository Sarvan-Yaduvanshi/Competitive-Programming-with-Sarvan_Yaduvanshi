/*
 * ============================================================================
 *         MATRIX ROTATION (90°, 180°, 270°) - ZERO TO GM MASTERY
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Topic   : Matrix Rotation In-Place & Extra Space
 * Level   : 0 (Beginner) → 6 (GM)
 * ============================================================================
 *
 *  TABLE OF CONTENTS
 *  ─────────────────
 *  Level 0 : Understanding Rotation (Index Mapping)
 *  Level 1 : Rotate 90° Clockwise (Extra Space)
 *  Level 2 : Rotate 90° Clockwise (In-Place) [LC #48]
 *  Level 3 : Rotate 90° Counter-Clockwise
 *  Level 4 : Rotate 180°
 *  Level 5 : Rotate 270° (= 90° CCW = 3× 90° CW)
 *  Level 6 : Rotate Rectangular Matrix & Rotate by K×90°
 *
 * ============================================================================
 *  ROTATION INDEX MAPPINGS (N×N Matrix):
 *  ┌───────────────────────────────────────────────────────────────┐
 *  │  90° CW:   (i, j) → (j, N-1-i)                              │
 *  │  90° CCW:  (i, j) → (N-1-j, i)                              │
 *  │  180°:     (i, j) → (N-1-i, N-1-j)                          │
 *  │  270° CW:  Same as 90° CCW                                   │
 *  └───────────────────────────────────────────────────────────────┘
 *
 *  IN-PLACE ROTATION FORMULAS:
 *  ┌───────────────────────────────────────────────────────────────┐
 *  │  90° CW:   Transpose + Reverse each ROW                     │
 *  │  90° CCW:  Transpose + Reverse each COLUMN                  │
 *  │         OR Reverse each ROW + Transpose                     │
 *  │  180°:     Reverse each ROW + Reverse each COLUMN           │
 *  │         OR Rotate 90° twice                                 │
 *  └───────────────────────────────────────────────────────────────┘
 *
 *  Related Problems:
 *  - LC #48: Rotate Image
 *  - LC #1886: Determine Whether Matrix Can Be Obtained By Rotation
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
// LEVEL 0: UNDERSTANDING ROTATION (INDEX MAPPING)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Original:     90° CW:       180°:         90° CCW (270° CW):
 *  1  2  3       7  4  1       9  8  7       3  6  9
 *  4  5  6       8  5  2       6  5  4       2  5  8
 *  7  8  9       9  6  3       3  2  1       1  4  7
 *
 *  For 90° CW rotation:
 *  (0,0)→(0,2)  (0,1)→(1,2)  (0,2)→(2,2)
 *  (1,0)→(0,1)  (1,1)→(1,1)  (1,2)→(2,1)
 *  (2,0)→(0,0)  (2,1)→(1,0)  (2,2)→(2,0)
 *
 *  General: (i, j) → (j, N-1-i)
 *
 *  FOUR-ELEMENT CYCLE (for in-place rotation):
 *  Element at (i,j) moves to (j, N-1-i)
 *  Which moves to (N-1-i, N-1-j)
 *  Which moves to (N-1-j, i)
 *  Which moves back to (i, j)
 *  These 4 form a rotation cycle!
 */
void indexMappingDemo() {
    cout << "=== Rotation Index Mapping Demo ===" << endl;
    int n = 4;
    cout << "For " << n << "x" << n << " matrix:" << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "  (" << i << "," << j << ") →90°CW→ ("
                 << j << "," << n-1-i << ")" << endl;
        }
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 1: ROTATE 90° CLOCKWISE (EXTRA SPACE)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Create new matrix: result[j][N-1-i] = mat[i][j]
 *  Time: O(N²), Space: O(N²)
 */
vector<vector<int>> rotate90CW_ExtraSpace(const vector<vector<int>>& mat) {
    cout << "=== Rotate 90° CW (Extra Space) ===" << endl;
    int n = mat.size();
    vector<vector<int>> result(n, vector<int>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[j][n - 1 - i] = mat[i][j];

    printMatrix(mat, "Before");
    printMatrix(result, "After 90° CW");
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 2: ROTATE 90° CLOCKWISE (IN-PLACE) — LC #48
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  METHOD 1: Transpose + Reverse Each Row
 *  ──────────────────────────────────────
 *  Step 1: Transpose (swap mat[i][j] with mat[j][i])
 *    1  2  3       1  4  7
 *    4  5  6  →    2  5  8
 *    7  8  9       3  6  9
 *
 *  Step 2: Reverse each row
 *    1  4  7       7  4  1
 *    2  5  8  →    8  5  2
 *    3  6  9       9  6  3
 *
 *  Time: O(N²), Space: O(1)  ← In-place!
 */
void rotate90CW_InPlace_Method1(vector<vector<int>>& mat) {
    cout << "=== Rotate 90° CW In-Place (Transpose + Reverse) ===" << endl;
    int n = mat.size();
    printMatrix(mat, "Before");

    // Step 1: Transpose
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            swap(mat[i][j], mat[j][i]);

    // Step 2: Reverse each row
    for (int i = 0; i < n; i++)
        reverse(mat[i].begin(), mat[i].end());

    printMatrix(mat, "After 90° CW");
}

/*
 *  METHOD 2: Four-Element Cycle Swap
 *  ──────────────────────────────────
 *  Process elements in rings (layers) from outside to inside.
 *  For each element in the top row of a ring, do a 4-way swap:
 *
 *  temp            = mat[i][j]
 *  mat[i][j]       = mat[N-1-j][i]
 *  mat[N-1-j][i]   = mat[N-1-i][N-1-j]
 *  mat[N-1-i][N-1-j] = mat[j][N-1-i]
 *  mat[j][N-1-i]   = temp
 *
 *  Time: O(N²), Space: O(1)
 */
void rotate90CW_InPlace_Method2(vector<vector<int>>& mat) {
    cout << "=== Rotate 90° CW In-Place (4-way Swap) ===" << endl;
    int n = mat.size();
    printMatrix(mat, "Before");

    for (int layer = 0; layer < n / 2; layer++) {
        int first = layer;
        int last = n - 1 - layer;

        for (int i = first; i < last; i++) {
            int offset = i - first;

            // Save top
            int temp = mat[first][i];

            // Left → Top
            mat[first][i] = mat[last - offset][first];

            // Bottom → Left
            mat[last - offset][first] = mat[last][last - offset];

            // Right → Bottom
            mat[last][last - offset] = mat[i][last];

            // Top (saved) → Right
            mat[i][last] = temp;
        }
    }

    printMatrix(mat, "After 90° CW");
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 3: ROTATE 90° COUNTER-CLOCKWISE
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  METHOD 1: Transpose + Reverse Each Column
 *
 *  Original:     Transpose:     Reverse Cols:
 *  1  2  3       1  4  7        3  6  9
 *  4  5  6  →    2  5  8   →    2  5  8
 *  7  8  9       3  6  9        1  4  7
 *
 *  METHOD 2: Reverse Each Row + Transpose
 *
 *  Original:     Reverse Rows:  Transpose:
 *  1  2  3       3  2  1        3  6  9
 *  4  5  6  →    6  5  4   →    2  5  8
 *  7  8  9       9  8  7        1  4  7
 *
 *  Both give same result! Time: O(N²), Space: O(1)
 */
void rotate90CCW_InPlace(vector<vector<int>>& mat) {
    cout << "=== Rotate 90° CCW In-Place ===" << endl;
    int n = mat.size();
    printMatrix(mat, "Before");

    // Method: Transpose + Reverse each column
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

    printMatrix(mat, "After 90° CCW");
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 4: ROTATE 180°
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  180° rotation: (i, j) → (N-1-i, N-1-j)
 *
 *  Original:     180°:
 *  1  2  3       9  8  7
 *  4  5  6  →    6  5  4
 *  7  8  9       3  2  1
 *
 *  Methods:
 *  1. Reverse each row, then reverse the order of rows
 *  2. Apply 90° CW twice
 *  3. Swap mat[i][j] with mat[N-1-i][N-1-j] for first half of elements
 *
 *  Time: O(N²), Space: O(1)
 */
void rotate180_InPlace(vector<vector<int>>& mat) {
    cout << "=== Rotate 180° In-Place ===" << endl;
    int n = mat.size();
    printMatrix(mat, "Before");

    // Method: Reverse each row + Reverse order of rows
    // Step 1: Reverse each row
    for (int i = 0; i < n; i++)
        reverse(mat[i].begin(), mat[i].end());

    // Step 2: Reverse order of rows
    reverse(mat.begin(), mat.end());

    printMatrix(mat, "After 180°");
}

// Alternative: Direct swap
void rotate180_DirectSwap(vector<vector<int>>& mat) {
    cout << "=== Rotate 180° (Direct Swap) ===" << endl;
    int n = mat.size();
    printMatrix(mat, "Before");

    int total = n * n;
    for (int k = 0; k < total / 2; k++) {
        int i1 = k / n, j1 = k % n;
        int i2 = n - 1 - i1, j2 = n - 1 - j1;
        swap(mat[i1][j1], mat[i2][j2]);
    }

    printMatrix(mat, "After 180°");
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 5: ROTATE 270° CW (= 90° CCW)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  270° CW = 90° CCW = Three 90° CW rotations
 *
 *  Original:     270° CW:
 *  1  2  3       3  6  9
 *  4  5  6  →    2  5  8
 *  7  8  9       1  4  7
 */
void rotate270CW_InPlace(vector<vector<int>>& mat) {
    cout << "=== Rotate 270° CW (= 90° CCW) ===" << endl;
    int n = mat.size();
    printMatrix(mat, "Before");

    // Same as 90° CCW: Reverse each row + Transpose
    for (int i = 0; i < n; i++)
        reverse(mat[i].begin(), mat[i].end());

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            swap(mat[i][j], mat[j][i]);

    printMatrix(mat, "After 270° CW");
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 6: ROTATE BY K × 90° & RECTANGULAR MATRIX ROTATION
// ─────────────────────────────────────────────────────────────────────────────

// General rotation by k * 90° (k can be any integer)
void rotateByK(vector<vector<int>>& mat, int k) {
    k = ((k % 4) + 4) % 4; // Normalize to 0, 1, 2, 3
    cout << "=== Rotate by " << k << " × 90° ===" << endl;

    for (int t = 0; t < k; t++) {
        // Apply 90° CW rotation
        int n = mat.size();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                swap(mat[i][j], mat[j][i]);
        for (int i = 0; i < n; i++)
            reverse(mat[i].begin(), mat[i].end());
    }

    printMatrix(mat, "After Rotation");
}

// Rotate Rectangular Matrix 90° CW (requires new matrix since dimensions change)
vector<vector<int>> rotateRectangular90CW(const vector<vector<int>>& mat) {
    cout << "=== Rotate Rectangular Matrix 90° CW ===" << endl;
    int n = mat.size(), m = mat[0].size();
    printMatrix(mat, "Original " + to_string(n) + "x" + to_string(m));

    // N×M → M×N
    vector<vector<int>> result(m, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            result[j][n - 1 - i] = mat[i][j];

    printMatrix(result, "Rotated " + to_string(m) + "x" + to_string(n));
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 6B: CHECK IF ROTATION POSSIBLE (LC #1886)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Given two N×N matrices, check if one can be obtained by rotating
 *  the other by 0°, 90°, 180°, or 270°.
 *
 *  LC #1886: Determine Whether Matrix Can Be Obtained By Rotation
 *  Time: O(N²), Space: O(1)
 */
bool canObtainByRotation(vector<vector<int>> mat, vector<vector<int>>& target) {
    cout << "=== Can Obtain By Rotation? ===" << endl;
    int n = mat.size();

    for (int rot = 0; rot < 4; rot++) {
        if (mat == target) {
            cout << "YES! After " << rot << " × 90° CW rotations" << endl << endl;
            return true;
        }
        // Rotate 90° CW
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                swap(mat[i][j], mat[j][i]);
        for (int i = 0; i < n; i++)
            reverse(mat[i].begin(), mat[i].end());
    }

    cout << "NO! Cannot be obtained by rotation" << endl << endl;
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║    MATRIX ROTATION - ZERO TO GM MASTERY         ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << endl;

    // Level 0: Index Mapping
    indexMappingDemo();

    // Level 1: Extra Space
    vector<vector<int>> mat1 = {{1,2,3},{4,5,6},{7,8,9}};
    rotate90CW_ExtraSpace(mat1);

    // Level 2: In-Place 90° CW
    vector<vector<int>> mat2a = {{1,2,3},{4,5,6},{7,8,9}};
    rotate90CW_InPlace_Method1(mat2a);

    vector<vector<int>> mat2b = {{1,2,3},{4,5,6},{7,8,9}};
    rotate90CW_InPlace_Method2(mat2b);

    // Level 3: 90° CCW
    vector<vector<int>> mat3 = {{1,2,3},{4,5,6},{7,8,9}};
    rotate90CCW_InPlace(mat3);

    // Level 4: 180°
    vector<vector<int>> mat4a = {{1,2,3},{4,5,6},{7,8,9}};
    rotate180_InPlace(mat4a);

    vector<vector<int>> mat4b = {{1,2,3},{4,5,6},{7,8,9}};
    rotate180_DirectSwap(mat4b);

    // Level 5: 270° CW
    vector<vector<int>> mat5 = {{1,2,3},{4,5,6},{7,8,9}};
    rotate270CW_InPlace(mat5);

    // Level 6: Rotate by K
    vector<vector<int>> mat6 = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
    printMatrix(mat6, "Original 4x4");
    rotateByK(mat6, 2); // 180°

    // Rectangular rotation
    vector<vector<int>> rect = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    rotateRectangular90CW(rect);

    // LC #1886
    vector<vector<int>> src = {{0,1},{1,0}};
    vector<vector<int>> tgt = {{1,0},{0,1}};
    canObtainByRotation(src, tgt);

    return 0;
}

