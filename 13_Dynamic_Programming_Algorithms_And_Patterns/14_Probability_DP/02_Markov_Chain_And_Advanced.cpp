/*
 * ============================================================================
 *          MARKOV CHAIN DP & ADVANCED PROBABILITY
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Probability DP — Markov Chain, Absorbing States, Matrix Expo
 * Level   : ⭐⭐⭐⭐ Expert
 * ============================================================================
 *
 * MARKOV CHAIN DP:
 *   System with states. At each step, transition to next state
 *   with given probabilities. Compute expected steps/probability.
 *
 * ABSORBING MARKOV CHAIN:
 *   Some states are "absorbing" (game over states).
 *   Compute: expected steps to reach absorbing state.
 *   Compute: probability of reaching each absorbing state.
 *
 * KEY TECHNIQUE:
 *   Set up system of linear equations from E[s] = 1 + Σ p(s→s') * E[s']
 *   For small states: solve iteratively or via Gaussian elimination.
 *   For large states with structure: use DP directly.
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * 1. DICE SUM PROBABILITY — AtCoder style
 *    Roll k dice, each with faces 1..d. Probability sum ≤ target?
 */
double diceSumProbability(int k, int d, int target) {
    // dp[i] = probability of getting sum i with remaining dice
    int maxSum = k * d;
    if (target >= maxSum) return 1.0;

    vector<double> dp(maxSum + 1, 0);
    dp[0] = 1.0;

    for (int die = 0; die < k; die++) {
        vector<double> ndp(maxSum + 1, 0);
        for (int sum = 0; sum <= maxSum; sum++) {
            if (dp[sum] == 0) continue;
            for (int face = 1; face <= d; face++) {
                if (sum + face <= maxSum) {
                    ndp[sum + face] += dp[sum] / d;
                }
            }
        }
        dp = ndp;
    }

    double prob = 0;
    for (int i = 0; i <= min(target, maxSum); i++) prob += dp[i];
    return prob;
}

/*
 * 2. KNIGHT PROBABILITY (LeetCode 688)
 *    Knight on n×n chess board, makes k moves randomly (8 directions).
 *    Probability knight remains on board after k moves.
 */
double knightProbability(int n, int k, int row, int col) {
    int dx[] = {-2,-2,-1,-1,1,1,2,2};
    int dy[] = {-1,1,-2,2,-2,2,-1,1};

    vector<vector<double>> dp(n, vector<double>(n, 0));
    dp[row][col] = 1.0;

    for (int step = 0; step < k; step++) {
        vector<vector<double>> ndp(n, vector<double>(n, 0));
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (dp[r][c] == 0) continue;
                for (int d = 0; d < 8; d++) {
                    int nr = r + dx[d], nc = c + dy[d];
                    if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                        ndp[nr][nc] += dp[r][c] / 8.0;
                    }
                }
            }
        }
        dp = ndp;
    }

    double prob = 0;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            prob += dp[r][c];
    return prob;
}

/*
 * 3. SOUP SERVINGS (LeetCode 808)
 *    Two soup types A, B (start with N ml each).
 *    4 operations with equal probability (1/4 each):
 *      Serve 100A+0B, 75A+25B, 50A+50B, 25A+75B
 *    P(A empties first) + 0.5 * P(both empty simultaneously)
 */
double soupServings(int N) {
    if (N >= 4800) return 1.0;  // For large N, answer ≈ 1
    N = (N + 24) / 25;  // Scale down

    vector<vector<double>> dp(N + 1, vector<double>(N + 1, 0));

    // dp[a][b] = answer when a ml of A, b ml of B remain
    int servA[] = {4, 3, 2, 1};
    int servB[] = {0, 1, 2, 3};

    for (int a = 0; a <= N; a++) {
        for (int b = 0; b <= N; b++) {
            if (a == 0 && b == 0) { dp[a][b] = 0.5; continue; }
            if (a == 0) { dp[a][b] = 1.0; continue; }
            if (b == 0) { dp[a][b] = 0.0; continue; }
        }
    }

    for (int a = 1; a <= N; a++) {
        for (int b = 1; b <= N; b++) {
            for (int k = 0; k < 4; k++) {
                int na = max(0, a - servA[k]);
                int nb = max(0, b - servB[k]);
                dp[a][b] += 0.25 * dp[na][nb];
            }
        }
    }
    return dp[N][N];
}

