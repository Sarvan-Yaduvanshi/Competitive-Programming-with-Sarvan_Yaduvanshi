/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-02 10:09:33
*/

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

vec<int> corpFlightBookings(const vvec<int>& bookings, int n){
    vec<int> ans(n, 0);

    // Step 1: Difference update (O(q))
    for (const auto& b : bookings){
        int l = b[0] - 1; // Convert 1-based to 0-based
        int r = b[1] - 1;
        int seats = b[2];

        ans[l] += seats;
        if (r + 1 < n) ans[r + 1] -= seats;
    }

    // Step 2: Prefix Sum Build (O(n))
    for (int i = 1; i < n; i++)
        ans[i] += ans[i - 1];

    return ans;
}

void solve() {
    int n, q;
    if (!(cin >> n >> q)) return;

    vvec<int> booking(q, vec<int>(3));
    for (int i = 0; i < q; i++){
        cin >> booking[i][0] >> booking[i][1] >> booking[i][2];
    }

    vec<int> ans = corpFlightBookings(booking, n);

    for (int i = 0; i < n; i++)
        cout << ans[i] << (i == n - 1 ? "" : " ");
    cout << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);
    
    // Multi-test case support (commented out for this demo)
    // int TC = 1;
    // cin >> TC;
    // while (TC--) solve();
    
    solve();
    return 0;
}

