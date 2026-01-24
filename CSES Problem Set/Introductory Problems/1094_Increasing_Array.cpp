// Author :  sarvan.dp.grandmaster
// Created :  2025-12-17 20:11:41
// Problem: Increasing Array
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1094
// Memory Limit: 512 MB
// Time Limit: 1000 ms

#ifndef __APPLE__
	#pragma GCC optimize("Ofast")
	#pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

// --- Type Definitions ---
using i64 = long long;
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

// --- Constants ---
constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;

// --- Random Number Generator ---
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// --- Macros ---
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

#define v1(v, n) vec<i64> v(n)
#define take(v) for(auto &x : v) cin >> x
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl


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