/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-20 01:00:24
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

/* Problem: 169. Majority Element
Given an array of size n, find the majority element.
The majority element is the element that appears more than ⌊n/2⌋ times.
You may assume that the majority element always exists in the array.

Example 1:
Input: [3,2,3]
Output: 3

Example 2:
Input: [2,2,1,1,1,2,2]
Output: 2

Constraints:
- n == nums.length
- 1 <= n <= 5 * 10^4
- -10^9 <= nums[i] <= 10^9
*/

// Approach 1: Use Sorting Approach
// Time Complexity: O(n log n) due to sorting
// Space Complexity: O(1) if we ignore the sorting space, otherwise O(n)
int majorityElementSorting(const vector<int>& nums){
    int n = sz(nums);

    sort(all(nums));

    return nums[n / 2];
}

// Approach 2: Use Hash Map to count frequencies
// Time Complexity: O(n)
// Space Complexity: O(n) in the worst case if all elements are unique
int majorityElementHashMap(const vector<int>& nums){
    int n = sz(nums);

    unordered_map<int, int> mp;
    for (const auto& num : nums) {
        mp[num]++;
        if (mp[num] > n / 2) {
            return num;
        }
    }
    return -1;
}

/* * GM ANALYSIS:
 * Approach: Boyer-Moore Voting Algorithm
 * * Core Logic:
 * We maintain a 'candidate' and a 'count'.
 * - The 'count' represents the "lead" the current candidate has over all other elements combined.
 * - When 'count' drops to 0, it means the previous candidate was completely neutralized
 * (paired off 1-to-1) by other numbers. We must pick a new candidate.
 * * * Mathematical Guarantee:
 * Since the majority element appears > N/2 times, even if every non-majority element
 * "cancels out" one instance of the majority element, the majority element will
 * still have at least 1 instance remaining. It survives the "war of attrition".
 *
 * Time Complexity: O(N) - Single pass
 * Space Complexity: O(1) - No extra structures (unlike Hash Map)
 */
int majorityElementBoyerMoore(const vector<int>& nums) {
    int candidate = 0;
    int count = 0;

    for (const auto& num : nums) {
        if (count == 0)
            candidate = num;

        if (num == candidate) count++;
        else count--;
    }

    return candidate;
}

void solve() {
    int n;
    cin >> n;
    vector<int> nums(n);
    read(nums);

    int result = majorityElementBoyerMoore(nums);
    cout << result << nl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);
    
    // Multi-test case support (commented out for this demo)
    // int TC = 1;
    // cin >> TC;
    // while (TC--) solve();
    
    solve();
    return 0;
}

