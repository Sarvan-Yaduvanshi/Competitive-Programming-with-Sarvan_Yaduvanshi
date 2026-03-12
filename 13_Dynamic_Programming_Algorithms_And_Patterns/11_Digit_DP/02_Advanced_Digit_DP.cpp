/*
 * ============================================================================
 *       ADVANCED DIGIT DP — BITMASK + DIGIT DP, SUM OF DIGITS
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : Digit DP — Advanced: Bitmask inside, Sum of digits in range
 * Level   : ⭐⭐⭐⭐⭐ Grandmaster
 * ============================================================================
 *
 * 1. SUM OF DIGITS in range [L, R]
 *    Not just counting — compute the actual SUM of all digits of all numbers.
 *
 * 2. BITMASK inside DIGIT DP
 *    Track which digits have been used (for unique digit constraint).
 *
 * 3. Count numbers divisible by K in range
 *
 * 4. Number of Digit One (LeetCode 233)
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

/*
 * 1. SUM OF ALL DIGITS of numbers in [1, N]
 *    For each position, compute contribution of each digit.
 *    dp[pos][tight] = {count, digit_sum}
 */
class DigitSumInRange {
    vector<int> digits;
    pair<long long, long long> dp[20][2];  // {count, sum}
    bool vis[20][2];

    pair<long long, long long> solve(int pos, bool tight) {
        if (pos == (int)digits.size()) return {1, 0};
        if (vis[pos][tight]) return dp[pos][tight];
        vis[pos][tight] = true;

        int limit = tight ? digits[pos] : 9;
        long long totalCount = 0, totalSum = 0;

        for (int d = 0; d <= limit; d++) {
            auto [cnt, sm] = solve(pos + 1, tight && (d == limit));
            totalCount += cnt;
            totalSum += sm + (long long)d * cnt;  // d contributes d * cnt times
        }
        return dp[pos][tight] = {totalCount, totalSum};
    }

public:
    long long sumOfDigits(long long N) {
        if (N <= 0) return 0;
        digits.clear();
        long long temp = N;
        while (temp > 0) { digits.push_back(temp % 10); temp /= 10; }
        reverse(digits.begin(), digits.end());
        memset(vis, false, sizeof(vis));
        return solve(0, true).second;
    }

    long long sumOfDigitsInRange(long long L, long long R) {
        return sumOfDigits(R) - sumOfDigits(L - 1);
    }
};

/*
 * 2. COUNT DIGIT 'D' appearances in [1, N]
 *    Example: LeetCode 233 (Number of Digit One, D=1)
 *    Generalized to any digit D.
 */
class CountDigitD {
    vector<int> digits;
    long long dp[20][20][2];  // pos, count_of_d, tight
    bool vis[20][20][2];
    int targetDigit;

    long long solve(int pos, int count, bool tight) {
        if (pos == (int)digits.size()) return count;
        if (vis[pos][count][tight]) return dp[pos][count][tight];
        vis[pos][count][tight] = true;

        int limit = tight ? digits[pos] : 9;
        long long result = 0;

        for (int d = 0; d <= limit; d++) {
            result += solve(pos + 1, count + (d == targetDigit),
                           tight && (d == limit));
        }
        return dp[pos][count][tight] = result;
    }

public:
    long long count(long long N, int D) {
        if (N <= 0) return 0;
        targetDigit = D;
        digits.clear();
        long long temp = N;
        while (temp > 0) { digits.push_back(temp % 10); temp /= 10; }
        reverse(digits.begin(), digits.end());
        memset(vis, false, sizeof(vis));
        return solve(0, 0, true);
    }
};

/*
 * 3. COUNT NUMBERS DIVISIBLE BY K in [1, N]
 *    Track remainder mod K as we build the number digit by digit.
 *    dp[pos][remainder][tight]
 */
class DivisibleByK {
    vector<int> digits;
    long long dp[20][1000][2];  // pos, rem, tight
    int K;

