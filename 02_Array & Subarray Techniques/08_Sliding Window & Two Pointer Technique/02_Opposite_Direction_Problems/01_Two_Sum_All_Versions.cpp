/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Two Sum — All Versions
 *  Level   : Easy → Medium
 * ============================================================================
 *
 *  VERSION 1: Two Sum (Unsorted) — LC 1
 *             Use HashMap → O(N) time, O(N) space
 *
 *  VERSION 2: Two Sum II (Sorted) — LC 167
 *             Use Two Pointer → O(N) time, O(1) space
 *
 *  VERSION 3: Two Sum (BST) — LC 653
 *             Inorder + Two Pointer or Set
 *
 *  VERSION 4: Two Sum (Data Structure Design) — LC 170
 *             Add/Find operations with HashMap
 *
 *  VERSION 5: Two Sum (Less Than) — Count pairs with sum < target
 *             Sort + Two Pointer → count += (right - left)
 *
 *  PROBLEMS:
 *   LC 1    — https://leetcode.com/problems/two-sum/
 *   LC 167  — https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
 *   LC 653  — https://leetcode.com/problems/two-sum-iv-input-is-a-bst/
 *   LC 170  — https://leetcode.com/problems/two-sum-iii-data-structure-design/
 *   LC 1099 — https://leetcode.com/problems/two-sum-less-than-k/
 *   CSES 1640 — https://cses.fi/problemset/task/1640
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

// VERSION 1: Two Sum (Unsorted) — HashMap
// Time: O(N), Space: O(N)
vector<int> twoSum_HashMap(vector<int>& nums, int target) {
    unordered_map<int, int> mp;
    for (int i = 0; i < (int)nums.size(); i++) {
        int complement = target - nums[i];
        if (mp.count(complement)) {
            return {mp[complement], i};
        }
        mp[nums[i]] = i;
    }
    return {};
}

// VERSION 2: Two Sum (Sorted) — Two Pointer
// Time: O(N), Space: O(1)
vector<int> twoSum_TwoPointer(vector<int>& nums, int target) {
    int left = 0, right = (int)nums.size() - 1;
    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum == target) return {left + 1, right + 1}; // 1-indexed
        else if (sum < target) left++;
        else right--;
    }
    return {};
}

// VERSION 3: Count pairs with sum < target
// Sort + Two Pointer — O(N log N)
int countPairsLessThan(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int left = 0, right = (int)nums.size() - 1;
    int count = 0;

    while (left < right) {
        if (nums[left] + nums[right] < target) {
            count += (right - left);  // ALL pairs (left, left+1..right) work
            left++;
        } else {
            right--;
        }
    }
    return count;
}

// VERSION 4: Two Sum Less Than K (find max sum < K)
// LC 1099 — O(N log N)
int twoSumLessThanK(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    int left = 0, right = (int)nums.size() - 1;
    int best = -1;

    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum < k) {
            best = max(best, sum);
            left++;
        } else {
            right--;
        }
    }
    return best;
}

int main() {
    // Version 1: HashMap
    vector<int> nums1 = {2, 7, 11, 15};
    auto res1 = twoSum_HashMap(nums1, 9);
    cout << "HashMap: [" << res1[0] << ", " << res1[1] << "]\n";

    // Version 2: Two Pointer (sorted)
    auto res2 = twoSum_TwoPointer(nums1, 9);
    cout << "Two Pointer: [" << res2[0] << ", " << res2[1] << "]\n";

    // Version 3: Count pairs < target
    vector<int> nums3 = {1, 3, 5, 7, 9};
    cout << "Pairs with sum < 10: " << countPairsLessThan(nums3, 10) << "\n";

    // Version 4: Max sum < K
    vector<int> nums4 = {34, 23, 1, 24, 75, 33, 54, 8};
    cout << "Max sum < 60: " << twoSumLessThanK(nums4, 60) << "\n";

    return 0;
}

