/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Online Greedy Algorithms
 *  Level   : Grandmaster
 * ============================================================================
 *
 *  ▶ WHAT IS AN ONLINE ALGORITHM?
 *  ──────────────────────────────
 *  An algorithm that processes input piece-by-piece (one at a time),
 *  making IRREVOCABLE decisions without seeing future input.
 *
 *  ▶ THE SECRETARY PROBLEM (Optimal Stopping):
 *  ────────────────────────────────────────────
 *  N candidates interviewed one at a time. After each, you must accept/reject.
 *  No going back. Maximize probability of picking the BEST candidate.
 *
 *  OPTIMAL STRATEGY: Reject the first N/e candidates (~37%), then pick the
 *  first one that's better than all previously seen.
 *  Success probability: ~1/e ≈ 36.8%
 *
 *  ▶ COMPETITIVE RATIO:
 *  ────────────────────
 *  For online algorithms, we measure performance by "competitive ratio":
 *  ratio of online algorithm's cost to optimal offline algorithm's cost.
 *
 *  ▶ ONLINE BIPARTITE MATCHING:
 *  ────────────────────────────
 *  Left vertices arrive online. When a vertex arrives, match it to an
 *  available right neighbor or leave it unmatched. Irrevocable.
 *
 *  GREEDY: Match to ANY available neighbor → competitive ratio = 1/2
 *  RANKING (Karp-Vazirani-Vazirani): Random priority → ratio = 1 - 1/e ≈ 0.63
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
using namespace std;

// ============================================================================
// Secretary Problem Simulation
// ============================================================================
int secretaryProblem(vector<int>& candidates) {
    int n = candidates.size();
    int rejectCount = max(1, (int)(n / M_E)); // Reject first n/e

    // Phase 1: Observe (reject) first n/e candidates
    int bestSeen = 0;
    for (int i = 0; i < rejectCount; i++) {
        bestSeen = max(bestSeen, candidates[i]);
    }

    // Phase 2: Accept first candidate better than bestSeen
    for (int i = rejectCount; i < n; i++) {
        if (candidates[i] > bestSeen) {
            return candidates[i]; // Accept!
        }
    }

    return candidates[n - 1]; // Last candidate (forced)
}

// ============================================================================
// Online Bipartite Matching (Greedy)
// ============================================================================
int onlineGreedyMatching(int n, int m, vector<vector<int>>& adj) {
    // n = left vertices (arrive online), m = right vertices
    // adj[i] = list of right vertices that left vertex i can match to
    vector<bool> matchedRight(m, false);
    int matches = 0;

    for (int i = 0; i < n; i++) {
        // Greedy: match to first available right vertex
        for (int r : adj[i]) {
            if (!matchedRight[r]) {
                matchedRight[r] = true;
                matches++;
                break;
            }
        }
    }
    return matches;
}

int main() {
    // Secretary Problem
    vector<int> candidates = {3, 7, 2, 9, 1, 8, 5, 4, 6, 10};
    int picked = secretaryProblem(candidates);
    cout << "Secretary picked: " << picked << " (best is 10)" << endl;

    // Online Matching
    int n = 3, m = 3;
    vector<vector<int>> adj = {{0, 1}, {1, 2}, {0, 2}};
    cout << "Online matching: " << onlineGreedyMatching(n, m, adj) << "/" << min(n, m) << endl;

    return 0;
}

