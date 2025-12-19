//
// Created by Sarvan Yaduvanshi on 10/10/25.
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

vec<pii<int, int>> primeFactorization(int x, vec<int>& spf) {
    vec<pii<int, int>> ans;
    while (x != 1) {
        int prime = spf[x];
        int count = 0;
        while (x % prime == 0) {
            count++;
            x /= prime;
        }
        ans.pb({prime, count});
    }

    return ans;
}

void solve() {
    int maxN = 1e6;
    vec<bool> isPrime(maxN, true);
    vec<int> spf(1e6, 1e9);
    for (i64 i = 2; i < maxN; i++) {
        if (isPrime[i]) {
            spf[i] = i;
            for (i64 j = i * i; j < maxN; j += i) {
                isPrime[j] = false;
                spf[j] = min(spf[j], spf[i]);
            }
        }
    }

    int num; cin >> num;
    vec<pii<int, int>> primeF = primeFactorization(num, spf);

    cout << "Prime factors of " << num << ":\n";
    for (auto [p, cnt] : primeF) {
        cout << p << "^" << cnt << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}