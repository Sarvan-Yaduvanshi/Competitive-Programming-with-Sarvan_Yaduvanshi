// Author: sarvan.dp.grandmaster
// Created: 2026-05-05 09:34:53
// Problem: Sliding Window Mex
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/3219
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
    int n, k; 
    cin >> n >> k;
    
    vec<int> a(n);
    read(a);
    
    vec<int> freq(n + 1, 0);
    set<int> miss_num;
    vec<int> ans;
    
    for (int i = 0; i <= k; i++)
        miss_num.insert(i);
        
    for (int i = 0; i < n; i++) {
        // Step 1: Add 
        int curr = a[i];
        if (curr <= k) {
            freq[curr]++;
            if (freq[curr] == 1)
                miss_num.erase(curr);
        }
        
        // Step 2: Remove if window are expire
        if (i >= k) {
            int prev_window_element = a[i - k];
            if (prev_window_element <= k) {
                freq[prev_window_element]--;
                if (freq[prev_window_element] == 0)
                    miss_num.insert(prev_window_element);
            }
        }
        
        // Step 3: Update Answer
        if (i >= k - 1)
            ans.pb(*miss_num.begin());
    }
    
    for (auto x : ans)
        cout << x << " ";
    cout << nl;
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