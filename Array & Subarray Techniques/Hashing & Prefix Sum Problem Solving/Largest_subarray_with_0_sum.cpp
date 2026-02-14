/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-13 00:06:32
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
/*
 * Problem: Given an array arr[] containing both positive and negative integers,
 * the task is to find the length of the longest subarray with a sum equals to 0.
 * Example: arr[] = [15, -2, 2, -8, 1, 7, 10, 23] --> Answer -> 5
 * The longest subarray with sum equals to 0 is [-2, 2, -8, 1, 7]
 */

// Approach 1: Using Brute force
// TC -> (N^2) | SC -> O(1)
int maxLengthBruteForce(const vec<int>& arr){
    int n = sz(arr);
    int ans = 0;

    for (int i = 0; i < n; i++){
        int currSum = 0;
        for (int j = i; j < n; j++){
            currSum += arr[j];
            if (currSum == 0)
                ans = max(ans, j - i + 1);
        }
    }
    return ans;
}

// Approach 2: Using Prefix Sums + Hashing
// Why hashmap is used: Because we want longest subarray, so we store the first occurrence
// TC -> O(N) | SC -> (N)
int maxLengthOptimal(const vec<int>& arr){
    int n = sz(arr);

    // Map to store (PrefixSum -> First Index)
    unordered_map<i64, int> mp;

    i64 sum = 0;
    int max_len = 0;

    for (int i = 0; i < n; i++){
        sum += arr[i];

        // Case 1: The cumulative sum itself is 0
        // Example: [1, -1] -> at index 1, sum is 0. Length is 1+1 = 2.
        if (sum == 0)
            max_len = max(max_len, i + 1);

        // Case 2: We have seen this sum before
        if (mp.contains(sum)){
            // The distance between the first occurrence and now
            int len = i - mp[sum];
            max_len = max(max_len, len);
        } else{
            // Case 3: First time seeing this sum, store it
            mp[sum] = i;
        }
    }
    return max_len;
}

void solve() {
    int n; cin >> n;
    vec<int> a(n);
    read(a);

    int ans = maxLengthOptimal(a);
    cout << ans << nl;
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

