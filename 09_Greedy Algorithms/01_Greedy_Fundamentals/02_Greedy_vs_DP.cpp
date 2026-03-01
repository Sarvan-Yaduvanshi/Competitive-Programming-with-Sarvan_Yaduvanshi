/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Greedy vs Dynamic Programming — When to Use Which?
 *  Level   : Beginner
 * ============================================================================
 *
 *  TABLE OF CONTENTS:
 *  ──────────────────
 *  1. Greedy vs DP — Side by Side Comparison
 *  2. Decision Framework: When to use Greedy vs DP
 *  3. Example: Coin Change — Greedy FAILS, DP WORKS
 *  4. Example: Activity Selection — Greedy WORKS (no need for DP)
 *  5. Example: 0/1 Knapsack — Greedy FAILS, DP WORKS
 *
 * ============================================================================
 *
 *  ▶ GREEDY vs DP — COMPARISON TABLE:
 *  ┌────────────────────┬──────────────────────┬──────────────────────┐
 *  │     Property       │      GREEDY          │         DP           │
 *  ├────────────────────┼──────────────────────┼──────────────────────┤
 *  │ Approach           │ Top-down, one pass   │ Bottom-up / Top-down │
 *  │ Subproblems        │ Never reconsidered   │ All explored         │
 *  │ Choice             │ Before subproblem    │ After subproblem     │
 *  │ Time Complexity    │ Usually O(n log n)   │ Usually O(n²) or O(n*W) │
 *  │ Space              │ O(1) or O(n)         │ O(n) to O(n²)        │
 *  │ Correctness Proof  │ Exchange argument    │ Optimal substructure │
 *  │ When to use        │ Local choice = global│ Need all subproblems │
 *  │ Difficulty         │ Hard to prove correct│ Easier to prove      │
 *  │ Implementation     │ Usually simpler      │ More complex         │
 *  └────────────────────┴──────────────────────┴──────────────────────┘
 *
 *  ▶ DECISION FRAMEWORK:
 *  ─────────────────────
 *  Ask yourself:
 *  1. Can I solve this by always making the locally best choice?
 *  2. Does making a locally best choice ever hurt the global solution?
 *  3. Can I PROVE the greedy choice is safe? (Exchange argument?)
 *
 *  If YES to 1&3, NO to 2 → USE GREEDY
 *  Otherwise → USE DP
 *
 *  ▶ BOTH NEED OPTIMAL SUBSTRUCTURE:
 *  ─────────────────────────────────
 *  Both Greedy and DP require that an optimal solution contains
 *  optimal solutions to subproblems. The difference:
 *  - Greedy: makes the choice FIRST, then solves one subproblem
 *  - DP: solves ALL subproblems, then makes the best choice
 *
 *  ▶ CLASSIC EXAMPLES:
 *  ───────────────────
 *  GREEDY WORKS: Activity Selection, Huffman Coding, Fractional Knapsack,
 *                MST (Kruskal/Prim), Dijkstra, Interval Scheduling
 *
 *  GREEDY FAILS (need DP): 0/1 Knapsack, Coin Change (general),
 *                           Edit Distance, LCS, LIS, Matrix Chain
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// ============================================================================
// EXAMPLE: Coin Change — Greedy FAILS, DP WORKS
// ============================================================================
// Denominations: {1, 3, 4}, Amount: 6
// Greedy: 4 + 1 + 1 = 3 coins  ❌
// DP:     3 + 3     = 2 coins  ✅

// GREEDY APPROACH (WRONG for arbitrary denominations)
int coinChangeGreedy(vector<int>& coins, int amount) {
    sort(coins.rbegin(), coins.rend());  // Sort descending
    int count = 0;
    for (int coin : coins) {
        count += amount / coin;
        amount %= coin;
    }
    return amount == 0 ? count : -1;
}

// DP APPROACH (ALWAYS CORRECT)
int coinChangeDP(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (coin <= i && dp[i - coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

// ============================================================================
// EXAMPLE: 0/1 Knapsack — Greedy FAILS
// ============================================================================
// Items: {weight: 10, value: 60}, {weight: 20, value: 100}, {weight: 30, value: 120}
// Capacity: 50
//
// Greedy by value/weight ratio: item1(6.0) + item2(5.0) = 160  ❌
// DP optimal: item2(100) + item3(120) = 220                    ✅
//
// Note: Fractional Knapsack CAN be solved greedily!

// ============================================================================
// EXAMPLE: Fractional Knapsack — Greedy WORKS
// ============================================================================
// Same items as above, but we can take fractions
// Greedy by value/weight: item1(all) + item2(all) + item3(2/3) = 240
// This IS optimal! (Proved by exchange argument)

double fractionalKnapsack(vector<pair<int,int>>& items, int capacity) {
    // items[i] = {weight, value}
    // Sort by value/weight ratio (descending)
    sort(items.begin(), items.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return (double)a.second / a.first > (double)b.second / b.first;
    });

    double totalValue = 0.0;
    for (auto& [w, v] : items) {
        if (capacity >= w) {
            totalValue += v;
            capacity -= w;
        } else {
            totalValue += (double)v * capacity / w;  // Take fraction
            break;
        }
    }
    return totalValue;
}

int main() {
    // Coin Change: Greedy vs DP
    cout << "=== Coin Change ===" << endl;
    vector<int> coins = {1, 3, 4};
    int amount = 6;
    cout << "Greedy: " << coinChangeGreedy(coins, amount) << " coins" << endl;  // 3 (wrong!)
    cout << "DP:     " << coinChangeDP(coins, amount) << " coins" << endl;      // 2 (correct!)
    cout << endl;

    // Fractional Knapsack: Greedy works!
    cout << "=== Fractional Knapsack ===" << endl;
    vector<pair<int,int>> items = {{10, 60}, {20, 100}, {30, 120}};
    cout << "Max value: " << fractionalKnapsack(items, 50) << endl;  // 240

    return 0;
}

