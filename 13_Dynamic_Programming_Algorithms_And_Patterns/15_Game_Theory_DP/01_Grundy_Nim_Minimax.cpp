/*
 * ============================================================================
 *                GAME THEORY DP — GRUNDY, NIM, MINIMAX
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Game Theory DP — Grundy, Sprague-Grundy, Nim, Minimax, Stone Games
 * Level   : ⭐⭐⭐⭐ Expert
 * ============================================================================
 *
 * GAME THEORY DP:
 *   Two players play optimally. Determine who wins / optimal strategy.
 *
 * KEY CONCEPTS:
 * 1. WINNING/LOSING STATES:
 *    - A state is LOSING if ALL moves lead to WINNING states (for opponent)
 *    - A state is WINNING if ANY move leads to LOSING state (for opponent)
 *    - Base: terminal state (no moves) is LOSING
 *
 * 2. GRUNDY NUMBERS (Sprague-Grundy):
 *    - G(state) = mex({G(next_states)})  where mex = minimum excludant
 *    - State is losing iff G(state) = 0
 *    - For combined games: G(game1 + game2) = G(game1) XOR G(game2)
 *
 * 3. NIM GAME:
 *    - n piles of stones. Remove any number from one pile.
 *    - First player wins iff XOR of all pile sizes ≠ 0
 *
 * 4. MINIMAX:
 *    - Maximizer wants to maximize score
 *    - Minimizer wants to minimize score
 *    - dp[state] = optimal score with current player to move
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * 1. GRUNDY NUMBERS — Foundation
 *    Compute Grundy number for a single game state.
 *    mex(S) = smallest non-negative integer NOT in set S.
 */
int mex(set<int>& s) {
    int m = 0;
    while (s.count(m)) m++;
    return m;
}

// Grundy number for a subtraction game
// Remove 1, 2, or 3 stones from a pile of n.
vector<int> grundySubtraction(int maxN, vector<int>& moves) {
    vector<int> grundy(maxN + 1, 0);

    for (int n = 1; n <= maxN; n++) {
        set<int> reachable;
        for (int m : moves) {
            if (n >= m) reachable.insert(grundy[n - m]);
        }
        grundy[n] = mex(reachable);
    }
    return grundy;
}

/*
 * 2. NIM GAME — Classic
 *    n piles with sizes a[0], a[1], ..., a[n-1]
 *    Remove any positive number of stones from one pile.
 *    Player who can't move loses.
 *
 *    THEOREM: First player wins iff a[0] XOR a[1] XOR ... XOR a[n-1] ≠ 0
 */
bool nimGame(vector<int>& piles) {
    int xorSum = 0;
    for (int p : piles) xorSum ^= p;
    return xorSum != 0;  // First player wins if XOR ≠ 0
}

/*
 * 3. SPRAGUE-GRUNDY FOR COMBINED GAMES
 *    Multiple independent games played simultaneously.
 *    Each turn: make a move in exactly ONE game.
 *    Grundy of combined game = XOR of individual Grundy numbers.
 */
bool combinedGameWinner(vector<int>& piles, vector<int>& moves) {
    auto grundy = grundySubtraction(100, moves);
    int xorSum = 0;
    for (int p : piles) xorSum ^= grundy[p];
    return xorSum != 0;
}

/*
 * 4. STONE GAME — LeetCode 877
 *    Piles in a row. Alice and Bob take from either end.
 *    Both play optimally. Does Alice win?
 *
 *    dp[i][j] = max score difference (current player - other)
 *               for piles[i..j]
 */
int stoneGame(vector<int>& piles) {
    int n = piles.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Base: single pile
    for (int i = 0; i < n; i++) dp[i][i] = piles[i];

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = max(piles[i] - dp[i+1][j],   // Take left
                           piles[j] - dp[i][j-1]);    // Take right
        }
    }
    return dp[0][n-1];  // Positive = first player leads by this much
}

/*
 * 5. MINIMAX DP — Optimal Strategy for Game
 *    Two players alternate. Maximize own score.
 *
 *    dp[i][j] = max coins first player can collect from piles[i..j]
 */
