// Author :  sarvan.dp.grandmaster
// Created :  2025-09-28 18:23:44
// Problem: D. Range Sum
// Contest: Codeforces - Contest #2
// URL: https://codeforces.com/group/MWSDmqGsZm/contest/326907/problem/D
// Memory Limit: 256 MB
// Time Limit: 1000 ms

#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using i128 = __int128_t;
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

i64 f(i64 n) {
	i64 ans = n * 1ll * (n + 1) / 2;
	return ans;
}

void solve() {
	i64 l, r; cin >> l >> r;
	
	// first approach
	// i64 sum = 0;
	// for (int i = l; i <= r; i++) sum += i;
	// cout << sum << endl;
	
	// 2nd approach Math formula
	if (l > r) swap(l, r);
	
	i64 ans = f(r) - f(l - 1);
	
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