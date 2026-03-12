/*
 * ============================================================================
 *                    DIGIT DP — COMPLETE GUIDE
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Digit DP — Template, Counting with Constraints, Range Queries
 * Level   : ⭐⭐⭐⭐ Expert
 * ============================================================================
 *
 * DIGIT DP PATTERN:
 *   Count numbers in range [L, R] satisfying some digit-based property.
 *   answer(L, R) = f(R) - f(L-1)   where f(X) = count in [0, X]
 *
 * STATE: dp[pos][tight][...extra states...]
 *   pos    = current digit position (0 to num_digits-1)
 *   tight  = are we still bounded by the limit? (0 or 1)
 *   extra  = problem-specific (digit sum, last digit, bitmask, etc.)
 *
 * TEMPLATE:
 *   solve(pos, tight, ...extra...) {
 *       if (pos == n) return check_condition();
 *       if (memo[pos][tight][extra] != -1) return memo;
 *
 *       int limit = tight ? digit[pos] : 9;
 *       int result = 0;
 *       for (d = 0; d <= limit; d++) {
 *           result += solve(pos+1, tight && (d == limit), update(extra, d));
 *       }
 *       return memo[pos][tight][extra] = result;
 *   }
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * PROBLEM 1: Count numbers in [1, N] with digit sum ≤ S
 */
class DigitSumCounter {
    vector<int> digits;
    long long dp[20][200][2];  // pos, sum_so_far, tight
    int maxSum;

    long long solve(int pos, int sum, bool tight) {
        if (sum > maxSum) return 0;
        if (pos == (int)digits.size()) return 1;
        if (dp[pos][sum][tight] != -1) return dp[pos][sum][tight];

        int limit = tight ? digits[pos] : 9;
        long long result = 0;

        for (int d = 0; d <= limit; d++) {
            result += solve(pos + 1, sum + d, tight && (d == limit));
        }
        return dp[pos][sum][tight] = result;
    }

public:
    long long count(long long N, int S) {
        if (N < 0) return 0;
        maxSum = S;
        digits.clear();
        if (N == 0) { digits.push_back(0); }
        else {
            long long temp = N;
            while (temp > 0) { digits.push_back(temp % 10); temp /= 10; }
            reverse(digits.begin(), digits.end());
        }
        memset(dp, -1, sizeof(dp));
        return solve(0, 0, true);
    }
};

/*
 * PROBLEM 2: Count numbers in [L, R] that DON'T contain digit D
 */
class AvoidDigitCounter {
    vector<int> digits;
    long long dp[20][2];
    int avoidDigit;

    long long solve(int pos, bool tight) {
        if (pos == (int)digits.size()) return 1;
        if (dp[pos][tight] != -1) return dp[pos][tight];

        int limit = tight ? digits[pos] : 9;
        long long result = 0;

        for (int d = 0; d <= limit; d++) {
            if (d == avoidDigit) continue;  // Skip forbidden digit
            result += solve(pos + 1, tight && (d == limit));
        }
        return dp[pos][tight] = result;
    }

public:
    long long count(long long N, int D) {
        if (N < 0) return 0;
        avoidDigit = D;
        digits.clear();
        long long temp = N;
        while (temp > 0) { digits.push_back(temp % 10); temp /= 10; }
        reverse(digits.begin(), digits.end());
        if (digits.empty()) digits.push_back(0);
        memset(dp, -1, sizeof(dp));
        return solve(0, true);
    }
};

/*
 * PROBLEM 3: Count numbers with all unique digits in [1, N]
 */
class UniqueDigitsCounter {
    vector<int> digits;
    long long dp[20][1024][2];  // pos, bitmask of used digits, tight

    long long solve(int pos, int mask, bool tight, bool started) {
        if (pos == (int)digits.size()) return started ? 1 : 0;

        // Create a combined state key (to avoid 4D DP)
        if (dp[pos][mask][tight] != -1 && started) return dp[pos][mask][tight];

        int limit = tight ? digits[pos] : 9;
        long long result = 0;

        for (int d = 0; d <= limit; d++) {
            if (started && (mask & (1 << d))) continue;  // Digit already used

            if (!started && d == 0) {
                result += solve(pos + 1, mask, false, false);  // Leading zero
            } else {
                result += solve(pos + 1, mask | (1 << d),
                               tight && (d == limit), true);
            }
        }
        if (started) dp[pos][mask][tight] = result;
        return result;
    }

public:
    long long count(long long N) {
        digits.clear();
        long long temp = N;
        while (temp > 0) { digits.push_back(temp % 10); temp /= 10; }
        reverse(digits.begin(), digits.end());
        memset(dp, -1, sizeof(dp));
        return solve(0, 0, true, false);
    }
};

