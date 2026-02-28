/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Find the Duplicate Number (LC 287) — Floyd's on Array
 *  Level   : Medium
 *  Link    : https://leetcode.com/problems/find-the-duplicate-number/
 * ============================================================================
 *
 *  Array of n+1 integers in [1, n]. Exactly one duplicate (may repeat many times).
 *  Find it without modifying array, O(1) space.
 *
 *  TRICK: Treat index as node, arr[index] as next pointer → functional graph.
 *  Since values are in [1,n] but we have n+1 elements, there's a cycle.
 *  The duplicate is the cycle entry point!
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
using namespace std;

int findDuplicate(vector<int>& nums) {
    int slow = nums[0], fast = nums[0];

    // Phase 1: Find meeting point inside cycle
    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);

    // Phase 2: Find cycle entry (= duplicate)
    slow = nums[0];
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }
    return slow;
}

int main() {
    vector<int> nums1 = {1, 3, 4, 2, 2};
    cout << "Duplicate: " << findDuplicate(nums1) << "\n"; // 2

    vector<int> nums2 = {3, 1, 3, 4, 2};
    cout << "Duplicate: " << findDuplicate(nums2) << "\n"; // 3

    return 0;
}

