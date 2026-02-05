// Author: sarvan.dp.grandmaster
// Created: 2026-02-05 12:15:19
// Problem: C. Little Girl and Maximum Sum
// Contest: Codeforces - Codeforces Round 169 (Div. 2)
// URL: https://codeforces.com/problemset/problem/276/C
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
    int n, q;
    cin >> n >> q;
    
    vec<int> a(n);
    read(a);
    
    vec<i64> diff(n + 2, 0);
    
    while (q--) {
        int l, r;
        cin >> l >> r;
        
        diff[l - 1]++; // convert 1 based to 0 index
        diff[r]--;
    }
    
    vec<i64> freq(n);
    i64 curr = 0;
    
    for (int i = 0; i < n; i++) {
        curr += diff[i];
        
        freq[i] = curr;
    }
    
    sort(all(a));
    sort(all(freq));
    
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        ans += a[i] * freq[i];
    }
    
    cout << ans << nl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);
    
    solve();
       
    return 0;
}