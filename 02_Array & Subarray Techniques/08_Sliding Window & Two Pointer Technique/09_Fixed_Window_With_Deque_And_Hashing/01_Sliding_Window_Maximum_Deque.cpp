/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Sliding Window Maximum — Monotonic Deque
 *  Level   : Hard
 * ============================================================================
 *
 *  LC 239  — Sliding Window Maximum
 *            https://leetcode.com/problems/sliding-window-maximum/
 *  LC 1438 — Longest Subarray Abs Diff ≤ Limit (two deques)
 *            https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/
 *  LC 480  — Sliding Window Median
 *            https://leetcode.com/problems/sliding-window-median/
 *  CSES 1077 — Sliding Window Median
 *             https://cses.fi/problemset/task/1077
 *  CSES 1076 — Sliding Window Cost
 *             https://cses.fi/problemset/task/1076
 *  GFG     — Maximum of all subarrays of size K
 *            https://practice.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k/
 *
 *  ▶ MONOTONIC DEQUE:
 *  ──────────────────
 *  Maintain a deque of INDICES where values are decreasing (for max).
 *  - Front of deque = index of current window maximum
 *  - When adding new element: pop all smaller elements from back (they'll never be max)
 *  - When sliding: pop front if it's outside the window
 *
 *  This gives O(1) amortized per element → O(N) total.
 *
 *  For MINIMUM: use increasing deque instead.
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

// ============================================================================
// LC 239: Sliding Window Maximum
// ============================================================================
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    deque<int> dq;  // Stores indices. Values are monotone decreasing.
    vector<int> result;

    for (int i = 0; i < n; i++) {
        // Remove indices outside the window
        while (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();

        // Remove all smaller elements from back (they'll never be the max)
        while (!dq.empty() && nums[dq.back()] <= nums[i])
            dq.pop_back();

        dq.push_back(i);

        // Once we have a full window, record the max
        if (i >= k - 1)
            result.push_back(nums[dq.front()]);
    }
    return result;
}

// Sliding Window MINIMUM (same idea, but increasing deque)
vector<int> minSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    deque<int> dq;
    vector<int> result;

    for (int i = 0; i < n; i++) {
        while (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();
        while (!dq.empty() && nums[dq.back()] >= nums[i])
            dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1)
            result.push_back(nums[dq.front()]);
    }
    return result;
}

// ============================================================================
// LC 1438: Longest Continuous Subarray With Abs Diff ≤ Limit
// Use TWO deques: one for max, one for min. Variable window.
// ============================================================================
int longestSubarray(vector<int>& nums, int limit) {
    deque<int> maxDq, minDq; // Indices
    int left = 0, best = 0;

    for (int right = 0; right < (int)nums.size(); right++) {
        while (!maxDq.empty() && nums[maxDq.back()] <= nums[right]) maxDq.pop_back();
        maxDq.push_back(right);
        while (!minDq.empty() && nums[minDq.back()] >= nums[right]) minDq.pop_back();
        minDq.push_back(right);

        // Shrink window if max - min > limit
        while (nums[maxDq.front()] - nums[minDq.front()] > limit) {
            left++;
            if (maxDq.front() < left) maxDq.pop_front();
            if (minDq.front() < left) minDq.pop_front();
        }
        best = max(best, right - left + 1);
    }
    return best;
}

int main() {
    // Sliding Window Maximum
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    auto res = maxSlidingWindow(nums, 3);
    cout << "Window Max (K=3): ";
    for (int x : res) cout << x << " ";
    cout << "\n"; // 3 3 5 5 6 7

    // Longest subarray with |diff| ≤ limit
    vector<int> nums2 = {8, 2, 4, 7};
    cout << "Longest (limit=4): " << longestSubarray(nums2, 4) << "\n"; // 2

    return 0;
}

