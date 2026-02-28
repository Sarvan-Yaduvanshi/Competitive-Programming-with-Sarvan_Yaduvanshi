// Author: sarvan.dp.grandmaster
// Created: 2025-12-29 01:53:57
// Problem: Sherlock and Divisors
// Contest: HackerRank - Mathematics - Fundamentals
// URL: https://www.hackerrank.com/challenges/sherlock-and-divisors/problem
// Memory Limit: 512 MB
// Time Limit: 4000 ms

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

void solve() {
    i64 n; cin >> n;
    
    // 1. Optimization: If N is odd, it has no even divisors.
    if (n % 2 != 0) {
        cout << 0 << nl;
        return;
    }
    
    // Method 1 : Find all divisors using the O(sqrt(N)) loop, then check if (divisor % 2 == 0).  
    // Drawback: Performs unnecessary modulus operations inside the loop. 
    // i64 ans = 0;
    // for (i64 i = 2; i * i <= n; i++) {  // TM --> O(Sqrt(N))
    //     if (n % i == 0) {
    //         i64 divisors1 = i;
    //         i64 divisors2 = n / i;
    //         if ((divisors1 & 1) == 0) ans++;
    //         if (divisors1 != divisors2) {
    //             if ((divisors2 & 1) == 0) ans++;
    //         }
    //     }
    // }
    // // check last number
    // if ((n & 1) == 0) ans++;
    // cout << ans << nl;
    
    // Method 2 : The GM Approach (Number Theory)  Time Complexity -- > O(Sqrt(N / 2^K))
    // Advantage: This is strictly faster than standard O(Sqrt(N)). For a number like N = 2^30, the loop runs O(1) times instead of O(2^15)
    // Insight: Any integer N can be decomposed into N = 2^K * M, where M is the odd part of N.
    // Logic:
    //     1. K is the count of factor 2 in N.
    //     2. M is what remains after dividing N by 2 repeatedly.
    //     3. The total number of even divisors is simply K * countDivisors(M).
    i64 k = 0;
    while (n % 2 == 0) {
        k++;
        n /= 2; 
    }

    // 3. Count total divisors of the remaining odd part 'n' (which is M)
    i64 divisors_of_m = 0;
    for (i64 i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divisors_of_m++; // found a divisor 'i'
            
            // if 'i' is not the square root, count the pair 'n/i'
            if (i != n / i) {
                divisors_of_m++;
            }
        }
    }

    // 4. Result is K * (Divisors of M)
    cout << k * divisors_of_m << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    int TC = 1;
    cin >> TC; 
    while(TC--) {
        solve();
    }
    return 0;
}