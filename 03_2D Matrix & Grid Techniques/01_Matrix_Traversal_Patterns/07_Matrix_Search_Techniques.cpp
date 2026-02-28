/*
 * ============================================================================
 *           MATRIX SEARCH TECHNIQUES - ZERO TO GM MASTERY
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Topic   : Searching in 2D Matrices (Linear, Staircase, Binary Search)
 *           + Matrix Sorting Techniques + Median of Row-Sorted Matrix
 * Level   : 0 (Beginner) → 10 (GM)
 * ============================================================================
 *
 *  TABLE OF CONTENTS
 *  ─────────────────
 *  Level 0   : Brute Force Linear Search O(N×M)
 *  Level 0.5 : Sort Entire Matrix (Flatten+Sort+Reshape) O(NM×log(NM))
 *  Level 0.6 : Sort Each Row Independently O(N×(M×logM))
 *  Level 0.7 : Sort Each Column Independently O(M×(N×logN))
 *  Level 1   : Binary Search on Each Row O(N×logM)
 *  Level 2   : Binary Search on Fully Sorted Matrix O(log(N×M)) [LC #74]
 *  Level 3   : Staircase Search in Row+Col Sorted Matrix O(N+M) [LC #240]
 *  Level 4   : Find Row with Maximum 1s in Binary Matrix O(N+M)
 *  Level 5   : Find Peak Element in 2D Matrix O(N×logM) [LC #1901]
 *  Level 6   : Kth Smallest in Sorted Matrix O(N×log(max-min)) [LC #378]
 *  Level 7   : Count Negative Numbers in Sorted Matrix O(N+M) [LC #1351]
 *  Level 8   : Median of Row-Sorted Matrix O(N×logM×log(max-min)) [GFG]
 *  Level 9   : Sort Matrix Diagonally O(min(N,M)²×log(min(N,M))) [LC #1329]
 *  Level 10  : Sort Matrix by Row+Col (Make Row & Col sorted) O(N×M×log(NM))
 *
 * ============================================================================
 *  SEARCH STRATEGY DECISION TABLE:
 *  ┌────────────────────────────────┬────────────────────┬──────────────────────┐
 *  │ Matrix Type                    │ Best Algorithm     │ Complexity           │
 *  ├────────────────────────────────┼────────────────────┼──────────────────────┤
 *  │ Unsorted                       │ Linear Search      │ O(N×M)               │
 *  │ Each row sorted                │ Binary per row     │ O(N×logM)            │
 *  │ Fully sorted (row-major)       │ Binary on flat     │ O(log(NM))           │
 *  │ Row+Col sorted                 │ Staircase          │ O(N+M)               │
 *  │ Binary (0s then 1s per row)    │ Binary+Staircase   │ O(N+M)               │
 *  └────────────────────────────────┴────────────────────┴──────────────────────┘
 *
 *  SORTING STRATEGY DECISION TABLE:
 *  ┌────────────────────────────────┬────────────────────┬──────────────────────┐
 *  │ Task                           │ Approach           │ Complexity           │
 *  ├────────────────────────────────┼────────────────────┼──────────────────────┤
 *  │ Sort entire matrix             │ Flatten+Sort+Put   │ O(NM×log(NM))        │
 *  │ Sort each row only             │ Sort each row      │ O(N×(M×logM))        │
 *  │ Sort each column only          │ Extract+Sort+Put   │ O(M×(N×logN))        │
 *  │ Sort diagonals                 │ Extract diag+Sort  │ O(min(N,M)²×log)     │
 *  │ Make row+col sorted            │ Flatten+Sort+Put   │ O(NM×log(NM))        │
 *  │ Find median (row-sorted)       │ BS on value range  │ O(N×logM×log(range)) │
 *  └────────────────────────────────┴────────────────────┴──────────────────────┘
 *
 *  Related Problems:
 *  - LC #74:   Search a 2D Matrix
 *  - LC #240:  Search a 2D Matrix II
 *  - LC #378:  Kth Smallest Element in a Sorted Matrix
 *  - LC #1351: Count Negative Numbers in a Sorted Matrix
 *  - LC #1901: Find a Peak Element II
 *  - LC #1329: Sort the Matrix Diagonally
 *  - GFG:      Median in a Row-Wise Sorted Matrix
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
#include <algorithm>
#include <climits>

using namespace std;

void printMatrix(const vector<vector<int>>& mat, const string& title = "") {
    if (!title.empty()) cout << "--- " << title << " ---" << endl;
    for (const auto& row : mat) {
        for (int val : row) cout << setw(5) << val;
        cout << "\n";
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 0: BRUTE FORCE LINEAR SEARCH  O(N × M)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Simply scan every element.
 *  Works on ANY matrix (sorted or unsorted).
 *  Time: O(N×M), Space: O(1)
 */
