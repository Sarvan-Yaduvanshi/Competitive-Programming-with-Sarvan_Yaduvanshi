/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Lexicographic Greedy Technique
 *  Level   : Advanced
 * ============================================================================
 *
 *  ▶ CORE IDEA: To build the lexicographically smallest (or largest) string:
 *  At each position, pick the smallest (or largest) character that still allows
 *  a valid solution for the remaining positions.
 *
 *  ▶ COMMON PROBLEMS:
 *  1. Smallest String with Numeric Value (LC 1663)
 *  2. Remove Duplicate Letters / Smallest Subsequence (LC 316/1081)
 *  3. Construct smallest number from digit pattern
 *
 *  ▶ KEY TECHNIQUE:
 *  Use a STACK to greedily build the result:
 *  - Before pushing a character, pop larger characters if we can still add them later
 *  - This ensures the smallest possible prefix at each step
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

// ============================================================================
// LC 1663: Smallest String With A Given Numeric Value
// String of length n with value k (a=1, b=2, ..., z=26)
// ============================================================================
string getSmallestString(int n, int k) {
    string result(n, 'a');
    k -= n; // After filling all 'a's, distribute remaining value

    // Fill from the end with largest possible characters
    for (int i = n - 1; i >= 0 && k > 0; i--) {
        int add = min(25, k); // At most 'z' - 'a' = 25 more
        result[i] += add;
        k -= add;
    }
    return result;
}

// ============================================================================
// LC 316 / LC 1081: Remove Duplicate Letters (Smallest Subsequence)
// Remove duplicates such that result is lexicographically smallest
// ============================================================================
string removeDuplicateLetters(string s) {
    vector<int> lastIndex(26, 0);  // Last occurrence of each char
    vector<bool> inStack(26, false);

    for (int i = 0; i < (int)s.size(); i++)
        lastIndex[s[i] - 'a'] = i;

    string stack_str;
    for (int i = 0; i < (int)s.size(); i++) {
        int c = s[i] - 'a';
        if (inStack[c]) continue; // Already in result

        // Pop larger characters if they appear later
        while (!stack_str.empty() && stack_str.back() > s[i]
               && lastIndex[stack_str.back() - 'a'] > i) {
            inStack[stack_str.back() - 'a'] = false;
            stack_str.pop_back();
        }

        stack_str.push_back(s[i]);
        inStack[c] = true;
    }
    return stack_str;
}

// ============================================================================
// Build Lexicographically Smallest String by Appending or Prepending
// At each step, compare remaining string with its reverse to decide
// ============================================================================
string smallestByAppendPrepend(string s) {
    int left = 0, right = (int)s.size() - 1;
    string result;

    while (left <= right) {
        if (s[left] < s[right]) {
            result += s[left++];
        } else if (s[right] < s[left]) {
            result += s[right--];
        } else {
            // Equal: look ahead to break tie
            int l = left, r = right;
            while (l < r && s[l] == s[r]) { l++; r--; }
            if (l >= r || s[l] < s[r]) result += s[left++];
            else result += s[right--];
        }
    }
    return result;
}

int main() {
    // LC 1663
    cout << "Smallest string (3, 27): " << getSmallestString(3, 27) << endl; // "aay"

    // LC 316
    cout << "Remove dups 'bcabc': " << removeDuplicateLetters("bcabc") << endl; // "abc"
    cout << "Remove dups 'cbacdcbc': " << removeDuplicateLetters("cbacdcbc") << endl; // "acdb"

    return 0;
}

