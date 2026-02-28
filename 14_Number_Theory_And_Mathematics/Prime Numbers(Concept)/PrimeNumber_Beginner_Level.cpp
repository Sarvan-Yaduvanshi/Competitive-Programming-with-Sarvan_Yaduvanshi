/*
Author: Sarvan.DP.GrandMaster
Created : 2025-12-28 19:21:14
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

// Method 1 : Beginner Level Time Complexity O(N^2) it handle N=10^5
void isPrime(i64 n){
    if (n < 2){
        cout << "Invalid Number Enter N >= 2 like 2,15,23,....";
        return;
    } else {
        cout << "All Prime Factors : ";
        for (int i = 2; i <= n; i++){
            bool flag = true;
            for (int j = 2; j < i; j++){
                if (i % j == 0){
                    flag = false;
                    break;
                }
            }

            if (flag) cout << i << " ";
        }
        cout << nl;
    }
}

// Method 2 : Trial Division with 6k ± 1 Optimization
// code uses a very popular optimization known as the 6k ± 1 rule.
// Why it works:
//  1. Any integer can be written as (6k + i), where $i = 0, 1, 2, 3, 4, 5.
//  2. 6k+0, 6k+2, 6k+4 are divisible by 2.
//  3. 6k+3 is divisible by 3.
//  4. Therefore, primes can only exist in the form 6k+1 or 6k+5 (which is 6k-1).
// This is excellent for checking if one specific large number (e.g., 10^14) is prime.
// Max Limit: Can handle N up to approx 10^14 in < 1 second.  TM --> O(Sqrt(N)
bool checkPrime(const i64 n){
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    // Check divisibility by 6k ± 1. We only check up to sqrt(n)
    for (i64 i = 5; i * i <= n; i += 6){
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }

    return true;
}
void solve() {
    i64 n; cin >> n;

    // Method 1 : Beginner Level Time Complexity O(N^2) it handle N=10^5
    isPrime(n);

    // Method 2 : Trial Division with 6k ± 1 Optimization
    // Total Complexity: O(NSqrt(N))
    cout << "All Prime Factors : ";
    for (i64 i = 2; i <= n; i++){  // O(N)
        if (checkPrime(i)) cout << i << " "; // checkPrime Fun Time Comp --> O(Sqrt(N))
    }
    cout << nl;
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

