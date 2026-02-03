/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-31 15:31:59
Updated : 2026-01-31 (Complete Suffix & Difference Array Mastery)
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
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

// --- Type Definitions ---
using i64 = long long;
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

// --- Constants ---
constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;
constexpr int MAXN  = 1005;

// --- Random Number Generator ---
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// --- Macros ---
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

// Input helper
template<class T>
void read(vec<T> &v) {
    for (auto &x : v) cin >> x;
}
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

inline i64 gcd(i64 a, i64 b) { return std::gcd(a, b); }
inline i64 lcm(i64 a, i64 b) { return (a / std::gcd(a, b)) * b; }

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD) {
    i64 res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

/**
 * ==========================================
 * 🏆 GM-LEVEL ARRAY TECHNIQUES MASTERY
 * ==========================================
 *
 * This template contains:
 * 1. 1D Suffix Sum (0-based & 1-based)
 * 2. 2D Suffix Sum (0-based & 1-based)
 * 3. 1D Difference Array (0-based & 1-based)
 * 4. 2D Difference Array (0-based & 1-based)
 *
 * Time Complexity:
 * - Build: O(N) for 1D, O(N*M) for 2D
 * - Query: O(1) for suffix sum
 * - Range Update: O(1) for difference array
 *
 * Space Complexity: O(N) for 1D, O(N*M) for 2D
 */

// ==========================================
// SECTION 1: 1D SUFFIX SUM
// ==========================================

/**
 * 📚 WHAT IS SUFFIX SUM?
 * ----------------------
 * Suffix sum is the reverse of prefix sum.
 *
 * Prefix[i] = arr[0] + arr[1] + ... + arr[i]     (sum from START to i)
 * Suffix[i] = arr[i] + arr[i+1] + ... + arr[n-1]  (sum from i to END)
 *
 * 💡 USE CASES:
 * - Calculate sum from index i to end in O(1)
 * - Useful in problems where you need "sum of remaining elements"
 * - Example: "For each position, find sum of all elements to the right"
 *
 * 🔥 KEY INSIGHT:
 * Suffix sum builds BACKWARDS (from right to left)
 * Formula: suffix[i] = arr[i] + suffix[i+1]
 */

// METHOD 1.1: 0-Based Suffix Sum (LeetCode Standard)
void suffix_1d_0based() {
    int n;
    cin >> n;

    vec<i64> arr(n);
    read(arr);

    vec<i64> suffix(n);

    // Step 1: Base case - last element
    suffix[n - 1] = arr[n - 1];

    // Step 2: Build suffix sum backwards
    for (int i = n - 2; i >= 0; i--) {
        suffix[i] = arr[i] + suffix[i + 1];
    }

    // Step 3: Use suffix sum
    cout << "Original Array: ";
    for (auto x : arr) cout << x << " ";
    cout << nl;

    cout << "Suffix Sum:     ";
    for (auto x : suffix) cout << x << " ";
    cout << nl;

    // Example query: Sum from index i to end
    int idx;
    cout << "Enter index to query sum from that point to end: ";
    cin >> idx;
    if (idx >= 0 && idx < n) {
        cout << "Sum from index " << idx << " to end = " << suffix[idx] << nl;
    }
}

// METHOD 1.2: 1-Based Suffix Sum (Competitive Programming)
i64 arr_1[MAXN];
i64 suffix_1[MAXN];

void suffix_1d_1based() {
    int n;
    cin >> n;

    // Read array (1-based)
    for (int i = 1; i <= n; i++) {
        cin >> arr_1[i];
    }

    // Build suffix sum (1-based)
    suffix_1[n] = arr_1[n];

    for (int i = n - 1; i >= 1; i--) {
        suffix_1[i] = arr_1[i] + suffix_1[i + 1];
    }

    // Print
    cout << "Original Array: ";
    for (int i = 1; i <= n; i++) cout << arr_1[i] << " ";
    cout << nl;

    cout << "Suffix Sum:     ";
    for (int i = 1; i <= n; i++) cout << suffix_1[i] << " ";
    cout << nl;
}

// ==========================================
// SECTION 2: 2D SUFFIX SUM
// ==========================================

/**
 * 📚 WHAT IS 2D SUFFIX SUM?
 * -------------------------
 * 2D Suffix sum stores sum from position (i,j) to bottom-right corner (n-1, m-1)
 *
 * suffix[i][j] = sum of all elements in rectangle from (i,j) to (n-1, m-1)
 *
 * 💡 USE CASES:
 * - Calculate sum of bottom-right submatrix in O(1)
 * - Problems involving "count elements to the right and below"
 *
 * 🔥 FORMULA (2D Inclusion-Exclusion in Reverse):
 * suffix[i][j] = mat[i][j] + suffix[i+1][j] + suffix[i][j+1] - suffix[i+1][j+1]
 *
 * Why subtract suffix[i+1][j+1]?
 * Because it's counted in BOTH suffix[i+1][j] and suffix[i][j+1]
 */

// METHOD 2.1: 0-Based 2D Suffix Sum (LeetCode Standard)
void suffix_2d_0based() {
    int n, m;
    cin >> n >> m;

    vvec<i64> mat(n, vec<i64>(m));
    vvec<i64> suffix(n, vec<i64>(m, 0));

    // Read matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
        }
    }

    // Build 2D suffix sum (start from bottom-right)
    suffix[n-1][m-1] = mat[n-1][m-1];

    // Last row
    for (int j = m - 2; j >= 0; j--) {
        suffix[n-1][j] = mat[n-1][j] + suffix[n-1][j+1];
    }

    // Last column
    for (int i = n - 2; i >= 0; i--) {
        suffix[i][m-1] = mat[i][m-1] + suffix[i+1][m-1];
    }

    // Rest of the matrix
    for (int i = n - 2; i >= 0; i--) {
        for (int j = m - 2; j >= 0; j--) {
            suffix[i][j] = mat[i][j]
                         + suffix[i+1][j]      // Below
                         + suffix[i][j+1]      // Right
                         - suffix[i+1][j+1];   // Overlap (counted twice)
        }
    }

    // Print original matrix
    cout << "Original Matrix:" << nl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << mat[i][j] << " ";
        }
        cout << nl;
    }

    // Print suffix sum
    cout << nl << "2D Suffix Sum:" << nl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << suffix[i][j] << " ";
        }
        cout << nl;
    }

    // Example query: Sum from (i,j) to bottom-right
    int r, c;
    cout << nl << "Enter row and column to query sum to bottom-right: ";
    cin >> r >> c;
    if (r >= 0 && r < n && c >= 0 && c < m) {
        cout << "Sum from (" << r << "," << c << ") to bottom-right = "
             << suffix[r][c] << nl;
    }
}

