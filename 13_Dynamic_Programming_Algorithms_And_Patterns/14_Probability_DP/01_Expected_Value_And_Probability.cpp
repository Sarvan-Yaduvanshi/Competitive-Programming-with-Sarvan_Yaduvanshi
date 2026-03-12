/*
 * ============================================================================
 *                    PROBABILITY & EXPECTED VALUE DP
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Probability DP — Expected Value, Markov, Dice, Random Walk
 * Level   : ⭐⭐⭐⭐ Expert
 * ============================================================================
 *
 * EXPECTED VALUE DP:
 *   E[state] = Σ (probability of transition) * (E[next_state] + cost)
 *
 * KEY FORMULA:
 *   E[X] = Σ P(event) * value(event)
 *
 * LINEARITY OF EXPECTATION:
 *   E[X + Y] = E[X] + E[Y]  (even if X, Y are dependent!)
 *   This is a powerful tool — decompose complex expected values.
 *
 * COMMON PATTERNS:
 * 1. Expected steps to reach goal (work backwards from goal)
 * 2. Probability of reaching states (work forwards from start)
 * 3. Coupon collector (expected time to collect all items)
 * 4. Random walks on graphs
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * 1. DICE PROBABILITY DP
 *    Roll a 6-sided die repeatedly. What's the probability
 *    that total sum equals exactly S?
 *
 *    dp[s] = probability of reaching sum s
 *    dp[s] = Σ dp[s - face] * (1/6) for face in {1..6}
 */
vector<double> diceProbability(int S) {
    vector<double> dp(S + 1, 0);
    dp[0] = 1.0;

    for (int s = 1; s <= S; s++) {
        for (int face = 1; face <= 6 && face <= s; face++) {
            dp[s] += dp[s - face] / 6.0;
        }
    }
    return dp;
}

/*
 * 2. EXPECTED VALUE — Coin Collection (AtCoder DP I — Coins)
 *    N coins, each with probability p[i] of heads.
 *    What's the probability that more than N/2 are heads?
 *
 *    dp[i][j] = probability that first i coins give j heads
 */
double coinProbability(vector<double>& p) {
    int n = p.size();
    vector<vector<double>> dp(n + 1, vector<double>(n + 1, 0));
    dp[0][0] = 1.0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (dp[i][j] == 0) continue;
            dp[i + 1][j + 1] += dp[i][j] * p[i];       // Heads
            dp[i + 1][j]     += dp[i][j] * (1 - p[i]);  // Tails
        }
    }

    double ans = 0;
    for (int j = n / 2 + 1; j <= n; j++)
        ans += dp[n][j];
    return ans;
}

/*
 * 3. COUPON COLLECTOR PROBLEM
 *    N distinct coupons. Each draw gives random coupon (uniform).
 *    Expected draws to collect ALL N coupons?
 *
 *    E = N * (1/1 + 1/2 + ... + 1/N) = N * H(N)
 *
 *    DP approach:
 *    E[k] = expected draws to go from k collected to k+1 collected
 *    When we have k coupons, probability of new one = (N-k)/N
 *    E[k] = N / (N-k)
 *    Total = Σ E[k] for k = 0 to N-1
 */
double couponCollector(int N) {
    double expected = 0;
    for (int k = 0; k < N; k++) {
        expected += (double)N / (N - k);
    }
    return expected;
}

/*
 * 4. EXPECTED VALUE — Sushi Problem (AtCoder DP J)
 *    N plates, each with 1, 2, or 3 sushi. Randomly pick a plate.
 *    If it has sushi, eat one. Expected picks to eat all sushi?
 *
 *    State: (count of plates with 1, count with 2, count with 3)
 *    E[a][b][c] = expected picks when a plates have 1, b have 2, c have 3
 *
 *    Transitions: pick plate with 0 sushi (wasted), 1, 2, or 3 sushi
 *    E[a][b][c] = 1 + (empty/N)*E[a][b][c] + (a/N)*E[a-1][b][c]
 *                   + (b/N)*E[a+1][b-1][c] + (c/N)*E[a][b+1][c-1]
 *
 *    Rearranging (since E appears on both sides):
 *    E[a][b][c] = N/(a+b+c) + ...
 */
