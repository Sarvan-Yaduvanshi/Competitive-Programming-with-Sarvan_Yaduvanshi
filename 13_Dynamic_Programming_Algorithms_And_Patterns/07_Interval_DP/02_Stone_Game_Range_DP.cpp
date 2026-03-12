/*
 * ============================================================================
 *              INTERVAL DP — STONE GAME & RANGE DP VARIANTS
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Interval DP — Range DP, Stone Games, Parenthesization
 * Level   : ⭐⭐⭐ Advanced
 * ============================================================================
 *
 * More Interval DP problems:
 * 1. Stone Game (merge piles)
 * 2. Strange Printer (LeetCode 664)
 * 3. Min Cost to Cut a Stick (LeetCode 1547)
 * 4. Minimum Score Triangulation (LeetCode 1039)
 * 5. Boolean Parenthesization
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Stone Merge (Classic) — Merge adjacent piles, cost = sum of merged
int stoneMerge(vector<int>& stones) {
    int n = stones.size();
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i+1] = prefix[i] + stones[i];

    auto cost = [&](int l, int r) { return prefix[r+1] - prefix[l]; };

    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + cost(i, j));
            }
        }
    }
    return dp[0][n-1];
}

// 2. Strange Printer (LeetCode 664)
// Min turns to print string. Each turn prints one char repeated on range.
int strangePrinter(string& s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) dp[i][i] = 1;

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = dp[i][j-1] + 1;  // Print s[j] separately

            for (int k = i; k < j; k++) {
                if (s[k] == s[j]) {
                    dp[i][j] = min(dp[i][j], dp[i][k] +
                        (k + 1 <= j - 1 ? dp[k+1][j-1] : 0));
                }
            }
        }
    }
    return dp[0][n-1];
}

// 3. Min Cost to Cut a Stick (LeetCode 1547)
int minCostCut(int n, vector<int>& cuts) {
    cuts.push_back(0);
    cuts.push_back(n);
    sort(cuts.begin(), cuts.end());

    int m = cuts.size();
    vector<vector<int>> dp(m, vector<int>(m, 0));

    for (int len = 3; len <= m; len++) {
        for (int i = 0; i + len - 1 < m; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i + 1; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + cuts[j] - cuts[i]);
            }
        }
    }
    return dp[0][m-1];
}

// 4. Minimum Score Triangulation of Polygon (LeetCode 1039)
int minScoreTriangulation(vector<int>& values) {
    int n = values.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int len = 3; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i + 1; k < j; k++) {
                dp[i][j] = min(dp[i][j],
                    dp[i][k] + dp[k][j] + values[i] * values[k] * values[j]);
            }
        }
    }
    return dp[0][n-1];
}

// 5. Boolean Parenthesization
// Given boolean expr: T|F&T^F, count ways to parenthesize to get True.
struct BoolDP {
    // dp[i][j] = {ways_true, ways_false} for expression positions i to j
    pair<long long, long long> solve(string& expr) {
        int n = (expr.size() + 1) / 2;  // Number of operands
        vector<vector<pair<long long,long long>>> dp(n,
            vector<pair<long long,long long>>(n, {0, 0}));

        // Base: single operand
        for (int i = 0; i < n; i++) {
            if (expr[2 * i] == 'T') dp[i][i] = {1, 0};
            else dp[i][i] = {0, 1};
        }

        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;

                for (int k = i; k < j; k++) {
                    char op = expr[2 * k + 1];
                    auto [lt, lf] = dp[i][k];
                    auto [rt, rf] = dp[k + 1][j];

                    long long tt = lt * rt, tf = lt * rf;
                    long long ft = lf * rt, ff = lf * rf;

                    if (op == '&') {
                        dp[i][j].first += tt;
                        dp[i][j].second += tf + ft + ff;
                    } else if (op == '|') {
                        dp[i][j].first += tt + tf + ft;
                        dp[i][j].second += ff;
                    } else {  // XOR
                        dp[i][j].first += tf + ft;
                        dp[i][j].second += tt + ff;
                    }
                }
            }
        }
        return dp[0][n - 1];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== INTERVAL DP — MORE VARIANTS ===" << endl;

    // Stone Merge
    vector<int> stones = {4, 1, 2, 3};
    cout << "\n--- Stone Merge ---" << endl;
    cout << "Min cost: " << stoneMerge(stones) << endl;

    // Strange Printer
    string s = "aaabbb";
    cout << "\n--- Strange Printer ---" << endl;
    cout << "\"" << s << "\" → " << strangePrinter(s) << " turns" << endl;

    // Min Cost Cut
    vector<int> cuts = {1, 3, 4, 5};
    cout << "\n--- Min Cost to Cut Stick ---" << endl;
    cout << "Stick length 7, cuts: "; for (int c : cuts) cout << c << " ";
    cout << "\nMin cost: " << minCostCut(7, cuts) << endl;

    // Polygon Triangulation
    vector<int> polygon = {1, 2, 3};
    cout << "\n--- Polygon Triangulation ---" << endl;
    cout << "Min score: " << minScoreTriangulation(polygon) << endl;

    // Boolean Parenthesization
    string expr = "T|F&T^F";
    BoolDP bdp;
    auto [waysTrue, waysFalse] = bdp.solve(expr);
    cout << "\n--- Boolean Parenthesization ---" << endl;
    cout << "\"" << expr << "\"" << endl;
    cout << "Ways to get True: " << waysTrue << endl;
    cout << "Ways to get False: " << waysFalse << endl;

    return 0;
}

