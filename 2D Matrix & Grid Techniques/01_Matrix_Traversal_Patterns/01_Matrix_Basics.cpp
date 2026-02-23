/*
 * ============================================================================
 *                    MATRIX BASICS - ZERO TO GM MASTERY
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Topic   : Matrix Declaration, Initialization, Input/Output & Memory Layout
 * Level   : 0 (Beginner) → 2 (Intermediate)
 * ============================================================================
 *
 *  TABLE OF CONTENTS
 *  ─────────────────
 *  Level 0 : What is a Matrix? (2D Array)
 *  Level 1 : Declaration Methods (C-style, vector, array)
 *  Level 2 : Initialization Patterns (zero, identity, custom)
 *  Level 3 : Input / Output Techniques
 *  Level 4 : Row-Major vs Column-Major Memory Layout
 *  Level 5 : Utility Functions (print, fill, copy)
 *  Level 6 : CP Tips & Tricks for Matrix Problems
 *
 * ============================================================================
 *  KEY CONCEPTS:
 *  - A matrix is a 2D grid of elements with R rows and C columns
 *  - Element at row i, column j is accessed as mat[i][j]
 *  - 0-indexed: rows [0, R-1], columns [0, C-1]
 *  - Total elements = R × C
 *  - Memory: Row-major in C++ (row elements are contiguous)
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

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 0: WHAT IS A MATRIX?
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  A matrix is a rectangular arrangement of numbers in rows and columns.
 *
 *  Example 3×4 matrix:
 *
 *      Col 0  Col 1  Col 2  Col 3
 *  Row 0:  1      2      3      4
 *  Row 1:  5      6      7      8
 *  Row 2:  9     10     11     12
 *
 *  Notation: mat[i][j] = element at row i, column j
 *  mat[1][2] = 7 (row 1, col 2)
 *
 *  Square Matrix: rows == columns (e.g., 3×3)
 *  Rectangular Matrix: rows != columns (e.g., 3×4)
 */

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 1: DECLARATION METHODS
// ─────────────────────────────────────────────────────────────────────────────

// Method 1: C-style 2D Array (Fixed Size - Stack Allocated)
void declarationCStyle() {
    cout << "=== Method 1: C-Style 2D Array ===" << endl;

    constexpr int MAXN = 100;
    int mat[MAXN][MAXN]; // Fixed size, fast but limited

    // Initialize a small portion
    int n = 3, m = 4;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            mat[i][j] = i * m + j + 1;

    // Print
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << mat[i][j] << "\t";
        cout << endl;
    }
    cout << endl;
}

// Method 2: Vector of Vectors (Dynamic - Heap Allocated)
void declarationVector() {
    cout << "=== Method 2: Vector of Vectors ===" << endl;

    int n = 3, m = 4;

    // Way 1: Declare and resize
    vector<vector<int>> mat(n, vector<int>(m, 0)); // n×m matrix filled with 0

    // Way 2: Using assign
    // mat.assign(n, vector<int>(m, 0));

    // Way 3: Push back rows
    // vector<vector<int>> mat;
    // for(int i = 0; i < n; i++) {
    //     vector<int> row(m, 0);
    //     mat.push_back(row);
    // }

    // Fill with values
    int val = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            mat[i][j] = val++;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << mat[i][j] << "\t";
        cout << endl;
    }
    cout << endl;
}

// Method 3: Global Array (For Competitive Programming - Large Sizes)
// CP TIP: Declare large arrays globally to avoid stack overflow!
constexpr int MAXN = 1005;
int globalMat[MAXN][MAXN]; // Stored in BSS segment, zero-initialized

