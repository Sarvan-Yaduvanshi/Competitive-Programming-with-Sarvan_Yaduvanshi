// Author :  sarvan.dp.grandmaster
// Created :  2025-10-03 19:02:59
// Problem: B. Searching
// Contest: Codeforces - Sheet #3 (Arrays)
// URL: https://codeforces.com/group/MWSDmqGsZm/contest/219774/problem/B
// Memory Limit: 64 MB
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

int linerSearch(const vector<i64>& a, i64 x) {
	int n = a.size();
	
	for (int i = 0; i < n; i++) {
		if (a[i] == x) return i;
	}
	
	return -1;
}

void solve() {
	i64 n; cin >> n;
	
	vector<i64> a(n);
	for (auto &x : a) cin >> x;
	
	i64 x; cin >> x;
	
	// 1st appraoch liner search tm --> o(n)
	// cout << linerSearch(a, x);
	
	// liner search using STL 
	auto it = find(a.begin(), a.end(), x);
	
	if (it != a.end()) cout << (it - a.begin()) << endl;
	else cout << -1 << endl;
	
	
	// 2nd approach using Binary Search tm --> o(longN)
	// But array are not sorted so sort tm --> o(nlogn)
	// so total tm --> (nlogN) this is not good
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