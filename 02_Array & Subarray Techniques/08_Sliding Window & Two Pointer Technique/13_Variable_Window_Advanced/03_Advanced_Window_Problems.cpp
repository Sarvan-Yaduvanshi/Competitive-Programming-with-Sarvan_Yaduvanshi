/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Advanced Variable Window Problems (Expert Level)
 *  Level   : Hard → Expert
 * ============================================================================
 *
 *  LC 862  — Shortest Subarray with Sum at Least K (with negatives!)
 *            https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/
 *
 *  LC 795  — Number of Subarrays with Bounded Maximum
 *            https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/
 *
 *  LC 2302 — Count Subarrays With Score Less Than K
 *            https://leetcode.com/problems/count-subarrays-with-score-less-than-k/
 *
 *  LC 2009 — Minimum Number of Operations to Make Array Continuous
 *            https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/
 *
 *  LC 2516 — Take K of Each Character From Left and Right
 *            https://leetcode.com/problems/take-k-of-each-character-from-left-and-right/
 *
 *  LC 1574 — Shortest Subarray to be Removed to Make Array Sorted
 *            https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <climits>
using namespace std;
using ll = long long;

// ============================================================================
// LC 862: Shortest Subarray with Sum at Least K (HARD — negatives allowed!)
// ============================================================================
/*
 * CAN'T use simple two-pointer because of negatives!
 * Use PREFIX SUM + MONOTONE DEQUE.
 *
 * Key insight:
 * - We want shortest [i, j] where prefix[j+1] - prefix[i] >= K
 * - Maintain a deque of indices where prefix values are increasing.
 * - For each j, pop from front while prefix[j] - prefix[front] >= K (try shorter).
 * - Pop from back while prefix[back] >= prefix[j] (back is never useful).
 *
 * Time: O(N), Space: O(N)
 */
int shortestSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    vector<ll> prefix(n + 1, 0);
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + nums[i];

    deque<int> dq; // Indices into prefix array, monotone increasing
    int best = INT_MAX;

    for (int j = 0; j <= n; j++) {
        // Check if we found a valid subarray (try to minimize)
        while (!dq.empty() && prefix[j] - prefix[dq.front()] >= k) {
            best = min(best, j - dq.front());
            dq.pop_front();
        }
        // Maintain monotone increasing deque
        while (!dq.empty() && prefix[dq.back()] >= prefix[j])
            dq.pop_back();
        dq.push_back(j);
    }
    return best == INT_MAX ? -1 : best;
}

// ============================================================================
// LC 795: Number of Subarrays with Bounded Maximum (L ≤ max ≤ R)
// ============================================================================
/*
 * TRICK: count(max ≤ R) - count(max ≤ L-1)
 *
 * count(max ≤ X) = number of subarrays where all elements ≤ X
 * For each right, find the last position where element > X → left boundary
 * count += (right - lastBad)
 */
int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
    auto countAtMost = [&](int bound) -> int {
        int count = 0, cur = 0;
        for (int x : nums) {
            if (x <= bound) cur++;
            else cur = 0;
            count += cur;
        }
        return count;
    };
    return countAtMost(right) - countAtMost(left - 1);
}

// ============================================================================
// LC 2009: Min Operations to Make Array Continuous
// ============================================================================
/*
 * Final array must be sorted with no duplicates, values form a contiguous range.
 * So we need to find the LONGEST subsequence that can form a valid range [x, x+n-1].
 *
 * Sort + deduplicate, then sliding window: for each right, find leftmost where
 * arr[right] - arr[left] < n.
 *
 * Answer = n - maxValid
 */
int minOperations(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    int m = nums.size();
    int best = 0, left = 0;

    for (int right = 0; right < m; right++) {
        while (nums[right] - nums[left] >= n)
            left++;
        best = max(best, right - left + 1);
    }
    return n - best;
}

// ============================================================================
// LC 2516: Take K of Each Character From Left and Right
// ============================================================================
/*
 * Remove chars from left and right to have at least K of each a, b, c.
 * Reverse: find LONGEST middle substring we can keep such that the
 * remaining (left + right) has at least K of each.
 *
 * Total freq of each char minus the middle's freq must be >= K.
 * So middle can have at most (total[c] - K) of each char c.
 */
int takeCharacters(string s, int k) {
    int total[3] = {};
    for (char c : s) total[c - 'a']++;

    // Check if possible
    for (int i = 0; i < 3; i++)
        if (total[i] < k) return -1;

    int n = s.size();
    int maxMiddle = 0;
    int freq[3] = {};
    int left = 0;

    for (int right = 0; right < n; right++) {
        freq[s[right] - 'a']++;

        // Middle has too many of some char → shrink
        while (freq[0] > total[0] - k || freq[1] > total[1] - k || freq[2] > total[2] - k) {
            freq[s[left] - 'a']--;
            left++;
        }
        maxMiddle = max(maxMiddle, right - left + 1);
    }
    return n - maxMiddle;
}

// ============================================================================
// LC 2302: Count Subarrays With Score Less Than K
// ============================================================================
/*
 * Score of subarray = sum * length. Count subarrays with score < K.
 * Variable window: expand right, shrink left when sum * len >= K.
 * count += (right - left + 1) for each valid right.
 */
long long countSubarrays(vector<int>& nums, long long k) {
    int left = 0;
    long long sum = 0, count = 0;

    for (int right = 0; right < (int)nums.size(); right++) {
        sum += nums[right];
        while (sum * (right - left + 1) >= k) {
            sum -= nums[left];
            left++;
        }
        count += (right - left + 1);
    }
    return count;
}

int main() {
    // LC 862: Shortest Subarray Sum ≥ K
    vector<int> nums1 = {2, -1, 2};
    cout << "Shortest subarray sum≥3: " << shortestSubarray(nums1, 3) << "\n"; // 3

    // LC 795: Bounded Maximum
    vector<int> nums2 = {2, 1, 4, 3};
    cout << "Bounded [2,3]: " << numSubarrayBoundedMax(nums2, 2, 3) << "\n"; // 3

    // LC 2516: Take K chars
    cout << "Take K (aabaaaacaabc, K=2): " << takeCharacters("aabaaaacaabc", 2) << "\n"; // 8

    // LC 2302: Score < K
    vector<int> nums3 = {2, 1, 4, 3, 5};
    cout << "Score < 10: " << countSubarrays(nums3, 10) << "\n"; // 6

    return 0;
}

