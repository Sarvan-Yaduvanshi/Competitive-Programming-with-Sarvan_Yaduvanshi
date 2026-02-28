/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Sliding Window + Two Pointers on Sorted Array (Value Space)
 *  Level   : Medium → Hard
 * ============================================================================
 *
 *  ▶ DIFFERENCE FROM NORMAL SLIDING WINDOW:
 *  ────────────────────────────────────────
 *  Normal window: contiguous subarray [l..r] in original order.
 *  THIS pattern: SORT the array first, then two pointer on SORTED array.
 *  Not tracking contiguous subarrays — tracking pairs/groups under constraint.
 *
 *  ▶ WHEN TO USE:
 *  ──────────────
 *  ✅ "Pair/group elements under a limit" (sum, diff, product)
 *  ✅ "Longest subsequence under constraint" (after sorting)
 *  ✅ "Maximize covered elements within budget"
 *  ✅ "Sliding over VALUE SPACE" (not index space)
 *
 *  PROBLEMS:
 *  LC 2294 — Partition Array Such That Max Diff Is K (sort + greedy window)
 *            https://leetcode.com/problems/partition-array-such-that-maximum-difference-is-k/
 *  LC 2779 — Max Beauty of Array After Operations (sort + two pointer on values)
 *            https://leetcode.com/problems/maximum-beauty-of-an-array-after-applying-operation/
 *  LC 1838 — Frequency of Most Frequent Element (sort + prefix + window)
 *            https://leetcode.com/problems/frequency-of-the-most-frequent-element/
 *  LC 2968 — Apply Operations to Maximize Frequency Score (sort + BS + window)
 *            https://leetcode.com/problems/apply-operations-to-maximize-frequency-score/
 *  LC 1498 — Number of Subsequences That Satisfy Sum (sort + 2ptr + mod pow)
 *            https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/
 *  LC 881  — Boats to Save People (sort + 2ptr pairing)
 *            https://leetcode.com/problems/boats-to-save-people/
 *  CF 1462D — Add to Neighbour and Remove (greedy merge, 1400)
 *            https://codeforces.com/problemset/problem/1462/D
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

// ============================================================================
// LC 1838: Frequency of the Most Frequent Element (Sort + Window)
// ============================================================================
/*
 * Given array and budget K. Can increment any element by 1 (costs 1 per op).
 * Maximize the frequency of any single value.
 *
 * INSIGHT: Sort. For a window [l..r], make all elements equal to nums[r].
 * Cost = nums[r] * windowSize - sum(window).
 * Shrink left if cost > K.
 *
 * Time: O(N log N), Space: O(1)
 */
int maxFrequency(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    ll sum = 0;
    int left = 0, best = 0;

    for (int right = 0; right < n; right++) {
        sum += nums[right];
        // Cost to make all elements in [left..right] equal to nums[right]
        while ((ll)nums[right] * (right - left + 1) - sum > k) {
            sum -= nums[left++];
        }
        best = max(best, right - left + 1);
    }
    return best;
}

// ============================================================================
// LC 2779: Maximum Beauty After Applying Operation
// ============================================================================
/*
 * Each element can change by at most K. Two elements can "match" if their
 * ranges overlap: [nums[i]-k, nums[i]+k] and [nums[j]-k, nums[j]+k].
 * Ranges overlap iff |nums[i] - nums[j]| ≤ 2*K.
 *
 * SORT. Longest window where max - min ≤ 2*K.
 * Two pointer: shrink left while nums[right] - nums[left] > 2*K.
 *
 * Time: O(N log N), Space: O(1)
 */
int maximumBeauty(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    int left = 0, best = 0;

    for (int right = 0; right < (int)nums.size(); right++) {
        while (nums[right] - nums[left] > 2 * k) left++;
        best = max(best, right - left + 1);
    }
    return best;
}

// ============================================================================
// LC 2294: Partition Array Such That Max Diff Is K
// ============================================================================
/*
 * Partition into groups where max-min ≤ K in each group.
 * Sort. Greedily start a new group when nums[i] - groupStart > K.
 * This is a greedy window on sorted values.
 */
int partitionArray(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    int groups = 1, start = nums[0];

    for (int i = 1; i < (int)nums.size(); i++) {
        if (nums[i] - start > k) {
            groups++;
            start = nums[i];
        }
    }
    return groups;
}

// ============================================================================
// Longest Subsequence Under Constraint (Sort + Window)
// ============================================================================
/*
 * General pattern: After sorting, find longest window [l, r] where
 * some constraint on the window is satisfied (difference, sum, budget).
 *
 * This works because sorting lets us reason about the extreme values
 * (min = nums[left], max = nums[right]) and the cost to "equalize".
 */

// Example: Longest subsequence where max - min ≤ K
int longestSubseqDiffK(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    int left = 0, best = 0;
    for (int right = 0; right < (int)nums.size(); right++) {
        while (nums[right] - nums[left] > k) left++;
        best = max(best, right - left + 1);
    }
    return best;
}

// ============================================================================
// Pairing Under Limit (Sort + Two Pointer from Ends)
// ============================================================================
/*
 * Pair smallest with largest. If pair sum ≤ limit → both fit.
 * Otherwise largest goes alone. Classic boats problem.
 */
int minPairs(vector<int>& nums, int limit) {
    sort(nums.begin(), nums.end());
    int left = 0, right = (int)nums.size() - 1, pairs = 0;
    while (left <= right) {
        if (nums[left] + nums[right] <= limit) left++;
        right--;
        pairs++;
    }
    return pairs;
}

// ============================================================================
// LC 1498: Number of Subsequences With Sum ≤ target (Sort + 2Ptr + ModPow)
// ============================================================================
/*
 * Count non-empty subsequences where min + max ≤ target.
 * Sort. For each left (min), find rightmost right where nums[left]+nums[right] ≤ target.
 * Subsequences: pick left, choose any subset of [left+1..right] → 2^(right-left).
 *
 * Time: O(N log N), Space: O(N) for power table
 */
int numSubseq(vector<int>& nums, int target) {
    const int MOD = 1e9 + 7;
    sort(nums.begin(), nums.end());
    int n = nums.size();

    // Precompute powers of 2
    vector<ll> pw(n);
    pw[0] = 1;
    for (int i = 1; i < n; i++) pw[i] = pw[i-1] * 2 % MOD;

    ll count = 0;
    int left = 0, right = n - 1;
    while (left <= right) {
        if (nums[left] + nums[right] <= target) {
            count = (count + pw[right - left]) % MOD;
            left++;
        } else {
            right--;
        }
    }
    return (int)count;
}

int main() {
    // Max frequency
    vector<int> a1 = {1, 2, 4};
    cout << "Max freq (k=5): " << maxFrequency(a1, 5) << "\n"; // 3

    // Max beauty
    vector<int> a2 = {4, 6, 1, 2};
    cout << "Max beauty (k=2): " << maximumBeauty(a2, 2) << "\n"; // 3

    // Partition
    vector<int> a3 = {3, 6, 1, 2, 5};
    cout << "Partitions (k=2): " << partitionArray(a3, 2) << "\n"; // 2

    // Longest subsequence diff ≤ K
    vector<int> a4 = {1, 5, 3, 7, 2};
    cout << "Longest diff≤3: " << longestSubseqDiffK(a4, 3) << "\n"; // 4

    // Number of subsequences
    vector<int> a5 = {3, 5, 6, 7};
    cout << "Subsequences sum≤9: " << numSubseq(a5, 9) << "\n"; // 4

    return 0;
}

