// Author: sarvan.dp.grandmaster
// Created: 2025-12-29 00:35:27
// Problem: A. Noldbach problem
// Contest: Codeforces - Codeforces Beta Round 17
// URL: https://codeforces.com/problemset/problem/17/A
// Memory Limit: 64 MB
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
// Use rng() to get a random number. Much faster/better than rand().
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
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

bool checkPrime(i64 num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    
    for (i64 i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    
    return true;
}

void solve() {
    i64 n, k;
    cin >> n >> k;

    // Method 1 : Trial Division with 6k ± 1 Optimization
    // vec<i64> primes;
    // for (i64 i = 2; i <= n; i++) {
    //     if (checkPrime(i)) primes.pb(i);
    // }
    // int cnt = 0;
    // for (int i = 0; i + 1 < primes.size(); i++) {
    //     int x = 1 + primes[i] + primes[i + 1];
    //     if (x <= n && checkPrime(x)) cnt++;
    // }
    // cout << (cnt >= k ? "YES" : "NO") << nl;
    
    // Method 2 : Using Sieve Eratosthenes Version
    vec<bool> isPrime(n + 1, true);
    isPrime[0] = false, isPrime[1] = false;
    
    for (i64 i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (i64 j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    vec<int> primes;
    for (i64 i = 2; i <= n; i++) {
        if (isPrime[i]) primes.pb(i);
    }
    
    int cnt = 0;
    for (int i = 0; i + 1 < primes.size(); i++) {
        int x = 1 + primes[i] + primes[i + 1];
        if (x <= n && isPrime[x]) cnt++;
    }
    
    // cout << (cnt >= k ? "YES" : "NO") << nl; 
    if (cnt >= k) {
        cout << "YES" << nl;
        return;
    }      
    cout << "NO" << nl;

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    solve();
    
    return 0;
}