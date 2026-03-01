/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 08 — 2D SEARCHING & BINARY SEARCH                        ║
║           From Zero to Grandmaster — Complete Foundation                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 LEVEL 1 — Basic 2D Search
   1.1 Search in row-wise sorted matrix
   1.2 Flatten matrix → binary search
   1.3 Search in 2D as 1D mapping
   1.4 Matrix treated as sorted array

 LEVEL 2 — Row + Column Sorted Matrix
   2.1 Staircase search O(n+m)
   2.2 Top-right elimination method
   2.3 Bottom-left method
   2.4 Count elements ≤ X in matrix

 LEVEL 3 — Binary Search on Matrix Answer
   3.1 Kth smallest element in sorted matrix
   3.2 Binary search on value space
   3.3 Count elements ≤ mid
   3.4 Median in row-wise sorted matrix

 LEVEL 4 — 2D Peak & Optimization Search
   4.1 Find peak element in 2D
   4.2 Binary search on columns
   4.3 Mountain matrix 2D variant

 LEVEL 5 — Advanced / ICPC
   5.1 Binary search on submatrix condition
   5.2 Parametric search in grid
   5.3 2D prefix + binary search hybrid
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <climits>
#include <queue>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// LEVEL 1: BASIC 2D SEARCH
// ═══════════════════════════════════════════════════════════════

// 1.1 Search in row-wise sorted matrix (each row sorted independently)
// O(m * log n) — binary search each row
/*
 Matrix:
   [10, 20, 30, 40]
   [15, 25, 35, 45]
   [27, 29, 37, 48]
   [32, 33, 39, 50]
 Each row is sorted, but rows are independent.
*/
bool searchRowSorted(vector<vector<int>>& matrix, int target) {
    for (auto& row : matrix) {
        if (binary_search(row.begin(), row.end(), target))
            return true;
    }
    return false;
}

// 1.2/1.3 Search in fully sorted 2D matrix (LC 74)
// Matrix: each row sorted, first element of next row > last of previous
// Treat as 1D sorted array: index i → matrix[i/cols][i%cols]
/*
 Matrix:
   [1,  3,  5,  7 ]
   [10, 11, 16, 20]
   [23, 30, 34, 60]
 Flattened: [1, 3, 5, 7, 10, 11, 16, 20, 23, 30, 34, 60]
*/
bool searchMatrix_1D(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    int rows = matrix.size(), cols = matrix[0].size();
    int lo = 0, hi = rows * cols - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int val = matrix[mid / cols][mid % cols]; // 1D → 2D mapping
        if (val == target) return true;
        if (val < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return false;
}

// 1.4 Binary search row first, then column
bool searchMatrix_twoBS(vector<vector<int>>& matrix, int target) {
    if (matrix.empty()) return false;
    int rows = matrix.size(), cols = matrix[0].size();

    // Binary search for the correct row
    int lo = 0, hi = rows - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (matrix[mid][0] <= target && target <= matrix[mid][cols - 1]) {
            // Binary search within this row
            return binary_search(matrix[mid].begin(), matrix[mid].end(), target);
        }
        if (matrix[mid][0] > target) hi = mid - 1;
        else lo = mid + 1;
    }
    return false;
}

void demo_level1() {
    cout << "=== LEVEL 1: BASIC 2D SEARCH ===" << endl;

    vector<vector<int>> matrix = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };

    cout << "Search 3 (1D mapping): " << searchMatrix_1D(matrix, 3) << endl;    // 1
    cout << "Search 13 (1D mapping): " << searchMatrix_1D(matrix, 13) << endl;   // 0
    cout << "Search 30 (two BS): " << searchMatrix_twoBS(matrix, 30) << endl;    // 1

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// LEVEL 2: ROW + COLUMN SORTED MATRIX
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Matrix where BOTH rows and columns are sorted (LC 240):
   [1,  4,  7,  11, 15]
   [2,  5,  8,  12, 19]
   [3,  6,  9,  16, 22]
   [10, 13, 14, 17, 24]
   [18, 21, 23, 26, 30]

 This is NOT fully sorted as 1D — can't use simple BS.
 But we can exploit the row+column sorted property.
*/

