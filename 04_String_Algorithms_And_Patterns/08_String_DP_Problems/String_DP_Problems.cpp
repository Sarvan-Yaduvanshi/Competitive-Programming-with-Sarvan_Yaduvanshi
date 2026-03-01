/*
╔══════════════════════════════════════════════════════════════════════════════╗
║     CHAPTER 08 — STRING DP PROBLEMS                                       ║
║     From Zero to Grandmaster — Dynamic Programming on Strings              ║
║     Author: Sarvan Yaduvanshi                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Edit Distance (Levenshtein Distance)
 2. Longest Common Subsequence (LCS)
 3. Longest Common Substring
 4. Longest Palindromic Subsequence
 5. Distinct Subsequences
 6. Wildcard Matching
 7. Regular Expression Matching

CORE THEORY — STRING DP:
─────────────────────────
 String DP typically involves two strings (or a string against itself).
 State: dp[i][j] = answer considering first i chars of s1 and first j chars of s2.

 COMMON PATTERNS:
   • Match/mismatch at current characters → different transitions
   • "Take" or "skip" current character
   • Three operations: insert, delete, replace (edit distance)

 SPACE OPTIMIZATION:
   Many 2D string DPs only look at dp[i-1][...] → can use 1D rolling array.
   Reduces O(nm) space to O(min(n,m)).

 TIME COMPLEXITY:
   Most string DPs: O(n * m) where n, m = string lengths
   Cannot do better for general case (SETH hypothesis).
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;
using i64 = long long;

// ═══════════════════════════════════════════════════════════════
// PROBLEM 1: EDIT DISTANCE (Levenshtein Distance)
// ═══════════════════════════════════════════════════════════════
/*
 DEFINITION:
 ──────────
 Minimum number of operations to convert s1 into s2.
 Operations: Insert, Delete, Replace (each costs 1)

 RECURRENCE:
   dp[i][j] = minimum edits to convert s1[0..i-1] to s2[0..j-1]

   If s1[i-1] == s2[j-1]:
     dp[i][j] = dp[i-1][j-1]  (no operation needed)
   Else:
     dp[i][j] = 1 + min(
       dp[i-1][j-1],  // Replace s1[i-1] with s2[j-1]
       dp[i-1][j],    // Delete s1[i-1]
       dp[i][j-1]     // Insert s2[j-1]
     )

   Base cases:
     dp[i][0] = i  (delete all chars from s1)
     dp[0][j] = j  (insert all chars from s2)

 Time: O(n*m), Space: O(n*m) or O(m) with optimization
*/

// 2D DP — O(n*m) time, O(n*m) space
int editDistance2D(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    // Base cases
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;

    // Fill DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({dp[i - 1][j - 1],  // replace
                                     dp[i - 1][j],       // delete
                                     dp[i][j - 1]});     // insert
            }
        }
    }
    return dp[n][m];
}

// Space-optimized — O(n*m) time, O(m) space
int editDistanceOptimized(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<int> prev(m + 1), curr(m + 1);

    for (int j = 0; j <= m; j++) prev[j] = j;

    for (int i = 1; i <= n; i++) {
        curr[0] = i;
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                curr[j] = prev[j - 1];
            } else {
                curr[j] = 1 + min({prev[j - 1], prev[j], curr[j - 1]});
            }
        }
        swap(prev, curr);
    }
    return prev[m];
}

// Reconstruct the operations
string reconstructEdit(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = (s1[i-1] == s2[j-1]) ? dp[i-1][j-1] :
                        1 + min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]});

    // Backtrack
    string ops;
    int i = n, j = m;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && s1[i-1] == s2[j-1]) {
            ops = "MATCH " + string(1, s1[i-1]) + "\n" + ops;
            i--; j--;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i-1][j-1] + 1) {
            ops = "REPLACE " + string(1, s1[i-1]) + " → " + string(1, s2[j-1]) + "\n" + ops;
            i--; j--;
        } else if (i > 0 && dp[i][j] == dp[i-1][j] + 1) {
            ops = "DELETE " + string(1, s1[i-1]) + "\n" + ops;
            i--;
        } else {
            ops = "INSERT " + string(1, s2[j-1]) + "\n" + ops;
            j--;
        }
    }
    return ops;
}

