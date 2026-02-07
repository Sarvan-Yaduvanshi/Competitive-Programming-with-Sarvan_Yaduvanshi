// Author :  sarvan.dp.grandmaster
// Created :  2025-12-14 18:11:52
// Problem: Number Groups
// Contest: HackerRank - Mathematics - Algebra
// URL: https://www.hackerrank.com/challenges/number-groups/problem
// Memory Limit: 512 MB
// Time Limit: 4000 ms

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
	// Group 1 --> (1) --> sum --> 1 (1)^3
	// Group 2 --> (3, 5) --> sum --> 8  (2)^3
	// Group 1 --> (7, 9, 11) --> sum --> 27  (3)^3
	// Group 1 --> (13, 15, 17, 19) --> sum --> 64 --> (4)^3
	// The Solution:The sum of the elements in the kth group is simply k^3 (k cubed).
	
	i64 k; cin >> k;
	
	i64 ans = k * k * k;
	
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