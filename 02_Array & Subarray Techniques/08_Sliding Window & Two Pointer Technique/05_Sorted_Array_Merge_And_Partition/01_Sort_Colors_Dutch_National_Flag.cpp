/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Sort Colors / Dutch National Flag (3-Way Partition)
 *  Level   : Medium
 * ============================================================================
 *
 *  LC 75   — Sort Colors  https://leetcode.com/problems/sort-colors/
 *  GFG     — Sort 0s 1s 2s
 *            https://practice.geeksforgeeks.org/problems/sort-an-array-of-0s-1s-and-2s/
 *
 *  DUTCH NATIONAL FLAG ALGORITHM (Dijkstra):
 *  ─────────────────────────────────────────
 *  Three pointers: low, mid, high
 *  - [0..low-1]    → all 0s
 *  - [low..mid-1]  → all 1s
 *  - [mid..high]   → unknown (to be processed)
 *  - [high+1..N-1] → all 2s
 *
 *  Process mid pointer:
 *  - If arr[mid] == 0: swap(arr[low], arr[mid]), low++, mid++
 *  - If arr[mid] == 1: mid++ (already in correct region)
 *  - If arr[mid] == 2: swap(arr[mid], arr[high]), high-- (don't advance mid!)
 *
 *  Time: O(N), Space: O(1)
 *
 *  GENERALIZATION:
 *  This pattern works for ANY 3-way partition problem:
 *  - Partition around a pivot (< pivot, == pivot, > pivot)
 *  - LC 2161: Partition Array According to Given Pivot
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================================
// LC 75: Sort Colors — Dutch National Flag
// ============================================================================
void sortColors(vector<int>& nums) {
    int low = 0, mid = 0, high = (int)nums.size() - 1;

    while (mid <= high) {
        if (nums[mid] == 0) {
            swap(nums[low], nums[mid]);
            low++;
            mid++;
        }
        else if (nums[mid] == 1) {
            mid++;
        }
        else { // nums[mid] == 2
            swap(nums[mid], nums[high]);
            high--;
            // DON'T increment mid! The swapped element needs to be checked.
        }
    }
}

// ============================================================================
// LC 905: Sort Array By Parity — Two pointer partition
// ============================================================================
/*
 * Move all even numbers to the front, odd to the back.
 * https://leetcode.com/problems/sort-array-by-parity/
 */
vector<int> sortArrayByParity(vector<int>& nums) {
    int left = 0, right = (int)nums.size() - 1;
    while (left < right) {
        if (nums[left] % 2 == 1 && nums[right] % 2 == 0) {
            swap(nums[left], nums[right]);
        }
        if (nums[left] % 2 == 0) left++;
        if (nums[right] % 2 == 1) right--;
    }
    return nums;
}

// ============================================================================
// LC 2161: Partition Array According to Given Pivot
// ============================================================================
/*
 * Rearrange: elements < pivot, then == pivot, then > pivot.
 * Maintain relative order within each group.
 * https://leetcode.com/problems/partition-array-according-to-given-pivot/
 */
vector<int> pivotArray(vector<int>& nums, int pivot) {
    vector<int> less, equal, greater;
    for (int x : nums) {
        if (x < pivot) less.push_back(x);
        else if (x == pivot) equal.push_back(x);
        else greater.push_back(x);
    }
    vector<int> result;
    for (int x : less) result.push_back(x);
    for (int x : equal) result.push_back(x);
    for (int x : greater) result.push_back(x);
    return result;
}

int main() {
    // Sort Colors
    vector<int> colors = {2, 0, 2, 1, 1, 0};
    sortColors(colors);
    cout << "Sort Colors: ";
    for (int x : colors) cout << x << " ";
    cout << "\n"; // 0 0 1 1 2 2

    // Sort by Parity
    vector<int> parity = {3, 1, 2, 4};
    sortArrayByParity(parity);
    cout << "Sort by Parity: ";
    for (int x : parity) cout << x << " ";
    cout << "\n"; // 4 2 ... (evens first)

    return 0;
}

