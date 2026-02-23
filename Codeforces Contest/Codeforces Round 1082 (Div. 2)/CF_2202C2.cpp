// Author: sarvan.dp.grandmaster
// Created: 2026-02-23 20:38:08
// Problem: C2. Lost Civilization (Hard Version)
// Contest: Codeforces - Codeforces Round 1082 (Div. 2)
// URL: https://codeforces.com/contest/2202/problem/C2
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
    int n;
    if (!(cin >> n)) return;
    
    vec<int> a(n);
    read(a);

    i64 ans = 1LL * n * (n + 1) / 2;

    vec<pii> st;
    st.reserve(n);

    st.pb({a[0], 1});

    for (int i = 1; i < n; ++i) {
        int x = a[i];
        int prev = a[i-1];
        int cnt_resets = 0;

        if (x > prev + 1) {
            cnt_resets = i; 
            st.clear();
            st.pb({x, i + 1});
        } 
        
        else {
            int merged_cnt = 0;
            
            while (!st.empty() && st.back().fi >= x) {
                merged_cnt += st.back().se;
                st.pop_back();
            }
            
            cnt_resets = merged_cnt;
            st.pb({x, merged_cnt + 1});
        }

        ans += 1LL* cnt_resets * (n - i);
    }

    cout << ans << nl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);
    
    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    
    return 0;
}