/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-04 17:20:49
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

/* Problem: Find the K-th Rotation of a Sorted Array
 * Given an increasing sorted rotated array arr[] of distinct integers. The array is right-rotated k times. Find the value of k.
 * Let's suppose we have an array arr[] = [2, 4, 6, 9], if we rotate it by 2 times it will look like this:
 * After 1st Rotation : [9, 2, 4, 6]
 * After 2nd Rotation : [6, 9, 2, 4]
 *
 * Example 1:
 * Input: arr[] = {5 1 2 3 4}
 * Output: 1
 *
 * Example 2:
 * Input: arr[] = {1 2 3 4 5}
 * Output: 0
 *
 * Constraints:
 * 1 <= N <= 10^5
 * 1 <= arr[i] <= 10^7
 *
 * Note: You must write an efficient algorithm that runs in O(log N) time complexity.
*/

int findKthRotation(const vec<int>& arr){
    int lo = 0;
    int hi = sz(arr) - 1;

    while (lo < hi){
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] < arr[hi]){
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    return lo;
}

void solve() {
    int n;
    cin >> n;
    vec<int> arr(n);
    read(arr);

    int k = findKthRotation(arr);
    cout << k << nl;
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

