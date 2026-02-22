/*
 * ============================================================================
 *           SPIRAL MATRIX TRAVERSAL - ZERO TO GM MASTERY
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Topic   : Spiral Traversal, Spiral Generation, Anti-Spiral
 * Level   : 0 (Beginner) → 6 (GM)
 * ============================================================================
 *
 *  TABLE OF CONTENTS
 *  ─────────────────
 *  Level 0 : Understanding Spiral Pattern
 *  Level 1 : Spiral Order Traversal (Clockwise) [LC #54]
 *  Level 2 : Spiral Matrix Generation [LC #59]
 *  Level 3 : Anti-Clockwise Spiral Traversal
 *  Level 4 : Spiral Traversal for Rectangular Matrices
 *  Level 5 : Inside-Out (Reverse) Spiral
 *  Level 6 : Spiral with Variable Starting Point
 *
 * ============================================================================
 *  SPIRAL PATTERN (Clockwise Inward):
 *
 *   →  →  →  →  →
 *   ↑              ↓
 *   ↑  →  →  →    ↓
 *   ↑  ↑     ↓    ↓
 *   ↑  ←  ←  ←    ↓
 *   ←  ←  ←  ←  ←
 *
 *  ALGORITHM (Four-Pointer Boundary Shrinking):
 *  - Maintain: top, bottom, left, right boundaries
 *  - Traverse: right → down → left → up
 *  - After each direction, shrink the corresponding boundary
 *  - Continue until boundaries cross
 *
 *  Related Problems:
 *  - LC #54:  Spiral Matrix
 *  - LC #59:  Spiral Matrix II
 *  - LC #885: Spiral Matrix III
 * ============================================================================
 *  Time Complexity: O(N × M)
 *  Space Complexity: O(1) extra (O(N×M) for output)
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
// LEVEL 0: UNDERSTANDING SPIRAL PATTERN
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  For a 4×5 matrix:
 *   1  2  3  4  5
 *   6  7  8  9 10
 *  11 12 13 14 15
 *  16 17 18 19 20
 *
 *  Spiral Clockwise Order:
 *  1,2,3,4,5, 10,15,20, 19,18,17,16, 11,6, 7,8,9, 14, 13,12
 *
 *  Step-by-step:
 *  Round 1:
 *    Right: 1,2,3,4,5    (top row, left→right)
 *    Down:  10,15,20      (right col, top+1→bottom)
 *    Left:  19,18,17,16   (bottom row, right-1→left)
 *    Up:    11,6           (left col, bottom-1→top+1)
 *  Round 2:
 *    Right: 7,8,9         (inner top row)
 *    Down:  14             (inner right col)
 *    Left:  13,12          (inner bottom row)
 *    Up:    (empty)
 */

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 1: SPIRAL ORDER TRAVERSAL (CLOCKWISE) — LC #54
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Four-Pointer Method:
 *  - top: first unvisited row (starts at 0)
 *  - bottom: last unvisited row (starts at N-1)
 *  - left: first unvisited column (starts at 0)
 *  - right: last unvisited column (starts at M-1)
 *
 *  Time: O(N×M), Space: O(1)
 */
vector<int> spiralOrder(const vector<vector<int>>& mat) {
    cout << "=== Spiral Order Traversal (LC #54) ===" << endl;
    vector<int> result;
    if (mat.empty()) return result;

    int n = mat.size(), m = mat[0].size();
    int top = 0, bottom = n - 1, left = 0, right = m - 1;

    while (top <= bottom && left <= right) {
        // Step 1: Traverse Right → (top row)
        for (int j = left; j <= right; j++)
            result.push_back(mat[top][j]);
        top++; // Shrink top boundary

        // Step 2: Traverse Down ↓ (right column)
        for (int i = top; i <= bottom; i++)
            result.push_back(mat[i][right]);
        right--; // Shrink right boundary

        // Step 3: Traverse Left ← (bottom row)
        if (top <= bottom) { // Check: avoid revisiting if single row left
            for (int j = right; j >= left; j--)
                result.push_back(mat[bottom][j]);
            bottom--; // Shrink bottom boundary
        }

        // Step 4: Traverse Up ↑ (left column)
        if (left <= right) { // Check: avoid revisiting if single column left
            for (int i = bottom; i >= top; i--)
                result.push_back(mat[i][left]);
            left++; // Shrink left boundary
        }
    }

    cout << "Spiral: ";
    for (int x : result) cout << x << " ";
    cout << "\n\n";
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 2: SPIRAL MATRIX GENERATION — LC #59
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Generate an N×N matrix filled with values 1 to N² in spiral order.
 *
 *  For N=4:
 *   1  2  3  4
 *  12 13 14  5
 *  11 16 15  6
 *  10  9  8  7
 *
 *  Time: O(N²), Space: O(N²)
 */
vector<vector<int>> generateSpiralMatrix(int n) {
    cout << "=== Generate Spiral Matrix " << n << "x" << n << " (LC #59) ===" << endl;
    vector<vector<int>> mat(n, vector<int>(n, 0));
    int val = 1;
    int top = 0, bottom = n - 1, left = 0, right = n - 1;

    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; j++)
            mat[top][j] = val++;
        top++;

        for (int i = top; i <= bottom; i++)
            mat[i][right] = val++;
        right--;

        if (top <= bottom) {
            for (int j = right; j >= left; j--)
                mat[bottom][j] = val++;
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--)
                mat[i][left] = val++;
            left++;
        }
    }

    printMatrix(mat);
    return mat;
}

