/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Custom Sorting for Greedy — Comparator Design
 *  Level   : Intermediate
 * ============================================================================
 *
 *  KEY CONCEPT: In greedy, the sorting comparator IS the greedy strategy.
 *  Designing the right comparator = solving the problem.
 *
 *  ▶ COMMON SORTING PATTERNS:
 *  ──────────────────────────
 *  1. Sort by END TIME → Interval scheduling (maximize count)
 *  2. Sort by DEADLINE → Minimize lateness
 *  3. Sort by VALUE/WEIGHT ratio → Knapsack, weighted scheduling
 *  4. Sort by DIFFERENCE (cost_a - cost_b) → Two-city scheduling
 *  5. Sort by CUSTOM COMPARISON → "Which should come first?"
 *
 *  ▶ HOW TO DESIGN A COMPARATOR:
 *  ─────────────────────────────
 *  Ask: "Given two elements A and B, is (A before B) better than (B before A)?"
 *  Compare the cost/benefit of both orderings.
 *  If cost(A,B) < cost(B,A), then A should come first.
 *
 *  ▶ PROVING COMPARATOR CORRECTNESS:
 *  ──────────────────────────────────
 *  The comparator must define a TOTAL ORDER (transitive, antisymmetric, total).
 *  Use the exchange argument: show any adjacent inversion can be fixed.
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// ============================================================================
// EXAMPLE 1: Largest Number (LC 179)
// Given [3, 30, 34, 5, 9], form the largest number: "9534330"
// ============================================================================
string largestNumber(vector<int>& nums) {
    vector<string> strs;
    for (int n : nums) strs.push_back(to_string(n));

    // Custom comparator: A+B vs B+A
    // "30" vs "3": "303" < "330" → "3" should come first
    sort(strs.begin(), strs.end(), [](const string& a, const string& b) {
        return a + b > b + a;
    });

    if (strs[0] == "0") return "0";

    string result;
    for (auto& s : strs) result += s;
    return result;
}

// ============================================================================
// EXAMPLE 2: Two City Scheduling (LC 1029)
// Sort by difference (cost_a - cost_b) to decide which city to assign
// ============================================================================
int twoCityScheduling(vector<vector<int>>& costs) {
    // Sort by (cost_to_A - cost_to_B) ascending
    // People with biggest savings by going to A should go to A
    sort(costs.begin(), costs.end(), [](auto& a, auto& b) {
        return (a[0] - a[1]) < (b[0] - b[1]);
    });

    int n = costs.size() / 2;
    int totalCost = 0;
    for (int i = 0; i < 2 * n; i++) {
        totalCost += (i < n) ? costs[i][0] : costs[i][1];
    }
    return totalCost;
}

// ============================================================================
// EXAMPLE 3: Minimum Number of Arrows (LC 452)
// Sort by end point, greedily shoot at the end of each balloon
// ============================================================================
int minArrows(vector<vector<int>>& points) {
    sort(points.begin(), points.end(), [](auto& a, auto& b) {
        return a[1] < b[1]; // Sort by end point
    });

    int arrows = 1;
    int arrowPos = points[0][1];

    for (int i = 1; i < (int)points.size(); i++) {
        if (points[i][0] > arrowPos) { // Not hit by current arrow
            arrows++;
            arrowPos = points[i][1];
        }
    }
    return arrows;
}

int main() {
    // Example 1
    vector<int> nums = {3, 30, 34, 5, 9};
    cout << "Largest number: " << largestNumber(nums) << endl; // "9534330"

    // Example 2
    vector<vector<int>> costs = {{10,20}, {30,200}, {400,50}, {30,20}};
    cout << "Min cost: " << twoCityScheduling(costs) << endl; // 110

    return 0;
}

