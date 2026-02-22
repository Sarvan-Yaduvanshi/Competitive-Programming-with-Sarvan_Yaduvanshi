/*
 * ============================================================================
 *          PREFIX SUM ON 2D MATRIX - ZERO TO GM MASTERY
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Topic   : 2D Prefix Sum, Submatrix Sum Queries, Difference Array 2D
 * Level   : 0 (Beginner) → 7 (GM)
 * ============================================================================
 *
 *  TABLE OF CONTENTS
 *  ─────────────────
 *  Level 0 : Brute Force Submatrix Sum O(N²×M²)
 *  Level 1 : 1D Prefix Sum Recap
 *  Level 2 : 2D Prefix Sum Construction O(N×M)
 *  Level 3 : Submatrix Sum Query O(1) [LC #304]
 *  Level 4 : Inclusion-Exclusion Principle (Visual)
 *  Level 5 : Count Submatrices with Sum = K [LC #1074]
 *  Level 6 : 2D Difference Array (Range Update)
 *  Level 7 : Maximum Sum Submatrix (Kadane 2D)
 *
 * ============================================================================
 *  2D PREFIX SUM FORMULA:
 *  ┌────────────────────────────────────────────────────────────────┐
 *  │  BUILD:                                                        │
 *  │  pre[i][j] = mat[i][j]                                       │
 *  │            + pre[i-1][j] + pre[i][j-1]                       │
 *  │            - pre[i-1][j-1]                                     │
 *  │                                                                │
 *  │  QUERY (sum of submatrix from (r1,c1) to (r2,c2)):           │
 *  │  sum = pre[r2][c2]                                             │
 *  │      - pre[r1-1][c2] - pre[r2][c1-1]                         │
 *  │      + pre[r1-1][c1-1]                                        │
 *  └────────────────────────────────────────────────────────────────┘
 *
 *  INCLUSION-EXCLUSION VISUAL:
 *
 *  ┌───────────────────────┐
 *  │ A │        B          │
 *  │───┼───────────────────│  pre[r2][c2] = Full rectangle
 *  │   │ Target            │  - B area (above target)
 *  │ C │ Region  █████████ │  - C area (left of target)
 *  │   │         █████████ │  + A area (double-subtracted)
 *  └───────────────────────┘
 *
 *  Related Problems:
 *  - LC #304:  Range Sum Query 2D - Immutable
 *  - LC #1074: Number of Submatrices That Sum to Target
 *  - LC #363:  Max Sum of Rectangle No Larger Than K
 * ============================================================================
 *  Time: O(N×M) to build, O(1) per query
 *  Space: O(N×M) for prefix sum array
 * ============================================================================
 */

#include <bits/stdc++.h>
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
// LEVEL 0: BRUTE FORCE SUBMATRIX SUM  O(N² × M²)
// ─────────────────────────────────────────────────────────────────────────────
int bruteForceSubmatrixSum(const vector<vector<int>>& mat,
                            int r1, int c1, int r2, int c2) {
    int sum = 0;
    for (int i = r1; i <= r2; i++)
        for (int j = c1; j <= c2; j++)
            sum += mat[i][j];
    return sum;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 1: 1D PREFIX SUM RECAP
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  arr:    [1, 2, 3, 4, 5]
 *  prefix: [0, 1, 3, 6, 10, 15]  (1-indexed, prefix[0] = 0)
 *
 *  Sum of arr[l..r] = prefix[r+1] - prefix[l]
 *
 *  This concept extends to 2D!
 */
void prefixSum1DRecap() {
    cout << "=== 1D Prefix Sum Recap ===" << endl;
    vector<int> arr = {1, 2, 3, 4, 5};
    int n = arr.size();
    vector<int> prefix(n + 1, 0);

    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + arr[i];

    cout << "Array:  ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    cout << "Prefix: ";
    for (int x : prefix) cout << x << " ";
    cout << endl;

    // Query: sum of arr[1..3] = prefix[4] - prefix[1] = 10 - 1 = 9
    cout << "Sum[1..3] = " << prefix[4] - prefix[1] << endl << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 2: 2D PREFIX SUM CONSTRUCTION
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Using 1-indexed prefix sum (easier boundary handling):
 *
 *  pre[i][j] = sum of all elements in submatrix from (0,0) to (i-1,j-1)
 *
 *  Build formula:
 *  pre[i][j] = mat[i-1][j-1] + pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1]
 *
 *  Example:
 *  mat:          pre (1-indexed):
 *  1  2  3       0  0  0  0
 *  4  5  6       0  1  3  6
 *  7  8  9       0  5  12 21
 *                0  12 27 45
 */
vector<vector<long long>> build2DPrefixSum(const vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    // 1-indexed: (n+1) × (m+1), first row/col are zeros
    vector<vector<long long>> pre(n + 1, vector<long long>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            pre[i][j] = mat[i-1][j-1]
                       + pre[i-1][j]
                       + pre[i][j-1]
                       - pre[i-1][j-1];
        }
    }

    return pre;
}

