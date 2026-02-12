// Author: sarvan.dp.grandmaster
// Created: 2026-02-12 22:38:09
// Problem: E. Binary Deque
// Contest: Codeforces - Codeforces Round 799 (Div. 4)
// URL: https://codeforces.com/problemset/problem/1692/E
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
    int n, s; cin >> n >> s;

    vec<int> a(n);
    i64 sum = 0;
    for (int i = 0; i < n; i++){
        cin >> a[i];
        sum += a[i];
    }

    // Case 1: Impossible to reach sum S
    if (sum < s){
        cout << -1 << nl;
        return;
    }

    // Case 2: Exact match initially
    if (sum == s){
        cout << 0 << nl;
        return;
    }

    // Sliding Window to find longest subarray with sum S
    int left = 0;
    int curr_sum = 0;
    int mxLen = 0;

    for (int right = 0; right < n; right++){
        curr_sum += a[right];

        // If sum exceeds S, shrink from the left
        if (curr_sum > s){
            curr_sum -= a[left];
            left++;
        }

        // If exact match found, update max_len
        if (curr_sum == s){
            mxLen = max(mxLen, right - left + 1);
        }
    }

    // Min operations = Total Length - Longest Valid Subarray
    cout << n - mxLen << nl;
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
