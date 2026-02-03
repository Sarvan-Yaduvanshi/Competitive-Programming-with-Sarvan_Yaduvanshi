// Author: sarvan.dp.grandmaster
// Created: 2026-01-28 15:13:00
// Problem: Forest Queries
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1652
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
    int n, q;
    cin >> n >> q;

    vec<vec<i64>> grid(n + 1, vec<i64>(n + 1, 0));
    vec<vec<i64>> pref(n + 1, vec<i64>(n + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char ch;
            cin >> ch;
            grid[i][j] = (ch == '*');
        }
    }

    // Step 1 : Build Prefix sum
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            pref[i][j] = grid[i][j] + pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
    }

    // Step 2 : Queries Answer
    while (q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        i64 ans = pref[r2][c2] - pref[r1 - 1][c2] - pref[r2][c1 - 1] + pref[r1 - 1][c1 - 1];

        cout << ans << nl;
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    solve();

    return 0;
}

