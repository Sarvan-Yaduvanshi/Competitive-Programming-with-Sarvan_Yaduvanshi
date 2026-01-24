/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-04 23:05:10
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

// Method 1: Manual Implementation (Standard Linear Scan)
// Complexity: 2(N-1) comparisons
// GM Note: Safe initialization using arr[0] handles all data types automatically.
pii findMinMax(const vec<int>& arr) {
    if (arr.empty()) return {INT_MAX, INT_MIN}; // Safety check

    int mnVal = arr[0];
    int mxVal = arr[0];

    for (int i = 1; i < sz(arr); i++) {
        if (arr[i] < mnVal) mnVal = arr[i];
        else if (arr[i] > mxVal) mxVal = arr[i]; // 'else if' saves 1 comp in best case
    }

    return {mnVal, mxVal};
}

// Method 2: Tournament Method (3N/2 - 2 comparisons)
// GM Note: This minimizes comparisons, but branching logic might make it
// slower than Method 1 on modern CPUs due to branch misprediction and lack of SIMD.
pii findMinMaxOptimal(const vec<int>& arr) {
    int n = sz(arr);
    if (n == 0) return {INT_MAX, INT_MIN};

    int mnVal, mxVal;
    int i;

    // Correct Initialization Logic
    if (!(n & 1)) {
        // If Even: Initialize with the first pair
        if (arr[0] < arr[1]) {
            mnVal = arr[0];
            mxVal = arr[1];
        } else {
            mnVal = arr[1];
            mxVal = arr[0];
        }
        i = 2; // Start loop from index 2
    } else {
        // If Odd: Initialize with the first element
        mnVal = mxVal = arr[0];
        i = 1; // Start loop from index 1
    }

    // Process elements in pairs
    while (i < n - 1) {
        if (arr[i] < arr[i + 1]) {
            if (arr[i] < mnVal) mnVal = arr[i];
            if (arr[i + 1] > mxVal) mxVal = arr[i + 1];
        } else {
            if (arr[i + 1] < mnVal) mnVal = arr[i + 1];
            if (arr[i] > mxVal) mxVal = arr[i];
        }
        i += 2;
    }

    return {mnVal, mxVal};
}

void solve() {
    int n; cin >> n;
    vec<int> arr(n); read(arr);

    // Method 1
    pii ans = findMinMax(arr);
    cout << "M1 -> Min: " << ans.fi << ", Max: " << ans.se << nl;

    // Method 2
    pii ans2 = findMinMaxOptimal(arr);
    cout << "M2 -> Min: " << ans2.fi << ", Max: " << ans2.se << nl;

    // Method 3: STL (What a GM actually types in a contest)
    // std::minmax_element is optimized by compiler developers to be as fast as possible.
    if (!arr.empty()) {
        auto res = minmax_element(all(arr));
        cout << "STL -> Min: " << *res.fi << ", Max: " << *res.se << nl;

        // C++17 Structured binding version (Careful with iterators)
        // auto [mn_it, mx_it] = minmax_element(all(arr));
        // cout << *mn_it << " " << *mx_it << nl;
    }
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