void demo_edit_distance() {
    cout << "=== PROBLEM 1: EDIT DISTANCE ===" << endl;
    cout << "horse → ros: " << editDistance2D("horse", "ros") << endl;  // 3
    cout << "intention → execution: " << editDistanceOptimized("intention", "execution") << endl;  // 5
    cout << "abc → abc: " << editDistance2D("abc", "abc") << endl;  // 0
    cout << "'' → abc: " << editDistance2D("", "abc") << endl;      // 3
    cout << "\nOperations for horse → ros:" << endl;
    cout << reconstructEdit("horse", "ros");
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 2: LONGEST COMMON SUBSEQUENCE (LCS)
// ═══════════════════════════════════════════════════════════════
/*
 DEFINITION:
 ──────────
 Find the longest subsequence present in both strings.
 Subsequence = characters in order, but not necessarily contiguous.

 Example: "abcde" and "ace" → LCS = "ace" (length 3)

 RECURRENCE:
   dp[i][j] = LCS length of s1[0..i-1] and s2[0..j-1]

   If s1[i-1] == s2[j-1]:
     dp[i][j] = dp[i-1][j-1] + 1
   Else:
     dp[i][j] = max(dp[i-1][j], dp[i][j-1])

 Time: O(n*m), Space: O(n*m) or O(m)
*/

int lcsLength(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

// Reconstruct LCS string
string lcsString(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = (s1[i-1] == s2[j-1]) ? dp[i-1][j-1] + 1 : max(dp[i-1][j], dp[i][j-1]);

    // Backtrack
    string result;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            result = s1[i - 1] + result;
            i--; j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    return result;
}

// Space-optimized LCS (only length, not reconstruction)
int lcsOptimized(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    if (n < m) return lcsOptimized(s2, s1);  // ensure m is smaller for space
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1])
                curr[j] = prev[j - 1] + 1;
            else
                curr[j] = max(prev[j], curr[j - 1]);
        }
        swap(prev, curr);
        fill(curr.begin(), curr.end(), 0);
    }
    return prev[m];
}

// Shortest Common Supersequence (uses LCS)
string shortestCommonSupersequence(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = (s1[i-1] == s2[j-1]) ? dp[i-1][j-1] + 1 : max(dp[i-1][j], dp[i][j-1]);

    string result;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s1[i-1] == s2[j-1]) {
            result = s1[i-1] + result;
            i--; j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            result = s1[i-1] + result;
            i--;
        } else {
            result = s2[j-1] + result;
            j--;
        }
    }
    while (i > 0) result = s1[--i] + result;
    while (j > 0) result = s2[--j] + result;
    return result;
}

void demo_lcs() {
    cout << "\n=== PROBLEM 2: LONGEST COMMON SUBSEQUENCE ===" << endl;
    cout << "LCS length(abcde, ace): " << lcsLength("abcde", "ace") << endl;  // 3
    cout << "LCS string(abcde, ace): " << lcsString("abcde", "ace") << endl;  // ace
    cout << "LCS optimized(abcde, ace): " << lcsOptimized("abcde", "ace") << endl;
    cout << "SCS(abac, cab): " << shortestCommonSupersequence("abac", "cab") << endl;
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 3: LONGEST COMMON SUBSTRING
// ═══════════════════════════════════════════════════════════════
/*
 DEFINITION:
 ──────────
 Find the longest CONTIGUOUS sequence present in both strings.
 (Different from LCS: substring must be contiguous!)

 RECURRENCE:
   dp[i][j] = length of longest common substring ending at s1[i-1] and s2[j-1]

   If s1[i-1] == s2[j-1]:
     dp[i][j] = dp[i-1][j-1] + 1
   Else:
     dp[i][j] = 0  (must be contiguous!)

   Answer = max of all dp[i][j]

 Time: O(n*m), Space: O(n*m) or O(m) with 1D optimization
 Also solvable in O((n+m) log(min(n,m))) with hashing (Chapter 04)
*/

pair<int, string> longestCommonSubstring(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    int maxLen = 0, endIdx = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLen) {
                    maxLen = dp[i][j];
                    endIdx = i;
                }
            }
            // else dp[i][j] = 0 (already initialized)
        }
    }
    return {maxLen, s1.substr(endIdx - maxLen, maxLen)};
}

