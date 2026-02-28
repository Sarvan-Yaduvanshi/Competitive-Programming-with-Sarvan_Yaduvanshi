/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : String Compression, Backspace Compare, Longest Mountain
 *            — Miscellaneous Two Pointer Patterns
 *  Level   : Easy → Medium
 * ============================================================================
 *
 *  LC 443  — String Compression (reader-writer two pointer)
 *            https://leetcode.com/problems/string-compression/
 *
 *  LC 844  — Backspace String Compare (reverse two pointer)
 *            https://leetcode.com/problems/backspace-string-compare/
 *
 *  LC 845  — Longest Mountain in Array (expand from peak)
 *            https://leetcode.com/problems/longest-mountain-in-array/
 *
 *  LC 443 uses the READER-WRITER pattern (same direction).
 *  LC 844 uses REVERSE two pointer (scan from the back).
 *  LC 845 uses EXPAND FROM CENTER (like palindromic substring).
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ============================================================================
// LC 443: String Compression — Reader-Writer Pattern
// ============================================================================
/*
 * Compress ["a","a","b","b","c","c","c"] → ["a","2","b","2","c","3"]
 * Return new length. Modify array in-place.
 *
 * Reader scans through, writer writes compressed result.
 * When we find a run of same chars, write char + count (if > 1).
 *
 * Time: O(N), Space: O(1)
 */
int compress(vector<char>& chars) {
    int writer = 0;     // Where to write next
    int reader = 0;     // Current read position
    int n = chars.size();

    while (reader < n) {
        char current = chars[reader];
        int count = 0;

        // Count consecutive same characters
        while (reader < n && chars[reader] == current) {
            reader++;
            count++;
        }

        // Write the character
        chars[writer++] = current;

        // Write the count (if > 1)
        if (count > 1) {
            string countStr = to_string(count);
            for (char c : countStr)
                chars[writer++] = c;
        }
    }
    return writer;
}

// ============================================================================
// LC 844: Backspace String Compare — Reverse Two Pointer (O(1) space!)
// ============================================================================
/*
 * '#' means backspace. Compare two strings after applying backspaces.
 *
 * APPROACH 1: Stack → O(N) space
 * APPROACH 2: Reverse two pointer → O(1) space ⭐
 *
 * Scan from the END. When we see '#', count how many chars to skip.
 * Compare the next "real" characters from both strings.
 *
 * Time: O(N + M), Space: O(1)
 */
bool backspaceCompare(string s, string t) {
    int i = (int)s.size() - 1;
    int j = (int)t.size() - 1;

    while (i >= 0 || j >= 0) {
        // Find next real char in s
        int skipS = 0;
        while (i >= 0) {
            if (s[i] == '#') { skipS++; i--; }
            else if (skipS > 0) { skipS--; i--; }
            else break;
        }

        // Find next real char in t
        int skipT = 0;
        while (j >= 0) {
            if (t[j] == '#') { skipT++; j--; }
            else if (skipT > 0) { skipT--; j--; }
            else break;
        }

        // Compare
        if (i >= 0 && j >= 0) {
            if (s[i] != t[j]) return false;
        } else if (i >= 0 || j >= 0) {
            return false; // One is empty, other isn't
        }
        i--; j--;
    }
    return true;
}

// ============================================================================
// LC 845: Longest Mountain in Array — Expand from Peak
// ============================================================================
/*
 * Mountain: strictly increase, then strictly decrease. Length ≥ 3.
 * Find the longest mountain subarray.
 *
 * APPROACH 1: For each peak candidate, expand left and right.
 * APPROACH 2: One-pass with up/down counters.
 *
 * Time: O(N), Space: O(1)
 */

// Approach 1: Expand from peak (two pointer from center)
int longestMountain_expand(vector<int>& arr) {
    int n = arr.size(), best = 0;

    for (int i = 1; i < n - 1; i++) {
        // Check if i is a peak
        if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
            int left = i, right = i;
            // Expand left while ascending
            while (left > 0 && arr[left - 1] < arr[left]) left--;
            // Expand right while descending
            while (right < n - 1 && arr[right] > arr[right + 1]) right++;
            best = max(best, right - left + 1);
        }
    }
    return best;
}

// Approach 2: One-pass with up/down counters
int longestMountain_onepass(vector<int>& arr) {
    int n = arr.size(), best = 0;
    int up = 0, down = 0;

    for (int i = 1; i < n; i++) {
        // Reset on flat or valley (new potential mountain)
        if (arr[i] == arr[i - 1] || (down > 0 && arr[i] > arr[i - 1])) {
            up = 0;
            down = 0;
        }

        if (arr[i] > arr[i - 1]) up++;
        if (arr[i] < arr[i - 1]) down++;

        // Valid mountain: has both up and down
        if (up > 0 && down > 0)
            best = max(best, up + down + 1);
    }
    return best;
}

int main() {
    // String Compression
    vector<char> chars = {'a','a','b','b','c','c','c'};
    int len = compress(chars);
    cout << "Compressed (" << len << "): ";
    for (int i = 0; i < len; i++) cout << chars[i];
    cout << "\n"; // a2b2c3

    // Backspace String Compare
    cout << "Backspace (ab#c, ad#c): " << backspaceCompare("ab#c", "ad#c") << "\n"; // 1 (both "ac")
    cout << "Backspace (ab##, c#d#): " << backspaceCompare("ab##", "c#d#") << "\n"; // 1 (both "")
    cout << "Backspace (a#c, b): " << backspaceCompare("a#c", "b") << "\n"; // 0 ("c" vs "b")

    // Longest Mountain
    vector<int> mountain = {2, 1, 4, 7, 3, 2, 5};
    cout << "Longest Mountain (expand): " << longestMountain_expand(mountain) << "\n"; // 5
    cout << "Longest Mountain (onepass): " << longestMountain_onepass(mountain) << "\n"; // 5

    return 0;
}

