// Author: sarvan.dp.grandmaster
// Created: 2025-12-30 16:35:30
// Problem: A. Gregor and Cryptography
// Contest: Codeforces - Codeforces Round 736 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1549/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms

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
// Use rng() to get a random number. Much faster/better than rand().
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
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

void solve() {
    i64 p; 
    cin >> p;

    // We always fix a = 2
    // Reason:
    // - If p is odd, then p % 2 = 1
    // - If p is even, then p % 2 = 0

    // Case 1: p is odd (true for all primes >= 5)
    // Choose b = p - 1
    // p % (p - 1) = 1
    // So: p % 2 == p % (p - 1)
    if (p & 1) {
        cout << 2 << " " << p - 1 << nl;
    }
    // Case 2: p is even (theoretical safety, not needed for constraints)
    // p % 2 = 0
    // p % p = 0
    else {
        cout << 2 << " " << p << nl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    int TC = 1;
    cin >> TC; 
    while(TC--) {
        solve();
    }
    return 0;
}