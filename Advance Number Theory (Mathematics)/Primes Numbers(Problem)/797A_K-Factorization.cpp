// Author: sarvan.dp.grandmaster
// Created: 2025-12-30 16:56:49
// Problem: A. k-Factorization
// Contest: Codeforces - Educational Codeforces Round 19
// URL: https://codeforces.com/problemset/problem/797/A
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
    i64 n, k;
    cin >> n >> k;

    vector<i64> ans;

    // 1. Extract small factors to fill the first k-1 spots
    // We add 'ans.size() < k - 1' to the loop condition to stop early
    for (i64 i = 2; i * i <= n && ans.size() < k - 1; i++) {
        while (n % i == 0 && ans.size() < k - 1) {
            ans.pb(i);
            n /= i;
        }
    }

    // 2. CHECK:
    // Case A: We didn't find k-1 factors (ans.size() < k - 1)
    // Case B: We found k-1 factors, but the remaining 'n' became 1 (n == 1)
    //         This means the k-th factor would be 1, which is invalid.
    if (ans.size() < k - 1 || n == 1) {
        cout << -1 << nl;
        return;
    }

    // 3. Add the last remaining part of n as the k-th factor
    ans.pb(n);

    for (auto x : ans) cout << x << " ";
    cout << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    solve();
    
    return 0;
}