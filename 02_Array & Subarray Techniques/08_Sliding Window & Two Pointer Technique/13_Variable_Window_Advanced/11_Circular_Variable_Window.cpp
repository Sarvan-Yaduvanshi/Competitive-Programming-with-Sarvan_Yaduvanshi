/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Circular Variable Window
 *  Level   : Medium → Hard
 * ============================================================================
 *
 *  ▶ CIRCULAR + VARIABLE WINDOW:
 *  ─────────────────────────────
 *  When the array is circular AND the window size is variable, use:
 *
 *  1. Double Array Trick + Variable Window:
 *     Concatenate arr with itself (size 2N). Run variable window on doubled.
 *     But restrict: window length ≤ N (can't wrap more than once).
 *
 *  2. Complement Trick:
 *     Circular max subarray = totalSum - min non-circular subarray.
 *     Already covered for fixed/Kadane. Extend to variable constraints.
 *
 *  3. Two Cases Split:
 *     Case A: subarray doesn't wrap → standard variable window
 *     Case B: subarray wraps → complement is a normal subarray
 *     Answer = max/min(Case A, Case B)
 *
 *  PROBLEMS:
 *  LC 918  — Maximum Sum Circular Subarray (Kadane + complement)
 *            https://leetcode.com/problems/maximum-sum-circular-subarray/
 *  LC 1658 — Minimum Operations to Reduce X to Zero (complement window)
 *            https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/
 *  LC 2134 — Min Swaps to Group 1s II (circular, fixed but variable-like)
 *            https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/
 *  CF 1030C — Vasya and Golden Ticket (circular substring, 1300)
 *            https://codeforces.com/problemset/problem/1030/C
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <numeric>
using namespace std;
using ll = long long;

// ============================================================================
// LC 1658: Min Operations to Reduce X to Zero — Complement Window
// ============================================================================
/*
 * Remove from left and/or right to reduce X to 0.
 * Equivalent: find LONGEST middle subarray with sum = totalSum - X.
 * This converts a circular-like problem into a standard variable window!
 *
 * Time: O(N), Space: O(1)
 */
int minOperations(vector<int>& nums, int x) {
    int n = nums.size();
    int totalSum = accumulate(nums.begin(), nums.end(), 0);
    int target = totalSum - x;
    if (target < 0) return -1;
    if (target == 0) return n;

    int left = 0, sum = 0, maxLen = -1;
    for (int right = 0; right < n; right++) {
        sum += nums[right];
        while (sum > target) sum -= nums[left++];
        if (sum == target) maxLen = max(maxLen, right - left + 1);
    }
    return maxLen == -1 ? -1 : n - maxLen;
}

// ============================================================================
// Circular Variable Window — Double Array + Length Constraint
// ============================================================================
/*
 * General pattern: Find longest/shortest circular subarray satisfying property.
 * Double the array: arr + arr. Run variable window on doubled array.
 * Constraint: window length ≤ N (can't use same element twice).
 */

// Example: Longest circular subarray with sum ≤ K
int longestCircularSubarraySumLeK(vector<int>& arr, int k) {
    int n = arr.size();
    // Double the array
    vector<int> doubled(2 * n);
    for (int i = 0; i < 2 * n; i++) doubled[i] = arr[i % n];

    int left = 0, best = 0;
    ll sum = 0;
    for (int right = 0; right < 2 * n; right++) {
        sum += doubled[right];
        while (sum > k || right - left + 1 > n) // Window ≤ N!
            sum -= doubled[left++];
        best = max(best, right - left + 1);
    }
    return best;
}

// ============================================================================
// Circular Subarray Maximum Sum — Kadane + Complement
// ============================================================================
/*
 * Two cases:
 * Case 1: Max subarray doesn't wrap → standard Kadane
 * Case 2: Max subarray wraps → totalSum - minSubarray
 * Answer = max(Case 1, Case 2)
 * Edge: if all negative, Case 2 gives 0 → use Case 1.
 */
int maxSubarraySumCircular(vector<int>& nums) {
    int totalSum = 0;
    int maxSum = INT_MIN, curMax = 0;
    int minSum = INT_MAX, curMin = 0;

    for (int x : nums) {
        totalSum += x;
        curMax = max(curMax + x, x); maxSum = max(maxSum, curMax);
        curMin = min(curMin + x, x); minSum = min(minSum, curMin);
    }
    if (maxSum < 0) return maxSum; // All negative
    return max(maxSum, totalSum - minSum);
}

// ============================================================================
// Circular Longest Substring Without Repeating Characters
// ============================================================================
/*
 * Double the string + constraint length ≤ N.
 * Standard "no repeating" window on doubled string.
 */
int circularLongestNoRepeat(string s) {
    int n = s.size();
    string doubled = s + s;
    int freq[128] = {};
    int left = 0, best = 0;

    for (int right = 0; right < 2 * n; right++) {
        freq[(int)doubled[right]]++;
        while (freq[(int)doubled[right]] > 1 || right - left + 1 > n) {
            freq[(int)doubled[left]]--;
            left++;
        }
        best = max(best, right - left + 1);
    }
    return best;
}

int main() {
    // Min operations to reduce X
    vector<int> a1 = {1, 1, 4, 2, 3};
    cout << "Min ops (x=5): " << minOperations(a1, 5) << "\n"; // 2

    // Circular max sum
    vector<int> a2 = {5, -3, 5};
    cout << "Circular max sum: " << maxSubarraySumCircular(a2) << "\n"; // 10

    // Circular subarray sum ≤ K
    vector<int> a3 = {3, 1, 2, 4};
    cout << "Circular longest sum≤6: " << longestCircularSubarraySumLeK(a3, 6) << "\n"; // 3

    // Circular no repeating
    cout << "Circular no repeat 'abca': " << circularLongestNoRepeat("abca") << "\n"; // 4

    return 0;
}

