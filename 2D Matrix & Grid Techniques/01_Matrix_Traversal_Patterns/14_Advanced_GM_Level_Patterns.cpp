/*
 * ============================================================================
 *      ADVANCED GM-LEVEL MATRIX PATTERNS - ZERO TO GM MASTERY
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Topic   : Saddle Point, Magic Square, Toeplitz, Sparse, and more
 * Level   : 5 (Advanced) → 9 (Grandmaster)
 * ============================================================================
 *
 *  TABLE OF CONTENTS
 *  ─────────────────
 *  Level 5 : Saddle Point in Matrix
 *  Level 5 : Toeplitz Matrix Check [LC #766]
 *  Level 6 : Magic Square Validation
 *  Level 6 : Sparse Matrix Representation (COO, CSR)
 *  Level 7 : Matrix Multiplication O(N³)
 *  Level 7 : Set Matrix Zeroes [LC #73]
 *  Level 8 : Game of Life [LC #289]
 *  Level 8 : Lucky Numbers in a Matrix [LC #1380]
 *  Level 9 : GM Tips & Tricks Cheat Sheet
 *
 * ============================================================================
 *  These are advanced patterns frequently tested in:
 *  - Codeforces (Div 1-2)
 *  - Google/Meta/Amazon interviews
 *  - ICPC regionals
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
// LEVEL 5: SADDLE POINT IN MATRIX
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  A saddle point is an element that is:
 *  - Minimum in its row AND
 *  - Maximum in its column
 *
 *  Not every matrix has a saddle point.
 *  A matrix can have at most one saddle point VALUE (but could appear
 *  at multiple positions with the same value).
 *
 *  Algorithm:
 *  1. For each row, find the minimum element
 *  2. Check if that element is the maximum of its column
 *
 *  Time: O(N×M), Space: O(1)
 */
void findSaddlePoint(const vector<vector<int>>& mat) {
    cout << "=== Saddle Point ===" << endl;
    int n = mat.size(), m = mat[0].size();
    bool found = false;

    for (int i = 0; i < n; i++) {
        // Find minimum in row i
        int minVal = *min_element(mat[i].begin(), mat[i].end());
        int minCol = min_element(mat[i].begin(), mat[i].end()) - mat[i].begin();

        // Check if it's maximum in its column
        bool isMaxInCol = true;
        for (int k = 0; k < n; k++) {
            if (mat[k][minCol] > minVal) {
                isMaxInCol = false;
                break;
            }
        }

        if (isMaxInCol) {
            cout << "Saddle point at (" << i << ", " << minCol << ") = " << minVal << endl;
            found = true;
        }
    }

    if (!found) cout << "No saddle point exists" << endl;
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 5B: TOEPLITZ MATRIX CHECK — LC #766
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  A Toeplitz matrix has the same value on every diagonal (top-left to bottom-right).
 *  In other words: mat[i][j] == mat[i+1][j+1] for all valid i, j.
 *
 *  Example of Toeplitz matrix:
 *  1  2  3  4
 *  5  1  2  3
 *  9  5  1  2
 *
 *  Check: Every element equals its top-left neighbor.
 *
 *  LC #766: Toeplitz Matrix
 *  Time: O(N×M), Space: O(1)
 */
bool isToeplitz(const vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
            if (mat[i][j] != mat[i-1][j-1])
                return false;
    return true;
}

void toeplitzDemo() {
    cout << "=== Toeplitz Matrix Check (LC #766) ===" << endl;

    vector<vector<int>> t1 = {{1,2,3,4},{5,1,2,3},{9,5,1,2}};
    printMatrix(t1, "Matrix 1");
    cout << "Is Toeplitz? " << (isToeplitz(t1) ? "YES ✓" : "NO ✗") << endl << endl;

    vector<vector<int>> t2 = {{1,2},{2,2}};
    printMatrix(t2, "Matrix 2");
    cout << "Is Toeplitz? " << (isToeplitz(t2) ? "YES ✓" : "NO ✗") << endl << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 6: MAGIC SQUARE VALIDATION
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  A Magic Square is N×N where:
 *  - All numbers 1 to N² appear exactly once
 *  - All row sums, column sums, and both diagonal sums are equal
 *  - Magic constant = N × (N² + 1) / 2
 *
 *  For N=3: Magic constant = 3 × 10 / 2 = 15
 *
 *  Example:
 *  2  7  6
 *  9  5  1
 *  4  3  8
 *
 *  All rows: 15, All cols: 15, Both diags: 15 ✓
 *
 *  Time: O(N²), Space: O(N²) for number tracking
 */
bool isMagicSquare(const vector<vector<int>>& mat) {
    int n = mat.size();
    if (n == 0) return false;
    for (auto& row : mat)
        if ((int)row.size() != n) return false;

    int magicConstant = n * (n * n + 1) / 2;

    // Check all numbers 1 to N² appear exactly once
    vector<bool> seen(n * n + 1, false);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val = mat[i][j];
            if (val < 1 || val > n * n || seen[val])
                return false;
            seen[val] = true;
        }
    }

    // Check row sums
    for (int i = 0; i < n; i++) {
        int sum = accumulate(mat[i].begin(), mat[i].end(), 0);
        if (sum != magicConstant) return false;
    }

    // Check column sums
    for (int j = 0; j < n; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) sum += mat[i][j];
        if (sum != magicConstant) return false;
    }

    // Check primary diagonal
    int diagSum = 0;
    for (int i = 0; i < n; i++) diagSum += mat[i][i];
    if (diagSum != magicConstant) return false;

    // Check secondary diagonal
    int antiDiagSum = 0;
    for (int i = 0; i < n; i++) antiDiagSum += mat[i][n - 1 - i];
    if (antiDiagSum != magicConstant) return false;

    return true;
}

