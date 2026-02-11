// Author: sarvan.dp.grandmaster
// Created: 2026-02-11 22:24:48
// Problem: D. Another Problem about Beautiful Pairs
// Contest: Codeforces - Codeforces Round 1079 (Div. 2)
// URL: https://codeforces.com/contest/2197/problem/D
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

constexpr int MAXN = 200005;
int a[MAXN];

void solve() {
    int n; cin >> n;

    int B = sqrt(n); 
    
    for (int i = 1; i <= n; i++) 
        cin >> a[i];

    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] <= B) {
            for (int y = 1; y <= B; y++) {
                i64 j = i + 1ll * a[i] * y;
                if (j > n) break;
                if (a[j] == y) ans++;
            }
        
        } else {
            for (int k = 1; ; k++) {
                i64 j = i + 1ll * a[i] * k;
                if (j > n) break;
                if (a[j] == k) ans++;
            }
        }
    }

    for (int j = 1; j <= n; j++) {
        if (a[j] > B) {
            for (int k = 1; k <= B; k++) {
                i64 i = j - 1ll * a[j] * k;
                if (i < 1) break; 
                if (a[i] == k) ans++;
            }
        }
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