// METHOD 2.2: 1-Based 2D Suffix Sum (Competitive Programming)
i64 mat_2[MAXN][MAXN];
i64 suffix_2[MAXN][MAXN];

void suffix_2d_1based() {
    int n, m;
    cin >> n >> m;

    // Read matrix (1-based)
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mat_2[i][j];
        }
    }

    // Build 2D suffix sum (1-based)
    // Base case: bottom-right corner
    suffix_2[n][m] = mat_2[n][m];

    // Last row
    for (int j = m - 1; j >= 1; j--) {
        suffix_2[n][j] = mat_2[n][j] + suffix_2[n][j+1];
    }

    // Last column
    for (int i = n - 1; i >= 1; i--) {
        suffix_2[i][m] = mat_2[i][m] + suffix_2[i+1][m];
    }

    // Rest of the matrix
    for (int i = n - 1; i >= 1; i--) {
        for (int j = m - 1; j >= 1; j--) {
            suffix_2[i][j] = mat_2[i][j]
                           + suffix_2[i+1][j]
                           + suffix_2[i][j+1]
                           - suffix_2[i+1][j+1];
        }
    }

    // Print
    cout << "Original Matrix:" << nl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << mat_2[i][j] << " ";
        }
        cout << nl;
    }

    cout << nl << "2D Suffix Sum:" << nl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << suffix_2[i][j] << " ";
        }
        cout << nl;
    }
}

