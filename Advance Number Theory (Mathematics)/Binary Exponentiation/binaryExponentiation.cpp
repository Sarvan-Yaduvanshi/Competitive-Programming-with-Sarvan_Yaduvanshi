/*
Author: Sarvan.DP.GrandMaster
Created : 2025-12-28 00:54:34
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

// First the recursive approach
i64 binpow(i64 a, i64 b) {
    if (b == 0) return 1;

    i64 res = binpow(a, b / 2);

    if (b & 1) return res * res * a; // // Checks if b is odd (Standard CP optimization)
    else return res * res;
}

// Iterative Through
i64 binpow2(i64 a, i64 b) {
    i64 res = 1;
    while (b > 0) {
        if (b & 1)
            // If 'b' is odd (last bit is 1), multiply 'a' with result
            res = res * a;
        // Square 'a' for the next bit position
        a = a * a;
        // Divide b by 2 using bitwise shift (faster)
        b >>= 1;
    }
    return res;
}

void solve() {
    i64 base, exponent;
    cout << "Enter base: "; cin >> base;
    cout << "Enter exponent: "; cin >> exponent;

    cout << "Base = " << base
         << ", Exponent = " << exponent << nl;

    cout << "Recursive: "
         << base << "^" << exponent
         << " = " << binpow(base, exponent) << nl;

    cout << "Iterative: "
         << base << "^" << exponent
         << " = " << binpow2(base, exponent) << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    solve();

    return 0;
}

