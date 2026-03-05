/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-05 11:46:44
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

/* Problem Link : LeetCode 1095. Find in Mountain Array
 * Difficulty : Hard
 * This is an interactive problem.
 *
 * You may recall that an array arr is a mountain array if and only if:
 * - arr.length >= 3
 * - There exists some i with 0 < i < arr.length - 1 such that:
 *   - arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
 *   - arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
 * Given a mountain array mountainArr, return the minimum index such that mountainArr.get(index) == target. If such an index doesn't exist, return -1.
 * You cannot access the mountain array directly. You may only access the array using a MountainArray interface:
 * - MountainArray.get(k) returns the element of the array at index k (0-indexed).
 * - MountainArray.length() returns the length of the array.
 *
 * Example 1:
 * Input: mountainArr = [1,2,3,4,5,3,1], target = 3
 * Output: 2
 * Explanation: 3 exists in the array, at index 2 and index 5. Return the minimum index, which is 2.
 *
 * Example 2:
 * Input: mountainArr = [0,1,2,4,2,1], target = 3
 * Output: -1
 * Explanation: 3 does not exist in the array, so we return -1.
 *
 * Constraints:
 * - 3 <= mountain_arr.length() <= 10^4
 * - 0 <= target <= 10^9
 * - 0 <= mountain_arr.get(index) <= 10^9
 */

// ==========================================
// 1. MOCK API SETUP (The Black Box)
// ==========================================
class MountainArray {
    vec<int> arr;
    int call_count; // To track if we stay under 100

public:
    MountainArray(vec<int> a) {
        arr = a;
        call_count = 0;
    }

    int get(int index) {
        call_count++;
        return arr[index];
    }

    int length() {
        return sz(arr);
    }

    // Custom helper just for our local testing to verify efficiency
    int getCallCount() {
        return call_count;
    }
};

// ==========================================
// 2. YOUR SOLUTION CLASS
// ==========================================
class Solution {
public:
    static int findInMountainArray(int target, MountainArray &mountainArr) {
        int n = mountainArr.length();

        // --------------------------------------------------
        // STEP 1: FIND THE PEAK (Standard LC 852 Logic)
        // --------------------------------------------------
        int left = 0, right = n - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (mountainArr.get(mid) < mountainArr.get(mid + 1)) {
                // We are walking uphill, peak is to the right
                left = mid + 1;
            } else {
                // We are at peak or walking downhill, peak is left/current
                right = mid;
            }
        }
        int peak = left; // We found the summit!

        // --------------------------------------------------
        // STEP 2: BINARY SEARCH ON ASCENDING LEFT SLOPE
        // --------------------------------------------------
        left = 0;
        right = peak;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int mid_val = mountainArr.get(mid);

            if (mid_val == target) return mid; // Target found on left slope!

            if (mid_val < target) {
                left = mid + 1; // Standard ascending binary search
            } else {
                right = mid - 1;
            }
        }

        // --------------------------------------------------
        // STEP 3: BINARY SEARCH ON DESCENDING RIGHT SLOPE
        // --------------------------------------------------
        left = peak + 1;
        right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int mid_val = mountainArr.get(mid);

            if (mid_val == target) return mid; // Target found on right slope!

            // GM INSIGHT: Notice the reversed logic here!
            // Because the right slope goes DOWN, if mid_val > target,
            // the target must be further to the right (down the hill).
            if (mid_val > target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // Target doesn't exist anywhere on the mountain
        return -1;
    }
};

// 3. LEETCODE-STYLE TEST SUITE
struct TestCase {
    vector<int> arr;
    int target;
    int expected;
};

int main() {
    cout << "--- LEETCODE 1095: LOCAL TEST SUITE ---\n\n";

    Solution sol;

    vector<TestCase> test_cases = {
        {{1,2,3,4,5,3,1}, 3, 2},    // Example 1: Exists on both sides, return left
        {{0,1,2,4,2,1}, 3, -1},     // Example 2: Does not exist
        {{1,5,2}, 2, 2},            // Minimal mountain array
        {{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,19,18,17}, 19, 18} // Large test
    };

    for (int i = 0; i < test_cases.size(); i++) {
        MountainArray mockAPI(test_cases[i].arr);

        cout << "Test " << (i + 1) << " | Target: " << test_cases[i].target << "\n";

        int result = Solution::findInMountainArray(test_cases[i].target, mockAPI);
        int calls_made = mockAPI.getCallCount();

        if (result == test_cases[i].expected) {
            cout << "  -> [PASS] Result: " << result << "\n";
        } else {
            cout << "  -> [FAIL] Expected " << test_cases[i].expected << " but got " << result << "\n";
        }

        // Verify system constraint
        if (calls_made <= 100) {
            cout << "  -> [API OK] " << calls_made << " calls made (Limit: 100)\n\n";
        } else {
            cout << "  -> [API FAIL] " << calls_made << " calls made! Exceeded 100 limit!\n\n";
        }
    }

    return 0;
}
