/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-20 09:37:19
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

/* Problem: 974. Subarray Sums Divisible by K
Given an integer array nums and an integer k,
return the number of non-empty subarrays that have a sum divisible by k.
A subarray is a contiguous part of an array.

Example 1:
Input: nums = [4,5,0,-2,-3,1], k = 5
Output: 7
Explanation: There are 7 subarrays with a sum divisible by k = 5:
[4, 5, 0, -2, -3, 1], sum = 5
[5], sum = 5
[5, 0], sum = 5
[5, 0, -2], sum = 3
[0], sum = 0
[0, -2, -3], sum = -5
[-2, -3], sum = -5

Example 2:
Input: nums = [5], k = 9
Output: 0

Constraints:
1 <= nums.length <= 3 * 104
-104 <= nums[i] <= 104
2 <= k <= 104

*/

// Approach 1: Use Brute Force
// Time Complexity: O(n^2) for checking all subarrays and calculating their sums.
// Space Complexity: O(1) if we don't count the input and output space.
int subarraysDivByKBruteForce(const vec<int>& nums, int k) {
    int count = 0;
    int n = sz(nums);

    for (int start = 0; start < n; start++) {
        int sum = 0;
        for (int end = start; end < n; end++) {
            sum += nums[end];
            if (sum % k == 0) {
                count++;
            }
        }
    }

    return count;
}

// Approach 2: Use Prefix Sum and Hash Map
// Logic: We can use a hash map to store the frequency of prefix sums modulo k.
// If two prefix sums have the same modulo k value, it means the subarray between them
// has a sum that is divisible by k.
// Time Complexity: O(n) for iterating through the array once.
// Space Complexity: O(k) for the hash map storing frequencies of modulo values.
int subarraysDivByK(const vec<int>& nums, int k){
    unordered_map<int, int> remCnt;
    remCnt[0] = 1;
    int sum = 0;
    int cnt = 0;

    for (const auto& num : nums){
        sum += num;

        // Also this line handle negative number
        // rem = sum % k;
        // if (rem < 0) rem += k;
        int rem = ((sum % k) + k) % k; // Handle negative number +k
        cnt += remCnt[rem];
        remCnt[rem]++;
    }
    return cnt;
}

void solve() {
    int n, k;
    if (!(cin >> n >> k)) return;

    vec<int> a(n);
    read(a);

    cout << subarraysDivByK(a, k) << nl;
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

