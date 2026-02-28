/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Minimum Window Substring (LC 76)
 *  Level   : Hard
 * ============================================================================
 *
 *  LC 76  — Minimum Window Substring
 *           https://leetcode.com/problems/minimum-window-substring/
 *  GFG    — Smallest Window Containing All Characters
 *           https://practice.geeksforgeeks.org/problems/smallest-window-in-a-string-containing-all-the-characters-of-another-string/
 *
 *  PROBLEM: Given strings s and t, find minimum window in s that contains
 *  all characters of t (including duplicates).
 *
 *  APPROACH:
 *  ─────────
 *  1. Count frequency of all chars in t.
 *  2. Expand right: add s[right] to window.
 *  3. If s[right] matches a needed char, increment "formed" counter.
 *  4. Once all chars satisfied: shrink left to minimize window.
 *  5. Track minimum window.
 *
 *  Time: O(|s| + |t|), Space: O(|t|)
 *
 * ============================================================================
 */
#include <iostream>
#include <string>
#include <unordered_map>
#include <climits>
using namespace std;

string minWindow(string s, string t) {
    if (t.empty() || s.size() < t.size()) return "";

    unordered_map<char, int> need, have;
    for (char c : t) need[c]++;

    int required = need.size();  // Number of unique chars we need
    int formed = 0;              // How many unique chars we have in correct frequency

    int left = 0;
    int minLen = INT_MAX, minStart = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        char c = s[right];
        have[c]++;

        // If this char's frequency in window matches what we need
        if (need.count(c) && have[c] == need[c])
            formed++;

        // Try to shrink window from left
        while (formed == required) {
            // Update answer
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minStart = left;
            }

            // Remove leftmost character
            char lc = s[left];
            have[lc]--;
            if (need.count(lc) && have[lc] < need[lc])
                formed--;
            left++;
        }
    }

    return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
}

int main() {
    cout << "minWindow(ADOBECODEBANC, ABC): " << minWindow("ADOBECODEBANC", "ABC") << "\n"; // "BANC"
    cout << "minWindow(a, a): " << minWindow("a", "a") << "\n"; // "a"
    cout << "minWindow(a, aa): " << minWindow("a", "aa") << "\n"; // ""

    return 0;
}

