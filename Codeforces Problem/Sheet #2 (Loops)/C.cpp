// Author :  sarvan.dp.grandmaster
// Created :  2025-10-01 16:16:35
// Problem: C. Even, Odd, Positive and Negative
// Contest: Codeforces - Sheet #2 (Loops)
// URL: https://codeforces.com/group/MWSDmqGsZm/contest/219432/problem/C
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
    int n;
    cin >> n;

    int even_cnt = 0, odd_cnt = 0, pos_cnt = 0, neg_cnt = 0;

    for (int i = 0; i < n; i++) {
        int number;
        cin >> number;

        if (number % 2 == 0) even_cnt++;
        else odd_cnt++;

        if (number > 0) pos_cnt++;
        else if (number < 0) neg_cnt++;
    }

    cout << "Even: " << even_cnt << endl;
    cout << "Odd: " << odd_cnt << endl;
    cout << "Positive: " << pos_cnt << endl;
    cout << "Negative: " << neg_cnt << endl;
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