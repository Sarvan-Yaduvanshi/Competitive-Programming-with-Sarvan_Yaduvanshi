/*
 * ============================================================================
 *          STONE GAME VARIANTS & OPTIMAL STRATEGY DP
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Game Theory DP — Stone Game variants, Optimal play
 * Level   : ⭐⭐⭐⭐ Expert
 * ============================================================================
 *
 * STONE GAME COLLECTION (LeetCode):
 * 1. Stone Game I   (877)  — Can Alice always win?
 * 2. Stone Game II  (1140) — Variable moves, maximize stones
 * 3. Stone Game III (1406) — Take 1-3 stones, max relative score
 * 4. Stone Game IV  (1510) — Can first player always win? (square moves)
 * 5. Stone Game V   (1563) — Split and keep smaller half
 * 6. Removal Game   (CSES) — Deque game, max first player score
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// Stone Game II (LeetCode 1140)
// On each turn, take 1 to 2M piles from front. M = max(M, piles taken).
// Both play optimally. Return max stones Alice gets.
int stoneGameII(vector<int>& piles) {
    int n = piles.size();
    vector<int> suffix(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) suffix[i] = suffix[i + 1] + piles[i];

    // dp[i][m] = max stones current player can get from piles[i..n-1] with M=m
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int i = n - 1; i >= 0; i--) {
        for (int m = 1; m <= n; m++) {
            for (int x = 1; x <= 2 * m && i + x <= n; x++) {
                // Take x piles. Opponent gets dp[i+x][max(m,x)]
                int newM = min(n, max(m, x));
                dp[i][m] = max(dp[i][m], suffix[i] - dp[i + x][newM]);
            }
        }
    }
    return dp[0][1];
}

// Stone Game III (LeetCode 1406)
// Take 1, 2, or 3 from front. Maximize your score minus opponent's.
string stoneGameIII(vector<int>& values) {
    int n = values.size();
    vector<int> dp(n + 1, 0);
    // dp[i] = max (my_score - opponent_score) for values[i..n-1]

    vector<int> suffix(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) suffix[i] = suffix[i + 1] + values[i];

    for (int i = n - 1; i >= 0; i--) {
        dp[i] = INT_MIN;
        int take = 0;
        for (int k = 1; k <= 3 && i + k <= n; k++) {
            take += values[i + k - 1];
            dp[i] = max(dp[i], take - dp[i + k]);
        }
    }

    if (dp[0] > 0) return "Alice";
    if (dp[0] < 0) return "Bob";
    return "Tie";
}

// Stone Game IV (LeetCode 1510)
// Pile of n stones. Each turn remove a perfect square number.
// Player who can't move loses. Can Alice win?
bool stoneGameIV(int n) {
    vector<bool> win(n + 1, false);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j * j <= i; j++) {
            if (!win[i - j * j]) {
                win[i] = true;
                break;
            }
        }
    }
    return win[n];
}

// Removal Game (CSES) — Same as LeetCode 877 generalized
// Array of n numbers. Players alternately take from left or right end.
// Both play optimally. What is the FIRST player's score?
long long removalGame(vector<int>& arr) {
    int n = arr.size();
    vector<vector<long long>> dp(n, vector<long long>(n, 0));

    // dp[i][j] = max score difference (current_player - other) for arr[i..j]
    for (int i = 0; i < n; i++) dp[i][i] = arr[i];

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = max((long long)arr[i] - dp[i + 1][j],
                           (long long)arr[j] - dp[i][j - 1]);
        }
    }

    // First player's score = (total + score_diff) / 2
    long long total = 0;
    for (int x : arr) total += x;
    return (total + dp[0][n - 1]) / 2;
}

// Predict the Winner (LeetCode 486) — same idea
bool predictWinner(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) dp[i][i] = nums[i];

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = max(nums[i] - dp[i+1][j], nums[j] - dp[i][j-1]);
        }
    }
    return dp[0][n-1] >= 0;
}

// Cat and Mouse Game State DP (concept)
// States: (mouse_pos, cat_pos, whose_turn)
// Mouse wins if reaches hole. Cat wins if catches mouse.
// BFS from winning states backwards (retrograde analysis).

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== STONE GAME VARIANTS ===" << endl;

    // Stone Game II
    vector<int> piles = {2, 7, 9, 4, 4};
    cout << "\n--- Stone Game II ---" << endl;
    cout << "Alice max: " << stoneGameII(piles) << endl;

    // Stone Game III
    vector<int> values = {1, 2, 3, 7};
    cout << "\n--- Stone Game III ---" << endl;
    cout << "Winner: " << stoneGameIII(values) << endl;

    // Stone Game IV
    cout << "\n--- Stone Game IV ---" << endl;
    for (int n = 1; n <= 10; n++)
        cout << "n=" << n << ": " << (stoneGameIV(n) ? "Alice WINS" : "Bob WINS") << endl;

    // Removal Game
    vector<int> arr = {4, 10, 2, 3};
    cout << "\n--- Removal Game (CSES) ---" << endl;
    cout << "Array: "; for (int x : arr) cout << x << " ";
    cout << "\nFirst player score: " << removalGame(arr) << endl;

    // Predict the Winner
    vector<int> nums = {1, 5, 233, 7};
    cout << "\n--- Predict the Winner ---" << endl;
    cout << "Player 1 wins: " << (predictWinner(nums) ? "YES" : "NO") << endl;

    return 0;
}

