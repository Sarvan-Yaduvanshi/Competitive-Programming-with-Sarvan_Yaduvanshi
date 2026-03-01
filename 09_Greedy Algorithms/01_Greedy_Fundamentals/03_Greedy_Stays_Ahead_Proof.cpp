/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Proof Technique — "Greedy Stays Ahead"
 *  Level   : Beginner-Intermediate
 * ============================================================================
 *
 *  ▶ WHAT IS "GREEDY STAYS AHEAD"?
 *  ───────────────────────────────
 *  This is the most common proof technique for greedy algorithms.
 *
 *  IDEA: Show that at every step, the greedy solution is "at least as good"
 *  as any other solution. If greedy is never behind, it must be optimal.
 *
 *  ▶ PROOF TEMPLATE:
 *  ─────────────────
 *  1. Let G = {g1, g2, ..., gk} be the greedy solution
 *  2. Let O = {o1, o2, ..., om} be ANY optimal solution
 *  3. PROVE by induction: for all i, g_i is "at least as good" as o_i
 *     (define "as good" based on the problem — earlier finish, less cost, etc.)
 *  4. CONCLUDE: Since greedy never falls behind, |G| ≥ |O| (or cost(G) ≤ cost(O))
 *
 *  ▶ EXAMPLE: Activity Selection Proof
 *  ────────────────────────────────────
 *  Claim: Greedy (pick earliest finish time) gives maximum activities.
 *
 *  Proof:
 *  - Let G = {g1, g2, ..., gk} sorted by finish time (greedy solution)
 *  - Let O = {o1, o2, ..., om} sorted by finish time (any optimal solution)
 *  - We prove: finish(g_i) ≤ finish(o_i) for all i (greedy stays ahead)
 *
 *  Base case: finish(g1) ≤ finish(o1)
 *    Because greedy picks the EARLIEST finishing activity, g1 finishes
 *    no later than any other choice, including o1.
 *
 *  Inductive step: Assume finish(g_i) ≤ finish(o_i)
 *    Then o_{i+1} starts after finish(o_i) ≥ finish(g_i) (non-overlapping)
 *    So o_{i+1} is a valid candidate when greedy makes choice i+1
 *    Greedy picks the earliest-finishing valid activity: finish(g_{i+1}) ≤ finish(o_{i+1})
 *
 *  Conclusion: Greedy stays ahead → if k < m, there would be more valid
 *  activities after g_k, contradicting that greedy stopped. So k ≥ m.
 *  Since m is optimal, k = m. Greedy is optimal! ✅
 *
 *  ▶ WHEN TO USE THIS PROOF:
 *  ─────────────────────────
 *  - Maximization problems (max items, max profit)
 *  - When you can define a natural ordering of solution elements
 *  - When greedy makes a "safe" choice that doesn't close off options
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Activity Selection with detailed proof-aware implementation
int activitySelectionProved(vector<pair<int,int>>& activities) {
    /*
     * GREEDY STRATEGY: Pick activity with earliest finish time
     *
     * PROOF (Greedy Stays Ahead):
     * At step i, greedy's finish time ≤ optimal's finish time
     * → Greedy always has "more room" for future activities
     * → Greedy selects at least as many activities as optimal
     */

    // Step 1: Sort by finish time
    sort(activities.begin(), activities.end(),
         [](const auto& a, const auto& b) { return a.second < b.second; });

    int count = 0;
    int lastFinish = -1;

    for (auto& [start, end] : activities) {
        // Step 2: Greedy choice — take if compatible
        if (start >= lastFinish) {
            count++;
            lastFinish = end;
            // INVARIANT: lastFinish ≤ finish time of i-th activity in ANY optimal solution
        }
    }

    return count;
}

int main() {
    vector<pair<int,int>> activities = {{1,3}, {2,5}, {4,7}, {1,8}, {5,9}, {8,10}};
    cout << "Max activities: " << activitySelectionProved(activities) << endl;
    // Greedy picks: (1,3), (4,7), (8,10) → 3 activities
    return 0;
}

