// Author :  sarvan.dp.grandmaster
// Created :  2025-12-14 17:44:25
// Problem: Summing the N series
// Contest: HackerRank - Mathematics - Fundamentals
// URL: https://www.hackerrank.com/challenges/summing-the-n-series/problem
// Memory Limit: 512 MB
// Time Limit: 4000 ms

#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using ld  = long double;

constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD  = 1'000'000'007LL;
constexpr i64 MOD1 = 1'000'000'007LL;
constexpr i64 MOD2 = 998'244'353LL;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) int((x).size())
#define pb push_back
#define fi first
#define se second

template<class T> using vec = vector<T>;
template<class A, class B> using pii = pair<A,B>;

// ---------------- Toolbox ----------------
inline i64 gcdll(i64 a, i64 b) { while(b){ a %= b; swap(a,b);} return abs(a);}
inline i64 lcmll(i64 a, i64 b) { return a / gcdll(a,b) * b;}
inline i64 modpow(i64 a, i64 e, i64 mod = MOD) {
    i64 r = 1;
    while(e) {
        if(e & 1) r = r * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return r;
}

void solve() {
	i64 n; cin >> n;
	
	/*
 * ==========================================
 * LOGIC & DERIVATION
 * ==========================================
 *
 * 1. MATHEMATICAL SIMPLIFICATION (Telescoping Series):
 * The term is defined as: T_n = n^2 - (n-1)^2
 * Let's write out the sum for the first few terms:
 * T_1 = 1^2 - 0^2
 * T_2 = 2^2 - 1^2
 * T_3 = 3^2 - 2^2
 * ...
 * T_n = n^2 - (n-1)^2
 *
 * When summing these (S_n), the diagonal terms cancel out:
 * The +1^2 cancels with -1^2.
 * The +2^2 cancels with -2^2.
 * * We are left with only the final term: n^2.
 * THEREFORE: S_n = n^2
 *
 * 2. CONSTRAINT HANDLING (n <= 10^16):
 * - The input n can be up to 10^16.
 * - Calculating n*n directly gives 10^32, which overflows 
 * a 64-bit integer (long long max is ~9*10^18).
 *
 * 3. SOLUTION:
 * Use Modular Arithmetic property: (a * b) % m = ((a % m) * (b % m)) % m
 * * Step A: Reduce n first ->  n = n % 1000000007
 * Step B: Square it      ->  ans = (n * n) % 1000000007
 */
	i64 ans = ((n % MOD ) * (n % MOD ) % MOD );
	
	cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    cin >> TC;
    while(TC--) {
        solve();
    }
    return 0;
}