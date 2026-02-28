/*
Author: Sarvan.DP.GrandMaster
Created : 2025-12-28 14:51:23
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

// Method 1 : The Algorithm: Right-to-Left (Simple Beginner Level)
i64 BinaryToDec(i64 n) {
    i64 ans = 0, powOf2 = 1;

    while (n > 0) {
        const i64 rem = n % 10;
        ans += rem * powOf2;
        n /= 10;
        powOf2 *= 2; // update power eg : 2, 4, 8, 16, 32,.......
    }

    return ans;
}

// Method 2 : The Grand Master Refactor (Correct Logic)
i64 binaryToDecimal(const string &str) {
    i64 ans = 0, powOf2 = 1;
    // We iterate backwards through the string
    for (int i = sz(str) - 1; i >= 0; i--) {
        if (str[i] == '1') ans += powOf2;
        powOf2 *= 2;
    }

    return ans;
}

// Method 3: (Horner's Method) is the Grand Master Choice. always use in CP
i64 binToDecimal(const string &str) {
    i64 ans = 0;
    for (const char ch : str) {
        // Shift current answer left (multiply by 2)
        // ans *= 2;
        // Add the current bit (convert char '0'/'1' to int 0/1)
        // if (ch == '1') ans += 1;

        // (Note: ans << 1 is same as ans * 2, and | (ch - '0') is same as + 1 if the bit is 0,
        // but faster on some older compilers. Modern compilers optimize both equally.)
        ans = (ans << 1) | (ch - '0'); // GM Optimization: Shift and OR
    }

    return ans;
}
void solve() {
    cout << "Enter a Binary Number : ";
    string str; cin >> str;
    // first convert string --> integer | (string → int : stoi()), (string → long long : stoll())
    const i64 num = stoll(str);
    cout << BinaryToDec(num) << nl;  // M-1 value pass int form (so string --> integer)
    cout << binaryToDecimal(str) << nl;  // M-2
    cout << binToDecimal(str) << nl;  // M-3

    // Method 4 :- Grand Master Shortcut (Built-in C++ STL)
    cout << stoi(str, nullptr, 2);
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

