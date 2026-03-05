/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-05 10:52:15
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

// --- Type Definitions ---
using i64 = long long;
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

// --- Constants ---
constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;

// --- Random Number Generator ---
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// --- Macros ---
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

// Input helper
template<class T>
void read(vec<T> &v) {
    for (auto &x : v) cin >> x;
}
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

inline i64 gcd(i64 a, i64 b) { return std::gcd(a, b); }
inline i64 lcm(i64 a, i64 b) { return (a / std::gcd(a, b)) * b; }

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD) {
    i64 res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

/* Problem: LeetCode 278. First Bad Version
 * You are a product manager and currently leading a team to develop a new product. Unfortunately,
 * the latest version of your product fails the quality check. Since each version is developed based on the previous version,
 * all the versions after a bad version are also bad.
 *
 * Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one,
 * which causes all the following ones to be bad.
 *
 * You are given an API bool isBadVersion(version) which returns whether version is bad.
 * Implement a function to find the first bad version. You should minimize the number of calls to the API.
 *
 * Example 1:
 * Input: n = 5, bad = 4
 * Output: 4
 * Explanation:
 * call isBadVersion(3) -> false
 * call isBadVersion(5) -> true
 * call isBadVersion(4) -> true
 * Then 4 is the first bad version.
 *
 * Example 2:
 * Input: n = 1, bad = 1
 * Output: 1
 * Explanation:
 * call isBadVersion(1) -> true
 * Then 1 is the first bad version.
 *
 *
 * Constraints:
 *     1 <= bad <= n <= 231 - 1

 THEORY:
 ───────
 We have versions 1 to n. Once a version is bad, all future versions are bad.
 This creates a monotonic condition: F, F, F, T, T, T, T
 We need to find the FIRST 'T' (True).

 APPROACH: Binary Search on Answer
   1. Search space is from 1 to n (NOT 0 to n-1, because versions are 1-indexed).
   2. If mid is BAD, the first bad version is either mid, or something before mid.
      So we pull the right boundary in: hi = mid.
   3. If mid is GOOD, the first bad version MUST be after mid.
      So we push the left boundary up: lo = mid + 1.
*/

// GM LEVEL: LEETCODE 278 (FIRST BAD VERSION) VIA EXPONENTIAL SEARCH
// 1. MOCK API SETUP
i64 SECRET_BAD_VERSION = 0;

bool isBadVersion(i64 version) {
    return version >= SECRET_BAD_VERSION;
}

class Solution {
public:
    static int firstBadVersion(int n) {
        int lo = 1, hi = n;

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (isBadVersion(mid)) {
                hi = mid; // First bad version is at mid or before
            } else {
                lo = mid + 1; // First bad version is after mid
            }
        }
        return lo; // At the end, lo == hi and points to the first bad version
    }
};

// 3. LEETCODE-STYLE TEST SUITE
// A struct to pair 'n' (total versions) and 'bad' (the secret target)
struct TestCase {
    int n;
    int bad;
};

int main() {
    cout << "--- LEETCODE 278: LOCAL TEST SUITE ---\n\n";

    Solution sol;

    // CHANGED: Here are your multiple test cases!
    // Format: {n, bad}
    vector<TestCase> test_cases = {
        {5, 4},             // Example 1 from LeetCode
        {1, 1},             // Example 2 from LeetCode (Minimum bounds)
        {10, 7},            // Standard middle-of-the-pack test
        {2147483647, 2147483647}, // Extreme Edge Case: Both n and bad are INT_MAX
        {2147483647, 1}     // Extreme Edge Case: Massive n, but bad is right at the start
    };

    int passed = 0;
    int total_tests = test_cases.size();

    // Loop through every single test case automatically
    for (int i = 0; i < total_tests; i++) {
        int current_n = test_cases[i].n;
        int current_bad = test_cases[i].bad;

        // 1. Tell our mock API what the correct answer is for this round
        SECRET_BAD_VERSION = current_bad;

        cout << "Test " << (i + 1) << " | Input: n = " << current_n << ", bad = " << current_bad << "\n";

        // 2. Run your code
        int result = sol.firstBadVersion(current_n);

        // 3. Verify the output
        if (result == current_bad) {
            cout << "  -> [PASS] Found: " << result << "\n\n";
            passed++;
        } else {
            cout << "  -> [FAIL] Expected: " << current_bad << " but got: " << result << "\n\n";
        }
    }

    cout << "=======================================\n";
    cout << "FINAL RESULT: " << passed << " / " << total_tests << " TESTS PASSED\n";
    cout << "=======================================\n";

    return 0;
}