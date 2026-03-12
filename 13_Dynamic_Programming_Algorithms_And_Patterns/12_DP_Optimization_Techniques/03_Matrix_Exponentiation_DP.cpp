/*
 * ============================================================================
 *       MATRIX EXPONENTIATION DP — LINEAR RECURRENCES IN O(LOG N)
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : DP Optimization — Matrix Exponentiation for Linear Recurrences
 * Level   : ⭐⭐⭐⭐ Expert / ICPC Essential
 * ============================================================================
 *
 * WHEN TO USE:
 *   Any linear recurrence: dp[n] = c1*dp[n-1] + c2*dp[n-2] + ... + ck*dp[n-k]
 *   When n is HUGE (up to 10^18) but k is small.
 *   Convert recurrence to matrix form: [dp[n]] = M^(n-k) × [dp[k-1]..dp[0]]
 *
 * TIME: O(k³ × log n)  where k = number of terms in recurrence
 *
 * CLASSIC PROBLEMS:
 * 1. Fibonacci in O(log n)
 * 2. Counting paths of length exactly L in a graph (adjacency matrix power)
 * 3. Linear recurrence with constant coefficients
 * 4. Tiling problems with large N
 * 5. Knight moves on chessboard (count paths of length N)
 * 6. CSES: Fibonacci Numbers, Graph Paths I/II
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;

typedef vector<vector<long long>> Matrix;

// Matrix multiplication mod p
Matrix matMul(const Matrix& A, const Matrix& B) {
    int n = A.size(), m = B[0].size(), k = B.size();
    Matrix C(n, vector<long long>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int p = 0; p < k; p++)
                C[i][j] = (C[i][j] + A[i][p] * B[p][j]) % MOD;
    return C;
}

// Matrix power: M^exp in O(k³ log exp)
Matrix matPow(Matrix M, long long exp) {
    int n = M.size();
    Matrix result(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) result[i][i] = 1; // Identity

    while (exp > 0) {
        if (exp & 1) result = matMul(result, M);
        M = matMul(M, M);
        exp >>= 1;
    }
    return result;
}

/*
 * 1. FIBONACCI — F(n) in O(log n)
 *    F(n) = F(n-1) + F(n-2)
 *
 *    Matrix form:
 *    |F(n)  |   |1 1|^(n-1)   |F(1)|
 *    |F(n-1)| = |1 0|       × |F(0)|
 */
long long fibonacci(long long n) {
    if (n <= 1) return n;
    Matrix M = {{1, 1}, {1, 0}};
    Matrix result = matPow(M, n - 1);
    return result[0][0];  // F(n) = result[0][0]*F(1) + result[0][1]*F(0)
}

/*
 * 2. GENERAL LINEAR RECURRENCE
 *    dp[n] = c1*dp[n-1] + c2*dp[n-2] + ... + ck*dp[n-k]
 *
 *    Matrix form (k×k transition matrix):
 *    |dp[n]  |   |c1 c2 c3 ... ck|   |dp[n-1]|
 *    |dp[n-1]| = |1  0  0  ... 0 | × |dp[n-2]|
 *    |dp[n-2]| = |0  1  0  ... 0 |   |dp[n-3]|
 *    |...    |   |...             |   |...    |
 *    |dp[n-k+1]  |0  0  0  ... 0 |   |dp[n-k]|
 */
long long linearRecurrence(vector<long long>& coeffs, vector<long long>& initial, long long n) {
    int k = coeffs.size();
    if (n < k) return initial[n];

    // Build transition matrix
    Matrix M(k, vector<long long>(k, 0));
    for (int j = 0; j < k; j++) M[0][j] = coeffs[j] % MOD;
    for (int i = 1; i < k; i++) M[i][i-1] = 1;

    Matrix result = matPow(M, n - k + 1);

    // Multiply with initial state [dp[k-1], dp[k-2], ..., dp[0]]
    long long ans = 0;
    for (int j = 0; j < k; j++)
        ans = (ans + result[0][j] * initial[k - 1 - j]) % MOD;
    return ans;
}

/*
 * 3. COUNTING PATHS OF LENGTH EXACTLY L IN GRAPH
 *    Given adjacency matrix A of a graph with n nodes.
 *    A^L[i][j] = number of walks of length exactly L from i to j.
 *    Time: O(n³ × log L)
 *
 *    CSES: Graph Paths I
 */
long long countPaths(Matrix& adj, int src, int dst, long long L) {
    Matrix result = matPow(adj, L);
    return result[src][dst];
}

/*
 * 4. TILING 2×N BOARD — For huge N
 *    T(n) = T(n-1) + T(n-2)  (same as Fibonacci)
 *    For 3×N: T(n) = 4*T(n-2) - T(n-4) with T(0)=1, T(2)=3
 */
long long tiling2xN(long long n) {
    if (n % 2 == 1) return 0;  // Odd width → 0 for 3×N
    return fibonacci(n + 1);    // 2×N same as Fibonacci
}

