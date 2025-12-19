// Author :  sarvan.dp.grandmaster
// Created :  2025-12-18 01:09:58
// Problem: Counting Divisors
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1713
// Memory Limit: 512 MB
// Time Limit: 1000 ms

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

// Maximum value of x as per constraints
const int MAX_X = 1000005;
int divisors_count[MAX_X];

// Precompute divisors for all numbers up to MAX_X
void precompute() {
	for (int i = 1; i < MAX_X; i++) {
		// Visit every multiple of i: i, 2i, 3i, 4i...
		for (int j = i; j < MAX_X; j += i) divisors_count[j]++;
	}
}

void solve() {
	// Time Complexity -- > O(MAX_X log(MAX_X))
	int x; cin >> x;
	
	cout << divisors_count[x] << "\n";
}
 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 1. Run the sieve once
    precompute();
    
    // 2. Answer queries in O(1)
    int n; 
    cin >> n;
    while(n--) {
        solve();
    }
    
    return 0;
}