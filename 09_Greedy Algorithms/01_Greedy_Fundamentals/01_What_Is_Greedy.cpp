/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : What is Greedy Algorithm?
 *  Level   : Beginner
 * ============================================================================
 *
 *  TABLE OF CONTENTS:
 *  ──────────────────
 *  1. Definition & Intuition
 *  2. Real-Life Analogies
 *  3. How Greedy Works (Step-by-Step)
 *  4. When Greedy Works vs Fails
 *  5. Simple Example: Coin Change (Greedy version)
 *  6. Simple Example: Activity Selection
 *
 * ============================================================================
 *
 *  ▶ WHAT IS A GREEDY ALGORITHM?
 *  ─────────────────────────────
 *  A Greedy Algorithm builds up a solution piece by piece, always choosing
 *  the NEXT piece that offers the most IMMEDIATE benefit (local optimum),
 *  without reconsidering previous choices.
 *
 *  KEY IDEA: At each step, make the choice that LOOKS BEST RIGHT NOW.
 *
 *  ▶ REAL-LIFE ANALOGIES:
 *  ──────────────────────
 *  1. MAKING CHANGE: If someone asks for 36 cents change, you pick the
 *     largest coin that fits: 25¢, then 10¢, then 1¢ → 3 coins.
 *     (This works for US coins but NOT for all coin systems!)
 *
 *  2. EATING BUFFET: You pick the most appealing dish first, then the
 *     next most appealing, etc. You never go back and swap dishes.
 *
 *  3. DRIVING GPS: At each intersection, take the road that seems shortest
 *     to the destination. (This is essentially Dijkstra's algorithm!)
 *
 *  4. JOB INTERVIEW: If you have multiple job offers, accept the best one
 *     and decline the rest. You don't reconsider.
 *
 *  ▶ GENERAL TEMPLATE:
 *  ───────────────────
 *  1. Sort / organize the input (if needed)
 *  2. Initialize solution as empty
 *  3. For each element in the input:
 *     a. Check if this element can be added to the solution (feasibility)
 *     b. If yes, add it (greedy choice)
 *     c. Check if we have a complete solution (solution check)
 *  4. Return the solution
 *
 *  ▶ WHEN DOES GREEDY WORK?
 *  ────────────────────────
 *  TWO conditions must hold:
 *
 *  1. GREEDY CHOICE PROPERTY:
 *     A global optimum can be arrived at by making a locally optimal choice.
 *     i.e., we can assemble a global solution by selecting local optima.
 *
 *  2. OPTIMAL SUBSTRUCTURE:
 *     An optimal solution to the problem contains optimal solutions to
 *     subproblems. (Same property needed for DP!)
 *
 *  ▶ WHEN DOES GREEDY FAIL?
 *  ────────────────────────
 *  - 0/1 Knapsack: Greedy by value/weight ratio doesn't give optimal
 *  - Coin Change with arbitrary denominations: {1, 3, 4} making 6
 *    Greedy: 4+1+1 = 3 coins. Optimal: 3+3 = 2 coins!
 *  - Longest Path in a graph (NP-hard)
 *  - Traveling Salesman Problem (NP-hard)
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================================
// EXAMPLE 1: Coin Change (Greedy) — Works for standard denominations
// ============================================================================
/*
 * Given: Standard US coin denominations {25, 10, 5, 1}
 * Goal : Make 'amount' cents using minimum number of coins
 *
 * WHY GREEDY WORKS HERE:
 * Each larger coin is a multiple of smaller ones (or close to it),
 * so picking the largest possible coin never leads to a worse solution.
 *
 * WHY GREEDY FAILS for {1, 3, 4} and amount = 6:
 * Greedy picks 4 → remaining 2 → picks 1+1 → total 3 coins
 * Optimal: 3+3 = 2 coins
 */
int minCoinsGreedy(int amount) {
    vector<int> coins = {25, 10, 5, 1};
    int count = 0;

    for (int coin : coins) {
        count += amount / coin;  // Take as many of this coin as possible
        amount %= coin;           // Remaining amount
    }

    return count;
}

// ============================================================================
// EXAMPLE 2: Activity Selection — Classic Greedy Problem
// ============================================================================
/*
 * Given: N activities with start and end times
 * Goal : Select maximum number of non-overlapping activities
 *
 * GREEDY STRATEGY: Always pick the activity that finishes earliest
 *
 * WHY IT WORKS:
 * By choosing the earliest-finishing activity, we leave the most room
 * for subsequent activities → maximizes the count.
 *
 * PROOF (Greedy Stays Ahead):
 * Let G = greedy solution, O = any optimal solution
 * We can show that at every step, greedy's latest finish time ≤ optimal's
 * Therefore |G| ≥ |O|, so greedy IS optimal.
 */
int activitySelection(vector<pair<int,int>>& activities) {
    // Sort by end time (greedy criterion)
    sort(activities.begin(), activities.end(),
         [](const pair<int,int>& a, const pair<int,int>& b) {
             return a.second < b.second;
         });

    int count = 1;  // Select first activity
    int lastEnd = activities[0].second;

    for (int i = 1; i < (int)activities.size(); i++) {
        if (activities[i].first >= lastEnd) {  // Non-overlapping?
            count++;
            lastEnd = activities[i].second;
        }
    }

    return count;
}

// ============================================================================
// MAIN — Demonstration
// ============================================================================
int main() {
    // Example 1: Coin Change
    cout << "=== Coin Change (Greedy) ===" << endl;
    int amount = 36;
    cout << "Amount: " << amount << " cents" << endl;
    cout << "Minimum coins: " << minCoinsGreedy(amount) << endl;
    // Output: 3 (25 + 10 + 1)

    cout << endl;

    // Example 2: Activity Selection
    cout << "=== Activity Selection ===" << endl;
    vector<pair<int,int>> activities = {{1,4}, {3,5}, {0,6}, {5,7}, {3,9}, {5,9}, {6,10}, {8,11}, {8,12}, {2,14}, {12,16}};
    cout << "Max non-overlapping activities: " << activitySelection(activities) << endl;
    // Output: 4 (activities ending at 4, 7, 11, 16)

    return 0;
}

