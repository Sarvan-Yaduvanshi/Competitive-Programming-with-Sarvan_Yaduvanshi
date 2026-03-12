/*
 * ============================================================================
 *    1D DP — JUMP GAME, WORD BREAK, UGLY NUMBERS, PERFECT SQUARES
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : 1D DP — Classic Interview + CP Problems
 * Level   : ⭐⭐ Intermediate
 * ============================================================================
 *
 * More 1D DP classics essential for complete coverage:
 * 1. Jump Game I — can reach end?
 * 2. Jump Game II — min jumps to reach end
 * 3. Word Break — can string be segmented?
 * 4. Word Break II — all segmentations
 * 5. Perfect Squares — min squares summing to n
 * 6. Ugly Numbers — nth number with prime factors 2,3,5 only
 * 7. Count Binary Strings without consecutive 1s
 * 8. Number of Ways to Decode (extended)
 * 9. Best Time to Buy and Sell Stock — DP interpretation
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// 1. Jump Game I (LeetCode 55)
bool canJump(vector<int>& nums) {
    int maxReach = 0;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (i > maxReach) return false;
        maxReach = max(maxReach, i + nums[i]);
    }
    return true;
}

// 2. Jump Game II — Min Jumps (LeetCode 45)
int minJumps(vector<int>& nums) {
    int n = nums.size();
    int jumps = 0, curEnd = 0, farthest = 0;
    for (int i = 0; i < n - 1; i++) {
        farthest = max(farthest, i + nums[i]);
        if (i == curEnd) {
            jumps++;
            curEnd = farthest;
        }
    }
    return jumps;
}

// 3. Word Break (LeetCode 139)
bool wordBreak(string& s, vector<string>& wordDict) {
    int n = s.size();
    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (dp[j] && dict.count(s.substr(j, i - j))) {
                dp[i] = true;
                break;
            }
        }
    }
    return dp[n];
}

// 4. Word Break II — All segmentations (LeetCode 140)
vector<string> wordBreakII(string& s, vector<string>& wordDict) {
    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    int n = s.size();

    // Check feasibility first
    vector<bool> dp(n + 1, false);
    dp[0] = true;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            if (dp[j] && dict.count(s.substr(j, i - j)))
                { dp[i] = true; break; }

    vector<string> result;
    if (!dp[n]) return result;

    // Backtrack
    function<void(int, string)> backtrack = [&](int start, string sentence) {
        if (start == n) { result.push_back(sentence); return; }
        for (int end = start + 1; end <= n; end++) {
            string word = s.substr(start, end - start);
            if (dict.count(word) && dp[end]) {
                string next = sentence.empty() ? word : sentence + " " + word;
                backtrack(end, next);
            }
        }
    };
    backtrack(0, "");
    return result;
}

// 5. Perfect Squares (LeetCode 279)
int numSquares(int n) {
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j * j <= i; j++)
            dp[i] = min(dp[i], dp[i - j * j] + 1);
    return dp[n];
}

// 6. Ugly Numbers II (LeetCode 264) — nth ugly number (2, 3, 5 only)
int nthUglyNumber(int n) {
    vector<int> ugly(n);
    ugly[0] = 1;
    int i2 = 0, i3 = 0, i5 = 0;

    for (int i = 1; i < n; i++) {
        int next2 = ugly[i2] * 2;
        int next3 = ugly[i3] * 3;
        int next5 = ugly[i5] * 5;
        ugly[i] = min({next2, next3, next5});

        if (ugly[i] == next2) i2++;
        if (ugly[i] == next3) i3++;
        if (ugly[i] == next5) i5++;
    }
    return ugly[n - 1];
}

// 7. Count Binary Strings without consecutive 1s
long long binaryStringsNoConsec1(int n) {
    // dp[i][0] = strings of length i ending in 0
    // dp[i][1] = strings of length i ending in 1
    // dp[i][0] = dp[i-1][0] + dp[i-1][1]
    // dp[i][1] = dp[i-1][0]
    // Total = Fibonacci!
    long long a = 1, b = 1; // end0, end1 for length 1
    for (int i = 2; i <= n; i++) {
        long long new_a = a + b;
        long long new_b = a;
        a = new_a; b = new_b;
    }
    return a + b;
}

// 8. Stock Buy/Sell — DP with State Machine
// Best Time to Buy and Sell with at most K transactions (LeetCode 188)
int maxProfitKTxn(int k, vector<int>& prices) {
    int n = prices.size();
    if (n < 2) return 0;

    if (k >= n / 2) {
        // Unlimited transactions
        int profit = 0;
        for (int i = 1; i < n; i++)
            profit += max(0, prices[i] - prices[i-1]);
        return profit;
    }

    // dp[j][0] = max profit with j transactions done, not holding
    // dp[j][1] = max profit with j transactions done, holding
    vector<vector<int>> dp(k + 1, vector<int>(2, 0));
    for (int j = 0; j <= k; j++) dp[j][1] = INT_MIN;

    for (int price : prices) {
        for (int j = k; j >= 1; j--) {
            dp[j][0] = max(dp[j][0], dp[j][1] + price);    // Sell
            dp[j][1] = max(dp[j][1], dp[j-1][0] - price);  // Buy
        }
    }
    return dp[k][0];
}

// Stock with Cooldown (LeetCode 309)
int maxProfitCooldown(vector<int>& prices) {
    int n = prices.size();
    if (n < 2) return 0;

    int held = -prices[0], sold = 0, rest = 0;
    for (int i = 1; i < n; i++) {
        int new_held = max(held, rest - prices[i]);
        int new_sold = held + prices[i];
        int new_rest = max(rest, sold);
        held = new_held; sold = new_sold; rest = new_rest;
    }
    return max(sold, rest);
}

// 9. Minimum Deletions to Make String Palindrome
int minDeletionsPalindrome(string& s) {
    int n = s.size();
    string rev(s.rbegin(), s.rend());

    // LCS of s and reverse(s)
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = (s[i-1] == rev[j-1]) ? dp[i-1][j-1] + 1 : max(dp[i-1][j], dp[i][j-1]);

    return n - dp[n][n];  // Delete chars not in LPS
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== 1D DP — MORE CLASSICS ===" << endl;

    // Jump Game
    vector<int> nums1 = {2, 3, 1, 1, 4};
    cout << "\n--- Jump Game I ---" << endl;
    cout << "Can jump: " << (canJump(nums1) ? "YES" : "NO") << endl;
    cout << "Min jumps: " << minJumps(nums1) << endl;

    // Word Break
    string s = "leetcode";
    vector<string> dict = {"leet", "code"};
    cout << "\n--- Word Break ---" << endl;
    cout << "\"" << s << "\": " << (wordBreak(s, dict) ? "YES" : "NO") << endl;

    // Perfect Squares
    cout << "\n--- Perfect Squares ---" << endl;
    cout << "12 = " << numSquares(12) << " squares" << endl;
    cout << "13 = " << numSquares(13) << " squares" << endl;

    // Ugly Numbers
    cout << "\n--- Ugly Numbers ---" << endl;
    cout << "10th ugly: " << nthUglyNumber(10) << endl;

    // Binary strings no consecutive 1s
    cout << "\n--- Binary Strings (no 11) ---" << endl;
    for (int n = 1; n <= 8; n++)
        cout << "n=" << n << ": " << binaryStringsNoConsec1(n) << " ";
    cout << endl;

    // Stock with K transactions
    vector<int> prices = {3, 2, 6, 5, 0, 3};
    cout << "\n--- Stock K=2 transactions ---" << endl;
    cout << "Max profit: " << maxProfitKTxn(2, prices) << endl;

    // Stock with cooldown
    vector<int> prices2 = {1, 2, 3, 0, 2};
    cout << "With cooldown: " << maxProfitCooldown(prices2) << endl;

    return 0;
}

