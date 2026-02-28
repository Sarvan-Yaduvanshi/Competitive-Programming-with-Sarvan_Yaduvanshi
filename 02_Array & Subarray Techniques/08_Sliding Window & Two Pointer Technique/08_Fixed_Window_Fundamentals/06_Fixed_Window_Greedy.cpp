/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Fixed Window + Greedy (Consecutive Ones, Group Elements)
 *  Level   : Medium
 * ============================================================================
 *
 *  ▶ PATTERN: Fixed window + greedy → "What's the best fixed-size window?"
 *  The window size might be determined by a constraint (K flips, total 1s, etc.)
 *
 *  PROBLEMS:
 *  LC 1004 — Max Consecutive Ones III (variable window, but K=fixed flips)
 *            https://leetcode.com/problems/max-consecutive-ones-iii/
 *  LC 2009 — Min Operations to Make Array Continuous (sort + fixed window)
 *            https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/
 *  LC 2134 — Min Swaps to Group 1s Together II (covered in circular file)
 *            https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/
 *  LC 1151 — Min Swaps to Group All 1s Together (non-circular)
 *            https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together/
 *  LC 2516 — Take K of Each Character From Left and Right
 *            https://leetcode.com/problems/take-k-of-each-character-from-left-and-right/
 *  LC 1052 — Grumpy Bookstore Owner (already covered in 08/02)
 *            https://leetcode.com/problems/grumpy-bookstore-owner/
 *  LC 2024 — Maximize the Confusion of an Exam (variable but K-flips)
 *            https://leetcode.com/problems/maximize-the-confusion-of-an-exam/
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

// ============================================================================
// LC 1151: Min Swaps to Group All 1s Together (Non-Circular)
// ============================================================================
/*
 * Binary array. Group all 1s together using minimum swaps.
 * Window size = total number of 1s.
 * Find window with max 1s already → swaps = totalOnes - maxOnesInWindow.
 *
 * Time: O(N), Space: O(1)
 */
int minSwapsNonCircular(vector<int>& data) {
    int n = data.size();
    int totalOnes = 0;
    for (int x : data) totalOnes += x;
    if (totalOnes <= 1) return 0;

    int k = totalOnes;
    int onesInWin = 0, maxOnes = 0;
    for (int i = 0; i < n; i++) {
        onesInWin += data[i];
        if (i >= k) onesInWin -= data[i - k];
        if (i >= k - 1) maxOnes = max(maxOnes, onesInWin);
    }
    return k - maxOnes;
}

// ============================================================================
// LC 2009: Min Operations to Make Array Continuous (Sort + Fixed Window)
// ============================================================================
/*
 * After operations, array must contain consecutive integers.
 * N elements → target range of size N. Find window of [x, x+N-1] that
 * covers the most unique elements. Answer = N - maxCovered.
 *
 * TECHNIQUE: Sort + remove duplicates. Sliding window of value range N.
 * For each left, find rightmost right where arr[right] <= arr[left] + N - 1.
 *
 * Time: O(N log N), Space: O(N)
 */
int minOperations(vector<int>& nums) {
    int n = nums.size();
    // Sort and remove duplicates
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    int m = nums.size(); // Unique count

    int maxCovered = 0, right = 0;
    for (int left = 0; left < m; left++) {
        while (right < m && nums[right] <= nums[left] + n - 1)
            right++;
        maxCovered = max(maxCovered, right - left);
    }
    return n - maxCovered;
}

// ============================================================================
// LC 2024: Maximize Confusion (Max Consecutive T's or F's with K flips)
// ============================================================================
/*
 * Answer key string of T/F. Can change at most K answers.
 * Maximize longest consecutive same answers.
 *
 * Same as "Max Consecutive Ones III" but for two characters.
 * Run sliding window twice: once for max T's, once for max F's.
 *
 * Time: O(N), Space: O(1)
 */
int maxConsecutiveChar(string& s, int k, char target) {
    int left = 0, flips = 0, best = 0;
    for (int right = 0; right < (int)s.size(); right++) {
        if (s[right] != target) flips++;
        while (flips > k) {
            if (s[left] != target) flips--;
            left++;
        }
        best = max(best, right - left + 1);
    }
    return best;
}

int maxConsecutiveAnswers(string answerKey, int k) {
    return max(maxConsecutiveChar(answerKey, k, 'T'),
               maxConsecutiveChar(answerKey, k, 'F'));
}

// ============================================================================
// LC 2516: Take K of Each Character From Left and Right
// ============================================================================
/*
 * String of a/b/c. Take K of each from left and/or right.
 * Equivalent: Find LONGEST middle window to REMOVE such that
 * remaining left+right still has ≥ K of each.
 *
 * = Find longest window where removed a's ≤ total_a - k, etc.
 * This is a variable window on the middle.
 *
 * Time: O(N), Space: O(1)
 */
int takeCharacters(string s, int k) {
    int n = s.size();
    int total[3] = {};
    for (char c : s) total[c - 'a']++;

    // Check if possible
    for (int i = 0; i < 3; i++)
        if (total[i] < k) return -1;

    // Max window to remove: window can have at most (total[i] - k) of each char
    int maxRemove[3];
    for (int i = 0; i < 3; i++) maxRemove[i] = total[i] - k;

    int windowCount[3] = {};
    int left = 0, maxWindowLen = 0;

    for (int right = 0; right < n; right++) {
        windowCount[s[right] - 'a']++;
        while (windowCount[0] > maxRemove[0] ||
               windowCount[1] > maxRemove[1] ||
               windowCount[2] > maxRemove[2]) {
            windowCount[s[left] - 'a']--;
            left++;
        }
        maxWindowLen = max(maxWindowLen, right - left + 1);
    }
    return n - maxWindowLen;
}

// ============================================================================
// Window with Max Score — Fixed window, pick elements greedily
// ============================================================================
/*
 * Given array and window size K, find window with max "score".
 * Score = sum of top M elements in the window (greedy pick).
 * For simple max sum → standard fixed window.
 * For top M in window → multiset or sorted structure.
 */

int main() {
    // Min swaps (non-circular)
    vector<int> data = {1, 0, 1, 0, 1};
    cout << "Min swaps: " << minSwapsNonCircular(data) << "\n"; // 1

    // Min operations continuous
    vector<int> nums = {4, 2, 5, 3};
    cout << "Min ops continuous: " << minOperations(nums) << "\n"; // 0

    // Max consecutive answers
    cout << "Max confusion: " << maxConsecutiveAnswers("TTFF", 2) << "\n"; // 4

    // Take K of each character
    cout << "Take chars: " << takeCharacters("aabaaaacaabc", 2) << "\n"; // 8

    return 0;
}

