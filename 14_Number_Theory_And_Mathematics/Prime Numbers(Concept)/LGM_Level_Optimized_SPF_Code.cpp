/*
Author: Sarvan.DP.GrandMaster
Created : 2025-12-28 02:08:06
*/

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

inline i64 gcd(i64 a, i64 b) { return std::gcd(a, b); }
inline i64 lcm(i64 a, i64 b) { return (a / std::gcd(a, b)) * b; }

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD) {
    i64 res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

constexpr int MAXN = 1e7 + 5;  // Adjust depending on problem
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
vec<pair<int, int>> get_prime_factorization(int n) {
    vec<pair<int, int>> factors;
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

    vec<pair<int, int>> primeF = get_prime_factorization(num);

    cout << "Prime factors of " << num << ":\n";
    for (auto const& [p, cnt] : primeF) {
        cout << p << "^" << cnt << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << fixed << setprecision(10);

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


