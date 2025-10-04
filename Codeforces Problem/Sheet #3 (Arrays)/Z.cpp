// Author :  sarvan.dp.grandmaster
// Created :  2025-10-03 18:16:36
// Problem: Z. Binary Search
// Contest: Codeforces - Sheet #3 (Arrays)
// URL: https://codeforces.com/group/MWSDmqGsZm/contest/219774/problem/Z
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
    i64 n, q; cin >> n >> q;
    
    vector<i64> a(n);
    for (auto &x : a) cin >> x;
    
    sort(a.begin(), a.end());
    
    for (int i = 0; i < q; i++) {
        i64 x; cin >> x;
        
        // bool found = false;
        // int L = 0, R = n - 1;
//         
        // while (L <= R) {
        	// i64 mid = L + (R - L) / 2;
        	// if (a[mid] == x) {
        		// found = true;
        		// break;
        	// } else if (a[mid] > x) R = mid - 1;
        	// else L = mid + 1;
        // }
//         
        // if (found) println("found");
        // else println("not found");
        
        // 2nd approach Using STL The Best CP Solution
        if (binary_search(a.begin(), a.end(), x)) println("found");
        else println("not found");
    }
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