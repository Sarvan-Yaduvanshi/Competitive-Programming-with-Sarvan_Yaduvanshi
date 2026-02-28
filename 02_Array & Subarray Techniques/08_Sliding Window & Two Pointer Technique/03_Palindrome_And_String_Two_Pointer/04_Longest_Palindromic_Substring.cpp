/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Longest Palindromic Substring (LC 5) — Expand from Center
 *  Level   : Medium
 *  Link    : https://leetcode.com/problems/longest-palindromic-substring/
 * ============================================================================
 *
 *  For each center (and each pair of adjacent centers for even-length),
 *  expand outward while characters match. Track the longest.
 *  Time: O(N²), Space: O(1)
 *
 *  Also: LC 647 — Count ALL palindromic substrings (same expand technique)
 *  https://leetcode.com/problems/palindromic-substrings/
 * ============================================================================
 */
#include <iostream>
#include <string>
using namespace std;

// Expand around center — returns length of palindrome
int expandAroundCenter(const string& s, int left, int right) {
    while (left >= 0 && right < (int)s.size() && s[left] == s[right]) {
        left--; right++;
    }
    return right - left - 1; // length of palindrome
}

// LC 5: Longest Palindromic Substring
string longestPalindrome(string s) {
    if (s.empty()) return "";
    int start = 0, maxLen = 1;

    for (int i = 0; i < (int)s.size(); i++) {
        int len1 = expandAroundCenter(s, i, i);     // Odd length
        int len2 = expandAroundCenter(s, i, i + 1);  // Even length
        int len = max(len1, len2);

        if (len > maxLen) {
            maxLen = len;
            start = i - (len - 1) / 2;
        }
    }
    return s.substr(start, maxLen);
}

// LC 647: Count Palindromic Substrings
int countSubstrings(string s) {
    int count = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        // Odd length palindromes
        int left = i, right = i;
        while (left >= 0 && right < (int)s.size() && s[left] == s[right]) {
            count++;
            left--; right++;
        }
        // Even length palindromes
        left = i; right = i + 1;
        while (left >= 0 && right < (int)s.size() && s[left] == s[right]) {
            count++;
            left--; right++;
        }
    }
    return count;
}

int main() {
    cout << "Longest palindrome of 'babad': " << longestPalindrome("babad") << "\n";
    cout << "Count palindromic substrings of 'abc': " << countSubstrings("abc") << "\n";   // 3
    cout << "Count palindromic substrings of 'aaa': " << countSubstrings("aaa") << "\n";   // 6
    return 0;
}

