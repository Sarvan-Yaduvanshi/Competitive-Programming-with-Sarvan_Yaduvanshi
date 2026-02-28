/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : All Two Pointer Templates Reference (6 Core Templates)
 *  Level   : Beginner → GM
 * ============================================================================
 *
 *  ALL 6 CORE TEMPLATES IN ONE FILE:
 *  ─────────────────────────────────
 *  Template 1: Opposite Direction (Converging)
 *  Template 2: Same Direction (Reader-Writer / Compaction)
 *  Template 3: Merge Two Sorted Sequences
 *  Template 4: Fast & Slow (Floyd's Cycle)
 *  Template 5: N-Sum (3Sum, 4Sum, KSum)
 *  Template 6: Binary Search + Two Pointer (Count Pairs)
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

// =====================================================================
// TEMPLATE 1: OPPOSITE DIRECTION (CONVERGING)
// =====================================================================
/*
 * USE: Sorted array pair finding, palindrome, container water
 * TIME: O(N)   SPACE: O(1)
 *
 * PROBLEMS:
 *   LC 167 (Two Sum II), LC 11 (Container Water), LC 42 (Trapping Rain),
 *   LC 977 (Sorted Squares), LC 344 (Reverse String), LC 125 (Valid Palindrome)
 */
/*
void template_converging(vector<int>& arr, int target) {
    int left = 0, right = (int)arr.size() - 1;
    while (left < right) {
        int val = arr[left] + arr[right]; // or some expression
        if (val == target) {
            // found pair
            left++; right--;
        } else if (val < target) {
            left++;
        } else {
            right--;
        }
    }
}
*/

// =====================================================================
// TEMPLATE 2: SAME DIRECTION (READER-WRITER)
// =====================================================================
/*
 * USE: Remove duplicates, remove element, move zeroes, compaction
 * TIME: O(N)   SPACE: O(1)
 *
 * PROBLEMS:
 *   LC 26 (Remove Duplicates), LC 27 (Remove Element), LC 283 (Move Zeroes),
 *   LC 80 (Remove Duplicates II), LC 905 (Sort by Parity)
 */
/*
int template_reader_writer(vector<int>& arr) {
    int writer = 0;
    for (int reader = 0; reader < (int)arr.size(); reader++) {
        if (arr[reader] satisfies some condition) {
            arr[writer] = arr[reader];
            writer++;
        }
    }
    return writer; // new length
}
*/

// =====================================================================
// TEMPLATE 3: MERGE TWO SORTED SEQUENCES
// =====================================================================
/*
 * USE: Merge sorted arrays, intersection of sorted arrays
 * TIME: O(N + M)   SPACE: O(N + M) for result
 *
 * PROBLEMS:
 *   LC 88 (Merge Sorted Array), LC 349 (Intersection), LC 350 (Intersection II),
 *   LC 986 (Interval List Intersections)
 */
/*
vector<int> template_merge(vector<int>& A, vector<int>& B) {
    vector<int> result;
    int i = 0, j = 0;
    while (i < A.size() && j < B.size()) {
        if (A[i] <= B[j]) result.push_back(A[i++]);
        else result.push_back(B[j++]);
    }
    while (i < A.size()) result.push_back(A[i++]);
    while (j < B.size()) result.push_back(B[j++]);
    return result;
}
*/

// =====================================================================
// TEMPLATE 4: FAST & SLOW (FLOYD'S CYCLE DETECTION)
// =====================================================================
/*
 * USE: Cycle detection, find middle, find duplicate in [1,n]
 * TIME: O(N)   SPACE: O(1)
 *
 * PROBLEMS:
 *   LC 141 (Cycle Detection), LC 142 (Cycle Start), LC 287 (Find Duplicate),
 *   LC 202 (Happy Number), LC 876 (Middle of LL)
 */
/*
// Phase 1: Detect meeting point
int slow = start, fast = start;
do {
    slow = next(slow);       // 1 step
    fast = next(next(fast));  // 2 steps
} while (slow != fast);

// Phase 2: Find cycle entry (if needed)
slow = start;
while (slow != fast) {
    slow = next(slow);
    fast = next(fast);
}
// slow == fast == cycle entry
*/

// =====================================================================
// TEMPLATE 5: N-SUM (3Sum, 4Sum, General KSum)
// =====================================================================
/*
 * USE: Find all k-tuples summing to target
 * TIME: O(N^(K-1))   SPACE: O(1) extra (excluding result)
 *
 * KEY: Sort first, then fix (K-2) elements and use 2-pointer for last 2.
 * Skip duplicates to avoid duplicate tuples.
 *
 * PROBLEMS:
 *   LC 15 (3Sum), LC 16 (3Sum Closest), LC 18 (4Sum), LC 259 (3Sum Smaller),
 *   LC 923 (3Sum Multiplicity), CSES 1640-1642
 */
vector<vector<int>> threeSum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    int n = nums.size();

    for (int i = 0; i < n - 2; i++) {
        // Skip duplicate for first element
        if (i > 0 && nums[i] == nums[i - 1]) continue;

        int left = i + 1, right = n - 1;
        int need = target - nums[i];

        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum == need) {
                result.push_back({nums[i], nums[left], nums[right]});
                // Skip duplicates
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                left++;
                right--;
            }
            else if (sum < need) left++;
            else right--;
        }
    }
    return result;
}

