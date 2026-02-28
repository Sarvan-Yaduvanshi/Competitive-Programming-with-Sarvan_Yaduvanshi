/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : What is Two Pointer Technique?
 *  Level   : Beginner
 * ============================================================================
 *
 *  TABLE OF CONTENTS:
 *  ──────────────────
 *  1. Definition & Intuition
 *  2. Real-Life Analogies
 *  3. The THREE Types of Two Pointer
 *  4. When to Use Two Pointer
 *  5. When Two Pointer FAILS
 *  6. Time & Space Complexity
 *  7. Simple Example: Pair Sum in Sorted Array
 *
 * ============================================================================
 *
 *  ▶ WHAT IS TWO POINTER?
 *  ──────────────────────
 *  Two Pointer is a technique where we use TWO indices (pointers) that move
 *  through a data structure in a coordinated way. Instead of using nested
 *  loops (O(N²)), we use two pointers that together visit each element at
 *  most once, giving us O(N) time.
 *
 *  KEY IDEA: Replace brute-force O(N²) with smart pointer movement O(N).
 *
 *  ▶ REAL-LIFE ANALOGIES:
 *  ──────────────────────
 *  1. BOOK READING: Two people reading a book — one from the front, one
 *     from the back. They meet somewhere in the middle.
 *     → This is OPPOSITE DIRECTION two pointer.
 *
 *  2. RACE TRACK: A fast runner and a slow runner on a circular track.
 *     The fast one will eventually lap the slow one.
 *     → This is FAST & SLOW pointer (Floyd's cycle detection).
 *
 *  3. COPYING HOMEWORK: One person reads (reader), another writes (writer).
 *     The reader goes through everything, the writer only copies what matters.
 *     → This is SAME DIRECTION (reader-writer) two pointer.
 *
 *  4. TASTING WINE: Two sommeliers taste wines — one starts with the
 *     cheapest, the other with the most expensive. They adjust based on
 *     whether the current pair is too cheap or too expensive.
 *     → This is CONVERGING two pointer for pair finding.
 *
 *  ▶ THE THREE TYPES OF TWO POINTER:
 *  ──────────────────────────────────
 *
 *  TYPE 1: OPPOSITE DIRECTION (Converging)
 *  ────────────────────────────────────────
 *  - Two pointers start at opposite ends: left=0, right=N-1
 *  - Move towards each other until they meet
 *  - USE WHEN: Sorted array pair finding, palindrome check, container water
 *
 *     left ──────►         ◄────── right
 *     [0]  [1]  [2]  [3]  [4]  [5]  [6]
 *
 *  TYPE 2: SAME DIRECTION (Reader-Writer / Merge)
 *  ───────────────────────────────────────────────
 *  - Both pointers start at the same end (usually 0)
 *  - Fast pointer (reader) scans everything
 *  - Slow pointer (writer) only advances for valid elements
 *  - USE WHEN: Remove duplicates, move zeroes, merge sorted arrays
 *
 *     slow ──►
 *     fast ────────────────────────────►
 *     [0]  [1]  [2]  [3]  [4]  [5]  [6]
 *
 *  TYPE 3: FAST & SLOW (Floyd's Tortoise and Hare)
 *  ─────────────────────────────────────────────────
 *  - Slow moves 1 step, Fast moves 2 steps
 *  - If there's a cycle, they WILL meet
 *  - USE WHEN: Cycle detection, finding middle, finding duplicate
 *
 *     slow ─► (1 step)
 *     fast ──────► (2 steps)
 *     [0] → [1] → [2] → [3] → [4] → [2] (cycle!)
 *
 *  ▶ WHEN TO USE TWO POINTER:
 *  ──────────────────────────
 *  ✅ Array/string is SORTED (or can be sorted)
 *  ✅ Need to find PAIRS/TRIPLETS satisfying a condition
 *  ✅ Need to COMPACT/FILTER an array in-place
 *  ✅ Need to MERGE two sorted sequences
 *  ✅ Need to detect CYCLES in linked list / functional graph
 *  ✅ Need to check PALINDROME
 *  ✅ Need to find SUBARRAY with some property (→ sliding window variant)
 *
 *  ▶ WHEN TWO POINTER FAILS:
 *  ─────────────────────────
 *  ❌ Array is NOT sorted and sorting would lose information (indices)
 *  ❌ Problem needs ALL pairs, not just existence/count → O(N²) unavoidable
 *  ❌ Non-monotonic relationship between pointer movement and answer
 *  ❌ Problem requires DP / graph / tree traversal
 *
 *  ▶ TIME & SPACE:
 *  ───────────────
 *  Time:  O(N) — each pointer moves at most N times
 *  Space: O(1) — just two integer indices
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================================
// EXAMPLE 1: Pair Sum in Sorted Array (Opposite Direction)
// ============================================================================
/*
 * Given: Sorted array, find if there exist two elements that sum to target.
 *
 * BRUTE FORCE: O(N²) — check all pairs
 * TWO POINTER: O(N) — start from both ends
 *
 * WHY IT WORKS:
 * If sum < target → left pointer must increase (need bigger numbers)
 * If sum > target → right pointer must decrease (need smaller numbers)
 * Since array is sorted, these movements are always correct.
 */
pair<int,int> pairSumSorted(vector<int>& arr, int target) {
    int left = 0, right = (int)arr.size() - 1;

    while (left < right) {
        int sum = arr[left] + arr[right];

        if (sum == target) {
            return {left, right};   // Found!
        }
        else if (sum < target) {
            left++;     // Need bigger sum → move left forward
        }
        else {
            right--;    // Need smaller sum → move right backward
        }
    }
    return {-1, -1};   // Not found
}

// ============================================================================
// EXAMPLE 2: Move Zeroes (Same Direction / Reader-Writer)
// ============================================================================
/*
 * Given: Array with some zeroes. Move all zeroes to end, maintain order.
 *
 * Writer (slow) points to where next non-zero should go.
 * Reader (fast) scans through all elements.
 */
void moveZeroes(vector<int>& nums) {
    int writer = 0;     // Slow pointer — where to write next non-zero

    for (int reader = 0; reader < (int)nums.size(); reader++) {
        if (nums[reader] != 0) {
            swap(nums[writer], nums[reader]);
            writer++;
        }
    }
    // All non-zeroes are now at positions [0..writer-1]
    // Zeroes are automatically at positions [writer..N-1]
}

// ============================================================================
// EXAMPLE 3: Palindrome Check (Opposite Direction)
// ============================================================================
bool isPalindrome(const string& s) {
    int left = 0, right = (int)s.size() - 1;

    while (left < right) {
        if (s[left] != s[right]) return false;
        left++;
        right--;
    }
    return true;
}

int main() {
    // Example 1: Pair Sum
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    int target = 12;
    auto [i, j] = pairSumSorted(arr, target);
    cout << "Pair with sum " << target << ": ";
    if (i != -1) cout << "arr[" << i << "]=" << arr[i] << ", arr[" << j << "]=" << arr[j] << "\n";
    else cout << "Not found\n";

    // Example 2: Move Zeroes
    vector<int> nums = {0, 1, 0, 3, 12};
    moveZeroes(nums);
    cout << "After moving zeroes: ";
    for (int x : nums) cout << x << " ";
    cout << "\n";

    // Example 3: Palindrome
    string s = "racecar";
    cout << "\"" << s << "\" is palindrome: " << (isPalindrome(s) ? "YES" : "NO") << "\n";

    return 0;
}

