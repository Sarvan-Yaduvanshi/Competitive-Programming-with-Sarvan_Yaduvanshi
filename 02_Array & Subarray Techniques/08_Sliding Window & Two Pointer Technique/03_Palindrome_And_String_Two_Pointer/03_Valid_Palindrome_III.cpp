/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Valid Palindrome III (LC 1216) — Remove at most K characters
 *  Level   : Hard
 *  Link    : https://leetcode.com/problems/valid-palindrome-iii/
 * ============================================================================
 *
 *  This is where Two Pointer meets DP!
 *  Check if string can become palindrome by removing at most k characters.
 *  Equivalent to: len(s) - LPS(s) <= k, where LPS = Longest Palindromic Subsequence.
 *
 *  LPS(s) = LCS(s, reverse(s))
 *  Time: O(N²), Space: O(N)
 * ============================================================================
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Longest Palindromic Subsequence via LCS(s, reverse(s))
int longestPalindromicSubseq(const string& s) {
    int n = s.size();
    string t = string(s.rbegin(), s.rend());
    vector<int> prev(n + 1, 0), curr(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i-1] == t[j-1])
                curr[j] = prev[j-1] + 1;
            else
                curr[j] = max(prev[j], curr[j-1]);
        }
        swap(prev, curr);
    }
    return prev[n];
}

bool isValidPalindrome(string s, int k) {
    int lps = longestPalindromicSubseq(s);
    return (int)s.size() - lps <= k;
}

int main() {
    cout << isValidPalindrome("abcdeca", 2) << "\n"; // 1 (remove 'b' and 'e')
    cout << isValidPalindrome("abbababa", 1) << "\n"; // 1
    return 0;
}