// ==========================================
// SECTION 3: 1D DIFFERENCE ARRAY
// ==========================================

/**
 * 📚 WHAT IS DIFFERENCE ARRAY?
 * ----------------------------
 * Difference array is used for RANGE UPDATES in O(1) time.
 *
 * Problem: You have Q queries, each adds 'val' to range [L, R]
 * Naive: O(Q * N) → TLE for large inputs
 * Difference Array: O(Q + N) → FAST!
 *
 * 💡 HOW IT WORKS:
 * 1. Create diff[] array
 * 2. For update [L, R] with value 'val':
 *    - diff[L] += val      (start of range)
 *    - diff[R+1] -= val    (end of range + 1)
 * 3. After all updates, compute prefix sum of diff[] to get final array
 *
 * 🔥 INTUITION:
 * Think of it like a "waterfall effect"
 * - Adding at L creates a +val "step up"
 * - Subtracting at R+1 creates a "step down" back to normal
 * - Prefix sum propagates the effect through the range
 *
 * 💡 USE CASES:
 * - Multiple range additions/subtractions
 * - Sweep line algorithms
 * - Example: LeetCode 1109 - Corporate Flight Bookings
 */

// METHOD 3.1: 0-Based Difference Array (LeetCode Standard)
void difference_1d_0based() {
    int n;
    cin >> n;

    vec<i64> arr(n, 0);     // Original array (initialized to 0)
    vec<i64> diff(n + 1, 0); // Difference array (extra space to avoid bounds check)

    // Process Q range update queries
    int q;
    cout << "Enter number of range update queries: ";
    cin >> q;

    cout << "Enter queries in format: L R val (add 'val' to range [L, R])" << nl;

    for (int i = 0; i < q; i++) {
        int L, R;
        i64 val;
        cin >> L >> R >> val;

        // Range update [L, R] with value 'val'
        diff[L] += val;        // Start of range
        diff[R + 1] -= val;    // End of range + 1
    }

    // Compute final array using prefix sum
    arr[0] = diff[0];
    for (int i = 1; i < n; i++) {
        arr[i] = arr[i - 1] + diff[i];
    }

    // Print result
    cout << "Final Array after all range updates:" << nl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << nl;
}

// METHOD 3.2: 1-Based Difference Array (Competitive Programming)
i64 diff_1[MAXN];
i64 result_1[MAXN];

void difference_1d_1based() {
    int n;
    cin >> n;

    // Process Q range update queries
    int q;
    cout << "Enter number of range update queries: ";
    cin >> q;

    cout << "Enter queries in format: L R val (1-based indices)" << nl;

    for (int i = 0; i < q; i++) {
        int L, R;
        i64 val;
        cin >> L >> R >> val;

        // Range update [L, R] with value 'val' (1-based)
        diff_1[L] += val;
        diff_1[R + 1] -= val;
    }

    // Compute final array using prefix sum (1-based)
    result_1[1] = diff_1[1];
    for (int i = 2; i <= n; i++) {
        result_1[i] = result_1[i - 1] + diff_1[i];
    }

    // Print result
    cout << "Final Array after all range updates:" << nl;
    for (int i = 1; i <= n; i++) {
        cout << result_1[i] << " ";
    }
    cout << nl;
}

// ==========================================
// SECTION 4: 2D DIFFERENCE ARRAY
// ==========================================

