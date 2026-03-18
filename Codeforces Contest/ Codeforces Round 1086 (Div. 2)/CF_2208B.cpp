// Author: sarvan.dp.grandmaster
// Created: 2026-03-14 20:12:25
// Problem: B. Cyclists
// Contest: Codeforces - Codeforces Round 1086 (Div. 2)
// URL: https://codeforces.com/contest/2208/problem/B
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
    i64 n, k, p, m;
    cin >> n >> k >> p >> m;

    vec<i64> a(n);
    read(a);

    i64 w_cost = a[p - 1];
    i64 cost_init = 0;

    if (p > k) {
        vec<i64> pre(a.begin(), a.begin() + p - 1);
        sort(all(pre));

        int shifts = p - k;
        for (int i = 0; i < shifts; i++) 
            cost_init += pre[i];
        
    }

    if (m < cost_init + w_cost) {
        cout << 0 << nl;
        return;
    }

    i64 rem = m - (cost_init + w_cost);
    i64 plays = 1;

    if (k == n) {
        plays += rem / w_cost;
        cout << plays << nl;
        return;
    }

    vec<i64> other;
    for (int i = 0; i < n; i++) {
        if (i != p - 1) other.pb(a[i]);
    }

    sort(all(other));

    i64 cycle_cost = 0;
    int shifts = n - k;
    for (int i = 0; i < shifts; i++) {
        cycle_cost += other[i];
    }

    i64 cost_loop = cycle_cost + w_cost;
    plays += rem / cost_loop;

    cout << plays << nl;
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