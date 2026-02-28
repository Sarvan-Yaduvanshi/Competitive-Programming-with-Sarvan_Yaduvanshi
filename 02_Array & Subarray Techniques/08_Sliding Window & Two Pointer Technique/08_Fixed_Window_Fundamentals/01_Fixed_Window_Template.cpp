/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Fixed Size Sliding Window — Template & Intuition
 *  Level   : Beginner
 * ============================================================================
 *
 *  ▶ WHAT IS FIXED SIZE SLIDING WINDOW?
 *  ─────────────────────────────────────
 *  A window of FIXED size K slides across the array one position at a time.
 *  At each step:
 *  - ADD the new element entering from the right
 *  - REMOVE the element leaving from the left
 *  - COMPUTE/UPDATE the answer for the current window
 *
 *  This avoids recomputing the entire window from scratch → O(1) per slide.
 *
 *  ▶ TEMPLATE:
 *  ───────────
 *  int left = 0;
 *  for (int right = 0; right < N; right++) {
 *      // 1. ADD arr[right] to window state
 *
 *      // 2. Once window reaches size K
 *      if (right - left + 1 == K) {
 *          // 3. COMPUTE answer for this window
 *
 *          // 4. REMOVE arr[left] from window state
 *          left++;
 *      }
 *  }
 *
 *  ▶ WHEN TO USE:
 *  ──────────────
 *  ✅ "Subarray of size K" / "Window of size K"
 *  ✅ "Every K consecutive elements"
 *  ✅ "Average / sum / max / min of K elements"
 *  ✅ Problem explicitly mentions a fixed size constraint
 *
 *  ▶ TIME: O(N), SPACE: O(1) to O(K) depending on window state
 *
 *  ▶ COMPARISON WITH BRUTE FORCE:
 *  ──────────────────────────────
 *  Brute Force: For each window, sum all K elements → O(N*K)
 *  Sliding Window: Slide by adding 1 and removing 1 → O(N)
 *
 *  PROBLEMS:
 *  GFG    — Max Sum Subarray of Size K
 *           https://practice.geeksforgeeks.org/problems/max-sum-subarray-of-size-k/
 *  LC 643 — Maximum Average Subarray I
 *           https://leetcode.com/problems/maximum-average-subarray-i/
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// ============================================================================
// Basic Template: Max Sum Subarray of Size K
// ============================================================================
int maxSumSubarraySizeK(vector<int>& arr, int k) {
    int n = arr.size();
    int windowSum = 0, maxSum = INT_MIN;

    for (int right = 0; right < n; right++) {
        windowSum += arr[right];             // Add right element

        if (right >= k - 1) {                // Window reached size K
            maxSum = max(maxSum, windowSum);  // Compute answer
            windowSum -= arr[right - k + 1]; // Remove leftmost element
        }
    }
    return maxSum;
}

// Alternative template using left pointer explicitly
int maxSumSubarraySizeK_v2(vector<int>& arr, int k) {
    int n = arr.size();
    int windowSum = 0, maxSum = INT_MIN;
    int left = 0;

    for (int right = 0; right < n; right++) {
        windowSum += arr[right];

        if (right - left + 1 == k) {
            maxSum = max(maxSum, windowSum);
            windowSum -= arr[left];
            left++;
        }
    }
    return maxSum;
}

// Min Sum Subarray of Size K
int minSumSubarraySizeK(vector<int>& arr, int k) {
    int n = arr.size();
    int windowSum = 0, minSum = INT_MAX;
    int left = 0;

    for (int right = 0; right < n; right++) {
        windowSum += arr[right];
        if (right - left + 1 == k) {
            minSum = min(minSum, windowSum);
            windowSum -= arr[left];
            left++;
        }
    }
    return minSum;
}

// LC 643: Maximum Average Subarray I
double findMaxAverage(vector<int>& nums, int k) {
    int windowSum = 0;
    for (int i = 0; i < k; i++) windowSum += nums[i];

    int maxSum = windowSum;
    for (int i = k; i < (int)nums.size(); i++) {
        windowSum += nums[i] - nums[i - k];
        maxSum = max(maxSum, windowSum);
    }
    return (double)maxSum / k;
}

int main() {
    vector<int> arr = {2, 1, 5, 1, 3, 2};
    cout << "Max sum (K=3): " << maxSumSubarraySizeK(arr, 3) << "\n";   // 9
    cout << "Min sum (K=3): " << minSumSubarraySizeK(arr, 3) << "\n";   // 6

    vector<int> nums = {1, 12, -5, -6, 50, 3};
    cout << "Max avg (K=4): " << findMaxAverage(nums, 4) << "\n";       // 12.75

    return 0;
}

