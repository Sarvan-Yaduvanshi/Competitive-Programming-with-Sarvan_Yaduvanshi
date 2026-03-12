/*
 * ============================================================================
 *    CIRCULAR DP + DP ON PERMUTATION CYCLES + BURNSIDE/POLYA
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Advanced DP — Circular DP, Cycle Decomposition, Burnside
 * Level   : ⭐⭐⭐⭐ Expert / ICPC
 * ============================================================================
 *
 * CIRCULAR DP:
 *   When array is circular: fix first element's state, then DP,
 *   and check compatibility at the end.
 *
 * DP ON PERMUTATION CYCLES:
 *   Permutation = product of disjoint cycles.
 *   DP on cycle structure for counting permutations with properties.
 *   Connected to Stirling numbers (1st kind).
 *
 * BURNSIDE'S LEMMA (with DP):
 *   Count distinct objects under group of symmetries.
 *   |orbits| = (1/|G|) × Σ |Fix(g)|
 *   where Fix(g) = objects fixed by symmetry g.
 *   Compute Fix(g) using DP.
 *
 * APPLICATIONS:
 *   - Necklace coloring (how many distinct necklaces?)
 *   - Circular seating arrangements
 *   - Counting non-isomorphic graphs/structures
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

long long power(long long base, long long exp, long long mod) {
    long long result = 1; base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

/*
 * 1. CIRCULAR DP — General Technique
 *    Problem: n items in circle, each colored with k colors.
 *    Adjacent items must have different colors. Count valid colorings.
 *
 *    Linear: dp[i][c] = ways to color items 1..i with item i = color c
 *    Circular: fix item 1's color, then at end check item n ≠ item 1
 *
 *    Answer = Σ over c1: dp_ending_not_c1[n]
 *    Or use chromatic polynomial: P(Cn, k) = (k-1)^n + (-1)^n × (k-1)
 */
long long circularColoring(int n, int k) {
    // Chromatic polynomial of cycle Cn with k colors
    // P(Cn, k) = (k-1)^n + (-1)^n * (k-1)
    long long term1 = power(k - 1, n, MOD);
    long long term2 = (n % 2 == 0) ? (k - 1) : (MOD - (k - 1));
    return (term1 + term2) % MOD;
}

// General circular DP with custom transition
// dp with first element fixed, checking last-first compatibility
long long circularDP_general(int n, vector<vector<int>>& cost) {
    // cost[a][b] = cost/validity of adjacent elements (a, b)
    // k = number of states per position
    int k = cost.size();

    long long total = 0;

    // Fix first element's state
    for (int first = 0; first < k; first++) {
        // dp[j] = min cost / count with current position having state j
        vector<long long> dp(k, 0);
        dp[first] = 1;

        for (int pos = 1; pos < n; pos++) {
            vector<long long> ndp(k, 0);
            for (int cur = 0; cur < k; cur++) {
                for (int prev = 0; prev < k; prev++) {
                    if (cost[prev][cur] >= 0) {  // Valid transition
                        ndp[cur] = (ndp[cur] + dp[prev]) % MOD;
                    }
                }
            }
            dp = ndp;
        }

        // Check compatibility of last with first
        for (int last = 0; last < k; last++) {
            if (cost[last][first] >= 0) {  // Last → First valid
                total = (total + dp[last]) % MOD;
            }
        }
    }
    return total;
}

/*
 * 2. HOUSE ROBBER II — Circular Array (LeetCode 213)
 *    Can't rob first AND last house (they're adjacent).
 *    Solution: max(rob(0..n-2), rob(1..n-1))
 */
int houseRobberCircular(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];

    auto rob = [&](int lo, int hi) -> int {
        int prev2 = 0, prev1 = 0;
        for (int i = lo; i <= hi; i++) {
            int cur = max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = cur;
        }
        return prev1;
    };

    return max(rob(0, n - 2), rob(1, n - 1));
}

/*
 * 3. BURNSIDE'S LEMMA — Count distinct necklaces
 *    n beads, k colors. Rotational symmetry.
 *    |distinct necklaces| = (1/n) × Σ_{d|n} φ(n/d) × k^d
 *    where φ = Euler's totient function.
 */
