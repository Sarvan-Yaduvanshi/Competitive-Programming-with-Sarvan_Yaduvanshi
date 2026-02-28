/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Variable Size Sliding Window — Templates
 *  Level   : Intermediate
 * ============================================================================
 *
 *  ▶ WHAT IS VARIABLE SIZE SLIDING WINDOW?
 *  ───────────────────────────────────────
 *  Unlike fixed window (size always K), the window SIZE CHANGES dynamically.
 *  We EXPAND the right boundary, and SHRINK the left boundary based on
 *  whether a condition is satisfied.
 *
 *  TWO MAIN PATTERNS:
 *
 *  PATTERN A: LONGEST Subarray/Substring Satisfying Condition
 *  ──────────────────────────────────────────────────────────
 *  int left = 0, best = 0;
 *  for (int right = 0; right < N; right++) {
 *      // ADD arr[right] to window
 *      while (window VIOLATES condition) {
 *          // REMOVE arr[left] from window
 *          left++;
 *      }
 *      best = max(best, right - left + 1);
 *  }
 *
 *  PATTERN B: SHORTEST Subarray/Substring Satisfying Condition
 *  ───────────────────────────────────────────────────────────
 *  int left = 0, best = INF;
 *  for (int right = 0; right < N; right++) {
 *      // ADD arr[right] to window
 *      while (window SATISFIES condition) {
 *          best = min(best, right - left + 1);
 *          // REMOVE arr[left] from window (try to shrink more)
 *          left++;
 *      }
 *  }
 *
 *  ▶ KEY INSIGHT: WHY O(N)?
 *  ────────────────────────
 *  Left pointer only moves forward. Right pointer only moves forward.
 *  Each pointer visits each element at most once → O(N) total.
 *
 *  ▶ WHEN TO USE:
 *  ──────────────
 *  ✅ "Longest subarray with sum ≤ K"
 *  ✅ "Shortest subarray with sum ≥ K"
 *  ✅ "Longest substring with at most K distinct characters"
 *  ✅ "Minimum window containing all characters"
 *  ✅ Any problem where the window can grow/shrink based on a condition
 *
 *  PROBLEMS:
 *  LC 209  — Minimum Size Subarray Sum
 *            https://leetcode.com/problems/minimum-size-subarray-sum/
 *  LC 1004 — Max Consecutive Ones III
 *            https://leetcode.com/problems/max-consecutive-ones-iii/
 *  GFG     — Longest Subarray with Sum K
 *            https://practice.geeksforgeeks.org/problems/longest-sub-array-with-sum-k/
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// ============================================================================
// PATTERN A: Longest Subarray with Sum ≤ target (all positives)
// ============================================================================
int longestSubarraySumAtMost(vector<int>& arr, int target) {
    int n = arr.size();
    int left = 0, sum = 0, best = 0;

    for (int right = 0; right < n; right++) {
        sum += arr[right];
        while (sum > target) {
            sum -= arr[left];
            left++;
        }
        best = max(best, right - left + 1);
    }
    return best;
}

// ============================================================================
// PATTERN B: Shortest Subarray with Sum ≥ target
// LC 209: Minimum Size Subarray Sum
// https://leetcode.com/problems/minimum-size-subarray-sum/
// ============================================================================
int minSubArrayLen(int target, vector<int>& nums) {
    int n = nums.size();
    int left = 0, sum = 0, best = INT_MAX;

    for (int right = 0; right < n; right++) {
        sum += nums[right];
        while (sum >= target) {
            best = min(best, right - left + 1);
            sum -= nums[left];
            left++;
        }
    }
    return best == INT_MAX ? 0 : best;
}

// ============================================================================
// LC 1004: Max Consecutive Ones III — flip at most K zeros
// https://leetcode.com/problems/max-consecutive-ones-iii/
// ============================================================================
/*
 * TRICK: Find longest subarray with at most K zeros.
 * Window condition: count of zeros in window ≤ K.
 */
int longestOnes(vector<int>& nums, int k) {
    int left = 0, zeros = 0, best = 0;

    for (int right = 0; right < (int)nums.size(); right++) {
        if (nums[right] == 0) zeros++;
        while (zeros > k) {
            if (nums[left] == 0) zeros--;
            left++;
        }
        best = max(best, right - left + 1);
    }
    return best;
}

// ============================================================================
// LC 713: Subarray Product Less Than K — Count subarrays
// https://leetcode.com/problems/subarray-product-less-than-k/
// ============================================================================
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    if (k <= 1) return 0;
    int left = 0, count = 0;
    long long product = 1;

    for (int right = 0; right < (int)nums.size(); right++) {
        product *= nums[right];
        while (product >= k) {
            product /= nums[left];
            left++;
        }
        // All subarrays ending at 'right' with start in [left..right]
        count += (right - left + 1);
    }
    return count;
}

// ============================================================================
// LC 1658: Min Operations to Reduce X to Zero — Reverse thinking!
// https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/
// ============================================================================
/*
 * TRICK: Removing from ends with sum = x
 *      = Finding MIDDLE subarray with sum = totalSum - x
 *      Find longest middle subarray with sum = totalSum - x.
 *      Answer = N - length of that subarray.
 */
int minOperations(vector<int>& nums, int x) {
    int n = nums.size();
    int totalSum = 0;
    for (int num : nums) totalSum += num;

    int target = totalSum - x;
    if (target < 0) return -1;
    if (target == 0) return n;

    int left = 0, windowSum = 0, maxLen = -1;
    for (int right = 0; right < n; right++) {
        windowSum += nums[right];
        while (windowSum > target) {
            windowSum -= nums[left];
            left++;
        }
        if (windowSum == target)
            maxLen = max(maxLen, right - left + 1);
    }
    return maxLen == -1 ? -1 : n - maxLen;
}

int main() {
    // Shortest subarray sum ≥ 7
    vector<int> nums = {2, 3, 1, 2, 4, 3};
    cout << "Min subarray len (sum≥7): " << minSubArrayLen(7, nums) << "\n"; // 2

    // Max consecutive ones with K flips
    vector<int> arr = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
    cout << "Max ones (K=2): " << longestOnes(arr, 2) << "\n"; // 6

    // Product less than K
    vector<int> nums2 = {10, 5, 2, 6};
    cout << "Product < 100: " << numSubarrayProductLessThanK(nums2, 100) << "\n"; // 8

    // Min operations
    vector<int> nums3 = {1, 1, 4, 2, 3};
    cout << "Min ops (x=5): " << minOperations(nums3, 5) << "\n"; // 2

    return 0;
}

