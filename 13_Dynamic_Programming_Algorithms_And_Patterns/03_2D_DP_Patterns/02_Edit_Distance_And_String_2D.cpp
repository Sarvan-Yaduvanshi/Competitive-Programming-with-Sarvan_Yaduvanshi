/*
 * ============================================================================
 *              EDIT DISTANCE & INTERLEAVING STRINGS
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : 2D DP — Edit Distance, Distinct Subsequences, Interleaving
 * Level   : ⭐⭐ Intermediate
 * ============================================================================
 *
 * EDIT DISTANCE (LeetCode 72):
 *   Minimum operations (insert/delete/replace) to convert s1 → s2
 *   dp[i][j] = edit distance of s1[0..i-1] and s2[0..j-1]
 *
 * DISTINCT SUBSEQUENCES (LeetCode 115):
 *   Count subsequences of s that equal t
 *   dp[i][j] = ways to form t[0..j-1] from s[0..i-1]
 *
 * INTERLEAVING STRING (LeetCode 97):
 *   Is s3 an interleaving of s1 and s2?
 *   dp[i][j] = can s1[0..i-1] and s2[0..j-1] form s3[0..i+j-1]?
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// Edit Distance (Levenshtein Distance)
// Time: O(n*m), Space: O(m) optimized
int editDistance(string& s1, string& s2) {
    int n = s1.size(), m = s2.size();
    vector<int> prev(m + 1), curr(m + 1);

    for (int j = 0; j <= m; j++) prev[j] = j;  // Base: delete all from s2

    for (int i = 1; i <= n; i++) {
        curr[0] = i;  // Base: delete all from s1
        for (int j = 1; j <= m; j++) {
            if (s1[i-1] == s2[j-1]) {
                curr[j] = prev[j-1];  // Characters match
            } else {
                curr[j] = 1 + min({prev[j-1],   // Replace
                                   prev[j],       // Delete from s1
                                   curr[j-1]});   // Insert into s1
            }
        }
        swap(prev, curr);
    }
    return prev[m];
}

// Print Edit Distance Operations (for understanding)
void editDistanceWithOps(string& s1, string& s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (s1[i-1] == s2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]});

    // Backtrack to find operations
    int i = n, j = m;
    vector<string> ops;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && s1[i-1] == s2[j-1]) {
            ops.push_back("Keep '" + string(1, s1[i-1]) + "'");
            i--; j--;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i-1][j-1] + 1) {
            ops.push_back("Replace '" + string(1, s1[i-1]) + "' → '" + string(1, s2[j-1]) + "'");
            i--; j--;
        } else if (i > 0 && dp[i][j] == dp[i-1][j] + 1) {
            ops.push_back("Delete '" + string(1, s1[i-1]) + "'");
            i--;
        } else {
            ops.push_back("Insert '" + string(1, s2[j-1]) + "'");
            j--;
        }
    }

    reverse(ops.begin(), ops.end());
    cout << "Operations (" << dp[n][m] << " total):" << endl;
    for (auto& op : ops) cout << "  " << op << endl;
}

// Distinct Subsequences
// Count subsequences of s that equal t
long long distinctSubsequences(string& s, string& t) {
    int n = s.size(), m = t.size();
    vector<long long> dp(m + 1, 0);
    dp[0] = 1;  // Empty string is subsequence of anything

    for (int i = 1; i <= n; i++) {
        // Iterate backwards to avoid overwriting
        for (int j = min(i, m); j >= 1; j--) {
            if (s[i-1] == t[j-1]) {
                dp[j] += dp[j-1];
            }
        }
    }
    return dp[m];
}

// Interleaving String
bool isInterleave(string& s1, string& s2, string& s3) {
    int n = s1.size(), m = s2.size();
    if (n + m != (int)s3.size()) return false;

    vector<bool> dp(m + 1, false);

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 && j == 0) {
                dp[j] = true;
            } else if (i == 0) {
                dp[j] = dp[j-1] && (s2[j-1] == s3[j-1]);
            } else if (j == 0) {
                dp[j] = dp[j] && (s1[i-1] == s3[i-1]);
            } else {
                dp[j] = (dp[j] && s1[i-1] == s3[i+j-1]) ||
                         (dp[j-1] && s2[j-1] == s3[i+j-1]);
            }
        }
    }
    return dp[m];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== EDIT DISTANCE & STRING 2D DP ===" << endl;

    // Edit Distance
    string s1 = "horse", s2 = "ros";
    cout << "\n--- Edit Distance ---" << endl;
    cout << "\"" << s1 << "\" → \"" << s2 << "\"" << endl;
    cout << "Distance: " << editDistance(s1, s2) << endl;
    editDistanceWithOps(s1, s2);

    // Distinct Subsequences
    string s = "rabbbit", t = "rabbit";
    cout << "\n--- Distinct Subsequences ---" << endl;
    cout << "s=\"" << s << "\", t=\"" << t << "\"" << endl;
    cout << "Count: " << distinctSubsequences(s, t) << endl;

    // Interleaving String
    string a = "aabcc", b = "dbbca", c = "aadbbcbcac";
    cout << "\n--- Interleaving String ---" << endl;
    cout << "s1=\"" << a << "\", s2=\"" << b << "\", s3=\"" << c << "\"" << endl;
    cout << "Is interleave? " << (isInterleave(a, b, c) ? "YES" : "NO") << endl;

    return 0;
}

