// Author :  sarvan.dp.grandmaster
// Created :  2025-10-02 15:21:15
// Problem: J. Primes from 1 to n
// Contest: Codeforces - Sheet #2 (Loops)
// URL: https://codeforces.com/group/MWSDmqGsZm/contest/219432/problem/J
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

// ## Method 1: Using Your isPrime Function in a Loop
// bool isPrime(i64 n) {
	// if (n < 2) return false;
	// if (n == 2 || n == 3) return true;
	// if (n % 2 == 0 || n % 3 == 0) return false;
// 	
	// for (int i = 5; i * i <= n; i += 6) {
		// if (n % i == 0 || n % (i + 2) == 0) return false;
	// }
// 	
	// return true;
// }

void solve() {
	int n; cin >> n;
	
	// Method 2: The Sieve of Eratosthenes (The Best Way) 
	vector<bool> isPrime(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	
	for (int i = 2; i * i <= n; i++) {
		if (isPrime[i]) {
			// Mark all multiples of p as not prime
			for (int j = i * i; j <= n; j += i) {
				isPrime[j] = false;
			}
		}
	}
	
	// Print all prime number
	for (int i = 2; i <= n; i++) {
		if (isPrime[i]) cout << i << " ";
	}
	
	cout << endl;
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