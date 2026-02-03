/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-23 18:32:15
Updated : 2026-01-31 (Enhanced with 0-based LeetCode compatibility)
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
#include <numeric>
#include <random>
#include <chrono>

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
 * 🏆 GM-LEVEL 2D PREFIX SUM MASTERY
 * ==========================================
 *
 * Problem: 2D Prefix Sum and Range Sum Queries
 * Approach: 2D Prefix Sum (Inclusion-Exclusion Principle)
 *
 * Time Complexity:
 * - Build: O(N * M)
 * - Query: O(1) per query
 * - Total: O(N * M + Q)
 *
 * Space Complexity: O(N * M) for the prefix array
 */

/**
 * ==========================================
 * ✅ GM-LEVEL CHECKLIST (CRITICAL!)
 * ==========================================
 *
 * 1️⃣ READ PROBLEM CONSTRAINTS FIRST!
 *    ├─ CodeForces/AtCoder/SPOJ     → Usually 1-based input
 *    ├─ LeetCode/HackerRank         → ALWAYS 0-based input
 *    └─ Check: "1 ≤ r, c ≤ N" (1-based) vs "0 ≤ r, c < N" (0-based)
 *
 * 2️⃣ CHOOSE YOUR INDEXING STRATEGY:
 *    ├─ 1-BASED PREFIX (Recommended for CP)
 *    │  • Cleaner formulas, less conditionals
 *    │  • Array size: [N+1][M+1], skip index 0
 *    │
 *    └─ 0-BASED PREFIX (Required for LeetCode)
 *       • More if-conditions, but mandatory for LeetCode classes
 *       • Array size: [N][M], use all indices
 *
 * 3️⃣ VALIDATE CONSTRAINTS:
 *    • N, M ≤ 1000 → Static arrays OK
 *    • N, M > 1000 → Use vectors (avoid stack overflow)
 *    • Q ≤ 10^5   → O(1) queries mandatory
 *
 * 4️⃣ OVERFLOW CHECK:
 *    • Max sum = N * M * max_value
 *    • If > 2×10^9 → Use i64 (long long)
 *
 * 5️⃣ EDGE CASES TO TEST:
 *    • Single cell grid (1×1)
 *    • Query = entire grid
 *    • Query = single cell
 *    • Negative numbers (if allowed)
 *
 * 6️⃣ DEBUGGING TIPS:
 *    • Print prefix array after building
 *    • Verify: pref[n][m] should equal sum of all elements
 *    • Check boundary queries first
 */

// ==========================================
// METHOD 1: 1-BASED INDEX (COMPETITIVE PROGRAMMING GOLD STANDARD)
// ==========================================
// ✅ Use for: CodeForces, AtCoder, CSES, SPOJ
// ✅ Pros: Cleaner code, less conditionals, faster to write in contests
// ❌ Cons: Won't work on LeetCode (array indices start at 0)

constexpr int MAXN = 1005;
i64 mat[MAXN][MAXN];
i64 pref[MAXN][MAXN];

void solve_1based_static() {
    int n, m;
    cin >> n >> m;

    // Step 1: Input matrix (1-based) and build prefix sum
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mat[i][j];

            // 🔥 BUILD FORMULA (1-based):
            // "Current + Top + Left - Overlap"
            pref[i][j] = mat[i][j]
                       + pref[i - 1][j]      // Top
                       + pref[i][j - 1]      // Left
                       - pref[i - 1][j - 1]; // Overlap (counted twice)
        }
    }

    // Step 2: Answer queries
    int q;
    cin >> q;

    while (q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        // 🔥 QUERY FORMULA (1-based):
        // "Big - Top - Left + Corner"
        i64 ans = pref[r2][c2]                    // Big rectangle
                - pref[r1 - 1][c2]                // Remove top strip
                - pref[r2][c1 - 1]                // Remove left strip
                + pref[r1 - 1][c1 - 1];          // Add back corner (removed twice)

        cout << ans << nl;
    }
}

// ==========================================
// METHOD 2: 0-BASED INDEX (LEETCODE STANDARD)
// ==========================================
// ✅ Use for: LeetCode, HackerRank, or when input is 0-indexed
// ✅ Pros: Works with LeetCode's class structure, no index shifting
// ❌ Cons: More conditionals, slightly slower in contests

i64 prefix[MAXN][MAXN];

