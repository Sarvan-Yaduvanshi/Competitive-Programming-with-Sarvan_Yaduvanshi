// Author: sarvan.dp.grandmaster
// Created: 2026-02-04 09:16:02
// Problem: C. Greg and Array
// Contest: Codeforces - Codeforces Round 179 (Div. 2)
// URL: https://codeforces.com/problemset/problem/296/C
// Memory Limit: 256 MB
// Time Limit: 1500 ms

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>ß
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

constexpr int MAXN = 100005;
i64 a[MAXN];
i64 oper_cnt[MAXN]; 
i64 diff[MAXN];    

struct Operation {
    int l, r;
    i64 d;
};

Operation ops[MAXN];

void solve() {
    int n, m, k;
    if (!(cin >> n >> m >> k)) return;
    
    for (int i = 1; i <= n; i++) 
        cin >> a[i];
        
    for (int i = 1; i <= m; i++) {
        cin >> ops[i].l >> ops[i].r >> ops[i].d;
    }

    // Range [x, y]
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        oper_cnt[x]++;
        oper_cnt[y + 1]--;
    }

    // Prefix sum to get actual count of each operation
    for (int i = 1; i <= m; i++) {
        oper_cnt[i] += oper_cnt[i - 1];
    }
    
    for (int i = 1; i <= m; i++) {
        if (oper_cnt[i] == 0) continue;
        
        i64 total_val = ops[i].d * oper_cnt[i];
        diff[ops[i].l] += total_val;
        diff[ops[i].r + 1] -= total_val;
    }

    for (int i = 1; i <= n; i++) {
        diff[i] += diff[i - 1];
        a[i] += diff[i]; // Apply to original array
    }

    // Output result
    for (int i = 1; i <= n; i++) {
        cout << a[i] << (i == n ? "" : " ");
    }
    cout << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);
    
    solve();
    
    return 0;
}