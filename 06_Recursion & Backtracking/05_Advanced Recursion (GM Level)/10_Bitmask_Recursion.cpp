/*
╔══════════════════════════════════════════════════════════════╗
║  10. BITMASK + RECURSION — TSP, Assignment, SOS DP           ║
║  Level 5 — Advanced Recursion (GM Level)                     ║
╚══════════════════════════════════════════════════════════════╝

════════════════════════════════════════════════════════════════
📖 BITMASK RECURSION
════════════════════════════════════════════════════════════════

Use a BITMASK to represent which elements are "used" or "selected".

If we have n elements (n ≤ 20-23), we can represent any subset
as an integer from 0 to 2^n - 1.

Bit i is 1 → element i is selected
Bit i is 0 → element i is not selected

🔧 KEY OPERATIONS:
   - Check if bit i is set:   (mask >> i) & 1
   - Set bit i:               mask | (1 << i)
   - Clear bit i:             mask & ~(1 << i)
   - Toggle bit i:            mask ^ (1 << i)
   - Count set bits:          __builtin_popcount(mask)
   - Iterate subsets of mask: for(int sub=mask; sub>0; sub=(sub-1)&mask)

════════════════════════════════════════════════════════════════

🎯 Problems:
   1. Travelling Salesman Problem (TSP) — O(n^2 * 2^n)
   2. Assignment Problem (Hungarian via bitmask)
   3. Count ways to assign tasks (Codeforces style)
   4. SOS DP — Sum over Subsets
   5. Hamiltonian Path check
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>
#include <functional>

using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;

constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD = 1'000'000'007LL;

#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'


// ═══════════════════════════════════════════════════════════
// 1️⃣ TRAVELLING SALESMAN PROBLEM (TSP) — O(n^2 * 2^n)
// ═══════════════════════════════════════════════════════════
/*
   Given n cities and distances between them, find minimum cost
   Hamiltonian cycle (visit each city exactly once and return to start).

   State: dp[mask][i] = min cost to visit cities in `mask`,
                         currently at city i

   Transition: For each unvisited city j:
       dp[mask | (1<<j)][j] = min(dp[mask][i] + dist[i][j])

   Base: dp[1][0] = 0 (start at city 0, only city 0 visited)
   Answer: min over all i of dp[(1<<n)-1][i] + dist[i][0]

   Time: O(n^2 * 2^n), Space: O(n * 2^n)
   Works for n ≤ 20
*/
i64 tsp(vvec<int>& dist) {
    int n = sz(dist);
    int fullMask = (1 << n) - 1;

    vvec<i64> dp(1 << n, vec<i64>(n, INF64));
    dp[1][0] = 0;  // Start at city 0

    // Bottom-up (but recursive version below)
    for (int mask = 1; mask <= fullMask; mask++) {
        for (int u = 0; u < n; u++) {
            if (dp[mask][u] == INF64) continue;
            if (!((mask >> u) & 1)) continue;  // u must be in mask

            for (int v = 0; v < n; v++) {
                if ((mask >> v) & 1) continue;  // v must NOT be in mask
                int newMask = mask | (1 << v);
                dp[newMask][v] = min(dp[newMask][v], dp[mask][u] + dist[u][v]);
            }
        }
    }

    i64 ans = INF64;
    for (int i = 0; i < n; i++) {
        ans = min(ans, dp[fullMask][i] + dist[i][0]);
    }
    return ans;
}

// Recursive version (top-down with memoization)
i64 tspRecursive(vvec<int>& dist) {
    int n = sz(dist);
    int fullMask = (1 << n) - 1;
    vvec<i64> dp(1 << n, vec<i64>(n, -1));

    function<i64(int, int)> solve = [&](int mask, int u) -> i64 {
        if (mask == fullMask) return dist[u][0];  // Return to start
        if (dp[mask][u] != -1) return dp[mask][u];

        i64 res = INF64;
        for (int v = 0; v < n; v++) {
            if ((mask >> v) & 1) continue;  // Already visited
            res = min(res, dist[u][v] + solve(mask | (1 << v), v));
        }
        return dp[mask][u] = res;
    };

    return solve(1, 0);  // Start at city 0
}


// ═══════════════════════════════════════════════════════════
// 2️⃣ ASSIGNMENT PROBLEM — Bitmask DP
// ═══════════════════════════════════════════════════════════
/*
   n workers, n tasks. cost[i][j] = cost of assigning task j to worker i.
   Assign exactly one task to each worker. Minimize total cost.

   State: dp[mask] = min cost of assigning tasks in `mask` to
          the first popcount(mask) workers.

   If popcount(mask) = k, we're assigning task to worker k-1.
   Actually: worker index = popcount(mask), mask = set of tasks assigned.

   Time: O(n * 2^n)
*/
i64 assignmentProblem(vvec<int>& cost) {
    int n = sz(cost);
    vec<i64> dp(1 << n, INF64);
    dp[0] = 0;

    for (int mask = 0; mask < (1 << n); mask++) {
        int worker = __builtin_popcount(mask);
        if (worker >= n) continue;

        for (int task = 0; task < n; task++) {
            if ((mask >> task) & 1) continue;  // Task already assigned
            dp[mask | (1 << task)] = min(dp[mask | (1 << task)],
                                          dp[mask] + cost[worker][task]);
        }
    }

    return dp[(1 << n) - 1];
}


