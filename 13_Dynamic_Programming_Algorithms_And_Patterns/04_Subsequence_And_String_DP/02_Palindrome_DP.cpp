/*
 * ============================================================================
 *             PALINDROME DP — SUBSEQUENCE & SUBSTRING
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Subsequence DP — Palindrome Problems
 * Level   : ⭐⭐ Intermediate
 * ============================================================================
 *
 * 1. Longest Palindromic Subsequence (LeetCode 516)
 *    dp[i][j] = LPS of s[i..j]
 *    Key insight: LPS(s) = LCS(s, reverse(s))
 *
 * 2. Longest Palindromic Substring (LeetCode 5)
 *    dp[i][j] = true if s[i..j] is palindrome
 *
 * 3. Palindrome Partitioning (LeetCode 132)
 *    dp[i] = min cuts to make s[0..i] all palindromes
 *
 * 4. Min insertions to make palindrome
 *    = n - LPS length
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// Longest Palindromic Subsequence — O(n²) time, O(n) space
int longestPalinSubseq(string& s) {
    int n = s.size();
    vector<int> dp(n, 0), prev(n, 0);

    for (int i = n - 1; i >= 0; i--) {
        dp[i] = 1;  // Single char is palindrome
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[j])
                dp[j] = prev[j-1] + 2;
            else
                dp[j] = max(prev[j], dp[j-1]);
        }
        swap(dp, prev);
    }
    return prev[n-1];
}

// Longest Palindromic Substring — O(n²) time
// Expand around center approach (more efficient than DP)
string longestPalinSubstring(string& s) {
    int n = s.size(), maxLen = 0, start = 0;

    auto expand = [&](int l, int r) {
        while (l >= 0 && r < n && s[l] == s[r]) { l--; r++; }
        if (r - l - 1 > maxLen) {
            maxLen = r - l - 1;
            start = l + 1;
        }
    };

    for (int i = 0; i < n; i++) {
        expand(i, i);      // Odd length
        expand(i, i + 1);  // Even length
    }
    return s.substr(start, maxLen);
}

// DP approach for Longest Palindromic Substring
string longestPalinSubstringDP(string& s) {
    int n = s.size();
    if (n <= 1) return s;

    vector<vector<bool>> dp(n, vector<bool>(n, false));
    int maxLen = 1, start = 0;

    // All single chars are palindromes
    for (int i = 0; i < n; i++) dp[i][i] = true;

    // Check length 2
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i+1]) {
            dp[i][i+1] = true;
            start = i; maxLen = 2;
        }
    }

    // Check length 3 to n
    for (int len = 3; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j] && dp[i+1][j-1]) {
                dp[i][j] = true;
                if (len > maxLen) {
                    start = i;
                    maxLen = len;
                }
            }
        }
    }
    return s.substr(start, maxLen);
}

// Palindrome Partitioning II — Min Cuts (LeetCode 132)
int minCutPalindrome(string& s) {
    int n = s.size();
    vector<vector<bool>> isPalin(n, vector<bool>(n, false));

    // Precompute palindrome table
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i; j < n; j++) {
            if (s[i] == s[j] && (j - i <= 2 || isPalin[i+1][j-1]))
                isPalin[i][j] = true;
        }
    }

    // dp[i] = min cuts for s[0..i]
    vector<int> dp(n, 0);
    for (int i = 0; i < n; i++) {
        if (isPalin[0][i]) {
            dp[i] = 0;  // Whole prefix is palindrome
        } else {
            dp[i] = i;  // Worst case: cut every character
            for (int j = 1; j <= i; j++) {
                if (isPalin[j][i]) {
                    dp[i] = min(dp[i], dp[j-1] + 1);
                }
            }
        }
    }
    return dp[n-1];
}

// Min insertions to make string palindrome
int minInsertionsPalindrome(string& s) {
    // Answer = n - LPS(s)
    return s.size() - longestPalinSubseq(s);
}

// Count palindromic substrings (LeetCode 647)
int countPalindromicSubstrings(string& s) {
    int n = s.size(), count = 0;

    auto expand = [&](int l, int r) {
        while (l >= 0 && r < n && s[l] == s[r]) {
            count++;
            l--; r++;
        }
    };

    for (int i = 0; i < n; i++) {
        expand(i, i);
        expand(i, i + 1);
    }
    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== PALINDROME DP ===" << endl;

    string s1 = "bbbab";
    cout << "\n--- Longest Palindromic Subsequence ---" << endl;
    cout << "s=\"" << s1 << "\" → LPS length: " << longestPalinSubseq(s1) << endl;
    // "bbbb" → 4

    string s2 = "babad";
    cout << "\n--- Longest Palindromic Substring ---" << endl;
    cout << "s=\"" << s2 << "\" → \"" << longestPalinSubstring(s2) << "\"" << endl;
    cout << "DP approach: \"" << longestPalinSubstringDP(s2) << "\"" << endl;

    string s3 = "aab";
    cout << "\n--- Palindrome Partitioning (Min Cuts) ---" << endl;
    cout << "s=\"" << s3 << "\" → " << minCutPalindrome(s3) << " cuts" << endl;
    // "aa" | "b" → 1 cut

    string s4 = "abcd";
    cout << "\n--- Min Insertions for Palindrome ---" << endl;
    cout << "s=\"" << s4 << "\" → " << minInsertionsPalindrome(s4) << " insertions" << endl;

    string s5 = "abc";
    cout << "\n--- Count Palindromic Substrings ---" << endl;
    cout << "s=\"" << s5 << "\" → " << countPalindromicSubstrings(s5) << " palindromes" << endl;
    // "a", "b", "c" → 3

    return 0;
}

