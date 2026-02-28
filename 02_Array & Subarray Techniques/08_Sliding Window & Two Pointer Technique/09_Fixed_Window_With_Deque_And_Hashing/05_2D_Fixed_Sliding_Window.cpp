/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : 2D Fixed Sliding Window (Matrix Window Problems)
 *  Level   : Medium → Hard (CF 1800 → 2200)
 * ============================================================================
 *
 *  ▶ CORE IDEA:
 *  ────────────
 *  Extend 1D fixed window to 2D:
 *  1. k×k submatrix SUM → 2D prefix sum, query in O(1)
 *  2. k×k submatrix MAX → Fix column range, slide row deques
 *  3. k×k submatrix OPERATIONS → Combine row-wise sliding windows
 *
 *  ▶ 2D PREFIX SUM:
 *  ────────────────
 *  prefix[i][j] = sum of rectangle [0,0] to [i-1,j-1]
 *  Sum of [r1,c1] to [r2,c2] =
 *    prefix[r2+1][c2+1] - prefix[r1][c2+1] - prefix[r2+1][c1] + prefix[r1][c1]
 *
 *  ▶ 2D SLIDING WINDOW MAX (k×k):
 *  ──────────────────────────────
 *  Step 1: For each row, compute sliding window max of size k → rowMax[i][j]
 *  Step 2: For each column of rowMax, compute sliding window max of size k
 *  Result: 2D sliding window maximum in O(M*N)
 *
 *  PROBLEMS:
 *  LC 1895 — Largest Magic Square (prefix 2D + fixed window check)
 *            https://leetcode.com/problems/largest-magic-square/
 *  LC 1074 — Number of Submatrices That Sum to Target (2D prefix + hashmap)
 *            https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/
 *  LC 363  — Max Sum of Rectangle No Larger Than K (2D prefix + set)
 *            https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/
 *  LC 304  — Range Sum Query 2D (2D prefix sum template)
 *            https://leetcode.com/problems/range-sum-query-2d-immutable/
 *  CF 1195D2 — Submarine in the Rybinsk Sea (2D math, 1800)
 *            https://codeforces.com/problemset/problem/1195/D2
 *  GFG      — Maximum sum rectangle of size k×k
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <climits>
#include <set>
using namespace std;
using ll = long long;

// ============================================================================
// 2D Prefix Sum — Build O(M*N), Query O(1)
// ============================================================================
struct PrefixSum2D {
    vector<vector<ll>> prefix;

    void build(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        prefix.assign(m + 1, vector<ll>(n + 1, 0));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                prefix[i+1][j+1] = grid[i][j] + prefix[i][j+1]
                                    + prefix[i+1][j] - prefix[i][j];
    }

    // Sum of rectangle [r1,c1] to [r2,c2] (0-indexed, inclusive)
    ll query(int r1, int c1, int r2, int c2) {
        return prefix[r2+1][c2+1] - prefix[r1][c2+1]
               - prefix[r2+1][c1] + prefix[r1][c1];
    }
};

// ============================================================================
// k×k Submatrix Sum — All windows using 2D prefix sum
// ============================================================================
vector<vector<ll>> allKxKSums(vector<vector<int>>& grid, int k) {
    PrefixSum2D ps;
    ps.build(grid);
    int m = grid.size(), n = grid[0].size();
    vector<vector<ll>> result;

    for (int i = 0; i + k - 1 < m; i++) {
        vector<ll> row;
        for (int j = 0; j + k - 1 < n; j++)
            row.push_back(ps.query(i, j, i + k - 1, j + k - 1));
        result.push_back(row);
    }
    return result;
}

// Max k×k submatrix sum
ll maxKxKSum(vector<vector<int>>& grid, int k) {
    auto sums = allKxKSums(grid, k);
    ll best = LLONG_MIN;
    for (auto& row : sums)
        for (ll x : row)
            best = max(best, x);
    return best;
}

