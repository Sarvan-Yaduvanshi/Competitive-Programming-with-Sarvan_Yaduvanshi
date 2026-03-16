/*
 * ============================================================
 *  Topic   : Expected Value & Probability DP
 *  Pattern : Linearity of expectation, probability transitions
 *
 *  Problems:
 *    - Expected dice throws to get 6
 *    - Coupon collector expected value
 *    - LeetCode 688 — Knight Probability in Chessboard
 *    - LeetCode 837 — New 21 Game
 *
 *  Complexity: Problem-dependent
 * ============================================================
 */

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

template<class T>
void read(vec<T> &v) { for (auto &x : v) cin >> x; }
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

/*
 * ============================================================
 *  COUPON COLLECTOR — Expected Value via Linearity
 * ============================================================
 *
 *  Collect all n types. Each draw gives random type.
 *  E[total draws] = Σ_{k=0}^{n-1} n/(n-k) = n * H_n
 *  where H_n = 1 + 1/2 + 1/3 + ... + 1/n (harmonic number)
 *
 *  H_n ≈ ln(n) + γ  where γ ≈ 0.5772 (Euler-Mascheroni)
 * ============================================================
 */

ld couponCollector(int n) {
    ld expected = 0;
    for (int k = 0; k < n; k++) {
        expected += (ld)n / (n - k);
    }
    return expected;
}

/*
 * ============================================================
 *  PROBABILITY DP: Knight on Chessboard
 * ============================================================
 *  LeetCode 688: Knight makes k moves on n×n board.
 *  What's the probability it stays on board?
 *
 *  dp[step][r][c] = probability of being at (r,c) after step moves
 *  Each move: 8 possible positions, each with prob 1/8
 * ============================================================
 */

ld knightProbability(int n, int k, int row, int col) {
    int dr[] = {-2,-2,-1,-1,1,1,2,2};
    int dc[] = {-1,1,-2,2,-2,2,-1,1};

    // dp[r][c] = probability of being at (r,c)
    vvec<ld> dp(n, vec<ld>(n, 0.0));
    dp[row][col] = 1.0;

    for (int step = 0; step < k; step++) {
        vvec<ld> ndp(n, vec<ld>(n, 0.0));
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (dp[r][c] < 1e-15) continue;
                for (int d = 0; d < 8; d++) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                        ndp[nr][nc] += dp[r][c] / 8.0;
                    }
                }
            }
        }
        dp = ndp;
    }

    ld prob = 0;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            prob += dp[r][c];

    return prob;
}

/*
 * ============================================================
 *  EXPECTED VALUE DP: Dice Problem
 * ============================================================
 *  Expected number of throws of a fair 6-sided die to reach
 *  sum >= n.
 *
 *  E[i] = expected additional throws to reach n from current sum i
 *  E[i] = 0  for i >= n
 *  E[i] = 1 + (1/6) * Σ_{d=1}^{6} E[i + d]
 * ============================================================
 */

ld expectedDiceThrows(int n) {
    vec<ld> E(n + 7, 0);
    for (int i = n - 1; i >= 0; i--) {
        E[i] = 1.0;
        for (int d = 1; d <= 6; d++) {
            E[i] += E[min(i + d, n)] / 6.0;
        }
    }
    return E[0];
}

/*
 * ============================================================
 *  MODULAR PROBABILITY
 * ============================================================
 *  In CP, probability p/q mod MOD is computed as:
 *  p * modinv(q, MOD) % MOD
 *
 *  Example: probability 1/3 mod 1e9+7
 *  = 1 * modpow(3, MOD-2, MOD) % MOD
 *  = 333333336
 * ============================================================
 */

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD) {
    i64 res = 1; base %= mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

// Compute probability p/q mod MOD
i64 modprob(i64 p, i64 q) {
    return p % MOD * modpow(q, MOD - 2, MOD) % MOD;
}

void solve() {
    int n;
    cin >> n;

    cout << "Coupon collector E[" << n << "] = " << couponCollector(n) << nl;
    cout << "Expected dice throws to reach " << n << " = " << expectedDiceThrows(n) << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    int TC = 1;
    cin >> TC;
    while (TC--) solve();

    return 0;
}

