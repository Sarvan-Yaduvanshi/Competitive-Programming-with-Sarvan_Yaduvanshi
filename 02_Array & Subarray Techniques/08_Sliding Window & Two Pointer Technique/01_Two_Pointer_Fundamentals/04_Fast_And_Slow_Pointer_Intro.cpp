/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Fast & Slow Pointer Introduction
 *  Level   : Beginner
 * ============================================================================
 *
 *  ▶ FAST & SLOW POINTER (FLOYD'S TORTOISE AND HARE)
 *  ──────────────────────────────────────────────────
 *  - Slow pointer moves 1 step at a time
 *  - Fast pointer moves 2 steps at a time
 *  - If there's a cycle, fast WILL catch slow (they meet inside cycle)
 *  - If no cycle, fast reaches the end (NULL)
 *
 *  ▶ KEY APPLICATIONS:
 *  ───────────────────
 *  1. Detect cycle in linked list           → LC 141
 *  2. Find where cycle starts               → LC 142
 *  3. Find middle of linked list            → LC 876
 *  4. Find duplicate number (array as LL)   → LC 287
 *  5. Happy number detection                → LC 202
 *
 *  ▶ WHY DOES FLOYD'S WORK?
 *  ────────────────────────
 *  If cycle length = C, after slow enters cycle:
 *  Fast gains 1 step per iteration on slow.
 *  After at most C iterations, fast catches slow.
 *
 *  To find cycle START:
 *  After meeting point, reset one pointer to head.
 *  Move both at speed 1. They meet at cycle start.
 *  MATH: distance from head to cycle start = distance from meeting point to cycle start (going forward)
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ============================================================================
// EXAMPLE 1: Happy Number (Floyd's on Math sequence)
// ============================================================================
/*
 * LC 202: Happy Number
 * https://leetcode.com/problems/happy-number/
 *
 * Starting with number n, repeatedly replace it with sum of squares of digits.
 * If it reaches 1, it's happy. If it loops forever, it's not.
 * Use Floyd's to detect the cycle!
 */
int sumOfSquares(int n) {
    int sum = 0;
    while (n > 0) {
        int d = n % 10;
        sum += d * d;
        n /= 10;
    }
    return sum;
}

bool isHappy(int n) {
    int slow = n, fast = n;
    do {
        slow = sumOfSquares(slow);            // 1 step
        fast = sumOfSquares(sumOfSquares(fast)); // 2 steps
    } while (slow != fast);

    return slow == 1;  // If cycle includes 1, it's happy
}

// ============================================================================
// EXAMPLE 2: Find Middle of Array (simulated linked list)
// ============================================================================
/*
 * LC 876: Middle of the Linked List
 *
 * When fast reaches end, slow is at the middle.
 * For array: fast moves 2, slow moves 1.
 */
int findMiddleIndex(vector<int>& arr) {
    int slow = 0, fast = 0;
    int n = arr.size();

    while (fast < n - 1 && fast + 1 < n) {
        slow++;
        fast += 2;
    }
    return slow;
}

// ============================================================================
// EXAMPLE 3: Find Duplicate Number (Floyd's on Array)
// ============================================================================
/*
 * LC 287: Find the Duplicate Number
 * https://leetcode.com/problems/find-the-duplicate-number/
 *
 * Array of n+1 integers in range [1, n]. Exactly one duplicate.
 * Treat arr[i] as a "next pointer" → linked list with a cycle!
 * The duplicate is the cycle entry point.
 */
int findDuplicate(vector<int>& nums) {
    // Phase 1: Detect cycle (find meeting point)
    int slow = nums[0], fast = nums[0];
    do {
        slow = nums[slow];           // 1 step
        fast = nums[nums[fast]];     // 2 steps
    } while (slow != fast);

    // Phase 2: Find cycle entry (= duplicate number)
    slow = nums[0];
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];  // Both move 1 step now
    }
    return slow;
}

int main() {
    // Happy Number
    cout << "Is 19 happy? " << (isHappy(19) ? "YES" : "NO") << "\n";   // YES
    cout << "Is 2 happy? " << (isHappy(2) ? "YES" : "NO") << "\n";     // NO

    // Find Middle
    vector<int> arr = {1, 2, 3, 4, 5};
    cout << "Middle index of [1,2,3,4,5]: " << findMiddleIndex(arr) << "\n"; // 2

    // Find Duplicate
    vector<int> nums = {1, 3, 4, 2, 2};
    cout << "Duplicate: " << findDuplicate(nums) << "\n";  // 2

    return 0;
}

