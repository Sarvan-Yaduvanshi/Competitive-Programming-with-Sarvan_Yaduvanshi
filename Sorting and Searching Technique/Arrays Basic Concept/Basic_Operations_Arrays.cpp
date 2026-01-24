/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-01 20:31:33
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

#define v1(v, n) vec<i64> v(n)
#define take(v) for(auto &x : v) cin >> x
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
    vector<int> v;

    v.push_back(2); // [2]
    v.push_back(3); // [2, 3]
    v.push_back(5); // [2, 3, 5]
    v.push_back(7); // [2, 3, 5, 7]
    v[1] = 4; // sets element at index 1 to 4 --> [2, 4, 5, 7]
    v.erase(v.begin() + 1); // removes element at index 1 -> [2, 5, 7]
    // this remove method is O(n); to be avoided
    v.push_back(8); // [2, 5, 7, 8]
    v.erase(v.end() - 1); // [2, 5, 7]
    // here, we remove the element from the end of the list; this is O(1).
    v.push_back(4); // [2, 5, 7, 4]
    v.push_back(4); // [2, 5, 7, 4, 4]
    v.push_back(9); // [2, 5, 7, 4, 4, 9]
    cout << v[2]; // print value index 2 --> 7
    v.erase(v.begin(), v.begin() + 3); // [4, 4, 9]
    // this erases the first three elements; O(n)

    // In a dynamic array, we can also add and delete
    // elements at the end in O(1) time.
    // However, we need to be careful that we only add elements to the end of the vector;
    // insertion and deletion in the middle of the vector is O(n)

    for (auto val : v) cout << val << " ";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);

    // int TC = 1;
    // cin >> TC;
    // while (TC--) solve();
    
    solve();
    return 0;
}