// Generate Rectangular Spiral Matrix N×M
vector<vector<int>> generateSpiralRectangular(int n, int m) {
    cout << "=== Generate Spiral Matrix " << n << "x" << m << " ===" << endl;
    vector<vector<int>> mat(n, vector<int>(m, 0));
    int val = 1;
    int top = 0, bottom = n - 1, left = 0, right = m - 1;

    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; j++) mat[top][j] = val++;
        top++;
        for (int i = top; i <= bottom; i++) mat[i][right] = val++;
        right--;
        if (top <= bottom) {
            for (int j = right; j >= left; j--) mat[bottom][j] = val++;
            bottom--;
        }
        if (left <= right) {
            for (int i = bottom; i >= top; i--) mat[i][left] = val++;
            left++;
        }
    }

    printMatrix(mat);
    return mat;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 3: ANTI-CLOCKWISE SPIRAL TRAVERSAL
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Instead of Right→Down→Left→Up, traverse: Down→Right→Up→Left
 *
 *  For:
 *  1  2  3
 *  4  5  6
 *  7  8  9
 *
 *  Anti-CW Spiral: 1,4,7, 8,9, 6,3, 2, 5
 *
 *  Steps:
 *  Down:  1,4,7   (left column, top→bottom)
 *  Right: 8,9     (bottom row, left+1→right)
 *  Up:    6,3     (right column, bottom-1→top)
 *  Left:  2       (top row, right-1→left+1)
 *  Down:  5       (inner)
 */