/*
 * 4. MATRIX EXPONENTIATION for Markov Chains
 *    When transitions are fixed (same probabilities), compute
 *    state after k steps using matrix power.
 *
 *    state[k] = T^k × state[0]  where T is transition matrix.
 *    T^k computed in O(n³ log k) using fast matrix exponentiation.
 */
typedef vector<vector<double>> Matrix;

Matrix matMul(Matrix& A, Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

Matrix matPow(Matrix A, long long p) {
    int n = A.size();
    Matrix result(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++) result[i][i] = 1;  // Identity

    while (p > 0) {
        if (p & 1) result = matMul(result, A);
        A = matMul(A, A);
        p >>= 1;
    }
    return result;
}

// Random walk on cycle of size n, k steps
// Start at 0, each step: +1 or -1 with equal probability
vector<double> randomWalkCycle(int n, long long k) {
    Matrix T(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++) {
        T[i][(i + 1) % n] = 0.5;
        T[i][(i - 1 + n) % n] = 0.5;
    }

    Matrix Tk = matPow(T, k);

    // Start at state 0
    vector<double> prob(n);
    for (int j = 0; j < n; j++) prob[j] = Tk[0][j];
    return prob;
}

/*
 * 5. SNAKES AND LADDERS (LeetCode 909 variant)
 *    Expected number of dice rolls to reach end.
 *    DP backwards from destination.
 */
double snakesAndLaddersExpected(int n, map<int, int>& jumps) {
    // Board: positions 1 to n*n
    int total = n * n;
    vector<double> E(total + 1, 0);
    // E[total] = 0 (already at end)

    for (int pos = total - 1; pos >= 1; pos--) {
        double sum = 0;
        int validMoves = 0;

        for (int dice = 1; dice <= 6; dice++) {
            int next = pos + dice;
            if (next > total) continue;
            validMoves++;

            // Check for snake/ladder
            if (jumps.count(next)) next = jumps[next];
            sum += E[next];
        }

        if (validMoves > 0) {
            E[pos] = 1.0 + sum / validMoves;
        } else {
            E[pos] = 1e18;  // Can't move
        }
    }
    return E[1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== MARKOV CHAIN & ADVANCED PROBABILITY DP ===" << endl;

    // Dice Sum Probability
    cout << "\n--- Dice Sum Probability ---" << endl;
    cout << "2 dice (d=6), P(sum ≤ 7) = " << fixed << setprecision(4)
         << diceSumProbability(2, 6, 7) << endl;

    // Knight Probability
    cout << "\n--- Knight Probability ---" << endl;
    cout << "n=3, k=2, start(0,0): " << fixed << setprecision(5)
         << knightProbability(3, 2, 0, 0) << endl;

    // Random Walk on Cycle
    cout << "\n--- Random Walk on Cycle (n=4, k=10) ---" << endl;
    auto prob = randomWalkCycle(4, 10);
    for (int i = 0; i < 4; i++)
        cout << "P(at " << i << ") = " << fixed << setprecision(4) << prob[i] << endl;

    // Snakes and Ladders
    cout << "\n--- Snakes & Ladders Expected Rolls ---" << endl;
    map<int, int> jumps;
    // Simple 6×6 board with one ladder and one snake
    jumps[3] = 22;   // Ladder
    jumps[24] = 8;   // Snake
    cout << "Expected rolls (6×6 board): " << fixed << setprecision(2)
         << snakesAndLaddersExpected(6, jumps) << endl;

    return 0;
}