void demo_common_substring() {
    cout << "\n=== PROBLEM 3: LONGEST COMMON SUBSTRING ===" << endl;
    auto [len, str] = longestCommonSubstring("abcdef", "xbcdyz");
    cout << "LCSubstr(abcdef, xbcdyz): " << str << " (len=" << len << ")" << endl;
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 4: LONGEST PALINDROMIC SUBSEQUENCE
// ═══════════════════════════════════════════════════════════════
/*
 DEFINITION:
 ──────────
 Find the longest subsequence of s that is a palindrome.

 KEY INSIGHT: LPS(s) = LCS(s, reverse(s))

 ALTERNATIVE DP:
   dp[i][j] = length of longest palindromic subsequence in s[i..j]

   If s[i] == s[j]:
     dp[i][j] = dp[i+1][j-1] + 2
   Else:
     dp[i][j] = max(dp[i+1][j], dp[i][j-1])

   Base: dp[i][i] = 1

 Time: O(n²), Space: O(n²) or O(n)

 RELATED: Minimum deletions to make palindrome = n - LPS(s)
*/

int longestPalindromicSubseq(const string& s) {
    int n = s.size();
    // dp[i][j] = LPS length of s[i..j]
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Base case: single characters
    for (int i = 0; i < n; i++) dp[i][i] = 1;

    // Fill for increasing lengths
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[0][n - 1];
}

// Space-optimized using LCS approach
int longestPalindromicSubseqOptimized(const string& s) {
    string rev(s.rbegin(), s.rend());
    int n = s.size();
    vector<int> prev(n + 1, 0), curr(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i - 1] == rev[j - 1])
                curr[j] = prev[j - 1] + 1;
            else
                curr[j] = max(prev[j], curr[j - 1]);
        }
        swap(prev, curr);
        fill(curr.begin(), curr.end(), 0);
    }
    return prev[n];
}

// Minimum insertions to make palindrome = n - LPS
int minInsertionsPalindrome(const string& s) {
    return s.size() - longestPalindromicSubseq(s);
}

void demo_palindromic_subseq() {
    cout << "\n=== PROBLEM 4: LONGEST PALINDROMIC SUBSEQUENCE ===" << endl;
    cout << "LPS(bbbab): " << longestPalindromicSubseq("bbbab") << endl;  // 4 (bbbb)
    cout << "LPS(cbbd): " << longestPalindromicSubseq("cbbd") << endl;    // 2 (bb)
    cout << "LPS optimized(bbbab): " << longestPalindromicSubseqOptimized("bbbab") << endl;
    cout << "Min insertions for 'abcd': " << minInsertionsPalindrome("abcd") << endl;  // 3
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 5: DISTINCT SUBSEQUENCES
// ═══════════════════════════════════════════════════════════════
/*
 DEFINITION:
 ──────────
 Count the number of distinct subsequences of s that equal t.
 i.e., how many ways can we pick characters from s (in order) to form t?

 Example: s = "rabbbit", t = "rabbit" → 3

 RECURRENCE:
   dp[i][j] = number of ways to form t[0..j-1] using s[0..i-1]

   If s[i-1] == t[j-1]:
     dp[i][j] = dp[i-1][j-1] + dp[i-1][j]
                 (use s[i-1])  + (skip s[i-1])
   Else:
     dp[i][j] = dp[i-1][j]   (skip s[i-1])

   Base: dp[i][0] = 1 (empty t is subsequence of anything)
         dp[0][j] = 0 for j > 0

 Time: O(n*m), Space: O(n*m) or O(m)
*/

int distinctSubsequences(const string& s, const string& t) {
    int n = s.size(), m = t.size();
    // Use long long to handle large counts
    vector<vector<i64>> dp(n + 1, vector<i64>(m + 1, 0));

    // Base case: empty t
    for (int i = 0; i <= n; i++) dp[i][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = dp[i - 1][j];  // skip s[i-1]
            if (s[i - 1] == t[j - 1]) {
                dp[i][j] += dp[i - 1][j - 1];  // use s[i-1]
            }
        }
    }
    return dp[n][m];
}

// Space-optimized
i64 distinctSubseqOptimized(const string& s, const string& t) {
    int m = t.size();
    vector<i64> dp(m + 1, 0);
    dp[0] = 1;

    for (char c : s) {
        // Traverse RIGHT to LEFT to avoid using updated values
        for (int j = m; j >= 1; j--) {
            if (c == t[j - 1]) {
                dp[j] += dp[j - 1];
            }
        }
    }
    return dp[m];
}

