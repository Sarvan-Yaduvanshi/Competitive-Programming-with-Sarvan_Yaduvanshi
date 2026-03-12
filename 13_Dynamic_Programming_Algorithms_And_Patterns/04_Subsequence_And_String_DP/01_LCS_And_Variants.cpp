/*
 * ============================================================================
 *           LONGEST COMMON SUBSEQUENCE (LCS) & VARIANTS
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Subsequence DP — LCS, LCS Variants, Shortest Common Supersequence
 * Level   : ⭐⭐ Intermediate
 * ============================================================================
 *
 * LCS (LeetCode 1143):
 *   dp[i][j] = LCS length of s1[0..i-1] and s2[0..j-1]
 *   if s1[i-1]==s2[j-1]: dp[i][j] = dp[i-1][j-1] + 1
 *   else: dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 *
 * VARIANTS:
 * - Print LCS string
 * - Longest Common Substring (contiguous)
 * - Shortest Common Supersequence
 * - Minimum deletions to make strings equal
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// LCS Length — O(n*m) time, O(m) space
int lcsLength(string& s1, string& s2) {
    int n = s1.size(), m = s2.size();
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i-1] == s2[j-1])
                curr[j] = prev[j-1] + 1;
            else
                curr[j] = max(prev[j], curr[j-1]);
        }
        swap(prev, curr);
        fill(curr.begin(), curr.end(), 0);
    }
    return prev[m];
}

// Print LCS String — need full table for backtracking
string printLCS(string& s1, string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = (s1[i-1] == s2[j-1]) ? dp[i-1][j-1] + 1
                                               : max(dp[i-1][j], dp[i][j-1]);

    // Backtrack to build LCS string
    string lcs;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s1[i-1] == s2[j-1]) {
            lcs += s1[i-1];
            i--; j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    reverse(lcs.begin(), lcs.end());
    return lcs;
}

// Longest Common Substring (contiguous) — O(n*m) time, O(m) space
int longestCommonSubstring(string& s1, string& s2) {
    int n = s1.size(), m = s2.size();
    int maxLen = 0;
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i-1] == s2[j-1]) {
                curr[j] = prev[j-1] + 1;
                maxLen = max(maxLen, curr[j]);
            } else {
                curr[j] = 0;  // Must be contiguous!
            }
        }
        swap(prev, curr);
        fill(curr.begin(), curr.end(), 0);
    }
    return maxLen;
}

// Shortest Common Supersequence (LeetCode 1092)
string shortestCommonSupersequence(string& s1, string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = (s1[i-1] == s2[j-1]) ? dp[i-1][j-1] + 1
                                               : max(dp[i-1][j], dp[i][j-1]);

    // Build SCS by backtracking through LCS table
    string result;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s1[i-1] == s2[j-1]) {
            result += s1[i-1];
            i--; j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            result += s1[i-1];
            i--;
        } else {
            result += s2[j-1];
            j--;
        }
    }
    while (i > 0) result += s1[--i];
    while (j > 0) result += s2[--j];

    reverse(result.begin(), result.end());
    return result;
}

// Minimum deletions to make strings equal = n + m - 2*LCS
int minDeletions(string& s1, string& s2) {
    int lcs = lcsLength(s1, s2);
    return s1.size() + s2.size() - 2 * lcs;
}

// Minimum insertions + deletions to convert s1 → s2
pair<int,int> minInsertDelete(string& s1, string& s2) {
    int lcs = lcsLength(s1, s2);
    int deletions = s1.size() - lcs;
    int insertions = s2.size() - lcs;
    return {insertions, deletions};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== LCS & VARIANTS ===" << endl;

    string s1 = "abcde", s2 = "ace";
    cout << "\ns1=\"" << s1 << "\", s2=\"" << s2 << "\"" << endl;
    cout << "LCS length: " << lcsLength(s1, s2) << endl;
    cout << "LCS string: " << printLCS(s1, s2) << endl;

    string a = "abcdef", b = "zbcdf";
    cout << "\na=\"" << a << "\", b=\"" << b << "\"" << endl;
    cout << "LCS: " << printLCS(a, b) << endl;
    cout << "Longest Common Substring: " << longestCommonSubstring(a, b) << endl;
    cout << "Min deletions to equalize: " << minDeletions(a, b) << endl;
    auto [ins, del] = minInsertDelete(a, b);
    cout << "Min insert=" << ins << ", delete=" << del << " to convert" << endl;

    string x = "abac", y = "cab";
    cout << "\nx=\"" << x << "\", y=\"" << y << "\"" << endl;
    cout << "Shortest Common Supersequence: " << shortestCommonSupersequence(x, y) << endl;

    return 0;
}