vector<vector<int>> fourSum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    int n = nums.size();

    for (int i = 0; i < n - 3; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;

        for (int j = i + 1; j < n - 2; j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;

            int left = j + 1, right = n - 1;
            long long need = (long long)target - nums[i] - nums[j];

            while (left < right) {
                long long sum = (long long)nums[left] + nums[right];
                if (sum == need) {
                    result.push_back({nums[i], nums[j], nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++; right--;
                }
                else if (sum < need) left++;
                else right--;
            }
        }
    }
    return result;
}

// =====================================================================
// TEMPLATE 6: BINARY SEARCH + TWO POINTER (COUNT PAIRS)
// =====================================================================
/*
 * USE: Count pairs with sum/diff condition, Kth smallest pair distance
 * TIME: O(N log N) or O(N log N * log MAX)
 *
 * PROBLEMS:
 *   LC 719 (Kth Smallest Pair Distance), LC 2824 (Count Pairs < Target),
 *   LC 532 (K-diff Pairs), LC 881 (Boats to Save People)
 */
/*
// Count pairs (i, j) where arr[i] + arr[j] <= target
// Sort first, then for each right, find how many left values work
int countPairsLessEqual(vector<int>& arr, int target) {
    sort(arr.begin(), arr.end());
    int count = 0;
    int left = 0, right = (int)arr.size() - 1;
    while (left < right) {
        if (arr[left] + arr[right] <= target) {
            count += (right - left);  // All pairs (left, left+1..right) work
            left++;
        } else {
            right--;
        }
    }
    return count;
}
*/

// =====================================================================
// 🏆 GM TIPS & PATTERN RECOGNITION
// =====================================================================
/*
 * HOW TO IDENTIFY WHICH TEMPLATE TO USE:
 *
 * Q: Is the array sorted (or can you sort it)?
 *    YES → Consider Template 1 (Converging) or Template 5 (N-Sum)
 *
 * Q: Do you need to modify array in-place?
 *    YES → Template 2 (Reader-Writer)
 *
 * Q: Do you need to merge/intersect two sorted sequences?
 *    YES → Template 3 (Merge)
 *
 * Q: Is there a cycle or repeated state?
 *    YES → Template 4 (Floyd's)
 *
 * Q: Do you need to count pairs satisfying a condition?
 *    YES → Template 6 (BS + Two Pointer)
 *
 * Q: Do you need longest/shortest subarray with a condition?
 *    YES → Sliding Window (see Modules 08-14!)
 *
 * COMMON MISTAKES:
 * ✗ Forgetting to skip duplicates in N-Sum
 * ✗ Using left <= right instead of left < right (off-by-one)
 * ✗ Not handling overflow in 4Sum (use long long)
 * ✗ Forgetting to sort before using two pointer
 */

int main() {
    // 3Sum example
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    auto triplets = threeSum(nums, 0);
    cout << "3Sum results:\n";
    for (auto& t : triplets) {
        cout << "  [" << t[0] << ", " << t[1] << ", " << t[2] << "]\n";
    }

    // 4Sum example
    vector<int> nums2 = {1, 0, -1, 0, -2, 2};
    auto quads = fourSum(nums2, 0);
    cout << "4Sum results:\n";
    for (auto& q : quads) {
        cout << "  [" << q[0] << ", " << q[1] << ", " << q[2] << ", " << q[3] << "]\n";
    }

    return 0;
}

