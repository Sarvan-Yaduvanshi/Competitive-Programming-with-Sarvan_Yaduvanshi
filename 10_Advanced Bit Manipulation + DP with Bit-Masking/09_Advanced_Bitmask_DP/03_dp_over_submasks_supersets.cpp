/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 09.03 — DP OVER SUBMASKS & SUPERSETS                     ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

DP OVER SUBMASKS:
═════════════════
    dp[mask] depends on dp[sub] for all sub ⊂ mask.
    Process masks in increasing order (smaller subsets first).

    Transition example:
    dp[mask] = min over all proper submasks s of (dp[s] + cost(mask \ s))

    This splits mask into two disjoint parts. Time: O(3ⁿ).

DP OVER SUPERSETS:
══════════════════
    dp[mask] depends on dp[super] for all super ⊃ mask.
    Process masks in decreasing order (larger supersets first).

INCLUSION-EXCLUSION WITH BITMASK:
═════════════════════════════════
    f(S) = Σ_{T⊆S} (-1)^|S\T| g(T)

    This is the Möbius inversion on the subset lattice.
    Can compute in O(n × 2ⁿ) using SOS-like DP with alternating signs.

PRACTICE PROBLEMS:
══════════════════
    Codeforces: 449D (Jzzhu and Cities variant)
    AtCoder: ABC 187-F
*/
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   DP OVER SUBMASKS & SUPERSETS                  ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Example: Split mask into minimum number of groups, each with sum ≤ limit
    int n = 4;
    vector<int> w = {3, 5, 2, 7};
    int limit = 8;

    // Precompute subset sums
    vector<int> subsetSum(1 << n, 0);
    for (int mask = 1; mask < (1 << n); mask++) {
        int lowest = mask & (-mask);
        int idx = __builtin_ctz(lowest);
        subsetSum[mask] = subsetSum[mask ^ lowest] + w[idx];
    }

    // Mark valid groups (sum ≤ limit)
    vector<bool> valid(1 << n);
    for (int mask = 0; mask < (1 << n); mask++)
        valid[mask] = (subsetSum[mask] <= limit);

    // dp[mask] = min groups to partition mask into valid groups
    vector<int> dp(1 << n, INT_MAX);
    dp[0] = 0;

    for (int mask = 1; mask < (1 << n); mask++) {
        // Try all submasks as one group
        for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
            if (valid[sub] && dp[mask ^ sub] != INT_MAX) {
                dp[mask] = min(dp[mask], dp[mask ^ sub] + 1);
            }
        }
    }

    cout << "\n  Weights: {3,5,2,7}, Limit: " << limit << endl;
    cout << "  Min groups: " << dp[(1<<n)-1] << endl;
    // Groups: {3,5} and {2} and {7} = 3 groups, or {3,2}(5) and {5}(5) and {7}(7) = 3
    // {3,5}=8, {2,7}=9 > 8... {3,2}=5, {5}=5, {7}=7 → 3 groups

    // Inclusion-Exclusion demo
    cout << "\n--- Inclusion-Exclusion via SOS ---" << endl;
    vector<long long> g = {1, 2, 3, 4, 5, 6, 7, 8};
    int N = 3;
    // Compute f(S) = Σ_{T⊆S} (-1)^|S\T| g(T) — Möbius function
    vector<long long> f = g;
    for (int i = 0; i < N; i++)
        for (int mask = (1<<N)-1; mask >= 0; mask--)
            if (mask & (1 << i))
                f[mask] -= f[mask ^ (1 << i)];

    cout << "  Möbius inversion results:" << endl;
    for (int mask = 0; mask < (1 << N); mask++)
        cout << "  f[" << bitset<3>(mask) << "] = " << f[mask] << endl;

    cout << "\n✅ DP over submasks and supersets demonstrated!" << endl;
    return 0;
}

