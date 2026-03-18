// Author: sarvan.dp.grandmaster
// Created: 2026-03-14 20:54:15
// Problem: D1. Tree Orientation (Easy Version)
// Contest: Codeforces - Codeforces Round 1086 (Div. 2)
// URL: https://codeforces.com/contest/2208/problem/D1
// Memory Limit: 1024 MB
// Time Limit: 3000 ms

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
    int n; cin >> n;

    vec<string> s(n);
    read(s);

    vec<pii> edges;

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (u == v || s[u][v] == '0') continue;

            bool flag = true;
            for (int k = 0; k < n; k++) {
                if (k == u || k == v) continue;
                if (s[u][k] == '1' && s[k][v] == '1') {
                    flag = false;
                    break;
                }
            }

            if (flag) edges.pb({u, v});
        }
    }

    if (sz(edges) != n - 1) {
        NO;
        return;
    }

    vvec<int> und(n), dir(n);

    for (auto [u, v] : edges) {
        und[u].pb(v);
        und[v].pb(u);
        dir[u].pb(v);
    }

    vec<int> vis(n, 0);
    queue<int> q;

    q.push(0);
    vis[0] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : und[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            NO;
            return;
        }
    }

    vec<string> got(n, string(n, '0'));

    for (int src = 0; src < n; src++) {
        vec<int> seen(n, 0);
        stack<int> st;

        st.push(src);
        seen[src] = 1;

        while (!st.empty()) {
            int u = st.top();
            st.pop();

            for (int v : dir[u]) {
                if (!seen[v]) {
                    seen[v] = 1;
                    st.push(v);
                }
            }
        }

        for (int v = 0; v < n; v++) {
            if (seen[v]) got[src][v] = '1';
        }
    }

    if (got != s) {
        NO;
        return;
    }

    YES;
    for (auto [u, v] : edges) {
        cout << u + 1 << " " << v + 1 << nl;
    }
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