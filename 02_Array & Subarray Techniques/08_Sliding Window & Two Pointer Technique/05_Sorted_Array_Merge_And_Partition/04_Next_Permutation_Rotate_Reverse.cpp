/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Next Permutation, Rotate Array, Reverse Technique
 *  Level   : Medium
 * ============================================================================
 *
 *  LC 31   — Next Permutation (two pointer + reverse)
 *            https://leetcode.com/problems/next-permutation/
 *
 *  LC 189  — Rotate Array (3 reverses technique)
 *            https://leetcode.com/problems/rotate-array/
 *
 *  LC 151  — Reverse Words in a String (reverse full + reverse each word)
 *            https://leetcode.com/problems/reverse-words-in-a-string/
 *
 *  THESE ARE ALL BASED ON THE "REVERSE TECHNIQUE" — a two pointer pattern
 *  where reversing sub-sections achieves the desired permutation/rotation.
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ============================================================================
// LC 31: Next Permutation
// ============================================================================
/*
 *  ALGORITHM (Narayana Pandita's algorithm):
 *  ──────────────────────────────────────────
 *  1. From the RIGHT, find first index i where nums[i] < nums[i+1]
 *     (this is the "dip" — the rightmost point where the suffix stops being sorted desc)
 *  2. From the RIGHT, find first index j where nums[j] > nums[i]
 *     (smallest element larger than nums[i] in the suffix)
 *  3. Swap nums[i] and nums[j]
 *  4. Reverse the suffix after index i (make it ascending)
 *
 *  If no dip found (fully descending) → reverse entire array (go to first permutation)
 *
 *  WHY TWO POINTER? Step 4 uses reverse (two pointer converging swap).
 *  Steps 1 & 2 use right-to-left scanning.
 *
 *  Time: O(N), Space: O(1)
 *
 *  VISUAL EXAMPLE:
 *  [1, 2, 3] → [1, 3, 2]
 *  [3, 2, 1] → [1, 2, 3]  (wrap around)
 *  [1, 1, 5] → [1, 5, 1]
 *  [2, 3, 1] → step1: i=0(2<3), step2: j=2(1? no, 1<2), j=1(3>2)
 *              swap → [3, 2, 1], reverse after i=0 → [3, 1, 2]
 */
void nextPermutation(vector<int>& nums) {
    int n = nums.size();

    // Step 1: Find the dip from right
    int i = n - 2;
    while (i >= 0 && nums[i] >= nums[i + 1])
        i--;

    if (i >= 0) {
        // Step 2: Find smallest element > nums[i] from right
        int j = n - 1;
        while (nums[j] <= nums[i])
            j--;
        // Step 3: Swap
        swap(nums[i], nums[j]);
    }

    // Step 4: Reverse suffix after index i
    reverse(nums.begin() + i + 1, nums.end());
}

// ============================================================================
// LC 189: Rotate Array — 3 Reverses Technique
// ============================================================================
/*
 *  Rotate array to the right by k steps.
 *  [1,2,3,4,5,6,7], k=3 → [5,6,7,1,2,3,4]
 *
 *  TECHNIQUE (3 reverses):
 *  1. Reverse entire array:     [7,6,5,4,3,2,1]
 *  2. Reverse first k elements: [5,6,7,4,3,2,1]
 *  3. Reverse remaining n-k:    [5,6,7,1,2,3,4] ✓
 *
 *  WHY? Reverse = two pointer swap from both ends.
 *  Time: O(N), Space: O(1)
 */
void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k %= n;  // Handle k > n
    if (k == 0) return;

    reverse(nums.begin(), nums.end());           // Reverse all
    reverse(nums.begin(), nums.begin() + k);     // Reverse first k
    reverse(nums.begin() + k, nums.end());       // Reverse rest
}

// ============================================================================
// LC 151: Reverse Words in a String
// ============================================================================
/*
 * "the sky is blue" → "blue is sky the"
 *
 * TECHNIQUE: Reverse entire string, then reverse each word.
 * Also need to handle multiple spaces, leading/trailing spaces.
 *
 * This uses two pointer for:
 * 1. The reverse operation itself
 * 2. The reader-writer to compact spaces
 */
string reverseWords(string s) {
    // Step 1: Reverse entire string
    reverse(s.begin(), s.end());

    int n = s.size();
    int writer = 0; // Where to write next character
    int i = 0;

    while (i < n) {
        // Skip spaces
        if (s[i] == ' ') { i++; continue; }

        // Add space between words (not before first word)
        if (writer > 0) s[writer++] = ' ';

        // Copy word and track its start
        int wordStart = writer;
        while (i < n && s[i] != ' ')
            s[writer++] = s[i++];

        // Reverse this word in-place
        reverse(s.begin() + wordStart, s.begin() + writer);
    }

    s.resize(writer);
    return s;
}

int main() {
    // Next Permutation
    vector<int> nums1 = {1, 2, 3};
    nextPermutation(nums1);
    cout << "Next perm of [1,2,3]: ";
    for (int x : nums1) cout << x << " ";
    cout << "\n"; // 1 3 2

    vector<int> nums2 = {3, 2, 1};
    nextPermutation(nums2);
    cout << "Next perm of [3,2,1]: ";
    for (int x : nums2) cout << x << " ";
    cout << "\n"; // 1 2 3

    vector<int> nums3 = {1, 1, 5};
    nextPermutation(nums3);
    cout << "Next perm of [1,1,5]: ";
    for (int x : nums3) cout << x << " ";
    cout << "\n"; // 1 5 1

    // Rotate Array
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    rotate(arr, 3);
    cout << "Rotate k=3: ";
    for (int x : arr) cout << x << " ";
    cout << "\n"; // 5 6 7 1 2 3 4

    // Reverse Words
    cout << "Reverse words: \"" << reverseWords("  the sky is  blue  ") << "\"\n";
    // "blue is sky the"

    return 0;
}

