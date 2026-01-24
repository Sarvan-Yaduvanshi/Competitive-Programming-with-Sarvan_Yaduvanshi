// Author: sDynamic_Sarvan
// Created: 2026-01-13 15:09:47
// Problem: Distinct Numbers
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1621
// Memory Limit: 512 MB
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

void solve() {
    i64 n; cin >> n;
    vec<i64> a(n); read(a);
    
    // Method 3 : Unique + Sorting -> Faster 
    // 1. Sort the array so duplicates are adjacent
    sort(all(a));
    
    // 2. unique moves duplicates to the end return itretor
    // 3. We subtract the begin iterator to get the count
    int ans = unique(all(a)) - a.begin();
    
    cout << ans << nl;
    
    // Method 2 : Set -> this is shorter, but slower
    // cout << set<int>(all(a)).size() << nl;
    
    // Method 1 : 
    // int cnt = 1;
    // for (int i = 0; i + 1 < n; i++) {
        // if (a[i] != a[i + 1]) cnt++;
    // }
    // cout << cnt << nl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);
    
    solve();
    
    return 0;
}