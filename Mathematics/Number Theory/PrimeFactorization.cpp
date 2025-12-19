//
// Created by Sarvan Yaduvanshi on 10/7/25.
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

// Prints all prime factors of n, including duplicates (e.g., 12 -> 2 2 3).
void primeFactorization(i64 n) {
    vector<i64> factorization;
    for (i64 i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            factorization.push_back(i);
            n /= i;
        }
    }
    // If n is still > 1, it must be a prime factor itself.
    if (n > 1) factorization.push_back(n);

    for (i64 factor : factorization) cout << factor << " ";
    cout << endl;
}

// Print all Distinct Prime factors
void distinctPrimeFactors(i64 n) {
    vector<i64> factorization;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            factorization.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    // checking for the only prime factor that is > sqrt(N)
    if (n > 1) factorization.push_back(n);

    for (auto factor : factorization) cout << factor << " ";
    cout << endl;
}

void solve() {
    i64 n;
    cin >> n;

    cout << "All prime factors including duplicates" << endl;
    primeFactorization(n);

    cout << "All distinct prime factors " << endl;
    distinctPrimeFactors(n);

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}