void magicSquareDemo() {
    cout << "=== Magic Square Validation ===" << endl;

    vector<vector<int>> magic = {{2,7,6},{9,5,1},{4,3,8}};
    printMatrix(magic, "Matrix 1");
    cout << "Is Magic Square? " << (isMagicSquare(magic) ? "YES ✓" : "NO ✗") << endl;
    cout << "Magic constant = " << 3 * (9 + 1) / 2 << endl << endl;

    vector<vector<int>> notMagic = {{1,2,3},{4,5,6},{7,8,9}};
    printMatrix(notMagic, "Matrix 2");
    cout << "Is Magic Square? " << (isMagicSquare(notMagic) ? "YES ✓" : "NO ✗") << endl << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 6B: SPARSE MATRIX REPRESENTATION
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  A sparse matrix has mostly zero elements.
 *  Storing all N×M elements wastes memory.
 *
 *  Two common representations:
 *
 *  1. COO (Coordinate) Format:
 *     Store triplets (row, col, value) for non-zero elements
 *
 *  2. CSR (Compressed Sparse Row) Format:
 *     - values[]: non-zero values
 *     - colIdx[]: column index for each value
 *     - rowPtr[]: start index in values[] for each row
 *
 *  Space: O(nnz) where nnz = number of non-zero elements
 */
struct SparseMatrixCOO {
    int rows, cols;
    vector<tuple<int,int,int>> entries; // (row, col, value)

    SparseMatrixCOO(const vector<vector<int>>& mat) {
        rows = mat.size();
        cols = mat[0].size();
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (mat[i][j] != 0)
                    entries.push_back({i, j, mat[i][j]});
    }

    void print() {
        cout << "COO Format (" << entries.size() << " non-zeros):" << endl;
        for (auto& [r, c, v] : entries)
            cout << "  (" << r << ", " << c << ") = " << v << endl;
    }

    // Convert back to dense matrix
    vector<vector<int>> toDense() {
        vector<vector<int>> mat(rows, vector<int>(cols, 0));
        for (auto& [r, c, v] : entries)
            mat[r][c] = v;
        return mat;
    }
};

void sparseMatrixDemo() {
    cout << "=== Sparse Matrix Representation ===" << endl;
    vector<vector<int>> mat = {
        {0, 0, 3, 0, 4},
        {0, 0, 5, 7, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 6, 0, 0}
    };
    printMatrix(mat, "Sparse Matrix (many zeros)");

    int total = mat.size() * mat[0].size();
    int nonzero = 0;
    for (auto& row : mat)
        for (int v : row)
            if (v != 0) nonzero++;

    cout << "Total elements: " << total << endl;
    cout << "Non-zero elements: " << nonzero << endl;
    cout << "Sparsity: " << (1.0 - (double)nonzero / total) * 100 << "%" << endl;
    cout << "Memory saving: " << total << " → " << nonzero * 3 << " (COO)" << endl << endl;

    SparseMatrixCOO sparse(mat);
    sparse.print();
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 7: MATRIX MULTIPLICATION O(N³)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  A (N×K) × B (K×M) = C (N×M)
 *  C[i][j] = Σ A[i][k] × B[k][j]  for k = 0 to K-1
 *
 *  Time: O(N×M×K), Space: O(N×M)
 *
 *  CP Tip: Loop order matters for cache!
 *  Best order: i, k, j (access B row-by-row)
 */
vector<vector<long long>> matMul(const vector<vector<int>>& A,
                                  const vector<vector<int>>& B) {
    int n = A.size(), k = A[0].size(), m = B[0].size();
    vector<vector<long long>> C(n, vector<long long>(m, 0));

    // Cache-friendly order: i, k, j
    for (int i = 0; i < n; i++)
        for (int kk = 0; kk < k; kk++)
            for (int j = 0; j < m; j++)
                C[i][j] += (long long)A[i][kk] * B[kk][j];

    return C;
}

void matMulDemo() {
    cout << "=== Matrix Multiplication ===" << endl;
    vector<vector<int>> A = {{1,2},{3,4},{5,6}};
    vector<vector<int>> B = {{7,8,9},{10,11,12}};

    printMatrix(A, "A (3×2)");
    printMatrix(B, "B (2×3)");

    auto C = matMul(A, B);
    cout << "C = A × B (3×3):" << endl;
    for (auto& row : C) {
        for (long long val : row) cout << setw(5) << val;
        cout << endl;
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 7B: SET MATRIX ZEROES — LC #73
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  If an element is 0, set its entire row and column to 0.
 *  Do it IN-PLACE with O(1) extra space.
 *
 *  Approach: Use first row and first column as markers.
 *
 *  Time: O(N×M), Space: O(1)
 */
void setZeroes(vector<vector<int>>& mat) {
    cout << "=== Set Matrix Zeroes (LC #73) ===" << endl;
    int n = mat.size(), m = mat[0].size();
    printMatrix(mat, "Before");

    bool firstRowZero = false, firstColZero = false;

    // Check if first row has zero
    for (int j = 0; j < m; j++)
        if (mat[0][j] == 0) firstRowZero = true;

    // Check if first column has zero
    for (int i = 0; i < n; i++)
        if (mat[i][0] == 0) firstColZero = true;

    // Use first row/col as markers
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
            if (mat[i][j] == 0) {
                mat[i][0] = 0; // Mark row
                mat[0][j] = 0; // Mark column
            }

    // Zero out marked rows/cols (skip first row/col)
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
            if (mat[i][0] == 0 || mat[0][j] == 0)
                mat[i][j] = 0;

    // Handle first row
    if (firstRowZero)
        for (int j = 0; j < m; j++)
            mat[0][j] = 0;

    // Handle first column
    if (firstColZero)
        for (int i = 0; i < n; i++)
            mat[i][0] = 0;

    printMatrix(mat, "After");
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 8: GAME OF LIFE — LC #289
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Cellular automaton rules (8-directional neighbors):
 *  - Live cell with < 2 live neighbors → dies (underpopulation)
 *  - Live cell with 2-3 live neighbors → lives
 *  - Live cell with > 3 live neighbors → dies (overpopulation)
 *  - Dead cell with exactly 3 live neighbors → becomes alive
 *
 *  In-place solution: Encode transitions in unused bits.
 *  State encoding: Use 2 bits [next_state | current_state]
 *  - 0 (00): dead → dead
 *  - 1 (01): live → dead  (will die)
 *  - 2 (10): dead → live  (will be born)
 *  - 3 (11): live → live  (will survive)
 *
 *  Time: O(N×M), Space: O(1)
 */
void gameOfLife(vector<vector<int>>& board) {
    cout << "=== Game of Life (LC #289) ===" << endl;
    int n = board.size(), m = board[0].size();
    printMatrix(board, "Before");

    int dx[] = {-1,-1,-1,0,0,1,1,1};
    int dy[] = {-1,0,1,-1,1,-1,0,1};

    // Step 1: Encode transitions
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int liveNeighbors = 0;
            for (int d = 0; d < 8; d++) {
                int ni = i + dx[d], nj = j + dy[d];
                if (ni >= 0 && ni < n && nj >= 0 && nj < m)
                    liveNeighbors += (board[ni][nj] & 1); // Current state is bit 0
            }

            if (board[i][j] & 1) { // Currently alive
                if (liveNeighbors == 2 || liveNeighbors == 3)
                    board[i][j] = 3; // 11: live → live
                // else stays 1 (01: live → dead)
            } else { // Currently dead
                if (liveNeighbors == 3)
                    board[i][j] = 2; // 10: dead → live
            }
        }
    }

    // Step 2: Extract next state (bit 1)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            board[i][j] >>= 1;

    printMatrix(board, "After one generation");
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 8B: LUCKY NUMBERS IN MATRIX — LC #1380
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  A lucky number is an element that is:
 *  - Minimum in its row AND
 *  - Maximum in its column
 *
 *  (Same as saddle point!)
 *  Time: O(N×M), Space: O(N+M)
 */
vector<int> luckyNumbers(const vector<vector<int>>& mat) {
    cout << "=== Lucky Numbers (LC #1380) ===" << endl;
    int n = mat.size(), m = mat[0].size();
    printMatrix(mat, "Matrix");

    // Find minimum in each row
    vector<int> rowMin(n, INT_MAX);
    for (int i = 0; i < n; i++)
        rowMin[i] = *min_element(mat[i].begin(), mat[i].end());

    // Find maximum in each column
    vector<int> colMax(m, INT_MIN);
    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++)
            colMax[j] = max(colMax[j], mat[i][j]);

    vector<int> result;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mat[i][j] == rowMin[i] && mat[i][j] == colMax[j])
                result.push_back(mat[i][j]);

    cout << "Lucky numbers: ";
    for (int x : result) cout << x << " ";
    if (result.empty()) cout << "(none)";
    cout << "\n\n";
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 9: GM CHEAT SHEET — MATRIX TRAVERSAL PATTERNS
// ─────────────────────────────────────────────────────────────────────────────
void gmCheatSheet() {
    cout << R"(
╔════════════════════════════════════════════════════════════════════════════╗
║              GM CHEAT SHEET — MATRIX TRAVERSAL PATTERNS                 ║
╠════════════════════════════════════════════════════════════════════════════╣
║                                                                          ║
║  TRAVERSAL TYPES & COMPLEXITIES:                                         ║
║  ────────────────────────────────                                        ║
║  Row-wise / Col-wise      → O(N×M)        Basic                        ║
║  Boundary                 → O(N+M)        Linear                       ║
║  Snake/Zigzag             → O(N×M)        Use direction flag            ║
║  Diagonal (all)           → O(N×M)        Key: i±j                     ║
║  Spiral (inward)          → O(N×M)        4 pointers: top,bot,left,right║
║  Ring/Layer               → O(N×M)        min(i,j,N-1-i,M-1-j)        ║
║  DFS/BFS on grid          → O(N×M)        Direction arrays + visited    ║
║  2D Prefix Sum query      → O(1)          Build O(N×M)                  ║
║                                                                          ║
║  ROTATION FORMULAS (N×N):                                                ║
║  ────────────────────────                                                ║
║  90° CW:   Transpose + Reverse rows      (i,j)→(j,N-1-i)              ║
║  90° CCW:  Transpose + Reverse columns    (i,j)→(N-1-j,i)             ║
║  180°:     Reverse rows + Reverse cols    (i,j)→(N-1-i,N-1-j)         ║
║                                                                          ║
║  DIAGONAL PROPERTIES:                                                    ║
║  ────────────────────                                                    ║
║  Same primary diagonal:    i - j = constant                              ║
║  Same anti-diagonal:       i + j = constant                              ║
║  On ANY diagonal:          |r1-r2| == |c1-c2|                           ║
║  Total diagonals:          N + M - 1                                    ║
║                                                                          ║
║  GRID DFS/BFS PATTERNS:                                                  ║
║  ───────────────────────                                                 ║
║  4-dir: dx={-1,1,0,0}, dy={0,0,-1,1}                                   ║
║  8-dir: All 8 neighbors (include diagonals)                              ║
║  Bounds: 0≤i<N && 0≤j<M                                                ║
║  Mark visited: visited[][] OR modify grid in-place                       ║
║  Multi-source BFS: Start with all sources in queue                       ║
║                                                                          ║
║  2D PREFIX SUM:                                                          ║
║  ──────────────                                                          ║
║  Build: pre[i][j] = mat + pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1]   ║
║  Query: sum = pre[r2][c2] - pre[r1-1][c2] - pre[r2][c1-1]             ║
║              + pre[r1-1][c1-1]                                           ║
║                                                                          ║
║  SPECIAL MATRIX TYPES:                                                   ║
║  ────────────────────                                                    ║
║  Symmetric:       A[i][j] = A[j][i]                                    ║
║  Skew-Symmetric:  A[i][j] = -A[j][i], diag = 0                        ║
║  Toeplitz:        A[i][j] = A[i-1][j-1]                                ║
║  Identity:        A[i][j] = (i==j ? 1 : 0)                             ║
║  Magic Square:    All row/col/diag sums = N×(N²+1)/2                   ║
║                                                                          ║
║  CP SPEED TIPS:                                                          ║
║  ──────────────                                                          ║
║  1. Global arrays for N > 1000 (avoid stack overflow)                    ║
║  2. scanf/printf faster than cin/cout for massive I/O                    ║
║  3. Row-wise traversal for cache (2-5x faster for N > 2000)            ║
║  4. memset(arr, 0, sizeof(arr)) for C-style arrays                      ║
║  5. Bit tricks: encode two states in one cell (Game of Life)            ║
║  6. 1D mapping: (i,j) ↔ i*M+j for sets/maps                           ║
║                                                                          ║
╚════════════════════════════════════════════════════════════════════════════╝
)" << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║  ADVANCED GM-LEVEL PATTERNS - ZERO TO GM MASTERY║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << endl;

    // Level 5: Saddle Point
    vector<vector<int>> mat1 = {{1,2,3},{4,5,6},{7,8,9}};
    printMatrix(mat1, "Matrix for Saddle Point");
    findSaddlePoint(mat1);

    vector<vector<int>> mat1b = {{1,2,3},{4,5,6},{7,8,0}};
    printMatrix(mat1b, "Matrix 2 for Saddle Point");
    findSaddlePoint(mat1b);

    // Level 5B: Toeplitz
    toeplitzDemo();

    // Level 6: Magic Square
    magicSquareDemo();

    // Level 6B: Sparse Matrix
    sparseMatrixDemo();

    // Level 7: Matrix Multiplication
    matMulDemo();

    // Level 7B: Set Matrix Zeroes (LC #73)
    vector<vector<int>> mat7 = {{1,1,1},{1,0,1},{1,1,1}};
    setZeroes(mat7);

    // Level 8: Game of Life (LC #289)
    vector<vector<int>> board = {{0,1,0},{0,0,1},{1,1,1},{0,0,0}};
    gameOfLife(board);

    // Level 8B: Lucky Numbers (LC #1380)
    vector<vector<int>> mat8 = {{3,7,8},{9,11,13},{15,16,17}};
    luckyNumbers(mat8);

    vector<vector<int>> mat8b = {{1,10,4,2},{9,3,8,7},{15,16,17,12}};
    luckyNumbers(mat8b);

    // Level 9: GM Cheat Sheet
    gmCheatSheet();

    return 0;
}

