/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-24 15:25:29
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
using ld = long double;
template<class T>
using vec = vector<T>;
template<class T>
using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

// --- Constants ---
constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD = 1'000'000'007LL;
constexpr i64 MOD9 = 998'244'353LL;
constexpr ld PI = 3.14159265358979323846;

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
void read(vec<T>& v){
    for (auto& x : v) cin >> x;
}

#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

inline i64 gcd(i64 a, i64 b){ return std::gcd(a, b); }
inline i64 lcm(i64 a, i64 b){ return (a / std::gcd(a, b)) * b; }

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD){
    i64 res = 1;
    base %= mod;
    while (exp > 0){
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

/**
 * PROBLEM: Partition Array into Two Subarrays with Equal Sum
 * * LOGIC:
 * We need to find an index 'i' such that Sum(0...i) == Sum(i+1...n-1).
 * Let TotalSum = Sum(0...n-1).
 * If Sum(0...i) == Sum(i+1...n-1), then 2 * Sum(0...i) == TotalSum.
 * * COROLLARY:
 * 1. If TotalSum is ODD, partition is impossible -> Return False immediately.
 * 2. We only need to find a prefix sum equal to TotalSum / 2.
 */

// Approach 1: Brute Force
// Checks every possible split point independently.
// Time: O(N^2) | Space: O(1)
// note: Use i64 for sums to prevent overflow on large inputs.
bool checkBruteForce(const vec<int>& a) {
    int n = sz(a);

    // Split point i: Left subarray is a[0...i], Right is a[i+1...n-1]
    for (int i = 0; i < n - 1; i++) {
        i64 leftSum = 0, rightSum = 0;

        for (int j = 0; j <= i; j++) leftSum += a[j];
        for (int j = i + 1; j < n; j++) rightSum += a[j];

        if (leftSum == rightSum) return true;
    }
    return false;
}

// Approach 2: Prefix Sum Optimization (Linear Scan)
// Accumulate prefix sum and derive suffix sum in O(1).
// Time: O(N) | Space: O(1)
bool checkLinear(const vec<int>& a) {
    int n = sz(a);

    // 1. Calculate Total Sum
    // using accumulate is cleaner, but loop is fine.
    i64 totalSum = 0;
    for (int x : a) totalSum += x;

    // GM Optimization: Parity Check
    // If sum is odd, it's impossible to split into two integers.
    if (totalSum % 2 != 0) return false;

    // 2. Iterate and check split points
    i64 leftSum = 0;

    // Iterate up to n-2 because right subarray must be non-empty
    // (Last valid split is at index n-2, leaving a[n-1] for right side)
    for (int i = 0; i < n - 1; i++) {
        leftSum += a[i];

        // Mathematical Check: Is current prefix half of total?
        // Equivalent to: if (leftSum == totalSum - leftSum)
        if (leftSum * 2 == totalSum) {
            return true;
        }
    }

    return false;
}

void solve() {
    int n;
    cin >> n;
    vec<int> a(n);
    read(a);

    // In a contest, usually only the optimal solution is submitted.
    bool possible = checkLinear(a);

    cout << (possible ? "YES" : "NO") << nl;
}

int main(){
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

