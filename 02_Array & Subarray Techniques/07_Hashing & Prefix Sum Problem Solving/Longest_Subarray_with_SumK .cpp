/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-14 15:51:11
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

// Problem: Give an array and a sum K, find the length of the longest subarray with sum K.
// Example: arr = [1, -1, 5, -2, 3], K = 3
// Subarrays with sum 3 are:
// [1, -1, 5, -2] -> length = 4
// [5, -2] -> length = 2
// [3] -> length = 1
// Answer: 4 (the longest ones are of length 4)

// Approach 1: Brute Force
// Time Complexity -> O(N^2) | Space Complexity -> O(1)
int longestSubarrayBruteForce(const vec<int>& arr, int K){
    int n = sz(arr);
    int ans = 0;

    for (int i = 0; i < n; i++){
        int currSum = 0;
        for (int j = i ; j < n; j++){
            currSum += arr[j];
            if (currSum == 0)
                ans = max(ans, j - i + j);
        }
    }
    return ans;
}

// Approach 2: Using a Prefix Sum + Hashing
// Time Complexity -> O(N) | Space Complexity -> O(N)
int longestSubarrayUsingPrefixSum(const vec<int>& arr, int k){
    int n = sz(arr);
    unordered_map<int, int> prefixSum;
    prefixSum[0] = -1;

    int max_len = 0;
    int currSum = 0;

    for (int i = 0; i < n; i++){
        currSum += arr[i];

        if (prefixSum.contains(currSum - k)){
            max_len = max(max_len, i - prefixSum[currSum - k]);
        }

        if (!prefixSum.contains(currSum)){
            prefixSum[currSum] = i;
        }
    }
    return max_len;
}

void solve() {
    int n; cin >> n;
    vec<int> arr(n); read(arr);
    int k; cin >> k;

    cout << longestSubarrayUsingPrefixSum(arr, k) << nl;
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