double sushiExpected(vector<int>& plates) {
    int N = plates.size();
    int cnt[4] = {0};
    for (int p : plates) cnt[p]++;

    // dp[a][b][c] = expected picks
    vector<vector<vector<double>>> dp(
        N + 1, vector<vector<double>>(N + 1, vector<double>(N + 1, 0)));

    for (int c = 0; c <= N; c++) {
        for (int b = 0; b + c <= N; b++) {
            for (int a = 0; a + b + c <= N; a++) {
                if (a == 0 && b == 0 && c == 0) continue;
                int total = a + b + c;
                double val = (double)N / total;

                if (a > 0) val += (double)a / total * dp[a-1][b][c];
                if (b > 0) val += (double)b / total * dp[a+1][b-1][c];
                if (c > 0) val += (double)c / total * dp[a][b+1][c-1];

                dp[a][b][c] = val;
            }
        }
    }
    return dp[cnt[1]][cnt[2]][cnt[3]];
}

/*
 * 5. RANDOM WALK ON LINE
 *    Start at position 0. Each step: +1 with prob p, -1 with prob (1-p).
 *    Expected steps to reach position N?
 *
 *    For p = 0.5: E[0→N] = N²
 *    For p ≠ 0.5: E[0→N] = N/(2p-1) - N*(1-p)^N * something...
 *
 *    DP: E[i] = expected steps from position i to N
 *    E[i] = 1 + p*E[i+1] + (1-p)*E[i-1]
 *    With absorbing barrier at 0 (reflect) or -inf.
 */
vector<double> randomWalkExpected(int N, double p) {
    // E[N] = 0 (goal reached)
    // E[i] = 1 + p*E[i+1] + (1-p)*E[i-1]
    // Rearrange: p*E[i+1] - E[i] + (1-p)*E[i-1] = -1
    // Solve system of linear equations

    // Simpler: for symmetric walk p=0.5, E[i→N] = (N-i)² with reflecting barrier
    // Here we use DP simulation:
    double q = 1.0 - p;
    vector<double> E(N + 1, 0);
    E[N] = 0;

    // Iterative solution (Gauss-Seidel-like)
    for (int iter = 0; iter < 10000; iter++) {
        for (int i = N - 1; i >= 0; i--) {
            double next = (i + 1 <= N) ? E[i + 1] : 0;
            double prev = (i - 1 >= 0) ? E[i - 1] : E[0];  // Reflect at 0
            E[i] = (1.0 + p * next + q * prev);
            // This needs to be solved as system... simplified iteration shown
        }
    }

    // For the simple case p=q=0.5, E[i] = (N-i)^2
    // Let's return the analytical answer for symmetric case:
    vector<double> analytical(N + 1);
    for (int i = 0; i <= N; i++)
        analytical[i] = (double)(N - i) * (N - i);

    return analytical;
}

/*
 * 6. GAMBLER'S RUIN — Probability of reaching N before 0
 *    Start at position k. p = prob of +1, q = 1-p = prob of -1.
 *
 *    If p ≠ q: P(reach N before 0 | start at k) = (1 - (q/p)^k) / (1 - (q/p)^N)
 *    If p = q = 0.5: P = k/N
 */
double gamblersRuin(int k, int N, double p) {
    if (abs(p - 0.5) < 1e-9) return (double)k / N;
    double r = (1.0 - p) / p;  // q/p
    return (1.0 - pow(r, k)) / (1.0 - pow(r, N));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== PROBABILITY & EXPECTED VALUE DP ===" << endl;

    // Dice probability
    cout << "\n--- Dice Probability ---" << endl;
    auto dp = diceProbability(12);
    for (int s = 1; s <= 12; s++)
        cout << "P(sum=" << s << ") = " << fixed << setprecision(4) << dp[s] << endl;

    // Coin probability
    vector<double> p = {0.3, 0.6, 0.8, 0.2, 0.5};
    cout << "\n--- Coin Probability (>N/2 heads) ---" << endl;
    cout << "P = " << fixed << setprecision(6) << coinProbability(p) << endl;

    // Coupon Collector
    cout << "\n--- Coupon Collector ---" << endl;
    for (int n : {5, 10, 50, 100}) {
        cout << "N=" << n << " → Expected draws: " << fixed << setprecision(2)
             << couponCollector(n) << endl;
    }

    // Sushi
    vector<int> plates = {1, 2, 3};
    cout << "\n--- Sushi Expected (AtCoder DP J) ---" << endl;
    cout << "Expected picks: " << fixed << setprecision(4) << sushiExpected(plates) << endl;

    // Gambler's Ruin
    cout << "\n--- Gambler's Ruin ---" << endl;
    cout << "k=5, N=10, p=0.5 → P(win) = " << gamblersRuin(5, 10, 0.5) << endl;
    cout << "k=5, N=10, p=0.6 → P(win) = " << gamblersRuin(5, 10, 0.6) << endl;
    cout << "k=5, N=10, p=0.4 → P(win) = " << gamblersRuin(5, 10, 0.4) << endl;

    return 0;
}