void demo_distinct_subseq() {
    cout << "\n=== PROBLEM 5: DISTINCT SUBSEQUENCES ===" << endl;
    cout << "rabbbit → rabbit: " << distinctSubsequences("rabbbit", "rabbit") << endl;  // 3
    cout << "babgbag → bag: " << distinctSubsequences("babgbag", "bag") << endl;        // 5
    cout << "optimized: " << distinctSubseqOptimized("babgbag", "bag") << endl;
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 6: WILDCARD MATCHING
// ═══════════════════════════════════════════════════════════════
/*
 DEFINITION:
 ──────────
 Pattern p with wildcards: '?' matches any single char, '*' matches any sequence.
 Does pattern p match entire string s?

 Example: s = "adceb", p = "*a*b" → true
          s = "acdcb", p = "a*c?b" → false

 RECURRENCE:
   dp[i][j] = does s[0..i-1] match p[0..j-1]?

   If p[j-1] == '*':
     dp[i][j] = dp[i-1][j] || dp[i][j-1]
                 (* matches current char and more)  ||  (* matches empty)
   Else if p[j-1] == '?' || p[j-1] == s[i-1]:
     dp[i][j] = dp[i-1][j-1]
   Else:
     dp[i][j] = false

   Base:
     dp[0][0] = true
     dp[0][j] = dp[0][j-1] && p[j-1] == '*'

 Time: O(n*m), Space: O(n*m) or O(m)
*/

bool wildcardMatch(const string& s, const string& p) {
    int n = s.size(), m = p.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    dp[0][0] = true;

    // Base: pattern of only '*' can match empty string
    for (int j = 1; j <= m; j++) {
        dp[0][j] = dp[0][j - 1] && p[j - 1] == '*';
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (p[j - 1] == '*') {
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            } else if (p[j - 1] == '?' || p[j - 1] == s[i - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
        }
    }
    return dp[n][m];
}

// Space-optimized wildcard matching
bool wildcardMatchOptimized(const string& s, const string& p) {
    int n = s.size(), m = p.size();
    vector<bool> prev(m + 1, false), curr(m + 1, false);
    prev[0] = true;
    for (int j = 1; j <= m; j++) prev[j] = prev[j - 1] && p[j - 1] == '*';

    for (int i = 1; i <= n; i++) {
        curr[0] = false;
        for (int j = 1; j <= m; j++) {
            if (p[j - 1] == '*')
                curr[j] = prev[j] || curr[j - 1];
            else if (p[j - 1] == '?' || p[j - 1] == s[i - 1])
                curr[j] = prev[j - 1];
            else
                curr[j] = false;
        }
        swap(prev, curr);
    }
    return prev[m];
}

void demo_wildcard() {
    cout << "\n=== PROBLEM 6: WILDCARD MATCHING ===" << endl;
    cout << "adceb, *a*b: " << wildcardMatch("adceb", "*a*b") << endl;     // 1
    cout << "acdcb, a*c?b: " << wildcardMatch("acdcb", "a*c?b") << endl;  // 0
    cout << "cb, ?a: " << wildcardMatch("cb", "?a") << endl;              // 0
    cout << "'', *: " << wildcardMatch("", "*") << endl;                   // 1
    cout << "optimized: " << wildcardMatchOptimized("adceb", "*a*b") << endl;
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 7: REGULAR EXPRESSION MATCHING
// ═══════════════════════════════════════════════════════════════
/*
 DEFINITION:
 ──────────
 Pattern with '.' (matches any single char) and '*' (zero or more of preceding char).
 Note: '*' here is Kleene star, different from wildcard '*'!

 Examples:
   s = "aa", p = "a*" → true  (a* = one or more a's)
   s = "ab", p = ".*" → true  (.* = zero or more of any char)
   s = "aab", p = "c*a*b" → true (c* = zero c's, a* = two a's, b)

 RECURRENCE:
   dp[i][j] = does s[0..i-1] match p[0..j-1]?

   If p[j-1] == '*':
     // Option 1: zero occurrences of p[j-2]
     dp[i][j] = dp[i][j-2]
     // Option 2: one more occurrence (if p[j-2] matches s[i-1])
     If p[j-2] == '.' || p[j-2] == s[i-1]:
       dp[i][j] |= dp[i-1][j]

   Else if p[j-1] == '.' || p[j-1] == s[i-1]:
     dp[i][j] = dp[i-1][j-1]

   Else:
     dp[i][j] = false

 Time: O(n*m), Space: O(n*m) or O(m)
*/

bool regexMatch(const string& s, const string& p) {
    int n = s.size(), m = p.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    dp[0][0] = true;

    // Base: patterns like a*, a*b*, .* can match empty string
    for (int j = 2; j <= m; j++) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (p[j - 1] == '*') {
                // Zero occurrences
                dp[i][j] = dp[i][j - 2];
                // One or more occurrences
                if (p[j - 2] == '.' || p[j - 2] == s[i - 1]) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
            } else if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
        }
    }
    return dp[n][m];
}

void demo_regex() {
    cout << "\n=== PROBLEM 7: REGEX MATCHING ===" << endl;
    cout << "aa, a: " << regexMatch("aa", "a") << endl;             // 0
    cout << "aa, a*: " << regexMatch("aa", "a*") << endl;           // 1
    cout << "ab, .*: " << regexMatch("ab", ".*") << endl;           // 1
    cout << "aab, c*a*b: " << regexMatch("aab", "c*a*b") << endl;  // 1
    cout << "mississippi, mis*is*p*.: " << regexMatch("mississippi", "mis*is*p*.") << endl;  // 0
}

// ═══════════════════════════════════════════════════════════════
// BONUS: INTERLEAVING STRING
// ═══════════════════════════════════════════════════════════════
/*
 Can s3 be formed by interleaving s1 and s2?
 dp[i][j] = can s3[0..i+j-1] be formed from s1[0..i-1] and s2[0..j-1]?
*/

bool isInterleave(const string& s1, const string& s2, const string& s3) {
    int n = s1.size(), m = s2.size();
    if (n + m != (int)s3.size()) return false;

    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    dp[0][0] = true;

    for (int i = 1; i <= n; i++) dp[i][0] = dp[i-1][0] && s1[i-1] == s3[i-1];
    for (int j = 1; j <= m; j++) dp[0][j] = dp[0][j-1] && s2[j-1] == s3[j-1];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]) ||
                        (dp[i][j-1] && s2[j-1] == s3[i+j-1]);
        }
    }
    return dp[n][m];
}

