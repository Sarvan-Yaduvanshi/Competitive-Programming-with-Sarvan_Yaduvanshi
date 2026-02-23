// Author: sarvan.dp.grandmaster
// Created: 2026-02-23 20:12:05
// Problem: B. ABAB Construction
// Contest: Codeforces - Codeforces Round 1082 (Div. 2)
// URL: https://codeforces.com/contest/2202/problem/B
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
    int n; string x;
    cin >> n >> x;

    int mn_k = 0, mx_k = 0;
    int msk = 2; 

    for (int i = 1; i <= n; ++i) {
        int nMin = INF32;
        int nMax = -INF32;
        int nMsk = 0;
        
        char tar = x[i-1];

        auto update_state = [&](int l, int r, int p) {
            if (l > r) return;
            nMin = min(nMin, l);
            nMax = max(nMax, r);
            
            if (p == 0) nMsk |= 2;
            else nMsk |= 1;
        };

        for (int p = 0; p <= 1; ++p) {
            int bit = (p == 0 ? 1 : 0); 
            if (!((msk >> bit) & 1)) continue;

            int s = mn_k;
            if ((s & 1) != p) s++; 
            
            int e = mx_k;
            if ((e & 1) != p) e--; 
            
            if (s > e) continue;

            char charL = (p == 0 ? 'a' : 'b');
            if (tar == '?' || tar == charL) {
                update_state(s + 1, e + 1, 1 - p);
            }

            i64 idx_val = (i64)n - i + 1 + s;
            char charR = (idx_val % 2 != 0 ? 'a' : 'b');

            if (tar == '?' || tar == charR) {
                update_state(s, e, p);
            }
        }

        if (nMsk == 0) {
            NO;
            return;
        }

        mn_k = nMin;
        mx_k = nMax;
        msk = nMsk;
    }

    YES;
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