/**
 * 📚 WHAT IS 2D DIFFERENCE ARRAY?
 * -------------------------------
 * Extension of 1D difference array to 2D grid.
 * Used for RECTANGLE RANGE UPDATES in O(1) time.
 *
 * Problem: Add 'val' to all cells in rectangle (r1,c1) to (r2,c2)
 * Naive: O(Q * rows * cols) → TLE
 * 2D Difference: O(Q + rows*cols) → FAST!
 *
 * 💡 HOW IT WORKS:
 * For rectangle (r1,c1) to (r2,c2) with value 'val':
 * 1. diff[r1][c1] += val           (top-left: start effect)
 * 2. diff[r1][c2+1] -= val         (top-right + 1: stop horizontal)
 * 3. diff[r2+1][c1] -= val         (bottom-left + 1: stop vertical)
 * 4. diff[r2+1][c2+1] += val       (bottom-right + 1: restore)
 *
 * 🔥 VISUAL EXPLANATION:
 *
 *     c1    c2  c2+1
 *      ↓     ↓    ↓
 * r1 → +val  ...  -val
 *      ...   ✅   ...
 * r2 → ...   ✅   ...
 * r2+1 -val  ...  +val
 *
 * After updates, compute 2D prefix sum to get final matrix.
 *
 * 💡 USE CASES:
 * - Multiple rectangle updates on grid
 * - Example: LeetCode 2536 - Increment Submatrices by One
 * - Competitive Programming: Range updates on 2D arrays
 */

// METHOD 4.1: 0-Based 2D Difference Array (LeetCode Standard)
void difference_2d_0based() {
    int n, m;
    cin >> n >> m;

    vvec<i64> grid(n, vec<i64>(m, 0));           // Original grid
    vvec<i64> diff(n + 1, vec<i64>(m + 1, 0));  // Difference array (extra space)

    // Process Q rectangle update queries
    int q;
    cout << "Enter number of rectangle update queries: ";
    cin >> q;

    cout << "Enter queries: r1 c1 r2 c2 val (add 'val' to rectangle)" << nl;

    for (int i = 0; i < q; i++) {
        int r1, c1, r2, c2;
        i64 val;
        cin >> r1 >> c1 >> r2 >> c2 >> val;

        // Rectangle update [r1,c1] to [r2,c2] with value 'val'
        diff[r1][c1] += val;           // Top-left
        diff[r1][c2 + 1] -= val;       // Top-right + 1
        diff[r2 + 1][c1] -= val;       // Bottom-left + 1
        diff[r2 + 1][c2 + 1] += val;   // Bottom-right + 1
    }

    // Compute final grid using 2D prefix sum
    // First, compute prefix sum row-wise
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j > 0) {
                diff[i][j] += diff[i][j - 1];
            }
        }
    }

    // Then, compute prefix sum column-wise
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i > 0) {
                diff[i][j] += diff[i - 1][j];
            }
            grid[i][j] = diff[i][j];
        }
    }

    // Print final grid
    cout << "Final Grid after all rectangle updates:" << nl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << grid[i][j] << " ";
        }
        cout << nl;
    }
}

// METHOD 4.2: 1-Based 2D Difference Array (Competitive Programming)
i64 diff_2d[MAXN][MAXN];
i64 grid_2d[MAXN][MAXN];

void difference_2d_1based() {
    int n, m;
    cin >> n >> m;

    // Process Q rectangle update queries
    int q;
    cout << "Enter number of rectangle update queries: ";
    cin >> q;

    cout << "Enter queries: r1 c1 r2 c2 val (1-based indices)" << nl;

    for (int i = 0; i < q; i++) {
        int r1, c1, r2, c2;
        i64 val;
        cin >> r1 >> c1 >> r2 >> c2 >> val;

        // Rectangle update [r1,c1] to [r2,c2] with value 'val' (1-based)
        diff_2d[r1][c1] += val;
        diff_2d[r1][c2 + 1] -= val;
        diff_2d[r2 + 1][c1] -= val;
        diff_2d[r2 + 1][c2 + 1] += val;
    }

    // Compute final grid using 2D prefix sum (1-based)
    // Row-wise prefix
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            diff_2d[i][j] += diff_2d[i][j - 1];
        }
    }

    // Column-wise prefix
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            diff_2d[i][j] += diff_2d[i - 1][j];
            grid_2d[i][j] = diff_2d[i][j];
        }
    }

    // Print final grid
    cout << "Final Grid after all rectangle updates:" << nl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << grid_2d[i][j] << " ";
        }
        cout << nl;
    }
}

