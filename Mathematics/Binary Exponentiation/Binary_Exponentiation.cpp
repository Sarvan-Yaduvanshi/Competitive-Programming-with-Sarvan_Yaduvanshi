//
// Created by Sarvan Yaduvanshi on 10/13/25.
//

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

// First the recursive approach
i64 binpow(i64 a, i64 b) {
    if (b == 0)
        return 1;
    i64 res = binpow(a, b / 2);
    if (b % 2)
        return res * res * a;
    else
        return res * res;
}

// Iterative Through
i64 binpow2(i64 a, i64 b) {
    i64 res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

void solve() {
   i64 a, b; cin >> a >> b;

    // Recursive Through
    cout << a << "^" << b << " = " << binpow(a, b) << endl;

    // Iterative Through
    cout << a << "^" << b << " = " << binpow2(a, b) << endl;
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