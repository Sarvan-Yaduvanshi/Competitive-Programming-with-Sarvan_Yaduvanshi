// Author: sarvan.dp.grandmaster
// Created: 2026-02-27 21:35:10
// Problem: E. Divisive Battle
// Contest: Codeforces - Codeforces Round 1084 (Div. 3)
// URL: https://codeforces.com/contest/2200/problem/E
// Memory Limit: 256 MB
// Time Limit: 3000 ms

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

constexpr int MAXN = 1000005;
int spf[MAXN];

void precompute() {
    for (int i = 1; i < MAXN; ++i) {
        spf[i] = i;
    }
    for (int i = 2; i * i < MAXN; ++i) {
        if (spf[i] == i) {
            for (int j = i * i; j < MAXN; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
}

void solve() {
    int n; cin >> n;
    
    vec<int> a(n);
    bool sorted_init = true;
    
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (i > 0 && a[i] < a[i-1]) {
            sorted_init = false;
        }
    }

    if (sorted_init) {
        cout << "Bob\n";
        return;
    }

    vec<int> p(n);
    bool alice_wins = false;

    for (int i = 0; i < n; ++i) {
        int x = a[i];
        if (x == 1) 
            p[i] = 1;
        
        else {
            int first_prime = spf[x];
            int temp = x;
            
            while (temp % first_prime == 0)
                temp /= first_prime;
            
            if (temp > 1) {
                alice_wins = true;
                break;
            } 
            else 
                p[i] = first_prime;
        }
    }

    if (alice_wins) {
        cout << "Alice\n";
        return;
    }

    bool p_sorted = true;
    for (int i = 1; i < n; ++i) {
        if (p[i] < p[i-1]) {
            p_sorted = false;
            break;
        }
    }
  
    cout << (p_sorted ? "Bob" : "Alice") << nl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    precompute();
    
    cout << fixed << setprecision(10);
    
    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    
    return 0;
}