int optimalStrategy(vector<int>& coins) {
    int n = coins.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) dp[i][i] = coins[i];

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            // If I take coins[i], opponent gets dp[i+1][j]
            // My total from rest = sum(i+1..j) - dp[i+1][j]
            // Similarly for taking coins[j]

            // Simpler formulation:
            dp[i][j] = max(
                coins[i] + min(                    // Take left
                    (i+2 <= j ? dp[i+2][j] : 0),  // Opponent takes left
                    (i+1 <= j-1 ? dp[i+1][j-1] : 0)  // Opponent takes right
                ),
                coins[j] + min(                    // Take right
                    (i <= j-2 ? dp[i][j-2] : 0),  // Opponent takes right
                    (i+1 <= j-1 ? dp[i+1][j-1] : 0)  // Opponent takes left
                )
            );
        }
    }
    return dp[0][n-1];
}

/*
 * 6. NIM VARIANTS
 */

// Staircase Nim: Only moves from odd-indexed piles matter
bool staircaseNim(vector<int>& stairs) {
    int xorSum = 0;
    for (int i = 1; i < (int)stairs.size(); i += 2)
        xorSum ^= stairs[i];
    return xorSum != 0;
}

// Bash Game: Single pile, remove 1..k stones
// First player wins iff n % (k+1) != 0
bool bashGame(int n, int k) {
    return n % (k + 1) != 0;
}

// Wythoff's Game: Two piles, remove any from one OR equal from both
// Losing positions: (floor(k*phi), floor(k*phi²)) for k=0,1,2,...
// where phi = (1+sqrt(5))/2
bool wythoffGame(int a, int b) {
    if (a > b) swap(a, b);
    double phi = (1.0 + sqrt(5.0)) / 2.0;
    int k = b - a;
    int expectedA = (int)(k * phi);
    return !(a == expectedA);  // Wins if NOT a cold position
}

/*
 * 7. WINNING MOVES — Print the winning move
 */
int findWinningMove(vector<int>& piles) {
    int xorSum = 0;
    for (int p : piles) xorSum ^= p;

    if (xorSum == 0) return -1;  // No winning move exists

    // Find a pile where removing stones makes XOR = 0
    for (int i = 0; i < (int)piles.size(); i++) {
        int target = piles[i] ^ xorSum;  // What pile[i] should become
        if (target < piles[i]) {
            cout << "Remove " << (piles[i] - target)
                 << " from pile " << i << " (reduce to " << target << ")" << endl;
            return i;
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== GAME THEORY DP ===" << endl;

    // Grundy Numbers
    vector<int> moves = {1, 2, 3};
    auto grundy = grundySubtraction(15, moves);
    cout << "\n--- Grundy Numbers (subtract {1,2,3}) ---" << endl;
    for (int i = 0; i <= 15; i++)
        cout << "G(" << i << ")=" << grundy[i] << " ";
    cout << endl;

    // Nim Game
    vector<int> piles = {3, 4, 5};
    cout << "\n--- Nim Game ---" << endl;
    cout << "Piles: "; for (int p : piles) cout << p << " ";
    cout << "\nFirst player wins: " << (nimGame(piles) ? "YES" : "NO") << endl;
    findWinningMove(piles);

    // Stone Game
    vector<int> stones = {5, 3, 4, 5};
    cout << "\n--- Stone Game ---" << endl;
    cout << "Piles: "; for (int s : stones) cout << s << " ";
    int diff = stoneGame(stones);
    cout << "\nScore difference: " << diff << endl;
    cout << "First player " << (diff > 0 ? "WINS" : "LOSES") << endl;

    // Optimal Strategy
    vector<int> coins = {8, 15, 3, 7};
    cout << "\n--- Optimal Strategy ---" << endl;
    cout << "Coins: "; for (int c : coins) cout << c << " ";
    cout << "\nFirst player max coins: " << optimalStrategy(coins) << endl;

    // Bash Game
    cout << "\n--- Bash Game (1 pile, remove 1-3) ---" << endl;
    for (int n = 1; n <= 10; n++)
        cout << "n=" << n << " → " << (bashGame(n, 3) ? "WIN" : "LOSE") << endl;

    // Wythoff
    cout << "\n--- Wythoff Game ---" << endl;
    cout << "(3,5): " << (wythoffGame(3, 5) ? "WIN" : "LOSE") << endl;
    cout << "(1,2): " << (wythoffGame(1, 2) ? "WIN" : "LOSE") << endl;
    cout << "(0,0): " << (wythoffGame(0, 0) ? "WIN" : "LOSE") << endl;

    return 0;
}