void solve_0based_static() {
    int n, m;
    cin >> n >> m;

    // Step 1: Input matrix (0-based) and build prefix sum
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];

            // 🔥 BUILD FORMULA (0-based):
            // Start with current element
            prefix[i][j] = mat[i][j];

            // Add top (if exists)
            if (i > 0) prefix[i][j] += prefix[i - 1][j];

            // Add left (if exists)
            if (j > 0) prefix[i][j] += prefix[i][j - 1];

            // Subtract overlap (if exists)
            if (i > 0 && j > 0) prefix[i][j] -= prefix[i - 1][j - 1];
        }
    }

    // Step 2: Answer queries (0-based input: r1, c1, r2, c2)
    int q;
    cin >> q;

    while (q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        // 🔥 QUERY FORMULA (0-based):
        i64 ans = prefix[r2][c2];

        // Subtract top strip (if exists)
        if (r1 > 0) ans -= prefix[r1 - 1][c2];

        // Subtract left strip (if exists)
        if (c1 > 0) ans -= prefix[r2][c1 - 1];

        // Add back corner (if exists)
        if (r1 > 0 && c1 > 0) ans += prefix[r1 - 1][c1 - 1];

        cout << ans << nl;
    }
}

// ==========================================
// METHOD 3: VECTOR-BASED (DYNAMIC MEMORY)
// ==========================================
// ✅ Use for: Variable N/M, memory-constrained problems, interviews
// ✅ Pros: No stack overflow, scalable, good for software engineering
// ❌ Cons: Slower than static arrays, more verbose

void solve_1based_vector() {
    int n, m;
    cin >> n >> m;

    // Allocate (n+1) × (m+1) for 1-based indexing
    vec<vec<i64>> grid(n + 1, vec<i64>(m + 1, 0));
    vec<vec<i64>> prefixSum(n + 1, vec<i64>(m + 1, 0));

    // Step 1: Input and build prefix sum
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> grid[i][j];

            prefixSum[i][j] = grid[i][j]
                            + prefixSum[i - 1][j]
                            + prefixSum[i][j - 1]
                            - prefixSum[i - 1][j - 1];
        }
    }

    // Step 2: Answer queries
    int q;
    cin >> q;

    while (q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        i64 ans = prefixSum[r2][c2]
                - prefixSum[r1 - 1][c2]
                - prefixSum[r2][c1 - 1]
                + prefixSum[r1 - 1][c1 - 1];

        cout << ans << nl;
    }
}

// ==========================================
// METHOD 4: LEETCODE CLASS TEMPLATE (0-BASED)
// ==========================================
// ✅ Use this exact structure for LeetCode problems
// ✅ Example: LeetCode 304 - Range Sum Query 2D - Immutable

class NumMatrix {
private:
    vec<vec<int>> prefix;
    int rows, cols;

public:
    // Constructor: Build prefix sum (0-based input)
    NumMatrix(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return;

        rows = matrix.size();
        cols = matrix[0].size();

        // Allocate (rows+1) × (cols+1) to avoid boundary checks
        prefix.assign(rows + 1, vec<int>(cols + 1, 0));

        // Build prefix sum using 1-based internal indexing
        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                prefix[i][j] = matrix[i - 1][j - 1]  // Convert to 0-based input
                             + prefix[i - 1][j]
                             + prefix[i][j - 1]
                             - prefix[i - 1][j - 1];
            }
        }
    }

    // Query: Sum of rectangle (0-based input coordinates)
    int sumRegion(int row1, int col1, int row2, int col2) {
        // Convert 0-based input to 1-based internal coordinates
        row1++; col1++; row2++; col2++;

        return prefix[row2][col2]
             - prefix[row1 - 1][col2]
             - prefix[row2][col1 - 1]
             + prefix[row1 - 1][col1 - 1];
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    // 🎯 CHOOSE YOUR METHOD BASED ON PROBLEM:

    // For CodeForces/AtCoder (1-based input):
    // solve_1based_static();

    // For LeetCode/0-based input problems:
    // solve_0based_static();

    // For dynamic sizing or interviews:
    // solve_1based_vector();

    // Uncomment the method you need:
    solve_1based_static();

    return 0;
}

