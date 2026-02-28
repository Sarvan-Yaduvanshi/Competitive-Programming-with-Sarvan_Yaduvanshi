/*
Author: Sarvan.DP.GrandMaster
Created : 2025-12-28 14:42:01
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
    int a, b;
    // 1. Clean Input Style for Local/Notes
    cout << "Enter a: "; cin >> a;
    cout << "Enter b: "; cin >> b;

    cout << "\n--- Original Values ---\n";
    cout << "a = " << a << ", b = " << b << "\n\n";

    // ==========================================
    // METHOD 1: STL Swap (The "Grandmaster" Way)
    // ==========================================
    // WHY: Safe, fastest, handles all data types, optimized by compiler.
    swap(a, b);
    cout << "[Method 1 - STL] Swapped: " << a << " " << b << nl;
    // Resetting for next example
    swap(a, b);


    // ==========================================
    // METHOD 2: Temp Variable (The "Classic" Way)
    // ==========================================
    // WHY: Easy to understand, works in almost every programming language.
    {
        int temp = a;
        a = b;
        b = temp;
    }
    cout << "[Method 2 - Temp] Swapped: " << a << " " << b << nl;
    swap(a, b); // Reset


    // ==========================================
    // METHOD 3: XOR Swap (Bit Manipulation)
    // ==========================================
    // WHY: Often asked in interviews. No extra memory used.
    // WARNING: Fails if &a == &b (swapping a variable with itself makes it 0).
    if (&a != &b) { // Safety check
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
    }
    cout << "[Method 3 - XOR]  Swapped: " << a << " " << b << nl;
    swap(a, b); // Reset


    // ==========================================
    // METHOD 4: Arithmetic Swap (+ and -)
    // ==========================================
    // WHY: Interview trick.
    // WARNING: Risky! Can cause Integer Overflow if a + b > INT_MAX.
    a = a + b;
    b = a - b;
    a = a - b;
    cout << "[Method 4 - Math] Swapped: " << a << " " << b << nl;
    swap(a, b); // Reset


    // ==========================================
    // METHOD 5: C++17 Tuple Swap (Modern/Python-like)
    // ==========================================
    // WHY: Looks cool, similar to Python's a, b = b, a
    tie(a, b) = make_tuple(b, a);
    cout << "[Method 5 - Tie]  Swapped: " << a << " " << b << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    solve();

    return 0;
}

