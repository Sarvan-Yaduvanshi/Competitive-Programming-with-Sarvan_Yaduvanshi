/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Same Direction (Reader-Writer) Two Pointers
 *  Level   : Beginner
 * ============================================================================
 *
 *  TABLE OF CONTENTS:
 *  ──────────────────
 *  1. What is Same Direction Two Pointer?
 *  2. Reader-Writer Pattern (In-Place Compaction)
 *  3. Merge Two Sorted Arrays Pattern
 *  4. Intersection of Two Sorted Arrays Pattern
 *
 * ============================================================================
 *
 *  ▶ WHAT IS SAME DIRECTION TWO POINTER?
 *  ──────────────────────────────────────
 *  Both pointers move in the SAME direction (usually left to right).
 *  One is "fast" (reader) — scans through every element.
 *  One is "slow" (writer) — only advances when we find a valid element.
 *
 *  TEMPLATE (Reader-Writer):
 *  ─────────────────────────
 *  int writer = 0;
 *  for (int reader = 0; reader < N; reader++) {
 *      if (arr[reader] satisfies condition) {
 *          arr[writer] = arr[reader];  // or swap
 *          writer++;
 *      }
 *  }
 *  // arr[0..writer-1] contains all valid elements
 *
 *  TEMPLATE (Merge):
 *  ─────────────────
 *  int i = 0, j = 0;
 *  while (i < A.size() && j < B.size()) {
 *      if (A[i] <= B[j]) result.push_back(A[i++]);
 *      else result.push_back(B[j++]);
 *  }
 *  // append remaining from whichever hasn't finished
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================================
// PATTERN 1: Remove Duplicates from Sorted Array
// ============================================================================
/*
 * LC 26: Remove Duplicates from Sorted Array
 * https://leetcode.com/problems/remove-duplicates-from-sorted-array/
 *
 * Remove duplicates in-place, return new length.
 * Writer only advances when we see a NEW value.
 */
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;

    int writer = 1;  // First element is always unique
    for (int reader = 1; reader < (int)nums.size(); reader++) {
        if (nums[reader] != nums[reader - 1]) {
            nums[writer] = nums[reader];
            writer++;
        }
    }
    return writer;
}

// ============================================================================
// PATTERN 2: Remove Element
// ============================================================================
/*
 * LC 27: Remove Element
 * https://leetcode.com/problems/remove-element/
 *
 * Remove all occurrences of val in-place, return new length.
 */
int removeElement(vector<int>& nums, int val) {
    int writer = 0;
    for (int reader = 0; reader < (int)nums.size(); reader++) {
        if (nums[reader] != val) {
            nums[writer] = nums[reader];
            writer++;
        }
    }
    return writer;
}

// ============================================================================
// PATTERN 3: Merge Sorted Array
// ============================================================================
/*
 * LC 88: Merge Sorted Array
 * https://leetcode.com/problems/merge-sorted-array/
 *
 * Merge nums2 into nums1 (nums1 has extra space at end).
 * TRICK: Merge from the BACK to avoid overwriting.
 */
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1;      // Last real element in nums1
    int j = n - 1;      // Last element in nums2
    int k = m + n - 1;  // Last position in merged array

    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) {
            nums1[k--] = nums1[i--];
        } else {
            nums1[k--] = nums2[j--];
        }
    }
    // Copy remaining nums2 elements (nums1 elements are already in place)
    while (j >= 0) {
        nums1[k--] = nums2[j--];
    }
}

// ============================================================================
// PATTERN 4: Intersection of Two Sorted Arrays
// ============================================================================
/*
 * LC 349/350: Intersection of Two Arrays
 * https://leetcode.com/problems/intersection-of-two-arrays/
 *
 * Two pointers on sorted arrays — skip duplicates.
 */
vector<int> intersection(vector<int>& a, vector<int>& b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    vector<int> result;
    int i = 0, j = 0;

    while (i < (int)a.size() && j < (int)b.size()) {
        if (a[i] == b[j]) {
            // Skip duplicates
            if (result.empty() || result.back() != a[i])
                result.push_back(a[i]);
            i++; j++;
        }
        else if (a[i] < b[j]) i++;
        else j++;
    }
    return result;
}

// ============================================================================
// PATTERN 5: Move Zeroes
// ============================================================================
/*
 * LC 283: Move Zeroes
 * https://leetcode.com/problems/move-zeroes/
 *
 * Move all 0s to end, maintain relative order of non-zero elements.
 */
void moveZeroes(vector<int>& nums) {
    int writer = 0;
    for (int reader = 0; reader < (int)nums.size(); reader++) {
        if (nums[reader] != 0) {
            swap(nums[writer], nums[reader]);
            writer++;
        }
    }
}

int main() {
    // Remove Duplicates
    vector<int> arr = {1, 1, 2, 2, 3, 4, 4};
    int newLen = removeDuplicates(arr);
    cout << "Remove Duplicates (" << newLen << "): ";
    for (int i = 0; i < newLen; i++) cout << arr[i] << " ";
    cout << "\n";

    // Merge Sorted
    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    vector<int> nums2 = {2, 5, 6};
    merge(nums1, 3, nums2, 3);
    cout << "Merged: ";
    for (int x : nums1) cout << x << " ";
    cout << "\n";

    // Move Zeroes
    vector<int> nums = {0, 1, 0, 3, 12};
    moveZeroes(nums);
    cout << "Move Zeroes: ";
    for (int x : nums) cout << x << " ";
    cout << "\n";

    return 0;
}

