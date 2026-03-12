/*
 * ============================================================================
 *    COMBINATORIAL DP — CATALAN, STIRLING, BELL, PARTITIONS
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Advanced DP — Integer Partitions, Catalan, Stirling, Bell Numbers
 * Level   : ⭐⭐⭐⭐ Expert / ICPC Essential
 * ============================================================================
 *
 * COMBINATORIAL SEQUENCES computed via DP:
 * 1. Catalan Numbers — C(n) = C(2n,n)/(n+1)
 * 2. Stirling Numbers of 2nd Kind — S(n,k) = ways to partition n into k non-empty subsets
 * 3. Bell Numbers — B(n) = total partitions of n elements
 * 4. Integer Partitions — p(n) = ways to write n as sum of positive integers
 * 5. Partition into k parts — restricted partitions
 * 6. Derangement Numbers — D(n) = permutations with no fixed point
 * 7. Euler Numbers — alternating permutations
 *
 * These are EXTREMELY common in ICPC combinatorics problems!
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long power(long long base, long long exp, long long mod) {
    long long result = 1; base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

/*
 * 1. CATALAN NUMBERS
 *    C(0)=1, C(n) = Σ C(i)*C(n-1-i) for i=0..n-1
 *    C(n) = C(2n,n) / (n+1)
 *
 *    Applications:
 *    - Valid parenthesizations of n pairs
 *    - BST count with n nodes
 *    - Triangulations of polygon with n+2 sides
 *    - Non-crossing partitions
 *    - Paths that don't cross diagonal (ballot problem)
 *    - Stack-sortable permutations
 */
vector<long long> catalanDP(int n) {
    vector<long long> C(n + 1, 0);
    C[0] = C[1] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = 0; j < i; j++)
            C[i] = (C[i] + C[j] * C[i-1-j]) % MOD;
    return C;
}

// Catalan using formula: C(n) = C(2n,n) / (n+1)
long long catalanFormula(int n) {
    // Need factorials
    vector<long long> fact(2*n + 1);
    fact[0] = 1;
    for (int i = 1; i <= 2*n; i++) fact[i] = fact[i-1] * i % MOD;
    long long inv_fact_n1 = power(fact[n+1], MOD - 2, MOD);
    long long inv_fact_n = power(fact[n], MOD - 2, MOD);
    return fact[2*n] % MOD * inv_fact_n1 % MOD * inv_fact_n % MOD;
}

/*
 * 2. STIRLING NUMBERS OF THE SECOND KIND
 *    S(n, k) = number of ways to partition n elements into k non-empty subsets
 *
 *    Recurrence:
 *    S(n, k) = k * S(n-1, k) + S(n-1, k-1)
 *    Base: S(0, 0) = 1, S(n, 0) = 0, S(0, k) = 0
 *
 *    Interpretation:
 *    - Element n either goes to an existing group (k choices)
 *    - OR starts its own new group
 */
vector<vector<long long>> stirling2(int n) {
    vector<vector<long long>> S(n + 1, vector<long long>(n + 1, 0));
    S[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            S[i][j] = (j * S[i-1][j] + S[i-1][j-1]) % MOD;
    return S;
}

/*
 * 3. BELL NUMBERS
 *    B(n) = total number of partitions of n elements = Σ S(n, k) for k=0..n
 *
 *    Bell Triangle:
 *    B(0) = 1
 *    b[i][0] = b[i-1][i-1]
 *    b[i][j] = b[i][j-1] + b[i-1][j-1]
 *    B(n) = b[n][0]
 */
vector<long long> bellNumbers(int n) {
    vector<long long> B(n + 1, 0);
    auto S = stirling2(n);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= i; j++)
            B[i] = (B[i] + S[i][j]) % MOD;
    return B;
}

/*
 * 4. INTEGER PARTITIONS
 *    p(n) = number of ways to write n as sum of positive integers (order doesn't matter)
 *    p(5) = 7: {5}, {4+1}, {3+2}, {3+1+1}, {2+2+1}, {2+1+1+1}, {1+1+1+1+1}
 *
 *    DP approach: dp[i][j] = partitions of i using parts ≤ j
 *    dp[i][j] = dp[i][j-1] + dp[i-j][j]
 *    (don't use j, or use at least one j)
 *
 *    Space optimized to 1D (like unbounded knapsack):
 */
long long integerPartitions(int n) {
    vector<long long> dp(n + 1, 0);
    dp[0] = 1;
    for (int part = 1; part <= n; part++)        // Outer: part size
        for (int i = part; i <= n; i++)           // Inner: target sum
            dp[i] = (dp[i] + dp[i - part]) % MOD;
    return dp[n];
}

// Partitions of n into exactly k parts
long long partitionsIntoK(int n, int k) {
    // p(n, k) = p(n-1, k-1) + p(n-k, k)
    // Either smallest part is 1 (remove it: p(n-1, k-1))
    // Or all parts ≥ 2 (subtract 1 from each: p(n-k, k))
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= min(i, k); j++)
            dp[i][j] = (dp[i-1][j-1] + (i >= j ? dp[i-j][j] : 0)) % MOD;
    return dp[n][k];
}

