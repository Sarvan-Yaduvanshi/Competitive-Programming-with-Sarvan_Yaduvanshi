/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-16 16:43:29
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
using ld = long double;
template<class T>
using vec = vector<T>;
template<class T>
using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

// --- Constants ---
constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD = 1'000'000'007LL;
constexpr i64 MOD9 = 998'244'353LL;
constexpr ld PI = 3.14159265358979323846;

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
void read(vec<T>& v){
    for (auto& x : v) cin >> x;
}

#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

inline i64 gcd(i64 a, i64 b){ return std::gcd(a, b); }
inline i64 lcm(i64 a, i64 b){ return (a / std::gcd(a, b)) * b; }

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD){
    i64 res = 1;
    base %= mod;
    while (exp > 0){
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// Given an integer array nums, rotate the array to the right by k steps,
// where k is non-negative.
// Example :- nums = [1,2,3,4,5,6,7], k = 3
// Output :- 5 6 7 1 2 3
// Time Complexity -> O(N) | SP -> O(1)
void rotatedArray(vec<int>& arr, int k){
    int n = sz(arr);
    if (n <= 1) return;

    k %= n;
    if (k == 0) return;

    int st, en;

    // Step 1: Reverse whole array
    st = 0, en = n - 1;
    while (st < en) swap(arr[st++], arr[en--]);

    // Step 2 : Reverse first k elements
    st = 0, en = k - 1;
    while (st < en) swap(arr[st++], arr[en--]);

    // Step 3 : Reverse remaining n-k elements
    st = k, en = n - 1;
    while (st < en) swap(arr[st++], arr[en--]);
}

void solve(){
    int n; cin >> n;
    vec<int> a(n);
    read(a);

    for (auto x : a) cout << x << " ";
    cout << nl;


    int k; cin >> k;
    rotatedArray(a, k);
    for (auto x : a) cout << x << " ";
}


int main(){
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

