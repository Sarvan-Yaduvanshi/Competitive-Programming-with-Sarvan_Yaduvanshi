/*
 * ============================================================================
 *             STATE DEFINITION & TRANSITION FORMULA
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : DP Foundations — State, Transition, and Base Cases
 * Level   : ⭐ Beginner
 * ============================================================================
 *
 * THE THREE PILLARS OF DP:
 * =========================
 *
 * 1. STATE DEFINITION (What does dp[...] represent?)
 *    ─ The most important step!
 *    ─ State must capture ALL information needed to make decisions
 *    ─ Think: "What changes between subproblems?"
 *
 *    Common state variables:
 *    • Index i (current position in array/string)
 *    • Remaining capacity/amount
 *    • Boolean flags (used/not used)
 *    • Previous element value
 *    • Bitmask of used elements
 *
 * 2. TRANSITION FORMULA (How do states relate?)
 *    ─ The recurrence relation
 *    ─ How to compute dp[current] from dp[smaller states]
 *    ─ Think: "What CHOICES do I have at this state?"
 *
 * 3. BASE CASES (What are the trivial answers?)
 *    ─ States where answer is immediately known
 *    ─ Usually: empty array, zero capacity, reached boundary
 *
 * STATE DESIGN METHODOLOGY:
 * ==========================
 * 1. What CHOICES do I have at each step?
 * 2. What INFORMATION do I need to make that choice?
 * 3. What is the MINIMUM information that uniquely identifies a subproblem?
 * 4. How many unique states are there? (determines time complexity)
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * EXAMPLE 1: House Robber (LeetCode 198)
 * ========================================
 * Rob houses along a street, can't rob two adjacent houses.
 * Maximize total money.
 *
 * STATE DESIGN THOUGHT PROCESS:
 * • What changes? → Current house index
 * • What info needed? → Can I rob this house? → Depends on whether I robbed previous
 * • Simplification: dp[i] = max money from first i houses
 *
 * STATE:      dp[i] = max money considering houses 0..i
 * TRANSITION: dp[i] = max(dp[i-1],         ← skip house i
 *                         dp[i-2] + a[i])   ← rob house i
 * BASE:       dp[0] = a[0], dp[1] = max(a[0], a[1])
 * ANSWER:     dp[n-1]
 */
int houseRobber(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];

    // Tabulation
    vector<int> dp(n);
    dp[0] = nums[0];                      // Base case 1
    dp[1] = max(nums[0], nums[1]);        // Base case 2

    for (int i = 2; i < n; i++) {
        dp[i] = max(dp[i-1],              // Skip house i
                    dp[i-2] + nums[i]);    // Rob house i
    }
    return dp[n-1];
}

/*
 * EXAMPLE 2: Decode Ways (LeetCode 91)
 * ======================================
 * Given digit string, count ways to decode to letters (A=1, ..., Z=26).
 *
 * STATE DESIGN:
 * • What changes? → Current position in string
 * • dp[i] = number of ways to decode s[i..n-1]
 *
 * TRANSITION:
 *   dp[i] = dp[i+1]                    (if s[i] is valid single digit: 1-9)
 *          + dp[i+2]                    (if s[i..i+1] is valid: 10-26)
 *
 * BASE: dp[n] = 1 (empty string = 1 way)
 */
int decodeWays(string& s) {
    int n = s.size();
    vector<int> dp(n + 1, 0);
    dp[n] = 1;  // Base: empty string

    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '0') {
            dp[i] = 0;  // '0' can't be decoded alone
        } else {
            dp[i] = dp[i + 1];  // Single digit

            // Two digits
            if (i + 1 < n) {
                int twoDigit = (s[i] - '0') * 10 + (s[i + 1] - '0');
                if (twoDigit >= 10 && twoDigit <= 26) {
                    dp[i] += dp[i + 2];
                }
            }
        }
    }
    return dp[0];
}

/*
 * EXAMPLE 3: Jump Game II (LeetCode 45) — DP approach
 * =====================================================
 * Given array of jump lengths, find minimum jumps to reach end.
 *
 * STATE:    dp[i] = min jumps to reach position i
 * TRANSITION: dp[j] = min(dp[j], dp[i] + 1) for all j reachable from i
 * BASE:    dp[0] = 0
 */
int jumpGame(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, INT_MAX);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        if (dp[i] == INT_MAX) continue;
        for (int j = 1; j <= nums[i] && i + j < n; j++) {
            dp[i + j] = min(dp[i + j], dp[i] + 1);
        }
    }
    return dp[n - 1];
}

/*
 * EXAMPLE 4: Paint House (3 colors)
 * ===================================
 * Paint n houses with 3 colors. No two adjacent same color.
 * cost[i][c] = cost to paint house i with color c.
 *
 * STATE:    dp[i][c] = min cost to paint houses 0..i, house i is color c
 * TRANSITION: dp[i][c] = cost[i][c] + min(dp[i-1][other colors])
 * BASE:    dp[0][c] = cost[0][c]
 */
int paintHouse(vector<vector<int>>& cost) {
    int n = cost.size();
    if (n == 0) return 0;

    vector<vector<int>> dp(n, vector<int>(3));
    dp[0] = cost[0];  // Base

    for (int i = 1; i < n; i++) {
        dp[i][0] = cost[i][0] + min(dp[i-1][1], dp[i-1][2]);
        dp[i][1] = cost[i][1] + min(dp[i-1][0], dp[i-1][2]);
        dp[i][2] = cost[i][2] + min(dp[i-1][0], dp[i-1][1]);
    }
    return *min_element(dp[n-1].begin(), dp[n-1].end());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "============================================" << endl;
    cout << "   STATE & TRANSITION DESIGN — DEMO" << endl;
    cout << "============================================" << endl;

    // House Robber
    vector<int> houses = {2, 7, 9, 3, 1};
    cout << "\n--- House Robber ---" << endl;
    cout << "Houses: ";
    for (int h : houses) cout << h << " ";
    cout << "\nMax rob: " << houseRobber(houses) << endl;
    // Expected: 2 + 9 + 1 = 12

    // Decode Ways
    string code = "226";
    cout << "\n--- Decode Ways ---" << endl;
    cout << "String: \"" << code << "\"" << endl;
    cout << "Ways: " << decodeWays(code) << endl;
    // "226" → "2,2,6" / "22,6" / "2,26" → 3 ways

    // Jump Game
    vector<int> jumps = {2, 3, 1, 1, 4};
    cout << "\n--- Jump Game II ---" << endl;
    cout << "Array: ";
    for (int j : jumps) cout << j << " ";
    cout << "\nMin jumps: " << jumpGame(jumps) << endl;

    // Paint House
    vector<vector<int>> paintCost = {{17,2,17}, {16,16,5}, {14,3,19}};
    cout << "\n--- Paint House ---" << endl;
    cout << "Min cost: " << paintHouse(paintCost) << endl;
    // House 0: blue(2), House 1: green(5), House 2: blue(3) → 10

    cout << "\n============================================" << endl;
    cout << "  STATE DESIGN CHEAT SHEET:" << endl;
    cout << "  1. Ask: What info do I NEED?" << endl;
    cout << "  2. Ask: What CHOICES do I have?" << endl;
    cout << "  3. State = minimum info to decide" << endl;
    cout << "  4. Transition = choice → next state" << endl;
    cout << "  5. Base = trivially known answers" << endl;
    cout << "============================================" << endl;

    return 0;
}

