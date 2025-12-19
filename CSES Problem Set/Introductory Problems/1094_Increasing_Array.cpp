// Author :  sarvan.dp.grandmaster
// Created :  2025-12-17 20:11:41
// Problem: Increasing Array
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1094
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

void solve() {
	i64 n; cin >> n;
	
	// Time --> O(N) Space Comp --> O(N)
	// vec<i64> a(n);
	// for (auto &x : a) cin >> x;
// 
	// i64 moves = 0;
	// for (int i = 1; i < n; i++) {
		// if (a[i] < a[i - 1]) {
			// moves += a[i - 1] - a[i];
			// a[i] = a[i - 1];
		// }
	// }
// 	
	// cout << moves << "\n";
	
	
	// Time Comp --> O(N)  SP --> O(1)
	
	i64 mx = 0;
	i64 moves = 0;
	i64 x;
	
	// Read first element to initialize mx
	if (n > 0) {
		cin >> mx;
		n--;
	}
	
	while (n--) {
		cin >> x;
		if (x < mx) {
			moves += (mx - x);
		} else mx = x;
	}
	
	cout << moves << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    
    return 0;
}