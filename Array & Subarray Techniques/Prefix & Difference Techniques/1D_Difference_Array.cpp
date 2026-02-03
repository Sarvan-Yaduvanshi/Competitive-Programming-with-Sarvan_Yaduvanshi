/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-29 01:50:18
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

/**
 * Problem: 1D Difference Array (Range Updates + Point Query)
 * Technique: Difference Array + Prefix Sum
 * Time Complexity: O(Q + N)
 * Space Complexity: O(N)
 */

// METHOD 1: STATIC ARRAYS (The GM Choice)
// Pros: O(1) allocation, cache-friendly, safer recursion
constexpr int MAXN = 100005; // Set strictly larger than N
i64 arr[MAXN];               // Global array auto-initialized to 0

void solve_static() {
    int n, q;
    if (!(cin >> n >> q)) return;

    // Optional: Reset if multiple test cases
    // memset(arr, 0, sizeof(arr));

    // 1. Process Range Updates (O(1) per update)
    while (q--) {
        int l, r;
        i64 x;
        cin >> l >> r >> x;

        // Difference Array Logic
        arr[l] += x;       // Start adding X at index l
        arr[r + 1] -= x;   // Stop adding X after index r
    }

    // 2. Compute Prefix Sum (The Sweep)
    // Transforms Difference Array -> Final Values
    for (int i = 1; i <= n; i++) {
        arr[i] += arr[i - 1];
    }

    // 3. Print Final Array
    for (int i = 1; i <= n; i++) {
        cout << arr[i] << (i == n ? "" : " ");
    }
    cout << nl;
}

// METHOD 2: VECTOR (Clean & Dynamic)
// Pros: Memory isolation
void solve_vector() {
    int n, q;
    cin >> n >> q;

    // Size is n+2 to safely handle index [r+1] without if-checks
    vector<i64> diff(n + 2, 0);

    // 1. Updates
    while (q--) {
        int l, r;
        i64 x;
        cin >> l >> r >> x;

        diff[l] += x;
        diff[r + 1] -= x;
    }

    // 2. Sweep
    for (int i = 1; i <= n; i++) {
        diff[i] += diff[i - 1];
    }

    // 3. Print
    for (int i = 1; i <= n; i++) {
        cout << diff[i] << (i == n ? "" : " ");
    }
    cout << nl;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve_static(); // GM Preference
    // solve_vector();

    return 0;
}

/*
 * ==========================================
 * 1D DIFFERENCE ARRAY CHEATSHEET
 * ==========================================
 *
 * GOAL: Add value X to range [L, R]
 *
 * LOGIC (Update Phase):
 * 1. Start effect at L:      arr[L]   += X
 * 2. Cancel effect after R:  arr[R+1] -= X
 *
 * LOGIC (Build Phase):
 * Run standard Prefix Sum to propagate the effect.
 * arr[i] += arr[i-1];
 *
 * EXAMPLE:
 * Range [2, 4] += 10 on size 5 array
 * Init: [ 0,  0,  0,  0,  0,  0 ]
 * Diff: [ 0,  0, +10, 0,  0, -10] (after update)
 * Pref: [ 0,  0, 10, 10, 10,  0 ] (after sweep)
 */