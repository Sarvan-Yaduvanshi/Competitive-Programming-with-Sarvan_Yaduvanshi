// Author :  sarvan.dp.grandmaster
// Created :  2025-10-01 19:34:36
// Problem: Z. Three Numbers
// Contest: Codeforces - Sheet #2 (Loops)
// URL: https://codeforces.com/group/MWSDmqGsZm/contest/219432/problem/Z
// Memory Limit: 256 MB
// Time Limit: 3000 ms

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
	int k, s; cin >> k >> s;
	
	// 1st approach nested loop tm --> o(n^2)
	// int cnt = 0;
	// for (int x = 0; x <= k; x++) {
		// for (int y = 0; y <= k; y++) {
			// int z = s - x - y;
// 			
			// if (z >= 0 && z <= k) cnt++;
		// }
	// }
	// cout << cnt << endl;
	
	// 2nd approach yse math tm --> o(k)
	i64 count = 0;
    for (int x = 0; x <= k; ++x) {
        // The upper bound for y is the minimum of k and what's left from S
        int upper_bound_y = min(k, s - x);
        
        // The lower bound for y must be at least 0, AND satisfy the constraint for z
        int lower_bound_y = max(0, s - x - k);

        // If the range is valid (upper is not smaller than lower)
        if (upper_bound_y >= lower_bound_y) {
            // The number of integers in the range [L, R] is R - L + 1
            count += (upper_bound_y - lower_bound_y + 1);
        }
    }
    cout << count << endl;
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