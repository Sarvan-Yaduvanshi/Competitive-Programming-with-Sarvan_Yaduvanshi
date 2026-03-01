/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Greedy Invariant Maintenance
 *  Level   : Grandmaster
 * ============================================================================
 *
 *  ▶ WHAT IS INVARIANT MAINTENANCE?
 *  ────────────────────────────────
 *  An INVARIANT is a property that remains true throughout the algorithm.
 *  In complex greedy problems, the key is to identify and maintain the right
 *  invariant at each step.
 *
 *  ▶ COMMON INVARIANTS IN GREEDY:
 *  ──────────────────────────────
 *  1. BALANCE INVARIANT:
 *     "The difference between two quantities stays bounded"
 *     Example: Candy distribution — left and right constraints both satisfied
 *
 *  2. MONOTONICITY INVARIANT:
 *     "The solution maintains a sorted/monotone property"
 *     Example: Monotone stack — stack is always increasing/decreasing
 *
 *  3. FEASIBILITY INVARIANT:
 *     "At each step, a valid completion still exists"
 *     Example: Parentheses — open count stays in valid range
 *
 *  4. OPTIMALITY INVARIANT:
 *     "The partial solution is part of some optimal complete solution"
 *     Example: Greedy stays ahead — at step i, greedy ≥ optimal up to i
 *
 *  5. COVERAGE INVARIANT:
 *     "All elements up to position i are properly handled"
 *     Example: Jump game — farthest reachable index ≥ i
 *
 *  ▶ HOW TO IDENTIFY THE RIGHT INVARIANT:
 *  ──────────────────────────────────────
 *  1. What property must the FINAL solution have?
 *  2. How can this property be maintained incrementally?
 *  3. What's the "weakest" invariant that still guarantees correctness?
 *
 *  ▶ GM-LEVEL SKILL:
 *  ─────────────────
 *  At GM level, the invariant is often NON-OBVIOUS. The problem gives you
 *  a complex scenario, and you must discover what quantity to track.
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

// ============================================================================
// EXAMPLE 1: Greedy with Balance Invariant
// CF 1515C — Phoenix and Towers
// Assign blocks to K towers, keep max height difference ≤ max_block_height
// INVARIANT: At each step, assign to shortest tower → heights stay balanced
// ============================================================================
vector<int> phoenixTowers(int n, int k, vector<int>& heights) {
    // Sort blocks (actually, process in any order with min-heap)
    // INVARIANT: Difference between tallest and shortest tower ≤ max(h[i])
    vector<int> assignment(n);
    // Min-heap of {current_height, tower_id}
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    for (int i = 0; i < k; i++) pq.push({0, i});

    // Process blocks in decreasing order for better balance
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        return heights[a] > heights[b];
    });

    for (int idx : order) {
        auto [h, tower] = pq.top(); pq.pop();
        assignment[idx] = tower + 1; // 1-indexed
        pq.push({h + heights[idx], tower});
    }

    return assignment;
}

// ============================================================================
// EXAMPLE 2: Greedy with Feasibility Invariant
// Valid Parentheses with wildcards
// INVARIANT: min_open ≤ actual_open ≤ max_open at every position
// ============================================================================
bool checkValidString(string s) {
    int lo = 0, hi = 0; // Range of possible open counts

    for (char c : s) {
        if (c == '(') { lo++; hi++; }
        else if (c == ')') { lo--; hi--; }
        else { lo--; hi++; } // '*' can be '(', ')', or empty

        // INVARIANT: hi ≥ 0 (if hi < 0, too many ')', impossible)
        if (hi < 0) return false;

        // INVARIANT: lo ≥ 0 (can't have negative open count)
        lo = max(lo, 0);
    }

    // FINAL CHECK: can we reach exactly 0 open?
    return lo == 0;
}

// ============================================================================
// EXAMPLE 3: Greedy with Monotonicity Invariant
// Painting the Array (CF 1657D) — Maximize distinct adjacent pairs
// INVARIANT: Track the last element of each subsequence
// Greedily assign to the subsequence where it creates MORE distinct pairs
// ============================================================================
int paintingArrayMax(vector<int>& a) {
    int n = a.size();
    int last0 = -1, last1 = -1; // Last element of subsequence 0 and 1
    int distinctPairs = 0;

    for (int i = 0; i < n; i++) {
        bool diff0 = (a[i] != last0); // Would create distinct pair in seq 0
        bool diff1 = (a[i] != last1); // Would create distinct pair in seq 1

        if (diff0 && diff1) {
            // Both create distinct pairs — choose the one where the OTHER
            // subsequence has more "flexibility"
            // Greedy: assign to the subsequence whose last element == a[i+1] (if exists)
            // (so the other subsequence can still create a distinct pair next)
            if (i + 1 < n && a[i + 1] == last0) {
                last1 = a[i]; // Assign to seq 1, keep last0 for next
            } else {
                last0 = a[i];
            }
            distinctPairs++;
        } else if (diff0) {
            last0 = a[i];
            distinctPairs++;
        } else if (diff1) {
            last1 = a[i];
            distinctPairs++;
        } else {
            // Neither creates a distinct pair — forced, assign to either
            last0 = a[i];
        }
    }
    return distinctPairs;
}

int main() {
    // Balance Invariant: Phoenix Towers
    vector<int> heights = {3, 1, 2, 1, 3};
    auto assign = phoenixTowers(5, 2, heights);
    cout << "Tower assignment: ";
    for (int a : assign) cout << a << " ";
    cout << endl;

    // Feasibility Invariant: Valid String
    cout << "Valid '(*))': " << checkValidString("(*))") << endl; // 1 (true)
    cout << "Valid '(*)': " << checkValidString("(*)") << endl;   // 1 (true)
    cout << "Valid ')*(': " << checkValidString(")*(") << endl;   // 0 (false)

    // Monotonicity Invariant: Painting Array
    vector<int> arr = {1, 1, 2, 2, 1};
    cout << "Max distinct: " << paintingArrayMax(arr) << endl;

    return 0;
}