void declarationGlobal() {
    cout << "=== Method 3: Global Array (CP Style) ===" << endl;
    int n = 3, m = 3;
    int val = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            globalMat[i][j] = val++;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << globalMat[i][j] << "\t";
        cout << endl;
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 2: INITIALIZATION PATTERNS
// ─────────────────────────────────────────────────────────────────────────────

// Zero Matrix
void zeroMatrix(int n, int m) {
    cout << "=== Zero Matrix " << n << "x" << m << " ===" << endl;
    vector<vector<int>> mat(n, vector<int>(m, 0));
    for (auto& row : mat) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
    cout << endl;
}

// Identity Matrix (Square only)
void identityMatrix(int n) {
    cout << "=== Identity Matrix " << n << "x" << n << " ===" << endl;
    vector<vector<int>> mat(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        mat[i][i] = 1; // Only diagonal elements = 1

    for (auto& row : mat) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
    cout << endl;
}

// Custom Value Matrix
void customMatrix(int n, int m, int val) {
    cout << "=== Custom Matrix " << n << "x" << m << " filled with " << val << " ===" << endl;
    vector<vector<int>> mat(n, vector<int>(m, val));
    for (auto& row : mat) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 3: INPUT / OUTPUT TECHNIQUES
// ─────────────────────────────────────────────────────────────────────────────

// Standard Input
void inputMatrix() {
    cout << "=== Input Matrix Demo ===" << endl;
    // Simulating input with hardcoded values
    int n = 3, m = 3;
    vector<vector<int>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    /*
     * For actual input in CP:
     *
     * cin >> n >> m;
     * vector<vector<int>> mat(n, vector<int>(m));
     * for(int i = 0; i < n; i++)
     *     for(int j = 0; j < m; j++)
     *         cin >> mat[i][j];
     */

    // Output Method 1: Index-based
    cout << "Index-based output:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << mat[i][j] << " ";
        cout << "\n";
    }

    // Output Method 2: Range-based for loop
    cout << "Range-based output:" << endl;
    for (const auto& row : mat) {
        for (int val : row)
            cout << val << " ";
        cout << "\n";
    }

    // Output Method 3: Formatted with width (neat alignment)
    cout << "Formatted output:" << endl;
    for (const auto& row : mat) {
        for (int val : row)
            cout << setw(4) << val;
        cout << "\n";
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 4: ROW-MAJOR vs COLUMN-MAJOR MEMORY LAYOUT
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  C++ uses ROW-MAJOR order:
 *
 *  Matrix:       Memory Layout (contiguous):
 *  1  2  3       [1][2][3][4][5][6][7][8][9]
 *  4  5  6        ← Row 0 →← Row 1 →← Row 2 →
 *  7  8  9
 *
 *  mat[i][j] = *(base + i * num_cols + j)
 *
 *  WHY THIS MATTERS FOR CP:
 *  - Accessing elements row-by-row is CACHE FRIENDLY (fast)
 *  - Accessing elements column-by-column causes CACHE MISSES (slow)
 *  - For large matrices (N > 1000), row-wise traversal can be 2-5x faster!
 *
 *  1D Mapping:
 *  2D index (i, j) → 1D index: idx = i * M + j
 *  1D index idx → 2D index: i = idx / M, j = idx % M
 */

void memoryLayoutDemo() {
    cout << "=== Memory Layout Demo ===" << endl;
    int mat[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    int n = 3, m = 4;

    // 1D mapping
    cout << "1D representation: ";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cout << mat[i][j] << " ";
    cout << endl;

    // Convert 2D to 1D index
    int row = 1, col = 2; // mat[1][2] = 7
    int idx1D = row * m + col;
    cout << "mat[" << row << "][" << col << "] = " << mat[row][col]
         << ", 1D index = " << idx1D << endl;

    // Convert 1D to 2D index
    int idx = 7; // Should be mat[1][3] = 8
    int r = idx / m, c = idx % m;
    cout << "1D index " << idx << " → mat[" << r << "][" << c << "] = "
         << mat[r][c] << endl;
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 5: UTILITY FUNCTIONS
// ─────────────────────────────────────────────────────────────────────────────

// Print Matrix Utility (reusable)
void printMatrix(const vector<vector<int>>& mat, const string& title = "") {
    if (!title.empty()) cout << "=== " << title << " ===" << endl;
    for (const auto& row : mat) {
        for (int val : row)
            cout << setw(4) << val;
        cout << "\n";
    }
    cout << endl;
}

// Fill Matrix with Sequential Values
vector<vector<int>> fillSequential(int n, int m, int start = 1) {
    vector<vector<int>> mat(n, vector<int>(m));
    int val = start;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            mat[i][j] = val++;
    return mat;
}

// Copy Matrix
vector<vector<int>> copyMatrix(const vector<vector<int>>& mat) {
    return mat; // Deep copy for vectors
}

// Compare Two Matrices
bool areEqual(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i].size() != b[i].size()) return false;
        for (int j = 0; j < (int)a[i].size(); j++)
            if (a[i][j] != b[i][j]) return false;
    }
    return true;
}

// Get Matrix Dimensions
pair<int,int> getDimensions(const vector<vector<int>>& mat) {
    if (mat.empty()) return {0, 0};
    return {mat.size(), mat[0].size()};
}

void utilityDemo() {
    cout << "=== Utility Functions Demo ===" << endl;
    auto mat1 = fillSequential(3, 4);
    printMatrix(mat1, "Sequential 3x4");

    auto mat2 = copyMatrix(mat1);
    cout << "Matrices equal? " << (areEqual(mat1, mat2) ? "YES" : "NO") << endl;

    auto [rows, cols] = getDimensions(mat1);
    cout << "Dimensions: " << rows << " x " << cols << endl;
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 6: CP TIPS & TRICKS
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  ╔════════════════════════════════════════════════════════════════════╗
 *  ║                     CP TIPS FOR MATRIX PROBLEMS                    ║
 *  ╠════════════════════════════════════════════════════════════════════╣
 *  ║ 1. Use global arrays for large matrices to avoid stack overflow    ║
 *  ║ 2. Use memset(mat, 0, sizeof(mat)) to zero-fill C-style arrays     ║
 *  ║ 3. Use memset(mat, -1, sizeof(mat)) for -1 fill (works for int)    ║
 *  ║ 4. Prefer row-wise traversal for cache efficiency                  ║
 *  ║ 5. Use ios_base::sync_with_stdio(false); cin.tie(NULL); for I/O    ║
 *  ║ 6. Use '\n' instead of endl for faster output                      ║
 *  ║ 7. For direction arrays: dx[] = {-1,1,0,0}, dy[] = {0,0,-1,1}      ║
 *  ║ 8. Check bounds: 0 <= i < n && 0 <= j < m                          ║
 *  ║ 9. For 1-indexed: allocate (n+1) × (m+1) and start from 1          ║
 *  ║ 10. Use pair<int,int> or struct for cell coordinates               ║
 *  ╚════════════════════════════════════════════════════════════════════╝
 */

// Direction Arrays - Most Important Pattern in Grid Problems!
void directionArraysDemo() {
    cout << "=== Direction Arrays Demo ===" << endl;

    // 4-directional (Up, Down, Left, Right)
    int dx4[] = {-1, 1, 0, 0};
    int dy4[] = {0, 0, -1, 1};
    string dir4[] = {"Up", "Down", "Left", "Right"};

    // 8-directional (includes diagonals)
    int dx8[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy8[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    string dir8[] = {"UpLeft", "Up", "UpRight", "Left", "Right", "DownLeft", "Down", "DownRight"};

    int n = 5, m = 5;
    int curR = 2, curC = 2; // Center cell

    cout << "From cell (" << curR << "," << curC << "), 4-directional neighbors:" << endl;
    for (int d = 0; d < 4; d++) {
        int nr = curR + dx4[d];
        int nc = curC + dy4[d];
        if (nr >= 0 && nr < n && nc >= 0 && nc < m) { // Bounds check!
            cout << "  " << dir4[d] << " → (" << nr << "," << nc << ")" << endl;
        }
    }

    cout << "\nFrom cell (" << curR << "," << curC << "), 8-directional neighbors:" << endl;
    for (int d = 0; d < 8; d++) {
        int nr = curR + dx8[d];
        int nc = curC + dy8[d];
        if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
            cout << "  " << dir8[d] << " → (" << nr << "," << nc << ")" << endl;
        }
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN - DEMO ALL CONCEPTS
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║     MATRIX BASICS - ZERO TO GM MASTERY       ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
    cout << endl;

    // Level 1: Declaration Methods
    declarationCStyle();
    declarationVector();
    declarationGlobal();

    // Level 2: Initialization Patterns
    zeroMatrix(3, 3);
    identityMatrix(4);
    customMatrix(2, 5, 7);

    // Level 3: Input/Output
    inputMatrix();

    // Level 4: Memory Layout
    memoryLayoutDemo();

    // Level 5: Utilities
    utilityDemo();

    // Level 6: CP Tips
    directionArraysDemo();

    return 0;
}

