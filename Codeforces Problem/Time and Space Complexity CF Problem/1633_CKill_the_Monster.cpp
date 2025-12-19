// Author :  sarvan.dp.grandmaster
// Created :  2025-12-15 15:05:21
// Problem: C. Kill the Monster
// Contest: Codeforces - Educational Codeforces Round 122 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1633/C
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
	i64 hc, dc, hm, dm;
	cin >> hc >> dc >> hm >> dm;
	
	i64 k, w, a;
	cin >> k >> w >> a;
	
	for (int i = 0; i <= k; i++) {
		i64 h = hc + a * i;
		i64 d = dc + w * (k - i);
		
		i64 cm = (hm + d - 1) / d;
		i64 mc = (h + dm - 1) / dm;
		
		if (cm <= mc) {
			cout << "YES\n";
			return;
		}
	}
	
	cout << "NO\n";
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