// 2.1/2.2 Staircase Search — Top-Right Elimination
// Start at top-right corner. If val > target, go left. If val < target, go down.
// O(n + m) time
bool staircaseSearch_topRight(vector<vector<int>>& matrix, int target) {
    if (matrix.empty()) return false;
    int rows = matrix.size(), cols = matrix[0].size();
    int r = 0, c = cols - 1;

    while (r < rows && c >= 0) {
        if (matrix[r][c] == target) return true;
        if (matrix[r][c] > target) c--;  // Eliminate column
        else r++;                          // Eliminate row
    }
    return false;
}

// 2.3 Bottom-Left Method (symmetric to top-right)
bool staircaseSearch_bottomLeft(vector<vector<int>>& matrix, int target) {
    if (matrix.empty()) return false;
    int rows = matrix.size(), cols = matrix[0].size();
    int r = rows - 1, c = 0;

    while (r >= 0 && c < cols) {
        if (matrix[r][c] == target) return true;
        if (matrix[r][c] > target) r--;
        else c++;
    }
    return false;
}

// 2.4 Count elements ≤ X in row+column sorted matrix
// Start from bottom-left: O(n + m)
int countLessOrEqual(vector<vector<int>>& matrix, int x) {
    int rows = matrix.size(), cols = matrix[0].size();
    int count = 0;
    int r = rows - 1, c = 0;

    while (r >= 0 && c < cols) {
        if (matrix[r][c] <= x) {
            count += (r + 1); // All elements above in this column are also ≤ x
            c++;
        } else {
            r--;
        }
    }
    return count;
}