// ==========================================
// MAIN FUNCTION - CHOOSE YOUR METHOD
// ==========================================

void solve() {
    // Uncomment the method you want to test:

    // 1D Suffix Sum
    // suffix_1d_0based();
    // suffix_1d_1based();

    // 2D Suffix Sum
    // suffix_2d_0based();
    // suffix_2d_1based();

    // 1D Difference Array
    // difference_1d_0based();
    // difference_1d_1based();

    // 2D Difference Array
    // difference_2d_0based();
    // difference_2d_1based();

    cout << "Choose a method to run (uncomment in solve() function)" << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    solve();

    return 0;
}

/*
 * ==========================================
 * 📚 COMPLETE FORMULA CHEATSHEET
 * ==========================================
 *
 * ┌──────────────────────────────────────────────────────────────┐
 * │ 1️⃣ 1D SUFFIX SUM                                            │
 * └──────────────────────────────────────────────────────────────┘
 *
 * BUILD (0-based):
 * ----------------
 * suffix[n-1] = arr[n-1];
 * for (int i = n-2; i >= 0; i--)
 *     suffix[i] = arr[i] + suffix[i+1];
 *
 * BUILD (1-based):
 * ----------------
 * suffix[n] = arr[n];
 * for (int i = n-1; i >= 1; i--)
 *     suffix[i] = arr[i] + suffix[i+1];
 *
 * QUERY:
 * ------
 * Sum from index i to end = suffix[i]  (O(1))
 *
 * ┌──────────────────────────────────────────────────────────────┐
 * │ 2️⃣ 2D SUFFIX SUM                                            │
 * └──────────────────────────────────────────────────────────────┘
 *
 * BUILD FORMULA:
 * --------------
 * suffix[i][j] = mat[i][j]
 *              + suffix[i+1][j]      // Below
 *              + suffix[i][j+1]      // Right
 *              - suffix[i+1][j+1];   // Overlap
 *
 * STEPS (0-based):
 * ----------------
 * 1. Base: suffix[n-1][m-1] = mat[n-1][m-1]
 * 2. Last row: suffix[n-1][j] = mat[n-1][j] + suffix[n-1][j+1]
 * 3. Last col: suffix[i][m-1] = mat[i][m-1] + suffix[i+1][m-1]
 * 4. Rest: Use formula above
 *
 * QUERY:
 * ------
 * Sum from (i,j) to bottom-right = suffix[i][j]  (O(1))
 *
 * ┌──────────────────────────────────────────────────────────────┐
 * │ 3️⃣ 1D DIFFERENCE ARRAY                                      │
 * └──────────────────────────────────────────────────────────────┘
 *
 * RANGE UPDATE [L, R] with value 'val':
 * --------------------------------------
 * diff[L] += val;        // Start
 * diff[R+1] -= val;      // End + 1
 *
 * COMPUTE FINAL ARRAY (0-based):
 * ------------------------------
 * arr[0] = diff[0];
 * for (int i = 1; i < n; i++)
 *     arr[i] = arr[i-1] + diff[i];
 *
 * COMPUTE FINAL ARRAY (1-based):
 * ------------------------------
 * arr[1] = diff[1];
 * for (int i = 2; i <= n; i++)
 *     arr[i] = arr[i-1] + diff[i];
 *
 * ┌──────────────────────────────────────────────────────────────┐
 * │ 4️⃣ 2D DIFFERENCE ARRAY                                      │
 * └──────────────────────────────────────────────────────────────┘
 *
 * RECTANGLE UPDATE (r1,c1) to (r2,c2) with value 'val':
 * -----------------------------------------------------
 * diff[r1][c1] += val;           // Top-left
 * diff[r1][c2+1] -= val;         // Top-right + 1
 * diff[r2+1][c1] -= val;         // Bottom-left + 1
 * diff[r2+1][c2+1] += val;       // Bottom-right + 1
 *
 * COMPUTE FINAL GRID (2D Prefix Sum):
 * ------------------------------------
 * // Step 1: Row-wise prefix
 * for (int i = 0; i < n; i++)
 *     for (int j = 0; j < m; j++)
 *         if (j > 0) diff[i][j] += diff[i][j-1];
 *
 * // Step 2: Column-wise prefix
 * for (int i = 0; i < n; i++)
 *     for (int j = 0; j < m; j++)
 *         if (i > 0) diff[i][j] += diff[i-1][j];
 *
 * ┌──────────────────────────────────────────────────────────────┐
 * │ 🏆 GM-LEVEL PRO TIPS                                         │
 * └──────────────────────────────────────────────────────────────┘
 *
 * 1. SUFFIX SUM vs PREFIX SUM:
 *    ├─ Prefix: Sum from START to index i
 *    └─ Suffix: Sum from index i to END
 *
 * 2. WHEN TO USE SUFFIX SUM:
 *    ✅ Need "sum of remaining elements" frequently
 *    ✅ Reverse iteration problems
 *    ✅ DP problems with backwards dependencies
 *
 * 3. WHEN TO USE DIFFERENCE ARRAY:
 *    ✅ Multiple range updates (Q updates in O(Q + N))
 *    ✅ LeetCode: Corporate Flight Bookings, Car Pooling
 *    ✅ Sweep line algorithms
 *
 * 4. INDEXING STRATEGY:
 *    ├─ CodeForces/AtCoder → 1-based (cleaner)
 *    └─ LeetCode           → 0-based (required)
 *
 * 5. MEMORY TIP:
 *    • Difference array needs n+1 size (for diff[R+1])
 *    • 2D difference needs (n+1) × (m+1) size
 *
 * 6. COMMON MISTAKES:
 *    ❌ Forgetting diff[R+1] -= val in 1D
 *    ❌ Forgetting all 4 corners in 2D difference
 *    ❌ Not computing prefix sum after difference updates
 *    ❌ Index out of bounds (use n+1, m+1 size)
 *
 * 7. DEBUGGING TIPS:
 *    • After difference updates, verify with small example
 *    • Check boundary cases (L=0, R=n-1)
 *    • Ensure diff array is large enough (n+1)
 *
 * 8. PRACTICE PROBLEMS:
 *    • LeetCode 1109 - Corporate Flight Bookings (1D Diff)
 *    • LeetCode 1094 - Car Pooling (1D Diff)
 *    • LeetCode 2536 - Increment Submatrices (2D Diff)
 *    • CodeForces - Range Update Queries
 *
 * ┌──────────────────────────────────────────────────────────────┐
 * │ ⚡ SPEED CODING MACROS                                       │
 * └──────────────────────────────────────────────────────────────┘
 *
 * // 1D Difference Array (0-based)
 * #define RANGE_ADD(L,R,val) diff[L]+=val, diff[R+1]-=val
 *
 * // 2D Difference Array (0-based)
 * #define RECT_ADD(r1,c1,r2,c2,val) \
 *     diff[r1][c1]+=val, diff[r1][c2+1]-=val, \
 *     diff[r2+1][c1]-=val, diff[r2+1][c2+1]+=val
 *
 * Usage:
 * ------
 * RANGE_ADD(L, R, val);              // 1D update
 * RECT_ADD(r1, c1, r2, c2, val);     // 2D update
 */


