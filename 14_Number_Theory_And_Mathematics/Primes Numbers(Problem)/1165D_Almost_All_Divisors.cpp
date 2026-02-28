// Author: sarvan.dp.grandmaster
// Created: 2025-12-29 02:32:50
// Problem: D. Almost All Divisors
// Contest: Codeforces - Codeforces Round 560 (Div. 3)
// URL: https://codeforces.com/problemset/problem/1165/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms

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
    i64 n; cin >> n;
    
    v1(d, n); take(d);
    
    // Step 1: Sort to easily find the smallest and largest divisor
    sort(all(d));
    
    // Step 2: Guess the secret number X
    // Formula: Smallest Divisor * Largest Divisor
    i64 secretX = d[0] * d[n - 1];  
    
    // Step 3: Verify X by generating its REAL list of divisors
    vec<i64> realDivisors;
    
    // We iterate from 2 up to sqrt(x)
    for (i64 i = 2; i * i <= secretX; i++) {
        if (secretX % i == 0) {
            realDivisors.pb(i);
            if (i != secretX / i) realDivisors.pb(secretX / i);
        }
    }
    
    // Sort our generated list to compare it with the input list
    sort(all(realDivisors));
    
    // Step 4: Compare
    if (realDivisors == d) cout << secretX << nl;
    else cout << -1 << nl;
    
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