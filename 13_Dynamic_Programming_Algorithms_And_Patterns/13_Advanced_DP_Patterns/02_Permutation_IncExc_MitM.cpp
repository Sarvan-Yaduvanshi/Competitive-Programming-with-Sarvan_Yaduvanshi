/*
 * ============================================================================
 *    ADVANCED DP — PERMUTATION DP, INCLUSION-EXCLUSION, MEET-IN-MIDDLE
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Advanced DP — Permutation DP, Inclusion-Exclusion DP, MitM
 * Level   : ⭐⭐⭐⭐⭐ Grandmaster
 * ============================================================================
 *
 * DP ON PERMUTATIONS:
 *   Count permutations with specific constraints.
 *   Often combined with bitmask DP.
 *   dp[i][mask] = ways to place first i elements into positions in mask.
 *
 * DP WITH INCLUSION-EXCLUSION:
 *   Count objects satisfying ALL conditions by including/excluding subsets.
 *   |A₁ ∩ A₂ ∩ ... ∩ Aₙ| = Σ(-1)^|S| * |complement of union of S|
 *
 * DP WITH MEET-IN-THE-MIDDLE:
 *   Split elements into two halves. DP on each half.
 *   Merge results. Turns O(2^n) into O(2^(n/2)).
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

/*
 * 1. PERMUTATION DP — AtCoder DP T
 *    Given sequence of '<' and '>', count permutations of [1..n]
 *    that satisfy the constraints.
 *
 *    dp[i][j] = number of valid permutations of first i elements
 *               where the i-th element is the j-th smallest among first i.
 */
long long permutationDP(string& s) {
    int n = s.size() + 1;
    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));
    dp[1][1] = 1;

    for (int i = 2; i <= n; i++) {
        // Prefix sums for efficient computation
        vector<long long> prefix(n + 2, 0);
        for (int j = 1; j <= i - 1; j++)
            prefix[j] = (prefix[j - 1] + dp[i - 1][j]) % MOD;

        for (int j = 1; j <= i; j++) {
            if (s[i - 2] == '<') {
                // j-th position: elements before j are smaller
                // Sum dp[i-1][1..j-1]
                dp[i][j] = prefix[j - 1];
            } else {
                // j-th position: elements before j are larger
                // Sum dp[i-1][j..i-1]
                dp[i][j] = (prefix[i - 1] - prefix[j - 1] + MOD) % MOD;
            }
        }
    }

    long long ans = 0;
    for (int j = 1; j <= n; j++)
        ans = (ans + dp[n][j]) % MOD;
    return ans;
}

/*
 * 2. DERANGEMENTS — Permutation with no fixed points
 *    D(n) = (n-1) * (D(n-1) + D(n-2))
 *    D(0) = 1, D(1) = 0
 */
long long derangements(int n) {
    if (n == 0) return 1;
    if (n == 1) return 0;
    long long a = 1, b = 0;  // D(0), D(1)
    for (int i = 2; i <= n; i++) {
        long long c = ((long long)(i - 1) % MOD * ((a + b) % MOD)) % MOD;
        a = b;
        b = c;
    }
    return b;
}

/*
 * 3. INCLUSION-EXCLUSION DP
 *    Count permutations where element i is NOT at forbidden position
 *
 *    Example: Count permutations of [1..n] where p[i] ≠ i for all i
 *    (Derangement — a special case)
 *
 *    General: forbidden[i] = set of positions where element i can't go
 *    Use bitmask + inclusion-exclusion.
 */

// Count ways to place n non-attacking rooks on an n×n board
// with some cells forbidden. Uses inclusion-exclusion.
long long rookPlacement(int n, vector<vector<bool>>& allowed) {
    // r[k] = number of ways to place k non-attacking rooks on forbidden cells
    // Answer = Σ (-1)^k * r[k] * (n-k)!

    // dp[mask] = ways to place rooks on rows in mask using columns 0,1,...
    vector<long long> dp(1 << n, 0);
    dp[0] = 1;

    for (int col = 0; col < n; col++) {
        vector<long long> ndp = dp;  // Don't place rook in this column
        for (int mask = 0; mask < (1 << n); mask++) {
            if (dp[mask] == 0) continue;
            for (int row = 0; row < n; row++) {
                if (mask & (1 << row)) continue;
                if (!allowed[row][col]) continue;
                ndp[mask | (1 << row)] = (ndp[mask | (1 << row)] + dp[mask]) % MOD;
            }
        }
        dp = ndp;
    }
    return dp[(1 << n) - 1];
}

/*
 * 4. MEET IN THE MIDDLE DP
 *    Problem: Given n numbers (n ≤ 40), count subsets with sum = target.
 *
 *    Naive: O(2^n) — too slow for n=40.
 *    MitM: Split into two halves of n/2 each.
 *          Generate all 2^(n/2) subset sums for each half.
 *          For each sum in first half, binary search complement in second.
 *    Time: O(2^(n/2) * log(2^(n/2))) = O(2^(n/2) * n)
 */
long long meetInMiddle(vector<long long>& nums, long long target) {
    int n = nums.size();
    int half = n / 2;

    // Generate all subset sums for first half
    vector<long long> left;
    for (int mask = 0; mask < (1 << half); mask++) {
        long long sum = 0;
        for (int i = 0; i < half; i++)
            if (mask & (1 << i)) sum += nums[i];
        left.push_back(sum);
    }

    // Generate all subset sums for second half
    vector<long long> right;
    int rn = n - half;
    for (int mask = 0; mask < (1 << rn); mask++) {
        long long sum = 0;
        for (int i = 0; i < rn; i++)
            if (mask & (1 << i)) sum += nums[half + i];
        right.push_back(sum);
    }

    sort(right.begin(), right.end());

    long long count = 0;
    for (long long lsum : left) {
        long long need = target - lsum;
        // Count occurrences of 'need' in right
        count += upper_bound(right.begin(), right.end(), need)
               - lower_bound(right.begin(), right.end(), need);
    }
    return count;
}

/*
 * 5. DP WITH BITSETS — Speed up subset DP
 *    Use bitset<N> to parallelize boolean DP transitions.
 *    Example: Subset Sum with bitset — O(n * maxSum / 64)
 */
bool subsetSumBitset(vector<int>& nums, int target) {
    bitset<100001> dp;
    dp[0] = 1;

    for (int num : nums) {
        dp |= (dp << num);  // All sums achievable by adding 'num'
    }
    return dp[target];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== ADVANCED DP PATTERNS ===" << endl;

    // Permutation DP
    string s = "<><";
    cout << "\n--- Permutation DP ---" << endl;
    cout << "Pattern: " << s << endl;
    cout << "Valid permutations: " << permutationDP(s) << endl;

    // Derangements
    cout << "\n--- Derangements ---" << endl;
    for (int n = 0; n <= 8; n++)
        cout << "D(" << n << ") = " << derangements(n) << endl;

    // Meet in the Middle
    vector<long long> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    long long target = 15;
    cout << "\n--- Meet in the Middle ---" << endl;
    cout << "Subsets with sum " << target << ": " << meetInMiddle(nums, target) << endl;

    // Subset Sum with Bitset
    vector<int> arr = {3, 34, 4, 12, 5, 2};
    cout << "\n--- Subset Sum (Bitset) ---" << endl;
    cout << "Sum 9: " << (subsetSumBitset(arr, 9) ? "YES" : "NO") << endl;
    cout << "Sum 30: " << (subsetSumBitset(arr, 30) ? "YES" : "NO") << endl;

    return 0;
}

