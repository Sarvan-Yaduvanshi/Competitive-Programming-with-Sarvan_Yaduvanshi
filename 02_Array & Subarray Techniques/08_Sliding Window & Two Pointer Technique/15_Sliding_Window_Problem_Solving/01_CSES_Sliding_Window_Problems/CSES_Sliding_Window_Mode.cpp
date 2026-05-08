// Author: sarvan.dp.grandmaster
// Created: 2026-05-05 10:29:48
// Problem: Sliding Window Mode
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/3224
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

void solve() {
    int n, k;
    cin >> n >> k;
    
    vec<int> a(n);
    read(a);
    
    map<int, int> freq;
    
    // stores {-frequency, value}
    set<pii> mode_set;
    vec<int> ans;
    
    for (int i = 0; i < n; i++) {
        int curr = a[i];
        
        if (freq[curr] > 0) 
            mode_set.erase({-freq[curr], curr});

        freq[curr]++;
        mode_set.insert({-freq[curr], curr});
        
        if (i >= k) {
            int rem = a[i - k];
            mode_set.erase({-freq[rem], rem});
            freq[rem]--;
            if (freq[rem] > 0) 
                mode_set.insert({-freq[rem], rem});
        }
        
        if (i >= k - 1) {
            ans.pb(mode_set.begin()->se);
        }
    }
    
    for (auto x : ans) {
        cout << x << " ";
    }
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