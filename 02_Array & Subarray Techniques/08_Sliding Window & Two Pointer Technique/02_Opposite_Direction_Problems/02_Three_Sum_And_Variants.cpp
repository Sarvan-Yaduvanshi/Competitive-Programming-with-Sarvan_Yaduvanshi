/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : 3Sum and All Variants
 *  Level   : Medium
 * ============================================================================
 *
 *  PROBLEMS COVERED:
 *   LC 15   — 3Sum (find all triplets summing to 0)
 *             https://leetcode.com/problems/3sum/
 *   LC 16   — 3Sum Closest (find triplet with sum closest to target)
 *             https://leetcode.com/problems/3sum-closest/
 *   LC 259  — 3Sum Smaller (count triplets with sum < target)
 *             https://leetcode.com/problems/3sum-smaller/
 *   LC 923  — 3Sum With Multiplicity (count with repeats, mod 1e9+7)
 *             https://leetcode.com/problems/3sum-with-multiplicity/
 *   CSES 1641 — Sum of Three Values
 *             https://cses.fi/problemset/task/1641
 *
 *  CORE IDEA:
 *  ──────────
 *  Sort the array. Fix one element (i), then use two pointer on remaining.
 *  Skip duplicates to avoid duplicate triplets.
 *  Time: O(N²), Space: O(1) extra
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// ============================================================================
// LC 15: 3Sum — Find all unique triplets that sum to zero
// ============================================================================
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    int n = nums.size();

    for (int i = 0; i < n - 2; i++) {
        // OPTIMIZATION: if smallest > 0, no more solutions
        if (nums[i] > 0) break;

        // Skip duplicate first element
        if (i > 0 && nums[i] == nums[i - 1]) continue;

        int left = i + 1, right = n - 1;
        int target = -nums[i];

        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum == target) {
                result.push_back({nums[i], nums[left], nums[right]});
                // Skip duplicates for second and third elements
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                left++;
                right--;
            }
            else if (sum < target) left++;
            else right--;
        }
    }
    return result;
}

// ============================================================================
// LC 16: 3Sum Closest — Find triplet with sum closest to target
// ============================================================================
int threeSumClosest(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int closestSum = nums[0] + nums[1] + nums[2];

    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;

        int left = i + 1, right = n - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];

            if (abs(sum - target) < abs(closestSum - target)) {
                closestSum = sum;
            }

            if (sum == target) return target;  // Can't get closer than 0
            else if (sum < target) left++;
            else right--;
        }
    }
    return closestSum;
}

// ============================================================================
// LC 259: 3Sum Smaller — Count triplets with sum < target
// ============================================================================
/*
 * KEY INSIGHT: When nums[i] + nums[left] + nums[right] < target,
 * ALL pairs (i, left, left+1..right) also satisfy the condition!
 * So count += (right - left)
 */
int threeSumSmaller(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int count = 0;

    for (int i = 0; i < n - 2; i++) {
        int left = i + 1, right = n - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum < target) {
                count += (right - left);  // All pairs (left, left+1..right) work
                left++;
            } else {
                right--;
            }
        }
    }
    return count;
}

// ============================================================================
// LC 923: 3Sum With Multiplicity — Count triplets with sum = target (mod 1e9+7)
// ============================================================================
/*
 * Array may have duplicates. Count ALL (i,j,k) with i<j<k, sum = target.
 * Use two pointer + careful counting for equal elements.
 */
int threeSumMulti(vector<int>& arr, int target) {
    const int MOD = 1e9 + 7;
    sort(arr.begin(), arr.end());
    long long count = 0;
    int n = arr.size();

    for (int i = 0; i < n - 2; i++) {
        int left = i + 1, right = n - 1;
        int need = target - arr[i];

        while (left < right) {
            int sum = arr[left] + arr[right];
            if (sum < need) { left++; continue; }
            if (sum > need) { right--; continue; }

            // sum == need
            if (arr[left] == arr[right]) {
                // All elements from left to right are equal
                long long cnt = right - left + 1;
                count = (count + cnt * (cnt - 1) / 2) % MOD;
                break;
            } else {
                // Count duplicates of arr[left] and arr[right]
                int leftCount = 1, rightCount = 1;
                while (left + leftCount < right && arr[left + leftCount] == arr[left])
                    leftCount++;
                while (right - rightCount > left && arr[right - rightCount] == arr[right])
                    rightCount++;
                count = (count + (long long)leftCount * rightCount) % MOD;
                left += leftCount;
                right -= rightCount;
            }
        }
    }
    return (int)count;
}

int main() {
    // 3Sum
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    auto res = threeSum(nums);
    cout << "3Sum:\n";
    for (auto& t : res)
        cout << "  [" << t[0] << ", " << t[1] << ", " << t[2] << "]\n";

    // 3Sum Closest
    vector<int> nums2 = {-1, 2, 1, -4};
    cout << "3Sum Closest to 1: " << threeSumClosest(nums2, 1) << "\n"; // 2

    // 3Sum Smaller
    vector<int> nums3 = {-2, 0, 1, 3};
    cout << "3Sum Smaller than 2: " << threeSumSmaller(nums3, 2) << "\n"; // 2

    return 0;
}

