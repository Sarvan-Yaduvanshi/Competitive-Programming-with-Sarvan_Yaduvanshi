/*
 * ============================================================================
 *              KADANE'S ALGORITHM & MAX SUBARRAY VARIANTS
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : 1D DP — Kadane, Max Product Subarray, Partition DP
 * Level   : ⭐⭐ Intermediate
 * ============================================================================
 *
 * KADANE'S ALGORITHM (LeetCode 53):
 *   dp[i] = max subarray sum ending at i
 *   dp[i] = max(arr[i], dp[i-1] + arr[i])
 *   Answer = max of all dp[i]
 *
 * MAX PRODUCT SUBARRAY (LeetCode 152):
 *   Track both max and min (negative × negative = positive!)
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// Kadane's Algorithm — Max Subarray Sum
// Time: O(n), Space: O(1)
int maxSubarraySum(vector<int>& nums) {
    int maxEndingHere = nums[0];
    int maxSoFar = nums[0];

    for (int i = 1; i < (int)nums.size(); i++) {
        maxEndingHere = max(nums[i], maxEndingHere + nums[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }
    return maxSoFar;
}

// Kadane with subarray indices
pair<int, pair<int,int>> kadaneWithIndices(vector<int>& nums) {
    int maxSum = nums[0], currSum = nums[0];
    int start = 0, end = 0, tempStart = 0;

    for (int i = 1; i < (int)nums.size(); i++) {
        if (nums[i] > currSum + nums[i]) {
            currSum = nums[i];
            tempStart = i;
        } else {
            currSum += nums[i];
        }
        if (currSum > maxSum) {
            maxSum = currSum;
            start = tempStart;
            end = i;
        }
    }
    return {maxSum, {start, end}};
}

// Maximum Product Subarray (LeetCode 152)
// Track max AND min because min * negative = new max
int maxProductSubarray(vector<int>& nums) {
    int maxProd = nums[0], minProd = nums[0], result = nums[0];

    for (int i = 1; i < (int)nums.size(); i++) {
        if (nums[i] < 0) swap(maxProd, minProd);

        maxProd = max(nums[i], maxProd * nums[i]);
        minProd = min(nums[i], minProd * nums[i]);
        result = max(result, maxProd);
    }
    return result;
}

// Maximum Circular Subarray Sum (LeetCode 918)
// Answer = max(normal kadane, total_sum - min_subarray)
int maxCircularSubarray(vector<int>& nums) {
    int totalSum = 0;
    int maxSum = nums[0], currMax = 0;
    int minSum = nums[0], currMin = 0;

    for (int num : nums) {
        currMax = max(num, currMax + num);
        maxSum = max(maxSum, currMax);

        currMin = min(num, currMin + num);
        minSum = min(minSum, currMin);

        totalSum += num;
    }

    // If all negative, maxSum is the answer
    return maxSum > 0 ? max(maxSum, totalSum - minSum) : maxSum;
}

// Maximum Sum with No K Adjacent Elements
long long maxSumNoKAdjacent(vector<int>& arr, int k) {
    int n = arr.size();
    vector<long long> dp(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i-1];  // Skip current
        // Take current, skip back k steps
        int prev = max(0, i - k);
        dp[i] = max(dp[i], (prev > 0 ? dp[prev - 1] : 0LL) + arr[i-1]);
    }
    return dp[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== KADANE & MAX SUBARRAY VARIANTS ===" << endl;

    // Kadane's
    vector<int> arr1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "\n--- Kadane's Algorithm ---" << endl;
    cout << "Array: "; for (int x : arr1) cout << x << " ";
    cout << "\nMax subarray sum: " << maxSubarraySum(arr1) << endl;

    auto [sum, indices] = kadaneWithIndices(arr1);
    cout << "Subarray [" << indices.first << ".." << indices.second
         << "] = " << sum << endl;

    // Max Product
    vector<int> arr2 = {2, 3, -2, 4};
    cout << "\n--- Max Product Subarray ---" << endl;
    cout << "Array: "; for (int x : arr2) cout << x << " ";
    cout << "\nMax product: " << maxProductSubarray(arr2) << endl;

    vector<int> arr3 = {-2, 0, -1};
    cout << "Array: "; for (int x : arr3) cout << x << " ";
    cout << "\nMax product: " << maxProductSubarray(arr3) << endl;

    // Circular
    vector<int> arr4 = {5, -3, 5};
    cout << "\n--- Max Circular Subarray ---" << endl;
    cout << "Array: "; for (int x : arr4) cout << x << " ";
    cout << "\nMax circular sum: " << maxCircularSubarray(arr4) << endl;
    // Wrap around: 5+5 = 10

    return 0;
}

