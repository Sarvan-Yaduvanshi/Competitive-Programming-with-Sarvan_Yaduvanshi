/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Remove Duplicates & In-Place Compaction
 *  Level   : Easy → Medium
 * ============================================================================
 *
 *  LC 26  — Remove Duplicates from Sorted Array
 *           https://leetcode.com/problems/remove-duplicates-from-sorted-array/
 *  LC 80  — Remove Duplicates II (at most 2 allowed)
 *           https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
 *  LC 27  — Remove Element
 *           https://leetcode.com/problems/remove-element/
 *  LC 283 — Move Zeroes
 *           https://leetcode.com/problems/move-zeroes/
 *  GFG    — Merge Without Extra Space
 *           https://practice.geeksforgeeks.org/problems/merge-two-sorted-arrays5135/
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// LC 26: Remove Duplicates (keep 1 of each)
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    int w = 1;
    for (int r = 1; r < (int)nums.size(); r++)
        if (nums[r] != nums[r - 1])
            nums[w++] = nums[r];
    return w;
}

// LC 80: Remove Duplicates II (keep at most 2)
int removeDuplicatesII(vector<int>& nums) {
    if (nums.size() <= 2) return nums.size();
    int w = 2;
    for (int r = 2; r < (int)nums.size(); r++)
        if (nums[r] != nums[w - 2])
            nums[w++] = nums[r];
    return w;
}

// LC 27: Remove Element
int removeElement(vector<int>& nums, int val) {
    int w = 0;
    for (int r = 0; r < (int)nums.size(); r++)
        if (nums[r] != val)
            nums[w++] = nums[r];
    return w;
}

// LC 283: Move Zeroes
void moveZeroes(vector<int>& nums) {
    int w = 0;
    for (int r = 0; r < (int)nums.size(); r++)
        if (nums[r] != 0)
            swap(nums[w++], nums[r]);
}

// GFG: Merge Without Extra Space (Gap method)
void mergeWithoutExtraSpace(vector<int>& a, vector<int>& b) {
    int n = a.size(), m = b.size();
    int gap = (n + m + 1) / 2;

    while (gap > 0) {
        int i = 0, j = gap;
        while (j < n + m) {
            int& x = (i < n) ? a[i] : b[i - n];
            int& y = (j < n) ? a[j] : b[j - n];
            if (x > y) swap(x, y);
            i++; j++;
        }
        if (gap == 1) break;
        gap = (gap + 1) / 2;
    }
}

int main() {
    vector<int> nums = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int len = removeDuplicates(nums);
    cout << "Remove Dups (" << len << "): ";
    for (int i = 0; i < len; i++) cout << nums[i] << " ";
    cout << "\n";

    vector<int> nums2 = {1, 1, 1, 2, 2, 3};
    int len2 = removeDuplicatesII(nums2);
    cout << "Remove Dups II (" << len2 << "): ";
    for (int i = 0; i < len2; i++) cout << nums2[i] << " ";
    cout << "\n";

    vector<int> nums3 = {0, 1, 0, 3, 12};
    moveZeroes(nums3);
    cout << "Move Zeroes: ";
    for (int x : nums3) cout << x << " ";
    cout << "\n";

    return 0;
}

