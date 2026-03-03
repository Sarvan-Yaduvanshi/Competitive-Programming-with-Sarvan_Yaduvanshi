/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-03 21:02:57
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

/* Problem: Given a sorted array and a target value,
 * find the number of occurrences of the target in the array.
 *
 * Example: arr = [1, 2, 2, 3, 4], target = 2 → Output: 2
 * Example: arr = [1, 1, 1, 1], target = 1 → Output: 4
 *
 * Approach: Use Upper Bound and Lower Bound to find the count of occurrences.
 * Time Complexity: O(log n) due to two binary searches.
 * Space Complexity: O(1) if we ignore input storage.
*/

// Manual lower_bound: first index with arr[index] >= k
int lowerBound(const vec<int>& arr, int k){
    int lo = 0;
    int hi = sz(arr);

    while (lo < hi){
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] < k) lo = mid + 1;
        else hi = mid; // arr[mid] >= k, could be the answer
    }
    return lo;
}

// Manual upper_bound: first index with arr[index] > k
int upperBound(const vec<int>& arr, int k){
    int lo = 0;
    int hi = sz(arr);

    while (lo < hi){
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] <= k) lo = mid + 1;
        else hi = mid; // arr[mid] > k, could be the answer
    }
    return lo;
}

void solve() {
    int n, target;
    cin >> n >> target;
    vec<int> arr(n);
    read(arr);

    int count = upperBound(arr, target) - lowerBound(arr, target);
    cout << count << nl;

    // Using STL
    // auto [lo_it, hi_it] = equal_range(all(arr), target);
    // int count_stl = hi_it - lo_it;
    // cout << count_stl << nl;
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