// 3×N tiling
long long tiling3xN(long long n) {
    if (n % 2 == 1) return 0;
    if (n == 0) return 1;
    if (n == 2) return 3;

    // T(n) = 4*T(n-2) - T(n-4)
    // State: [T(n), T(n-2)]
    // |T(n+2)| = |4 -1| × |T(n)  |
    // |T(n)  |   |1  0|   |T(n-2)|
    Matrix M = {{4, MOD - 1}, {1, 0}};  // MOD-1 for -1
    Matrix result = matPow(M, n / 2 - 1);
    // Initial: T(2)=3, T(0)=1
    long long ans = (result[0][0] * 3 + result[0][1]) % MOD;
    return ans;
}

/*
 * 5. KNIGHT DISTANCE COUNT
 *    On 1D board of size w, knight moves by ±a, ±b.
 *    Count paths of length exactly N from position s to t.
 *    Build w×w transition matrix, raise to power N.
 */
long long knightPaths1D(int w, int a, int b, int s, int t, long long N) {
    Matrix M(w, vector<long long>(w, 0));
    for (int i = 0; i < w; i++) {
        if (i + a < w) M[i][i + a] = 1;
        if (i - a >= 0) M[i][i - a] = 1;
        if (i + b < w) M[i][i + b] = 1;
        if (i - b >= 0) M[i][i - b] = 1;
    }
    Matrix result = matPow(M, N);
    return result[s][t];
}

/*
 * 6. RECURRENCE WITH NON-HOMOGENEOUS TERM
 *    dp[n] = a*dp[n-1] + b*dp[n-2] + c  (constant c added)
 *
 *    Trick: Add an extra dimension for the constant!
 *    |dp[n]  |   |a b c|   |dp[n-1]|
 *    |dp[n-1]| = |1 0 0| × |dp[n-2]|
 *    |1      |   |0 0 1|   |1      |
 */
long long recurrenceWithConstant(long long a, long long b, long long c,
                                  long long d0, long long d1, long long n) {
    if (n == 0) return d0;
    if (n == 1) return d1;

    Matrix M = {{a % MOD, b % MOD, c % MOD}, {1, 0, 0}, {0, 0, 1}};
    Matrix result = matPow(M, n - 1);
    long long ans = (result[0][0] * d1 % MOD + result[0][1] * d0 % MOD + result[0][2]) % MOD;
    return ans;
}

/*
 * 7. KITAMASA METHOD (Brief Concept)
 *    For large n and large k (order of recurrence):
 *    Matrix exponentiation is O(k³ log n) — too slow if k > ~200.
 *    Kitamasa: O(k² log n) or O(k log k log n) with NTT.
 *    Idea: Express x^n mod characteristic polynomial using polynomial division.
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== MATRIX EXPONENTIATION DP ===" << endl;

    // Fibonacci
    cout << "\n--- Fibonacci ---" << endl;
    for (long long n : {0LL, 1LL, 10LL, 50LL, 1000000000000000000LL}) {
        cout << "F(" << n << ") = " << fibonacci(n) << endl;
    }

    // General linear recurrence: Tribonacci T(n) = T(n-1) + T(n-2) + T(n-3)
    cout << "\n--- Tribonacci ---" << endl;
    vector<long long> coeffs = {1, 1, 1};
    vector<long long> initial = {0, 0, 1};  // T(0)=0, T(1)=0, T(2)=1
    for (long long n = 0; n <= 10; n++)
        cout << "T(" << n << ") = " << linearRecurrence(coeffs, initial, n) << " ";
    cout << endl;

    // Count paths in graph
    cout << "\n--- Graph Paths ---" << endl;
    Matrix adj = {{0,1,0,0}, {1,0,1,0}, {0,1,0,1}, {0,0,1,0}};
    // Path graph: 0-1-2-3
    cout << "Paths of length 3 from 0→3: " << countPaths(adj, 0, 3, 3) << endl;
    cout << "Paths of length 4 from 0→0: " << countPaths(adj, 0, 0, 4) << endl;

    // 3×N tiling
    cout << "\n--- 3×N Tiling ---" << endl;
    for (int n : {0, 2, 4, 6, 8, 10}) {
        cout << "3×" << n << ": " << tiling3xN(n) << " ";
    }
    cout << endl;

    // Non-homogeneous: dp[n] = 2*dp[n-1] + 3*dp[n-2] + 5
    cout << "\n--- Non-Homogeneous Recurrence ---" << endl;
    cout << "dp[n] = 2*dp[n-1] + 3*dp[n-2] + 5, dp[0]=1, dp[1]=2" << endl;
    cout << "dp[10] = " << recurrenceWithConstant(2, 3, 5, 1, 2, 10) << endl;

    cout << "\n============================================" << endl;
    cout << "  MATRIX EXPO CHEAT SHEET:" << endl;
    cout << "  1. Find the recurrence" << endl;
    cout << "  2. Write as matrix multiplication" << endl;
    cout << "  3. Fast power in O(k³ log n)" << endl;
    cout << "  4. For constants: add extra row" << endl;
    cout << "  5. For graph paths: A^L[i][j]" << endl;
    cout << "============================================" << endl;

    return 0;
}

