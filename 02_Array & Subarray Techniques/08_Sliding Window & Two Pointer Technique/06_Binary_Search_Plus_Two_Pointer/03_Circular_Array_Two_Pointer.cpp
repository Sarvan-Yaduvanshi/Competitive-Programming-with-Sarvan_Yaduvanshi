/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Circular Array Two Pointer Problems
 *  Level   : Medium → Hard
 * ============================================================================
 *
 *  ▶ WHAT IS CIRCULAR TWO POINTER?
 *  ───────────────────────────────
 *  In circular arrays, the array wraps around: after index N-1 comes index 0.
 *  Two pointer on circular arrays requires special handling:
 *    - Use modular arithmetic: next = (i + 1) % N
 *    - Or "double the array" trick: concatenate arr with itself
 *    - Or split into two cases: subarray doesn't wrap vs subarray wraps
 *
 *  ▶ KEY INSIGHT — "WRAP = TOTAL - NON-WRAP":
 *  ───────────────────────────────────────────
 *  For MANY circular subarray problems:
 *    max circular subarray = totalSum - min non-circular subarray
 *    min circular subarray = totalSum - max non-circular subarray
 *
 *  This avoids explicit circular handling!
 *
 *  PROBLEMS:
 *  LC 918  — Maximum Sum Circular Subarray
 *            https://leetcode.com/problems/maximum-sum-circular-subarray/
 *  LC 1838 — Frequency of the Most Frequent Element (sort + sliding window)
 *            https://leetcode.com/problems/frequency-of-the-most-frequent-element/
 *  LC 2134 — Min Swaps to Group All 1s Together II (circular fixed window)
 *            https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/
 *  LC 503  — Next Greater Element II (circular — use 2N technique)
 *            https://leetcode.com/problems/next-greater-element-ii/
 *  LC 457  — Circular Array Loop (covered in Module 04)
 *            https://leetcode.com/problems/circular-array-loop/
 *  CF 1860C — Game on Permutation (circular greedy, 1400)
 *            https://codeforces.com/problemset/problem/1860/C
 *  CSES 1662 — Subarray Divisibility (prefix + modular arithmetic)
 *            https://cses.fi/problemset/task/1662
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>
using namespace std;

// ============================================================================
// LC 918: Maximum Sum Circular Subarray
// ============================================================================
/*
 * APPROACH — Two Cases:
 * Case 1: Max subarray does NOT wrap around → standard Kadane's
 * Case 2: Max subarray WRAPS around → totalSum - minSubarray
 *         (because wrapping subarray = total - middle non-wrapping subarray)
 *
 * Answer = max(Case 1, Case 2)
 *
 * EDGE CASE: If all elements are negative, minSubarray = totalSum,
 * so Case 2 gives 0. We must return Case 1 (the "least negative" element).
 *
 * Time: O(N), Space: O(1)
 *
 *  VISUAL:
 *  Non-wrapping:  [... maxSub ...]
 *  Wrapping:      [maxPart] ... minSub ... [maxPart]
 *                  total - minSub = wrapping max
 */
int maxSubarraySumCircular(vector<int>& nums) {
    int totalSum = 0;
    int maxSum = INT_MIN, curMax = 0;  // Kadane for max
    int minSum = INT_MAX, curMin = 0;  // Kadane for min

    for (int x : nums) {
        totalSum += x;

        curMax = max(curMax + x, x);
        maxSum = max(maxSum, curMax);

        curMin = min(curMin + x, x);
        minSum = min(minSum, curMin);
    }

    // If all negative, minSum == totalSum, wrapping gives 0 → invalid
    if (maxSum < 0) return maxSum;

    return max(maxSum, totalSum - minSum);
}

// ============================================================================
// LC 2134: Minimum Swaps to Group All 1s Together II (Circular Fixed Window)
// ============================================================================
/*
 * Circular binary array. Group all 1s together with minimum swaps.
 *
 * TRICK:
 * 1. Count total 1s → that's the window size K.
 * 2. "Double the array" or use modular indexing to handle circularity.
 * 3. Fixed window of size K: find window with MOST 1s already present.
 * 4. Answer = K - maxOnesInWindow (= swaps needed).
 *
 * Time: O(N), Space: O(1)
 */
int minSwaps(vector<int>& nums) {
    int n = nums.size();
    int totalOnes = 0;
    for (int x : nums) totalOnes += x;

    if (totalOnes <= 1) return 0;

    // Circular fixed window of size totalOnes
    int k = totalOnes;
    int onesInWindow = 0;

    // Initialize first window
    for (int i = 0; i < k; i++)
        onesInWindow += nums[i % n];

    int maxOnes = onesInWindow;

    // Slide window circularly
    for (int i = 1; i < n; i++) {
        onesInWindow += nums[(i + k - 1) % n];  // Add new right
        onesInWindow -= nums[(i - 1) % n];       // Remove old left
        maxOnes = max(maxOnes, onesInWindow);
    }

    return k - maxOnes;
}

// ============================================================================
// LC 503: Next Greater Element II (Circular Stack — 2N technique)
// ============================================================================
/*
 * For each element in a circular array, find next greater element.
 *
 * TRICK: Iterate through array TWICE (0 to 2N-1), use i % N for indexing.
 * Monotone decreasing stack. Only assign result in first pass.
 *
 * Time: O(N), Space: O(N)
 */
#include <stack>
vector<int> nextGreaterElements(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st; // Stores indices

    for (int i = 0; i < 2 * n; i++) {
        while (!st.empty() && nums[st.top()] < nums[i % n]) {
            result[st.top()] = nums[i % n];
            st.pop();
        }
        if (i < n) st.push(i); // Only push in first pass
    }
    return result;
}

// ============================================================================
// Circular Subarray Queries — General Technique
// ============================================================================
/*
 * GENERAL RULE for circular subarrays:
 * ─────────────────────────────────────
 * For ANY "max/min circular subarray" problem, use:
 *   circular_max = totalSum - non_circular_min
 *   circular_min = totalSum - non_circular_max
 *
 * For FIXED SIZE K circular windows:
 *   Use "double the array" or "modular arithmetic"
 *   index: i % N
 *
 * For EXISTENCE problems (does circular subarray with property X exist?):
 *   Split into 2 cases:
 *   Case A: subarray is [l..r] where l ≤ r (normal)
 *   Case B: subarray is [l..N-1] ∪ [0..r] (wrapping)
 *   Case B equivalent: complement [r+1..l-1] does NOT have property X
 */

int main() {
    // LC 918: Max Sum Circular Subarray
    vector<int> nums1 = {5, -3, 5};
    cout << "Max Circular Sum: " << maxSubarraySumCircular(nums1) << "\n"; // 10

    vector<int> nums2 = {-3, -2, -3};
    cout << "All negative: " << maxSubarraySumCircular(nums2) << "\n"; // -2

    // LC 2134: Min Swaps to Group 1s
    vector<int> nums3 = {0, 1, 0, 1, 1, 0, 0};
    cout << "Min swaps: " << minSwaps(nums3) << "\n"; // 1

    // LC 503: Next Greater Element II
    vector<int> nums4 = {1, 2, 1};
    auto res = nextGreaterElements(nums4);
    cout << "Next Greater II: ";
    for (int x : res) cout << x << " ";
    cout << "\n"; // 2 -1 2

    return 0;
}

