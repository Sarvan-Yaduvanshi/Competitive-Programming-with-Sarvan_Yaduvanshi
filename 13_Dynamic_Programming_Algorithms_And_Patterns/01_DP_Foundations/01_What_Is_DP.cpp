/*
 * ============================================================================
 *                         WHAT IS DYNAMIC PROGRAMMING?
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : DP Foundations — What is DP?
 * Level   : ⭐ Beginner
 * ============================================================================
 *
 * DEFINITION:
 * -----------
 * Dynamic Programming (DP) is a method for solving complex problems by
 * breaking them into simpler overlapping subproblems, solving each
 * subproblem only once, and storing the result for future use.
 *
 * TWO KEY PROPERTIES FOR DP TO WORK:
 * -----------------------------------
 * 1. OVERLAPPING SUBPROBLEMS:
 *    - The same subproblem is solved multiple times
 *    - Example: Fibonacci → F(5) calls F(3) which is also called by F(4)
 *
 * 2. OPTIMAL SUBSTRUCTURE:
 *    - The optimal solution to the problem can be constructed from
 *      optimal solutions of its subproblems
 *    - Example: Shortest path → if A→B→C is shortest, then A→B part
 *      is also shortest
 *
 * WHEN TO USE DP:
 * ----------------
 * ✅ Problem asks: "count ways", "min/max", "is it possible?"
 * ✅ Problem has choices at each step
 * ✅ Brute force has exponential time due to repeated work
 * ✅ You can define states that capture all needed info
 *
 * WHEN NOT TO USE DP:
 * --------------------
 * ❌ Greedy gives optimal (no overlapping subproblems needed)
 * ❌ No overlapping subproblems (pure divide & conquer)
 * ❌ Problem doesn't have optimal substructure
 *
 * DP vs OTHER PARADIGMS:
 * -----------------------
 *  Paradigm          | Subproblems Overlap? | Optimal Substructure?
 *  ------------------|----------------------|----------------------
 *  Brute Force       | Doesn't matter       | Doesn't matter
 *  Divide & Conquer  | NO                   | YES
 *  Greedy            | NO                   | YES
 *  Dynamic Prog.     | YES                  | YES
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * EXAMPLE 1: Fibonacci — The Classic Introduction to DP
 *
 * Fibonacci: F(n) = F(n-1) + F(n-2), F(0)=0, F(1)=1
 *
 * WITHOUT DP (Pure Recursion):
 *
 *                     F(5)
 *                   /      \
 *                F(4)       F(3)        ← F(3) computed TWICE!
 *               /    \      /   \
 *            F(3)   F(2)  F(2)  F(1)   ← F(2) computed THREE times!
 *           /   \   / \   / \
 *         F(2) F(1) ...  ...  ...
 *         / \
 *       F(1) F(0)
 *
 * Time Complexity: O(2^n)  ← EXPONENTIAL! Very slow!
 * Space Complexity: O(n)   ← recursion stack
 *
 * WITH DP (Memoization): Store results, never recompute
 * Time Complexity: O(n)    ← LINEAR! Each subproblem solved once
 * Space Complexity: O(n)   ← storage for results
 */

// ==================== APPROACH 1: Pure Recursion (NO DP) ====================
// Time: O(2^n) — Exponential, very slow for n > 40
long long fib_recursive(int n) {
    if (n <= 1) return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

// ==================== APPROACH 2: Memoization (Top-Down DP) =================
// Time: O(n) — Each subproblem solved exactly once
// Space: O(n) — memo array + recursion stack
long long memo[1000];
bool visited[1000];

long long fib_memo(int n) {
    if (n <= 1) return n;
    if (visited[n]) return memo[n];  // Already computed? Return stored result

    visited[n] = true;
    memo[n] = fib_memo(n - 1) + fib_memo(n - 2);
    return memo[n];
}

// ==================== APPROACH 3: Tabulation (Bottom-Up DP) =================
// Time: O(n)
// Space: O(n) — dp array
long long fib_tabulation(int n) {
    if (n <= 1) return n;

    vector<long long> dp(n + 1);
    dp[0] = 0;     // Base case
    dp[1] = 1;     // Base case

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];  // Transition
    }
    return dp[n];
}

// ==================== APPROACH 4: Space Optimized DP ========================
// Time: O(n)
// Space: O(1) — Only need last two values!
long long fib_optimized(int n) {
    if (n <= 1) return n;

    long long prev2 = 0, prev1 = 1;
    for (int i = 2; i <= n; i++) {
        long long curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "============================================" << endl;
    cout << "   WHAT IS DYNAMIC PROGRAMMING? — DEMO" << endl;
    cout << "============================================" << endl;

    int n = 10;

    cout << "\nFibonacci(" << n << ") using different approaches:" << endl;
    cout << "1. Pure Recursion:     " << fib_recursive(n) << endl;

    memset(visited, false, sizeof(visited));
    cout << "2. Memoization:        " << fib_memo(n) << endl;
    cout << "3. Tabulation:         " << fib_tabulation(n) << endl;
    cout << "4. Space Optimized:    " << fib_optimized(n) << endl;

    cout << "\n--- First 15 Fibonacci Numbers ---" << endl;
    for (int i = 0; i < 15; i++) {
        cout << "F(" << i << ") = " << fib_optimized(i) << endl;
    }

    /*
     * KEY TAKEAWAY:
     * =============
     * DP = Recursion + Storage (to avoid recomputation)
     *
     * Steps to solve ANY DP problem:
     * 1. Define the STATE — What information do I need?
     * 2. Define the TRANSITION — How do states relate?
     * 3. Define BASE CASES — What are the trivial answers?
     * 4. Implement (Memo or Tabulation)
     * 5. Optimize space if possible
     */

    return 0;
}