pair<int,int> linearSearch(const vector<vector<int>>& mat, int target) {
    int n = mat.size(), m = mat[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mat[i][j] == target)
                return {i, j};
    return {-1, -1}; // Not found
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 0.5: SORT ENTIRE MATRIX AND THEN BINARY SEARCH  O(N×M log(N×M))
// ─────────────────────────────────────────────────────────────────────────────
/*
 * The Concept: Flatten, Sort, Reshape
 * To sort the entire matrix, you don't need a complex 2D sorting algorithm. You simply transform the problem into a 1D problem.
 *     1. Flatten: Copy all elements from the matrix into a single 1D array (or vector).
 *     2. Sort: Sort that 1D array using a standard algorithm (like QuickSort or IntroSort).
 *     3. Reshape: Fill the original matrix back up with the values from the sorted 1D array.
 *  Time = O(m * n) = O(N)
 */
void sortEntireMatrix(vector<vector<int>>& matrix) {
    // Edge case: Empty matrix
    if (matrix.empty()) return;

    int rows = matrix.size();
    int cols = matrix[0].size();

    // 1. FLATTEN
    // We create a temporary 1D vector to hold all elements.
    vector<int> temp;

    // Reserve memory to prevent reallocations (Optimization)
    temp.reserve(rows * cols);

    for (const auto& row : matrix) {
        for (int val : row) {
            temp.push_back(val);
        }
    }

    // 2. SORT
    // std::sort uses IntroSort (Mix of QuickSort, HeapSort, InsertionSort)
    sort(temp.begin(), temp.end());

    // 3. RESHAPE (Put back)
    // We iterate through the sorted 'temp' array and fill the matrix.
    int k = 0; // Pointer for the temp array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = temp[k++];
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 0.6: SORT EACH ROW INDEPENDENTLY  O(N × (M × log M))
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  WHY THIS MATTERS:
 *  ─────────────────
 *  Sorting each row independently is a CRITICAL preprocessing step used in:
 *  1. "Median of Row-Wise Sorted Matrix" (GFG Classic) — needs each row sorted
 *     so we can binary-search within each row to count elements ≤ mid.
 *  2. Binary search per row (Level 1) — only works if each row is sorted.
 *  3. Staircase search (Level 3) — requires both rows AND columns sorted.
 *     Row sorting is the first step if matrix is unsorted.
 *  4. Many greedy/DP problems on matrices assume row-sorted input.
 *
 *  THE CONCEPT:
 *  ────────────
 *  Treat each row as an independent 1D array and sort it.
 *  No relationship between rows is maintained or required.
 *
 *  ALGORITHM:
 *  ──────────
 *  For each row i from 0 to N-1:
 *      sort(matrix[i].begin(), matrix[i].end())
 *
 *  TIME COMPLEXITY ANALYSIS:
 *  ─────────────────────────
 *  - Each row has M elements → sorting one row = O(M × log M)
 *  - We have N rows → Total = O(N × M × log M)
 *  - Space: O(1) extra (in-place sort, ignoring sort's internal stack)
 *
 *  EXAMPLE:
 *  ────────
 *  Before:                    After:
 *   9  3  7  1               1  3  7  9
 *   5  2  8  4               2  4  5  8
 *   6  1  3  2               1  2  3  6
 *
 *  Notice: Each row is sorted, but columns are NOT sorted.
 *          Row 0 col 0 = 1, Row 1 col 0 = 2, Row 2 col 0 = 1 → NOT column-sorted!
 *
 *  INTERVIEW TIP:
 *  ──────────────
 *  If asked "Can you make binary search work on an unsorted matrix?"
 *  → Sort each row first: O(N × M × log M) preprocessing
 *  → Then binary search per row: O(N × log M) per query
 *  → Total for Q queries: O(N × M × log M + Q × N × log M)
 */
void sortEachRow(vector<vector<int>>& matrix) {
    if (matrix.empty()) return;
    int rows = matrix.size();

    for (int i = 0; i < rows; i++) {
        // Each row is a vector<int>, sort it independently
        sort(matrix[i].begin(), matrix[i].end());
    }
}

// Variant: Sort each row in DESCENDING order (useful for some greedy problems)
void sortEachRowDescending(vector<vector<int>>& matrix) {
    if (matrix.empty()) return;
    for (auto& row : matrix) {
        sort(row.begin(), row.end(), greater<int>());
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 0.7: SORT EACH COLUMN INDEPENDENTLY  O(M × (N × log N))
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  WHY THIS MATTERS:
 *  ─────────────────
 *  Column sorting is used in:
 *  1. Making a matrix "column-sorted" as prerequisite for certain search algos.
 *  2. The famous "Sort Matrix by Column" problem.
 *  3. Combined with row sorting → makes matrix fully row+col sorted for
 *     staircase search (only when values allow it, like in Young Tableau).
 *  4. Shearsort algorithm uses alternating row-sort and column-sort.
 *
 *  THE CONCEPT:
 *  ────────────
 *  Unlike rows (which are contiguous in memory as vector<int>),
 *  columns are NOT stored contiguously. So we must:
 *    1. EXTRACT column j into a temporary 1D vector
 *    2. SORT that temporary vector
 *    3. PUT BACK the sorted values into column j of the matrix
 *
 *  This is a classic example of the "Extract → Process → Put Back" pattern
 *  that appears frequently in matrix problems.
 *
 *  ALGORITHM:
 *  ──────────
 *  For each column j from 0 to M-1:
 *      temp = []
 *      For each row i: temp.push_back(matrix[i][j])
 *      sort(temp)
 *      For each row i: matrix[i][j] = temp[i]
 *
 *  TIME COMPLEXITY ANALYSIS:
 *  ─────────────────────────
 *  - Each column has N elements → sorting one column = O(N × log N)
 *  - We have M columns → Total = O(M × N × log N)
 *  - Space: O(N) for the temporary column vector
 *
 *  CACHE PERFORMANCE NOTE (GM-Level Insight):
 *  ──────────────────────────────────────────
 *  Column access is NOT cache-friendly! In a row-major 2D array, accessing
 *  matrix[0][j], matrix[1][j], matrix[2][j]... jumps by M elements each time.
 *  This causes cache misses. For very large matrices (N,M > 10000), consider:
 *  - Transposing the matrix → sort rows → transpose back
 *  - This converts column access into row access (cache-friendly!)
 *  - Trade-off: 2 extra O(N×M) transpose passes vs. cache-miss penalty
 *
 *  EXAMPLE:
 *  ────────
 *  Before:                    After:
 *   9  3  7                   5  1  3
 *   5  2  8                   6  2  7
 *   6  1  3                   9  3  8
 *
 *  Column 0: [9,5,6] → sorted → [5,6,9]
 *  Column 1: [3,2,1] → sorted → [1,2,3]
 *  Column 2: [7,8,3] → sorted → [3,7,8]
 *
 *  Notice: Each column is sorted top-to-bottom, but rows are NOT sorted.
 */
void sortEachColumn(vector<vector<int>>& matrix) {
    if (matrix.empty()) return;
    int rows = matrix.size();
    int cols = matrix[0].size();

    for (int j = 0; j < cols; j++) {
        // 1. EXTRACT column j
        vector<int> col(rows);
        for (int i = 0; i < rows; i++) {
            col[i] = matrix[i][j];
        }

        // 2. SORT
        sort(col.begin(), col.end());

        // 3. PUT BACK
        for (int i = 0; i < rows; i++) {
            matrix[i][j] = col[i];
        }
    }
}

// Variant: Cache-friendly column sort using transpose
// (Better performance for large matrices)
void sortEachColumnTranspose(vector<vector<int>>& matrix) {
    if (matrix.empty()) return;
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Step 1: Transpose (swap rows and columns)
    vector<vector<int>> transposed(cols, vector<int>(rows));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            transposed[j][i] = matrix[i][j];

    // Step 2: Sort each row of transposed matrix (= sorting columns of original)
    for (int j = 0; j < cols; j++)
        sort(transposed[j].begin(), transposed[j].end());

    // Step 3: Transpose back
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = transposed[j][i];
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 1: BINARY SEARCH ON EACH ROW  O(N × log M)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  If each row is sorted independently, binary search each row.
 *  Time: O(N × log M), Space: O(1)
 */
pair<int,int> binarySearchPerRow(const vector<vector<int>>& mat, int target) {
    int n = mat.size(), m = mat[0].size();
    for (int i = 0; i < n; i++) {
        // Binary search in row i
        int lo = 0, hi = m - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (mat[i][mid] == target)
                return {i, mid};
            else if (mat[i][mid] < target)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
    }
    return {-1, -1};
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 2: BINARY SEARCH ON FULLY SORTED MATRIX  O(log(N×M))
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Matrix where:
 *  - Each row is sorted left to right
 *  - First element of each row > last element of previous row
 *
 *  This means the entire matrix is sorted in row-major order!
 *  Treat it as a 1D sorted array of size N×M.
 *
 *  Index mapping:
 *  1D index k → row = k / M, col = k % M
 *
 *  LC #74: Search a 2D Matrix
 *  Time: O(log(N×M)), Space: O(1)
 *
 *  Example:
 *   1   3   5   7
 *  10  11  16  20
 *  23  30  34  60
 *
 *  Target = 3 → Found at (0, 1)
 */
bool searchFullySortedMatrix(const vector<vector<int>>& mat, int target) {
    int n = mat.size(), m = mat[0].size();
    int lo = 0, hi = n * m - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int row = mid / m;
        int col = mid % m;
        int val = mat[row][col];

        if (val == target) {
            cout << "Found " << target << " at (" << row << ", " << col << ")" << endl;
            return true;
        } else if (val < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    cout << target << " not found" << endl;
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 3: STAIRCASE SEARCH  O(N + M)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  For matrix where:
 *  - Each row is sorted left to right
 *  - Each column is sorted top to bottom
 *  (But first element of next row is NOT necessarily > last of previous row)
 *
 *  Start from TOP-RIGHT corner (or BOTTOM-LEFT corner).
 *
 *  From top-right (0, M-1):
 *  - If current == target → Found!
 *  - If current > target → Move LEFT (smaller values)
 *  - If current < target → Move DOWN (larger values)
 *
 *  LC #240: Search a 2D Matrix II
 *  Time: O(N + M), Space: O(1)
 *
 *  Example:
 *   1   4   7  11  15
 *   2   5   8  12  19
 *   3   6   9  16  22
 *  10  13  14  17  24
 *  18  21  23  26  30
 *
 *  Target = 5:
 *  Start at (0,4)=15 > 5 → left
 *  (0,3)=11 > 5 → left
 *  (0,2)=7 > 5 → left
 *  (0,1)=4 < 5 → down
 *  (1,1)=5 = 5 → Found!
 */
bool staircaseSearch(const vector<vector<int>>& mat, int target) {
    int n = mat.size(), m = mat[0].size();

    // Start from top-right corner
    int i = 0, j = m - 1;

    while (i < n && j >= 0) {
        if (mat[i][j] == target) {
            cout << "Found " << target << " at (" << i << ", " << j << ")" << endl;
            return true;
        } else if (mat[i][j] > target) {
            j--; // Move left
        } else {
            i++; // Move down
        }
    }

    cout << target << " not found" << endl;
    return false;
}

// Alternative: Start from Bottom-Left corner
bool staircaseSearchBL(const vector<vector<int>>& mat, int target) {
    int n = mat.size(), m = mat[0].size();
    int i = n - 1, j = 0;

    while (i >= 0 && j < m) {
        if (mat[i][j] == target) {
            cout << "Found " << target << " at (" << i << ", " << j << ")" << endl;
            return true;
        } else if (mat[i][j] > target) {
            i--; // Move up
        } else {
            j++; // Move right
        }
    }

    cout << target << " not found" << endl;
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 4: ROW WITH MAXIMUM 1s IN BINARY MATRIX  O(N + M)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Given binary matrix where each row has 0s followed by 1s,
 *  find the row with the maximum number of 1s.
 *
 *  Approach: Start from top-right. Move left on 1, move down on 0.
 *  Time: O(N + M), Space: O(1)
 *
 *  Example:
 *  0 0 0 1 1
 *  0 0 1 1 1
 *  0 0 0 0 1
 *  0 1 1 1 1
 * Answer: Row 3 (four 1s)
 * Counting number of 1s using index j
 * (Staircase Algorithm Notes)
 * Example row:
 * index:  0 1 2 3 4
 * value:  0 0 0 1 1
 * After staircase movement:
 * index:  0 1 2 3 4
 * value:  0 0 0 1 1
               ↑
               j = 2   (j points to LAST 0)
 * ----------------------------------------
 * Step 1: Count number of zeros
 * Zeros exist from index 0 to j
 * Formula:
 * count = last_index - first_index + 1
 * count = j - 0 + 1
 * count = j + 1
 * Example:
 * j = 2
 * zeros = 2 + 1 = 3
 * Reason:
 * Index starts from 0, so count is always j+1
 * ----------------------------------------
 * Step 2: Count number of ones
 * Total columns = m
 * Formula:
 * ones = total_columns - zeros
 * ones = m - (j + 1)
 * ones = m - 1 - j
 * Example:
 * m = 5, j = 2
 * ones = 5 - 1 - 2 -> ans => 2
 * ----------------------------------------
 * Final formulas to remember:
 * zeros = j + 1
 * ones  = m - 1 - j
 * ----------------------------------------
 * Key intuition:
 * j points to last 0
 * j+1 is first 1 index
 * Example:
 * 0 0 0 1 1
        ↑
        j
 * ones exist from index (j+1) to (m-1)
 * count = (m-1) - (j+1) + 1 -> m - 1 - j
 * ----------------------------------------
 * Time complexity advantage:
 * No need to count manually → O(1)
 * Because staircase already found boundary
 *  interview version: In staircase search, we start from the top-right corner.
 *                     At each step, depending on the value, we eliminate either one full row or one full column.
 *                     This reduces the search space efficiently, giving O(n + m) time complexity.
 */
int rowWithMaxOnes(const vector<vector<int>>& mat) {
    cout << "=== Row with Maximum 1s ===" << endl;
    int n = mat.size(), m = mat[0].size();
    int maxRow = 0;
    int j = m - 1; // Start from top-right

    for (int i = 0; i < n; i++) {
        while (j >= 0 && mat[i][j] == 1) {
            j--;
            maxRow = i; // This row has more 1s
        }
    }

    cout << "Row " << maxRow << " has the most 1s" << endl;
    cout << "Number of 1s = " << (m - 1 - j) << endl << endl;
    return maxRow;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 5: FIND PEAK ELEMENT IN 2D MATRIX  O(N × log M)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  A peak element is greater than or equal to all its 4 neighbors.
 *
 *  Approach: Binary search on columns.
 *  1. Pick middle column
 *  2. Find the maximum in that column
 *  3. Compare with left and right neighbors
 *  4. Move towards the larger neighbor
 *
 *  LC #1901: Find a Peak Element II
 *  Time: O(N × log M), Space: O(1)
 */
vector<int> findPeakGrid(const vector<vector<int>>& mat) {
    cout << "=== Find Peak Element in 2D ===" << endl;
    int n = mat.size(), m = mat[0].size();
    int lo = 0, hi = m - 1;

    while (lo <= hi) {
        int midCol = lo + (hi - lo) / 2;

        // Find max in this column
        int maxRow = 0;
        for (int i = 0; i < n; i++)
            if (mat[i][midCol] > mat[maxRow][midCol])
                maxRow = i;

        // Compare with left and right
        int left = (midCol > 0) ? mat[maxRow][midCol - 1] : -1;
        int right = (midCol < m - 1) ? mat[maxRow][midCol + 1] : -1;
        int cur = mat[maxRow][midCol];

        if (cur >= left && cur >= right) {
            cout << "Peak at (" << maxRow << ", " << midCol << ") = " << cur << endl << endl;
            return {maxRow, midCol};
        } else if (left > cur) {
            hi = midCol - 1;
        } else {
            lo = midCol + 1;
        }
    }
    return {-1, -1};
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 6: KTH SMALLEST IN SORTED MATRIX  O(N × log(max-min))
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Matrix where each row and each column is sorted.
 *  Find the kth smallest element.
 *
 *  Approach: Binary search on value range.
 *  - lo = mat[0][0] (minimum), hi = mat[n-1][m-1] (maximum)
 *  - For each mid value, count elements ≤ mid
 *  - If count < k → lo = mid + 1
 *  - If count >= k → hi = mid
 *
 *  Counting ≤ mid: Start from bottom-left of each column.
 *
 *  LC #378: Kth Smallest Element in a Sorted Matrix
 *  Time: O(N × log(max - min)), Space: O(1)
 */
int countLessEqual(const vector<vector<int>>& mat, int target) {
    int n = mat.size(), m = mat[0].size();
    int count = 0;
    int i = n - 1, j = 0; // Start from bottom-left

    while (i >= 0 && j < m) {
        if (mat[i][j] <= target) {
            count += (i + 1); // All elements above in this column are ≤ target
            j++;
        } else {
            i--;
        }
    }
    return count;
}

int kthSmallest(const vector<vector<int>>& mat, int k) {
    cout << "=== Kth Smallest Element (k=" << k << ") ===" << endl;
    int n = mat.size(), m = mat[0].size();
    int lo = mat[0][0], hi = mat[n-1][m-1];

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        int count = countLessEqual(mat, mid);

        if (count < k)
            lo = mid + 1;
        else
            hi = mid;
    }

    cout << "The " << k << "th smallest element = " << lo << endl << endl;
    return lo;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 7: COUNT NEGATIVE NUMBERS IN SORTED MATRIX  O(N + M)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Matrix sorted in non-increasing order in both row and column.
 *  Count the number of negative numbers.
 *
 *  Approach: Staircase from bottom-left.
 *
 *  LC #1351: Count Negative Numbers in a Sorted Matrix
 *  Time: O(N + M), Space: O(1)
 */
int countNegatives(const vector<vector<int>>& mat) {
    cout << "=== Count Negative Numbers ===" << endl;
    int n = mat.size(), m = mat[0].size();
    int count = 0;
    int i = 0, j = m - 1;

    while (i < n && j >= 0) {
        if (mat[i][j] < 0) {
            count += (n - i); // All elements below are also negative
            j--;
        } else {
            i++;
        }
    }

    cout << "Negative count = " << count << endl << endl;
    return count;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 8: MEDIAN OF ROW-WISE SORTED MATRIX  O(N × log M × log(max-min))
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  PROBLEM (GFG Classic / Amazon / Google Interview):
 *  ──────────────────────────────────────────────────
 *  Given an N × M matrix where each ROW is sorted in ascending order,
 *  and N × M is always ODD, find the MEDIAN of the matrix.
 *
 *  The median is the middle element when all N×M elements are sorted.
 *  Position of median = (N × M) / 2  (0-indexed in sorted order)
 *  We need at least (N×M)/2 + 1 elements ≤ median (1-indexed: (N×M+1)/2)
 *
 *  WHY ROW SORTING MATTERS:
 *  ────────────────────────
 *  Because each row is sorted, we can use BINARY SEARCH (upper_bound)
 *  within each row to count how many elements are ≤ a given value.
 *  This is exactly why Level 0.6 (Sort Each Row) is a prerequisite!
 *
 *  If the matrix was NOT row-sorted, we'd need O(N×M) to count elements ≤ mid.
 *  With row-sorting, counting takes only O(N × log M).
 *
 *  APPROACH: Binary Search on Answer (Value Range)
 *  ────────────────────────────────────────────────
 *  1. Find the global MIN (= min of first column) and MAX (= max of last column)
 *  2. Binary search on the value range [MIN, MAX]:
 *     - For each candidate mid value:
 *       - Count how many elements in the matrix are ≤ mid
 *       - Use upper_bound on each row → O(N × log M)
 *     - If count ≤ (N×M)/2 → median is LARGER → lo = mid + 1
 *     - Else                → median could be mid or smaller → hi = mid
 *  3. When lo == hi, that's the median.
 *
 *  WHY upper_bound?
 *  ────────────────
 *  upper_bound(row.begin(), row.end(), mid) returns iterator to FIRST element > mid.
 *  Distance from begin = number of elements ≤ mid in that row.
 *
 *  COMPLEXITY:
 *  ──────────
 *  - Binary search on value range: O(log(MAX - MIN)) iterations
 *  - Each iteration: count across N rows using upper_bound → O(N × log M)
 *  - Total: O(N × log M × log(MAX - MIN))
 *  - Space: O(1)
 *
 *  For 32-bit integers: log(MAX - MIN) ≤ 32, so effectively O(32 × N × log M)
 *
 *  EXAMPLE:
 *  ────────
 *  Matrix (3×3, each row sorted):
 *   1  3  5
 *   2  6  9
 *   3  6  9
 *
 *  All elements sorted: [1, 2, 3, 3, 5, 6, 6, 9, 9]
 *  N×M = 9, median position = 9/2 = 4 (0-indexed) → median = 5
 *  Required: at least 5 elements ≤ median
 *
 *  Binary search trace:
 *  lo=1, hi=9
 *  mid=5: count(≤5) = 2(row0:[1,3]) + 1(row1:[2]) + 2(row2:[3]) → wait:
 *    Row 0: [1,3,5] → upper_bound(5) points past 5 → count=3
 *    Row 1: [2,6,9] → upper_bound(5) points to 6 → count=1
 *    Row 2: [3,6,9] → upper_bound(5) points to 6 → count=1
 *    Total = 3+1+1 = 5 ≥ 5 → hi=5
 *  lo=1, hi=5 → mid=3:
 *    Row 0: [1,3,5] → upper_bound(3) points to 5 → count=2
 *    Row 1: [2,6,9] → upper_bound(3) points to 6 → count=1
 *    Row 2: [3,6,9] → upper_bound(3) points to 6 → count=1
 *    Total = 2+1+1 = 4 ≤ 4 → lo=4
 *  lo=4, hi=5 → mid=4:
 *    Row 0: [1,3,5] → upper_bound(4) points to 5 → count=2
 *    Row 1: [2,6,9] → upper_bound(4) points to 6 → count=1
 *    Row 2: [3,6,9] → upper_bound(4) points to 6 → count=1
 *    Total = 2+1+1 = 4 ≤ 4 → lo=5
 *  lo=5, hi=5 → answer = 5 ✓
 *
 *  INTERVIEW VERSION:
 *  ──────────────────
 *  We binary search on the VALUE range, not on indices. For each candidate
 *  value, we count elements ≤ it using upper_bound on each sorted row.
 *  The key insight is: the median is the smallest value where
 *  count(≤ value) > (N×M)/2.
 */
int medianOfRowSortedMatrix(const vector<vector<int>>& matrix) {
    cout << "=== Median of Row-Sorted Matrix ===" << endl;
    int n = matrix.size();
    int m = matrix[0].size();
    int desired = (n * m) / 2; // number of elements that should be ≤ median - 1

    // Find global min and max
    int lo = INT_MAX, hi = INT_MIN;
    for (int i = 0; i < n; i++) {
        lo = min(lo, matrix[i][0]);       // First element of each row (minimum in that row)
        hi = max(hi, matrix[i][m - 1]);   // Last element of each row (maximum in that row)
    }

    // Binary search on value range
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        // Count elements ≤ mid across all rows
        int count = 0;
        for (int i = 0; i < n; i++) {
            // upper_bound returns iterator to first element > mid
            // distance from begin = count of elements ≤ mid in this row
            count += (int)(upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin());
        }

        if (count <= desired) {
            lo = mid + 1; // Median is larger
        } else {
            hi = mid;     // Median could be mid or smaller
        }
    }

    cout << "Median = " << lo << endl << endl;
    return lo;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 9: SORT MATRIX DIAGONALLY  O(min(N,M)² × log(min(N,M)))
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  LC #1329: Sort the Matrix Diagonally
 *
 *  PROBLEM:
 *  ────────
 *  A matrix diagonal is a diagonal line of cells starting from some cell
 *  in either the topmost row or leftmost column and going towards
 *  bottom-right direction. Sort each diagonal independently in ascending order.
 *
 *  KEY INSIGHT:
 *  ────────────
 *  All cells on the same diagonal have the same value of (i - j).
 *  So we group cells by (i - j), sort each group, and put them back.
 *
 *  Using a map<int, vector<int>>:
 *  - Key = i - j (diagonal identifier)
 *  - Value = list of elements on that diagonal
 *
 *  ALGORITHM:
 *  ──────────
 *  1. For each cell (i, j), push matrix[i][j] into diagonals[i - j]
 *  2. Sort each diagonal vector
 *  3. For each cell (i, j), pop from diagonals[i - j] and place back
 *
 *  COMPLEXITY:
 *  ──────────
 *  - Number of diagonals = N + M - 1
 *  - Longest diagonal has min(N, M) elements
 *  - Sorting all diagonals: O(N × M × log(min(N, M)))
 *  - Space: O(N × M)
 *
 *  EXAMPLE:
 *  ────────
 *  Before:              After:
 *   3  3  1  1          1  1  1  1
 *   2  2  1  2          1  2  2  2
 *   1  1  1  2          1  2  1  3
 *
 *  Diagonals grouped by (i - j):
 *  (i-j = -3): [1]           → [1]
 *  (i-j = -2): [1, 2]       → [1, 2]
 *  (i-j = -1): [3, 1, 1]   → [1, 1, 3]
 *  (i-j =  0): [3, 2, 1]   → [1, 2, 3]
 *  (i-j =  1): [2, 1]       → [1, 2]
 *  (i-j =  2): [1]           → [1]
 *
 *  Rebuild matrix using sorted diagonals:
 *  (0,0)=diag[0][0]=1  (0,1)=diag[-1][0]=1  (0,2)=diag[-2][0]=1  (0,3)=diag[-3][0]=1
 *  (1,0)=diag[1][0]=1  (1,1)=diag[0][1]=2   (1,2)=diag[-1][1]=1  (1,3)=diag[-2][1]=2
 *  (2,0)=diag[2][0]=1  (2,1)=diag[1][1]=2   (2,2)=diag[0][2]=3   (2,3)=diag[-1][2]=3  ← wait
 *
 *  Actually the exact output depends on traversal order. The standard LC expected:
 *  Input:  [[3,3,1,1],[2,2,1,2],[1,1,1,2]]
 *  Output: [[1,1,1,1],[1,2,2,2],[1,1,1,2]]  (only main & lower diags change)
 */
vector<vector<int>> sortMatrixDiagonally(vector<vector<int>> mat) {
    cout << "=== Sort Matrix Diagonally ===" << endl;
    int n = mat.size(), m = mat[0].size();

    // Group elements by diagonal (i - j)
    map<int, vector<int>> diags;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            diags[i - j].push_back(mat[i][j]);

    // Sort each diagonal
    for (auto& [key, vec] : diags)
        sort(vec.begin(), vec.end());

    // Create index trackers for each diagonal
    map<int, int> idx;
    for (auto& [key, vec] : diags)
        idx[key] = 0;

    // Put back sorted values
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            mat[i][j] = diags[i - j][idx[i - j]++];

    return mat;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 10: MAKE MATRIX ROW+COL SORTED (Young Tableau Construction)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  PROBLEM:
 *  ────────
 *  Given any unsorted N×M matrix, rearrange elements such that:
 *  - Each row is sorted left to right
 *  - Each column is sorted top to bottom
 *  (This forms a "Young Tableau" - a fundamental data structure in combinatorics)
 *
 *  APPROACH: Flatten + Sort + Row-Major Fill
 *  ──────────────────────────────────────────
 *  If we flatten all elements, sort them, and fill back in row-major order:
 *  - Row i, Col j gets element at position (i * M + j) in the sorted array
 *  - Since sorted[i*M + j] < sorted[i*M + j + 1] → rows are sorted ✓
 *  - Since sorted[i*M + j] < sorted[(i+1)*M + j] → columns are sorted ✓
 *    (because i*M + j < (i+1)*M + j as M > 0)
 *
 *  This is actually the same as sortEntireMatrix (Level 0.5)!
 *  The insight here is that flatten+sort+row-major-fill GUARANTEES
 *  both row-sorted AND column-sorted properties.
 *
 *  PROOF:
 *  ──────
 *  For any cell (i, j), its 1D index = i*M + j.
 *  Right neighbor (i, j+1) has index i*M + j + 1 > i*M + j → mat[i][j+1] ≥ mat[i][j] ✓
 *  Below neighbor (i+1, j) has index (i+1)*M + j = i*M + M + j > i*M + j → mat[i+1][j] ≥ mat[i][j] ✓
 *
 *  COMPLEXITY:
 *  ──────────
 *  Time: O(N × M × log(N × M)) for sorting
 *  Space: O(N × M) for temporary array
 *
 *  EXAMPLE:
 *  ────────
 *  Before (unsorted):
 *   9  5  3
 *   7  1  8
 *   6  2  4
 *
 *  Flatten: [9,5,3,7,1,8,6,2,4]
 *  Sort:    [1,2,3,4,5,6,7,8,9]
 *  Reshape (3×3):
 *   1  2  3     ← Row sorted ✓
 *   4  5  6     ← Row sorted ✓
 *   7  8  9     ← Row sorted ✓
 *   ↓  ↓  ↓
 *   Col sorted ✓
 *
 *  GM-Level Note:
 *  This works perfectly for creating a Young Tableau from scratch.
 *  However, if you need to INSERT/DELETE from a Young Tableau while
 *  maintaining the sorted property, you need the O(N+M) "bubble" algorithm.
 */
void makeRowColSorted(vector<vector<int>>& matrix) {
    cout << "=== Make Matrix Row+Col Sorted (Young Tableau) ===" << endl;
    if (matrix.empty()) return;
    int rows = matrix.size(), cols = matrix[0].size();

    // Flatten
    vector<int> temp;
    temp.reserve(rows * cols);
    for (const auto& row : matrix)
        for (int val : row)
            temp.push_back(val);

    // Sort
    sort(temp.begin(), temp.end());

    // Reshape in row-major order
    int k = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = temp[k++];
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   MATRIX SEARCH TECHNIQUES - ZERO TO GM MASTERY  ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << endl;

    // Level 0: Linear Search
    cout << "=== Level 0: Linear Search ===" << endl;
    vector<vector<int>> mat1 = {{5,2,8},{1,9,3},{7,4,6}};
    printMatrix(mat1, "Unsorted Matrix");
    auto [r, c] = linearSearch(mat1, 9);
    cout << "Found 9 at (" << r << ", " << c << ")\n\n";

    // Level 0.5: Sort Entire Matrix
    cout << "=== Level 0.5: Sort Entire Matrix ===" << endl;
    vector<vector<int>> matSort1 = {{9,5,3},{7,1,8},{6,2,4}};
    printMatrix(matSort1, "Before Sort Entire Matrix");
    sortEntireMatrix(matSort1);
    printMatrix(matSort1, "After Sort Entire Matrix");

    // Level 0.6: Sort Each Row
    cout << "=== Level 0.6: Sort Each Row Independently ===" << endl;
    vector<vector<int>> matSort2 = {{9,3,7,1},{5,2,8,4},{6,1,3,2}};
    printMatrix(matSort2, "Before Sort Each Row");
    sortEachRow(matSort2);
    printMatrix(matSort2, "After Sort Each Row");

    // Level 0.7: Sort Each Column
    cout << "=== Level 0.7: Sort Each Column Independently ===" << endl;
    vector<vector<int>> matSort3 = {{9,3,7},{5,2,8},{6,1,3}};
    printMatrix(matSort3, "Before Sort Each Column");
    sortEachColumn(matSort3);
    printMatrix(matSort3, "After Sort Each Column");

    // Also demo cache-friendly variant
    vector<vector<int>> matSort3b = {{9,3,7},{5,2,8},{6,1,3}};
    sortEachColumnTranspose(matSort3b);
    printMatrix(matSort3b, "After Sort Each Column (Transpose Method)");

    // Level 1: Binary Search per Row
    cout << "=== Level 1: Binary Search per Row ===" << endl;
    vector<vector<int>> mat2 = {{1,3,5,7},{2,4,6,8},{10,20,30,40}};
    printMatrix(mat2, "Row-Sorted Matrix");
    auto [r2, c2] = binarySearchPerRow(mat2, 6);
    cout << "Found 6 at (" << r2 << ", " << c2 << ")\n\n";

    // Level 2: Binary Search on Fully Sorted Matrix (LC #74)
    cout << "=== Level 2: Fully Sorted Binary Search ===" << endl;
    vector<vector<int>> mat3 = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    printMatrix(mat3, "Fully Sorted Matrix");
    searchFullySortedMatrix(mat3, 3);
    searchFullySortedMatrix(mat3, 13);
    cout << endl;

    // Level 3: Staircase Search (LC #240)
    cout << "=== Level 3: Staircase Search ===" << endl;
    vector<vector<int>> mat4 = {
        {1,  4,  7,  11, 15},
        {2,  5,  8,  12, 19},
        {3,  6,  9,  16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };
    printMatrix(mat4, "Row+Col Sorted Matrix");
    staircaseSearch(mat4, 5);
    staircaseSearch(mat4, 20);
    cout << "Using Bottom-Left start:" << endl;
    staircaseSearchBL(mat4, 14);
    cout << endl;

    // Level 4: Row with Maximum 1s
    vector<vector<int>> binMat = {
        {0, 0, 0, 1, 1},
        {0, 0, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 1, 1, 1, 1}
    };
    printMatrix(binMat, "Binary Matrix");
    rowWithMaxOnes(binMat);

    // Level 5: Peak Element in 2D
    vector<vector<int>> mat5 = {
        {10, 20, 15},
        {21, 30, 14},
        {7,  16, 32}
    };
    printMatrix(mat5, "Matrix for Peak");
    findPeakGrid(mat5);

    // Level 6: Kth Smallest (LC #378)
    vector<vector<int>> mat6 = {
        {1,  5,  9},
        {10, 11, 13},
        {12, 13, 15}
    };
    printMatrix(mat6, "Sorted Matrix");
    kthSmallest(mat6, 1); // 1st smallest = 1
    kthSmallest(mat6, 5); // 5th smallest = 11
    kthSmallest(mat6, 8); // 8th smallest = 13

    // Level 7: Count Negatives (LC #1351)
    vector<vector<int>> mat7 = {
        {4,  3,  2, -1},
        {3,  2,  1, -1},
        {1,  1, -1, -2},
        {-1, -1, -2, -3}
    };
    printMatrix(mat7, "Non-Increasing Sorted Matrix");
    countNegatives(mat7);

    // Level 8: Median of Row-Sorted Matrix (GFG Classic)
    cout << "=== Level 8: Median of Row-Sorted Matrix ===" << endl;
    vector<vector<int>> mat8 = {
        {1, 3, 5},
        {2, 6, 9},
        {3, 6, 9}
    };
    printMatrix(mat8, "Row-Sorted Matrix for Median");
    medianOfRowSortedMatrix(mat8); // Expected: 5

    vector<vector<int>> mat8b = {
        {1,  3,  5,  7,  9},
        {2,  4,  6,  8, 10},
        {11, 13, 15, 17, 19}
    };
    printMatrix(mat8b, "Larger Row-Sorted Matrix for Median");
    medianOfRowSortedMatrix(mat8b); // All sorted: [1,2,3,4,5,6,7,8,9,10,11,13,15,17,19] → median=7

    // Demonstrate: What if matrix is NOT row-sorted? Sort rows first, then find median!
    cout << "=== Median of Unsorted Matrix (Sort Rows First!) ===" << endl;
    vector<vector<int>> mat8c = {
        {9, 3, 7},
        {5, 2, 8},
        {6, 1, 3}
    };
    printMatrix(mat8c, "Unsorted Matrix");
    sortEachRow(mat8c); // Prerequisite: sort each row!
    printMatrix(mat8c, "After Row Sorting (now we can find median)");
    medianOfRowSortedMatrix(mat8c); // All: [1,2,3,3,5,6,7,8,9] → median=5

    // Level 9: Sort Matrix Diagonally (LC #1329)
    cout << "=== Level 9: Sort Matrix Diagonally ===" << endl;
    vector<vector<int>> mat9 = {
        {3, 3, 1, 1},
        {2, 2, 1, 2},
        {1, 1, 1, 2}
    };
    printMatrix(mat9, "Before Diagonal Sort");
    auto mat9sorted = sortMatrixDiagonally(mat9);
    printMatrix(mat9sorted, "After Diagonal Sort");

    // Level 10: Make Matrix Row+Col Sorted (Young Tableau)
    cout << "=== Level 10: Make Row+Col Sorted ===" << endl;
    vector<vector<int>> mat10 = {
        {9, 5, 3},
        {7, 1, 8},
        {6, 2, 4}
    };
    printMatrix(mat10, "Before (Unsorted)");
    makeRowColSorted(mat10);
    printMatrix(mat10, "After (Row+Col Sorted - Young Tableau)");

    // Verify row+col sorted property
    cout << "Verification:" << endl;
    bool valid = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j + 1 < 3 && mat10[i][j] > mat10[i][j+1]) { valid = false; break; }
            if (i + 1 < 3 && mat10[i][j] > mat10[i+1][j]) { valid = false; break; }
        }
    }
    cout << "Matrix is " << (valid ? "VALID" : "INVALID") << " Young Tableau\n\n";

    return 0;
}