void demo_level2() {
    cout << "=== LEVEL 2: ROW + COLUMN SORTED ===" << endl;

    vector<vector<int>> matrix = {
        {1, 4, 7, 11, 15},
        {2, 5, 8, 12, 19},
        {3, 6, 9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };

    cout << "Search 5 (top-right): " << staircaseSearch_topRight(matrix, 5) << endl;     // 1
    cout << "Search 20 (top-right): " << staircaseSearch_topRight(matrix, 20) << endl;    // 0
    cout << "Search 14 (bottom-left): " << staircaseSearch_bottomLeft(matrix, 14) << endl; // 1

    cout << "Count ≤ 9: " << countLessOrEqual(matrix, 9) << endl;   // 9
    cout << "Count ≤ 15: " << countLessOrEqual(matrix, 15) << endl;  // 13

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// LEVEL 3: BINARY SEARCH ON MATRIX ANSWER
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Instead of searching FOR an element, we binary search on the
 VALUE SPACE of the matrix.

 KEY TECHNIQUE:
   For a matrix with row+column sorted property:
   - min value = matrix[0][0]
   - max value = matrix[n-1][m-1]
   - Binary search on value X in [min, max]
   - Count elements ≤ X using staircase method: O(n+m)
   - Total: O((n+m) * log(max-min))
*/

// 3.1/3.2/3.3 Kth Smallest Element in Sorted Matrix (LC 378)
int kthSmallest(vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    int lo = matrix[0][0], hi = matrix[n - 1][n - 1];

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        int count = countLessOrEqual(matrix, mid);
        if (count < k) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

// 3.4 Median in Row-wise Sorted Matrix
// Rows are sorted, but columns may not be.
// Matrix has odd total elements (r*c is odd).
int countLessOrEqual_rowwise(vector<vector<int>>& matrix, int x) {
    int count = 0;
    for (auto& row : matrix) {
        count += upper_bound(row.begin(), row.end(), x) - row.begin();
    }
    return count;
}

int matrixMedian(vector<vector<int>>& matrix) {
    int rows = matrix.size(), cols = matrix[0].size();
    int total = rows * cols;
    int needed = total / 2 + 1; // Median is at position (total+1)/2

    int lo = INT_MAX, hi = INT_MIN;
    for (auto& row : matrix) {
        lo = min(lo, row.front());
        hi = max(hi, row.back());
    }

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        int count = countLessOrEqual_rowwise(matrix, mid);
        if (count < needed) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

void demo_level3() {
    cout << "=== LEVEL 3: BS ON MATRIX ANSWER ===" << endl;

    // Kth Smallest
    vector<vector<int>> matrix = {
        {1, 5, 9},
        {10, 11, 13},
        {12, 13, 15}
    };
    cout << "Kth smallest (k=8): " << kthSmallest(matrix, 8) << endl; // 13

    // Median in row-wise sorted matrix
    vector<vector<int>> mat2 = {
        {1, 3, 5},
        {2, 6, 9},
        {3, 6, 9}
    };
    cout << "Matrix median: " << matrixMedian(mat2) << endl; // 5

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// LEVEL 4: 2D PEAK & OPTIMIZATION SEARCH
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 A 2D peak is an element that is ≥ all its neighbors (up, down, left, right).

 BRUTE FORCE: O(n*m) — check every element
 OPTIMAL: O(n log m) or O(m log n) — binary search on columns

 ALGORITHM (BS on columns):
   1. Pick middle column mid_col
   2. Find maximum element in that column → (max_row, mid_col)
   3. Compare with left and right neighbors
   4. If left neighbor > current → peak is in left half
   5. If right neighbor > current → peak is in right half
   6. Otherwise → current is a peak
*/

// Find Peak Element in 2D Matrix
pair<int, int> findPeak2D(vector<vector<int>>& matrix) {
    int rows = matrix.size(), cols = matrix[0].size();
    int lo = 0, hi = cols - 1;

    while (lo <= hi) {
        int midCol = lo + (hi - lo) / 2;

        // Find row with max value in midCol
        int maxRow = 0;
        for (int r = 1; r < rows; r++) {
            if (matrix[r][midCol] > matrix[maxRow][midCol]) {
                maxRow = r;
            }
        }

        int current = matrix[maxRow][midCol];
        int left = (midCol > 0) ? matrix[maxRow][midCol - 1] : INT_MIN;
        int right = (midCol < cols - 1) ? matrix[maxRow][midCol + 1] : INT_MIN;

        if (current >= left && current >= right) {
            return {maxRow, midCol}; // Found peak
        } else if (left > current) {
            hi = midCol - 1;
        } else {
            lo = midCol + 1;
        }
    }
    return {-1, -1};
}

void demo_level4() {
    cout << "=== LEVEL 4: 2D PEAK SEARCH ===" << endl;

    vector<vector<int>> matrix = {
        {10, 8, 10, 10},
        {14, 13, 12, 11},
        {15, 9, 11, 21},
        {16, 17, 19, 20}
    };

    auto [r, c] = findPeak2D(matrix);
    cout << "2D Peak at (" << r << "," << c << ") = " << matrix[r][c] << endl;
    // Verify it's a peak
    bool isPeak = true;
    int val = matrix[r][c];
    if (r > 0 && matrix[r - 1][c] > val) isPeak = false;
    if (r < (int)matrix.size() - 1 && matrix[r + 1][c] > val) isPeak = false;
    if (c > 0 && matrix[r][c - 1] > val) isPeak = false;
    if (c < (int)matrix[0].size() - 1 && matrix[r][c + 1] > val) isPeak = false;
    cout << "Verified peak: " << (isPeak ? "YES" : "NO") << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// LEVEL 5: ADVANCED / ICPC
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Advanced 2D search combines binary search with prefix sums,
 parametric search, or more complex feasibility checks.
*/

// 5.1 Binary Search on Submatrix Sum condition
// Find minimum side length of square submatrix with sum ≥ target
// Uses 2D prefix sum + binary search on side length
int minSideForSum(vector<vector<int>>& matrix, int target) {
    int n = matrix.size(), m = matrix[0].size();

    // Build 2D prefix sum
    vector<vector<long long>> prefix(n + 1, vector<long long>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            prefix[i][j] = matrix[i - 1][j - 1] + prefix[i - 1][j]
                         + prefix[i][j - 1] - prefix[i - 1][j - 1];

    auto submatrixSum = [&](int r1, int c1, int r2, int c2) -> long long {
        return prefix[r2 + 1][c2 + 1] - prefix[r1][c2 + 1]
             - prefix[r2 + 1][c1] + prefix[r1][c1];
    };

    auto canAchieve = [&](int side) -> bool {
        for (int i = 0; i + side - 1 < n; i++)
            for (int j = 0; j + side - 1 < m; j++)
                if (submatrixSum(i, j, i + side - 1, j + side - 1) >= target)
                    return true;
        return false;
    };

    int lo = 1, hi = min(n, m);
    if (!canAchieve(hi)) return -1; // Impossible

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (canAchieve(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

// 5.2 Count submatrices with sum ≤ target (using BS)
int countSubmatricesWithSumLeq(vector<vector<int>>& matrix, int target) {
    int n = matrix.size(), m = matrix[0].size();
    int count = 0;

    // Fix top and bottom rows, compress to 1D, use prefix sum
    for (int top = 0; top < n; top++) {
        vector<long long> colSum(m, 0);
        for (int bottom = top; bottom < n; bottom++) {
            for (int j = 0; j < m; j++)
                colSum[j] += matrix[bottom][j];

            // Now find subarrays with sum ≤ target in colSum
            // Using prefix sum + binary search or two pointers
            // (Simplified: for positive values, sliding window)
            long long prefSum = 0;
            vector<long long> prefix = {0};
            for (int j = 0; j < m; j++) {
                prefSum += colSum[j];
                // Count previous prefix sums ≥ prefSum - target
                int pos = lower_bound(prefix.begin(), prefix.end(), prefSum - target) - prefix.begin();
                count += pos;
                // Insert prefSum maintaining sorted order
                auto it = lower_bound(prefix.begin(), prefix.end(), prefSum);
                prefix.insert(it, prefSum);
            }
        }
    }
    return count;
}

// 5.3 Kth smallest sum from two sorted arrays using BS
// Given two sorted arrays, find kth smallest pairwise sum
long long kthSmallestPairSum(vector<int>& a, vector<int>& b, int k) {
    long long lo = (long long)a[0] + b[0];
    long long hi = (long long)a.back() + b.back();

    auto countLeq = [&](long long x) -> long long {
        long long cnt = 0;
        for (int i = 0; i < (int)a.size(); i++) {
            // Count b[j] such that a[i] + b[j] <= x → b[j] <= x - a[i]
            long long target = x - a[i];
            cnt += upper_bound(b.begin(), b.end(), (int)target) - b.begin();
        }
        return cnt;
    };

    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (countLeq(mid) < k) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

void demo_level5() {
    cout << "=== LEVEL 5: ADVANCED / ICPC ===" << endl;

    // Min side for sum
    vector<vector<int>> matrix = {
        {1, 1, 3, 2, 4, 3, 2},
        {1, 1, 3, 2, 4, 3, 2},
        {1, 1, 3, 2, 4, 3, 2}
    };
    int target = 4;
    int side = minSideForSum(matrix, target);
    cout << "Min square side for sum ≥ " << target << ": " << side << endl;

    // Kth smallest pair sum
    vector<int> a = {1, 7, 11};
    vector<int> b = {2, 4, 6};
    int k = 3;
    cout << "Kth smallest pair sum (k=" << k << "): "
         << kthSmallestPairSum(a, b, k) << endl; // 1+4=5? Let's see: (1,2)=3, (1,4)=5, (1,6)=7... k=3 → 7? No: (1,2)=3, (1,4)=5, (7,2)=9...
    // Sorted sums: 3, 5, 7, 9, 11, 13 → k=3 is 7

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║   CHAPTER 08: 2D SEARCHING & BINARY SEARCH                  ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;

    demo_level1();
    demo_level2();
    demo_level3();
    demo_level4();
    demo_level5();

    cout << "═══════════════════════════════════════════════════════════════" << endl;
    cout << "All Chapter 08 demos completed successfully!" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                         PRACTICE PROBLEMS                                  ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                            ║
║  🟢 EASY (Level 1):                                                       ║
║  1. Search a 2D Matrix (LC 74)                                             ║
║  2. Search a 2D Matrix II (LC 240)                                         ║
║                                                                            ║
║  🟡 MEDIUM (Level 2-3):                                                   ║
║  3. Kth Smallest Element in Sorted Matrix (LC 378)                         ║
║  4. Find K Pairs with Smallest Sums (LC 373)                               ║
║  5. Count Negative Numbers in Sorted Matrix (LC 1351)                      ║
║  6. Median in Row-wise Sorted Matrix (GFG)                                 ║
║                                                                            ║
║  🔴 HARD (Level 4):                                                       ║
║  7. Find Peak Element in 2D (custom)                                       ║
║  8. Kth Smallest Number in Multiplication Table (LC 668)                   ║
║  9. Smallest Rectangle Enclosing Black Pixels (LC 302)                     ║
║                                                                            ║
║  🔵 GRANDMASTER (Level 5):                                                ║
║ 10. Max Sum Submatrix No Larger Than K (LC 363)                            ║
║ 11. Number of Submatrices That Sum to Target (LC 1074)                     ║
║ 12. CF 1300E — Water Balance (parametric + 2D)                             ║
║ 13. ICPC Regional — Matrix binary search problems                          ║
║                                                                            ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

