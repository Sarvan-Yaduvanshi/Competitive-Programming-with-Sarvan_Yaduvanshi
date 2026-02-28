/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-10 18:54:43
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

/* Problem: Leetcode 209. Minimum Size Subarray Sum
 * Given an array of positive integers nums and a positive integer target,
 * return the minimal length of a subarray whose sum is greater than or equal to target.
 * If there is no such subarray, return 0 instead
 * Example: nums = [2,3,1,2,4,3], target = 7, Answer -> 2 (4, 3) -> Minimum Length
 */

// Approach 1: Using Brute Force Logic
// TC -> O(N^2) | SC -> O(N)
int minSubArrayLen(int tar, const vec<int>& nums){
    int n = sz(nums);
    int mnSize = INT_MAX;

    for (int i = 0; i < n; i++){
        i64 currSum = 0;
        for (int j = i; j < n; j++){
            currSum += nums[j];
            if (currSum >= tar)
                mnSize = min(mnSize, j - i + 1); // update answer minimum length
        }
    }
    return (mnSize == INT_MAX ? 0 : mnSize);
}

// Approach 2: Using Prefix Sum + Binary Search
// TC -> O(N logN) | SC -> O(N)
int minSubArrayLenPrefixSum(int tar, const vec<int>& nums){
    int n = sz(nums);
    int mnSize = INT_MAX;

    // Step 1: Build Prefix Sum
    vec<i64> pref(n + 1, 0);
    for (int i = 0; i < n; i++)
        pref[i + 1] = pref[i] + nums[i];

    // Step 2: for every start idx
    for (int i = 0; i < n; i++){
        i64 req = tar + pref[i];

        // Step 3: find smallest k using binary search
        int lo = 0, hi = n, idx = -1;
        while (lo <= hi){
            int mid = lo + (hi - lo) / 2;
            if (pref[mid] >= req){
                idx = mid;
                hi = mid - 1;
            } else lo = mid + 1;
        }
        // Step 4: update answer = min(answer, k - i)
        if (idx != -1) mnSize = min(mnSize, idx - i);
    }
    return (mnSize == INT_MAX ? 0 : mnSize);
}

void solve() {
    int n; cin >> n;
    vec<int> nums(n);
    read(nums);

    int tar; cin >> tar;
    cout << minSubArrayLen(tar, nums) << nl;
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

