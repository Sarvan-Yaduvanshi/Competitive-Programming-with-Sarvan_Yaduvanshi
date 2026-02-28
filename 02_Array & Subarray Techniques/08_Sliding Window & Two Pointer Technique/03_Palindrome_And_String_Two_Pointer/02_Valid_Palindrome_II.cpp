/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Valid Palindrome II (LC 680) — Can remove at most 1 character
 *  Level   : Easy
 *  Link    : https://leetcode.com/problems/valid-palindrome-ii/
 * ============================================================================
 *
 *  On mismatch: try skipping left OR skipping right.
 *  If either produces a palindrome, return true.
 *  Time: O(N), Space: O(1)
 * ============================================================================
 */
#include <iostream>
#include <string>
using namespace std;

bool isPalinRange(const string& s, int lo, int hi) {
    while (lo < hi) {
        if (s[lo] != s[hi]) return false;
        lo++; hi--;
    }
    return true;
}

bool validPalindrome(string s) {
    int left = 0, right = (int)s.size() - 1;
    while (left < right) {
        if (s[left] != s[right]) {
            return isPalinRange(s, left + 1, right) || isPalinRange(s, left, right - 1);
        }
        left++; right--;
    }
    return true;
}

int main() {
    cout << validPalindrome("aba") << "\n";   // 1
    cout << validPalindrome("abca") << "\n";  // 1 (remove 'c' or 'b')
    cout << validPalindrome("abc") << "\n";   // 0
    return 0;
}