// ============================================================================
// 2D Sliding Window Maximum (k×k) — Two-Pass Deque Approach
// ============================================================================
/*
 * Step 1: For each row, compute sliding window max of size k horizontally.
 *         Store in rowMax[i][j] = max of row i, columns [j..j+k-1].
 * Step 2: For each column of rowMax, compute sliding window max of size k vertically.
 *         This gives the k×k window max.
 *
 * Time: O(M*N), Space: O(M*N)
 */
vector<vector<int>> slidingWindowMax2D(vector<vector<int>>& grid, int k) {
    int m = grid.size(), n = grid[0].size();

    // Step 1: Horizontal sliding window max (size k) for each row
    vector<vector<int>> rowMax(m);
    for (int i = 0; i < m; i++) {
        deque<int> dq;
        for (int j = 0; j < n; j++) {
            while (!dq.empty() && dq.front() <= j - k) dq.pop_front();
            while (!dq.empty() && grid[i][dq.back()] <= grid[i][j]) dq.pop_back();
            dq.push_back(j);
            if (j >= k - 1) rowMax[i].push_back(grid[i][dq.front()]);
        }
    }

    // Step 2: Vertical sliding window max (size k) on rowMax
    int cols = n - k + 1;
    vector<vector<int>> result;
    for (int j = 0; j < cols; j++) {
        deque<int> dq;
        for (int i = 0; i < m; i++) {
            while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
            while (!dq.empty() && rowMax[dq.back()][j] <= rowMax[i][j]) dq.pop_back();
            dq.push_back(i);
            if (i >= k - 1) {
                if ((int)result.size() <= i - k + 1) result.push_back(vector<int>());
                result[i - k + 1].push_back(rowMax[dq.front()][j]);
            }
        }
    }
    return result;
}

// ============================================================================
// LC 363: Max Sum of Rectangle No Larger Than K — 2D Prefix + Set
// ============================================================================
/*
 * Find rectangle with max sum ≤ K.
 * Fix left and right column boundaries. Compute row prefix sums.
 * Use an ordered set to find max prefix diff ≤ K (like "max subarray ≤ K").
 *
 * Time: O(N² * M * log M) for M rows, N cols (optimize by choosing smaller dimension)
 */
int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
    int m = matrix.size(), n = matrix[0].size();
    int best = INT_MIN;

    for (int left = 0; left < n; left++) {
        vector<int> rowSum(m, 0);
        for (int right = left; right < n; right++) {
            for (int i = 0; i < m; i++)
                rowSum[i] += matrix[i][right];

            // Find max subarray sum ≤ k in rowSum
            set<int> prefixSet;
            prefixSet.insert(0);
            int prefix = 0;
            for (int i = 0; i < m; i++) {
                prefix += rowSum[i];
                // Want max (prefix - prev) ≤ k → prev ≥ prefix - k
                auto it = prefixSet.lower_bound(prefix - k);
                if (it != prefixSet.end())
                    best = max(best, prefix - *it);
                prefixSet.insert(prefix);
            }
        }
    }
    return best;
}

int main() {
    vector<vector<int>> grid = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    // k×k sum windows
    auto sums = allKxKSums(grid, 2);
    cout << "2x2 sums:\n";
    for (auto& row : sums) {
        for (ll x : row) cout << x << " ";
        cout << "\n";
    }
    // 14 18 22
    // 30 34 38

    // Max 2x2 sum
    cout << "Max 2x2 sum: " << maxKxKSum(grid, 2) << "\n"; // 38

    // 2D sliding window max (2×2)
    auto maxWin = slidingWindowMax2D(grid, 2);
    cout << "2x2 max windows:\n";
    for (auto& row : maxWin) {
        for (int x : row) cout << x << " ";
        cout << "\n";
    }
    // 6 7 8
    // 10 11 12

    // Max sum rectangle ≤ K
    vector<vector<int>> mat = {{1,0,1},{0,-2,3}};
    cout << "Max sum rect ≤ 2: " << maxSumSubmatrix(mat, 2) << "\n"; // 2

    return 0;
}