    long long solve(int pos, int rem, bool tight) {
        if (pos == (int)digits.size()) return (rem == 0) ? 1 : 0;
        if (dp[pos][rem][tight] != -1) return dp[pos][rem][tight];

        int limit = tight ? digits[pos] : 9;
        long long result = 0;

        for (int d = 0; d <= limit; d++) {
            result += solve(pos + 1, (rem * 10 + d) % K, tight && (d == limit));
        }
        return dp[pos][rem][tight] = result;
    }

public:
    long long count(long long N, int k) {
        if (N <= 0) return 0;
        K = k;
        digits.clear();
        long long temp = N;
        while (temp > 0) { digits.push_back(temp % 10); temp /= 10; }
        reverse(digits.begin(), digits.end());
        memset(dp, -1, sizeof(dp));
        return solve(0, 0, true) - 1;  // Subtract 0
    }
};

/*
 * 4. COUNT NUMBERS that are palindromes in [L, R]
 *    Two approaches: generate palindromes OR digit DP
 *    Here: digit DP with comparison to reversed number
 */
class PalindromeCounter {
    // Count d-digit palindromes ≤ N
    // For odd length d: determine first ceil(d/2) digits
    // For even length d: determine first d/2 digits

public:
    long long countPalindromes(long long L, long long R) {
        // Simple approach: generate all palindromes up to R
        // and count those ≥ L
        long long count = 0;

        // Generate palindromes by length
        for (int len = 1; len <= 18; len++) {
            int half = (len + 1) / 2;
            long long lo = (half == 1) ? 0 : (long long)pow(10, half - 1);
            long long hi = (long long)pow(10, half) - 1;

            for (long long h = lo; h <= hi; h++) {
                // Build palindrome from half
                string s = to_string(h);
                string rev = s;
                if (len % 2 == 1) rev = string(s.begin(), s.end() - 1);
                reverse(rev.begin(), rev.end());

                long long palindrome = stoll(s + rev);
                if (palindrome >= L && palindrome <= R) count++;
                if (palindrome > R) break;
            }
        }
        return count;
    }
};

/*
 * 5. CLASSY DIGIT DP — Numbers with increasing digits
 *    Count numbers in [1, N] whose digits are strictly increasing.
 *    Example: 123, 159, 2489 are valid. 112, 321 are not.
 */
class IncreasingDigits {
    vector<int> digits;
    long long dp[20][10][2];  // pos, last_digit, tight

    long long solve(int pos, int last, bool tight, bool started) {
        if (pos == (int)digits.size()) return started ? 1 : 0;
        if (started && dp[pos][last][tight] != -1) return dp[pos][last][tight];

        int limit = tight ? digits[pos] : 9;
        long long result = 0;

        for (int d = 0; d <= limit; d++) {
            if (started && d <= last) continue;  // Must be strictly increasing
            if (!started && d == 0)
                result += solve(pos + 1, 0, false, false);
            else
                result += solve(pos + 1, d, tight && (d == limit), true);
        }
        if (started) dp[pos][last][tight] = result;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== ADVANCED DIGIT DP ===" << endl;

    // Sum of digits
    DigitSumInRange dsir;
    cout << "\n--- Sum of Digits in Range ---" << endl;
    cout << "Sum of digits [1, 100]: " << dsir.sumOfDigits(100) << endl;
    cout << "Sum of digits [50, 100]: " << dsir.sumOfDigitsInRange(50, 100) << endl;

    // Count digit D
    CountDigitD cdd;
    cout << "\n--- Count Digit Appearances ---" << endl;
    cout << "Digit 1 in [1, 100]: " << cdd.count(100, 1) << endl;
    cout << "Digit 0 in [1, 100]: " << cdd.count(100, 0) << endl;

    // Divisible by K
    DivisibleByK dbk;
    cout << "\n--- Divisible by K ---" << endl;
    cout << "Divisible by 7 in [1, 100]: " << dbk.count(100, 7) << endl;
    cout << "Divisible by 13 in [1, 1000]: " << dbk.count(1000, 13) << endl;

    // Palindromes
    PalindromeCounter pc;
    cout << "\n--- Palindrome Count ---" << endl;
    cout << "Palindromes in [1, 1000]: " << pc.countPalindromes(1, 1000) << endl;

    // Increasing digits
    IncreasingDigits id;
    cout << "\n--- Numbers with Increasing Digits ---" << endl;
    cout << "In [1, 1000]: " << id.count(1000) << endl;
    cout << "In [1, 100000]: " << id.count(100000) << endl;

    return 0;
}

