// Author :  sarvan.dp.grandmaster
// Created :  2025-12-18 01:09:58
// Problem: Counting Divisors
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1713
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


// Maximum value of x as per constraints
constexpr int MAX_X = 1000005;
int divisors_count[MAX_X];

// Precompute divisors for all numbers up to MAX_X
void precompute() {
	for (int i = 1; i < MAX_X; i++) {
		// Visit every multiple of i: i, 2i, 3i, 4i...
		for (int j = i; j < MAX_X; j += i) divisors_count[j]++;
	}
}

void solve() {
	// Time Complexity -- > O(MAX_X log(MAX_X))
	int x; cin >> x;
	
	cout << divisors_count[x] << "\n";
}
 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 1. Run the sieve once
    precompute();
    
    // 2. Answer queries in O(1)
    int n; 
    cin >> n;
    while(n--) {
        solve();
    }
    
    return 0;
}