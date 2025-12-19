// Author :  sarvan.dp.grandmaster
// Created :  2025-10-24 22:18:13
// Problem: A. System of Equations
// Contest: Codeforces - Codeforces Round 131 (Div. 2)
// URL: https://codeforces.com/problemset/problem/214/A
// Memory Limit: 256 MB
// Time Limit: 2000 ms

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
	i64 n, m;
	cin >> n >> m;
	
	i64 cnt = 0;
	
	// Tm --> O(N ^2)
	// for (int a = 0; a * a <= n; a++) {
		// for (int b = 0; b * b <= m; b++) {
			// if (((a * a + b) == n) && ((a + b * b) == m)) cnt++;
		// }
	// }
	
	for (int a = 0; a * a <= n; a++) {
		int b = n - (a * a);
		
		// We only need to check if this (a, b) pair
		// satisfies the second equation.
		if ((a + b * b) == m) {
			cnt++;
		}
	}
	
	println("{}", cnt);
	
	
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();

    // int TC = 1;
    // cin >> TC;
    // while(TC--) {
        // solve();
    // }
    return 0;
}