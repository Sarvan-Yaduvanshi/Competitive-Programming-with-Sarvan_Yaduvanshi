/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Kth Smallest Pair Distance (LC 719) — BS + Two Pointer
 *  Level   : Hard
 *  Link    : https://leetcode.com/problems/find-k-th-smallest-pair-distance/
 * ============================================================================
 *
 *  PROBLEM: Given array, find kth smallest |nums[i] - nums[j]| (i < j).
 *
 *  APPROACH: Binary Search on Answer + Two Pointer Count
 *  ─────────────────────────────────────────────────────
 *  1. Sort the array.
 *  2. Binary search on distance d ∈ [0, max-min].
 *  3. For each d, count pairs with difference ≤ d using two pointer.
 *  4. Find smallest d where count ≥ k.
 *
 *  Count pairs with diff ≤ d:
 *  For each right, find smallest left where nums[right] - nums[left] ≤ d.
 *  Pairs = right - left.
 *
 *  Time: O(N log N + N log(max-min)), Space: O(1)
 *
 *  ALSO COVERS:
 *  LC 2824 — Count Pairs Whose Sum Is Less Than Target
 *            https://leetcode.com/problems/count-pairs-whose-sum-is-less-than-target/
 *  LC 532  — K-diff Pairs in an Array
 *            https://leetcode.com/problems/k-diff-pairs-in-an-array/
 *  LC 1679 — Max Number of K-Sum Pairs
 *            https://leetcode.com/problems/max-number-of-k-sum-pairs/
 *  LC 1855 — Max Distance Between a Pair of Values
 *            https://leetcode.com/problems/maximum-distance-between-a-pair-of-values/
 *  LC 658  — Find K Closest Elements
 *            https://leetcode.com/problems/find-k-closest-elements/
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Count pairs with difference ≤ d (array must be sorted)
int countPairsWithDiffAtMost(vector<int>& nums, int d) {
    int count = 0, left = 0;
    for (int right = 1; right < (int)nums.size(); right++) {
        while (nums[right] - nums[left] > d) left++;
        count += (right - left);
    }
    return count;
}

// LC 719: Kth Smallest Pair Distance
int smallestDistancePair(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    int lo = 0, hi = nums.back() - nums.front();

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (countPairsWithDiffAtMost(nums, mid) >= k)
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

// LC 2824: Count Pairs Whose Sum < Target
int countPairs(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int left = 0, right = (int)nums.size() - 1, count = 0;
    while (left < right) {
        if (nums[left] + nums[right] < target) {
            count += (right - left);
            left++;
        } else {
            right--;
        }
    }
    return count;
}

// LC 1679: Max Number of K-Sum Pairs
int maxOperations(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    int left = 0, right = (int)nums.size() - 1, ops = 0;
    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum == k) { ops++; left++; right--; }
        else if (sum < k) left++;
        else right--;
    }
    return ops;
}

// LC 1855: Maximum Distance Between a Pair of Values
int maxDistance(vector<int>& nums1, vector<int>& nums2) {
    int i = 0, j = 0, maxDist = 0;
    while (i < (int)nums1.size() && j < (int)nums2.size()) {
        if (nums1[i] > nums2[j]) i++;
        else {
            maxDist = max(maxDist, j - i);
            j++;
        }
    }
    return maxDist;
}

int main() {
    // Kth Smallest Pair Distance
    vector<int> nums = {1, 3, 1};
    cout << "Kth Smallest (k=1): " << smallestDistancePair(nums, 1) << "\n"; // 0

    // Count Pairs < target
    vector<int> nums2 = {-1, 1, 2, 3, 1};
    cout << "Pairs with sum < 2: " << countPairs(nums2, 2) << "\n"; // 3

    // Max K-Sum Pairs
    vector<int> nums3 = {1, 2, 3, 4};
    cout << "Max K-Sum ops (k=5): " << maxOperations(nums3, 5) << "\n"; // 2

    return 0;
}

