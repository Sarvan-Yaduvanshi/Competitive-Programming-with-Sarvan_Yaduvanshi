/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Greedy Choice Property & Optimal Substructure
 *  Level   : Beginner
 * ============================================================================
 *
 *  ▶ THE TWO PILLARS OF GREEDY ALGORITHMS:
 *  ────────────────────────────────────────
 *
 *  PILLAR 1: GREEDY CHOICE PROPERTY
 *  ─────────────────────────────────
 *  "We can assemble a globally optimal solution by making locally optimal choices."
 *
 *  This means: At each decision point, we pick what looks best RIGHT NOW,
 *  and this choice is part of SOME optimal solution.
 *
 *  How to verify:
 *  - Can we always find an optimal solution that includes the greedy choice?
 *  - Does the greedy choice NOT eliminate all optimal solutions?
 *
 *  PILLAR 2: OPTIMAL SUBSTRUCTURE
 *  ──────────────────────────────
 *  "An optimal solution to the problem contains optimal solutions to subproblems."
 *
 *  This means: After making a greedy choice, the remaining problem is a
 *  SMALLER instance of the same problem, and solving it optimally gives
 *  the overall optimal solution.
 *
 *  Note: DP also requires optimal substructure!
 *  The difference: Greedy makes the choice FIRST, then solves the subproblem.
 *  DP solves ALL subproblems first, then makes the choice.
 *
 *  ▶ PROVING GREEDY WORKS — CHECKLIST:
 *  ────────────────────────────────────
 *  □ Step 1: Define what "locally optimal" means for your problem
 *  □ Step 2: Prove Greedy Choice Property:
 *            "There exists an optimal solution containing the greedy choice"
 *  □ Step 3: Prove Optimal Substructure:
 *            "After the greedy choice, remaining problem has same structure"
 *  □ Step 4: (Optional) Use Exchange Argument or Stays-Ahead for formal proof
 *
 *  ▶ EXAMPLES WHERE BOTH PROPERTIES HOLD:
 *  ──────────────────────────────────────
 *
 *  1. ACTIVITY SELECTION:
 *     - Greedy Choice: Pick earliest-finishing activity
 *     - Substructure: After picking, solve for remaining compatible activities
 *
 *  2. HUFFMAN CODING:
 *     - Greedy Choice: Merge two lowest-frequency nodes
 *     - Substructure: After merge, solve Huffman for n-1 nodes
 *
 *  3. FRACTIONAL KNAPSACK:
 *     - Greedy Choice: Take item with best value/weight ratio
 *     - Substructure: After taking, solve knapsack with remaining capacity
 *
 *  4. DIJKSTRA'S ALGORITHM:
 *     - Greedy Choice: Process node with smallest tentative distance
 *     - Substructure: After processing, remaining nodes form a subproblem
 *
 *  ▶ EXAMPLES WHERE GREEDY CHOICE PROPERTY FAILS:
 *  ───────────────────────────────────────────────
 *
 *  1. 0/1 KNAPSACK:
 *     Greedy by ratio might skip an item that's part of optimal solution
 *
 *  2. LONGEST PATH (DAG):
 *     Greedy picks longest edge first, but this can lead to dead ends
 *
 *  3. COIN CHANGE (general):
 *     Picking largest coin first can use more coins than needed
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * DEMONSTRATION: Checking Both Properties for Fractional Knapsack
 *
 * Property 1 (Greedy Choice):
 *   The item with the highest value/weight ratio MUST be in some optimal solution.
 *   Proof: If it's not, we can exchange a fraction of another item for a fraction
 *   of this item and get equal or better total value. Contradiction.
 *
 * Property 2 (Optimal Substructure):
 *   After taking as much as possible of the best-ratio item, the remaining
 *   problem is a fractional knapsack with smaller capacity → same structure!
 */
double fractionalKnapsack(vector<pair<int,int>>& items, int W) {
    // Sort by value/weight ratio (descending)
    sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
        return (double)a.second / a.first > (double)b.second / b.first;
    });

    double totalValue = 0.0;
    int remainingCapacity = W;

    for (auto& [weight, value] : items) {
        if (remainingCapacity <= 0) break;

        // GREEDY CHOICE: Take as much of the best-ratio item as possible
        int take = min(weight, remainingCapacity);
        totalValue += (double)value * take / weight;
        remainingCapacity -= take;
        // OPTIMAL SUBSTRUCTURE: Now solve knapsack(remaining_items, remaining_capacity)
    }

    return totalValue;
}

int main() {
    cout << "=== Greedy Choice + Optimal Substructure Demo ===" << endl;

    vector<pair<int,int>> items = {{10, 60}, {20, 100}, {30, 120}};
    // Ratios: 6.0, 5.0, 4.0

    cout << "Items: {w=10,v=60}, {w=20,v=100}, {w=30,v=120}" << endl;
    cout << "Capacity: 50" << endl;
    cout << "Greedy Choice: Take item with ratio 6.0 first (all 10 units)" << endl;
    cout << "Subproblem: Remaining capacity 40, remaining items" << endl;
    cout << "Max value: " << fractionalKnapsack(items, 50) << endl; // 240

    return 0;
}