/*
 * ==========================================
 * 📚 2D PREFIX SUM FORMULA CHEATSHEET
 * ==========================================
 *
 * ┌─────────────────────────────────────────┐
 * │  1️⃣ BUILD FORMULA (Pre-computation)    │
 * └─────────────────────────────────────────┘
 *
 * 1-BASED:
 * --------
 * pref[i][j] = mat[i][j]
 *            + pref[i-1][j]      // Top
 *            + pref[i][j-1]      // Left
 *            - pref[i-1][j-1];   // Overlap
 *
 * 0-BASED:
 * --------
 * prefix[i][j] = mat[i][j];
 * if (i > 0) prefix[i][j] += prefix[i-1][j];
 * if (j > 0) prefix[i][j] += prefix[i][j-1];
 * if (i > 0 && j > 0) prefix[i][j] -= prefix[i-1][j-1];
 *
 * ┌─────────────────────────────────────────┐
 * │  2️⃣ QUERY FORMULA (O(1) Retrieval)     │
 * └─────────────────────────────────────────┘
 *
 * Visual Representation:
 *
 *     c1-1  c1      c2
 *       │    │       │
 * r1-1──┼────┼───────┤
 *       │ ❌ │  ❌   │
 * r1────┼────┼───────┤
 *       │ ❌ │  ✅   │ ← Target Region
 * r2────┼────┼───────┤
 *
 * Formula Breakdown:
 * ------------------
 * ans = BIG - TOP - LEFT + CORNER
 *
 * BIG    = pref[r2][c2]         → Sum from (0,0) to (r2,c2)
 * TOP    = pref[r1-1][c2]       → Remove region above target
 * LEFT   = pref[r2][c1-1]       → Remove region left of target
 * CORNER = pref[r1-1][c1-1]     → Add back (subtracted twice)
 *
 * 1-BASED CODE:
 * -------------
 * ans = pref[r2][c2]
 *     - pref[r1-1][c2]
 *     - pref[r2][c1-1]
 *     + pref[r1-1][c1-1];
 *
 * 0-BASED CODE:
 * -------------
 * ans = prefix[r2][c2];
 * if (r1 > 0) ans -= prefix[r1-1][c2];
 * if (c1 > 0) ans -= prefix[r2][c1-1];
 * if (r1 > 0 && c1 > 0) ans += prefix[r1-1][c1-1];
 *
 * ┌─────────────────────────────────────────┐
 * │  🏆 GM-LEVEL PRO TIPS                   │
 * └─────────────────────────────────────────┘
 *
 * 1. INDEXING CHOICE:
 *    ├─ Competitive Programming → 1-based (cleaner, faster to code)
 *    └─ LeetCode               → 0-based OR use (n+1)×(m+1) trick
 *
 * 2. LEETCODE TRICK:
 *    • Allocate prefix[n+1][m+1] (internally 1-based)
 *    • Convert input: prefix[i+1][j+1] = matrix[i][j]
 *    • Query: add 1 to all coordinates
 *    • Result: Clean 1-based formulas work perfectly!
 *
 * 3. MEMORY OPTIMIZATION:
 *    • N, M ≤ 1000   → Static arrays [MAXN][MAXN]
 *    • N, M > 1000   → Vectors (avoid stack overflow)
 *    • Multiple test cases → memset(pref, 0, sizeof(pref))
 *
 * 4. OVERFLOW PREVENTION:
 *    • Always use long long (i64) for prefix sums
 *    • Check: N * M * max_element > 2×10^9 → Must use i64
 *
 * 5. DEBUGGING CHECKLIST:
 *    ✓ Print pref[n][m] → Should equal sum of all elements
 *    ✓ Test query for entire grid
 *    ✓ Test single cell query
 *    ✓ Check boundary cases (first row, first column)
 *
 * 6. COMMON MISTAKES:
 *    ❌ Forgetting to subtract overlap in BUILD
 *    ❌ Forgetting to add corner back in QUERY
 *    ❌ Using int when sum can exceed 2×10^9
 *    ❌ Off-by-one errors in 0-based indexing
 *    ❌ Not checking if (i > 0) in 0-based code
 *
 * 7. CONTEST STRATEGY:
 *    • Read problem constraints FIRST
 *    • 1-based input → Use Method 1 (fastest to code)
 *    • 0-based input → Use Method 4 (LeetCode template)
 *    • Practice both methods until muscle memory!
 *
 * 8. RELATED PROBLEMS:
 *    • LeetCode 304 - Range Sum Query 2D - Immutable
 *    • LeetCode 1314 - Matrix Block Sum
 *    • CSES - Forest Queries
 *    • CodeForces - Greg and Array (1D version)
 *
 * ┌─────────────────────────────────────────┐
 * │  ⚡ SPEED CODING SHORTCUTS              │
 * └─────────────────────────────────────────┘
 *
 * 1-Based Macro (for contests):
 * ------------------------------
 * #define BUILD(i,j) pref[i][j]=mat[i][j]+pref[i-1][j]+pref[i][j-1]-pref[i-1][j-1]
 * #define QUERY(r1,c1,r2,c2) (pref[r2][c2]-pref[r1-1][c2]-pref[r2][c1-1]+pref[r1-1][c1-1])
 *
 * Usage:
 * for(int i=1; i<=n; i++)
 *   for(int j=1; j<=m; j++)
 *     cin >> mat[i][j], BUILD(i,j);
 *
 * cout << QUERY(r1, c1, r2, c2) << nl;
 */

