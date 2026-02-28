/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Valid Palindrome (LC 125)
 *  Level   : Easy
 *  Link    : https://leetcode.com/problems/valid-palindrome/
 * ============================================================================
 *
 *  Check if string is palindrome — only considering alphanumeric characters,
 *  ignoring cases. Two pointer from both ends, skip non-alphanumeric.
 *
 *  Time: O(N), Space: O(1)
 * ============================================================================
 */
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isPalindrome(string s) {
    int left = 0, right = (int)s.size() - 1;
    while (left < right) {
        while (left < right && !isalnum(s[left])) left++;
        while (left < right && !isalnum(s[right])) right--;
        if (tolower(s[left]) != tolower(s[right])) return false;
        left++; right--;
    }
    return true;
}

int main() {
    cout << isPalindrome("A man, a plan, a canal: Panama") << "\n"; // 1
    cout << isPalindrome("race a car") << "\n"; // 0
    return 0;
}

