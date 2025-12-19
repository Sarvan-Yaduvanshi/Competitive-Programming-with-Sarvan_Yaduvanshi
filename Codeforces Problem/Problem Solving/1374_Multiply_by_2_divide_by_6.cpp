// Author :  sarvan.dp.grandmaster
// Created :  2025-12-18 17:31:53
// Problem: B. Multiply by 2, divide by 6
// Contest: Codeforces - Codeforces Round 653 (Div. 3)
// URL: https://codeforces.com/problemset/problem/1374/B
// Memory Limit: 256 MB
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
	
	i64 power2 = 0, power3 = 0;
	
	while (n % 2 == 0) {
		power2++;
		n /= 2;
	}
	
	while (n % 3 == 0) {
		power3++;
		n /= 3;
	}
	
	if (n > 1 || power2 > power3) cout << "-1\n";
	else cout << ((power3 - power2) + power3) << "\n"; 
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