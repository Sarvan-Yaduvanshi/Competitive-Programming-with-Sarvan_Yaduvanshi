/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : When Greedy FAILS — Counter-Examples
 *  Level   : Expert
 * ============================================================================
 *
 *  Understanding when greedy fails is JUST AS IMPORTANT as knowing when it works.
 *  Here are classic problems where greedy gives wrong answers.
 *
 *  ▶ FAILURE 1: 0/1 KNAPSACK
 *  ──────────────────────────
 *  Items: {w=10,v=60}, {w=20,v=100}, {w=30,v=120}. Capacity=50
 *  Greedy (by v/w): Take item1(6.0) + item2(5.0) = 160 ❌
 *  Optimal: item2(100) + item3(120) = 220 ✅
 *  WHY: Can't take fractions. Greedy ratio doesn't account for wasted space.
 *
 *  ▶ FAILURE 2: COIN CHANGE (Arbitrary Denominations)
 *  ──────────────────────────────────────────────────
 *  Coins = {1, 3, 4}, Amount = 6
 *  Greedy: 4+1+1 = 3 coins ❌
 *  Optimal: 3+3 = 2 coins ✅
 *  WHY: Picking largest coin forces suboptimal choices for remainder.
 *
 *  ▶ FAILURE 3: LONGEST INCREASING SUBSEQUENCE
 *  ────────────────────────────────────────────
 *  Array: [3, 1, 2, 4]
 *  Greedy (always extend): might pick 3, 4 → length 2 ❌
 *  Optimal: 1, 2, 4 → length 3 ✅
 *  WHY: Locally best starting point isn't globally best.
 *
 *  ▶ FAILURE 4: VERTEX COVER
 *  ─────────────────────────
 *  Greedy (pick highest degree vertex): Can be O(log n) times worse than optimal.
 *  This is an NP-hard problem — no polynomial greedy can solve it optimally.
 *
 *  ▶ FAILURE 5: TRAVELING SALESMAN (TSP)
 *  ─────────────────────────────────────
 *  Nearest-neighbor greedy can be arbitrarily bad.
 *  NP-hard → no polynomial algorithm (assuming P ≠ NP).
 *
 *  ▶ FAILURE 6: GRAPH COLORING
 *  ───────────────────────────
 *  Greedy coloring depends on vertex ORDER.
 *  Bad ordering can use O(n) colors when O(1) suffice.
 *
 *  ▶ HOW TO DETECT GREEDY FAILURE:
 *  ────────────────────────────────
 *  1. Find a small counter-example (try N=3 or N=4)
 *  2. Check if locally optimal ≠ globally optimal
 *  3. Check if the problem has matroid structure
 *  4. If greedy fails → try DP, or prove greedy first!
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// Demonstration: Greedy vs DP for 0/1 Knapsack
int knapsackGreedy(vector<pair<int,int>>& items, int W) {
    // Sort by v/w ratio
    sort(items.begin(), items.end(), [](auto& a, auto& b) {
        return (double)a.second / a.first > (double)b.second / b.first;
    });
    int totalVal = 0, remaining = W;
    for (auto& [w, v] : items) {
        if (w <= remaining) {
            totalVal += v;
            remaining -= w;
        }
    }
    return totalVal;
}

int knapsackDP(vector<pair<int,int>>& items, int W) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i-1][w];
            if (items[i-1].first <= w)
                dp[i][w] = max(dp[i][w], dp[i-1][w - items[i-1].first] + items[i-1].second);
        }
    }
    return dp[n][W];
}

int main() {
    cout << "=== When Greedy FAILS ===" << endl;

    // 0/1 Knapsack
    vector<pair<int,int>> items = {{10,60}, {20,100}, {30,120}};
    cout << "\n0/1 Knapsack (W=50):" << endl;
    cout << "  Greedy: " << knapsackGreedy(items, 50) << endl; // 160 (WRONG)
    cout << "  DP:     " << knapsackDP(items, 50) << endl;     // 220 (CORRECT)

    // Coin Change
    cout << "\nCoin Change {1,3,4}, amount=6:" << endl;
    cout << "  Greedy: 4+1+1 = 3 coins (WRONG)" << endl;
    cout << "  DP:     3+3   = 2 coins (CORRECT)" << endl;

    cout << "\n=== LESSON ===" << endl;
    cout << "Always PROVE your greedy or find a counter-example!" << endl;
    cout << "If unsure, try brute force on small inputs to validate." << endl;

    return 0;
}

