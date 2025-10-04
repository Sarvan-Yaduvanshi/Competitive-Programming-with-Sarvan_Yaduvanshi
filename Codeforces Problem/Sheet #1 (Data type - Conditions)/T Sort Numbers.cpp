// Author :  sarvan.dp.grandmaster
// Created :  2025-09-28 07:54:58
// Problem: T. Sort Numbers
// Contest: Codeforces - Sheet #1 (Data type - Conditions)
// URL: https://codeforces.com/group/MWSDmqGsZm/contest/219158/problem/T
// Memory Limit: 256 MB
// Time Limit: 250 ms

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
	i64 a, b, c; cin >> a >> b >> c;
	
	array<i64, 3> arr = {a, b, c};
    sort(arr.begin(), arr.end());

    for (auto v : arr) cout << v << "\n";
    cout << "\n";
    cout << a << "\n" << b << "\n" << c << "\n";
	
	// // copy all val
	// i64 x = a, y = b, z = c;
// 	
	// if (x > y) swap(x, y);
	// if (y > z) swap(y, z);
	// if (x > y) swap(x, y);
// 	
	// cout << x << endl;
	// cout << y << endl;
	// cout << z << endl;
// 	
	// cout << endl;
// 	
	// cout << a << endl;
	// cout << b << endl;
	// cout << c << endl;
	
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // int TC = 1;
    // cin >> TC;
    // while(TC--) {
        // solve();
    // }
    solve();
    
    return 0;
}