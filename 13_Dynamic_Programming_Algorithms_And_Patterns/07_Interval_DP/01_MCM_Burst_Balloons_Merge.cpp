/*
 * ============================================================================
 *                    INTERVAL DP — MCM & BURST BALLOONS
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Interval DP — Matrix Chain, Burst Balloons, Merge Stones
 * Level   : ⭐⭐⭐ Advanced
 * ============================================================================
 *
 * INTERVAL DP PATTERN:
 *   dp[i][j] = optimal answer for the subproblem on range [i..j]
 *   dp[i][j] = optimize over all split points k in [i..j-1]:
 *              dp[i][k] + dp[k+1][j] + cost(i, j, k)
 *
 * TEMPLATE:
 *   for (len = 2; len <= n; len++)        // increasing length
 *     for (i = 0; i + len - 1 < n; i++)   // start
 *       j = i + len - 1;                   // end
 *       for (k = i; k < j; k++)            // split point
 *         dp[i][j] = optimize(dp[i][k] + dp[k+1][j] + cost)
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * 1. MATRIX CHAIN MULTIPLICATION
 *    Given dimensions p[], find min scalar multiplications.
 *    Matrix i has dimensions p[i-1] × p[i].
 *    dp[i][j] = min cost to multiply matrices i..j
 *    dp[i][j] = min over k: dp[i][k] + dp[k+1][j] + p[i-1]*p[k]*p[j]
 *    Time: O(n³), Space: O(n²)
 */
int matrixChainMul(vector<int>& p) {
    int n = p.size() - 1;  // Number of matrices
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k+1][j] + p[i] * p[k+1] * p[j+1];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    return dp[0][n-1];
}

/*
 * 2. BURST BALLOONS (LeetCode 312)
 *    Given balloons with values, burst them to maximize coins.
 *    Bursting balloon i gives nums[l] * nums[i] * nums[r] coins.
 *
 *    KEY INSIGHT: Think about which balloon to burst LAST in range [i..j]
 *    dp[i][j] = max coins from bursting all balloons in range (i, j)
 *    dp[i][j] = max over k: dp[i][k] + dp[k][j] + nums[i]*nums[k]*nums[j]
 */
int burstBalloons(vector<int>& nums) {
    int n = nums.size();
    vector<int> a(n + 2);
    a[0] = a[n + 1] = 1;
    for (int i = 0; i < n; i++) a[i + 1] = nums[i];
    n += 2;

    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int len = 2; len < n; len++) {
        for (int i = 0; i + len < n; i++) {
            int j = i + len;
            for (int k = i + 1; k < j; k++) {
                dp[i][j] = max(dp[i][j],
                    dp[i][k] + dp[k][j] + a[i] * a[k] * a[j]);
            }
        }
    }
    return dp[0][n-1];
}

/*
 * 3. MINIMUM COST TO MERGE STONES (LeetCode 1000)
 *    Merge k consecutive piles. Cost = sum of merged piles.
 *    dp[i][j] = min cost to merge piles[i..j] into as few piles as possible
 */
int mergeStones(vector<int>& stones, int k) {
    int n = stones.size();
    if ((n - 1) % (k - 1) != 0) return -1;

    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i+1] = prefix[i] + stones[i];

    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int len = k; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int mid = i; mid < j; mid += k - 1) {
                dp[i][j] = min(dp[i][j], dp[i][mid] + dp[mid+1][j]);
            }
            if ((j - i) % (k - 1) == 0) {
                dp[i][j] += prefix[j+1] - prefix[i];
            }
        }
    }
    return dp[0][n-1];
}

/*
 * 4. PALINDROME PARTITIONING II (LeetCode 132)
 *    Min cuts to partition string into palindromes.
 */
int palindromePartition(string& s) {
    int n = s.size();
    vector<vector<bool>> isPalin(n, vector<bool>(n, false));

    for (int i = n - 1; i >= 0; i--)
        for (int j = i; j < n; j++)
            isPalin[i][j] = (s[i] == s[j]) && (j - i <= 2 || isPalin[i+1][j-1]);

    vector<int> dp(n, 0);
    for (int i = 0; i < n; i++) {
        if (isPalin[0][i]) { dp[i] = 0; continue; }
        dp[i] = i;
        for (int j = 1; j <= i; j++)
            if (isPalin[j][i])
                dp[i] = min(dp[i], dp[j-1] + 1);
    }
    return dp[n-1];
}

/*
 * 5. OPTIMAL BST
 *    Given keys with frequencies, build BST minimizing search cost.
 *    dp[i][j] = min cost BST using keys[i..j]
 */
int optimalBST(vector<int>& keys, vector<int>& freq) {
    int n = keys.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) dp[i][i] = freq[i];

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            int freqSum = 0;
            for (int x = i; x <= j; x++) freqSum += freq[x];

            for (int k = i; k <= j; k++) {
                int cost = freqSum;
                if (k > i) cost += dp[i][k-1];
                if (k < j) cost += dp[k+1][j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    return dp[0][n-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== INTERVAL DP ===" << endl;

    // MCM
    vector<int> dims = {10, 20, 30, 40, 30};
    cout << "\n--- Matrix Chain Multiplication ---" << endl;
    cout << "Dimensions: "; for (int d : dims) cout << d << " ";
    cout << "\nMin multiplications: " << matrixChainMul(dims) << endl;

    // Burst Balloons
    vector<int> balloons = {3, 1, 5, 8};
    cout << "\n--- Burst Balloons ---" << endl;
    cout << "Balloons: "; for (int b : balloons) cout << b << " ";
    cout << "\nMax coins: " << burstBalloons(balloons) << endl;

    // Merge Stones
    vector<int> stones = {3, 2, 4, 1};
    cout << "\n--- Merge Stones (k=2) ---" << endl;
    cout << "Min cost: " << mergeStones(stones, 2) << endl;

    // Palindrome Partition
    string s = "aab";
    cout << "\n--- Palindrome Partition ---" << endl;
    cout << "\"" << s << "\" → " << palindromePartition(s) << " cuts" << endl;

    // Optimal BST
    vector<int> keys = {10, 12, 20};
    vector<int> freq = {34, 8, 50};
    cout << "\n--- Optimal BST ---" << endl;
    cout << "Min cost: " << optimalBST(keys, freq) << endl;

    return 0;
}