vector<int> antiClockwiseSpiral(const vector<vector<int>>& mat) {
    cout << "=== Anti-Clockwise Spiral Traversal ===" << endl;
    vector<int> result;
    if (mat.empty()) return result;

    int n = mat.size(), m = mat[0].size();
    int top = 0, bottom = n - 1, left = 0, right = m - 1;

    while (top <= bottom && left <= right) {
        // Step 1: Down ↓ (left column)
        for (int i = top; i <= bottom; i++)
            result.push_back(mat[i][left]);
        left++;

        // Step 2: Right → (bottom row)
        for (int j = left; j <= right; j++)
            result.push_back(mat[bottom][j]);
        bottom--;

        // Step 3: Up ↑ (right column)
        if (left <= right) {
            for (int i = bottom; i >= top; i--)
                result.push_back(mat[i][right]);
            right--;
        }

        // Step 4: Left ← (top row)
        if (top <= bottom) {
            for (int j = right; j >= left; j--)
                result.push_back(mat[top][j]);
            top++;
        }
    }

    cout << "Anti-CW Spiral: ";
    for (int x : result) cout << x << " ";
    cout << "\n\n";
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 4: SPIRAL PRINT WITH DIRECTION ENUM (Clean Code)
// ─────────────────────────────────────────────────────────────────────────────
vector<int> spiralWithDirection(const vector<vector<int>>& mat) {
    cout << "=== Spiral with Direction Enum ===" << endl;
    enum Direction { RIGHT, DOWN, LEFT, UP };
    vector<int> result;
    if (mat.empty()) return result;

    int n = mat.size(), m = mat[0].size();
    int top = 0, bottom = n - 1, left = 0, right = m - 1;
    Direction dir = RIGHT;

    while (top <= bottom && left <= right) {
        switch (dir) {
            case RIGHT:
                for (int j = left; j <= right; j++)
                    result.push_back(mat[top][j]);
                top++;
                dir = DOWN;
                break;
            case DOWN:
                for (int i = top; i <= bottom; i++)
                    result.push_back(mat[i][right]);
                right--;
                dir = LEFT;
                break;
            case LEFT:
                for (int j = right; j >= left; j--)
                    result.push_back(mat[bottom][j]);
                bottom--;
                dir = UP;
                break;
            case UP:
                for (int i = bottom; i >= top; i--)
                    result.push_back(mat[i][left]);
                left++;
                dir = RIGHT;
                break;
        }
    }

    cout << "Spiral: ";
    for (int x : result) cout << x << " ";
    cout << "\n\n";
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 5: INSIDE-OUT (REVERSE) SPIRAL
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Start from the center and spiral outward.
 *  Simply reverse the normal spiral order!
 *
 *  Normal spiral: 1,2,3,4,5,10,15,20,19,18,17,16,11,6,7,8,9,14,13,12
 *  Reverse spiral: 12,13,14,9,8,7,6,11,16,17,18,19,20,15,10,5,4,3,2,1
 */
vector<int> insideOutSpiral(const vector<vector<int>>& mat) {
    cout << "=== Inside-Out Spiral ===" << endl;
    auto result = spiralOrder(mat);
    reverse(result.begin(), result.end());

    cout << "Inside-Out: ";
    for (int x : result) cout << x << " ";
    cout << "\n\n";
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 6: SPIRAL MATRIX III — LC #885
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Start from position (rStart, cStart) and walk in clockwise spiral.
 *  Return all cells of the R×C grid in the order visited.
 *  (Cells outside the grid are skipped but the spiral continues.)
 *
 *  Pattern: Go 1 step right, 1 step down, 2 steps left, 2 steps up,
 *           3 steps right, 3 steps down, 4 steps left, 4 steps up, ...
 *  Steps increase by 1 after every 2 direction changes.
 *
 *  Time: O(max(R,C)²), Space: O(R×C)
 */
vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
    cout << "=== Spiral Matrix III (LC #885) ===" << endl;
    cout << "Grid: " << rows << "x" << cols << ", Start: (" << rStart << "," << cStart << ")" << endl;

    vector<vector<int>> result;
    int dr[] = {0, 1, 0, -1}; // Right, Down, Left, Up
    int dc[] = {1, 0, -1, 0};
    int total = rows * cols;

    int r = rStart, c = cStart;
    int d = 0; // Direction index
    int steps = 1;

    result.push_back({r, c});

    while ((int)result.size() < total) {
        for (int rep = 0; rep < 2; rep++) { // Two directions per step-size
            for (int s = 0; s < steps; s++) {
                r += dr[d];
                c += dc[d];
                if (r >= 0 && r < rows && c >= 0 && c < cols) {
                    result.push_back({r, c});
                }
            }
            d = (d + 1) % 4;
        }
        steps++;
    }

    cout << "Visit order (first 20): ";
    for (int i = 0; i < min(20, (int)result.size()); i++)
        cout << "(" << result[i][0] << "," << result[i][1] << ") ";
    cout << "\n\n";
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 6B: SPIRAL LAYER/RING NUMBER
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Given position (i, j) in N×N matrix, what spiral ring/layer does it belong to?
 *
 *  Layer = min(i, j, N-1-i, N-1-j)
 *
 *  Layer 0: outermost ring
 *  Layer 1: next inner ring
 *  ...
 *
 *  Example for 5×5:
 *  0 0 0 0 0
 *  0 1 1 1 0
 *  0 1 2 1 0
 *  0 1 1 1 0
 *  0 0 0 0 0
 */
void spiralLayerDemo(int n) {
    cout << "=== Spiral Layer Numbers for " << n << "x" << n << " ===" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int layer = min({i, j, n-1-i, n-1-j});
            cout << setw(3) << layer;
        }
        cout << "\n";
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   SPIRAL MATRIX TRAVERSAL - ZERO TO GM MASTERY  ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << endl;

    // Level 1: Spiral Order (LC #54)
    vector<vector<int>> mat1 = {
        {1,  2,  3,  4,  5},
        {6,  7,  8,  9,  10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20}
    };
    printMatrix(mat1, "Original 4x5 Matrix");
    spiralOrder(mat1);

    // Level 2: Generate Spiral Matrix (LC #59)
    generateSpiralMatrix(4);
    generateSpiralMatrix(5);
    generateSpiralRectangular(3, 5);

    // Level 3: Anti-Clockwise Spiral
    vector<vector<int>> mat3 = {{1,2,3},{4,5,6},{7,8,9}};
    printMatrix(mat3, "3x3 Matrix");
    antiClockwiseSpiral(mat3);

    // Level 4: Direction Enum
    spiralWithDirection(mat1);

    // Level 5: Inside-Out Spiral
    vector<vector<int>> mat5 = {{1,2,3},{4,5,6},{7,8,9}};
    insideOutSpiral(mat5);

    // Level 6: Spiral Matrix III (LC #885)
    spiralMatrixIII(5, 6, 1, 4);

    // Level 6B: Spiral Layers
    spiralLayerDemo(5);
    spiralLayerDemo(6);

    // Edge Cases
    cout << "=== Edge Cases ===" << endl;
    vector<vector<int>> single = {{42}};
    spiralOrder(single);

    vector<vector<int>> singleRow = {{1, 2, 3, 4, 5}};
    spiralOrder(singleRow);

    vector<vector<int>> singleCol = {{1},{2},{3},{4}};
    spiralOrder(singleCol);

    return 0;
}

