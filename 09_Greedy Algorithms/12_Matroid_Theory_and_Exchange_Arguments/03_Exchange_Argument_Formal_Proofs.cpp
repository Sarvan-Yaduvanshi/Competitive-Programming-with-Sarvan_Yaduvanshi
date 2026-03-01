/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Exchange Argument — Formal Proofs (5+ Examples)
 *  Level   : Expert
 * ============================================================================
 *
 *  ▶ EXCHANGE ARGUMENT TEMPLATE (Reminder):
 *  ─────────────────────────────────────────
 *  1. Assume OPT differs from GREEDY at position i
 *  2. Show we can SWAP the choice at position i to match GREEDY
 *     without worsening the solution
 *  3. Repeat → OPT becomes GREEDY → GREEDY is optimal
 *
 *  Below are 5 complete exchange argument proofs for classic problems.
 *
 * ============================================================================
 *
 *  ▶ PROOF 1: ACTIVITY SELECTION
 *  ─────────────────────────────
 *  Greedy: Pick activity with earliest finish time f_i.
 *
 *  Proof: Let O be an optimal solution. Let o_1 be its first activity.
 *  Let g_1 be greedy's first activity. We know f(g_1) ≤ f(o_1).
 *
 *  Swap o_1 with g_1 in O. Since f(g_1) ≤ f(o_1), no conflict is introduced
 *  with o_2, o_3, ... So O' = {g_1, o_2, o_3, ...} is still valid.
 *  |O'| = |O|. Repeat for remaining positions. ✅
 *
 *  ──────────────────────────────────────────────────────────────
 *
 *  ▶ PROOF 2: FRACTIONAL KNAPSACK
 *  ───────────────────────────────
 *  Greedy: Take item with highest value/weight ratio first.
 *
 *  Proof: Let O be optimal. Suppose O takes less of item A (highest ratio)
 *  and more of item B (lower ratio).
 *
 *  Swap: Take ε more of A, ε*(w_A/w_B) less of B (to keep total weight same).
 *  Value change: ε*(v_A/w_A) - ε*(w_A/w_B)*(v_B/w_B) = ε*w_A/w_B * (v_A/w_A - v_B/w_B)
 *  Since ratio_A > ratio_B, this is positive → O' is better. Contradiction. ✅
 *
 *  ──────────────────────────────────────────────────────────────
 *
 *  ▶ PROOF 3: MINIMIZING LATENESS (EDF)
 *  ─────────────────────────────────────
 *  Greedy: Earliest Deadline First.
 *
 *  Proof: If optimal O has an inversion (job i before j with d_i > d_j):
 *  - Both finish before same time (adjacent, same total time)
 *  - After swap: j finishes earlier (lateness may decrease), i finishes
 *    at same time j used to (but d_i > d_j, so lateness doesn't increase)
 *  - max(lateness_i', lateness_j') ≤ max(lateness_i, lateness_j)
 *  Remove all inversions → get EDF order → greedy is optimal. ✅
 *
 *  ──────────────────────────────────────────────────────────────
 *
 *  ▶ PROOF 4: HUFFMAN CODING
 *  ─────────────────────────
 *  Greedy: Merge two lowest-frequency nodes.
 *
 *  Proof: Let x, y be the two lowest-frequency characters.
 *  Claim: There exists an optimal tree where x and y are siblings at max depth.
 *
 *  If not, let a, b be siblings at max depth. Since freq(x), freq(y) are smallest
 *  and a, b are deepest: swapping x↔a and y↔b doesn't increase total cost
 *  (lower frequency at deeper level is same or better). ✅
 *
 *  ──────────────────────────────────────────────────────────────
 *
 *  ▶ PROOF 5: WEIGHTED COMPLETION TIME (SMITH'S RULE)
 *  ──────────────────────────────────────────────────
 *  Greedy: Sort by p_i/w_i ascending (processing_time / weight).
 *
 *  Proof: Consider adjacent jobs i, j. If p_i/w_i > p_j/w_j but i is before j:
 *  Cost of (i,j) order: w_i*p_i + w_j*(p_i + p_j)
 *  Cost of (j,i) order: w_j*p_j + w_i*(p_j + p_i)
 *
 *  Difference: w_j*p_i - w_i*p_j > 0 (since p_i/w_i > p_j/w_j → p_i*w_j > p_j*w_i)
 *  So (i,j) costs MORE → swap to (j,i). ✅
 *
 * ============================================================================
 */

#include <iostream>
using namespace std;

/*
 * This file is primarily a THEORY file with formal proofs.
 * The implementations are in their respective modules.
 *
 * KEY TAKEAWAY:
 * The exchange argument is YOUR most important tool for proving
 * greedy correctness in contests. Practice writing these proofs!
 *
 * When you think of a greedy approach:
 * 1. Assume there's an optimal solution that differs from yours
 * 2. Find the first difference
 * 3. Show that swapping makes it no worse
 * 4. Conclude your greedy is optimal
 */

int main() {
    cout << "=== Exchange Argument Proofs ===" << endl;
    cout << "This is a theory file. See the block comments above." << endl;
    cout << endl;
    cout << "5 Proven Greedy Algorithms:" << endl;
    cout << "1. Activity Selection (earliest finish)" << endl;
    cout << "2. Fractional Knapsack (best ratio first)" << endl;
    cout << "3. Minimize Lateness (earliest deadline first)" << endl;
    cout << "4. Huffman Coding (merge lowest frequency)" << endl;
    cout << "5. Weighted Completion Time (Smith's Rule: p/w ascending)" << endl;
    return 0;
}