void demo_bonus() {
    cout << "\n=== BONUS: INTERLEAVING STRING ===" << endl;
    cout << "aabcc + dbbca → aadbbcbcac: "
         << isInterleave("aabcc", "dbbca", "aadbbcbcac") << endl;  // 1
    cout << "aabcc + dbbca → aadbbbaccc: "
         << isInterleave("aabcc", "dbbca", "aadbbbaccc") << endl;  // 0
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demo_edit_distance();
    demo_lcs();
    demo_common_substring();
    demo_palindromic_subseq();
    demo_distinct_subseq();
    demo_wildcard();
    demo_regex();
    demo_bonus();

    cout << "\n═══════════════════════════════════════════" << endl;
    cout << "✅ All 7+ String DP Problems covered!" << endl;
    cout << "═══════════════════════════════════════════" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════╗
║  PRACTICE PROBLEMS                                              ║
╠══════════════════════════════════════════════════════════════════╣
║  LeetCode 72   — Edit Distance                                  ║
║  LeetCode 1143 — Longest Common Subsequence                     ║
║  LeetCode 583  — Delete Operation for Two Strings               ║
║  LeetCode 718  — Maximum Length of Repeated Subarray             ║
║  LeetCode 516  — Longest Palindromic Subsequence                ║
║  LeetCode 1312 — Minimum Insertion Steps to Make Palindrome      ║
║  LeetCode 115  — Distinct Subsequences                           ║
║  LeetCode 44   — Wildcard Matching                               ║
║  LeetCode 10   — Regular Expression Matching                     ║
║  LeetCode 97   — Interleaving String                             ║
║  LeetCode 1092 — Shortest Common Supersequence                   ║
║  LeetCode 712  — Minimum ASCII Delete Sum                        ║
║  CF 56D        — Edit Distance variant                           ║
║  CSES          — Edit Distance                                   ║
║  CSES          — Longest Common Subsequence (print)              ║
╚══════════════════════════════════════════════════════════════════╝
*/

