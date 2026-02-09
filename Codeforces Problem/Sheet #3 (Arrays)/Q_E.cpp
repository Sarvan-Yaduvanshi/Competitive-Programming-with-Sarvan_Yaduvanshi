// Author :  sarvan.dp.grandmaster
// Created :  2025-10-04 08:59:09
// Problem: E. Lowest Number
// Contest: Codeforces - Sheet #3 (Arrays)
// URL: https://codeforces.com/group/MWSDmqGsZm/contest/219774/problem/E
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
	int n; cin >> n;
	
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];
	// for (auto &x : a) cin >> x;
	
	// 1st approach using Lopp Through tm --> O(N)
	// int minNum = INT_MAX;
	// int pos = -1;
	// for (int i = 1; i <= n; i++) {
		// if (a[i] < minNum) {
			// minNum = a[i];
			// pos = i;
		// }
	// }
	
	// cout << minNum << " " << pos << endl;
	
	// 2nd approach using STL tm --> O(N) best for cp
	auto it = min_element(a.begin() + 1, a.end());
	
	int index = it - a.begin();
	
	cout << *it << " " << index << endl;
	
	// 3rd approach using sorting tm --> O(N log N)
	// vector<pair<int, int>> num;
	// for (int i = 1; i <= n; i++) {
		// num.push_back({a[i], i});
	// }
// 	
	// sort(num.begin(), num.end());
// 	
	// cout << num[0].first << " " << num[0].second << endl;
	
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