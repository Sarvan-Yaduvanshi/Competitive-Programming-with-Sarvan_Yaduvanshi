/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Matroid Definition & Properties
 *  Level   : Expert
 * ============================================================================
 *
 *  ▶ WHAT IS A MATROID?
 *  ────────────────────
 *  A matroid M = (S, I) where:
 *  - S = finite ground set (e.g., edges of a graph)
 *  - I = collection of "independent sets" (subsets of S)
 *
 *  THREE PROPERTIES (Matroid Axioms):
 *  1. EMPTY SET:     ∅ ∈ I (the empty set is independent)
 *  2. HEREDITARY:    If A ∈ I and B ⊆ A, then B ∈ I
 *                    (subset of independent set is independent)
 *  3. EXCHANGE:      If A, B ∈ I and |A| < |B|, then ∃ x ∈ B\A
 *                    such that A ∪ {x} ∈ I
 *                    (can always grow a smaller independent set)
 *
 *  ▶ WHY DOES THIS MATTER?
 *  ───────────────────────
 *  THEOREM (Rado-Edmonds): The greedy algorithm finds the maximum-weight
 *  independent set if and only if I forms a matroid.
 *
 *  This means: If your problem has matroid structure, greedy is GUARANTEED optimal!
 *
 *  ▶ TYPES OF MATROIDS:
 *  ────────────────────
 *  1. UNIFORM MATROID U(k,n):
 *     S = set of n elements, I = all subsets of size ≤ k
 *     Greedy: Pick k elements with highest weight.
 *
 *  2. GRAPHIC MATROID (Forest Matroid):
 *     S = edges of graph, I = acyclic subsets (forests)
 *     Greedy: Kruskal's algorithm → MST
 *
 *  3. PARTITION MATROID:
 *     S = elements partitioned into groups, I = sets taking ≤ k_i from group i
 *     Greedy: Pick highest weight from each group up to quota.
 *
 *  4. TRANSVERSAL MATROID:
 *     Related to bipartite matching.
 *
 *  ▶ MATROID INTERSECTION:
 *  ──────────────────────
 *  Finding max weight set that's independent in TWO matroids simultaneously.
 *  This is POLYNOMIAL (not greedy, but efficient).
 *  Applications: Colorful spanning tree, arborescences.
 *  Note: Intersection of 3+ matroids is NP-hard!
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// ============================================================================
// EXAMPLE: Uniform Matroid — Pick k heaviest elements
// ============================================================================
long long uniformMatroidGreedy(vector<int>& weights, int k) {
    sort(weights.rbegin(), weights.rend());
    long long total = 0;
    for (int i = 0; i < min(k, (int)weights.size()); i++)
        total += weights[i];
    return total;
}

// ============================================================================
// EXAMPLE: Partition Matroid — Pick at most k[i] from group i, maximize weight
// ============================================================================
long long partitionMatroidGreedy(
    vector<vector<pair<int,int>>>& groups, // groups[i] = {{weight, id}, ...}
    vector<int>& quota                      // quota[i] = max picks from group i
) {
    // Sort each group by weight descending, pick top quota[i]
    long long total = 0;
    for (int i = 0; i < (int)groups.size(); i++) {
        sort(groups[i].begin(), groups[i].end(), [](auto& a, auto& b) {
            return a.first > b.first;
        });
        for (int j = 0; j < min(quota[i], (int)groups[i].size()); j++) {
            total += groups[i][j].first;
        }
    }
    return total;
}

int main() {
    // Uniform Matroid: Pick 3 heaviest from {5, 2, 8, 1, 9, 3}
    vector<int> weights = {5, 2, 8, 1, 9, 3};
    cout << "Uniform (k=3): " << uniformMatroidGreedy(weights, 3) << endl; // 22

    // Partition Matroid: 2 groups, pick at most 2 from each
    vector<vector<pair<int,int>>> groups = {
        {{5,0}, {3,1}, {7,2}},   // Group 0
        {{4,3}, {6,4}, {2,5}}    // Group 1
    };
    vector<int> quota = {2, 2};
    cout << "Partition: " << partitionMatroidGreedy(groups, quota) << endl; // 22

    return 0;
}

