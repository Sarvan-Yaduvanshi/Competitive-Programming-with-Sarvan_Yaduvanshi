/*
 * ============================================================================
 *            PROFILE DP (BITMASK) + PERFECT MATCHING
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Bitmask DP — Profile DP, Perfect Matching, Subset of Subsets
 * Level   : ⭐⭐⭐⭐ Expert
 * ============================================================================
 *
 * 1. PERFECT MATCHING with bitmask (AtCoder DP O — Matching)
 *    N men, N women. Assign each man to one woman. Count valid matchings.
 *
 * 2. DP OVER SUBMASKS — Enumerate all submasks of each mask
 *    for(sub = mask; sub > 0; sub = (sub-1) & mask)
 *    Total work: O(3^n) across all masks.
 *
 * 3. GROUPING DP (AtCoder DP U — Grouping)
 *    Partition n elements into groups. Each group has a score.
 *    dp[mask] = max score partitioning elements in mask.
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

/*
 * 1. MATCHING — Count perfect matchings
 *    dp[mask] = ways to match first popcount(mask) men to women in mask
 */
long long countMatchings(int n, vector<vector<bool>>& compatible) {
    vector<long long> dp(1 << n, 0);
    dp[0] = 1;

    for (int mask = 0; mask < (1 << n); mask++) {
        int man = __builtin_popcount(mask);  // Which man we're assigning
        if (man >= n) continue;

        for (int woman = 0; woman < n; woman++) {
            if (mask & (1 << woman)) continue;  // Already matched
            if (!compatible[man][woman]) continue;  // Not compatible
            dp[mask | (1 << woman)] = (dp[mask | (1 << woman)] + dp[mask]) % MOD;
        }
    }
    return dp[(1 << n) - 1];
}

/*
 * 2. GROUPING — Partition into groups, maximize score
 *    Precompute score[mask] for each possible group.
 *    dp[mask] = max score partitioning elements in mask into groups.
 *    dp[mask] = max(dp[mask ^ sub] + score[sub]) for all submasks sub
 */
long long groupingDP(int n, vector<vector<int>>& benefit) {
    // Precompute score for each possible group
    vector<long long> score(1 << n, 0);
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i))) continue;
            for (int j = i + 1; j < n; j++) {
                if (!(mask & (1 << j))) continue;
                score[mask] += benefit[i][j];
            }
        }
    }

    // DP over submasks
    vector<long long> dp(1 << n, 0);
    for (int mask = 1; mask < (1 << n); mask++) {
        // Iterate over all non-empty submasks
        for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
            dp[mask] = max(dp[mask], dp[mask ^ sub] + score[sub]);
        }
    }
    return dp[(1 << n) - 1];
}

/*
 * 3. ELEVATOR RIDES (CSES)
 *    N people with weights. Elevator capacity X.
 *    Minimize number of rides to transport everyone.
 *
 *    dp[mask] = {min rides, min weight in last ride} for people in mask
 */
pair<int, int> elevatorRides(vector<int>& weights, int capacity) {
    int n = weights.size();
    // dp[mask] = {rides, remaining weight in last ride}
    vector<pair<int,int>> dp(1 << n, {n + 1, 0});
    dp[0] = {1, 0};  // Empty: 1 ride with 0 weight

    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask].first > n) continue;

        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) continue;
            int newMask = mask | (1 << i);

            pair<int,int> option;
            if (dp[mask].second + weights[i] <= capacity) {
                option = {dp[mask].first, dp[mask].second + weights[i]};
            } else {
                option = {dp[mask].first + 1, weights[i]};
            }
            dp[newMask] = min(dp[newMask], option);
        }
    }
    return dp[(1 << n) - 1];
}

/*
 * 4. SOS DP (Sum over Subsets) — Detailed
 *    f[mask] = Σ a[sub] for all submasks sub of mask
 *
 *    Naive O(3^n) vs SOS O(n * 2^n)
 */
vector<long long> sosDPDetailed(vector<int>& a, int n) {
    int N = 1 << n;
    vector<long long> f(N);
    for (int i = 0; i < N; i++) f[i] = a[i];

    // Process one bit at a time
    for (int bit = 0; bit < n; bit++) {
        for (int mask = 0; mask < N; mask++) {
            if (mask & (1 << bit)) {
                f[mask] += f[mask ^ (1 << bit)];
            }
        }
    }
    // Now f[mask] = sum of a[sub] for all sub ⊆ mask

    // SUPERSET SOS: g[mask] = sum of a[sup] for all sup ⊇ mask
    vector<long long> g(N);
    for (int i = 0; i < N; i++) g[i] = a[i];
    for (int bit = 0; bit < n; bit++) {
        for (int mask = N - 1; mask >= 0; mask--) {
            if (!(mask & (1 << bit))) {
                g[mask] += g[mask | (1 << bit)];
            }
        }
    }

    return f;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== BITMASK DP — ADVANCED ===" << endl;

    // Matching
    int n = 3;
    vector<vector<bool>> compat = {
        {true, true, false},
        {true, false, true},
        {false, true, true}
    };
    cout << "\n--- Perfect Matching Count ---" << endl;
    cout << "Matchings: " << countMatchings(n, compat) << endl;

    // Grouping
    vector<vector<int>> benefit = {
        {0, 10, 20},
        {10, 0, 30},
        {20, 30, 0}
    };
    cout << "\n--- Grouping DP ---" << endl;
    cout << "Max score: " << groupingDP(3, benefit) << endl;

    // Elevator Rides
    vector<int> weights = {2, 3, 3, 5, 6};
    int capacity = 10;
    auto [rides, lastWeight] = elevatorRides(weights, capacity);
    cout << "\n--- Elevator Rides ---" << endl;
    cout << "Weights: "; for (int w : weights) cout << w << " ";
    cout << "\nCapacity: " << capacity << endl;
    cout << "Min rides: " << rides << endl;

    // SOS DP
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8};
    auto sos = sosDPDetailed(a, 3);
    cout << "\n--- SOS DP ---" << endl;
    for (int mask = 0; mask < 8; mask++) {
        cout << "f[" << bitset<3>(mask) << "] = " << sos[mask] << endl;
    }

    return 0;
}

