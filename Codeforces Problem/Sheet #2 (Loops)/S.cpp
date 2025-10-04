// Author :  sarvan.dp.grandmaster
// Created :  2025-10-02 22:15:55
// Problem: S. Sum of Consecutive Odd Numbers
// Contest: Codeforces - Sheet #2 (Loops)
// URL: https://codeforces.com/group/MWSDmqGsZm/contest/219432/problem/S
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
	int x, y; cin >> x >> y;
	
	// int sum = 0;
	// if (x > y) swap(x, y);
	// for (int i = x + 1; i < y; i++) {
		// if (i % 2 == 1) sum += i;
	// }
// 	
	// println("{}", sum);
	
	// Here is O(1) solution
	// 1. Establish the exclusive range [start_range + 1, end_range - 1]
    int start_range = min(x, y);
    int end_range = max(x, y);

    // 2. Find the first odd number in the range
    int first_odd = start_range + 1;
    if (first_odd % 2 == 0) {
        first_odd++;
    }

    // 3. Find the last odd number in the range
    int last_odd = end_range - 1;
    if (last_odd % 2 == 0) {
        last_odd--;
    }

    i64 sum = 0;
    
    // 4. If a valid range of odd numbers exists, calculate the sum
    if (first_odd <= last_odd) {
        // A) Calculate the number of terms in the series (e.g., for 5,7,9, it's 3)
        int num_terms = ((last_odd - first_odd) / 2) + 1;
        
        // B) Apply the arithmetic series sum formula: Sum = n/2 * (first + last)
        sum = (i64)num_terms * (first_odd + last_odd) / 2;
    }

    cout << sum << endl;
	
	
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