void buildDemo() {
    cout << "=== Build 2D Prefix Sum ===" << endl;
    vector<vector<int>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    printMatrix(mat, "Original");

    auto pre = build2DPrefixSum(mat);
    cout << "Prefix Sum (1-indexed):" << endl;
    for (auto& row : pre) {
        for (long long val : row) cout << setw(5) << val;
        cout << "\n";
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 3: SUBMATRIX SUM QUERY O(1) — LC #304
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Query: Sum of submatrix from (r1, c1) to (r2, c2) in ORIGINAL matrix
 *
 *  Using 1-indexed prefix sum:
 *  sum = pre[r2+1][c2+1]
 *      - pre[r1][c2+1]
 *      - pre[r2+1][c1]
 *      + pre[r1][c1]
 *
 *  This is the INCLUSION-EXCLUSION principle!
 */
class NumMatrix {
    vector<vector<long long>> pre;
public:
    NumMatrix(const vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        pre.assign(n + 1, vector<long long>(m + 1, 0));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                pre[i][j] = matrix[i-1][j-1] + pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
    }

    // Sum of submatrix from (r1, c1) to (r2, c2) — 0-indexed in original
    long long sumRegion(int r1, int c1, int r2, int c2) {
        return pre[r2+1][c2+1] - pre[r1][c2+1] - pre[r2+1][c1] + pre[r1][c1];
    }
};

void queryDemo() {
    cout << "=== Submatrix Sum Query O(1) — LC #304 ===" << endl;
    vector<vector<int>> mat = {
        {3, 0, 1, 4, 2},
        {5, 6, 3, 2, 1},
        {1, 2, 0, 1, 5},
        {4, 1, 0, 1, 7},
        {1, 0, 3, 0, 5}
    };
    printMatrix(mat, "Matrix");

    NumMatrix nm(mat);

    // Query 1: (2,1) to (4,3)
    cout << "Sum[(2,1)→(4,3)] = " << nm.sumRegion(2, 1, 4, 3) << endl;
    cout << "  Expected: 2+0+1 + 1+0+1 + 0+3+0 = 8" << endl;

    // Query 2: (1,1) to (2,2)
    cout << "Sum[(1,1)→(2,2)] = " << nm.sumRegion(1, 1, 2, 2) << endl;
    cout << "  Expected: 6+3 + 2+0 = 11" << endl;

    // Query 3: (1,2) to (2,4)
    cout << "Sum[(1,2)→(2,4)] = " << nm.sumRegion(1, 2, 2, 4) << endl;
    cout << "  Expected: 3+2+1 + 0+1+5 = 12" << endl;

    // Verify with brute force
    cout << "\nBrute force verification:" << endl;
    cout << "BF Sum[(2,1)→(4,3)] = " << bruteForceSubmatrixSum(mat, 2, 1, 4, 3) << endl;
    cout << "BF Sum[(1,1)→(2,2)] = " << bruteForceSubmatrixSum(mat, 1, 1, 2, 2) << endl;
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 4: INCLUSION-EXCLUSION STEP-BY-STEP
// ─────────────────────────────────────────────────────────────────────────────
void inclusionExclusionDemo() {
    cout << "=== Inclusion-Exclusion Step by Step ===" << endl;
    cout << R"(
  For query sum(r1=1, c1=1, r2=2, c2=2) in 0-indexed:

  Full rectangle pre[3][3]:     Subtract top pre[1][3]:
  ┌─────────────────┐           ┌─────────────────┐
  │ X  X  X         │           │ X  X  X         │
  │ X  ██ ██        │           │                  │
  │ X  ██ ██        │    -      │                  │
  └─────────────────┘           └─────────────────┘

  Subtract left pre[3][1]:      Add back corner pre[1][1]:
  ┌─────────────────┐           ┌─────────────────┐
  │ X               │           │ X               │
  │ X               │    +      │                  │
  │ X               │           │                  │
  └─────────────────┘           └─────────────────┘

  Formula: pre[r2+1][c2+1] - pre[r1][c2+1] - pre[r2+1][c1] + pre[r1][c1]
)" << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 5: COUNT SUBMATRICES WITH SUM = TARGET — LC #1074
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Count number of non-empty submatrices that sum to target.
 *
 *  Approach: Fix top and bottom rows, compress columns using prefix sum,
 *  then use 1D "subarray sum equals K" technique with hashmap.
 *
 *  Time: O(N² × M), Space: O(M)
 *
 *  This is the 2D extension of LC #560 (Subarray Sum Equals K)!
 */
int numSubmatrixSumTarget(const vector<vector<int>>& matrix, int target) {
    cout << "=== Count Submatrices with Sum = " << target << " (LC #1074) ===" << endl;
    int n = matrix.size(), m = matrix[0].size();
    int count = 0;

    // Prefix sum for each row
    vector<vector<int>> rowPrefix(n, vector<int>(m + 1, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            rowPrefix[i][j + 1] = rowPrefix[i][j] + matrix[i][j];

    // Fix left and right column boundaries
    for (int c1 = 0; c1 < m; c1++) {
        for (int c2 = c1; c2 < m; c2++) {
            // Compress into 1D: sum of row i from c1 to c2
            unordered_map<int, int> prefMap;
            prefMap[0] = 1;
            int runSum = 0;

            for (int i = 0; i < n; i++) {
                runSum += rowPrefix[i][c2 + 1] - rowPrefix[i][c1];
                if (prefMap.count(runSum - target))
                    count += prefMap[runSum - target];
                prefMap[runSum]++;
            }
        }
    }

    cout << "Count = " << count << "\n\n";
    return count;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 6: 2D DIFFERENCE ARRAY (RANGE UPDATE)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Apply multiple range updates on a 2D matrix efficiently.
 *
 *  Problem: Given N×M matrix (initially 0), perform Q updates:
 *  "Add val to all elements in submatrix (r1,c1) to (r2,c2)"
 *
 *  Brute force per update: O(N×M)
 *  With difference array: O(1) per update, O(N×M) to reconstruct
 *
 *  2D Difference Array Update:
 *  diff[r1][c1]     += val
 *  diff[r1][c2+1]   -= val
 *  diff[r2+1][c1]   -= val
 *  diff[r2+1][c2+1] += val
 *
 *  Reconstruction: Apply 2D prefix sum on diff array
 */
class DiffArray2D {
    int n, m;
    vector<vector<long long>> diff;
public:
    DiffArray2D(int rows, int cols) : n(rows), m(cols) {
        diff.assign(n + 2, vector<long long>(m + 2, 0)); // Extra space for boundaries
    }

    // Add val to submatrix (r1,c1) to (r2,c2) — 0-indexed
    void update(int r1, int c1, int r2, int c2, long long val) {
        diff[r1][c1] += val;
        diff[r1][c2 + 1] -= val;
        diff[r2 + 1][c1] -= val;
        diff[r2 + 1][c2 + 1] += val;
    }

    // Build final matrix after all updates
    vector<vector<long long>> build() {
        vector<vector<long long>> result(n, vector<long long>(m));

        // Apply 2D prefix sum on diff
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (i > 0) diff[i][j] += diff[i-1][j];
                if (j > 0) diff[i][j] += diff[i][j-1];
                if (i > 0 && j > 0) diff[i][j] -= diff[i-1][j-1];
                result[i][j] = diff[i][j];
            }

        return result;
    }
};

void diffArray2DDemo() {
    cout << "=== 2D Difference Array Demo ===" << endl;
    int n = 4, m = 5;
    DiffArray2D da(n, m);

    // Update 1: Add 5 to (1,1)→(2,3)
    da.update(1, 1, 2, 3, 5);
    cout << "Update: Add 5 to (1,1)→(2,3)" << endl;

    // Update 2: Add 3 to (0,0)→(3,4)
    da.update(0, 0, 3, 4, 3);
    cout << "Update: Add 3 to (0,0)→(3,4)" << endl;

    // Update 3: Add -2 to (2,2)→(3,3)
    da.update(2, 2, 3, 3, -2);
    cout << "Update: Add -2 to (2,2)→(3,3)" << endl;

    auto result = da.build();
    cout << "Final matrix:" << endl;
    for (auto& row : result) {
        for (long long val : row) cout << setw(4) << val;
        cout << "\n";
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// LEVEL 7: MAXIMUM SUM SUBMATRIX (2D KADANE'S)
// ─────────────────────────────────────────────────────────────────────────────
/*
 *  Find the submatrix with the maximum sum.
 *  Extension of Kadane's algorithm to 2D.
 *
 *  Approach:
 *  1. Fix left and right column boundaries (O(M²))
 *  2. Compress rows into 1D array (column sums)
 *  3. Apply 1D Kadane's on the compressed array
 *
 *  Time: O(N × M²), Space: O(N)
 */

// 1D Kadane's Algorithm
struct KadaneResult {
    long long maxSum;
    int start, end;
};

KadaneResult kadane1D(const vector<long long>& arr) {
    long long maxSum = LLONG_MIN, curSum = 0;
    int start = 0, end = 0, tempStart = 0;

    for (int i = 0; i < (int)arr.size(); i++) {
        curSum += arr[i];
        if (curSum > maxSum) {
            maxSum = curSum;
            start = tempStart;
            end = i;
        }
        if (curSum < 0) {
            curSum = 0;
            tempStart = i + 1;
        }
    }
    return {maxSum, start, end};
}

void maxSumSubmatrix(const vector<vector<int>>& mat) {
    cout << "=== Maximum Sum Submatrix (2D Kadane's) ===" << endl;
    int n = mat.size(), m = mat[0].size();
    printMatrix(mat, "Matrix");

    long long globalMax = LLONG_MIN;
    int bestR1 = 0, bestC1 = 0, bestR2 = 0, bestC2 = 0;

    // Fix left column
    for (int left = 0; left < m; left++) {
        vector<long long> colSum(n, 0); // Compressed column sums

        // Expand right column
        for (int right = left; right < m; right++) {
            // Add column 'right' to colSum
            for (int i = 0; i < n; i++)
                colSum[i] += mat[i][right];

            // Apply 1D Kadane's
            auto [maxSum, topRow, bottomRow] = kadane1D(colSum);

            if (maxSum > globalMax) {
                globalMax = maxSum;
                bestR1 = topRow;
                bestC1 = left;
                bestR2 = bottomRow;
                bestC2 = right;
            }
        }
    }

    cout << "Maximum sum = " << globalMax << endl;
    cout << "Submatrix: (" << bestR1 << "," << bestC1 << ") to ("
         << bestR2 << "," << bestC2 << ")" << endl;

    cout << "Submatrix elements:" << endl;
    for (int i = bestR1; i <= bestR2; i++) {
        for (int j = bestC1; j <= bestC2; j++)
            cout << setw(4) << mat[i][j];
        cout << endl;
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
    cout << "║   PREFIX SUM 2D MATRIX - ZERO TO GM MASTERY     ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << endl;

    // Level 1: 1D Recap
    prefixSum1DRecap();

    // Level 2: Build 2D Prefix Sum
    buildDemo();

    // Level 3: Query O(1) — LC #304
    queryDemo();

    // Level 4: Inclusion-Exclusion
    inclusionExclusionDemo();

    // Level 5: Count Submatrices — LC #1074
    vector<vector<int>> mat5 = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 1, 0}
    };
    printMatrix(mat5, "Matrix for LC #1074");
    numSubmatrixSumTarget(mat5, 0);
    numSubmatrixSumTarget(mat5, 1);
    numSubmatrixSumTarget(mat5, 3);

    // Level 6: 2D Difference Array
    diffArray2DDemo();

    // Level 7: Max Sum Submatrix (2D Kadane)
    vector<vector<int>> mat7 = {
        {1,   2, -1, -4, -20},
        {-8, -3,  4,  2,   1},
        {3,   8, 10,  1,   3},
        {-4, -1,  1,  7,  -6}
    };
    maxSumSubmatrix(mat7);

    return 0;
}