// ═══════════════════════════════════════════════════════════
// 3️⃣ COUNT WAYS TO FORM TEAMS (Codeforces Style)
// ═══════════════════════════════════════════════════════════
/*
   n people, n roles. compatible[i] = bitmask of roles person i can fill.
   Count ways to assign roles such that each person gets exactly one role.

   Similar to assignment but we COUNT instead of minimize.
*/
i64 countAssignments(vec<int>& compatible, int n) {
    vec<i64> dp(1 << n, 0);
    dp[0] = 1;

    for (int mask = 0; mask < (1 << n); mask++) {
        int person = __builtin_popcount(mask);
        if (person >= n) continue;

        for (int role = 0; role < n; role++) {
            if ((mask >> role) & 1) continue;
            if (!((compatible[person] >> role) & 1)) continue;  // Not compatible

            dp[mask | (1 << role)] = (dp[mask | (1 << role)] + dp[mask]) % MOD;
        }
    }

    return dp[(1 << n) - 1];
}


// ═══════════════════════════════════════════════════════════
// 4️⃣ SOS DP — Sum over Subsets
// ═══════════════════════════════════════════════════════════
/*
   Given array f of size 2^n.
   Compute for each mask:
       F[mask] = sum of f[sub] for all sub that are subsets of mask

   Naive: O(3^n) — iterate over all subsets of each mask
   SOS DP: O(n * 2^n) — much faster!

   🧠 The idea: Build up dimension by dimension.

   dp[mask][i] = sum of f[sub] where sub agrees with mask
                  on bits i+1, i+2, ..., n-1
                  and sub is a submask of mask on bits 0..i

   Transition:
   - If bit i of mask is 0: dp[mask][i] = dp[mask][i-1]
   - If bit i of mask is 1: dp[mask][i] = dp[mask][i-1] + dp[mask^(1<<i)][i-1]

   We can compress to 1D: iterate i from 0 to n-1,
   for each mask with bit i set, add dp[mask ^ (1<<i)]

   This is CRITICAL for Codeforces Div 1 / Div 2 D-E problems!
*/
vec<i64> sosDP(vec<i64>& f, int n) {
    vec<i64> dp = f;  // Copy

    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if ((mask >> i) & 1) {
                dp[mask] += dp[mask ^ (1 << i)];
            }
        }
    }

    return dp;
    // Now dp[mask] = sum of f[sub] for all subsets sub of mask
}


// ═══════════════════════════════════════════════════════════
// 5️⃣ HAMILTONIAN PATH — Does one exist? (Bitmask DP)
// ═══════════════════════════════════════════════════════════
/*
   Given directed graph, check if Hamiltonian path exists.

   State: dp[mask][v] = true if there's a path visiting exactly
          the vertices in `mask`, ending at vertex v

   Time: O(n^2 * 2^n)
*/
bool hamiltonianPath(vvec<int>& adj, int n) {
    vvec<bool> dp(1 << n, vec<bool>(n, false));

    // Base: single vertex
    for (int i = 0; i < n; i++) dp[1 << i][i] = true;

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {
            if (!dp[mask][u]) continue;
            if (!((mask >> u) & 1)) continue;

            for (int v : adj[u]) {
                if ((mask >> v) & 1) continue;  // Already visited
                dp[mask | (1 << v)][v] = true;
            }
        }
    }

    int fullMask = (1 << n) - 1;
    for (int i = 0; i < n; i++) {
        if (dp[fullMask][i]) return true;
    }
    return false;
}


// ═══════════════════════════════════════════════════════════
// 🧪 TEST
// ═══════════════════════════════════════════════════════════

void solve() {
    // 1. TSP
    {
        cout << "=== TSP ===" << nl;
        vvec<int> dist = {
            {0, 10, 15, 20},
            {10, 0, 35, 25},
            {15, 35, 0, 30},
            {20, 25, 30, 0}
        };
        cout << "Min tour cost: " << tspRecursive(dist) << nl;
        // Expected: 80 (0→1→3→2→0)
    }

    // 2. Assignment Problem
    {
        cout << nl << "=== ASSIGNMENT PROBLEM ===" << nl;
        vvec<int> cost = {
            {9, 2, 7, 8},
            {6, 4, 3, 7},
            {5, 8, 1, 8},
            {7, 6, 9, 4}
        };
        cout << "Min assignment cost: " << assignmentProblem(cost) << nl;
        // Expected: 13 (2+3+1+7 or similar optimal)
    }

    // 3. SOS DP
    {
        cout << nl << "=== SOS DP ===" << nl;
        int n = 3;
        vec<i64> f = {1, 2, 3, 4, 5, 6, 7, 8};  // 2^3 = 8 values
        auto res = sosDP(f, n);
        cout << "F[7] (all subsets of 111) = " << res[7] << nl;
        // Should be sum of all: 1+2+3+4+5+6+7+8 = 36
        cout << "F[5] (subsets of 101) = " << res[5] << nl;
        // Subsets of 101: 000, 001, 100, 101 → f[0]+f[1]+f[4]+f[5] = 1+2+5+6 = 14
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    while (TC--) solve();

    return 0;
}

