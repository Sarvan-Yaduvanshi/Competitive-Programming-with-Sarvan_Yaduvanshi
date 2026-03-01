/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Construction Problems — Build Valid Objects Greedily
 *  Level   : Grandmaster
 * ============================================================================
 *
 *  ▶ WHAT ARE CONSTRUCTION PROBLEMS?
 *  ─────────────────────────────────
 *  Given constraints, BUILD (construct) a valid object:
 *  - A permutation with certain properties
 *  - A string satisfying conditions
 *  - A graph with required edges/degrees
 *  - A sequence with specific subarray sums
 *
 *  ▶ GREEDY STRATEGIES FOR CONSTRUCTION:
 *  ────────────────────────────────────
 *  1. BUILD GREEDILY: Fill positions one by one, always satisfying local constraints
 *  2. BALANCE: Alternate between options to maintain balance
 *  3. EXTREME VALUES: Place largest/smallest first where they cause least conflict
 *  4. PARITY: Exploit even/odd properties
 *
 *  ▶ COMMON CF PATTERNS:
 *  ────────────────────
 *  - "Construct a permutation such that..." → fill position by position
 *  - "Construct a binary string such that..." → track counts/parities
 *  - "Build a graph with degree sequence..." → Erdős–Gallai check + greedy construction
 *  - "Can you reorder to satisfy?" → sort + place
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

// ============================================================================
// EXAMPLE 1: Construct a permutation with K inversions
// Greedy: Start with sorted [1..N], then create inversions from the end
// ============================================================================
vector<int> permutationWithKInversions(int n, long long k) {
    deque<int> result;
    for (int i = n; i >= 1; i--) {
        // We can create at most (i-1) inversions by placing i at the front
        if (k >= i - 1) {
            result.push_front(i); // Place at front → (i-1) inversions with elements after it
            k -= (i - 1);
        } else {
            // Place at position k from front (0-indexed)
            result.insert(result.begin() + k, i);
            k = 0;
        }
    }
    return vector<int>(result.begin(), result.end());
}

// ============================================================================
// EXAMPLE 2: Construct string with exactly K distinct substrings of length 2
// (Simplified version of many CF string construction problems)
// ============================================================================
string constructStringKPairs(int n, int k) {
    // Use 'a' and 'b'. "aaaa...a" has 1 distinct pair. Each time we switch,
    // we add at most 1 new pair.
    // More precisely: use first (k) distinct pairs by cycling characters
    string result;
    int charsToUse = min(k, 26); // At most 26 distinct chars

    for (int i = 0; i < n; i++) {
        result += 'a' + (i % charsToUse);
    }
    return result;
}

// ============================================================================
// EXAMPLE 3: CF 1927E — Klever Permutation
// Construct permutation where every window of size K has ~equal sum
// Strategy: Fill positions in a snake-like pattern
// ============================================================================
vector<int> kleverPermutation(int n, int k) {
    vector<int> result(n);
    int val = 1;
    // Fill in zigzag by residue class mod k
    for (int r = 0; r < k; r++) {
        vector<int> positions;
        for (int i = r; i < n; i += k) positions.push_back(i);

        // Alternate: fill ascending for even r, descending for odd r
        if (r % 2 == 1) reverse(positions.begin(), positions.end());

        for (int pos : positions) {
            result[pos] = val++;
        }
    }
    return result;
}

int main() {
    // Permutation with K inversions
    auto perm = permutationWithKInversions(5, 3);
    cout << "Permutation with 3 inversions: ";
    for (int x : perm) cout << x << " ";
    cout << endl;

    // Klever Permutation
    auto kp = kleverPermutation(6, 3);
    cout << "Klever permutation (n=6,k=3): ";
    for (int x : kp) cout << x << " ";
    cout << endl;

    return 0;
}