// Partitions into distinct parts
long long partitionsDistinct(int n) {
    vector<long long> dp(n + 1, 0);
    dp[0] = 1;
    for (int part = 1; part <= n; part++)
        for (int i = n; i >= part; i--)  // Backwards like 0/1 knapsack
            dp[i] = (dp[i] + dp[i - part]) % MOD;
    return dp[n];
}

/*
 * 5. DERANGEMENTS
 *    D(n) = n! × Σ (-1)^k / k! for k=0..n
 *    D(n) = (n-1) × (D(n-1) + D(n-2))
 */
vector<long long> derangements(int n) {
    vector<long long> D(n + 1, 0);
    D[0] = 1; // Convention: D(0) = 1
    if (n >= 1) D[1] = 0;
    for (int i = 2; i <= n; i++)
        D[i] = (long long)(i - 1) % MOD * ((D[i-1] + D[i-2]) % MOD) % MOD;
    return D;
}

/*
 * 6. STIRLING NUMBERS OF THE FIRST KIND
 *    s(n, k) = number of permutations of n with exactly k cycles
 *    |s(n, k)| (unsigned) = c(n, k)
 *
 *    Recurrence:
 *    c(n, k) = (n-1) * c(n-1, k) + c(n-1, k-1)
 *    Base: c(0, 0) = 1
 *
 *    Interpretation: element n either:
 *    - Starts its own cycle → c(n-1, k-1)
 *    - Joins an existing cycle (n-1 positions to insert) → (n-1)*c(n-1, k)
 */
vector<vector<long long>> stirling1(int n) {
    vector<vector<long long>> c(n + 1, vector<long long>(n + 1, 0));
    c[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            c[i][j] = ((long long)(i-1) * c[i-1][j] + c[i-1][j-1]) % MOD;
    return c;
}

/*
 * 7. MULTINOMIAL COEFFICIENTS
 *    n! / (k1! × k2! × ... × km!)
 *    Number of ways to divide n items into groups of sizes k1, k2, ..., km
 */
long long multinomial(int n, vector<int>& groups) {
    vector<long long> fact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i % MOD;

    long long result = fact[n];
    for (int k : groups)
        result = result % MOD * power(fact[k], MOD - 2, MOD) % MOD;
    return result;
}

/*
 * 8. NUMBER OF LABELED FORESTS / TREES
 *    Cayley's formula: number of labeled trees on n vertices = n^(n-2)
 *    Number of labeled forests on n vertices with k trees:
 *    C(n-1, k-1) × n^(n-k)
 */
long long labeledTrees(int n) {
    if (n <= 2) return 1;
    return power(n, n - 2, MOD);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== COMBINATORIAL DP ===" << endl;

    // Catalan
    auto C = catalanDP(15);
    cout << "\n--- Catalan Numbers ---" << endl;
    for (int i = 0; i <= 10; i++) cout << "C(" << i << ")=" << C[i] << " ";
    cout << endl;

    // Stirling 2nd kind
    auto S = stirling2(7);
    cout << "\n--- Stirling (2nd Kind) — S(n,k) ---" << endl;
    for (int i = 0; i <= 5; i++) {
        cout << "n=" << i << ": ";
        for (int j = 0; j <= i; j++) cout << S[i][j] << " ";
        cout << endl;
    }

    // Bell Numbers
    auto B = bellNumbers(10);
    cout << "\n--- Bell Numbers ---" << endl;
    for (int i = 0; i <= 10; i++) cout << "B(" << i << ")=" << B[i] << " ";
    cout << endl;

    // Integer Partitions
    cout << "\n--- Integer Partitions ---" << endl;
    for (int n = 0; n <= 15; n++)
        cout << "p(" << n << ")=" << integerPartitions(n) << " ";
    cout << endl;

    // Partitions into k parts
    cout << "p(10, 3) = " << partitionsIntoK(10, 3) << endl;

    // Partitions into distinct parts
    cout << "Distinct partitions of 10 = " << partitionsDistinct(10) << endl;

    // Derangements
    auto D = derangements(10);
    cout << "\n--- Derangements ---" << endl;
    for (int i = 0; i <= 10; i++) cout << "D(" << i << ")=" << D[i] << " ";
    cout << endl;

    // Stirling 1st kind
    auto c = stirling1(7);
    cout << "\n--- Stirling (1st Kind) — c(n,k) ---" << endl;
    for (int i = 0; i <= 5; i++) {
        cout << "n=" << i << ": ";
        for (int j = 0; j <= i; j++) cout << c[i][j] << " ";
        cout << endl;
    }

    // Labeled Trees
    cout << "\n--- Cayley's Formula (Labeled Trees) ---" << endl;
    for (int n = 1; n <= 8; n++)
        cout << "n=" << n << ": " << labeledTrees(n) << " ";
    cout << endl;

    return 0;
}

