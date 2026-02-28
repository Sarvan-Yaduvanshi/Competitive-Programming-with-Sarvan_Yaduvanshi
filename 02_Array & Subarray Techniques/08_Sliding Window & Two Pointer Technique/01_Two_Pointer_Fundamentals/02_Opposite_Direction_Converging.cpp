/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Opposite Direction (Converging) Two Pointers
 *  Level   : Beginner
 * ============================================================================
 *
 *  TABLE OF CONTENTS:
 *  ──────────────────
 *  1. What is Opposite Direction Two Pointer?
 *  2. The Core Template
 *  3. Why Correctness is Guaranteed (Proof Sketch)
 *  4. Pattern: Pair Finding (Two Sum Sorted)
 *  5. Pattern: Container Width Optimization
 *  6. Pattern: Palindrome Verification
 *  7. Pattern: Squeeze / Narrow Search Space
 *
 * ============================================================================
 *
 *  ▶ WHAT IS OPPOSITE DIRECTION TWO POINTER?
 *  ──────────────────────────────────────────
 *  Two pointers start at OPPOSITE ENDS of the array and move TOWARDS
 *  each other. At each step, we decide which pointer to move based on
 *  some condition.
 *
 *  INVARIANT: We never miss a valid pair because:
 *  - If we move left++, all pairs (left, right'), right' < right are
 *    guaranteed to be suboptimal (smaller sum / smaller area / etc.)
 *  - If we move right--, all pairs (left', right), left' > left are
 *    guaranteed to be suboptimal
 *
 *  ▶ CORE TEMPLATE:
 *  ────────────────
 *
 *  int left = 0, right = N - 1;
 *  while (left < right) {
 *      // compute something using arr[left] and arr[right]
 *      if (condition_to_advance_left) {
 *          left++;
 *      } else if (condition_to_retreat_right) {
 *          right--;
 *      } else {
 *          // found answer / process pair
 *          left++; right--; // or just one of them
 *      }
 *  }
 *
 *  ▶ WHEN TO USE:
 *  ──────────────
 *  ✅ Array is SORTED
 *  ✅ Finding pair with target sum/difference
 *  ✅ Maximizing/minimizing expression involving two endpoints
 *  ✅ Checking symmetry (palindrome)
 *  ✅ Squeezing search space from both ends
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================================
// PATTERN 1: Two Sum on Sorted Array
// ============================================================================
/*
 * LC 167: Two Sum II — Input Array Is Sorted
 * https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
 *
 * Given sorted array, find two numbers that add up to target.
 * Return 1-indexed positions.
 */
vector<int> twoSum(vector<int>& nums, int target) {
    int left = 0, right = (int)nums.size() - 1;

    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum == target) {
            return {left + 1, right + 1};   // 1-indexed
        }
        else if (sum < target) left++;
        else right--;
    }
    return {};
}

// ============================================================================
// PATTERN 2: Container With Most Water
// ============================================================================
/*
 * LC 11: Container With Most Water
 * https://leetcode.com/problems/container-with-most-water/
 *
 * Given heights, find two lines that form container holding most water.
 * Area = min(h[left], h[right]) * (right - left)
 *
 * KEY INSIGHT: Always move the pointer with SMALLER height.
 * Moving the taller one can only decrease width without guaranteed height gain.
 */
int maxArea(vector<int>& height) {
    int left = 0, right = (int)height.size() - 1;
    int best = 0;

    while (left < right) {
        int w = right - left;
        int h = min(height[left], height[right]);
        best = max(best, w * h);

        if (height[left] < height[right])
            left++;     // Move the shorter one
        else
            right--;
    }
    return best;
}

// ============================================================================
// PATTERN 3: Squares of a Sorted Array
// ============================================================================
/*
 * LC 977: Squares of a Sorted Array
 * https://leetcode.com/problems/squares-of-a-sorted-array/
 *
 * Given sorted array (may have negatives), return squares in sorted order.
 *
 * KEY INSIGHT: Largest squares are at the ends (most negative or most positive).
 * Fill result from the back, compare |arr[left]| vs |arr[right]|.
 */
vector<int> sortedSquares(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n);
    int left = 0, right = n - 1;
    int pos = n - 1;  // Fill from the back

    while (left <= right) {
        int lsq = nums[left] * nums[left];
        int rsq = nums[right] * nums[right];

        if (lsq > rsq) {
            result[pos--] = lsq;
            left++;
        } else {
            result[pos--] = rsq;
            right--;
        }
    }
    return result;
}

// ============================================================================
// PATTERN 4: Reverse String
// ============================================================================
/*
 * LC 344: Reverse String
 * https://leetcode.com/problems/reverse-string/
 *
 * The simplest converging two pointer — swap from both ends.
 */
void reverseString(vector<char>& s) {
    int left = 0, right = (int)s.size() - 1;
    while (left < right) {
        swap(s[left], s[right]);
        left++;
        right--;
    }
}

int main() {
    // Two Sum
    vector<int> arr = {2, 7, 11, 15};
    auto res = twoSum(arr, 9);
    cout << "Two Sum: [" << res[0] << ", " << res[1] << "]\n";

    // Container With Most Water
    vector<int> heights = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << "Max Area: " << maxArea(heights) << "\n";

    // Sorted Squares
    vector<int> nums = {-4, -1, 0, 3, 10};
    auto sq = sortedSquares(nums);
    cout << "Sorted Squares: ";
    for (int x : sq) cout << x << " ";
    cout << "\n";

    return 0;
}

