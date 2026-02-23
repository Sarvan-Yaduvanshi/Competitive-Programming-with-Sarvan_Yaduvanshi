/*
 * ============================================================================
 *         SNAKE / ZIGZAG ROW TRAVERSAL - ZERO TO GM MASTERY
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Topic   : Snake Traversal, Zigzag Pattern, Boustrophedon Traversal
 * Level   : 0 (Beginner) → 5 (GM)
 * ============================================================================
 *
 *  TABLE OF CONTENTS
 *  ─────────────────
 *  Level 0 : Basic Snake Traversal (Row Zigzag)
 *  Level 1 : Reverse Snake (Start Right→Left)
 *  Level 2 : Column Zigzag (Wave Traversal)
 *  Level 3 : Snake Traversal for Matrix Generation (LC #1260)
 *  Level 4 : Zigzag Level Order (like BFS zigzag in trees)
 *  Level 5 : Convert Snake to Normal & Vice Versa
 *
 * ============================================================================
 *  Time Complexity: O(N × M) for all traversals
 *  Space Complexity: O(1) extra
 *
 *  WHAT IS SNAKE TRAVERSAL?
 *  ─────────────────────────
 *  Also called "Boustrophedon" (Greek: "as the ox turns")
 *  - Even rows: Left → Right
 *  - Odd rows:  Right → Left
 *
 *  Visualization:
 *  → → → → →
 *  ← ← ← ← ←
 *  → → → → →
 *  ← ← ← ← ←
 *
 *  Related Problems:
 *  - LeetCode 1260: Shift 2D Grid
 *  - LeetCode 103: Binary Tree Zigzag Level Order
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
// LEVEL 0: BASIC SNAKE TRAVERSAL (ROW ZIGZAG)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Even rows (0, 2, 4...): Left → Right
 *  Odd rows (1, 3, 5...):  Right → Left
 *
 *  Matrix:         Snake Traversal:
 *  1  2  3  4      1→ 2→ 3→ 4
 *  5  6  7  8      8← 7← 6← 5
 *  9  10 11 12     9→10→11→12
 *  13 14 15 16    16←15←14←13
 *
 *  Result: 1,2,3,4, 8,7,6,5, 9,10,11,12, 16,15,14,13
 */
vector<int> snakeTraversal(const vector<vector<int>>& mat) {
    cout << "=== Basic Snake Traversal ===" << endl;
    int n = mat.size(), m = mat[0].size();
    vector<int> result;

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            // Even row: Left → Right
            for (int j = 0; j < m; j++)
                result.push_back(mat[i][j]);
        } else {
            // Odd row: Right → Left
            for (int j = m - 1; j >= 0; j--)
                result.push_back(mat[i][j]);
        }
    }

    cout << "Order: ";
    for (int x : result) cout << x << " ";
    cout << "\n\n";
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 0B: CLEANER IMPLEMENTATION USING FLAG
// ─────────────────────────────────────────────────────────────────────────────
vector<int> snakeTraversalClean(const vector<vector<int>>& mat) {
    cout << "=== Snake Traversal (Clean Version) ===" << endl;
    int n = mat.size(), m = mat[0].size();
    vector<int> result;
    bool leftToRight = true;

    for (int i = 0; i < n; i++) {
        if (leftToRight) {
            for (int j = 0; j < m; j++)
                result.push_back(mat[i][j]);
        } else {
            for (int j = m - 1; j >= 0; j--)
                result.push_back(mat[i][j]);
        }
        leftToRight = !leftToRight; // Toggle direction
    }

    cout << "Order: ";
    for (int x : result) cout << x << " ";
    cout << "\n\n";
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 1: REVERSE SNAKE (Start Right→Left)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Even rows: Right → Left (reversed start)
 *  Odd rows:  Left → Right
 *
 *  Matrix:         Reverse Snake:
 *  1  2  3  4      4← 3← 2← 1
 *  5  6  7  8      5→ 6→ 7→ 8
 *  9  10 11 12    12←11←10← 9
 *  13 14 15 16    13→14→15→16
 */
vector<int> reverseSnake(const vector<vector<int>>& mat) {
    cout << "=== Reverse Snake Traversal ===" << endl;
    int n = mat.size(), m = mat[0].size();
    vector<int> result;
    bool leftToRight = false; // Start with Right → Left

    for (int i = 0; i < n; i++) {
        if (leftToRight) {
            for (int j = 0; j < m; j++)
                result.push_back(mat[i][j]);
        } else {
            for (int j = m - 1; j >= 0; j--)
                result.push_back(mat[i][j]);
        }
        leftToRight = !leftToRight;
    }

    cout << "Order: ";
    for (int x : result) cout << x << " ";
    cout << "\n\n";
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 2: COLUMN ZIGZAG (WAVE TRAVERSAL)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Even columns: Top → Bottom
 *  Odd columns:  Bottom → Top
 *
 *  Matrix:         Column Zigzag:
 *  1  2  3  4      ↓  ↑  ↓  ↑
 *  5  6  7  8      1  8  3 16
 *  9  10 11 12     5  6 11 12
 *  13 14 15 16     9 10  7  8
 *                  13  2 15  4
 *                  14
 *
 *  Result: 1,5,9,13, 14,10,6,2, 3,7,11,15, 16,12,8,4
 */
vector<int> columnZigzag(const vector<vector<int>>& mat) {
    cout << "=== Column Zigzag (Wave) Traversal ===" << endl;
    int n = mat.size(), m = mat[0].size();
    vector<int> result;

    for (int j = 0; j < m; j++) {
        if (j % 2 == 0) {
            // Even column: Top → Bottom
            for (int i = 0; i < n; i++)
                result.push_back(mat[i][j]);
        } else {
            // Odd column: Bottom → Top
            for (int i = n - 1; i >= 0; i--)
                result.push_back(mat[i][j]);
        }
    }

    cout << "Order: ";
    for (int x : result) cout << x << " ";
    cout << "\n\n";
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 3: GENERATE SNAKE-FILLED MATRIX
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Fill an N×M matrix with values 1 to N*M in snake order.
 *
 *  For N=3, M=4:
 *   1  2  3  4
 *   8  7  6  5
 *   9 10 11 12
 */
vector<vector<int>> generateSnakeMatrix(int n, int m) {
    cout << "=== Generate Snake-Filled Matrix " << n << "x" << m << " ===" << endl;
    vector<vector<int>> mat(n, vector<int>(m));
    int val = 1;

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < m; j++)
                mat[i][j] = val++;
        } else {
            for (int j = m - 1; j >= 0; j--)
                mat[i][j] = val++;
        }
    }

    printMatrix(mat);
    return mat;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 4: SNAKE INDEX MAPPING (Important for CP!)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Given a snake-order index k (0-based), find the (i, j) position.
 *  This is useful for problems like "Snakes and Ladders" (LC #909).
 *
 *  For a matrix filled in snake order:
 *  Index 0 → (0, 0)
 *  Index 1 → (0, 1)
 *  ...
 *  Index M-1 → (0, M-1)
 *  Index M → (1, M-1)  ← reversed!
 *  Index M+1 → (1, M-2)
 */
pair<int,int> snakeIndexToPosition(int idx, int n, int m) {
    int row = idx / m;
    int col = idx % m;
    // If odd row, reverse the column
    if (row % 2 == 1) {
        col = m - 1 - col;
    }
    return {row, col};
}

int positionToSnakeIndex(int i, int j, int n, int m) {
    if (i % 2 == 0) {
        return i * m + j;
    } else {
        return i * m + (m - 1 - j);
    }
}

void snakeIndexDemo() {
    cout << "=== Snake Index Mapping ===" << endl;
    int n = 4, m = 4;

    cout << "Snake index → Position:" << endl;
    for (int idx = 0; idx < n * m; idx++) {
        auto [r, c] = snakeIndexToPosition(idx, n, m);
        cout << "  Index " << setw(2) << idx << " → (" << r << ", " << c << ")" << endl;
    }

    cout << "\nPosition → Snake index:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int idx = positionToSnakeIndex(i, j, n, m);
            cout << setw(4) << idx;
        }
        cout << endl;
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 5: CONVERT BETWEEN NORMAL AND SNAKE ORDER
// ─────────────────────────────────────────────────────────────────────────────

// Convert normal matrix to snake matrix (rearrange values)
vector<vector<int>> normalToSnake(const vector<vector<int>>& mat) {
    cout << "=== Convert Normal → Snake Order ===" << endl;
    int n = mat.size(), m = mat[0].size();
    vector<vector<int>> snake(n, vector<int>(m));

    // Collect all values in row-major order
    vector<int> values;
    for (const auto& row : mat)
        for (int val : row)
            values.push_back(val);

    // Place them in snake order
    int idx = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < m; j++)
                snake[i][j] = values[idx++];
        } else {
            for (int j = m - 1; j >= 0; j--)
                snake[i][j] = values[idx++];
        }
    }

    printMatrix(snake, "Snake Order");
    return snake;
}

