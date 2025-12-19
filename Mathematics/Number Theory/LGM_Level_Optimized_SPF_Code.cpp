//
// Created by Sarvan Yaduvanshi on 10/12/25.
//

#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using i128 = __int128_t;
using ld  = long double;

constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD  = 1'000'000'007LL;
constexpr i64 MOD1 = 1'000'000'007LL;
constexpr i64 MOD2 = 998'244'353LL;
constexpr int MAXN = 1e7 + 5;  // Adjust depending on problem

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

// ---------------- Linear Sieve (O(N)) ----------------
vec<int> spf(MAXN);    // smallest prime factor
vec<int> primes;       // list of primes

void linear_sieve() {
    for (int i = 2; i < MAXN; ++i) {
        if (spf[i] == 0) { // If spf[i] is 0, 'i' is a prime number.
            spf[i] = i;
            primes.pb(i);
        }
        // This is the core of the linear sieve.
        // For each prime p, we mark p*i.
        // We stop if p > spf[i] because that ensures every composite is
        // marked exactly once by its smallest prime factor.
        for (int p : primes) {
            if (p > spf[i] || (i64)i * p >= MAXN) {
                break;
            }
            spf[i * p] = p;
        }
    }
}

// A slightly cleaner way to write the factorization logic.
// Functionally the same as yours, but common in top coder templates.
vec<pii<int, int>> get_prime_factorization(int n) {
    vec<pii<int, int>> factors;
    while (n != 1) {
        int p = spf[n];
        int count = 0;
        while (n % p == 0) {
            count++;
            n /= p;
        }
        factors.pb({p, count});
    }
    return factors;
}

void solve() {
    int num;
    cin >> num;

    if (num <= 1) {
        cout << "No prime factors\n";
        return;
    }

    vec<pii<int, int>> primeF = get_prime_factorization(num);

    cout << "Prime factors of " << num << ":\n";
    for (auto const& [p, cnt] : primeF) {
        cout << p << "^" << cnt << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // --- Precomputation is done ONCE ---
    linear_sieve();

    // --- Handle single or multiple test cases ---
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}

/*
Input:
6
1
2
60
97
999983
10000000
*/

/*
Expected Output:
Prime factors of 1:
(no factors)

Prime factors of 2:
2^1

Prime factors of 60:
2^2 3^1 5^1

Prime factors of 97:
97^1

Prime factors of 999983:
999983^1

Prime factors of 10000000:
2^7 5^7
*/
