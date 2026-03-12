/*
 * ============================================================================
 *                BITMASK DP — TSP, ASSIGNMENT, SUBSET DP
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Bitmask DP — TSP, Assignment Problem, Subset DP
 * Level   : ⭐⭐⭐⭐ Expert
 * ============================================================================
 *
 * BITMASK DP PATTERN:
 *   State: dp[mask][i] where mask = bitmask of visited/selected elements
 *   mask encodes which elements are included in the subset
 *
 * BIT OPERATIONS CHEAT SHEET:
 *   Check if bit i is set:    mask & (1 << i)
 *   Set bit i:                mask | (1 << i)
 *   Clear bit i:              mask & ~(1 << i)
 *   Toggle bit i:             mask ^ (1 << i)
 *   Count set bits:           __builtin_popcount(mask)
 *   Iterate submasks:         for(s=mask; s>0; s=(s-1)&mask)
 *
 * Total states: O(2^n * n), Transition: O(n) → Total: O(2^n * n²)
 * Practical for n ≤ 20 (sometimes 23-24 with optimization)
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * 1. TRAVELING SALESMAN PROBLEM (TSP)
 *    Visit all cities exactly once, return to start, minimize total distance.
 *    dp[mask][i] = min cost to visit cities in mask, ending at city i
 *    dp[mask | (1<<j)][j] = min(dp[mask][i] + dist[i][j]) for j not in mask
 *    Time: O(2^n * n²)
 */
int tsp(vector<vector<int>>& dist) {
    int n = dist.size();
    int full = (1 << n) - 1;
    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));

    dp[1][0] = 0;  // Start at city 0

    for (int mask = 1; mask <= full; mask++) {
        for (int u = 0; u < n; u++) {
            if (dp[mask][u] == INT_MAX) continue;
            if (!(mask & (1 << u))) continue;

            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue;  // Already visited
                int newMask = mask | (1 << v);
                dp[newMask][v] = min(dp[newMask][v], dp[mask][u] + dist[u][v]);
            }
        }
    }

    // Return to start
    int ans = INT_MAX;
    for (int i = 1; i < n; i++) {
        if (dp[full][i] != INT_MAX) {
            ans = min(ans, dp[full][i] + dist[i][0]);
        }
    }
    return ans;
}

/*
 * 2. ASSIGNMENT PROBLEM
 *    n persons, n jobs. cost[i][j] = cost if person i does job j.
 *    Assign one job per person, minimize total cost.
 *    dp[mask] = min cost when mask represents assigned jobs
 *    Person index = popcount(mask) (i.e., how many jobs assigned so far)
 */
int assignmentProblem(vector<vector<int>>& cost) {
    int n = cost.size();
    vector<int> dp(1 << n, INT_MAX);
    dp[0] = 0;

    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] == INT_MAX) continue;
        int person = __builtin_popcount(mask);
        if (person >= n) continue;

        for (int job = 0; job < n; job++) {
            if (mask & (1 << job)) continue;
            dp[mask | (1 << job)] = min(dp[mask | (1 << job)],
                                        dp[mask] + cost[person][job]);
        }
    }
    return dp[(1 << n) - 1];
}

/*
 * 3. MINIMUM HAMILTONIAN PATH
 *    Visit all nodes, no return needed. Minimize cost.
 *    dp[mask][i] = min cost path visiting cities in mask, ending at i
 *    Start from any city.
 */
int minHamiltonianPath(vector<vector<int>>& dist) {
    int n = dist.size();
    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));

    // Can start from any city
    for (int i = 0; i < n; i++) dp[1 << i][i] = 0;

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {
            if (dp[mask][u] == INT_MAX) continue;
            if (!(mask & (1 << u))) continue;

            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue;
                dp[mask | (1 << v)][v] = min(dp[mask | (1 << v)][v],
                                              dp[mask][u] + dist[u][v]);
            }
        }
    }

    int full = (1 << n) - 1;
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) ans = min(ans, dp[full][i]);
    return ans;
}

/*
 * 4. SUBSET PARTITION — Can we partition into k subsets with equal sum?
 *    dp[mask] = can elements in mask be partitioned?
 *    We track the "leftover" sum in current group.
 */
bool canPartitionK(vector<int>& nums, int k) {
    int n = nums.size();
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (total % k != 0) return false;
    int target = total / k;

    vector<int> dp(1 << n, -1);
    dp[0] = 0;

    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] == -1) continue;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) continue;
            if (dp[mask] + nums[i] <= target) {
                dp[mask | (1 << i)] = (dp[mask] + nums[i]) % target;
            }
        }
    }
    return dp[(1 << n) - 1] == 0;
}

/*
 * 5. DP OVER SUBMASKS
 *    For each mask, iterate over all submasks efficiently.
 *    Total iterations across ALL masks = 3^n (not 4^n!)
 *
 *    for (mask = 0; mask < (1<<n); mask++)
 *      for (sub = mask; sub > 0; sub = (sub-1) & mask)
 *        // sub is a submask of mask
 */
void subsetSumDP(vector<int>& a, int n) {
    // dp[mask] = sum of elements in mask
    vector<int> dp(1 << n, 0);

    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                dp[mask] += a[i];
                break;  // dp[mask] = dp[mask without lowest set bit] + a[lowest]
            }
        }
        // Better: dp[mask] = dp[mask ^ (mask & -mask)] + a[__builtin_ctz(mask)]
    }

    cout << "Subset sums:" << endl;
    for (int mask = 0; mask < (1 << n); mask++) {
        cout << "  mask=" << bitset<4>(mask) << " → sum=" << dp[mask] << endl;
    }
}

/*
 * 6. COUNTING HAMILTONIAN PATHS (Count, not just min cost)
 *    dp[mask][i] = number of Hamiltonian paths ending at node i
 */
long long countHamiltonianPaths(int n, vector<vector<bool>>& hasEdge) {
    vector<vector<long long>> dp(1 << n, vector<long long>(n, 0));

    for (int i = 0; i < n; i++) dp[1 << i][i] = 1;

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u))) continue;
            if (dp[mask][u] == 0) continue;

            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue;
                if (!hasEdge[u][v]) continue;
                dp[mask | (1 << v)][v] += dp[mask][u];
            }
        }
    }

    long long total = 0;
    for (int i = 0; i < n; i++) total += dp[(1 << n) - 1][i];
    return total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== BITMASK DP ===" << endl;

    // TSP
    vector<vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    cout << "\n--- TSP ---" << endl;
    cout << "Min tour cost: " << tsp(dist) << endl;

    // Assignment Problem
    vector<vector<int>> cost = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };
    cout << "\n--- Assignment Problem ---" << endl;
    cout << "Min cost: " << assignmentProblem(cost) << endl;

    // Hamiltonian Path
    cout << "\n--- Min Hamiltonian Path ---" << endl;
    cout << "Min path cost: " << minHamiltonianPath(dist) << endl;

    // Partition into K subsets
    vector<int> nums = {4, 3, 2, 3, 5, 2, 1};
    cout << "\n--- Partition into 4 equal subsets ---" << endl;
    cout << "Possible: " << (canPartitionK(nums, 4) ? "YES" : "NO") << endl;

    // Subset Sum
    vector<int> a = {1, 3, 5, 7};
    cout << "\n--- Subset Sum DP ---" << endl;
    subsetSumDP(a, 4);

    return 0;
}

