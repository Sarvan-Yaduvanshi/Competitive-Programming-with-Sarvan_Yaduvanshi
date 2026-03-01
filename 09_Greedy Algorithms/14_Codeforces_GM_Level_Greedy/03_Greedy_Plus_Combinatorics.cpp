/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Greedy + Combinatorics
 *  Level   : Grandmaster
 * ============================================================================
 *
 *  ▶ GREEDY + COUNTING:
 *  ────────────────────
 *  Sometimes you need to COUNT the number of valid solutions while
 *  using greedy to efficiently enumerate or bound.
 *
 *  ▶ COMMON PATTERNS:
 *  1. Count valid permutations with greedy constraints
 *  2. Count ways to partition with greedy assignment
 *  3. Greedy + inclusion-exclusion
 *  4. Greedy + Catalan / binomial coefficients
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

// ============================================================================
// LC 2580: Count Ways to Group Overlapping Ranges
// Merge overlapping ranges, then answer = 2^(number_of_groups) mod 10^9+7
// Greedy merge + combinatorics
// ============================================================================
int countWays(vector<vector<int>>& ranges) {
    sort(ranges.begin(), ranges.end());

    int groups = 1;
    int maxEnd = ranges[0][1];

    for (int i = 1; i < (int)ranges.size(); i++) {
        if (ranges[i][0] > maxEnd) {
            groups++; // New group
        }
        maxEnd = max(maxEnd, ranges[i][1]);
    }

    return power(2, groups, MOD);
}

// ============================================================================
// Count valid parenthesis sequences with greedy validation
// Given a string with '(', ')', and '?', count valid completions
// Greedy: track min and max possible open count
// ============================================================================
long long countValidParentheses(string s) {
    long long lo = 0, hi = 0; // Range of possible open counts

    for (char c : s) {
        if (c == '(') {
            lo++; hi++;
        } else if (c == ')') {
            lo--; hi--;
        } else { // '?'
            lo--; hi++;
        }
        if (hi < 0) return 0; // Impossible
        lo = max(lo, 0LL);    // Open count can't be negative
    }

    return lo == 0 ? 1 : 0; // Valid only if we can reach 0 open
}

// ============================================================================
// Greedy arrangement counting
// How many permutations of N elements have exactly K "ascents"?
// (An ascent at position i means a[i] < a[i+1])
// This uses Eulerian numbers, but greedy helps verify.
// ============================================================================

int main() {
    // Count Ways to Group Overlapping Ranges
    vector<vector<int>> ranges = {{6,10},{5,15}};
    cout << "Ways to group: " << countWays(ranges) << endl; // 2

    // Valid Parentheses count
    cout << "Valid '(?)': " << countValidParentheses("(?)") << endl; // 1

    return 0;
}