/*
 * PROBLEM 4: Count numbers in [L, R] where digit sum is divisible by K
 *            (CSES: Counting Numbers variant / AtCoder S - Digit Sum)
 */
class DigitSumDivisible {
    vector<int> digits;
    long long dp[20][200][2];  // pos, sum_mod_k, tight
    int K;

    long long solve(int pos, int sumMod, bool tight) {
        if (pos == (int)digits.size()) return (sumMod == 0) ? 1 : 0;
        if (dp[pos][sumMod][tight] != -1) return dp[pos][sumMod][tight];

        int limit = tight ? digits[pos] : 9;
        long long result = 0;

        for (int d = 0; d <= limit; d++) {
            result += solve(pos + 1, (sumMod + d) % K, tight && (d == limit));
        }
        return dp[pos][sumMod][tight] = result;
    }

public:
    long long count(long long N, int k) {
        if (N < 0) return 0;
        K = k;
        digits.clear();
        long long temp = N;
        while (temp > 0) { digits.push_back(temp % 10); temp /= 10; }
        reverse(digits.begin(), digits.end());
        if (digits.empty()) digits.push_back(0);
        memset(dp, -1, sizeof(dp));
        return solve(0, 0, true);
    }
};

/*
 * PROBLEM 5: CSES — Counting Numbers
 *    Count numbers in [L, R] with no two adjacent digits same
 */
class NoAdjacentSame {
    vector<int> digits;
    long long dp[20][10][2];  // pos, last_digit, tight

    long long solve(int pos, int last, bool tight, bool started) {
        if (pos == (int)digits.size()) return started ? 1 : 0;
        if (started && dp[pos][last][tight] != -1) return dp[pos][last][tight];

        int limit = tight ? digits[pos] : 9;
        long long result = 0;

        for (int d = 0; d <= limit; d++) {
            if (started && d == last) continue;
            if (!started && d == 0)
                result += solve(pos + 1, -1, false, false);
            else
                result += solve(pos + 1, d, tight && (d == limit), true);
        }
        if (started) dp[pos][last][tight] = result;
        return result;
    }

public:
    long long count(long long N) {
        if (N <= 0) return (N == 0) ? 1 : 0;
        digits.clear();
        long long temp = N;
        while (temp > 0) { digits.push_back(temp % 10); temp /= 10; }
        reverse(digits.begin(), digits.end());
        memset(dp, -1, sizeof(dp));
        return solve(0, -1, true, false);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== DIGIT DP ===" << endl;

    // Problem 1: Digit sum ≤ S
    DigitSumCounter dsc;
    cout << "\n--- Digit Sum ≤ 10 in [1, 100] ---" << endl;
    cout << "Count: " << dsc.count(100, 10) - 1 << endl;  // -1 for 0

    // Problem 2: Avoid digit
    AvoidDigitCounter adc;
    cout << "\n--- Numbers without digit 4 in [1, 100] ---" << endl;
    cout << "Count: " << adc.count(100, 4) - 1 << endl;

    // Problem 3: Unique digits
    UniqueDigitsCounter udc;
    cout << "\n--- Numbers with unique digits in [1, 1000] ---" << endl;
    cout << "Count: " << udc.count(1000) << endl;

    // Problem 4: Digit sum divisible by K
    DigitSumDivisible dsd;
    cout << "\n--- Digit sum divisible by 3 in [1, 100] ---" << endl;
    cout << "Count: " << dsd.count(100, 3) - 1 << endl;

    // Problem 5: No adjacent same
    NoAdjacentSame nas;
    cout << "\n--- No adjacent same digits in [1, 100] ---" << endl;
    cout << "Count: " << nas.count(100) << endl;

    return 0;
}

