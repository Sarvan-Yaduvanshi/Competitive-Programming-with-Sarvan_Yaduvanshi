/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Proof Technique — "Exchange Argument"
 *  Level   : Beginner-Intermediate
 * ============================================================================
 *
 *  ▶ WHAT IS THE "EXCHANGE ARGUMENT"?
 *  ──────────────────────────────────
 *  The Exchange Argument is a powerful proof technique where you:
 *  1. Assume an optimal solution O that differs from greedy solution G
 *  2. Show you can SWAP elements in O to make it more like G
 *     WITHOUT making it worse (or making it better)
 *  3. Repeat swaps until O = G, proving G is optimal
 *
 *  ▶ PROOF TEMPLATE:
 *  ─────────────────
 *  1. Let G be the greedy solution
 *  2. Let O be an optimal solution that differs from G
 *  3. Find the FIRST difference: G chooses x, O chooses y (x ≠ y)
 *  4. Show: swapping y with x in O gives O' where cost(O') ≤ cost(O)
 *  5. O' is still valid AND more similar to G
 *  6. Repeat until O becomes G → G is optimal
 *
 *  ▶ EXAMPLE 1: Minimize Total Weighted Completion Time
 *  ────────────────────────────────────────────────────
 *  Problem: N jobs with processing times p_i and weights w_i
 *  Schedule to minimize Σ(w_i * C_i) where C_i = completion time of job i
 *
 *  Greedy: Sort by p_i / w_i (ascending) — Shortest Job First weighted
 *
 *  Exchange Argument Proof:
 *  - Consider two adjacent jobs i and j in an optimal schedule
 *  - If i comes before j: cost contribution = w_i * p_i + w_j * (p_i + p_j)
 *  - If j comes before i: cost contribution = w_j * p_j + w_i * (p_j + p_i)
 *  - i before j is better when: w_i*p_i + w_j*p_i + w_j*p_j < w_j*p_j + w_i*p_j + w_i*p_i
 *  - Simplify: w_j*p_i < w_i*p_j → p_i/w_i < p_j/w_j
 *  - So sort by p_i/w_i ascending! ✅
 *
 *  ▶ EXAMPLE 2: Minimizing Lateness
 *  ─────────────────────────────────
 *  Problem: N jobs with processing times p_i and deadlines d_i
 *  Schedule to minimize maximum lateness (max over all jobs of finish_i - d_i)
 *
 *  Greedy: Earliest Deadline First (sort by d_i ascending)
 *
 *  Exchange Argument Proof:
 *  - If optimal O has an INVERSION (job i before j where d_i > d_j)
 *  - Swapping i and j: j finishes earlier (good), i finishes later (but d_i > d_j)
 *  - The maximum lateness doesn't increase → swap is safe
 *  - Remove all inversions → we get the greedy schedule → greedy is optimal
 *
 *  ▶ WHEN TO USE EXCHANGE ARGUMENT:
 *  ────────────────────────────────
 *  - Ordering / scheduling problems
 *  - When you need to prove a specific ORDERING is optimal
 *  - When you can compare two adjacent elements and show one order is better
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================================
// EXAMPLE 1: Minimize Total Weighted Completion Time
// ============================================================================
/*
 * GREEDY: Sort jobs by p[i] / w[i] ratio (ascending)
 * PROOF: Exchange argument on adjacent pairs shows this ordering minimizes cost
 */
long long minWeightedCompletion(vector<pair<int,int>>& jobs) {
    // jobs[i] = {processing_time, weight}

    // Sort by p/w ratio ascending (use cross-multiplication to avoid floating point)
    sort(jobs.begin(), jobs.end(), [](const auto& a, const auto& b) {
        return (long long)a.first * b.second < (long long)b.first * a.second;
    });

    long long totalCost = 0, currentTime = 0;
    for (auto& [p, w] : jobs) {
        currentTime += p;
        totalCost += (long long)w * currentTime;
    }
    return totalCost;
}

// ============================================================================
// EXAMPLE 2: Minimize Maximum Lateness
// ============================================================================
/*
 * GREEDY: Earliest Deadline First
 * PROOF: Any inversion in a schedule can be swapped without increasing max lateness
 */
int minMaxLateness(vector<pair<int,int>>& jobs) {
    // jobs[i] = {processing_time, deadline}

    // Sort by deadline (ascending)
    sort(jobs.begin(), jobs.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    int maxLateness = 0, currentTime = 0;
    for (auto& [p, d] : jobs) {
        currentTime += p;
        int lateness = max(0, currentTime - d);
        maxLateness = max(maxLateness, lateness);
    }
    return maxLateness;
}

int main() {
    // Example 1: Weighted Completion Time
    cout << "=== Weighted Completion Time ===" << endl;
    vector<pair<int,int>> jobs1 = {{3, 4}, {1, 3}, {2, 1}};
    // p/w ratios: 3/4=0.75, 1/3=0.33, 2/1=2.0
    // Optimal order: job2(1/3=0.33), job1(3/4=0.75), job3(2/1=2.0)
    cout << "Min weighted completion: " << minWeightedCompletion(jobs1) << endl;

    cout << endl;

    // Example 2: Maximum Lateness
    cout << "=== Maximum Lateness ===" << endl;
    vector<pair<int,int>> jobs2 = {{3, 6}, {2, 8}, {1, 9}, {4, 9}, {3, 14}, {2, 15}};
    cout << "Min max lateness: " << minMaxLateness(jobs2) << endl;

    return 0;
}

