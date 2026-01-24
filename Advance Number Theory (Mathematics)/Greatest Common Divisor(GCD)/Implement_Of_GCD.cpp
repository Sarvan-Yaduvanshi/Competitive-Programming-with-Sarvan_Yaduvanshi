/*
Author: Sarvan.DP.GrandMaster
Created : 2025-12-29 18:54:39
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

#define v1(v, n) vec<i64> v(n)
#define take(v) for(auto &x : v) cin >> x
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

// Method 1 : Naive Code (Brute Force): Check every number from the smaller input down to 1.
// Time Complexity: O(min(a, b)) -> Too Slow for large numbers!
i64 gcd_naive(i64 a, i64 b){
    // Step 1 : first cal min(a, b)
    i64 ans = min(a, b);

    while (ans > 0){
        if (a % ans == 0 && b % ans == 0) break;
        ans--;
    }

    return ans;
}

// Method 2 : Level 1: The Euclidean Algorithm (Standard Level)
// The Logic: If a number divides both A and B, it must also divide their difference (A - B)
//    *. GCD(20, 12) is the same as GCD(20-12, 12) -> GCD(8, 12)
//    *. Keep subtracting the smaller number from the larger one until one becomes 0.
// Better Logic (Modulo): Instead of subtracting repeatedly (which is slow), use % (modulo).
// GCD(a, b) = GCD(b%a, b)
// Code (Recursive - Most Common):
i64 recursiveGCD(i64 a, i64 b){
    if (a == 0) return b;
    return gcd(b % a, b);
}

// Method 3 : Iterative Through Cal GCD
i64 iterativeGCD(i64 a, i64 b){
    while (a){
        i64 temp = a;
        a = b % a;
        b = temp;
    }

    return b;
}


void solve() {
    i64 a, b;
    cout << "Enter a first number : "; cin >> a;
    cout << "Enter a second number : "; cin >> b;

    // Method 1 :  Fun Call and print
    i64 ans = gcd_naive(a, b);
    cout << "GCD(" << a << ", " << b << ") : " << ans << nl;

    // Method 2 :  Fun Call and print
    i64 ans1 = recursiveGCD(a, b);
    cout << "GCD(" << a << ", " << b << ") : " << ans1 << nl;

    // Method 3 :  Fun Call and print
    i64 ans2 = iterativeGCD(a, b);
    cout << "GCD(" << a << ", " << b << ") : " << ans2 << nl;

    // Method 4 : GM Tip: Since C++17, there is a built-in function. Always use this in contests to avoid bugs.
    cout << "GCD(" << a << ", " << b << ") : " << std::gcd(a, b) << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);

    // int TC = 1;
    // cin >> TC;
    // while (TC--) solve();
    
    solve();
    return 0;
}