// Convert snake matrix back to normal order
vector<vector<int>> snakeToNormal(const vector<vector<int>>& snake) {
    cout << "=== Convert Snake → Normal Order ===" << endl;
    int n = snake.size(), m = snake[0].size();
    vector<vector<int>> normal(n, vector<int>(m));

    // Read values in snake order
    vector<int> values;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < m; j++)
                values.push_back(snake[i][j]);
        } else {
            for (int j = m - 1; j >= 0; j--)
                values.push_back(snake[i][j]);
        }
    }

    // Place them in normal (row-major) order
    int idx = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            normal[i][j] = values[idx++];

    printMatrix(normal, "Normal Order");
    return normal;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 5B: SNAKE TRAVERSAL WITH K SHIFTS (LC #1260 - Shift 2D Grid)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Shift all elements in the grid k times.
 *  In each shift, the last element moves to position (0, 0)
 *  and every other element shifts by one position in snake order.
 *
 *  Approach: Flatten → Rotate → Reshape
 *  Time: O(N*M), Space: O(N*M)
 */
vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
    cout << "=== Shift 2D Grid by " << k << " ===" << endl;
    int n = grid.size(), m = grid[0].size();

    // Flatten
    vector<int> flat;
    for (auto& row : grid)
        for (int val : row)
            flat.push_back(val);

    // Rotate right by k
    k %= (n * m);
    rotate(flat.begin(), flat.end() - k, flat.end());

    // Reshape
    vector<vector<int>> result(n, vector<int>(m));
    for (int i = 0; i < n * m; i++)
        result[i / m][i % m] = flat[i];

    printMatrix(result, "After Shift");
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   SNAKE/ZIGZAG TRAVERSAL - ZERO TO GM MASTERY   ║" << endl;
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
    snakeTraversal(mat);
    snakeTraversalClean(mat);

    // Level 1
    reverseSnake(mat);

    // Level 2
    columnZigzag(mat);

    // Level 3
    generateSnakeMatrix(3, 5);
    generateSnakeMatrix(4, 4);

    // Level 4
    snakeIndexDemo();

    // Level 5
    auto snake = normalToSnake(mat);
    snakeToNormal(snake);

    // LC #1260
    vector<vector<int>> grid = {{1,2,3},{4,5,6},{7,8,9}};
    printMatrix(grid, "Grid before shift");
    shiftGrid(grid, 2);

    return 0;
}

