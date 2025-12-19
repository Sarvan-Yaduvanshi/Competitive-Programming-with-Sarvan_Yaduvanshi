// Author :  sarvan.dp.grandmaster
// Created :  2025-12-14 18:37:54
// Problem: A. Holiday Of Equality
// Contest: Codeforces - Codeforces Round 392 (Div. 2)
// URL: https://codeforces.com/problemset/problem/758/A
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
	// vec<int> arr(n);
	// for (auto &x : arr) cin >> x;
	// Time Complexity --> O(NlogN)
	// sort(arr.begin(), arr.end());
	// int maxNum = arr[n - 1];
	// int sum = 0;
	// for (int i = 0; i < n; i++) {
		// sum += maxNum - arr[i];
	// }
	// cout << sum << endl;
	
	// Time Complexity --> O(N) Space Complexity --> O(1)
	// Logic
	// Cost = (Max - A1) + (Max - A2) +.....+ (Max - An)
	// Cost = (n * Max) - (A1 + A2 + A3 + ...An)
	// Cost = (n * Max) - TotalSum
	int maxVal = -1;
	int totalSum = 0;
	
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		if (x > maxVal) maxVal = x;
		totalSum += x;
	}
	
	int ans = (n * maxVal) - totalSum;
	
	cout << ans << endl; 
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