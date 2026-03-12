/*
 * ============================================================================
 *           WILDCARD & REGEX MATCHING DP
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Subsequence DP — Wildcard Matching, Regex Matching
 * Level   : ⭐⭐⭐ Advanced
 * ============================================================================
 *
 * WILDCARD MATCHING (LeetCode 44):
 *   '?' matches single char, '*' matches any sequence (including empty)
 *   dp[i][j] = does pattern[0..i-1] match string[0..j-1]?
 *
 * REGEX MATCHING (LeetCode 10):
 *   '.' matches single char, 'x*' matches zero or more of 'x'
 *   dp[i][j] = does pattern[0..i-1] match string[0..j-1]?
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// Wildcard Matching (LeetCode 44)
bool wildcardMatch(string& s, string& p) {
    int n = s.size(), m = p.size();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;

    // Pattern starts with *s — they can match empty string
    for (int i = 1; i <= m; i++) {
        if (p[i-1] == '*') dp[i][0] = dp[i-1][0];
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[i-1] == s[j-1] || p[i-1] == '?') {
                dp[i][j] = dp[i-1][j-1];
            } else if (p[i-1] == '*') {
                dp[i][j] = dp[i-1][j]      // * matches empty
                         || dp[i][j-1];     // * matches s[j-1] and more
            }
        }
    }
    return dp[m][n];
}

// Wildcard Matching — Space Optimized
bool wildcardMatchOpt(string& s, string& p) {
    int n = s.size(), m = p.size();
    vector<bool> prev(n + 1, false), curr(n + 1, false);
    prev[0] = true;

    for (int i = 1; i <= m; i++) {
        curr[0] = (p[i-1] == '*') ? prev[0] : false;
        for (int j = 1; j <= n; j++) {
            if (p[i-1] == s[j-1] || p[i-1] == '?')
                curr[j] = prev[j-1];
            else if (p[i-1] == '*')
                curr[j] = prev[j] || curr[j-1];
            else
                curr[j] = false;
        }
        swap(prev, curr);
        fill(curr.begin(), curr.end(), false);
    }
    return prev[n];
}

// Regular Expression Matching (LeetCode 10)
bool regexMatch(string& s, string& p) {
    int n = s.size(), m = p.size();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;

    // Handle patterns like a*, a*b*, a*b*c* that can match empty
    for (int i = 2; i <= m; i++) {
        if (p[i-1] == '*') dp[i][0] = dp[i-2][0];
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[i-1] == s[j-1] || p[i-1] == '.') {
                dp[i][j] = dp[i-1][j-1];
            } else if (p[i-1] == '*') {
                // '*' with preceding element p[i-2]
                dp[i][j] = dp[i-2][j];  // Zero occurrences

                if (p[i-2] == s[j-1] || p[i-2] == '.') {
                    dp[i][j] = dp[i][j] || dp[i][j-1];  // One or more
                }
            }
        }
    }
    return dp[m][n];
}

/*
 * DRY RUN — Wildcard Matching:
 * s = "adceb", p = "*a*b"
 *
 *     ""  a  d  c  e  b
 * ""   T  F  F  F  F  F
 * *    T  T  T  T  T  T
 * a    F  T  F  F  F  F
 * *    F  T  T  T  T  T
 * b    F  F  F  F  F  T  ← Answer: TRUE
 *
 * DRY RUN — Regex Matching:
 * s = "aab", p = "c*a*b"
 *
 *      ""  a  a  b
 * ""    T  F  F  F
 * c     F  F  F  F
 * *     T  F  F  F    (c* matches empty)
 * a     F  T  F  F
 * *     T  T  T  F    (a* matches 0,1,2 a's)
 * b     F  F  F  T    ← Answer: TRUE
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== WILDCARD & REGEX MATCHING ===" << endl;

    // Wildcard
    string s1 = "adceb", p1 = "*a*b";
    cout << "\n--- Wildcard Matching ---" << endl;
    cout << "s=\"" << s1 << "\", p=\"" << p1 << "\"" << endl;
    cout << "Match: " << (wildcardMatch(s1, p1) ? "YES" : "NO") << endl;

    string s2 = "acdcb", p2 = "a*c?b";
    cout << "s=\"" << s2 << "\", p=\"" << p2 << "\"" << endl;
    cout << "Match: " << (wildcardMatch(s2, p2) ? "YES" : "NO") << endl;

    // Regex
    string s3 = "aab", p3 = "c*a*b";
    cout << "\n--- Regex Matching ---" << endl;
    cout << "s=\"" << s3 << "\", p=\"" << p3 << "\"" << endl;
    cout << "Match: " << (regexMatch(s3, p3) ? "YES" : "NO") << endl;

    string s4 = "mississippi", p4 = "mis*is*p*.";
    cout << "s=\"" << s4 << "\", p=\"" << p4 << "\"" << endl;
    cout << "Match: " << (regexMatch(s4, p4) ? "YES" : "NO") << endl;

    return 0;
}

