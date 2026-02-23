/*
 * ============================================================================
 *           MATRIX SEARCH TECHNIQUES - ZERO TO GM MASTERY
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Topic   : Searching in 2D Matrices (Linear, Staircase, Binary Search)
 * Level   : 0 (Beginner) → 7 (GM)
 * ============================================================================
 *
 *  TABLE OF CONTENTS
 *  ─────────────────
 *  Level 0 : Brute Force Linear Search O(N×M)
 *  Level 1 : Binary Search on Each Row O(N×logM)
 *  Level 2 : Binary Search on Fully Sorted Matrix O(log(N×M)) [LC #74]
 *  Level 3 : Staircase Search in Row+Col Sorted Matrix O(N+M) [LC #240]
 *  Level 4 : Find Row with Maximum 1s in Binary Matrix O(N+M)
 *  Level 5 : Find Peak Element in 2D Matrix O(N×logM) [LC #1901]
 *  Level 6 : Kth Smallest in Sorted Matrix O(N×log(max-min)) [LC #378]
 *  Level 7 : Count Negative Numbers in Sorted Matrix O(N+M) [LC #1351]
 *
 * ============================================================================
 *  SEARCH STRATEGY DECISION TABLE:
 *  ┌────────────────────────────────┬────────────────────┬────────────┐
 *  │ Matrix Type                    │ Best Algorithm     │ Complexity │
 *  ├────────────────────────────────┼────────────────────┼────────────┤
 *  │ Unsorted                       │ Linear Search      │ O(N×M)     │
 *  │ Each row sorted                │ Binary per row     │ O(N×logM)  │
 *  │ Fully sorted (row-major)       │ Binary on flat     │ O(log(NM)) │
 *  │ Row+Col sorted                 │ Staircase          │ O(N+M)     │
 *  │ Binary (0s then 1s per row)    │ Binary+Staircase   │ O(N+M)     │
 *  └────────────────────────────────┴────────────────────┴────────────┘
 *
 *  Related Problems:
 *  - LC #74:   Search a 2D Matrix
 *  - LC #240:  Search a 2D Matrix II
 *  - LC #378:  Kth Smallest Element in a Sorted Matrix
 *  - LC #1351: Count Negative Numbers in a Sorted Matrix
 *  - LC #1901: Find a Peak Element II
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
 *
 *  Answer: Row 3 (four 1s)
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
// MAIN
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   MATRIX SEARCH TECHNIQUES - ZERO TO GM MASTERY ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << endl;

    // Level 0: Linear Search
    cout << "=== Level 0: Linear Search ===" << endl;
    vector<vector<int>> mat1 = {{5,2,8},{1,9,3},{7,4,6}};
    printMatrix(mat1, "Unsorted Matrix");
    auto [r, c] = linearSearch(mat1, 9);
    cout << "Found 9 at (" << r << ", " << c << ")\n\n";

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

    return 0;
}