long long eulerTotient(long long n) {
    long long result = n;
    for (long long p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

long long countNecklaces(int n, int k) {
    // Burnside: (1/n) × Σ_{d|n} φ(n/d) × k^d
    long long ans = 0;
    for (int d = 1; d * d <= n; d++) {
        if (n % d != 0) continue;
        ans = (ans + eulerTotient(n / d) % MOD * power(k, d, MOD)) % MOD;
        if (d != n / d)
            ans = (ans + eulerTotient(d) % MOD * power(k, n / d, MOD)) % MOD;
    }
    return ans % MOD * power(n, MOD - 2, MOD) % MOD;
}

/*
 * 4. BURNSIDE WITH DP — Necklace with constraints
 *    Count necklaces where no two adjacent beads have same color.
 *    Fix(rotation by d) = number of valid colorings fixed by rotation by d.
 *    A coloring is fixed by rotation by d iff it's periodic with period d.
 *
 *    For rotation by d positions (where d | n):
 *    Fix = number of valid (d-length) colorings of a cycle of length d = P(C_d, k)
 *    But only if n/d copies work, i.e., gcd consideration.
 *
 *    Fix(rotation by j) = number of colorings where color[i] = color[i+j]
 *    This means the coloring is periodic with period gcd(n, j).
 *    Fix = P(C_{gcd(n,j)}, k)  if gcd(n,j) | n  (always true)
 */
long long constrainedNecklaces(int n, int k) {
    long long ans = 0;
    for (int j = 0; j < n; j++) {
        int d = __gcd(n, j == 0 ? n : j);
        // P(C_d, k) = (k-1)^d + (-1)^d * (k-1)
        long long fix = circularColoring(d, k);
        ans = (ans + fix) % MOD;
    }
    return ans % MOD * power(n, MOD - 2, MOD) % MOD;
}

/*
 * 5. DP ON PERMUTATION CYCLE STRUCTURE
 *    Count permutations of [1..n] with exactly k cycles.
 *    This is Stirling number of the first kind: c(n, k)
 *    c(n, k) = (n-1)*c(n-1, k) + c(n-1, k-1)
 */
long long permWithKCycles(int n, int k) {
    vector<vector<long long>> c(n + 1, vector<long long>(k + 1, 0));
    c[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= min(i, k); j++)
            c[i][j] = ((long long)(i - 1) * c[i-1][j] + c[i-1][j-1]) % MOD;
    return c[n][k];
}

/*
 * 6. CIRCULAR SUBARRAY MAX — Kadane on circular array (LeetCode 918)
 *    max(standard Kadane, total_sum - min_subarray_sum)
 */
int circularMaxSubarray(vector<int>& nums) {
    int maxKadane = INT_MIN, minKadane = INT_MAX;
    int curMax = 0, curMin = 0, total = 0;

    for (int x : nums) {
        curMax = max(x, curMax + x);
        maxKadane = max(maxKadane, curMax);
        curMin = min(x, curMin + x);
        minKadane = min(minKadane, curMin);
        total += x;
    }

    if (total == minKadane) return maxKadane;  // All negative
    return max(maxKadane, total - minKadane);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== CIRCULAR DP & BURNSIDE ===" << endl;

    // Circular coloring
    cout << "\n--- Circular Coloring (no adjacent same) ---" << endl;
    for (int n = 3; n <= 8; n++)
        cout << "n=" << n << ", k=3: " << circularColoring(n, 3) << endl;

    // Necklaces
    cout << "\n--- Distinct Necklaces (Burnside) ---" << endl;
    for (int n = 3; n <= 8; n++)
        cout << "n=" << n << ", k=2: " << countNecklaces(n, 2) << endl;

    // Constrained necklaces (no adjacent same + rotational symmetry)
    cout << "\n--- Constrained Necklaces ---" << endl;
    for (int n = 3; n <= 8; n++)
        cout << "n=" << n << ", k=3: " << constrainedNecklaces(n, 3) << endl;

    // Permutations with k cycles
    cout << "\n--- Permutations with k Cycles ---" << endl;
    for (int k = 1; k <= 4; k++)
        cout << "c(5," << k << ") = " << permWithKCycles(5, k) << "  ";
    cout << endl;

    // Circular max subarray
    vector<int> nums = {5, -3, 5};
    cout << "\n--- Circular Max Subarray ---" << endl;
    cout << "Max: " << circularMaxSubarray(nums) << endl;

    // House Robber circular
    vector<int> houses = {2, 3, 2};
    cout << "\n--- House Robber Circular ---" << endl;
    cout << "Max: " << houseRobberCircular(houses) << endl;

    return 0;
}

