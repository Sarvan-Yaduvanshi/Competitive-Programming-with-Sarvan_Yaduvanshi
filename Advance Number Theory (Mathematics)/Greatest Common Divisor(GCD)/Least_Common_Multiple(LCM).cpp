/*
Author: Sarvan.DP.GrandMaster
Created : 2025-12-29 19:25:36
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

// Level 2: LCM (Least Common Multiple)
// To find the LCM, you don't need a new algorithm. You use the GCD formula.
//  LCM(a, b) = (a * b) / gcd(a, b) ---> But Give me overflow during multiplication
// so correct ways :   LCM(a, b) = (a / gcd(a, b)) * b reason -- > Calculate GCD first than multiply
i64 implementLCM(i64 a, i64 b){
    if (a == 0 || b == 0) return 0;
    return (a / std::gcd(a, b)) * b;
}

// Level 3: Extended Euclidean Algorithm (Pro Level)
// In hard problems, you are often asked to find integer solutions for x and y in the equation:
//          A.x + B.y = GCD(A, B)
// This is called Linear Diophantine Equation. You need the Extended GCD for this.
// Why use this?
//           *. It is used to find Modular Inverse (needed for combinatorics nCr % M).
// Returns gcd(a, b) and updates x and y such that ax + by = gcd(a, b)
int extendedGCD(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = extendedGCD(b, a % b, x1, y1);

    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

// Level 4: Grandmaster Properties of GCD / LCM
// These are the "tricks" used in Div 1 / Div 2 C-D problems.
//   1. GCD on an Array GCD(a, b, c) = GCD(a, GCD(b, c))

//

void solve() {
    i64 a, b;
    cout << "Enter a first number : "; cin >> a;
    cout << "Enter a second number : "; cin >> b;

    // Fun Call and print
    i64 ans = implementLCM(a, b);
    cout << "LCM(" << a << ", " << b << ") : " << ans << nl;
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

